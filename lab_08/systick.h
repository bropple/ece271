#ifndef __STM32L476G_DISCOVERY_SYSTICK_H
#define __STM32L476G_DISCOVERY_SYSTICK_H

#include <stdint.h>


void SysTick_Initialize (uint32_t ticks);
void Delay(uint32_t nTime);
void SysTick_Handler(void);

#endif /* __STM32L476G_DISCOVERY_LCD_H */
