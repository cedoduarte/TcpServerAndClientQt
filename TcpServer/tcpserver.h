#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <QTcpServer>
#include <map>

class TcpClient;

class TcpServer : public QTcpServer
{
    Q_OBJECT
public:
    explicit TcpServer(QObject *parent = nullptr);
    virtual ~TcpServer();
    bool tcpListen(int port);
    void disconnectClient(int socketDescriptor);
    void stopServer();
signals:
    void newTcpClientConnected(TcpClient *client);
    void tcpClientDisconnected(int socketDescriptor);
    void tcpClientReadyRead(TcpClient *client);
protected:
    void incomingConnection(qintptr socketDescriptor);
private slots:
    void clientReadyRead(TcpClient *client);
    void clientDisconnected(TcpClient *client);
private:
    int socketDescriptorByClient(TcpClient *client) const;

    std::map<int, TcpClient*> m_clientList;
};

#endif // TCPSERVER_H
