#include "sniffer.h"
#include "ui_sniffer.h"
#include <QDebug>
#include <QTableWidgetItem>

pcap_if_t *alldevs;
pcap_if_t *d;
int i = 0;
int inum = 1;
pcap_t* adhandle;
char errbuf[PCAP_ERRBUF_SIZE];
u_int netmask;
char packet_filter[] = "ip";
struct bpf_program fcode;

int res;
struct tm* ltime;
char timestr[16];
struct pcap_pkthdr *header;
const u_char *pkt_data;
ip_header* ih;
udp_header* uh;
tcp_header* th;
u_int ip_len;
u_short sport, dport;
time_t local_tv_sec;

int captimes = 10;

QList<QString> adapterList;
QList<packet_info> packetList;

sniffer::sniffer(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::sniffer)
{
    ui->setupUi(this);
    /* 设置表格不可编辑,选中一行 */
    ui->PCITable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->PCITable->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->trafficTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->trafficTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    /* 设置文本框不可编辑 */
    ui->PCIText->setReadOnly(true);

    if (pcap_findalldevs(&alldevs, errbuf) == -1)
    {
        qDebug() << errbuf;
    }
    for (d = alldevs; d; d = d->next)
    {
        QString adapter = "";
        adapter.append(QString::number(++i, 10));
        adapter.append(d->name);
        // qDebug()<< ++i << d->name;
        if(d->description)
        {
            qDebug() << d->description;
            adapter.append(d->description);
        }
        else
        {
            qDebug() << "No description available ";
        }
        adapterList << adapter;
    }
    if (0 == i)
    {
        qDebug() << "No interfaces found!Make sure WinPcap is installed";
    }
    ui->adapters->addItems(adapterList);
}

sniffer::~sniffer()
{
    if (alldevs != NULL)
        pcap_freealldevs(alldevs);
    delete ui;
}

/* 往表格中添加数据 */
void sniffer::createItemsPCIRow(QString time, uint len, QString sip, QString dip,QString protrol,
    ushort sport, ushort dport, uchar ttl)
{
    int rowcount = ui->PCITable->rowCount();
    ui->PCITable->setRowCount(rowcount + 1);
    // qDebug() << rowcount;
    ui->PCITable->setItem(rowcount, 0, new QTableWidgetItem(time));
    ui->PCITable->setItem(rowcount, 1, new QTableWidgetItem(QString::number(len)));
    ui->PCITable->setItem(rowcount, 2, new QTableWidgetItem(sip));
    ui->PCITable->setItem(rowcount, 3, new QTableWidgetItem(dip));
    ui->PCITable->setItem(rowcount, 4, new QTableWidgetItem(protrol));
    ui->PCITable->setItem(rowcount, 5, new QTableWidgetItem(QString::number(sport)));
    ui->PCITable->setItem(rowcount, 6, new QTableWidgetItem(QString::number(dport)));
    ui->PCITable->setItem(rowcount, 7, new QTableWidgetItem(QString::number(ttl)));    
    ui->PCITable->repaint();
}

void sniffer::createItemsTrafficRow(QString sip, QString dip, int traffic)
{
    int rowcount = ui->trafficTable->rowCount();
    ui->trafficTable->setRowCount(rowcount + 1);
    ui->trafficTable->setItem(rowcount, 0, new QTableWidgetItem(sip));
    ui->trafficTable->setItem(rowcount, 1, new QTableWidgetItem(dip));
    ui->trafficTable->setItem(rowcount, 2, new QTableWidgetItem(QString::number(traffic)));
    ui->trafficTable->repaint();
}

/* 将ip4地址转化为地址字符串 */
QString sniffer::toIpString(uchar byte1, uchar byte2, uchar byte3, uchar byte4)
{
    QString str = "";
    str.append(QString::number(byte1));
    str.append(".");
    str.append(QString::number(byte2));
    str.append(".");
    str.append(QString::number(byte3));
    str.append(".");
    str.append(QString::number(byte4));
    return str;
}

packet_info sniffer::packet(QString timestr, QString sip, QString dip, QString sport, QString dport,
    ip_header* ipheader, tcp_header* tcpheader, udp_header* udpheader)
{
    packet_info info;

    info.timestr = timestr;
    info.sip = sip;
    info.dip = dip;
    info.sport = sport;
    info.dport = dport;
    info.ipheader = *ipheader;
    if (tcpheader != NULL) info.tcpheader = *tcpheader;
    if (udpheader != NULL) info.udpheader = *udpheader;
    return info;
}

void sniffer::on_selectBtn_clicked(bool checked)
{
    /* 跳转到已选设备 */
    for (d = alldevs, i = 0; i < inum - 1; d = d->next, i++);

    /* 打开适配器 */
    if ((adhandle = pcap_open(d->name,  // 设备名
        65536,                          // 要捕捉的数据包的部分
                                        // 65535保证能捕获到不同数据链路层上的每个数据包的全部内容
        PCAP_OPENFLAG_PROMISCUOUS,      // 混杂模式
        1000,                           // 读取超时时间
        NULL,                           // 远程机器验证
        errbuf                          // 错误缓冲池
        )) == NULL)
    {
        qDebug() << "\nUnable to open the adapter." << d->name << "is not supported by WinPcap";
        pcap_freealldevs(alldevs);
        return;
    }

    /* 检查数据链路层，为了简单，我们只考虑以太网 */
    if (pcap_datalink(adhandle) != DLT_EN10MB)
    {
        qDebug() << "This program works only on Ethernet networks.";
        /* 释放设备列表 */
        pcap_freealldevs(alldevs);
        return;
    }

    if (d->addresses != NULL)
        /* 获得接口第一个地址的掩码 */
        netmask = ((struct sockaddr_in*)(d->addresses->netmask))->sin_addr.S_un.S_addr;
    else
        /* 如果接口没有地址，那么我们假设一个C类的掩码 */
        netmask = 0xffffff;

    //编译过滤器
    if (pcap_compile(adhandle, &fcode, packet_filter, 1, netmask) < 0)
    {
        qDebug() << "\nUnable to compile the packet filter. Check the syntax.";
        /* 释放设备列表 */
        pcap_freealldevs(alldevs);
        return;
    }

    //设置过滤器
    if (pcap_setfilter(adhandle, &fcode) < 0)
    {
        qDebug() << "\nError setting the filter.";
        /* 释放设备列表 */
        pcap_freealldevs(alldevs);
        return;
    }

    qDebug() << "Listening on " << d->name << "...";

    /* 释放设备列表 */
    // pcap_freealldevs(alldevs);
    /* 开始捕捉 */
    int j = 0;
    while ((res = pcap_next_ex(adhandle, &header, &pkt_data)) >= 0 && j < captimes)
    {
        if (res == 0)
        {
            /* 超时时间到 */
            qDebug() << "Out of time";
            continue;
        }

        /* 将时间戳转换成可识别的格式 */
        local_tv_sec = header->ts.tv_sec;
        ltime = localtime(&local_tv_sec);
        strftime(timestr, sizeof timestr, "%H:%M:%S", ltime);

        /* 获得IP数据包头部的位置，以太网头部长度, 14字节为mac头长度 */
        ih = (ip_header*)(pkt_data + 14);

        packet_info info;       
        /* TCP协议 */
        if (IPPROTO_TCP == ih->proto)
        {

            ip_len = (ih->ver_ihl & 0xf) * 4;

            u_short tlen = ntohs(ih->tlen);
            th = (tcp_header*)((u_char*)ih + ip_len);
            sport = ntohs(th->src_port);
            dport = ntohs(th->dst_port);
            // 将ip地址转化为“xxx.xxx.xxx.xxx”格式字符串
            QString sip = toIpString(ih->saddr.byte1, ih->saddr.byte2, ih->saddr.byte3, ih->saddr.byte4);
            QString dip = toIpString(ih->daddr.byte1, ih->daddr.byte2, ih->daddr.byte3, ih->daddr.byte4);
            createItemsPCIRow(timestr, tlen, sip, dip, "TCP", sport, dport, ih->ttl);
            info = packet(timestr, sip, dip, QString::number(sport), QString::number(dport), ih, th, NULL);
            packetList.append(info);
        }
        /* UDP协议 */
        if (IPPROTO_UDP == ih->proto)
        {            
            ip_len = (ih->ver_ihl & 0xf) * 4;
            u_short tlen = ntohs(ih->tlen);
            uh = (udp_header*)((u_char*)ih + ip_len);
            sport = ntohs(uh->sport);
            dport = ntohs(uh->dport);
            QString sip = toIpString(ih->saddr.byte1, ih->saddr.byte2, ih->saddr.byte3, ih->saddr.byte4);
            QString dip = toIpString(ih->daddr.byte1, ih->daddr.byte2, ih->daddr.byte3, ih->daddr.byte4);
            createItemsPCIRow(timestr, tlen, sip, dip, "UDP", sport, dport, ih->ttl);
            info = packet(timestr, sip, dip, QString::number(sport), QString::number(dport), ih, NULL, uh);
            packetList.append(info);
        }
        j++;

        if (res == -1)
        {
            qDebug() << "Error reading the packets: " << pcap_geterr(adhandle);
            return;
        }
    }


}

void sniffer::on_adapters_currentIndexChanged(int index)
{
    inum = index + 1;
    // qDebug() << inum;
}


void sniffer::on_PCITable_cellChanged(int row, int column)
{
    if (column != 3)
        return;

    // 统计源ip到目的ip地址的流量
    QTableWidgetItem* item;
    int k;

    // 获取当前数据包的源ip地址
    item = ui->PCITable->item(row, column - 1);
    QString sip = item->text();
    // qDebug() << sip;
    // 获取当前数据包目的ip地址
    item = ui->PCITable->item(row, column);
    QString dip = item->text();
    // qDebug() << dip;
    // 统计流量
    int trafrow = ui->trafficTable->rowCount();
    if (trafrow == 0)
    {
        createItemsTrafficRow(sip, dip, 1);
        return;
    }

    for (k = 0; k < trafrow; k++)
    {
        // 比较源ip和目的ip地址
        QString sip1 = ui->trafficTable->item(k, 0)->text();
        QString dip1 = ui->trafficTable->item(k, 1)->text();
        if (QString::compare(sip, sip1) == 0 && QString::compare(dip, dip1) == 0)
            break;
    }

    if (k < trafrow)    // ip已在列表中，将对应数据包数加1
    {
        item = ui->trafficTable->item(k, 2);
        int num = item->text().toInt() + 1;
        ui->trafficTable->setItem(k, 2, new QTableWidgetItem(QString::number(num)));
        ui->trafficTable->repaint();
    }
    else            // ip不在列表中，将ip添加到列表中
    {
        createItemsTrafficRow(sip, dip, 1);
    }

}

void sniffer::on_captimeText_textChanged(const QString &text)
{
    captimes = text.toInt();
    if (captimes <= 0)
        captimes = 10;
    // qDebug() << captimes;
}


void sniffer::on_PCITable_cellClicked(int row, int column)
{
    ui->PCIText->clear();
    packet_info packet = packetList.at(row);
    ui->PCIText->append(QString("时间(Time)：%1").arg(packet.timestr));
    ui->PCIText->append(QString("IP协议版本号(Version)：V%1").arg((packet.ipheader.ver_ihl & 0xf0) >> 4));
    ui->PCIText->append(QString("首部大小(Header Length)：%1").arg((packet.ipheader.ver_ihl & 0xf) * 4));
    ui->PCIText->append(QString("服务类型(Type Of Service)：%1").arg(ntohs(packet.ipheader.tos)));
    ui->PCIText->append(QString("数据包总长度(Total Length)：%1").arg(ntohs(packet.ipheader.tlen)));
    ui->PCIText->append(QString("身份标识(Identification)：%1").arg(ntohs(packet.ipheader.identification)));
    ui->PCIText->append(QString("存活时间(Time To Live)：%1").arg(packet.ipheader.ttl));
    ui->PCIText->append(QString("标志位&偏移(Flags & Offset)：%1B").arg(ntohs(packet.ipheader.flags_fo), 16, 2, QLatin1Char('0')));
    ui->PCIText->append(QString("首部校验和(Checksum)：0x%1").arg(ntohs(packet.ipheader.crc), 4, 16, QLatin1Char('0')));
    ui->PCIText->append(QString("源ip地址(Source Address)：%1").arg(packet.sip));
    ui->PCIText->append(QString("目的ip地址(Destination address)：%1").arg(packet.dip));
    ui->PCIText->append("");
    // ui->PCIText->append(QString::number(packet.ipheader.proto));
    if (IPPROTO_TCP == packet.ipheader.proto)
    {
        ui->PCIText->append("传输协议(Protocol)：TCP");
        ui->PCIText->append(QString("源端口号(Source Port)：%1").arg(ntohs(packet.tcpheader.src_port)));
        ui->PCIText->append(QString("目的端口号(Destination Port)：%1").arg(ntohs(packet.tcpheader.dst_port)));
        ui->PCIText->append(QString("序列号(Sequence Number)：%1").arg(ntohl(packet.tcpheader.seq_no)));
        ui->PCIText->append(QString("确认号(ACK Number)：%1").arg(ntohl(packet.tcpheader.ack_no)));
        ui->PCIText->append(QString("窗口大小(Window Size)：%1").arg(ntohs(packet.tcpheader.wnd_size)));
        ui->PCIText->append(QString("头部长度(Header Length)：%1").arg(packet.tcpheader.thl * 4));
        ui->PCIText->append(QString("标志位(Flags)：%1B").arg(packet.tcpheader.flag, 8, 2, QLatin1Char('0')));
        ui->PCIText->append(QString("紧急指针(Urgent Pointer)：%1").arg(ntohs(packet.tcpheader.urgt_p)));
        ui->PCIText->append(QString("TCP首部校验和(Header Checksum)：0x%1").arg(ntohs(packet.tcpheader.chk_sum), 4, 16, QLatin1Char('0')));

    }

    if (IPPROTO_UDP == packet.ipheader.proto)
    {
        ui->PCIText->append("传输协议(Protocol)：UDP");
        ui->PCIText->append(QString("源端口号(Source Port)：%1").arg(ntohs(packet.udpheader.sport)));
        ui->PCIText->append(QString("目的端口号(Destination Port)：%1").arg(ntohs(packet.udpheader.dport)));
        ui->PCIText->append(QString("数据长度(Data Length)：%1").arg(ntohs(packet.udpheader.len)));
    }


}
