/******************************************************************************
	STM32 446 TIM 1 and 8
Author: Sergio Santos 
	<sergio.salazar.santos@gmail.com>
License: GNU General Public License
Hardware: STM32-446
Date: 22062023
Comment:
	
*******************************************************************************/
#ifndef _STM32446TIM1AND8_H_
	#define _STM32446TIM1AND8_H_
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
}STM32446TIM1_CR1, STM32446TIM8_CR1;
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
}STM32446TIM1_CR2, STM32446TIM8_CR2;
typedef struct{
	void (*etp)(uint8_t bool);
	void (*ece)(uint8_t bool);
	void (*etps)(uint8_t value);
	void (*etf)(uint8_t value);
	void (*msm)(uint8_t bool);
	void (*ts)(uint8_t value);
	void (*sms)(uint8_t value);
}STM32446TIM1_SMCR, STM32446TIM8_SMCR;
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
}STM32446TIM1_DIER, STM32446TIM8_DIER;
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
}STM32446TIM1_SR, STM32446TIM8_SR;
typedef struct{
	void (*bg)(void);
	void (*tg)(void);
	void (*comg)(void);
	void (*cc4g)(void);
	void (*cc3g)(void);
	void (*cc2g)(void);
	void (*cc1g)(void);
	void (*ug)(void);
}STM32446TIM1_EGR, STM32446TIM8_EGR;
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
}STM32446TIM1_CCMR1, STM32446TIM8_CCMR1;
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
}STM32446TIM1_CCMR2, STM32446TIM8_CCMR2;
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
}STM32446TIM1_CCER, STM32446TIM8_CCER;
typedef struct{
	void (*moe)(uint8_t bool);
	void (*aoe)(uint8_t bool);
	void (*bkp)(uint8_t bool);
	void (*bke)(uint8_t bool);
	void (*ossr)(uint8_t bool);
	void (*ossi)(uint8_t bool);
	void (*lock)(uint8_t value);
	void (*dtg)(uint8_t value);
}STM32446TIM1_BDTR, STM32446TIM8_BDTR;
typedef struct{
	void (*dbl)(uint8_t value);
	void (*dba)(uint8_t value);
}STM32446TIM1_DCR, STM32446TIM8_DCR;
/*** TIMER TypeDef***/
// ( 1 and 8 ) TIM 
typedef struct
{
	TIM_TypeDef* reg;
	/*** Bit Mapping ***/
	STM32446TIM1_CR1 cr1;
	STM32446TIM1_CR2 cr2;
	STM32446TIM1_SMCR smcr;
	STM32446TIM1_DIER dier;
	STM32446TIM1_SR sr;
	STM32446TIM1_EGR egr;
	STM32446TIM1_CCMR1 ccmr1;
	STM32446TIM1_CCMR2 ccmr2;
	STM32446TIM1_CCER ccer;
	void (*cnt)(uint16_t value);
	uint16_t (*get_cnt)(void);
	void (*psc)(uint16_t value);
	void (*arr)(uint16_t value);
	void (*rep)(uint8_t value);
	void (*ccr1)(uint16_t value);
	void (*ccr2)(uint16_t value);
	void (*ccr3)(uint16_t value);
	void (*ccr4)(uint16_t value);
	STM32446TIM1_BDTR bdtr;
	STM32446TIM1_DCR dcr;
	void (*dmar)(uint16_t value);
	/*** Other ***/
	void (*clock)(uint8_t bool);
	void (*nvic)(uint8_t value);
}STM32446TIM1obj, STM32446TIM8obj;
/*******************/
/*** INIC 1 and 8 ***/
/*******************/
STM32446TIM1obj tim1_inic(void);
STM32446TIM8obj tim8_inic(void);
/****************************************/
/*** TIM1 Procedure & Function Header ***/
/****************************************/
void STM32446Tim1Clock(uint8_t bool);
void STM32446Tim1Nvic(uint8_t value);
/*** TIM1 Bit Mapping Header ***/
// CR1
uint8_t STM32446Tim1_get_ckd(void);
void STM32446Tim1_set_apre(uint8_t bool);
void STM32446Tim1_set_cms(uint8_t value);
void STM32446Tim1_set_dir(uint8_t bool);
void STM32446Tim1_set_opm(uint8_t bool);
void STM32446Tim1_set_urs(uint8_t bool);
void STM32446Tim1_set_udis(uint8_t bool);
void STM32446Tim1_cen(uint8_t bool);
// CR2
void STM32446Tim1_ti1s(uint8_t bool);
void STM32446Tim1_mms(uint8_t value);
void STM32446Tim1_ccds(uint8_t bool);
// SMCR
void STM32446Tim1_etp(uint8_t bool);
void STM32446Tim1_ece(uint8_t bool);
void STM32446Tim1_etps(uint8_t value);
void STM32446Tim1_etf(uint8_t value);
void STM32446Tim1_msm(uint8_t bool);
void STM32446Tim1_ts(uint8_t value);
void STM32446Tim1_sms(uint8_t value);
// DIER
void STM32446Tim1_tde(uint8_t bool);
void STM32446Tim1_cc4de(uint8_t bool);
void STM32446Tim1_cc3de(uint8_t bool);
void STM32446Tim1_cc2de(uint8_t bool);
void STM32446Tim1_cc1de(uint8_t bool);
void STM32446Tim1_ude(uint8_t bool);
void STM32446Tim1_tie(uint8_t bool);
void STM32446Tim1_cc4ie(uint8_t bool);
void STM32446Tim1_cc3ie(uint8_t bool);
void STM32446Tim1_cc2ie(uint8_t bool);
void STM32446Tim1_cc1ie(uint8_t bool);
void STM32446Tim1_uie(uint8_t bool);
// SR
uint8_t STM32446Tim1_cc4of(void);
void STM32446Tim1_clear_cc4of(void);
uint8_t STM32446Tim1_cc3of(void);
void STM32446Tim1_clear_cc3of(void);
uint8_t STM32446Tim1_cc2of(void);
void STM32446Tim1_clear_cc2of(void);
uint8_t STM32446Tim1_cc1of(void);
void STM32446Tim1_clear_cc1of(void);
uint8_t STM32446Tim1_tif(void);
void STM32446Tim1_clear_tif(void);
uint8_t STM32446Tim1_cc4if(void);
void STM32446Tim1_clear_cc4if(void);
uint8_t STM32446Tim1_cc3if(void);
void STM32446Tim1_clear_cc3if(void);
uint8_t STM32446Tim1_cc2if(void);
void STM32446Tim1_clear_cc2if(void);
uint8_t STM32446Tim1_cc1if(void);
void STM32446Tim1_clear_cc1if(void);
uint8_t STM32446Tim1_uif(void);
void STM32446Tim1_clear_uif(void);
// EGR
void STM32446Tim1_tg(void);
void STM32446Tim1_cc4g(void);
void STM32446Tim1_cc3g(void);
void STM32446Tim1_cc2g(void);
void STM32446Tim1_cc1g(void);
void STM32446Tim1_ug(void);
// CCMR1
void STM32446Tim1_oc2ce(uint8_t value);
void STM32446Tim1_oc2m(uint8_t value);
void STM32446Tim1_ic2f(uint8_t value);
void STM32446Tim1_oc2pe(uint8_t bool);
void STM32446Tim1_oc2fe(uint8_t bool);
void STM32446Tim1_ic2psc(uint8_t value);
void STM32446Tim1_cc2s(uint8_t value);
void STM32446Tim1_oc1ce(uint8_t value);
void STM32446Tim1_oc1m(uint8_t value);
void STM32446Tim1_ic1f(uint8_t value);
void STM32446Tim1_oc1pe(uint8_t bool);
void STM32446Tim1_oc1fe(uint8_t bool);
void STM32446Tim1_ic1psc(uint8_t value);
void STM32446Tim1_cc1s(uint8_t value);
// CCMR2
void STM32446Tim1_oc4ce(uint8_t value);
void STM32446Tim1_oc4m(uint8_t value);
void STM32446Tim1_ic4f(uint8_t value);
void STM32446Tim1_oc4pe(uint8_t bool);
void STM32446Tim1_oc4fe(uint8_t bool);
void STM32446Tim1_ic4psc(uint8_t value);
void STM32446Tim1_cc4s(uint8_t value);
void STM32446Tim1_oc3ce(uint8_t value);
void STM32446Tim1_oc3m(uint8_t value);
void STM32446Tim1_ic3f(uint8_t value);
void STM32446Tim1_oc3pe(uint8_t bool);
void STM32446Tim1_oc3fe(uint8_t bool);
void STM32446Tim1_ic3psc(uint8_t value);
void STM32446Tim1_cc3s(uint8_t value);
// CCER
void STM32446Tim1_cc4np(uint8_t bool);
void STM32446Tim1_cc4p(uint8_t bool);
void STM32446Tim1_cc4e(uint8_t bool);
void STM32446Tim1_cc3np(uint8_t bool);
void STM32446Tim1_cc3p(uint8_t bool);
void STM32446Tim1_cc3e(uint8_t bool);
void STM32446Tim1_cc2np(uint8_t bool);
void STM32446Tim1_cc2p(uint8_t bool);
void STM32446Tim1_cc2e(uint8_t bool);
void STM32446Tim1_cc1np(uint8_t bool);
void STM32446Tim1_cc1p(uint8_t bool);
void STM32446Tim1_cc1e(uint8_t bool);
// CNT
void STM32446Tim1_cnt(uint16_t value);
uint16_t STM32446Tim1_get_cnt(void);
// PSC
void STM32446Tim1_psc(uint16_t value);
// ARR
void STM32446Tim1_arr(uint16_t value);
// CCR1
void STM32446Tim1_ccr1(uint16_t value);
// CCR2
void STM32446Tim1_ccr2(uint16_t value);
// CCR3
void STM32446Tim1_ccr3(uint16_t value);
// CCR4
void STM32446Tim1_ccr4(uint16_t value);
// DCR
void STM32446Tim1_dbl(uint8_t value);
void STM32446Tim1_dba(uint8_t value);
// DMAR
void STM32446Tim1_dmab(uint16_t value);
uint16_t STM32446Tim1_get_dmab(void);
// OR
void STM32446Tim1_itr1_rmp(uint8_t value);
/****************************************/
/*** TIM8 Procedure & Function Header ***/
/****************************************/
void STM32446Tim8Clock(uint8_t bool);
void STM32446Tim8Nvic(uint8_t value);
/*** TIM8 Bit Mapping Header ***/
// CR1
uint8_t STM32446Tim8_get_ckd(void);
void STM32446Tim8_set_apre(uint8_t bool);
void STM32446Tim8_set_cms(uint8_t value);
void STM32446Tim8_set_dir(uint8_t bool);
void STM32446Tim8_set_opm(uint8_t bool);
void STM32446Tim8_set_urs(uint8_t bool);
void STM32446Tim8_set_udis(uint8_t bool);
void STM32446Tim8_cen(uint8_t bool);
// CR2
void STM32446Tim8_ti1s(uint8_t bool);
void STM32446Tim8_mms(uint8_t value);
void STM32446Tim8_ccds(uint8_t bool);
// SMCR
void STM32446Tim8_etp(uint8_t bool);
void STM32446Tim8_ece(uint8_t bool);
void STM32446Tim8_etps(uint8_t value);
void STM32446Tim8_etf(uint8_t value);
void STM32446Tim8_msm(uint8_t bool);
void STM32446Tim8_ts(uint8_t value);
void STM32446Tim8_sms(uint8_t value);
// DIER
void STM32446Tim8_tde(uint8_t bool);
void STM32446Tim8_cc4de(uint8_t bool);
void STM32446Tim8_cc3de(uint8_t bool);
void STM32446Tim8_cc2de(uint8_t bool);
void STM32446Tim8_cc1de(uint8_t bool);
void STM32446Tim8_ude(uint8_t bool);
void STM32446Tim8_tie(uint8_t bool);
void STM32446Tim8_cc4ie(uint8_t bool);
void STM32446Tim8_cc3ie(uint8_t bool);
void STM32446Tim8_cc2ie(uint8_t bool);
void STM32446Tim8_cc1ie(uint8_t bool);
void STM32446Tim8_uie(uint8_t bool);
// SR
uint8_t STM32446Tim8_cc4of(void);
void STM32446Tim8_clear_cc4of(void);
uint8_t STM32446Tim8_cc3of(void);
void STM32446Tim8_clear_cc3of(void);
uint8_t STM32446Tim8_cc2of(void);
void STM32446Tim8_clear_cc2of(void);
uint8_t STM32446Tim8_cc1of(void);
void STM32446Tim8_clear_cc1of(void);
uint8_t STM32446Tim8_tif(void);
void STM32446Tim8_clear_tif(void);
uint8_t STM32446Tim8_cc4if(void);
void STM32446Tim8_clear_cc4if(void);
uint8_t STM32446Tim8_cc3if(void);
void STM32446Tim8_clear_cc3if(void);
uint8_t STM32446Tim8_cc2if(void);
void STM32446Tim8_clear_cc2if(void);
uint8_t STM32446Tim8_cc1if(void);
void STM32446Tim8_clear_cc1if(void);
uint8_t STM32446Tim8_uif(void);
void STM32446Tim8_clear_uif(void);
// EGR
void STM32446Tim8_tg(void);
void STM32446Tim8_cc4g(void);
void STM32446Tim8_cc3g(void);
void STM32446Tim5_cc2g(void);
void STM32446Tim8_cc1g(void);
void STM32446Tim8_ug(void);
// CCMR1
void STM32446Tim8_oc2ce(uint8_t value);
void STM32446Tim8_oc2m(uint8_t value);
void STM32446Tim8_ic2f(uint8_t value);
void STM32446Tim8_oc2pe(uint8_t bool);
void STM32446Tim8_oc2fe(uint8_t bool);
void STM32446Tim8_ic2psc(uint8_t value);
void STM32446Tim8_cc2s(uint8_t value);
void STM32446Tim8_oc1ce(uint8_t value);
void STM32446Tim8_oc1m(uint8_t value);
void STM32446Tim8_ic1f(uint8_t value);
void STM32446Tim8_oc1pe(uint8_t bool);
void STM32446Tim8_oc1fe(uint8_t bool);
void STM32446Tim8_ic1psc(uint8_t value);
void STM32446Tim8_cc1s(uint8_t value);
// CCMR2
void STM32446Tim8_oc4ce(uint8_t value);
void STM32446Tim8_oc4m(uint8_t value);
void STM32446Tim8_ic4f(uint8_t value);
void STM32446Tim8_oc4pe(uint8_t bool);
void STM32446Tim8_oc4fe(uint8_t bool);
void STM32446Tim8_ic4psc(uint8_t value);
void STM32446Tim8_cc4s(uint8_t value);
void STM32446Tim8_oc3ce(uint8_t value);
void STM32446Tim8_oc3m(uint8_t value);
void STM32446Tim8_ic3f(uint8_t value);
void STM32446Tim8_oc3pe(uint8_t bool);
void STM32446Tim8_oc3fe(uint8_t bool);
void STM32446Tim8_ic3psc(uint8_t value);
void STM32446Tim8_cc3s(uint8_t value);
// CCER
void STM32446Tim8_cc4np(uint8_t bool);
void STM32446Tim8_cc4p(uint8_t bool);
void STM32446Tim8_cc4e(uint8_t bool);
void STM32446Tim8_cc3np(uint8_t bool);
void STM32446Tim8_cc3p(uint8_t bool);
void STM32446Tim8_cc3e(uint8_t bool);
void STM32446Tim8_cc2np(uint8_t bool);
void STM32446Tim8_cc2p(uint8_t bool);
void STM32446Tim8_cc2e(uint8_t bool);
void STM32446Tim8_cc1np(uint8_t bool);
void STM32446Tim8_cc1p(uint8_t bool);
void STM32446Tim8_cc1e(uint8_t bool);
// CNT
void STM32446Tim8_cnt(uint16_t value);
uint16_t STM32446Tim8_get_cnt(void);
// PSC
void STM32446Tim8_psc(uint16_t value);
// ARR
void STM32446Tim8_arr(uint16_t value);
// CCR1
void STM32446Tim8_ccr1(uint16_t value);
// CCR2
void STM32446Tim8_ccr2(uint16_t value);
// CCR3
void STM32446Tim8_ccr3(uint16_t value);
// CCR4
void STM32446Tim8_ccr4(uint16_t value);
// DCR
void STM32446Tim8_dbl(uint8_t value);
void STM32446Tim8_dba(uint8_t value);
// DMAR
void STM32446Tim8_dmab(uint16_t value);
uint16_t STM32446Tim8_get_dmab(void);
// OR
void STM32446Tim8_ti4_rmp(uint8_t value);
/****************************************/

/*** INTERRUPT HEADER ***/
void TIM1_BRK_TIM9_IRQHandler(void);
void TIM1_UP_TIM10_IRQHandler(void);
void TIM1_TRG_COM_TIM11_IRQHandler(void);
void TIM1_CC_IRQHandler(void);
void TIM8_BRK_TIM12_IRQHandler(void);
void TIM8_UP_TIM13_IRQHandler(void);
void TIM8_TRG_COM_TIM14_IRQHandler(void);
void TIM8_CC_IRQHandler(void);

/*** INTERRUPT HEADER ***/
void TIM1_BRK_TIM9_IRQHandler(void);
void TIM1_UP_TIM10_IRQHandler(void);
void TIM1_TRG_COM_TIM11_IRQHandler(void);
void TIM1_CC_IRQHandler(void);
void TIM8_BRK_TIM12_IRQHandler(void);
void TIM8_UP_TIM13_IRQHandler(void);
void TIM8_TRG_COM_TIM14_IRQHandler(void);
void TIM8_CC_IRQHandler(void);

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


