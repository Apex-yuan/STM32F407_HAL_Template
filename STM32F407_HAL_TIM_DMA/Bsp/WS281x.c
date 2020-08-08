#include "WS281x.h"
#include <string.h>

#ifndef PIXEL_NUM
  #define PIXEL_NUM 5
#endif
#define GRB (3*8)

#define WS_TERO 30
#define WS_ONE  45

/* pwm 占空比数值为uint16_t 类型，DMA传输时只能以半字输出，pixelBuffer应为uint16_t 类型 */
uint16_t pixelBuffer[PIXEL_NUM][GRB]; 

void ws281x_init(void)
{
  /* 配置TIM3 pwm频率为800Khz */
  tim3_init();
}

void ws281x_show(void)
{
  HAL_TIM_PWM_Start_DMA(&htim3, TIM_CHANNEL_1, (uint32_t *)pixelBuffer, PIXEL_NUM * GRB);
}

uint32_t ws281x_color(uint8_t r, uint8_t g, uint8_t b)
{
  return (uint32_t)(g << 16 | r << 8 | b);
}

/* pixel num from 0 start */
void ws281x_setColor(uint16_t n, uint32_t color)
{
  if(n < PIXEL_NUM)
  {
    for(uint8_t i = 0; i < GRB; ++i)
    {
      pixelBuffer[n][i] = ((color << i) & 0x800000) ? WS_ONE : WS_TERO;
    }
  }
}

void ws281x_close(void)
{
  uint16_t* ptr = (uint16_t *)pixelBuffer; 
  for(uint16_t i = 0; i < PIXEL_NUM * GRB; ++i)
  {
    *ptr++ = WS_TERO;
  }
  ws281x_show();
}

/* 中断回调函数，在设定的pwm通过DMA发送完成后会调用 */
void HAL_TIM_PWM_PulseFinishedCallback(TIM_HandleTypeDef* htim)
{
  __HAL_TIM_SetCompare(htim, TIM_CHANNEL_1, 0); //占空比清0，若不清会导致灯珠颜色不对 
  HAL_TIM_PWM_Stop_DMA(htim, TIM_CHANNEL_1);
}

uint32_t WS281x_Wheel(uint8_t wheelPos) {
  wheelPos = 255 - wheelPos;
  if(wheelPos < 85) {
    return ws281x_color(255 - wheelPos * 3, 0, wheelPos * 3);
  }
  if(wheelPos < 170) {
    wheelPos -= 85;
    return ws281x_color(0, wheelPos * 3, 255 - wheelPos * 3);
  }
  wheelPos -= 170;
  return ws281x_color(wheelPos * 3, 255 - wheelPos * 3, 0);
}

void WS281x_Rainbow(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256; j++) {
    for(i=0; i<PIXEL_NUM; i++) {
      ws281x_setColor(i, WS281x_Wheel((i+j) & 255));
    }
    ws281x_show();
    HAL_Delay(wait);
  }
}
