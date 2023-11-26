#ifndef _MV_FG_CTRL_H_
#define _MV_FG_CTRL_H_

#include "MVFGDefines.h"
#include "MVFGErrorDefine.h"

/************************************************************************/
/* ��̬�⵼�뵼������                                                   */
/* Import and export definition of the dynamic library                  */
/************************************************************************/
#ifndef MV_FGCTRL_API
    #if (defined (_WIN32) || defined(WIN64))
        #if defined(MV_FGCTRL_EXPORTS)
            #define MV_FGCTRL_API __declspec(dllexport)
        #else
            #define MV_FGCTRL_API __declspec(dllimport)
        #endif
    #else
        #ifndef __stdcall
            #define __stdcall
        #endif 

        #ifndef MV_FGCTRL_API
            #if defined(MV_FGCTRL_ROC_EXPORTS)
                #define  MV_FGCTRL_API __attribute__((visibility("default")))
            #else
                #define  MV_FGCTRL_API
            #endif
        #endif
    #endif
#endif

#ifndef IN
    #define IN
#endif

#ifndef OUT
    #define OUT
#endif

#ifdef __cplusplus
extern "C" {
#endif 

/***********************************************************************/
/*                             �汾��Ϣ                                */
/*                        Version information                          */
/***********************************************************************/
/********************************************************************//**
 *  @~chinese
 *  @brief  ��ȡSDK�汾��Ϣ
 *  @return ���ַ�����ʽ����SDK�汾��Ϣ
 *  @remarks ��ʽ�����汾 + ���� + ����ʱ�䡱
  
 *  @~english
 *  @brief  Get SDK Version Information
 *  @return Return SDK version information in a string.
 *  @remarks Format: "Version number + Type + Compile Time".
 ************************************************************************/
MV_FGCTRL_API unsigned char* __stdcall MV_FG_GetSDKVersion();


/***********************************************************************/
/*                             ��������                                */
/*                         Basic operation                             */
/***********************************************************************/
/********************************************************************//**
 *  @~chinese
 *  @brief  ��ʼ��SDK��Դ
 *  @return �ɹ�������MV_FG_SUCCESS��ʧ�ܷ��ش�����
 *  @remarks �����ڵ��������ӿ�֮ǰ���ã���ʼ��SDK��Դ�� \n
 *  @~english
 *  @brief  Initialize SDK resources 
 *  @return Return MV_FG_SUCCESS on success, and return Error Code on failure.
 *  @remarks It can be called before calling other functions to initialize SDK resources.
 ************************************************************************/
MV_FGCTRL_API int __stdcall MV_FG_Initialize();

/********************************************************************//**
 *  @~chinese
 *  @brief  ����SDK���ã�������Դ
 *  @return �ɹ�������MV_FG_SUCCESS��ʧ�ܷ��ش�����
 *  @remarks �ýӿڵ��ú�SDK���ͷ������������Դ�����Ҫ����ʹ��SDK�ӿڣ���Ҫ�ȵ���MV_FG_Initialize��������ö�ٲɼ����� \n
 *  @~english
 *  @brief  End the SDK call and destroy the resource
 *  @return Return MV_FG_SUCCESS on success, and return Error Code on failure.
 *  @remarks It can be called before calling other functions to initialize SDK resources.
 ************************************************************************/
MV_FGCTRL_API int __stdcall MV_FG_Finalize();

/********************************************************************//**
 *  @~chinese
 *  @brief  ���²ɼ����б�
 *  @param  nTLayerType             [IN]           �ɼ�������
 *  @param  pbChanged               [OUT]          �ɼ����б��Ƿ�ı�
 *  @return �ɹ�������MV_FG_SUCCESS��ʧ�ܷ��ش�����
 *  @remarks ���вɼ�������֮ǰ������øýӿڣ�ֻ���ڵ��øýӿ�ʱ�ڲ��ɼ����б�Ż���¡� \n
             �ɼ�������˵�����£�\n
                | ��� | �ɼ������Ͷ��� | ֵ | ˵�� |
                | :---:| :---:| :---:| :---:|
                | 1 | MV_FG_GEV_INTERFACE | 0x00000001 | GigE Vision�ɼ��� |
                | 2 | MV_FG_CAMERALINK_INTERFACE | 0x00000004 | Camera Link�ɼ��� |
                | 3 | MV_FG_CXP_INTERFACE | 0x00000008 | CoaXPress�ɼ��� |
                | 4 | MV_FG_XoF_INTERFACE | 0x00000010 | XoFLink�ɼ��� |
 *  @~english
 *  @brief  Update frame grabber list
 *  @param  nTLayerType             [IN]            Frame grabber type
 *  @param  pbChanged               [OUT]           Whether the frame grabber list changed
 *  @return Return MV_FG_SUCCESS on success, and return Error Code on failure.
 *  @remarks This API must be called before the operation of the frame grabber. The internal frame grabber list will be updated only when this API is called. \n
             TLayerType description: \n
                | No. | TLayerType Definition | Value | explain |
                | :---:| :---:| :---:| :---:|
                | 1 | MV_FG_GEV_INTERFACE | 0x00000001 | GigE Vision interface |
                | 2 | MV_FG_CAMERALINK_INTERFACE | 0x00000004 | Camera Link interface |
                | 3 | MV_FG_CXP_INTERFACE | 0x00000008 | CoaXPress interface |
                | 4 | MV_FG_XoF_INTERFACE | 0x00000010 | XoFLink interface |
 ************************************************************************/
MV_FGCTRL_API int __stdcall MV_FG_UpdateInterfaceList(IN unsigned int nTLayerType, OUT bool8_t *pbChanged);

/********************************************************************//**
 *  @~chinese
 *  @brief  �ͷ�ָ�����͵Ĳɼ�����Դ
 *  @param  nTLayerType             [IN]           �ɼ�������
 *  @return �ɹ�������MV_FG_SUCCESS��ʧ�ܷ��ش�����
 *  @remarks ���øýӿ�֮ǰ����ر����и����͵Ĳɼ�����ͨ��FreeLibrary�����ͷŸÿ�ǰ��Ҫ���øýӿ��ͷ����вɼ�����Դ
             �ɼ�������˵�����£�\n
                | ��� | �ɼ������Ͷ��� | ֵ | ˵�� |
                | :---:| :---:| :---:| :---:|
                | 1 | MV_FG_GEV_INTERFACE | 0x00000001 | GigE Vision�ɼ��� |
                | 2 | MV_FG_CAMERALINK_INTERFACE | 0x00000004 | Camera Link�ɼ��� |
                | 3 | MV_FG_CXP_INTERFACE | 0x00000008 | CoaXPress�ɼ��� |
                | 4 | MV_FG_XoF_INTERFACE | 0x00000010 | XoFLink�ɼ��� |
  
 *  @~english
 *  @brief  Release frame grabber resources of specified types
 *  @param  nTLayerType             [IN]            Frame grabber type
 *  @return Return MV_FG_SUCCESS on success, and return Error Code on failure.
 *  @remarks All frame grabbers of the specified type should be disabled before calling this API. Before releasing the library libMVFGControl.so via function FreeLibrary, you need to call this API to release all frame grabber resources.
             TLayerType description: \n
                | No. | TLayerType Definition | Value | explain |
                | :---:| :---:| :---:| :---:|
                | 1 | MV_FG_GEV_INTERFACE | 0x00000001 | GigE Vision interface |
                | 2 | MV_FG_CAMERALINK_INTERFACE | 0x00000004 | Camera Link interface |
                | 3 | MV_FG_CXP_INTERFACE | 0x00000008 | CoaXPress interface |
                | 4 | MV_FG_XoF_INTERFACE | 0x00000010 | XoFLink interface |
 ************************************************************************/
MV_FGCTRL_API int __stdcall MV_FG_ReleaseTLayerResource(IN unsigned int nTLayerType);

/********************************************************************//**
 *  @~chinese
 *  @brief  ��ȡ�ɼ�������
 *  @param  pnNumIfaces             [OUT]          �ɼ�������
 *  @return �ɹ�������MV_FG_SUCCESS��ʧ�ܷ��ش�����
  
 *  @~english
 *  @brief  Get the number of frame grabbers
 *  @param  pnNumIfaces             [OUT]           Number of frame grabbers.
 *  @return Return MV_FG_SUCCESS on success, and return Error Code on failure.
 ************************************************************************/
MV_FGCTRL_API int __stdcall MV_FG_GetNumInterfaces(OUT unsigned int *pnNumIfaces);

/********************************************************************//**
 *  @~chinese
 *  @brief  ����������ȡ�ɼ�����Ϣ
 *  @param  nIndex                  [IN]           �ɼ�����������0��ʼ
 *  @param  pstIfaceInfo            [OUT]          �ɼ�����Ϣ
 *  @return �ɹ�������MV_FG_SUCCESS��ʧ�ܷ��ش�����
  
 *  @~english
 *  @brief  Get the frame grabber information via frame grabber index
 *  @param  nIndex                  [IN]            Frame grabber index, which starts from 0
 *  @param  pstIfaceInfo            [OUT]           Frame grabber information
 *  @return Return MV_FG_SUCCESS on success, and return Error Code on failure.
 ************************************************************************/
MV_FGCTRL_API int __stdcall MV_FG_GetInterfaceInfo(IN unsigned int nIndex, OUT MV_FG_INTERFACE_INFO *pstIfaceInfo);

/********************************************************************//**
 *  @~chinese
 *  @brief  �򿪲ɼ���
 *  @param  nIndex                  [IN]           �ɼ�����������0��ʼ
 *  @param  phIface                 [OUT]          �ɼ������
 *  @return �ɹ�������MV_FG_SUCCESS��ʧ�ܷ��ش�����
  
 *  @~english
 *  @brief  Open the frame grabber
 *  @param  nIndex                  [IN]            Frame grabber index, which starts from 0
 *  @param  phIface                 [OUT]           Frame grabber handle
 *  @return Return MV_FG_SUCCESS on success, and return Error Code on failure.
 ************************************************************************/
MV_FGCTRL_API int __stdcall MV_FG_OpenInterface(IN unsigned int nIndex, OUT IFHANDLE* phIface);

/********************************************************************//**
 *  @~chinese
 *  @brief  �򿪲ɼ�������ָ��Ȩ��
 *  @param  nIndex                  [IN]           �ɼ�����������0��ʼ
 *  @param  nAccess                 [IN]           Ȩ��
 *  @param  phIface                 [OUT]          �ɼ������
 *  @return �ɹ�������MV_FG_SUCCESS��ʧ�ܷ��ش�����
 *  @remarks nAccessȨ��˵�����£�\n��
                | ��� | Ȩ�����Ͷ��� | ֵ | ˵�� |
                | :---:| :---:| :---:| :---:|
                | 1 | MV_FG_ACCESS_READONLY | 0x1 | ֻ��Ȩ�ޣ������Ի�ȡ�ڵ�ֵ|
                | 2 | MV_FG_ACCESS_CONTROL | 0x2 | ����Ȩ��
  
 *  @~english
 *  @brief  Open the frame grabber and specify its access mode
 *  @param  nIndex                  [IN]            Frame grabber index, which starts from 0
 *  @param  nAccess                 [IN]            Access mode
 *  @param  phIface                 [OUT]           Frame grabber handle
 *  @return Return MV_FG_SUCCESS on success, and return Error Code on failure.
 *  @remarks Access mode description: \n
                | No. | Access Definition | Value | explain |
                | :---:| :---:| :---:| :---:|
                | 1 | MV_FG_ACCESS_READONLY | 0x1 | Read only, Get node value only |
                | 2 | MV_FG_ACCESS_CONTROL | 0x2 | Control mode
 ************************************************************************/
MV_FGCTRL_API int __stdcall MV_FG_OpenInterfaceEx(IN unsigned int nIndex, IN int nAccess, OUT IFHANDLE* phIface);

/********************************************************************//**
 *  @~chinese
 *  @brief  ͨ���ɼ���ID�򿪲ɼ�������ָ��Ȩ��
 *  @param  pcInterfaceID           [IN]           �ɼ���ID
 *  @param  nAccess                 [IN]           Ȩ��
 *  @param  phIface                 [OUT]          �ɼ������
 *  @return �ɹ�������MV_FG_SUCCESS��ʧ�ܷ��ش�����
 *  @remarks nAccessȨ��˵�����£�\n��
                | ��� | Ȩ�����Ͷ��� | ֵ | ˵�� |
                | :---:| :---:| :---:| :---:|
                | 1 | MV_FG_ACCESS_READONLY | 0x1 | ֻ��Ȩ�� |
                | 2 | MV_FG_ACCESS_CONTROL | 0x2 | ����Ȩ��
  
 *  @~english
 *  @brief  Open the frame grabber with its ID and specify its access mode
 *  @param  pcInterfaceID           [IN]            Frame grabber ID
 *  @param  nAccess                 [IN]            Access mode
 *  @param  phIface                 [OUT]           Frame grabber handle
 *  @return Return MV_FG_SUCCESS on success, and return Error Code on failure.
 *  @remarks Access mode description: \n
                | No. | Access Definition | Value | explain |
                | :---:| :---:| :---:| :---:|
                | 1 | MV_FG_ACCESS_READONLY | 0x1 | Read only, Get node value only |
                | 2 | MV_FG_ACCESS_CONTROL | 0x2 | Control mode
 ************************************************************************/
MV_FGCTRL_API int __stdcall MV_FG_OpenInterfaceByID(IN char* pcInterfaceID, IN int nAccess, OUT IFHANDLE* phIface);

/********************************************************************//**
 *  @~chinese
 *  @brief  �򿪲ɼ��������������ļ��������ļ�����MV_FG_FeatureSave�ӿڣ�
 *  @param  nIndex                  [IN]           �ɼ�����������0��ʼ
 *  @param  pcConfigFile            [IN]           �����ļ�·�����û����ṩ��ΪNULLʱ����
 *  @param  phIface                 [OUT]          �ɼ������
 *  @return �ɹ�������MV_FG_SUCCESS��ʧ�ܷ��ش�����
 *  @remarks ʹ�ô˽ӿ����ṩ�����ļ����ɼ������Կ���Ȩ�޴򿪡�
  
 *  @~english
 *  @brief  Open the Interface with config file
 *  @param  nIndex                  [IN]            Interface index, starting from 0
 *  @param  pcConfigFile            [IN]            Config file path��users need to provide. An error was reported when it was NULL
 *  @param  phIface                 [OUT]           Interface handle
 *  @return Success, return MV_FG_SUCCESS. Failure, return error code 
 *  @remarks To use this interface, you need to provide a configuration file. The Interface will be opened with control permissions.
 ************************************************************************/
MV_FGCTRL_API int __stdcall MV_FG_OpenInterfaceWithConfig(IN unsigned int nIndex, IN char* pcConfigFile, OUT IFHANDLE* phIface);

/********************************************************************//**
 *  @~chinese
 *  @brief  �رղɼ���
 *  @param  hIface                  [IN]           �ɼ������
 *  @return �ɹ�������MV_FG_SUCCESS��ʧ�ܷ��ش�����
  
 *  @~english
 *  @brief  Close the frame grabber
 *  @param  hIface                  [IN]            Frame grabber handle
 *  @return Return MV_FG_SUCCESS on success, and return Error Code on failure.
 ************************************************************************/
MV_FGCTRL_API int __stdcall MV_FG_CloseInterface(IN IFHANDLE hIface);

/********************************************************************//**
 *  @~chinese
 *  @brief  ����ָ���ɼ����µ�����б�
 *  @param  hIface                  [IN]           �ɼ������
 *  @param  pbChanged               [OUT]          ����б��Ƿ�ı�
 *  @return �ɹ�������MV_FG_SUCCESS��ʧ�ܷ��ش�����
 *  @remarks ֻ���ڵ��øýӿ�ʱ�ڲ�����б�Ż���¡�
  
 *  @~english
 *  @brief  Update the device list of a specified frame grabber
 *  @param  hIface                  [IN]            Frame grabber handle
 *  @param  pbChanged               [OUT]           Whether the device list is updated
 *  @return Return MV_FG_SUCCESS on success, and return Error Code on failure.
 *  @remarks The internal device list is updated only when this API is called.
 ************************************************************************/
MV_FGCTRL_API int __stdcall MV_FG_UpdateDeviceList(IN IFHANDLE hIface, OUT bool8_t *pbChanged);

/********************************************************************//**
 *  @~chinese
 *  @brief  ��ȡ�������
 *  @param  hIface                  [IN]           �ɼ������
 *  @param  pnNumDevices            [OUT]          �������
 *  @return �ɹ�������MV_FG_SUCCESS��ʧ�ܷ��ش�����
  
 *  @~english
 *  @brief  Get the number of devices of a specified frame grabber.
 *  @param  hIface                  [IN]            Frame grabber handle
 *  @param  pnNumDevices            [OUT]           Number of devices
 *  @return Return MV_FG_SUCCESS on success, and return Error Code on failure.
 ************************************************************************/
MV_FGCTRL_API int __stdcall MV_FG_GetNumDevices(IN IFHANDLE hIface, OUT unsigned int *pnNumDevices);

/********************************************************************//**
 *  @~chinese
 *  @brief  ��ȡ�����Ϣ
 *  @param  hIface                  [IN]           �ɼ������
 *  @param  nIndex                  [IN]           �����������0��ʼ
 *  @param  pstDevInfo              [OUT]          �����Ϣ
 *  @return �ɹ�������MV_FG_SUCCESS��ʧ�ܷ��ش�����
  
 *  @~english
 *  @brief  Get the device information
 *  @param  hIface                  [IN]            Frame grabber handle
 *  @param  nIndex                  [IN]            Device index, which starts from 0
 *  @param  pstDevInfo              [OUT]           Device information
 *  @return Return MV_FG_SUCCESS on success, and return Error Code on failure.
 ************************************************************************/
MV_FGCTRL_API int __stdcall MV_FG_GetDeviceInfo(IN IFHANDLE hIface, IN unsigned int nIndex, OUT MV_FG_DEVICE_INFO *pstDevInfo);

/********************************************************************//**
 *  @~chinese
 *  @brief  �����
 *  @param  hIface                  [IN]           �ɼ������
 *  @param  nIndex                  [IN]           �����������0��ʼ
 *  @param  phDevice                [OUT]          ������
 *  @return �ɹ�������MV_FG_SUCCESS��ʧ�ܷ��ش�����
  
 *  @~english
 *  @brief  Open the device according to index
 *  @param  hIface                  [IN]            Frame grabber handle
 *  @param  nIndex                  [IN]            Device index, which starts from 0
 *  @param  phDevice                [OUT]           Device handle
 *  @return Return MV_FG_SUCCESS on success, and return Error Code on failure.
 ************************************************************************/
MV_FGCTRL_API int __stdcall MV_FG_OpenDevice(IN IFHANDLE hIface, IN unsigned int nIndex, OUT DEVHANDLE* phDevice);

/********************************************************************//**
 *  @~chinese
 *  @brief  �����
 *  @param  hIface                  [IN]           �ɼ������
 *  @param  pcDeviceID              [IN]           ���ID
 *  @param  phDevice                [OUT]          ������
 *  @return �ɹ�������MV_FG_SUCCESS��ʧ�ܷ��ش�����
  
 *  @~english
 *  @brief  Open the device according to ID
 *  @param  hIface                  [IN]            Frame grabber handle
 *  @param  pcDeviceID              [IN]            Device ID
 *  @param  phDevice                [OUT]           Device handle
 *  @return Return MV_FG_SUCCESS on success, and return Error Code on failure.
 ************************************************************************/
MV_FGCTRL_API int __stdcall MV_FG_OpenDeviceByID(IN IFHANDLE hIface, IN char* pcDeviceID, OUT DEVHANDLE* phDevice);

/********************************************************************//**
 *  @~chinese
 *  @brief  �ر����
 *  @param  hDevice                 [IN]           ������
 *  @return �ɹ�������MV_FG_SUCCESS��ʧ�ܷ��ش�����
  
 *  @~english
 *  @brief  Close the device
 *  @param  hDevice                 [IN]            Device handle
 *  @return Return MV_FG_SUCCESS on success, and return Error Code on failure.
 ************************************************************************/
MV_FGCTRL_API int __stdcall MV_FG_CloseDevice(IN DEVHANDLE hDevice);


/***********************************************************************/
/*                             ͼ��ɼ�                                */
/*                        Image acquisition                            */
/***********************************************************************/
/********************************************************************//**
 *  @~chinese
 *  @brief  ��ȡ��ͨ������
 *  @param  hDevice                 [IN]           ������
 *  @param  pnNumStreams            [OUT]          ��ͨ������
 *  @return �ɹ�������MV_FG_SUCCESS��ʧ�ܷ��ش�����
 *  @remarks Ŀǰһ�����ֻ֧��һ����ͨ����
  
 *  @~english
 *  @brief  Get the number of stream channels
 *  @param  hDevice                 [IN]            Device handle
 *  @param  pnNumStreams            [OUT]           Number of stream channels
 *  @return Return MV_FG_SUCCESS on success, and return Error Code on failure.
 *  @remarks Currently, a device only supports one stream channel.
 ************************************************************************/
MV_FGCTRL_API int __stdcall MV_FG_GetNumStreams(IN DEVHANDLE hDevice, OUT unsigned int *pnNumStreams);

/********************************************************************//**
 *  @~chinese
 *  @brief  ����ͨ��
 *  @param  hDevice                 [IN]           ������
 *  @param  nIndex                  [IN]           ��ͨ������
 *  @param  phStream                [OUT]          ��ͨ�����
 *  @return �ɹ�������MV_FG_SUCCESS��ʧ�ܷ��ش�����
  
 *  @~english
 *  @brief  Open the stream channel
 *  @param  hDevice                 [IN]            Device handle
 *  @param  nIndex                  [IN]            Stream channel index
 *  @param  phStream                [OUT]           Stream channel handle
 *  @return Return MV_FG_SUCCESS on success, and return Error Code on failure.
 ************************************************************************/
MV_FGCTRL_API int __stdcall MV_FG_OpenStream(IN DEVHANDLE hDevice, IN unsigned int nIndex, OUT STREAMHANDLE* phStream);

/********************************************************************//**
 *  @~chinese
 *  @brief  �ر���ͨ��
 *  @param  hStream                 [IN]           ��ͨ�����
 *  @return �ɹ�������MV_FG_SUCCESS��ʧ�ܷ��ش�����
  
 *  @~english
 *  @brief  Close the stream channel
 *  @param  hStream                 [IN]            Stream channel handle
 *  @return Return MV_FG_SUCCESS on success, and return Error Code on failure.
 ************************************************************************/
MV_FGCTRL_API int __stdcall MV_FG_CloseStream(IN STREAMHANDLE hStream);

/********************************************************************//**
 *  @~chinese
 *  @brief  ����SDK�ڲ���������
 *  @param  hStream                 [IN]           ��ͨ�����
 *  @param  nBufferNum              [IN]           ��������
 *  @return �ɹ�������MV_FG_SUCCESS��ʧ�ܷ��ش�����
 *  @remarks ��δ���øýӿڻ���nBufferNum��������Ϊ0ʱ����ʾSDK�ڲ��޻��棬��ʱ��Ҫ�û����뻺�沢����ͨ��ע�Ỻ�棬�����޷���ʼȡ����\n
             ��nBufferNum�������ô���0ʱ����ʾ������SDK�ڲ��������룬��ʱ�������û�����ͨ��ע�Ỻ�档\n
             ��������ͼ�񻺴���������Linux����ϵͳ�У��������ͼ�񻺴��������󣬵���ϵͳ�ڴ���ͣ�Ӧ�ó���ᱻ����ϵͳɱ����
  
 *  @~english
 *  @brief  Set the number of internal buffers for the SDK
 *  @param  hStream                 [IN]            Stream channel handle
 *  @param  nBufferNum              [IN]            Number of buffers
 *  @return Return MV_FG_SUCCESS on success, and return Error Code on failure.
 *  @remarks The SDK has no internal buffer if this API is not called or the value of parameter nBufferNum is set to 0.When there is no internal buffer, you need to request and register buffers to stream channels before starting image acquisition. \n
             When the parameter nBufferNum is set to a value greater than 0, buffers will be registered internally by the SDK, and it is not allowed to register buffers to stream channels at this time. \n
             The number of image buffers should be reasonably allocated. For Linux operating systems, if the number of image buffers is too large, then the system memory will be too low and the application will be killed by the operating system.
 ************************************************************************/
MV_FGCTRL_API int __stdcall MV_FG_SetBufferNum(IN STREAMHANDLE hStream, IN unsigned int nBufferNum);

/********************************************************************//**
 *  @~chinese
 *  @brief  ����ȡ������
 *  @param  hStream                 [IN]           ��ͨ�����
 *  @param  enGrabStrategy          [IN]           ȡ������
 *  @param  bUseTrashBuffer         [IN]           �Ƿ�ʹ����������, 0��ʾ�رգ�1��ʾ����
 *  @return �ɹ�������MV_FG_SUCCESS��ʧ�ܷ��ش�����
 *  @remarks �ýӿڶ���������ȡ�����ԣ��û����Ը���ʵ���������ѡ�񡣾����������£�
        -OneByOne:�Ӿɵ���һ֡һ֡�Ĵ���������б��л�ȡͼ�񣬴�����ͨ����Ĭ��Ϊ�ò���
        -LatestImagesOnly:������������б��л�ȡ���µ�һ֡ͼ��ͬʱ�����������б�
        -LatestImages:����������б��л�ȡ���µ�ͼ�񣬲������������б�
        -UpcomingImage:�ڵ���ȡͼ�ӿ�ʱ�����������б�������ͼ�񣬲��ȴ�����������ɵ�һ֡ͼ��
        bUseTrashBuffer����bUseTrashBuffer=trueʱ, ���ע��Ļ���ȫ����ȡ����û�е���MV_FG_ReleaseFrameBuffer\MV_FG_QueueBuffer\MV_FG_FlushQueue������Żأ�
        ��ʼʹ���ڲ������������ͼ�񣬽��յ���ͼ��ᱻ��������ֹ�ɼ����˶�ͼ��

 *  @~english
 *  @brief  Set grab strategy
 *  @param  hStream                 [IN]            Stream handle
 *  @param  enGrabStrategy          [IN]            Grab strategy
 *  @param  bUseTrashBuffer         [IN]            Whether use trash buffer to receive buffers
 *  @return Success, return MV_FG_SUCCESS. Failure, return error code 
 *  @remarks This interface is set by four image acquisition approaches, the user may choose one as needed. Specific details are as followed: 
        -OneByOne:Obtain image from output cache list frame by frame in order, this function is default strategy when device is on.
        -LatestImagesOnly:Obtain the latest image from output cache list only, meanwhile clear output cache list.
        -LatestImages:Obtain the latest OutputQueueSize image from output cache list, the range of OutputQueueSize is 1-ImageNodeNum, the user may set the value of MV_CC_SetOutputQueueSizeinterface,the default value of ImageNodeNum is 1,If the user usesMV_CC_SetImageNodeNuminterface to set up OutputQueueSize,when the value of OutputQueueSize is set to be 1, the function will be same as LatestImagesOnly; if the value of OutputQueueSize is set to be ImageNodeNum, the function will be same as OneByOne.
        -UpcomingImage:Ignore all images in output cache list when calling get image interface, wait the next upcoming image generated. Support for GigE camera only, not support for U3V camera.
        bUseTrashBuffer: when bUseTrashBuffer is true, start use trash buffer to receive buffers while all announced buffers has been taken and not put back, images in trash buffer will be discarded to avaid frame loss on hardware layer. 
        ************************************************************************/
MV_FGCTRL_API int __stdcall MV_FG_SetGrabStrategy(IN STREAMHANDLE hStream, IN MV_FG_GRAB_STRATEGY enGrabStrategy, bool8_t bUseTrashBuffer);

/********************************************************************//**
 *  @~chinese
 *  @brief  ע��֡������Ϣ�ص�����(SDK�ڲ����뻺�淽ʽ)
 *  @param  hStream                 [IN]           ��ͨ�����
 *  @param  cbFrame                 [IN]           ֡������Ϣ�ص�����
 *  @param  pUser                   [IN]           �û��Զ�������
 *  @return �ɹ�������MV_FG_SUCCESS��ʧ�ܷ��ش�����
 *  @remarks �ڻص������д����ʱ��������������֡��Ϣ��ȡ��\n
             ע��ص���ʽ��MV_FG_GetFrameBuffer���⡣\n
             �����ڵ���MV_FG_StartAcquisitionǰע��ص�������
  
 *  @~english
 *  @brief  Register the callback function for frame buffer information. This API is valid only when buffers are requested internally by the SDK.
 *  @param  hStream                 [IN]            Stream channel handle
 *  @param  cbFrame                 [IN]            Frame buffer information callback function
 *  @param  pUser                   [IN]            User-defined data
 *  @return Return MV_FG_SUCCESS on success, and return Error Code on failure.
 *  @remarks Time-consuming operations in the callback function will block the access to the subsequent frame buffer information. \n
             This API and MV_FG_GetFrameBuffer() are mutually exclusive. \n
             You need to call this API to register the callback function before calling API MV_FG_StartAcquisition() .
 ************************************************************************/
MV_FGCTRL_API int __stdcall MV_FG_RegisterFrameCallBack(IN STREAMHANDLE hStream, IN MV_FG_FrameCallBack cbFrame, IN void* pUser);

/********************************************************************//**
 *  @~chinese
 *  @brief  ע��֡������Ϣ�ص�����(SDK�ڲ����뻺�淽ʽ)
 *  @param  hStream                 [IN]           ��ͨ�����
 *  @param  cbFrame                 [IN]           ֡������Ϣ�ص�����
 *  @param  pUser                   [IN]           �û��Զ�������
 *  @param  bBufferRelease          [IN]           ������ձ�ǣ�1:�ص������������ڴ��Զ�������;0:�ص�������������Ҫ����MV_FG_ReleaseFrameBuffer���ܻ���
 *  @return �ɹ�������MV_FG_SUCCESS��ʧ�ܷ��ش�����
 *  @remarks �ڻص������д����ʱ��������������֡��Ϣ��ȡ��\n
             ע��ص���ʽ��MV_FG_GetFrameBuffer���⡣\n
             �����ڵ���MV_FG_StartAcquisitionǰע��ص�������\n
             ��bBufferReleaseΪ0ʱ��buffer�����Զ��ͷţ���Ҫ��ʱ���� MV_FG_ReleaseFrameBuffer �ͷ�buffer������ڲ�buffer���꣬�޷�����ȡ����
  
 *  @~english
 *  @brief  Register the callback function for frame buffer information. This API is valid only when buffers are requested internally by the SDK.
 *  @param  hStream                 [IN]            Stream channel handle
 *  @param  cbFrame                 [IN]            Frame buffer information callback function
 *  @param  pUser                   [IN]            User-defined data
 *  @param  bBufferRelease          [IN]            Method of releasing buffer. 1: The buffer will be released automatically after the callback function ends. 0: Call MV_FG_ReleaseFrameBuffer() to release the buffer after the callback function ends.
 *  @return Return MV_FG_SUCCESS on success, and return Error Code on failure.
 *  @remarks Time-consuming operations in the callback function will block the access to the subsequent frame buffer information. \n
             This API and MV_FG_GetFrameBuffer() are mutually exclusive. \n
             You need to call this API to register the callback function before calling API MV_FG_StartAcquisition() . \n
             When bBufferRelease is 0, the buffer will not be released automatically, and MV_FG_ReleaseFrameBuffer needs to be called in time to release the buffer. If the internal buffer is used up, the streaming cannot continue.
 ************************************************************************/
MV_FGCTRL_API int __stdcall MV_FG_RegisterFrameCallBackEx(IN STREAMHANDLE hStream, IN MV_FG_FrameCallBack cbFrame, IN void* pUser, IN bool8_t bBufferRelease);

/********************************************************************//**
 *  @~chinese
 *  @brief  ��ȡһ֡ͼ��Ļ�����Ϣ(SDK�ڲ����뻺�淽ʽ)
 *  @param  hStream                 [IN]           ��ͨ�����
 *  @param  pstBufferInfo           [OUT]          ������Ϣ
 *  @param  nTimeout                [IN]           ��ʱʱ�䣬�Ժ���Ϊ��λ
 *  @return �ɹ�������MV_FG_SUCCESS��ʧ�ܷ��ش�����
 *  @remarks ��Ҫ����MV_FG_ReleaseFrameBuffer�ӿڽ��л�����Ϣ���ͷš�
  
 *  @~english
 *  @brief  Get the buffer information of a frame. This API is valid only when buffers are requested internally by the SDK.
 *  @param  hStream                 [IN]            Stream channel handle
 *  @param  pstBufferInfo           [OUT]           Buffer information
 *  @param  nTimeout                [IN]            Timeout, unit: millisecond
 *  @return Return MV_FG_SUCCESS on success, and return Error Code on failure.
 *  @remarks The API MV_FG_ReleaseFrameBuffer() should be called to release the buffer information.
 ************************************************************************/
MV_FGCTRL_API int __stdcall MV_FG_GetFrameBuffer(IN STREAMHANDLE hStream, OUT MV_FG_BUFFER_INFO* pstBufferInfo, IN unsigned int nTimeout);

/********************************************************************//**
 *  @~chinese
 *  @brief  �ͷŻ�����Ϣ(SDK�ڲ����뻺�淽ʽ���˽ӿ������ͷŲ���ʹ�õ�ͼ�񻺴棬��MV_FG_GetFrameBuffer����ʹ��)
 *  @param  hStream                 [IN]           ��ͨ�����
 *  @param  pstBufferInfo           [IN]           ������Ϣ
 *  @return �ɹ�������MV_FG_SUCCESS��ʧ�ܷ��ش�����
 *  @remarks �ýӿ���MV_FG_GetFrameBuffer����ʹ�ã�ʹ��MV_FG_GetFrameBuffer�ӿ�ȡ����ͼ������pstBufferInfo����Ҫ��MV_FG_ReleaseFrameBuffer�ӿڽ���Ȩ���ͷš�
  
 *  @~english
 *  @brief  Release the buffer information. This API is valid only when buffers are requested internally by the SDK. This API is used to release the image buffer which is no longer used.
 *  @param  hStream                 [IN]            Stream channel handle
 *  @param  pstBufferInfo           [IN]            Buffer information
 *  @return Return MV_FG_SUCCESS on success, and return Error Code on failure.
 *  @remarks This API and MV_FG_GetFrameBuffer() should be used in pair. The image data (pstBufferInfo) obtained via MV_FG_GetFrameBuffer() should be released by this API.
 ************************************************************************/
MV_FGCTRL_API int __stdcall MV_FG_ReleaseFrameBuffer(IN STREAMHANDLE hStream, IN MV_FG_BUFFER_INFO* pstBufferInfo);

/********************************************************************//**
 *  @~chinese
 *  @brief  ��ȡ�����ڵ�ChunkData��Ϣ
 *  @param  hStream                 [IN]           ��ͨ�����
 *  @param  pstBufferInfo           [IN]           ������Ϣ
 *  @param  nIndex                  [IN]           ChunkData����
 *  @param  pstChunkDataInfo        [OUT]          ChunkData��Ϣ
 *  @return �ɹ�������MV_FG_SUCCESS��ʧ�ܷ��ش�����
 *  @remarks �ڻ�ȡ��������Ϣ֮�󣬵���MV_FG_ReleaseFrameBuffer����MV_FG_QueueBuffer֮ǰ���øýӿڲ��ܵõ���Ч��Ϣ��
  
 *  @~english
 *  @brief  Get the chunk data information of a buffer
 *  @param  hStream                 [IN]            Stream channel handle
 *  @param  pstBufferInfo           [IN]            Buffer information
 *  @param  nIndex                  [IN]            Chunk data index
 *  @param  pstChunkDataInfo        [OUT]           Chunk data information
 *  @return Return MV_FG_SUCCESS on success, and return Error Code on failure.
 *  @remarks After getting the buffer information, this API must be called before calling the APIs MV_FG_ReleaseFrameBuffer() and MV_FG_QueueBuffer() to get valid information of the chunk data.
 ************************************************************************/
MV_FGCTRL_API int __stdcall MV_FG_GetBufferChunkData(IN STREAMHANDLE hStream, IN MV_FG_BUFFER_INFO* pstBufferInfo, IN unsigned int nIndex, OUT MV_FG_CHUNK_DATA_INFO* pstChunkDataInfo);

/********************************************************************//**
 *  @~chinese
 *  @brief  ��ȡ��ͨ����ͼ���С
 *  @param  hStream                 [IN]           ��ͨ�����
 *  @param  pnPayloadSize           [OUT]          ��ͨ����ͼ���С
 *  @return �ɹ�������MV_FG_SUCCESS��ʧ�ܷ��ش�����
 *  @remarks �޸����ͼ����ز������ߡ����ظ�ʽ�Ȳ�������Ҫ���»�ȡ��ͨ����ͼ���С��
  
 *  @~english
 *  @brief  Get the image size of the stream channel
 *  @param  hStream                 [IN]            Stream channel handle
 *  @param  pnPayloadSize           [OUT]           Image size of the stream channel
 *  @return Return MV_FG_SUCCESS on success, and return Error Code on failure.
 *  @remarks The image size of the stream channel needs to be reacquired after the image-related parameters of the camera are changed, such as width, height, and pixel format.
 ************************************************************************/
MV_FGCTRL_API int __stdcall MV_FG_GetPayloadSize(IN STREAMHANDLE hStream, OUT unsigned int* pnPayloadSize);

/********************************************************************//**
 *  @~chinese
 *  @brief  ����ͨ����ע�Ỻ��(������MV_FG_StartAcquisitionǰע�Ỻ��)
 *  @param  hStream                 [IN]           ��ͨ�����
 *  @param  pBuffer                 [IN]           ͼ�񻺴��ַ
 *  @param  nSize                   [IN]           ͼ�񻺴��С
 *  @param  pPrivate                [IN]           ˽����Ϣ��ַ
 *  @param  phBuffer                [OUT]          ������
 *  @return �ɹ�������MV_FG_SUCCESS��ʧ�ܷ��ش�����
 *  @remarks ͼ�񻺴��Сͨ��MV_FG_GetPayloadSize�ӿڻ�ȡ��˽����Ϣ���û��Զ��塣
  
 *  @~english
 *  @brief  Register buffer to the stream channel. This API must be called prior to MV_FG_StartAcquisition.
 *  @param  hStream                 [IN]            Stream channel handle
 *  @param  pBuffer                 [IN]            Image buffer address
 *  @param  nSize                   [IN]            Image buffer size
 *  @param  pPrivate                [IN]            Private information address
 *  @param  phBuffer                [OUT]           Buffer handle
 *  @return Return MV_FG_SUCCESS on success, and return Error Code on failure.
 *  @remarks The image buffer size is acquired by calling the API MV_FG_GetPayloadSize(). The private information is user-defined.
 ************************************************************************/
MV_FGCTRL_API int __stdcall MV_FG_AnnounceBuffer(IN STREAMHANDLE hStream, IN void *pBuffer, IN unsigned int nSize, IN void *pPrivate, OUT BUFFERHANDLE *phBuffer); 

/********************************************************************//**
 *  @~chinese
 *  @brief  ����ͨ����������MV_FG_AnnounceBuffer�ӿ�ע��Ļ���
 *  @param  hStream                 [IN]           ��ͨ�����
 *  @param  hBuffer                 [IN]           ������
 *  @param  pBuffer                 [OUT]          ͼ�񻺴��ַ
 *  @param  pPrivate                [OUT]          ˽����Ϣ��ַ
 *  @return �ɹ�������MV_FG_SUCCESS��ʧ�ܷ��ش�����
 *  @remarks ֻ�ܳ���δʹ�ö����еĻ��棬��ͨ��MV_FG_FlushQueue�ӿڽ�����ŵ�δʹ�ö��С�
  
 *  @~english
 *  @brief  Revoke buffer from the stream channel
 *  @param  hStream                 [IN]            Stream channel handle
 *  @param  hBuffer                 [IN]            Buffer handle
 *  @param  pBuffer                 [OUT]           Image buffer address
 *  @param  pPrivate                [OUT]           Private information address
 *  @return Return MV_FG_SUCCESS on success, and return Error Code on failure.
 *  @remarks Only buffers in unused queues can be revoked. You can allocate buffers to unused queues by calling the API MV_FG_FlushQueue().
 ************************************************************************/
MV_FGCTRL_API int __stdcall MV_FG_RevokeBuffer(IN STREAMHANDLE hStream, IN BUFFERHANDLE hBuffer, OUT void **pBuffer, OUT void **pPrivate);

/********************************************************************//**
 *  @~chinese
 *  @brief  ˢ�»������
 *  @param  hStream                 [IN]           ��ͨ�����
 *  @param  enQueueType             [IN]           ��������
 *  @return �ɹ�������MV_FG_SUCCESS��ʧ�ܷ��ش�����
 *  @remarks ȡ�������в�֧��MV_FG_BUFFER_QUEUE_INPUT_TO_OUTPUT��MV_FG_BUFFER_QUEUE_ALL_DISCARD��
  
 *  @~english
 *  @brief  Refresh the buffer queue
 *  @param  hStream                 [IN]            Stream channel handle
 *  @param  enQueueType             [IN]            Buffer queue type
 *  @return Return MV_FG_SUCCESS on success, and return Error Code on failure.
 *  @remarks The following queue types are not supported during image acquisition: MV_FG_BUFFER_QUEUE_INPUT_TO_OUTPUT and MV_FG_BUFFER_QUEUE_ALL_DISCARD.
 ************************************************************************/
MV_FGCTRL_API int __stdcall MV_FG_FlushQueue(IN STREAMHANDLE hStream, IN MV_FG_BUFFER_QUEUE_TYPE enQueueType);

/********************************************************************//**
 *  @~chinese
 *  @brief  ��ʼȡ��
 *  @param  hStream                 [IN]           ��ͨ�����
 *  @return �ɹ�������MV_FG_SUCCESS��ʧ�ܷ��ش�����
  
 *  @~english
 *  @brief  Start image acquisition
 *  @param  hStream                 [IN]            Stream channel handle
 *  @return Return MV_FG_SUCCESS on success, and return Error Code on failure.
 ************************************************************************/
MV_FGCTRL_API int __stdcall MV_FG_StartAcquisition(IN STREAMHANDLE hStream);

/********************************************************************//**
 *  @~chinese
 *  @brief  ֹͣȡ��
 *  @param  hStream                 [IN]           ��ͨ�����
 *  @return �ɹ�������MV_FG_SUCCESS��ʧ�ܷ��ش�����
  
 *  @~english
 *  @brief  Stop image acquisition
 *  @param  hStream                 [IN]            Stream channel handle
 *  @return Return MV_FG_SUCCESS on success, and return Error Code on failure.
 ************************************************************************/
MV_FGCTRL_API int __stdcall MV_FG_StopAcquisition(IN STREAMHANDLE hStream);

/********************************************************************//**
 *  @~chinese
 *  @brief  ��ȡһ֡ͼ��Ļ�����Ϣ(ʹ��MV_FG_AnnounceBufferע�Ỻ���ȡ����ʽ)
 *  @param  hStream                 [IN]           ��ͨ�����
 *  @param  phBuffer                [OUT]          ������
 *  @param  nTimeout                [IN]           ��ʱʱ�䣬�Ժ���Ϊ��λ
 *  @return �ɹ�������MV_FG_SUCCESS��ʧ�ܷ��ش�����
 *  @remarks ͨ��MV_FG_GetBufferInfo�ӿڸ��ݻ�������ȡͼ����Ϣ��
  
 *  @~english
 *  @brief  Get the buffer handle of a frame. This API is valid only when buffers are registered and managed externally.
 *  @param  hStream                 [IN]            Stream channel handle
 *  @param  phBuffer                [OUT]           Buffer handle
 *  @param  nTimeout                [IN]            Timeout, unit: millisecond
 *  @return Return MV_FG_SUCCESS on success, and return Error Code on failure.
 *  @remarks By calling the API MV_FG_GetBufferInfo(), you can get the buffer information with the acquired buffer handle.
 ************************************************************************/
MV_FGCTRL_API int __stdcall MV_FG_GetImageBuffer(IN STREAMHANDLE hStream, OUT BUFFERHANDLE *phBuffer, IN unsigned int nTimeout);

/********************************************************************//**
 *  @~chinese
 *  @brief  ͨ����������ȡ������Ϣ
 *  @param  hBuffer                 [IN]           ������
 *  @param  pstBufferInfo           [OUT]          ������Ϣ
 *  @return �ɹ�������MV_FG_SUCCESS��ʧ�ܷ��ش�����
  
 *  @~english
 *  @brief  Get the buffer information by buffer handle
 *  @param  hBuffer                 [IN]            Buffer handle
 *  @param  pstBufferInfo           [OUT]           Buffer information
 *  @return Return MV_FG_SUCCESS on success, and return Error Code on failure.
 ************************************************************************/
MV_FGCTRL_API int __stdcall MV_FG_GetBufferInfo(IN BUFFERHANDLE hBuffer, OUT MV_FG_BUFFER_INFO* pstBufferInfo);

/********************************************************************//**
 *  @~chinese
 *  @brief  ��ͼ�񻺴�Ż�������У����ڵȴ��ɼ�ͼ��ͼ�񻺴�������MV_FG_GetImageBuffer�ӿڣ�
 *  @param  hBuffer                 [IN]           ������
 *  @return �ɹ�������MV_FG_SUCCESS��ʧ�ܷ��ش�����
  
 *  @~english
 *  @brief  Insert the buffer back to the input queue
 *  @param  hBuffer                 [IN]            Buffer handle
 *  @return Return MV_FG_SUCCESS on success, and return Error Code on failure.
 ************************************************************************/
MV_FGCTRL_API int __stdcall MV_FG_QueueBuffer(IN BUFFERHANDLE hBuffer);


/***********************************************************************/
/*                             ͼ����                                */
/*                         Image processing                            */
/***********************************************************************/
/********************************************************************//**
 *  @~chinese
 *  @brief  ��ʾһ֡ͼ��
 *  @param  hImage                  [IN]           ͼ����(����ʹ�òɼ���/���/�����)
 *  @param  hWnd                    [IN]           ���ھ��
 *  @param  pstDisplayFrameInfo     [IN]           ��ʾ��ͼ����Ϣ
 *  @return �ɹ�������MV_FG_SUCCESS��ʧ�ܷ��ش�����
 *  @remark ��Linuxƽ̨����Զ����ʾʱ����ҪOpenGL֧��Զ��ֱ����Ⱦģʽ��OpenGL�汾����4.0�汾�������Կ�����֧�ָ߰汾OpenGL��
  
 *  @~english
 *  @brief  Display one frame of image
 *  @param  hImage                  [IN]            Image handle. You can use the handle of frame grabbers, devices, or stream channels
 *  @param  hWnd                    [IN]            Window handle
 *  @param  pstDisplayFrameInfo     [IN]            Image information to be displayed
 *  @return Return MV_FG_SUCCESS on success, and return Error Code on failure.
 *  @remark When remote display is performed on the Linux platform, OpenGL must support the remote direct rendering mode, the OpenGL version need be later than 4.0, and the graphics card driver needs support a later version of OpenGL.
 ************************************************************************/
MV_FGCTRL_API int __stdcall MV_FG_DisplayOneFrame(IN IMAGEHANDLE hImage, IN void* hWnd, IN MV_FG_DISPLAY_FRAME_INFO *pstDisplayFrameInfo);

/********************************************************************//**
 *  @~chinese
 *  @brief  ��ͼ���ϻ��ƾ��ο�����(Linux�ݲ�֧��)
 *  @param  hImage                      [IN]            ͼ����(����ʹ�òɼ���/���/�����) ���������ʾ�ӿھ��һ��
 *  @param  pRectInfo                   [IN]            ���θ����ߵ���Ϣ
 *  @return �ɹ�������MV_FG_SUCCESS��ʧ�ܷ��ش�����
 *  @remarks  
 
 *  @~english
 *  @brief  Draw Rect Auxiliary Line(Linux is currently not supported)
 *  @param  handle                      [IN]            Image handle. You can use the handle of frame grabbers, devices, or stream channels. The handle should be consistent with the MV_FG_DisplayOneFrame interface.
 *  @param  pRectInfo                   [IN]            Rect Auxiliary Line Info
 *  @return Return MV_FG_SUCCESS on success, and return Error Code on failure.
 *  @remarks 
 ***********************************************************************/
MV_FGCTRL_API int __stdcall MV_FG_DrawRect(IN IMAGEHANDLE hImage, IN MVFG_RECT_INFO* pRectInfo);

/********************************************************************//**
 *  @~chinese
 *  @brief  ��ͼ���ϻ���Բ�θ�����(Linux�ݲ�֧��)
 *  @param  hImage                      [IN]            ͼ����(����ʹ�òɼ���/���/�����) ���������ʾ�ӿھ��һ��
 *  @param  pCircleInfo                 [IN]            Բ�θ����ߵ���Ϣ
 *  @return �ɹ�������MV_FG_SUCCESS��ʧ�ܷ��ش�����
 *  @remarks  
 
 *  @~english
 *  @brief  Draw Circle Auxiliary Line(Linux is currently not supported)
 *  @param  handle                      [IN]            Image handle. You can use the handle of frame grabbers, devices, or stream channels. The handle should be consistent with the MV_FG_DisplayOneFrame interface.
 *  @param  pCircleInfo                 [IN]            Circle Auxiliary Line Info
 *  @return  Return MV_FG_SUCCESS on success, and return Error Code on failure.
 *  @remarks 
 ***********************************************************************/
MV_FGCTRL_API int __stdcall MV_FG_DrawCircle(IN IMAGEHANDLE hImage, IN MVFG_CIRCLE_INFO* pCircleInfo);

/********************************************************************//**
 *  @~chinese
 *  @brief  ��ͼ���ϻ�������(Linux�ݲ�֧��)
 *  @param  hImage                      [IN]            ͼ����(����ʹ�òɼ���/���/�����) ���������ʾ�ӿھ��һ��
 *  @param  pLinesInfo                  [IN]            ������������Ϣ
 *  @return �ɹ�������MV_FG_SUCCESS��ʧ�ܷ��ش�����
 *  @remarks  
 
 *  @~english
 *  @brief  Draw Line Auxiliary Line(Linux is currently not supported)
 *  @param  handle                      [IN]            Image handle. You can use the handle of frame grabbers, devices, or stream channels. The handle should be consistent with the MV_FG_DisplayOneFrame interface.
 *  @param  pLinesInfo                  [IN]            Linear Auxiliary Line Info
 *  @return  Return MV_FG_SUCCESS on success, and return Error Code on failure.
 *  @remarks 
 ***********************************************************************/
MV_FGCTRL_API int __stdcall MV_FG_DrawLines(IN IMAGEHANDLE hImage, IN MVFG_LINES_INFO* pLinesInfo);

/********************************************************************//**
 *  @~chinese
 *  @brief  ����BMPͼ��
 *  @param  hImage                  [IN]           ͼ����(����ʹ�òɼ���/���/�����)
 *  @param  pstSaveBitmapInfo       [IN][OUT]      BMPͼ����Ϣ
 *  @return �ɹ�������MV_FG_SUCCESS��ʧ�ܷ��ش�����
  
 *  @~english
 *  @brief  Save the BMP image
 *  @param  hImage                  [IN]            Image handle. You can use the handle of frame grabbers, devices, or stream channels
 *  @param  pstSaveBitmapInfo       [IN][OUT]       BMP image information
 *  @return Return MV_FG_SUCCESS on success, and return Error Code on failure.
 ************************************************************************/
MV_FGCTRL_API int __stdcall MV_FG_SaveBitmap(IN IMAGEHANDLE hImage, IN OUT MV_FG_SAVE_BITMAP_INFO *pstSaveBitmapInfo);

/********************************************************************//**
 *  @~chinese
 *  @brief  ����JPEGͼ��
 *  @param  hImage                  [IN]           ͼ����(����ʹ�òɼ���/���/�����)
 *  @param  pstSaveJpegInfo         [IN][OUT]      JPEGͼ����Ϣ
 *  @return �ɹ�������MV_FG_SUCCESS��ʧ�ܷ��ش�����
  
 *  @~english
 *  @brief  Save the JPEG image
 *  @param  hImage                  [IN]            Image handle. You can use the handle of frame grabbers, devices, or stream channels
 *  @param  pstSaveJpegInfo         [IN][OUT]       JPEG image information
 *  @return Return MV_FG_SUCCESS on success, and return Error Code on failure.
 ************************************************************************/
MV_FGCTRL_API int __stdcall MV_FG_SaveJpeg(IN IMAGEHANDLE hImage, IN OUT MV_FG_SAVE_JPEG_INFO *pstSaveJpegInfo);

/********************************************************************//**
 *  @~chinese
 *  @brief  ����TIFFͼ��
 *  @param  hImage                  [IN]           ͼ����(����ʹ�òɼ���/���/�����)
 *  @param  pstSaveTiffInfo         [IN][OUT]      TIFFͼ����Ϣ
 *  @return �ɹ�������MV_FG_SUCCESS��ʧ�ܷ��ش�����
  
 *  @~english
 *  @brief  Save the TIFF image
 *  @param  hImage                  [IN]            Image handle. You can use the handle of frame grabbers, devices, or stream channels
 *  @param  pstSaveTiffInfo         [IN][OUT]       TIFF image information
 *  @return Return MV_FG_SUCCESS on success, and return Error Code on failure.
 ************************************************************************/
MV_FGCTRL_API int __stdcall MV_FG_SaveTiffToFile(IN IMAGEHANDLE hImage, IN OUT MV_FG_SAVE_TIFF_TO_FILE_INFO *pstSaveTiffInfo);

/********************************************************************//**
 *  @~chinese
 *  @brief  ����PNGͼ��
 *  @param  hImage                  [IN]           ͼ����(����ʹ�òɼ���/���/�����)
 *  @param  pstSavePngInfo          [IN][OUT]      PNGͼ����Ϣ
 *  @return �ɹ�������MV_FG_SUCCESS��ʧ�ܷ��ش�����
  
 *  @~english
 *  @brief  Save the PNG image
 *  @param  hImage                  [IN]            Image handle. You can use the handle of frame grabbers, devices, or stream channels
 *  @param  pstSavePngInfo          [IN][OUT]       PNG image information
 *  @return Return MV_FG_SUCCESS on success, and return Error Code on failure.
 ************************************************************************/
MV_FGCTRL_API int __stdcall MV_FG_SavePngToFile(IN IMAGEHANDLE hImage, IN OUT MV_FG_SAVE_PNG_TO_FILE_INFO *pstSavePngInfo);

/********************************************************************//**
 *  @~chinese
 *  @brief  ���ظ�ʽת��
 *  @param  hImage                  [IN]           ͼ����(����ʹ�òɼ���/���/�����)
 *  @param  pstConvertPixelInfo     [IN][OUT]      ���ظ�ʽת����Ϣ
 *  @return �ɹ�������MV_FG_SUCCESS��ʧ�ܷ��ش�����

 *  @~english
 *  @brief  Convert the pixel format
 *  @param  hImage                  [IN]            Image handle. You can use the handle of frame grabbers, devices, or stream channels
 *  @param  pstConvertPixelInfo     [IN][OUT]       Pixel format conversion information
 *  @return Return MV_FG_SUCCESS on success, and return Error Code on failure.
 ************************************************************************/
MV_FGCTRL_API int __stdcall MV_FG_ConvertPixelType(IN IMAGEHANDLE hImage, IN OUT MV_FG_CONVERT_PIXEL_INFO *pstConvertPixelInfo);

/********************************************************************//**
 *  @~chinese
 *  @brief  �������
 *  @param  hImage                      [IN]            ͼ����(����ʹ�òɼ���/���/�����)
 *  @param  pstDecodeParam              [IN][OUT]       �����������ṹ��
 *  @return �ɹ�������MV_FG_SUCCESS��ʧ�ܷ��ش�����
 *  @remarks ���������ȡ��������ѹ����������������ݣ�ͬʱ֧�ֽ�����ǰ���ʵʱͼ���ˮӡ��Ϣ���������������������ǵ�ǰ������߲���ʵʱȡ���ģ���ˮӡ���������쳣����
             ���봫�뵱ǰ��������������ܽ�����ͼ���ˮӡ��Ϣ������ɼ�������������ֻ�ܽ���������롣
 
 *  @~english
 *  @brief  Lossless decoding
 *  @param  hImage                      [IN]            Image handle. You can use the handle of frame grabbers, devices, or stream channels
 *  @param  pstDecodeParam              [IN][OUT]       Lossless decoding parameter structure
 *  @return Return MV_FG_SUCCESS on success, and return Error Code on failure.
 *  @remarks Decode the lossless compressed stream data from the camera into raw data. \n
             The API can also parse the watermark information of the real-time image of the current camera. (If the input lossless stream data is not from the current camera, or is not real-time stream, then exception might occur during the watermark parsing.) \n
             The watermark information of the image can be parsed only when you input the handle of the current camera. The frame grabber handle or the stream channel handle can only be used for lossless decoding.
 ************************************************************************/
MV_FGCTRL_API int __stdcall MV_FG_HB_Decode(IN IMAGEHANDLE hImage, IN OUT MV_FG_HB_DECODE_PARAM* pstDecodeParam);

/********************************************************************//**
 *  @~chinese
 *  @brief  JPEG����
 *  @param  hImage                      [IN]            ͼ����(����ʹ�òɼ���/���/�����)
 *  @param  pstDecodeParam              [IN][OUT]       JPEG��������ṹ��
 *  @return �ɹ�������MV_FG_SUCCESS��ʧ�ܷ��ش�����
 *  @remarks ���������ȡ����JPEG������������ݡ�
 
 *  @~english
 *  @brief  JPEG decoding
 *  @param  hImage                      [IN]            Image handle. You can use the handle of frame grabbers, cameras, or stream channels
 *  @param  pstDecodeParam              [IN][OUT]       JPEG decoding parameter structure
 *  @return Return MV_FG_SUCCESS on success, and return Error Code on failure.
 *  @remarks Decode the JPEG stream from the camera into raw data.
 ************************************************************************/
MV_FGCTRL_API int __stdcall MV_FG_DecodeJpeg(IN IMAGEHANDLE hImage, IN OUT MV_FG_DECODE_JPEG_PARAM* pstDecodeParam);

/********************************************************************//**
 *  @~chinese
 *  @brief  ����ͼ��
 *  @param  hImage                  [IN]           ͼ����(����ʹ�òɼ���/���/�����)
 *  @param  pstReconstructInfo      [IN][OUT]      ������Ϣ
 *  @return �ɹ�������MV_FG_SUCCESS��ʧ�ܷ��ش�����
 *  @remarks ֧��ͼ����ת��ͼ��ת��ͼ��ָ��������ض�ǰ�������磺\n
             ͼ����ת��ͼ��ת֧�ֵ����ظ�ʽΪMV_FG_PIXEL_TYPE_Mono8��MV_FG_PIXEL_TYPE_RGB8_Packed��MV_FG_PIXEL_TYPE_BGR8_Packed��\n
             ͼ��ָ�֧���������ظ�ʽ��ͼ��ָ�Ӧ����������ġ�MultiLightControl���ڵ����ʹ�ã��ýڵ�����ö����ͬ���ع�ֵ����MultiLightControl=2��\n
             ����Ὣ������ͬ�ع�ֵ����Ӧ������ͼ�񽻵��ϲ�Ϊһ��ͼ��(ʵ�ʸ߶�Ϊ����ͼ��ĸ߶�)���͸��ϲ�Ӧ�ó���\n
             ���øýӿڲ��������鷽ʽΪRECONSTRUCT_MODE_SPLIT_BY_LINE_2���ɽ�������͵�һ��ͼ��ָ�Ϊ2��ͼ��������ͼ��ֱ��Ӧһ���ع�ֵ��\n
             ��ʹ����ͨ�����δ����������ġ�MultiLightControl���ڵ㣬��ͼ��ָ������壬ֻ�ǽ�ͼ���зָ�Ϊ2��3��4��ͼ��\n
             ÿ��ͼ��ĸ߶ȱ�Ϊԭͼ���1/2��1/3��1/4(��enReconstructMode����)��
  
 *  @~english
 *  @brief  Reconstruct Image
 *  @param  hImage                  [IN]            Image handle. You can use the handle of frame grabbers, devices, or stream channels
 *  @param  pstReconstructInfo      [IN][OUT]       Reconstruct imag information
 *  @return Return MV_FG_SUCCESS on success, and return Error Code on failure.
 *  @remarks Image rotation, image flipping, and image splitting are supported, but with specific preconditions. \n
             The pixel format supported by image rotation and image flipping are MV_FG_PIXEL_TYPE_Mono8, MV_FG_PIXEL_TYPE_RGB8_Packet, and MV_FG_PIXEL_TYPE_BGR8_Packed. \n
             Image segmentation supports all pixel formats. Image segmentation should be used with the "MultiLightControl" node of the linear array camera. This node can set multiple different exposure values, such as MultiLightControl=2. \n
             The camera will overlap and merge the two images with two different exposure values into one image (its height is the sum of the two images) and send it to the upper application. \n
             Call this API and pass in RECONSTRUCT_MODE_SPLIT_BY_LINE_2 to divide the image sent by the camera into two images, each of which corresponds to an exposure value. \n
             If an ordinary camera is used or the "MultiLightControl" node of the linear array camera is not enabled, then the image segmentation is meaningless. \n
             The image will only be divided into 2, 3, and 4 images by line, and the height of each image becomes 1/2, 1/3, 1/4 of the original image (determined by enReconstructMode).
 ************************************************************************/
MV_FGCTRL_API int __stdcall MV_FG_ReconstructImage(IN IMAGEHANDLE hImage, IN OUT MV_FG_RECONSTRUCT_INFO *pstReconstructInfo);


/***********************************************************************/
/*                             ͨ�ýӿ�                                */
/*                            General API                              */
/***********************************************************************/
/********************************************************************//**
 *  @~chinese
 *  @brief  ��ȡXML�ļ�
 *  @param  hPort                   [IN]           �������(����ʹ�òɼ���/������)
 *  @param  pData                   [IN][OUT]      ���XML�ļ��Ļ����ַ
 *  @param  nDataSize               [IN]           ���XML�ļ��Ļ����С
 *  @param  pnDataLen               [OUT]          XML�ļ�����
 *  @return �ɹ�������MV_FG_SUCCESS��ʧ�ܷ��ش�����
  
 *  @~english
 *  @brief  Get XML file of frame grabbers/devices
 *  @param  hPort                   [IN]            Handle of the object to which the parameter belongs; the object can be either a frame grabber or a device
 *  @param  pData                   [IN][OUT]       Address of the buffer in which the XML file is stored
 *  @param  nDataSize               [IN]            Size of the buffer in which the XML file is stored
 *  @param  pnDataLen               [OUT]           Length of the XML file
 *  @return Return MV_FG_SUCCESS on success, and return Error Code on failure.
 ************************************************************************/
MV_FGCTRL_API int __stdcall MV_FG_GetXMLFile(IN PORTHANDLE hPort, IN OUT unsigned char* pData, IN unsigned int nDataSize, OUT unsigned int* pnDataLen);

/********************************************************************//**
 *  @~chinese
 *  @brief  ��ýڵ�ķ���ģʽ
 *  @param  hPort                   [IN]           �������(����ʹ�òɼ���/������)
 *  @param  strName                 [IN]           �ڵ�����
 *  @param  penAccessMode           [OUT]          �ڵ����ģʽ
 *  @return �ɹ�������MV_FG_SUCCESS��ʧ�ܷ��ش�����
 *  @remarks ��ȡEnumEntry���ͽڵ�ķ���ģʽ��strNameӦ����EnumEntry_NodeName_EnumEntryName��\n
             ���ȡPixelFormatö�������µ�EnumEntry�ڵ�Mono8��strName��ʽΪ��EnumEntry_PixelFormat_Mono8����
  
 *  @~english
 *  @brief  Get the access mode of a node
 *  @param  hPort                   [IN]            Handle of the object to which the parameter belongs; the object can be either a frame grabber or a device
 *  @param  strName                 [IN]            Node name
 *  @param  penAccessMode           [OUT]           Node access mode
 *  @return Return MV_FG_SUCCESS on success, and return Error Code on failure.
 *  @remarks To get the access mode of the EnumEntry type node, the input value for strName should be in the format "EnumEntry_NodeName_EnumEntryName". \n
             For example, to get the access mode of the node MV_FG_PIXEL_TYPE_Mono8 of the enumeration MV_FG_PIXEL_TYPE, the strName should be "EnumEntry_PixelFormat_Mono8".
 ************************************************************************/
MV_FGCTRL_API int __stdcall MV_FG_GetNodeAccessMode(IN PORTHANDLE hPort, IN const char * strName, OUT MV_FG_NODE_ACCESS_MODE *penAccessMode);

/********************************************************************//**
 *  @~chinese
 *  @brief  ��ýڵ������
 *  @param  hPort                   [IN]           �������(����ʹ�òɼ���/������)
 *  @param  strName                 [IN]           �ڵ�����
 *  @param  penInterfaceType        [OUT]          �ڵ�����
 *  @return �ɹ�������MV_FG_SUCCESS��ʧ�ܷ��ش�����
  
 *  @~english
 *  @brief  Get the type of a node
 *  @param  hPort                   [IN]            Handle of the object to which the parameter belongs; the object can be either a frame grabber or a device
 *  @param  strName                 [IN]            Node name
 *  @param  penInterfaceType        [OUT]           Node type
 *  @return Return MV_FG_SUCCESS on success, and return Error Code on failure.
 ************************************************************************/
MV_FGCTRL_API int __stdcall MV_FG_GetNodeInterfaceType(IN PORTHANDLE hPort, IN const char * strName, OUT MV_FG_NODE_INTERFACE_TYPE *penInterfaceType);

/********************************************************************//**
 *  @~chinese
 *  @brief  ��ȡ���ͽڵ���Ϣ
 *  @param  hPort                   [IN]           �������(����ʹ�òɼ���/������)
 *  @param  strKey                  [IN]           �ڵ�����
 *  @param  pstIntValue             [OUT]          ���ͽڵ���Ϣ
 *  @return �ɹ�������MV_FG_SUCCESS��ʧ�ܷ��ش�����
  
 *  @~english
 *  @brief  Get the information about an integer type node
 *  @param  hPort                   [IN]            Handle of the object to which the parameter belongs; the object can be either a frame grabber or a device
 *  @param  strKey                  [IN]            Node name
 *  @param  pstIntValue             [OUT]           Integer node information
 *  @return Return MV_FG_SUCCESS on success, and return Error Code on failure.
 ************************************************************************/
MV_FGCTRL_API int __stdcall MV_FG_GetIntValue(IN PORTHANDLE hPort, IN const char* strKey, OUT MV_FG_INTVALUE *pstIntValue);

/********************************************************************//**
 *  @~chinese
 *  @brief  �������ͽڵ���Ϣ
 *  @param  hPort                   [IN]           �������(����ʹ�òɼ���/������)
 *  @param  strKey                  [IN]           �ڵ�����
 *  @param  nValue                  [IN]           Ҫ���õ�ֵ
 *  @return �ɹ�������MV_FG_SUCCESS��ʧ�ܷ��ش�����
  
 *  @~english
 *  @brief  Set the information of an integer type node
 *  @param  hPort                   [IN]            Handle of the object to which the parameter belongs; the object can be either a frame grabber or a device
 *  @param  strKey                  [IN]            Node name
 *  @param  nValue                  [IN]            Value to be set
 *  @return Return MV_FG_SUCCESS on success, and return Error Code on failure.
 ************************************************************************/
MV_FGCTRL_API int __stdcall MV_FG_SetIntValue(IN PORTHANDLE hPort, IN const char* strKey, IN int64_t nValue);

/********************************************************************//**
 *  @~chinese
 *  @brief  ��ȡö�����ͽڵ����Ϣ
 *  @param  hPort                   [IN]           �������(����ʹ�òɼ���/������)
 *  @param  strKey                  [IN]           �ڵ�����
 *  @param  pstEnumValue            [OUT]          ö�����ͽڵ���Ϣ
 *  @return �ɹ�������MV_FG_SUCCESS��ʧ�ܷ��ش�����
  
 *  @~english
 *  @brief  Get the information about an enumerated type node
 *  @param  hPort                   [IN]            Handle of the object to which the parameter belongs; the object can be either a frame grabber or a device
 *  @param  strKey                  [IN]            Node name
 *  @param  pstEnumValue            [OUT]           Information about the enumerated type node
 *  @return Return MV_FG_SUCCESS on success, and return Error Code on failure.
 ************************************************************************/
MV_FGCTRL_API int __stdcall MV_FG_GetEnumValue(IN PORTHANDLE hPort, IN const char* strKey, OUT MV_FG_ENUMVALUE *pstEnumValue);

/********************************************************************//**
 *  @~chinese
 *  @brief  ����ö�����ͽڵ����Ϣ
 *  @param  hPort                   [IN]           �������(����ʹ�òɼ���/������)
 *  @param  strKey                  [IN]           �ڵ�����
 *  @param  nValue                  [IN]           Ҫ���õ�ֵ
 *  @return �ɹ�������MV_FG_SUCCESS��ʧ�ܷ��ش�����
  
 *  @~english
 *  @brief  Set the information about an enumerated type node
 *  @param  hPort                   [IN]            Handle of the object to which the parameter belongs; the object can be either a frame grabber or a device
 *  @param  strKey                  [IN]            Node name
 *  @param  nValue                  [IN]            Value to be set
 *  @return Return MV_FG_SUCCESS on success, and return Error Code on failure.
 ************************************************************************/
MV_FGCTRL_API int __stdcall MV_FG_SetEnumValue(IN PORTHANDLE hPort, IN const char* strKey, IN unsigned int nValue);

/********************************************************************//**
 *  @~chinese
 *  @brief  ͨ���ַ�������ö�����ͽڵ����Ϣ
 *  @param  hPort                   [IN]           �������(����ʹ�òɼ���/������)
 *  @param  strKey                  [IN]           �ڵ�����
 *  @param  strValue                [IN]           Ҫ���õ�ֵ
 *  @return �ɹ�������MV_FG_SUCCESS��ʧ�ܷ��ش�����
  
 *  @~english
 *  @brief  Set the information of an enumeration type node by string
 *  @param  hPort                   [IN]            Handle of the object to which the parameter belongs; the object can be either a frame grabber or a device
 *  @param  strKey                  [IN]            Node name
 *  @param  strValue                [IN]            Value to be set
 *  @return Return MV_FG_SUCCESS on success, and return Error Code on failure.
 ************************************************************************/
MV_FGCTRL_API int __stdcall MV_FG_SetEnumValueByString(IN PORTHANDLE hPort, IN const char* strKey, IN const char* strValue);

/********************************************************************//**
 *  @~chinese
 *  @brief  ��ȡ�����ȸ����ͽڵ����Ϣ
 *  @param  hPort                   [IN]           ��������������
 *  @param  strKey                  [IN]           �ڵ�����
 *  @param  pstFloatValue           [OUT]          �����ȸ����ͽڵ���Ϣ
 *  @return �ɹ�������MV_FG_SUCCESS��ʧ�ܷ��ش�����
  
 *  @~english
 *  @brief  Get the information about a float type node
 *  @param  hPort                   [IN]            Handle of the object to which the parameter belongs; the object can be either a frame grabber or a device
 *  @param  strKey                  [IN]            Node name
 *  @param  pstFloatValue           [OUT]           Information about the float type node
 *  @return Return MV_FG_SUCCESS on success, and return Error Code on failure.
 ************************************************************************/
MV_FGCTRL_API int __stdcall MV_FG_GetFloatValue(IN PORTHANDLE hPort, IN const char* strKey, OUT MV_FG_FLOATVALUE *pstFloatValue);

/********************************************************************//**
 *  @~chinese
 *  @brief  ���õ����ȸ����ͽڵ����Ϣ
 *  @param  hPort                   [IN]           �������(����ʹ�òɼ���/������)
 *  @param  strKey                  [IN]           �ڵ�����
 *  @param  fValue                  [IN]           Ҫ���õ�ֵ
 *  @return �ɹ�������MV_FG_SUCCESS��ʧ�ܷ��ش�����
  
 *  @~english
 *  @brief  Set the information of a float type node
 *  @param  hPort                   [IN]            Handle of the object to which the parameter belongs; the object can be either a frame grabber or a device
 *  @param  strKey                  [IN]            Node name
 *  @param  fValue                  [IN]            Value to be set
 *  @return Return MV_FG_SUCCESS on success, and return Error Code on failure.
 ************************************************************************/
MV_FGCTRL_API int __stdcall MV_FG_SetFloatValue(IN PORTHANDLE hPort, IN const char* strKey, IN float fValue);

/********************************************************************//**
 *  @~chinese
 *  @brief  ��ȡ�����ͽڵ����Ϣ
 *  @param  hPort                   [IN]           �������(����ʹ�òɼ���/������)
 *  @param  strKey                  [IN]           �ڵ�����
 *  @param  pbValue                 [OUT]          �����ͽڵ���Ϣ
 *  @return �ɹ�������MV_FG_SUCCESS��ʧ�ܷ��ش�����
  
 *  @~english
 *  @brief  Get the information about a boolean type node
 *  @param  hPort                   [IN]            Handle of the object to which the parameter belongs; the object can be either a frame grabber or a device
 *  @param  strKey                  [IN]            Node name
 *  @param  pbValue                 [OUT]            Information about the boolean type node
 *  @return Return MV_FG_SUCCESS on success, and return Error Code on failure.
 ************************************************************************/
MV_FGCTRL_API int __stdcall MV_FG_GetBoolValue(IN PORTHANDLE hPort, IN const char* strKey, OUT bool8_t *pbValue);

/********************************************************************//**
 *  @~chinese
 *  @brief  ���ò������ͽڵ����Ϣ
 *  @param  hPort                   [IN]           �������(����ʹ�òɼ���/������)
 *  @param  strKey                  [IN]           �ڵ�����
 *  @param  bValue                  [IN]           Ҫ���õ�ֵ
 *  @return �ɹ�������MV_FG_SUCCESS��ʧ�ܷ��ش�����
  
 *  @~english
 *  @brief  Set the information of a boolean type node
 *  @param  hPort                   [IN]            Handle of the object to which the parameter belongs; the object can be either a frame grabber or a device
 *  @param  strKey                  [IN]            Node name
 *  @param  bValue                  [IN]            Value to be set
 *  @return Return MV_FG_SUCCESS on success, and return Error Code on failure.
 ************************************************************************/
MV_FGCTRL_API int __stdcall MV_FG_SetBoolValue(IN PORTHANDLE hPort, IN const char* strKey, IN bool8_t bValue);

/********************************************************************//**
 *  @~chinese
 *  @brief  ��ȡ�ַ����ͽڵ����Ϣ
 *  @param  hPort                   [IN]           �������(����ʹ�òɼ���/������)
 *  @param  strKey                  [IN]           �ڵ�����
 *  @param  pstStringValue          [OUT]          �ַ����ͽڵ���Ϣ
 *  @return �ɹ�������MV_FG_SUCCESS��ʧ�ܷ��ش�����
  
 *  @~english
 *  @brief  Get the information about a string type node
 *  @param  hPort                   [IN]            Handle of the object to which the parameter belongs; the object can be either a frame grabber or a device
 *  @param  strKey                  [IN]            Node name
 *  @param  pstStringValue          [OUT]           Information about the string type node
 *  @return Return MV_FG_SUCCESS on success, and return Error Code on failure.
 ************************************************************************/
MV_FGCTRL_API int __stdcall MV_FG_GetStringValue(IN PORTHANDLE hPort, IN const char* strKey, OUT MV_FG_STRINGVALUE *pstStringValue);

/********************************************************************//**
 *  @~chinese
 *  @brief  �����ַ����ͽڵ����Ϣ
 *  @param  hPort                   [IN]           �������(����ʹ�òɼ���/������)
 *  @param  strKey                  [IN]           �ڵ�����
 *  @param  strValue                [IN]           Ҫ���õ�ֵ
 *  @return �ɹ�������MV_FG_SUCCESS��ʧ�ܷ��ش�����
  
 *  @~english
 *  @brief  Set the information of a string type node
 *  @param  hPort                   [IN]            Handle of the object to which the parameter belongs; the object can be either a frame grabber or a device
 *  @param  strKey                  [IN]            Node name
 *  @param  strValue                [IN]            Value to be set
 *  @return Return MV_FG_SUCCESS on success, and return Error Code on failure.
 ************************************************************************/
MV_FGCTRL_API int __stdcall MV_FG_SetStringValue(IN PORTHANDLE hPort, IN const char* strKey, IN const char* strValue);

/********************************************************************//**
 *  @~chinese
 *  @brief  ִ�������ͽڵ������
 *  @param  hPort                   [IN]           �������(����ʹ�òɼ���/������)
 *  @param  strKey                  [IN]           �ڵ�����
 *  @return �ɹ�������MV_FG_SUCCESS��ʧ�ܷ��ش�����
  
 *  @~english
 *  @brief  Execute the commands of a command type node
 *  @param  hPort                   [IN]            Handle of the object to which the parameter belongs; the object can be either a frame grabber or a device
 *  @param  strKey                  [IN]            Node name
 *  @return Return MV_FG_SUCCESS on success, and return Error Code on failure.
 ************************************************************************/
MV_FGCTRL_API int __stdcall MV_FG_SetCommandValue(IN PORTHANDLE hPort, IN const char* strKey);

/********************************************************************//**
 *  @~chinese
 *  @brief  �����Զ��������ֵ
 *  @param  hPort                   [IN]           �������(ֻ��ʹ��������)
 *  @param  enConfigCmd             [IN]           ����ָ����粨����
 *  @param  nValue                  [IN]           Ҫ���õ�ֵ
 *  @return �ɹ�������MV_FG_SUCCESS��ʧ�ܷ��ش�����
 *  @remarks ��֧��CML�����
  
 *  @~english
 *  @brief  Configure custom integer type value
 *  @param  hPort                   [IN]            Handle of the object to which the parameter belongs; the object can only be a device
 *  @param  enConfigCmd             [IN]            Configuration command, such as baud rate
 *  @param  nValue                  [IN]            Values to be set
 *  @return Return MV_FG_SUCCESS on success, and return Error Code on failure.
 *  @remarks Only Camera Link cameras are supported
 ************************************************************************/
MV_FGCTRL_API int __stdcall MV_FG_SetConfigIntValue(IN PORTHANDLE hPort, IN MV_FG_CONFIG_CMD enConfigCmd, IN int64_t nValue);

/********************************************************************//**
 *  @~chinese
 *  @brief  �����豸����
 *  @param  hPort                   [IN]            �������(����ʹ�òɼ���/������)
 *  @param  strFileName             [IN]            �����ļ�������֧������·��
 *  @return �ɹ�������MV_FG_SUCCESS�����󣬷��ش����� 
 *  @remarks ��֧��CML���, �����û�ʹ��.hcf ��Ϊ����������ļ���׺�� \n
 *           ������������ʱ��ͬʱ����ɼ�����������ԡ�

 *  @~english
 *  @brief  Save device feature
 *  @param  hPort                   [IN]            Handle of the object to which the parameter belongs; the object can be either a frame grabber or a device
 *  @param  strFileName             [IN]            Name of the file in which the device attributes and features will be saved (only supports English)
 *  @return Return MV_FG_SUCCESS on success, and return Error Code on failure.
 *  @remarks Camera Link cameras are not supported. It is recommended that users use .hcf as the suffix name for saved attribute files. \n
 *           When passed to the device handle, both the frame grabber and device properties are saved.
 ************************************************************************/
MV_FGCTRL_API int __stdcall MV_FG_FeatureSave(IN PORTHANDLE hPort, IN const char* strFileName);

/********************************************************************//**
 *  @~chinese
 *  @brief  �����豸����
 *  @param  hPort                   [IN]            �������(����ʹ�òɼ���/������)
 *  @param  strFileName             [IN]            �����ļ�������֧������·��
 *  @return �ɹ�������MV_FG_SUCCESS�����󣬷��ش����� 
 *  @remarks ��֧��CML�����������������ʱ��ͬʱ����ɼ�����������ԡ�

 *  @~english
 *  @brief  Load device feature
 *  @param  hPort                   [IN]            Handle of the object to which the parameter belongs; the object can be either a frame grabber or a device
 *  @param  strFileName             [IN]            Name of the file in which the device attributes and features will be saved (only supports English)
 *  @return Return MV_FG_SUCCESS on success, and return Error Code on failure.
 *  @remarks Camera Link cameras are not supported. \n
 *           When passed to the device handle, both the frame grabber and device properties are loaded.
 ************************************************************************/
MV_FGCTRL_API int __stdcall MV_FG_FeatureLoad(IN PORTHANDLE hPort, IN const char* strFileName);

/********************************************************************//**
 *  @~chinese
 *  @brief  ���豸��ȡ�ļ�
 *  @param  hPort                       [IN]            �������(����ʹ�òɼ���/������)
 *  @param  pstFileAccess               [IN]            �ļ���ȡ�ṹ��
 *  @return �ɹ�������MV_FG_SUCCESS�����󣬷��ش����� 
 *  @remarks ������Ϊ�ļ�����Ȩ�޵����⵼�¶�ʧ�� \n
 *           ��/����ϵ��ļ�������UserSetSelector���Խڵ㡣
 
 *  @~english
 *  @brief  Read the file data from a device
 *  @param  hPort                       [IN]            Handle of the object to which the parameter belongs; the object can be either a frame grabber or a device
 *  @param  pstFileAccess               [IN]            File access structure
 *  @return Success, return MV_FG_SUCCESS. Failure, return error code
 *  @remarks Reading might fail if you do not have the operation permission of the files. \n
 *           The file name on the interface/camera comes from the UserSetSelector attribute node.
 ************************************************************************/
MV_FGCTRL_API int __stdcall MV_FG_FileAccessRead(IN PORTHANDLE hPort, IN OUT MV_FG_FILE_ACCESS* pstFileAccess);

/********************************************************************//**
 *  @~chinese
 *  @brief  ���ļ�д���豸
 *  @param  hPort                       [IN]            �������(����ʹ�òɼ���/������)
 *  @param  pstFileAccess               [IN]            �ļ���ȡ�ṹ��
 *  @return �ɹ�������MV_FG_SUCCESS�����󣬷��ش�����
 *  @remarks ��/����ϵ��ļ�������UserSetSelector���Խڵ㡣
 
 *  @~english
 *  @brief  Write the file to the device
 *  @param  hPort                       [IN]            Handle of the object to which the parameter belongs; the object can be either a frame grabber or a device
 *  @param  pstFileAccess               [IN]            File access structure
 *  @return Success, return MV_FG_SUCCESS. Failure, return error code
 *  @remark The file name on the interface/camera comes from the UserSetSelector attribute node.
 ************************************************************************/
MV_FGCTRL_API int __stdcall MV_FG_FileAccessWrite(IN PORTHANDLE hPort, IN MV_FG_FILE_ACCESS* pstFileAccess);

/********************************************************************//**
 *  @~chinese
 *  @brief  ���GenICam�ڵ㻺��
 *  @param  hPort                       [IN]            �������(����ʹ�òɼ���/������)
 *  @return �ɹ�������MV_FG_SUCCESS�����󣬷��ش�����
 
 *  @~english
 *  @brief  Clear the GenICam nodes buffer
 *  @param  hPort                       [IN]            Handle of the object to which the parameter belongs; the object can be either a frame grabber or a device
 *  @return Success, return MV_FG_SUCCESS. Failure, return error code
 ************************************************************************/
MV_FGCTRL_API int __stdcall MV_FG_InvalidateNodes(IN PORTHANDLE hPort);

/********************************************************************//**
 *  @~chinese
 *  @brief  ��ȡ�ɼ���/����Ĵ���
 *  @param  hPort                   [IN]            ���(����ʹ�òɼ���/������)
 *  @param  pBuffer                 [IN]            ��Ϊ����ֵʹ�ã�����������ڴ�ֵ��ע����ݲɼ���/����������ִ�С�ˣ�
 *  @param  nAddress                [IN]            ��ȡ���ڴ��ַ���õ�ַ���ԴӲɼ���/�����XML�ļ��л�ȡ������xxx_RegAddr�Ľڵ�ֵ
 *  @param  nLength                 [IN]            ��ȡ���ڴ泤��
 *  @param  pnOutLength             [OUT]           ʵ�ʷ��ص��ڴ泤��
 *  @return �ɹ�������MV_FG_SUCCESS�����󣬷��ش����� 
 *  @remarks ���ʲɼ���/�������ȡĳ�μĴ���������

 *  @~english
 *  @brief  Read frame grabber or device register
 *  @param  handle                      [IN]            Handle (frame grabber or device).
 *  @param  pBuffer                     [IN][OUT]       Used as a returned value to save the read-in memory value. (Memory value is stored in accordance with the big end and little end model.)
 *  @param  nAddress                    [IN]            Memory address to be read, which can be obtained from the xml file of the frame grabber or device. It is a node value in the format of xxx_RegAddr
 *  @param  nLength                     [IN]            Length of the memory to be read
 *  @param  pnOutLength                 [OUT]           Actual length of the returned memory
 *  @return Return MV_FG_SUCCESS on success, and return Error Code on failure.
 *  @remarks Access the frame grabber or device and read the data from a certain segment of register.
 ************************************************************************/
MV_FGCTRL_API int __stdcall MV_FG_ReadPort(IN PORTHANDLE hPort, void *pBuffer, int64_t nAddress, int64_t nLength, int64_t* pnOutLength);

/********************************************************************//**
 *  @~chinese
 *  @brief  д��ɼ���/����Ĵ���
 *  @param  hPort                   [IN]            ���(����ʹ�òɼ���/������)
 *  @param  pBuffer                 [IN]            ��д����ڴ�ֵ��ע����ݲɼ���/����������ִ�С�ˣ�
 *  @param  nAddress                [IN]            ��д����ڴ��ַ���õ�ַ���ԴӲɼ���/�����XML�ļ��л�ȡ������xxx_RegAddr�Ľڵ�ֵ
 *  @param  nLength                 [IN]            ��д����ڴ泤��
 *  @param  pnOutLength             [OUT]           ʵ��д����ڴ泤��
 *  @return �ɹ�������MV_FG_SUCCESS�����󣬷��ش����� 
 *  @remarks ���ʲɼ���/�������һ������д��ĳ�μĴ���

 *  @~english
 *  @brief  Write to frame grabber or device register
 *  @param  handle                      [IN]            Handle (frame grabber or device)
 *  @param  pBuffer                     [IN]            Memory value to be written. (Memory value is stored in accordance with the big end and little end model.)
 *  @param  nAddress                    [IN]            Memory address to be written, which can be obtained from the xml file of the frame grabber or device. It is a node value in the format of xxx_RegAddr
 *  @param  nLength                     [IN]            Length of the memory to be written
 *  @param  pnOutLength                 [OUT]           Actual length of the written memory
 *  @return Return MV_FG_SUCCESS on success, and return Error Code on failure.
 *  @remarks Access the frame grabber or device and write a piece of data into a certain segment of register.
 ************************************************************************/
MV_FGCTRL_API int __stdcall MV_FG_WritePort(IN PORTHANDLE hPort, const void *pBuffer, int64_t nAddress, int64_t nLength, int64_t* pnOutLength);

/********************************************************************//**
 *  @~chinese
 *  @brief  ע���¼��ص�����
 *  @param  hPort                   [IN]           �������(����ʹ�òɼ���/������)
 *  @param  strEventName            [IN]           �¼�����
 *  @param  cbEvent                 [IN]           �¼��ص�����
 *  @param  pUser                   [IN]           �û��Զ�������
 *  @return �ɹ�������MV_FG_SUCCESS��ʧ�ܷ��ش�����
 *  @remarks �ڻص������д����ʱ���������������¼���Ϣ�Ļ�ȡ��\n
             �ýӿ������òɼ���������¼��ص���ͨ�����벻ͬ�������ע�ᡣ
  
 *  @~english
 *  @brief  Register event callback function
 *  @param  hPort                   [IN]            Handle of the object to which the parameter belongs; the object can be either a frame grabber or a device
 *  @param  strEventName            [IN]            Event name
 *  @param  cbEvent                 [IN]            Event callback function
 *  @param  pUser                   [IN]            User-defined data
 *  @return Return MV_FG_SUCCESS on success, and return Error Code on failure.
 *  @remarks Time-consuming operations in the callback function will block the access to the subsequent event information. \n
             This API is applicable to the callback of frame grabber, camera, and stream events. It registers callback functions by passing in different handles.
 ************************************************************************/
MV_FGCTRL_API int __stdcall MV_FG_RegisterEventCallBack(IN PORTHANDLE hPort, IN const char* strEventName, IN MV_FG_EventCallBack cbEvent, IN void* pUser);

/********************************************************************//**
 *  @~chinese
 *  @brief  ע���쳣��Ϣ�ص�����
 *  @param  hPort                   [IN]           �������(����ʹ�òɼ���/������)
 *  @param  cbException             [IN]           �쳣��Ϣ�ص�����
 *  @param  pUser                   [IN]           �û��Զ�������
 *  @return �ɹ�������MV_FG_SUCCESS��ʧ�ܷ��ش�����
 *  @remarks �ڻص������д����ʱ���������������쳣��Ϣ�Ļ�ȡ��\n
             �ýӿ������òɼ���������쳣�ص���ͨ�����벻ͬ�������ע�ᡣ
             Ŀǰ��֧�ֲɼ����ĵ����¼����ɼ�����֧���Ȳ�Σ�������ֵ��ߵ�������ɼ������������Ҫ����PC����ʹ�ã��Ѹ����Ѻ���ʾ��
  
 *  @~english
 *  @brief  Register Exception Information Callback Function
 *  @param  hPort                   [IN]            Handle of the object to which the parameter belongs; the object can be either a frame grabber or a device
 *  @param  cbException             [IN]            Exception information callback function
 *  @param  pUser                   [IN]            User-defined data
 *  @return Return MV_FG_SUCCESS on success, and return Error Code on failure.
 *  @remarks Time-consuming operations in the callback function will block the access to the subsequent exception information. \n
             This API is applicable to the callback of frame grabber and camera exceptions. It registers callback functions by passing in different handles. \n
             Currently, the disconnected event of the frame grabbers is not supported. The frame grabbers do not support hot swap, so disconnected events will not occur. \n
             After the frame grabber is upgraded, you need to restart the PC to use it. A friendly reminder has been given.
 ************************************************************************/
MV_FGCTRL_API int __stdcall MV_FG_RegisterExceptionCallBack(IN PORTHANDLE hPort, IN MV_FG_ExceptionCallBack cbException, IN void* pUser);

#ifdef __cplusplus
}
#endif 

#endif //_MV_FG_CTRL_H_
