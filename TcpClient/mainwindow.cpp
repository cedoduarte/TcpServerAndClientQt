#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <cmath>
#include <QDebug>
#include <QSysInfo>
#include <QTcpSocket>
#include <QTextStream>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>
#include <QJsonParseError>
#include <QVariantMap>

#if defined(Q_OS_WIN)
#include <Windows.h>
#endif

#if defined(Q_OS_LINUX) || defined(Q_OS_UNIX)
#include <sys/sysinfo.h>
#endif

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    m_client = new QTcpSocket(this);
    m_client->connectToHost("localhost", 3333);
    m_client->waitForConnected();

    QString osName = QSysInfo::prettyProductName();

    // Get the operating system version
    QString osVersion = QSysInfo::productVersion();

    // Get the architecture of the CPU
    QString cpuArchitecture = QSysInfo::currentCpuArchitecture();

    double totalMemory = getTotalRam() / std::pow(1024.0, 3.0);
    QString totalRam = QString::number(totalMemory, 'f', 2) + " GB";

    QVariantMap osInfo {
        { "infoType", "OS-Info" },
        { "osName", osName },
        { "osVersion", osVersion },
        { "cpuArchitecture", cpuArchitecture },
        { "totalRam", totalRam }
    };

    QByteArray osInfoData = QJsonDocument::fromVariant(osInfo).toJson(QJsonDocument::Compact);

    QTextStream stream(m_client);
    stream << osInfoData;
}

MainWindow::~MainWindow()
{
    delete ui;
}

qint64 MainWindow::getTotalRam() const
{
#if defined(Q_OS_WIN)
        // Get total RAM on Windows
        MEMORYSTATUSEX memoryStatus;
        memoryStatus.dwLength = sizeof(memoryStatus);
        GlobalMemoryStatusEx(&memoryStatus);
        return static_cast<qint64>(memoryStatus.ullTotalPhys); // bytes
#endif

#if defined(Q_OS_LINUX) || defined(Q_OS_UNIX)
        // Get total RAM on Linux
        struct sysinfo sysInfo;
        if (sysinfo(&sysInfo) == 0) {
            return static_cast<qint64>(sysInfo.totalram) * sysInfo.mem_unit; // bytes
        }
#endif
    return 0;
}
