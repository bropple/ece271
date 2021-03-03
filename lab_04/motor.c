#include "stm32l476xx.h"
#include <stdint.h>
#include "motor.h"

void MDelay(uint32_t ticks)
{
	int cnt; //Delay(5) - 1 unit
	for(cnt = 0; cnt<(ticks*3000); cnt++); //'busy' work to occupy processor
}

void MotorInit(void) {
	GPIOB->MODER &= ~(GPIO_MODER_MODE2 | GPIO_MODER_MODE3 | GPIO_MODER_MODE6 | GPIO_MODER_MODE7);
	GPIOB->MODER |= (GPIO_MODER_MODE2_0 | GPIO_MODER_MODE3_0 | GPIO_MODER_MODE6_0 | GPIO_MODER_MODE7_0);
}

int k, j;
void FullStepper(int revs) {
	for(k = 0; k < revs; k++) {
		for( j = 0; j < 4; j++) {
			MDelay(1);
			GPIOB->ODR &= ~(GPIO_ODR_OD2 | GPIO_ODR_OD3 | GPIO_ODR_OD6 | GPIO_ODR_OD7);
			switch(j)
			{
				case 0:
						GPIOB->ODR |= (GPIO_ODR_OD2 | GPIO_ODR_OD7);
						break;
					case 1:
						GPIOB->ODR |= (GPIO_ODR_OD6 | GPIO_ODR_OD2);
						break;
					case 2:
						GPIOB->ODR |= (GPIO_ODR_OD3 | GPIO_ODR_OD6);
						break;
					case 3:
						GPIOB->ODR |= (GPIO_ODR_OD7 | GPIO_ODR_OD3);
						break;
					default:
						break;
			}
		}
	}
		GPIOB->ODR &= ~(GPIO_ODR_OD2 | GPIO_ODR_OD3 | GPIO_ODR_OD6 | GPIO_ODR_OD7);
}

void HalfStepper(int revs) {
			for (k = 0; k < revs; k++) {
				for (j = 0; j < 8; j++) {
					MDelay(1);
					GPIOB->ODR &= ~(GPIO_ODR_OD2 | GPIO_ODR_OD3 | GPIO_ODR_OD6 | GPIO_ODR_OD7);
					switch (j) {
						case 0:
							GPIOB->ODR |= (GPIO_ODR_OD2 | GPIO_ODR_OD7);
							break;
						case 1:
							GPIOB->ODR |= GPIO_ODR_OD2;
							break;	
						case 2:
							GPIOB->ODR |= (GPIO_ODR_OD2 | GPIO_ODR_OD6);
							break;
						case 3:
							GPIOB->ODR |= GPIO_ODR_OD6;
							break;
						case 4:
							GPIOB->ODR |= (GPIO_ODR_OD6 | GPIO_ODR_OD3);
							break;
						case 5:
							GPIOB->ODR |= GPIO_ODR_OD3;
							break;
						case 6:
							GPIOB->ODR |= (GPIO_ODR_OD7 | GPIO_ODR_OD3);
							break;
						case 7:
							GPIOB->ODR |= GPIO_ODR_OD7;
							break;
						default:
							break;
					}
				}
			}
			GPIOB->ODR &= ~(GPIO_ODR_OD2 | GPIO_ODR_OD3 | GPIO_ODR_OD6 | GPIO_ODR_OD7);
}
