#ifndef __USART_H
#define __USART_H

#include "stm32f4xx.h"

extern UART_HandleTypeDef uartHandle1;

void uart_init(UART_HandleTypeDef* uartHandle, uint32_t baud);
void uart_deinit(UART_HandleTypeDef* uartHandle);

#endif /* __USART_H */

