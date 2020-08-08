#ifndef __SERIAL_H
#define __SERIAL_H

#include "stm32f4xx.h"
#include "usart.h"

#define SERIAL_TX_BUFFER_SIZE 64
#define SERIAL_RX_BUFFER_SIZE 64

typedef struct Serial_s Serial_t;

struct Serial_s
{
    UART_HandleTypeDef* huart;
    IRQn_Type irq;
    uint8_t recv;
    uint8_t rx_buffer[SERIAL_RX_BUFFER_SIZE];
    volatile uint16_t rx_head;
    uint16_t rx_tail;
    uint8_t tx_buffer[SERIAL_TX_BUFFER_SIZE];
    uint16_t tx_head;
    volatile uint16_t tx_tail;
};

extern Serial_t serial1;

void serial_init(Serial_t* _serial, uint32_t baud);
void serial_end(Serial_t* _serial);
int serial_available(Serial_t* _serial);
int serial_peek(Serial_t* _serial);
int serial_read(Serial_t* _serial);
int serial_availableForWrite(Serial_t* _serial);
void serial_flush(Serial_t* _serial);
void serial_write(Serial_t* _serial, uint8_t c);

#endif /* __SERIAL_H */
