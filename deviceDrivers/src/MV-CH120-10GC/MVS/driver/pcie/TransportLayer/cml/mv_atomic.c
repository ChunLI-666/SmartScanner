/***************************************************************************************************
* 
* ��Ȩ��Ϣ����Ȩ���� (c) 2014, ���ݺ����������ּ����ɷ����޹�˾, ��������Ȩ��
* 
* �ļ����ƣ�atomic.c
* ժ    Ҫ��ԭ�ӱ�����غ���
*
* ��ǰ�汾��3.1.0
* ��    �ߣ�����Ԫ
* ��    �ڣ�2019-07-25
* ��    ע��
***************************************************************************************************/


#include <linux/kernel.h>
#include <linux/vmalloc.h>
#include <linux/slab.h>
#include <linux/version.h>


#include "mv_atomic.h"
#include "MvErrorDefine.h"
#include <asm/atomic.h>
#include <asm-generic/errno.h>
#include <asm-generic/errno-base.h>


int MV_AtomicInit(MV_ATOMIC* aAtomic)
{
    atomic_t* lAtomic = NULL;

    if (NULL == aAtomic)
    {
        return -EINVAL;
    }

    aAtomic->pAtomic = kmalloc(sizeof(atomic_t), GFP_KERNEL);
    if (NULL == aAtomic->pAtomic)
    {
        return -ENOMEM;
    }

    lAtomic = (atomic_t *)(aAtomic->pAtomic);

    *lAtomic = (atomic_t)ATOMIC_INIT(0);

    return MV_OK;
}

int MV_AtomicFree(MV_ATOMIC* aAtomic)
{
    if (NULL == aAtomic)
    {
        return -EINVAL;
    }

    if (NULL != aAtomic->pAtomic)
    {
        kfree(aAtomic->pAtomic);
        aAtomic->pAtomic = NULL;
    }

    return MV_OK;
}

int MV_AtomicSet(MV_ATOMIC* aAtomic, int i)
{
    atomic_t* lAtomic = NULL;

    if (NULL == aAtomic)
    {
        return -EINVAL;
    }
    lAtomic = (atomic_t *)(aAtomic->pAtomic);

    atomic_set(lAtomic, i);

    return MV_OK;
}

int MV_AtomicGet(MV_ATOMIC* aAtomic, int* i)
{
    atomic_t* lAtomic = NULL;

    if ((NULL == aAtomic) || (NULL == i))
    {
        return -EINVAL;
    }

    lAtomic = (atomic_t *)(aAtomic->pAtomic);

    *i = atomic_read(lAtomic);

    return MV_OK;
}

int MV_AtomicAdd(MV_ATOMIC* aAtomic, int i)
{
    atomic_t* lAtomic = NULL;

    if (NULL == aAtomic)
    {
        return -EINVAL;
    }
    lAtomic = (atomic_t *)(aAtomic->pAtomic);

    atomic_add(i, lAtomic);

    return MV_OK;
}

int MV_AtomicSub(MV_ATOMIC* aAtomic, int i)
{
    atomic_t* lAtomic = NULL;

    if (NULL == aAtomic)
    {
        return -EINVAL;
    }
    lAtomic = (atomic_t *)(aAtomic->pAtomic);

    atomic_sub(i, lAtomic);

    return MV_OK;
}

int MV_AtomicInc(MV_ATOMIC* aAtomic)
{
    atomic_t* lAtomic = NULL;

    if (NULL == aAtomic)
    {
        return -EINVAL;
    }
    lAtomic = (atomic_t *)(aAtomic->pAtomic);

    atomic_inc(lAtomic);

    return MV_OK;
}

int MV_AtomicDec(MV_ATOMIC* aAtomic)
{
    atomic_t* lAtomic = NULL;

    if (NULL == aAtomic)
    {
        return -EINVAL;
    }
    lAtomic = (atomic_t *)(aAtomic->pAtomic);

    atomic_dec(lAtomic);

    return MV_OK;
}

