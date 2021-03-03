#include "stm32l476xx.h"
#include "lcd.h"

void System_Clock_Init(void);
void KeyPrnt();

/* Ben Ropple
   Lab 3
   
   This program takes an input from a wired keypad and prints
   it to the LCD screen.
   
 */


int main(void){
	LCD_Initialization();	//Initializes LCD
	KeyPrnt();	//Prints input
}

void System_Clock_Init(void){
	
	// Enable High Speed Internal Clock (HSI = 16 MHz)
  RCC->CR |= ((uint32_t)RCC_CR_HSION);
	
  // wait until HSI is ready
  while ( (RCC->CR & (uint32_t) RCC_CR_HSIRDY) == 0 );
	
  // Select HSI as system clock source 
  RCC->CFGR &= (uint32_t)((uint32_t)~(RCC_CFGR_SW));
  RCC->CFGR |= (uint32_t)RCC_CFGR_SW_HSI;  //01: HSI16 oscillator used as system clock

  // Wait till HSI is used as system clock source 
  while ((RCC->CFGR & (uint32_t)RCC_CFGR_SWS) == 0 );
		
}

