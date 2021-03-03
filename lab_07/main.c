#include "stm32l476xx.h"
#include "LCD.h"

/* Ben Ropple
	 03/20/18
	 Objective: Blink LED and turn motor -90, 0, and 90 degrees
	 Clock Frequency: 8MHz
	 SysTick Clock Frequency: 1MHz
*/

void sysTick_Initialize(uint32_t ticks);
void DelayTime(uint32_t ms);
volatile uint32_t DelayCnt;
void SysTick_Handler(void);
void TIM1_Init(void);

uint32_t sc = 99;

int main(void)
{	
	int pc = 1; //Pause counter
	int i = 1; //Controls LED Brightness
	int s = 1; //Step Size
	char * message = "LED";
	
	LCD_Initialization();
	LCD_DisplayString(message);
	
	// Enable High Speed Internal Clock (HSI = 8 MHz)
	
	RCC->CR &= ~RCC_CR_MSION;		//Turn MSI off so clock speed can be changed
	RCC->CR |= RCC_CR_MSIRANGE_7;	//Change MSI clock to 8MHz
	RCC->CR |= RCC_CR_MSIRGSEL;	//Select the MSI clock as the system clock
	RCC->CR |= RCC_CR_MSION;	//Enable the MSI clock
	
  // wait until MSI is ready
  while ( (RCC->CR & (uint32_t) RCC_CR_MSIRDY) == 0 ) {;}
	
	sysTick_Initialize(1000);	//Initializes SysTick
		
	// Enable the clock to GPIO Port E	
  RCC->AHB2ENR |= RCC_AHB2ENR_GPIOEEN;
		
	// MODER:00: Input mode,              01: General purpose output mode  //319 249 21 36 10
  //       10: Alternate function mode, 11: Analog mode (reset state)
  GPIOE->MODER &= ~GPIO_MODER_MODE8;   // Clear MODER 8
  GPIOE->MODER |= GPIO_MODER_MODE8_1;   // Set MODER 8 to Alternate Function
  
	GPIOE->AFR[1] &= ~GPIO_AFRH_AFSEL8; // Clear AFRH8
		
	GPIOE->AFR[1] |= GPIO_AFRH_AFSEL8_0; // Set the Alternative Function to TIM1_CH1N
		
	//Joystick
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOAEN; //Enable clock to GPIO Port A
	
	GPIOA->MODER &= ~(0xCFF); // Set digital input for pins 0, 1, 2, 3, and 5
		
	GPIOA->PUPDR &= ~(0x8AA); //clears pins 0, 1, 2, 3, and 5
	GPIOA->PUPDR |= 0x8AA; //sets pins 0, 1, 2, 3, and 5 as pull-down
	
	TIM1_Init(); // Initializing TIMER 1
		
	while(pc <= 10)
	{
		if((i >= 99) || (i <= 0))
		{
			s = -s;	// Reverse direction
			pc += 1;
		}
		
		i += s; // Change i
		
		TIM1->CCR1 = i; // Change duty cycle of channel 1 outputs
		
		DelayTime(10);	// Delay 1 ms
	}
	
	sc = 1999;	// Changing Period for Motor
	
	TIM1_Init();
	
	LCD_Clear();
	message = "MOTOR";
	LCD_DisplayString(message);
		
	for(;i <= 140; i++)	// 0
	{
		DelayTime(10);
		TIM1->CCR1 = i;
	}
	DelayTime(1000);
	for(;i >= 54; i--) // 90
	{
		DelayTime(10);
		TIM1->CCR1 = i;
	}
	DelayTime(1000);
	for(;i <= 140; i++)	// 0
	{
		DelayTime(10);
		TIM1->CCR1 = i;
	}
	DelayTime(1000);
	for(;i <= 240; i++) // -90
	{
		DelayTime(10);
		TIM1->CCR1 = i;
	}
	DelayTime(1000);
	
	LCD_Clear();
	message = "DONE";
	LCD_DisplayString(message);
	TIM1->CCR1 = 140; //Move back to zero
	DelayTime(5000);
	while(1) {
		if(message != "JOYCLK") {
			LCD_Clear();
			message = "JOYCLK";
			LCD_DisplayString(message);
		}
		if((GPIOA->IDR & 1)==1) //if the CENTER button is pressed
		{
			if(TIM1->CCR1 == 140) {
				LCD_Clear();
				message = "90°   ";
				LCD_DisplayString(message);
				TIM1->CCR1 = 54;
			}
			else if (TIM1->CCR1 == 54) {
				LCD_Clear();
				message = "-90°  ";
				LCD_DisplayString(message);
				TIM1->CCR1 = 240;
			}
			else if (TIM1->CCR1 == 240) {
				LCD_Clear();
				message = "0°    ";
				LCD_DisplayString(message);
				TIM1->CCR1 = 140;
			}
			DelayTime(2500);
		}
	}
}	

void DelayTime(uint32_t ms)	//Delay the nTime passed in in milliseconds
{
	DelayCnt = ms;		//By setting TimeDelay to nTime, the SysTick_Handler occurs
	while(DelayCnt != 0);
}

void SysTick_Handler(void)	//Interrupt to decrease the TimeDelay
{
	if(DelayCnt > 0)
	{
		DelayCnt--;
	}
}

void sysTick_Initialize(uint32_t ticks)	//Initializes SysTick
{
	SysTick->CTRL = 0;	//Disable SysTick IRQ and SysTick timer
	
	SysTick->LOAD = ticks - 1;	//Set Load Value
	
	NVIC_SetPriority (SysTick_IRQn, (1<<__NVIC_PRIO_BITS) - 1);		//Set Interrupt Priority
	
	SysTick->VAL = 0;		//Clear SysTick current value register
	
	SysTick->CTRL &= ~SysTick_CTRL_CLKSOURCE_Msk;	//Set CLKSOURCE to 0 to use the MSI AHB clock frequency/8
	
	SysTick->CTRL |= SysTick_CTRL_TICKINT_Msk;	//Enable Systick Interrupt
	
	SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;	//Set Systick Control and Status Register
}

void TIM1_Init(void)
{
	// Enable TIMER 1 Clock
	RCC->APB2ENR |= RCC_APB2ENR_TIM1EN;
	
	//Counting direction: 0 = Up-counting, 1= Down-Counting
	TIM1->CR1 &= ~TIM_CR1_DIR; // Select Up-counting
	
	// Prescaler, slow down the input clock by a factor of (1 + prescaler)
	TIM1->PSC = 79; // 8 MHz / (1 + 79) = 100 KHz
	
	// Auto-reload
	TIM1->ARR = sc; // PWM period = (99 + 1) * 1/100KHz = 0.001s
	
	// Clear output compare mose bits for channel 1
	TIM1->CCMR1 &= ~TIM_CCMR1_OC1M;
	
	// Select PWM Mode 1 output on channel 1 (OC1M = 110)
	TIM1->CCMR1 |= TIM_CCMR1_OC1M_1 | TIM_CCMR1_OC1M_2;
	
	// Output 1 preload enable
	TIM1->CCMR1 |= TIM_CCMR1_OC1PE;
	
	// Select output polarity: 0 = Active High, 1 = Active Low
	TIM1->CCMR1 &= ~TIM_CCER_CC1NP; // OC1N = OCREF + CC1NP
	
	// Enable complementary output of channel 1 (CH1N)
	TIM1->CCER |= TIM_CCER_CC1NE;
	
	// Main output enable (MOE): 0 = Disable, 1 = Enable
	TIM1->BDTR |= TIM_BDTR_MOE;
	
	// Output Compare Register for channel 1
	TIM1->CCR1 = 50; // Initial duty cycle 50%
	
	// Enable counter
	TIM1->CR1 |= TIM_CR1_CEN;
}
