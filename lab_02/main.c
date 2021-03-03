#include "stm32l476xx.h"
#include "lcd.h"

void System_Clock_Init(void);
void Joystick_Init(void); //initializes joystick

int main(void){
	LCD_Initialization();
	LCD_Clear();
	Joystick_Init();
	//LCD_Display_Name();
	LCD_DisplayString((uint8_t*)"ECE271");
	//LCD_bar();
	while(1);
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

void Joystick_Init(void) {
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOAEN; //Enable clock to GPIO Port A
	
	GPIOA->MODER &= ~(0xCFF); // Set digital input for pins 0, 1, 2, 3, and 5
		
	GPIOA->PUPDR &= ~(0x8AA); //clears pins 0, 1, 2, 3, and 5
	GPIOA->PUPDR |= 0x8AA; //sets pins 0, 1, 2, 3, and 5 as pull-down
}
