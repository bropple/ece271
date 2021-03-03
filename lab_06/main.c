#include "stm32l476xx.h"
#include "LCD.h"
#include <stdio.h>

/* Ben Ropple
	 3/15/2018
	 Systick Lab
	 Clock Frequency: 8MHz
	 SysTick Clock Frequency: 1MHz
*/

void sysTick_Initialize(uint32_t ticks);	//Initializes SysTick
void DelayTime(uint32_t nTime);		//Time to Delay
void SysTick_Handler(void);		//System delay Interrupt
void red_toggle(void);		//toggles the red LED
volatile uint32_t DelayCnt;

int sec = 0;
char * p, text[5];

int main(void)
{
	
	// Enable High Speed Internal Clock (HSI = 8 MHz)
	
	RCC->CR &= ~RCC_CR_MSION;		//Disable MSI first
	RCC->CR |= RCC_CR_MSIRANGE_7;	//set to 8MHz
	RCC->CR |= RCC_CR_MSIRGSEL;	//Use MSI as the system clock
	RCC->CR |= RCC_CR_MSION;	//Enable MSI
	
  // wait until MSI is ready
  while ( (RCC->CR & (uint32_t) RCC_CR_MSIRDY) == 0 ) {;}
	
	// Enable the clock to GPIO Port B	
  RCC->AHB2ENR |= RCC_AHB2ENR_GPIOBEN;   

	// MODER:00: Input mode,              01: General purpose output mode
  //       10: Alternate function mode, 11: Analog mode (reset state)
  GPIOB->MODER &= ~0x00000030 ;   // Clear bit 4 and bit 5
  GPIOB->MODER |= 0x00000010;   // Set bit 4
  
  // PUPDR:00: NO PUPD (reset state),   01: Pullup
  //       10: Pulldown,                11: Reserved
	GPIOB->PUPDR &= ~0x00000030;  // Clear bit 4 and bit 5
		
	GPIOB->PUPDR &= ~0x00030000;  //Clear bit 16 and bit 17
	
	sysTick_Initialize(1000);	//Initialize SysTick
	LCD_Initialization();
	
	//void LCD_WriteChar(uint8_t* ch, bool point, bool colon, uint8_t position)
	
	while(1)	//blinks on and off with 1 second delays.
	{
		sprintf(text, "%d", sec);
		p = text;
		LCD_Clear();
		LCD_DisplayString(p);
		DelayTime(1000);
		red_toggle();
		sec++;
	}
}	

void DelayTime(uint32_t ms)	//Delay in milliseconds
{
	DelayCnt = ms;		//Set the Delay Counter to the number of milliseconds
	while(DelayCnt != 0);
}

void red_toggle(void)
{	
	if(GPIOB->ODR == 0)
	{
	GPIOB->ODR |= GPIO_ODR_ODR_2; // Turn on Red LED
	}
	else
	{
		GPIOB->ODR = 0; // Turn off Red LED
	}
}

void SysTick_Handler(void)	//Interrupt to decrease the Delay Counter
{
	if(DelayCnt > 0)
	{
		DelayCnt--;
	}
}

void sysTick_Initialize(uint32_t ticks)	//Initialize SysTick
{
	SysTick->CTRL = 0;	//Disable SysTick IRQ and SysTick timer
	SysTick->LOAD = ticks - 1;
	NVIC_SetPriority (SysTick_IRQn, (1<<__NVIC_PRIO_BITS) - 1);	//Change interrupt priority
	SysTick->VAL = 0;		//Reset SysTick value register
	SysTick->CTRL &= ~SysTick_CTRL_CLKSOURCE_Msk;	//Set CLKSOURCE to 0 to use the MSI
	SysTick->CTRL |= SysTick_CTRL_TICKINT_Msk;	//Enable Systick Interrupt
	SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;	//Set Systick Control and Status Register
}
