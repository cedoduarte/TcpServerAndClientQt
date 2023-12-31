#ifndef TCPCLIENTITEM_H
#define TCPCLIENTITEM_H

#include <QTreeWidgetItem>

class TcpClientItem : public QTreeWidgetItem
{
public:
    explicit TcpClientItem();
    virtual ~TcpClientItem();

    void update();

    QString name() const { return m_name; }
    QString peerIpAddress() const { return m_peerIpAddress; }
    QString peerPort() const { return m_peerPort; };
    QString localIpAddress() const { return m_localIpAddress; }
    QString localPort() const { return m_localPort; }
    QString state() const { return m_state; }
    QString osName() const { return m_osName; }
    QString osVersion() const { return m_osVersion; }
    QString cpuArchitecture() const { return m_cpuArchitecture; }
    QString totalRam() const { return m_totalRam; }
    QString username() const { return m_username; }

    TcpClientItem* setName(const QString &name)
    {
        m_name = name;
        return this;
    }

    TcpClientItem* setPeerIpAddress(const QString &peerIpAddress)
    {
        m_peerIpAddress = peerIpAddress;
        return this;
    }

    TcpClientItem* setPeerPort(const QString &peerPort)
    {
        m_peerPort = peerPort;
        return this;
    }

    TcpClientItem* setLocalIpAddress(const QString &localIpAddress)
    {
        m_localIpAddress = localIpAddress;
        return this;
    }

    TcpClientItem* setLocalPort(const QString &localPort)
    {
        m_localPort = localPort;
        return this;
    }

    TcpClientItem* setState(const QString &state)
    {
        m_state = state;
        return this;
    }

    TcpClientItem* setOsName(const QString &osName)
    {
        m_osName = osName;
        return this;
    }

    TcpClientItem* setOsVersion(const QString &osVersion)
    {
        m_osVersion = osVersion;
        return this;
    }

    TcpClientItem* setCpuArchitecture(const QString &cpuArchitecture)
    {
        m_cpuArchitecture = cpuArchitecture;
        return this;
    }

    TcpClientItem* setTotalRam(const QString &totalRam)
    {
        m_totalRam = totalRam;
        return this;
    }

    TcpClientItem* setUsername(const QString &username)
    {
        m_username = username;
        return this;
    }

    static QString unconnectedState() { return s_unconnectedState; }
    static QString disconnectedState() { return s_disconnectedState; }
    static QString hostLookupState() { return s_hostLookupState; }
    static QString connectingState() { return s_connectingState; }
    static QString connectedState() { return s_connectedState; }
    static QString boundState() { return s_boundState; }
    static QString listeningState() { return s_listeningState; }
    static QString closingState() { return s_closingState; }
private:
    void init();
    void setChildrenItems();

    QString m_name;
    QString m_peerIpAddress;
    QString m_peerPort;
    QString m_localIpAddress;
    QString m_localPort;
    QString m_state;
    QString m_osName;
    QString m_osVersion;
    QString m_cpuArchitecture;
    QString m_totalRam;
    QString m_username;

    QTreeWidgetItem *m_peerIpAddressItem;
    QTreeWidgetItem *m_peerPortItem;
    QTreeWidgetItem *m_localIpAddressItem;
    QTreeWidgetItem *m_localPortItem;
    QTreeWidgetItem *m_stateItem;
    QTreeWidgetItem *m_osNameItem;
    QTreeWidgetItem *m_osVersionItem;
    QTreeWidgetItem *m_cpuArchitectureItem;
    QTreeWidgetItem *m_totalRamItem;
    QTreeWidgetItem *m_usernameItem;

    static const QString s_unconnectedState;
    static const QString s_disconnectedState;
    static const QString s_hostLookupState;
    static const QString s_connectingState;
    static const QString s_connectedState;
    static const QString s_boundState;
    static const QString s_listeningState;
    static const QString s_closingState;
};

#endif // TCPCLIENTITEM_H
