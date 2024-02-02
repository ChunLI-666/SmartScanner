
#include <linux/time.h>
#include <linux/timex.h>
#include <linux/version.h>
#include <linux/delay.h>
#include <linux/math64.h>

#if LINUX_VERSION_CODE >= KERNEL_VERSION(5,0,0)
#include <linux/efi.h>
#else
#include <linux/rtc.h>
#endif

#include "mv_time.h"

/** 
 * @fn		void MV_MSleep(unsigned int msecs)
 * @brief	˯��ʱ�亯��
 * @param	msecs: ˯�ߵĺ�����
 * @return	��
 */ 
void MV_MSleep(unsigned int msecs)
{
    msleep(msecs);
}

/** 
 * @fn		void MV_MSleepInterruptible(unsigned int msecs)
 * @brief	���жϵ�˯��ʱ�亯��
 * @param	msecs: ˯�ߵĺ�����
 * @return	��
 */ 
void MV_MSleepInterruptible(unsigned int msecs)
{
    msleep_interruptible(msecs);
}

/*******************************************************************************
@   ����ԭ�ͣ�TM_RtcTime TM_GetCurrentTime(void)
@   �������ܣ���ȡ����ʱ��
@   ������ ��
@   ����ֵ������ʱ��
*******************************************************************************/
MV_TM_RtcTime TM_GetCurrentTime(void)
{
    struct rtc_time tm         = { 0 };
    MV_TM_RtcTime aCurrentTime = { 0 };

#if LINUX_VERSION_CODE >= KERNEL_VERSION(5,0,0)
    struct timespec64 txc = { 0 };

    /* ��ȡ��ǰ��UTCʱ�� */
    ktime_get_real_ts64(&txc);

    /* ��UTCʱ�����Ϊ����ʱ�� */
    txc.tv_sec -= sys_tz.tz_minuteswest * 60;
    /* ���ʱ���е������յ���ֵ��tm�� */
    rtc_time64_to_tm(txc.tv_sec,&tm);

#else
    struct timex  txc = { 0 };
    /* ��ȡ��ǰ��UTCʱ�� */
    do_gettimeofday(&(txc.time));

    /* ��UTCʱ�����Ϊ����ʱ�� */
    txc.time.tv_sec -= sys_tz.tz_minuteswest * 60;
    /* ���ʱ���е������յ���ֵ��tm�� */
    rtc_time_to_tm(txc.time.tv_sec,&tm);
#endif
    tm.tm_year = tm.tm_year + 1900;
    tm.tm_mon = tm.tm_mon + 1;

    aCurrentTime = *((MV_TM_RtcTime*)&tm);

    return aCurrentTime;
}



/*******************************************************************************
@   ����ԭ�ͣ�unsigned long TM_GetTickCount(void)
@   �������ܣ����ϵͳ��ǰʱ��ĺ�����
@   ������ ��
@   ����ֵ��ϵͳ��ǰʱ��ĺ�����
*******************************************************************************/
unsigned long long TM_GetTickCount(void)
{
    unsigned long long msce = 0;
#if LINUX_VERSION_CODE >= KERNEL_VERSION(5,0,0)
    struct timespec64 txc = { 0 };
    unsigned long long tv_sec = 0;
    unsigned long long tv_nsec = 0;
    /* ��ȡ��ǰ��UTCʱ�� */
    ktime_get_real_ts64(&txc);
    tv_sec = (unsigned long long)(txc.tv_sec);
    tv_nsec = (unsigned long long)(txc.tv_nsec);
    msce = txc.tv_sec * 1000 + div_u64(tv_nsec, 1000000);
#else
    struct  timeval   tv;
    unsigned long long tv_sec = 0;
    unsigned long long tv_usec = 0;
    do_gettimeofday(&tv);
    tv_sec = (unsigned long long)(tv.tv_sec);
    tv_usec = (unsigned long long)(tv.tv_usec);
    msce = tv_sec * 1000 + div_u64(tv_usec, 1000);
#endif
    return  msce;
}

