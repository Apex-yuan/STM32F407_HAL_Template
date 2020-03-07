#include "delay.h"

/**
 * 如果用SYSTICK实现微秒延时函数没有必要执行该函数
 * 如果用DWT实现微秒延时函数必须执行dwt_init()函数
 */
void delay_init(void)
{
    #if defined(DWT_BASE) && !defined(DWT_DELAY_DISABLED)
    dwt_init();
    #endif
}




