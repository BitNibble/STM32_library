/******************************************************************************
	STM32 446 TIM
Author: Sergio Santos 
	<sergio.salazar.santos@gmail.com>
License: GNU General Public License
Hardware: STM32-446
Date: 02062023
Comment:
	
*******************************************************************************/
/*** File Library ***/
#include <stm32446mapping.h>
#include "stm32446tim.h"

/*** File Procedure & Function Header ***/
uint32_t tim_getbit(uint32_t reg, uint32_t size_block, uint32_t bit);
void tim_setbit(volatile uint32_t* reg, uint32_t size_block, uint32_t bit, uint32_t data);
uint32_t tim_getsetbit(volatile uint32_t* reg, uint32_t size_block, uint32_t bit);

/*** TIMER Procedure & Function Definition ***/
/*** TIM9 ***/
void STM32446Tim9Clock(void)
{
	RCC->APB2ENR |= (1 << 16); //timer 9 clock enabled
}

void STM32446Tim9Inic(void)
{
	// Interrupt NVIC
	STM32446Tim9EnableInterrupt();
	//tim9.nvict1t9();

	// Frequency
	STM32446Tim9_arr(45535);
	//tim9.arr(45535);

	// Compare
	STM32446Tim9_ccr1(7530); // gives problems why ?
	//tim9.ccr1(7530);

	// prescaller
	STM32446Tim9_psc(20);
	//tim9.psc(20);

	// interrupt
	STM32446Tim9_cc1ie(1);
	//tim9.dier.cc1ie(1);
	//TIM9->DIER |= 3; //3 | (1 << 6);
	//TIM9->CCMR1 |= (3 << 2);
	//TIM9->CCMR1 |= (3 << 4);
	//TIM9->CCER |= 1;

	// Enable (Start/Stop)
	STM32446Tim9_set_apre(1);
	//tim9.cr1.apre(1);
	STM32446Tim9_cen(1);
	//tim9.cr1.cen(1);
}

// INTERRUPT
void STM32446Tim9EnableInterrupt(void)
{
	tim_setbit(NVIC->ISER,1,24,1); // enable interrupt tim 1 brk and tim 9 global (IRGn 24)
}

void STM32446Tim9DisableInterrupt(void)
{
	tim_setbit(NVIC->ICER,1,24,1); // disable interrupt tim 1 brk and tim 9 global (IRGn 24)
}

/*** TIM9 Bit Mapping ***/
// CR1
uint8_t STM32446Tim9_get_ckd(void)
{
	return tim_getbit(TIM9->CR1, 2, 8);
}

void STM32446Tim9_set_apre(uint8_t bool)
{
	tim_setbit(&TIM9->CR1, 1, 7, bool);
}

void STM32446Tim9_set_opm(uint8_t bool)
{
	tim_setbit(&TIM9->CR1, 1, 3, bool);
}

void STM32446Tim9_set_urs(uint8_t bool)
{
	tim_setbit(&TIM9->CR1, 1, 2, bool);
}

void STM32446Tim9_set_udis(uint8_t bool)
{
	tim_setbit(&TIM9->CR1, 1, 1, bool);
}

void STM32446Tim9_cen(uint8_t bool)
{
	tim_setbit(&TIM9->CR1, 1, 0, bool);
}

// SMCR
void STM32446Tim9_msm(uint8_t bool)
{
	tim_setbit(&TIM9->SMCR, 1, 7, bool);
}

void STM32446Tim9_ts(uint8_t ts)
{
	tim_setbit(&TIM9->SMCR, 3, 4, ts);
}

void STM32446Tim9_sms(uint8_t sms)
{
	tim_setbit(&TIM9->SMCR, 3, 0, sms);
}

// DIER
void STM32446Tim9_tie(uint8_t bool)
{
	tim_setbit(&TIM9->DIER, 1, 6, bool);
}

void STM32446Tim9_cc2ie(uint8_t bool)
{
	tim_setbit(&TIM9->DIER, 1, 2, bool);
}

void STM32446Tim9_cc1ie(uint8_t bool)
{
	tim_setbit(&TIM9->DIER, 1, 1, bool);
}

void STM32446Tim9_uie(uint8_t bool)
{
	tim_setbit(&TIM9->DIER, 1, 0, bool);
}

// SR
uint8_t STM32446Tim9_cc2of(void)
{
	return tim_getbit(TIM9->SR, 1, 10);
}
void STM32446Tim9_clear_cc2of(void)
{
	tim_setbit(&TIM9->SR, 1, 10, 0);
}

uint8_t STM32446Tim9_cc1of(void)
{
	return tim_getbit(TIM9->SR, 1, 9);
}
void STM32446Tim9_clear_cc1of(void)
{
	tim_setbit(&TIM9->SR, 1, 9, 0);
}

uint8_t STM32446Tim9_tif(void)
{
	return tim_getbit(TIM9->SR, 1, 6);
}
void STM32446Tim9_clear_tif(void)
{
	tim_setbit(&TIM9->SR, 1, 6, 0);
}

uint8_t STM32446Tim9_cc2if(void)
{
	return tim_getbit(TIM9->SR, 1, 2);
}
void STM32446Tim9_clear_cc2if(void)
{
	tim_setbit(&TIM9->SR, 1, 2, 0);
}

uint8_t STM32446Tim9_cc1if(void)
{
	return tim_getbit(TIM9->SR, 1, 1);
}
void STM32446Tim9_clear_cc1if(void)
{
	tim_setbit(&TIM9->SR, 1, 1, 0);
}

uint8_t STM32446Tim9_uif(void)
{
	return tim_getbit(TIM9->SR, 1, 0);
}
void STM32446Tim9_clear_uif(void)
{
	tim_setbit(&TIM9->SR, 1, 0, 0);
}

// EGR
void STM32446Tim9_tg(void)
{
	tim_setbit(&TIM9->EGR, 1, 6, 1);
}

void STM32446Tim9_cc2g(void)
{
	tim_setbit(&TIM9->EGR, 1, 2, 1);
}

void STM32446Tim9_cc1g(void)
{
	tim_setbit(&TIM9->EGR, 1, 1, 1);
}

void STM32446Tim9_ug(void)
{
	tim_setbit(&TIM9->EGR, 1, 0, 1);
}

// CCMR1
void STM32446Tim9_oc2m(uint8_t oc2m)
{
	tim_setbit(&TIM9->CCMR1, 3, 12, oc2m);
}
void STM32446Tim9_ic2f(uint8_t ic2f)
{
	tim_setbit(&TIM9->CCMR1, 4, 12, ic2f);
}

void STM32446Tim9_oc2pe(uint8_t bool)
{
	tim_setbit(&TIM9->CCMR1, 1, 11, bool);
}
void STM32446Tim9_oc2fe(uint8_t bool)
{
	tim_setbit(&TIM9->CCMR1, 1, 10, bool);
}
void STM32446Tim9_ic2psc(uint8_t ic2psc)
{
	tim_setbit(&TIM9->CCMR1, 2, 10, ic2psc);
}

void STM32446Tim9_cc2s(uint8_t cc2s)
{
	tim_setbit(&TIM9->CCMR1, 2, 8, cc2s);
}

void STM32446Tim9_oc1m(uint8_t oc1m)
{
	tim_setbit(&TIM9->CCMR1, 3, 4, oc1m);
}
void STM32446Tim9_ic1f(uint8_t ic1f)
{
	tim_setbit(&TIM9->CCMR1, 4, 4, ic1f);
}

void STM32446Tim9_oc1pe(uint8_t bool)
{
	tim_setbit(&TIM9->CCMR1, 1, 3, bool);
}
void STM32446Tim9_oc1fe(uint8_t bool)
{
	tim_setbit(&TIM9->CCMR1, 1, 2, bool);
}
void STM32446Tim9_ic1psc(uint8_t ic1psc)
{
	tim_setbit(&TIM9->CCMR1, 2, 2, ic1psc);
}

void STM32446Tim9_cc1s(uint8_t cc1s)
{
	tim_setbit(&TIM9->CCMR1, 2, 0, cc1s);
}

// CCER
void STM32446Tim9_cc2np(uint8_t bool)
{
	tim_setbit(&TIM9->CCER, 1, 7, bool);
}

void STM32446Tim9_cc2p(uint8_t bool)
{
	tim_setbit(&TIM9->CCER, 1, 5, bool);
}

void STM32446Tim9_cc2e(uint8_t bool)
{
	tim_setbit(&TIM9->CCER, 1, 4, bool);
}

void STM32446Tim9_cc1np(uint8_t bool)
{
	tim_setbit(&TIM9->CCER, 1, 3, bool);
}

void STM32446Tim9_cc1p(uint8_t bool)
{
	tim_setbit(&TIM9->CCER, 1, 1, bool);
}

void STM32446Tim9_cc1e(uint8_t bool)
{
	tim_setbit(&TIM9->CCER, 1, 0, bool);
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

/*** File Procedure & Function Definition***/
uint32_t tim_getbit(uint32_t reg, uint32_t size_block, uint32_t bit)
{
	uint32_t value = 0; uint32_t tmp = 0;
	uint32_t mask = (unsigned int)((1 << size_block) - 1);
	mask = (mask << bit);
	tmp = mask & reg;
	value = (tmp >> bit);
	return value;
}

void tim_setbit(volatile uint32_t* reg, uint32_t size_block, uint32_t bit, uint32_t data)
{
	uint32_t n = 0;
	if(bit > 31){ n = bit/32; bit = bit - (n * 32); }
	uint32_t value = 0;
	uint32_t mask = (unsigned int)((1 << size_block) - 1);
	value = data & mask;
	*(reg + n ) &= ~(mask << bit);
	*(reg + n ) |= (value << bit);
}

uint32_t tim_getsetbit(volatile uint32_t* reg, uint32_t size_block, uint32_t bit)
{
	uint32_t n = 0;
	if(bit > 31){ n = bit/32; bit = bit - (n * 32); }
	uint32_t value = 0;
	uint32_t mask = (unsigned int)((1 << size_block) - 1);
	value = *(reg + n ) & ~(mask << bit);
	value = (value >> bit);
	return value;
}

/*** File Interrupt ***/
// void TIM1_BRK_TIM9_IRQHandler(void){ // receive interrupt flags }

/*** EOF ***/


