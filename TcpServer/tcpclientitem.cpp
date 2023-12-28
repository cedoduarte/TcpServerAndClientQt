#include "tcpclientitem.h"

const QString TcpClientItem::s_unconnectedState = "Unconnected";
const QString TcpClientItem::s_disconnectedState = "Disconnected";
const QString TcpClientItem::s_hostLookupState = "Host look up";
const QString TcpClientItem::s_connectingState = "Connecting";
const QString TcpClientItem::s_connectedState = "Connected";
const QString TcpClientItem::s_boundState = "Bound";
const QString TcpClientItem::s_listeningState = "Listening";
const QString TcpClientItem::s_closingState = "Closing";

TcpClientItem::TcpClientItem()
{
    init();
    setChildrenItems();
    update();
}

TcpClientItem::~TcpClientItem()
{
}

void TcpClientItem::init()
{
    m_peerIpAddress = "unknown";
    m_peerPort = "unknown";
    m_localIpAddress = "unknown";
    m_localPort = "unknown";
    m_state = "unknown";
    m_osName = "unknown";
    m_osVersion ="unknown";
    m_cpuArchitecture = "unknown";
    m_totalRam = "unknown";

    m_peerIpAddressItem = new QTreeWidgetItem;
    m_peerPortItem = new QTreeWidgetItem;
    m_localIpAddressItem = new QTreeWidgetItem;
    m_localPortItem = new QTreeWidgetItem;
    m_stateItem = new QTreeWidgetItem;
    m_osNameItem = new QTreeWidgetItem;
    m_osVersionItem = new QTreeWidgetItem;
    m_cpuArchitectureItem = new QTreeWidgetItem;
    m_totalRamItem = new QTreeWidgetItem;
}

void TcpClientItem::setChildrenItems()
{
    addChildren({
        m_peerIpAddressItem,
        m_peerPortItem,
        m_localIpAddressItem,
        m_localPortItem,
        m_stateItem,
        m_osNameItem,
        m_osVersionItem,
        m_cpuArchitectureItem,
        m_totalRamItem
    });
}

void TcpClientItem::update()
{
    setText(0, "Client: " + m_name);
    m_peerIpAddressItem->setText(0, "Peer IP address: " + m_peerIpAddress);
    m_peerPortItem->setText(0, "Peer port: " + m_peerPort);
    m_localIpAddressItem->setText(0, "Local IP address: " + m_localIpAddress);
    m_localPortItem->setText(0, "Local port: " + m_localPort);
    m_stateItem->setText(0, "State: " + m_state);
    m_osNameItem->setText(0, "OS name: " + m_osName);
    m_osVersionItem->setText(0, "OS version: " + m_osVersion);
    m_cpuArchitectureItem->setText(0, "CPU Architecture: " + m_cpuArchitecture);
    m_totalRamItem->setText(0, "Total RAM: " + m_totalRam);
}
