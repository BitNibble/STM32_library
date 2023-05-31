/******************************************************************************
	STM32 446 TIM
Author: Sergio Santos 
	<sergio.salazar.santos@gmail.com>
License: GNU General Public License
Hardware: STM32-446
Date: 28052023
Comment:
	
*******************************************************************************/
#ifndef _STM32446TIM_H_
	#define _STM32446TIM_H_

/*** Library ***/
#include <inttypes.h>
#include "stm32446common.h"

/*** TIM 9 ***/
typedef struct{
	TIM_TypeDef* reg;
	STM32446TIM9_CR1 cr1;
	STM32446TIM9_SMCR smcr;
	STM32446TIM9_DIER dier;
	STM32446TIM9_SR sr;
	STM32446TIM9_EGR egr;
	STM32446TIM9_CCMR1 ccmr1;
	STM32446TIM9_CCER ccer;
	void (*cnt)(uint16_t value);
	uint16_t (*get_cnt)(void);
	void (*arr)(uint16_t value);
	void (*ccr1)(uint16_t value);
	void (*ccr2)(uint16_t value);
	void (*psc)(uint16_t value);
	void (*inic)(void);
	void (*nvict1t9)(void);
}STM32446TIM9;

STM32446TIM9 STM32446TIM9enable(void);
// INIC
void STM32446Tim9Inic(void);
// INTERRUPT
void STM32446Tim9EnableInterrupt(void);
// CR1
uint8_t STM32446Tim9_get_ckd(void);
void STM32446Tim9_set_apre(uint8_t bool);
void STM32446Tim9_set_opm(uint8_t bool);
void STM32446Tim9_set_urs(uint8_t bool);
void STM32446Tim9_set_udis(uint8_t bool);
void STM32446Tim9_cen(uint8_t bool);
// SMCR
void STM32446Tim9_msm(uint8_t bool);
void STM32446Tim9_ts(uint8_t ts);
void STM32446Tim9_sms(uint8_t sms);
// DIER
void STM32446Tim9_tie(uint8_t bool);
void STM32446Tim9_cc2ie(uint8_t bool);
void STM32446Tim9_cc1ie(uint8_t bool);
void STM32446Tim9_uie(uint8_t bool);
// SR
uint8_t STM32446Tim9_cc2of(void);
void STM32446Tim9_clear_cc2of(void);
uint8_t STM32446Tim9_cc1of(void);
void STM32446Tim9_clear_cc1of(void);
uint8_t STM32446Tim9_tif(void);
void STM32446Tim9_clear_tif(void);
uint8_t STM32446Tim9_cc2if(void);
void STM32446Tim9_clear_cc2if(void);
uint8_t STM32446Tim9_cc1if(void);
void STM32446Tim9_clear_cc1if(void);
uint8_t STM32446Tim9_uif(void);
void STM32446Tim9_clear_uif(void);
// EGR
void STM32446Tim9_tg(void);
void STM32446Tim9_cc2g(void);
void STM32446Tim9_cc1g(void);
void STM32446Tim9_ug(void);
// CCMR1
void STM32446Tim9_oc2m(uint8_t oc2m);
void STM32446Tim9_ic2f(uint8_t ic2f);
void STM32446Tim9_oc2pe(uint8_t bool);
void STM32446Tim9_oc2fe(uint8_t bool);
void STM32446Tim9_ic2psc(uint8_t ic2psc);
void STM32446Tim9_cc2s(uint8_t cc2s);
void STM32446Tim9_oc1m(uint8_t oc1m);
void STM32446Tim9_ic1f(uint8_t ic1f);
void STM32446Tim9_oc1pe(uint8_t bool);
void STM32446Tim9_oc1fe(uint8_t bool);
void STM32446Tim9_ic1psc(uint8_t ic1psc);
void STM32446Tim9_cc1s(uint8_t cc1s);
// CCER
void STM32446Tim9_cc2np(uint8_t bool);
void STM32446Tim9_cc2p(uint8_t bool);
void STM32446Tim9_cc2e(uint8_t bool);
void STM32446Tim9_cc1np(uint8_t bool);
void STM32446Tim9_cc1p(uint8_t bool);
void STM32446Tim9_cc1e(uint8_t bool);
// CNT
void STM32446Tim9_cnt(uint16_t value);
uint16_t STM32446Tim9_get_cnt(void);
// ARR
void STM32446Tim9_arr(uint16_t value);
// CCR1
void STM32446Tim9_ccr1(uint16_t value);
// CCR2
void STM32446Tim9_ccr2(uint16_t value);
// PSC
void STM32446Tim9_psc(uint16_t value);

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


