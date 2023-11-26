#ifndef _MV_FG_ERROR_DEFINE_H_
#define _MV_FG_ERROR_DEFINE_H_

typedef int MV_FG_ERROR;

/********************************************************************/
///  \~chinese
///  \name ��ȷ�붨��
///  @{
///  \~english
///  \name Definition of correct code
///  @{
#define    MV_FG_SUCCESS                  0          ///< \~chinese �ɹ����޴���             \~english Successed, no error
/// @}

/********************************************************************/
///  \~chinese
///  \name SDK����:��Χ0x80190001-0x801900FF
///  @{
///  \~english
///  \name SDK Error Codes: Range from 0x80190001-0x801900FF
///  @{
#define    MV_FG_ERR_ERROR                0x80190001    ///< \~chinese δ֪�Ĵ���                                                             \~english Unknown error
#define    MV_FG_ERR_NOT_INITIALIZED      0x80190002    ///< \~chinese ģ�����Դδ��ʼ��                                                   \~english Uninitialized
#define    MV_FG_ERR_NOT_IMPLEMENTED      0x80190003    ///< \~chinese ����δʵ��                                                           \~english Not implemented
#define    MV_FG_ERR_RESOURCE_IN_USE      0x80190004    ///< \~chinese �������Դ����ʹ����                                                 \~english Resource occupied
#define    MV_FG_ERR_ACCESS_DENIED        0x80190005    ///< \~chinese ����Ĳ�����Ȩ��ִ��;����,������ָ�ɼ���������Ѿ����������̴���        \~english No permission
#define    MV_FG_ERR_INVALID_HANDLE       0x80190006    ///< \~chinese ��Ч�ľ��;����,������ָʹ���˴���ľ�����߿�ָ����                     \~english Invalid handle
#define    MV_FG_ERR_INVALID_ID           0x80190007    ///< \~chinese ��Ч��ID                                                             \~english Invalid ID
#define    MV_FG_ERR_NO_DATA              0x80190008    ///< \~chinese û�п��Բ���������                                                         \~english No data
#define    MV_FG_ERR_INVALID_PARAMETER    0x80190009    ///< \~chinese ��Ч�Ĳ���                                                               \~english Invalid parameter
#define    MV_FG_ERR_IO                   0x80190010    ///< \~chinese IO����                                                                   \~english IO error
#define    MV_FG_ERR_TIMEOUT              0x80190011    ///< \~chinese ������ʱ;����,������ָ�ڻ�ȡͼ��Ľӿ�,���õĳ�ʱʱ��̫С,�����ڳ�ʱʱ����δ�ܻ�ȡ��ͼ������   \~english Timeout
#define    MV_FG_ERR_ABORT                0x80190012    ///< \~chinese ���������֮ǰ����ֹ                                                        \~english The operation was interrupted
#define    MV_FG_ERR_INVALID_BUFFER       0x80190013    ///< \~chinese ��Ч�Ļ�������޻���                                                     \~english Invalid buffer
#define    MV_FG_ERR_NOT_AVAILABLE        0x80190014    ///< \~chinese �ڵ�ǰ״̬�£��������Դ����Ϣ������                                    \~english Unreachable
#define    MV_FG_ERR_INVALID_ADDRESS      0x80190015    ///< \~chinese ��ַ��Ч�򳬹���Χ                                                       \~english Invalid address
#define    MV_FG_ERR_BUFFER_TOO_SMALL     0x80190016    ///< \~chinese ����̫С                                                                 \~english Buffer too small
#define    MV_FG_ERR_INVALID_INDEX        0x80190017    ///< \~chinese ��Ч������                                                                 \~english Invalid index
#define    MV_FG_ERR_PARSING_CHUNK_DATA   0x80190018    ///< \~chinese ����Chunkʧ��                                                            \~english Failed to parse Chunk
#define    MV_FG_ERR_INVALID_VALUE        0x80190019    ///< \~chinese ��Ч��ֵ                                                                 \~english Invalid value
#define    MV_FG_ERR_RESOURCE_EXHAUSTED   0x80190020    ///< \~chinese ϵͳ��Դ�ľ�;����,������ָ�����ļ���������ﵽ���ޡ�                         \~english Resource exhaustion
#define    MV_FG_ERR_OUT_OF_MEMORY        0x80190021    ///< \~chinese �ڴ�����ʧ��;����,������ָϵͳ��ϵͳ�е�����Ӳ�����ɼ������е��ڴ治�㡣     \~english Applying memory failed
#define    MV_FG_ERR_BUSY                 0x80190022    ///< \~chinese �������������ģ�飬��ʱ����ִ�������������޷�������Ĳ���ͬʱִ�С�             \~english Be busy
#define    MV_FG_ERR_LOADLIBRARY          0x80190023    ///< \~chinese ��̬�����ʧ��                                                           \~english Dynamic library loading failed
#define    MV_FG_ERR_CALLORDER            0x80190024    ///< \~chinese �������ô���                                                             \~english The order of function calls is wrong
#define    MV_FG_ERR_VERSION              0x80190025    ///< \~chinese �汾��ƥ��                                                             \~english Version not matched
/// @}

/********************************************************************/
///  \~chinese
///  \name GenICamϵ�д���:��Χ0x80190100-0x801901FF
///  @{
///  \~english
///  \name GenICam Series Error Codes: Range from 0x80190100-0x801901FF
///  @{
#define    MV_FG_ERR_GC_GENERIC             0x80190100  ///< \~chinese ͨ�ô���         \~english General error
#define    MV_FG_ERR_GC_ARGUMENT            0x80190101  ///< \~chinese ��Ч�Ĳ���       \~english Illegal parameters
#define    MV_FG_ERR_GC_RANGE               0x80190102  ///< \~chinese ������Χ����     \~english The value is out of range
#define    MV_FG_ERR_GC_PROPERTY            0x80190103  ///< \~chinese ���Դ���         \~english Property error
#define    MV_FG_ERR_GC_RUNTIME             0x80190104  ///< \~chinese ���л�������     \~english Running environment error
#define    MV_FG_ERR_GC_LOGICAL             0x80190105  ///< \~chinese �߼�����         \~english Logical error
#define    MV_FG_ERR_GC_ACCESS              0x80190106  ///< \~chinese Ȩ�޴���         \~english Accessing condition error
#define    MV_FG_ERR_GC_TIMEOUT             0x80190107  ///< \~chinese ��ʱ             \~english Timeout
#define    MV_FG_ERR_GC_DYNAMICCAST         0x80190108  ///< \~chinese ת���쳣         \~english Transformation exception
#define    MV_FG_ERR_GC_UNKNOW              0x801901FF  ///< \~chinese δ֪����         \~english Unknown error
/// @}

/********************************************************************/
///  \~chinese
///  \name ͼ�������:��Χ0x80190200-0x801902FF
///  @{
///  \~english
///  \name Image Process Error Codes: Range from 0x80190200-0x801902FF
///  @{
#define    MV_FG_ERR_IMG_HANDLE           0x80190200    ///< \~chinese ͼ�����������             \~english Handle error
#define    MV_FG_ERR_IMG_SUPPORT          0x80190201    ///< \~chinese ͼ����ⲻ֧��               \~english Not supported
#define    MV_FG_ERR_IMG_PARAMETER        0x80190202    ///< \~chinese ͼ������������             \~english Parameter error
#define    MV_FG_ERR_IMG_OVERFLOW         0x80190203    ///< \~chinese ͼ������ڴ����             \~english Out of memory
#define    MV_FG_ERR_IMG_INITIALIZED      0x80190204    ///< \~chinese ͼ��������δ��ʼ��         \~english Uninitialized
#define    MV_FG_ERR_IMG_RESOURCE         0x80190205    ///< \~chinese ͼ�������Դ�����ͷ�ʧ��     \~english Resource release failed
#define    MV_FG_ERR_IMG_ENCRYPT          0x80190206    ///< \~chinese ͼ����ܴ���                   \~english Encryption error
#define    MV_FG_ERR_IMG_FORMAT           0x80190207    ///< \~chinese ͼ���ʽ����ȷ���߲�֧��       \~english Incorrect format or unsupported
#define    MV_FG_ERR_IMG_SIZE             0x80190208    ///< \~chinese ͼ���߲���ȷ���߳�����Χ     \~english Incorrect width and height or out of range
#define    MV_FG_ERR_IMG_STEP             0x80190209    ///< \~chinese ͼ������step������ƥ��       \~english Width and height do not match step parameters
#define    MV_FG_ERR_IMG_DATA_NULL        0x80190210    ///< \~chinese ͼ�����ݴ洢��ַΪ��(ĳ������) \~english Data storage address is empty (a component)
#define    MV_FG_ERR_IMG_ABILITY_ARG      0x80190211    ///< \~chinese ͼ���㷨ABILITY������Ч����    \~english Invalid parameter for algorithm ABILITY
#define    MV_FG_ERR_IMG_UNKNOW           0x801902FF    ///< \~chinese ͼ����δ֪����               \~english Unknown error
/// @}

#endif //_MV_FG_ERROR_DEFINE_H_
