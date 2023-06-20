/******************************************************************************
	STM32 446 TIM
Author: Sergio Santos 
	<sergio.salazar.santos@gmail.com>
License: GNU General Public License
Hardware: STM32-446
Date: 19062023
Comment:
	
*******************************************************************************/
#ifndef _STM32446TIM_H_
	#define _STM32446TIM_H_
/*** Library ***/
#include <inttypes.h>
/*** TIMER Bit Mapping TypeDef ***/
typedef struct{
	void (*ckd)(uint8_t value);
	uint8_t (*get_ckd)(void);
	void (*apre)(uint8_t bool);
	void (*cms)(uint8_t value);
	void (*dir)(uint8_t bool);
	void (*opm)(uint8_t bool);
	void (*urs)(uint8_t bool);
	void (*udis)(uint8_t bool);
	void (*cen)(uint8_t bool);
}STM32446TIM_CR1;
typedef struct{
	void (*ois4)(uint8_t bool);
	void (*ois3n)(uint8_t bool);
	void (*ois3)(uint8_t bool);
	void (*ois2n)(uint8_t bool);
	void (*ois2)(uint8_t bool);
	void (*ois1n)(uint8_t bool);
	void (*ois1)(uint8_t bool);
	void (*ti1s)(uint8_t bool);
	void (*mms)(uint8_t value);
	void (*ccds)(uint8_t bool);
	void (*ccus)(uint8_t bool);
	void (*ccpc)(uint8_t bool);
}STM32446TIM_CR2;
typedef struct{
	void (*etp)(uint8_t bool);
	void (*ece)(uint8_t bool);
	void (*etps)(uint8_t value);
	void (*etf)(uint8_t value);
	void (*msm)(uint8_t bool);
	void (*ts)(uint8_t value);
	void (*sms)(uint8_t value);
}STM32446TIM_SMCR;
typedef struct{
	void (*tde)(uint8_t bool);
	void (*comde)(uint8_t bool);
	void (*cc4de)(uint8_t bool);
	void (*cc3de)(uint8_t bool);
	void (*cc2de)(uint8_t bool);
	void (*cc1de)(uint8_t bool);
	void (*ude)(uint8_t bool);
	void (*bie)(uint8_t bool);
	void (*tie)(uint8_t bool);
	void (*comie)(uint8_t bool);
	void (*cc4ie)(uint8_t bool);
	void (*cc3ie)(uint8_t bool);
	void (*cc2ie)(uint8_t bool);
	void (*cc1ie)(uint8_t bool);
	void (*uie)(uint8_t bool);
}STM32446TIM_DIER;
typedef struct{
	uint8_t (*cc4of)(void);
	void (*clear_cc4of)(void);
	uint8_t (*cc3of)(void);
	void (*clear_cc3of)(void);
	uint8_t (*cc2of)(void);
	void (*clear_cc2of)(void);
	uint8_t (*cc1of)(void);
	void (*clear_cc1of)(void);
	uint8_t (*bif)(void);
	void (*clear_bif)(void);
	uint8_t (*tif)(void);
	void (*clear_tif)(void);
	uint8_t (*comif)(void);
	void (*clear_comif)(void);
	uint8_t (*cc4if)(void);
	void (*clear_cc4if)(void);
	uint8_t (*cc3if)(void);
	void (*clear_cc3if)(void);
	uint8_t (*cc2if)(void);
	void (*clear_cc2if)(void);
	uint8_t (*cc1if)(void);
	void (*clear_cc1if)(void);
	uint8_t (*uif)(void);
	void (*clear_uif)(void);
}STM32446TIM_SR;
typedef struct{
	void (*bg)(void);
	void (*tg)(void);
	void (*comg)(void);
	void (*cc4g)(void);
	void (*cc3g)(void);
	void (*cc2g)(void);
	void (*cc1g)(void);
	void (*ug)(void);
}STM32446TIM_EGR;
typedef struct{
	void (*oc2ce)(uint8_t bool);
	void (*oc2m)(uint8_t value);
	void (*ic2f)(uint8_t value);
	void (*oc2pe)(uint8_t bool);
	void (*oc2fe)(uint8_t bool);
	void (*ic2psc)(uint8_t value);
	void (*cc2s)(uint8_t value);
	void (*oc1ce)(uint8_t bool);
	void (*oc1m)(uint8_t value);
	void (*ic1f)(uint8_t value);
	void (*oc1pe)(uint8_t bool);
	void (*oc1fe)(uint8_t bool);
	void (*ic1psc)(uint8_t value);
	void (*cc1s)(uint8_t value);
}STM32446TIM_CCMR1;
typedef struct{
	void (*oc4ce)(uint8_t bool);
	void (*oc4m)(uint8_t value);
	void (*ic4f)(uint8_t value);
	void (*oc4pe)(uint8_t bool);
	void (*oc4fe)(uint8_t bool);
	void (*ic4psc)(uint8_t value);
	void (*cc4s)(uint8_t value);
	void (*oc3ce)(uint8_t bool);
	void (*oc3m)(uint8_t value);
	void (*ic3f)(uint8_t value);
	void (*oc3pe)(uint8_t bool);
	void (*oc3fe)(uint8_t bool);
	void (*ic3psc)(uint8_t value);
	void (*cc3s)(uint8_t value);
}STM32446TIM_CCMR2;
typedef struct{
	void (*cc4p)(uint8_t bool);
	void (*cc4e)(uint8_t bool);
	void (*cc3np)(uint8_t bool);
	void (*cc3ne)(uint8_t bool);
	void (*cc3p)(uint8_t bool);
	void (*cc3e)(uint8_t bool);
	void (*cc2np)(uint8_t bool);
	void (*cc2ne)(uint8_t bool);
	void (*cc2p)(uint8_t bool);
	void (*cc2e)(uint8_t bool);
	void (*cc1np)(uint8_t bool);
	void (*cc1ne)(uint8_t bool);
	void (*cc1p)(uint8_t bool);
	void (*cc1e)(uint8_t bool);
}STM32446TIM_CCER;
/*** TIMER TypeDef***/
// TIM -> TIM1
typedef struct
{
	TIM_TypeDef* reg;
}STM32446TIM1obj;
// TIM -> TIM2
typedef struct
{
	TIM_TypeDef* reg;
}STM32446TIM2obj;
// TIM -> TIM3
typedef struct
{
	TIM_TypeDef* reg;
}STM32446TIM3obj;
// TIM -> TIM4
typedef struct
{
	TIM_TypeDef* reg;
}STM32446TIM4obj;
// TIM -> TIM5
typedef struct
{
	TIM_TypeDef* reg;
}STM32446TIM5obj;
// TIM -> TIM6
typedef struct
{
	TIM_TypeDef* reg;
}STM32446TIM6obj;
// TIM -> TIM7
typedef struct
{
	TIM_TypeDef* reg;
}STM32446TIM7obj;
// TIM -> TIM8
typedef struct
{
	TIM_TypeDef* reg;
}STM32446TIM8obj;
// TIM -> TIM9
typedef struct
{
	TIM_TypeDef* reg;
	/*** Bit Mapping ***/
	STM32446TIM_CR1 cr1;
	STM32446TIM_SMCR smcr;
	STM32446TIM_DIER dier;
	STM32446TIM_SR sr;
	STM32446TIM_EGR egr;
	STM32446TIM_CCMR1 ccmr1;
	STM32446TIM_CCER ccer;
	void (*cnt)(uint16_t value);
	uint16_t (*get_cnt)(void);
	void (*arr)(uint16_t value);
	void (*ccr1)(uint16_t value);
	void (*ccr2)(uint16_t value);
	void (*psc)(uint16_t value);
	/*** Other ***/
	void (*clock)(void);
}STM32446TIM9obj;
// TIM -> TIM10
typedef struct
{
	TIM_TypeDef* reg;
}STM32446TIM10obj;
// TIM -> TIM11
typedef struct
{
	TIM_TypeDef* reg;
}STM32446TIM11obj;
// TIM -> TIM12
typedef struct
{
	TIM_TypeDef* reg;
}STM32446TIM12obj;
// TIM -> TIM13
typedef struct
{
	TIM_TypeDef* reg;
}STM32446TIM13obj;
// TIM -> TIM14
typedef struct
{
	TIM_TypeDef* reg;
}STM32446TIM14obj;
// INIC
STM32446TIM1obj tim1_inic(void);
STM32446TIM2obj tim2_inic(void);
STM32446TIM3obj tim3_inic(void);
STM32446TIM4obj tim4_inic(void);
STM32446TIM5obj tim5_inic(void);
STM32446TIM6obj tim6_inic(void);
STM32446TIM7obj tim7_inic(void);
STM32446TIM8obj tim8_inic(void);
STM32446TIM9obj tim9_inic(void);
STM32446TIM10obj tim10_inic(void);
STM32446TIM11obj tim11_inic(void);
STM32446TIM12obj tim12_inic(void);
STM32446TIM13obj tim13_inic(void);
STM32446TIM14obj tim14_inic(void);
/*** TIM9 Procedure & Function Header ***/
// CLOCK
void STM32446Tim9Clock(void);
/*** TIM9 Bit Mapping Header ***/
// CR1
uint8_t STM32446Tim9_get_ckd(void);
void STM32446Tim9_set_apre(uint8_t bool);
void STM32446Tim9_set_opm(uint8_t bool);
void STM32446Tim9_set_urs(uint8_t bool);
void STM32446Tim9_set_udis(uint8_t bool);
void STM32446Tim9_cen(uint8_t bool);
// SMCR
void STM32446Tim9_msm(uint8_t bool);
void STM32446Tim9_ts(uint8_t value);
void STM32446Tim9_sms(uint8_t value);
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
void STM32446Tim9_oc2m(uint8_t value);
void STM32446Tim9_ic2f(uint8_t value);
void STM32446Tim9_oc2pe(uint8_t bool);
void STM32446Tim9_oc2fe(uint8_t bool);
void STM32446Tim9_ic2psc(uint8_t value);
void STM32446Tim9_cc2s(uint8_t value);
void STM32446Tim9_oc1m(uint8_t value);
void STM32446Tim9_ic1f(uint8_t value);
void STM32446Tim9_oc1pe(uint8_t bool);
void STM32446Tim9_oc1fe(uint8_t bool);
void STM32446Tim9_ic1psc(uint8_t value);
void STM32446Tim9_cc1s(uint8_t value);
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


