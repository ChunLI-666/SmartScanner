/* 
ch：该示例程序展示如何注册外部缓存，并使用外部缓存，通过MV_FG_GetImageBuffer()采集图像。使用外部缓存的方式，可以减少数据拷贝次数。

en: This sample program shows how to register the external buffer and use the external buffer with the API MV_FG_GetImageBuffer() to acquire images. Using external buffer can reduce the number of times to copy data.
*/

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include "MVFGControl.h"

#define BUFFER_NUMBER       3       // ch:申请的缓存个数 | en:Number of requested buffer
#define FILE_NAME_LEN       256     // ch:最大文件名长度 | en:Max of file name length
#define SAVE_IMAGE_NUM      10      // ch:最大存储图像数量 | en:Max number of stored images
#define TIMEOUT             1000    // ch:超时时间，单位毫秒 | en:Timeout, unit ms

bool g_bExit = false;               // ch:停止取流 | en:Stop grabbing

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

// ch:保存图像原始数据 | en:Save original image data
void SaveRawImage(int nImageNo, MV_FG_BUFFER_INFO* pstImageInfo)
{
    if (pstImageInfo)
    {
        char szFileName[FILE_NAME_LEN] = { 0 };

        sprintf(szFileName, "Image_w%d_h%d_n%d.raw", pstImageInfo->nWidth, pstImageInfo->nHeight, nImageNo);

        FILE* pImageFile = NULL;
        if (NULL == (pImageFile = fopen(szFileName, "wb")))
        {
            return;
        }

        fwrite(pstImageInfo->pBuffer, 1, pstImageInfo->nFilledSize, pImageFile);
        fclose(pImageFile);
    }
}

// ch:取流线程 | en:Grabbing image data thread
static void* GrabbingThread(void* pUser)
{
    if (pUser)
    {
        STREAMHANDLE        hStream = (STREAMHANDLE)pUser;
        BUFFERHANDLE        hBuffer = NULL;
        MV_FG_BUFFER_INFO   stFrameInfo = { 0 };    // 图像信息
        int                 nSaveImage = 0;         // 保存的图像数量
        int                 nRet = 0;

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
            // ch:获取图像缓存 | en:Get image buffer
            nRet = MV_FG_GetImageBuffer(hStream, &hBuffer, TIMEOUT);
            if (MV_FG_SUCCESS != nRet)
            {
                printf("Get image buffer failed! %#x\n", nRet);
                continue;
            }

            // ch:获取图像信息和数据 | en:Get image info and data
            nRet = MV_FG_GetBufferInfo(hBuffer, &stFrameInfo);
            if (MV_FG_SUCCESS != nRet)
            {
                printf("Get image info failed! %#x\n", nRet);
            }
            else
            {
                printf("FrameNumber:%ld, Width:%d, Height:%d\n", stFrameInfo.nFrameID, stFrameInfo.nWidth, stFrameInfo.nHeight);
                
                if ((NULL != stFrameInfo.pBuffer) && (0 < stFrameInfo.nFilledSize) && (SAVE_IMAGE_NUM > nSaveImage))
                {
                    SaveRawImage(++nSaveImage, &stFrameInfo);
                }
            }

            // ch:将缓存放回输入队列 | en:Put the buffer back into the input queue
            nRet = MV_FG_QueueBuffer(hBuffer);
            if (MV_FG_SUCCESS != nRet)
            {
                printf("Queue buffer failed! %#x\n", nRet);
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
    BUFFERHANDLE    hBuffer[BUFFER_NUMBER] = { 0 };
    void*           pBuffer[BUFFER_NUMBER] = { 0 };

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

        // ch:打开采集卡，获得采集卡句柄 | en:Open interface, get handle
        nRet = MV_FG_OpenInterface((unsigned int)nInterfaceIndex, &hInterface);
        if (MV_FG_SUCCESS != nRet)
        {
            printf("Open No.%d interface failed! %#x\n", nInterfaceIndex, nRet);
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

        // ch:获取流通道图像大小 | en:Get payload size of stream
        unsigned int nPayloadSize = 0;
        nRet = MV_FG_GetPayloadSize(hStream, &nPayloadSize);
        if (MV_FG_SUCCESS != nRet)
        {
            printf("Get payload size failed! %#x\n", nRet);
            break;
        }

        // ch:注册缓存 | en:Announce buffer
        for (unsigned int i = 0; i < BUFFER_NUMBER; i++)
        {
            // ch:分配图像缓存 | en:Allocate image memory
            pBuffer[i] = malloc(nPayloadSize);
            if (NULL == pBuffer[i])
            {
                printf("Allocate buffer failed!\n");
                nRet = MV_FG_ERR_OUT_OF_MEMORY;
                break;
            }

            // ch:向SDK注册缓存 | en:Announce buffer for SDK
            nRet = MV_FG_AnnounceBuffer(hStream, pBuffer[i], nPayloadSize, NULL, &(hBuffer[i]));
            if (MV_FG_SUCCESS != nRet)
            {
                printf("Announce buffer failed! %#x\n", nRet);
                break;
            }
        }
        if (MV_FG_SUCCESS != nRet)
        {
            break;
        }

        // ch:刷新缓存队列，用于取流 | en:Flush buffer for grabbing image
        nRet = MV_FG_FlushQueue(hStream, MV_FG_BUFFER_QUEUE_ALL_TO_INPUT);
        if (MV_FG_SUCCESS != nRet)
        {
            printf("Flush queue: all to input failed! %#x\n", nRet);
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

    // ch:释放资源 | en:Release resource
    if (NULL != hStream)
    {
        // ch:清空缓存队列 | en:Flush buffer queue
        nRet = MV_FG_FlushQueue(hStream, MV_FG_BUFFER_QUEUE_ALL_DISCARD);
        if (MV_FG_SUCCESS != nRet)
        {
            printf("Flush buffer queue failed! %#x\n", nRet);
        }

        // ch:撤销并释放注册的缓存 | en:Revoke and release buffer
        for (unsigned int i = 0; i < BUFFER_NUMBER; i++)
        {
            if (NULL != hBuffer[i])
            {
                nRet = MV_FG_RevokeBuffer(hStream, hBuffer[i], NULL, NULL);
                if (MV_FG_SUCCESS != nRet)
                {
                    printf("Revoke No.%d buffer failed! %#x\n", i, nRet);
                }
                hBuffer[i] = NULL;
            }

            if (NULL != pBuffer[i])
            {
                free(pBuffer[i]);
                pBuffer[i] = NULL;
            }
        }

        // ch:关闭流通道 | en:Close stream
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