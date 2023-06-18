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
uint32_t adc_readreg(uint32_t reg, uint32_t size_block, uint32_t bit);
void adc_writereg(volatile uint32_t* reg, uint32_t size_block, uint32_t bit, uint32_t data);
void adc_setreg(volatile uint32_t* reg, uint32_t size_block, uint32_t bit, uint32_t data);
void adc_setbit(volatile uint32_t* reg, uint32_t size_block, uint32_t bit, uint32_t data);
uint32_t adc_getsetbit(volatile uint32_t* reg, uint32_t size_block, uint32_t bit);

/*** ADC Procedure & Function Definition ***/
/*** ADC1 Bit Mapping ***/
// SR
uint8_t STM32446ADC1_sr_ovr(void)
{
	return adc_readreg(ADC1->SR, 1, 5);
}
void STM32446ADC1_sr_clear_ovr(void)
{
	adc_setreg(&ADC1->SR, 1, 5, 0);
}
uint8_t STM32446ADC1_sr_strt(void)
{
	return adc_readreg(ADC1->SR, 1, 4);
}
void STM32446ADC1_sr_clear_strt(void)
{
	adc_setreg(&ADC1->SR, 1, 4, 0);
}
uint8_t STM32446ADC1_sr_jstrt(void)
{
	return adc_readreg(ADC1->SR, 1, 3);
}
void STM32446ADC1_sr_clear_jstrt(void)
{
	adc_setreg(&ADC1->SR, 1, 3, 0);
}
uint8_t STM32446ADC1_sr_jeoc(void)
{
	return adc_readreg(ADC1->SR, 1, 2);
}
void STM32446ADC1_sr_clear_jeoc(void)
{
	adc_setreg(&ADC1->SR, 1, 2, 0);
}
uint8_t STM32446ADC1_sr_eoc(void)
{
	return adc_readreg(ADC1->SR, 1, 1);
}
void STM32446ADC1_sr_clear_eoc(void)
{
	adc_setreg(&ADC1->SR, 1, 1, 0);
}
uint8_t STM32446ADC1_sr_awd(void)
{
	return adc_readreg(ADC1->SR, 1, 0);
}
void STM32446ADC1_sr_clear_awd(void)
{
	adc_setreg(&ADC1->SR, 1, 0, 0);
}

// CR1
void STM32446ADC1_cr1_ovrie(uint8_t bool)
{
	adc_setreg(&ADC1->CR1, 1, 26, bool);
}
void STM32446ADC1_cr1_res(uint8_t value)
{
	adc_setreg(&ADC1->CR1, 2, 24, value);
}
void STM32446ADC1_cr1_awden(uint8_t bool)
{
	adc_setreg(&ADC1->CR1, 1, 23, bool);
}
void STM32446ADC1_cr1_jawden(uint8_t bool)
{
	adc_setreg(&ADC1->CR1, 1, 22, bool);
}
void STM32446ADC1_cr1_discnum(uint8_t value)
{
	adc_setreg(&ADC1->CR1, 3, 13, value);
}
void STM32446ADC1_cr1_jdiscen(uint8_t bool)
{
	adc_setreg(&ADC1->CR1, 1, 12, bool);
}
void STM32446ADC1_cr1_discen(uint8_t bool)
{
	adc_setreg(&ADC1->CR1, 1, 11, bool);
}
void STM32446ADC1_cr1_jauto(uint8_t bool)
{
	adc_setreg(&ADC1->CR1, 1, 10, bool);
}
void STM32446ADC1_cr1_awdsgl(uint8_t bool)
{
	adc_setreg(&ADC1->CR1, 1, 9, bool);
}
void STM32446ADC1_cr1_scan(uint8_t bool)
{
	adc_setreg(&ADC1->CR1, 1, 8, bool);
}
void STM32446ADC1_cr1_jeocie(uint8_t bool)
{
	adc_setreg(&ADC1->CR1, 1, 7, bool);
}
void STM32446ADC1_cr1_awdie(uint8_t bool)
{
	adc_setreg(&ADC1->CR1, 1, 6, bool);
}
void STM32446ADC1_cr1_eocie(uint8_t bool)
{
	adc_setreg(&ADC1->CR1, 1, 5, bool);
}
void STM32446ADC1_cr1_awdch(uint8_t value)
{
	adc_setreg(&ADC1->CR1, 5, 0, value);
}

// CR2
void STM32446ADC1_cr2_swstart(uint8_t bool)
{
	adc_setreg(&ADC1->CR2, 1, 30, bool);
}
void STM32446ADC1_cr2_exten(uint8_t value)
{
	adc_setreg(&ADC1->CR2, 2, 28, value);
}
void STM32446ADC1_cr2_extsel(uint8_t value)
{
	adc_setreg(&ADC1->CR2, 4, 24, value);
}
void STM32446ADC1_cr2_jswstart(uint8_t bool)
{
	adc_setreg(&ADC1->CR2, 1, 22, bool);
}
void STM32446ADC1_cr2_jexten(uint8_t value)
{
	adc_setreg(&ADC1->CR2, 2, 20, value);
}
void STM32446ADC1_cr2_jextsel(uint8_t value)
{
	adc_setreg(&ADC1->CR2, 4, 16, value);
}
void STM32446ADC1_cr2_align(uint8_t bool)
{
	adc_setreg(&ADC1->CR2, 1, 11, bool);
}
void STM32446ADC1_cr2_eocs(uint8_t bool)
{
	adc_setreg(&ADC1->CR2, 1, 10, bool);
}
void STM32446ADC1_cr2_dds(uint8_t bool)
{
	adc_setreg(&ADC1->CR2, 1, 9, bool);
}
void STM32446ADC1_cr2_dma(uint8_t bool)
{
	adc_setreg(&ADC1->CR2, 1, 8, bool);
}
void STM32446ADC1_cr2_cont(uint8_t bool)
{
	adc_setreg(&ADC1->CR2, 1, 1, bool);
}
void STM32446ADC1_cr2_adon(uint8_t bool)
{
	adc_setreg(&ADC1->CR2, 1, 0, bool);
}

// SMPR1
void STM32446ADC1_smpr1_smp18(uint8_t value)
{
	adc_setreg(&ADC1->SMPR1, 3, 24, value);
}
void STM32446ADC1_smpr1_smp17(uint8_t value)
{
	adc_setreg(&ADC1->SMPR1, 3, 21, value);
}
void STM32446ADC1_smpr1_smp16(uint8_t value)
{
	adc_setreg(&ADC1->SMPR1, 3, 18, value);
}
void STM32446ADC1_smpr1_smp15(uint8_t value)
{
	adc_setreg(&ADC1->SMPR1, 2, 16, value);
}
void STM32446ADC1_smpr1_smp15_0(uint8_t bool)
{
	adc_setreg(&ADC1->SMPR1, 1, 15, bool);
}
void STM32446ADC1_smpr1_smp14(uint8_t value)
{
	adc_setreg(&ADC1->SMPR1, 3, 12, value);
}
void STM32446ADC1_smpr1_smp13(uint8_t value)
{
	adc_setreg(&ADC1->SMPR1, 3, 9, value);
}
void STM32446ADC1_smpr1_smp12(uint8_t value)
{
	adc_setreg(&ADC1->SMPR1, 3, 6, value);
}
void STM32446ADC1_smpr1_smp11(uint8_t value)
{
	adc_setreg(&ADC1->SMPR1, 3, 3, value);
}
void STM32446ADC1_smpr1_smp10(uint8_t value)
{
	adc_setreg(&ADC1->SMPR1, 3, 0, value);
}

// SMPR2
void STM32446ADC1_smpr2_smp9(uint8_t value)
{
	adc_setreg(&ADC1->SMPR2, 3, 27, value);
}
void STM32446ADC1_smpr2_smp8(uint8_t value)
{
	adc_setreg(&ADC1->SMPR2, 3, 24, value);
}
void STM32446ADC1_smpr2_smp7(uint8_t value)
{
	adc_setreg(&ADC1->SMPR2, 3, 21, value);
}
void STM32446ADC1_smpr2_smp6(uint8_t value)
{
	adc_setreg(&ADC1->SMPR2, 3, 18, value);
}
void STM32446ADC1_smpr2_smp5(uint8_t bool)
{
	adc_setreg(&ADC1->SMPR2, 2, 16, bool);
}
void STM32446ADC1_smpr2_smp5_0(uint8_t bool)
{
	adc_setreg(&ADC1->SMPR2, 1, 15, bool);
}
void STM32446ADC1_smpr2_smp4(uint8_t value)
{
	adc_setreg(&ADC1->SMPR2, 3, 12, value);
}
void STM32446ADC1_smpr2_smp3(uint8_t value)
{
	adc_setreg(&ADC1->SMPR2, 3, 9, value);
}
void STM32446ADC1_smpr2_smp2(uint8_t value)
{
	adc_setreg(&ADC1->SMPR2, 3, 6, value);
}
void STM32446ADC1_smpr2_smp1(uint8_t value)
{
	adc_setreg(&ADC1->SMPR2, 3, 3, value);
}
void STM32446ADC1_smpr2_smp0(uint8_t value)
{
	adc_setreg(&ADC1->SMPR2, 3, 0, value);
}

// Other
void STM32446ADC1_jofr1(uint16_t value)
{
	adc_setreg(&ADC1->JOFR1, 12, 0, value);
}
void STM32446ADC1_jofr2(uint16_t value)
{
	adc_setreg(&ADC1->JOFR2, 12, 0, value);
}
void STM32446ADC1_jofr3(uint16_t value)
{
	adc_setreg(&ADC1->JOFR3, 12, 0, value);
}
void STM32446ADC1_jofr4(uint16_t value)
{
	adc_setreg(&ADC1->JOFR4, 12, 0, value);
}
void STM32446ADC1_htr(uint16_t value)
{
	adc_setreg(&ADC1->HTR, 12, 0, value);
}
void STM32446ADC1_ltr(uint16_t value)
{
	adc_setreg(&ADC1->LTR, 12, 0, value);
}

// SQR1
void STM32446ADC1_sqr1_l(uint8_t value)
{
	adc_setreg(&ADC1->SQR1, 4, 20, value);
}
void STM32446ADC1_sqr1_sq16(uint8_t value)
{
	adc_setreg(&ADC1->SQR1, 4, 16, value);
}
void STM32446ADC1_sqr1_sq16_0(uint8_t bool)
{
	adc_setreg(&ADC1->SQR1, 1, 15, bool);
}
void STM32446ADC1_sqr1_sq15(uint8_t value)
{
	adc_setreg(&ADC1->SQR1, 5, 10, value);
}
void STM32446ADC1_sqr1_sq14(uint8_t value)
{
	adc_setreg(&ADC1->SQR1, 5, 5, value);
}
void STM32446ADC1_sqr1_sq13(uint8_t value)
{
	adc_setreg(&ADC1->SQR1, 5, 0, value);
}

// SQR2
void STM32446ADC1_sqr2_sq12(uint8_t value)
{
	adc_setreg(&ADC1->SQR2, 5, 25, value);
}
void STM32446ADC1_sqr2_sq11(uint8_t value)
{
	adc_setreg(&ADC1->SQR2, 5, 20, value);
}
void STM32446ADC1_sqr2_sq10(uint8_t value)
{
	adc_setreg(&ADC1->SQR2, 4, 16, value);
}
void STM32446ADC1_sqr2_sq10_0(uint8_t bool)
{
	adc_setreg(&ADC1->SQR2, 1, 15, bool);
}
void STM32446ADC1_sqr2_sq9(uint8_t value)
{
	adc_setreg(&ADC1->SQR2, 5, 10, value);
}
void STM32446ADC1_sqr2_sq8(uint8_t value)
{
	adc_setreg(&ADC1->SQR2, 5, 5, value);
}
void STM32446ADC1_sqr2_sq7(uint8_t value)
{
	adc_setreg(&ADC1->SQR2, 5, 0, value);
}

// SQR3
void STM32446ADC1_sqr3_sq6(uint8_t value)
{
	adc_setreg(&ADC1->SQR3, 5, 25, value);
}
void STM32446ADC1_sqr3_sq5(uint8_t value)
{
	adc_setreg(&ADC1->SQR3, 5, 20, value);
}
void STM32446ADC1_sqr3_sq4(uint8_t value)
{
	adc_setreg(&ADC1->SQR3, 4, 16, value);
}
void STM32446ADC1_sqr3_sq4_0(uint8_t bool)
{
	adc_setreg(&ADC1->SQR3, 1, 15, bool);
}
void STM32446ADC1_sqr3_sq3(uint8_t value)
{
	adc_setreg(&ADC1->SQR3, 5, 10, value);
}
void STM32446ADC1_sqr3_sq2(uint8_t value)
{
	adc_setreg(&ADC1->SQR3, 5, 5, value);
}
void STM32446ADC1_sqr3_sq1(uint8_t value)
{
	adc_setreg(&ADC1->SQR3, 5, 0, value);
}

// JSQR
void STM32446ADC1_jsqr_jl(uint8_t value)
{
	adc_setreg(&ADC1->JSQR, 2, 20, value);
}
void STM32446ADC1_jsqr_jsq4(uint8_t value)
{
	adc_setreg(&ADC1->JSQR, 4, 16, value);
}
void STM32446ADC1_jsqr_jsq4_0(uint8_t bool)
{
	adc_setreg(&ADC1->JSQR, 1, 15, bool);
}
void STM32446ADC1_jsqr_jsq3(uint8_t value)
{
	adc_setreg(&ADC1->JSQR, 5, 10, value);
}
void STM32446ADC1_jsqr_jsq2(uint8_t value)
{
	adc_setreg(&ADC1->JSQR, 5, 5, value);
}
void STM32446ADC1_jsqr_jsq1(uint8_t value)
{
	adc_setreg(&ADC1->JSQR, 5, 0, value);
}

// Other
uint16_t STM32446ADC1_jdr1(void)
{
	return adc_readreg(ADC1->JDR1, 16, 0);
}
uint16_t STM32446ADC1_jdr2(void)
{
	return adc_readreg(ADC1->JDR2, 16, 0);
}
uint16_t STM32446ADC1_jdr3(void)
{
	return adc_readreg(ADC1->JDR3, 16, 0);
}
uint16_t STM32446ADC1_jdr4(void)
{
	return adc_readreg(ADC1->JDR4, 16, 0);
}
uint16_t STM32446ADC1_dr(void)
{
	return adc_readreg(ADC1->DR, 16, 0);
}

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

/*** ADC2 Bit Mapping ***/
// SR
uint8_t STM32446ADC2_sr_ovr(void)
{
	return adc_readreg(ADC2->SR, 1, 5);
}
void STM32446ADC2_sr_clear_ovr(void)
{
	adc_setreg(&ADC2->SR, 1, 5, 0);
}
uint8_t STM32446ADC2_sr_strt(void)
{
	return adc_readreg(ADC2->SR, 1, 4);
}
void STM32446ADC2_sr_clear_strt(void)
{
	adc_setreg(&ADC2->SR, 1, 4, 0);
}
uint8_t STM32446ADC2_sr_jstrt(void)
{
	return adc_readreg(ADC2->SR, 1, 3);
}
void STM32446ADC2_sr_clear_jstrt(void)
{
	adc_setreg(&ADC2->SR, 1, 3, 0);
}
uint8_t STM32446ADC2_sr_jeoc(void)
{
	return adc_readreg(ADC2->SR, 1, 2);
}
void STM32446ADC2_sr_clear_jeoc(void)
{
	adc_setreg(&ADC2->SR, 1, 2, 0);
}
uint8_t STM32446ADC2_sr_eoc(void)
{
	return adc_readreg(ADC2->SR, 1, 1);
}
void STM32446ADC2_sr_clear_eoc(void)
{
	adc_setreg(&ADC2->SR, 1, 1, 0);
}
uint8_t STM32446ADC2_sr_awd(void)
{
	return adc_readreg(ADC2->SR, 1, 0);
}
void STM32446ADC2_sr_clear_awd(void)
{
	adc_setreg(&ADC2->SR, 1, 0, 0);
}

// CR1
void STM32446ADC2_cr1_ovrie(uint8_t bool)
{
	adc_setreg(&ADC2->CR1, 1, 26, bool);
}
void STM32446ADC2_cr1_res(uint8_t value)
{
	adc_setreg(&ADC2->CR1, 2, 24, value);
}
void STM32446ADC2_cr1_awden(uint8_t bool)
{
	adc_setreg(&ADC2->CR1, 1, 23, bool);
}
void STM32446ADC2_cr1_jawden(uint8_t bool)
{
	adc_setreg(&ADC2->CR1, 1, 22, bool);
}
void STM32446ADC2_cr1_discnum(uint8_t value)
{
	adc_setreg(&ADC2->CR1, 3, 13, value);
}
void STM32446ADC2_cr1_jdiscen(uint8_t bool)
{
	adc_setreg(&ADC2->CR1, 1, 12, bool);
}
void STM32446ADC2_cr1_discen(uint8_t bool)
{
	adc_setreg(&ADC2->CR1, 1, 11, bool);
}
void STM32446ADC2_cr1_jauto(uint8_t bool)
{
	adc_setreg(&ADC2->CR1, 1, 10, bool);
}
void STM32446ADC2_cr1_awdsgl(uint8_t bool)
{
	adc_setreg(&ADC2->CR1, 1, 9, bool);
}
void STM32446ADC2_cr1_scan(uint8_t bool)
{
	adc_setreg(&ADC2->CR1, 1, 8, bool);
}
void STM32446ADC2_cr1_jeocie(uint8_t bool)
{
	adc_setreg(&ADC2->CR1, 1, 7, bool);
}
void STM32446ADC2_cr1_awdie(uint8_t bool)
{
	adc_setreg(&ADC2->CR1, 1, 6, bool);
}
void STM32446ADC2_cr1_eocie(uint8_t bool)
{
	adc_setreg(&ADC2->CR1, 1, 5, bool);
}
void STM32446ADC2_cr1_awdch(uint8_t value)
{
	adc_setreg(&ADC2->CR1, 5, 0, value);
}

// CR2
void STM32446ADC2_cr2_swstart(uint8_t bool)
{
	adc_setreg(&ADC2->CR2, 1, 30, bool);
}
void STM32446ADC2_cr2_exten(uint8_t value)
{
	adc_setreg(&ADC2->CR2, 2, 28, value);
}
void STM32446ADC2_cr2_extsel(uint8_t value)
{
	adc_setreg(&ADC2->CR2, 4, 24, value);
}
void STM32446ADC2_cr2_jswstart(uint8_t bool)
{
	adc_setreg(&ADC2->CR2, 1, 22, bool);
}
void STM32446ADC2_cr2_jexten(uint8_t value)
{
	adc_setreg(&ADC2->CR2, 2, 20, value);
}
void STM32446ADC2_cr2_jextsel(uint8_t value)
{
	adc_setreg(&ADC2->CR2, 4, 16, value);
}
void STM32446ADC2_cr2_align(uint8_t bool)
{
	adc_setreg(&ADC2->CR2, 1, 11, bool);
}
void STM32446ADC2_cr2_eocs(uint8_t bool)
{
	adc_setreg(&ADC2->CR2, 1, 10, bool);
}
void STM32446ADC2_cr2_dds(uint8_t bool)
{
	adc_setreg(&ADC2->CR2, 1, 9, bool);
}
void STM32446ADC2_cr2_dma(uint8_t bool)
{
	adc_setreg(&ADC2->CR2, 1, 8, bool);
}
void STM32446ADC2_cr2_cont(uint8_t bool)
{
	adc_setreg(&ADC2->CR2, 1, 1, bool);
}
void STM32446ADC2_cr2_adon(uint8_t bool)
{
	adc_setreg(&ADC2->CR2, 1, 0, bool);
}

// SMPR1
void STM32446ADC2_smpr1_smp18(uint8_t value)
{
	adc_setreg(&ADC2->SMPR1, 3, 24, value);
}
void STM32446ADC2_smpr1_smp17(uint8_t value)
{
	adc_setreg(&ADC2->SMPR1, 3, 21, value);
}
void STM32446ADC2_smpr1_smp16(uint8_t value)
{
	adc_setreg(&ADC2->SMPR1, 3, 18, value);
}
void STM32446ADC2_smpr1_smp15(uint8_t value)
{
	adc_setreg(&ADC2->SMPR1, 2, 16, value);
}
void STM32446ADC2_smpr1_smp15_0(uint8_t bool)
{
	adc_setreg(&ADC2->SMPR1, 1, 15, bool);
}
void STM32446ADC2_smpr1_smp14(uint8_t value)
{
	adc_setreg(&ADC2->SMPR1, 3, 12, value);
}
void STM32446ADC2_smpr1_smp13(uint8_t value)
{
	adc_setreg(&ADC2->SMPR1, 3, 9, value);
}
void STM32446ADC2_smpr1_smp12(uint8_t value)
{
	adc_setreg(&ADC2->SMPR1, 3, 6, value);
}
void STM32446ADC2_smpr1_smp11(uint8_t value)
{
	adc_setreg(&ADC2->SMPR1, 3, 3, value);
}
void STM32446ADC2_smpr1_smp10(uint8_t value)
{
	adc_setreg(&ADC2->SMPR1, 3, 0, value);
}

// SMPR2
void STM32446ADC2_smpr2_smp9(uint8_t value)
{
	adc_setreg(&ADC2->SMPR2, 3, 27, value);
}
void STM32446ADC2_smpr2_smp8(uint8_t value)
{
	adc_setreg(&ADC2->SMPR2, 3, 24, value);
}
void STM32446ADC2_smpr2_smp7(uint8_t value)
{
	adc_setreg(&ADC2->SMPR2, 3, 21, value);
}
void STM32446ADC2_smpr2_smp6(uint8_t value)
{
	adc_setreg(&ADC2->SMPR2, 3, 18, value);
}
void STM32446ADC2_smpr2_smp5(uint8_t bool)
{
	adc_setreg(&ADC2->SMPR2, 2, 16, bool);
}
void STM32446ADC2_smpr2_smp5_0(uint8_t bool)
{
	adc_setreg(&ADC2->SMPR2, 1, 15, bool);
}
void STM32446ADC2_smpr2_smp4(uint8_t value)
{
	adc_setreg(&ADC2->SMPR2, 3, 12, value);
}
void STM32446ADC2_smpr2_smp3(uint8_t value)
{
	adc_setreg(&ADC2->SMPR2, 3, 9, value);
}
void STM32446ADC2_smpr2_smp2(uint8_t value)
{
	adc_setreg(&ADC2->SMPR2, 3, 6, value);
}
void STM32446ADC2_smpr2_smp1(uint8_t value)
{
	adc_setreg(&ADC2->SMPR2, 3, 3, value);
}
void STM32446ADC2_smpr2_smp0(uint8_t value)
{
	adc_setreg(&ADC2->SMPR2, 3, 0, value);
}

// Other
void STM32446ADC2_jofr1(uint16_t value)
{
	adc_setreg(&ADC2->JOFR1, 12, 0, value);
}
void STM32446ADC2_jofr2(uint16_t value)
{
	adc_setreg(&ADC2->JOFR2, 12, 0, value);
}
void STM32446ADC2_jofr3(uint16_t value)
{
	adc_setreg(&ADC2->JOFR3, 12, 0, value);
}
void STM32446ADC2_jofr4(uint16_t value)
{
	adc_setreg(&ADC2->JOFR4, 12, 0, value);
}
void STM32446ADC2_htr(uint16_t value)
{
	adc_setreg(&ADC2->HTR, 12, 0, value);
}
void STM32446ADC2_ltr(uint16_t value)
{
	adc_setreg(&ADC2->LTR, 12, 0, value);
}

// SQR1
void STM32446ADC2_sqr1_l(uint8_t value)
{
	adc_setreg(&ADC2->SQR1, 4, 20, value);
}
void STM32446ADC2_sqr1_sq16(uint8_t value)
{
	adc_setreg(&ADC2->SQR1, 4, 16, value);
}
void STM32446ADC2_sqr1_sq16_0(uint8_t bool)
{
	adc_setreg(&ADC2->SQR1, 1, 15, bool);
}
void STM32446ADC2_sqr1_sq15(uint8_t value)
{
	adc_setreg(&ADC2->SQR1, 5, 10, value);
}
void STM32446ADC2_sqr1_sq14(uint8_t value)
{
	adc_setreg(&ADC2->SQR1, 5, 5, value);
}
void STM32446ADC2_sqr1_sq13(uint8_t value)
{
	adc_setreg(&ADC2->SQR1, 5, 0, value);
}

// SQR2
void STM32446ADC2_sqr2_sq12(uint8_t value)
{
	adc_setreg(&ADC2->SQR2, 5, 25, value);
}
void STM32446ADC2_sqr2_sq11(uint8_t value)
{
	adc_setreg(&ADC2->SQR2, 5, 20, value);
}
void STM32446ADC2_sqr2_sq10(uint8_t value)
{
	adc_setreg(&ADC2->SQR2, 4, 16, value);
}
void STM32446ADC2_sqr2_sq10_0(uint8_t bool)
{
	adc_setreg(&ADC2->SQR2, 1, 15, bool);
}
void STM32446ADC2_sqr2_sq9(uint8_t value)
{
	adc_setreg(&ADC2->SQR2, 5, 10, value);
}
void STM32446ADC2_sqr2_sq8(uint8_t value)
{
	adc_setreg(&ADC2->SQR2, 5, 5, value);
}
void STM32446ADC2_sqr2_sq7(uint8_t value)
{
	adc_setreg(&ADC2->SQR2, 5, 0, value);
}

// SQR3
void STM32446ADC2_sqr3_sq6(uint8_t value)
{
	adc_setreg(&ADC2->SQR3, 5, 25, value);
}
void STM32446ADC2_sqr3_sq5(uint8_t value)
{
	adc_setreg(&ADC2->SQR3, 5, 20, value);
}
void STM32446ADC2_sqr3_sq4(uint8_t value)
{
	adc_setreg(&ADC2->SQR3, 4, 16, value);
}
void STM32446ADC2_sqr3_sq4_0(uint8_t bool)
{
	adc_setreg(&ADC2->SQR3, 1, 15, bool);
}
void STM32446ADC2_sqr3_sq3(uint8_t value)
{
	adc_setreg(&ADC2->SQR3, 5, 10, value);
}
void STM32446ADC2_sqr3_sq2(uint8_t value)
{
	adc_setreg(&ADC2->SQR3, 5, 5, value);
}
void STM32446ADC2_sqr3_sq1(uint8_t value)
{
	adc_setreg(&ADC2->SQR3, 5, 0, value);
}

// JSQR
void STM32446ADC2_jsqr_jl(uint8_t value)
{
	adc_setreg(&ADC2->JSQR, 2, 20, value);
}
void STM32446ADC2_jsqr_jsq4(uint8_t value)
{
	adc_setreg(&ADC2->JSQR, 4, 16, value);
}
void STM32446ADC2_jsqr_jsq4_0(uint8_t bool)
{
	adc_setreg(&ADC2->JSQR, 1, 15, bool);
}
void STM32446ADC2_jsqr_jsq3(uint8_t value)
{
	adc_setreg(&ADC2->JSQR, 5, 10, value);
}
void STM32446ADC2_jsqr_jsq2(uint8_t value)
{
	adc_setreg(&ADC2->JSQR, 5, 5, value);
}
void STM32446ADC2_jsqr_jsq1(uint8_t value)
{
	adc_setreg(&ADC2->JSQR, 5, 0, value);
}

// Other
uint16_t STM32446ADC2_jdr1(void)
{
	return adc_readreg(ADC2->JDR1, 16, 0);
}
uint16_t STM32446ADC2_jdr2(void)
{
	return adc_readreg(ADC2->JDR2, 16, 0);
}
uint16_t STM32446ADC2_jdr3(void)
{
	return adc_readreg(ADC2->JDR3, 16, 0);
}
uint16_t STM32446ADC2_jdr4(void)
{
	return adc_readreg(ADC2->JDR4, 16, 0);
}
uint16_t STM32446ADC2_dr(void)
{
	return adc_readreg(ADC2->DR, 16, 0);
}

/*** ADC2 ***/
void STM32446Adc2Clock(void)
{
	RCC->APB2ENR |= (1 << 9); // ADC1EN: ADC1 clock enable
}

/*** ADC3 Bit Mapping ***/
// SR
uint8_t STM32446ADC3_sr_ovr(void)
{
	return adc_readreg(ADC3->SR, 1, 5);
}
void STM32446ADC3_sr_clear_ovr(void)
{
	adc_setreg(&ADC3->SR, 1, 5, 0);
}
uint8_t STM32446ADC3_sr_strt(void)
{
	return adc_readreg(ADC3->SR, 1, 4);
}
void STM32446ADC3_sr_clear_strt(void)
{
	adc_setreg(&ADC3->SR, 1, 4, 0);
}
uint8_t STM32446ADC3_sr_jstrt(void)
{
	return adc_readreg(ADC3->SR, 1, 3);
}
void STM32446ADC3_sr_clear_jstrt(void)
{
	adc_setreg(&ADC3->SR, 1, 3, 0);
}
uint8_t STM32446ADC3_sr_jeoc(void)
{
	return adc_readreg(ADC3->SR, 1, 2);
}
void STM32446ADC3_sr_clear_jeoc(void)
{
	adc_setreg(&ADC3->SR, 1, 2, 0);
}
uint8_t STM32446ADC3_sr_eoc(void)
{
	return adc_readreg(ADC3->SR, 1, 1);

}
void STM32446ADC3_sr_clear_eoc(void)
{
	adc_setreg(&ADC3->SR, 1, 1, 0);
}
uint8_t STM32446ADC3_sr_awd(void)
{
	return adc_readreg(ADC3->SR, 1, 0);
}
void STM32446ADC3_sr_clear_awd(void)
{
	adc_setreg(&ADC3->SR, 1, 0, 0);
}

// CR1
void STM32446ADC3_cr1_ovrie(uint8_t bool)
{
	adc_setreg(&ADC3->CR1, 1, 26, bool);
}
void STM32446ADC3_cr1_res(uint8_t value)
{
	adc_setreg(&ADC3->CR1, 2, 24, value);
}
void STM32446ADC3_cr1_awden(uint8_t bool)
{
	adc_setreg(&ADC3->CR1, 1, 23, bool);
}
void STM32446ADC3_cr1_jawden(uint8_t bool)
{
	adc_setreg(&ADC3->CR1, 1, 22, bool);
}
void STM32446ADC3_cr1_discnum(uint8_t value)
{
	adc_setreg(&ADC3->CR1, 3, 13, value);
}
void STM32446ADC3_cr1_jdiscen(uint8_t bool)
{
	adc_setreg(&ADC3->CR1, 1, 12, bool);
}
void STM32446ADC3_cr1_discen(uint8_t bool)
{
	adc_setreg(&ADC3->CR1, 1, 11, bool);
}
void STM32446ADC3_cr1_jauto(uint8_t bool)
{
	adc_setreg(&ADC3->CR1, 1, 10, bool);
}
void STM32446ADC3_cr1_awdsgl(uint8_t bool)
{
	adc_setreg(&ADC3->CR1, 1, 9, bool);
}
void STM32446ADC3_cr1_scan(uint8_t bool)
{
	adc_setreg(&ADC3->CR1, 1, 8, bool);
}
void STM32446ADC3_cr1_jeocie(uint8_t bool)
{
	adc_setreg(&ADC3->CR1, 1, 7, bool);
}
void STM32446ADC3_cr1_awdie(uint8_t bool)
{
	adc_setreg(&ADC3->CR1, 1, 6, bool);
}
void STM32446ADC3_cr1_eocie(uint8_t bool)
{
	adc_setreg(&ADC3->CR1, 1, 5, bool);
}
void STM32446ADC3_cr1_awdch(uint8_t value)
{
	adc_setreg(&ADC3->CR1, 5, 0, value);
}

// CR2
void STM32446ADC3_cr2_swstart(uint8_t bool)
{
	adc_setreg(&ADC3->CR2, 1, 30, bool);
}
void STM32446ADC3_cr2_exten(uint8_t value)
{
	adc_setreg(&ADC3->CR2, 2, 28, value);
}
void STM32446ADC3_cr2_extsel(uint8_t value)
{
	adc_setreg(&ADC3->CR2, 4, 24, value);
}
void STM32446ADC3_cr2_jswstart(uint8_t bool)
{
	adc_setreg(&ADC3->CR2, 1, 22, bool);
}
void STM32446ADC3_cr2_jexten(uint8_t value)
{
	adc_setreg(&ADC3->CR2, 2, 20, value);
}
void STM32446ADC3_cr2_jextsel(uint8_t value)
{
	adc_setreg(&ADC3->CR2, 4, 16, value);
}
void STM32446ADC3_cr2_align(uint8_t bool)
{
	adc_setreg(&ADC3->CR2, 1, 11, bool);
}
void STM32446ADC3_cr2_eocs(uint8_t bool)
{
	adc_setreg(&ADC3->CR2, 1, 10, bool);
}
void STM32446ADC3_cr2_dds(uint8_t bool)
{
	adc_setreg(&ADC3->CR2, 1, 9, bool);
}
void STM32446ADC3_cr2_dma(uint8_t bool)
{
	adc_setreg(&ADC3->CR2, 1, 8, bool);
}
void STM32446ADC3_cr2_cont(uint8_t bool)
{
	adc_setreg(&ADC3->CR2, 1, 1, bool);
}
void STM32446ADC3_cr2_adon(uint8_t bool)
{
	adc_setreg(&ADC3->CR2, 1, 0, bool);
}

// SMPR1
void STM32446ADC3_smpr1_smp18(uint8_t value)
{
	adc_setreg(&ADC3->SMPR1, 3, 24, value);
}
void STM32446ADC3_smpr1_smp17(uint8_t value)
{
	adc_setreg(&ADC3->SMPR1, 3, 21, value);
}
void STM32446ADC3_smpr1_smp16(uint8_t value)
{
	adc_setreg(&ADC3->SMPR1, 3, 18, value);
}
void STM32446ADC3_smpr1_smp15(uint8_t value)
{
	adc_setreg(&ADC3->SMPR1, 2, 16, value);
}
void STM32446ADC3_smpr1_smp15_0(uint8_t bool)
{
	adc_setreg(&ADC3->SMPR1, 1, 15, bool);
}
void STM32446ADC3_smpr1_smp14(uint8_t value)
{
	adc_setreg(&ADC3->SMPR1, 3, 12, value);
}
void STM32446ADC3_smpr1_smp13(uint8_t value)
{
	adc_setreg(&ADC3->SMPR1, 3, 9, value);
}
void STM32446ADC3_smpr1_smp12(uint8_t value)
{
	adc_setreg(&ADC3->SMPR1, 3, 6, value);
}
void STM32446ADC3_smpr1_smp11(uint8_t value)
{
	adc_setreg(&ADC3->SMPR1, 3, 3, value);
}
void STM32446ADC3_smpr1_smp10(uint8_t value)
{
	adc_setreg(&ADC3->SMPR1, 3, 0, value);
}

// SMPR2
void STM32446ADC3_smpr2_smp9(uint8_t value)
{
	adc_setreg(&ADC3->SMPR2, 3, 27, value);
}
void STM32446ADC3_smpr2_smp8(uint8_t value)
{
	adc_setreg(&ADC3->SMPR2, 3, 24, value);
}
void STM32446ADC3_smpr2_smp7(uint8_t value)
{
	adc_setreg(&ADC3->SMPR2, 3, 21, value);
}
void STM32446ADC3_smpr2_smp6(uint8_t value)
{
	adc_setreg(&ADC3->SMPR2, 3, 18, value);
}
void STM32446ADC3_smpr2_smp5(uint8_t bool)
{
	adc_setreg(&ADC3->SMPR2, 2, 16, bool);
}
void STM32446ADC3_smpr2_smp5_0(uint8_t bool)
{
	adc_setreg(&ADC3->SMPR2, 1, 15, bool);
}
void STM32446ADC3_smpr2_smp4(uint8_t value)
{
	adc_setreg(&ADC3->SMPR2, 3, 12, value);
}
void STM32446ADC3_smpr2_smp3(uint8_t value)
{
	adc_setreg(&ADC3->SMPR2, 3, 9, value);
}
void STM32446ADC3_smpr2_smp2(uint8_t value)
{
	adc_setreg(&ADC3->SMPR2, 3, 6, value);
}
void STM32446ADC3_smpr2_smp1(uint8_t value)
{
	adc_setreg(&ADC3->SMPR2, 3, 3, value);
}
void STM32446ADC3_smpr2_smp0(uint8_t value)
{
	adc_setreg(&ADC3->SMPR2, 3, 0, value);
}

// Other
void STM32446ADC3_jofr1(uint16_t value)
{
	adc_setreg(&ADC3->JOFR1, 12, 0, value);
}
void STM32446ADC3_jofr2(uint16_t value)
{
	adc_setreg(&ADC3->JOFR2, 12, 0, value);
}
void STM32446ADC3_jofr3(uint16_t value)
{
	adc_setreg(&ADC3->JOFR3, 12, 0, value);
}
void STM32446ADC3_jofr4(uint16_t value)
{
	adc_setreg(&ADC3->JOFR4, 12, 0, value);
}
void STM32446ADC3_htr(uint16_t value)
{
	adc_setreg(&ADC3->HTR, 12, 0, value);
}
void STM32446ADC3_ltr(uint16_t value)
{
	adc_setreg(&ADC3->LTR, 12, 0, value);
}

// SQR1
void STM32446ADC3_sqr1_l(uint8_t value)
{
	adc_setreg(&ADC3->SQR1, 4, 20, value);
}
void STM32446ADC3_sqr1_sq16(uint8_t value)
{
	adc_setreg(&ADC3->SQR1, 4, 16, value);
}
void STM32446ADC3_sqr1_sq16_0(uint8_t bool)
{
	adc_setreg(&ADC3->SQR1, 1, 15, bool);
}
void STM32446ADC3_sqr1_sq15(uint8_t value)
{
	adc_setreg(&ADC3->SQR1, 5, 10, value);
}
void STM32446ADC3_sqr1_sq14(uint8_t value)
{
	adc_setreg(&ADC3->SQR1, 5, 5, value);
}
void STM32446ADC3_sqr1_sq13(uint8_t value)
{
	adc_setreg(&ADC3->SQR1, 5, 0, value);
}

// SQR2
void STM32446ADC3_sqr2_sq12(uint8_t value)
{
	adc_setreg(&ADC3->SQR2, 5, 25, value);
}
void STM32446ADC3_sqr2_sq11(uint8_t value)
{
	adc_setreg(&ADC3->SQR2, 5, 20, value);
}
void STM32446ADC3_sqr2_sq10(uint8_t value)
{
	adc_setreg(&ADC3->SQR2, 4, 16, value);
}
void STM32446ADC3_sqr2_sq10_0(uint8_t bool)
{
	adc_setreg(&ADC3->SQR2, 1, 15, bool);
}
void STM32446ADC3_sqr2_sq9(uint8_t value)
{
	adc_setreg(&ADC3->SQR2, 5, 10, value);
}
void STM32446ADC3_sqr2_sq8(uint8_t value)
{
	adc_setreg(&ADC3->SQR2, 5, 5, value);
}
void STM32446ADC3_sqr2_sq7(uint8_t value)
{
	adc_setreg(&ADC3->SQR2, 5, 0, value);
}

// SQR3
void STM32446ADC3_sqr3_sq6(uint8_t value)
{
	adc_setreg(&ADC3->SQR3, 5, 25, value);
}
void STM32446ADC3_sqr3_sq5(uint8_t value)
{
	adc_setreg(&ADC3->SQR3, 5, 20, value);
}
void STM32446ADC3_sqr3_sq4(uint8_t value)
{
	adc_setreg(&ADC3->SQR3, 4, 16, value);
}
void STM32446ADC3_sqr3_sq4_0(uint8_t bool)
{
	adc_setreg(&ADC3->SQR3, 1, 15, bool);
}
void STM32446ADC3_sqr3_sq3(uint8_t value)
{
	adc_setreg(&ADC3->SQR3, 5, 10, value);
}
void STM32446ADC3_sqr3_sq2(uint8_t value)
{
	adc_setreg(&ADC3->SQR3, 5, 5, value);
}
void STM32446ADC3_sqr3_sq1(uint8_t value)
{
	adc_setreg(&ADC3->SQR3, 5, 0, value);
}

// JSQR
void STM32446ADC3_jsqr_jl(uint8_t value)
{
	adc_setreg(&ADC3->JSQR, 2, 20, value);
}
void STM32446ADC3_jsqr_jsq4(uint8_t value)
{
	adc_setreg(&ADC3->JSQR, 4, 16, value);
}
void STM32446ADC3_jsqr_jsq4_0(uint8_t bool)
{
	adc_setreg(&ADC3->JSQR, 1, 15, bool);
}
void STM32446ADC3_jsqr_jsq3(uint8_t value)
{
	adc_setreg(&ADC3->JSQR, 5, 10, value);
}
void STM32446ADC3_jsqr_jsq2(uint8_t value)
{
	adc_setreg(&ADC3->JSQR, 5, 5, value);
}
void STM32446ADC3_jsqr_jsq1(uint8_t value)
{
	adc_setreg(&ADC3->JSQR, 5, 0, value);
}

// Other
uint16_t STM32446ADC3_jdr1(void)
{
	return adc_readreg(ADC3->JDR1, 16, 0);
}
uint16_t STM32446ADC3_jdr2(void)
{
	return adc_readreg(ADC3->JDR2, 16, 0);
}
uint16_t STM32446ADC3_jdr3(void)
{
	return adc_readreg(ADC3->JDR3, 16, 0);
}
uint16_t STM32446ADC3_jdr4(void)
{
	return adc_readreg(ADC3->JDR4, 16, 0);
}
uint16_t STM32446ADC3_dr(void)
{
	return adc_readreg(ADC3->DR, 16, 0);
}

/*** COMMON ***/
// CSR
uint8_t STM32446ADC_csr_ovr3(void)
{
	return adc_readreg(ADC->CSR, 1, 21);
}
uint8_t STM32446ADC_csr_strt3(void)
{
	return adc_readreg(ADC->CSR, 1, 20);
}
uint8_t STM32446ADC_csr_jstrt3(void)
{
	return adc_readreg(ADC->CSR, 1, 19);
}
uint8_t STM32446ADC_csr_jeoc3(void)
{
	return adc_readreg(ADC->CSR, 1, 18);
}
uint8_t STM32446ADC_csr_eoc3(void)
{
	return adc_readreg(ADC->CSR, 1, 17);
}
uint8_t STM32446ADC_csr_awd3(void)
{
	return adc_readreg(ADC->CSR, 1, 16);
}
uint8_t STM32446ADC_csr_ovr2(void)
{
	return adc_readreg(ADC->CSR, 1, 13);
}
uint8_t STM32446ADC_csr_strt2(void)
{
	return adc_readreg(ADC->CSR, 1, 12);
}
uint8_t STM32446ADC_csr_jstrt2(void)
{
	return adc_readreg(ADC->CSR, 1, 11);
}
uint8_t STM32446ADC_csr_jeoc2(void)
{
	return adc_readreg(ADC->CSR, 1, 10);
}
uint8_t STM32446ADC_csr_eoc2(void)
{
	return adc_readreg(ADC->CSR, 1, 9);
}
uint8_t STM32446ADC_csr_awd2(void)
{
	return adc_readreg(ADC->CSR, 1, 8);
}
uint8_t STM32446ADC_csr_ovr1(void)
{
	return adc_readreg(ADC->CSR, 1, 5);
}
uint8_t STM32446ADC_csr_strt1(void)
{
	return adc_readreg(ADC->CSR, 1, 4);
}
uint8_t STM32446ADC_csr_jstrt1(void)
{
	return adc_readreg(ADC->CSR, 1, 3);
}
uint8_t STM32446ADC_csr_jeoc1(void)
{
	return adc_readreg(ADC->CSR, 1, 2);
}
uint8_t STM32446ADC_csr_eoc1(void)
{
	return adc_readreg(ADC->CSR, 1, 1);
}
uint8_t STM32446ADC_csr_awd1(void)
{
	return adc_readreg(ADC->CSR, 1, 0);
}

// CCR
void STM32446ADC_ccr_tsvrefe(uint8_t bool)
{
	adc_setreg(&ADC->CCR, 1, 23, bool);
}
void STM32446ADC_ccr_vbate(uint8_t bool)
{
	adc_setreg(&ADC->CCR, 2, 22, bool);
}
void STM32446ADC_ccr_adcpre(uint8_t value)
{
	adc_setreg(&ADC->CCR, 2, 16, value);
}
void STM32446ADC_ccr_dma(uint8_t value)
{
	adc_setreg(&ADC->CCR, 2, 14, value);
}
void STM32446ADC_ccr_dds(uint8_t bool)
{
	adc_setreg(&ADC->CCR, 1, 13, bool);
}
void STM32446ADC_ccr_delay(uint8_t value)
{
	adc_setreg(&ADC->CCR, 4, 8, value);
}
void STM32446ADC_ccr_multi(uint8_t value)
{
	adc_setreg(&ADC->CCR, 5, 0, value);
}

// CDR
uint32_t STM32446ADC_cdr(void)
{
	return adc_readreg(ADC->CDR, 32, 0);
}

/*** ADC3 ***/
void STM32446Adc3Clock(void)
{
	RCC->APB2ENR |= (1 << 10); // ADC1EN: ADC1 clock enable
}

/*** INIC Procedure & Function Definition ***/
STM32446ADC1obj adc1_inic(void)
{
	STM32446ADC1obj adc1_setup;

	adc1_setup.common.reg = ADC123_COMMON;
	adc1_setup.reg = ADC1;
	/*** ADC1 Bit Mapping Link ***/
	// SR
	adc1_setup.sr.ovr = STM32446ADC1_sr_ovr;
	adc1_setup.sr.clear_ovr = STM32446ADC1_sr_clear_ovr;
	adc1_setup.sr.strt = STM32446ADC1_sr_strt;
	adc1_setup.sr.clear_strt = STM32446ADC1_sr_clear_strt;
	adc1_setup.sr.jstrt = STM32446ADC1_sr_jstrt;
	adc1_setup.sr.clear_jstrt = STM32446ADC1_sr_clear_jstrt;
	adc1_setup.sr.jeoc = STM32446ADC1_sr_jeoc;
	adc1_setup.sr.clear_jeoc = STM32446ADC1_sr_clear_jeoc;
	adc1_setup.sr.eoc = STM32446ADC1_sr_eoc;
	adc1_setup.sr.clear_eoc = STM32446ADC1_sr_clear_eoc;
	adc1_setup.sr.awd =  STM32446ADC1_sr_awd;
	adc1_setup.sr.clear_awd = STM32446ADC1_sr_clear_awd;
	// CR1
	adc1_setup.cr1.ovrie = STM32446ADC1_cr1_ovrie;
	adc1_setup.cr1.res = STM32446ADC1_cr1_res;
	adc1_setup.cr1.awden = STM32446ADC1_cr1_awden;
	adc1_setup.cr1.jawden = STM32446ADC1_cr1_jawden;
	adc1_setup.cr1.discnum = STM32446ADC1_cr1_discnum;
	adc1_setup.cr1.jdiscen = STM32446ADC1_cr1_jdiscen;
	adc1_setup.cr1.discen = STM32446ADC1_cr1_discen;
	adc1_setup.cr1.jauto = STM32446ADC1_cr1_jauto;
	adc1_setup.cr1.awdsgl = STM32446ADC1_cr1_awdsgl;
	adc1_setup.cr1.scan = STM32446ADC1_cr1_scan;
	adc1_setup.cr1.jeocie = STM32446ADC1_cr1_jeocie;
	adc1_setup.cr1.awdie = STM32446ADC1_cr1_awdie;
	adc1_setup.cr1.eocie = STM32446ADC1_cr1_eocie;
	adc1_setup.cr1.awdch = STM32446ADC1_cr1_awdch;
	// CR2
	adc1_setup.cr2.swstart = STM32446ADC1_cr2_swstart;
	adc1_setup.cr2.exten = STM32446ADC1_cr2_exten;
	adc1_setup.cr2.extsel = STM32446ADC1_cr2_extsel;
	adc1_setup.cr2.jswstart = STM32446ADC1_cr2_jswstart;
	adc1_setup.cr2.jexten = STM32446ADC1_cr2_jexten;
	adc1_setup.cr2.jextsel = STM32446ADC1_cr2_jextsel;
	adc1_setup.cr2.align = STM32446ADC1_cr2_align;
	adc1_setup.cr2.eocs = STM32446ADC1_cr2_eocs;
	adc1_setup.cr2.dds = STM32446ADC1_cr2_dds;
	adc1_setup.cr2.dma = STM32446ADC1_cr2_dma;
	adc1_setup.cr2.cont = STM32446ADC1_cr2_cont;
	adc1_setup.cr2.adon = STM32446ADC1_cr2_adon;
	// SMPR1
	adc1_setup.smpr1.smp18 = STM32446ADC1_smpr1_smp18;
	adc1_setup.smpr1.smp17 = STM32446ADC1_smpr1_smp17;
	adc1_setup.smpr1.smp16 = STM32446ADC1_smpr1_smp16;
	adc1_setup.smpr1.smp15 = STM32446ADC1_smpr1_smp15;
	adc1_setup.smpr1.smp15_0 = STM32446ADC1_smpr1_smp15_0;
	adc1_setup.smpr1.smp14 = STM32446ADC1_smpr1_smp14;
	adc1_setup.smpr1.smp13 = STM32446ADC1_smpr1_smp13;
	adc1_setup.smpr1.smp12 = STM32446ADC1_smpr1_smp12;
	adc1_setup.smpr1.smp11 = STM32446ADC1_smpr1_smp11;
	adc1_setup.smpr1.smp10 = STM32446ADC1_smpr1_smp10;
	// SMPR2
	adc1_setup.smpr2.smp9 = STM32446ADC1_smpr2_smp9;
	adc1_setup.smpr2.smp8 = STM32446ADC1_smpr2_smp8;
	adc1_setup.smpr2.smp7 = STM32446ADC1_smpr2_smp7;
	adc1_setup.smpr2.smp6 = STM32446ADC1_smpr2_smp6;
	adc1_setup.smpr2.smp5 = STM32446ADC1_smpr2_smp5;
	adc1_setup.smpr2.smp5_0 = STM32446ADC1_smpr2_smp5_0;
	adc1_setup.smpr2.smp4 = STM32446ADC1_smpr2_smp4;
	adc1_setup.smpr2.smp3 = STM32446ADC1_smpr2_smp3;
	adc1_setup.smpr2.smp2 = STM32446ADC1_smpr2_smp2;
	adc1_setup.smpr2.smp1 = STM32446ADC1_smpr2_smp1;
	adc1_setup.smpr2.smp0 = STM32446ADC1_smpr2_smp0;
	// JOFR1
	adc1_setup.jofr1 = STM32446ADC1_jofr1;
	// JOFR2
	adc1_setup.jofr2 = STM32446ADC1_jofr2;
	// JOFR3
	adc1_setup.jofr3 = STM32446ADC1_jofr3;
	// JOFR4
	adc1_setup.jofr4 = STM32446ADC1_jofr4;
	// HTR
	adc1_setup.htr = STM32446ADC1_htr;
	// LTR
	adc1_setup.ltr = STM32446ADC1_ltr;
	// SQR1
	adc1_setup.sqr1.l = STM32446ADC1_sqr1_l;
	adc1_setup.sqr1.sq16 = STM32446ADC1_sqr1_sq16;
	adc1_setup.sqr1.sq16_0 = STM32446ADC1_sqr1_sq16_0;
	adc1_setup.sqr1.sq15 = STM32446ADC1_sqr1_sq15;
	adc1_setup.sqr1.sq14 = STM32446ADC1_sqr1_sq14;
	adc1_setup.sqr1.sq13 = STM32446ADC1_sqr1_sq13;
	// SQR2
	adc1_setup.sqr2.sq12 = STM32446ADC1_sqr2_sq12;
	adc1_setup.sqr2.sq11 = STM32446ADC1_sqr2_sq11;
	adc1_setup.sqr2.sq10 = STM32446ADC1_sqr2_sq10;
	adc1_setup.sqr2.sq10_0 = STM32446ADC1_sqr2_sq10_0;
	adc1_setup.sqr2.sq9 = STM32446ADC1_sqr2_sq9;
	adc1_setup.sqr2.sq8 = STM32446ADC1_sqr2_sq8;
	adc1_setup.sqr2.sq7 = STM32446ADC1_sqr2_sq7;
	// SQ3
	adc1_setup.sqr3.sq6 = STM32446ADC1_sqr3_sq6;
	adc1_setup.sqr3.sq5 = STM32446ADC1_sqr3_sq5;
	adc1_setup.sqr3.sq4 = STM32446ADC1_sqr3_sq4;
	adc1_setup.sqr3.sq4_0 = STM32446ADC1_sqr3_sq4_0;
	adc1_setup.sqr3.sq3 = STM32446ADC1_sqr3_sq3;
	adc1_setup.sqr3.sq2 = STM32446ADC1_sqr3_sq2;
	adc1_setup.sqr3.sq1 = STM32446ADC1_sqr3_sq1;
	// JSQR
	adc1_setup.jsqr.jl = STM32446ADC1_jsqr_jl;
	adc1_setup.jsqr.jsq4 = STM32446ADC1_jsqr_jsq4;
	adc1_setup.jsqr.jsq4_0 = STM32446ADC1_jsqr_jsq4_0;
	adc1_setup.jsqr.jsq3 = STM32446ADC1_jsqr_jsq3;
	adc1_setup.jsqr.jsq2 = STM32446ADC1_jsqr_jsq2;
	adc1_setup.jsqr.jsq1 = STM32446ADC1_jsqr_jsq1;
	// JDR1
	adc1_setup.jdr1 = STM32446ADC1_jdr1;
	// JDR2
	adc1_setup.jdr2 = STM32446ADC1_jdr2;
	// JDR3
	adc1_setup.jdr3 = STM32446ADC1_jdr3;
	// JDR4
	adc1_setup.jdr4 = STM32446ADC1_jdr4;
	// DR
	adc1_setup.dr = STM32446ADC1_dr;
	// CSR
	adc1_setup.common.csr.ovr3 = STM32446ADC_csr_ovr3;
	adc1_setup.common.csr.strt3 = STM32446ADC_csr_strt3;
	adc1_setup.common.csr.jstrt3 = STM32446ADC_csr_jstrt3;
	adc1_setup.common.csr.jeoc3 = STM32446ADC_csr_jeoc3;
	adc1_setup.common.csr.eoc3 = STM32446ADC_csr_eoc3;
	adc1_setup.common.csr.awd3 = STM32446ADC_csr_awd3;
	adc1_setup.common.csr.ovr2 = STM32446ADC_csr_ovr2;
	adc1_setup.common.csr.strt2 = STM32446ADC_csr_strt2;
	adc1_setup.common.csr.jstrt2 = STM32446ADC_csr_jstrt2;
	adc1_setup.common.csr.jeoc2 = STM32446ADC_csr_jeoc2;
	adc1_setup.common.csr.eoc2 = STM32446ADC_csr_eoc2;
	adc1_setup.common.csr.awd2 = STM32446ADC_csr_awd2;
	adc1_setup.common.csr.ovr1 = STM32446ADC_csr_ovr1;
	adc1_setup.common.csr.strt1 = STM32446ADC_csr_strt1;
	adc1_setup.common.csr.jstrt1 = STM32446ADC_csr_jstrt1;
	adc1_setup.common.csr.jeoc1 = STM32446ADC_csr_jeoc1;
	adc1_setup.common.csr.eoc1 = STM32446ADC_csr_eoc1;
	adc1_setup.common.csr.awd1 = STM32446ADC_csr_awd1;
	// CCR
	adc1_setup.common.ccr.tsvrefe = STM32446ADC_ccr_tsvrefe;
	adc1_setup.common.ccr.vbate = STM32446ADC_ccr_vbate;
	adc1_setup.common.ccr.adcpre = STM32446ADC_ccr_adcpre;
	adc1_setup.common.ccr.dma = STM32446ADC_ccr_dma;
	adc1_setup.common.ccr.dds = STM32446ADC_ccr_dds;
	adc1_setup.common.ccr.delay = STM32446ADC_ccr_delay;
	adc1_setup.common.ccr.multi = STM32446ADC_ccr_multi;
	// CDR
	adc1_setup.common.cdr = STM32446ADC_cdr;
	/*** Other ***/
	adc1_setup.single.inic = STM32446Adc1Inic;
	adc1_setup.single.vbat = STM32446Adc1VBAT;
	adc1_setup.single.temp = STM32446Adc1TEMP;
	adc1_setup.single.start = STM32446Adc1Start;
	adc1_setup.single.read = STM32446Adc1Read;
	adc1_setup.single.restart = STM32446Adc1Restart;
	adc1_setup.single.stop = STM32446Adc1Stop;
	adc1_setup.clock = STM32446Adc1Clock;

	return adc1_setup;
}

STM32446ADC2obj adc2_inic(void)
{
	STM32446ADC2obj adc2_setup;

	adc2_setup.common.reg = ADC123_COMMON;
	adc2_setup.reg = ADC2;
	/*** ADC2 Bit Mapping Link ***/
	// SR
	adc2_setup.sr.ovr = STM32446ADC2_sr_ovr;
	adc2_setup.sr.clear_ovr = STM32446ADC2_sr_clear_ovr;
	adc2_setup.sr.strt = STM32446ADC2_sr_strt;
	adc2_setup.sr.clear_strt = STM32446ADC2_sr_clear_strt;
	adc2_setup.sr.jstrt = STM32446ADC2_sr_jstrt;
	adc2_setup.sr.clear_jstrt = STM32446ADC2_sr_clear_jstrt;
	adc2_setup.sr.jeoc = STM32446ADC2_sr_jeoc;
	adc2_setup.sr.clear_jeoc = STM32446ADC2_sr_clear_jeoc;
	adc2_setup.sr.eoc = STM32446ADC2_sr_eoc;
	adc2_setup.sr.clear_eoc = STM32446ADC2_sr_clear_eoc;
	adc2_setup.sr.awd =  STM32446ADC2_sr_awd;
	adc2_setup.sr.clear_awd = STM32446ADC2_sr_clear_awd;
	// CR1
	adc2_setup.cr1.ovrie = STM32446ADC2_cr1_ovrie;
	adc2_setup.cr1.res = STM32446ADC2_cr1_res;
	adc2_setup.cr1.awden = STM32446ADC2_cr1_awden;
	adc2_setup.cr1.jawden = STM32446ADC2_cr1_jawden;
	adc2_setup.cr1.discnum = STM32446ADC2_cr1_discnum;
	adc2_setup.cr1.jdiscen = STM32446ADC2_cr1_jdiscen;
	adc2_setup.cr1.discen = STM32446ADC2_cr1_discen;
	adc2_setup.cr1.jauto = STM32446ADC2_cr1_jauto;
	adc2_setup.cr1.awdsgl = STM32446ADC2_cr1_awdsgl;
	adc2_setup.cr1.scan = STM32446ADC2_cr1_scan;
	adc2_setup.cr1.jeocie = STM32446ADC2_cr1_jeocie;
	adc2_setup.cr1.awdie = STM32446ADC2_cr1_awdie;
	adc2_setup.cr1.eocie = STM32446ADC2_cr1_eocie;
	adc2_setup.cr1.awdch = STM32446ADC2_cr1_awdch;
	// CR2
	adc2_setup.cr2.swstart = STM32446ADC2_cr2_swstart;
	adc2_setup.cr2.exten = STM32446ADC2_cr2_exten;
	adc2_setup.cr2.extsel = STM32446ADC2_cr2_extsel;
	adc2_setup.cr2.jswstart = STM32446ADC2_cr2_jswstart;
	adc2_setup.cr2.jexten = STM32446ADC2_cr2_jexten;
	adc2_setup.cr2.jextsel = STM32446ADC2_cr2_jextsel;
	adc2_setup.cr2.align = STM32446ADC2_cr2_align;
	adc2_setup.cr2.eocs = STM32446ADC2_cr2_eocs;
	adc2_setup.cr2.dds = STM32446ADC2_cr2_dds;
	adc2_setup.cr2.dma = STM32446ADC2_cr2_dma;
	adc2_setup.cr2.cont = STM32446ADC2_cr2_cont;
	adc2_setup.cr2.adon = STM32446ADC2_cr2_adon;
	// SMPR1
	adc2_setup.smpr1.smp18 = STM32446ADC2_smpr1_smp18;
	adc2_setup.smpr1.smp17 = STM32446ADC2_smpr1_smp17;
	adc2_setup.smpr1.smp16 = STM32446ADC2_smpr1_smp16;
	adc2_setup.smpr1.smp15 = STM32446ADC2_smpr1_smp15;
	adc2_setup.smpr1.smp15_0 = STM32446ADC2_smpr1_smp15_0;
	adc2_setup.smpr1.smp14 = STM32446ADC2_smpr1_smp14;
	adc2_setup.smpr1.smp13 = STM32446ADC2_smpr1_smp13;
	adc2_setup.smpr1.smp12 = STM32446ADC2_smpr1_smp12;
	adc2_setup.smpr1.smp11 = STM32446ADC2_smpr1_smp11;
	adc2_setup.smpr1.smp10 = STM32446ADC2_smpr1_smp10;
	// SMPR2
	adc2_setup.smpr2.smp9 = STM32446ADC2_smpr2_smp9;
	adc2_setup.smpr2.smp8 = STM32446ADC2_smpr2_smp8;
	adc2_setup.smpr2.smp7 = STM32446ADC2_smpr2_smp7;
	adc2_setup.smpr2.smp6 = STM32446ADC2_smpr2_smp6;
	adc2_setup.smpr2.smp5 = STM32446ADC2_smpr2_smp5;
	adc2_setup.smpr2.smp5_0 = STM32446ADC2_smpr2_smp5_0;
	adc2_setup.smpr2.smp4 = STM32446ADC2_smpr2_smp4;
	adc2_setup.smpr2.smp3 = STM32446ADC2_smpr2_smp3;
	adc2_setup.smpr2.smp2 = STM32446ADC2_smpr2_smp2;
	adc2_setup.smpr2.smp1 = STM32446ADC2_smpr2_smp1;
	adc2_setup.smpr2.smp0 = STM32446ADC2_smpr2_smp0;
	// JOFR1
	adc2_setup.jofr1 = STM32446ADC2_jofr1;
	// JOFR2
	adc2_setup.jofr2 = STM32446ADC2_jofr2;
	// JOFR3
	adc2_setup.jofr3 = STM32446ADC2_jofr3;
	// JOFR4
	adc2_setup.jofr4 = STM32446ADC2_jofr4;
	// HTR
	adc2_setup.htr = STM32446ADC2_htr;
	// LTR
	adc2_setup.ltr = STM32446ADC2_ltr;
	// SQR1
	adc2_setup.sqr1.l = STM32446ADC2_sqr1_l;
	adc2_setup.sqr1.sq16 = STM32446ADC2_sqr1_sq16;
	adc2_setup.sqr1.sq16_0 = STM32446ADC2_sqr1_sq16_0;
	adc2_setup.sqr1.sq15 = STM32446ADC2_sqr1_sq15;
	adc2_setup.sqr1.sq14 = STM32446ADC2_sqr1_sq14;
	adc2_setup.sqr1.sq13 = STM32446ADC2_sqr1_sq13;
	// SQR2
	adc2_setup.sqr2.sq12 = STM32446ADC2_sqr2_sq12;
	adc2_setup.sqr2.sq11 = STM32446ADC2_sqr2_sq11;
	adc2_setup.sqr2.sq10 = STM32446ADC2_sqr2_sq10;
	adc2_setup.sqr2.sq10_0 = STM32446ADC2_sqr2_sq10_0;
	adc2_setup.sqr2.sq9 = STM32446ADC2_sqr2_sq9;
	adc2_setup.sqr2.sq8 = STM32446ADC2_sqr2_sq8;
	adc2_setup.sqr2.sq7 = STM32446ADC2_sqr2_sq7;
	// SQ3
	adc2_setup.sqr3.sq6 = STM32446ADC2_sqr3_sq6;
	adc2_setup.sqr3.sq5 = STM32446ADC2_sqr3_sq5;
	adc2_setup.sqr3.sq4 = STM32446ADC2_sqr3_sq4;
	adc2_setup.sqr3.sq4_0 = STM32446ADC2_sqr3_sq4_0;
	adc2_setup.sqr3.sq3 = STM32446ADC2_sqr3_sq3;
	adc2_setup.sqr3.sq2 = STM32446ADC2_sqr3_sq2;
	adc2_setup.sqr3.sq1 = STM32446ADC2_sqr3_sq1;
	// JSQR
	adc2_setup.jsqr.jl = STM32446ADC2_jsqr_jl;
	adc2_setup.jsqr.jsq4 = STM32446ADC2_jsqr_jsq4;
	adc2_setup.jsqr.jsq4_0 = STM32446ADC2_jsqr_jsq4_0;
	adc2_setup.jsqr.jsq3 = STM32446ADC2_jsqr_jsq3;
	adc2_setup.jsqr.jsq2 = STM32446ADC2_jsqr_jsq2;
	adc2_setup.jsqr.jsq1 = STM32446ADC2_jsqr_jsq1;
	// JDR1
	adc2_setup.jdr1 = STM32446ADC2_jdr1;
	// JDR2
	adc2_setup.jdr2 = STM32446ADC2_jdr2;
	// JDR3
	adc2_setup.jdr3 = STM32446ADC2_jdr3;
	// JDR4
	adc2_setup.jdr4 = STM32446ADC2_jdr4;
	// DR
	adc2_setup.dr = STM32446ADC2_dr;
	// CSR
	adc2_setup.common.csr.ovr3 = STM32446ADC_csr_ovr3;
	adc2_setup.common.csr.strt3 = STM32446ADC_csr_strt3;
	adc2_setup.common.csr.jstrt3 = STM32446ADC_csr_jstrt3;
	adc2_setup.common.csr.jeoc3 = STM32446ADC_csr_jeoc3;
	adc2_setup.common.csr.eoc3 = STM32446ADC_csr_eoc3;
	adc2_setup.common.csr.awd3 = STM32446ADC_csr_awd3;
	adc2_setup.common.csr.ovr2 = STM32446ADC_csr_ovr2;
	adc2_setup.common.csr.strt2 = STM32446ADC_csr_strt2;
	adc2_setup.common.csr.jstrt2 = STM32446ADC_csr_jstrt2;
	adc2_setup.common.csr.jeoc2 = STM32446ADC_csr_jeoc2;
	adc2_setup.common.csr.eoc2 = STM32446ADC_csr_eoc2;
	adc2_setup.common.csr.awd2 = STM32446ADC_csr_awd2;
	adc2_setup.common.csr.ovr1 = STM32446ADC_csr_ovr1;
	adc2_setup.common.csr.strt1 = STM32446ADC_csr_strt1;
	adc2_setup.common.csr.jstrt1 = STM32446ADC_csr_jstrt1;
	adc2_setup.common.csr.jeoc1 = STM32446ADC_csr_jeoc1;
	adc2_setup.common.csr.eoc1 = STM32446ADC_csr_eoc1;
	adc2_setup.common.csr.awd1 = STM32446ADC_csr_awd1;
	// CCR
	adc2_setup.common.ccr.tsvrefe = STM32446ADC_ccr_tsvrefe;
	adc2_setup.common.ccr.vbate = STM32446ADC_ccr_vbate;
	adc2_setup.common.ccr.adcpre = STM32446ADC_ccr_adcpre;
	adc2_setup.common.ccr.dma = STM32446ADC_ccr_dma;
	adc2_setup.common.ccr.dds = STM32446ADC_ccr_dds;
	adc2_setup.common.ccr.delay = STM32446ADC_ccr_delay;
	adc2_setup.common.ccr.multi = STM32446ADC_ccr_multi;
	// CDR
	adc2_setup.common.cdr = STM32446ADC_cdr;
	// Other
	adc2_setup.clock = STM32446Adc2Clock;

	return adc2_setup;
}

STM32446ADC3obj adc3_inic(void)
{
	STM32446ADC3obj adc3_setup;

	adc3_setup.common.reg = ADC123_COMMON;
	adc3_setup.reg = ADC3;
	/*** ADC3 Bit Mapping Link ***/
	// SR
	adc3_setup.sr.ovr = STM32446ADC3_sr_ovr;
	adc3_setup.sr.clear_ovr = STM32446ADC3_sr_clear_ovr;
	adc3_setup.sr.strt = STM32446ADC3_sr_strt;
	adc3_setup.sr.clear_strt = STM32446ADC3_sr_clear_strt;
	adc3_setup.sr.jstrt = STM32446ADC3_sr_jstrt;
	adc3_setup.sr.clear_jstrt = STM32446ADC3_sr_clear_jstrt;
	adc3_setup.sr.jeoc = STM32446ADC3_sr_jeoc;
	adc3_setup.sr.clear_jeoc = STM32446ADC3_sr_clear_jeoc;
	adc3_setup.sr.eoc = STM32446ADC3_sr_eoc;
	adc3_setup.sr.clear_eoc = STM32446ADC3_sr_clear_eoc;
	adc3_setup.sr.awd =  STM32446ADC3_sr_awd;
	adc3_setup.sr.clear_awd = STM32446ADC3_sr_clear_awd;
	// CR1
	adc3_setup.cr1.ovrie = STM32446ADC3_cr1_ovrie;
	adc3_setup.cr1.res = STM32446ADC3_cr1_res;
	adc3_setup.cr1.awden = STM32446ADC3_cr1_awden;
	adc3_setup.cr1.jawden = STM32446ADC3_cr1_jawden;
	adc3_setup.cr1.discnum = STM32446ADC3_cr1_discnum;
	adc3_setup.cr1.jdiscen = STM32446ADC3_cr1_jdiscen;
	adc3_setup.cr1.discen = STM32446ADC3_cr1_discen;
	adc3_setup.cr1.jauto = STM32446ADC3_cr1_jauto;
	adc3_setup.cr1.awdsgl = STM32446ADC3_cr1_awdsgl;
	adc3_setup.cr1.scan = STM32446ADC3_cr1_scan;
	adc3_setup.cr1.jeocie = STM32446ADC3_cr1_jeocie;
	adc3_setup.cr1.awdie = STM32446ADC3_cr1_awdie;
	adc3_setup.cr1.eocie = STM32446ADC3_cr1_eocie;
	adc3_setup.cr1.awdch = STM32446ADC3_cr1_awdch;
	// CR2
	adc3_setup.cr2.swstart = STM32446ADC3_cr2_swstart;
	adc3_setup.cr2.exten = STM32446ADC3_cr2_exten;
	adc3_setup.cr2.extsel = STM32446ADC3_cr2_extsel;
	adc3_setup.cr2.jswstart = STM32446ADC3_cr2_jswstart;
	adc3_setup.cr2.jexten = STM32446ADC3_cr2_jexten;
	adc3_setup.cr2.jextsel = STM32446ADC3_cr2_jextsel;
	adc3_setup.cr2.align = STM32446ADC3_cr2_align;
	adc3_setup.cr2.eocs = STM32446ADC3_cr2_eocs;
	adc3_setup.cr2.dds = STM32446ADC3_cr2_dds;
	adc3_setup.cr2.dma = STM32446ADC3_cr2_dma;
	adc3_setup.cr2.cont = STM32446ADC3_cr2_cont;
	adc3_setup.cr2.adon = STM32446ADC3_cr2_adon;
	// SMPR1
	adc3_setup.smpr1.smp18 = STM32446ADC3_smpr1_smp18;
	adc3_setup.smpr1.smp17 = STM32446ADC3_smpr1_smp17;
	adc3_setup.smpr1.smp16 = STM32446ADC3_smpr1_smp16;
	adc3_setup.smpr1.smp15 = STM32446ADC3_smpr1_smp15;
	adc3_setup.smpr1.smp15_0 = STM32446ADC3_smpr1_smp15_0;
	adc3_setup.smpr1.smp14 = STM32446ADC3_smpr1_smp14;
	adc3_setup.smpr1.smp13 = STM32446ADC3_smpr1_smp13;
	adc3_setup.smpr1.smp12 = STM32446ADC3_smpr1_smp12;
	adc3_setup.smpr1.smp11 = STM32446ADC3_smpr1_smp11;
	adc3_setup.smpr1.smp10 = STM32446ADC3_smpr1_smp10;
	// SMPR2
	adc3_setup.smpr2.smp9 = STM32446ADC3_smpr2_smp9;
	adc3_setup.smpr2.smp8 = STM32446ADC3_smpr2_smp8;
	adc3_setup.smpr2.smp7 = STM32446ADC3_smpr2_smp7;
	adc3_setup.smpr2.smp6 = STM32446ADC3_smpr2_smp6;
	adc3_setup.smpr2.smp5 = STM32446ADC3_smpr2_smp5;
	adc3_setup.smpr2.smp5_0 = STM32446ADC3_smpr2_smp5_0;
	adc3_setup.smpr2.smp4 = STM32446ADC3_smpr2_smp4;
	adc3_setup.smpr2.smp3 = STM32446ADC3_smpr2_smp3;
	adc3_setup.smpr2.smp2 = STM32446ADC3_smpr2_smp2;
	adc3_setup.smpr2.smp1 = STM32446ADC3_smpr2_smp1;
	adc3_setup.smpr2.smp0 = STM32446ADC3_smpr2_smp0;
	// JOFR1
	adc3_setup.jofr1 = STM32446ADC3_jofr1;
	// JOFR2
	adc3_setup.jofr2 = STM32446ADC3_jofr2;
	// JOFR3
	adc3_setup.jofr3 = STM32446ADC3_jofr3;
	// JOFR4
	adc3_setup.jofr4 = STM32446ADC3_jofr4;
	// HTR
	adc3_setup.htr = STM32446ADC3_htr;
	// LTR
	adc3_setup.ltr = STM32446ADC3_ltr;
	// SQR1
	adc3_setup.sqr1.l = STM32446ADC3_sqr1_l;
	adc3_setup.sqr1.sq16 = STM32446ADC3_sqr1_sq16;
	adc3_setup.sqr1.sq16_0 = STM32446ADC3_sqr1_sq16_0;
	adc3_setup.sqr1.sq15 = STM32446ADC3_sqr1_sq15;
	adc3_setup.sqr1.sq14 = STM32446ADC3_sqr1_sq14;
	adc3_setup.sqr1.sq13 = STM32446ADC3_sqr1_sq13;
	// SQR2
	adc3_setup.sqr2.sq12 = STM32446ADC3_sqr2_sq12;
	adc3_setup.sqr2.sq11 = STM32446ADC3_sqr2_sq11;
	adc3_setup.sqr2.sq10 = STM32446ADC3_sqr2_sq10;
	adc3_setup.sqr2.sq10_0 = STM32446ADC3_sqr2_sq10_0;
	adc3_setup.sqr2.sq9 = STM32446ADC3_sqr2_sq9;
	adc3_setup.sqr2.sq8 = STM32446ADC3_sqr2_sq8;
	adc3_setup.sqr2.sq7 = STM32446ADC3_sqr2_sq7;
	// SQ3
	adc3_setup.sqr3.sq6 = STM32446ADC3_sqr3_sq6;
	adc3_setup.sqr3.sq5 = STM32446ADC3_sqr3_sq5;
	adc3_setup.sqr3.sq4 = STM32446ADC3_sqr3_sq4;
	adc3_setup.sqr3.sq4_0 = STM32446ADC3_sqr3_sq4_0;
	adc3_setup.sqr3.sq3 = STM32446ADC3_sqr3_sq3;
	adc3_setup.sqr3.sq2 = STM32446ADC3_sqr3_sq2;
	adc3_setup.sqr3.sq1 = STM32446ADC3_sqr3_sq1;
	// JSQR
	adc3_setup.jsqr.jl = STM32446ADC3_jsqr_jl;
	adc3_setup.jsqr.jsq4 = STM32446ADC3_jsqr_jsq4;
	adc3_setup.jsqr.jsq4_0 = STM32446ADC3_jsqr_jsq4_0;
	adc3_setup.jsqr.jsq3 = STM32446ADC3_jsqr_jsq3;
	adc3_setup.jsqr.jsq2 = STM32446ADC3_jsqr_jsq2;
	adc3_setup.jsqr.jsq1 = STM32446ADC3_jsqr_jsq1;
	// JDR1
	adc3_setup.jdr1 = STM32446ADC3_jdr1;
	// JDR2
	adc3_setup.jdr2 = STM32446ADC3_jdr2;
	// JDR3
	adc3_setup.jdr3 = STM32446ADC3_jdr3;
	// JDR4
	adc3_setup.jdr4 = STM32446ADC3_jdr4;
	// DR
	adc3_setup.dr = STM32446ADC3_dr;
	// CSR
	adc3_setup.common.csr.ovr3 = STM32446ADC_csr_ovr3;
	adc3_setup.common.csr.strt3 = STM32446ADC_csr_strt3;
	adc3_setup.common.csr.jstrt3 = STM32446ADC_csr_jstrt3;
	adc3_setup.common.csr.jeoc3 = STM32446ADC_csr_jeoc3;
	adc3_setup.common.csr.eoc3 = STM32446ADC_csr_eoc3;
	adc3_setup.common.csr.awd3 = STM32446ADC_csr_awd3;
	adc3_setup.common.csr.ovr2 = STM32446ADC_csr_ovr2;
	adc3_setup.common.csr.strt2 = STM32446ADC_csr_strt2;
	adc3_setup.common.csr.jstrt2 = STM32446ADC_csr_jstrt2;
	adc3_setup.common.csr.jeoc2 = STM32446ADC_csr_jeoc2;
	adc3_setup.common.csr.eoc2 = STM32446ADC_csr_eoc2;
	adc3_setup.common.csr.awd2 = STM32446ADC_csr_awd2;
	adc3_setup.common.csr.ovr1 = STM32446ADC_csr_ovr1;
	adc3_setup.common.csr.strt1 = STM32446ADC_csr_strt1;
	adc3_setup.common.csr.jstrt1 = STM32446ADC_csr_jstrt1;
	adc3_setup.common.csr.jeoc1 = STM32446ADC_csr_jeoc1;
	adc3_setup.common.csr.eoc1 = STM32446ADC_csr_eoc1;
	adc3_setup.common.csr.awd1 = STM32446ADC_csr_awd1;
	// CCR
	adc3_setup.common.ccr.tsvrefe = STM32446ADC_ccr_tsvrefe;
	adc3_setup.common.ccr.vbate = STM32446ADC_ccr_vbate;
	adc3_setup.common.ccr.adcpre = STM32446ADC_ccr_adcpre;
	adc3_setup.common.ccr.dma = STM32446ADC_ccr_dma;
	adc3_setup.common.ccr.dds = STM32446ADC_ccr_dds;
	adc3_setup.common.ccr.delay = STM32446ADC_ccr_delay;
	adc3_setup.common.ccr.multi = STM32446ADC_ccr_multi;
	// CDR
	adc3_setup.common.cdr = STM32446ADC_cdr;
	// Other
	adc3_setup.clock = STM32446Adc3Clock;

	return adc3_setup;
}

/*** File Procedure & Function Definition ***/
uint32_t adc_readreg(uint32_t reg, uint32_t size_block, uint32_t bit)
{
	if(bit > 31){ bit = 0;} if(size_block > 32){ size_block = 32;}
	uint32_t value = reg;
	uint32_t mask = (unsigned int)((1 << size_block) - 1);
	value &= (mask << bit);
	value = (value >> bit);
	return value;
}

void adc_writereg(volatile uint32_t* reg, uint32_t size_block, uint32_t bit, uint32_t data)
{
	if(bit > 31){ bit = 0;} if(size_block > 32){ size_block = 32;}
	uint32_t value = data;
	uint32_t mask = (unsigned int)((1 << size_block) - 1);
	value &= mask;
	value = (value << bit);
	*reg = value;
}

void adc_setreg(volatile uint32_t* reg, uint32_t size_block, uint32_t bit, uint32_t data)
{
	if(bit > 31){ bit = 0;} if(size_block > 32){ size_block = 32;}
	uint32_t value = data;
	uint32_t mask = (unsigned int)((1 << size_block) - 1);
	value &= mask;
	*reg &= ~(mask << bit);
	*reg |= (value << bit);
}

void adc_setbit(volatile uint32_t* reg, uint32_t size_block, uint32_t bit, uint32_t data)
{
	uint32_t n = 0;
	if(bit > 31){ n = bit/32; bit = bit - (n * 32); } if(size_block > 32){ size_block = 32;}
	uint32_t value = data;
	uint32_t mask = (unsigned int)((1 << size_block) - 1);
	value &= mask;
	*(reg + n ) &= ~(mask << bit);
	*(reg + n ) |= (value << bit);
}

uint32_t adc_getsetbit(volatile uint32_t* reg, uint32_t size_block, uint32_t bit)
{
	uint32_t n = 0;
	if(bit > 31){ n = bit/32; bit = bit - (n * 32); } if(size_block > 32){ size_block = 32;}
	uint32_t value = *(reg + n );
	uint32_t mask = (unsigned int)((1 << size_block) - 1);
	value &= (mask << bit);
	value = (value >> bit);
	return value;
}

/*** EOF ***/


