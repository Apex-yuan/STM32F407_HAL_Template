#ifndef __WS281X_H
#define __WS281x_H

#include "tim.h"

void ws281x_init(void);
void ws281x_show(void);
uint32_t ws281x_color(uint8_t r, uint8_t g, uint8_t b);
void ws281x_setColor(uint16_t n, uint32_t color);
void ws281x_close(void);
void WS281x_Rainbow(uint8_t wait);

#endif /* __WS281X_H */

