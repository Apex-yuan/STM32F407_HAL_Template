#include <stdio.h>
#include "serial.h"

/* 通过重定向实现printf函数 */

#if !defined(__MICROLIB)
#pragma import(__use_no_semihosting)
void _sys_exit(int x)
{
  x = x;
}
struct __FILE
{
  int handle;
};
FILE __stdout;
#endif

#ifdef __GNUC__
#define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif 
PUTCHAR_PROTOTYPE
{
//HAL_UART_Transmit(&huart2 , (uint8_t *)&ch, 1, 0xFFFF);
  serial_write(&serial1, (uint8_t)ch);
return ch;
}

/* 用于实现自己的printf函数的原型 */
//#include <stdarg.h>
//#include <string.h> 
//#include <stdio.h>
//void serial2_printf( const char * format, ... )
//{
//  char buffer[256];
//  va_list args;
//  va_start (args, format);
//  vsprintf (buffer,format, args);
//  //send_via_USART1 (buffer);
//  uint8_t len = strlen((const char*)buffer);
//  for(uint8_t i = 0; i < len; ++i)
//  {
//    serial_write(&serial2, (uint8_t)buffer[i]);
//  }
//  va_end (args);
//}

