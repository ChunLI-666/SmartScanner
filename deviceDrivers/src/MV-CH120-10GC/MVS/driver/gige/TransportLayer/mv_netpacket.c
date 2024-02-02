
#include <linux/skbuff.h>
#include <linux/ip.h>


#include "mv_netpacket.h"
#include "MvErrorDefine.h"
#include <asm-generic/errno.h>
#include <asm-generic/errno-base.h>

/*******************************************************************************
@   ����ԭ�ͣ�int NET_PacketDestroy(void* aPacket)
@   �������ܣ��������ݰ�
@   ����aPacket�� ���ݰ�buf
@   ����ֵ���ɹ�MV_OK��ʧ��MV_E_PARAMETER
*******************************************************************************/
int NET_PacketDestroy(void* aPacket)
{
    struct sk_buff* lSKBuffer = NULL;

    if(NULL == aPacket)
    {
        return MV_E_PARAMETER;
    }
    lSKBuffer = (struct sk_buff *)aPacket;

    kfree_skb(lSKBuffer);
    return MV_OK;
}

/*******************************************************************************
@   ����ԭ�ͣ�void* NET_PacketCopy(void* aPacket)
@   �������ܣ��������ݰ�
@   ����aPacket�� ���ݰ�buf
@   ����ֵ���ɹ�:���������ݰ�buf ʧ��NULL
*******************************************************************************/
void* NET_PacketCopy(void* aPacket)
{
    struct sk_buff* lSKBuffer = NULL;

    if(NULL == aPacket)
    {
        return NULL;
    }
    lSKBuffer = (struct sk_buff *)aPacket;

    return skb_copy(lSKBuffer, GFP_ATOMIC);
}

int NET_PacketCopyToUser(void* aPacket, unsigned int nOffset, void* pDst, unsigned int nLen)
{
    if (NULL == aPacket
        || NULL == pDst)
    {
        return -EINVAL;
    }

    return skb_copy_bits((struct sk_buff *)aPacket, nOffset, pDst, nLen);
}

/*******************************************************************************
@   ����ԭ�ͣ�NET_HEADER_IPV4* NET_ExtractIphdr(void* aPacket)
@   �������ܣ���ȡipͷ
@   ����aPacket�� ���ݰ�buf
@   ����ֵ���ɹ�:ipͷ ʧ��NULL
*******************************************************************************/
NET_HEADER_IPV4* NET_ExtractIphdr(void* aPacket)
{
    struct sk_buff* lSKBuffer = NULL;
    if(NULL == aPacket)
    {
        return NULL;
    }
    lSKBuffer = (struct sk_buff *)aPacket;

    return (NET_HEADER_IPV4 *)skb_network_header(lSKBuffer);
}

/*******************************************************************************
@   ����ԭ�ͣ�int	NET_ExtractIpLen(NET_HEADER_IPV4* aIpheader)
@   �������ܣ���ȡipͷ����
@   ����aIpheader�� ipͷ
@   ����ֵ���ɹ�:ip���� ʧ��:MV_E_PARAMETER
*******************************************************************************/
int NET_ExtractIpLen(NET_HEADER_IPV4* aIpheader)
{
    if(NULL == aIpheader)
    {
        return MV_E_PARAMETER;
    }
    return ((struct iphdr*)aIpheader)->ihl * 4;
}

/*******************************************************************************
@   ����ԭ�ͣ�unsigned char* NET_ExtractSkbufData(void *aPacket)
@   �������ܣ���ȡbuf�����ݲ���
@   ����aPacket�� ���ݰ�buf
@   ����ֵ���ɹ�:buf���ݲ��� ʧ��NULL
*******************************************************************************/
unsigned char* NET_ExtractSkbufData(void *aPacket)
{
    struct sk_buff* lSKBuffer = NULL;
    if(NULL == aPacket)
    {
        return NULL;
    }
    lSKBuffer = (struct sk_buff *)aPacket;
    return lSKBuffer->data;
}

/*******************************************************************************
@   ����ԭ�ͣ�unsigned short NET_Htons(unsigned short aAddr)
@   �������ܣ�������ת������(���ֽ�)
@   ����aAddr�� ��ַ
@   ����ֵ�������ֽ����ַ
*******************************************************************************/
unsigned short NET_Htons(unsigned short aAddr)
{
    return htons(aAddr);	
}

/*******************************************************************************
@   ����ԭ�ͣ�unsigned int NET_Htonl(unsigned int aAddr)
@   �������ܣ�������ת������(���ֽ�)
@   ����aAddr�� ��ַ
@   ����ֵ�������ֽ����ַ
*******************************************************************************/
unsigned int NET_Htonl(unsigned int aAddr)
{
    return htonl(aAddr);	
}

/*******************************************************************************
@   ����ԭ�ͣ�unsigned short NET_Htons(unsigned short aAddr)
@   �������ܣ�������ת������(���ֽ�)
@   ����aAddr�� ��ַ
@   ����ֵ�������ֽ����ַ
*******************************************************************************/
unsigned int NET_Ntohl(unsigned int aAddr)
{
    return ntohl(aAddr);	
}

/*******************************************************************************
@   ����ԭ�ͣ�unsigned int NET_Htonl(unsigned int aAddr)
@   �������ܣ�������ת������(���ֽ�)
@   ����aAddr�� ��ַ
@   ����ֵ�������ֽ����ַ
*******************************************************************************/
unsigned short NET_Ntohs(unsigned short aAddr)
{
    return ntohs(aAddr);	
}

