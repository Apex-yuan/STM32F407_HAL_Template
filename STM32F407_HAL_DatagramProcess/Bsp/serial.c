#include "serial.h"

Serial_t serial1;

void serial_init(Serial_t* _serial, uint32_t baud)
{
  /* clear buffer */
  _serial->rx_head = 0;
  _serial->rx_tail = 0;
  _serial->tx_head = 0;
  _serial->tx_tail = 0;

  if(&serial1 == _serial)
  {
    serial1.huart = &uartHandle1;
    serial1.irq = USART1_IRQn;
  }
  else
  {
    /* error handle */
  }
  uart_init(_serial->huart, baud);
  /* 使能串口接收中断 */
  HAL_UART_Receive_IT(_serial->huart, &_serial->recv, 1);
}

void serial_end(Serial_t* _serial)
{
  serial_flush(_serial);
  uart_deinit(_serial->huart);
}

int serial_available(Serial_t* _serial)
{
  return (SERIAL_RX_BUFFER_SIZE + _serial->rx_head - _serial->rx_tail) & (SERIAL_RX_BUFFER_SIZE - 1); 
}

int serial_peek(Serial_t* _serial)
{
  if(_serial->rx_head == _serial->rx_tail)
  {
    return -1;
  }
  else
  {
    return _serial->rx_buffer[_serial->rx_tail];    
  }
}

int serial_read(Serial_t* _serial)
{
  if(_serial->rx_head == _serial->rx_tail)
  {
    return -1;
  }
  else
  {
    uint8_t c = _serial->rx_buffer[_serial->rx_tail];
    _serial->rx_tail = (_serial->rx_tail + 1) &  (SERIAL_RX_BUFFER_SIZE - 1);
    return c;
  }
}

int serial_availableForWrite(Serial_t* _serial)
{
  return (SERIAL_TX_BUFFER_SIZE + _serial->tx_tail - _serial->tx_head - 1) & (SERIAL_TX_BUFFER_SIZE - 1);
}

void serial_flush(Serial_t* _serial)
{
  while(_serial->tx_tail != _serial->tx_head)
  {
    //等待中断将所有的数据发送出去
  }
}

void serial_write(Serial_t* _serial, uint8_t c)
{
  uint16_t i = (_serial->tx_head + 1) & (SERIAL_TX_BUFFER_SIZE - 1);

  while(_serial->tx_tail == i)
  {
    //发送缓冲满了，等待缓冲区有空间
  }

  _serial->tx_buffer[_serial->tx_head] = c;
  _serial->tx_head = i;

  HAL_NVIC_DisableIRQ(_serial->irq);
  HAL_UART_Transmit_IT(_serial->huart,&_serial->tx_buffer[_serial->tx_tail], 1);
  HAL_NVIC_EnableIRQ(_serial->irq);
}

/* 中断回调函数 */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef* huart)
{
  if(serial1.huart == huart)
  {
    uint16_t i = (serial1.rx_head + 1) & (SERIAL_RX_BUFFER_SIZE - 1);
    if(serial1.rx_tail != i)
    {
      serial1.rx_buffer[serial1.rx_head] = serial1.recv;
      serial1.rx_head = i;
    }
    /* 开启下次接收中断 */
    HAL_UART_Receive_IT(huart, &serial1.recv, 1);
  }
  else
  {
    /* 错误处理 */
  }
}

void HAL_UART_TxCpltCallback(UART_HandleTypeDef* huart)
{
  if(serial1.huart == huart)
  {
    serial1.tx_tail = (serial1.tx_tail + 1) & (SERIAL_TX_BUFFER_SIZE - 1);
    if(serial1.tx_tail == serial1.tx_head)
    {
      return;
    }
    HAL_UART_Transmit_IT(huart, &serial1.tx_buffer[serial1.tx_tail], 1);
  }
}
