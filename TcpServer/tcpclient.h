#ifndef TCPCLIENT_H
#define TCPCLIENT_H

#include <QTcpSocket>

class TcpClient : public QTcpSocket
{
    Q_OBJECT
public:
    explicit TcpClient(QObject *parent = nullptr);
    virtual ~TcpClient();
signals:
    void tcpReadyRead(TcpClient *self);
    void tcpDisconnected(TcpClient *self);
    void tcpStateChanged(TcpClient *self);
private slots:
    void onReadyRead();
    void onDisconnected();
    void onStateChanged(QAbstractSocket::SocketState socketState);
private:
    void connectSlots();
};

#endif // TCPCLIENT_H
