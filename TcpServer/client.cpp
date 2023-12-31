#include "client.h"

Client::Client(QObject *parent)
    : QObject(parent)
{
}

Client::Client(const Client &other)
    : QObject(other.parent())
{
    m_name = other.m_name;
    m_peerIpAddress = other.m_peerIpAddress;
    m_peerPort = other.m_peerPort;
    m_localIpAddress = other.m_localIpAddress;
    m_localPort = other.m_localPort;
    m_state = other.m_state;
    m_osName = other.m_osName;
    m_osVersion = other.m_osVersion;
    m_cpuArchitecture = other.m_cpuArchitecture;
    m_totalRam = other.m_totalRam;
    m_username = other.m_username;
}

Client::Client(const QString &name,
               const QString &peerIpAddress,
               const QString &peerPort,
               const QString &localIpAddress,
               const QString &localPort,
               const QString &state,
               const QString &osName,
               const QString &osVersion,
               const QString &cpuArchitecture,
               const QString &totalRam,
               const QString &username,
               QObject *parent)
    : QObject(parent)
{
    m_name = name;
    m_peerIpAddress = peerIpAddress;
    m_peerPort = peerPort;
    m_localIpAddress = localIpAddress;
    m_localPort = localPort;
    m_state = state;
    m_osName = osName;
    m_osVersion = osVersion;
    m_cpuArchitecture = cpuArchitecture;
    m_totalRam = totalRam;
    m_username = username;
}

Client* Client::setName(const QString &name)
{
    if (m_name != name)
    {
        m_name = name;
        emit nameChanged(m_name);
    }
    return this;
}

Client* Client::setPeerIpAddress(const QString &peerIpAddress)
{
    if (m_peerIpAddress != peerIpAddress)
    {
        m_peerIpAddress = peerIpAddress;
        emit peerIpAddressChanged(m_peerIpAddress);
    }
    return this;
}

Client* Client::setPeerPort(const QString &peerPort)
{
    if (m_peerPort != peerPort)
    {
        m_peerPort = peerPort;
        emit peerPortChanged(m_peerPort);
    }
    return this;
}

Client* Client::setLocalIpAddress(const QString &localIpAddress)
{
    if (m_localIpAddress != localIpAddress)
    {
        m_localIpAddress = localIpAddress;
        emit localIpAddressChanged(m_localIpAddress);
    }
    return this;
}

Client* Client::setLocalPort(const QString &localPort)
{
    if (m_localPort != localPort)
    {
        m_localPort = localPort;
        emit localPortChanged(m_localPort);
    }
    return this;
}

Client* Client::setState(const QString &state)
{
    if (m_state != state)
    {
        m_state = state;
        emit stateChanged(m_state);
    }
    return this;
}

Client* Client::setOsName(const QString &osName)
{
    if (m_osName != osName)
    {
        m_osName = osName;
        emit osNameChanged(m_osName);
    }
    return this;
}

Client* Client::setOsVersion(const QString &osVersion)
{
    if (m_osVersion != osVersion)
    {
        m_osVersion = osVersion;
        emit osVersionChanged(m_osVersion);
    }
    return this;
}

Client* Client::setCpuArchitecture(const QString &cpuArchitecture)
{
    if (m_cpuArchitecture != cpuArchitecture)
    {
        m_cpuArchitecture = cpuArchitecture;
        emit cpuArchitectureChanged(m_cpuArchitecture);
    }
    return this;
}

Client* Client::setTotalRam(const QString &totalRam)
{
    if (m_totalRam != totalRam)
    {
        m_totalRam = totalRam;
        emit totalRamChanged(m_totalRam);
    }
    return this;
}

Client* Client::setUsername(const QString &username)
{
    if (m_username != username)
    {
        m_username = username;
        emit usernameChanged(m_username);
    }
    return this;
}

QString Client::sqlCreate()
{
    return "CREATE TABLE IF NOT EXISTS client("
           "id INTEGER PRIMARY KEY AUTOINCREMENT, "
           "name VARCHAR(256), "
           "peer_ip_address VARCHAR(256), "
           "peer_port VARCHAR(32), "
           "local_ip_address VARCHAR(256), "
           "local_port VARCHAR(32), "
           "state VARCHAR(256), "
           "os_name VARCHAR(256), "
           "os_version VARCHAR(256), "
           "cpu_architecture VARCHAR(32), "
           "total_ram VARCHAR(32), "
           "username VARCHAR(256))";
}

QString Client::sqlInsert()
{
    return "INSERT INTO client("
           "name,"
           "peer_ip_address,"
           "peer_port,"
           "local_ip_address,"
           "local_port,"
           "state,"
           "os_name,"
           "os_version,"
           "cpu_architecture,"
           "total_ram,"
           "username)"
           " VALUES("
           ":name,"
           ":peer_ip_address,"
           ":peer_port,"
           ":local_ip_address,"
           ":local_port,"
           ":state,"
           ":os_name,"
           ":os_version,"
           ":cpu_architecture,"
           ":total_ram,"
           ":username)";
}
