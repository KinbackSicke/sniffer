#ifndef HEADERS_H
#define HEADERS_H

#ifndef WIN32
#define WIN32
#endif // !WIN32

#include "pcap.h"
#include <winsock2.h>
#include <QString>

/* 4字节的IP地址 */
typedef struct ip_address {
    u_char byte1;
    u_char byte2;
    u_char byte3;
    u_char byte4;
}ip_address;

/* IPv4 首部 */
typedef struct ip_header {
    u_char  ver_ihl;        // 版本 (4 bits) + 首部长度 (4 bits)
    u_char  tos;            // 服务类型(Type of service)
    u_short tlen;           // 总长(Total length)
    u_short identification; // 标识(Identification)
    u_short flags_fo;       // 标志位(Flags) (3 bits) + 段偏移量(Fragment offset) (13 bits)
    u_char  ttl;            // 存活时间(Time to live)
    u_char  proto;          // 协议(Protocol)
    u_short crc;            // 首部校验和(Header checksum)
    ip_address  saddr;      // 源地址(Source address)
    ip_address  daddr;      // 目的地址(Destination address)
    u_int   op_pad;         // 选项与填充(Option + Padding)
}ip_header;

// UDP 首部
typedef struct udp_header
{
    u_short sport;          // 源端口(Source port)
    u_short dport;          // 目的端口(Destination port)
    u_short len;            // UDP数据包长度(Datagram length)
    u_short crc;            // 校验和(Checksum)
}udp_header;

//TCP首部
typedef struct tcp_header
{
    unsigned short src_port;    //源端口号
    unsigned short dst_port;    //目的端口号
    unsigned int seq_no;        //序列号
    unsigned int ack_no;        //确认号
#if LITTLE_ENDIAN
    unsigned char reserved_1 : 4; //保留6位中的4位首部长度
    unsigned char thl : 4;        //tcp头部长度
    unsigned char flag : 6;       //6位标志
    unsigned char reseverd_2 : 2; //保留6位中的2位
#else
    unsigned char thl : 4;        //tcp头部长度
    unsigned char reserved_1 : 4; //保留6位中的4位首部长度
    unsigned char reseverd_2 : 2; //保留6位中的2位
    unsigned char flag : 6;       //6位标志
#endif
    unsigned short wnd_size;    //16位窗口大小
    unsigned short chk_sum;     //16位TCP检验和
    unsigned short urgt_p;      //16为紧急指针
}tcp_header;

// 数据包信息
typedef struct packet_info
{
    QString timestr;
    QString sip;
    QString dip;
    QString sport;
    QString dport;
    ip_header ipheader;
    tcp_header tcpheader;
    udp_header udpheader;
}packet_info;


#endif // HEADERS_H
