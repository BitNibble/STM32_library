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
uint32_t adc_getsetbit(volatile uint32_t* reg, uint32_t size_block, uint32_t bit);

/*** ADC Procedure & Function Definition ***/
/*** ADC1 Bit Mapping ***/
// SR
uint8_t STM32446ADC1_sr_ovr(void)
{
	return adc_getbit(ADC1->SR, 1, 5);
}
void STM32446ADC1_sr_clear_ovr(void)
{
	adc_setbit(&ADC1->SR, 1, 5, 0);
}
uint8_t STM32446ADC1_sr_strt(void)
{
	return adc_getbit(ADC1->SR, 1, 4);
}
void STM32446ADC1_sr_clear_strt(void)
{
	adc_setbit(&ADC1->SR, 1, 4, 0);
}
uint8_t STM32446ADC1_sr_jstrt(void)
{
	return adc_getbit(ADC1->SR, 1, 3);
}
void STM32446ADC1_sr_clear_jstrt(void)
{
	adc_setbit(&ADC1->SR, 1, 3, 0);
}
uint8_t STM32446ADC1_sr_jeoc(void)
{
	return adc_getbit(ADC1->SR, 1, 2);
}
void STM32446ADC1_sr_clear_jeoc(void)
{
	adc_setbit(&ADC1->SR, 1, 2, 0);
}
uint8_t STM32446ADC1_sr_eoc(void)
{
	return adc_getbit(ADC1->SR, 1, 1);

}
void STM32446ADC1_sr_clear_eoc(void)
{
	adc_setbit(&ADC1->SR, 1, 1, 0);
}
uint8_t STM32446ADC1_sr_awd(void)
{
	return adc_getbit(ADC1->SR, 1, 0);
}
void STM32446ADC1_sr_clear_awd(void)
{
	adc_setbit(&ADC1->SR, 1, 0, 0);
}

// CR1
void STM32446ADC1_cr1_ovrie(uint8_t bool)
{
	adc_setbit(&ADC1->CR1, 1, 26, bool);
}
void STM32446ADC1_cr1_res(uint8_t value)
{
	adc_setbit(&ADC1->CR1, 2, 24, value);
}
void STM32446ADC1_cr1_awden(uint8_t bool)
{
	adc_setbit(&ADC1->CR1, 1, 23, bool);
}
void STM32446ADC1_cr1_jawden(uint8_t bool)
{
	adc_setbit(&ADC1->CR1, 1, 22, bool);
}
void STM32446ADC1_cr1_discnum(uint8_t value)
{
	adc_setbit(&ADC1->CR1, 3, 13, value);
}
void STM32446ADC1_cr1_jdiscen(uint8_t bool)
{
	adc_setbit(&ADC1->CR1, 1, 12, bool);
}
void STM32446ADC1_cr1_discen(uint8_t bool)
{
	adc_setbit(&ADC1->CR1, 1, 11, bool);
}
void STM32446ADC1_cr1_jauto(uint8_t bool)
{
	adc_setbit(&ADC1->CR1, 1, 10, bool);
}
void STM32446ADC1_cr1_awdsgl(uint8_t bool)
{
	adc_setbit(&ADC1->CR1, 1, 9, bool);
}
void STM32446ADC1_cr1_scan(uint8_t bool)
{
	adc_setbit(&ADC1->CR1, 1, 8, bool);
}
void STM32446ADC1_cr1_jeocie(uint8_t bool)
{
	adc_setbit(&ADC1->CR1, 1, 7, bool);
}
void STM32446ADC1_cr1_awdie(uint8_t bool)
{
	adc_setbit(&ADC1->CR1, 1, 6, bool);
}
void STM32446ADC1_cr1_eocie(uint8_t bool)
{
	adc_setbit(&ADC1->CR1, 1, 5, bool);
}
void STM32446ADC1_cr1_awdch(uint8_t value)
{
	adc_setbit(&ADC1->CR1, 5, 0, value);
}

// CR2
void STM32446ADC1_cr2_swstart(uint8_t bool)
{
	adc_setbit(&ADC1->CR2, 1, 30, bool);
}
void STM32446ADC1_cr2_exten(uint8_t value)
{
	adc_setbit(&ADC1->CR2, 2, 28, value);
}
void STM32446ADC1_cr2_extsel(uint8_t value)
{
	adc_setbit(&ADC1->CR2, 4, 24, value);
}
void STM32446ADC1_cr2_jswstart(uint8_t bool)
{
	adc_setbit(&ADC1->CR2, 1, 22, bool);
}
void STM32446ADC1_cr2_jexten(uint8_t value)
{
	adc_setbit(&ADC1->CR2, 2, 20, value);
}
void STM32446ADC1_cr2_jextsel(uint8_t value)
{
	adc_setbit(&ADC1->CR2, 4, 16, value);
}
void STM32446ADC1_cr2_align(uint8_t bool)
{
	adc_setbit(&ADC1->CR2, 1, 11, bool);
}
void STM32446ADC1_cr2_eocs(uint8_t bool)
{
	adc_setbit(&ADC1->CR2, 1, 10, bool);
}
void STM32446ADC1_cr2_dds(uint8_t bool)
{
	adc_setbit(&ADC1->CR2, 1, 9, bool);
}
void STM32446ADC1_cr2_dma(uint8_t bool)
{
	adc_setbit(&ADC1->CR2, 1, 8, bool);
}
void STM32446ADC1_cr2_cont(uint8_t bool)
{
	adc_setbit(&ADC1->CR2, 1, 1, bool);
}
void STM32446ADC1_cr2_adon(uint8_t bool)
{
	adc_setbit(&ADC1->CR2, 1, 0, bool);
}

// SMPR1
void STM32446ADC1_smpr1_smp18(uint8_t value)
{
	adc_setbit(&ADC1->SMPR1, 3, 24, value);
}
void STM32446ADC1_smpr1_smp17(uint8_t value)
{
	adc_setbit(&ADC1->SMPR1, 3, 21, value);
}
void STM32446ADC1_smpr1_smp16(uint8_t value)
{
	adc_setbit(&ADC1->SMPR1, 3, 18, value);
}
void STM32446ADC1_smpr1_smp15(uint8_t value)
{
	adc_setbit(&ADC1->SMPR1, 2, 16, value);
}
void STM32446ADC1_smpr1_smp15_0(uint8_t bool)
{
	adc_setbit(&ADC1->SMPR1, 1, 15, bool);
}
void STM32446ADC1_smpr1_smp14(uint8_t value)
{
	adc_setbit(&ADC1->SMPR1, 3, 12, value);
}
void STM32446ADC1_smpr1_smp13(uint8_t value)
{
	adc_setbit(&ADC1->SMPR1, 3, 9, value);
}
void STM32446ADC1_smpr1_smp12(uint8_t value)
{
	adc_setbit(&ADC1->SMPR1, 3, 6, value);
}
void STM32446ADC1_smpr1_smp11(uint8_t value)
{
	adc_setbit(&ADC1->SMPR1, 3, 3, value);
}
void STM32446ADC1_smpr1_smp10(uint8_t value)
{
	adc_setbit(&ADC1->SMPR1, 3, 0, value);
}

// SMPR2
void STM32446ADC1_smpr2_smp9(uint8_t value)
{
	adc_setbit(&ADC1->SMPR2, 3, 27, value);
}
void STM32446ADC1_smpr2_smp8(uint8_t value)
{
	adc_setbit(&ADC1->SMPR2, 3, 24, value);
}
void STM32446ADC1_smpr2_smp7(uint8_t value)
{
	adc_setbit(&ADC1->SMPR2, 3, 21, value);
}
void STM32446ADC1_smpr2_smp6(uint8_t value)
{
	adc_setbit(&ADC1->SMPR2, 3, 18, value);
}
void STM32446ADC1_smpr2_smp5(uint8_t bool)
{
	adc_setbit(&ADC1->SMPR2, 2, 16, bool);
}
void STM32446ADC1_smpr2_smp5_0(uint8_t bool)
{
	adc_setbit(&ADC1->SMPR2, 1, 15, bool);
}
void STM32446ADC1_smpr2_smp4(uint8_t value)
{
	adc_setbit(&ADC1->SMPR2, 3, 12, value);
}
void STM32446ADC1_smpr2_smp3(uint8_t value)
{
	adc_setbit(&ADC1->SMPR2, 3, 9, value);
}
void STM32446ADC1_smpr2_smp2(uint8_t value)
{
	adc_setbit(&ADC1->SMPR2, 3, 6, value);
}
void STM32446ADC1_smpr2_smp1(uint8_t value)
{
	adc_setbit(&ADC1->SMPR2, 3, 3, value);
}
void STM32446ADC1_smpr2_smp0(uint8_t value)
{
	adc_setbit(&ADC1->SMPR2, 3, 0, value);
}

// Other
void STM32446ADC1_jofr1(uint16_t value)
{
	adc_setbit(&ADC1->JOFR1, 12, 0, value);
}
void STM32446ADC1_jofr2(uint16_t value)
{
	adc_setbit(&ADC1->JOFR2, 12, 0, value);
}
void STM32446ADC1_jofr3(uint16_t value)
{
	adc_setbit(&ADC1->JOFR3, 12, 0, value);
}
void STM32446ADC1_jofr4(uint16_t value)
{
	adc_setbit(&ADC1->JOFR4, 12, 0, value);
}
void STM32446ADC1_htr(uint16_t value)
{
	adc_setbit(&ADC1->HTR, 12, 0, value);
}
void STM32446ADC1_ltr(uint16_t value)
{
	adc_setbit(&ADC1->LTR, 12, 0, value);
}

// SQR1
void STM32446ADC1_sqr1_l(uint8_t value)
{
	adc_setbit(&ADC1->SQR1, 4, 20, value);
}
void STM32446ADC1_sqr1_sq16(uint8_t value)
{
	adc_setbit(&ADC1->SQR1, 4, 16, value);
}
void STM32446ADC1_sqr1_sq16_0(uint8_t bool)
{
	adc_setbit(&ADC1->SQR1, 1, 15, bool);
}
void STM32446ADC1_sqr1_sq15(uint8_t value)
{
	adc_setbit(&ADC1->SQR1, 5, 10, value);
}
void STM32446ADC1_sqr1_sq14(uint8_t value)
{
	adc_setbit(&ADC1->SQR1, 5, 5, value);
}
void STM32446ADC1_sqr1_sq13(uint8_t value)
{
	adc_setbit(&ADC1->SQR1, 5, 0, value);
}

// SQR2
void STM32446ADC1_sqr2_sq12(uint8_t value)
{
	adc_setbit(&ADC1->SQR2, 5, 25, value);
}
void STM32446ADC1_sqr2_sq11(uint8_t value)
{
	adc_setbit(&ADC1->SQR2, 5, 20, value);
}
void STM32446ADC1_sqr2_sq10(uint8_t value)
{
	adc_setbit(&ADC1->SQR2, 4, 16, value);
}
void STM32446ADC1_sqr2_sq10_0(uint8_t bool)
{
	adc_setbit(&ADC1->SQR2, 1, 15, bool);
}
void STM32446ADC1_sqr2_sq9(uint8_t value)
{
	adc_setbit(&ADC1->SQR2, 5, 10, value);
}
void STM32446ADC1_sqr2_sq8(uint8_t value)
{
	adc_setbit(&ADC1->SQR2, 5, 5, value);
}
void STM32446ADC1_sqr2_sq7(uint8_t value)
{
	adc_setbit(&ADC1->SQR2, 5, 0, value);
}

// SQR3
void STM32446ADC1_sqr3_sq6(uint8_t value)
{
	adc_setbit(&ADC1->SQR3, 5, 25, value);
}
void STM32446ADC1_sqr3_sq5(uint8_t value)
{
	adc_setbit(&ADC1->SQR3, 5, 20, value);
}
void STM32446ADC1_sqr3_sq4(uint8_t value)
{
	adc_setbit(&ADC1->SQR3, 4, 16, value);
}
void STM32446ADC1_sqr3_sq4_0(uint8_t bool)
{
	adc_setbit(&ADC1->SQR3, 1, 15, bool);
}
void STM32446ADC1_sqr3_sq3(uint8_t value)
{
	adc_setbit(&ADC1->SQR3, 5, 10, value);
}
void STM32446ADC1_sqr3_sq2(uint8_t value)
{
	adc_setbit(&ADC1->SQR3, 5, 5, value);
}
void STM32446ADC1_sqr3_sq1(uint8_t value)
{
	adc_setbit(&ADC1->SQR3, 5, 0, value);
}

// JSQR
void STM32446ADC1_jsqr_jl(uint8_t value)
{
	adc_setbit(&ADC1->JSQR, 2, 20, value);
}
void STM32446ADC1_jsqr_jsq4(uint8_t value)
{
	adc_setbit(&ADC1->JSQR, 4, 16, value);
}
void STM32446ADC1_jsqr_jsq4_0(uint8_t bool)
{
	adc_setbit(&ADC1->JSQR, 1, 15, bool);
}
void STM32446ADC1_jsqr_jsq3(uint8_t value)
{
	adc_setbit(&ADC1->JSQR, 5, 10, value);
}
void STM32446ADC1_jsqr_jsq2(uint8_t value)
{
	adc_setbit(&ADC1->JSQR, 5, 5, value);
}
void STM32446ADC1_jsqr_jsq1(uint8_t value)
{
	adc_setbit(&ADC1->JSQR, 5, 0, value);
}

// Other
uint16_t STM32446ADC1_jdr1(void)
{
	return adc_getbit(ADC1->JDR1, 16, 0);
}
uint16_t STM32446ADC1_jdr2(void)
{
	return adc_getbit(ADC1->JDR2, 16, 0);
}
uint16_t STM32446ADC1_jdr3(void)
{
	return adc_getbit(ADC1->JDR3, 16, 0);
}
uint16_t STM32446ADC1_jdr4(void)
{
	return adc_getbit(ADC1->JDR4, 16, 0);
}
uint16_t STM32446ADC1_dr(void)
{
	return adc_getbit(ADC1->DR, 16, 0);
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
	return adc_getbit(ADC2->SR, 1, 5);
}
void STM32446ADC2_sr_clear_ovr(void)
{
	adc_setbit(&ADC2->SR, 1, 5, 0);
}
uint8_t STM32446ADC2_sr_strt(void)
{
	return adc_getbit(ADC2->SR, 1, 4);
}
void STM32446ADC2_sr_clear_strt(void)
{
	adc_setbit(&ADC2->SR, 1, 4, 0);
}
uint8_t STM32446ADC2_sr_jstrt(void)
{
	return adc_getbit(ADC2->SR, 1, 3);
}
void STM32446ADC2_sr_clear_jstrt(void)
{
	adc_setbit(&ADC2->SR, 1, 3, 0);
}
uint8_t STM32446ADC2_sr_jeoc(void)
{
	return adc_getbit(ADC2->SR, 1, 2);
}
void STM32446ADC2_sr_clear_jeoc(void)
{
	adc_setbit(&ADC2->SR, 1, 2, 0);
}
uint8_t STM32446ADC2_sr_eoc(void)
{
	return adc_getbit(ADC2->SR, 1, 1);

}
void STM32446ADC2_sr_clear_eoc(void)
{
	adc_setbit(&ADC2->SR, 1, 1, 0);
}
uint8_t STM32446ADC2_sr_awd(void)
{
	return adc_getbit(ADC2->SR, 1, 0);
}
void STM32446ADC2_sr_clear_awd(void)
{
	adc_setbit(&ADC2->SR, 1, 0, 0);
}

// CR1
void STM32446ADC2_cr1_ovrie(uint8_t bool)
{
	adc_setbit(&ADC2->CR1, 1, 26, bool);
}
void STM32446ADC2_cr1_res(uint8_t value)
{
	adc_setbit(&ADC2->CR1, 2, 24, value);
}
void STM32446ADC2_cr1_awden(uint8_t bool)
{
	adc_setbit(&ADC2->CR1, 1, 23, bool);
}
void STM32446ADC2_cr1_jawden(uint8_t bool)
{
	adc_setbit(&ADC2->CR1, 1, 22, bool);
}
void STM32446ADC2_cr1_discnum(uint8_t value)
{
	adc_setbit(&ADC2->CR1, 3, 13, value);
}
void STM32446ADC2_cr1_jdiscen(uint8_t bool)
{
	adc_setbit(&ADC2->CR1, 1, 12, bool);
}
void STM32446ADC2_cr1_discen(uint8_t bool)
{
	adc_setbit(&ADC2->CR1, 1, 11, bool);
}
void STM32446ADC2_cr1_jauto(uint8_t bool)
{
	adc_setbit(&ADC2->CR1, 1, 10, bool);
}
void STM32446ADC2_cr1_awdsgl(uint8_t bool)
{
	adc_setbit(&ADC2->CR1, 1, 9, bool);
}
void STM32446ADC2_cr1_scan(uint8_t bool)
{
	adc_setbit(&ADC2->CR1, 1, 8, bool);
}
void STM32446ADC2_cr1_jeocie(uint8_t bool)
{
	adc_setbit(&ADC2->CR1, 1, 7, bool);
}
void STM32446ADC2_cr1_awdie(uint8_t bool)
{
	adc_setbit(&ADC2->CR1, 1, 6, bool);
}
void STM32446ADC2_cr1_eocie(uint8_t bool)
{
	adc_setbit(&ADC2->CR1, 1, 5, bool);
}
void STM32446ADC2_cr1_awdch(uint8_t value)
{
	adc_setbit(&ADC2->CR1, 5, 0, value);
}

// CR2
void STM32446ADC2_cr2_swstart(uint8_t bool)
{
	adc_setbit(&ADC2->CR2, 1, 30, bool);
}
void STM32446ADC2_cr2_exten(uint8_t value)
{
	adc_setbit(&ADC2->CR2, 2, 28, value);
}
void STM32446ADC2_cr2_extsel(uint8_t value)
{
	adc_setbit(&ADC2->CR2, 4, 24, value);
}
void STM32446ADC2_cr2_jswstart(uint8_t bool)
{
	adc_setbit(&ADC2->CR2, 1, 22, bool);
}
void STM32446ADC2_cr2_jexten(uint8_t value)
{
	adc_setbit(&ADC2->CR2, 2, 20, value);
}
void STM32446ADC2_cr2_jextsel(uint8_t value)
{
	adc_setbit(&ADC2->CR2, 4, 16, value);
}
void STM32446ADC2_cr2_align(uint8_t bool)
{
	adc_setbit(&ADC2->CR2, 1, 11, bool);
}
void STM32446ADC2_cr2_eocs(uint8_t bool)
{
	adc_setbit(&ADC2->CR2, 1, 10, bool);
}
void STM32446ADC2_cr2_dds(uint8_t bool)
{
	adc_setbit(&ADC2->CR2, 1, 9, bool);
}
void STM32446ADC2_cr2_dma(uint8_t bool)
{
	adc_setbit(&ADC2->CR2, 1, 8, bool);
}
void STM32446ADC2_cr2_cont(uint8_t bool)
{
	adc_setbit(&ADC2->CR2, 1, 1, bool);
}
void STM32446ADC2_cr2_adon(uint8_t bool)
{
	adc_setbit(&ADC2->CR2, 1, 0, bool);
}

// SMPR1
void STM32446ADC2_smpr1_smp18(uint8_t value)
{
	adc_setbit(&ADC2->SMPR1, 3, 24, value);
}
void STM32446ADC2_smpr1_smp17(uint8_t value)
{
	adc_setbit(&ADC2->SMPR1, 3, 21, value);
}
void STM32446ADC2_smpr1_smp16(uint8_t value)
{
	adc_setbit(&ADC2->SMPR1, 3, 18, value);
}
void STM32446ADC2_smpr1_smp15(uint8_t value)
{
	adc_setbit(&ADC2->SMPR1, 2, 16, value);
}
void STM32446ADC2_smpr1_smp15_0(uint8_t bool)
{
	adc_setbit(&ADC2->SMPR1, 1, 15, bool);
}
void STM32446ADC2_smpr1_smp14(uint8_t value)
{
	adc_setbit(&ADC2->SMPR1, 3, 12, value);
}
void STM32446ADC2_smpr1_smp13(uint8_t value)
{
	adc_setbit(&ADC2->SMPR1, 3, 9, value);
}
void STM32446ADC2_smpr1_smp12(uint8_t value)
{
	adc_setbit(&ADC2->SMPR1, 3, 6, value);
}
void STM32446ADC2_smpr1_smp11(uint8_t value)
{
	adc_setbit(&ADC2->SMPR1, 3, 3, value);
}
void STM32446ADC2_smpr1_smp10(uint8_t value)
{
	adc_setbit(&ADC2->SMPR1, 3, 0, value);
}

// SMPR2
void STM32446ADC2_smpr2_smp9(uint8_t value)
{
	adc_setbit(&ADC2->SMPR2, 3, 27, value);
}
void STM32446ADC2_smpr2_smp8(uint8_t value)
{
	adc_setbit(&ADC2->SMPR2, 3, 24, value);
}
void STM32446ADC2_smpr2_smp7(uint8_t value)
{
	adc_setbit(&ADC2->SMPR2, 3, 21, value);
}
void STM32446ADC2_smpr2_smp6(uint8_t value)
{
	adc_setbit(&ADC2->SMPR2, 3, 18, value);
}
void STM32446ADC2_smpr2_smp5(uint8_t bool)
{
	adc_setbit(&ADC2->SMPR2, 2, 16, bool);
}
void STM32446ADC2_smpr2_smp5_0(uint8_t bool)
{
	adc_setbit(&ADC2->SMPR2, 1, 15, bool);
}
void STM32446ADC2_smpr2_smp4(uint8_t value)
{
	adc_setbit(&ADC2->SMPR2, 3, 12, value);
}
void STM32446ADC2_smpr2_smp3(uint8_t value)
{
	adc_setbit(&ADC2->SMPR2, 3, 9, value);
}
void STM32446ADC2_smpr2_smp2(uint8_t value)
{
	adc_setbit(&ADC2->SMPR2, 3, 6, value);
}
void STM32446ADC2_smpr2_smp1(uint8_t value)
{
	adc_setbit(&ADC2->SMPR2, 3, 3, value);
}
void STM32446ADC2_smpr2_smp0(uint8_t value)
{
	adc_setbit(&ADC2->SMPR2, 3, 0, value);
}

// Other
void STM32446ADC2_jofr1(uint16_t value)
{
	adc_setbit(&ADC2->JOFR1, 12, 0, value);
}
void STM32446ADC2_jofr2(uint16_t value)
{
	adc_setbit(&ADC2->JOFR2, 12, 0, value);
}
void STM32446ADC2_jofr3(uint16_t value)
{
	adc_setbit(&ADC2->JOFR3, 12, 0, value);
}
void STM32446ADC2_jofr4(uint16_t value)
{
	adc_setbit(&ADC2->JOFR4, 12, 0, value);
}
void STM32446ADC2_htr(uint16_t value)
{
	adc_setbit(&ADC2->HTR, 12, 0, value);
}
void STM32446ADC2_ltr(uint16_t value)
{
	adc_setbit(&ADC2->LTR, 12, 0, value);
}

// SQR1
void STM32446ADC2_sqr1_l(uint8_t value)
{
	adc_setbit(&ADC2->SQR1, 4, 20, value);
}
void STM32446ADC2_sqr1_sq16(uint8_t value)
{
	adc_setbit(&ADC2->SQR1, 4, 16, value);
}
void STM32446ADC2_sqr1_sq16_0(uint8_t bool)
{
	adc_setbit(&ADC2->SQR1, 1, 15, bool);
}
void STM32446ADC2_sqr1_sq15(uint8_t value)
{
	adc_setbit(&ADC2->SQR1, 5, 10, value);
}
void STM32446ADC2_sqr1_sq14(uint8_t value)
{
	adc_setbit(&ADC2->SQR1, 5, 5, value);
}
void STM32446ADC2_sqr1_sq13(uint8_t value)
{
	adc_setbit(&ADC2->SQR1, 5, 0, value);
}

// SQR2
void STM32446ADC2_sqr2_sq12(uint8_t value)
{
	adc_setbit(&ADC2->SQR2, 5, 25, value);
}
void STM32446ADC2_sqr2_sq11(uint8_t value)
{
	adc_setbit(&ADC2->SQR2, 5, 20, value);
}
void STM32446ADC2_sqr2_sq10(uint8_t value)
{
	adc_setbit(&ADC2->SQR2, 4, 16, value);
}
void STM32446ADC2_sqr2_sq10_0(uint8_t bool)
{
	adc_setbit(&ADC2->SQR2, 1, 15, bool);
}
void STM32446ADC2_sqr2_sq9(uint8_t value)
{
	adc_setbit(&ADC2->SQR2, 5, 10, value);
}
void STM32446ADC2_sqr2_sq8(uint8_t value)
{
	adc_setbit(&ADC2->SQR2, 5, 5, value);
}
void STM32446ADC2_sqr2_sq7(uint8_t value)
{
	adc_setbit(&ADC2->SQR2, 5, 0, value);
}

// SQR3
void STM32446ADC2_sqr3_sq6(uint8_t value)
{
	adc_setbit(&ADC2->SQR3, 5, 25, value);
}
void STM32446ADC2_sqr3_sq5(uint8_t value)
{
	adc_setbit(&ADC2->SQR3, 5, 20, value);
}
void STM32446ADC2_sqr3_sq4(uint8_t value)
{
	adc_setbit(&ADC2->SQR3, 4, 16, value);
}
void STM32446ADC2_sqr3_sq4_0(uint8_t bool)
{
	adc_setbit(&ADC2->SQR3, 1, 15, bool);
}
void STM32446ADC2_sqr3_sq3(uint8_t value)
{
	adc_setbit(&ADC2->SQR3, 5, 10, value);
}
void STM32446ADC2_sqr3_sq2(uint8_t value)
{
	adc_setbit(&ADC2->SQR3, 5, 5, value);
}
void STM32446ADC2_sqr3_sq1(uint8_t value)
{
	adc_setbit(&ADC2->SQR3, 5, 0, value);
}

// JSQR
void STM32446ADC2_jsqr_jl(uint8_t value)
{
	adc_setbit(&ADC2->JSQR, 2, 20, value);
}
void STM32446ADC2_jsqr_jsq4(uint8_t value)
{
	adc_setbit(&ADC2->JSQR, 4, 16, value);
}
void STM32446ADC2_jsqr_jsq4_0(uint8_t bool)
{
	adc_setbit(&ADC2->JSQR, 1, 15, bool);
}
void STM32446ADC2_jsqr_jsq3(uint8_t value)
{
	adc_setbit(&ADC2->JSQR, 5, 10, value);
}
void STM32446ADC2_jsqr_jsq2(uint8_t value)
{
	adc_setbit(&ADC2->JSQR, 5, 5, value);
}
void STM32446ADC2_jsqr_jsq1(uint8_t value)
{
	adc_setbit(&ADC2->JSQR, 5, 0, value);
}

// Other
uint16_t STM32446ADC2_jdr1(void)
{
	return adc_getbit(ADC2->JDR1, 16, 0);
}
uint16_t STM32446ADC2_jdr2(void)
{
	return adc_getbit(ADC2->JDR2, 16, 0);
}
uint16_t STM32446ADC2_jdr3(void)
{
	return adc_getbit(ADC2->JDR3, 16, 0);
}
uint16_t STM32446ADC2_jdr4(void)
{
	return adc_getbit(ADC2->JDR4, 16, 0);
}
uint16_t STM32446ADC2_dr(void)
{
	return adc_getbit(ADC2->DR, 16, 0);
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
	return adc_getbit(ADC3->SR, 1, 5);
}
void STM32446ADC3_sr_clear_ovr(void)
{
	adc_setbit(&ADC3->SR, 1, 5, 0);
}
uint8_t STM32446ADC3_sr_strt(void)
{
	return adc_getbit(ADC3->SR, 1, 4);
}
void STM32446ADC3_sr_clear_strt(void)
{
	adc_setbit(&ADC3->SR, 1, 4, 0);
}
uint8_t STM32446ADC3_sr_jstrt(void)
{
	return adc_getbit(ADC3->SR, 1, 3);
}
void STM32446ADC3_sr_clear_jstrt(void)
{
	adc_setbit(&ADC3->SR, 1, 3, 0);
}
uint8_t STM32446ADC3_sr_jeoc(void)
{
	return adc_getbit(ADC3->SR, 1, 2);
}
void STM32446ADC3_sr_clear_jeoc(void)
{
	adc_setbit(&ADC3->SR, 1, 2, 0);
}
uint8_t STM32446ADC3_sr_eoc(void)
{
	return adc_getbit(ADC3->SR, 1, 1);

}
void STM32446ADC3_sr_clear_eoc(void)
{
	adc_setbit(&ADC3->SR, 1, 1, 0);
}
uint8_t STM32446ADC3_sr_awd(void)
{
	return adc_getbit(ADC3->SR, 1, 0);
}
void STM32446ADC3_sr_clear_awd(void)
{
	adc_setbit(&ADC3->SR, 1, 0, 0);
}

// CR1
void STM32446ADC3_cr1_ovrie(uint8_t bool)
{
	adc_setbit(&ADC3->CR1, 1, 26, bool);
}
void STM32446ADC3_cr1_res(uint8_t value)
{
	adc_setbit(&ADC3->CR1, 2, 24, value);
}
void STM32446ADC3_cr1_awden(uint8_t bool)
{
	adc_setbit(&ADC3->CR1, 1, 23, bool);
}
void STM32446ADC3_cr1_jawden(uint8_t bool)
{
	adc_setbit(&ADC3->CR1, 1, 22, bool);
}
void STM32446ADC3_cr1_discnum(uint8_t value)
{
	adc_setbit(&ADC3->CR1, 3, 13, value);
}
void STM32446ADC3_cr1_jdiscen(uint8_t bool)
{
	adc_setbit(&ADC3->CR1, 1, 12, bool);
}
void STM32446ADC3_cr1_discen(uint8_t bool)
{
	adc_setbit(&ADC3->CR1, 1, 11, bool);
}
void STM32446ADC3_cr1_jauto(uint8_t bool)
{
	adc_setbit(&ADC3->CR1, 1, 10, bool);
}
void STM32446ADC3_cr1_awdsgl(uint8_t bool)
{
	adc_setbit(&ADC3->CR1, 1, 9, bool);
}
void STM32446ADC3_cr1_scan(uint8_t bool)
{
	adc_setbit(&ADC3->CR1, 1, 8, bool);
}
void STM32446ADC3_cr1_jeocie(uint8_t bool)
{
	adc_setbit(&ADC3->CR1, 1, 7, bool);
}
void STM32446ADC3_cr1_awdie(uint8_t bool)
{
	adc_setbit(&ADC3->CR1, 1, 6, bool);
}
void STM32446ADC3_cr1_eocie(uint8_t bool)
{
	adc_setbit(&ADC3->CR1, 1, 5, bool);
}
void STM32446ADC3_cr1_awdch(uint8_t value)
{
	adc_setbit(&ADC3->CR1, 5, 0, value);
}

// CR2
void STM32446ADC3_cr2_swstart(uint8_t bool)
{
	adc_setbit(&ADC3->CR2, 1, 30, bool);
}
void STM32446ADC3_cr2_exten(uint8_t value)
{
	adc_setbit(&ADC3->CR2, 2, 28, value);
}
void STM32446ADC3_cr2_extsel(uint8_t value)
{
	adc_setbit(&ADC3->CR2, 4, 24, value);
}
void STM32446ADC3_cr2_jswstart(uint8_t bool)
{
	adc_setbit(&ADC3->CR2, 1, 22, bool);
}
void STM32446ADC3_cr2_jexten(uint8_t value)
{
	adc_setbit(&ADC3->CR2, 2, 20, value);
}
void STM32446ADC3_cr2_jextsel(uint8_t value)
{
	adc_setbit(&ADC3->CR2, 4, 16, value);
}
void STM32446ADC3_cr2_align(uint8_t bool)
{
	adc_setbit(&ADC3->CR2, 1, 11, bool);
}
void STM32446ADC3_cr2_eocs(uint8_t bool)
{
	adc_setbit(&ADC3->CR2, 1, 10, bool);
}
void STM32446ADC3_cr2_dds(uint8_t bool)
{
	adc_setbit(&ADC3->CR2, 1, 9, bool);
}
void STM32446ADC3_cr2_dma(uint8_t bool)
{
	adc_setbit(&ADC3->CR2, 1, 8, bool);
}
void STM32446ADC3_cr2_cont(uint8_t bool)
{
	adc_setbit(&ADC3->CR2, 1, 1, bool);
}
void STM32446ADC3_cr2_adon(uint8_t bool)
{
	adc_setbit(&ADC3->CR2, 1, 0, bool);
}

// SMPR1
void STM32446ADC3_smpr1_smp18(uint8_t value)
{
	adc_setbit(&ADC3->SMPR1, 3, 24, value);
}
void STM32446ADC3_smpr1_smp17(uint8_t value)
{
	adc_setbit(&ADC3->SMPR1, 3, 21, value);
}
void STM32446ADC3_smpr1_smp16(uint8_t value)
{
	adc_setbit(&ADC3->SMPR1, 3, 18, value);
}
void STM32446ADC3_smpr1_smp15(uint8_t value)
{
	adc_setbit(&ADC3->SMPR1, 2, 16, value);
}
void STM32446ADC3_smpr1_smp15_0(uint8_t bool)
{
	adc_setbit(&ADC3->SMPR1, 1, 15, bool);
}
void STM32446ADC3_smpr1_smp14(uint8_t value)
{
	adc_setbit(&ADC3->SMPR1, 3, 12, value);
}
void STM32446ADC3_smpr1_smp13(uint8_t value)
{
	adc_setbit(&ADC3->SMPR1, 3, 9, value);
}
void STM32446ADC3_smpr1_smp12(uint8_t value)
{
	adc_setbit(&ADC3->SMPR1, 3, 6, value);
}
void STM32446ADC3_smpr1_smp11(uint8_t value)
{
	adc_setbit(&ADC3->SMPR1, 3, 3, value);
}
void STM32446ADC3_smpr1_smp10(uint8_t value)
{
	adc_setbit(&ADC3->SMPR1, 3, 0, value);
}

// SMPR2
void STM32446ADC3_smpr2_smp9(uint8_t value)
{
	adc_setbit(&ADC3->SMPR2, 3, 27, value);
}
void STM32446ADC3_smpr2_smp8(uint8_t value)
{
	adc_setbit(&ADC3->SMPR2, 3, 24, value);
}
void STM32446ADC3_smpr2_smp7(uint8_t value)
{
	adc_setbit(&ADC3->SMPR2, 3, 21, value);
}
void STM32446ADC3_smpr2_smp6(uint8_t value)
{
	adc_setbit(&ADC3->SMPR2, 3, 18, value);
}
void STM32446ADC3_smpr2_smp5(uint8_t bool)
{
	adc_setbit(&ADC3->SMPR2, 2, 16, bool);
}
void STM32446ADC3_smpr2_smp5_0(uint8_t bool)
{
	adc_setbit(&ADC3->SMPR2, 1, 15, bool);
}
void STM32446ADC3_smpr2_smp4(uint8_t value)
{
	adc_setbit(&ADC3->SMPR2, 3, 12, value);
}
void STM32446ADC3_smpr2_smp3(uint8_t value)
{
	adc_setbit(&ADC3->SMPR2, 3, 9, value);
}
void STM32446ADC3_smpr2_smp2(uint8_t value)
{
	adc_setbit(&ADC3->SMPR2, 3, 6, value);
}
void STM32446ADC3_smpr2_smp1(uint8_t value)
{
	adc_setbit(&ADC3->SMPR2, 3, 3, value);
}
void STM32446ADC3_smpr2_smp0(uint8_t value)
{
	adc_setbit(&ADC3->SMPR2, 3, 0, value);
}

// Other
void STM32446ADC3_jofr1(uint16_t value)
{
	adc_setbit(&ADC3->JOFR1, 12, 0, value);
}
void STM32446ADC3_jofr2(uint16_t value)
{
	adc_setbit(&ADC3->JOFR2, 12, 0, value);
}
void STM32446ADC3_jofr3(uint16_t value)
{
	adc_setbit(&ADC3->JOFR3, 12, 0, value);
}
void STM32446ADC3_jofr4(uint16_t value)
{
	adc_setbit(&ADC3->JOFR4, 12, 0, value);
}
void STM32446ADC3_htr(uint16_t value)
{
	adc_setbit(&ADC3->HTR, 12, 0, value);
}
void STM32446ADC3_ltr(uint16_t value)
{
	adc_setbit(&ADC3->LTR, 12, 0, value);
}

// SQR1
void STM32446ADC3_sqr1_l(uint8_t value)
{
	adc_setbit(&ADC3->SQR1, 4, 20, value);
}
void STM32446ADC3_sqr1_sq16(uint8_t value)
{
	adc_setbit(&ADC3->SQR1, 4, 16, value);
}
void STM32446ADC3_sqr1_sq16_0(uint8_t bool)
{
	adc_setbit(&ADC3->SQR1, 1, 15, bool);
}
void STM32446ADC3_sqr1_sq15(uint8_t value)
{
	adc_setbit(&ADC3->SQR1, 5, 10, value);
}
void STM32446ADC3_sqr1_sq14(uint8_t value)
{
	adc_setbit(&ADC3->SQR1, 5, 5, value);
}
void STM32446ADC3_sqr1_sq13(uint8_t value)
{
	adc_setbit(&ADC3->SQR1, 5, 0, value);
}

// SQR2
void STM32446ADC3_sqr2_sq12(uint8_t value)
{
	adc_setbit(&ADC3->SQR2, 5, 25, value);
}
void STM32446ADC3_sqr2_sq11(uint8_t value)
{
	adc_setbit(&ADC3->SQR2, 5, 20, value);
}
void STM32446ADC3_sqr2_sq10(uint8_t value)
{
	adc_setbit(&ADC3->SQR2, 4, 16, value);
}
void STM32446ADC3_sqr2_sq10_0(uint8_t bool)
{
	adc_setbit(&ADC3->SQR2, 1, 15, bool);
}
void STM32446ADC3_sqr2_sq9(uint8_t value)
{
	adc_setbit(&ADC3->SQR2, 5, 10, value);
}
void STM32446ADC3_sqr2_sq8(uint8_t value)
{
	adc_setbit(&ADC3->SQR2, 5, 5, value);
}
void STM32446ADC3_sqr2_sq7(uint8_t value)
{
	adc_setbit(&ADC3->SQR2, 5, 0, value);
}

// SQR3
void STM32446ADC3_sqr3_sq6(uint8_t value)
{
	adc_setbit(&ADC3->SQR3, 5, 25, value);
}
void STM32446ADC3_sqr3_sq5(uint8_t value)
{
	adc_setbit(&ADC3->SQR3, 5, 20, value);
}
void STM32446ADC3_sqr3_sq4(uint8_t value)
{
	adc_setbit(&ADC3->SQR3, 4, 16, value);
}
void STM32446ADC3_sqr3_sq4_0(uint8_t bool)
{
	adc_setbit(&ADC3->SQR3, 1, 15, bool);
}
void STM32446ADC3_sqr3_sq3(uint8_t value)
{
	adc_setbit(&ADC3->SQR3, 5, 10, value);
}
void STM32446ADC3_sqr3_sq2(uint8_t value)
{
	adc_setbit(&ADC3->SQR3, 5, 5, value);
}
void STM32446ADC3_sqr3_sq1(uint8_t value)
{
	adc_setbit(&ADC3->SQR3, 5, 0, value);
}

// JSQR
void STM32446ADC3_jsqr_jl(uint8_t value)
{
	adc_setbit(&ADC3->JSQR, 2, 20, value);
}
void STM32446ADC3_jsqr_jsq4(uint8_t value)
{
	adc_setbit(&ADC3->JSQR, 4, 16, value);
}
void STM32446ADC3_jsqr_jsq4_0(uint8_t bool)
{
	adc_setbit(&ADC3->JSQR, 1, 15, bool);
}
void STM32446ADC3_jsqr_jsq3(uint8_t value)
{
	adc_setbit(&ADC3->JSQR, 5, 10, value);
}
void STM32446ADC3_jsqr_jsq2(uint8_t value)
{
	adc_setbit(&ADC3->JSQR, 5, 5, value);
}
void STM32446ADC3_jsqr_jsq1(uint8_t value)
{
	adc_setbit(&ADC3->JSQR, 5, 0, value);
}

// Other
uint16_t STM32446ADC3_jdr1(void)
{
	return adc_getbit(ADC3->JDR1, 16, 0);
}
uint16_t STM32446ADC3_jdr2(void)
{
	return adc_getbit(ADC3->JDR2, 16, 0);
}
uint16_t STM32446ADC3_jdr3(void)
{
	return adc_getbit(ADC3->JDR3, 16, 0);
}
uint16_t STM32446ADC3_jdr4(void)
{
	return adc_getbit(ADC3->JDR4, 16, 0);
}
uint16_t STM32446ADC3_dr(void)
{
	return adc_getbit(ADC3->DR, 16, 0);
}

/*** COMMON ***/
// CSR
uint8_t STM32446ADC_csr_ovr3(void)
{
	return adc_getbit(ADC->CSR, 1, 21);
}
uint8_t STM32446ADC_csr_strt3(void)
{
	return adc_getbit(ADC->CSR, 1, 20);
}
uint8_t STM32446ADC_csr_jstrt3(void)
{
	return adc_getbit(ADC->CSR, 1, 19);
}
uint8_t STM32446ADC_csr_jeoc3(void)
{
	return adc_getbit(ADC->CSR, 1, 18);
}
uint8_t STM32446ADC_csr_eoc3(void)
{
	return adc_getbit(ADC->CSR, 1, 17);
}
uint8_t STM32446ADC_csr_awd3(void)
{
	return adc_getbit(ADC->CSR, 1, 16);
}
uint8_t STM32446ADC_csr_ovr2(void)
{
	return adc_getbit(ADC->CSR, 1, 13);
}
uint8_t STM32446ADC_csr_strt2(void)
{
	return adc_getbit(ADC->CSR, 1, 12);
}
uint8_t STM32446ADC_csr_jstrt2(void)
{
	return adc_getbit(ADC->CSR, 1, 11);
}
uint8_t STM32446ADC_csr_jeoc2(void)
{
	return adc_getbit(ADC->CSR, 1, 10);
}
uint8_t STM32446ADC_csr_eoc2(void)
{
	return adc_getbit(ADC->CSR, 1, 9);
}
uint8_t STM32446ADC_csr_awd2(void)
{
	return adc_getbit(ADC->CSR, 1, 8);
}
uint8_t STM32446ADC_csr_ovr1(void)
{
	return adc_getbit(ADC->CSR, 1, 5);
}
uint8_t STM32446ADC_csr_strt1(void)
{
	return adc_getbit(ADC->CSR, 1, 4);
}
uint8_t STM32446ADC_csr_jstrt1(void)
{
	return adc_getbit(ADC->CSR, 1, 3);
}
uint8_t STM32446ADC_csr_jeoc1(void)
{
	return adc_getbit(ADC->CSR, 1, 2);
}
uint8_t STM32446ADC_csr_eoc1(void)
{
	return adc_getbit(ADC->CSR, 1, 1);
}
uint8_t STM32446ADC_csr_awd1(void)
{
	return adc_getbit(ADC->CSR, 1, 0);
}

// CCR
void STM32446ADC_ccr_tsvrefe(uint8_t bool)
{
	adc_setbit(&ADC->CCR, 1, 23, bool);
}
void STM32446ADC_ccr_vbate(uint8_t bool)
{
	adc_setbit(&ADC->CCR, 2, 22, bool);
}
void STM32446ADC_ccr_adcpre(uint8_t value)
{
	adc_setbit(&ADC->CCR, 2, 16, value);
}
void STM32446ADC_ccr_dma(uint8_t value)
{
	adc_setbit(&ADC->CCR, 2, 14, value);
}
void STM32446ADC_ccr_dds(uint8_t bool)
{
	adc_setbit(&ADC->CCR, 1, 13, bool);
}
void STM32446ADC_ccr_delay(uint8_t value)
{
	adc_setbit(&ADC->CCR, 4, 8, value);
}
void STM32446ADC_ccr_multi(uint8_t value)
{
	adc_setbit(&ADC->CCR, 5, 0, value);
}

// CDR
uint32_t STM32446ADC_cdr(void)
{
	return adc_getbit(ADC->CDR, 32, 0);
}

/*** ADC3 ***/
void STM32446Adc3Clock(void)
{
	RCC->APB2ENR |= (1 << 10); // ADC1EN: ADC1 clock enable
}

/*** Procedure & Function Definition ***/
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

uint32_t adc_getsetbit(volatile uint32_t* reg, uint32_t size_block, uint32_t bit)
{
	uint32_t n = 0;
	if(bit > 31){ n = bit/32; bit = bit - (n * 32); }
	uint32_t value = 0;
	uint32_t mask = (unsigned int)((1 << size_block) - 1);
	value = *(reg + n ) & ~(mask << bit);
	value = (value >> bit);
	return value;
}

/*** EOF ***/


