#include "stm32l476xx.h"
#include "LCD.h"
#include "SYSTICK.h"

int cnt;

void MSI_Init()
{
	//Enable 4MHz internal clock
	RCC->CR &= ~(RCC_CR_MSION);
	RCC->CR |= (RCC_CR_MSIRANGE_6);
	RCC->CR |= RCC_CR_MSIRGSEL;
	RCC->CR |= (RCC_CR_MSION);
	while ( (RCC->CR & (uint32_t) RCC_CR_MSIRDY) == 0 ) {;}
	return;
}

void EXTI_Init()
{
	//enable SYSCFG
	RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;
	
	//select PA0 as trigger source of EXTI0
	SYSCFG->EXTICR[0] &= ~SYSCFG_EXTICR1_EXTI0;
	SYSCFG->EXTICR[0] |= SYSCFG_EXTICR1_EXTI0_PA;
	SYSCFG->EXTICR[0] &= ~(0x000F);

	//select PA1 as trigger source of EXTI1
	SYSCFG->EXTICR[0] &= ~SYSCFG_EXTICR1_EXTI1;
	SYSCFG->EXTICR[0] |= SYSCFG_EXTICR1_EXTI1_PA;
	SYSCFG->EXTICR[0] &= ~(0x000F);
	
	//select PA2 as trigger source of EXTI2
	SYSCFG->EXTICR[0] &= ~SYSCFG_EXTICR1_EXTI2;
	SYSCFG->EXTICR[0] |= SYSCFG_EXTICR1_EXTI2_PA;
	SYSCFG->EXTICR[0] &= ~(0x000F);
	
	//Enable rising edge trigger for EXTI0
	EXTI->RTSR1 |= EXTI_RTSR1_RT0;
	
	//Enable rising edge trigger for EXTI1
	EXTI->RTSR1 |= EXTI_RTSR1_RT1;
	
	//Enable rising edge trigger for EXTI2
	EXTI->RTSR1 |= EXTI_RTSR1_RT2;
	
	//Disable falling edge trigger for EXTI0
	EXTI->FTSR2 &= ~EXTI_FTSR1_FT0;
	
	//Disable falling edge trigger for EXTI1
	EXTI->FTSR2 &= ~EXTI_FTSR1_FT1;
	
	//Disable falling edge trigger for EXTI2
	EXTI->FTSR2 &= ~EXTI_FTSR1_FT2;
	
	//Enable EXTI0 interrupt
	EXTI->IMR1 |= EXTI_IMR1_IM0;
	
	//Enable EXTI1 interrupt
	EXTI->IMR1 |= EXTI_IMR1_IM1;
	
	//Enable EXTI2 interrupt
	EXTI->IMR1 |= EXTI_IMR1_IM2;
	
	//set EXTI0 priority to 1
	NVIC_SetPriority(EXTI0_IRQn, 1);
	
	//set EXTI1 priority to 1
	NVIC_SetPriority(EXTI1_IRQn, 1);
	
	//set EXTI2 priority to 1
	NVIC_SetPriority(EXTI2_IRQn, 1);
	
	//Enable EXTI0 interrupt
	NVIC_EnableIRQ(EXTI0_IRQn);
	
	//Enable EXTI1 interrupt
	NVIC_EnableIRQ(EXTI1_IRQn);
	
	//Enable EXTI2 interrupt
	NVIC_EnableIRQ(EXTI2_IRQn);
}

void EXTI0_IRQHandler()
{
	if ((EXTI->PR1 & EXTI_PR1_PIF0) == EXTI_PR1_PIF0) {
		LCD_Clear();
		GPIOE->ODR ^= 1<<8;     //toggle PE8
		if(cnt == 0) {
			LCD_DisplayString((uint8_t*)"ON    ");
		}
		if(cnt == 1) {
			LCD_DisplayString((uint8_t*)"OFF   ");
		}
		EXTI->PR1 |= EXTI_PR1_PIF0;  //clear
		cnt++;
		if(cnt > 1) cnt = 0;
	}
}	
void EXTI1_IRQHandler()																//clear interrupt for left/right joystick buttons (don't do anything, but would interrupt if pushed)
{
	if ((EXTI->PR1 & EXTI_PR1_PIF1) == EXTI_PR1_PIF1) {
		EXTI->PR1 |= EXTI_PR1_PIF1;  //clear
	}
}
void EXTI2_IRQHandler()
{
	if ((EXTI->PR1 & EXTI_PR1_PIF2) == EXTI_PR1_PIF2) {
		EXTI->PR1 |= EXTI_PR1_PIF2;  //clear
	}
}
