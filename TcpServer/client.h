#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>

class Client : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged FINAL)
    Q_PROPERTY(QString peerIpAddress READ peerIpAddress WRITE setPeerIpAddress NOTIFY peerIpAddressChanged FINAL)
    Q_PROPERTY(QString peerPort READ peerPort WRITE setPeerPort NOTIFY peerPortChanged FINAL)
    Q_PROPERTY(QString localIpAddress READ localIpAddress WRITE setLocalIpAddress NOTIFY localIpAddressChanged FINAL)
    Q_PROPERTY(QString localPort READ localPort WRITE setLocalPort NOTIFY localPortChanged FINAL)
    Q_PROPERTY(QString state READ state WRITE setState NOTIFY stateChanged FINAL)
    Q_PROPERTY(QString osName READ osName WRITE setOsName NOTIFY osNameChanged FINAL)
    Q_PROPERTY(QString osVersion READ osVersion WRITE setOsVersion NOTIFY osVersionChanged FINAL)
    Q_PROPERTY(QString cpuArchitecture READ cpuArchitecture WRITE setCpuArchitecture NOTIFY cpuArchitectureChanged FINAL)
    Q_PROPERTY(QString totalRam READ totalRam WRITE setTotalRam NOTIFY totalRamChanged FINAL)
    Q_PROPERTY(QString username READ username WRITE setUsername NOTIFY usernameChanged FINAL)
public:
    Client(QObject *parent = nullptr);

    Client(const Client &other);

    Client(const QString &name,
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
           QObject *parent = nullptr);

    virtual ~Client() {}

    QString name() const { return m_name; }
    QString peerIpAddress() const { return m_peerIpAddress; }
    QString peerPort() const { return m_peerPort; }
    QString localIpAddress() const { return m_localIpAddress; }
    QString localPort() const { return m_localPort; }
    QString state() const { return m_state; }
    QString osName() const { return m_osName; }
    QString osVersion() const { return m_osVersion; }
    QString cpuArchitecture() const { return m_cpuArchitecture; }
    QString totalRam() const { return m_totalRam; }
    QString username() const { return m_username; }

    Client* setName(const QString &name);
    Client* setPeerIpAddress(const QString &peerIpAddress);
    Client* setPeerPort(const QString &peerPort);
    Client* setLocalIpAddress(const QString &localIpAddress);
    Client* setLocalPort(const QString &localPort);
    Client* setState(const QString &state);
    Client* setOsName(const QString &osName);
    Client* setOsVersion(const QString &osVersion);
    Client* setCpuArchitecture(const QString &cpuArchitecture);
    Client* setTotalRam(const QString &totalRam);
    Client* setUsername(const QString &username);

    static QString sqlCreate();
    static QString sqlInsert();
signals:
    void nameChanged(const QString &name);
    void peerIpAddressChanged(const QString &peerIpAddress);
    void peerPortChanged(const QString &peerPort);
    void localIpAddressChanged(const QString &localIpAddress);
    void localPortChanged(const QString &localPort);
    void stateChanged(const QString &state);
    void osNameChanged(const QString &osName);
    void osVersionChanged(const QString &osVersion);
    void cpuArchitectureChanged(const QString &cpuArchitecture);
    void totalRamChanged(const QString &totalRam);
    void usernameChanged(const QString &username);
private:
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
};

#endif // CLIENT_H
