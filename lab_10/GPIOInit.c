#include "stm32l476xx.h"
#include "GPIOInit.h"

void GPIOInit()
{
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOBEN;      //enable clock for GPIOB
	GPIOB->MODER &= ~GPIO_MODER_MODE2;				//red LED for output
	GPIOB->MODER |= GPIO_MODER_MODE2_0;
	GPIOB->PUPDR &= ~GPIO_PUPDR_PUPD2;				//push pull
	
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOAEN;      //enable clock for GPIOA
	GPIOA->MODER &= ~GPIO_MODER_MODE1;				//set mode to analog
	GPIOA->MODER |= GPIO_MODER_MODE1;
	GPIOA->ASCR |= GPIO_ASCR_ASC1;						//set bit 1 to close analog switch
	
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOEEN;      //enable clock for GPIOE
	GPIOE->MODER &= ~GPIO_MODER_MODE8;					//green	LED for output
	GPIOE->MODER |= GPIO_MODER_MODE8_0;
}
