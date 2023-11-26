
#ifndef     __MEMORY_H__
#define     __MEMORY_H__

typedef struct _MV_MEMORYPAGELIST_
{
    unsigned long  PageCount;       // page������
    void**         PageList;        // page���б�ָ��
    unsigned long  OffsetPage;      // Buf���׸�page�е�ƫ����
    void*          KernelAddress;   // �ں�̬�е��߼���ַ
    void*          UserAddress;     // �û�̬�е��߼���ַ
    unsigned int   Size;            // Buf���ܴ�С
    unsigned long  hMm;              // ���������ڴ�ռ�
} MV_MEMORYPAGELIST;


#ifdef __cplusplus
extern "C"
{
#endif 

//#include "misc.h"

typedef struct __TEST__
{
    int a;
    int b;
}MV_TEST;

extern void* MV_KMalloc(int aSize);
extern void* MV_KMallocAtomic(int aSize);
extern void  MV_KFree( void* aAddress );
extern void* MV_VMalloc(int aSize);
extern void  MV_VFree(void* aAddress);
extern void  MV_Memset(void* aAddress, unsigned int aValue, int aSize);
extern void  MV_Memcpy(void* aDestination, const void* aSource, int aSize);
extern unsigned int  MV_MemcpyToUser( void* aTo, const void* aFrom, int aSize );
extern unsigned int  MV_MemcpyFromUser(void* aTo, const void* aFrom, int aSize );
extern unsigned int  test(MV_TEST myTest, int e);
extern int MV_MallocPages(MV_MEMORYPAGELIST* pPageList, unsigned int nSize);
extern int MV_FreePages(MV_MEMORYPAGELIST* pPageList);
extern unsigned int MV_GetVmaSize(void* vma);

#ifdef __cplusplus
}
#endif 


#endif		//	__MEMORY_H__

