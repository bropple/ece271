#include "stm32l476xx.h"
#include "LCD.h"
#include "SYSTICK.h"
#include "EXTI.h"

/*
 *Ben Ropple
 *4/29/2018
 *Clock speed 4MHZ
 *Bonus Lab 8 - External Interrupt (Push Button)
 */


int main(void){
	MSI_Init();
  // Enable clock for GPIO Ports, A, E, and B
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOEEN;
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOAEN;
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOBEN;
	// MODE: 00: Input mode               01: General purpose output mode
  //       10: Alternate function mode  11: Reset
	GPIOE->MODER &= ~(GPIO_MODER_MODER8);
	GPIOE->MODER |= (GPIO_MODER_MODER8_0); 
	GPIOA->MODER &= ~(0x0CFF);
	GPIOB->MODER &= ~(GPIO_MODER_MODE2);
	GPIOB->MODER |= GPIO_MODER_MODE2_0;
	// PUPDR:00: Reset    01: Pull-up
  //       10: Pull-down 11: Reserved
	GPIOA->PUPDR &= ~(0x00000CFF);
	GPIOA->PUPDR |= 0x000008AA;
	
	LCD_Clock_Init();
	LCD_Initialization();
	LCD_Clear();
	sysTick_Initialize(999); //lower number means faster red LED toggle
	
	LCD_DisplayString((uint8_t*)"OFF   ");
	
	EXTI_Init();
	while (1) {
		GPIOB->ODR ^= GPIO_ODR_OD2;  //toggles red LED
		DelayTime(250);
	}
}
