/******************************************************************************
	STM32 446 TIM 9 to 14
Author: Sergio Santos 
	<sergio.salazar.santos@gmail.com>
License: GNU General Public License
Hardware: STM32-446
Date: 22062023
Comment:
	
*******************************************************************************/
#ifndef _STM32446TIM9TO14_H_
	#define _STM32446TIM9TO14_H_
/*** Library ***/
#include <inttypes.h>
/*** TIMER 9 to 14 Bit Mapping TypeDef ***/
// CR1 9/12
typedef struct{
	void (*ckd)(uint8_t value);
	uint8_t (*get_ckd)(void);
	void (*apre)(uint8_t bool);
	void (*opm)(uint8_t bool);
	void (*urs)(uint8_t bool);
	void (*udis)(uint8_t bool);
	void (*cen)(uint8_t bool);
}STM32446TIM9_CR1, STM32446TIM12_CR1;
// CR1 10/11/13/14
typedef struct{
	void (*ckd)(uint8_t value);
	uint8_t (*get_ckd)(void);
	void (*apre)(uint8_t bool);
	void (*urs)(uint8_t bool);
	void (*udis)(uint8_t bool);
	void (*cen)(uint8_t bool);
}STM32446TIM10_CR1, STM32446TIM11_CR1, STM32446TIM13_CR1, STM32446TIM14_CR1;
// SMCR 9/12
typedef struct{
	void (*msm)(uint8_t bool);
	void (*ts)(uint8_t value);
	void (*sms)(uint8_t value);
}STM32446TIM9_SMCR, STM32446TIM12_SMCR;
// DIER 9/12
typedef struct{
	void (*tie)(uint8_t bool);
	void (*cc2ie)(uint8_t bool);
	void (*cc1ie)(uint8_t bool);
	void (*uie)(uint8_t bool);
}STM32446TIM9_DIER, STM32446TIM12_DIER;
// DIER 10/11/13/14
typedef struct{
	void (*cc1ie)(uint8_t bool);
	void (*uie)(uint8_t bool);
}STM32446TIM10_DIER, STM32446TIM11_DIER, STM32446TIM13_DIER, STM32446TIM14_DIER;
// SR 9/12
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
}STM32446TIM9_SR, STM32446TIM12_SR;
// SR 10/11/13/14
typedef struct{
	uint8_t (*cc1of)(void);
	void (*clear_cc1of)(void);
	uint8_t (*cc1if)(void);
	void (*clear_cc1if)(void);
	uint8_t (*uif)(void);
	void (*clear_uif)(void);
}STM32446TIM10_SR, STM32446TIM11_SR, STM32446TIM13_SR, STM32446TIM14_SR;
// EGR 9/12
typedef struct{
	void (*tg)(void);
	void (*cc2g)(void);
	void (*cc1g)(void);
	void (*ug)(void);
}STM32446TIM9_EGR, STM32446TIM12_EGR;
// EGR 10/11/13/14
typedef struct{
	void (*cc1g)(void);
	void (*ug)(void);
}STM32446TIM10_EGR, STM32446TIM11_EGR, STM32446TIM13_EGR, STM32446TIM14_EGR;
// CCMR1 9/12
typedef struct{
	void (*oc2m)(uint8_t value);
	void (*ic2f)(uint8_t value);
	void (*oc2pe)(uint8_t bool);
	void (*oc2fe)(uint8_t bool);
	void (*ic2psc)(uint8_t value);
	void (*cc2s)(uint8_t value);
	void (*oc1m)(uint8_t value);
	void (*ic1f)(uint8_t value);
	void (*oc1pe)(uint8_t bool);
	void (*oc1fe)(uint8_t bool);
	void (*ic1psc)(uint8_t value);
	void (*cc1s)(uint8_t value);
}STM32446TIM9_CCMR1, STM32446TIM12_CCMR1;
// CCMR1 10/11/13/14
typedef struct{
	void (*oc1m)(uint8_t value);
	void (*ic1f)(uint8_t value);
	void (*oc1pe)(uint8_t bool);
	void (*oc1fe)(uint8_t bool);
	void (*ic1psc)(uint8_t value);
	void (*cc1s)(uint8_t value);
}STM32446TIM10_CCMR1, STM32446TIM11_CCMR1, STM32446TIM13_CCMR1, STM32446TIM14_CCMR1;
// CCER 9/12
typedef struct{
	void (*cc2np)(uint8_t bool);
	void (*cc2p)(uint8_t bool);
	void (*cc2e)(uint8_t bool);
	void (*cc1np)(uint8_t bool);
	void (*cc1p)(uint8_t bool);
	void (*cc1e)(uint8_t bool);
}STM32446TIM9_CCER, STM32446TIM12_CCER;
// CCER 10/11/13/14
typedef struct{
	void (*cc1np)(uint8_t bool);
	void (*cc1p)(uint8_t bool);
	void (*cc1e)(uint8_t bool);
}STM32446TIM10_CCER, STM32446TIM11_CCER, STM32446TIM13_CCER, STM32446TIM14_CCER;
/*** TIMER 9 TO 14 TypeDef***/
// ( 9/12 ) TIM
typedef struct
{
	TIM_TypeDef* reg;
	/*** Bit Mapping ***/
	STM32446TIM9_CR1 cr1;
	STM32446TIM9_SMCR smcr;
	STM32446TIM9_DIER dier;
	STM32446TIM9_SR sr;
	STM32446TIM9_EGR egr;
	STM32446TIM9_CCMR1 ccmr1;
	STM32446TIM9_CCER ccer;
	void (*cnt)(uint16_t value);
	uint16_t (*get_cnt)(void);
	void (*psc)(uint16_t value);
	void (*arr)(uint16_t value);
	void (*ccr1)(uint16_t value);
	void (*ccr2)(uint16_t value);
	/*** Other ***/
	void (*clock)(uint8_t bool);
	void (*nvic)(uint8_t bool);
}STM32446TIM9obj, STM32446TIM12obj;
// ( 10/11/13/14 ) TIM
typedef struct
{
	TIM_TypeDef* reg;
	/*** Bit Mapping ***/
	STM32446TIM10_CR1 cr1;
	STM32446TIM10_DIER dier;
	STM32446TIM10_SR sr;
	STM32446TIM10_EGR egr;
	STM32446TIM10_CCMR1 ccmr1;
	STM32446TIM10_CCER ccer;
	void (*cnt)(uint16_t value);
	uint16_t (*get_cnt)(void);
	void (*psc)(uint16_t value);
	void (*arr)(uint16_t value);
	void (*ccr1)(uint16_t value);
	void (*or)(uint8_t value);
	/*** Other ***/
	void (*clock)(uint8_t bool);
	void (*nvic)(uint8_t bool);
}STM32446TIM10obj, STM32446TIM11obj, STM32446TIM13obj, STM32446TIM14obj;
/************************/
/*** INIC TIM 9 to 14 ***/
/************************/
STM32446TIM9obj tim9_inic(void);
STM32446TIM10obj tim10_inic(void);
STM32446TIM11obj tim11_inic(void);
STM32446TIM12obj tim12_inic(void);
STM32446TIM13obj tim13_inic(void);
STM32446TIM14obj tim14_inic(void);
/****************************************/
/*** TIM9 Procedure & Function Header ***/
/****************************************/
void STM32446Tim9Clock(uint8_t bool);
void STM32446Tim9Nvic(uint8_t bool);
/*** TIM9 Bit Mapping Header ***/
// CR1
void STM32446Tim9_ckd(uint8_t value);
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
// PSC
void STM32446Tim9_psc(uint16_t value);
// ARR
void STM32446Tim9_arr(uint16_t value);
// CCR1
void STM32446Tim9_ccr1(uint16_t value);
// CCR2
void STM32446Tim9_ccr2(uint16_t value);
/*****************************************/
/*** TIM10 Procedure & Function Header ***/
/*****************************************/
void STM32446Tim10Clock(uint8_t bool);
void STM32446Tim10Nvic(uint8_t bool);
/*** TIM10 Bit Mapping Header ***/
// CR1
void STM32446Tim10_ckd(uint8_t value);
uint8_t STM32446Tim10_get_ckd(void);
void STM32446Tim10_set_apre(uint8_t bool);
void STM32446Tim10_set_opm(uint8_t bool);
void STM32446Tim10_set_urs(uint8_t bool);
void STM32446Tim10_set_udis(uint8_t bool);
void STM32446Tim10_cen(uint8_t bool);
// DIER
void STM32446Tim10_tie(uint8_t bool);
void STM32446Tim10_cc2ie(uint8_t bool);
void STM32446Tim10_cc1ie(uint8_t bool);
void STM32446Tim10_uie(uint8_t bool);
// SR
uint8_t STM32446Tim10_cc2of(void);
void STM32446Tim10_clear_cc2of(void);
uint8_t STM32446Tim10_cc1of(void);
void STM32446Tim10_clear_cc1of(void);
uint8_t STM32446Tim10_tif(void);
void STM32446Tim10_clear_tif(void);
uint8_t STM32446Tim10_cc2if(void);
void STM32446Tim10_clear_cc2if(void);
uint8_t STM32446Tim10_cc1if(void);
void STM32446Tim10_clear_cc1if(void);
uint8_t STM32446Tim10_uif(void);
void STM32446Tim10_clear_uif(void);
// EGR
void STM32446Tim10_tg(void);
void STM32446Tim10_cc2g(void);
void STM32446Tim10_cc1g(void);
void STM32446Tim10_ug(void);
// CCMR1
void STM32446Tim10_oc2m(uint8_t value);
void STM32446Tim10_ic2f(uint8_t value);
void STM32446Tim10_oc2pe(uint8_t bool);
void STM32446Tim10_oc2fe(uint8_t bool);
void STM32446Tim10_ic2psc(uint8_t value);
void STM32446Tim10_cc2s(uint8_t value);
void STM32446Tim10_oc1m(uint8_t value);
void STM32446Tim10_ic1f(uint8_t value);
void STM32446Tim10_oc1pe(uint8_t bool);
void STM32446Tim10_oc1fe(uint8_t bool);
void STM32446Tim10_ic1psc(uint8_t value);
void STM32446Tim10_cc1s(uint8_t value);
// CCER
void STM32446Tim10_cc2np(uint8_t bool);
void STM32446Tim10_cc2p(uint8_t bool);
void STM32446Tim10_cc2e(uint8_t bool);
void STM32446Tim10_cc1np(uint8_t bool);
void STM32446Tim10_cc1p(uint8_t bool);
void STM32446Tim10_cc1e(uint8_t bool);
// CNT
void STM32446Tim10_cnt(uint16_t value);
uint16_t STM32446Tim10_get_cnt(void);
// PSC
void STM32446Tim10_psc(uint16_t value);
// ARR
void STM32446Tim10_arr(uint16_t value);
// CCR1
void STM32446Tim10_ccr1(uint16_t value);
// OR
void STM32446Tim10_or(uint8_t value);
/*****************************************/
/*** TIM11 Procedure & Function Header ***/
/*****************************************/
void STM32446Tim11Clock(uint8_t bool);
void STM32446Tim11Nvic(uint8_t bool);
/*** TIM11 Bit Mapping Header ***/
// CR1
void STM32446Tim11_ckd(uint8_t value);
uint8_t STM32446Tim11_get_ckd(void);
void STM32446Tim11_set_apre(uint8_t bool);
void STM32446Tim11_set_opm(uint8_t bool);
void STM32446Tim11_set_urs(uint8_t bool);
void STM32446Tim11_set_udis(uint8_t bool);
void STM32446Tim11_cen(uint8_t bool);
// DIER
void STM32446Tim11_tie(uint8_t bool);
void STM32446Tim11_cc2ie(uint8_t bool);
void STM32446Tim11_cc1ie(uint8_t bool);
void STM32446Tim11_uie(uint8_t bool);
// SR
uint8_t STM32446Tim11_cc2of(void);
void STM32446Tim11_clear_cc2of(void);
uint8_t STM32446Tim11_cc1of(void);
void STM32446Tim11_clear_cc1of(void);
uint8_t STM32446Tim11_tif(void);
void STM32446Tim11_clear_tif(void);
uint8_t STM32446Tim11_cc2if(void);
void STM32446Tim11_clear_cc2if(void);
uint8_t STM32446Tim11_cc1if(void);
void STM32446Tim11_clear_cc1if(void);
uint8_t STM32446Tim11_uif(void);
void STM32446Tim11_clear_uif(void);
// EGR
void STM32446Tim11_tg(void);
void STM32446Tim11_cc2g(void);
void STM32446Tim11_cc1g(void);
void STM32446Tim11_ug(void);
// CCMR1
void STM32446Tim11_oc2m(uint8_t value);
void STM32446Tim11_ic2f(uint8_t value);
void STM32446Tim11_oc2pe(uint8_t bool);
void STM32446Tim11_oc2fe(uint8_t bool);
void STM32446Tim11_ic2psc(uint8_t value);
void STM32446Tim11_cc2s(uint8_t value);
void STM32446Tim11_oc1m(uint8_t value);
void STM32446Tim11_ic1f(uint8_t value);
void STM32446Tim11_oc1pe(uint8_t bool);
void STM32446Tim11_oc1fe(uint8_t bool);
void STM32446Tim11_ic1psc(uint8_t value);
void STM32446Tim11_cc1s(uint8_t value);
// CCER
void STM32446Tim11_cc2np(uint8_t bool);
void STM32446Tim11_cc2p(uint8_t bool);
void STM32446Tim11_cc2e(uint8_t bool);
void STM32446Tim11_cc1np(uint8_t bool);
void STM32446Tim11_cc1p(uint8_t bool);
void STM32446Tim11_cc1e(uint8_t bool);
// CNT
void STM32446Tim11_cnt(uint16_t value);
uint16_t STM32446Tim11_get_cnt(void);
// PSC
void STM32446Tim11_psc(uint16_t value);
// ARR
void STM32446Tim11_arr(uint16_t value);
// CCR1
void STM32446Tim11_ccr1(uint16_t value);
// OR
void STM32446Tim11_or(uint8_t value);
/*****************************************/
/*** TIM12 Procedure & Function Header ***/
/*****************************************/
void STM32446Tim12Clock(uint8_t bool);
void STM32446Tim12Nvic(uint8_t bool);
/*** TIM12 Bit Mapping Header ***/
// CR1
void STM32446Tim12_ckd(uint8_t value);
uint8_t STM32446Tim12_get_ckd(void);
void STM32446Tim12_set_apre(uint8_t bool);
void STM32446Tim12_set_opm(uint8_t bool);
void STM32446Tim12_set_urs(uint8_t bool);
void STM32446Tim12_set_udis(uint8_t bool);
void STM32446Tim12_cen(uint8_t bool);
// SMCR
void STM32446Tim12_msm(uint8_t bool);
void STM32446Tim12_ts(uint8_t value);
void STM32446Tim12_sms(uint8_t value);
// DIER
void STM32446Tim12_tie(uint8_t bool);
void STM32446Tim12_cc2ie(uint8_t bool);
void STM32446Tim12_cc1ie(uint8_t bool);
void STM32446Tim12_uie(uint8_t bool);
// SR
uint8_t STM32446Tim12_cc2of(void);
void STM32446Tim12_clear_cc2of(void);
uint8_t STM32446Tim12_cc1of(void);
void STM32446Tim12_clear_cc1of(void);
uint8_t STM32446Tim12_tif(void);
void STM32446Tim12_clear_tif(void);
uint8_t STM32446Tim12_cc2if(void);
void STM32446Tim12_clear_cc2if(void);
uint8_t STM32446Tim12_cc1if(void);
void STM32446Tim12_clear_cc1if(void);
uint8_t STM32446Tim12_uif(void);
void STM32446Tim12_clear_uif(void);
// EGR
void STM32446Tim12_tg(void);
void STM32446Tim12_cc2g(void);
void STM32446Tim12_cc1g(void);
void STM32446Tim12_ug(void);
// CCMR1
void STM32446Tim12_oc2m(uint8_t value);
void STM32446Tim12_ic2f(uint8_t value);
void STM32446Tim12_oc2pe(uint8_t bool);
void STM32446Tim12_oc2fe(uint8_t bool);
void STM32446Tim12_ic2psc(uint8_t value);
void STM32446Tim12_cc2s(uint8_t value);
void STM32446Tim12_oc1m(uint8_t value);
void STM32446Tim12_ic1f(uint8_t value);
void STM32446Tim12_oc1pe(uint8_t bool);
void STM32446Tim12_oc1fe(uint8_t bool);
void STM32446Tim12_ic1psc(uint8_t value);
void STM32446Tim12_cc1s(uint8_t value);
// CCER
void STM32446Tim12_cc2np(uint8_t bool);
void STM32446Tim12_cc2p(uint8_t bool);
void STM32446Tim12_cc2e(uint8_t bool);
void STM32446Tim12_cc1np(uint8_t bool);
void STM32446Tim12_cc1p(uint8_t bool);
void STM32446Tim12_cc1e(uint8_t bool);
// CNT
void STM32446Tim12_cnt(uint16_t value);
uint16_t STM32446Tim12_get_cnt(void);
// PSC
void STM32446Tim12_psc(uint16_t value);
// ARR
void STM32446Tim12_arr(uint16_t value);
// CCR1
void STM32446Tim12_ccr1(uint16_t value);
// CCR2
void STM32446Tim12_ccr2(uint16_t value);
/*****************************************/
/*** TIM13 Procedure & Function Header ***/
/*****************************************/
void STM32446Tim13Clock(uint8_t bool);
void STM32446Tim13Nvic(uint8_t bool);
/*** TIM13 Bit Mapping Header ***/
// CR1
void STM32446Tim13_ckd(uint8_t value);
uint8_t STM32446Tim13_get_ckd(void);
void STM32446Tim13_set_apre(uint8_t bool);
void STM32446Tim13_set_opm(uint8_t bool);
void STM32446Tim13_set_urs(uint8_t bool);
void STM32446Tim13_set_udis(uint8_t bool);
void STM32446Tim13_cen(uint8_t bool);
// DIER
void STM32446Tim13_tie(uint8_t bool);
void STM32446Tim13_cc2ie(uint8_t bool);
void STM32446Tim13_cc1ie(uint8_t bool);
void STM32446Tim13_uie(uint8_t bool);
// SR
uint8_t STM32446Tim13_cc2of(void);
void STM32446Tim13_clear_cc2of(void);
uint8_t STM32446Tim13_cc1of(void);
void STM32446Tim13_clear_cc1of(void);
uint8_t STM32446Tim13_tif(void);
void STM32446Tim13_clear_tif(void);
uint8_t STM32446Tim13_cc2if(void);
void STM32446Tim13_clear_cc2if(void);
uint8_t STM32446Tim13_cc1if(void);
void STM32446Tim13_clear_cc1if(void);
uint8_t STM32446Tim13_uif(void);
void STM32446Tim13_clear_uif(void);
// EGR
void STM32446Tim13_tg(void);
void STM32446Tim13_cc2g(void);
void STM32446Tim13_cc1g(void);
void STM32446Tim13_ug(void);
// CCMR1
void STM32446Tim13_oc2m(uint8_t value);
void STM32446Tim13_ic2f(uint8_t value);
void STM32446Tim13_oc2pe(uint8_t bool);
void STM32446Tim13_oc2fe(uint8_t bool);
void STM32446Tim13_ic2psc(uint8_t value);
void STM32446Tim13_cc2s(uint8_t value);
void STM32446Tim13_oc1m(uint8_t value);
void STM32446Tim13_ic1f(uint8_t value);
void STM32446Tim13_oc1pe(uint8_t bool);
void STM32446Tim13_oc1fe(uint8_t bool);
void STM32446Tim13_ic1psc(uint8_t value);
void STM32446Tim13_cc1s(uint8_t value);
// CCER
void STM32446Tim13_cc2np(uint8_t bool);
void STM32446Tim13_cc2p(uint8_t bool);
void STM32446Tim13_cc2e(uint8_t bool);
void STM32446Tim13_cc1np(uint8_t bool);
void STM32446Tim13_cc1p(uint8_t bool);
void STM32446Tim13_cc1e(uint8_t bool);
// CNT
void STM32446Tim13_cnt(uint16_t value);
uint16_t STM32446Tim13_get_cnt(void);
// PSC
void STM32446Tim13_psc(uint16_t value);
// ARR
void STM32446Tim13_arr(uint16_t value);
// CCR1
void STM32446Tim13_ccr1(uint16_t value);
// OR
void STM32446Tim13_or(uint8_t value);
/*****************************************/
/*** TIM14 Procedure & Function Header ***/
/*****************************************/
void STM32446Tim14Clock(uint8_t bool);
void STM32446Tim14Nvic(uint8_t bool);
/*** TIM14 Bit Mapping Header ***/
// CR1
void STM32446Tim14_ckd(uint8_t value);
uint8_t STM32446Tim14_get_ckd(void);
void STM32446Tim14_set_apre(uint8_t bool);
void STM32446Tim14_set_opm(uint8_t bool);
void STM32446Tim14_set_urs(uint8_t bool);
void STM32446Tim14_set_udis(uint8_t bool);
void STM32446Tim14_cen(uint8_t bool);
// DIER
void STM32446Tim14_tie(uint8_t bool);
void STM32446Tim14_cc2ie(uint8_t bool);
void STM32446Tim14_cc1ie(uint8_t bool);
void STM32446Tim14_uie(uint8_t bool);
// SR
uint8_t STM32446Tim14_cc2of(void);
void STM32446Tim14_clear_cc2of(void);
uint8_t STM32446Tim14_cc1of(void);
void STM32446Tim14_clear_cc1of(void);
uint8_t STM32446Tim14_tif(void);
void STM32446Tim14_clear_tif(void);
uint8_t STM32446Tim14_cc2if(void);
void STM32446Tim14_clear_cc2if(void);
uint8_t STM32446Tim14_cc1if(void);
void STM32446Tim14_clear_cc1if(void);
uint8_t STM32446Tim14_uif(void);
void STM32446Tim14_clear_uif(void);
// EGR
void STM32446Tim14_tg(void);
void STM32446Tim14_cc2g(void);
void STM32446Tim14_cc1g(void);
void STM32446Tim14_ug(void);
// CCMR1
void STM32446Tim14_oc2m(uint8_t value);
void STM32446Tim14_ic2f(uint8_t value);
void STM32446Tim14_oc2pe(uint8_t bool);
void STM32446Tim14_oc2fe(uint8_t bool);
void STM32446Tim14_ic2psc(uint8_t value);
void STM32446Tim14_cc2s(uint8_t value);
void STM32446Tim14_oc1m(uint8_t value);
void STM32446Tim14_ic1f(uint8_t value);
void STM32446Tim14_oc1pe(uint8_t bool);
void STM32446Tim14_oc1fe(uint8_t bool);
void STM32446Tim14_ic1psc(uint8_t value);
void STM32446Tim14_cc1s(uint8_t value);
// CCER
void STM32446Tim14_cc2np(uint8_t bool);
void STM32446Tim14_cc2p(uint8_t bool);
void STM32446Tim14_cc2e(uint8_t bool);
void STM32446Tim14_cc1np(uint8_t bool);
void STM32446Tim14_cc1p(uint8_t bool);
void STM32446Tim14_cc1e(uint8_t bool);
// CNT
void STM32446Tim14_cnt(uint16_t value);
uint16_t STM32446Tim14_get_cnt(void);
// PSC
void STM32446Tim14_psc(uint16_t value);
// ARR
void STM32446Tim14_arr(uint16_t value);
// CCR1
void STM32446Tim14_ccr1(uint16_t value);
// OR
void STM32446Tim14_or(uint8_t value);

/*** INTERRUPT HEADER ***/
void TIM1_BRK_TIM9_IRQHandler(void);
void TIM1_UP_TIM10_IRQHandler(void);
void TIM1_TRG_COM_TIM11_IRQHandler(void);
void TIM8_BRK_TIM12_IRQHandler(void);
void TIM8_UP_TIM13_IRQHandler(void);
void TIM8_TRG_COM_TIM14_IRQHandler(void);

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


