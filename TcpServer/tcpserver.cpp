#include "tcpserver.h"
#include "tcpclient.h"

TcpServer::TcpServer(QObject *parent)
    : QTcpServer(parent)
{
}

TcpServer::~TcpServer()
{
}

bool TcpServer::tcpListen(int port)
{
    return listen(QHostAddress::Any, port);
}

void TcpServer::disconnectClient(int socketDescriptor)
{
    auto it = m_clientList.find(socketDescriptor);
    if (it != m_clientList.end())
    {
        it->second->disconnectFromHost();
    }
}

void TcpServer::incomingConnection(qintptr socketDescriptor)
{
    TcpClient *client = new TcpClient;
    client->setSocketDescriptor(socketDescriptor);
    connect(client, &TcpClient::tcpReadyRead, this, &TcpServer::clientReadyRead);
    connect(client, &TcpClient::tcpDisconnected, this, &TcpServer::clientDisconnected);
    m_clientList[socketDescriptor] = client;
    emit newTcpClientConnected(client);
}

void TcpServer::clientReadyRead(TcpClient *client)
{
    emit tcpClientReadyRead(client);
}

void TcpServer::clientDisconnected(TcpClient *client)
{
    int socketDescriptor = socketDescriptorByClient(client);
    emit tcpClientDisconnected(socketDescriptor);
    m_clientList.erase(m_clientList.find(socketDescriptor));
    client->deleteLater();
}

int TcpServer::socketDescriptorByClient(TcpClient *client) const
{
    int socketDescriptor = -1;
    auto it = m_clientList.begin();
    for (; it != m_clientList.end(); it++)
    {
        if (it->second == client)
        {
            socketDescriptor = it->first;
            break;
        }
    }
    return socketDescriptor;
}
