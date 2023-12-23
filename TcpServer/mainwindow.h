#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class TcpServer;
class TcpClient;
class QTreeWidgetItem;

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
    void removeClient(int socketDescriptor);
    QString clientStateToString(int state) const;
    void clearTreeWidget();

    Ui::MainWindow *ui;
    TcpServer *m_tcpServer;
};

#endif // MAINWINDOW_H
