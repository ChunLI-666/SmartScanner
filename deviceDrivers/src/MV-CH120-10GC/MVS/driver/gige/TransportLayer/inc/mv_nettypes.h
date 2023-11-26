
#ifndef __MV_NETTYPE_H__
#define __MV_NETTYPE_H__


#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus

//#include "misc.h"


#define NET_PROTOCOL_UDP                17


#pragma pack( push, 1 )
// ipv4 header
typedef struct
{
    // �汾��(Version)4bit, ��ͷ����(Internet Header Length��IHL)4bit
    unsigned char       		VersionAndHeaderLength;

    // �������� (Type of Service ��TOS) 8bit
    unsigned char       		DifferentiatedServices; 

    // �ܳ����ֶ� 16bit
    unsigned short     			TotalLength;
    
    // ��־�ֶ�: 16bit
    unsigned short      		Identification;

    // ��־λ�ֶ�: 3bit, ��ƫ���ֶΣ�13bit
    unsigned short      		FlagsAndFragmentOffset;
    
    // �����ڣ�TTL: Time to Live���ֶΣ�8bit
    unsigned char       		TTL;

    // Э���ֶ�: 8bit
    unsigned char       		Protocol;

    // ͷ��У����ֶ�: 16bit
    unsigned short      		HeaderChecksum ;
    
    // ԴIP��ַ��Ŀ��IP��ַ�ֶ�: ��32bit
    unsigned int				SourceIP;
    unsigned int	       		DestinationIP;

}NET_HEADER_IPV4;
#pragma pack( pop )


#pragma pack( push, 1 )
// udp header
typedef struct
{
    unsigned short 				SourcePort;
    unsigned short 				DestinationPort;
    unsigned short 				Length;
    unsigned short 				Checksum;
}NET_HEADER_UDP;
#pragma pack( pop )


#ifdef __cplusplus
}
#endif // __cplusplus


#endif	// __MV_NETTYPE_H__
