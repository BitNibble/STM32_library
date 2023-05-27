/******************************************************************************
	STM32 446 ADC
Author: Sergio Santos 
	<sergio.salazar.santos@gmail.com>
License: GNU General Public License
Hardware: STM32-446
Date: 23052023
Comment:
	
*******************************************************************************/
/*** File Library ***/
#include "stm32446mapping.h" // after fix architecture in rcc lib, use it here.
#include "stm32446adc.h"

static STM32446 stm32446;
static STM32446ADC1 adc1;
static double STM32446temperature;

/*** ADC 1 ***/
// ADC1
void STM32446Adc1Inic(void);
void STM32446Adc1VBAT(void);
void STM32446Adc1TEMP(void);
void STM32446Adc1Start(void);
double STM32446Adc1Read(void);
void STM32446Adc1Restart(void);
void STM32446Adc1Stop(void);
// ADC1
void STM32446Adc1Enable(void);

// ADC1
STM32446ADC1 STM32446ADC1enable(void)
{
	stm32446 = STM32446enable();

	STM32446temperature = 0;

	adc1.common.reg = (ADC_Common_TypeDef*) ADC123_COMMON_BASE;
	adc1.reg = (ADC_TypeDef*) ADC1_BASE;

	adc1.single.inic = STM32446Adc1Inic;
	adc1.single.vbat = STM32446Adc1VBAT;
	adc1.single.temp = STM32446Adc1TEMP;
	adc1.single.start = STM32446Adc1Start;
	adc1.single.read = STM32446Adc1Read;
	adc1.single.restart = STM32446Adc1Restart;
	adc1.single.stop = STM32446Adc1Stop;

	STM32446Adc1Enable();

	return adc1;
}

void STM32446Adc1Enable(void)
{
	stm32446.rcc.reg->APB2ENR |= (1 << 8); // ADC1EN: ADC1 clock enable
}

void STM32446Adc1Inic(void)
{
	// ADC Clock
	// stm32446.rcc.reg->APB1ENR |= (1 << 29); // DACEN: DAC interface clock enable
	//STM32446Adc1Enable();
	// stm32446.rcc.reg->APB2ENR |= (1 << 8); // ADC1EN: ADC1 clock enable
	// ADC CONFIG
	adc1.reg->CR2 |= (1 << 10); // EOCS: End of conversion selection
	adc1.common.reg->CCR |= (3 << 16); // ADCPRE: ADC prescaler, 11: PCLK2 divided by 8
	adc1.reg->SMPR1 |= (7 << 24); // SMPx[2:0]: Channel x sampling time selection
	adc1.reg->CR1 |= (1 << 11); // DISCEN: Discontinuous mode on regular channels
	adc1.reg->SQR3 |= 18; // SQ1[4:0]: 1st conversion in regular sequence
}

void STM32446Adc1VBAT(void) // vbat overrides temperature
{
	adc1.common.reg->CCR |= (1 << 22); // VBATE: VBAT enable
}

void STM32446Adc1TEMP(void)
{
	// Temperature (in ?C) = {(VSENSE V25) / Avg_Slope} + 25
	adc1.common.reg->CCR |= (1 << 23); // TSVREFE: Temperature sensor and VREFINT enable
}

void STM32446Adc1Start()
{
	// turn on select source and start reading
	adc1.reg->CR2 |= (1 << 0); // ADON: A/D Converter ON / OFF
	//
	adc1.reg->CR2 |= (1 << 30); // SWSTART: Start conversion of regular channels
}

double STM32446Adc1Read(void)
{
	if(adc1.common.reg->CSR & (1 << 1)){ // EOC1: End of conversion of ADC1
		STM32446temperature = adc1.reg->DR;
		adc1.reg->SR &= (unsigned int) ~(1 << 4); // STRT: Regular channel start flag
	}
	return STM32446temperature;
}

void STM32446Adc1Restart(void)
{
	if(adc1.common.reg->CSR & (1 << 4)) // STRT1: Regular channel Start flag of ADC1
		;
	else
		adc1.reg->CR2 |= (1 << 30); // SWSTART: Start conversion of regular channels;
}

void STM32446Adc1Stop(void)
{
	adc1.reg->CR2 |= (1 << 0); // ADON: A/D Converter ON / OFF
}

/*** ADC 2 ***/
// For future implementation.

/*** ADC 3 ***/
// For future implementation.


