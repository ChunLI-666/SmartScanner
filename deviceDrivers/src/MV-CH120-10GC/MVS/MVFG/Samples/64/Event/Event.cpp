/* 
ch：该示例程序展示如何使用MV_FG_RegisterEventCallBack（）接口获取采集卡接收到图像的（ReceiveImageFrameStart0）事件信息。

en: This sample program shows how to use the API MV_FG_RegisterEventCallBack() to get the (ReceiveImageFrameStart0) event information of the image received by the frame grabber.
*/
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include "MVFGControl.h"

#define BUFFER_NUMBER       3       // ch:申请的缓存个数 | en:Number of requested buffer
#define TIMEOUT             1000    // ch:超时时间，单位毫秒 | en:Timeout, unit ms
bool g_bExit = false;               // ch:停止取流 | en:Stop grabbing

void EventCallBack(MV_FG_EVENT_INFO* pstEventInfo, void* pUser)
{
    static int nEventNum = 0;

    nEventNum++;

    if (NULL != pstEventInfo)
    {
        printf("%d Event: name %s  id 0x%x time %lld \r\n", nEventNum, pstEventInfo->EventName, pstEventInfo->nEventID, pstEventInfo->nTimestamp);
    }
}

// 等待用户输入enter键来结束取流或结束程序
// wait for user to input enter to stop grabbing or end the sample program
void PressEnterToExit(void)
{
    int c;
    while ( (c = getchar()) != '\n' && c != EOF );
    fprintf( stderr, "\nPress enter to exit.\n");
    while( getchar() != '\n');
    sleep(1);
}

// ch:取流线程 | en:Grabbing image data thread
static void* GrabbingThread(void* pUser)
{
    if (pUser)
    {
        STREAMHANDLE        hStream = (STREAMHANDLE)pUser;
        MV_FG_BUFFER_INFO   stFrameInfo = { 0 };    // 图像信息
        int                 nRet = 0;
        int                 nSaveNum = 0;

        // ch:开始取流 | en:Start Acquisition
        nRet = MV_FG_StartAcquisition(hStream);
        if (MV_FG_SUCCESS != nRet)
        {
            printf("Start acquistion failed! %#x\n", nRet);
            return NULL;
        }
        g_bExit = false;

        while (!g_bExit)
        {
            // ch:获取一帧图像缓存信息 | en:Get one frame buffer's info
            nRet = MV_FG_GetFrameBuffer(hStream, &stFrameInfo, TIMEOUT);
            if (MV_FG_SUCCESS != nRet)
            {
                printf("Get frame buffer info failed! %#x\n", nRet);
                continue;
            }
            else
            {
                printf("FrameNumber:%ld, Width:%d, Height:%d\n", stFrameInfo.nFrameID, stFrameInfo.nWidth, stFrameInfo.nHeight);
            }

            // ch:将缓存放回输入队列 | en:Put the buffer back into the input queue
            nRet = MV_FG_ReleaseFrameBuffer(hStream, &stFrameInfo);
            if (MV_FG_SUCCESS != nRet)
            {
                printf("Release frame buffer failed! %#x\n", nRet);
                break;
            }
        }

        // ch:停止取流 | en:Stop Acquisition
        nRet = MV_FG_StopAcquisition(hStream);
        if (MV_FG_SUCCESS != nRet)
        {
            printf("Stop acquisition failed! %#x\n", nRet);
            return NULL;
        }

    }
	
	return 0;
}

// ch:打印采集卡信息 | en:Print interface info
bool PrintInterfaceInfo(unsigned int nInterfaceNum)
{
    int nRet = 0;

    for (unsigned int i = 0; i < nInterfaceNum; i++)
    {
        MV_FG_INTERFACE_INFO stInterfaceInfo = { 0 };

        nRet = MV_FG_GetInterfaceInfo(i, &stInterfaceInfo);
        if (MV_FG_SUCCESS != nRet)
        {
            printf("Get info of No.%d interface failed! %#x\n", i, nRet);
            return false;
        }

        switch (stInterfaceInfo.nTLayerType)
        {
        case MV_FG_CXP_INTERFACE:
            {
                printf("[CXP]No.%d Interface: \n\tDisplayName: %s\n\tInterfaceID: %s\n\tSerialNumber:%s\n", i, 
                    stInterfaceInfo.IfaceInfo.stCXPIfaceInfo.chDisplayName, 
                    stInterfaceInfo.IfaceInfo.stCXPIfaceInfo.chInterfaceID, 
                    stInterfaceInfo.IfaceInfo.stCXPIfaceInfo.chSerialNumber);
                break;
            }
        case MV_FG_GEV_INTERFACE:
            {
                printf("[GEV]No.%d Interface: \n\tDisplayName: %s\n\tInterfaceID: %s\n\tSerialNumber:%s\n", i, 
                    stInterfaceInfo.IfaceInfo.stGEVIfaceInfo.chDisplayName, 
                    stInterfaceInfo.IfaceInfo.stGEVIfaceInfo.chInterfaceID, 
                    stInterfaceInfo.IfaceInfo.stGEVIfaceInfo.chSerialNumber);
                break;
            }
        case MV_FG_CAMERALINK_INTERFACE:
            {
                printf("[CML]No.%d Interface: \n\tDisplayName: %s\n\tInterfaceID: %s\n\tSerialNumber:%s\n", i, 
                    stInterfaceInfo.IfaceInfo.stCMLIfaceInfo.chDisplayName, 
                    stInterfaceInfo.IfaceInfo.stCMLIfaceInfo.chInterfaceID, 
                    stInterfaceInfo.IfaceInfo.stCMLIfaceInfo.chSerialNumber);
                break;
            }
        case MV_FG_XoF_INTERFACE:
            {
                printf("[XoF]No.%d Interface: \n\tDisplayName: %s\n\tInterfaceID: %s\n\tSerialNumber:%s\n", i, 
                    stInterfaceInfo.IfaceInfo.stXoFIfaceInfo.chDisplayName, 
                    stInterfaceInfo.IfaceInfo.stXoFIfaceInfo.chInterfaceID, 
                    stInterfaceInfo.IfaceInfo.stXoFIfaceInfo.chSerialNumber);
                break;
            }            
        default:
            {
                printf("Unknown interface type.\n");
                return false;
            }
        }
    }

    return true;
}

// ch:打印设备信息 | en:Print device info
bool PrintDeviceInfo(IFHANDLE hInterface, unsigned int nDeviceNum)
{
    int nRet = 0;

    for (unsigned int i = 0; i < nDeviceNum; i++)
    {
        MV_FG_DEVICE_INFO stDeviceInfo = { 0 };

        nRet = MV_FG_GetDeviceInfo(hInterface, i, &stDeviceInfo);
        if (MV_FG_SUCCESS != nRet)
        {
            printf("Get info of No.%d device failed! %#x\n", i, nRet);
            return false;
        }

        switch (stDeviceInfo.nDevType)
        {
        case MV_FG_CXP_DEVICE:
            {
                printf("[CXP]No.%d Device: \n\tUserDefinedName: %s\n\tModelName: %s\n\tSerialNumber: %s\n", i, 
                    stDeviceInfo.DevInfo.stCXPDevInfo.chUserDefinedName,
                    stDeviceInfo.DevInfo.stCXPDevInfo.chModelName,
                    stDeviceInfo.DevInfo.stCXPDevInfo.chSerialNumber);
                break;
            }
        case MV_FG_GEV_DEVICE:
            {
                printf("[GEV]No.%d Device: \n\tUserDefinedName: %s\n\tModelName: %s\n\tSerialNumber: %s\n", i, 
                    stDeviceInfo.DevInfo.stGEVDevInfo.chUserDefinedName,
                    stDeviceInfo.DevInfo.stGEVDevInfo.chModelName,
                    stDeviceInfo.DevInfo.stGEVDevInfo.chSerialNumber);
                break;
            }
        case MV_FG_CAMERALINK_DEVICE:
            {
                printf("[CML]No.%d Device: \n\tUserDefinedName: %s\n\tModelName: %s\n\tSerialNumber: %s\n", i, 
                    stDeviceInfo.DevInfo.stCMLDevInfo.chUserDefinedName,
                    stDeviceInfo.DevInfo.stCMLDevInfo.chModelName,
                    stDeviceInfo.DevInfo.stCMLDevInfo.chSerialNumber);
                break;
            }
        case MV_FG_XoF_DEVICE:
            {
                printf("[XoF]No.%d Device: \n\tUserDefinedName: %s\n\tModelName: %s\n\tSerialNumber: %s\n", i, 
                    stDeviceInfo.DevInfo.stXoFDevInfo.chUserDefinedName,
                    stDeviceInfo.DevInfo.stXoFDevInfo.chModelName,
                    stDeviceInfo.DevInfo.stXoFDevInfo.chSerialNumber);
                break;                    
            }
        default:
            {
                printf("Unknown device type.\n");
                return false;
            }
        }
    }

    return true;
}

int main()
{
    int             nRet = 0;
    IFHANDLE        hInterface = NULL;
    DEVHANDLE       hDevice = NULL;
    STREAMHANDLE    hStream = NULL;

    do
    {
        // ch:枚举采集卡 | en:Enum interface
        bool bChanged = false;
        nRet = MV_FG_UpdateInterfaceList(MV_FG_CXP_INTERFACE | MV_FG_GEV_INTERFACE | MV_FG_CAMERALINK_INTERFACE | MV_FG_XoF_INTERFACE, &bChanged);
        if (MV_FG_SUCCESS != nRet)
        {
            printf("Update interface list failed! %#x\n", nRet);
            break;
        }

        // ch:获取采集卡数量 | en:Get interface num
        unsigned int nInterfaceNum = 0;
        nRet = MV_FG_GetNumInterfaces(&nInterfaceNum);
        if (MV_FG_SUCCESS != nRet || 0 == nInterfaceNum)
        {
            printf("No interface found! return = %d, number = %d\n", nRet, nInterfaceNum);
            break;
        }

        // ch:显示采集卡信息 | en:Show interface info
        if (false == PrintInterfaceInfo(nInterfaceNum))
        {
            break;
        }

        // ch:选择采集卡 | en:Select interface
        int nInterfaceIndex = -1;
        printf("Select an interface: ");
        scanf("%d", &nInterfaceIndex);

        if (nInterfaceIndex < 0 || nInterfaceIndex >= (int)nInterfaceNum)
        {
            printf("Invalid interface index.\nQuit.\n");
            break;
        }

        // ch:以指定权限打开采集卡，获得采集卡句柄 | en:Open interface with specified permissions, get handle
        nRet = MV_FG_OpenInterface((unsigned int)nInterfaceIndex, &hInterface);
        if (MV_FG_SUCCESS != nRet)
        {
            printf("Open No.%d interface failed! %#x\n", nInterfaceIndex, nRet);
            break;
        }

        // 注册采集卡帧开始事件回调
        nRet = MV_FG_RegisterEventCallBack(hInterface, "ReceiveImageFrameStart0", EventCallBack, NULL);
        if (MV_FG_SUCCESS != nRet)
        {
            printf("MV_FG_RegisterEventCallBack event %s error, %#x\n", "ReceiveImageFrameStart0", nRet);
            break;
        }

        // 设置事件类型为流事件(可自行设置EventCategory相机节点下的其他事件类型)
        nRet = MV_FG_SetEnumValueByString(hInterface, "EventCategory", "StreamEvent");
        if (MV_FG_SUCCESS != nRet)
        {
            printf("MV_FG_SetEnumValueByString EventCategory %s error, %#x\n", "StreamEvent", nRet);
            break;
        }

        // 设置事件通道(Channel0-Channel3)
        nRet = MV_FG_SetEnumValueByString(hInterface, "ChannelSelector", "Channel0");
        if (MV_FG_SUCCESS != nRet)
        {
            printf("MV_FG_SetEnumValueByString ChannelSelector %s error, %#x\n", "Channel0", nRet);
            break;
        }

        // 设置具体事件(可自行设置EventSelector相机节点下的其他具体事件)
        nRet = MV_FG_SetEnumValueByString(hInterface, "EventSelector", "ReceiveImageFrameStart0");
        if (MV_FG_SUCCESS != nRet)
        {
            printf("MV_FG_SetEnumValueByString EventSelector %s error, %#x\n", "ReceiveImageFrameStart0", nRet);
            break;
        }

        // 打开事件通知
        nRet = MV_FG_SetEnumValueByString(hInterface, "EventNotification", "On");
        if (MV_FG_SUCCESS != nRet)
        {
            printf("MV_FG_SetEnumValueByString EventNotification %s error, %#x\n", "On", nRet);
            break;
        }

        // ch:枚举采集卡上的相机 | en:Enum camera of interface
        nRet = MV_FG_UpdateDeviceList(hInterface, &bChanged);
        if (MV_FG_SUCCESS != nRet)
        {
            printf("Update device list failed! %#x\n", nRet);
            break;
        }

        // ch:获取设备数量 | en:Get device number
        unsigned int nDeviceNum = 0;
        nRet = MV_FG_GetNumDevices(hInterface, &nDeviceNum);
        if (MV_FG_SUCCESS != nRet || 0 == nDeviceNum)
        {
            printf("No device found! return = %d, number = %d\n", nRet, nDeviceNum);
            break;
        }

        // ch:显示设备信息 | en:Show device info
        if (false == PrintDeviceInfo(hInterface, nDeviceNum))
        {
            break;
        }

        // ch:选择设备 | en:Select device
        int nDeviceIndex = -1;
        printf("Select a device: ");
        scanf("%d", &nDeviceIndex);

        if (nDeviceIndex < 0 || nDeviceIndex >= (int)nDeviceNum)
        {
            printf("Invalid device index.\nQuit.\n");
            break;
        }

        // ch:打开设备，获得设备句柄 | en:Open device, get handle
        nRet = MV_FG_OpenDevice(hInterface, (unsigned int)nDeviceIndex, &hDevice);
        if (MV_FG_SUCCESS != nRet)
        {
            printf("Open No.%d device failed! %#x\n", nDeviceIndex, nRet);
            hDevice = NULL;
            break;
        }

        // ch:关闭触发模式 | en:Close trigger mode
        nRet = MV_FG_SetEnumValueByString(hDevice, "TriggerMode", "Off");
        if (MV_FG_SUCCESS != nRet)
        {
            printf("Turn off trigger mode failed! %#x\n", nRet);
            break;
        }

        // ch:获取流通道个数 | en:Get number of stream
        unsigned int nStreamNum = 0;
        nRet = MV_FG_GetNumStreams(hDevice, &nStreamNum);
        if (MV_FG_SUCCESS != nRet || 0 == nStreamNum)
        {
            printf("No stream available! return = %d, number = %d\n", nRet, nStreamNum);
            break;
        }

        // ch:打开流通道(目前只支持单个通道) | en:Open stream(Only a single stream is supported now)
        nRet = MV_FG_OpenStream(hDevice, 0, &hStream);
        if (MV_FG_SUCCESS != nRet)
        {
            printf("Open stream failed! %#x\n", nRet);
            break;
        }

        // ch:设置SDK内部缓存数量 | en:Set internal buffer number
        nRet = MV_FG_SetBufferNum(hStream, BUFFER_NUMBER);
        if (MV_FG_SUCCESS != nRet)
        {
            printf("Set buffer number failed! %#x\n", nRet);
            break;
        }

        // ch:创建取流线程 | en:Create acquistion thread
		pthread_t nThreadID;
        nRet = pthread_create(&nThreadID, NULL ,GrabbingThread, hStream);
        if (nRet != 0)
        {
            printf("thread create failed.ret = %d\n",nRet);
            break;
        }

        printf("Press Enter to stop acquisition.\n");
        PressEnterToExit();

        // ch:关闭取流线程 | en:Close acquistion thread
        g_bExit = true;

        // ch:等待取流线程结束 | en:Join acquistion thread
        nRet = pthread_join(nThreadID, NULL);
        if (nRet != 0)
        {
            printf("thread join failed.ret = %d\n",nRet);
            break;
        }
    } while (0);

    // ch:关闭流通道 | en:Close Stream
    if (NULL != hStream)
    {
        nRet = MV_FG_CloseStream(hStream);
        if (MV_FG_SUCCESS != nRet)
        {
            printf("Close stream failed! %#x\n", nRet);
        }
        hStream = NULL;
    }

    // ch:关闭设备 | en:Close device
    if (NULL != hDevice)
    {
        nRet = MV_FG_CloseDevice(hDevice);
        if (MV_FG_SUCCESS != nRet)
        {
            printf("Close device failed! %#x\n", nRet);
        }
        hDevice = NULL;
    }

    // ch:关闭采集卡 | en:Close interface
    if (NULL != hInterface)
    {
        nRet = MV_FG_CloseInterface(hInterface);
        if (MV_FG_SUCCESS != nRet)
        {
            printf("Close interface failed! %#x\n", nRet);
        }
        hInterface = NULL;
    }

    return 0;
}