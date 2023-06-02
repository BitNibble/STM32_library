/******************************************************************************
	STM32 446 ADC
Author: Sergio Santos 
	<sergio.salazar.santos@gmail.com>
License: GNU General Public License
Hardware: STM32-446
Date: 02062023
Comment:
	
*******************************************************************************/
/*** File Library ***/
#include "stm32446mapping.h"
#include "stm32446adc.h"

static double STM32446temperature;

/*** File Procedure & Funtion Header ***/
uint32_t adc_getbit(uint32_t reg, uint32_t size_block, uint32_t bit);
void adc_setbit(volatile uint32_t* reg, uint32_t size_block, uint32_t bit, uint32_t data);

/*** ADC1 ***/
void STM32446Adc1Clock(void)
{
	RCC->APB2ENR |= (1 << 8); // ADC1EN: ADC1 clock enable
}

void STM32446Adc1Inic(void)
{
	// ADC Clock
	// stm32446.rcc.reg->APB1ENR |= (1 << 29); // DACEN: DAC interface clock enable
	//STM32446Adc1Enable();
	// stm32446.rcc.reg->APB2ENR |= (1 << 8); // ADC1EN: ADC1 clock enable
	// ADC CONFIG
	ADC1->CR2 |= (1 << 10); // EOCS: End of conversion selection
	ADC123_COMMON->CCR |= (3 << 16); // ADCPRE: ADC prescaler, 11: PCLK2 divided by 8
	ADC1->SMPR1 |= (7 << 24); // SMPx[2:0]: Channel x sampling time selection
	ADC1->CR1 |= (1 << 11); // DISCEN: Discontinuous mode on regular channels
	ADC1->SQR3 |= 18; // SQ1[4:0]: 1st conversion in regular sequence
}

void STM32446Adc1VBAT(void) // vbat overrides temperature
{
	ADC123_COMMON->CCR |= (1 << 22); // VBATE: VBAT enable
}

void STM32446Adc1TEMP(void)
{
	// Temperature (in degrees) = {(VSENSE V25) / Avg_Slope} + 25
	ADC123_COMMON->CCR |= (1 << 23); // TSVREFE: Temperature sensor and VREFINT enable
}

void STM32446Adc1Start()
{
	// turn on select source and start reading
	ADC1->CR2 |= (1 << 0); // ADON: A/D Converter ON / OFF
	//
	ADC1->CR2 |= (1 << 30); // SWSTART: Start conversion of regular channels
}

double STM32446Adc1Read(void)
{
	if(ADC123_COMMON->CSR & (1 << 1)){ // EOC1: End of conversion of ADC1
		STM32446temperature = ADC1->DR;
		ADC1->SR &= (unsigned int) ~(1 << 4); // STRT: Regular channel start flag
	}
	return STM32446temperature;
}

void STM32446Adc1Restart(void)
{
	if(ADC123_COMMON->CSR & (1 << 4)) // STRT1: Regular channel Start flag of ADC1
		;
	else
		ADC1->CR2 |= (1 << 30); // SWSTART: Start conversion of regular channels;
}

void STM32446Adc1Stop(void)
{
	ADC1->CR2 |= (1 << 0); // ADON: A/D Converter ON / OFF
}

/*** ADC 2 ***/
// For future implementation.

/*** ADC 3 ***/
// For future implementation.

uint32_t adc_getbit(uint32_t reg, uint32_t size_block, uint32_t bit)
{
	uint32_t value = 0; uint32_t tmp = 0;

	uint32_t mask = (unsigned int)((1 << size_block) - 1);
	mask = (mask << bit);
	tmp = mask & reg;
	value = (tmp >> bit);
	return value;
}

void adc_setbit(volatile uint32_t* reg, uint32_t size_block, uint32_t bit, uint32_t data)
{
	uint32_t n = 0;
	if(bit > 31){ n = bit/32; bit = bit - (n * 32); }
	uint32_t value = 0;
	uint32_t mask = (unsigned int)((1 << size_block) - 1);
	value = data & mask;
	*(reg + n ) &= ~(mask << bit);
	*(reg + n ) |= (value << bit);
}

/*** EOF ***/


