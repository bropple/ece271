#include "stm32l476xx.h"
#include "ADC.h"


void ADC1_Wakeup (void) 
{
	int wait_time;
	
	//to start ADC operations, the following sequence should be applied
	//DEEPPWD = 0: ADC not in deep-power down
	//DEEPPWD = 1: ADC in deep-power down (default reset state)
	if ((ADC1->CR & ADC_CR_DEEPPWD) == ADC_CR_DEEPPWD) {
		ADC1->CR &= ~ADC_CR_DEEPPWD;
	}
	
	//Enable the ADC internal voltage regulator
	//Before performing any operations such as launching a calibration or
	//enabling the ADC, the ADC voltage regulator must first be enabled and
	//the software must wait for the regulator start up time
	ADC1->CR |= ADC_CR_ADVREGEN;
	
	//wait for ADC voltage regulator start up time. the software must wait for
	//the startup time of the ADC voltage regulator (T_ADCVREG_STUP, i.e., 20
	// us) beforelaunching a calibration or enabling the ADC
	wait_time = 20 * (80000000/1000000);
	while (wait_time != 0) {
		wait_time--;
	}
	return;
}



void ADC1_Init(void)
{
	RCC->AHB2ENR |= RCC_AHB2ENR_ADCEN;					//Enable ADC clock
	ADC1->CR &= ~ADC_CR_ADEN;										//Disable ADC1
	SYSCFG->CFGR1 |= SYSCFG_CFGR1_BOOSTEN;	//Enable I/O analog switches voltage booster
	ADC123_COMMON->CCR |= ADC_CCR_VREFEN;				//Enable conversion of internal channels
	ADC123_COMMON->CCR &= ~ADC_CCR_PRESC;				//select not clock divide
	ADC123_COMMON->CCR &= ~ADC_CCR_CKMODE;			//select synchronous clock
	ADC123_COMMON->CCR |= ADC_CCR_CKMODE_0;
	ADC123_COMMON->CCR &= ~ADC_CCR_DUAL;				//configure as independent
	ADC1_Wakeup();															//wake up ADC1
	ADC1->CFGR &= ~ADC_CFGR_RES;								//resolution of 12 bits
	ADC1->CFGR &= ~ADC_CFGR_ALIGN;							//Right alingment
	ADC1->SQR1 &= ~ADC_SQR1_L;									//1 conversion in the regular channel sequence
	ADC1->SQR1 &= ~ADC_SQR1_SQ1;								//select channel 6 as 1st conversion
	ADC1->SQR1 |= ADC_SQR1_SQ1_1;
	ADC1->SQR1 |= ADC_SQR1_SQ1_2;
	ADC1->DIFSEL &= ~ADC_DIFSEL_DIFSEL_6;				//channel 6 as single ended
	ADC1->SMPR1 &= ~ADC_SMPR1_SMP6;							//select sampling time
	ADC1->SMPR1 |= (ADC_SMPR1_SMP6_2 | ADC_SMPR1_SMP6_0);
	ADC1->CFGR &= ~ADC_CFGR_CONT;								//discontinous mode
	ADC1->CFGR &= ~ADC_CFGR_EXTEN;							//select software trigger
	ADC1->CR |= ADC_CR_ADEN;										//enable ADC1
	while ((ADC1->ISR & ADC_ISR_ADRDY) != ADC_ISR_ADRDY);
	return;
}

//void ADC1_2_IRQHandler (void)
//{
//	if ((ADC1->ISR & ADC_ISR_EOC) == ADC_ISR_EOC) {
//		//For a regular channel, check End of conversion (EOC) flag
//		//Reading ADC data register (DR) clears the EOC flag
//		Result = ADC1->DR;
//} else if ((ADC1->ISR & ADC_ISR_JEOS) == ADC_ISR_JEOS) {
//	//For injected channels, check End of sequence (JEOS) flag
//	//Reading injected data registers does not clear the JEOS flag
//	//Each injected channel has a dedicated data register
//	Result_1 = ADC1->JDR1;		//INjected channel 1
//	Result_2 = ADC1->JDR2;		//INjected channel 2
//	Result_3 = ADC1->JDR3;		//INjected channel 3
//	Result_4 = ADC1->JDR4;		//INjected channel 4
//	ADC1->ISR |= ADC_ISR_EOS; //Clear the flag by writing 1 to it
//	}
//}
