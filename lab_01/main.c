//Ben Ropple
//Blinking LED Lab

#include "stm32l476xx.h"

int Delay(uint32_t ticks)
{
	int cnt; //Delay(5) - 1 unit
	for(cnt = 0; cnt<(ticks*100000); cnt++); //'busy' work to occupy processor
}

void Dot()
{
		GPIOB->ODR ^= GPIO_ODR_ODR_2;
		GPIOE->ODR ^= GPIO_ODR_ODR_8;
		Delay(5);
		GPIOB->ODR ^= GPIO_ODR_ODR_2;
		GPIOE->ODR ^= GPIO_ODR_ODR_8;
		Delay(5);
}

void Dash()
{
		GPIOB->ODR ^= GPIO_ODR_ODR_2;
		GPIOE->ODR ^= GPIO_ODR_ODR_8;
		Delay(15);
		GPIOB->ODR ^= GPIO_ODR_ODR_2;
		GPIOE->ODR ^= GPIO_ODR_ODR_8;
		Delay(5);
}
	
int main(void){
	// Enable High Speed Internal Clock (HSI = 16 MHz)
  RCC->CR |= ((uint32_t)RCC_CR_HSION);
	
  // wait until HSI is ready
  while ( (RCC->CR & (uint32_t) RCC_CR_HSIRDY) == 0 ) {;}
	
  // Select HSI as system clock source 
  RCC->CFGR &= (uint32_t)((uint32_t)~(RCC_CFGR_SW));
  RCC->CFGR |= (uint32_t)RCC_CFGR_SW_HSI;     // 01: HSI16 oscillator used as system clock

  // Wait till HSI is used as system clock source 
  while ((RCC->CFGR & (uint32_t)RCC_CFGR_SWS) == 0 ) {;}
  
	//Red LED (GIVEN CODE)
  RCC->AHB2ENR |= RCC_AHB2ENR_GPIOBEN;   // Enable the clock to GPIO Port B	

	// MODE: 00: Input mode,              01: General purpose output mode
  //       10: Alternate function mode, 11: Analog mode (reset state)
  GPIOB->MODER &= ~(GPIO_MODER_MODER2_1);   // Clear bit 13 and bit 12
  GPIOB->MODER |= (1<<4); //set bit

	//Green LED
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOEEN; //Enable the clock to GPIO Port E
		
	GPIOE->MODER &= ~(GPIO_MODER_MODER8);   // Clear bit 17 and bit 16
  GPIOE->MODER |= (1<<16);  //set bit 16
		
	//Joystick
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOAEN; //Enable clock to GPIO Port A
	
	GPIOA->MODER &= ~(0xCFF); // Set digital input for pins 0, 1, 2, 3, and 5
		
	GPIOA->PUPDR &= ~(0x8AA); //clears pins 0, 1, 2, 3, and 5
	GPIOA->PUPDR |= 0x8AA; //sets pins 0, 1, 2, 3, and 5 as pull-down
	
	while(1) //infinite loop
	{
		if((GPIOA->IDR & 1)==1) //if the CENTER button is pressed
		{
			GPIOB->ODR ^= GPIO_ODR_ODR_2; //Toggle the red LED
			GPIOE->ODR ^= GPIO_ODR_ODR_8; //Toggle the green LED on
			while((GPIOA->IDR & 1)!=0); //wait for the button to be released
		}
		if((GPIOA->IDR & 1<<1)==1<<1) //if the LEFT button is pressed
		{
			GPIOB->ODR ^= GPIO_ODR_ODR_2; //Toggle the red LED
			while((GPIOA->IDR & 1<<1)!=0); //wait for the button to be released
		}
			if((GPIOA->IDR & 1<<2)==1<<2) //if the RIGHT button is pressed
		{
			GPIOE->ODR ^= GPIO_ODR_ODR_8; //Toggle the green LED
			while((GPIOA->IDR & 1<<2)!=0); //wait for the button to be released
		}
		if((GPIOA->IDR & 1<<3)==1<<3) //if the UP button is pressed
		{
			int cnt = 0;
			int loop = 0;
			while(cnt<4)  //H in morse code
			{
				Dot();
				cnt++;
			}
			Delay(15);
			for(cnt=0; cnt<1; cnt++) //E in morse code
			{
				Dot();
			}
				Delay(15);
			while(loop<2) //L (x2)
			{
				for(cnt=0; cnt<1; cnt++)
				{
					Dot();
					Dash();
					Dot();
					Dot();
					Delay(15);
					loop++;
				}
			}
			for(cnt=0; cnt<3; cnt++) //O
			{
				Dash();
			}
			Delay(35);
			for(cnt=0; cnt<1; cnt++) //W
			{
				Dot();
				Dash();
				Dash();
			}
			Delay(15);
				for(cnt=0; cnt<3; cnt++) //O
			{
				Dash();
			}
			for(cnt=0; cnt<1; cnt++) //R
			{
				Dot();
				Dash();
				Dot();
			}
			Delay(15);
			for(cnt=0; cnt<1; cnt++) //L
				{
					Dot();
					Dash();
					Dot();
					Dot();
				}
			Delay(15);
			for(cnt=0; cnt<1; cnt++) //D
			{
				Dash();
				Dot();
				Dot();
			}
			Delay(35);
			cnt = 0;
			while((GPIOA->IDR & 1<<3)!=0); //wait for the button to be released
		}
			if((GPIOA->IDR & 1<<5)==1<<5) //if the DOWN button is pressed
		{
			GPIOB->ODR ^= GPIO_ODR_ODR_2; //Toggle the red LED
			while((GPIOA->IDR & 1<<5)!=0); //wait for the button to be released
		}
	}
}