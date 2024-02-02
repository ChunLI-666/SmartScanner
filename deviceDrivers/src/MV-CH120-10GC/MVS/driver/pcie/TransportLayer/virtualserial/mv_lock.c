
#include <linux/kernel.h>
#include <linux/spinlock.h>
#include <linux/slab.h>
#include <linux/vmalloc.h>
#include <linux/version.h>

#include "mv_lock.h"
#include "MvErrorDefine.h"
#include <asm-generic/errno.h>
#include <asm-generic/errno-base.h>

/*******************************************************************************
@   ����ԭ�ͣ�int MV_LockCheck(void)
@   �������ܣ�������������֤
@   ������ ��
@   ����ֵ���ɹ�MV_OK ʧ��MV_E_PARAMETER
*******************************************************************************/
int MV_LockCheck(void)
{
    //if(MV_SPINLOCK_SIZE < sizeof(spinlock_t))
    //{
    //    printk("spinlock_t size = %d / %d\n", (int)sizeof(spinlock_t), (int)MV_SPINLOCK_SIZE);
    //    printk("Lock not compatible with your distribution\n");
    //    return MV_E_PARAMETER;
    //}

    return MV_OK;
}

/*******************************************************************************
@   ����ԭ�ͣ�int MV_LockInit(MV_LOCK* aLock)
@   �������ܣ���������ʼ��
@   ����aLock�� ������
@   ����ֵ���ɹ�MV_OK ʧ��MV_E_PARAMETER
*******************************************************************************/
int MV_LockInit(MV_LOCK* aLock)
{
    spinlock_t* lSpinlock = NULL;

    if(NULL == aLock)
    {
        return -EINVAL;
    }

    aLock->pSpinLock = kmalloc(sizeof(spinlock_t), GFP_KERNEL);
    if (NULL == aLock->pSpinLock)
    {
        return -ENOMEM;
    }
    
    lSpinlock = (spinlock_t *)(aLock->pSpinLock);

    spin_lock_init(lSpinlock);

    return MV_OK;
} 

int MV_LockFree(MV_LOCK* aLock)
{
    if (aLock == NULL)
    {
        return -EINVAL;
    }

    if (NULL != aLock->pSpinLock)
    {
        kfree((spinlock_t *)aLock->pSpinLock);
        aLock->pSpinLock = NULL;
    }

    return MV_OK;
}

/*******************************************************************************
@   ����ԭ�ͣ�int MV_LockAcquire(MV_LOCK* aLock, unsigned long *aFlag)
@   �������ܣ�����������
@   ����aLock�� ������
@   ����aFlag�� �жϱ�־
@   ����ֵ���ɹ�MV_OK ʧ��MV_E_PARAMETER
*******************************************************************************/
int MV_LockAcquire(MV_LOCK* aLock)
{
    spinlock_t* lSpinlock = NULL;

    if(NULL == aLock)
    {
        return -EINVAL;
    }

    lSpinlock = (spinlock_t *)(aLock->pSpinLock);

    spin_lock( lSpinlock );

    return MV_OK;
}

int MV_LockIrqAcquire(MV_LOCK* aLock)
{
    spinlock_t* lSpinlock = NULL;
    if(NULL == aLock)
    {
        return -EINVAL;
    }
    lSpinlock = (spinlock_t *)(aLock->pSpinLock);

    spin_lock_irq( lSpinlock);

    return MV_OK;
}

int MV_LockBhAcquire(MV_LOCK* aLock)
{
    spinlock_t* lSpinlock = NULL;

    if(NULL == aLock)
    {
        return -EINVAL;
    }
    lSpinlock = (spinlock_t *)(aLock->pSpinLock);

    spin_lock_bh( lSpinlock);

    return MV_OK;
}


/*******************************************************************************
@   ����ԭ�ͣ�int MV_LockRelease(MV_LOCK* aLock, unsigned long *aFlag)
@   �������ܣ�����������
@   ����aLock�� ������
@   ����aFlag�� �жϱ�־
@   ����ֵ���ɹ�MV_OK ʧ��MV_E_PARAMETER
*******************************************************************************/
int MV_LockRelease(MV_LOCK* aLock)
{
    spinlock_t* lSpinlock = NULL;

    if(NULL == aLock)
    {
        return -EINVAL;
    }
    lSpinlock = (spinlock_t *)(aLock->pSpinLock);

    spin_unlock( lSpinlock );

    return MV_OK;
}

int MV_LockIrqRelease(MV_LOCK* aLock)
{
    spinlock_t* lSpinlock = NULL;

    if(NULL == aLock)
    {
        return -EINVAL;
    }
    lSpinlock = (spinlock_t *)(aLock->pSpinLock);

    spin_unlock_irq( lSpinlock );

    return MV_OK;
}

int MV_LockBhRelease(MV_LOCK* aLock)
{
    spinlock_t* lSpinlock = NULL;

    if(NULL == aLock)
    {
        return -EINVAL;
    }
    lSpinlock = (spinlock_t *)(aLock->pSpinLock);

    spin_unlock_bh( lSpinlock );

    return MV_OK;
}

