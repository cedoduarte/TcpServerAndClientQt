#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlDatabase>

class TcpServer;
class TcpClient;
class QTreeWidgetItem;
class Client;

namespace Ui
{
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
    virtual ~MainWindow();
private slots:
    void newTcpClientConnected(TcpClient *client);
    void tcpClientDisconnected(int socketDescriptor);
    void tcpClientReadyRead(TcpClient *client);
    void on_disconnectClientButton_clicked();    
    void on_treeWidget_itemClicked(QTreeWidgetItem *item, int column);
    void on_removeClientButton_clicked();
    void on_listenServerButton_clicked();
    void on_stopServerButton_clicked();
private:
    int clientIndex(int socketDescriptor) const;
    void addClient(TcpClient *client);
    QString clientStateToString(int state) const;
    void clearTreeWidget();
    bool usernameExists(const QString &username) const;
    QString generateUniqueUsername(const QString &baseName) const;
    void createTables() const;
    void insertClient(const Client *client) const;

    Ui::MainWindow *ui;
    TcpServer *m_tcpServer;
    QSqlDatabase m_db;
};

#endif // MAINWINDOW_H
