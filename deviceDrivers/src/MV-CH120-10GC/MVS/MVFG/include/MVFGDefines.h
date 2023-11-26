#ifndef _MV_FG_DEFINES_H_
#define _MV_FG_DEFINES_H_

#  if defined(_WIN32)
#    if defined(_MSC_VER) && _MSC_VER >= 1600 /* VS2010 provides stdint.h */
#      include <stdint.h>
#    elif !defined _STDINT_H && !defined _STDINT
       /* stdint.h is usually not available under Windows */
       typedef unsigned char uint8_t;
       typedef __int32 int32_t;
       typedef __int64 int64_t;
       typedef unsigned __int32 uint32_t;
       typedef unsigned __int64 uint64_t;
#    endif
#  else
#    include <stdint.h>
#  endif

#ifdef __cplusplus
     typedef bool bool8_t;
#else
     typedef uint8_t bool8_t;
#endif
typedef unsigned int bool32_t;

#ifndef WIN32
   #ifndef __stdcall
        #define __stdcall
    #endif
#endif

#ifdef __cplusplus
extern "C" {
#endif 

/// \~chinese ������Ͷ���        \~english Handle type definition
typedef void*  IFHANDLE;                                            ///< \~chinese �ɼ������    \~english Interface handle
typedef void*  DEVHANDLE;                                           ///< \~chinese ������      \~english Device handle
typedef void*  STREAMHANDLE;                                        ///< \~chinese ȡ�����      \~english Stream handle
typedef void*  BUFFERHANDLE;                                        ///< \~chinese ������      \~english Buffer handle
typedef void*  PORTHANDLE;                                          ///< \~chinese �������������ʹ�òɼ���/���/�����  \~english Port handle, (Can use Interface/Device/Stream handle)
typedef void*  IMAGEHANDLE;                                         ///< \~chinese ͼ����������ʹ�òɼ���/���/�����  \~english Image handle, (Can use Interface/Device/Stream handle)

///< \~chinese �ɼ�������         \~english Interface type
#define MV_FG_GEV_INTERFACE                     0x00000001          ///< \~chinese GigE Vision�ɼ���        \~english GigE Vision interface
#define MV_FG_U3V_INTERFACE                     0x00000002          ///< \~chinese U3V�ɼ���                \~english U3V interface
#define MV_FG_CAMERALINK_INTERFACE              0x00000004          ///< \~chinese Camera Link�ɼ���        \~english Camera Link interface
#define MV_FG_CXP_INTERFACE                     0x00000008          ///< \~chinese CoaXPress�ɼ���          \~english CoaXPress interface
#define MV_FG_XoF_INTERFACE                     0x00000010          ///< \~chinese XoFLink�ɼ���            \~english XoFLink interface

///< \~chinese ����Ϣ���ַ�����󳤶�      \~english Maximum string length of interface information
#define MV_FG_MAX_IF_INFO_SIZE                  64

///< \~chinese �ɼ���Ȩ��         \~english Interface access mode
#define MV_FG_ACCESS_UNKNOWN                    0x0                 ///< \~chinese Ȩ��δ����    \~english Access mode not defined
#define MV_FG_ACCESS_READONLY                   0x1                 ///< \~chinese ֻ��Ȩ��      \~english Read only mode
#define MV_FG_ACCESS_CONTROL                    0x2                 ///< \~chinese ����Ȩ��      \~english Control mode

///< \~chinese CoaXPress�ɼ�����Ϣ         \~english CoaXPress interface information
typedef struct _MV_CXP_INTERFACE_INFO_
{
    unsigned char       chInterfaceID[MV_FG_MAX_IF_INFO_SIZE];      ///< \~chinese �ɼ���ID    \~english Interface ID
    unsigned char       chDisplayName[MV_FG_MAX_IF_INFO_SIZE];      ///< \~chinese ��ʾ����    \~english Display name
    unsigned char       chSerialNumber[MV_FG_MAX_IF_INFO_SIZE];     ///< \~chinese ���к�      \~english Serial number

    // ��16λ��Ч: bits(0~2)������, bits(3~7)�������, bits(8-15)��������
    // The lower 16 bits are valid: bits (0~2) represents the function, bits (3~7) represents the device, and bits (8~15) represents the bus
    // |15  14  13  12  11  10  9  8 | 7  6  5  4  3 | 2  1  0 |
    // +-----------------------------+---------------+---------+
    // |             bus             |    device     |  func   |
    unsigned int        nPCIEInfo;                                  ///< \~chinese �ɼ�����PCIE�����Ϣ  \~english PCIe slot information of interface

    unsigned char       chModelName[MV_FG_MAX_IF_INFO_SIZE];        ///< [OUT] \~chinese �ͺ�       \~english model name
    unsigned char       chManufacturer[MV_FG_MAX_IF_INFO_SIZE];     ///< [OUT] \~chinese ����       \~english manufacturer name
    unsigned char       chDeviceVersion[MV_FG_MAX_IF_INFO_SIZE];    ///< [OUT] \~chinese �汾��     \~english device version
    unsigned char       chUserDefinedName[MV_FG_MAX_IF_INFO_SIZE];  ///< [OUT] \~chinese �Զ������� \~english user defined name

}MV_CXP_INTERFACE_INFO;

///< \~chinese GigE Vision�ɼ�����Ϣ         \~english GigE Vision interface information
typedef struct _MV_GEV_INTERFACE_INFO_
{
    unsigned char       chInterfaceID[MV_FG_MAX_IF_INFO_SIZE];      ///< \~chinese �ɼ���ID    \~english Interface ID
    unsigned char       chDisplayName[MV_FG_MAX_IF_INFO_SIZE];      ///< \~chinese ��ʾ����    \~english Display name
    unsigned char       chSerialNumber[MV_FG_MAX_IF_INFO_SIZE];     ///< \~chinese ���к�      \~english Serial number

    // ��16λ��Ч: bits(0~2)������, bits(3~7)�������, bits(8-15)��������
    // The lower 16 bits are valid: bits (0~2) represents the function, bits (3~7) represents the device, and bits (8~15) represents the bus
    // |15  14  13  12  11  10  9  8 | 7  6  5  4  3 | 2  1  0 |
    // +-----------------------------+---------------+---------+
    // |             bus             |    device     |  func   |
    unsigned int        nPCIEInfo;                                  ///< \~chinese �ɼ�����PCIE�����Ϣ  \~english PCIe slot information of interface

    unsigned char       chModelName[MV_FG_MAX_IF_INFO_SIZE];        ///< [OUT] \~chinese �ͺ�       \~english model name
    unsigned char       chManufacturer[MV_FG_MAX_IF_INFO_SIZE];     ///< [OUT] \~chinese ����       \~english manufacturer name
    unsigned char       chDeviceVersion[MV_FG_MAX_IF_INFO_SIZE];    ///< [OUT] \~chinese �汾��     \~english device version
    unsigned char       chUserDefinedName[MV_FG_MAX_IF_INFO_SIZE];  ///< [OUT] \~chinese �Զ������� \~english user defined name

}MV_GEV_INTERFACE_INFO;

///< \~chinese Camera Link�ɼ�����Ϣ         \~english Camera Link interface information
typedef struct _MV_CML_INTERFACE_INFO_
{
    unsigned char       chInterfaceID[MV_FG_MAX_IF_INFO_SIZE];      ///< \~chinese �ɼ���ID    \~english Interface ID
    unsigned char       chDisplayName[MV_FG_MAX_IF_INFO_SIZE];      ///< \~chinese ��ʾ����    \~english Display name
    unsigned char       chSerialNumber[MV_FG_MAX_IF_INFO_SIZE];     ///< \~chinese ���к�      \~english Serial number

    // ��16λ��Ч: bits(0~2)������, bits(3~7)�������, bits(8-15)��������
    // The lower 16 bits are valid: bits (0~2) represents the function, bits (3~7) represents the device, and bits (8~15) represents the bus
    // |15  14  13  12  11  10  9  8 | 7  6  5  4  3 | 2  1  0 |
    // +-----------------------------+---------------+---------+
    // |             bus             |    device     |  func   |
    unsigned int        nPCIEInfo;                                  ///< \~chinese �ɼ�����PCIE�����Ϣ  \~english PCIe slot information of interface

    unsigned char       chModelName[MV_FG_MAX_IF_INFO_SIZE];        ///< [OUT] \~chinese �ͺ�       \~english model name
    unsigned char       chManufacturer[MV_FG_MAX_IF_INFO_SIZE];     ///< [OUT] \~chinese ����       \~english manufacturer name
    unsigned char       chDeviceVersion[MV_FG_MAX_IF_INFO_SIZE];    ///< [OUT] \~chinese �汾��     \~english device version
    unsigned char       chUserDefinedName[MV_FG_MAX_IF_INFO_SIZE];  ///< [OUT] \~chinese �Զ������� \~english user defined name

}MV_CML_INTERFACE_INFO;

///< \~chinese XoFLink�ɼ�����Ϣ         \~english XoFLink interface information
typedef struct _MV_XoF_INTERFACE_INFO_
{
    unsigned char       chInterfaceID[MV_FG_MAX_IF_INFO_SIZE];      ///< \~chinese �ɼ���ID    \~english Interface ID
    unsigned char       chDisplayName[MV_FG_MAX_IF_INFO_SIZE];      ///< \~chinese ��ʾ����    \~english Display name
    unsigned char       chSerialNumber[MV_FG_MAX_IF_INFO_SIZE];     ///< \~chinese ���к�      \~english Serial number

    // ��16λ��Ч: bits(0~2)������, bits(3~7)�������, bits(8-15)��������
    // The lower 16 bits are valid: bits (0~2) represents the function, bits (3~7) represents the device, and bits (8~15) represents the bus
    // |15  14  13  12  11  10  9  8 | 7  6  5  4  3 | 2  1  0 |
    // +-----------------------------+---------------+---------+
    // |             bus             |    device     |  func   |
    unsigned int        nPCIEInfo;                                  ///< \~chinese �ɼ�����PCIE�����Ϣ  \~english PCIe slot information of interface

    unsigned char       chModelName[MV_FG_MAX_IF_INFO_SIZE];        ///< [OUT] \~chinese �ͺ�       \~english model name
    unsigned char       chManufacturer[MV_FG_MAX_IF_INFO_SIZE];     ///< [OUT] \~chinese ����       \~english manufacturer name
    unsigned char       chDeviceVersion[MV_FG_MAX_IF_INFO_SIZE];    ///< [OUT] \~chinese �汾��     \~english device version
    unsigned char       chUserDefinedName[MV_FG_MAX_IF_INFO_SIZE];  ///< [OUT] \~chinese �Զ������� \~english user defined name

}MV_XoF_INTERFACE_INFO;

///< \~chinese �ɼ�����Ϣ            \~english Interface information
typedef struct _MV_FG_INTERFACE_INFO_
{
    unsigned int        nTLayerType;                                ///< \~chinese �ɼ�������    \~english Interface type
    unsigned int        nReserved[4];                               ///< \~chinese �����ֶ�      \~english Reserved

    union
    {
        MV_CXP_INTERFACE_INFO   stCXPIfaceInfo;                     ///< \~chinese CoaXPress�ɼ�����Ϣ          \~english CoaXPress interface information
        MV_GEV_INTERFACE_INFO   stGEVIfaceInfo;                     ///< \~chinese GigE Vision�ɼ�����Ϣ        \~english GigE Vision interface information
        MV_CML_INTERFACE_INFO   stCMLIfaceInfo;                     ///< \~chinese Camera Link�ɼ�����Ϣ        \~english Camera Link interface information
        MV_XoF_INTERFACE_INFO   stXoFIfaceInfo;                     ///< \~chinese XoFLink�ɼ�����Ϣ            \~english XoFLink interface information

        unsigned int            nReserved[256];                     ///< \~chinese �����ֶ�     \~english Reserved
        // more ...
    }IfaceInfo;

}MV_FG_INTERFACE_INFO;

///< \~chinese �����Ϣ����󳤶�        \~english Maximum length of device information
#define MV_FG_MAX_DEV_INFO_SIZE 64

///< \~chinese CoaXPress�����Ϣ      \~english CoaXPress device information
typedef struct _MV_CXP_DEVICE_INFO_
{
    unsigned char       chVendorName[MV_FG_MAX_DEV_INFO_SIZE];      ///< \~chinese ��Ӧ������       \~english Vendor name
    unsigned char       chModelName[MV_FG_MAX_DEV_INFO_SIZE];       ///< \~chinese �ͺ�����         \~english Model name
    unsigned char       chManufacturerInfo[MV_FG_MAX_DEV_INFO_SIZE];///< \~chinese ������Ϣ         \~english Manufacturer information
    unsigned char       chDeviceVersion[MV_FG_MAX_DEV_INFO_SIZE];   ///< \~chinese ����汾         \~english Device version
    unsigned char       chSerialNumber[MV_FG_MAX_DEV_INFO_SIZE];    ///< \~chinese ���к�           \~english Serial number
    unsigned char       chUserDefinedName[MV_FG_MAX_DEV_INFO_SIZE]; ///< \~chinese �û��Զ�������   \~english User defined name
    unsigned char       chDeviceID[MV_FG_MAX_DEV_INFO_SIZE];        ///< \~chinese ���ID            \~english Device ID

    unsigned int        nReserved[48];                              ///< \~chinese �����ֶ�      \~english Reserved

}MV_CXP_DEVICE_INFO;

#define MV_FG_GEV_IFCONFIG_LLA_BIT        0x00000004                ///< \~chinese GigE Vision���LLAʹ�ܱ�־λ    \~english LLA enable flag bit of GigE Vision device
#define MV_FG_GEV_IFCONFIG_DHCP_BIT       0x00000002                ///< \~chinese GigE Vision���DHCPʹ�ܱ�־λ   \~english DHCP enable flag bit of GigE Vision device
#define MV_FG_GEV_IFCONFIG_PERSISTENT_BIT 0x00000001                ///< \~chinese GigE Vision�����̬IPʹ�ܱ�־λ        \~english Persistent IP enable flag bit of GigE Vision device
#define MV_FG_GEV_IFCONFIG_PR_BIT         0x80000000                ///< \~chinese GigE Vision����ܷ���PAUSE֡��־λ   \~english Can the GigE Vision device handle the pause frame flag bit
#define MV_FG_GEV_IFCONFIG_PG_BIT         0x40000000                ///< \~chinese GigE Vision����ܷ�����PAUSE֡��־λ   \~english Can the GigE Vision device generate pause frame flag bit

///< \~chinese GigE Vision�����Ϣ          \~english GigE Vision device information
typedef struct _MV_GEV_DEVICE_INFO_
{
    // ֧��IP���ã�1����֧�֡�bit0����̬IP, bit1��DHCP, bits2��LLA
    // Support IP configuration, and 1 represents support. Bit0: persistent IP, Bit1: DHCP, bits2: LLA
    // |31 30 29 28 27 26 25 24 23 22 21 20 19 18 17 16 | 15  14  13  12  11  10  9  8 7  6  5  4  3 |   2       1         0     |
    // |-----------------------------------------------------------------------------------------------------+-------+-----------|
    // |PR PG                                           |                                            |  LLA  +  DHCP + PERSISTENT|
    unsigned int        nIpCfgOption;                               ///< \~chinese ֧�ֵ�IP����                       \~english Supported IP configurations
    unsigned int        nIpCfgCurrent;                              ///< \~chinese ��ǰIP���ã��ο�֧�ֵ�IP����˵��   \~english For the current IP configuration, refer to the supported IP configuration description

    unsigned int        nCurrentIp;                                 ///< \~chinese ��ǰIP��ַ       \~english Current IP address
    unsigned int        nCurrentSubNetMask;                         ///< \~chinese ��ǰ��������     \~english Current subnet mask
    unsigned int        nDefultGateWay;                             ///< \~chinese ��ǰ����         \~english Current gateway
    unsigned int        nNetExport;                                 ///< \~chinese ����IP��ַ       \~english Network port IP address
    uint64_t            nMacAddress;                                ///< \~chinese MAC��ַ          \~english MAC address

    unsigned char       chVendorName[MV_FG_MAX_DEV_INFO_SIZE];      ///< \~chinese ��Ӧ������       \~english Vendor name
    unsigned char       chModelName[MV_FG_MAX_DEV_INFO_SIZE];       ///< \~chinese �ͺ�����         \~english Model name
    unsigned char       chManufacturerInfo[MV_FG_MAX_DEV_INFO_SIZE];///< \~chinese ������Ϣ         \~english Manufacturer information
    unsigned char       chDeviceVersion[MV_FG_MAX_DEV_INFO_SIZE];   ///< \~chinese ����汾         \~english Device version
    unsigned char       chSerialNumber[MV_FG_MAX_DEV_INFO_SIZE];    ///< \~chinese ���к�           \~english Serial number
    unsigned char       chUserDefinedName[MV_FG_MAX_DEV_INFO_SIZE]; ///< \~chinese �û��Զ�������   \~english User defined name
    unsigned char       chDeviceID[MV_FG_MAX_DEV_INFO_SIZE];        ///< \~chinese ���ID           \~english Device ID

    unsigned int        nCurrentPort;                               ///< \~chinese ��ǰ�˿�         \~english Current Port

    unsigned int        nReserved[47];                              ///< \~chinese �����ֶ�         \~english Reserved

}MV_GEV_DEVICE_INFO;

///< \~chinese Camera Link�����Ϣ          \~english Camera Link device information
typedef struct _MV_CML_DEVICE_INFO_
{
    unsigned char       chVendorName[MV_FG_MAX_DEV_INFO_SIZE];      ///< \~chinese ��Ӧ������       \~english Vendor name
    unsigned char       chModelName[MV_FG_MAX_DEV_INFO_SIZE];       ///< \~chinese �ͺ�����         \~english Model name
    unsigned char       chManufacturerInfo[MV_FG_MAX_DEV_INFO_SIZE];///< \~chinese ������Ϣ         \~english Manufacturer information
    unsigned char       chDeviceVersion[MV_FG_MAX_DEV_INFO_SIZE];   ///< \~chinese ����汾         \~english Device version
    unsigned char       chSerialNumber[MV_FG_MAX_DEV_INFO_SIZE];    ///< \~chinese ���к�           \~english Serial number
    unsigned char       chUserDefinedName[MV_FG_MAX_DEV_INFO_SIZE]; ///< \~chinese �û��Զ�������   \~english User defined name
    unsigned char       chDeviceID[MV_FG_MAX_DEV_INFO_SIZE];        ///< \~chinese ���ID            \~english Device ID

    unsigned int        nReserved[48];                              ///< \~chinese �����ֶ�      \~english Reserved

}MV_CML_DEVICE_INFO;

///< \~chinese XoFLink�����Ϣ      \~english XoFLink device information
typedef struct _MV_XoF_DEVICE_INFO_
{
    unsigned char       chVendorName[MV_FG_MAX_DEV_INFO_SIZE];      ///< \~chinese ��Ӧ������       \~english Vendor name
    unsigned char       chModelName[MV_FG_MAX_DEV_INFO_SIZE];       ///< \~chinese �ͺ�����         \~english Model name
    unsigned char       chManufacturerInfo[MV_FG_MAX_DEV_INFO_SIZE];///< \~chinese ������Ϣ         \~english Manufacturer information
    unsigned char       chDeviceVersion[MV_FG_MAX_DEV_INFO_SIZE];   ///< \~chinese ����汾         \~english Device version
    unsigned char       chSerialNumber[MV_FG_MAX_DEV_INFO_SIZE];    ///< \~chinese ���к�           \~english Serial number
    unsigned char       chUserDefinedName[MV_FG_MAX_DEV_INFO_SIZE]; ///< \~chinese �û��Զ�������   \~english User defined name
    unsigned char       chDeviceID[MV_FG_MAX_DEV_INFO_SIZE];        ///< \~chinese ���ID            \~english Device ID

    unsigned int        nReserved[48];                              ///< \~chinese �����ֶ�      \~english Reserved

}MV_XoF_DEVICE_INFO;

///< \~chinese �������         \~english Device type
#define MV_FG_GEV_DEVICE                     0x00000001             ///< \~chinese GigE Vision���        \~english GigE Vision device
#define MV_FG_U3V_DEVICE                     0x00000002             ///< \~chinese U3V���         \~english U3V device
#define MV_FG_CAMERALINK_DEVICE              0x00000003             ///< \~chinese Camera Link���   \~english Camera Link device
#define MV_FG_CXP_DEVICE                     0x00000004             ///< \~chinese CoaXPress���         \~english CoaXPress device
#define MV_FG_XoF_DEVICE                     0x00000005             ///< \~chinese XoFLink���         \~english XoFLink device

///< \~chinese �����Ϣ         \~english Device information
typedef struct _MV_FG_DEVICE_INFO_
{
    unsigned int                nDevType;                           ///< \~chinese �������     \~english Device type
    unsigned int                nReserved[3];                       ///< \~chinese �����ֶ�     \~english Reserved

    union
    {
        MV_CXP_DEVICE_INFO      stCXPDevInfo;                       ///< \~chinese CoaXPress�����Ϣ          \~english CoaXPress device information
        MV_GEV_DEVICE_INFO      stGEVDevInfo;                       ///< \~chinese GigE Vision�����Ϣ          \~english GigE Vision device information
        MV_CML_DEVICE_INFO      stCMLDevInfo;                       ///< \~chinese Camera Link�����Ϣ    \~english Camera Link device information
        MV_XoF_DEVICE_INFO      stXoFDevInfo;                       ///< \~chinese XoFLink�����Ϣ           \~english XoFLink device information

        unsigned int            nReserved[256];                     ///< \~chinese �����ֶ�     \~english Reserved
        // more ...
    }DevInfo;

}MV_FG_DEVICE_INFO;

///< \~chinese �����������           \~english Buffer queue type
typedef enum _MV_FG_BUFFER_QUEUE_TYPE_
{
    MV_FG_BUFFER_QUEUE_INPUT_TO_OUTPUT          = 0,                ///< \~chinese ��������е�BUFFER�ŵ��������   \~english Put BUFFER of input queue into output queue
    MV_FG_BUFFER_QUEUE_OUTPUT_DISCARD           = 1,                ///< \~chinese ����������е�BUFFER              \~english Discard BUFFER of output queue
    MV_FG_BUFFER_QUEUE_ALL_TO_INPUT             = 2,                ///< \~chinese �����е�BUFFER(�����������)�ŵ��������  \~english Put all BUFFER (including output queue) into input queue
    MV_FG_BUFFER_QUEUE_UNQUEUED_TO_INPUT        = 3,                ///< \~chinese ��δʹ�õ�BUFFER�ŵ��������     \~english Put unused BUFFER into input queue
    MV_FG_BUFFER_QUEUE_ALL_DISCARD              = 4                 ///< \~chinese �����������������е�BUFFER     \~english Discard BUFFER in input and output queues

}MV_FG_BUFFER_QUEUE_TYPE;

///< \~chinese ���ظ�ʽ����           \~english Pixel format definition
#define MV_FG_PIXEL_MONO                        0x01000000          ///< \~chinese Mono��ʽ        \~english Mono format
#define MV_FG_PIXEL_COLOR                       0x02000000          ///< \~chinese ��ɫ��ʽ        \~english Color format
#define MV_FG_PIXEL_CUSTOM                      0x80000000          ///< \~chinese �Զ���          \~english custom
#define MV_FG_PIXEL_BIT_COUNT(n)                ((n) << 16)         ///< \~chinese λ��������λ��  \~english Location of the number of bits
typedef enum _MV_FG_PIXEL_TYPE_
{
    ///< \~chinese δ����ĸ�ʽ       \~english Undefined format
    MV_FG_PIXEL_TYPE_Undefined                  = 0xFFFFFFFF,

    ///< \~chinese Mono��ʽ           \~english Mono format
    MV_FG_PIXEL_TYPE_Mono8                      = (MV_FG_PIXEL_MONO | MV_FG_PIXEL_BIT_COUNT(8) | 0x0001),   ///< \~chinese Mono8            \~english Mono8
    MV_FG_PIXEL_TYPE_Mono10                     = (MV_FG_PIXEL_MONO | MV_FG_PIXEL_BIT_COUNT(16) | 0x0003),  ///< \~chinese Mono10           \~english Mono10
    MV_FG_PIXEL_TYPE_Mono10_Packed              = (MV_FG_PIXEL_MONO | MV_FG_PIXEL_BIT_COUNT(12) | 0x0004),  ///< \~chinese Mono10_Packed    \~english Mono10_Packed
    MV_FG_PIXEL_TYPE_Mono12                     = (MV_FG_PIXEL_MONO | MV_FG_PIXEL_BIT_COUNT(16) | 0x0005),  ///< \~chinese Mono12           \~english Mono12
    MV_FG_PIXEL_TYPE_Mono12_Packed              = (MV_FG_PIXEL_MONO | MV_FG_PIXEL_BIT_COUNT(12) | 0x0006),  ///< \~chinese Mono12_Packed    \~english Mono12_Packed
    MV_FG_PIXEL_TYPE_Mono16                     = (MV_FG_PIXEL_MONO | MV_FG_PIXEL_BIT_COUNT(16) | 0x0007),  ///< \~chinese Mono16           \~english Mono16

    ///< \~chinese Bayer��ʽ          \~english Bayer format
    MV_FG_PIXEL_TYPE_BayerGR8                   = (MV_FG_PIXEL_MONO | MV_FG_PIXEL_BIT_COUNT(8) | 0x0008),   ///< \~chinese BayerGR8         \~english BayerGR8
    MV_FG_PIXEL_TYPE_BayerRG8                   = (MV_FG_PIXEL_MONO | MV_FG_PIXEL_BIT_COUNT(8) | 0x0009),   ///< \~chinese BayerRG8         \~english BayerRG8
    MV_FG_PIXEL_TYPE_BayerGB8                   = (MV_FG_PIXEL_MONO | MV_FG_PIXEL_BIT_COUNT(8) | 0x000A),   ///< \~chinese BayerGB8         \~english BayerGB8
    MV_FG_PIXEL_TYPE_BayerBG8                   = (MV_FG_PIXEL_MONO | MV_FG_PIXEL_BIT_COUNT(8) | 0x000B),   ///< \~chinese BayerBG8         \~english BayerBG8
    MV_FG_PIXEL_TYPE_BayerRBGG8                 = (MV_FG_PIXEL_MONO | MV_FG_PIXEL_BIT_COUNT(8) | 0x0046),   ///< \~chinese BayerRBGG8       \~english BayerRBGG8
    MV_FG_PIXEL_TYPE_BayerGR10                  = (MV_FG_PIXEL_MONO | MV_FG_PIXEL_BIT_COUNT(16) | 0x000C),  ///< \~chinese BayerGR10        \~english BayerGR10
    MV_FG_PIXEL_TYPE_BayerRG10                  = (MV_FG_PIXEL_MONO | MV_FG_PIXEL_BIT_COUNT(16) | 0x000D),  ///< \~chinese BayerRG10        \~english BayerRG10
    MV_FG_PIXEL_TYPE_BayerGB10                  = (MV_FG_PIXEL_MONO | MV_FG_PIXEL_BIT_COUNT(16) | 0x000E),  ///< \~chinese BayerGB10        \~english BayerGB10
    MV_FG_PIXEL_TYPE_BayerBG10                  = (MV_FG_PIXEL_MONO | MV_FG_PIXEL_BIT_COUNT(16) | 0x000F),  ///< \~chinese BayerBG10        \~english BayerBG10
    MV_FG_PIXEL_TYPE_BayerGR12                  = (MV_FG_PIXEL_MONO | MV_FG_PIXEL_BIT_COUNT(16) | 0x0010),  ///< \~chinese BayerGR12        \~english BayerGR12
    MV_FG_PIXEL_TYPE_BayerRG12                  = (MV_FG_PIXEL_MONO | MV_FG_PIXEL_BIT_COUNT(16) | 0x0011),  ///< \~chinese BayerRG12        \~english BayerRG12
    MV_FG_PIXEL_TYPE_BayerGB12                  = (MV_FG_PIXEL_MONO | MV_FG_PIXEL_BIT_COUNT(16) | 0x0012),  ///< \~chinese BayerGB12        \~english BayerGB12
    MV_FG_PIXEL_TYPE_BayerBG12                  = (MV_FG_PIXEL_MONO | MV_FG_PIXEL_BIT_COUNT(16) | 0x0013),  ///< \~chinese BayerBG12        \~english BayerBG12
    MV_FG_PIXEL_TYPE_BayerGR10_Packed           = (MV_FG_PIXEL_MONO | MV_FG_PIXEL_BIT_COUNT(12) | 0x0026),  ///< \~chinese BayerGR10_Packed \~english BayerGR10_Packed
    MV_FG_PIXEL_TYPE_BayerRG10_Packed           = (MV_FG_PIXEL_MONO | MV_FG_PIXEL_BIT_COUNT(12) | 0x0027),  ///< \~chinese BayerRG10_Packed \~english BayerRG10_Packed
    MV_FG_PIXEL_TYPE_BayerGB10_Packed           = (MV_FG_PIXEL_MONO | MV_FG_PIXEL_BIT_COUNT(12) | 0x0028),  ///< \~chinese BayerGB10_Packed \~english BayerGB10_Packed
    MV_FG_PIXEL_TYPE_BayerBG10_Packed           = (MV_FG_PIXEL_MONO | MV_FG_PIXEL_BIT_COUNT(12) | 0x0029),  ///< \~chinese BayerBG10_Packed \~english BayerBG10_Packed
    MV_FG_PIXEL_TYPE_BayerGR12_Packed           = (MV_FG_PIXEL_MONO | MV_FG_PIXEL_BIT_COUNT(12) | 0x002A),  ///< \~chinese BayerGR12_Packed \~english BayerGR12_Packed
    MV_FG_PIXEL_TYPE_BayerRG12_Packed           = (MV_FG_PIXEL_MONO | MV_FG_PIXEL_BIT_COUNT(12) | 0x002B),  ///< \~chinese BayerRG12_Packed \~english BayerRG12_Packed
    MV_FG_PIXEL_TYPE_BayerGB12_Packed           = (MV_FG_PIXEL_MONO | MV_FG_PIXEL_BIT_COUNT(12) | 0x002C),  ///< \~chinese BayerGB12_Packed \~english BayerGB12_Packed
    MV_FG_PIXEL_TYPE_BayerBG12_Packed           = (MV_FG_PIXEL_MONO | MV_FG_PIXEL_BIT_COUNT(12) | 0x002D),  ///< \~chinese BayerBG12_Packed \~english BayerBG12_Packed
    MV_FG_PIXEL_TYPE_BayerGR16                  = (MV_FG_PIXEL_MONO | MV_FG_PIXEL_BIT_COUNT(16) | 0x002E),  ///< \~chinese BayerGR16        \~english BayerGR16
    MV_FG_PIXEL_TYPE_BayerRG16                  = (MV_FG_PIXEL_MONO | MV_FG_PIXEL_BIT_COUNT(16) | 0x002F),  ///< \~chinese BayerRG16        \~english BayerRG16
    MV_FG_PIXEL_TYPE_BayerGB16                  = (MV_FG_PIXEL_MONO | MV_FG_PIXEL_BIT_COUNT(16) | 0x0030),  ///< \~chinese BayerGB16        \~english BayerGB16
    MV_FG_PIXEL_TYPE_BayerBG16                  = (MV_FG_PIXEL_MONO | MV_FG_PIXEL_BIT_COUNT(16) | 0x0031),  ///< \~chinese BayerBG16        \~english BayerBG16

    ///< \~chinese RGB��ʽ            \~english RGB format
    MV_FG_PIXEL_TYPE_RGB8_Packed                = (MV_FG_PIXEL_COLOR | MV_FG_PIXEL_BIT_COUNT(24) | 0x0014),  ///< \~chinese RGB8_Packed     \~english RGB8_Packed
    MV_FG_PIXEL_TYPE_BGR8_Packed                = (MV_FG_PIXEL_COLOR | MV_FG_PIXEL_BIT_COUNT(24) | 0x0015),  ///< \~chinese BGR8_Packed     \~english BGR8_Packed
    MV_FG_PIXEL_TYPE_RGBA8_Packed               = (MV_FG_PIXEL_COLOR | MV_FG_PIXEL_BIT_COUNT(32) | 0x0016),  ///< \~chinese RGBA8_Packed    \~english RGBA8_Packed
    MV_FG_PIXEL_TYPE_BGRA8_Packed               = (MV_FG_PIXEL_COLOR | MV_FG_PIXEL_BIT_COUNT(32) | 0x0017),  ///< \~chinese BGRA8_Packed    \~english BGRA8_Packed
    MV_FG_PIXEL_TYPE_RGB16_Packed               = (MV_FG_PIXEL_COLOR | MV_FG_PIXEL_BIT_COUNT(48) | 0x0033),  ///< \~chinese RGB16_Packed    \~english RGB16_Packed

    ///< \~chinese YUV��ʽ            \~english YUV format
    MV_FG_PIXEL_TYPE_YUV422_Packed              = (MV_FG_PIXEL_COLOR | MV_FG_PIXEL_BIT_COUNT(16) | 0x001F),  ///< \~chinese YUV422_Packed       \~english YUV422_Packed
    MV_FG_PIXEL_TYPE_YUV422_YUYV_Packed         = (MV_FG_PIXEL_COLOR | MV_FG_PIXEL_BIT_COUNT(16) | 0x0032),  ///< \~chinese YUV422_YUYV_Packed  \~english YUV422_YUYV_Packed

    ///< \~chinese Jpeg��ʽ           \~english Jpeg format
    MV_FG_PIXEL_TYPE_JPEG                       = (MV_FG_PIXEL_CUSTOM | MV_FG_PIXEL_BIT_COUNT(24) | 0x0001), ///< \~chinese JPEG            \~english JPEG

    ///< \~chinese ����ѹ�����ظ�ʽ����
    MV_FG_PIXEL_TYPE_HB_Mono8                   = (MV_FG_PIXEL_CUSTOM | MV_FG_PIXEL_MONO | MV_FG_PIXEL_BIT_COUNT(8) | 0x0001),
    MV_FG_PIXEL_TYPE_HB_Mono10                  = (MV_FG_PIXEL_CUSTOM | MV_FG_PIXEL_MONO | MV_FG_PIXEL_BIT_COUNT(16) | 0x0003),
    MV_FG_PIXEL_TYPE_HB_Mono10_Packed           = (MV_FG_PIXEL_CUSTOM | MV_FG_PIXEL_MONO | MV_FG_PIXEL_BIT_COUNT(12) | 0x0004),
    MV_FG_PIXEL_TYPE_HB_Mono12                  = (MV_FG_PIXEL_CUSTOM | MV_FG_PIXEL_MONO | MV_FG_PIXEL_BIT_COUNT(16) | 0x0005),
    MV_FG_PIXEL_TYPE_HB_Mono12_Packed           = (MV_FG_PIXEL_CUSTOM | MV_FG_PIXEL_MONO | MV_FG_PIXEL_BIT_COUNT(12) | 0x0006),
    MV_FG_PIXEL_TYPE_HB_Mono16                  = (MV_FG_PIXEL_CUSTOM | MV_FG_PIXEL_MONO | MV_FG_PIXEL_BIT_COUNT(16) | 0x0007),
    MV_FG_PIXEL_TYPE_HB_BayerGR8                = (MV_FG_PIXEL_CUSTOM | MV_FG_PIXEL_MONO | MV_FG_PIXEL_BIT_COUNT(8) | 0x0008),
    MV_FG_PIXEL_TYPE_HB_BayerRG8                = (MV_FG_PIXEL_CUSTOM | MV_FG_PIXEL_MONO | MV_FG_PIXEL_BIT_COUNT(8) | 0x0009),
    MV_FG_PIXEL_TYPE_HB_BayerGB8                = (MV_FG_PIXEL_CUSTOM | MV_FG_PIXEL_MONO | MV_FG_PIXEL_BIT_COUNT(8) | 0x000A),
    MV_FG_PIXEL_TYPE_HB_BayerBG8                = (MV_FG_PIXEL_CUSTOM | MV_FG_PIXEL_MONO | MV_FG_PIXEL_BIT_COUNT(8) | 0x000B),
    MV_FG_PIXEL_TYPE_HB_BayerRBGG8              = (MV_FG_PIXEL_CUSTOM | MV_FG_PIXEL_MONO | MV_FG_PIXEL_BIT_COUNT(8) | 0x0046),
    MV_FG_PIXEL_TYPE_HB_BayerGR10               = (MV_FG_PIXEL_CUSTOM | MV_FG_PIXEL_MONO | MV_FG_PIXEL_BIT_COUNT(16) | 0x000C),
    MV_FG_PIXEL_TYPE_HB_BayerRG10               = (MV_FG_PIXEL_CUSTOM | MV_FG_PIXEL_MONO | MV_FG_PIXEL_BIT_COUNT(16) | 0x000D),
    MV_FG_PIXEL_TYPE_HB_BayerGB10               = (MV_FG_PIXEL_CUSTOM | MV_FG_PIXEL_MONO | MV_FG_PIXEL_BIT_COUNT(16) | 0x000E),
    MV_FG_PIXEL_TYPE_HB_BayerBG10               = (MV_FG_PIXEL_CUSTOM | MV_FG_PIXEL_MONO | MV_FG_PIXEL_BIT_COUNT(16) | 0x000F),
    MV_FG_PIXEL_TYPE_HB_BayerGR12               = (MV_FG_PIXEL_CUSTOM | MV_FG_PIXEL_MONO | MV_FG_PIXEL_BIT_COUNT(16) | 0x0010),
    MV_FG_PIXEL_TYPE_HB_BayerRG12               = (MV_FG_PIXEL_CUSTOM | MV_FG_PIXEL_MONO | MV_FG_PIXEL_BIT_COUNT(16) | 0x0011),
    MV_FG_PIXEL_TYPE_HB_BayerGB12               = (MV_FG_PIXEL_CUSTOM | MV_FG_PIXEL_MONO | MV_FG_PIXEL_BIT_COUNT(16) | 0x0012),
    MV_FG_PIXEL_TYPE_HB_BayerBG12               = (MV_FG_PIXEL_CUSTOM | MV_FG_PIXEL_MONO | MV_FG_PIXEL_BIT_COUNT(16) | 0x0013),
    MV_FG_PIXEL_TYPE_HB_BayerGR10_Packed        = (MV_FG_PIXEL_CUSTOM | MV_FG_PIXEL_MONO | MV_FG_PIXEL_BIT_COUNT(12) | 0x0026),
    MV_FG_PIXEL_TYPE_HB_BayerRG10_Packed        = (MV_FG_PIXEL_CUSTOM | MV_FG_PIXEL_MONO | MV_FG_PIXEL_BIT_COUNT(12) | 0x0027),
    MV_FG_PIXEL_TYPE_HB_BayerGB10_Packed        = (MV_FG_PIXEL_CUSTOM | MV_FG_PIXEL_MONO | MV_FG_PIXEL_BIT_COUNT(12) | 0x0028),
    MV_FG_PIXEL_TYPE_HB_BayerBG10_Packed        = (MV_FG_PIXEL_CUSTOM | MV_FG_PIXEL_MONO | MV_FG_PIXEL_BIT_COUNT(12) | 0x0029),
    MV_FG_PIXEL_TYPE_HB_BayerGR12_Packed        = (MV_FG_PIXEL_CUSTOM | MV_FG_PIXEL_MONO | MV_FG_PIXEL_BIT_COUNT(12) | 0x002A),
    MV_FG_PIXEL_TYPE_HB_BayerRG12_Packed        = (MV_FG_PIXEL_CUSTOM | MV_FG_PIXEL_MONO | MV_FG_PIXEL_BIT_COUNT(12) | 0x002B),
    MV_FG_PIXEL_TYPE_HB_BayerGB12_Packed        = (MV_FG_PIXEL_CUSTOM | MV_FG_PIXEL_MONO | MV_FG_PIXEL_BIT_COUNT(12) | 0x002C),
    MV_FG_PIXEL_TYPE_HB_BayerBG12_Packed        = (MV_FG_PIXEL_CUSTOM | MV_FG_PIXEL_MONO | MV_FG_PIXEL_BIT_COUNT(12) | 0x002D),
    MV_FG_PIXEL_TYPE_HB_YUV422_Packed           = (MV_FG_PIXEL_CUSTOM | MV_FG_PIXEL_COLOR | MV_FG_PIXEL_BIT_COUNT(16) | 0x001F),
    MV_FG_PIXEL_TYPE_HB_YUV422_YUYV_Packed      = (MV_FG_PIXEL_CUSTOM | MV_FG_PIXEL_COLOR | MV_FG_PIXEL_BIT_COUNT(16) | 0x0032),
    MV_FG_PIXEL_TYPE_HB_RGB8_Packed             = (MV_FG_PIXEL_CUSTOM | MV_FG_PIXEL_COLOR | MV_FG_PIXEL_BIT_COUNT(24) | 0x0014),
    MV_FG_PIXEL_TYPE_HB_BGR8_Packed             = (MV_FG_PIXEL_CUSTOM | MV_FG_PIXEL_COLOR | MV_FG_PIXEL_BIT_COUNT(24) | 0x0015),
    MV_FG_PIXEL_TYPE_HB_RGBA8_Packed            = (MV_FG_PIXEL_CUSTOM | MV_FG_PIXEL_COLOR | MV_FG_PIXEL_BIT_COUNT(32) | 0x0016),
    MV_FG_PIXEL_TYPE_HB_BGRA8_Packed            = (MV_FG_PIXEL_CUSTOM | MV_FG_PIXEL_COLOR | MV_FG_PIXEL_BIT_COUNT(32) | 0x0017),
    MV_FG_PIXEL_TYPE_HB_RGB16_Packed            = (MV_FG_PIXEL_CUSTOM | MV_FG_PIXEL_COLOR | MV_FG_PIXEL_BIT_COUNT(48) | 0x0033),

}MV_FG_PIXEL_TYPE;

///< \~chinese �����֡������Ϣ          \~english Output Frame buffer information
typedef struct _MV_FG_BUFFER_INFO_
{
    void*               pBuffer;                                    ///< [OUT] \~chinese ͼ�񻺴��ַ       \~english Image buffer address
    unsigned int        nSize;                                      ///< [OUT] \~chinese ��ַ��С           \~english Address size
    unsigned int        nFilledSize;                                ///< [OUT] \~chinese ͼ�񳤶�           \~english Image length
    void*               pPrivate;                                   ///< [OUT] \~chinese ˽������           \~english Private data

    unsigned int        nWidth;                                     ///< [OUT] \~chinese ���               \~english Width
    unsigned int        nHeight;                                    ///< [OUT] \~chinese �߶�               \~english Height
    MV_FG_PIXEL_TYPE    enPixelType;                                ///< [OUT] \~chinese ���ظ�ʽ           \~english Pixel type

    bool                bNewData;                                   ///< [OUT] \~chinese �Ƿ�����ͼ����   \~english Is it a new image coming
    bool                bQueued;                                    ///< [OUT] \~chinese �Ƿ���ȡͼ������   \~english Is it in the drawing queue
    bool                bAcquiring;                                 ///< [OUT] \~chinese �Ƿ���ȡͼ         \~english Is it taking pictures
    bool                bIncomplete;                                ///< [OUT] \~chinese �Ƿ�δ���         \~english Is it incomplete

    int64_t             nFrameID;                                   ///< [OUT] \~chinese ֡��               \~english Frame ID
    int64_t             nDevTimeStamp;                              ///< [OUT] \~chinese ���ʱ���         \~english Device timestamp
    int64_t             nHostTimeStamp;                             ///< [OUT] \~chinese ����ʱ���         \~english Host timestamp

    unsigned int        nNumChunks;                                 ///< [OUT] \~chinese Chunk����          \~english Number of Chunks
    unsigned int        nChunkPayloadSize;                          ///< [OUT] \~chinese Chunk���س���      \~english Payload size of Chunk

    unsigned int        nSecondCount;                               ///< [OUT] \~chinese ����(ʱ��)         \~english Seconds (time scale)
    unsigned int        nCycleCount;                                ///< [OUT] \~chinese ������(ʱ��)       \~english Number of cycles (time scale)
    unsigned int        nCycleOffset;                               ///< [OUT] \~chinese ����ƫ����(ʱ��)   \~english Cycle offset (time scale)

    float               fGain;                                      ///< [OUT] \~chinese ����               \~english Gain
    float               fExposureTime;                              ///< [OUT] \~chinese �ع�ʱ��           \~english Exposure time
    unsigned int        nAverageBrightness;                         ///< [OUT] \~chinese ƽ������           \~english Average brightness
    unsigned int        nFrameCounter;                              ///< [OUT] \~chinese ��֡��             \~english Total frames
    unsigned int        nTriggerIndex;                              ///< [OUT] \~chinese ��������           \~english Trigger index

    unsigned int        nInput;                                     ///< [OUT] \~chinese ����               \~english Input
    unsigned int        nOutput;                                    ///< [OUT] \~chinese ���               \~english Output

    unsigned int        nRed;                                       ///< [OUT] \~chinese ��ɫ(��ƽ��)       \~english Red (white balance)
    unsigned int        nGreen;                                     ///< [OUT] \~chinese ��ɫ(��ƽ��)       \~english Green (white balance)
    unsigned int        nBlue;                                      ///< [OUT] \~chinese ��ɫ(��ƽ��)       \~english Blue (white balance)

    unsigned int        nOffsetX;                                   ///< [OUT] \~chinese ˮƽƫ����(ROIλ��)   \~english Horizontal offset (ROI position)
    unsigned int        nOffsetY;                                   ///< [OUT] \~chinese ��ֱƫ����(ROIλ��)   \~english Vertical offset (ROI position)
    unsigned int        nChunkWidth;                                ///< [OUT] \~chinese ���(ROIλ��)         \~english Width (ROI position)
    unsigned int        nChunkHeight;                               ///< [OUT] \~chinese �߶�(ROIλ��)         \~english Height (ROI position)

    unsigned int        nLastFrameFlag;                             ///< [OUT] \~chinese ��ƽ�������һ֡   \~english last level frame flag
    unsigned int        nReserved[44];                              ///<       \~chinese �����ֶ�           \~english Reserved

}MV_FG_BUFFER_INFO;

///< \~chinese Chunk��Ϣ          \~english Chunk information
typedef struct _MV_FG_CHUNK_DATA_INFO_
{
    unsigned char*      pChunkData;                                 ///< [OUT] \~chinese Chunk����    \~english Chunk data
    unsigned int        nChunkID;                                   ///< [OUT] \~chinese Chunk ID     \~english Chunk ID
    unsigned int        nChunkLen;                                  ///< [OUT] \~chinese Chunk�ĳ���  \~english Length of Chunk

    unsigned int        nReserved[4];                               ///<       \~chinese �����ֶ�     \~english Reserved

}MV_FG_CHUNK_DATA_INFO;

/// \~chinese �����ͼ����Ϣ           \~english Input image information
typedef struct _MV_FG_INPUT_IMAGE_INFO_
{
    unsigned int        nWidth;                                     ///< [IN]   \~chinese ͼ���       \~english Width
    unsigned int        nHeight;                                    ///< [IN]   \~chinese ͼ���       \~english Height
    MV_FG_PIXEL_TYPE    enPixelType;                                ///< [IN]   \~chinese ���ظ�ʽ     \~english Pixel type

    unsigned char*      pImageBuf;                                  ///< [IN]   \~chinese ����ͼ�񻺴�    \~english Input image buffer
    unsigned int        nImageBufLen;                               ///< [IN]   \~chinese ����ͼ�񳤶�    \~english Input image length

    unsigned int        nReserved[4];                               ///<        \~chinese Ԥ���ֶ�      \~english Reserved

}MV_FG_INPUT_IMAGE_INFO, MV_FG_DISPLAY_FRAME_INFO;

/// \~chinese �����ͼ����Ϣ           \~english Output image information
typedef struct _MV_FG_OUTPUT_IMAGE_INFO_
{
    unsigned int        nWidth;                                     ///< [OUT]  \~chinese ͼ���       \~english Width
    unsigned int        nHeight;                                    ///< [OUT]  \~chinese ͼ���       \~english Height
    MV_FG_PIXEL_TYPE    enPixelType;                                ///< [OUT]   \~chinese ���ظ�ʽ     \~english Pixel type

    unsigned char*      pImageBuf;                                  ///< [IN][OUT]  \~chinese ���ݻ���  \~english Data buffer
    unsigned int        nImageBufSize;                              ///< [IN]   \~chinese ���ݻ����С  \~english Data buffer size
    unsigned int        nImageBufLen;                               ///< [OUT]  \~chinese ͼ�񳤶�      \~english Image length

    unsigned int        nReserved[4];                               ///<        \~chinese Ԥ���ֶ�      \~english Reserved
}MV_FG_OUTPUT_IMAGE_INFO;

/// \~chinese ��ֵ����          \~english CFA method
typedef enum _MV_FG_CFA_METHOD_
{
    MV_FG_CFA_METHOD_QUICK              = 0,                        ///< \~chinese ����       \~english Quick
    MV_FG_CFA_METHOD_BALANCE            = 1,                        ///< \~chinese ����       \~english Balance
    MV_FG_CFA_METHOD_OPTIMAL            = 2,                        ///< \~chinese ����       \~english Optimal

}MV_FG_CFA_METHOD;

/// \~chinese ����BMPͼ����Ϣ         \~english Save BMP image information
typedef struct _MV_FG_SAVE_BITMAP_INFO_
{
    MV_FG_INPUT_IMAGE_INFO  stInputImageInfo;                       ///< [IN]  \~chinese ����ͼƬ��Ϣ     \~english Input image information

    unsigned char*      pBmpBuf;                                    ///< [IN][OUT]  \~chinese �����BMPͼƬ����    \~english Output BMP image buffer
    unsigned int        nBmpBufSize;                                ///< [IN]  \~chinese ����Ļ�������С          \~english Output buffer size
    unsigned int        nBmpBufLen;                                 ///< [OUT] \~chinese �����BMPͼƬ����         \~english Output BMP picture length
    
    MV_FG_CFA_METHOD    enCfaMethod;                                ///< [IN]  \~chinese ��ֵ����       \~english CFA method

    unsigned int        nReserved[4];                               ///<       \~chinese Ԥ���ֶ�       \~english Reserved

}MV_FG_SAVE_BITMAP_INFO;

/// \~chinese ����JPEGͼ����Ϣ            \~english Save JPEG image information
typedef struct _MV_FG_SAVE_JPEG_INFO_
{
    MV_FG_INPUT_IMAGE_INFO  stInputImageInfo;                       ///< [IN]  \~chinese ����ͼƬ��Ϣ     \~english Input image information

    unsigned char*      pJpgBuf;                                    ///< [IN][OUT]  \~chinese �����JPEGͼƬ����   \~english Output JPEG image buffer
    unsigned int        nJpgBufSize;                                ///< [IN]  \~chinese ����Ļ�������С          \~english Output buffer size
    unsigned int        nJpgBufLen;                                 ///< [OUT] \~chinese �����JPEGͼƬ����        \~english Output JPEG picture length

    unsigned int        nJpgQuality;                                ///< [IN]  \~chinese ��������, (0-100]      \~english Encoding quality, (0-100]
    MV_FG_CFA_METHOD    enCfaMethod;                                ///< [IN]  \~chinese ��ֵ����               \~english CFA method

    unsigned int        nReserved[4];                               ///<       \~chinese Ԥ���ֶ�       \~english Reserved

}MV_FG_SAVE_JPEG_INFO;

typedef enum _MV_FG_RESOLUTION_UNIT_
{
    MV_FG_Resolution_Unit_None = 1,           // �޵�λ
    MV_FG_Resolution_Unit_Inch = 2,           // Ӣ��
    MV_FG_Resolution_Unit_CENTIMETER = 3,     // ����

}MV_FG_RESOLUTION_UNIT;

/// \~chinese ����Tiffͼ����Ϣ            \~english Save Tiff image information
typedef struct _MV_FG_SAVE_TIFF_TO_FILE_INFO_
{
    MV_FG_INPUT_IMAGE_INFO  stInputImageInfo;                       ///< [IN]  \~chinese ����ͼƬ��Ϣ     \~english Input image information

    char*               pcImagePath;                                ///< [IN]  \~chinese �����ļ�·��     \~english Input image path
    float               fXResolution;                               ///< [IN]  \~chinese ˮƽ�ֱ���       \~english Horizontal resolution
    float               fYResolution;                               ///< [IN]  \~chinese ��ֱ�ֱ���       \~english Vertical resolution
    MV_FG_RESOLUTION_UNIT  enResolutionUnit;                        ///< [IN]  \~chinese �ֱ��ʵ�λ       \~english Resolution unit
    MV_FG_CFA_METHOD    enCfaMethod;                                ///< [IN]  \~chinese ��ֵ����         \~english CFA method

    unsigned int        nReserved[4];                               ///<       \~chinese Ԥ���ֶ�         \~english Reserved

}MV_FG_SAVE_TIFF_TO_FILE_INFO;

/// \~chinese ����Pngͼ����Ϣ            \~english Save Png image information
typedef struct _MV_FG_SAVE_PNG_TO_FILE_INFO_
{
    MV_FG_INPUT_IMAGE_INFO  stInputImageInfo;                       ///< [IN]  \~chinese ����ͼƬ��Ϣ           \~english Input image information

    char*               pcImagePath;                                ///< [IN]  \~chinese �����ļ�·��           \~english Input image path
    unsigned int        nPngCompression;                            ///< [IN]  \~chinese ����ѹ����, [0-9]�� Ŀǰ����������ѹ������֧��ѹ����      \~english Encoding compression, [0-9]. Currently, lossless compression is used and compression rate is not supported.
    MV_FG_CFA_METHOD    enCfaMethod;                                ///< [IN]  \~chinese ��ֵ����               \~english CFA method

    unsigned int        nReserved[4];                               ///<       \~chinese Ԥ���ֶ�               \~english Reserved

}MV_FG_SAVE_PNG_TO_FILE_INFO;

/// \~chinese Gamma����           \~english Gamma type
typedef enum _MV_FG_GAMMA_TYPE_
{
    MV_FG_GAMMA_TYPE_NONE               = 0,                        ///< \~chinese ������                       \~english Disable
    MV_FG_GAMMA_TYPE_VALUE              = 1,                        ///< \~chinese Gammaֵ                      \~english Gamma value
    MV_FG_GAMMA_TYPE_USER_CURVE         = 2,                        ///< \~chinese Gamma����                    \~english Gamma curve
                                                                    ///< \~chinese ���ͼ������Ϊ8λʱ          \~english Output image data is 8 bit
                                                                    ///< \~chinese      ���߳��ȣ�256*sizeof(unsigned char)      \~english 8bit,length:256*sizeof(unsigned char)
                                                                    ///< \~chinese ���ͼ������Ϊ16λʱ���������ݸ�������ͼ��������ͬ      \~english Output image data is 16 bit
                                                                    ///< \~chinese      Դͼ���ʽ10λ, ���߳��ȣ�1024*sizeof(unsigned short)   \~english Input image 10bit, curve length:1024*sizeof(unsigned short)
                                                                    ///< \~chinese      Դͼ���ʽ12λ, ���߳��ȣ�4096*sizeof(unsigned short)   \~english Input image 12bit, curve length:4096*sizeof(unsigned short)
                                                                    ///< \~chinese      Դͼ���ʽ16λ, ���߳��ȣ�65536*sizeof(unsigned short)  \~english Input image 16bit, curve length:65536*sizeof(unsigned short)
    MV_FG_GAMMA_TYPE_LRGB2SRGB          = 3,                        ///< \~chinese linear RGB to sRGB           \~english linear RGB to sRGB
    MV_FG_GAMMA_TYPE_SRGB2LRGB          = 4,                        ///< \~chinese sRGB to linear RGB(��ɫ�ʲ�ֵʱ֧�֣�ɫ��У��ʱ��Ч) \~english sRGB to linear RGB

}MV_FG_GAMMA_TYPE;

/// \~chinese Gamma��Ϣ, ����Gamma���߽���ʱ����������Ч�Ľ�������   \~english Gamma information, setting gamma curve correction, input a valid correction curve
typedef struct _MV_FG_GAMMA_INFO_
{
    MV_FG_GAMMA_TYPE    enGammaType;                                ///< [IN]  \~chinese Gamma����              \~english Gamma type

    float               fGammaValue;                                ///< [IN]  \~chinese Gammaֵ[0.1,4.0]       \~english Gamma value[0.1,4.0]

    unsigned char*      pGammaCurveBuf;                             ///< [IN]  \~chinese Gamma���߻���          \~english Gamma curve buffer
    unsigned int        nGammaCurveBufLen;                          ///< [IN]  \~chinese Gamma���߳���          \~english Gamma curve buffer size

    unsigned int        nReserved[4];                               ///<       \~chinese Ԥ���ֶ�       \~english Reserved

}MV_FG_GAMMA_INFO;

/// \~chinese CCM��Ϣ         \~english CCM information
typedef struct _MV_FG_CCM_INFO_
{
    bool32_t            bCCMEnable;                                 ///< [IN]  \~chinese �Ƿ�����CCM            \~english CCM enable

    int                 nCCMat[9];                                  ///< [IN]  \~chinese CCM����(-65536~65536)  \~english Color correction matrix(-65536~65536)
    unsigned int        nCCMScale;                                  ///< [IN]  \~chinese ����ϵ����2��������,���65536��    \~english Quantitative scale(Integer power of 2, <= 65536)

    unsigned int        nReserved[4];                               ///<       \~chinese Ԥ���ֶ�       \~english Reserved

}MV_FG_CCM_INFO;

/// \~chinese ���ظ�ʽת����Ϣ          \~english Pixel format conversion information
typedef struct _MV_FG_CONVERT_PIXEL_INFO_
{
    MV_FG_INPUT_IMAGE_INFO  stInputImageInfo;                       ///< [IN]  \~chinese ����ͼƬ��Ϣ     \~english Input image information

    MV_FG_OUTPUT_IMAGE_INFO stOutputImageInfo;                      ///< [IN][OUT]  \~chinese ���ͼƬ��Ϣ    \~english Output image information

    // ���²�����Bayer��ֵ����Ч
    // The following parameters work in Bayer CFA
    MV_FG_CFA_METHOD    enCfaMethod;                                ///< [IN]  \~chinese ��ֵ����   \~english CFA method
    bool32_t            bFilterEnable;                              ///< [IN]  \~chinese ƽ��ʹ��   \~english Filter enable
    MV_FG_GAMMA_INFO    stGammaInfo;                                ///< [IN]  \~chinese Gamma��Ϣ  \~english Gamma information
    MV_FG_CCM_INFO      stCCMInfo;                                  ///< [IN]  \~chinese CCM��Ϣ,��windows֧��    \~english CCM information��support only windows

    unsigned int        nReserved[4];                               ///<       \~chinese Ԥ���ֶ�   \~english Reserved

}MV_FG_CONVERT_PIXEL_INFO;

/// \~chinese ˮӡ��Ϣ                  \~english  Frame-specific information
typedef struct _MV_FG_FRAME_SPEC_INFO_
{
    /// \~chinese ���ˮӡʱ��      \~english Device frame-specific time scale
    unsigned int        nSecondCount;                               ///< [OUT] \~chinese ����                   \~english The Seconds
    unsigned int        nCycleCount;                                ///< [OUT] \~chinese ������                 \~english The Count of Cycle
    unsigned int        nCycleOffset;                               ///< [OUT] \~chinese ����ƫ����             \~english The Offset of Cycle

    float               fGain;                                      ///< [OUT] \~chinese ����                   \~english Gain
    float               fExposureTime;                              ///< [OUT] \~chinese �ع�ʱ��               \~english Exposure Time
    unsigned int        nAverageBrightness;                         ///< [OUT] \~chinese ƽ������               \~english Average brightness

    /// \~chinese ��ƽ�����        \~english White balance
    unsigned int        nRed;                                       ///< [OUT] \~chinese ��ɫ                   \~english Red
    unsigned int        nGreen;                                     ///< [OUT] \~chinese ��ɫ                   \~english Green
    unsigned int        nBlue;                                      ///< [OUT] \~chinese ��ɫ                   \~english Blue

    unsigned int        nFrameCounter;                              ///< [OUT] \~chinese ��֡��                 \~english Frame Counter
    unsigned int        nTriggerIndex;                              ///< [OUT] \~chinese ��������               \~english Trigger Counting

    unsigned int        nInput;                                     ///< [OUT] \~chinese ����                   \~english Input
    unsigned int        nOutput;                                    ///< [OUT] \~chinese ���                   \~english Output

    /// \~chinese ROI����           \~english ROI Region
    unsigned short      nOffsetX;                                   ///< [OUT] \~chinese ˮƽƫ����             \~english OffsetX
    unsigned short      nOffsetY;                                   ///< [OUT] \~chinese ��ֱƫ����             \~english OffsetY
    unsigned short      nFrameWidth;                                ///< [OUT] \~chinese ˮӡ��                 \~english The Width of Chunk
    unsigned short      nFrameHeight;                               ///< [OUT] \~chinese ˮӡ��                 \~english The Height of Chunk

    unsigned int        nReserved[16];                              ///<       \~chinese Ԥ��                   \~english Reserved

}MV_FG_FRAME_SPEC_INFO;

/// \~chinese ����������              \~english High Bandwidth decode structure
typedef struct _MV_FG_HB_DECODE_PARAM_T_
{
    unsigned char*          pSrcBuf;                                ///< [IN]  \~chinese �������ݻ���           \~english Input data buffer
    unsigned int            nSrcLen;                                ///< [IN]  \~chinese �������ݴ�С           \~english Input data size

    MV_FG_OUTPUT_IMAGE_INFO stOutputImageInfo;                      ///< [IN][OUT]  \~chinese ���ͼƬ��Ϣ       \~english Output image information

    MV_FG_FRAME_SPEC_INFO   stFrameSpecInfo;                        ///< [OUT] \~chinese ˮӡ��Ϣ���ݲ�֧�֣�   \~english Frame Spec Info(Not support)

    unsigned int            nRes[8];                                ///<       \~chinese Ԥ��                   \~english Reserved

}MV_FG_HB_DECODE_PARAM;

/// \~ chinese JPEG�������             \~english JPEG decoding structure
typedef struct _MV_FG_DECODE_JPEG_PARAM_T_
{
    unsigned char*          pSrcBuf;                                ///< [IN]  \~chinese �������ݻ���           \~english Input data buffer
    unsigned int            nSrcLen;                                ///< [IN]  \~chinese �������ݴ�С           \~english Input data size

    MV_FG_OUTPUT_IMAGE_INFO stOutputImageInfo;                      ///< [IN][OUT]  \~chinese ���ͼƬ��Ϣ       \~english Output image information

    unsigned int            nRes[8];                                ///<       \~chinese Ԥ��                   \~english Reserved


}MV_FG_DECODE_JPEG_PARAM;

/// \~chinese ͼ�����鷽ʽ          \~english Image reconstruct mode
#define MV_FG_MAX_SPLIT_NUM                     8                   ///< \~chinese ��ཫԴͼ���ֵĸ���  \~english The maximum number of source images to split
#define MV_FG_ROTATE_MODE                       0x1000              ///< \~chinese ��ת��ʽ       \~english Rotation mode
#define MV_FG_FLIP_MODE                         0x2000              ///< \~chinese ��ת��ʽ       \~english Flip mode
#define MV_FG_SPLIT_BY_LINE_MODE                0x3000              ///< \~chinese ���в�ַ�ʽ   \~english Split by row

/// \~chinese ���鷽ʽ          \~english Reconstruct mode
typedef enum _MV_FG_RECONSTRUCT_MODE_
{
    /// \~chinese ��ת�ͷ�תֻ֧��MV_FG_PIXEL_TYPE_Mono8��MV_FG_PIXEL_TYPE_RGB8_Packed��MV_FG_PIXEL_TYPE_BGR8_Packed�������ظ�ʽ \~english Rotate and flip only support MV_FG_PIXEL_TYPE_Mono8, MV_FG_PIXEL_TYPE_RGB8_Packed and MV_FG_PIXEL_TYPE_BGR8_Packed pixel formats
    RECONSTRUCT_MODE_ROTATE_90                  = (MV_FG_ROTATE_MODE | 0x0001),         ///< \~chinese ��ת90��    \~english Rotate 90 degrees
    RECONSTRUCT_MODE_ROTATE_180                 = (MV_FG_ROTATE_MODE | 0x0002),         ///< \~chinese ��ת180��   \~english Rotate 180 degrees
    RECONSTRUCT_MODE_ROTATE_270                 = (MV_FG_ROTATE_MODE | 0x0003),         ///< \~chinese ��ת270��   \~english Rotate 270 degrees

    RECONSTRUCT_MODE_FLIP_VERTICAL              = (MV_FG_FLIP_MODE | 0x0001),           ///< \~chinese ��ֱ��ת    \~english Flip vertically
    RECONSTRUCT_MODE_FLIP_HORIZONTAL            = (MV_FG_FLIP_MODE | 0x0002),           ///< \~chinese ˮƽ��ת    \~english Flip horizontally

    /// \~chinese ���в��ֻ֧�ֶ���������ɼ���ͼ����в��  \~english Split by line only supports splitting the image collected by the line scan camera
    RECONSTRUCT_MODE_SPLIT_BY_LINE_2            = (MV_FG_SPLIT_BY_LINE_MODE | 0x0002),  ///< \~chinese ���в�ֳ�2��ͼ��    \~english Split into 2 images by line
    RECONSTRUCT_MODE_SPLIT_BY_LINE_3            = (MV_FG_SPLIT_BY_LINE_MODE | 0x0003),  ///< \~chinese ���в�ֳ�3��ͼ��    \~english Split into 3 images by line
    RECONSTRUCT_MODE_SPLIT_BY_LINE_4            = (MV_FG_SPLIT_BY_LINE_MODE | 0x0004),  ///< \~chinese ���в�ֳ�4��ͼ��    \~english Split into 4 images by line

}MV_FG_RECONSTRUCT_MODE;

/// \~chinese ������Ϣ          \~english Reconstruct information
typedef struct _MV_FG_RECONSTRUCT_INFO_
{
    MV_FG_INPUT_IMAGE_INFO  stInputImageInfo;                       ///< [IN]  \~chinese ����ͼƬ��Ϣ   \~english Input image information

    MV_FG_OUTPUT_IMAGE_INFO stOutputImageInfo[MV_FG_MAX_SPLIT_NUM]; ///< [IN][OUT]  \~chinese ���ͼƬ��Ϣ    \~english Output image information

    MV_FG_RECONSTRUCT_MODE  enReconstructMode;                      ///< [IN]  \~chinese ���鷽ʽ       \~english Reconstruct mode

    unsigned int        nReserved[4];                               ///<       \~chinese Ԥ���ֶ�       \~english Reserved

}MV_FG_RECONSTRUCT_INFO;

///< \~chinese �ڵ�Ȩ��         \~english Node permissions
typedef enum _MV_FG_NODE_ACCESS_MODE_
{
    ACCESS_MODE_NI                              = 0,                ///< \~chinese Value����ʵ��   \~english Value is not realizable
    ACCESS_MODE_NA                              = 1,                ///< \~chinese Value������     \~english Value not available
    ACCESS_MODE_WO                              = 2,                ///< \~chinese Valueֻд       \~english Value write only
    ACCESS_MODE_RO                              = 3,                ///< \~chinese Valueֻ��       \~english Value read only
    ACCESS_MODE_RW                              = 4,                ///< \~chinese Value��д       \~english Value read and write
    ACCESS_MODE_UNDEFINED                       = 5,                ///< \~chinese Valueδ����     \~english Value undefined

}MV_FG_NODE_ACCESS_MODE;

///< \~chinese �ڵ�����         \~english Node type
typedef enum _MV_FG_NODE_INTERFACE_TYPE_
{
    INTERFACE_TYPE_Value                        = 0,                ///< \~chinese Value        \~english Value
    INTERFACE_TYPE_Base                         = 1,                ///< \~chinese Base         \~english Base
    INTERFACE_TYPE_Integer                      = 2,                ///< \~chinese Integer      \~english Integer
    INTERFACE_TYPE_Boolean                      = 3,                ///< \~chinese Boolean      \~english Boolean
    INTERFACE_TYPE_Command                      = 4,                ///< \~chinese Command      \~english Command
    INTERFACE_TYPE_Float                        = 5,                ///< \~chinese Float        \~english Float
    INTERFACE_TYPE_String                       = 6,                ///< \~chinese String       \~english String
    INTERFACE_TYPE_Register                     = 7,                ///< \~chinese Register     \~english Register
    INTERFACE_TYPE_Category                     = 8,                ///< \~chinese Category     \~english Category
    INTERFACE_TYPE_Enumeration                  = 9,                ///< \~chinese Enumeration  \~english Enumeration
    INTERFACE_TYPE_EnumEntry                    = 10,               ///< \~chinese EnumEntry    \~english EnumEntry
    INTERFACE_TYPE_Port                         = 11,               ///< \~chinese Port         \~english Port

}MV_FG_NODE_INTERFACE_TYPE;

/// \~chinese Int������Ϣ           \~english Integer type information
typedef struct _MV_FG_INTVALUE_
{
    int64_t             nCurValue;                                  ///< [OUT] \~chinese ��ǰֵ    \~english Current value
    int64_t             nMax;                                       ///< [OUT] \~chinese ���ֵ    \~english Maximum value
    int64_t             nMin;                                       ///< [OUT] \~chinese ��Сֵ    \~english Minimum value
    int64_t             nInc;                                       ///< [OUT] \~chinese ����      \~english Increment

    unsigned int        nReserved[16];                              ///<       \~chinese �����ֶ�  \~english Reserved

}MV_FG_INTVALUE;

/// \~chinese XML�����ļ��е���������        \~english Maximum number of symbols in XML description file
#define MV_FG_MAX_SYMBOLIC_NUM                  64

/// \~chinese XML�����ļ��ķ�����󳤶�        \~english Maximum symbol length of XML description file
#define MV_FG_MAX_SYMBOLIC_STRLEN               64

/// \~chinese ö��������Ϣ            \~english Enumeration type information
typedef struct _MV_FG_ENUMVALUE_
{
    unsigned int        nCurValue;                                  ///< [OUT] \~chinese ��ǰֵ             \~english Current value
    char                strCurSymbolic[MV_FG_MAX_SYMBOLIC_STRLEN];  ///< [OUT] \~chinese ��ǰֵ�ķ�������   \~english The symbolic name of the current value

    unsigned int        nSupportedNum;                              ///< [OUT] \~chinese ֧�ֵ�ö�����͸���      \~english Number of supported enumeration types
    unsigned int        nSupportValue[MV_FG_MAX_SYMBOLIC_NUM];      ///< [OUT] \~chinese ֧�ֵ�ö�����͵�ֵ      \~english Values of supported enumeration types
    char                strSymbolic[MV_FG_MAX_SYMBOLIC_NUM][MV_FG_MAX_SYMBOLIC_STRLEN];///< [OUT] \~chinese ֧�ֵ�ö�����͵ķ�������    \~english Symbolic names of supported enumeration types

    unsigned int        nReserved[4];                               ///<       \~chinese �����ֶ�       \~english Reserved

}MV_FG_ENUMVALUE;

/// \~chinese Float������Ϣ         \~english Float type information
typedef struct _MV_FG_FLOATVALUE_
{
    float               fCurValue;                                  ///< [OUT] \~chinese ��ǰֵ    \~english Current value
    float               fMax;                                       ///< [OUT] \~chinese ���ֵ    \~english Maximum value
    float               fMin;                                       ///< [OUT] \~chinese ��Сֵ    \~english Minimum value

    unsigned int        nReserved[4];                               ///<       \~chinese �����ֶ�  \~english Reserved

}MV_FG_FLOATVALUE;

/// \~chinese String������Ϣ            \~english String type information
typedef struct _MV_FG_STRINGVALUE_
{
    char                strCurValue[256];                           ///< [OUT] \~chinese ��ǰֵ     \~english Current value
    int64_t             nMaxLength;                                 ///< [OUT] \~chinese ��󳤶�   \~english Maximum length

    unsigned int        nReserved[4];                               ///<       \~chinese �����ֶ�   \~english Reserved

}MV_FG_STRINGVALUE;

/// \~chinese �ļ���ȡ                  \~english File Access
typedef struct _MV_FG_FILE_ACCESS_
{
    const char*         pUserFileName;                              ///< [IN]  \~chinese �û��Զ�����ļ���     \~english User file name
    const char*         pDevFileName;                               ///< [IN]  \~chinese ��/����е��ļ���, ����UserSetSelector���Խڵ�, ö����, ����Default, UserSet1��ֵ   \~english The file name in the Interface/Camera, from the UserSetSelector attribute node, enumeration type, including Default, UserSet1, etc

    unsigned int        nReserved[32];                              ///<       \~chinese Ԥ��                   \~english Reserved

}MV_FG_FILE_ACCESS;

/// \~chinese ������           \~english Baud rate
#define MV_FG_BAUDRATE_9600                     0x00000001          ///< \~chinese 9600     \~english 9600
#define MV_FG_BAUDRATE_19200                    0x00000002          ///< \~chinese 19200    \~english 19200
#define MV_FG_BAUDRATE_38400                    0x00000004          ///< \~chinese 38400    \~english 38400
#define MV_FG_BAUDRATE_57600                    0x00000008          ///< \~chinese 57600    \~english 57600
#define MV_FG_BAUDRATE_115200                   0x00000010          ///< \~chinese 115200   \~english 115200
#define MV_FG_BAUDRATE_230400                   0x00000020          ///< \~chinese 230400   \~english 230400
#define MV_FG_BAUDRATE_460800                   0x00000040          ///< \~chinese 460800   \~english 460800
#define MV_FG_BAUDRATE_921600                   0x00000080          ///< \~chinese 921600   \~english 921600
#define MV_FG_BAUDRATE_AUTOMAX                  0x40000000          ///< \~chinese �Զ�Э�������֧�ֵ����ֵ   \~english Automatically negotiates to the maximum value supported by the camera

///< \~chinese ����ָ��         \~english Configuration commandy
typedef enum _MV_FG_CONFIG_CMD_
{
    CONFIG_CMD_INT64_BAUDRATE                   = 1,                ///< \~chinese �����ʣ�����, ��ΧMV_FG_BAUDRATE_9600 ~ MV_FG_BAUDRATE_AUTOMAX, Ĭ��ֵMV_FG_BAUDRATE_115200   \~english Baud rate, integer, Value range:MV_FG_BAUDRATE_9600 ~ MV_FG_BAUDRATE_AUTOMAX, Default vaule:MV_FG_BAUDRATE_115200

}MV_FG_CONFIG_CMD;

/// \~chinese �쳣��Ϣ����        \~english Exception information type
typedef enum _MV_FG_EXCEPTION_TYPE_
{
    EXCEPTION_TYPE_SYSTEM_TEMPERATURE_UPLIMIT          = 0x0080,           ///< \~chinese �¶�����                            \~english Temperature upper limit
    EXCEPTION_TYPE_SYSTEM_TEMPERATURE_LOWLIMIT         = 0x0081,           ///< \~chinese �¶�������                          \~english Temperature lower limit
    EXCEPTION_TYPE_SYSTEM_DDR_INIT                     = 0x0082,           ///< \~chinese DDR��ʼ��ʧ��                       \~english DDR Initial Error

    EXCEPTION_TYPE_CARD_PACKETBUF_ERR                  = 0x0180,           ///< \~chinese ���������                          \~english Card Packet Buffer Error
    EXCEPTION_TYPE_CARD_ACKPACKETBUF_ERR               = 0x0181,           ///< \~chinese ��Ӧ���������                      \~english Card Ack Packet Buffer Error
    EXCEPTION_TYPE_CARD_EVENT_PACKETBUF_ERR            = 0x0182,           ///< \~chinese �¼����������                      \~english Card Event Packet Buffer Error

    EXCEPTION_TYPE_LINK0_STREAM_CRC_ERR                = 0x1080,           ///< \~chinese Link0 ��CRCУ�����                 \~english Link0 Stream CRC Error Event
    EXCEPTION_TYPE_LINK0_STREAM_PACKET_RESEND          = 0x1081,           ///< \~chinese Link0 ���ط���                      \~english Link0 Stream Packet Resend
    EXCEPTION_TYPE_LINK0_STREAM_CTRLPACKET_ERR         = 0x1082,           ///< \~chinese Link0 ���ư�����                    \~english Link0 Control Packet Error Event
    EXCEPTION_TYPE_LINK0_PRETREATBUF_ERR               = 0x1090,           ///< \~chinese Link0 Ԥ���������                \~english Link0 Pretreat Buffer Error
    EXCEPTION_TYPE_LINK0_CAM_ACK_RECVBUF_ERR           = 0x1091,           ///< \~chinese Link0 ����ذ����ջ������          \~english Link0 Camera Ack Packet Receiver Buffer Error
    EXCEPTION_TYPE_LINK0_CAM_ACK_TRANSMITBUF_ERR       = 0x1092,           ///< \~chinese Link0 ����ذ����ͻ������          \~english Link0 Camera Packet Transmitter Buffer Error

    EXCEPTION_TYPE_LINK1_STREAM_CRC_ERR                = 0x1180,           ///< \~chinese Link1 ��CRCУ�����                 \~english Link1 Stream CRC Error Event
    EXCEPTION_TYPE_LINK1_STREAM_PACKET_RESEND          = 0x1181,           ///< \~chinese Link1 ���ط���                      \~english Link1 Stream Packet Resend
    EXCEPTION_TYPE_LINK1_STREAM_CTRLPACKET_ERR         = 0x1182,           ///< \~chinese Link1 ���ư�����                    \~english Link1 Control Packet Error Event
    EXCEPTION_TYPE_LINK1_PRETREATBUF_ERR               = 0x1190,           ///< \~chinese Link1 Ԥ���������                \~english Link1 Pretreat Buffer Error
    EXCEPTION_TYPE_LINK1_CAM_ACK_RECVBUF_ERR           = 0x1191,           ///< \~chinese Link1 ����ذ����ջ������          \~english Link1 Camera Ack Packet Receiver Buffer Error
    EXCEPTION_TYPE_LINK1_CAM_ACK_TRANSMITBUF_ERR       = 0x1192,           ///< \~chinese Link1 ����ذ����ͻ������          \~english Link1 Camera Packet Transmitter Buffer Error

    EXCEPTION_TYPE_LINK2_STREAM_CRC_ERR                = 0x1280,           ///< \~chinese Link2 ��CRCУ�����                 \~english Link2 Stream CRC Error Event
    EXCEPTION_TYPE_LINK2_STREAM_PACKET_RESEND          = 0x1281,           ///< \~chinese Link2 ���ط���                      \~english Link2 Stream Packet Resend
    EXCEPTION_TYPE_LINK2_STREAM_CTRLPACKET_ERR         = 0x1282,           ///< \~chinese Link2 ���ư�����                    \~english Link2 Control Packet Error Event
    EXCEPTION_TYPE_LINK2_PRETREATBUF_ERR               = 0x1290,           ///< \~chinese Link2 Ԥ���������                \~english Link2 Pretreat Buffer Error
    EXCEPTION_TYPE_LINK2_CAM_ACK_RECVBUF_ERR           = 0x1291,           ///< \~chinese Link2 ����ذ����ջ������          \~english Link2 Camera Ack Packet Receiver Buffer Error
    EXCEPTION_TYPE_LINK2_CAM_ACK_TRANSMITBUF_ERR       = 0x1292,           ///< \~chinese Link2 ����ذ����ͻ������          \~english Link2 Camera Packet Transmitter Buffer Error

    EXCEPTION_TYPE_LINK3_STREAM_CRC_ERR                = 0x1380,           ///< \~chinese Link3 ��CRCУ�����                 \~english Link3 Stream CRC Error Event
    EXCEPTION_TYPE_LINK3_STREAM_PACKET_RESEND          = 0x1381,           ///< \~chinese Link3 ���ط���                      \~english Link3 Stream Packet Resend
    EXCEPTION_TYPE_LINK3_STREAM_CTRLPACKET_ERR         = 0x1382,           ///< \~chinese Link3 ���ư�����                    \~english Link3 Control Packet Error Event
    EXCEPTION_TYPE_LINK3_PRETREATBUF_ERR               = 0x1390,           ///< \~chinese Link3 Ԥ���������                \~english Link3 Pretreat Buffer Error
    EXCEPTION_TYPE_LINK3_CAM_ACK_RECVBUF_ERR           = 0x1391,           ///< \~chinese Link3 ����ذ����ջ������          \~english Link3 Camera Ack Packet Receiver Buffer Error
    EXCEPTION_TYPE_LINK3_CAM_ACK_TRANSMITBUF_ERR       = 0x1392,           ///< \~chinese Link3 ����ذ����ͻ������          \~english Link3 Camera Packet Transmitter Buffer Error

    EXCEPTION_TYPE_STREAM0_DROP_FRAME_IMAGE            = 0x2080,           ///< \~chinese STREAM0 ����ͼ��֡���涪��          \~english STREAM0 Drop Image Frame
    EXCEPTION_TYPE_STREAM0_IMAGE_DATACOUNT_ERR         = 0x2081,           ///< \~chinese STREAM0 ����ͼ�񣨴�С�������쳣    \~english STREAM0 Receive Image Data Count Error
    EXCEPTION_TYPE_STREAM0_DROP_FRAME_TRIGGER          = 0x2082,           ///< \~chinese STREAM0 ����֡��������              \~english STREAM0 Drop Frame Trigger
    EXCEPTION_TYPE_STREAM0_QUEUEBUF_ERR                = 0x2090,           ///< \~chinese STREAM0 QUEUE�����쳣               \~english STREAM0 QUEUE Buffer Error
    EXCEPTION_TYPE_STREAM0_WDMABUF_ERR                 = 0x2091,           ///< \~chinese STREAM0 WDMA�����쳣                \~english STREAM0 WDMA Buffer Error
    EXCEPTION_TYPE_STREAM0_RDMABUF_ERR                 = 0x2092,           ///< \~chinese STREAM0 RDMA�����쳣                \~english STREAM0 RDMA Buffer Error
    EXCEPTION_TYPE_STREAM0_PACKETBUF_ERR               = 0x2093,           ///< \~chinese STREAM0 PACKET�����쳣              \~english STREAM0 PACKET Buffer Error
    EXCEPTION_TYPE_STREAM0_WDMALENGTH_ERR              = 0x2094,           ///< \~chinese STREAM0 WDMA�����쳣                \~english STREAM0 WDMA Length Error
    EXCEPTION_TYPE_STREAM0_RDMALENGTH_ERR              = 0x2095,           ///< \~chinese STREAM0 RDMA�����쳣                \~english STREAM0 RDMA Length Error

    EXCEPTION_TYPE_STREAM1_DROP_FRAME_IMAGE            = 0x2180,           ///< \~chinese STREAM1 ����ͼ��֡���涪��          \~english STREAM1 Drop Image Frame
    EXCEPTION_TYPE_STREAM1_IMAGE_DATACOUNT_ERR         = 0x2181,           ///< \~chinese STREAM1 ����ͼ�񣨴�С�������쳣    \~english STREAM1 Receive Image Data Count Error
    EXCEPTION_TYPE_STREAM1_DROP_FRAME_TRIGGER          = 0x2182,           ///< \~chinese STREAM1 ����֡��������              \~english STREAM1 Drop Frame Trigger
    EXCEPTION_TYPE_STREAM1_QUEUEBUF_ERR                = 0x2190,           ///< \~chinese STREAM1 QUEUE�����쳣               \~english STREAM1 QUEUE Buffer Error
    EXCEPTION_TYPE_STREAM1_WDMABUF_ERR                 = 0x2191,           ///< \~chinese STREAM1 WDMA�����쳣                \~english STREAM1 WDMA Buffer Error
    EXCEPTION_TYPE_STREAM1_RDMABUF_ERR                 = 0x2192,           ///< \~chinese STREAM1 RDMA�����쳣                \~english STREAM1 RDMA Buffer Error
    EXCEPTION_TYPE_STREAM1_PACKETBUF_ERR               = 0x2193,           ///< \~chinese STREAM1 PACKET�����쳣              \~english STREAM1 PACKET Buffer Error
    EXCEPTION_TYPE_STREAM1_WDMALENGTH_ERR              = 0x2194,           ///< \~chinese STREAM1 WDMA�����쳣                \~english STREAM1 WDMA Length Error
    EXCEPTION_TYPE_STREAM1_RDMALENGTH_ERR              = 0x2195,           ///< \~chinese STREAM1 RDMA�����쳣                \~english STREAM1 RDMA Length Error

    EXCEPTION_TYPE_STREAM2_DROP_FRAME_IMAGE            = 0x2280,           ///< \~chinese STREAM2 ����ͼ��֡���涪��          \~english STREAM2 Drop Image Frame
    EXCEPTION_TYPE_STREAM2_IMAGE_DATACOUNT_ERR         = 0x2281,           ///< \~chinese STREAM2 ����ͼ�񣨴�С�������쳣    \~english STREAM2 Receive Image Data Count Error
    EXCEPTION_TYPE_STREAM2_DROP_FRAME_TRIGGER          = 0x2282,           ///< \~chinese STREAM2 ����֡��������              \~english STREAM2 Drop Frame Trigger
    EXCEPTION_TYPE_STREAM2_QUEUEBUF_ERR                = 0x2290,           ///< \~chinese STREAM2 QUEUE�����쳣               \~english STREAM2 QUEUE Buffer Error
    EXCEPTION_TYPE_STREAM2_WDMABUF_ERR                 = 0x2291,           ///< \~chinese STREAM2 WDMA�����쳣                \~english STREAM2 WDMA Buffer Error
    EXCEPTION_TYPE_STREAM2_RDMABUF_ERR                 = 0x2292,           ///< \~chinese STREAM2 RDMA�����쳣                \~english STREAM2 RDMA Buffer Error
    EXCEPTION_TYPE_STREAM2_PACKETBUF_ERR               = 0x2293,           ///< \~chinese STREAM2 PACKET�����쳣              \~english STREAM2 PACKET Buffer Error
    EXCEPTION_TYPE_STREAM2_WDMALENGTH_ERR              = 0x2294,           ///< \~chinese STREAM2 WDMA�����쳣                \~english STREAM2 WDMA Length Error
    EXCEPTION_TYPE_STREAM2_RDMALENGTH_ERR              = 0x2295,           ///< \~chinese STREAM2 RDMA�����쳣                \~english STREAM2 RDMA Length Error

    EXCEPTION_TYPE_STREAM3_DROP_FRAME_IMAGE            = 0x2380,           ///< \~chinese STREAM3 ����ͼ��֡���涪��          \~english STREAM3 Drop Image Frame
    EXCEPTION_TYPE_STREAM3_IMAGE_DATACOUNT_ERR         = 0x2381,           ///< \~chinese STREAM3 ����ͼ�񣨴�С�������쳣    \~english STREAM3 Receive Image Data Count Error
    EXCEPTION_TYPE_STREAM3_DROP_FRAME_TRIGGER          = 0x2382,           ///< \~chinese STREAM3 ����֡��������              \~english STREAM3 Drop Frame Trigger
    EXCEPTION_TYPE_STREAM3_QUEUEBUF_ERR                = 0x2390,           ///< \~chinese STREAM3 QUEUE�����쳣               \~english STREAM3 QUEUE Buffer Error
    EXCEPTION_TYPE_STREAM3_WDMABUF_ERR                 = 0x2391,           ///< \~chinese STREAM3 WDMA�����쳣                \~english STREAM3 WDMA Buffer Error
    EXCEPTION_TYPE_STREAM3_RDMABUF_ERR                 = 0x2392,           ///< \~chinese STREAM3 RDMA�����쳣                \~english STREAM3 RDMA Buffer Error
    EXCEPTION_TYPE_STREAM3_PACKETBUF_ERR               = 0x2393,           ///< \~chinese STREAM3 PACKET�����쳣              \~english STREAM3 PACKET Buffer Error
    EXCEPTION_TYPE_STREAM3_WDMALENGTH_ERR              = 0x2394,           ///< \~chinese STREAM3 WDMA�����쳣                \~english STREAM3 WDMA Length Error
    EXCEPTION_TYPE_STREAM3_RDMALENGTH_ERR              = 0x2395,           ///< \~chinese STREAM3 RDMA�����쳣                \~english STREAM3 RDMA Length Error


    EXCEPTION_TYPE_PCIE_SCHEDULEBUF_ERR                = 0x3088,           ///< \~chinese ����ģ�黺���쳣                    \~english Sched Buffer Error
    EXCEPTION_TYPE_PCIE_SCHEDULE_ERR                   = 0x3089,           ///< \~chinese ���Ƚ�����쳣ֵ                    \~english Sched Error

    EXCEPTION_TYPE_PCIE_LINK0_RECVBUF_ERR              = 0x3180,           ///< \~chinese Link0 ����Link��buffer�쳣           \~english Link0 Reveive Buffer Error
    EXCEPTION_TYPE_PCIE_LINK0_LENGTH_ERR               = 0x3181,           ///< \~chinese Link0 ���ư������쳣                \~english Link0 Length Erro 
    EXCEPTION_TYPE_PCIE_LINK0_SOFT_RECVBUF_ERR         = 0x3280,           ///< \~chinese Link0 ����Link��buffer�쳣           \~english Link0 Soft Reveive Buffer Error
    EXCEPTION_TYPE_PCIE_LINK0_SOFT_LENGTH_ERR          = 0x3281,           ///< \~chinese Link0 ���ư������쳣                \~english Link0 Soft Length Erro 
    
    EXCEPTION_TYPE_PCIE_LINK1_RECVBUF_ERR              = 0x3188,           ///< \~chinese Link1 ����Link��buffer�쳣           \~english Link1 Reveive Buffer Error
    EXCEPTION_TYPE_PCIE_LINK1_LENGTH_ERR               = 0x3189,           ///< \~chinese Link1 ���ư������쳣                \~english Link1 Length Erro 
    EXCEPTION_TYPE_PCIE_LINK1_SOFT_RECVBUF_ERR         = 0x3288,           ///< \~chinese Link1 ����Link��buffer�쳣           \~english Link1 Soft Reveive Buffer Error
    EXCEPTION_TYPE_PCIE_LINK1_SOFT_LENGTH_ERR          = 0x3289,           ///< \~chinese Link1 ���ư������쳣                \~english Link1 Soft Length Erro 

    EXCEPTION_TYPE_PCIE_LINK2_RECVBUF_ERR              = 0x3190,           ///< \~chinese Link2 ����Link��buffer�쳣           \~english Link2 Reveive Buffer Error
    EXCEPTION_TYPE_PCIE_LINK2_LENGTH_ERR               = 0x3191,           ///< \~chinese Link2 ���ư������쳣                \~english Link2 Length Erro 
    EXCEPTION_TYPE_PCIE_LINK2_SOFT_RECVBUF_ERR         = 0x3290,           ///< \~chinese Link2 ����Link��buffer�쳣           \~english Link2 Soft Reveive Buffer Error
    EXCEPTION_TYPE_PCIE_LINK2_SOFT_LENGTH_ERR          = 0x3291,           ///< \~chinese Link2 ���ư������쳣                \~english Link2 Soft Length Erro 

    EXCEPTION_TYPE_PCIE_LINK3_RECVBUF_ERR              = 0x3198,           ///< \~chinese Link3 ����Link��buffer�쳣           \~english Link3 Reveive Buffer Error
    EXCEPTION_TYPE_PCIE_LINK3_LENGTH_ERR               = 0x3199,           ///< \~chinese Link3 ���ư������쳣                \~english Link3 Length Erro 
    EXCEPTION_TYPE_PCIE_LINK3_SOFT_RECVBUF_ERR         = 0x3298,           ///< \~chinese Link3 ����Link��buffer�쳣           \~english Link3 Soft Reveive Buffer Error
    EXCEPTION_TYPE_PCIE_LINK3_SOFT_LENGTH_ERR          = 0x3299,           ///< \~chinese Link3 ���ư������쳣                \~english Link3 Soft Length Erro 
    
    EXCEPTION_TYPE_PCIE_STREAM0_RECVBUF_ERR            = 0x3382,           ///< \~chinese STREAM0 ����Stream��fifo�쳣         \~english STREAM0 Receive Buffer Error
    EXCEPTION_TYPE_PCIE_STREAM0_LIST_ERR               = 0x3383,           ///< \~chinese STREAM0 �����ʽ����                \~english STREAM0 List Error
    EXCEPTION_TYPE_PCIE_STREAM0_SIZE_ERR               = 0x3384,           ///< \~chinese STREAM0 ͼ���С���ڴ治ƥ��        \~english STREAM0 Size Error

    EXCEPTION_TYPE_PCIE_STREAM1_RECVBUF_ERR            = 0x338A,           ///< \~chinese STREAM1 ����Stream��fifo�쳣         \~english STREAM1 Receive Buffer Error
    EXCEPTION_TYPE_PCIE_STREAM1_LIST_ERR               = 0x338B,           ///< \~chinese STREAM1 �����ʽ����                \~english STREAM1 List Error
    EXCEPTION_TYPE_PCIE_STREAM1_SIZE_ERR               = 0x338C,           ///< \~chinese STREAM1 ͼ���С���ڴ治ƥ��        \~english STREAM1 Size Error

    EXCEPTION_TYPE_PCIE_STREAM2_RECVBUF_ERR            = 0x3392,           ///< \~chinese STREAM2 ����Stream��fifo�쳣         \~english STREAM2 Receive Buffer Error
    EXCEPTION_TYPE_PCIE_STREAM2_LIST_ERR               = 0x3393,           ///< \~chinese STREAM2 �����ʽ����                \~english STREAM2 List Error
    EXCEPTION_TYPE_PCIE_STREAM2_SIZE_ERR               = 0x3394,           ///< \~chinese STREAM2 ͼ���С���ڴ治ƥ��        \~english STREAM2 Size Error

    EXCEPTION_TYPE_PCIE_STREAM3_RECVBUF_ERR            = 0x339A,           ///< \~chinese STREAM3 ����Stream��fifo�쳣         \~english STREAM3 Receive Buffer Error
    EXCEPTION_TYPE_PCIE_STREAM3_LIST_ERR               = 0x339B,           ///< \~chinese STREAM3 �����ʽ����                \~english STREAM3 List Error
    EXCEPTION_TYPE_PCIE_STREAM3_SIZE_ERR               = 0x339C,           ///< \~chinese STREAM3 ͼ���С���ڴ治ƥ��        \~english STREAM3 Size Error

    EXCEPTION_TYPE_CAMERA_DISCONNECT_ERR               = 0x10000001,       ///< \~chinese CAMERA ������ߴ���                 \~english CAMERA Disconnect Error


}MV_FG_EXCEPTION_TYPE;

///< \~chinese �¼�������󳤶�         \~english Maximum length of event name
#define MV_FG_MAX_EVENT_NAME_SIZE               128

/// \~chinese �¼���Ϣ          \~english Event information
typedef struct _MV_FG_EVENT_INFO_
{
    char                EventName[MV_FG_MAX_EVENT_NAME_SIZE];       ///< [OUT] \~chinese �¼�����   \~english Event name
    unsigned int        nEventID;                                   ///< [OUT] \~chinese �¼���     \~english Event ID

    uint64_t            nBlockID;                                   ///< [OUT] \~chinese ֡�ţ����¼���Ч�����޹̼�֧�֣�   \~english Frame ID, stream event valid����

    uint64_t            nTimestamp;                                 ///< [OUT] \~chinese ʱ���     \~english Timestamp

    void*               pEventData;                                 ///< [OUT] \~chinese �¼����ݣ��ڲ����棬��Ҫ��ʱ�������ݴ������޹̼�֧�֣�   \~english Event data, internal buffer, need to be processed in time
    unsigned int        nEventDataSize;                             ///< [OUT] \~chinese �¼����ݳ��ȣ����޹̼�֧�֣�     \~english Event data szie

    unsigned int        nReserved[4];                               ///<       \~chinese Ԥ��     \~english Reserved

}MV_FG_EVENT_INFO;

/// \~chinese �Զ����                    \~english Point defined
typedef struct _MVFG_POINTF
{
    float           fX;             ///<  \~chinese �õ����ͼ�����Ե���룬����ͼ������λ�ã���ΧΪ[0.0 , 1.0]   \~english Distance From Left��Range[0.0, 1.0]
    float           fY;             ///<  \~chinese �õ����ͼ���ϱ�Ե���룬����ͼ������λ�ã���ΧΪ[0.0 , 1.0]   \~english Distance From Top��Range[0.0, 1.0]
    unsigned int    nReserved[4];   ///<  \~chinese Ԥ��                        \~english Reserved

}MVFG_POINTF;

/// \~chinese ��������ɫ                \~english Color of Auxiliary Line
typedef struct _MVFG_COLORF
{
    float           fR;             ///<  \~chinese ��ɫ������������ɫ�������ȣ���ΧΪ[0.0 , 1.0]��������[0, 255]����ɫ���   \~english Red��Range[0.0, 1.0]
    float           fG;             ///<  \~chinese ��ɫ������������ɫ�������ȣ���ΧΪ[0.0 , 1.0]��������[0, 255]����ɫ���   \~english Green��Range[0.0, 1.0]
    float           fB;             ///<  \~chinese ��ɫ������������ɫ�������ȣ���ΧΪ[0.0 , 1.0]��������[0, 255]����ɫ���   \~english Blue��Range[0.0, 1.0]
    float           fAlpha;         ///<  \~chinese ͸���ȣ�����������ɫ�����͸���ȣ���ΧΪ[0.0 , 1.0] (�˲��������ݲ�֧��)    \~english Alpha��Range[0.0, 1.0](Not Support)
    unsigned int    nReserved[4];   ///<  \~chinese Ԥ��                        \~english Reserved

}MVFG_COLORF;

/// \~chinese ���ο�������Ϣ            \~english Rect Area Info
typedef struct _MVFG_RECT_INFO
{
    float           fTop;           ///<  \~chinese �����ϱ�Ե����ͼ���ϱ�Ե�ľ��룬����ͼ������λ�ã���ΧΪ[0.0 , 1.0]   \~english Distance From Image Top��Range[0, 1.0]
    float           fBottom;        ///<  \~chinese �����±�Ե����ͼ���ϱ�Ե�ľ��룬����ͼ������λ�ã���ΧΪ[0.0 , 1.0]   \~english Distance From Image Top��Range[0, 1.0]
    float           fLeft;          ///<  \~chinese �������Ե����ͼ�����Ե�ľ��룬����ͼ������λ�ã���ΧΪ[0.0 , 1.0]   \~english Distance From Image Left��Range[0, 1.0]
    float           fRight;         ///<  \~chinese �����ұ�Ե����ͼ�����Ե�ľ��룬����ͼ������λ�ã���ΧΪ[0.0 , 1.0]   \~english Distance From Image Left��Range[0, 1.0]

    MVFG_COLORF     stColor;        ///<  \~chinese ��������ɫ                      \~english Color of Auxiliary Line
    unsigned int    nLineWidth;     ///<  \~chinese �����߿�ȣ����ֻ����1��2      \~english Width of Auxiliary Line, width is 1 or 2
    unsigned int    nReserved[4];   ///<  \~chinese Ԥ��                            \~english Reserved

}MVFG_RECT_INFO;

/// \~chinese Բ�ο�������Ϣ            \~english Circle Area Info
typedef struct _MVFG_CIRCLE_INFO
{
    MVFG_POINTF     stCenterPoint;  ///<  \~chinese Բ����Ϣ                        \~english Circle Point Info

    float           fR1;            ///<  \~chinese ����뾶������ͼ������λ��[0, 1.0]���뾶��Բ�ĵ�λ���йأ��豣֤������Բ����ʾ��Χ֮�ڣ����򱨴�  \~english Windth Radius, Range[0, 1.0]
    float           fR2;            ///<  \~chinese ����뾶������ͼ������λ��[0, 1.0]���뾶��Բ�ĵ�λ���йأ��豣֤������Բ����ʾ��Χ֮�ڣ����򱨴�  \~english Height Radius, Range[0, 1.0]

    MVFG_COLORF     stColor;        ///<  \~chinese ��������ɫ��Ϣ                  \~english Color of Auxiliary Line
    unsigned int    nLineWidth;     ///<  \~chinese �����߿�ȣ����ֻ����1��2      \~english Width of Auxiliary Line, width is 1 or 2
    unsigned int    nReserved[4];   ///<  \~chinese Ԥ��                            \~english Reserved

}MVFG_CIRCLE_INFO;

/// \~chinese ������������Ϣ    \~english Linear Auxiliary Line Info
typedef struct _MVFG_LINES_INFO
{
    MVFG_POINTF     stStartPoint;   ///<  \~chinese ���������ߵ���ʼ������          \~english The Start Point of Auxiliary Line
    MVFG_POINTF     stEndPoint;     ///<  \~chinese ���������ߵ��յ�����            \~english The End Point of Auxiliary Line
    MVFG_COLORF     stColor;        ///<  \~chinese ��������ɫ��Ϣ                  \~english Color of Auxiliary Line
    unsigned int    nLineWidth;     ///<  \~chinese �����߿�ȣ����ֻ����1��2      \~english Width of Auxiliary Line, width is 1 or 2
    unsigned int    nReserved[4];   ///<  \~chinese Ԥ��                            \~english Reserved

}MVFG_LINES_INFO;

/// \~chinese ȡ������                  \~english The strategy of Grabbing
typedef enum _MV_FG_GRAB_STRATEGY_
{
    MV_FG_GrabStrategy_OneByOne            = 0,                        ///< \~chinese �Ӿɵ���һ֡һ֡�Ļ�ȡͼ��   \~english Grab One By One
    MV_FG_GrabStrategy_LatestImagesOnly    = 1,                        ///< \~chinese ��ȡ�б������µ�һ֡ͼ��     \~english Grab The Latest Image
    MV_FG_GrabStrategy_LatestImages        = 2,                        ///< \~chinese ��ȡ�б������µ�ͼ��         \~english Grab The Latest Images
    MV_FG_GrabStrategy_UpcomingImage       = 3,                        ///< \~chinese �ȴ���һ֡ͼ��               \~english Grab The Upcoming Image

}MV_FG_GRAB_STRATEGY;

/// \~chinese ֡������Ϣ�ص�����         \~english Frame buffer information callback function
typedef void(__stdcall *MV_FG_FrameCallBack)(MV_FG_BUFFER_INFO* pstBufferInfo, void* pUser);

/// \~chinese �쳣��Ϣ�ص�����          \~english Exception information callback function
typedef void(__stdcall *MV_FG_ExceptionCallBack)(MV_FG_EXCEPTION_TYPE enExceptionType, void* pUser);

/// \~chinese �¼��ص�����            \~english Event callback function
typedef void(__stdcall *MV_FG_EventCallBack)(MV_FG_EVENT_INFO* pstEventInfo, void* pUser);

#ifdef __cplusplus
}
#endif 

#endif //_MV_FG_DEFINES_H_
