/******************************************************************************
	STM32 446 TIM
Author: Sergio Santos 
	<sergio.salazar.santos@gmail.com>
License: GNU General Public License
Hardware: STM32-446
Date: 19062023
Comment:
	
*******************************************************************************/
/*** File Library ***/
#include "stm32446mapping.h"
#include "stm32446tim.h"

/*** File Procedure & Function Header ***/
uint32_t tim_readreg(uint32_t reg, uint32_t size_block, uint32_t bit);
void tim_writereg(volatile uint32_t* reg, uint32_t size_block, uint32_t bit, uint32_t data);
void tim_setreg(volatile uint32_t* reg, uint32_t size_block, uint32_t bit, uint32_t data);
void tim_setbit(volatile uint32_t* reg, uint32_t size_block, uint32_t bit, uint32_t data);
uint32_t tim_getsetbit(volatile uint32_t* reg, uint32_t size_block, uint32_t bit);
STM32446TIM9_CR1 stm32446_tim9_cr1_inic(void);
STM32446TIM9_SMCR stm32446_tim9_smcr_inic(void);
STM32446TIM9_DIER stm32446_tim9_dier_inic(void);
STM32446TIM9_SR stm32446_tim9_sr_inic(void);
STM32446TIM9_EGR stm32446_tim9_egr_inic(void);
STM32446TIM9_CCMR1 stm32446_tim9_ccmr1_inic(void);
STM32446TIM9_CCER stm32446_tim9_ccer_inic(void);

/*** TIMER Procedure & Function Definition ***/
/*** TIM9 ***/
void STM32446Tim9Clock(void)
{
	RCC->APB2ENR |= (1 << 16); //timer 9 clock enabled
}
/*** TIM9 Bit Mapping ***/
// CR1
uint8_t STM32446Tim9_get_ckd(void)
{
	return tim_readreg(TIM9->CR1, 2, 8);
}

void STM32446Tim9_set_apre(uint8_t bool)
{
	tim_setreg(&TIM9->CR1, 1, 7, bool);
}

void STM32446Tim9_set_opm(uint8_t bool)
{
	tim_setreg(&TIM9->CR1, 1, 3, bool);
}

void STM32446Tim9_set_urs(uint8_t bool)
{
	tim_setreg(&TIM9->CR1, 1, 2, bool);
}

void STM32446Tim9_set_udis(uint8_t bool)
{
	tim_setreg(&TIM9->CR1, 1, 1, bool);
}

void STM32446Tim9_cen(uint8_t bool)
{
	tim_setreg(&TIM9->CR1, 1, 0, bool);
}

// SMCR
void STM32446Tim9_msm(uint8_t bool)
{
	tim_setreg(&TIM9->SMCR, 1, 7, bool);
}

void STM32446Tim9_ts(uint8_t ts)
{
	tim_setreg(&TIM9->SMCR, 3, 4, ts);
}

void STM32446Tim9_sms(uint8_t sms)
{
	tim_setreg(&TIM9->SMCR, 3, 0, sms);
}

// DIER
void STM32446Tim9_tie(uint8_t bool)
{
	tim_setreg(&TIM9->DIER, 1, 6, bool);
}

void STM32446Tim9_cc2ie(uint8_t bool)
{
	tim_setreg(&TIM9->DIER, 1, 2, bool);
}

void STM32446Tim9_cc1ie(uint8_t bool)
{
	tim_setreg(&TIM9->DIER, 1, 1, bool);
}

void STM32446Tim9_uie(uint8_t bool)
{
	tim_setreg(&TIM9->DIER, 1, 0, bool);
}

// SR
uint8_t STM32446Tim9_cc2of(void)
{
	return tim_readreg(TIM9->SR, 1, 10);
}
void STM32446Tim9_clear_cc2of(void)
{
	tim_setreg(&TIM9->SR, 1, 10, 0);
}

uint8_t STM32446Tim9_cc1of(void)
{
	return tim_readreg(TIM9->SR, 1, 9);
}
void STM32446Tim9_clear_cc1of(void)
{
	tim_setreg(&TIM9->SR, 1, 9, 0);
}

uint8_t STM32446Tim9_tif(void)
{
	return tim_readreg(TIM9->SR, 1, 6);
}
void STM32446Tim9_clear_tif(void)
{
	tim_setreg(&TIM9->SR, 1, 6, 0);
}

uint8_t STM32446Tim9_cc2if(void)
{
	return tim_readreg(TIM9->SR, 1, 2);
}
void STM32446Tim9_clear_cc2if(void)
{
	tim_setreg(&TIM9->SR, 1, 2, 0);
}

uint8_t STM32446Tim9_cc1if(void)
{
	return tim_readreg(TIM9->SR, 1, 1);
}
void STM32446Tim9_clear_cc1if(void)
{
	tim_setreg(&TIM9->SR, 1, 1, 0);
}

uint8_t STM32446Tim9_uif(void)
{
	return tim_readreg(TIM9->SR, 1, 0);
}
void STM32446Tim9_clear_uif(void)
{
	tim_setreg(&TIM9->SR, 1, 0, 0);
}

// EGR
void STM32446Tim9_tg(void)
{
	tim_setreg(&TIM9->EGR, 1, 6, 1);
}

void STM32446Tim9_cc2g(void)
{
	tim_setreg(&TIM9->EGR, 1, 2, 1);
}

void STM32446Tim9_cc1g(void)
{
	tim_setreg(&TIM9->EGR, 1, 1, 1);
}

void STM32446Tim9_ug(void)
{
	tim_setreg(&TIM9->EGR, 1, 0, 1);
}

// CCMR1
void STM32446Tim9_oc2m(uint8_t oc2m)
{
	tim_setreg(&TIM9->CCMR1, 3, 12, oc2m);
}
void STM32446Tim9_ic2f(uint8_t ic2f)
{
	tim_setreg(&TIM9->CCMR1, 4, 12, ic2f);
}

void STM32446Tim9_oc2pe(uint8_t bool)
{
	tim_setreg(&TIM9->CCMR1, 1, 11, bool);
}
void STM32446Tim9_oc2fe(uint8_t bool)
{
	tim_setreg(&TIM9->CCMR1, 1, 10, bool);
}
void STM32446Tim9_ic2psc(uint8_t ic2psc)
{
	tim_setreg(&TIM9->CCMR1, 2, 10, ic2psc);
}

void STM32446Tim9_cc2s(uint8_t cc2s)
{
	tim_setreg(&TIM9->CCMR1, 2, 8, cc2s);
}

void STM32446Tim9_oc1m(uint8_t oc1m)
{
	tim_setreg(&TIM9->CCMR1, 3, 4, oc1m);
}
void STM32446Tim9_ic1f(uint8_t ic1f)
{
	tim_setreg(&TIM9->CCMR1, 4, 4, ic1f);
}

void STM32446Tim9_oc1pe(uint8_t bool)
{
	tim_setreg(&TIM9->CCMR1, 1, 3, bool);
}
void STM32446Tim9_oc1fe(uint8_t bool)
{
	tim_setreg(&TIM9->CCMR1, 1, 2, bool);
}
void STM32446Tim9_ic1psc(uint8_t ic1psc)
{
	tim_setreg(&TIM9->CCMR1, 2, 2, ic1psc);
}

void STM32446Tim9_cc1s(uint8_t cc1s)
{
	tim_setreg(&TIM9->CCMR1, 2, 0, cc1s);
}

// CCER
void STM32446Tim9_cc2np(uint8_t bool)
{
	tim_setreg(&TIM9->CCER, 1, 7, bool);
}

void STM32446Tim9_cc2p(uint8_t bool)
{
	tim_setreg(&TIM9->CCER, 1, 5, bool);
}

void STM32446Tim9_cc2e(uint8_t bool)
{
	tim_setreg(&TIM9->CCER, 1, 4, bool);
}

void STM32446Tim9_cc1np(uint8_t bool)
{
	tim_setreg(&TIM9->CCER, 1, 3, bool);
}

void STM32446Tim9_cc1p(uint8_t bool)
{
	tim_setreg(&TIM9->CCER, 1, 1, bool);
}

void STM32446Tim9_cc1e(uint8_t bool)
{
	tim_setreg(&TIM9->CCER, 1, 0, bool);
}

// CNT
void STM32446Tim9_cnt(uint16_t value)
{
	TIM9->CNT = value;
}
uint16_t STM32446Tim9_get_cnt(void)
{
	return TIM9->CNT;
}

// ARR
void STM32446Tim9_arr(uint16_t value)
{
	TIM9->ARR = value;
}

// CCR1
void STM32446Tim9_ccr1(uint16_t value)
{
	TIM9->CCR1 = value;
}

// CCR2
void STM32446Tim9_ccr2(uint16_t value)
{
	TIM9->CCR2 = value;
}

// PSC
void STM32446Tim9_psc(uint16_t value)
{
	TIM9->PSC = value;
}

/*** TIM 10 ***/
// Future Implementation

/*** INIC Procedure & Function Definition ***/
STM32446TIM1obj tim1_inic(void)
{
	STM32446TIM1obj stm32446_tim1;
	stm32446_tim1.reg = TIM1;
	return stm32446_tim1;
}
STM32446TIM2obj tim2_inic(void)
{
	STM32446TIM2obj stm32446_tim2;
	stm32446_tim2.reg = TIM2;
	return stm32446_tim2;
}
STM32446TIM3obj tim3_inic(void)
{
	STM32446TIM3obj stm32446_tim3;
	stm32446_tim3.reg = TIM3;
	return stm32446_tim3;
}
STM32446TIM4obj tim4_inic(void)
{
	STM32446TIM4obj stm32446_tim4;
	stm32446_tim4.reg = TIM4;
	return stm32446_tim4;
}
STM32446TIM5obj tim5_inic(void)
{
	STM32446TIM5obj stm32446_tim5;
	stm32446_tim5.reg = TIM5;
	return stm32446_tim5;
}
STM32446TIM6obj tim6_inic(void)
{
	STM32446TIM6obj stm32446_tim6;
	stm32446_tim6.reg = TIM6;
	return stm32446_tim6;
}
STM32446TIM7obj tim7_inic(void)
{
	STM32446TIM7obj stm32446_tim7;
	stm32446_tim7.reg = TIM7;
	return stm32446_tim7;
}
STM32446TIM8obj tim8_inic(void)
{
	STM32446TIM8obj stm32446_tim8;
	stm32446_tim8.reg = TIM8;
	return stm32446_tim8;
}
/*** TIM9 Auxiliar ***/
STM32446TIM9_CR1 stm32446_tim9_cr1_inic(void)
{
	STM32446TIM9_CR1 stm32446_tim9_cr1;
	// CR1
	stm32446_tim9_cr1.get_ckd = STM32446Tim9_get_ckd;
	stm32446_tim9_cr1.apre = STM32446Tim9_set_apre;
	stm32446_tim9_cr1.opm = STM32446Tim9_set_opm;
	stm32446_tim9_cr1.urs = STM32446Tim9_set_urs;
	stm32446_tim9_cr1.udis = STM32446Tim9_set_udis;
	stm32446_tim9_cr1.cen = STM32446Tim9_cen;
	return stm32446_tim9_cr1;
}
STM32446TIM9_SMCR stm32446_tim9_smcr_inic(void)
{
	STM32446TIM9_SMCR stm32446_tim9_smcr;
	// SMCR
	stm32446_tim9_smcr.msm = STM32446Tim9_msm;
	stm32446_tim9_smcr.ts = STM32446Tim9_ts;
	stm32446_tim9_smcr.sms = STM32446Tim9_sms;
	return stm32446_tim9_smcr;
}
STM32446TIM9_DIER stm32446_tim9_dier_inic(void)
{
	STM32446TIM9_DIER stm32446_tim9_dier;
	// DIER
	stm32446_tim9_dier.tie = STM32446Tim9_tie;
	stm32446_tim9_dier.cc2ie = STM32446Tim9_cc2ie;
	stm32446_tim9_dier.cc1ie = STM32446Tim9_cc1ie;
	stm32446_tim9_dier.uie = STM32446Tim9_uie;
	return stm32446_tim9_dier;
}
STM32446TIM9_SR stm32446_tim9_sr_inic(void)
{
	STM32446TIM9_SR stm32446_tim9_sr;
	// SR
	stm32446_tim9_sr.cc2of = STM32446Tim9_cc2of;
	stm32446_tim9_sr.clear_cc2of = STM32446Tim9_clear_cc2of;
	stm32446_tim9_sr.cc1of = STM32446Tim9_cc1of;
	stm32446_tim9_sr.clear_cc1of = STM32446Tim9_clear_cc1of;
	stm32446_tim9_sr.tif = STM32446Tim9_tif;
	stm32446_tim9_sr.clear_tif = STM32446Tim9_clear_tif;
	stm32446_tim9_sr.cc2if = STM32446Tim9_cc2if;
	stm32446_tim9_sr.clear_cc2if = STM32446Tim9_clear_cc2if;
	stm32446_tim9_sr.cc1if = STM32446Tim9_cc1if;
	stm32446_tim9_sr.clear_cc1if = STM32446Tim9_clear_cc1if;
	stm32446_tim9_sr.uif = STM32446Tim9_uif;
	stm32446_tim9_sr.clear_uif = STM32446Tim9_clear_uif;
	return stm32446_tim9_sr;
}
STM32446TIM9_EGR stm32446_tim9_egr_inic(void)
{
	STM32446TIM9_EGR stm32446_tim9_egr;
	// EGR
	stm32446_tim9_egr.tg = STM32446Tim9_tg;
	stm32446_tim9_egr.cc2g = STM32446Tim9_cc2g;
	stm32446_tim9_egr.cc1g = STM32446Tim9_cc1g;
	stm32446_tim9_egr.ug = STM32446Tim9_ug;
	return stm32446_tim9_egr;
}
STM32446TIM9_CCMR1 stm32446_tim9_ccmr1_inic(void)
{
	STM32446TIM9_CCMR1 stm32446_tim9_ccmr1;
	// CCMR1
	stm32446_tim9_ccmr1.oc2m = STM32446Tim9_oc2m;
	stm32446_tim9_ccmr1.ic2f = STM32446Tim9_ic2f;
	stm32446_tim9_ccmr1.oc2pe = STM32446Tim9_oc2pe;
	stm32446_tim9_ccmr1.oc2fe = STM32446Tim9_oc2fe;
	stm32446_tim9_ccmr1.ic2psc = STM32446Tim9_ic2psc;
	stm32446_tim9_ccmr1.cc2s = STM32446Tim9_cc2s;
	stm32446_tim9_ccmr1.oc1m = STM32446Tim9_oc1m;
	stm32446_tim9_ccmr1.ic1f = STM32446Tim9_ic1f;
	stm32446_tim9_ccmr1.oc1pe = STM32446Tim9_oc1pe;
	stm32446_tim9_ccmr1.oc1fe = STM32446Tim9_oc1fe;
	stm32446_tim9_ccmr1.ic1psc = STM32446Tim9_ic1psc;
	stm32446_tim9_ccmr1.cc1s = STM32446Tim9_cc1s;
	return stm32446_tim9_ccmr1;
}
STM32446TIM9_CCER stm32446_tim9_ccer_inic(void)
{
	STM32446TIM9_CCER stm32446_tim9_ccer;
	// CCER
	stm32446_tim9_ccer.cc2np = STM32446Tim9_cc2np;
	stm32446_tim9_ccer.cc2p = STM32446Tim9_cc2p;
	stm32446_tim9_ccer.cc2e = STM32446Tim9_cc2e;
	stm32446_tim9_ccer.cc1np = STM32446Tim9_cc1np;
	stm32446_tim9_ccer.cc1p = STM32446Tim9_cc1p;
	stm32446_tim9_ccer.cc1e = STM32446Tim9_cc1e;
	return stm32446_tim9_ccer;
}
/*** TIM9 INIC Procedure & Function Definition***/
STM32446TIM9obj tim9_inic(void)
{
	STM32446TIM9obj stm32446_tim9;
	stm32446_tim9.reg = TIM9;
	// CLOCK
	stm32446_tim9.clock = STM32446Tim9Clock;
	/*** TIM9 Bit Mapping Link ***/
	stm32446_tim9.cr1 = stm32446_tim9_cr1_inic();
	stm32446_tim9.smcr = stm32446_tim9_smcr_inic();
	stm32446_tim9.dier = stm32446_tim9_dier_inic();
	stm32446_tim9.sr = stm32446_tim9_sr_inic();
	stm32446_tim9.egr = stm32446_tim9_egr_inic();
	stm32446_tim9.ccmr1 = stm32446_tim9_ccmr1_inic();
	stm32446_tim9.ccer = stm32446_tim9_ccer_inic();
	stm32446_tim9.cnt = STM32446Tim9_cnt;
	stm32446_tim9.get_cnt = STM32446Tim9_get_cnt;
	stm32446_tim9.arr = STM32446Tim9_arr;
	stm32446_tim9.ccr1 = STM32446Tim9_ccr1;
	stm32446_tim9.ccr2 = STM32446Tim9_ccr2;
	stm32446_tim9.psc = STM32446Tim9_psc;
	return stm32446_tim9;
}
STM32446TIM10obj tim10_inic(void)
{
	STM32446TIM10obj stm32446_tim10;
	stm32446_tim10.reg = TIM10;
	return stm32446_tim10;
}
STM32446TIM11obj tim11_inic(void)
{
	STM32446TIM11obj stm32446_tim11;
	stm32446_tim11.reg = TIM11;
	return stm32446_tim11;
}
STM32446TIM12obj tim12_inic(void)
{
	STM32446TIM12obj stm32446_tim12;
	stm32446_tim12.reg = TIM12;
	return stm32446_tim12;
}
STM32446TIM13obj tim13_inic(void)
{
	STM32446TIM13obj stm32446_tim13;
	stm32446_tim13.reg = TIM13;
	return stm32446_tim13;
}
STM32446TIM14obj tim14_inic(void)
{
	STM32446TIM14obj stm32446_tim14;
	stm32446_tim14.reg = TIM14;
	return stm32446_tim14;
}

/*** File Procedure & Function Definition***/
uint32_t tim_readreg(uint32_t reg, uint32_t size_block, uint32_t bit)
{
	if(bit > 31){ bit = 0;} if(size_block > 32){ size_block = 32;}
	uint32_t value = reg;
	uint32_t mask = (unsigned int)((1 << size_block) - 1);
	value &= (mask << bit);
	value = (value >> bit);
	return value;
}
void tim_writereg(volatile uint32_t* reg, uint32_t size_block, uint32_t bit, uint32_t data)
{
	if(bit > 31){ bit = 0;} if(size_block > 32){ size_block = 32;}
	uint32_t value = data;
	uint32_t mask = (unsigned int)((1 << size_block) - 1);
	value &= mask;
	value = (value << bit);
	*reg = value;
}
void tim_setreg(volatile uint32_t* reg, uint32_t size_block, uint32_t bit, uint32_t data)
{
	if(bit > 31){ bit = 0;} if(size_block > 32){ size_block = 32;}
	uint32_t value = data;
	uint32_t mask = (unsigned int)((1 << size_block) - 1);
	value &= mask;
	*reg &= ~(mask << bit);
	*reg |= (value << bit);
}
void tim_setbit(volatile uint32_t* reg, uint32_t size_block, uint32_t bit, uint32_t data)
{
	uint32_t n = 0;
	if(bit > 31){ n = bit/32; bit = bit - (n * 32); } if(size_block > 32){ size_block = 32;}
	uint32_t value = data;
	uint32_t mask = (unsigned int)((1 << size_block) - 1);
	value &= mask;
	*(reg + n ) &= ~(mask << bit);
	*(reg + n ) |= (value << bit);
}
uint32_t tim_getsetbit(volatile uint32_t* reg, uint32_t size_block, uint32_t bit)
{
	uint32_t n = 0;
	if(bit > 31){ n = bit/32; bit = bit - (n * 32); } if(size_block > 32){ size_block = 32;}
	uint32_t value = *(reg + n );
	uint32_t mask = (unsigned int)((1 << size_block) - 1);
	value &= (mask << bit);
	value = (value >> bit);
	return value;
}

/*** File Interrupt ***/
// void TIM1_BRK_TIM9_IRQHandler(void){ // receive interrupt flags }

/*** EOF ***/


