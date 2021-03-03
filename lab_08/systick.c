#include "SYSTICK.h"
#include "stm32l476xx.h"

volatile uint32_t TimeDelay;

void SysTick_Initialize (uint32_t ticks) {
	SysTick->CTRL = 0;
	SysTick->LOAD = ticks - 1;
	NVIC_SetPriority (SysTick_IRQn, (1<<__NVIC_PRIO_BITS) - 1);
	SysTick->VAL = 0;
	SysTick->CTRL &= ~SysTick_CTRL_CLKSOURCE_Msk;
	SysTick->CTRL |= SysTick_CTRL_TICKINT_Msk;
	SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;
}

void SysTick_Handler (void) {
	if (TimeDelay > 0)
		TimeDelay--;
}

void Delay(uint32_t nTime) {
	TimeDelay = nTime;
	while(TimeDelay != 0);
}

