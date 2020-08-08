#include "usart.h"

UART_HandleTypeDef uartHandle1;

void uart_init(UART_HandleTypeDef* uartHandle, uint32_t baud)
{
  if(&uartHandle1 == uartHandle)
  {
    uartHandle->Instance = USART1;
    uartHandle->Init.BaudRate = baud;
    uartHandle->Init.StopBits = UART_STOPBITS_1;
    uartHandle->Init.WordLength = UART_WORDLENGTH_8B;
    uartHandle->Init.Parity = UART_PARITY_NONE;
    uartHandle->Init.Mode = UART_MODE_TX_RX;
    uartHandle->Init.HwFlowCtl = UART_HWCONTROL_NONE;
    HAL_UART_Init(uartHandle);
  }
}

void uart_deinit(UART_HandleTypeDef* uartHandle)
{
  HAL_UART_MspDeInit(uartHandle);
}

void HAL_UART_MspInit(UART_HandleTypeDef* uartHandle)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  
  if(uartHandle->Instance == USART1)
  {
    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_USART1_CLK_ENABLE();
    
    /*
    PA9  ---> USART1_TX
    PA10 ---> USART1_RX
     */
    GPIO_InitStruct.Pin = GPIO_PIN_9 | GPIO_PIN_10;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF7_USART1;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
    
    HAL_NVIC_SetPriority(USART1_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(USART1_IRQn);
    
  }
}

void HAL_UART_MspDeInit(UART_HandleTypeDef* uartHandle)
{
  if(uartHandle->Instance == USART1)
  {
    __HAL_RCC_USART1_CLK_DISABLE();
    
    HAL_GPIO_DeInit(GPIOA, GPIO_PIN_9 | GPIO_PIN_10);
    
    HAL_NVIC_DisableIRQ(USART1_IRQn);
  }
}

/* 中断服务函数 */
void USART1_IRQHandler(void)
{
  HAL_UART_IRQHandler(&uartHandle1);
}
