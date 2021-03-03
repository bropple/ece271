#include "stm32l476xx.h"
#include "lcd.h"
#include "motor.h"

void System_Clock_Init(void);

/* Ben Ropple
   Lab 4
   
   This program takes an input from a wired keypad and spins a motor
	 by the specified number of degrees.
   
 */
double d, r;

int main(void){
	LCD_Initialization();	//Initializes LCD
	MotorInit(); //Ensures motor is usable
	while(1) {		
		d = KeyPrnt(); //reads degree input from keypad input
		r = d/360*512; //rotations are degrees / (360*512)
		LCD_Clear(); //Clear LCD after each printout
		FullStepper(r); //Full Stepping
		//HalfStepper(r); //Half Stepping
	}
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
