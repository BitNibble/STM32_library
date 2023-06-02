/******************************************************************************
	STM32 446 TIM
Author: Sergio Santos 
	<sergio.salazar.santos@gmail.com>
License: GNU General Public License
Hardware: STM32-446
Date: 02062023
Comment:
	
*******************************************************************************/
#ifndef _STM32446TIM_H_
	#define _STM32446TIM_H_

/*** Library ***/
#include <inttypes.h>

/*** TIMER9_Common ***/
typedef struct{
	uint8_t (*get_ckd)(void);
	void (*apre)(uint8_t bool);
	void (*opm)(uint8_t bool);
	void (*urs)(uint8_t bool);
	void (*udis)(uint8_t bool);
	void (*cen)(uint8_t bool);
}STM32446TIM9_CR1;

typedef struct{
	void (*msm)(uint8_t bool);
	void (*ts)(uint8_t ts);
	void (*sms)(uint8_t sms);
}STM32446TIM9_SMCR;

typedef struct{
	void (*tie)(uint8_t bool);
	void (*cc2ie)(uint8_t bool);
	void (*cc1ie)(uint8_t bool);
	void (*uie)(uint8_t bool);
}STM32446TIM9_DIER;

typedef struct{
	uint8_t (*cc2of)(void);
	void (*clear_cc2of)(void);
	uint8_t (*cc1of)(void);
	void (*clear_cc1of)(void);
	uint8_t (*tif)(void);
	void (*clear_tif)(void);
	uint8_t (*cc2if)(void);
	void (*clear_cc2if)(void);
	uint8_t (*cc1if)(void);
	void (*clear_cc1if)(void);
	uint8_t (*uif)(void);
	void (*clear_uif)(void);
}STM32446TIM9_SR;

typedef struct{
	void (*tg)(void);
	void (*cc2g)(void);
	void (*cc1g)(void);
	void (*ug)(void);
}STM32446TIM9_EGR;

typedef struct{
	void (*oc2m)(uint8_t oc2m);
	void (*ic2f)(uint8_t ic2f);
	void (*oc2pe)(uint8_t bool);
	void (*oc2fe)(uint8_t bool);
	void (*ic2psc)(uint8_t ic2psc);
	void (*cc2s)(uint8_t cc2s);
	void (*oc1m)(uint8_t oc1m);
	void (*ic1f)(uint8_t ic1f);
	void (*oc1pe)(uint8_t bool);
	void (*oc1fe)(uint8_t bool);
	void (*ic1psc)(uint8_t ic1psc);
	void (*cc1s)(uint8_t cc1s);
}STM32446TIM9_CCMR1;

typedef struct{
	void (*cc2np)(uint8_t bool);
	void (*cc2p)(uint8_t bool);
	void (*cc2e)(uint8_t bool);
	void (*cc1np)(uint8_t bool);
	void (*cc1p)(uint8_t bool);
	void (*cc1e)(uint8_t bool);
}STM32446TIM9_CCER;

// TIM -> TIM1
typedef struct
{
	TIM_TypeDef* reg;
	#if defined(_STM32446TIM_H_)
		void (*enable)(void);
	#endif
}STM32446TIM1obj;

// TIM -> TIM2
typedef struct
{
	TIM_TypeDef* reg;
	#if defined(_STM32446TIM_H_)
		void (*enable)(void);
	#endif
}STM32446TIM2obj;

// TIM -> TIM3
typedef struct
{
	TIM_TypeDef* reg;
	#if defined(_STM32446TIM_H_)
		void (*enable)(void);
	#endif
}STM32446TIM3obj;

// TIM -> TIM4
typedef struct
{
	TIM_TypeDef* reg;
	#if defined(_STM32446TIM_H_)
		void (*enable)(void);
	#endif
}STM32446TIM4obj;

// TIM -> TIM5
typedef struct
{
	TIM_TypeDef* reg;
	#if defined(_STM32446TIM_H_)
		void (*enable)(void);
	#endif
}STM32446TIM5obj;

// TIM -> TIM6
typedef struct
{
	TIM_TypeDef* reg;
	#if defined(_STM32446TIM_H_)
		void (*enable)(void);
	#endif
}STM32446TIM6obj;

// TIM -> TIM7
typedef struct
{
	TIM_TypeDef* reg;
	#if defined(_STM32446TIM_H_)
		void (*enable)(void);
	#endif
}STM32446TIM7obj;

// TIM -> TIM8
typedef struct
{
	TIM_TypeDef* reg;
	#if defined(_STM32446TIM_H_)
		void (*enable)(void);
	#endif
}STM32446TIM8obj;

// TIM -> TIM9
typedef struct
{
	TIM_TypeDef* reg;
	#if defined(_STM32446TIM_H_)
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
		void (*clock)(void);
		void (*inic)(void);
		void (*nvict1t9)(void);
	#endif
}STM32446TIM9obj;

// TIM -> TIM10
typedef struct
{
	TIM_TypeDef* reg;
	#if defined(_STM32446TIM_H_)
		void (*enable)(void);
	#endif
}STM32446TIM10obj;

// TIM -> TIM11
typedef struct
{
	TIM_TypeDef* reg;
	#if defined(_STM32446TIM_H_)
		void (*enable)(void);
	#endif
}STM32446TIM11obj;

// TIM -> TIM12
typedef struct
{
	TIM_TypeDef* reg;
	#if defined(_STM32446TIM_H_)
		void (*enable)(void);
	#endif
}STM32446TIM12obj;

// TIM -> TIM13
typedef struct
{
	TIM_TypeDef* reg;
	#if defined(_STM32446TIM_H_)
		void (*enable)(void);
	#endif
}STM32446TIM13obj;

// TIM -> TIM14
typedef struct
{
	TIM_TypeDef* reg;
	#if defined(_STM32446TIM_H_)
		void (*enable)(void);
	#endif
}STM32446TIM14obj;

/*** TIM9 ***/
// CLOCK
void STM32446Tim9Clock(void);
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


