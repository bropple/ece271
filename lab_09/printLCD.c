#include "stm32l476xx.h"
#include "lcd.h"
#include <stdio.h>

void System_Clock_Init(void);
void printLCD(void);
extern int timespan;

void printLCD(void){
	char str[6] = {' ',' ',' ',' ',' ',' '};
	//sprintf(str, "%d", (timespan/100));				// 1 Hz Signal
	sprintf(str, "%d", (timespan/148)+1);					// Distance
	LCD_DisplayString((uint8_t*)str);
}
