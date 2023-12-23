#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "tcpserver.h"
#include "tcpclient.h"
#include "tcpclientitem.h"
#include "util.h"

#include <QDebug>
#include <QTreeWidgetItem>
#include <QTreeWidgetItemIterator>
#include <QTextStream>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>
#include <QJsonParseError>
#include <QVariantMap>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->disconnectClientButton->setEnabled(false);
    ui->removeClientButton->setEnabled(false);

    m_tcpServer = new TcpServer(this);
    connect(m_tcpServer, &TcpServer::newTcpClientConnected, this, &MainWindow::newTcpClientConnected);
    connect(m_tcpServer, &TcpServer::tcpClientDisconnected, this, &MainWindow::tcpClientDisconnected);
    connect(m_tcpServer, &TcpServer::tcpClientReadyRead, this, &MainWindow::tcpClientReadyRead);
    m_tcpServer->tcpListen(3333);
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

void MainWindow::tcpClientReadyRead(TcpClient *client)
{
    QTextStream stream(client);
    QString content = stream.readAll();
    if (Util::stringContains(content, {"osName","osVersion","cpuArchitecture"}))
    {
        QJsonDocument doc = QJsonDocument::fromJson(content.toLatin1());
        QJsonObject osInfo = doc.object();
        QString osName = osInfo["osName"].toString();
        QString osVersion = osInfo["osVersion"].toString();
        QString cpuArchitecture = osInfo["cpuArchitecture"].toString();
        QString totalRam = osInfo["totalRam"].toString();
        int index = clientIndex(client->socketDescriptor());
        TcpClientItem *clientItem = dynamic_cast<TcpClientItem*>(ui->treeWidget->topLevelItem(index));
        clientItem->setOsName(osName)
            ->setOsVersion(osVersion)
            ->setCpuArchitecture(cpuArchitecture)
            ->setTotalRam(totalRam)
            ->update();
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

void MainWindow::removeClient(int socketDescriptor)
{
    // todo...
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

