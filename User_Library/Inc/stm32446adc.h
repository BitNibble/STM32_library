/******************************************************************************
	STM32 446 ADC
Author: Sergio Santos
	<sergio.salazar.santos@gmail.com>
License: GNU General Public License
Hardware: STM32-446
Date: 02062023
Comment:
	
*******************************************************************************/
#ifndef _STM32446ADC_H_
	#define _STM32446ADC_H_

/*** Library ***/
#include <inttypes.h>

/*** Bit Mapping ***/
// SR
typedef struct
{
	uint8_t (*ovr)(void);
	void (*clear_ovr)(void);
	uint8_t (*strt)(void);
	void (*clear_strt)(void);
	uint8_t (*jstrt)(void);
	void (*clear_jstrt)(void);
	uint8_t (*jeoc)(void);
	void (*clear_jeoc)(void);
	uint8_t (*eoc)(void);
	void (*clear_eoc)(void);
	uint8_t (*awd)(void);
	void (*clear_awd)(void);
}STM32446ADC_SR;

// CR1
typedef struct
{
	void (*ovrie)(uint8_t bool);
	void (*res)(uint8_t value);
	void (*awden)(uint8_t bool);
	void (*jawden)(uint8_t bool);
	void (*discnum)(uint8_t value);
	void (*jdiscen)(uint8_t bool);
	void (*discen)(uint8_t bool);
	void (*jauto)(uint8_t bool);
	void (*awdsgl)(uint8_t bool);
	void (*scan)(uint8_t bool);
	void (*jeocie)(uint8_t bool);
	void (*awdie)(uint8_t bool);
	void (*eocie)(uint8_t bool);
	void (*awdch)(uint8_t value);
}STM32446ADC_CR1;

// CR2
typedef struct
{
	void (*swstart)(uint8_t bool);
	void (*exten)(uint8_t value);
	void (*extsel)(uint8_t value);
	void (*jswstart)(uint8_t bool);
	void (*jexten)(uint8_t value);
	void (*jextsel)(uint8_t value);
	void (*align)(uint8_t bool);
	void (*eocs)(uint8_t bool);
	void (*dds)(uint8_t bool);
	void (*dma)(uint8_t bool);
	void (*cont)(uint8_t bool);
	void (*adon)(uint8_t bool);
}STM32446ADC_CR2;

// SMPR1
typedef struct
{
	void (*smp18)(uint8_t value);
	void (*smp17)(uint8_t value);
	void (*smp16)(uint8_t value);
	void (*smp15)(uint8_t value);
	void (*smp15_0)(uint8_t bool);
	void (*smp14)(uint8_t value);
	void (*smp13)(uint8_t value);
	void (*smp12)(uint8_t value);
	void (*smp11)(uint8_t value);
	void (*smp10)(uint8_t value);
}STM32446ADC_SMPR1;

// SMPR2
typedef struct
{
	void (*smp9)(uint8_t value);
	void (*smp8)(uint8_t value);
	void (*smp7)(uint8_t value);
	void (*smp6)(uint8_t value);
	void (*smp5)(uint8_t bool);
	void (*smp5_0)(uint8_t bool);
	void (*smp4)(uint8_t value);
	void (*smp3)(uint8_t value);
	void (*smp2)(uint8_t value);
	void (*smp1)(uint8_t value);
	void (*smp0)(uint8_t value);
}STM32446ADC_SMPR2;

// SQR1
typedef struct
{
	void (*l)(uint8_t value);
	void (*sq16)(uint8_t value);
	void (*sq16_0)(uint8_t bool);
	void (*sq15)(uint8_t value);
	void (*sq14)(uint8_t value);
	void (*sq13)(uint8_t value);
}STM32446ADC_SQR1;

// SQR2
typedef struct
{
	void (*sq12)(uint8_t value);
	void (*sq11)(uint8_t value);
	void (*sq10)(uint8_t value);
	void (*sq10_0)(uint8_t bool);
	void (*sq9)(uint8_t value);
	void (*sq8)(uint8_t value);
	void (*sq7)(uint8_t value);
}STM32446ADC_SQR2;

// SQR3
typedef struct
{
	void (*sq6)(uint8_t value);
	void (*sq5)(uint8_t value);
	void (*sq4)(uint8_t value);
	void (*sq4_0)(uint8_t bool);
	void (*sq3)(uint8_t value);
	void (*sq2)(uint8_t value);
	void (*sq1)(uint8_t value);
}STM32446ADC_SQR3;

// JSQR
typedef struct
{
	void (*jl)(uint8_t value);
	void (*jsq4)(uint8_t value);
	void (*jsq4_0)(uint8_t bool);
	void (*jsq3)(uint8_t value);
	void (*jsq2)(uint8_t value);
	void (*jsq1)(uint8_t value);
}STM32446ADC_JSQR;

// CSR
typedef struct
{
	uint8_t (*ovr3)(void);
	uint8_t (*strt3)(void);
	uint8_t (*jstrt3)(void);
	uint8_t (*jeoc3)(void);
	uint8_t (*eoc3)(void);
	uint8_t (*awd3)(void);
	uint8_t (*ovr2)(void);
	uint8_t (*strt2)(void);
	uint8_t (*jstrt2)(void);
	uint8_t (*jeoc2)(void);
	uint8_t (*eoc2)(void);
	uint8_t (*awd2)(void);
	uint8_t (*ovr1)(void);
	uint8_t (*strt1)(void);
	uint8_t (*jstrt1)(void);
	uint8_t (*jeoc1)(void);
	uint8_t (*eoc1)(void);
	uint8_t (*awd1)(void);
}STM32446ADC_CSR;

// CCR
typedef struct
{
	void (*tsvrefe)(uint8_t bool);
	void (*vbate)(uint8_t bool);
	void (*adcpre)(uint8_t value);
	void (*dma)(uint8_t value);
	void (*dds)(uint8_t bool);
	void (*delay)(uint8_t value);
	void (*multi)(uint8_t value);
}STM32446ADC_CCR;

/*** ADC_Common ***/
typedef struct
{
	ADC_Common_TypeDef* reg;
	#if defined(_STM32446ADC_H_)
		STM32446ADC_CSR csr;
		STM32446ADC_CCR ccr;
		uint32_t (*cdr)(void);
	#endif
}STM32446ADCCOMMONobj;

typedef struct
{
	void (*inic)(void);
	void (*vbat)(void);
	void (*temp)(void);
	void (*start)(void);
	double (*read)(void);
	void (*restart)(void);
	void (*stop)(void);
}STM32446ADC1single;

/*** ADC ***/
// ADC -> ADC1
typedef struct
{
	ADC_TypeDef* reg;
	STM32446ADCCOMMONobj common;
	#if defined(_STM32446ADC_H_)
		STM32446ADC_SR sr;
		STM32446ADC_CR1 cr1;
		STM32446ADC_CR2 cr2;
		STM32446ADC_SMPR1 smpr1;
		STM32446ADC_SMPR2 smpr2;
		void (*jofr1)(uint16_t value);
		void (*jofr2)(uint16_t value);
		void (*jofr3)(uint16_t value);
		void (*jofr4)(uint16_t value);
		void (*htr)(uint16_t value);
		void (*ltr)(uint16_t value);
		STM32446ADC_SQR1 sqr1;
		STM32446ADC_SQR2 sqr2;
		STM32446ADC_SQR3 sqr3;
		STM32446ADC_JSQR jsqr;
		uint16_t (*jdr1)(void);
		uint16_t (*jdr2)(void);
		uint16_t (*jdr3)(void);
		uint16_t (*jdr4)(void);
		uint16_t (*dr)(void);
		STM32446ADC1single single;
		void (*clock)(void);
	#endif
}STM32446ADC1obj;

// ADC -> ADC2
typedef struct
{
	ADC_TypeDef* reg;
	STM32446ADCCOMMONobj common;
	#if defined(_STM32446ADC_H_)
		void (*enable)(void);
	#endif
}STM32446ADC2obj;

// ADC -> ADC3
typedef struct
{
	ADC_TypeDef* reg;
	STM32446ADCCOMMONobj common;
	#if defined(_STM32446ADC_H_)
		void (*enable)(void);
	#endif
}STM32446ADC3obj;

/***** Procedure & Funtion Header ******/
/*** ADC1 ***/
void STM32446Adc1Clock(void);
void STM32446Adc1Inic(void);
void STM32446Adc1VBAT(void);
void STM32446Adc1TEMP(void);
void STM32446Adc1Start(void);
double STM32446Adc1Read(void);
void STM32446Adc1Restart(void);
void STM32446Adc1Stop(void);

/*** ADC1 Bit Mapping ***/
// SR
uint8_t STM32446ADC_sr_ovr(void);
void STM32446ADC_sr_clear_ovr(void);
uint8_t STM32446ADC_sr_strt(void);
void STM32446ADC_sr_clear_strt(void);
uint8_t STM32446ADC_sr_jstrt(void);
void STM32446ADC_sr_clear_jstrt(void);
uint8_t STM32446ADC_sr_jeoc(void);
void STM32446ADC_sr_clear_jeoc(void);
uint8_t STM32446ADC_sr_eoc(void);
void STM32446ADC_sr_clear_eoc(void);
uint8_t STM32446ADC_sr_awd(void);
void STM32446ADC_sr_clear_awd(void);
// CR1
void STM32446ADC_cr1_ovrie(uint8_t bool);
void STM32446ADC_cr1_res(uint8_t value);
void STM32446ADC_cr1_awden(uint8_t bool);
void STM32446ADC_cr1_jawden(uint8_t bool);
void STM32446ADC_cr1_discnum(uint8_t value);
void STM32446ADC_cr1_jdiscen(uint8_t bool);
void STM32446ADC_cr1_discen(uint8_t bool);
void STM32446ADC_cr1_jauto(uint8_t bool);
void STM32446ADC_cr1_awdsgl(uint8_t bool);
void STM32446ADC_cr1_scan(uint8_t bool);
void STM32446ADC_cr1_jeocie(uint8_t bool);
void STM32446ADC_cr1_awdie(uint8_t bool);
void STM32446ADC_cr1_eocie(uint8_t bool);
void STM32446ADC_cr1_awdch(uint8_t value);
// CR2
void STM32446ADC_cr2_swstart(uint8_t bool);
void STM32446ADC_cr2_exten(uint8_t value);
void STM32446ADC_cr2_extsel(uint8_t value);
void STM32446ADC_cr2_jswstart(uint8_t bool);
void STM32446ADC_cr2_jexten(uint8_t value);
void STM32446ADC_cr2_jextsel(uint8_t value);
void STM32446ADC_cr2_align(uint8_t bool);
void STM32446ADC_cr2_eocs(uint8_t bool);
void STM32446ADC_cr2_dds(uint8_t bool);
void STM32446ADC_cr2_dma(uint8_t bool);
void STM32446ADC_cr2_cont(uint8_t bool);
void STM32446ADC_cr2_adon(uint8_t bool);
// SMPR1
void STM32446ADC_smpr1_smp18(uint8_t value);
void STM32446ADC_smpr1_smp17(uint8_t value);
void STM32446ADC_smpr1_smp16(uint8_t value);
void STM32446ADC_smpr1_smp15(uint8_t value);
void STM32446ADC_smpr1_smp15_0(uint8_t bool);
void STM32446ADC_smpr1_smp14(uint8_t value);
void STM32446ADC_smpr1_smp13(uint8_t value);
void STM32446ADC_smpr1_smp12(uint8_t value);
void STM32446ADC_smpr1_smp11(uint8_t value);
void STM32446ADC_smpr1_smp10(uint8_t value);
// SMPR2
void STM32446ADC_smpr2_smp9(uint8_t value);
void STM32446ADC_smpr2_smp8(uint8_t value);
void STM32446ADC_smpr2_smp7(uint8_t value);
void STM32446ADC_smpr2_smp6(uint8_t value);
void STM32446ADC_smpr2_smp5(uint8_t bool);
void STM32446ADC_smpr2_smp5_0(uint8_t bool);
void STM32446ADC_smpr2_smp4(uint8_t value);
void STM32446ADC_smpr2_smp3(uint8_t value);
void STM32446ADC_smpr2_smp2(uint8_t value);
void STM32446ADC_smpr2_smp1(uint8_t value);
void STM32446ADC_smpr2_smp0(uint8_t value);
// Other
void STM32446ADC_jofr1(uint16_t value);
void STM32446ADC_jofr2(uint16_t value);
void STM32446ADC_jofr3(uint16_t value);
void STM32446ADC_jofr4(uint16_t value);
void STM32446ADC_htr(uint16_t value);
void STM32446ADC_ltr(uint16_t value);
// SQR1
void STM32446ADC_sqr1_l(uint8_t value);
void STM32446ADC_sqr1_sq16(uint8_t value);
void STM32446ADC_sqr1_sq16_0(uint8_t bool);
void STM32446ADC_sqr1_sq15(uint8_t value);
void STM32446ADC_sqr1_sq14(uint8_t value);
void STM32446ADC_sqr1_sq13(uint8_t value);
// SQR2
void STM32446ADC_sqr2_sq12(uint8_t value);
void STM32446ADC_sqr2_sq11(uint8_t value);
void STM32446ADC_sqr2_sq10(uint8_t value);
void STM32446ADC_sqr2_sq10_0(uint8_t bool);
void STM32446ADC_sqr2_sq9(uint8_t value);
void STM32446ADC_sqr2_sq8(uint8_t value);
void STM32446ADC_sqr2_sq7(uint8_t value);
// SQR3
void STM32446ADC_sqr3_sq6(uint8_t value);
void STM32446ADC_sqr3_sq5(uint8_t value);
void STM32446ADC_sqr3_sq4(uint8_t value);
void STM32446ADC_sqr3_sq4_0(uint8_t bool);
void STM32446ADC_sqr3_sq3(uint8_t value);
void STM32446ADC_sqr3_sq2(uint8_t value);
void STM32446ADC_sqr3_sq1(uint8_t value);
// JSQR
void STM32446ADC_jsqr_jl(uint8_t value);
void STM32446ADC_jsqr_jsq4(uint8_t value);
void STM32446ADC_jsqr_jsq4_0(uint8_t bool);
void STM32446ADC_jsqr_jsq3(uint8_t value);
void STM32446ADC_jsqr_jsq2(uint8_t value);
void STM32446ADC_jsqr_jsq1(uint8_t value);
// Other
uint16_t STM32446ADC_jdr1(void);
uint16_t STM32446ADC_jdr2(void);
uint16_t STM32446ADC_jdr3(void);
uint16_t STM32446ADC_jdr4(void);
uint16_t STM32446ADC_dr(void);
// CSR
uint8_t STM32446ADC_csr_ovr3(void);
uint8_t STM32446ADC_csr_strt3(void);
uint8_t STM32446ADC_csr_jstrt3(void);
uint8_t STM32446ADC_csr_jeoc3(void);
uint8_t STM32446ADC_csr_eoc3(void);
uint8_t STM32446ADC_csr_awd3(void);
uint8_t STM32446ADC_csr_ovr2(void);
uint8_t STM32446ADC_csr_strt2(void);
uint8_t STM32446ADC_csr_jstrt2(void);
uint8_t STM32446ADC_csr_jeoc2(void);
uint8_t STM32446ADC_csr_eoc2(void);
uint8_t STM32446ADC_csr_awd2(void);
uint8_t STM32446ADC_csr_ovr1(void);
uint8_t STM32446ADC_csr_strt1(void);
uint8_t STM32446ADC_csr_jstrt1(void);
uint8_t STM32446ADC_csr_jeoc1(void);
uint8_t STM32446ADC_csr_eoc1(void);
uint8_t STM32446ADC_csr_awd1(void);
// CCR
void STM32446ADC_ccr_tsvrefe(uint8_t bool);
void STM32446ADC_ccr_vbate(uint8_t bool);
void STM32446ADC_ccr_adcpre(uint8_t value);
void STM32446ADC_ccr_dma(uint8_t value);
void STM32446ADC_ccr_dds(uint8_t bool);
void STM32446ADC_ccr_delay(uint8_t value);
void STM32446ADC_ccr_multi(uint8_t value);
// CDR
uint32_t STM32446ADC_cdr(void);
#endif

/*** EOF ***/

/******
1º Sequence
2º Scope
	- Library Scope
	- File Scope
	- Function Scope
	- Precedence Scope
3º Pointer and Variable
4º Casting
******/


