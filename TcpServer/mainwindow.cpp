#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "tcpserver.h"
#include "tcpclient.h"
#include "tcpclientitem.h"
#include "util.h"
#include "client.h"

#include <QDebug>
#include <QDateTime>
#include <QTreeWidgetItem>
#include <QTextStream>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>
#include <QJsonParseError>
#include <QVariantMap>
#include <QSqlQuery>
#include <QSqlError>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    m_db = QSqlDatabase::addDatabase("QSQLITE");
    m_db.setDatabaseName("tcp_server_database.sqlite");
    if (m_db.open())
    {
        createTables();
    }

    ui->txtPort->setText("3333");
    ui->stopServerButton->setEnabled(false);
    ui->disconnectClientButton->setEnabled(false);
    ui->removeClientButton->setEnabled(false);

    m_tcpServer = new TcpServer(this);
    connect(m_tcpServer, &TcpServer::newTcpClientConnected, this, &MainWindow::newTcpClientConnected);
    connect(m_tcpServer, &TcpServer::tcpClientDisconnected, this, &MainWindow::tcpClientDisconnected);
    connect(m_tcpServer, &TcpServer::tcpClientReadyRead, this, &MainWindow::tcpClientReadyRead);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::newTcpClientConnected(TcpClient *client)
{
    addClient(client);
}

void MainWindow::tcpClientDisconnected(int socketDescriptor)
{
    const int index = clientIndex(socketDescriptor);
    TcpClientItem *clientItem = dynamic_cast<TcpClientItem*>(ui->treeWidget->topLevelItem(index));
    clientItem->setState(TcpClientItem::disconnectedState())->update();
}

QString MainWindow::generateUniqueUsername(const QString &baseName) const
{
    QString timestamp = QDateTime::currentDateTime().toString("yyyyMMddhhmmss");
    return baseName + "_" + timestamp;
}

void MainWindow::createTables() const
{
    QSqlQuery query;
    if (query.prepare(Client::sqlCreate()))
    {
        if (query.exec())
        {
            qDebug() << "table 'client' created successfully!";
        }
        else
        {
            qDebug() << query.lastError().text() << __FILE__ << __LINE__;
        }
    }
    else
    {
        qDebug() << query.lastError().text() << __FILE__ << __LINE__;
    }
}

void MainWindow::insertClient(const Client *client) const
{
    QSqlQuery query;
    if (query.prepare(Client::sqlInsert()))
    {
        query.bindValue(":name", client->name());
        query.bindValue(":peer_ip_address", client->peerIpAddress());
        query.bindValue(":peer_port", client->peerPort());
        query.bindValue(":local_ip_address", client->localIpAddress());
        query.bindValue(":local_port", client->localPort());
        query.bindValue(":state", client->state());
        query.bindValue(":os_name", client->osName());
        query.bindValue(":os_version", client->osVersion());
        query.bindValue(":cpu_architecture", client->cpuArchitecture());
        query.bindValue(":total_ram", client->totalRam());
        query.bindValue(":username", client->username());
        if (query.exec())
        {
            qDebug() << "client inserted successfully!";
        }
        else
        {
            qDebug() << query.lastError().text() << __FILE__ << __LINE__;
        }
    }
    else
    {
        qDebug() << query.lastError().text() << __FILE__ << __LINE__;
    }
}

void MainWindow::tcpClientReadyRead(TcpClient *client)
{
    QTextStream stream(client);
    QString content = stream.readAll();
    if (Util::stringContains(content, {"\"infoType\":\"OS-Info\""}))
    {
        QJsonDocument doc = QJsonDocument::fromJson(content.toLatin1());
        QJsonObject osInfo = doc.object();

        QString username = osInfo["username"].toString();
        if (usernameExists(username))
        {
            username = generateUniqueUsername(username);
        }
        QString osName = osInfo["osName"].toString();
        QString osVersion = osInfo["osVersion"].toString();
        QString cpuArchitecture = osInfo["cpuArchitecture"].toString();
        QString totalRam = osInfo["totalRam"].toString();

        int itemIndex = clientIndex(client->socketDescriptor());
        TcpClientItem *clientItem = dynamic_cast<TcpClientItem*>(ui->treeWidget->topLevelItem(itemIndex));
        clientItem->setOsName(osName)
            ->setOsVersion(osVersion)
            ->setCpuArchitecture(cpuArchitecture)
            ->setTotalRam(totalRam)
            ->setUsername(username)
            ->update();

        Client *client = new Client;
        client->setName(clientItem->name())
            ->setPeerIpAddress(clientItem->peerIpAddress())
            ->setPeerPort(clientItem->peerPort())
            ->setLocalIpAddress(clientItem->localIpAddress())
            ->setLocalPort(clientItem->localPort())
            ->setState(clientItem->state())
            ->setOsName(clientItem->osName())
            ->setOsVersion(clientItem->osVersion())
            ->setCpuArchitecture(clientItem->cpuArchitecture())
            ->setTotalRam(clientItem->totalRam())
            ->setUsername(clientItem->username());
        insertClient(client);
        delete client;
    }
}

int MainWindow::clientIndex(int socketDescriptor) const
{
    for (int itemIndex = 0; itemIndex < ui->treeWidget->topLevelItemCount(); itemIndex++)
    {
        TcpClientItem *item = dynamic_cast<TcpClientItem*>(ui->treeWidget->topLevelItem(itemIndex));
        if (item->name() == QString::number(socketDescriptor))
        {
            return itemIndex;
        }
    }
    return -1;
}

void MainWindow::addClient(TcpClient *client)
{
    TcpClientItem *clientItem = new TcpClientItem;
    clientItem->setName(QString::number(client->socketDescriptor()))
        ->setPeerIpAddress(client->peerAddress().toString())
        ->setPeerPort(QString::number(client->peerPort()))
        ->setLocalIpAddress(client->localAddress().toString())
        ->setLocalPort(QString::number(client->localPort()))
        ->setState(clientStateToString(client->state()))
        ->update();
    ui->treeWidget->addTopLevelItem(clientItem);
}

QString MainWindow::clientStateToString(int state) const
{
    switch (state)
    {
        case TcpClient::UnconnectedState: return TcpClientItem::unconnectedState();
        case TcpClient::HostLookupState: return TcpClientItem::hostLookupState();
        case TcpClient::ConnectingState: return TcpClientItem::connectingState();
        case TcpClient::ConnectedState: return TcpClientItem::connectedState();
        case TcpClient::BoundState: return TcpClientItem::boundState();
        case TcpClient::ListeningState: return TcpClientItem::listeningState();
        case TcpClient::ClosingState: return TcpClientItem::closingState();
    }
    return "";
}

void MainWindow::clearTreeWidget()
{
    int total = ui->treeWidget->topLevelItemCount();
    for (int itemIndex = 0; itemIndex < total; itemIndex++)
    {
        delete ui->treeWidget->takeTopLevelItem(0);
    }
}

bool MainWindow::usernameExists(const QString &username) const
{
    for (int itemIndex = 0; itemIndex < ui->treeWidget->topLevelItemCount(); itemIndex++)
    {
        TcpClientItem *clientItem = dynamic_cast<TcpClientItem*>(ui->treeWidget->topLevelItem(itemIndex));
        if (clientItem->username() == username)
        {
            return true;
        }
    }
    return false;
}

void MainWindow::on_disconnectClientButton_clicked()
{
    QTreeWidgetItem *currentItem = ui->treeWidget->currentItem();
    TcpClientItem *clientItem = dynamic_cast<TcpClientItem*>(currentItem);
    if (clientItem)
    {
        int socketDescriptor = clientItem->name().toInt();
        m_tcpServer->disconnectClient(socketDescriptor);
        ui->disconnectClientButton->setEnabled(false);
        ui->removeClientButton->setEnabled(true);
    }
}

void MainWindow::on_treeWidget_itemClicked(QTreeWidgetItem *item, int column)
{
    (void) column;
    TcpClientItem *clientItem = dynamic_cast<TcpClientItem*>(item);
    if (clientItem)
    {
        ui->disconnectClientButton->setEnabled(clientItem->state() == TcpClientItem::connectedState());
        ui->removeClientButton->setEnabled(clientItem->state() == TcpClientItem::disconnectedState());
    }
    else
    {
        ui->disconnectClientButton->setEnabled(false);
        ui->removeClientButton->setEnabled(false);
    }
}

void MainWindow::on_removeClientButton_clicked()
{
    int topLevelIndex = ui->treeWidget->indexFromItem(ui->treeWidget->currentItem()).row();
    delete ui->treeWidget->takeTopLevelItem(topLevelIndex);
    ui->treeWidget->setCurrentItem(nullptr);
    ui->removeClientButton->setEnabled(false);
}

void MainWindow::on_listenServerButton_clicked()
{
    int port = ui->txtPort->text().toInt();
    if (m_tcpServer->tcpListen(port))
    {
        ui->listenServerButton->setText("Listening...");
        ui->listenServerButton->setEnabled(false);
        ui->stopServerButton->setEnabled(true);
    }
}

void MainWindow::on_stopServerButton_clicked()
{
    m_tcpServer->stopServer();
    ui->listenServerButton->setEnabled(true);
    ui->stopServerButton->setEnabled(false);
    clearTreeWidget();
}
