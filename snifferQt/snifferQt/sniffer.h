#ifndef SNIFFER_H
#define SNIFFER_H

#include <QMainWindow>
#include <pcap.h>
#include "headers.h"

QT_BEGIN_NAMESPACE
namespace Ui { class sniffer; }
QT_END_NAMESPACE

class sniffer : public QMainWindow
{
    Q_OBJECT

public:
    sniffer(QWidget *parent = nullptr);
    ~sniffer();
    void createItemsPCIRow(QString time, uint len, QString sip, QString dip,
       QString protrol, ushort sport, ushort dport, uchar ttl);
    void createItemsTrafficRow(QString sip, QString dip, int traffic);
    QString toIpString(uchar byte1, uchar byte2, uchar byte3, uchar byte4);
    packet_info packet(QString timestr, QString sip, QString dip, QString sport, QString dport,
        ip_header* ipheader, tcp_header* tcpheader, udp_header* udpheader);
private slots:
    void on_selectBtn_clicked(bool checked);

    void on_adapters_currentIndexChanged(int index);

    void on_PCITable_cellChanged(int row, int column);

    void on_captimeText_textChanged(const QString &arg1);

    void on_PCITable_cellClicked(int row, int column);

private:
    Ui::sniffer *ui;
};
#endif // SNIFFER_H
