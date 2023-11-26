
#include <linux/kernel.h>
#include <linux/delay.h>
#include <asm/current.h>
#include <linux/mm.h>
#include <linux/sched.h>
#include "mv_misc.h"


/*******************************************************************************
@   ����ԭ�ͣ�void MV_Printk(int res)
@   �������ܣ���ӡ����
@   ����res�� ��ӡֵ
@   ����ֵ����
*******************************************************************************/
void MV_Printk(const char* aFormat, ...)
{
    return;

    va_list lArgs;

    va_start(lArgs, aFormat);
    vprintk(aFormat, lArgs);
    va_end(lArgs);
}

/*******************************************************************************
@   ����ԭ�ͣ�void MV_Mdelay(int nMSec)
@   �������ܣ�ʱ��ȴ�����
@   ����nMSec�� �ȴ��ĺ�����
@   ����ֵ��
*******************************************************************************/
void MV_Mdelay(int nMSec)
{
    mdelay(nMSec);
}

void* MV_GetCurrent(void)
{
    return (void*)current;
}


void* MV_GetCurrentMm(void)
{
    return (void*)current->mm;
}
