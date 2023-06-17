/******************************************************************************
	STM32 446 MAPPING
Author: Sergio Santos 
	<sergio.salazar.santos@gmail.com>
License: GNU General Public License
Hardware: STM32-446
Date: 15062023
Comment:
	-manual um1724, m0390, pm0056, pm0214, and other sources.
	-Virtual Image STM32-446, mapping.
	-Still in progress 15062023, increment has go along.
	-Dependent on CMSIS
	-Stable.
*******************************************************************************/
/*** File Library ***/
#include "stm32446mapping.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <math.h>

/*** File Constant & Macros ***/
// CORE
#define STM32446_SCB_BASE ((0xE000E000UL) + 0x0D00UL))

/*** File Variable ***/
static STM32446 stm32446;
static uint32_t DelayCounter;
static uint32_t mem[4];
static uint32_t nen[4];

/*** File Header ***/
/*** TOP ***/
uint32_t STM32446_readreg(uint32_t reg, uint32_t size_block, uint32_t bit);
void STM32446_writereg(volatile uint32_t* reg, uint32_t size_block, uint32_t bit, uint32_t data);
void STM32446_setreg(volatile uint32_t* reg, uint32_t size_block, uint32_t bit, uint32_t data);
void STM32446_setbit(volatile uint32_t* reg, uint32_t size_block, uint32_t bit, uint32_t data);
uint32_t STM32446_getsetbit(volatile uint32_t* reg, uint32_t size_block, uint32_t bit);

/*** SYSTICK ***/
void SystickInic(void);
void STM32446delay_ms(uint32_t ms);
void STM32446delay_10us(uint32_t ten_us);
void STM32446delay_us(uint32_t us);
// INTERRUPT
void SysTick_Handler(void);

// QUERY CLOCK
uint32_t STM32446_getclocksource(void);
uint32_t STM32446_pllsource(void);
uint16_t STM32446_gethpre(void);
uint8_t STM32446_gethppre1(void);
uint8_t STM32446_gethppre2(void);
uint8_t STM32446_getrtcpre(void);
uint8_t STM32446_gethmco1pre(void);
uint8_t STM32446_gethmco2pre(void);
uint8_t STM32446_getpllm(void);
uint16_t STM32446_getplln(void);
uint8_t STM32446_getpllp(void);
uint8_t STM32446_getpllq(void);
uint8_t STM32446_getpllr(void);
uint32_t STM32446_getsysclk(void);

/*** MISCELLANEOUS ***/
// MCU
void STM32446RegSetBits( unsigned int* reg, int n_bits, ... );
void STM32446RegResetBits( unsigned int* reg, int n_bits, ... );
void STM32446VecSetup( volatile uint32_t vec[], const unsigned int size_block, unsigned int data, unsigned int block_n );
// BUTTON
uint32_t STM32446triggerA(uint32_t hllh_io, uint8_t pin, uint32_t counter);
uint32_t STM32446triggerB(uint32_t hl_io, uint32_t lh_io, uint8_t pin, uint32_t counter);
// BYTE
uint16_t STM32ReadHLByte(STM32HighLowByte reg);
uint16_t STM32ReadLHByte(STM32HighLowByte reg);
STM32HighLowByte STM32WriteHLByte(uint16_t val);
STM32HighLowByte STM32WriteLHByte(uint16_t val);
uint16_t STM32SwapByte(uint16_t num);
// GENERIC
char* STM32446FUNCftoa(double num, char* res, uint8_t afterpoint);
char* STM32446FUNCprint( char* str, uint8_t size_str, const char* format, ... );
char STM32446bcd2dec(char num);
char STM32446dec2bcd(char num);
//COMMON
void STM32446Reverse(char s[]);
int STM32446StringLength (const char string[]);
uint8_t STM32446FUNCintinvstr(int32_t num, char* res, uint8_t n_digit);

/******* STM32F446RE Procedure & Function Definition *******/
STM32446 STM32446enable(void){
	/*** DEFAULT ***/
	mem[0] = 0;
	nen[0] = 0;
	/************* CORE ************/
	// Coprocessor Access Control Register
	stm32446.scb.reg = ((SCB_Type*) STM32446_SCB_BASE;

	// NVIC
	stm32446.nvic.reg = NVIC;
	#if defined(_STM32446NVIC_H_)
		/*** NVIC Bit Mapping Link ***/
		stm32446.nvic.set_enable = STM32446NVIC_set_enable;
		stm32446.nvic.clear_enable = STM32446NVIC_clear_enable;
		stm32446.nvic.set_pending = STM32446NVIC_set_pending;
		stm32446.nvic.clear_pending = STM32446NVIC_clear_pending;
		stm32446.nvic.active = STM32446NVIC_active;
		stm32446.nvic.priority = STM32446NVIC_priority;
		stm32446.nvic.trigger = STM32446NVIC_trigger;

	#endif

	// SysTick (Used as Delay Source)
	stm32446.systick.reg = (SysTick_Type*) SysTick_BASE;
	stm32446.systick.delay_ms = STM32446delay_ms;
	stm32446.systick.delay_10us = STM32446delay_10us;
	stm32446.systick.delay_us = STM32446delay_us;
	
	/************ MCU ************/
	// ADC -> ADC1
	stm32446.adc1.common.reg = ADC123_COMMON;
	stm32446.adc1.reg = ADC1;
	#if defined(_STM32446ADC_H_)
		stm32446.adc1.single.inic = STM32446Adc1Inic;
		stm32446.adc1.single.vbat = STM32446Adc1VBAT;
		stm32446.adc1.single.temp = STM32446Adc1TEMP;
		stm32446.adc1.single.start = STM32446Adc1Start;
		stm32446.adc1.single.read = STM32446Adc1Read;
		stm32446.adc1.single.restart = STM32446Adc1Restart;
		stm32446.adc1.single.stop = STM32446Adc1Stop;
		stm32446.adc1.clock = STM32446Adc1Clock;
		/*** ADC1 Bit Mapping Link ***/
		// SR
		stm32446.adc1.sr.ovr = STM32446ADC1_sr_ovr;
		stm32446.adc1.sr.clear_ovr = STM32446ADC1_sr_clear_ovr;
		stm32446.adc1.sr.strt = STM32446ADC1_sr_strt;
		stm32446.adc1.sr.clear_strt = STM32446ADC1_sr_clear_strt;
		stm32446.adc1.sr.jstrt = STM32446ADC1_sr_jstrt;
		stm32446.adc1.sr.clear_jstrt = STM32446ADC1_sr_clear_jstrt;
		stm32446.adc1.sr.jeoc = STM32446ADC1_sr_jeoc;
		stm32446.adc1.sr.clear_jeoc = STM32446ADC1_sr_clear_jeoc;
		stm32446.adc1.sr.eoc = STM32446ADC1_sr_eoc;
		stm32446.adc1.sr.clear_eoc = STM32446ADC1_sr_clear_eoc;
		stm32446.adc1.sr.awd =  STM32446ADC1_sr_awd;
		stm32446.adc1.sr.clear_awd = STM32446ADC1_sr_clear_awd;
		// CR1
		stm32446.adc1.cr1.ovrie = STM32446ADC1_cr1_ovrie;
		stm32446.adc1.cr1.res = STM32446ADC1_cr1_res;
		stm32446.adc1.cr1.awden = STM32446ADC1_cr1_awden;
		stm32446.adc1.cr1.jawden = STM32446ADC1_cr1_jawden;
		stm32446.adc1.cr1.discnum = STM32446ADC1_cr1_discnum;
		stm32446.adc1.cr1.jdiscen = STM32446ADC1_cr1_jdiscen;
		stm32446.adc1.cr1.discen = STM32446ADC1_cr1_discen;
		stm32446.adc1.cr1.jauto = STM32446ADC1_cr1_jauto;
		stm32446.adc1.cr1.awdsgl = STM32446ADC1_cr1_awdsgl;
		stm32446.adc1.cr1.scan = STM32446ADC1_cr1_scan;
		stm32446.adc1.cr1.jeocie = STM32446ADC1_cr1_jeocie;
		stm32446.adc1.cr1.awdie = STM32446ADC1_cr1_awdie;
		stm32446.adc1.cr1.eocie = STM32446ADC1_cr1_eocie;
		stm32446.adc1.cr1.awdch = STM32446ADC1_cr1_awdch;
		// CR2
		stm32446.adc1.cr2.swstart = STM32446ADC1_cr2_swstart;
		stm32446.adc1.cr2.exten = STM32446ADC1_cr2_exten;
		stm32446.adc1.cr2.extsel = STM32446ADC1_cr2_extsel;
		stm32446.adc1.cr2.jswstart = STM32446ADC1_cr2_jswstart;
		stm32446.adc1.cr2.jexten = STM32446ADC1_cr2_jexten;
		stm32446.adc1.cr2.jextsel = STM32446ADC1_cr2_jextsel;
		stm32446.adc1.cr2.align = STM32446ADC1_cr2_align;
		stm32446.adc1.cr2.eocs = STM32446ADC1_cr2_eocs;
		stm32446.adc1.cr2.dds = STM32446ADC1_cr2_dds;
		stm32446.adc1.cr2.dma = STM32446ADC1_cr2_dma;
		stm32446.adc1.cr2.cont = STM32446ADC1_cr2_cont;
		stm32446.adc1.cr2.adon = STM32446ADC1_cr2_adon;
		// SMPR1
		stm32446.adc1.smpr1.smp18 = STM32446ADC1_smpr1_smp18;
		stm32446.adc1.smpr1.smp17 = STM32446ADC1_smpr1_smp17;
		stm32446.adc1.smpr1.smp16 = STM32446ADC1_smpr1_smp16;
		stm32446.adc1.smpr1.smp15 = STM32446ADC1_smpr1_smp15;
		stm32446.adc1.smpr1.smp15_0 = STM32446ADC1_smpr1_smp15_0;
		stm32446.adc1.smpr1.smp14 = STM32446ADC1_smpr1_smp14;
		stm32446.adc1.smpr1.smp13 = STM32446ADC1_smpr1_smp13;
		stm32446.adc1.smpr1.smp12 = STM32446ADC1_smpr1_smp12;
		stm32446.adc1.smpr1.smp11 = STM32446ADC1_smpr1_smp11;
		stm32446.adc1.smpr1.smp10 = STM32446ADC1_smpr1_smp10;
		// SMPR2
		stm32446.adc1.smpr2.smp9 = STM32446ADC1_smpr2_smp9;
		stm32446.adc1.smpr2.smp8 = STM32446ADC1_smpr2_smp8;
		stm32446.adc1.smpr2.smp7 = STM32446ADC1_smpr2_smp7;
		stm32446.adc1.smpr2.smp6 = STM32446ADC1_smpr2_smp6;
		stm32446.adc1.smpr2.smp5 = STM32446ADC1_smpr2_smp5;
		stm32446.adc1.smpr2.smp5_0 = STM32446ADC1_smpr2_smp5_0;
		stm32446.adc1.smpr2.smp4 = STM32446ADC1_smpr2_smp4;
		stm32446.adc1.smpr2.smp3 = STM32446ADC1_smpr2_smp3;
		stm32446.adc1.smpr2.smp2 = STM32446ADC1_smpr2_smp2;
		stm32446.adc1.smpr2.smp1 = STM32446ADC1_smpr2_smp1;
		stm32446.adc1.smpr2.smp0 = STM32446ADC1_smpr2_smp0;
		// JOFR1
		stm32446.adc1.jofr1 = STM32446ADC1_jofr1;
		// JOFR2
		stm32446.adc1.jofr2 = STM32446ADC1_jofr2;
		// JOFR3
		stm32446.adc1.jofr3 = STM32446ADC1_jofr3;
		// JOFR4
		stm32446.adc1.jofr4 = STM32446ADC1_jofr4;
		// HTR
		stm32446.adc1.htr = STM32446ADC1_htr;
		// LTR
		stm32446.adc1.ltr = STM32446ADC1_ltr;
		// SQR1
		stm32446.adc1.sqr1.l = STM32446ADC1_sqr1_l;
		stm32446.adc1.sqr1.sq16 = STM32446ADC1_sqr1_sq16;
		stm32446.adc1.sqr1.sq16_0 = STM32446ADC1_sqr1_sq16_0;
		stm32446.adc1.sqr1.sq15 = STM32446ADC1_sqr1_sq15;
		stm32446.adc1.sqr1.sq14 = STM32446ADC1_sqr1_sq14;
		stm32446.adc1.sqr1.sq13 = STM32446ADC1_sqr1_sq13;
		// SQR2
		stm32446.adc1.sqr2.sq12 = STM32446ADC1_sqr2_sq12;
		stm32446.adc1.sqr2.sq11 = STM32446ADC1_sqr2_sq11;
		stm32446.adc1.sqr2.sq10 = STM32446ADC1_sqr2_sq10;
		stm32446.adc1.sqr2.sq10_0 = STM32446ADC1_sqr2_sq10_0;
		stm32446.adc1.sqr2.sq9 = STM32446ADC1_sqr2_sq9;
		stm32446.adc1.sqr2.sq8 = STM32446ADC1_sqr2_sq8;
		stm32446.adc1.sqr2.sq7 = STM32446ADC1_sqr2_sq7;
		// SQ3
		stm32446.adc1.sqr3.sq6 = STM32446ADC1_sqr3_sq6;
		stm32446.adc1.sqr3.sq5 = STM32446ADC1_sqr3_sq5;
		stm32446.adc1.sqr3.sq4 = STM32446ADC1_sqr3_sq4;
		stm32446.adc1.sqr3.sq4_0 = STM32446ADC1_sqr3_sq4_0;
		stm32446.adc1.sqr3.sq3 = STM32446ADC1_sqr3_sq3;
		stm32446.adc1.sqr3.sq2 = STM32446ADC1_sqr3_sq2;
		stm32446.adc1.sqr3.sq1 = STM32446ADC1_sqr3_sq1;
		// JSQR
		stm32446.adc1.jsqr.jl = STM32446ADC1_jsqr_jl;
		stm32446.adc1.jsqr.jsq4 = STM32446ADC1_jsqr_jsq4;
		stm32446.adc1.jsqr.jsq4_0 = STM32446ADC1_jsqr_jsq4_0;
		stm32446.adc1.jsqr.jsq3 = STM32446ADC1_jsqr_jsq3;
		stm32446.adc1.jsqr.jsq2 = STM32446ADC1_jsqr_jsq2;
		stm32446.adc1.jsqr.jsq1 = STM32446ADC1_jsqr_jsq1;
		// JDR1
		stm32446.adc1.jdr1 = STM32446ADC1_jdr1;
		// JDR2
		stm32446.adc1.jdr2 = STM32446ADC1_jdr2;
		// JDR3
		stm32446.adc1.jdr3 = STM32446ADC1_jdr3;
		// JDR4
		stm32446.adc1.jdr4 = STM32446ADC1_jdr4;
		// DR
		stm32446.adc1.dr = STM32446ADC1_dr;
		// CSR
		stm32446.adc1.common.csr.ovr3 = STM32446ADC_csr_ovr3;
		stm32446.adc1.common.csr.strt3 = STM32446ADC_csr_strt3;
		stm32446.adc1.common.csr.jstrt3 = STM32446ADC_csr_jstrt3;
		stm32446.adc1.common.csr.jeoc3 = STM32446ADC_csr_jeoc3;
		stm32446.adc1.common.csr.eoc3 = STM32446ADC_csr_eoc3;
		stm32446.adc1.common.csr.awd3 = STM32446ADC_csr_awd3;
		stm32446.adc1.common.csr.ovr2 = STM32446ADC_csr_ovr2;
		stm32446.adc1.common.csr.strt2 = STM32446ADC_csr_strt2;
		stm32446.adc1.common.csr.jstrt2 = STM32446ADC_csr_jstrt2;
		stm32446.adc1.common.csr.jeoc2 = STM32446ADC_csr_jeoc2;
		stm32446.adc1.common.csr.eoc2 = STM32446ADC_csr_eoc2;
		stm32446.adc1.common.csr.awd2 = STM32446ADC_csr_awd2;
		stm32446.adc1.common.csr.ovr1 = STM32446ADC_csr_ovr1;
		stm32446.adc1.common.csr.strt1 = STM32446ADC_csr_strt1;
		stm32446.adc1.common.csr.jstrt1 = STM32446ADC_csr_jstrt1;
		stm32446.adc1.common.csr.jeoc1 = STM32446ADC_csr_jeoc1;
		stm32446.adc1.common.csr.eoc1 = STM32446ADC_csr_eoc1;
		stm32446.adc1.common.csr.awd1 = STM32446ADC_csr_awd1;
		// CCR
		stm32446.adc1.common.ccr.tsvrefe = STM32446ADC_ccr_tsvrefe;
		stm32446.adc1.common.ccr.vbate = STM32446ADC_ccr_vbate;
		stm32446.adc1.common.ccr.adcpre = STM32446ADC_ccr_adcpre;
		stm32446.adc1.common.ccr.dma = STM32446ADC_ccr_dma;
		stm32446.adc1.common.ccr.dds = STM32446ADC_ccr_dds;
		stm32446.adc1.common.ccr.delay = STM32446ADC_ccr_delay;
		stm32446.adc1.common.ccr.multi = STM32446ADC_ccr_multi;
		// CDR
		stm32446.adc1.common.cdr = STM32446ADC_cdr;

	#endif

	// ADC -> ADC2
	stm32446.adc2.common.reg = ADC123_COMMON;
	stm32446.adc2.reg = ADC2;
	#if defined(_STM32446ADC_H_)
		stm32446.adc2.clock = STM32446Adc2Clock;
		/*** ADC2 Bit Mapping Link ***/
		// SR
		stm32446.adc2.sr.ovr = STM32446ADC2_sr_ovr;
		stm32446.adc2.sr.clear_ovr = STM32446ADC2_sr_clear_ovr;
		stm32446.adc2.sr.strt = STM32446ADC2_sr_strt;
		stm32446.adc2.sr.clear_strt = STM32446ADC2_sr_clear_strt;
		stm32446.adc2.sr.jstrt = STM32446ADC2_sr_jstrt;
		stm32446.adc2.sr.clear_jstrt = STM32446ADC2_sr_clear_jstrt;
		stm32446.adc2.sr.jeoc = STM32446ADC2_sr_jeoc;
		stm32446.adc2.sr.clear_jeoc = STM32446ADC2_sr_clear_jeoc;
		stm32446.adc2.sr.eoc = STM32446ADC2_sr_eoc;
		stm32446.adc2.sr.clear_eoc = STM32446ADC2_sr_clear_eoc;
		stm32446.adc2.sr.awd =  STM32446ADC2_sr_awd;
		stm32446.adc2.sr.clear_awd = STM32446ADC2_sr_clear_awd;
		// CR1
		stm32446.adc2.cr1.ovrie = STM32446ADC2_cr1_ovrie;
		stm32446.adc2.cr1.res = STM32446ADC2_cr1_res;
		stm32446.adc2.cr1.awden = STM32446ADC2_cr1_awden;
		stm32446.adc2.cr1.jawden = STM32446ADC2_cr1_jawden;
		stm32446.adc2.cr1.discnum = STM32446ADC2_cr1_discnum;
		stm32446.adc2.cr1.jdiscen = STM32446ADC2_cr1_jdiscen;
		stm32446.adc2.cr1.discen = STM32446ADC2_cr1_discen;
		stm32446.adc2.cr1.jauto = STM32446ADC2_cr1_jauto;
		stm32446.adc2.cr1.awdsgl = STM32446ADC2_cr1_awdsgl;
		stm32446.adc2.cr1.scan = STM32446ADC2_cr1_scan;
		stm32446.adc2.cr1.jeocie = STM32446ADC2_cr1_jeocie;
		stm32446.adc2.cr1.awdie = STM32446ADC2_cr1_awdie;
		stm32446.adc2.cr1.eocie = STM32446ADC2_cr1_eocie;
		stm32446.adc2.cr1.awdch = STM32446ADC2_cr1_awdch;
		// CR2
		stm32446.adc2.cr2.swstart = STM32446ADC2_cr2_swstart;
		stm32446.adc2.cr2.exten = STM32446ADC2_cr2_exten;
		stm32446.adc2.cr2.extsel = STM32446ADC2_cr2_extsel;
		stm32446.adc2.cr2.jswstart = STM32446ADC2_cr2_jswstart;
		stm32446.adc2.cr2.jexten = STM32446ADC2_cr2_jexten;
		stm32446.adc2.cr2.jextsel = STM32446ADC2_cr2_jextsel;
		stm32446.adc2.cr2.align = STM32446ADC2_cr2_align;
		stm32446.adc2.cr2.eocs = STM32446ADC2_cr2_eocs;
		stm32446.adc2.cr2.dds = STM32446ADC2_cr2_dds;
		stm32446.adc2.cr2.dma = STM32446ADC2_cr2_dma;
		stm32446.adc2.cr2.cont = STM32446ADC2_cr2_cont;
		stm32446.adc2.cr2.adon = STM32446ADC2_cr2_adon;
		// SMPR1
		stm32446.adc2.smpr1.smp18 = STM32446ADC2_smpr1_smp18;
		stm32446.adc2.smpr1.smp17 = STM32446ADC2_smpr1_smp17;
		stm32446.adc2.smpr1.smp16 = STM32446ADC2_smpr1_smp16;
		stm32446.adc2.smpr1.smp15 = STM32446ADC2_smpr1_smp15;
		stm32446.adc2.smpr1.smp15_0 = STM32446ADC2_smpr1_smp15_0;
		stm32446.adc2.smpr1.smp14 = STM32446ADC2_smpr1_smp14;
		stm32446.adc2.smpr1.smp13 = STM32446ADC2_smpr1_smp13;
		stm32446.adc2.smpr1.smp12 = STM32446ADC2_smpr1_smp12;
		stm32446.adc2.smpr1.smp11 = STM32446ADC2_smpr1_smp11;
		stm32446.adc2.smpr1.smp10 = STM32446ADC2_smpr1_smp10;
		// SMPR2
		stm32446.adc2.smpr2.smp9 = STM32446ADC2_smpr2_smp9;
		stm32446.adc2.smpr2.smp8 = STM32446ADC2_smpr2_smp8;
		stm32446.adc2.smpr2.smp7 = STM32446ADC2_smpr2_smp7;
		stm32446.adc2.smpr2.smp6 = STM32446ADC2_smpr2_smp6;
		stm32446.adc2.smpr2.smp5 = STM32446ADC2_smpr2_smp5;
		stm32446.adc2.smpr2.smp5_0 = STM32446ADC2_smpr2_smp5_0;
		stm32446.adc2.smpr2.smp4 = STM32446ADC2_smpr2_smp4;
		stm32446.adc2.smpr2.smp3 = STM32446ADC2_smpr2_smp3;
		stm32446.adc2.smpr2.smp2 = STM32446ADC2_smpr2_smp2;
		stm32446.adc2.smpr2.smp1 = STM32446ADC2_smpr2_smp1;
		stm32446.adc2.smpr2.smp0 = STM32446ADC2_smpr2_smp0;
		// JOFR1
		stm32446.adc2.jofr1 = STM32446ADC2_jofr1;
		// JOFR2
		stm32446.adc2.jofr2 = STM32446ADC2_jofr2;
		// JOFR3
		stm32446.adc2.jofr3 = STM32446ADC2_jofr3;
		// JOFR4
		stm32446.adc2.jofr4 = STM32446ADC2_jofr4;
		// HTR
		stm32446.adc2.htr = STM32446ADC2_htr;
		// LTR
		stm32446.adc2.ltr = STM32446ADC2_ltr;
		// SQR1
		stm32446.adc2.sqr1.l = STM32446ADC2_sqr1_l;
		stm32446.adc2.sqr1.sq16 = STM32446ADC2_sqr1_sq16;
		stm32446.adc2.sqr1.sq16_0 = STM32446ADC2_sqr1_sq16_0;
		stm32446.adc2.sqr1.sq15 = STM32446ADC2_sqr1_sq15;
		stm32446.adc2.sqr1.sq14 = STM32446ADC2_sqr1_sq14;
		stm32446.adc2.sqr1.sq13 = STM32446ADC2_sqr1_sq13;
		// SQR2
		stm32446.adc2.sqr2.sq12 = STM32446ADC2_sqr2_sq12;
		stm32446.adc2.sqr2.sq11 = STM32446ADC2_sqr2_sq11;
		stm32446.adc2.sqr2.sq10 = STM32446ADC2_sqr2_sq10;
		stm32446.adc2.sqr2.sq10_0 = STM32446ADC2_sqr2_sq10_0;
		stm32446.adc2.sqr2.sq9 = STM32446ADC2_sqr2_sq9;
		stm32446.adc2.sqr2.sq8 = STM32446ADC2_sqr2_sq8;
		stm32446.adc2.sqr2.sq7 = STM32446ADC2_sqr2_sq7;
		// SQ3
		stm32446.adc2.sqr3.sq6 = STM32446ADC2_sqr3_sq6;
		stm32446.adc2.sqr3.sq5 = STM32446ADC2_sqr3_sq5;
		stm32446.adc2.sqr3.sq4 = STM32446ADC2_sqr3_sq4;
		stm32446.adc2.sqr3.sq4_0 = STM32446ADC2_sqr3_sq4_0;
		stm32446.adc2.sqr3.sq3 = STM32446ADC2_sqr3_sq3;
		stm32446.adc2.sqr3.sq2 = STM32446ADC2_sqr3_sq2;
		stm32446.adc2.sqr3.sq1 = STM32446ADC2_sqr3_sq1;
		// JSQR
		stm32446.adc2.jsqr.jl = STM32446ADC2_jsqr_jl;
		stm32446.adc2.jsqr.jsq4 = STM32446ADC2_jsqr_jsq4;
		stm32446.adc2.jsqr.jsq4_0 = STM32446ADC2_jsqr_jsq4_0;
		stm32446.adc2.jsqr.jsq3 = STM32446ADC2_jsqr_jsq3;
		stm32446.adc2.jsqr.jsq2 = STM32446ADC2_jsqr_jsq2;
		stm32446.adc2.jsqr.jsq1 = STM32446ADC2_jsqr_jsq1;
		// JDR1
		stm32446.adc2.jdr1 = STM32446ADC2_jdr1;
		// JDR2
		stm32446.adc2.jdr2 = STM32446ADC2_jdr2;
		// JDR3
		stm32446.adc2.jdr3 = STM32446ADC2_jdr3;
		// JDR4
		stm32446.adc2.jdr4 = STM32446ADC2_jdr4;
		// DR
		stm32446.adc2.dr = STM32446ADC2_dr;
		// CSR
		stm32446.adc2.common.csr.ovr3 = STM32446ADC_csr_ovr3;
		stm32446.adc2.common.csr.strt3 = STM32446ADC_csr_strt3;
		stm32446.adc2.common.csr.jstrt3 = STM32446ADC_csr_jstrt3;
		stm32446.adc2.common.csr.jeoc3 = STM32446ADC_csr_jeoc3;
		stm32446.adc2.common.csr.eoc3 = STM32446ADC_csr_eoc3;
		stm32446.adc2.common.csr.awd3 = STM32446ADC_csr_awd3;
		stm32446.adc2.common.csr.ovr2 = STM32446ADC_csr_ovr2;
		stm32446.adc2.common.csr.strt2 = STM32446ADC_csr_strt2;
		stm32446.adc2.common.csr.jstrt2 = STM32446ADC_csr_jstrt2;
		stm32446.adc2.common.csr.jeoc2 = STM32446ADC_csr_jeoc2;
		stm32446.adc2.common.csr.eoc2 = STM32446ADC_csr_eoc2;
		stm32446.adc2.common.csr.awd2 = STM32446ADC_csr_awd2;
		stm32446.adc2.common.csr.ovr1 = STM32446ADC_csr_ovr1;
		stm32446.adc2.common.csr.strt1 = STM32446ADC_csr_strt1;
		stm32446.adc2.common.csr.jstrt1 = STM32446ADC_csr_jstrt1;
		stm32446.adc2.common.csr.jeoc1 = STM32446ADC_csr_jeoc1;
		stm32446.adc2.common.csr.eoc1 = STM32446ADC_csr_eoc1;
		stm32446.adc2.common.csr.awd1 = STM32446ADC_csr_awd1;
		// CCR
		stm32446.adc2.common.ccr.tsvrefe = STM32446ADC_ccr_tsvrefe;
		stm32446.adc2.common.ccr.vbate = STM32446ADC_ccr_vbate;
		stm32446.adc2.common.ccr.adcpre = STM32446ADC_ccr_adcpre;
		stm32446.adc2.common.ccr.dma = STM32446ADC_ccr_dma;
		stm32446.adc2.common.ccr.dds = STM32446ADC_ccr_dds;
		stm32446.adc2.common.ccr.delay = STM32446ADC_ccr_delay;
		stm32446.adc2.common.ccr.multi = STM32446ADC_ccr_multi;
		// CDR
		stm32446.adc2.common.cdr = STM32446ADC_cdr;

	#endif

	// ADC -> ADC3
	stm32446.adc3.common.reg = ADC123_COMMON;
	stm32446.adc3.reg = ADC3;
	#if defined(_STM32446ADC_H_)
		stm32446.adc3.clock = STM32446Adc3Clock;
		/*** ADC3 Bit Mapping Link ***/
		// SR
		stm32446.adc3.sr.ovr = STM32446ADC3_sr_ovr;
		stm32446.adc3.sr.clear_ovr = STM32446ADC3_sr_clear_ovr;
		stm32446.adc3.sr.strt = STM32446ADC3_sr_strt;
		stm32446.adc3.sr.clear_strt = STM32446ADC3_sr_clear_strt;
		stm32446.adc3.sr.jstrt = STM32446ADC3_sr_jstrt;
		stm32446.adc3.sr.clear_jstrt = STM32446ADC3_sr_clear_jstrt;
		stm32446.adc3.sr.jeoc = STM32446ADC3_sr_jeoc;
		stm32446.adc3.sr.clear_jeoc = STM32446ADC3_sr_clear_jeoc;
		stm32446.adc3.sr.eoc = STM32446ADC3_sr_eoc;
		stm32446.adc3.sr.clear_eoc = STM32446ADC3_sr_clear_eoc;
		stm32446.adc3.sr.awd =  STM32446ADC3_sr_awd;
		stm32446.adc3.sr.clear_awd = STM32446ADC3_sr_clear_awd;
		// CR1
		stm32446.adc3.cr1.ovrie = STM32446ADC3_cr1_ovrie;
		stm32446.adc3.cr1.res = STM32446ADC3_cr1_res;
		stm32446.adc3.cr1.awden = STM32446ADC3_cr1_awden;
		stm32446.adc3.cr1.jawden = STM32446ADC3_cr1_jawden;
		stm32446.adc3.cr1.discnum = STM32446ADC3_cr1_discnum;
		stm32446.adc3.cr1.jdiscen = STM32446ADC3_cr1_jdiscen;
		stm32446.adc3.cr1.discen = STM32446ADC3_cr1_discen;
		stm32446.adc3.cr1.jauto = STM32446ADC3_cr1_jauto;
		stm32446.adc3.cr1.awdsgl = STM32446ADC3_cr1_awdsgl;
		stm32446.adc3.cr1.scan = STM32446ADC3_cr1_scan;
		stm32446.adc3.cr1.jeocie = STM32446ADC3_cr1_jeocie;
		stm32446.adc3.cr1.awdie = STM32446ADC3_cr1_awdie;
		stm32446.adc3.cr1.eocie = STM32446ADC3_cr1_eocie;
		stm32446.adc3.cr1.awdch = STM32446ADC3_cr1_awdch;
		// CR2
		stm32446.adc3.cr2.swstart = STM32446ADC3_cr2_swstart;
		stm32446.adc3.cr2.exten = STM32446ADC3_cr2_exten;
		stm32446.adc3.cr2.extsel = STM32446ADC3_cr2_extsel;
		stm32446.adc3.cr2.jswstart = STM32446ADC3_cr2_jswstart;
		stm32446.adc3.cr2.jexten = STM32446ADC3_cr2_jexten;
		stm32446.adc3.cr2.jextsel = STM32446ADC3_cr2_jextsel;
		stm32446.adc3.cr2.align = STM32446ADC3_cr2_align;
		stm32446.adc3.cr2.eocs = STM32446ADC3_cr2_eocs;
		stm32446.adc3.cr2.dds = STM32446ADC3_cr2_dds;
		stm32446.adc3.cr2.dma = STM32446ADC3_cr2_dma;
		stm32446.adc3.cr2.cont = STM32446ADC3_cr2_cont;
		stm32446.adc3.cr2.adon = STM32446ADC3_cr2_adon;
		// SMPR1
		stm32446.adc3.smpr1.smp18 = STM32446ADC3_smpr1_smp18;
		stm32446.adc3.smpr1.smp17 = STM32446ADC3_smpr1_smp17;
		stm32446.adc3.smpr1.smp16 = STM32446ADC3_smpr1_smp16;
		stm32446.adc3.smpr1.smp15 = STM32446ADC3_smpr1_smp15;
		stm32446.adc3.smpr1.smp15_0 = STM32446ADC3_smpr1_smp15_0;
		stm32446.adc3.smpr1.smp14 = STM32446ADC3_smpr1_smp14;
		stm32446.adc3.smpr1.smp13 = STM32446ADC3_smpr1_smp13;
		stm32446.adc3.smpr1.smp12 = STM32446ADC3_smpr1_smp12;
		stm32446.adc3.smpr1.smp11 = STM32446ADC3_smpr1_smp11;
		stm32446.adc3.smpr1.smp10 = STM32446ADC3_smpr1_smp10;
		// SMPR2
		stm32446.adc3.smpr2.smp9 = STM32446ADC3_smpr2_smp9;
		stm32446.adc3.smpr2.smp8 = STM32446ADC3_smpr2_smp8;
		stm32446.adc3.smpr2.smp7 = STM32446ADC3_smpr2_smp7;
		stm32446.adc3.smpr2.smp6 = STM32446ADC3_smpr2_smp6;
		stm32446.adc3.smpr2.smp5 = STM32446ADC3_smpr2_smp5;
		stm32446.adc3.smpr2.smp5_0 = STM32446ADC3_smpr2_smp5_0;
		stm32446.adc3.smpr2.smp4 = STM32446ADC3_smpr2_smp4;
		stm32446.adc3.smpr2.smp3 = STM32446ADC3_smpr2_smp3;
		stm32446.adc3.smpr2.smp2 = STM32446ADC3_smpr2_smp2;
		stm32446.adc3.smpr2.smp1 = STM32446ADC3_smpr2_smp1;
		stm32446.adc3.smpr2.smp0 = STM32446ADC3_smpr2_smp0;
		// JOFR1
		stm32446.adc3.jofr1 = STM32446ADC3_jofr1;
		// JOFR2
		stm32446.adc3.jofr2 = STM32446ADC3_jofr2;
		// JOFR3
		stm32446.adc3.jofr3 = STM32446ADC3_jofr3;
		// JOFR4
		stm32446.adc3.jofr4 = STM32446ADC3_jofr4;
		// HTR
		stm32446.adc3.htr = STM32446ADC3_htr;
		// LTR
		stm32446.adc3.ltr = STM32446ADC3_ltr;
		// SQR1
		stm32446.adc3.sqr1.l = STM32446ADC3_sqr1_l;
		stm32446.adc3.sqr1.sq16 = STM32446ADC3_sqr1_sq16;
		stm32446.adc3.sqr1.sq16_0 = STM32446ADC3_sqr1_sq16_0;
		stm32446.adc3.sqr1.sq15 = STM32446ADC3_sqr1_sq15;
		stm32446.adc3.sqr1.sq14 = STM32446ADC3_sqr1_sq14;
		stm32446.adc3.sqr1.sq13 = STM32446ADC3_sqr1_sq13;
		// SQR2
		stm32446.adc3.sqr2.sq12 = STM32446ADC3_sqr2_sq12;
		stm32446.adc3.sqr2.sq11 = STM32446ADC3_sqr2_sq11;
		stm32446.adc3.sqr2.sq10 = STM32446ADC3_sqr2_sq10;
		stm32446.adc3.sqr2.sq10_0 = STM32446ADC3_sqr2_sq10_0;
		stm32446.adc3.sqr2.sq9 = STM32446ADC3_sqr2_sq9;
		stm32446.adc3.sqr2.sq8 = STM32446ADC3_sqr2_sq8;
		stm32446.adc3.sqr2.sq7 = STM32446ADC3_sqr2_sq7;
		// SQ3
		stm32446.adc3.sqr3.sq6 = STM32446ADC3_sqr3_sq6;
		stm32446.adc3.sqr3.sq5 = STM32446ADC3_sqr3_sq5;
		stm32446.adc3.sqr3.sq4 = STM32446ADC3_sqr3_sq4;
		stm32446.adc3.sqr3.sq4_0 = STM32446ADC3_sqr3_sq4_0;
		stm32446.adc3.sqr3.sq3 = STM32446ADC3_sqr3_sq3;
		stm32446.adc3.sqr3.sq2 = STM32446ADC3_sqr3_sq2;
		stm32446.adc3.sqr3.sq1 = STM32446ADC3_sqr3_sq1;
		// JSQR
		stm32446.adc3.jsqr.jl = STM32446ADC3_jsqr_jl;
		stm32446.adc3.jsqr.jsq4 = STM32446ADC3_jsqr_jsq4;
		stm32446.adc3.jsqr.jsq4_0 = STM32446ADC3_jsqr_jsq4_0;
		stm32446.adc3.jsqr.jsq3 = STM32446ADC3_jsqr_jsq3;
		stm32446.adc3.jsqr.jsq2 = STM32446ADC3_jsqr_jsq2;
		stm32446.adc3.jsqr.jsq1 = STM32446ADC3_jsqr_jsq1;
		// JDR1
		stm32446.adc3.jdr1 = STM32446ADC3_jdr1;
		// JDR2
		stm32446.adc3.jdr2 = STM32446ADC3_jdr2;
		// JDR3
		stm32446.adc3.jdr3 = STM32446ADC3_jdr3;
		// JDR4
		stm32446.adc3.jdr4 = STM32446ADC3_jdr4;
		// DR
		stm32446.adc3.dr = STM32446ADC3_dr;
		// CSR
		stm32446.adc3.common.csr.ovr3 = STM32446ADC_csr_ovr3;
		stm32446.adc3.common.csr.strt3 = STM32446ADC_csr_strt3;
		stm32446.adc3.common.csr.jstrt3 = STM32446ADC_csr_jstrt3;
		stm32446.adc3.common.csr.jeoc3 = STM32446ADC_csr_jeoc3;
		stm32446.adc3.common.csr.eoc3 = STM32446ADC_csr_eoc3;
		stm32446.adc3.common.csr.awd3 = STM32446ADC_csr_awd3;
		stm32446.adc3.common.csr.ovr2 = STM32446ADC_csr_ovr2;
		stm32446.adc3.common.csr.strt2 = STM32446ADC_csr_strt2;
		stm32446.adc3.common.csr.jstrt2 = STM32446ADC_csr_jstrt2;
		stm32446.adc3.common.csr.jeoc2 = STM32446ADC_csr_jeoc2;
		stm32446.adc3.common.csr.eoc2 = STM32446ADC_csr_eoc2;
		stm32446.adc3.common.csr.awd2 = STM32446ADC_csr_awd2;
		stm32446.adc3.common.csr.ovr1 = STM32446ADC_csr_ovr1;
		stm32446.adc3.common.csr.strt1 = STM32446ADC_csr_strt1;
		stm32446.adc3.common.csr.jstrt1 = STM32446ADC_csr_jstrt1;
		stm32446.adc3.common.csr.jeoc1 = STM32446ADC_csr_jeoc1;
		stm32446.adc3.common.csr.eoc1 = STM32446ADC_csr_eoc1;
		stm32446.adc3.common.csr.awd1 = STM32446ADC_csr_awd1;
		// CCR
		stm32446.adc3.common.ccr.tsvrefe = STM32446ADC_ccr_tsvrefe;
		stm32446.adc3.common.ccr.vbate = STM32446ADC_ccr_vbate;
		stm32446.adc3.common.ccr.adcpre = STM32446ADC_ccr_adcpre;
		stm32446.adc3.common.ccr.dma = STM32446ADC_ccr_dma;
		stm32446.adc3.common.ccr.dds = STM32446ADC_ccr_dds;
		stm32446.adc3.common.ccr.delay = STM32446ADC_ccr_delay;
		stm32446.adc3.common.ccr.multi = STM32446ADC_ccr_multi;
		// CDR
		stm32446.adc3.common.cdr = STM32446ADC_cdr;

	#endif

	// CRC
	stm32446.crc.reg = CRC;
	#if defined(_STM32446CRC_H_)
		/***CRC Bit Mapping Link***/
		stm32446.crc.dr = STM32446CRC_dr;
		stm32446.crc.get_dr = STM32446CRC_get_dr;
		stm32446.crc.idr = STM32446CRC_idr;
		stm32446.crc.get_idr = STM32446CRC_get_idr;
		stm32446.crc.reset = STM32446CRC_reset;

	#endif
	
	// DMA1
	stm32446.dma1.reg = DMA1;
	stm32446.dma1.stream[0].reg = DMA1_Stream0;

	// DMA2
	stm32446.dma2.reg = DMA2;
	stm32446.dma2.stream[0].reg = DMA2_Stream0;

	// FLASH
	stm32446.flash.reg = FLASH;
	#if defined(_STM32446FLASH_H_)
		/*** FLASH Bit Mapping Link ***/
		// ACR
		stm32446.flash.acr.dcrst = STM32446FLASH_acr_dcrst;
		stm32446.flash.acr.icrst = STM32446FLASH_acr_icrst;
		stm32446.flash.acr.dcen = STM32446FLASH_acr_dcen;
		stm32446.flash.acr.icen = STM32446FLASH_acr_icen;
		stm32446.flash.acr.prften = STM32446FLASH_acr_prften;
		stm32446.flash.acr.latency = STM32446FLASH_acr_latency;
		// SR
		stm32446.flash.sr.bsy = STM32446FLASH_sr_bsy;
		stm32446.flash.sr.rderr = STM32446FLASH_sr_rderr;
		stm32446.flash.sr.clear_rderr = STM32446FLASH_sr_clear_rderr;
		stm32446.flash.sr.pgserr = STM32446FLASH_sr_pgserr;
		stm32446.flash.sr.clear_pgserr = STM32446FLASH_sr_clear_pgserr;
		stm32446.flash.sr.pgperr = STM32446FLASH_sr_pgperr;
		stm32446.flash.sr.clear_pgperr = STM32446FLASH_sr_clear_pgperr;
		stm32446.flash.sr.pgaerr = STM32446FLASH_sr_pgaerr;
		stm32446.flash.sr.clear_pgaerr = STM32446FLASH_sr_clear_pgaerr;
		stm32446.flash.sr.wrperr = STM32446FLASH_sr_wrperr;
		stm32446.flash.sr.clear_wrperr = STM32446FLASH_sr_clear_wrperr;
		stm32446.flash.sr.operr = STM32446FLASH_sr_operr;
		stm32446.flash.sr.clear_operr = STM32446FLASH_sr_clear_operr;
		stm32446.flash.sr.eop = STM32446FLASH_sr_eop;
		stm32446.flash.sr.clear_eop = STM32446FLASH_sr_clear_eop;
		// CR
		stm32446.flash.cr.lock = STM32446FLASH_cr_lock;
		stm32446.flash.cr.errie = STM32446FLASH_cr_errie;
		stm32446.flash.cr.eopie = STM32446FLASH_cr_eopie;
		stm32446.flash.cr.strt = STM32446FLASH_cr_strt;
		stm32446.flash.cr.psize = STM32446FLASH_cr_psize;
		stm32446.flash.cr.snb = STM32446FLASH_cr_snb;
		stm32446.flash.cr.mer = STM32446FLASH_cr_mer;
		stm32446.flash.cr.ser = STM32446FLASH_cr_ser;
		stm32446.flash.cr.pg = STM32446FLASH_cr_pg;
		// OPTCR
		stm32446.flash.optcr.sprmod = STM32446FLASH_optcr_sprmod;
		stm32446.flash.optcr.n_wrp = STM32446FLASH_optcr_n_wrp;
		stm32446.flash.optcr.get_n_wrp = STM32446FLASH_optcr_get_n_wrp;
		stm32446.flash.optcr.rdp = STM32446FLASH_optcr_rdp;
		stm32446.flash.optcr.get_rdp = STM32446FLASH_optcr_get_rdp;
		stm32446.flash.optcr.nrst_stdby = STM32446FLASH_optcr_nrst_stdby;
		stm32446.flash.optcr.nrst_stop = STM32446FLASH_optcr_nrst_stop;
		stm32446.flash.optcr.wdg_sw = STM32446FLASH_optcr_wdg_sw;
		stm32446.flash.optcr.bor_lev = STM32446FLASH_optcr_bor_lev;
		stm32446.flash.optcr.optstrt = STM32446FLASH_optcr_optstrt;
		stm32446.flash.optcr.optlock = STM32446FLASH_optcr_optlock;
		// KEYR
		stm32446.flash.keyr = STM32446FLASH_keyr_key;
		// OPTKEYR
		stm32446.flash.optkeyr = STM32446FLASH_optkeyr_optkey;

	#endif

	// GPIOA
	stm32446.gpioa.reg = GPIOA;
	#if defined(_STM32446GPIO_H_)
		stm32446.gpioa.clock = STM32446GpioAclock;
		/*** GPIOA Bit Mapping Link ***/
		stm32446.gpioa.moder = STM32446GpioAmoder;
		stm32446.gpioa.ospeedr = STM32446GpioAospeedr;
		stm32446.gpioa.pupdr = STM32446GpioApupdr;
		stm32446.gpioa.reset = STM32446GpioAreset;
		stm32446.gpioa.set = STM32446GpioAset;
		stm32446.gpioa.afr = STM32446GpioAafr;
		/*** Other ***/
		stm32446.gpioa.func.readreg = STM32446_readreg;
		stm32446.gpioa.func.writereg = STM32446_writereg;
		stm32446.gpioa.func.setreg = STM32446_setreg;
		stm32446.gpioa.func.setbit = STM32446_setbit;
		stm32446.gpioa.func.getsetbit = STM32446_getsetbit;


	#endif

	// GPIOB
	stm32446.gpiob.reg = GPIOB;
	#if defined(_STM32446GPIO_H_)
		stm32446.gpiob.clock = STM32446GpioBclock;
		/*** GPIOB Bit Mapping Link ***/
		stm32446.gpiob.moder = STM32446GpioBmoder;
		stm32446.gpiob.ospeedr = STM32446GpioBospeedr;
		stm32446.gpiob.pupdr = STM32446GpioBpupdr;
		stm32446.gpiob.reset = STM32446GpioBreset;
		stm32446.gpiob.set = STM32446GpioBset;
		stm32446.gpiob.afr = STM32446GpioBafr;
		/*** Other ***/
		stm32446.gpiob.func.readreg = STM32446_readreg;
		stm32446.gpiob.func.writereg = STM32446_writereg;
		stm32446.gpiob.func.setreg = STM32446_setreg;
		stm32446.gpiob.func.setbit = STM32446_setbit;
		stm32446.gpiob.func.getsetbit = STM32446_getsetbit;

	#endif

	// GPIOC
	stm32446.gpioc.reg = GPIOC;
	#if defined(_STM32446GPIO_H_)
		stm32446.gpioc.clock = STM32446GpioCclock;
		/*** GPIOC Bit Mapping Link ***/
		stm32446.gpioc.moder = STM32446GpioCmoder;
		stm32446.gpioc.ospeedr = STM32446GpioCospeedr;
		stm32446.gpioc.pupdr = STM32446GpioCpupdr;
		stm32446.gpioc.reset = STM32446GpioCreset;
		stm32446.gpioc.set = STM32446GpioCset;
		stm32446.gpioc.afr = STM32446GpioCafr;
		/*** Other ***/
		stm32446.gpioc.func.readreg = STM32446_readreg;
		stm32446.gpioc.func.writereg = STM32446_writereg;
		stm32446.gpioc.func.setreg = STM32446_setreg;
		stm32446.gpioc.func.setbit = STM32446_setbit;
		stm32446.gpioc.func.getsetbit = STM32446_getsetbit;

	#endif

	// GPIOD
	stm32446.gpiod.reg = GPIOD;
	#if defined(_STM32446GPIO_H_)
		stm32446.gpiod.clock = STM32446GpioDclock;
		/*** GPIOD Bit Mapping Link ***/
		stm32446.gpiod.moder = STM32446GpioDmoder;
		stm32446.gpiod.ospeedr = STM32446GpioDospeedr;
		stm32446.gpiod.pupdr = STM32446GpioDpupdr;
		stm32446.gpiod.reset = STM32446GpioDreset;
		stm32446.gpiod.set = STM32446GpioDset;
		stm32446.gpiod.afr = STM32446GpioDafr;
		/*** Other ***/
		stm32446.gpiod.func.readreg = STM32446_readreg;
		stm32446.gpiod.func.writereg = STM32446_writereg;
		stm32446.gpiod.func.setreg = STM32446_setreg;
		stm32446.gpiod.func.setbit = STM32446_setbit;
		stm32446.gpiod.func.getsetbit = STM32446_getsetbit;

	#endif

	// GPIOE
	stm32446.gpioe.reg = GPIOE;
	#if defined(_STM32446GPIO_H_)
		stm32446.gpioe.clock = STM32446GpioEclock;
		/*** GPIOE Bit Mapping Link ***/
		stm32446.gpioe.moder = STM32446GpioEmoder;
		stm32446.gpioe.ospeedr = STM32446GpioEospeedr;
		stm32446.gpioe.pupdr = STM32446GpioEpupdr;
		stm32446.gpioe.reset = STM32446GpioEreset;
		stm32446.gpioe.set = STM32446GpioEset;
		stm32446.gpioe.afr = STM32446GpioEafr;
		/*** Other ***/
		stm32446.gpioe.func.readreg = STM32446_readreg;
		stm32446.gpioe.func.writereg = STM32446_writereg;
		stm32446.gpioe.func.setreg = STM32446_setreg;
		stm32446.gpioe.func.setbit = STM32446_setbit;
		stm32446.gpioe.func.getsetbit = STM32446_getsetbit;

	#endif

	// GPIOF
	stm32446.gpiof.reg = NULL;
	#if defined(_STM32446GPIO_H_)
		stm32446.gpiof.clock = NULL;
		/*** GPIOF Bit Mapping Link ***/
		stm32446.gpiof.moder = NULL;
		stm32446.gpiof.ospeedr = NULL;
		stm32446.gpiof.pupdr = NULL;
		stm32446.gpiof.reset = NULL;
		stm32446.gpiof.set = NULL;
		stm32446.gpiof.afr = NULL;
		/*** Other ***/
		stm32446.gpioa.func.readreg = NULL;
		stm32446.gpioa.func.writereg = NULL;
		stm32446.gpioa.func.setreg = NULL;
		stm32446.gpiof.func.setbit = NULL;
		stm32446.gpiof.func.getsetbit = NULL;

	#endif

	// GPIOG
	stm32446.gpiog.reg = NULL;
	#if defined(_STM32446GPIO_H_)
		stm32446.gpiog.clock = NULL;
		/*** GPIOG Bit Mapping Link ***/
		stm32446.gpiog.moder = NULL;
		stm32446.gpiog.ospeedr = NULL;
		stm32446.gpiog.pupdr = NULL;
		stm32446.gpiog.reset = NULL;
		stm32446.gpiog.set = NULL;
		stm32446.gpiog.afr = NULL;
		/*** Other ***/
		stm32446.gpiog.func.readreg = NULL;
		stm32446.gpiog.func.writereg = NULL;
		stm32446.gpiog.func.setreg = NULL;
		stm32446.gpiog.func.setbit = NULL;
		stm32446.gpiog.func.getsetbit = NULL;

	#endif

	// GPIOH
	stm32446.gpioh.reg = GPIOH;
	#if defined(_STM32446GPIO_H_)
		stm32446.gpioh.clock = STM32446GpioHclock;
		/*** GPIOH Bit Mapping Link ***/
		stm32446.gpioh.moder = STM32446GpioHmoder;
		stm32446.gpioh.ospeedr = STM32446GpioHospeedr;
		stm32446.gpioh.pupdr = STM32446GpioHpupdr;
		stm32446.gpioh.reset = STM32446GpioHreset;
		stm32446.gpioh.set = STM32446GpioHset;
		stm32446.gpioh.afr = STM32446GpioHafr;
		/*** Other ***/
		stm32446.gpioa.func.readreg = STM32446_readreg;
		stm32446.gpioa.func.writereg = STM32446_writereg;
		stm32446.gpioa.func.setreg = STM32446_setreg;
		stm32446.gpioh.func.setbit = STM32446_setbit;
		stm32446.gpioh.func.getsetbit = STM32446_getsetbit;

	#endif

	// SYSCFG
	stm32446.syscfg.reg = SYSCFG;
	
	// PWR
	stm32446.pwr.reg = PWR;
	#if defined(_STM32446PWR_H_)
		/*** PWR Bit Mapping Link ***/
		// CR
		stm32446.pwr.cr.fissr = STM32446PWR_cr_fissr;
		stm32446.pwr.cr.fmssr = STM32446PWR_cr_fmssr;
		stm32446.pwr.cr.uden = STM32446PWR_cr_uden;
		stm32446.pwr.cr.odswen = STM32446PWR_cr_odswen;
		stm32446.pwr.cr.oden = STM32446PWR_cr_oden;
		stm32446.pwr.cr.vos = STM32446PWR_cr_vos;
		stm32446.pwr.cr.adcdc1 = STM32446PWR_cr_adcdc1;
		stm32446.pwr.cr.mruds = STM32446PWR_cr_mruds;
		stm32446.pwr.cr.lpuds = STM32446PWR_cr_lpuds;
		stm32446.pwr.cr.fpds = STM32446PWR_cr_fpds;
		stm32446.pwr.cr.dbp = STM32446PWR_cr_dbp;
		stm32446.pwr.cr.pls = STM32446PWR_cr_pls;
		stm32446.pwr.cr.get_pls = STM32446PWR_cr_get_pls;
		stm32446.pwr.cr.pvde = STM32446PWR_cr_pvde;
		stm32446.pwr.cr.clear_csbf = STM32446PWR_cr_clear_csbf;
		stm32446.pwr.cr.clear_cwuf = STM32446PWR_cr_clear_cwuf;
		stm32446.pwr.cr.pdds =STM32446PWR_cr_pdds;
		stm32446.pwr.cr.lpds = STM32446PWR_cr_lpds;
		// CSR
		stm32446.pwr.csr.udrdy = STM32446PWR_udrdy;
		stm32446.pwr.csr.clear_udrdy = STM32446PWR_csr_clear_udrdy;
		stm32446.pwr.csr.odswrdy = STM32446PWR_csr_odswrdy;
		stm32446.pwr.csr.odrdy = STM32446PWR_csr_odrdy;
		stm32446.pwr.csr.vosrdy = STM32446PWR_csr_vosrdy;
		stm32446.pwr.csr.bre = STM32446PWR_csr_bre;
		stm32446.pwr.csr.ewup1 = STM32446PWR_csr_ewup1;
		stm32446.pwr.csr.ewup2 = STM32446PWR_csr_ewup2;
		stm32446.pwr.csr.brr = STM32446PWR_csr_brr;
		stm32446.pwr.csr.pvdo = STM32446PWR_csr_pvdo;
		stm32446.pwr.csr.sbf = STM32446PWR_csr_sbf;
		stm32446.pwr.csr.wuf = STM32446PWR_csr_wuf;

	#endif

	// PLL
	#if defined(_STM32446RCC_H_)
		stm32446.rcc.pll.enable = STM32446RccPLLCLKEnable;
		stm32446.rcc.plli2s.enable = STM32446RccPLLI2SEnable;
		stm32446.rcc.pllsai.enable = STM32446RccPLLSAIEnable;
		stm32446.rcc.pll.division = STM32446PLLDivision;
		stm32446.rcc.prescaler = STM32446Prescaler;

	#endif

	// RCC
	stm32446.rcc.reg = RCC;
	#if defined(_STM32446RCC_H_)
		/*** RCC Bit Mapping Link ***/
		// CR
		stm32446.rcc.cr.get_pllsairdy = STM32446RCC_CR_get_pllsairdy;
		stm32446.rcc.cr.pllsaion = STM32446RCC_CR_pllsaion;
		stm32446.rcc.cr.get_plli2srdy = STM32446RCC_CR_get_plli2srdy;
		stm32446.rcc.cr.plli2son = STM32446RCC_CR_plli2son;
		stm32446.rcc.cr.get_pllrdy = STM32446RCC_CR_get_pllrdy;
		stm32446.rcc.cr.pllon = STM32446RCC_CR_pllon;
		stm32446.rcc.cr.csson = STM32446RCC_CR_csson;
		stm32446.rcc.cr.hsebyp = STM32446RCC_CR_hsebyp;
		stm32446.rcc.cr.get_hserdy = STM32446RCC_CR_get_hserdy;
		stm32446.rcc.cr.hseon = STM32446RCC_CR_hseon;
		stm32446.rcc.cr.get_hsical = STM32446RCC_CR_get_hsical;
		stm32446.rcc.cr.hsitrim = STM32446RCC_CR_hsitrim;
		stm32446.rcc.cr.get_hsirdy = STM32446RCC_CR_get_hsirdy;
		stm32446.rcc.cr.hsion = STM32446RCC_CR_hsion;
		// PLLCFGR
		stm32446.rcc.pllcfgr.pllr = STM32446RCC_PLLCFGR_pllr;
		stm32446.rcc.pllcfgr.pllq = STM32446RCC_PLLCFGR_pllq;
		stm32446.rcc.pllcfgr.pllsrc = STM32446RCC_PLLCFGR_pllsrc;
		stm32446.rcc.pllcfgr.pllp = STM32446RCC_PLLCFGR_pllp;
		stm32446.rcc.pllcfgr.plln = STM32446RCC_PLLCFGR_plln;
		stm32446.rcc.pllcfgr.pllm = STM32446RCC_PLLCFGR_pllm;
		// CFGR
		stm32446.rcc.cfgr.mco2 = STM32446RCC_CFGR_mco2;
		stm32446.rcc.cfgr.mco2pre = STM32446RCC_CFGR_mco2pre;
		stm32446.rcc.cfgr.mco1pre = STM32446RCC_CFGR_mco1pre;
		stm32446.rcc.cfgr.mco1 = STM32446RCC_CFGR_mco1;
		stm32446.rcc.cfgr.rtcpre = STM32446RCC_CFGR_rtcpre;
		stm32446.rcc.cfgr.ppre2 = STM32446RCC_CFGR_ppre2;
		stm32446.rcc.cfgr.ppre1 = STM32446RCC_CFGR_ppre1;
		stm32446.rcc.cfgr.hpre = STM32446RCC_CFGR_hpre;
		stm32446.rcc.cfgr.get_sws = STM32446RCC_CFGR_get_sws;
		stm32446.rcc.cfgr.sw = STM32446RCC_CFGR_sw;
		// CIR
		stm32446.rcc.cir.clear_cssc = STM32446RCC_CIR_clear_cssc;
		stm32446.rcc.cir.clear_pllsairdyc = STM32446RCC_CIR_clear_pllsairdyc;
		stm32446.rcc.cir.clear_plli2srdyc = STM32446RCC_CIR_clear_plli2srdyc;
		stm32446.rcc.cir.clear_pllrdyc = STM32446RCC_CIR_clear_pllrdyc;
		stm32446.rcc.cir.clear_hserdyc = STM32446RCC_CIR_clear_hserdyc;
		stm32446.rcc.cir.clear_hsirdyc = STM32446RCC_CIR_clear_hsirdyc;
		stm32446.rcc.cir.clear_lserdyc = STM32446RCC_CIR_clear_lserdyc;
		stm32446.rcc.cir.clear_lsirdyc = STM32446RCC_CIR_clear_lsirdyc;
		stm32446.rcc.cir.pllsairdyie = STM32446RCC_CIR_pllsairdyie;
		stm32446.rcc.cir.plli2srdyie = STM32446RCC_CIR_plli2srdyie;
		stm32446.rcc.cir.pllrdyie = STM32446RCC_CIR_pllrdyie;
		stm32446.rcc.cir.hserdyie = STM32446RCC_CIR_hserdyie;
		stm32446.rcc.cir.hsirdyie = STM32446RCC_CIR_hsirdyie;
		stm32446.rcc.cir.lserdyie = STM32446RCC_CIR_lserdyie;
		stm32446.rcc.cir.lsirdyie = STM32446RCC_CIR_lsirdyie;
		stm32446.rcc.cir.get_cssf = STM32446RCC_CIR_get_cssf;
		stm32446.rcc.cir.get_pllsairdyf = STM32446RCC_CIR_get_pllsairdyf;
		stm32446.rcc.cir.get_plli2srdyf = STM32446RCC_CIR_get_plli2srdyf;
		stm32446.rcc.cir.get_pllrdyf = STM32446RCC_CIR_get_pllrdyf;
		stm32446.rcc.cir.get_hserdyf = STM32446RCC_CIR_get_hserdyf;
		stm32446.rcc.cir.get_hsirdyf = STM32446RCC_CIR_get_hsirdyf;
		stm32446.rcc.cir.get_lserdyf = STM32446RCC_CIR_get_lserdyf;
		stm32446.rcc.cir.get_lsirdyf = STM32446RCC_CIR_get_lsirdyf;
		// AHB1RSTR
		stm32446.rcc.ahb1rstr.otghsrst = STM32446RCC_AHB1RSTR_otghsrst;
		stm32446.rcc.ahb1rstr.dma2rst = STM32446RCC_AHB1RSTR_dma2rst;
		stm32446.rcc.ahb1rstr.dma1rst = STM32446RCC_AHB1RSTR_dma1rst;
		stm32446.rcc.ahb1rstr.crcrst = STM32446RCC_AHB1RSTR_crcrst;
		stm32446.rcc.ahb1rstr.gpiohrst = STM32446RCC_AHB1RSTR_gpiohrst;
		stm32446.rcc.ahb1rstr.gpiogrst = STM32446RCC_AHB1RSTR_gpiogrst;
		stm32446.rcc.ahb1rstr.gpiofrst = STM32446RCC_AHB1RSTR_gpiofrst;
		stm32446.rcc.ahb1rstr.gpioerst = STM32446RCC_AHB1RSTR_gpioerst;
		stm32446.rcc.ahb1rstr.gpiodrst = STM32446RCC_AHB1RSTR_gpiodrst;
		stm32446.rcc.ahb1rstr.gpiocrst = STM32446RCC_AHB1RSTR_gpiocrst;
		stm32446.rcc.ahb1rstr.gpiobrst = STM32446RCC_AHB1RSTR_gpiobrst;
		stm32446.rcc.ahb1rstr.gpioarst = STM32446RCC_AHB1RSTR_gpioarst;
		// AHB2RSTR
		stm32446.rcc.ahb2rstr.otgfsrst = STM32446RCC_AHB2RSTR_otgfsrst;
		stm32446.rcc.ahb2rstr.dcmirst = STM32446RCC_AHB2RSTR_dcmirst;
		// AHB3RSTR
		stm32446.rcc.ahb3rstr.qspirst = STM32446RCC_AHB3RSTR_qspirst;
		stm32446.rcc.ahb3rstr.fmcrst = STM32446RCC_AHB3RSTR_fmcrst;
		// APB1RSTR
		stm32446.rcc.apb1rstr.dacrst = STM32446RCC_APB1RSTR_dacrst;
		stm32446.rcc.apb1rstr.pwrrst = STM32446RCC_APB1RSTR_pwrrst;
		stm32446.rcc.apb1rstr.cecrst = STM32446RCC_APB1RSTR_cecrst;
		stm32446.rcc.apb1rstr.can2rst = STM32446RCC_APB1RSTR_can2rst;
		stm32446.rcc.apb1rstr.can1rst = STM32446RCC_APB1RSTR_can1rst;
		stm32446.rcc.apb1rstr.fmpi2c1rst = STM32446RCC_APB1RSTR_fmpi2c1rst;
		stm32446.rcc.apb1rstr.i2c3rst = STM32446RCC_APB1RSTR_i2c3rst;
		stm32446.rcc.apb1rstr.i2c2rst = STM32446RCC_APB1RSTR_i2c2rst;
		stm32446.rcc.apb1rstr.i2c1rst = STM32446RCC_APB1RSTR_i2c1rst;
		stm32446.rcc.apb1rstr.uart5rst = STM32446RCC_APB1RSTR_uart5rst;
		stm32446.rcc.apb1rstr.uart4rst = STM32446RCC_APB1RSTR_uart4rst;
		stm32446.rcc.apb1rstr.usart3rst = STM32446RCC_APB1RSTR_usart3rst;
		stm32446.rcc.apb1rstr.usart2rst = STM32446RCC_APB1RSTR_usart2rst;
		stm32446.rcc.apb1rstr.spdifrxrst = STM32446RCC_APB1RSTR_spdifrxrst;
		stm32446.rcc.apb1rstr.spi3rst = STM32446RCC_APB1RSTR_spi3rst;
		stm32446.rcc.apb1rstr.spi2rst = STM32446RCC_APB1RSTR_spi2rst;
		stm32446.rcc.apb1rstr.wwdgrst = STM32446RCC_APB1RSTR_wwdgrst;
		stm32446.rcc.apb1rstr.tim14rst = STM32446RCC_APB1RSTR_tim14rst;
		stm32446.rcc.apb1rstr.tim13rst = STM32446RCC_APB1RSTR_tim13rst;
		stm32446.rcc.apb1rstr.tim12rst = STM32446RCC_APB1RSTR_tim12rst;
		stm32446.rcc.apb1rstr.tim7rst = STM32446RCC_APB1RSTR_tim7rst;
		stm32446.rcc.apb1rstr.tim6rst = STM32446RCC_APB1RSTR_tim6rst;
		stm32446.rcc.apb1rstr.tim5rst = STM32446RCC_APB1RSTR_tim5rst;
		stm32446.rcc.apb1rstr.tim4rst = STM32446RCC_APB1RSTR_tim4rst;
		stm32446.rcc.apb1rstr.tim3rst = STM32446RCC_APB1RSTR_tim3rst;
		stm32446.rcc.apb1rstr.tim2rst = STM32446RCC_APB1RSTR_tim2rst;
		// APB2RSTR
		stm32446.rcc.apb2rstr.sai2rst = STM32446RCC_APB2RSTR_sai2rst;
		stm32446.rcc.apb2rstr.sai1rst = STM32446RCC_APB2RSTR_sai1rst;
		stm32446.rcc.apb2rstr.tim11rst = STM32446RCC_APB2RSTR_tim11rst;
		stm32446.rcc.apb2rstr.tim10rst = STM32446RCC_APB2RSTR_tim10rst;
		stm32446.rcc.apb2rstr.tim9rst = STM32446RCC_APB2RSTR_tim9rst;
		stm32446.rcc.apb2rstr.syscfgrst = STM32446RCC_APB2RSTR_syscfgrst;
		stm32446.rcc.apb2rstr.spi4rst = STM32446RCC_APB2RSTR_spi4rst;
		stm32446.rcc.apb2rstr.spi1rst = STM32446RCC_APB2RSTR_spi1rst;
		stm32446.rcc.apb2rstr.sdiorst = STM32446RCC_APB2RSTR_sdiorst;
		stm32446.rcc.apb2rstr.adcrst = STM32446RCC_APB2RSTR_adcrst;
		stm32446.rcc.apb2rstr.usart6rst = STM32446RCC_APB2RSTR_usart6rst;
		stm32446.rcc.apb2rstr.usart1rst = STM32446RCC_APB2RSTR_usart1rst;
		stm32446.rcc.apb2rstr.tim8rst = STM32446RCC_APB2RSTR_tim8rst;
		stm32446.rcc.apb2rstr.tim1rst = STM32446RCC_APB2RSTR_tim1rst;
		// AHB1ENR
		stm32446.rcc.ahb1enr.otghsulpien = STM32446RCC_AHB1ENR_otghsulpien;
		stm32446.rcc.ahb1enr.otghsen = STM32446RCC_AHB1ENR_otghsen;
		stm32446.rcc.ahb1enr.dma2en = STM32446RCC_AHB1ENR_dma2en;
		stm32446.rcc.ahb1enr.dma1en = STM32446RCC_AHB1ENR_dma1en;
		stm32446.rcc.ahb1enr.bkpsramen = STM32446RCC_AHB1ENR_bkpsramen;
		stm32446.rcc.ahb1enr.crcen = STM32446RCC_AHB1ENR_crcen;
		stm32446.rcc.ahb1enr.gpiohen = STM32446RCC_AHB1ENR_gpiohen;
		stm32446.rcc.ahb1enr.gpiogen = STM32446RCC_AHB1ENR_gpiogen;
		stm32446.rcc.ahb1enr.gpiofen = STM32446RCC_AHB1ENR_gpiofen;
		stm32446.rcc.ahb1enr.gpioeen = STM32446RCC_AHB1ENR_gpioeen;
		stm32446.rcc.ahb1enr.gpioden = STM32446RCC_AHB1ENR_gpioden;
		stm32446.rcc.ahb1enr.gpiocen = STM32446RCC_AHB1ENR_gpiocen;
		stm32446.rcc.ahb1enr.gpioben = STM32446RCC_AHB1ENR_gpioben;
		stm32446.rcc.ahb1enr.gpioaen = STM32446RCC_AHB1ENR_gpioaen;
		// AHB2ENR
		stm32446.rcc.ahb2enr.otgfsen = STM32446RCC_AHB2ENR_otgfsen;
		stm32446.rcc.ahb2enr.dcmien = STM32446RCC_AHB2ENR_dcmien;
		// AHB3ENR
		stm32446.rcc.ahb3enr.qspien = STM32446RCC_AHB3ENR_qspien;
		stm32446.rcc.ahb3enr.fmcen = STM32446RCC_AHB3ENR_fmcen;
		// APB1ENR
		stm32446.rcc.apb1enr.dacen = STM32446RCC_APB1ENR_dacen;
		stm32446.rcc.apb1enr.pwren = STM32446RCC_APB1ENR_pwren;
		stm32446.rcc.apb1enr.cecen = STM32446RCC_APB1ENR_cecen;
		stm32446.rcc.apb1enr.can2en = STM32446RCC_APB1ENR_can2en;
		stm32446.rcc.apb1enr.can1en = STM32446RCC_APB1ENR_can1en;
		stm32446.rcc.apb1enr.fmpi2c1en = STM32446RCC_APB1ENR_fmpi2c1en;
		stm32446.rcc.apb1enr.i2c3en = STM32446RCC_APB1ENR_i2c3en;
		stm32446.rcc.apb1enr.i2c2en = STM32446RCC_APB1ENR_i2c2en;
		stm32446.rcc.apb1enr.i2c1en = STM32446RCC_APB1ENR_i2c1en;
		stm32446.rcc.apb1enr.uart5en = STM32446RCC_APB1ENR_uart5en;
		stm32446.rcc.apb1enr.uart4en = STM32446RCC_APB1ENR_uart4en;
		stm32446.rcc.apb1enr.usart3en = STM32446RCC_APB1ENR_usart3en;
		stm32446.rcc.apb1enr.usart2en = STM32446RCC_APB1ENR_usart2en;
		stm32446.rcc.apb1enr.spdifrxen = STM32446RCC_APB1ENR_spdifrxen;
		stm32446.rcc.apb1enr.spi3en = STM32446RCC_APB1ENR_spi3en;
		stm32446.rcc.apb1enr.spi2en = STM32446RCC_APB1ENR_spi2en;
		stm32446.rcc.apb1enr.wwdgen = STM32446RCC_APB1ENR_wwdgen;
		stm32446.rcc.apb1enr.tim14en = STM32446RCC_APB1ENR_tim14en;
		stm32446.rcc.apb1enr.tim13en = STM32446RCC_APB1ENR_tim13en;
		stm32446.rcc.apb1enr.tim12en = STM32446RCC_APB1ENR_tim12en;
		stm32446.rcc.apb1enr.tim7en = STM32446RCC_APB1ENR_tim7en;
		stm32446.rcc.apb1enr.tim6en = STM32446RCC_APB1ENR_tim6en;
		stm32446.rcc.apb1enr.tim5en = STM32446RCC_APB1ENR_tim5en;
		stm32446.rcc.apb1enr.tim4en = STM32446RCC_APB1ENR_tim4en;
		stm32446.rcc.apb1enr.tim3en = STM32446RCC_APB1ENR_tim3en;
		stm32446.rcc.apb1enr.tim2en = STM32446RCC_APB1ENR_tim2en;
		// APB2ENR
		stm32446.rcc.apb2enr.sai2en = STM32446RCC_APB2ENR_sai2en;
		stm32446.rcc.apb2enr.sai1en = STM32446RCC_APB2ENR_sai1en;
		stm32446.rcc.apb2enr.tim11en = STM32446RCC_APB2ENR_tim11en;
		stm32446.rcc.apb2enr.tim10en = STM32446RCC_APB2ENR_tim10en;
		stm32446.rcc.apb2enr.tim9en = STM32446RCC_APB2ENR_tim9en;
		stm32446.rcc.apb2enr.syscfgen = STM32446RCC_APB2ENR_syscfgen;
		stm32446.rcc.apb2enr.spi4en = STM32446RCC_APB2ENR_spi4en;
		stm32446.rcc.apb2enr.spi1en = STM32446RCC_APB2ENR_spi1en;
		stm32446.rcc.apb2enr.sdioen = STM32446RCC_APB2ENR_sdioen;
		stm32446.rcc.apb2enr.adc3en = STM32446RCC_APB2ENR_adc3en;
		stm32446.rcc.apb2enr.adc2en = STM32446RCC_APB2ENR_adc2en;
		stm32446.rcc.apb2enr.adc1en = STM32446RCC_APB2ENR_adc1en;
		stm32446.rcc.apb2enr.usart6en = STM32446RCC_APB2ENR_usart6en;
		stm32446.rcc.apb2enr.usart1en = STM32446RCC_APB2ENR_usart1en;
		stm32446.rcc.apb2enr.tim8en = STM32446RCC_APB2ENR_tim8en;
		stm32446.rcc.apb2enr.tim1en = STM32446RCC_APB2ENR_tim1en;
		//AHB1LPENR
		stm32446.rcc.ahb1lpenr.otghsulpilpen = STM32446RCC_AHB1LPENR_otghsulpilpen;
		stm32446.rcc.ahb1lpenr.otghslpen = STM32446RCC_AHB1LPENR_otghslpen;
		stm32446.rcc.ahb1lpenr.dma2lpen = STM32446RCC_AHB1LPENR_dma2lpen;
		stm32446.rcc.ahb1lpenr.dma1lpen = STM32446RCC_AHB1LPENR_dma1lpen;
		stm32446.rcc.ahb1lpenr.bkpsramlpen = STM32446RCC_AHB1LPENR_bkpsramlpen;
		stm32446.rcc.ahb1lpenr.sram2lpen = STM32446RCC_AHB1LPENR_sram2lpen;
		stm32446.rcc.ahb1lpenr.sram1lpen = STM32446RCC_AHB1LPENR_sram1lpen;
		stm32446.rcc.ahb1lpenr.flitflpen = STM32446RCC_AHB1LPENR_flitflpen;
		stm32446.rcc.ahb1lpenr.crclpen = STM32446RCC_AHB1LPENR_crclpen;
		stm32446.rcc.ahb1lpenr.gpiohlpen = STM32446RCC_AHB1LPENR_gpiohlpen;
		stm32446.rcc.ahb1lpenr.gpioglpen = STM32446RCC_AHB1LPENR_gpioglpen;
		stm32446.rcc.ahb1lpenr.gpioflpen = STM32446RCC_AHB1LPENR_gpioflpen;
		stm32446.rcc.ahb1lpenr.gpioelpen = STM32446RCC_AHB1LPENR_gpioelpen;
		stm32446.rcc.ahb1lpenr.gpiodlpen = STM32446RCC_AHB1LPENR_gpiodlpen;
		stm32446.rcc.ahb1lpenr.gpioclpen = STM32446RCC_AHB1LPENR_gpioclpen;
		stm32446.rcc.ahb1lpenr.gpioblpen = STM32446RCC_AHB1LPENR_gpioblpen;
		stm32446.rcc.ahb1lpenr.gpioalpen = STM32446RCC_AHB1LPENR_gpioalpen;
		// AHB2LPENR
		stm32446.rcc.ahb2lpenr.otgfslpen = STM32446RCC_AHB2LPENR_otgfslpen;
		stm32446.rcc.ahb2lpenr.dcmilpen = STM32446RCC_AHB2LPENR_dcmilpen;
		// AHB3LPENR
		stm32446.rcc.ahb3lpenr.qspilpen = STM32446RCC_AHB3LPENR_qspilpen;
		stm32446.rcc.ahb3lpenr.fmclpen = STM32446RCC_AHB3LPENR_fmclpen;
		// APB1LPENR
		stm32446.rcc.apb1lpenr.daclpen = STM32446RCC_APB1LPENR_daclpen;
		stm32446.rcc.apb1lpenr.pwrlpen = STM32446RCC_APB1LPENR_pwrlpen;
		stm32446.rcc.apb1lpenr.ceclpen = STM32446RCC_APB1LPENR_ceclpen;
		stm32446.rcc.apb1lpenr.can2lpen = STM32446RCC_APB1LPENR_can2lpen;
		stm32446.rcc.apb1lpenr.can1lpen = STM32446RCC_APB1LPENR_can1lpen;
		stm32446.rcc.apb1lpenr.fmpi2c1lpen = STM32446RCC_APB1LPENR_fmpi2c1lpen;
		stm32446.rcc.apb1lpenr.i2c3lpen = STM32446RCC_APB1LPENR_i2c3lpen;
		stm32446.rcc.apb1lpenr.i2c2lpen = STM32446RCC_APB1LPENR_i2c2lpen;
		stm32446.rcc.apb1lpenr.i2c1lpen = STM32446RCC_APB1LPENR_i2c1lpen;
		stm32446.rcc.apb1lpenr.uart5lpen = STM32446RCC_APB1LPENR_uart5lpen;
		stm32446.rcc.apb1lpenr.uart4lpen = STM32446RCC_APB1LPENR_uart4lpen;
		stm32446.rcc.apb1lpenr.usart3lpen = STM32446RCC_APB1LPENR_usart3lpen;
		stm32446.rcc.apb1lpenr.usart2lpen = STM32446RCC_APB1LPENR_usart2lpen;
		stm32446.rcc.apb1lpenr.spdifrxlpen = STM32446RCC_APB1LPENR_spdifrxlpen;
		stm32446.rcc.apb1lpenr.spi3lpen = STM32446RCC_APB1LPENR_spi3lpen;
		stm32446.rcc.apb1lpenr.spi2lpen = STM32446RCC_APB1LPENR_spi2lpen;
		stm32446.rcc.apb1lpenr.wwdglpen = STM32446RCC_APB1LPENR_wwdglpen;
		stm32446.rcc.apb1lpenr.tim14lpen = STM32446RCC_APB1LPENR_tim14lpen;
		stm32446.rcc.apb1lpenr.tim13lpen = STM32446RCC_APB1LPENR_tim13lpen;
		stm32446.rcc.apb1lpenr.tim12lpen = STM32446RCC_APB1LPENR_tim12lpen;
		stm32446.rcc.apb1lpenr.tim7lpen = STM32446RCC_APB1LPENR_tim7lpen;
		stm32446.rcc.apb1lpenr.tim6lpen = STM32446RCC_APB1LPENR_tim6lpen;
		stm32446.rcc.apb1lpenr.tim5lpen = STM32446RCC_APB1LPENR_tim5lpen;
		stm32446.rcc.apb1lpenr.tim4lpen = STM32446RCC_APB1LPENR_tim4lpen;
		stm32446.rcc.apb1lpenr.tim3lpen = STM32446RCC_APB1LPENR_tim3lpen;
		stm32446.rcc.apb1lpenr.tim2lpen = STM32446RCC_APB1LPENR_tim2lpen;
		// APB2LPENR
		stm32446.rcc.apb2lpenr.sai2lpen = STM32446RCC_APB2LPENR_sai2lpen;
		stm32446.rcc.apb2lpenr.sai1lpen = STM32446RCC_APB2LPENR_sai1lpen;
		stm32446.rcc.apb2lpenr.tim11lpen = STM32446RCC_APB2LPENR_tim11lpen;
		stm32446.rcc.apb2lpenr.tim10lpen = STM32446RCC_APB2LPENR_tim10lpen;
		stm32446.rcc.apb2lpenr.tim9lpen = STM32446RCC_APB2LPENR_tim9lpen;
		stm32446.rcc.apb2lpenr.syscfglpen = STM32446RCC_APB2LPENR_syscfglpen;
		stm32446.rcc.apb2lpenr.spi4lpen = STM32446RCC_APB2LPENR_spi4lpen;
		stm32446.rcc.apb2lpenr.sai1lpen = STM32446RCC_APB2LPENR_spi1lpen;
		stm32446.rcc.apb2lpenr.sdiolpen = STM32446RCC_APB2LPENR_sdiolpen;
		stm32446.rcc.apb2lpenr.adc3lpen = STM32446RCC_APB2LPENR_adc3lpen;
		stm32446.rcc.apb2lpenr.adc2lpen = STM32446RCC_APB2LPENR_adc2lpen;
		stm32446.rcc.apb2lpenr.adc1lpen = STM32446RCC_APB2LPENR_adc1lpen;
		stm32446.rcc.apb2lpenr.usart6lpen = STM32446RCC_APB2LPENR_usart6lpen;
		stm32446.rcc.apb2lpenr.usart1lpen = STM32446RCC_APB2LPENR_usart1lpen;
		stm32446.rcc.apb2lpenr.tim8lpen = STM32446RCC_APB2LPENR_tim8lpen;
		stm32446.rcc.apb2lpenr.tim1lpen = STM32446RCC_APB2LPENR_tim1lpen;
		// BDCR
		stm32446.rcc.bdcr.bdrst = STM32446RCC_BDCR_bdrst;
		stm32446.rcc.bdcr.rtcen = STM32446RCC_BDCR_rtcen;
		stm32446.rcc.bdcr.rtcsel = STM32446RCC_BDCR_rtcsel;
		stm32446.rcc.bdcr.lsemod = STM32446RCC_BDCR_lsemod;
		stm32446.rcc.bdcr.lsebyp = STM32446RCC_BDCR_lsebyp;
		stm32446.rcc.bdcr.get_lserdy = STM32446RCC_BDCR_get_lserdy;
		stm32446.rcc.bdcr.lseon = STM32446RCC_BDCR_lseon;
		// CSR
		stm32446.rcc.csr.get_lpwrrstf = STM32446RCC_CSR_get_lpwrrstf;
		stm32446.rcc.csr.get_wwdgrstf = STM32446RCC_CSR_get_wwdgrstf;
		stm32446.rcc.csr.get_iwdqrstf = STM32446RCC_CSR_get_iwdqrstf;
		stm32446.rcc.csr.get_sftrstf = STM32446RCC_CSR_get_sftrstf;
		stm32446.rcc.csr.get_porrstf = STM32446RCC_CSR_get_porrstf;
		stm32446.rcc.csr.get_pinrstf = STM32446RCC_CSR_get_pinrstf;
		stm32446.rcc.csr.get_borrstf = STM32446RCC_CSR_get_borrstf;
		stm32446.rcc.csr.clear_rmvf = STM32446RCC_CSR_clear_rmvf;
		stm32446.rcc.csr.get_lsirdy = STM32446RCC_CSR_get_lsirdy;
		stm32446.rcc.csr.lsion = STM32446RCC_CSR_lsion;
		// SSCGR
		stm32446.rcc.sscgr.sscgen = STM32446RCC_SSCGR_sscgen;
		stm32446.rcc.sscgr.spreadsel = STM32446RCC_SSCGR_spreadsel;
		stm32446.rcc.sscgr.incstep = STM32446RCC_SSCGR_incstep;
		stm32446.rcc.sscgr.modper = STM32446RCC_SSCGR_modper;
		// PLLI2SCFGR
		stm32446.rcc.plli2scfgr.plli2sr = STM32446RCC_PLLI2SCFGR_plli2sr;
		stm32446.rcc.plli2scfgr.plli2sq = STM32446RCC_PLLI2SCFGR_plli2sq;
		stm32446.rcc.plli2scfgr.plli2sp = STM32446RCC_PLLI2SCFGR_plli2sp;
		stm32446.rcc.plli2scfgr.plli2sn = STM32446RCC_PLLI2SCFGR_plli2sn;
		stm32446.rcc.plli2scfgr.plli2sm = STM32446RCC_PLLI2SCFGR_plli2sm;
		// PLLSAICFGR
		stm32446.rcc.pllsaicfgr.pllsaiq = STM32446RCC_PLLSAICFGR_pllsaiq;
		stm32446.rcc.pllsaicfgr.pllsaip = STM32446RCC_PLLSAICFGR_pllsaip;
		stm32446.rcc.pllsaicfgr.pllsain = STM32446RCC_PLLSAICFGR_pllsain;
		stm32446.rcc.pllsaicfgr.pllsaim = STM32446RCC_PLLSAICFGR_pllsaim;
		// DCKCFGR
		stm32446.rcc.dckcfgr.i2s2src = STM32446RCC_DCKCFGR_i2s2src;
		stm32446.rcc.dckcfgr.i2s1src = STM32446RCC_DCKCFGR_i2s1src;
		stm32446.rcc.dckcfgr.timpre = STM32446RCC_DCKCFGR_timpre;
		stm32446.rcc.dckcfgr.sai2src = STM32446RCC_DCKCFGR_sai2src;
		stm32446.rcc.dckcfgr.sai1src = STM32446RCC_DCKCFGR_sai1src;
		stm32446.rcc.dckcfgr.pllsaidivq = STM32446RCC_DCKCFGR_pllsaidivq;
		stm32446.rcc.dckcfgr.plli2sdivq = STM32446RCC_DCKCFGR_plli2sdivq;
		// CKGATENR
		stm32446.rcc.ckgatenr.rcc_cken = STM32446RCC_CKGATENR_rcc_cken;
		stm32446.rcc.ckgatenr.flitf_cken = STM32446RCC_CKGATENR_flitf_cken;
		stm32446.rcc.ckgatenr.sram_cken = STM32446RCC_CKGATENR_sram_cken;
		stm32446.rcc.ckgatenr.spare_cken = STM32446RCC_CKGATENR_spare_cken;
		stm32446.rcc.ckgatenr.cm4dbg_cken = STM32446RCC_CKGATENR_cm4dbg_cken;
		stm32446.rcc.ckgatenr.ahb2apb2_cken = STM32446RCC_CKGATENR_ahb2apb2_cken;
		stm32446.rcc.ckgatenr.ahb2apb1_cken = STM32446RCC_CKGATENR_ahb2apb1_cken;
		// DCKCFGR2
		stm32446.rcc.dckcfgr2.spdifrxsel = STM32446RCC_DCKCFGR2_spdifrxsel;
		stm32446.rcc.dckcfgr2.sdiosel = STM32446RCC_DCKCFGR2_sdiosel;
		stm32446.rcc.dckcfgr2.ck48msel = STM32446RCC_DCKCFGR2_ck48msel;
		stm32446.rcc.dckcfgr2.cecsel = STM32446RCC_DCKCFGR2_cecsel;
		stm32446.rcc.dckcfgr2.fmpi2c1sel = STM32446RCC_DCKCFGR2_fmpi2c1sel;
		/*** Other ***/
		stm32446.rcc.inic = STM32446RccInic;
		stm32446.rcc.henable = STM32446RccHEnable;
		stm32446.rcc.hselect = STM32446RccHSelect;
		stm32446.rcc.lenable = STM32446RccLEnable;
		stm32446.rcc.lselect = STM32446RccLSelect;

	#endif
	
	//RTC
	stm32446.rtc.reg = RTC;
	#if defined(_STM32446RTC_H_)
		stm32446.rtc.clock = STM32446RtcClock;
		stm32446.rtc.inic = STM32446RtcInic;
		stm32446.rtc.Day = STM32446RtcDay;
		stm32446.rtc.Month = STM32446RtcMonth;
		stm32446.rtc.WeekDay = STM32446RtcWeekDay;
		stm32446.rtc.Year = STM32446RtcYear;
		stm32446.rtc.Hour = STM32446RtcHour;
		stm32446.rtc.Minute = STM32446RtcMinute;
		stm32446.rtc.Second = STM32446RtcSecond;
		stm32446.rtc.dr2vec = STM32446Rtcdr2vec;
		stm32446.rtc.tr2vec = STM32446Rtctr2vec;
		stm32446.rtc.RegWrite = STM32446RtcRegWrite;
		stm32446.rtc.RegRead = STM32446RtcRegRead;

	#endif
	
	// SRAM
	#if defined(_STM32446SRAM_H_)
		stm32446.sram.access = STM32446SramAccess;

	#endif

	// TIM -> TIM1
	stm32446.tim1.reg = TIM1;
	#if defined(_STM32446TIM_H_)
		stm32446.tim1.enable = NULL;

	#endif

	// TIM -> TIM2
	stm32446.tim2.reg = TIM2;
	#if defined(_STM32446TIM_H_)
		stm32446.tim2.enable = NULL;

	#endif

	// TIM -> TIM3
	stm32446.tim3.reg = TIM3;
	#if defined(_STM32446TIM_H_)
		stm32446.tim3.enable = NULL;

	#endif

	// TIM -> TIM4
	stm32446.tim4.reg = TIM4;
	#if defined(_STM32446TIM_H_)
		stm32446.tim4.enable = NULL;

	#endif

	// TIM -> TIM5
	stm32446.tim5.reg = TIM5;
	#if defined(_STM32446TIM_H_)
		stm32446.tim5.enable = NULL;

	#endif

	// TIM -> TIM6
	stm32446.tim6.reg = TIM6;
	#if defined(_STM32446TIM_H_)
		stm32446.tim6.enable = NULL;

	#endif

	// TIM -> TIM7
	stm32446.tim7.reg = TIM7;
	#if defined(_STM32446TIM_H_)
		stm32446.tim7.enable = NULL;

	#endif

	// TIM -> TIM8
	stm32446.tim8.reg = TIM8;
	#if defined(_STM32446TIM_H_)
		stm32446.tim8.enable = NULL;

	#endif

	// TIM -> TIM9
	stm32446.tim9.reg = TIM9;
	#if defined(_STM32446TIM_H_)
		// CLOCK
		stm32446.tim9.clock = STM32446Tim9Clock;
		// INIC
		stm32446.tim9.inic = STM32446Tim9Inic;
		/*** TIM9 Bit Mapping Link ***/
		// CR1
		stm32446.tim9.cr1.get_ckd = STM32446Tim9_get_ckd;
		stm32446.tim9.cr1.apre = STM32446Tim9_set_apre;
		stm32446.tim9.cr1.opm = STM32446Tim9_set_opm;
		stm32446.tim9.cr1.urs = STM32446Tim9_set_urs;
		stm32446.tim9.cr1.udis = STM32446Tim9_set_udis;
		stm32446.tim9.cr1.cen = STM32446Tim9_cen;
		// SMCR
		stm32446.tim9.smcr.msm = STM32446Tim9_msm;
		stm32446.tim9.smcr.ts = STM32446Tim9_ts;
		stm32446.tim9.smcr.sms = STM32446Tim9_sms;
		// DIER
		stm32446.tim9.dier.tie = STM32446Tim9_tie;
		stm32446.tim9.dier.cc2ie = STM32446Tim9_cc2ie;
		stm32446.tim9.dier.cc1ie = STM32446Tim9_cc1ie;
		stm32446.tim9.dier.uie = STM32446Tim9_uie;
		// SR
		stm32446.tim9.sr.cc2of = STM32446Tim9_cc2of;
		stm32446.tim9.sr.clear_cc2of = STM32446Tim9_clear_cc2of;
		stm32446.tim9.sr.cc1of = STM32446Tim9_cc1of;
		stm32446.tim9.sr.clear_cc1of = STM32446Tim9_clear_cc1of;
		stm32446.tim9.sr.tif = STM32446Tim9_tif;
		stm32446.tim9.sr.clear_tif = STM32446Tim9_clear_tif;
		stm32446.tim9.sr.cc2if = STM32446Tim9_cc2if;
		stm32446.tim9.sr.clear_cc2if = STM32446Tim9_clear_cc2if;
		stm32446.tim9.sr.cc1if = STM32446Tim9_cc1if;
		stm32446.tim9.sr.clear_cc1if = STM32446Tim9_clear_cc1if;
		stm32446.tim9.sr.uif = STM32446Tim9_uif;
		stm32446.tim9.sr.clear_uif = STM32446Tim9_clear_uif;
		// EGR
		stm32446.tim9.egr.tg = STM32446Tim9_tg;
		stm32446.tim9.egr.cc2g = STM32446Tim9_cc2g;
		stm32446.tim9.egr.cc1g = STM32446Tim9_cc1g;
		stm32446.tim9.egr.ug = STM32446Tim9_ug;
		// CCMR1
		stm32446.tim9.ccmr1.oc2m = STM32446Tim9_oc2m;
		stm32446.tim9.ccmr1.ic2f = STM32446Tim9_ic2f;
		stm32446.tim9.ccmr1.oc2pe = STM32446Tim9_oc2pe;
		stm32446.tim9.ccmr1.oc2fe = STM32446Tim9_oc2fe;
		stm32446.tim9.ccmr1.ic2psc = STM32446Tim9_ic2psc;
		stm32446.tim9.ccmr1.cc2s = STM32446Tim9_cc2s;
		stm32446.tim9.ccmr1.oc1m = STM32446Tim9_oc1m;
		stm32446.tim9.ccmr1.ic1f = STM32446Tim9_ic1f;
		stm32446.tim9.ccmr1.oc1pe = STM32446Tim9_oc1pe;
		stm32446.tim9.ccmr1.oc1fe = STM32446Tim9_oc1fe;
		stm32446.tim9.ccmr1.ic1psc = STM32446Tim9_ic1psc;
		stm32446.tim9.ccmr1.cc1s = STM32446Tim9_cc1s;
		// CCER
		stm32446.tim9.ccer.cc2np = STM32446Tim9_cc2np;
		stm32446.tim9.ccer.cc2p = STM32446Tim9_cc2p;
		stm32446.tim9.ccer.cc2e = STM32446Tim9_cc2e;
		stm32446.tim9.ccer.cc1np = STM32446Tim9_cc1np;
		stm32446.tim9.ccer.cc1p = STM32446Tim9_cc1p;
		stm32446.tim9.ccer.cc1e = STM32446Tim9_cc1e;
		// CNT
		stm32446.tim9.cnt = STM32446Tim9_cnt;
		stm32446.tim9.get_cnt = STM32446Tim9_get_cnt;
		// ARR
		stm32446.tim9.arr = STM32446Tim9_arr;
		// CCR1
		stm32446.tim9.ccr1 = STM32446Tim9_ccr1;
		// CCR2
		stm32446.tim9.ccr2 = STM32446Tim9_ccr2;
		// PSC
		stm32446.tim9.psc = STM32446Tim9_psc;
		// INIC
		stm32446.tim9.inic = STM32446Tim9Inic;
		// INTERRUPT
		stm32446.tim9.nvict1t9 = STM32446Tim9EnableInterrupt;

	#endif

	// TIM -> TIM10
	stm32446.tim10.reg = TIM10;
	#if defined(_STM32446TIM_H_)
		stm32446.tim10.enable = NULL;

	#endif

	// TIM -> TIM11
	stm32446.tim11.reg = TIM11;
	#if defined(_STM32446TIM_H_)
		stm32446.tim11.enable = NULL;

	#endif

	// TIM -> TIM12
	stm32446.tim12.reg = TIM12;
	#if defined(_STM32446TIM_H_)
		stm32446.tim12.enable = NULL;

	#endif

	// TIM -> TIM13
	stm32446.tim13.reg = TIM13;
	#if defined(_STM32446TIM_H_)
		stm32446.tim13.enable = NULL;

	#endif

	// TIM -> TIM14
	stm32446.tim14.reg = TIM14;
	#if defined(_STM32446TIM_H_)
		stm32446.tim14.enable = NULL;

	#endif

	// USART -> USART1
	stm32446.usart1.reg = USART1;
	#if defined(_STM32446USART_H_)
		/*** USART1 Bit Mapping Link ***/
		// SR
		stm32446.usart1.sr.cts = STM32446Usart1_cts;
		stm32446.usart1.sr.clear_cts = STM32446Usart1_clear_cts;
		stm32446.usart1.sr.lbd = STM32446Usart1_lbd;
		stm32446.usart1.sr.clear_lbd = STM32446Usart1_clear_lbd;
		stm32446.usart1.sr.txe = STM32446Usart1_txe;
		stm32446.usart1.sr.tc = STM32446Usart1_tc;
		stm32446.usart1.sr.clear_tc = STM32446Usart1_clear_tc;
		stm32446.usart1.sr.rxne = STM32446Usart1_rxne;
		stm32446.usart1.sr.clear_rxne = STM32446Usart1_clear_rxne;
		stm32446.usart1.sr.idle = STM32446Usart1_idle;
		stm32446.usart1.sr.ore = STM32446Usart1_ore;
		stm32446.usart1.sr.nf = STM32446Usart1_nf;
		stm32446.usart1.sr.fe = STM32446Usart1_fe;
		stm32446.usart1.sr.pe = STM32446Usart1_pe;
		// DR
		stm32446.usart1.dr = STM32446Usart1_dr;
		stm32446.usart1.get_dr = STM32446Usart1_get_dr;
		// BRR
		stm32446.usart1.brr.div_mantissa = STM32446Usart1_div_mantissa;
		stm32446.usart1.brr.div_fraction = STM32446Usart1_div_fraction;
		// CR1
		stm32446.usart1.cr1.over8 = STM32446Usart1_over8;
		stm32446.usart1.cr1.ue = STM32446Usart1_ue;
		stm32446.usart1.cr1.m = STM32446Usart1_m;
		stm32446.usart1.cr1.wake = STM32446Usart1_wake;
		stm32446.usart1.cr1.pce = STM32446Usart1_pce;
		stm32446.usart1.cr1.ps = STM32446Usart1_ps;
		stm32446.usart1.cr1.peie = STM32446Usart1_peie;
		stm32446.usart1.cr1.txeie = STM32446Usart1_txeie;
		stm32446.usart1.cr1.tcie = STM32446Usart1_tcie;
		stm32446.usart1.cr1.rxneie = STM32446Usart1_rxneie;
		stm32446.usart1.cr1.idleie = STM32446Usart1_idleie;
		stm32446.usart1.cr1.te = STM32446Usart1_te;
		stm32446.usart1.cr1.re = STM32446Usart1_re;
		stm32446.usart1.cr1.rwu = STM32446Usart1_rwu;
		stm32446.usart1.cr1.sbk = STM32446Usart1_sbk;
		// CR2
		stm32446.usart1.cr2.linen = STM32446Usart1_linen;
		stm32446.usart1.cr2.stop = STM32446Usart1_stop;
		stm32446.usart1.cr2.clken = STM32446Usart1_clken;
		stm32446.usart1.cr2.cpol = STM32446Usart1_cpol;
		stm32446.usart1.cr2.cpha = STM32446Usart1_cpha;
		stm32446.usart1.cr2.lbcl = STM32446Usart1_lbcl;
		stm32446.usart1.cr2.lbdie = STM32446Usart1_lbdie;
		stm32446.usart1.cr2.lbdl = STM32446Usart1_lbdl;
		stm32446.usart1.cr2.add = STM32446Usart1_add;
		// CR3
		stm32446.usart1.cr3.onebit = STM32446Usart1_onebit;
		stm32446.usart1.cr3.ctsie = STM32446Usart1_ctsie;
		stm32446.usart1.cr3.ctse = STM32446Usart1_ctse;
		stm32446.usart1.cr3.rtse = STM32446Usart1_rtse;
		stm32446.usart1.cr3.dmat = STM32446Usart1_dmat;
		stm32446.usart1.cr3.dmar = STM32446Usart1_dmar;
		stm32446.usart1.cr3.scen = STM32446Usart1_scen;
		stm32446.usart1.cr3.nack = STM32446Usart1_nack;
		stm32446.usart1.cr3.hdsel = STM32446Usart1_hdsel;
		stm32446.usart1.cr3.irlp = STM32446Usart1_irlp;
		stm32446.usart1.cr3.iren = STM32446Usart1_iren;
		stm32446.usart1.cr3.eie = STM32446Usart1_eie;
		// GTPR
		stm32446.usart1.gtpr.gt = STM32446Usart1_gt;
		stm32446.usart1.gtpr.psc = STM32446Usart1_psc;
		// Other
		stm32446.usart1.clock = STM32446Usart1Clock;
		stm32446.usart1.inic = STM32446Usart1Inic;
		stm32446.usart1.parameter = STM32446Usart1Parameter;
		stm32446.usart1.transmit = STM32446Usart1Transmit;
		stm32446.usart1.receive = STM32446Usart1Receive;
		stm32446.usart1.stop = STM32446Usart1Stop;

	#endif

	// USART -> USART2
	stm32446.usart2.reg = USART2;
	#if defined(_STM32446USART_H_)
		/*** USART2 Bit Mapping Link ***/
		// SR
		stm32446.usart2.sr.cts = STM32446Usart2_cts;
		stm32446.usart2.sr.clear_cts = STM32446Usart2_clear_cts;
		stm32446.usart2.sr.lbd = STM32446Usart2_lbd;
		stm32446.usart2.sr.clear_lbd = STM32446Usart2_clear_lbd;
		stm32446.usart2.sr.txe = STM32446Usart2_txe;
		stm32446.usart2.sr.tc = STM32446Usart2_tc;
		stm32446.usart2.sr.clear_tc = STM32446Usart2_clear_tc;
		stm32446.usart2.sr.rxne = STM32446Usart2_rxne;
		stm32446.usart2.sr.clear_rxne = STM32446Usart2_clear_rxne;
		stm32446.usart2.sr.idle = STM32446Usart2_idle;
		stm32446.usart2.sr.ore = STM32446Usart2_ore;
		stm32446.usart2.sr.nf = STM32446Usart2_nf;
		stm32446.usart2.sr.fe = STM32446Usart2_fe;
		stm32446.usart2.sr.pe = STM32446Usart2_pe;
		// DR
		stm32446.usart2.dr = STM32446Usart2_dr;
		stm32446.usart2.get_dr = STM32446Usart2_get_dr;
		// BRR
		stm32446.usart2.brr.div_mantissa = STM32446Usart2_div_mantissa;
		stm32446.usart2.brr.div_fraction = STM32446Usart2_div_fraction;
		// CR1
		stm32446.usart2.cr1.over8 = STM32446Usart2_over8;
		stm32446.usart2.cr1.ue = STM32446Usart2_ue;
		stm32446.usart2.cr1.m = STM32446Usart2_m;
		stm32446.usart2.cr1.wake = STM32446Usart2_wake;
		stm32446.usart2.cr1.pce = STM32446Usart2_pce;
		stm32446.usart2.cr1.ps = STM32446Usart2_ps;
		stm32446.usart2.cr1.peie = STM32446Usart2_peie;
		stm32446.usart2.cr1.txeie = STM32446Usart2_txeie;
		stm32446.usart2.cr1.tcie = STM32446Usart2_tcie;
		stm32446.usart2.cr1.rxneie = STM32446Usart2_rxneie;
		stm32446.usart2.cr1.idleie = STM32446Usart2_idleie;
		stm32446.usart2.cr1.te = STM32446Usart2_te;
		stm32446.usart2.cr1.re = STM32446Usart2_re;
		stm32446.usart2.cr1.rwu = STM32446Usart2_rwu;
		stm32446.usart2.cr1.sbk = STM32446Usart2_sbk;
		// CR2
		stm32446.usart2.cr2.linen = STM32446Usart2_linen;
		stm32446.usart2.cr2.stop = STM32446Usart2_stop;
		stm32446.usart2.cr2.clken = STM32446Usart2_clken;
		stm32446.usart2.cr2.cpol = STM32446Usart2_cpol;
		stm32446.usart2.cr2.cpha = STM32446Usart2_cpha;
		stm32446.usart2.cr2.lbcl = STM32446Usart2_lbcl;
		stm32446.usart2.cr2.lbdie = STM32446Usart2_lbdie;
		stm32446.usart2.cr2.lbdl = STM32446Usart2_lbdl;
		stm32446.usart2.cr2.add = STM32446Usart2_add;
		// CR3
		stm32446.usart2.cr3.onebit = STM32446Usart2_onebit;
		stm32446.usart2.cr3.ctsie = STM32446Usart2_ctsie;
		stm32446.usart2.cr3.ctse = STM32446Usart2_ctse;
		stm32446.usart2.cr3.rtse = STM32446Usart2_rtse;
		stm32446.usart2.cr3.dmat = STM32446Usart2_dmat;
		stm32446.usart2.cr3.dmar = STM32446Usart2_dmar;
		stm32446.usart2.cr3.scen = STM32446Usart2_scen;
		stm32446.usart2.cr3.nack = STM32446Usart2_nack;
		stm32446.usart2.cr3.hdsel = STM32446Usart1_hdsel;
		stm32446.usart2.cr3.irlp = STM32446Usart2_irlp;
		stm32446.usart2.cr3.iren = STM32446Usart2_iren;
		stm32446.usart2.cr3.eie = STM32446Usart2_eie;
		// GTPR
		stm32446.usart2.gtpr.gt = STM32446Usart2_gt;
		stm32446.usart2.gtpr.psc = STM32446Usart2_psc;
		// Other
		stm32446.usart2.clock = STM32446Usart2Clock;
		stm32446.usart2.parameter = STM32446Usart2Parameter;
		stm32446.usart2.transmit = STM32446Usart2Transmit;
		stm32446.usart2.receive = STM32446Usart2Receive;
		stm32446.usart2.stop = STM32446Usart2Stop;

	#endif

	// USART -> USART3
	stm32446.usart3.reg = USART3;
	#if defined(_STM32446USART_H_)
		/*** USART3 Bit Mapping Link ***/
		// SR
		stm32446.usart3.sr.cts = STM32446Usart3_cts;
		stm32446.usart3.sr.clear_cts = STM32446Usart3_clear_cts;
		stm32446.usart3.sr.lbd = STM32446Usart3_lbd;
		stm32446.usart3.sr.clear_lbd = STM32446Usart3_clear_lbd;
		stm32446.usart3.sr.txe = STM32446Usart3_txe;
		stm32446.usart3.sr.tc = STM32446Usart3_tc;
		stm32446.usart3.sr.clear_tc = STM32446Usart3_clear_tc;
		stm32446.usart3.sr.rxne = STM32446Usart3_rxne;
		stm32446.usart3.sr.clear_rxne = STM32446Usart3_clear_rxne;
		stm32446.usart3.sr.idle = STM32446Usart3_idle;
		stm32446.usart3.sr.ore = STM32446Usart3_ore;
		stm32446.usart3.sr.nf = STM32446Usart3_nf;
		stm32446.usart3.sr.fe = STM32446Usart3_fe;
		stm32446.usart3.sr.pe = STM32446Usart3_pe;
		// DR
		stm32446.usart3.dr = STM32446Usart3_dr;
		stm32446.usart3.get_dr = STM32446Usart3_get_dr;
		// BRR
		stm32446.usart3.brr.div_mantissa = STM32446Usart3_div_mantissa;
		stm32446.usart3.brr.div_fraction = STM32446Usart3_div_fraction;
		// CR1
		stm32446.usart3.cr1.over8 = STM32446Usart3_over8;
		stm32446.usart3.cr1.ue = STM32446Usart3_ue;
		stm32446.usart3.cr1.m = STM32446Usart3_m;
		stm32446.usart3.cr1.wake = STM32446Usart3_wake;
		stm32446.usart3.cr1.pce = STM32446Usart3_pce;
		stm32446.usart3.cr1.ps = STM32446Usart3_ps;
		stm32446.usart3.cr1.peie = STM32446Usart3_peie;
		stm32446.usart3.cr1.txeie = STM32446Usart3_txeie;
		stm32446.usart3.cr1.tcie = STM32446Usart3_tcie;
		stm32446.usart3.cr1.rxneie = STM32446Usart3_rxneie;
		stm32446.usart3.cr1.idleie = STM32446Usart3_idleie;
		stm32446.usart3.cr1.te = STM32446Usart3_te;
		stm32446.usart3.cr1.re = STM32446Usart3_re;
		stm32446.usart3.cr1.rwu = STM32446Usart3_rwu;
		stm32446.usart3.cr1.sbk = STM32446Usart3_sbk;
		// CR2
		stm32446.usart3.cr2.linen = STM32446Usart3_linen;
		stm32446.usart3.cr2.stop = STM32446Usart3_stop;
		stm32446.usart3.cr2.clken = STM32446Usart3_clken;
		stm32446.usart3.cr2.cpol = STM32446Usart3_cpol;
		stm32446.usart3.cr2.cpha = STM32446Usart3_cpha;
		stm32446.usart3.cr2.lbcl = STM32446Usart3_lbcl;
		stm32446.usart3.cr2.lbdie = STM32446Usart3_lbdie;
		stm32446.usart3.cr2.lbdl = STM32446Usart3_lbdl;
		stm32446.usart3.cr2.add = STM32446Usart3_add;
		// CR3
		stm32446.usart3.cr3.onebit = STM32446Usart3_onebit;
		stm32446.usart3.cr3.ctsie = STM32446Usart3_ctsie;
		stm32446.usart3.cr3.ctse = STM32446Usart3_ctse;
		stm32446.usart3.cr3.rtse = STM32446Usart3_rtse;
		stm32446.usart3.cr3.dmat = STM32446Usart3_dmat;
		stm32446.usart3.cr3.dmar = STM32446Usart3_dmar;
		stm32446.usart3.cr3.scen = STM32446Usart3_scen;
		stm32446.usart3.cr3.nack = STM32446Usart3_nack;
		stm32446.usart3.cr3.hdsel = STM32446Usart3_hdsel;
		stm32446.usart3.cr3.irlp = STM32446Usart3_irlp;
		stm32446.usart3.cr3.iren = STM32446Usart3_iren;
		stm32446.usart3.cr3.eie = STM32446Usart3_eie;
		// GTPR
		stm32446.usart3.gtpr.gt = STM32446Usart3_gt;
		stm32446.usart3.gtpr.psc = STM32446Usart3_psc;
		// Other
		stm32446.usart3.clock = STM32446Usart3Clock;
		stm32446.usart3.parameter = STM32446Usart3Parameter;
		stm32446.usart3.transmit = STM32446Usart3Transmit;
		stm32446.usart3.receive = STM32446Usart3Receive;
		stm32446.usart3.stop = STM32446Usart3Stop;

	#endif

	// USART -> UART4
	stm32446.uart4.reg = UART4;
	#if defined(_STM32446USART_H_)
		/*** UART4 Bit Mapping Link ***/
		// SR
		stm32446.uart4.sr.cts = STM32446Uart4_cts;
		stm32446.uart4.sr.clear_cts = STM32446Uart4_clear_cts;
		stm32446.uart4.sr.lbd = STM32446Uart4_lbd;
		stm32446.uart4.sr.clear_lbd = STM32446Uart4_clear_lbd;
		stm32446.uart4.sr.txe = STM32446Uart4_txe;
		stm32446.uart4.sr.tc = STM32446Uart4_tc;
		stm32446.uart4.sr.clear_tc = STM32446Uart4_clear_tc;
		stm32446.uart4.sr.rxne = STM32446Uart4_rxne;
		stm32446.uart4.sr.clear_rxne = STM32446Uart4_clear_rxne;
		stm32446.uart4.sr.idle = STM32446Uart4_idle;
		stm32446.uart4.sr.ore = STM32446Uart4_ore;
		stm32446.uart4.sr.nf = STM32446Uart4_nf;
		stm32446.uart4.sr.fe = STM32446Uart4_fe;
		stm32446.uart4.sr.pe = STM32446Uart4_pe;
		// DR
		stm32446.uart4.dr = STM32446Uart4_dr;
		stm32446.uart4.get_dr = STM32446Uart4_get_dr;
		// BRR
		stm32446.uart4.brr.div_mantissa = STM32446Uart4_div_mantissa;
		stm32446.uart4.brr.div_fraction = STM32446Uart4_div_fraction;
		// CR1
		stm32446.uart4.cr1.over8 = STM32446Uart4_over8;
		stm32446.uart4.cr1.ue = STM32446Uart4_ue;
		stm32446.uart4.cr1.m = STM32446Uart4_m;
		stm32446.uart4.cr1.wake = STM32446Uart4_wake;
		stm32446.uart4.cr1.pce = STM32446Uart4_pce;
		stm32446.uart4.cr1.ps = STM32446Uart4_ps;
		stm32446.uart4.cr1.peie = STM32446Uart4_peie;
		stm32446.uart4.cr1.txeie = STM32446Uart4_txeie;
		stm32446.uart4.cr1.tcie = STM32446Uart4_tcie;
		stm32446.uart4.cr1.rxneie = STM32446Uart4_rxneie;
		stm32446.uart4.cr1.idleie = STM32446Uart4_idleie;
		stm32446.uart4.cr1.te = STM32446Uart4_te;
		stm32446.uart4.cr1.re = STM32446Uart4_re;
		stm32446.uart4.cr1.rwu = STM32446Uart4_rwu;
		stm32446.uart4.cr1.sbk = STM32446Uart4_sbk;
		// CR2
		stm32446.uart4.cr2.linen = STM32446Uart4_linen;
		stm32446.uart4.cr2.stop = STM32446Uart4_stop;
		stm32446.uart4.cr2.clken = STM32446Uart4_clken;
		stm32446.uart4.cr2.cpol = STM32446Uart4_cpol;
		stm32446.uart4.cr2.cpha = STM32446Uart4_cpha;
		stm32446.uart4.cr2.lbcl = STM32446Uart4_lbcl;
		stm32446.uart4.cr2.lbdie = STM32446Uart4_lbdie;
		stm32446.uart4.cr2.lbdl = STM32446Uart4_lbdl;
		stm32446.uart4.cr2.add = STM32446Uart4_add;
		// CR3
		stm32446.uart4.cr3.onebit = STM32446Uart4_onebit;
		stm32446.uart4.cr3.ctsie = STM32446Uart4_ctsie;
		stm32446.uart4.cr3.ctse = STM32446Uart4_ctse;
		stm32446.uart4.cr3.rtse = STM32446Uart4_rtse;
		stm32446.uart4.cr3.dmat = STM32446Uart4_dmat;
		stm32446.uart4.cr3.dmar = STM32446Uart4_dmar;
		stm32446.uart4.cr3.scen = STM32446Uart4_scen;
		stm32446.uart4.cr3.nack = STM32446Uart4_nack;
		stm32446.uart4.cr3.hdsel = STM32446Uart4_hdsel;
		stm32446.uart4.cr3.irlp = STM32446Uart4_irlp;
		stm32446.uart4.cr3.iren = STM32446Uart4_iren;
		stm32446.uart4.cr3.eie = STM32446Uart4_eie;
		// GTPR
		stm32446.uart4.gtpr.gt = STM32446Uart4_gt;
		stm32446.uart4.gtpr.psc = STM32446Uart4_psc;
		// Other
		stm32446.uart4.clock = STM32446Uart4Clock;
		stm32446.uart4.parameter = STM32446Uart4Parameter;
		stm32446.uart4.transmit = STM32446Uart4Transmit;
		stm32446.uart4.receive = STM32446Uart4Receive;
		stm32446.uart4.stop = STM32446Uart4Stop;

	#endif

	// UART -> UART5
	stm32446.uart5.reg = UART5;
	#if defined(_STM32446USART_H_)
		/*** UART5 Bit Mapping Link ***/
		// SR
		stm32446.uart5.sr.cts = STM32446Uart5_cts;
		stm32446.uart5.sr.clear_cts = STM32446Uart5_clear_cts;
		stm32446.uart5.sr.lbd = STM32446Uart5_lbd;
		stm32446.uart5.sr.clear_lbd = STM32446Uart5_clear_lbd;
		stm32446.uart5.sr.txe = STM32446Uart5_txe;
		stm32446.uart5.sr.tc = STM32446Uart5_tc;
		stm32446.uart5.sr.clear_tc = STM32446Uart5_clear_tc;
		stm32446.uart5.sr.rxne = STM32446Uart5_rxne;
		stm32446.uart5.sr.clear_rxne = STM32446Uart5_clear_rxne;
		stm32446.uart5.sr.idle = STM32446Uart5_idle;
		stm32446.uart5.sr.ore = STM32446Uart5_ore;
		stm32446.uart5.sr.nf = STM32446Uart5_nf;
		stm32446.uart5.sr.fe = STM32446Uart5_fe;
		stm32446.uart5.sr.pe = STM32446Uart5_pe;
		// DR
		stm32446.uart5.dr = STM32446Uart5_dr;
		stm32446.uart5.get_dr = STM32446Uart5_get_dr;
		// BRR
		stm32446.uart5.brr.div_mantissa = STM32446Uart5_div_mantissa;
		stm32446.uart5.brr.div_fraction = STM32446Uart5_div_fraction;
		// CR1
		stm32446.uart5.cr1.over8 = STM32446Uart5_over8;
		stm32446.uart5.cr1.ue = STM32446Uart5_ue;
		stm32446.uart5.cr1.m = STM32446Uart5_m;
		stm32446.uart5.cr1.wake = STM32446Uart5_wake;
		stm32446.uart5.cr1.pce = STM32446Uart5_pce;
		stm32446.uart5.cr1.ps = STM32446Uart5_ps;
		stm32446.uart5.cr1.peie = STM32446Uart5_peie;
		stm32446.uart5.cr1.txeie = STM32446Uart5_txeie;
		stm32446.uart5.cr1.tcie = STM32446Uart5_tcie;
		stm32446.uart5.cr1.rxneie = STM32446Uart5_rxneie;
		stm32446.uart5.cr1.idleie = STM32446Uart5_idleie;
		stm32446.uart5.cr1.te = STM32446Uart5_te;
		stm32446.uart5.cr1.re = STM32446Uart5_re;
		stm32446.uart5.cr1.rwu = STM32446Uart5_rwu;
		stm32446.uart5.cr1.sbk = STM32446Uart5_sbk;
		// CR2
		stm32446.uart5.cr2.linen = STM32446Uart5_linen;
		stm32446.uart5.cr2.stop = STM32446Uart5_stop;
		stm32446.uart5.cr2.clken = STM32446Uart5_clken;
		stm32446.uart5.cr2.cpol = STM32446Uart5_cpol;
		stm32446.uart5.cr2.cpha = STM32446Uart5_cpha;
		stm32446.uart5.cr2.lbcl = STM32446Uart5_lbcl;
		stm32446.uart5.cr2.lbdie = STM32446Uart5_lbdie;
		stm32446.uart5.cr2.lbdl = STM32446Uart5_lbdl;
		stm32446.uart5.cr2.add = STM32446Uart5_add;
		// CR3
		stm32446.uart5.cr3.onebit = STM32446Uart5_onebit;
		stm32446.uart5.cr3.ctsie = STM32446Uart5_ctsie;
		stm32446.uart5.cr3.ctse = STM32446Uart5_ctse;
		stm32446.uart5.cr3.rtse = STM32446Uart5_rtse;
		stm32446.uart5.cr3.dmat = STM32446Uart5_dmat;
		stm32446.uart5.cr3.dmar = STM32446Uart5_dmar;
		stm32446.uart5.cr3.scen = STM32446Uart5_scen;
		stm32446.uart5.cr3.nack = STM32446Uart5_nack;
		stm32446.uart5.cr3.hdsel = STM32446Uart5_hdsel;
		stm32446.uart5.cr3.irlp = STM32446Uart5_irlp;
		stm32446.uart5.cr3.iren = STM32446Uart5_iren;
		stm32446.uart5.cr3.eie = STM32446Uart5_eie;
		// GTPR
		stm32446.uart5.gtpr.gt = STM32446Uart5_gt;
		stm32446.uart5.gtpr.psc = STM32446Uart5_psc;
		// Other
		stm32446.uart5.clock = STM32446Uart5Clock;
		stm32446.uart5.parameter = STM32446Uart5Parameter;
		stm32446.uart5.transmit = STM32446Uart5Transmit;
		stm32446.uart5.receive = STM32446Uart5Receive;
		stm32446.uart5.stop = STM32446Uart5Stop;

	#endif

	// USART -> USART6
	stm32446.usart6.reg = USART6;
	#if defined(_STM32446USART_H_)
		/*** USART6 Bit Mapping Link ***/
		// SR
		stm32446.usart6.sr.cts = STM32446Usart6_cts;
		stm32446.usart6.sr.clear_cts = STM32446Usart6_clear_cts;
		stm32446.usart6.sr.lbd = STM32446Usart6_lbd;
		stm32446.usart6.sr.clear_lbd = STM32446Usart6_clear_lbd;
		stm32446.usart6.sr.txe = STM32446Usart6_txe;
		stm32446.usart6.sr.tc = STM32446Usart6_tc;
		stm32446.usart6.sr.clear_tc = STM32446Usart6_clear_tc;
		stm32446.usart6.sr.rxne = STM32446Usart6_rxne;
		stm32446.usart6.sr.clear_rxne = STM32446Usart6_clear_rxne;
		stm32446.usart6.sr.idle = STM32446Usart6_idle;
		stm32446.usart6.sr.ore = STM32446Usart6_ore;
		stm32446.usart6.sr.nf = STM32446Usart6_nf;
		stm32446.usart6.sr.fe = STM32446Usart6_fe;
		stm32446.usart6.sr.pe = STM32446Usart6_pe;
		// DR
		stm32446.usart6.dr = STM32446Usart6_dr;
		stm32446.usart6.get_dr = STM32446Usart6_get_dr;
		// BRR
		stm32446.usart6.brr.div_mantissa = STM32446Usart6_div_mantissa;
		stm32446.usart6.brr.div_fraction = STM32446Usart6_div_fraction;
		// CR1
		stm32446.usart6.cr1.over8 = STM32446Usart6_over8;
		stm32446.usart6.cr1.ue = STM32446Usart6_ue;
		stm32446.usart6.cr1.m = STM32446Usart6_m;
		stm32446.usart6.cr1.wake = STM32446Usart6_wake;
		stm32446.usart6.cr1.pce = STM32446Usart6_pce;
		stm32446.usart6.cr1.ps = STM32446Usart6_ps;
		stm32446.usart6.cr1.peie = STM32446Usart6_peie;
		stm32446.usart6.cr1.txeie = STM32446Usart6_txeie;
		stm32446.usart6.cr1.tcie = STM32446Usart6_tcie;
		stm32446.usart6.cr1.rxneie = STM32446Usart6_rxneie;
		stm32446.usart6.cr1.idleie = STM32446Usart6_idleie;
		stm32446.usart6.cr1.te = STM32446Usart6_te;
		stm32446.usart6.cr1.re = STM32446Usart6_re;
		stm32446.usart6.cr1.rwu = STM32446Usart6_rwu;
		stm32446.usart6.cr1.sbk = STM32446Usart6_sbk;
		// CR2
		stm32446.usart6.cr2.linen = STM32446Usart6_linen;
		stm32446.usart6.cr2.stop = STM32446Usart6_stop;
		stm32446.usart6.cr2.clken = STM32446Usart6_clken;
		stm32446.usart6.cr2.cpol = STM32446Usart6_cpol;
		stm32446.usart6.cr2.cpha = STM32446Usart6_cpha;
		stm32446.usart6.cr2.lbcl = STM32446Usart6_lbcl;
		stm32446.usart6.cr2.lbdie = STM32446Usart6_lbdie;
		stm32446.usart6.cr2.lbdl = STM32446Usart6_lbdl;
		stm32446.usart6.cr2.add = STM32446Usart6_add;
		// CR3
		stm32446.usart6.cr3.onebit = STM32446Usart6_onebit;
		stm32446.usart6.cr3.ctsie = STM32446Usart6_ctsie;
		stm32446.usart6.cr3.ctse = STM32446Usart6_ctse;
		stm32446.usart6.cr3.rtse = STM32446Usart6_rtse;
		stm32446.usart6.cr3.dmat = STM32446Usart6_dmat;
		stm32446.usart6.cr3.dmar = STM32446Usart6_dmar;
		stm32446.usart6.cr3.scen = STM32446Usart6_scen;
		stm32446.usart6.cr3.nack = STM32446Usart6_nack;
		stm32446.usart6.cr3.hdsel = STM32446Usart6_hdsel;
		stm32446.usart6.cr3.irlp = STM32446Usart6_irlp;
		stm32446.usart6.cr3.iren = STM32446Usart6_iren;
		stm32446.usart6.cr3.eie = STM32446Usart6_eie;
		// GTPR
		stm32446.usart6.gtpr.gt = STM32446Usart6_gt;
		stm32446.usart6.gtpr.psc = STM32446Usart6_psc;
		// Other
		stm32446.usart6.clock = STM32446Usart6Clock;
		stm32446.usart6.parameter = STM32446Usart6Parameter;
		stm32446.usart6.transmit = STM32446Usart6Transmit;
		stm32446.usart6.receive = STM32446Usart6Receive;
		stm32446.usart6.stop = STM32446Usart6Stop;

	#endif

	// QUERY
	stm32446.query.ClockSource = STM32446_getclocksource;
	stm32446.query.PllSource = STM32446_pllsource;
	stm32446.query.CLOCK_prescaler.AHB = STM32446_gethpre;
	stm32446.query.CLOCK_prescaler.APB1 = STM32446_gethppre1;
	stm32446.query.CLOCK_prescaler.APB2 = STM32446_gethppre2;
	stm32446.query.CLOCK_prescaler.RTCclk = STM32446_getrtcpre;
	stm32446.query.CLOCK_prescaler.MCO1 = STM32446_gethmco1pre;
	stm32446.query.CLOCK_prescaler.MCO2 = STM32446_gethmco2pre;
	stm32446.query.PLL_parameter.M = STM32446_getpllm;
	stm32446.query.PLL_parameter.N = STM32446_getplln;
	stm32446.query.PLL_parameter.P = STM32446_getpllp;
	stm32446.query.PLL_parameter.Q = STM32446_getpllq;
	stm32446.query.PLL_parameter.R = STM32446_getpllr;
	stm32446.query.SystemClock = STM32446_getsysclk;

	// FUNC
	stm32446.func.bcd2dec = STM32446bcd2dec;
	stm32446.func.dec2bcd = STM32446dec2bcd;
	stm32446.func.triggerA = STM32446triggerA;
	stm32446.func.triggerB = STM32446triggerB;
	stm32446.func.ReadHLByte = STM32ReadHLByte;
	stm32446.func.ReadLHByte = STM32ReadLHByte;
	stm32446.func.WriteHLByte = STM32WriteHLByte;
	stm32446.func.WriteLHByte = STM32WriteLHByte;
	stm32446.func.SwapByte = STM32SwapByte;
	stm32446.func.ftoa = STM32446FUNCftoa;
	stm32446.func.print = STM32446FUNCprint;
	stm32446.func.regsetbits = STM32446RegSetBits;
	stm32446.func.regresetbits = STM32446RegResetBits;
	stm32446.func.vecsetup = STM32446VecSetup;
	stm32446.func.readreg = STM32446_readreg;
	stm32446.func.writereg = STM32446_writereg;
	stm32446.func.setreg = STM32446_setreg;
	stm32446.func.setbit = STM32446_setbit;
	stm32446.func.getsetbit = STM32446_getsetbit;
	
	SystickInic(); // Polling delay source.

	return stm32446;
}

/*** Query Procedure & Function Definition ***/
uint32_t STM32446_getclocksource(void)
{
	uint32_t reg = RCC->CR;
	uint32_t source;
	if(reg & (1 << 1)){source = HSI_RC;}else if(reg & (1 << 17)){source = HSE_OSC;}

	return source;
}

uint32_t STM32446_pllsource(void)
{
	uint32_t reg = RCC->CFGR;
	uint32_t source;

	if(reg & (1 << 22)) source = HSE_OSC; else source = HSI_RC;

	return source;
}

uint16_t STM32446_gethpre(void)
{
	uint32_t value = STM32446_readreg(RCC->CFGR, 4, 4);

	switch(value)
	{
		case 0b1000:
			value = 2;
		break;
		case 0b1001:
			value = 4;
		break;
		case 0b1010:
			value = 8;
		break;
		case 0b1011:
			value = 16;
		break;
		case 0b1100:
			value = 64;
		break;
		case 0b1101:
			value = 128;
		break;
		case 0b1110:
			value = 256;
		break;
		case 0b1111:
			value = 512;
		break;
		default:
			value = 1;
		break;
	}
	return value;
}

uint8_t STM32446_gethppre1(void)
{
	uint32_t value = STM32446_readreg(RCC->CFGR, 3, 10);

	switch(value)
	{
		case 0b100:
			value = 2;
		break;
		case 0b101:
			value = 4;
		break;
		case 0b110:
			value = 8;
		break;
		case 0b111:
			value = 16;
		break;
		default:
			value = 1;
		break;
	}
	return value;
}

uint8_t STM32446_gethppre2(void)
{
	uint32_t value = STM32446_readreg(RCC->CFGR, 3, 13);

	switch(value)
	{
		case 0b100:
			value = 2;
		break;
		case 0b101:
			value = 4;
		break;
		case 0b110:
			value = 8;
		break;
		case 0b111:
			value = 16;
		break;
		default:
			value = 1;
		break;
	}
	return value;
}

uint8_t STM32446_getrtcpre(void)
{
	return STM32446_readreg(RCC->CFGR, 5, 16);
}

uint8_t STM32446_gethmco1pre(void)
{
	uint32_t value = STM32446_readreg(RCC->CFGR, 3, 24);

	switch(value)
	{
		case 0b100:
			value = 2;
		break;
		case 0b101:
			value = 3;
		break;
		case 0b110:
			value = 4;
		break;
		case 0b111:
			value = 5;
		break;
		default:
			value = 1;
		break;
	}
	return value;
}

uint8_t STM32446_gethmco2pre(void)
{
	uint32_t value = STM32446_readreg(RCC->CFGR, 3, 27);

	switch(value)
	{
		case 0b100:
			value = 2;
		break;
		case 0b101:
			value = 3;
		break;
		case 0b110:
			value = 4;
		break;
		case 0b111:
			value = 5;
		break;
		default:
			value = 1;
		break;
		}
	return value;
}

uint8_t STM32446_getpllm(void)
{
	return STM32446_readreg(RCC->PLLCFGR, 6, 0);
}

uint16_t STM32446_getplln(void)
{
	return STM32446_readreg(RCC->PLLCFGR, 9, 6);
}

uint8_t STM32446_getpllp(void)
{
	uint32_t value = STM32446_readreg(RCC->PLLCFGR, 2, 16);

	switch(value)
	{
		case 0b00:
			value = 2;
		break;
		case 0b01:
			value = 4;
		break;
		case 0b10:
			value = 6;
		break;
		case 0b11:
			value = 8;
		break;
		default:
		break;
	}
	return value;
}

uint8_t STM32446_getpllq(void)
{
	return STM32446_readreg(RCC->PLLCFGR, 4, 24);
}

uint8_t STM32446_getpllr(void)
{
	return STM32446_readreg(RCC->PLLCFGR, 3, 28);
}

uint32_t STM32446_getsysclk(void)
{
	uint32_t value = STM32446_readreg(RCC->CFGR, 2, 2);

	switch(value) // SWS[2]: System clock switch status
	{
		case 1: // 01: HSE oscillator used as the system clock
			value = HSE_OSC;
		break;
		case 2: // 10: PLL used as the system clock
			value = ( STM32446_getclocksource() / STM32446_getpllm() ) * ( STM32446_getplln() / STM32446_getpllp() );
		break;
		case 3: // 11: PLL_R used as the system clock
			value = ( STM32446_getclocksource() / STM32446_getpllm() ) * ( STM32446_getplln() / STM32446_getpllr() );
		break;
		default: // 00: HSI oscillator used as the system clock
			value = HSI_RC;
		break;
	}
	return value;
}

/*** File Procedure & Function Definition ***/
uint32_t STM32446_readreg(uint32_t reg, uint32_t size_block, uint32_t bit)
{
	if(bit > 31){ bit = 0;} if(size_block > 32){ size_block = 32;}
	uint32_t value = reg;
	uint32_t mask = (unsigned int)((1 << size_block) - 1);
	value &= (mask << bit);
	value = (value >> bit);
	return value;
}

void STM32446_writereg(volatile uint32_t* reg, uint32_t size_block, uint32_t bit, uint32_t data)
{
	if(bit > 31){ bit = 0;} if(size_block > 32){ size_block = 32;}
	uint32_t value = data;
	uint32_t mask = (unsigned int)((1 << size_block) - 1);
	value &= mask;
	value = (value << bit);
	*reg = value;
}

void STM32446_setreg(volatile uint32_t* reg, uint32_t size_block, uint32_t bit, uint32_t data)
{
	if(bit > 31){ bit = 0;} if(size_block > 32){ size_block = 32;}
	uint32_t value = data;
	uint32_t mask = (unsigned int)((1 << size_block) - 1);
	value &= mask;
	*reg &= ~(mask << bit);
	*reg |= (value << bit);
}

void STM32446_setbit(volatile uint32_t* reg, uint32_t size_block, uint32_t bit, uint32_t data)
{
	uint32_t n = 0;
	if(bit > 31){ n = bit/32; bit = bit - (n * 32); } if(size_block > 32){ size_block = 32;}
	uint32_t value = data;
	uint32_t mask = (unsigned int)((1 << size_block) - 1);
	value &= mask;
	*(reg + n ) &= ~(mask << bit);
	*(reg + n ) |= (value << bit);
}

uint32_t STM32446_getsetbit(volatile uint32_t* reg, uint32_t size_block, uint32_t bit)
{
	uint32_t n = 0;
	if(bit > 31){ n = bit/32; bit = bit - (n * 32); } if(size_block > 32){ size_block = 32;}
	uint32_t value = *(reg + n );
	uint32_t mask = (unsigned int)((1 << size_block) - 1);
	value &= (mask << bit);
	value = (value >> bit);
	return value;
}

/*** MISCELLANEOUS ***/
void STM32446RegSetBits( unsigned int* reg, int n_bits, ... )
{
	uint8_t i;
	if(n_bits > 0 && n_bits < 33){ // Filter input
		va_list list;
		va_start(list, n_bits);
		for(i = 0; i < n_bits; i++){
			*reg |= (unsigned int)(1 << va_arg(list, int));
		}
		va_end(list);
	}
}

void STM32446RegResetBits( unsigned int* reg, int n_bits, ... )
{
	uint8_t i;
	if(n_bits > 0 && n_bits < 33){ // Filter input
		va_list list;
		va_start(list, n_bits);
		for(i = 0; i < n_bits; i++){
			*reg &= (unsigned int)~((1 << va_arg(list, int)) << 16);
		}
		va_end(list);
	}
}

void STM32446VecSetup( volatile uint32_t vec[], const unsigned int size_block, unsigned int data, unsigned int block_n )
{
	const unsigned int n_bits = sizeof(data) * 8;
	const unsigned int mask = (unsigned int) (pow(2, size_block) - 1);
	unsigned int index = (block_n * size_block) / n_bits;
	data &= mask;
	vec[index] &= ~( mask << ((block_n * size_block) - (index * n_bits)) );
	vec[index] |= ( data << ((block_n * size_block) - (index * n_bits)) );
}

// Convert Binary Coded Decimal (BCD) to Decimal
char STM32446bcd2dec(char num)
{
	return ((num / 16 * 10) + (num % 16));
}

// Convert Decimal to Binary Coded Decimal (BCD)
char STM32446dec2bcd(char num)
{
	return ((num / 10 * 16) + (num % 10));
}

// triggerA
uint32_t STM32446triggerA(uint32_t hllh_io, uint8_t pin, uint32_t counter)
{
	mem[3] = 0;
	
	switch(mem[0]){
		case 0:
			if(hllh_io & (1 << pin)){
				mem[1] = counter;
				mem[0] = 1;
			}
		break;
		case 1:
			if(hllh_io & (1 << pin)){
				mem[2] = counter;
				if((mem[2] + 1) > mem[1]){
					mem[3] = mem[2] - mem[1];
				}else{
					mem[3] = ((uint32_t) ~0 - mem[1]) + mem[2];
				}
				mem[0] = 0;
			}
		break;
		default:
		break;
	}
	return mem[3];
}

// triggerB
uint32_t STM32446triggerB(uint32_t hl_io, uint32_t lh_io, uint8_t pin, uint32_t counter)
{
	nen[3] = 0;
	
	switch(nen[0]){ // Start value
		case 0:
			nen[1] = counter;
			if(hl_io & (1 << pin))
				nen[0] = 1;
		break;
		case 1:
			nen[2] = counter;
			if(nen[2] == nen[1])
				nen[2] += sizeof(nen[0]) * 8;
			if(lh_io & (1 << pin)){
				nen[3] = nen[2] - nen[1];
				nen[0] = 0;
			}
		break;
		default:
		break;
	}
	return nen[3];
}

uint16_t STM32ReadHLByte(STM32HighLowByte reg)
{
	return (uint16_t)(reg.H << 8) | reg.L;
}

uint16_t STM32ReadLHByte(STM32HighLowByte reg)
{
	return (uint16_t)(reg.L << 8) | reg.H;
}

STM32HighLowByte STM32WriteHLByte(uint16_t val)
{
	STM32HighLowByte reg; reg.H = (uint8_t)(val >> 8); reg.L = (uint8_t)val;
	return reg;
}

STM32HighLowByte STM32WriteLHByte(uint16_t val)
{
	STM32HighLowByte reg; reg.L = (uint8_t)(val >> 8); reg.H = (uint8_t)val; 
	return reg;
}

uint16_t STM32SwapByte(uint16_t num)
{
	uint16_t tp;
	tp = (uint16_t)(num << 8);
	return (num >> 8) | tp;
}

// ftoa
char* STM32446FUNCftoa(double num, char* res, uint8_t afterpoint)
{
	uint32_t ipart;
	double n, fpart;
	uint8_t k = 0;
	int8_t sign;
	if (num < 0){
		n = -num; sign = -1;
	}else{
		n = num; sign = 1;
	}
	ipart = (uint32_t) n; fpart = n - (double)ipart;
	k = STM32446FUNCintinvstr((int)ipart, res, 1);
	if (sign < 0) res[k++] = '-'; else res[k++] = ' ';
	res[k] = '\0';
	STM32446Reverse(res);
	if (afterpoint > 0 && afterpoint < (8 + 1)){
		res[k++] = '.';
		STM32446FUNCintinvstr( (int32_t)(fpart * pow(10, afterpoint)), (res + k), afterpoint );
		STM32446Reverse(res + k);
	}else{
		res[k++] = '.';
		STM32446FUNCintinvstr( (int32_t)(fpart * pow(10, 2)), (res + k), 2 );
		STM32446Reverse(res + k);
	}
	return res;
}

// print
char* STM32446FUNCprint( char* str, uint8_t size_str, const char* format, ... )
{
	va_list aptr;
	int ret;

	va_start(aptr, format);
	ret = vsnprintf( str, size_str, (const char*) format, aptr );
	//ret = vsnprintf( ptr, size_str, format, aptr );
	va_end(aptr);

	if(ret < 0){
		return NULL;
		//str[0]='/0';str[1]='/0';str[2]='/0';str[3]='/0';
	}else
		return str;
}

// Function to count the number of characters in a string
int STM32446StringLength (const char string[])
{
	int count;
	for (count = 0; string[count] != '\0'; count++ ) ;
	return count;
}

// reverse: reverse string s in place
void STM32446Reverse(char s[])
{
	char c;
	int i, j;
	for ( i = 0, j = STM32446StringLength(s) - 1; i < j ; i++, j-- ){
		c = s[i];
		s[i] = s[j];
		s[j] = c;
	}
}

// intinvstr
uint8_t STM32446FUNCintinvstr(int32_t num, char* res, uint8_t n_digit)
{
	uint8_t k = 0;
	for(res[k++] = (char)((num % 10) + '0'); (num /= 10) > 0 ; res[k++] = (char)((num % 10) + '0'));
	for( ; k < n_digit ; res[k++] = '0');
	res[k] = '\0';
	return k;
}

/************************ SYSTICK ************************/
void SystickInic(void)
{
	SysTick->LOAD = (uint32_t)( stm32446.query.SystemClock() - 1);
	SysTick->VAL = 0UL;
	SysTick->CTRL |= ((1 << 1) | (1 << 2));
}

void STM32446delay_ms(uint32_t ms)
{
	SysTick->LOAD = (uint32_t)(( stm32446.query.SystemClock() / 1000 ) - 1);
	// Enable the SysTick timer
	SysTick->CTRL |= (1 << 0);
	// Wait for a specified number of milliseconds
	DelayCounter = 0;
	while (DelayCounter < ms);
	// Disable the SysTick timer
	SysTick->CTRL &= (uint32_t) ~(1 << 0);
}

void STM32446delay_10us(uint32_t ten_us)
{
	SysTick->LOAD = (uint32_t)(( stm32446.query.SystemClock() / 100000) - 1);
	// Enable the SysTick timer
	SysTick->CTRL |= (1 << 0);
	// Wait for a specified number of milliseconds
	DelayCounter = 0;
	while (DelayCounter < ten_us);
	// Disable the SysTick timer
	SysTick->CTRL &= (uint32_t) ~(1 << 0);
}

void STM32446delay_us(uint32_t us)
{
	SysTick->LOAD = (uint32_t)(( stm32446.query.SystemClock() / 1000000) - 1);
	// Enable the SysTick timer
	SysTick->CTRL |= (1 << 0);
	// Wait for a specified number of milliseconds
	DelayCounter = 0;
	while (DelayCounter < us);
	// Disable the SysTick timer
	SysTick->CTRL &= (uint32_t) ~(1 << 0);
}

/*** File Interrupt Definition ***/
void SysTick_Handler(void)
{ // count down to zero systick interrupt and reload.
	DelayCounter++;
}

/***EOF***/

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


