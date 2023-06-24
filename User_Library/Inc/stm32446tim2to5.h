/******************************************************************************
	STM32 446 TIM 2 to 5
Author: Sergio Santos 
	<sergio.salazar.santos@gmail.com>
License: GNU General Public License
Hardware: STM32-446
Date: 22062023
Comment:
	
*******************************************************************************/
#ifndef _STM32446TIM2TO5_H_
	#define _STM32446TIM2TO5_H_
/*** Library ***/
#include <inttypes.h>
/*** TIMER 2 to 5 Bit Mapping TypeDef ***/
// CR1
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
}STM32446TIM2_CR1, STM32446TIM3_CR1, STM32446TIM4_CR1, STM32446TIM5_CR1;
// CR2
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
}STM32446TIM2_CR2, STM32446TIM3_CR2, STM32446TIM4_CR2, STM32446TIM5_CR2;
// SMCR
typedef struct{
	void (*etp)(uint8_t bool);
	void (*ece)(uint8_t bool);
	void (*etps)(uint8_t value);
	void (*etf)(uint8_t value);
	void (*msm)(uint8_t bool);
	void (*ts)(uint8_t value);
	void (*sms)(uint8_t value);
}STM32446TIM2_SMCR, STM32446TIM3_SMCR, STM32446TIM4_SMCR, STM32446TIM5_SMCR;
// DIER
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
}STM32446TIM2_DIER, STM32446TIM3_DIER, STM32446TIM4_DIER, STM32446TIM5_DIER;
// SR
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
}STM32446TIM2_SR, STM32446TIM3_SR, STM32446TIM4_SR, STM32446TIM5_SR;
// EGR
typedef struct{
	void (*bg)(void);
	void (*tg)(void);
	void (*comg)(void);
	void (*cc4g)(void);
	void (*cc3g)(void);
	void (*cc2g)(void);
	void (*cc1g)(void);
	void (*ug)(void);
}STM32446TIM2_EGR, STM32446TIM3_EGR, STM32446TIM4_EGR, STM32446TIM5_EGR;
// CCMR1
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
}STM32446TIM2_CCMR1, STM32446TIM3_CCMR1, STM32446TIM4_CCMR1, STM32446TIM5_CCMR1;
// CCMR2
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
}STM32446TIM2_CCMR2, STM32446TIM3_CCMR2, STM32446TIM4_CCMR2, STM32446TIM5_CCMR2;
// CCER
typedef struct{
	void (*cc4np)(uint8_t bool);
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
}STM32446TIM2_CCER, STM32446TIM3_CCER, STM32446TIM4_CCER, STM32446TIM5_CCER;
// BDTR
typedef struct{
	void (*moe)(uint8_t bool);
	void (*aoe)(uint8_t bool);
	void (*bkp)(uint8_t bool);
	void (*bke)(uint8_t bool);
	void (*ossr)(uint8_t bool);
	void (*ossi)(uint8_t bool);
	void (*lock)(uint8_t value);
	void (*dtg)(uint8_t value);
}STM32446TIM2_BDTR, STM32446TIM3_BDTR, STM32446TIM4_BDTR, STM32446TIM5_BDTR;
// DCR
typedef struct{
	void (*dbl)(uint8_t value);
	void (*dba)(uint8_t value);
}STM32446TIM2_DCR, STM32446TIM3_DCR, STM32446TIM4_DCR, STM32446TIM5_DCR;
/*** TIMER 2 to 5 TypeDef ***/
// ( 2 and 5 ) TIM
typedef struct
{
	TIM_TypeDef* reg;
	/*** Bit Mapping ***/
	STM32446TIM2_CR1 cr1;
	STM32446TIM2_CR2 cr2;
	STM32446TIM2_SMCR smcr;
	STM32446TIM2_DIER dier;
	STM32446TIM2_SR sr;
	STM32446TIM2_EGR egr;
	STM32446TIM2_CCMR1 ccmr1;
	STM32446TIM2_CCMR2 ccmr2;
	STM32446TIM2_CCER ccer;
	STM32446TIM2_DCR dcr;
	void (*cnt)(uint32_t value);
	uint32_t (*get_cnt)(void);
	void (*psc)(uint16_t value);
	void (*arr)(uint32_t value);
	void (*ccr1)(uint32_t value);
	void (*ccr2)(uint32_t value);
	void (*ccr3)(uint32_t value);
	void (*ccr4)(uint32_t value);
	void (*dmar)(uint16_t value);
	void (*or)(uint8_t value);
	/*** Other ***/
	void (*clock)(uint8_t bool);
	void (*nvic)(uint8_t bool);
}STM32446TIM2obj, STM32446TIM5obj;
// ( 3 and 4 ) TIM
typedef struct
{
	TIM_TypeDef* reg;
	/*** Bit Mapping ***/
	STM32446TIM3_CR1 cr1;
	STM32446TIM3_CR2 cr2;
	STM32446TIM3_SMCR smcr;
	STM32446TIM3_DIER dier;
	STM32446TIM3_SR sr;
	STM32446TIM3_EGR egr;
	STM32446TIM3_CCMR1 ccmr1;
	STM32446TIM3_CCMR2 ccmr2;
	STM32446TIM3_CCER ccer;
	STM32446TIM3_DCR dcr;
	void (*cnt)(uint16_t value);
	uint16_t (*get_cnt)(void);
	void (*psc)(uint16_t value);
	void (*arr)(uint16_t value);
	void (*ccr1)(uint16_t value);
	void (*ccr2)(uint16_t value);
	void (*ccr3)(uint16_t value);
	void (*ccr4)(uint16_t value);
	void (*dmar)(uint16_t value);
	/*** Other ***/
	void (*clock)(uint8_t bool);
	void (*nvic)(uint8_t bool);
}STM32446TIM3obj, STM32446TIM4obj;
/***********************/
/*** INIC TIM 2 to 5 ***/
/***********************/
STM32446TIM2obj tim2_inic(void);
STM32446TIM3obj tim3_inic(void);
STM32446TIM3obj tim4_inic(void);
STM32446TIM5obj tim5_inic(void);
/****************************************/
/*** TIM2 Procedure & Function Header ***/
/****************************************/
void STM32446Tim2Clock(uint8_t bool);
void STM32446Tim2Nvic(uint8_t bool);
/*** TIM2 Bit Mapping Header ***/
// CR1
void STM32446Tim2_ckd(uint8_t value);
uint8_t STM32446Tim2_get_ckd(void);
void STM32446Tim2_set_apre(uint8_t bool);
void STM32446Tim2_set_cms(uint8_t value);
void STM32446Tim2_set_dir(uint8_t bool);
void STM32446Tim2_set_opm(uint8_t bool);
void STM32446Tim2_set_urs(uint8_t bool);
void STM32446Tim2_set_udis(uint8_t bool);
void STM32446Tim2_cen(uint8_t bool);
// CR2
void STM32446Tim2_ti1s(uint8_t bool);
void STM32446Tim2_mms(uint8_t value);
void STM32446Tim2_ccds(uint8_t bool);
// SMCR
void STM32446Tim2_etp(uint8_t bool);
void STM32446Tim2_ece(uint8_t bool);
void STM32446Tim2_etps(uint8_t value);
void STM32446Tim2_etf(uint8_t value);
void STM32446Tim2_msm(uint8_t bool);
void STM32446Tim2_ts(uint8_t value);
void STM32446Tim2_sms(uint8_t value);
// DIER
void STM32446Tim2_tde(uint8_t bool);
void STM32446Tim2_cc4de(uint8_t bool);
void STM32446Tim2_cc3de(uint8_t bool);
void STM32446Tim2_cc2de(uint8_t bool);
void STM32446Tim2_cc1de(uint8_t bool);
void STM32446Tim2_ude(uint8_t bool);
void STM32446Tim2_tie(uint8_t bool);
void STM32446Tim2_cc4ie(uint8_t bool);
void STM32446Tim2_cc3ie(uint8_t bool);
void STM32446Tim2_cc2ie(uint8_t bool);
void STM32446Tim2_cc1ie(uint8_t bool);
void STM32446Tim2_uie(uint8_t bool);
// SR
uint8_t STM32446Tim2_cc4of(void);
void STM32446Tim2_clear_cc4of(void);
uint8_t STM32446Tim2_cc3of(void);
void STM32446Tim2_clear_cc3of(void);
uint8_t STM32446Tim2_cc2of(void);
void STM32446Tim2_clear_cc2of(void);
uint8_t STM32446Tim2_cc1of(void);
void STM32446Tim2_clear_cc1of(void);
uint8_t STM32446Tim2_tif(void);
void STM32446Tim2_clear_tif(void);
uint8_t STM32446Tim2_cc4if(void);
void STM32446Tim2_clear_cc4if(void);
uint8_t STM32446Tim2_cc3if(void);
void STM32446Tim2_clear_cc3if(void);
uint8_t STM32446Tim2_cc2if(void);
void STM32446Tim2_clear_cc2if(void);
uint8_t STM32446Tim2_cc1if(void);
void STM32446Tim2_clear_cc1if(void);
uint8_t STM32446Tim2_uif(void);
void STM32446Tim2_clear_uif(void);
// EGR
void STM32446Tim2_tg(void);
void STM32446Tim2_cc4g(void);
void STM32446Tim2_cc3g(void);
void STM32446Tim2_cc2g(void);
void STM32446Tim2_cc1g(void);
void STM32446Tim2_ug(void);
// CCMR1
void STM32446Tim2_oc2ce(uint8_t value);
void STM32446Tim2_oc2m(uint8_t value);
void STM32446Tim2_ic2f(uint8_t value);
void STM32446Tim2_oc2pe(uint8_t bool);
void STM32446Tim2_oc2fe(uint8_t bool);
void STM32446Tim2_ic2psc(uint8_t value);
void STM32446Tim2_cc2s(uint8_t value);
void STM32446Tim2_oc1ce(uint8_t value);
void STM32446Tim2_oc1m(uint8_t value);
void STM32446Tim2_ic1f(uint8_t value);
void STM32446Tim2_oc1pe(uint8_t bool);
void STM32446Tim2_oc1fe(uint8_t bool);
void STM32446Tim2_ic1psc(uint8_t value);
void STM32446Tim2_cc1s(uint8_t value);
// CCMR2
void STM32446Tim2_oc4ce(uint8_t value);
void STM32446Tim2_oc4m(uint8_t value);
void STM32446Tim2_ic4f(uint8_t value);
void STM32446Tim2_oc4pe(uint8_t bool);
void STM32446Tim2_oc4fe(uint8_t bool);
void STM32446Tim2_ic4psc(uint8_t value);
void STM32446Tim2_cc4s(uint8_t value);
void STM32446Tim2_oc3ce(uint8_t value);
void STM32446Tim2_oc3m(uint8_t value);
void STM32446Tim2_ic3f(uint8_t value);
void STM32446Tim2_oc3pe(uint8_t bool);
void STM32446Tim2_oc3fe(uint8_t bool);
void STM32446Tim2_ic3psc(uint8_t value);
void STM32446Tim2_cc3s(uint8_t value);
// CCER
void STM32446Tim2_cc4np(uint8_t bool);
void STM32446Tim2_cc4p(uint8_t bool);
void STM32446Tim2_cc4e(uint8_t bool);
void STM32446Tim2_cc3np(uint8_t bool);
void STM32446Tim2_cc3p(uint8_t bool);
void STM32446Tim2_cc3e(uint8_t bool);
void STM32446Tim2_cc2np(uint8_t bool);
void STM32446Tim2_cc2p(uint8_t bool);
void STM32446Tim2_cc2e(uint8_t bool);
void STM32446Tim2_cc1np(uint8_t bool);
void STM32446Tim2_cc1p(uint8_t bool);
void STM32446Tim2_cc1e(uint8_t bool);
// CNT
void STM32446Tim2_cnt(uint32_t value);
uint32_t STM32446Tim2_get_cnt(void);
// PSC
void STM32446Tim2_psc(uint16_t value);
// ARR
void STM32446Tim2_arr(uint32_t value);
// CCR1
void STM32446Tim2_ccr1(uint32_t value);
// CCR2
void STM32446Tim2_ccr2(uint32_t value);
// CCR3
void STM32446Tim2_ccr3(uint32_t value);
// CCR4
void STM32446Tim2_ccr4(uint32_t value);
// DCR
void STM32446Tim2_dbl(uint8_t value);
void STM32446Tim2_dba(uint8_t value);
// DMAR
void STM32446Tim2_dmab(uint16_t value);
uint16_t STM32446Tim2_get_dmab(void);
// OR
void STM32446Tim2_itr1_rmp(uint8_t value);
/****************************************/
/*** TIM3 Procedure & Function Header ***/
/****************************************/
void STM32446Tim3Clock(uint8_t bool);
void STM32446Tim3Nvic(uint8_t bool);
/*** TIM3 Bit Mapping Header ***/
// CR1
void STM32446Tim3_ckd(uint8_t value);
uint8_t STM32446Tim3_get_ckd(void);
void STM32446Tim3_set_apre(uint8_t bool);
void STM32446Tim3_set_cms(uint8_t value);
void STM32446Tim3_set_dir(uint8_t bool);
void STM32446Tim3_set_opm(uint8_t bool);
void STM32446Tim3_set_urs(uint8_t bool);
void STM32446Tim3_set_udis(uint8_t bool);
void STM32446Tim3_cen(uint8_t bool);
// CR2
void STM32446Tim3_ti1s(uint8_t bool);
void STM32446Tim3_mms(uint8_t value);
void STM32446Tim3_ccds(uint8_t bool);
// SMCR
void STM32446Tim3_etp(uint8_t bool);
void STM32446Tim3_ece(uint8_t bool);
void STM32446Tim3_etps(uint8_t value);
void STM32446Tim5_etf(uint8_t value);
void STM32446Tim3_msm(uint8_t bool);
void STM32446Tim3_ts(uint8_t value);
void STM32446Tim3_sms(uint8_t value);
// DIER
void STM32446Tim3_tde(uint8_t bool);
void STM32446Tim3_cc4de(uint8_t bool);
void STM32446Tim3_cc3de(uint8_t bool);
void STM32446Tim3_cc2de(uint8_t bool);
void STM32446Tim3_cc1de(uint8_t bool);
void STM32446Tim3_ude(uint8_t bool);
void STM32446Tim3_tie(uint8_t bool);
void STM32446Tim3_cc4ie(uint8_t bool);
void STM32446Tim3_cc3ie(uint8_t bool);
void STM32446Tim3_cc2ie(uint8_t bool);
void STM32446Tim3_cc1ie(uint8_t bool);
void STM32446Tim3_uie(uint8_t bool);
// SR
uint8_t STM32446Tim3_cc4of(void);
void STM32446Tim3_clear_cc4of(void);
uint8_t STM32446Tim3_cc3of(void);
void STM32446Tim3_clear_cc3of(void);
uint8_t STM32446Tim3_cc2of(void);
void STM32446Tim3_clear_cc2of(void);
uint8_t STM32446Tim3_cc1of(void);
void STM32446Tim3_clear_cc1of(void);
uint8_t STM32446Tim3_tif(void);
void STM32446Tim3_clear_tif(void);
uint8_t STM32446Tim3_cc4if(void);
void STM32446Tim3_clear_cc4if(void);
uint8_t STM32446Tim3_cc3if(void);
void STM32446Tim3_clear_cc3if(void);
uint8_t STM32446Tim3_cc2if(void);
void STM32446Tim3_clear_cc2if(void);
uint8_t STM32446Tim3_cc1if(void);
void STM32446Tim3_clear_cc1if(void);
uint8_t STM32446Tim3_uif(void);
void STM32446Tim3_clear_uif(void);
// EGR
void STM32446Tim3_tg(void);
void STM32446Tim3_cc4g(void);
void STM32446Tim3_cc3g(void);
void STM32446Tim3_cc2g(void);
void STM32446Tim3_cc1g(void);
void STM32446Tim3_ug(void);
// CCMR1
void STM32446Tim3_oc2ce(uint8_t value);
void STM32446Tim3_oc2m(uint8_t value);
void STM32446Tim3_ic2f(uint8_t value);
void STM32446Tim3_oc2pe(uint8_t bool);
void STM32446Tim3_oc2fe(uint8_t bool);
void STM32446Tim3_ic2psc(uint8_t value);
void STM32446Tim3_cc2s(uint8_t value);
void STM32446Tim3_oc1ce(uint8_t value);
void STM32446Tim3_oc1m(uint8_t value);
void STM32446Tim3_ic1f(uint8_t value);
void STM32446Tim3_oc1pe(uint8_t bool);
void STM32446Tim3_oc1fe(uint8_t bool);
void STM32446Tim3_ic1psc(uint8_t value);
void STM32446Tim3_cc1s(uint8_t value);
// CCMR2
void STM32446Tim3_oc4ce(uint8_t value);
void STM32446Tim3_oc4m(uint8_t value);
void STM32446Tim3_ic4f(uint8_t value);
void STM32446Tim3_oc4pe(uint8_t bool);
void STM32446Tim3_oc4fe(uint8_t bool);
void STM32446Tim3_ic4psc(uint8_t value);
void STM32446Tim3_cc4s(uint8_t value);
void STM32446Tim3_oc3ce(uint8_t value);
void STM32446Tim3_oc3m(uint8_t value);
void STM32446Tim3_ic3f(uint8_t value);
void STM32446Tim3_oc3pe(uint8_t bool);
void STM32446Tim3_oc3fe(uint8_t bool);
void STM32446Tim3_ic3psc(uint8_t value);
void STM32446Tim3_cc3s(uint8_t value);
// CCER
void STM32446Tim3_cc4np(uint8_t bool);
void STM32446Tim3_cc4p(uint8_t bool);
void STM32446Tim3_cc4e(uint8_t bool);
void STM32446Tim3_cc3np(uint8_t bool);
void STM32446Tim3_cc3p(uint8_t bool);
void STM32446Tim3_cc3e(uint8_t bool);
void STM32446Tim3_cc2np(uint8_t bool);
void STM32446Tim3_cc2p(uint8_t bool);
void STM32446Tim3_cc2e(uint8_t bool);
void STM32446Tim3_cc1np(uint8_t bool);
void STM32446Tim3_cc1p(uint8_t bool);
void STM32446Tim3_cc1e(uint8_t bool);
// CNT
void STM32446Tim3_cnt(uint16_t value);
uint16_t STM32446Tim3_get_cnt(void);
// PSC
void STM32446Tim3_psc(uint16_t value);
// ARR
void STM32446Tim3_arr(uint16_t value);
// CCR1
void STM32446Tim3_ccr1(uint16_t value);
// CCR2
void STM32446Tim3_ccr2(uint16_t value);
// CCR3
void STM32446Tim3_ccr3(uint16_t value);
// CCR4
void STM32446Tim3_ccr4(uint16_t value);
// DCR
void STM32446Tim3_dbl(uint8_t value);
void STM32446Tim3_dba(uint8_t value);
// DMAR
void STM32446Tim3_dmab(uint16_t value);
uint16_t STM32446Tim3_get_dmab(void);
/****************************************/
/*** TIM4 Procedure & Function Header ***/
/****************************************/
void STM32446Tim4Clock(uint8_t bool);
void STM32446Tim4Nvic(uint8_t bool);
/*** TIM4 Bit Mapping Header ***/
// CR1
void STM32446Tim4_ckd(uint8_t value);
uint8_t STM32446Tim4_get_ckd(void);
void STM32446Tim4_set_apre(uint8_t bool);
void STM32446Tim4_set_cms(uint8_t value);
void STM32446Tim4_set_dir(uint8_t bool);
void STM32446Tim4_set_opm(uint8_t bool);
void STM32446Tim4_set_urs(uint8_t bool);
void STM32446Tim4_set_udis(uint8_t bool);
void STM32446Tim4_cen(uint8_t bool);
// CR2
void STM32446Tim4_ti1s(uint8_t bool);
void STM32446Tim4_mms(uint8_t value);
void STM32446Tim4_ccds(uint8_t bool);
// SMCR
void STM32446Tim4_etp(uint8_t bool);
void STM32446Tim4_ece(uint8_t bool);
void STM32446Tim4_etps(uint8_t value);
void STM32446Tim5_etf(uint8_t value);
void STM32446Tim4_msm(uint8_t bool);
void STM32446Tim4_ts(uint8_t value);
void STM32446Tim4_sms(uint8_t value);
// DIER
void STM32446Tim4_tde(uint8_t bool);
void STM32446Tim4_cc4de(uint8_t bool);
void STM32446Tim4_cc3de(uint8_t bool);
void STM32446Tim4_cc2de(uint8_t bool);
void STM32446Tim4_cc1de(uint8_t bool);
void STM32446Tim4_ude(uint8_t bool);
void STM32446Tim4_tie(uint8_t bool);
void STM32446Tim4_cc4ie(uint8_t bool);
void STM32446Tim4_cc3ie(uint8_t bool);
void STM32446Tim4_cc2ie(uint8_t bool);
void STM32446Tim4_cc1ie(uint8_t bool);
void STM32446Tim4_uie(uint8_t bool);
// SR
uint8_t STM32446Tim4_cc4of(void);
void STM32446Tim4_clear_cc4of(void);
uint8_t STM32446Tim4_cc3of(void);
void STM32446Tim4_clear_cc3of(void);
uint8_t STM32446Tim4_cc2of(void);
void STM32446Tim4_clear_cc2of(void);
uint8_t STM32446Tim4_cc1of(void);
void STM32446Tim4_clear_cc1of(void);
uint8_t STM32446Tim4_tif(void);
void STM32446Tim4_clear_tif(void);
uint8_t STM32446Tim4_cc4if(void);
void STM32446Tim4_clear_cc4if(void);
uint8_t STM32446Tim4_cc3if(void);
void STM32446Tim4_clear_cc3if(void);
uint8_t STM32446Tim4_cc2if(void);
void STM32446Tim4_clear_cc2if(void);
uint8_t STM32446Tim4_cc1if(void);
void STM32446Tim4_clear_cc1if(void);
uint8_t STM32446Tim4_uif(void);
void STM32446Tim4_clear_uif(void);
// EGR
void STM32446Tim4_tg(void);
void STM32446Tim4_cc4g(void);
void STM32446Tim4_cc3g(void);
void STM32446Tim4_cc2g(void);
void STM32446Tim4_cc1g(void);
void STM32446Tim4_ug(void);
// CCMR1
void STM32446Tim4_oc2ce(uint8_t value);
void STM32446Tim4_oc2m(uint8_t value);
void STM32446Tim4_ic2f(uint8_t value);
void STM32446Tim4_oc2pe(uint8_t bool);
void STM32446Tim4_oc2fe(uint8_t bool);
void STM32446Tim4_ic2psc(uint8_t value);
void STM32446Tim4_cc2s(uint8_t value);
void STM32446Tim4_oc1ce(uint8_t value);
void STM32446Tim4_oc1m(uint8_t value);
void STM32446Tim4_ic1f(uint8_t value);
void STM32446Tim4_oc1pe(uint8_t bool);
void STM32446Tim4_oc1fe(uint8_t bool);
void STM32446Tim4_ic1psc(uint8_t value);
void STM32446Tim4_cc1s(uint8_t value);
// CCMR2
void STM32446Tim4_oc4ce(uint8_t value);
void STM32446Tim4_oc4m(uint8_t value);
void STM32446Tim4_ic4f(uint8_t value);
void STM32446Tim4_oc4pe(uint8_t bool);
void STM32446Tim4_oc4fe(uint8_t bool);
void STM32446Tim4_ic4psc(uint8_t value);
void STM32446Tim4_cc4s(uint8_t value);
void STM32446Tim4_oc3ce(uint8_t value);
void STM32446Tim4_oc3m(uint8_t value);
void STM32446Tim4_ic3f(uint8_t value);
void STM32446Tim4_oc3pe(uint8_t bool);
void STM32446Tim4_oc3fe(uint8_t bool);
void STM32446Tim4_ic3psc(uint8_t value);
void STM32446Tim4_cc3s(uint8_t value);
// CCER
void STM32446Tim4_cc4np(uint8_t bool);
void STM32446Tim4_cc4p(uint8_t bool);
void STM32446Tim4_cc4e(uint8_t bool);
void STM32446Tim4_cc3np(uint8_t bool);
void STM32446Tim4_cc3p(uint8_t bool);
void STM32446Tim4_cc3e(uint8_t bool);
void STM32446Tim4_cc2np(uint8_t bool);
void STM32446Tim4_cc2p(uint8_t bool);
void STM32446Tim4_cc2e(uint8_t bool);
void STM32446Tim4_cc1np(uint8_t bool);
void STM32446Tim4_cc1p(uint8_t bool);
void STM32446Tim4_cc1e(uint8_t bool);
// CNT
void STM32446Tim4_cnt(uint16_t value);
uint16_t STM32446Tim4_get_cnt(void);
// PSC
void STM32446Tim4_psc(uint16_t value);
// ARR
void STM32446Tim4_arr(uint16_t value);
// CCR1
void STM32446Tim4_ccr1(uint16_t value);
// CCR2
void STM32446Tim4_ccr2(uint16_t value);
// CCR3
void STM32446Tim4_ccr3(uint16_t value);
// CCR4
void STM32446Tim4_ccr4(uint16_t value);
// DCR
void STM32446Tim4_dbl(uint8_t value);
void STM32446Tim4_dba(uint8_t value);
// DMAR
void STM32446Tim4_dmab(uint16_t value);
uint16_t STM32446Tim4_get_dmab(void);
/****************************************/
/*** TIM5 Procedure & Function Header ***/
/****************************************/
void STM32446Tim5Clock(uint8_t bool);
void STM32446Tim5Nvic(uint8_t bool);
/*** TIM5 Bit Mapping Header ***/
// CR1
void STM32446Tim5_ckd(uint8_t value);
uint8_t STM32446Tim5_get_ckd(void);
void STM32446Tim5_set_apre(uint8_t bool);
void STM32446Tim5_set_cms(uint8_t value);
void STM32446Tim5_set_dir(uint8_t bool);
void STM32446Tim5_set_opm(uint8_t bool);
void STM32446Tim5_set_urs(uint8_t bool);
void STM32446Tim5_set_udis(uint8_t bool);
void STM32446Tim5_cen(uint8_t bool);
// CR2
void STM32446Tim5_ti1s(uint8_t bool);
void STM32446Tim5_mms(uint8_t value);
void STM32446Tim5_ccds(uint8_t bool);
// SMCR
void STM32446Tim5_etp(uint8_t bool);
void STM32446Tim5_ece(uint8_t bool);
void STM32446Tim5_etps(uint8_t value);
void STM32446Tim5_etf(uint8_t value);
void STM32446Tim5_msm(uint8_t bool);
void STM32446Tim5_ts(uint8_t value);
void STM32446Tim5_sms(uint8_t value);
// DIER
void STM32446Tim5_tde(uint8_t bool);
void STM32446Tim5_cc4de(uint8_t bool);
void STM32446Tim5_cc3de(uint8_t bool);
void STM32446Tim5_cc2de(uint8_t bool);
void STM32446Tim5_cc1de(uint8_t bool);
void STM32446Tim5_ude(uint8_t bool);
void STM32446Tim5_tie(uint8_t bool);
void STM32446Tim5_cc4ie(uint8_t bool);
void STM32446Tim5_cc3ie(uint8_t bool);
void STM32446Tim5_cc2ie(uint8_t bool);
void STM32446Tim5_cc1ie(uint8_t bool);
void STM32446Tim5_uie(uint8_t bool);
// SR
uint8_t STM32446Tim5_cc4of(void);
void STM32446Tim5_clear_cc4of(void);
uint8_t STM32446Tim5_cc3of(void);
void STM32446Tim5_clear_cc3of(void);
uint8_t STM32446Tim5_cc2of(void);
void STM32446Tim5_clear_cc2of(void);
uint8_t STM32446Tim5_cc1of(void);
void STM32446Tim5_clear_cc1of(void);
uint8_t STM32446Tim5_tif(void);
void STM32446Tim5_clear_tif(void);
uint8_t STM32446Tim5_cc4if(void);
void STM32446Tim5_clear_cc4if(void);
uint8_t STM32446Tim5_cc3if(void);
void STM32446Tim5_clear_cc3if(void);
uint8_t STM32446Tim5_cc2if(void);
void STM32446Tim5_clear_cc2if(void);
uint8_t STM32446Tim5_cc1if(void);
void STM32446Tim5_clear_cc1if(void);
uint8_t STM32446Tim5_uif(void);
void STM32446Tim5_clear_uif(void);
// EGR
void STM32446Tim5_tg(void);
void STM32446Tim5_cc4g(void);
void STM32446Tim5_cc3g(void);
void STM32446Tim5_cc2g(void);
void STM32446Tim5_cc1g(void);
void STM32446Tim5_ug(void);
// CCMR1
void STM32446Tim5_oc2ce(uint8_t value);
void STM32446Tim5_oc2m(uint8_t value);
void STM32446Tim5_ic2f(uint8_t value);
void STM32446Tim5_oc2pe(uint8_t bool);
void STM32446Tim5_oc2fe(uint8_t bool);
void STM32446Tim5_ic2psc(uint8_t value);
void STM32446Tim5_cc2s(uint8_t value);
void STM32446Tim5_oc1ce(uint8_t value);
void STM32446Tim5_oc1m(uint8_t value);
void STM32446Tim5_ic1f(uint8_t value);
void STM32446Tim5_oc1pe(uint8_t bool);
void STM32446Tim5_oc1fe(uint8_t bool);
void STM32446Tim5_ic1psc(uint8_t value);
void STM32446Tim5_cc1s(uint8_t value);
// CCMR2
void STM32446Tim5_oc4ce(uint8_t value);
void STM32446Tim5_oc4m(uint8_t value);
void STM32446Tim5_ic4f(uint8_t value);
void STM32446Tim5_oc4pe(uint8_t bool);
void STM32446Tim5_oc4fe(uint8_t bool);
void STM32446Tim5_ic4psc(uint8_t value);
void STM32446Tim5_cc4s(uint8_t value);
void STM32446Tim5_oc3ce(uint8_t value);
void STM32446Tim5_oc3m(uint8_t value);
void STM32446Tim5_ic3f(uint8_t value);
void STM32446Tim5_oc3pe(uint8_t bool);
void STM32446Tim5_oc3fe(uint8_t bool);
void STM32446Tim5_ic3psc(uint8_t value);
void STM32446Tim5_cc3s(uint8_t value);
// CCER
void STM32446Tim5_cc4np(uint8_t bool);
void STM32446Tim5_cc4p(uint8_t bool);
void STM32446Tim5_cc4e(uint8_t bool);
void STM32446Tim5_cc3np(uint8_t bool);
void STM32446Tim5_cc3p(uint8_t bool);
void STM32446Tim5_cc3e(uint8_t bool);
void STM32446Tim5_cc2np(uint8_t bool);
void STM32446Tim5_cc2p(uint8_t bool);
void STM32446Tim5_cc2e(uint8_t bool);
void STM32446Tim5_cc1np(uint8_t bool);
void STM32446Tim5_cc1p(uint8_t bool);
void STM32446Tim5_cc1e(uint8_t bool);
// CNT
void STM32446Tim5_cnt(uint32_t value);
uint32_t STM32446Tim5_get_cnt(void);
// PSC
void STM32446Tim5_psc(uint16_t value);
// ARR
void STM32446Tim5_arr(uint32_t value);
// CCR1
void STM32446Tim5_ccr1(uint32_t value);
// CCR2
void STM32446Tim5_ccr2(uint32_t value);
// CCR3
void STM32446Tim5_ccr3(uint32_t value);
// CCR4
void STM32446Tim5_ccr4(uint32_t value);
// DCR
void STM32446Tim5_dbl(uint8_t value);
void STM32446Tim5_dba(uint8_t value);
// DMAR
void STM32446Tim5_dmab(uint16_t value);
uint16_t STM32446Tim5_get_dmab(void);
// OR
void STM32446Tim5_ti4_rmp(uint8_t value);

/*** INTERRUPT HEADER ***/
void TIM2_IRQHandler(void);
void TIM3_IRQHandler(void);
void TIM4_IRQHandler(void);
void TIM5_IRQHandler(void);

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


