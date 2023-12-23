#include "tcpclient.h"

TcpClient::TcpClient(QObject *parent)
    : QTcpSocket(parent)
{
    connectSlots();
}

TcpClient::~TcpClient()
{
}

void TcpClient::onReadyRead()
{
    emit tcpReadyRead(this);
}

void TcpClient::onDisconnected()
{
    emit tcpDisconnected(this);
}

void TcpClient::onStateChanged(SocketState socketState)
{
    (void) socketState;
    emit tcpStateChanged(this);
}

void TcpClient::connectSlots()
{
    connect(this, &TcpClient::readyRead, this, &TcpClient::onReadyRead);
    connect(this, &TcpClient::disconnected, this, &TcpClient::onDisconnected);
    connect(this, &TcpClient::stateChanged, this, &TcpClient::onStateChanged);
}
