/******************************************************************************
	STM32 446 TIM 2 to 5
Author: Sergio Santos 
	<sergio.salazar.santos@gmail.com>
License: GNU General Public License
Hardware: STM32-446
Date: 22062023
Comment:
	
*******************************************************************************/
/*** File Library ***/
#include "stm32446mapping.h"
#include "stm32446tim2to5.h"

/*** File Procedure & Function Header ***/
uint32_t tim2to5_readreg(uint32_t reg, uint32_t size_block, uint32_t bit);
void tim2to5_writereg(volatile uint32_t* reg, uint32_t size_block, uint32_t bit, uint32_t data);
void tim2to5_setreg(volatile uint32_t* reg, uint32_t size_block, uint32_t bit, uint32_t data);
void tim2to5_setbit(volatile uint32_t* reg, uint32_t size_block, uint32_t bit, uint32_t data);
uint32_t tim2to5_getsetbit(volatile uint32_t* reg, uint32_t size_block, uint32_t bit);
/*** Auxiliar 2 to 5 ***/
STM32446TIM2_CR1 stm32446_tim2_cr1_inic(void);
STM32446TIM2_CR2 stm32446_tim2_cr2_inic(void);
STM32446TIM2_SMCR stm32446_tim2_smcr_inic(void);
STM32446TIM2_DIER stm32446_tim2_dier_inic(void);
STM32446TIM2_SR stm32446_tim2_sr_inic(void);
STM32446TIM2_EGR stm32446_tim2_egr_inic(void);
STM32446TIM2_CCMR1 stm32446_tim2_ccmr1_inic(void);
STM32446TIM2_CCMR2 stm32446_tim2_ccmr2_inic(void);
STM32446TIM2_CCER stm32446_tim2_ccer_inic(void);
STM32446TIM2_DCR stm32446_tim2_dcr_inic(void);
STM32446TIM3_CR1 stm32446_tim3_cr1_inic(void);
STM32446TIM3_CR2 stm32446_tim3_cr2_inic(void);
STM32446TIM3_SMCR stm32446_tim3_smcr_inic(void);
STM32446TIM3_DIER stm32446_tim3_dier_inic(void);
STM32446TIM3_SR stm32446_tim3_sr_inic(void);
STM32446TIM3_EGR stm32446_tim3_egr_inic(void);
STM32446TIM3_CCMR1 stm32446_tim3_ccmr1_inic(void);
STM32446TIM3_CCMR2 stm32446_tim3_ccmr2_inic(void);
STM32446TIM3_CCER stm32446_tim3_ccer_inic(void);
STM32446TIM3_DCR stm32446_tim3_dcr_inic(void);
STM32446TIM4_CR1 stm32446_tim4_cr1_inic(void);
STM32446TIM4_CR2 stm32446_tim4_cr2_inic(void);
STM32446TIM4_SMCR stm32446_tim4_smcr_inic(void);
STM32446TIM4_DIER stm32446_tim4_dier_inic(void);
STM32446TIM4_SR stm32446_tim4_sr_inic(void);
STM32446TIM4_EGR stm32446_tim4_egr_inic(void);
STM32446TIM4_CCMR1 stm32446_tim4_ccmr1_inic(void);
STM32446TIM4_CCMR2 stm32446_tim4_ccmr2_inic(void);
STM32446TIM4_CCER stm32446_tim4_ccer_inic(void);
STM32446TIM4_DCR stm32446_tim4_dcr_inic(void);
STM32446TIM5_CR1 stm32446_tim5_cr1_inic(void);
STM32446TIM5_CR2 stm32446_tim5_cr2_inic(void);
STM32446TIM5_SMCR stm32446_tim5_smcr_inic(void);
STM32446TIM5_DIER stm32446_tim5_dier_inic(void);
STM32446TIM5_SR stm32446_tim5_sr_inic(void);
STM32446TIM5_EGR stm32446_tim5_egr_inic(void);
STM32446TIM5_CCMR1 stm32446_tim5_ccmr1_inic(void);
STM32446TIM5_CCMR2 stm32446_tim5_ccmr2_inic(void);
STM32446TIM5_CCER stm32446_tim5_ccer_inic(void);
STM32446TIM5_DCR stm32446_tim5_dcr_inic(void);
/*** TIMER Procedure & Function Definition ***/
/************/
/*** TIM2 ***/
/************/
void STM32446Tim2Clock(uint8_t bool)
{
	if(bool){
		RCC->APB1ENR |= (1 << 0); // timer 2 clock enabled
	}else{
		RCC->APB1ENR &= ~(1 << 0); //timer 2 clock disabled
	}
}
void STM32446Tim2Nvic(uint8_t bool)
{ // 28
	if(bool){tim2to5_setbit(NVIC->ISER, 1, 28, 1);}
	else{tim2to5_setbit(NVIC->ICER, 1, 28, 1);}
}
/************************/
/*** TIM2 Bit Mapping ***/
/************************/
// CR1
void STM32446Tim2_ckd(uint8_t value)
{
	tim2to5_setreg(&TIM2->CR1, 2, 8, value);
}
uint8_t STM32446Tim2_get_ckd(void)
{
	return tim2to5_readreg(TIM2->CR1, 2, 8);
}
void STM32446Tim2_set_apre(uint8_t bool)
{
	tim2to5_setreg(&TIM2->CR1, 1, 7, bool);
}
void STM32446Tim2_set_cms(uint8_t value)
{
	tim2to5_setreg(&TIM2->CR1, 2, 5, value);
}
void STM32446Tim2_set_dir(uint8_t bool)
{
	tim2to5_setreg(&TIM2->CR1, 1, 4, bool);
}
void STM32446Tim2_set_opm(uint8_t bool)
{
	tim2to5_setreg(&TIM2->CR1, 1, 3, bool);
}
void STM32446Tim2_set_urs(uint8_t bool)
{
	tim2to5_setreg(&TIM2->CR1, 1, 2, bool);
}
void STM32446Tim2_set_udis(uint8_t bool)
{
	tim2to5_setreg(&TIM2->CR1, 1, 1, bool);
}
void STM32446Tim2_cen(uint8_t bool)
{
	tim2to5_setreg(&TIM2->CR1, 1, 0, bool);
}
// CR2
void STM32446Tim2_ti1s(uint8_t bool)
{
	tim2to5_setreg(&TIM2->CR1, 1, 7, bool);
}
void STM32446Tim2_mms(uint8_t value)
{
	tim2to5_setreg(&TIM2->CR1, 3, 4, value);
}
void STM32446Tim2_ccds(uint8_t bool)
{
	tim2to5_setreg(&TIM2->CR1, 1, 3, bool);
}
// SMCR
void STM32446Tim2_etp(uint8_t bool)
{
	tim2to5_setreg(&TIM2->SMCR, 1, 15, bool);
}
void STM32446Tim2_ece(uint8_t bool)
{
	tim2to5_setreg(&TIM2->SMCR, 1, 14, bool);
}
void STM32446Tim2_etps(uint8_t value)
{
	tim2to5_setreg(&TIM2->SMCR, 2, 12, value);
}
void STM32446Tim2_etf(uint8_t value)
{
	tim2to5_setreg(&TIM2->SMCR, 4, 8, value);
}
void STM32446Tim2_msm(uint8_t bool)
{
	tim2to5_setreg(&TIM2->SMCR, 1, 7, bool);
}
void STM32446Tim2_ts(uint8_t value)
{
	tim2to5_setreg(&TIM2->SMCR, 3, 4, value);
}
void STM32446Tim2_sms(uint8_t value)
{
	tim2to5_setreg(&TIM2->SMCR, 3, 0, value);
}
// DIER
void STM32446Tim2_tde(uint8_t bool)
{
	tim2to5_setreg(&TIM2->DIER, 1, 14, bool);
}
void STM32446Tim2_cc4de(uint8_t bool)
{
	tim2to5_setreg(&TIM2->DIER, 1, 12, bool);
}
void STM32446Tim2_cc3de(uint8_t bool)
{
	tim2to5_setreg(&TIM2->DIER, 1, 11, bool);
}
void STM32446Tim2_cc2de(uint8_t bool)
{
	tim2to5_setreg(&TIM2->DIER, 1, 10, bool);
}
void STM32446Tim2_cc1de(uint8_t bool)
{
	tim2to5_setreg(&TIM2->DIER, 1, 9, bool);
}
void STM32446Tim2_ude(uint8_t bool)
{
	tim2to5_setreg(&TIM2->DIER, 1, 8, bool);
}
void STM32446Tim2_tie(uint8_t bool)
{
	tim2to5_setreg(&TIM2->DIER, 1, 6, bool);
}
void STM32446Tim2_cc4ie(uint8_t bool)
{
	tim2to5_setreg(&TIM2->DIER, 1, 4, bool);
}
void STM32446Tim2_cc3ie(uint8_t bool)
{
	tim2to5_setreg(&TIM2->DIER, 1, 3, bool);
}
void STM32446Tim2_cc2ie(uint8_t bool)
{
	tim2to5_setreg(&TIM2->DIER, 1, 2, bool);
}
void STM32446Tim2_cc1ie(uint8_t bool)
{
	tim2to5_setreg(&TIM2->DIER, 1, 1, bool);
}
void STM32446Tim2_uie(uint8_t bool)
{
	tim2to5_setreg(&TIM2->DIER, 1, 0, bool);
}
// SR
uint8_t STM32446Tim2_cc4of(void)
{
	return tim2to5_readreg(TIM2->SR, 1, 12);
}
void STM32446Tim2_clear_cc4of(void)
{
	tim2to5_setreg(&TIM2->SR, 1, 12, 0);
}
uint8_t STM32446Tim2_cc3of(void)
{
	return tim2to5_readreg(TIM2->SR, 1, 11);
}
void STM32446Tim2_clear_cc3of(void)
{
	tim2to5_setreg(&TIM2->SR, 1, 11, 0);
}
uint8_t STM32446Tim2_cc2of(void)
{
	return tim2to5_readreg(TIM2->SR, 1, 10);
}
void STM32446Tim2_clear_cc2of(void)
{
	tim2to5_setreg(&TIM2->SR, 1, 10, 0);
}
uint8_t STM32446Tim2_cc1of(void)
{
	return tim2to5_readreg(TIM2->SR, 1, 9);
}
void STM32446Tim2_clear_cc1of(void)
{
	tim2to5_setreg(&TIM2->SR, 1, 9, 0);
}
uint8_t STM32446Tim2_tif(void)
{
	return tim2to5_readreg(TIM2->SR, 1, 6);
}
void STM32446Tim2_clear_tif(void)
{
	tim2to5_setreg(&TIM2->SR, 1, 6, 0);
}
uint8_t STM32446Tim2_cc4if(void)
{
	return tim2to5_readreg(TIM2->SR, 1, 4);
}
void STM32446Tim2_clear_cc4if(void)
{
	tim2to5_setreg(&TIM2->SR, 1, 4, 0);
}
uint8_t STM32446Tim2_cc3if(void)
{
	return tim2to5_readreg(TIM2->SR, 1, 3);
}
void STM32446Tim2_clear_cc3if(void)
{
	tim2to5_setreg(&TIM2->SR, 1, 3, 0);
}
uint8_t STM32446Tim2_cc2if(void)
{
	return tim2to5_readreg(TIM2->SR, 1, 2);
}
void STM32446Tim2_clear_cc2if(void)
{
	tim2to5_setreg(&TIM2->SR, 1, 2, 0);
}
uint8_t STM32446Tim2_cc1if(void)
{
	return tim2to5_readreg(TIM2->SR, 1, 1);
}
void STM32446Tim2_clear_cc1if(void)
{
	tim2to5_setreg(&TIM2->SR, 1, 1, 0);
}
uint8_t STM32446Tim2_uif(void)
{
	return tim2to5_readreg(TIM2->SR, 1, 0);
}
void STM32446Tim2_clear_uif(void)
{
	tim2to5_setreg(&TIM2->SR, 1, 0, 0);
}
// EGR
void STM32446Tim2_tg(void)
{
	tim2to5_setreg(&TIM2->EGR, 1, 6, 1);
}
void STM32446Tim2_cc4g(void)
{
	tim2to5_setreg(&TIM2->EGR, 1, 4, 1);
}
void STM32446Tim2_cc3g(void)
{
	tim2to5_setreg(&TIM2->EGR, 1, 3, 1);
}
void STM32446Tim2_cc2g(void)
{
	tim2to5_setreg(&TIM2->EGR, 1, 2, 1);
}
void STM32446Tim2_cc1g(void)
{
	tim2to5_setreg(&TIM2->EGR, 1, 1, 1);
}
void STM32446Tim2_ug(void)
{
	tim2to5_setreg(&TIM2->EGR, 1, 0, 1);
}
// CCMR1
void STM32446Tim2_oc2ce(uint8_t value)
{
	tim2to5_setreg(&TIM2->CCMR1, 1, 15, value);
}
void STM32446Tim2_oc2m(uint8_t value)
{
	tim2to5_setreg(&TIM2->CCMR1, 3, 12, value);
}
void STM32446Tim2_ic2f(uint8_t value)
{
	tim2to5_setreg(&TIM2->CCMR1, 4, 12, value);
}
void STM32446Tim2_oc2pe(uint8_t bool)
{
	tim2to5_setreg(&TIM2->CCMR1, 1, 11, bool);
}
void STM32446Tim2_oc2fe(uint8_t bool)
{
	tim2to5_setreg(&TIM2->CCMR1, 1, 10, bool);
}
void STM32446Tim2_ic2psc(uint8_t value)
{
	tim2to5_setreg(&TIM2->CCMR1, 2, 10, value);
}
void STM32446Tim2_cc2s(uint8_t value)
{
	tim2to5_setreg(&TIM2->CCMR1, 2, 8, value);
}
void STM32446Tim2_oc1ce(uint8_t value)
{
	tim2to5_setreg(&TIM2->CCMR1, 1, 7, value);
}
void STM32446Tim2_oc1m(uint8_t value)
{
	tim2to5_setreg(&TIM2->CCMR1, 3, 4, value);
}
void STM32446Tim2_ic1f(uint8_t value)
{
	tim2to5_setreg(&TIM2->CCMR1, 4, 4, value);
}
void STM32446Tim2_oc1pe(uint8_t bool)
{
	tim2to5_setreg(&TIM2->CCMR1, 1, 3, bool);
}
void STM32446Tim2_oc1fe(uint8_t bool)
{
	tim2to5_setreg(&TIM2->CCMR1, 1, 2, bool);
}
void STM32446Tim2_ic1psc(uint8_t value)
{
	tim2to5_setreg(&TIM2->CCMR1, 2, 2, value);
}
void STM32446Tim2_cc1s(uint8_t value)
{
	tim2to5_setreg(&TIM2->CCMR1, 2, 0, value);
}
// CCMR2
void STM32446Tim2_oc4ce(uint8_t value)
{
	tim2to5_setreg(&TIM2->CCMR2, 1, 15, value);
}
void STM32446Tim2_oc4m(uint8_t value)
{
	tim2to5_setreg(&TIM2->CCMR2, 3, 12, value);
}
void STM32446Tim2_ic4f(uint8_t value)
{
	tim2to5_setreg(&TIM2->CCMR2, 4, 12, value);
}
void STM32446Tim2_oc4pe(uint8_t bool)
{
	tim2to5_setreg(&TIM2->CCMR2, 1, 11, bool);
}
void STM32446Tim2_oc4fe(uint8_t bool)
{
	tim2to5_setreg(&TIM2->CCMR2, 1, 10, bool);
}
void STM32446Tim2_ic4psc(uint8_t value)
{
	tim2to5_setreg(&TIM2->CCMR2, 2, 10, value);
}
void STM32446Tim2_cc4s(uint8_t value)
{
	tim2to5_setreg(&TIM2->CCMR2, 2, 8, value);
}
void STM32446Tim2_oc3ce(uint8_t value)
{
	tim2to5_setreg(&TIM2->CCMR2, 1, 7, value);
}
void STM32446Tim2_oc3m(uint8_t value)
{
	tim2to5_setreg(&TIM2->CCMR2, 3, 4, value);
}
void STM32446Tim2_ic3f(uint8_t value)
{
	tim2to5_setreg(&TIM2->CCMR2, 4, 4, value);
}
void STM32446Tim2_oc3pe(uint8_t bool)
{
	tim2to5_setreg(&TIM2->CCMR2, 1, 3, bool);
}
void STM32446Tim2_oc3fe(uint8_t bool)
{
	tim2to5_setreg(&TIM2->CCMR2, 1, 2, bool);
}
void STM32446Tim2_ic3psc(uint8_t value)
{
	tim2to5_setreg(&TIM2->CCMR2, 2, 2, value);
}
void STM32446Tim2_cc3s(uint8_t value)
{
	tim2to5_setreg(&TIM2->CCMR2, 2, 0, value);
}
// CCER
void STM32446Tim2_cc4np(uint8_t bool)
{
	tim2to5_setreg(&TIM2->CCER, 1, 15, bool);
}
void STM32446Tim2_cc4p(uint8_t bool)
{
	tim2to5_setreg(&TIM2->CCER, 1, 13, bool);
}
void STM32446Tim2_cc4e(uint8_t bool)
{
	tim2to5_setreg(&TIM2->CCER, 1, 12, bool);
}
void STM32446Tim2_cc3np(uint8_t bool)
{
	tim2to5_setreg(&TIM2->CCER, 1, 11, bool);
}
void STM32446Tim2_cc3p(uint8_t bool)
{
	tim2to5_setreg(&TIM2->CCER, 1, 9, bool);
}
void STM32446Tim2_cc3e(uint8_t bool)
{
	tim2to5_setreg(&TIM2->CCER, 1, 8, bool);
}
void STM32446Tim2_cc2np(uint8_t bool)
{
	tim2to5_setreg(&TIM2->CCER, 1, 7, bool);
}
void STM32446Tim2_cc2p(uint8_t bool)
{
	tim2to5_setreg(&TIM2->CCER, 1, 5, bool);
}
void STM32446Tim2_cc2e(uint8_t bool)
{
	tim2to5_setreg(&TIM2->CCER, 1, 4, bool);
}
void STM32446Tim2_cc1np(uint8_t bool)
{
	tim2to5_setreg(&TIM2->CCER, 1, 3, bool);
}
void STM32446Tim2_cc1p(uint8_t bool)
{
	tim2to5_setreg(&TIM2->CCER, 1, 1, bool);
}
void STM32446Tim2_cc1e(uint8_t bool)
{
	tim2to5_setreg(&TIM2->CCER, 1, 0, bool);
}
// CNT
void STM32446Tim2_cnt(uint32_t value)
{
	TIM2->CNT = value;
}
uint32_t STM32446Tim2_get_cnt(void)
{
	return TIM2->CNT;
}
// PSC
void STM32446Tim2_psc(uint16_t value)
{
	TIM2->PSC = value;
}
// ARR
void STM32446Tim2_arr(uint32_t value)
{
	TIM2->ARR = value;
}
// CCR1
void STM32446Tim2_ccr1(uint32_t value)
{
	TIM2->CCR1 = value;
}
// CCR2
void STM32446Tim2_ccr2(uint32_t value)
{
	TIM2->CCR2 = value;
}
// CCR3
void STM32446Tim2_ccr3(uint32_t value)
{
	TIM2->CCR3 = value;
}
// CCR4
void STM32446Tim2_ccr4(uint32_t value)
{
	TIM2->CCR4 = value;
}
// DCR
void STM32446Tim2_dbl(uint8_t value)
{
	tim2to5_setreg(&TIM2->DCR, 5, 8, value);
}
void STM32446Tim2_dba(uint8_t value)
{
	tim2to5_setreg(&TIM2->DCR, 5, 0, value);
}
// DMAR
void STM32446Tim2_dmab(uint16_t value)
{
	TIM2->DMAR = value;
}
uint16_t STM32446Tim2_get_dmab(void)
{
	return TIM2->DMAR;
}
// OR
void STM32446Tim2_itr1_rmp(uint8_t value)
{
	tim2to5_setreg(&TIM2->OR, 2, 10, value);
}
/************/
/*** TIM3 ***/
/************/
void STM32446Tim3Clock(uint8_t bool)
{
	if(bool){
		RCC->APB1ENR |= (1 << 1); // timer 3 clock enabled
	}else{
		RCC->APB1ENR &= ~(1 << 1); //timer 3 clock disabled
	}
}
void STM32446Tim3Nvic(uint8_t bool)
{ // 29
	if(bool){tim2to5_setbit(NVIC->ISER, 1, 29, 1);}
	else{tim2to5_setbit(NVIC->ICER, 1, 29, 1);}
}
/************************/
/*** TIM3 Bit Mapping ***/
/************************/
// CR1
void STM32446Tim3_ckd(uint8_t value)
{
	tim2to5_setreg(&TIM2->CR1, 2, 8, value);
}
uint8_t STM32446Tim3_get_ckd(void)
{
	return tim2to5_readreg(TIM3->CR1, 2, 8);
}
void STM32446Tim3_set_apre(uint8_t bool)
{
	tim2to5_setreg(&TIM3->CR1, 1, 7, bool);
}
void STM32446Tim3_set_cms(uint8_t value)
{
	tim2to5_setreg(&TIM3->CR1, 2, 5, value);
}
void STM32446Tim3_set_dir(uint8_t bool)
{
	tim2to5_setreg(&TIM3->CR1, 1, 4, bool);
}
void STM32446Tim3_set_opm(uint8_t bool)
{
	tim2to5_setreg(&TIM3->CR1, 1, 3, bool);
}
void STM32446Tim3_set_urs(uint8_t bool)
{
	tim2to5_setreg(&TIM3->CR1, 1, 2, bool);
}
void STM32446Tim3_set_udis(uint8_t bool)
{
	tim2to5_setreg(&TIM3->CR1, 1, 1, bool);
}
void STM32446Tim3_cen(uint8_t bool)
{
	tim2to5_setreg(&TIM3->CR1, 1, 0, bool);
}
// CR2
void STM32446Tim3_ti1s(uint8_t bool)
{
	tim2to5_setreg(&TIM3->CR1, 1, 7, bool);
}
void STM32446Tim3_mms(uint8_t value)
{
	tim2to5_setreg(&TIM3->CR1, 3, 4, value);
}
void STM32446Tim3_ccds(uint8_t bool)
{
	tim2to5_setreg(&TIM3->CR1, 1, 3, bool);
}
// SMCR
void STM32446Tim3_etp(uint8_t bool)
{
	tim2to5_setreg(&TIM3->SMCR, 1, 15, bool);
}
void STM32446Tim3_ece(uint8_t bool)
{
	tim2to5_setreg(&TIM3->SMCR, 1, 14, bool);
}
void STM32446Tim3_etps(uint8_t value)
{
	tim2to5_setreg(&TIM3->SMCR, 2, 12, value);
}
void STM32446Tim3_etf(uint8_t value)
{
	tim2to5_setreg(&TIM3->SMCR, 4, 8, value);
}
void STM32446Tim3_msm(uint8_t bool)
{
	tim2to5_setreg(&TIM3->SMCR, 1, 7, bool);
}
void STM32446Tim3_ts(uint8_t value)
{
	tim2to5_setreg(&TIM3->SMCR, 3, 4, value);
}
void STM32446Tim3_sms(uint8_t value)
{
	tim2to5_setreg(&TIM3->SMCR, 3, 0, value);
}
// DIER
void STM32446Tim3_tde(uint8_t bool)
{
	tim2to5_setreg(&TIM3->DIER, 1, 14, bool);
}
void STM32446Tim3_cc4de(uint8_t bool)
{
	tim2to5_setreg(&TIM3->DIER, 1, 12, bool);
}
void STM32446Tim3_cc3de(uint8_t bool)
{
	tim2to5_setreg(&TIM3->DIER, 1, 11, bool);
}
void STM32446Tim3_cc2de(uint8_t bool)
{
	tim2to5_setreg(&TIM3->DIER, 1, 10, bool);
}
void STM32446Tim3_cc1de(uint8_t bool)
{
	tim2to5_setreg(&TIM3->DIER, 1, 9, bool);
}
void STM32446Tim3_ude(uint8_t bool)
{
	tim2to5_setreg(&TIM3->DIER, 1, 8, bool);
}
void STM32446Tim3_tie(uint8_t bool)
{
	tim2to5_setreg(&TIM3->DIER, 1, 6, bool);
}
void STM32446Tim3_cc4ie(uint8_t bool)
{
	tim2to5_setreg(&TIM3->DIER, 1, 4, bool);
}
void STM32446Tim3_cc3ie(uint8_t bool)
{
	tim2to5_setreg(&TIM3->DIER, 1, 3, bool);
}
void STM32446Tim3_cc2ie(uint8_t bool)
{
	tim2to5_setreg(&TIM3->DIER, 1, 2, bool);
}
void STM32446Tim3_cc1ie(uint8_t bool)
{
	tim2to5_setreg(&TIM3->DIER, 1, 1, bool);
}
void STM32446Tim3_uie(uint8_t bool)
{
	tim2to5_setreg(&TIM3->DIER, 1, 0, bool);
}
// SR
uint8_t STM32446Tim3_cc4of(void)
{
	return tim2to5_readreg(TIM3->SR, 1, 12);
}
void STM32446Tim3_clear_cc4of(void)
{
	tim2to5_setreg(&TIM3->SR, 1, 12, 0);
}
uint8_t STM32446Tim3_cc3of(void)
{
	return tim2to5_readreg(TIM3->SR, 1, 11);
}
void STM32446Tim3_clear_cc3of(void)
{
	tim2to5_setreg(&TIM3->SR, 1, 11, 0);
}
uint8_t STM32446Tim3_cc2of(void)
{
	return tim2to5_readreg(TIM3->SR, 1, 10);
}
void STM32446Tim3_clear_cc2of(void)
{
	tim2to5_setreg(&TIM3->SR, 1, 10, 0);
}
uint8_t STM32446Tim3_cc1of(void)
{
	return tim2to5_readreg(TIM3->SR, 1, 9);
}
void STM32446Tim3_clear_cc1of(void)
{
	tim2to5_setreg(&TIM3->SR, 1, 9, 0);
}
uint8_t STM32446Tim3_tif(void)
{
	return tim2to5_readreg(TIM3->SR, 1, 6);
}
void STM32446Tim3_clear_tif(void)
{
	tim2to5_setreg(&TIM3->SR, 1, 6, 0);
}
uint8_t STM32446Tim3_cc4if(void)
{
	return tim2to5_readreg(TIM3->SR, 1, 4);
}
void STM32446Tim3_clear_cc4if(void)
{
	tim2to5_setreg(&TIM3->SR, 1, 4, 0);
}
uint8_t STM32446Tim3_cc3if(void)
{
	return tim2to5_readreg(TIM3->SR, 1, 3);
}
void STM32446Tim3_clear_cc3if(void)
{
	tim2to5_setreg(&TIM3->SR, 1, 3, 0);
}
uint8_t STM32446Tim3_cc2if(void)
{
	return tim2to5_readreg(TIM3->SR, 1, 2);
}
void STM32446Tim3_clear_cc2if(void)
{
	tim2to5_setreg(&TIM3->SR, 1, 2, 0);
}
uint8_t STM32446Tim3_cc1if(void)
{
	return tim2to5_readreg(TIM3->SR, 1, 1);
}
void STM32446Tim3_clear_cc1if(void)
{
	tim2to5_setreg(&TIM3->SR, 1, 1, 0);
}
uint8_t STM32446Tim3_uif(void)
{
	return tim2to5_readreg(TIM3->SR, 1, 0);
}
void STM32446Tim3_clear_uif(void)
{
	tim2to5_setreg(&TIM3->SR, 1, 0, 0);
}
// EGR
void STM32446Tim3_tg(void)
{
	tim2to5_setreg(&TIM3->EGR, 1, 6, 1);
}
void STM32446Tim3_cc4g(void)
{
	tim2to5_setreg(&TIM3->EGR, 1, 4, 1);
}
void STM32446Tim3_cc3g(void)
{
	tim2to5_setreg(&TIM3->EGR, 1, 3, 1);
}
void STM32446Tim3_cc2g(void)
{
	tim2to5_setreg(&TIM3->EGR, 1, 2, 1);
}
void STM32446Tim3_cc1g(void)
{
	tim2to5_setreg(&TIM3->EGR, 1, 1, 1);
}
void STM32446Tim3_ug(void)
{
	tim2to5_setreg(&TIM3->EGR, 1, 0, 1);
}
// CCMR1
void STM32446Tim3_oc2ce(uint8_t value)
{
	tim2to5_setreg(&TIM3->CCMR1, 1, 15, value);
}
void STM32446Tim3_oc2m(uint8_t value)
{
	tim2to5_setreg(&TIM3->CCMR1, 3, 12, value);
}
void STM32446Tim3_ic2f(uint8_t value)
{
	tim2to5_setreg(&TIM3->CCMR1, 4, 12, value);
}
void STM32446Tim3_oc2pe(uint8_t bool)
{
	tim2to5_setreg(&TIM3->CCMR1, 1, 11, bool);
}
void STM32446Tim3_oc2fe(uint8_t bool)
{
	tim2to5_setreg(&TIM3->CCMR1, 1, 10, bool);
}
void STM32446Tim3_ic2psc(uint8_t value)
{
	tim2to5_setreg(&TIM3->CCMR1, 2, 10, value);
}
void STM32446Tim3_cc2s(uint8_t value)
{
	tim2to5_setreg(&TIM3->CCMR1, 2, 8, value);
}
void STM32446Tim3_oc1ce(uint8_t value)
{
	tim2to5_setreg(&TIM3->CCMR1, 1, 7, value);
}
void STM32446Tim3_oc1m(uint8_t value)
{
	tim2to5_setreg(&TIM3->CCMR1, 3, 4, value);
}
void STM32446Tim3_ic1f(uint8_t value)
{
	tim2to5_setreg(&TIM3->CCMR1, 4, 4, value);
}
void STM32446Tim3_oc1pe(uint8_t bool)
{
	tim2to5_setreg(&TIM3->CCMR1, 1, 3, bool);
}
void STM32446Tim3_oc1fe(uint8_t bool)
{
	tim2to5_setreg(&TIM3->CCMR1, 1, 2, bool);
}
void STM32446Tim3_ic1psc(uint8_t value)
{
	tim2to5_setreg(&TIM3->CCMR1, 2, 2, value);
}
void STM32446Tim3_cc1s(uint8_t value)
{
	tim2to5_setreg(&TIM3->CCMR1, 2, 0, value);
}
// CCMR2
void STM32446Tim3_oc4ce(uint8_t value)
{
	tim2to5_setreg(&TIM3->CCMR2, 1, 15, value);
}
void STM32446Tim3_oc4m(uint8_t value)
{
	tim2to5_setreg(&TIM3->CCMR2, 3, 12, value);
}
void STM32446Tim3_ic4f(uint8_t value)
{
	tim2to5_setreg(&TIM3->CCMR2, 4, 12, value);
}
void STM32446Tim3_oc4pe(uint8_t bool)
{
	tim2to5_setreg(&TIM3->CCMR2, 1, 11, bool);
}
void STM32446Tim3_oc4fe(uint8_t bool)
{
	tim2to5_setreg(&TIM3->CCMR2, 1, 10, bool);
}
void STM32446Tim3_ic4psc(uint8_t value)
{
	tim2to5_setreg(&TIM3->CCMR2, 2, 10, value);
}
void STM32446Tim3_cc4s(uint8_t value)
{
	tim2to5_setreg(&TIM3->CCMR2, 2, 8, value);
}
void STM32446Tim3_oc3ce(uint8_t value)
{
	tim2to5_setreg(&TIM3->CCMR2, 1, 7, value);
}
void STM32446Tim3_oc3m(uint8_t value)
{
	tim2to5_setreg(&TIM3->CCMR2, 3, 4, value);
}
void STM32446Tim3_ic3f(uint8_t value)
{
	tim2to5_setreg(&TIM3->CCMR2, 4, 4, value);
}
void STM32446Tim3_oc3pe(uint8_t bool)
{
	tim2to5_setreg(&TIM3->CCMR2, 1, 3, bool);
}
void STM32446Tim3_oc3fe(uint8_t bool)
{
	tim2to5_setreg(&TIM3->CCMR2, 1, 2, bool);
}
void STM32446Tim3_ic3psc(uint8_t value)
{
	tim2to5_setreg(&TIM3->CCMR2, 2, 2, value);
}
void STM32446Tim3_cc3s(uint8_t value)
{
	tim2to5_setreg(&TIM3->CCMR2, 2, 0, value);
}
// CCER
void STM32446Tim3_cc4np(uint8_t bool)
{
	tim2to5_setreg(&TIM3->CCER, 1, 15, bool);
}
void STM32446Tim3_cc4p(uint8_t bool)
{
	tim2to5_setreg(&TIM3->CCER, 1, 13, bool);
}
void STM32446Tim3_cc4e(uint8_t bool)
{
	tim2to5_setreg(&TIM3->CCER, 1, 12, bool);
}
void STM32446Tim3_cc3np(uint8_t bool)
{
	tim2to5_setreg(&TIM3->CCER, 1, 11, bool);
}
void STM32446Tim3_cc3p(uint8_t bool)
{
	tim2to5_setreg(&TIM3->CCER, 1, 9, bool);
}
void STM32446Tim3_cc3e(uint8_t bool)
{
	tim2to5_setreg(&TIM3->CCER, 1, 8, bool);
}
void STM32446Tim3_cc2np(uint8_t bool)
{
	tim2to5_setreg(&TIM3->CCER, 1, 7, bool);
}
void STM32446Tim3_cc2p(uint8_t bool)
{
	tim2to5_setreg(&TIM3->CCER, 1, 5, bool);
}
void STM32446Tim3_cc2e(uint8_t bool)
{
	tim2to5_setreg(&TIM3->CCER, 1, 4, bool);
}
void STM32446Tim3_cc1np(uint8_t bool)
{
	tim2to5_setreg(&TIM3->CCER, 1, 3, bool);
}
void STM32446Tim3_cc1p(uint8_t bool)
{
	tim2to5_setreg(&TIM3->CCER, 1, 1, bool);
}
void STM32446Tim3_cc1e(uint8_t bool)
{
	tim2to5_setreg(&TIM3->CCER, 1, 0, bool);
}
// CNT
void STM32446Tim3_cnt(uint16_t value)
{
	TIM3->CNT = value;
}
uint16_t STM32446Tim3_get_cnt(void)
{
	return TIM3->CNT;
}
// PSC
void STM32446Tim3_psc(uint16_t value)
{
	TIM3->PSC = value;
}
// ARR
void STM32446Tim3_arr(uint16_t value)
{
	TIM3->ARR = value;
}
// CCR1
void STM32446Tim3_ccr1(uint16_t value)
{
	TIM3->CCR1 = value;
}
// CCR2
void STM32446Tim3_ccr2(uint16_t value)
{
	TIM3->CCR2 = value;
}
// CCR3
void STM32446Tim3_ccr3(uint16_t value)
{
	TIM3->CCR3 = value;
}
// CCR4
void STM32446Tim3_ccr4(uint16_t value)
{
	TIM3->CCR4 = value;
}
// DCR
void STM32446Tim3_dbl(uint8_t value)
{
	tim2to5_setreg(&TIM3->DCR, 5, 8, value);
}
void STM32446Tim3_dba(uint8_t value)
{
	tim2to5_setreg(&TIM3->DCR, 5, 0, value);
}
// DMAR
void STM32446Tim3_dmab(uint16_t value)
{
	TIM3->DMAR = value;
}
uint16_t STM32446Tim3_get_dmab(void)
{
	return TIM3->DMAR;
}
/************/
/*** TIM4 ***/
/************/
void STM32446Tim4Clock(uint8_t bool)
{
	if(bool){
		RCC->APB1ENR |= (1 << 2); // timer 4 clock enabled
	}else{
		RCC->APB1ENR &= ~(1 << 2); //timer 4 clock disabled
	}
}
void STM32446Tim4Nvic(uint8_t bool)
{ // 30
	if(bool){tim2to5_setbit(NVIC->ISER, 1, 30, 1);}
	else{tim2to5_setbit(NVIC->ICER, 1, 30, 1);}
}
/************************/
/*** TIM4 Bit Mapping ***/
/************************/
// CR1
void STM32446Tim4_ckd(uint8_t value)
{
	tim2to5_setreg(&TIM2->CR1, 2, 8, value);
}
uint8_t STM32446Tim4_get_ckd(void)
{
	return tim2to5_readreg(TIM4->CR1, 2, 8);
}
void STM32446Tim4_set_apre(uint8_t bool)
{
	tim2to5_setreg(&TIM4->CR1, 1, 7, bool);
}
void STM32446Tim4_set_cms(uint8_t value)
{
	tim2to5_setreg(&TIM4->CR1, 2, 5, value);
}
void STM32446Tim4_set_dir(uint8_t bool)
{
	tim2to5_setreg(&TIM4->CR1, 1, 4, bool);
}
void STM32446Tim4_set_opm(uint8_t bool)
{
	tim2to5_setreg(&TIM4->CR1, 1, 3, bool);
}
void STM32446Tim4_set_urs(uint8_t bool)
{
	tim2to5_setreg(&TIM4->CR1, 1, 2, bool);
}
void STM32446Tim4_set_udis(uint8_t bool)
{
	tim2to5_setreg(&TIM4->CR1, 1, 1, bool);
}
void STM32446Tim4_cen(uint8_t bool)
{
	tim2to5_setreg(&TIM4->CR1, 1, 0, bool);
}
// CR2
void STM32446Tim4_ti1s(uint8_t bool)
{
	tim2to5_setreg(&TIM4->CR1, 1, 7, bool);
}
void STM32446Tim4_mms(uint8_t value)
{
	tim2to5_setreg(&TIM4->CR1, 3, 4, value);
}
void STM32446Tim4_ccds(uint8_t bool)
{
	tim2to5_setreg(&TIM4->CR1, 1, 3, bool);
}
// SMCR
void STM32446Tim4_etp(uint8_t bool)
{
	tim2to5_setreg(&TIM4->SMCR, 1, 15, bool);
}
void STM32446Tim4_ece(uint8_t bool)
{
	tim2to5_setreg(&TIM4->SMCR, 1, 14, bool);
}
void STM32446Tim4_etps(uint8_t value)
{
	tim2to5_setreg(&TIM4->SMCR, 2, 12, value);
}
void STM32446Tim4_etf(uint8_t value)
{
	tim2to5_setreg(&TIM4->SMCR, 4, 8, value);
}
void STM32446Tim4_msm(uint8_t bool)
{
	tim2to5_setreg(&TIM4->SMCR, 1, 7, bool);
}
void STM32446Tim4_ts(uint8_t value)
{
	tim2to5_setreg(&TIM4->SMCR, 3, 4, value);
}
void STM32446Tim4_sms(uint8_t value)
{
	tim2to5_setreg(&TIM4->SMCR, 3, 0, value);
}
// DIER
void STM32446Tim4_tde(uint8_t bool)
{
	tim2to5_setreg(&TIM4->DIER, 1, 14, bool);
}
void STM32446Tim4_cc4de(uint8_t bool)
{
	tim2to5_setreg(&TIM4->DIER, 1, 12, bool);
}
void STM32446Tim4_cc3de(uint8_t bool)
{
	tim2to5_setreg(&TIM4->DIER, 1, 11, bool);
}
void STM32446Tim4_cc2de(uint8_t bool)
{
	tim2to5_setreg(&TIM4->DIER, 1, 10, bool);
}
void STM32446Tim4_cc1de(uint8_t bool)
{
	tim2to5_setreg(&TIM4->DIER, 1, 9, bool);
}
void STM32446Tim4_ude(uint8_t bool)
{
	tim2to5_setreg(&TIM4->DIER, 1, 8, bool);
}
void STM32446Tim4_tie(uint8_t bool)
{
	tim2to5_setreg(&TIM4->DIER, 1, 6, bool);
}
void STM32446Tim4_cc4ie(uint8_t bool)
{
	tim2to5_setreg(&TIM4->DIER, 1, 4, bool);
}
void STM32446Tim4_cc3ie(uint8_t bool)
{
	tim2to5_setreg(&TIM4->DIER, 1, 3, bool);
}
void STM32446Tim4_cc2ie(uint8_t bool)
{
	tim2to5_setreg(&TIM4->DIER, 1, 2, bool);
}
void STM32446Tim4_cc1ie(uint8_t bool)
{
	tim2to5_setreg(&TIM4->DIER, 1, 1, bool);
}
void STM32446Tim4_uie(uint8_t bool)
{
	tim2to5_setreg(&TIM4->DIER, 1, 0, bool);
}
// SR
uint8_t STM32446Tim4_cc4of(void)
{
	return tim2to5_readreg(TIM4->SR, 1, 12);
}
void STM32446Tim4_clear_cc4of(void)
{
	tim2to5_setreg(&TIM4->SR, 1, 12, 0);
}
uint8_t STM32446Tim4_cc3of(void)
{
	return tim2to5_readreg(TIM4->SR, 1, 11);
}
void STM32446Tim4_clear_cc3of(void)
{
	tim2to5_setreg(&TIM4->SR, 1, 11, 0);
}
uint8_t STM32446Tim4_cc2of(void)
{
	return tim2to5_readreg(TIM4->SR, 1, 10);
}
void STM32446Tim4_clear_cc2of(void)
{
	tim2to5_setreg(&TIM4->SR, 1, 10, 0);
}
uint8_t STM32446Tim4_cc1of(void)
{
	return tim2to5_readreg(TIM4->SR, 1, 9);
}
void STM32446Tim4_clear_cc1of(void)
{
	tim2to5_setreg(&TIM4->SR, 1, 9, 0);
}
uint8_t STM32446Tim4_tif(void)
{
	return tim2to5_readreg(TIM4->SR, 1, 6);
}
void STM32446Tim4_clear_tif(void)
{
	tim2to5_setreg(&TIM4->SR, 1, 6, 0);
}
uint8_t STM32446Tim4_cc4if(void)
{
	return tim2to5_readreg(TIM4->SR, 1, 4);
}
void STM32446Tim4_clear_cc4if(void)
{
	tim2to5_setreg(&TIM4->SR, 1, 4, 0);
}
uint8_t STM32446Tim4_cc3if(void)
{
	return tim2to5_readreg(TIM4->SR, 1, 3);
}
void STM32446Tim4_clear_cc3if(void)
{
	tim2to5_setreg(&TIM4->SR, 1, 3, 0);
}
uint8_t STM32446Tim4_cc2if(void)
{
	return tim2to5_readreg(TIM4->SR, 1, 2);
}
void STM32446Tim4_clear_cc2if(void)
{
	tim2to5_setreg(&TIM4->SR, 1, 2, 0);
}
uint8_t STM32446Tim4_cc1if(void)
{
	return tim2to5_readreg(TIM4->SR, 1, 1);
}
void STM32446Tim4_clear_cc1if(void)
{
	tim2to5_setreg(&TIM4->SR, 1, 1, 0);
}
uint8_t STM32446Tim4_uif(void)
{
	return tim2to5_readreg(TIM4->SR, 1, 0);
}
void STM32446Tim4_clear_uif(void)
{
	tim2to5_setreg(&TIM4->SR, 1, 0, 0);
}
// EGR
void STM32446Tim4_tg(void)
{
	tim2to5_setreg(&TIM4->EGR, 1, 6, 1);
}
void STM32446Tim4_cc4g(void)
{
	tim2to5_setreg(&TIM4->EGR, 1, 4, 1);
}
void STM32446Tim4_cc3g(void)
{
	tim2to5_setreg(&TIM4->EGR, 1, 3, 1);
}
void STM32446Tim4_cc2g(void)
{
	tim2to5_setreg(&TIM4->EGR, 1, 2, 1);
}
void STM32446Tim4_cc1g(void)
{
	tim2to5_setreg(&TIM4->EGR, 1, 1, 1);
}
void STM32446Tim4_ug(void)
{
	tim2to5_setreg(&TIM4->EGR, 1, 0, 1);
}
// CCMR1
void STM32446Tim4_oc2ce(uint8_t value)
{
	tim2to5_setreg(&TIM4->CCMR1, 1, 15, value);
}
void STM32446Tim4_oc2m(uint8_t value)
{
	tim2to5_setreg(&TIM4->CCMR1, 3, 12, value);
}
void STM32446Tim4_ic2f(uint8_t value)
{
	tim2to5_setreg(&TIM4->CCMR1, 4, 12, value);
}
void STM32446Tim4_oc2pe(uint8_t bool)
{
	tim2to5_setreg(&TIM4->CCMR1, 1, 11, bool);
}
void STM32446Tim4_oc2fe(uint8_t bool)
{
	tim2to5_setreg(&TIM4->CCMR1, 1, 10, bool);
}
void STM32446Tim4_ic2psc(uint8_t value)
{
	tim2to5_setreg(&TIM4->CCMR1, 2, 10, value);
}
void STM32446Tim4_cc2s(uint8_t value)
{
	tim2to5_setreg(&TIM4->CCMR1, 2, 8, value);
}
void STM32446Tim4_oc1ce(uint8_t value)
{
	tim2to5_setreg(&TIM4->CCMR1, 1, 7, value);
}
void STM32446Tim4_oc1m(uint8_t value)
{
	tim2to5_setreg(&TIM4->CCMR1, 3, 4, value);
}
void STM32446Tim4_ic1f(uint8_t value)
{
	tim2to5_setreg(&TIM4->CCMR1, 4, 4, value);
}
void STM32446Tim4_oc1pe(uint8_t bool)
{
	tim2to5_setreg(&TIM4->CCMR1, 1, 3, bool);
}
void STM32446Tim4_oc1fe(uint8_t bool)
{
	tim2to5_setreg(&TIM4->CCMR1, 1, 2, bool);
}
void STM32446Tim4_ic1psc(uint8_t value)
{
	tim2to5_setreg(&TIM4->CCMR1, 2, 2, value);
}
void STM32446Tim4_cc1s(uint8_t value)
{
	tim2to5_setreg(&TIM4->CCMR1, 2, 0, value);
}
// CCMR2
void STM32446Tim4_oc4ce(uint8_t value)
{
	tim2to5_setreg(&TIM4->CCMR2, 1, 15, value);
}
void STM32446Tim4_oc4m(uint8_t value)
{
	tim2to5_setreg(&TIM4->CCMR2, 3, 12, value);
}
void STM32446Tim4_ic4f(uint8_t value)
{
	tim2to5_setreg(&TIM4->CCMR2, 4, 12, value);
}
void STM32446Tim4_oc4pe(uint8_t bool)
{
	tim2to5_setreg(&TIM4->CCMR2, 1, 11, bool);
}
void STM32446Tim4_oc4fe(uint8_t bool)
{
	tim2to5_setreg(&TIM4->CCMR2, 1, 10, bool);
}
void STM32446Tim4_ic4psc(uint8_t value)
{
	tim2to5_setreg(&TIM4->CCMR2, 2, 10, value);
}
void STM32446Tim4_cc4s(uint8_t value)
{
	tim2to5_setreg(&TIM4->CCMR2, 2, 8, value);
}
void STM32446Tim4_oc3ce(uint8_t value)
{
	tim2to5_setreg(&TIM4->CCMR2, 1, 7, value);
}
void STM32446Tim4_oc3m(uint8_t value)
{
	tim2to5_setreg(&TIM4->CCMR2, 3, 4, value);
}
void STM32446Tim4_ic3f(uint8_t value)
{
	tim2to5_setreg(&TIM4->CCMR2, 4, 4, value);
}
void STM32446Tim4_oc3pe(uint8_t bool)
{
	tim2to5_setreg(&TIM4->CCMR2, 1, 3, bool);
}
void STM32446Tim4_oc3fe(uint8_t bool)
{
	tim2to5_setreg(&TIM4->CCMR2, 1, 2, bool);
}
void STM32446Tim4_ic3psc(uint8_t value)
{
	tim2to5_setreg(&TIM4->CCMR2, 2, 2, value);
}
void STM32446Tim4_cc3s(uint8_t value)
{
	tim2to5_setreg(&TIM4->CCMR2, 2, 0, value);
}
// CCER
void STM32446Tim4_cc4np(uint8_t bool)
{
	tim2to5_setreg(&TIM4->CCER, 1, 15, bool);
}
void STM32446Tim4_cc4p(uint8_t bool)
{
	tim2to5_setreg(&TIM4->CCER, 1, 13, bool);
}
void STM32446Tim4_cc4e(uint8_t bool)
{
	tim2to5_setreg(&TIM4->CCER, 1, 12, bool);
}
void STM32446Tim4_cc3np(uint8_t bool)
{
	tim2to5_setreg(&TIM4->CCER, 1, 11, bool);
}
void STM32446Tim4_cc3p(uint8_t bool)
{
	tim2to5_setreg(&TIM4->CCER, 1, 9, bool);
}
void STM32446Tim4_cc3e(uint8_t bool)
{
	tim2to5_setreg(&TIM4->CCER, 1, 8, bool);
}
void STM32446Tim4_cc2np(uint8_t bool)
{
	tim2to5_setreg(&TIM4->CCER, 1, 7, bool);
}
void STM32446Tim4_cc2p(uint8_t bool)
{
	tim2to5_setreg(&TIM4->CCER, 1, 5, bool);
}
void STM32446Tim4_cc2e(uint8_t bool)
{
	tim2to5_setreg(&TIM4->CCER, 1, 4, bool);
}
void STM32446Tim4_cc1np(uint8_t bool)
{
	tim2to5_setreg(&TIM4->CCER, 1, 3, bool);
}
void STM32446Tim4_cc1p(uint8_t bool)
{
	tim2to5_setreg(&TIM4->CCER, 1, 1, bool);
}
void STM32446Tim4_cc1e(uint8_t bool)
{
	tim2to5_setreg(&TIM4->CCER, 1, 0, bool);
}
// CNT
void STM32446Tim4_cnt(uint16_t value)
{
	TIM4->CNT = value;
}
uint16_t STM32446Tim4_get_cnt(void)
{
	return TIM4->CNT;
}
// PSC
void STM32446Tim4_psc(uint16_t value)
{
	TIM4->PSC = value;
}
// ARR
void STM32446Tim4_arr(uint16_t value)
{
	TIM4->ARR = value;
}
// CCR1
void STM32446Tim4_ccr1(uint16_t value)
{
	TIM4->CCR1 = value;
}
// CCR2
void STM32446Tim4_ccr2(uint16_t value)
{
	TIM4->CCR2 = value;
}
// CCR3
void STM32446Tim4_ccr3(uint16_t value)
{
	TIM4->CCR3 = value;
}
// CCR4
void STM32446Tim4_ccr4(uint16_t value)
{
	TIM4->CCR4 = value;
}
// DCR
void STM32446Tim4_dbl(uint8_t value)
{
	tim2to5_setreg(&TIM4->DCR, 5, 8, value);
}
void STM32446Tim4_dba(uint8_t value)
{
	tim2to5_setreg(&TIM4->DCR, 5, 0, value);
}
// DMAR
void STM32446Tim4_dmab(uint16_t value)
{
	TIM4->DMAR = value;
}
uint16_t STM32446Tim4_get_dmab(void)
{
	return TIM4->DMAR;
}
/************/
/*** TIM5 ***/
/************/
void STM32446Tim5Clock(uint8_t bool)
{
	if(bool){
		RCC->APB1ENR |= (1 << 3); // timer 5 clock enabled
	}else{
		RCC->APB1ENR &= ~(1 << 3); //timer 5 clock disabled
	}
}
void STM32446Tim5Nvic(uint8_t bool)
{ // 50
	if(bool){tim2to5_setbit(NVIC->ISER, 1, 50, 1);}
	else{tim2to5_setbit(NVIC->ICER, 1, 50, 1);}
}
/************************/
/*** TIM5 Bit Mapping ***/
/************************/
// CR1
void STM32446Tim5_ckd(uint8_t value)
{
	tim2to5_setreg(&TIM2->CR1, 2, 8, value);
}
uint8_t STM32446Tim5_get_ckd(void)
{
	return tim2to5_readreg(TIM5->CR1, 2, 8);
}
void STM32446Tim5_set_apre(uint8_t bool)
{
	tim2to5_setreg(&TIM5->CR1, 1, 7, bool);
}
void STM32446Tim5_set_cms(uint8_t value)
{
	tim2to5_setreg(&TIM5->CR1, 2, 5, value);
}
void STM32446Tim5_set_dir(uint8_t bool)
{
	tim2to5_setreg(&TIM5->CR1, 1, 4, bool);
}
void STM32446Tim5_set_opm(uint8_t bool)
{
	tim2to5_setreg(&TIM5->CR1, 1, 3, bool);
}
void STM32446Tim5_set_urs(uint8_t bool)
{
	tim2to5_setreg(&TIM5->CR1, 1, 2, bool);
}
void STM32446Tim5_set_udis(uint8_t bool)
{
	tim2to5_setreg(&TIM5->CR1, 1, 1, bool);
}
void STM32446Tim5_cen(uint8_t bool)
{
	tim2to5_setreg(&TIM5->CR1, 1, 0, bool);
}
// CR2
void STM32446Tim5_ti1s(uint8_t bool)
{
	tim2to5_setreg(&TIM5->CR1, 1, 7, bool);
}
void STM32446Tim5_mms(uint8_t value)
{
	tim2to5_setreg(&TIM5->CR1, 3, 4, value);
}
void STM32446Tim5_ccds(uint8_t bool)
{
	tim2to5_setreg(&TIM5->CR1, 1, 3, bool);
}
// SMCR
void STM32446Tim5_etp(uint8_t bool)
{
	tim2to5_setreg(&TIM5->SMCR, 1, 15, bool);
}
void STM32446Tim5_ece(uint8_t bool)
{
	tim2to5_setreg(&TIM5->SMCR, 1, 14, bool);
}
void STM32446Tim5_etps(uint8_t value)
{
	tim2to5_setreg(&TIM5->SMCR, 2, 12, value);
}
void STM32446Tim5_etf(uint8_t value)
{
	tim2to5_setreg(&TIM5->SMCR, 4, 8, value);
}
void STM32446Tim5_msm(uint8_t bool)
{
	tim2to5_setreg(&TIM5->SMCR, 1, 7, bool);
}
void STM32446Tim5_ts(uint8_t value)
{
	tim2to5_setreg(&TIM5->SMCR, 3, 4, value);
}
void STM32446Tim5_sms(uint8_t value)
{
	tim2to5_setreg(&TIM5->SMCR, 3, 0, value);
}
// DIER
void STM32446Tim5_tde(uint8_t bool)
{
	tim2to5_setreg(&TIM5->DIER, 1, 14, bool);
}
void STM32446Tim5_cc4de(uint8_t bool)
{
	tim2to5_setreg(&TIM5->DIER, 1, 12, bool);
}
void STM32446Tim5_cc3de(uint8_t bool)
{
	tim2to5_setreg(&TIM5->DIER, 1, 11, bool);
}
void STM32446Tim5_cc2de(uint8_t bool)
{
	tim2to5_setreg(&TIM5->DIER, 1, 10, bool);
}
void STM32446Tim5_cc1de(uint8_t bool)
{
	tim2to5_setreg(&TIM5->DIER, 1, 9, bool);
}
void STM32446Tim5_ude(uint8_t bool)
{
	tim2to5_setreg(&TIM5->DIER, 1, 8, bool);
}
void STM32446Tim5_tie(uint8_t bool)
{
	tim2to5_setreg(&TIM5->DIER, 1, 6, bool);
}
void STM32446Tim5_cc4ie(uint8_t bool)
{
	tim2to5_setreg(&TIM5->DIER, 1, 4, bool);
}
void STM32446Tim5_cc3ie(uint8_t bool)
{
	tim2to5_setreg(&TIM5->DIER, 1, 3, bool);
}
void STM32446Tim5_cc2ie(uint8_t bool)
{
	tim2to5_setreg(&TIM5->DIER, 1, 2, bool);
}
void STM32446Tim5_cc1ie(uint8_t bool)
{
	tim2to5_setreg(&TIM5->DIER, 1, 1, bool);
}
void STM32446Tim5_uie(uint8_t bool)
{
	tim2to5_setreg(&TIM5->DIER, 1, 0, bool);
}
// SR
uint8_t STM32446Tim5_cc4of(void)
{
	return tim2to5_readreg(TIM5->SR, 1, 12);
}
void STM32446Tim5_clear_cc4of(void)
{
	tim2to5_setreg(&TIM5->SR, 1, 12, 0);
}
uint8_t STM32446Tim5_cc3of(void)
{
	return tim2to5_readreg(TIM5->SR, 1, 11);
}
void STM32446Tim5_clear_cc3of(void)
{
	tim2to5_setreg(&TIM5->SR, 1, 11, 0);
}
uint8_t STM32446Tim5_cc2of(void)
{
	return tim2to5_readreg(TIM5->SR, 1, 10);
}
void STM32446Tim5_clear_cc2of(void)
{
	tim2to5_setreg(&TIM5->SR, 1, 10, 0);
}
uint8_t STM32446Tim5_cc1of(void)
{
	return tim2to5_readreg(TIM5->SR, 1, 9);
}
void STM32446Tim5_clear_cc1of(void)
{
	tim2to5_setreg(&TIM5->SR, 1, 9, 0);
}
uint8_t STM32446Tim5_tif(void)
{
	return tim2to5_readreg(TIM5->SR, 1, 6);
}
void STM32446Tim5_clear_tif(void)
{
	tim2to5_setreg(&TIM5->SR, 1, 6, 0);
}
uint8_t STM32446Tim5_cc4if(void)
{
	return tim2to5_readreg(TIM5->SR, 1, 4);
}
void STM32446Tim5_clear_cc4if(void)
{
	tim2to5_setreg(&TIM5->SR, 1, 4, 0);
}
uint8_t STM32446Tim5_cc3if(void)
{
	return tim2to5_readreg(TIM5->SR, 1, 3);
}
void STM32446Tim5_clear_cc3if(void)
{
	tim2to5_setreg(&TIM5->SR, 1, 3, 0);
}
uint8_t STM32446Tim5_cc2if(void)
{
	return tim2to5_readreg(TIM5->SR, 1, 2);
}
void STM32446Tim5_clear_cc2if(void)
{
	tim2to5_setreg(&TIM5->SR, 1, 2, 0);
}
uint8_t STM32446Tim5_cc1if(void)
{
	return tim2to5_readreg(TIM5->SR, 1, 1);
}
void STM32446Tim5_clear_cc1if(void)
{
	tim2to5_setreg(&TIM5->SR, 1, 1, 0);
}
uint8_t STM32446Tim5_uif(void)
{
	return tim2to5_readreg(TIM5->SR, 1, 0);
}
void STM32446Tim5_clear_uif(void)
{
	tim2to5_setreg(&TIM5->SR, 1, 0, 0);
}
// EGR
void STM32446Tim5_tg(void)
{
	tim2to5_setreg(&TIM5->EGR, 1, 6, 1);
}
void STM32446Tim5_cc4g(void)
{
	tim2to5_setreg(&TIM5->EGR, 1, 4, 1);
}
void STM32446Tim5_cc3g(void)
{
	tim2to5_setreg(&TIM5->EGR, 1, 3, 1);
}
void STM32446Tim5_cc2g(void)
{
	tim2to5_setreg(&TIM5->EGR, 1, 2, 1);
}
void STM32446Tim5_cc1g(void)
{
	tim2to5_setreg(&TIM5->EGR, 1, 1, 1);
}
void STM32446Tim5_ug(void)
{
	tim2to5_setreg(&TIM5->EGR, 1, 0, 1);
}
// CCMR1
void STM32446Tim5_oc2ce(uint8_t value)
{
	tim2to5_setreg(&TIM5->CCMR1, 1, 15, value);
}
void STM32446Tim5_oc2m(uint8_t value)
{
	tim2to5_setreg(&TIM5->CCMR1, 3, 12, value);
}
void STM32446Tim5_ic2f(uint8_t value)
{
	tim2to5_setreg(&TIM5->CCMR1, 4, 12, value);
}
void STM32446Tim5_oc2pe(uint8_t bool)
{
	tim2to5_setreg(&TIM5->CCMR1, 1, 11, bool);
}
void STM32446Tim5_oc2fe(uint8_t bool)
{
	tim2to5_setreg(&TIM5->CCMR1, 1, 10, bool);
}
void STM32446Tim5_ic2psc(uint8_t value)
{
	tim2to5_setreg(&TIM5->CCMR1, 2, 10, value);
}
void STM32446Tim5_cc2s(uint8_t value)
{
	tim2to5_setreg(&TIM5->CCMR1, 2, 8, value);
}
void STM32446Tim5_oc1ce(uint8_t value)
{
	tim2to5_setreg(&TIM5->CCMR1, 1, 7, value);
}
void STM32446Tim5_oc1m(uint8_t value)
{
	tim2to5_setreg(&TIM5->CCMR1, 3, 4, value);
}
void STM32446Tim5_ic1f(uint8_t value)
{
	tim2to5_setreg(&TIM5->CCMR1, 4, 4, value);
}
void STM32446Tim5_oc1pe(uint8_t bool)
{
	tim2to5_setreg(&TIM5->CCMR1, 1, 3, bool);
}
void STM32446Tim5_oc1fe(uint8_t bool)
{
	tim2to5_setreg(&TIM5->CCMR1, 1, 2, bool);
}
void STM32446Tim5_ic1psc(uint8_t value)
{
	tim2to5_setreg(&TIM5->CCMR1, 2, 2, value);
}
void STM32446Tim5_cc1s(uint8_t value)
{
	tim2to5_setreg(&TIM5->CCMR1, 2, 0, value);
}
// CCMR2
void STM32446Tim5_oc4ce(uint8_t value)
{
	tim2to5_setreg(&TIM5->CCMR2, 1, 15, value);
}
void STM32446Tim5_oc4m(uint8_t value)
{
	tim2to5_setreg(&TIM5->CCMR2, 3, 12, value);
}
void STM32446Tim5_ic4f(uint8_t value)
{
	tim2to5_setreg(&TIM5->CCMR2, 4, 12, value);
}
void STM32446Tim5_oc4pe(uint8_t bool)
{
	tim2to5_setreg(&TIM5->CCMR2, 1, 11, bool);
}
void STM32446Tim5_oc4fe(uint8_t bool)
{
	tim2to5_setreg(&TIM5->CCMR2, 1, 10, bool);
}
void STM32446Tim5_ic4psc(uint8_t value)
{
	tim2to5_setreg(&TIM5->CCMR2, 2, 10, value);
}
void STM32446Tim5_cc4s(uint8_t value)
{
	tim2to5_setreg(&TIM5->CCMR2, 2, 8, value);
}
void STM32446Tim5_oc3ce(uint8_t value)
{
	tim2to5_setreg(&TIM5->CCMR2, 1, 7, value);
}
void STM32446Tim5_oc3m(uint8_t value)
{
	tim2to5_setreg(&TIM5->CCMR2, 3, 4, value);
}
void STM32446Tim5_ic3f(uint8_t value)
{
	tim2to5_setreg(&TIM5->CCMR2, 4, 4, value);
}
void STM32446Tim5_oc3pe(uint8_t bool)
{
	tim2to5_setreg(&TIM5->CCMR2, 1, 3, bool);
}
void STM32446Tim5_oc3fe(uint8_t bool)
{
	tim2to5_setreg(&TIM5->CCMR2, 1, 2, bool);
}
void STM32446Tim5_ic3psc(uint8_t value)
{
	tim2to5_setreg(&TIM5->CCMR2, 2, 2, value);
}
void STM32446Tim5_cc3s(uint8_t value)
{
	tim2to5_setreg(&TIM5->CCMR2, 2, 0, value);
}
// CCER
void STM32446Tim5_cc4np(uint8_t bool)
{
	tim2to5_setreg(&TIM5->CCER, 1, 15, bool);
}
void STM32446Tim5_cc4p(uint8_t bool)
{
	tim2to5_setreg(&TIM5->CCER, 1, 13, bool);
}
void STM32446Tim5_cc4e(uint8_t bool)
{
	tim2to5_setreg(&TIM5->CCER, 1, 12, bool);
}
void STM32446Tim5_cc3np(uint8_t bool)
{
	tim2to5_setreg(&TIM5->CCER, 1, 11, bool);
}
void STM32446Tim5_cc3p(uint8_t bool)
{
	tim2to5_setreg(&TIM5->CCER, 1, 9, bool);
}
void STM32446Tim5_cc3e(uint8_t bool)
{
	tim2to5_setreg(&TIM5->CCER, 1, 8, bool);
}
void STM32446Tim5_cc2np(uint8_t bool)
{
	tim2to5_setreg(&TIM5->CCER, 1, 7, bool);
}
void STM32446Tim5_cc2p(uint8_t bool)
{
	tim2to5_setreg(&TIM5->CCER, 1, 5, bool);
}
void STM32446Tim5_cc2e(uint8_t bool)
{
	tim2to5_setreg(&TIM5->CCER, 1, 4, bool);
}
void STM32446Tim5_cc1np(uint8_t bool)
{
	tim2to5_setreg(&TIM5->CCER, 1, 3, bool);
}
void STM32446Tim5_cc1p(uint8_t bool)
{
	tim2to5_setreg(&TIM5->CCER, 1, 1, bool);
}
void STM32446Tim5_cc1e(uint8_t bool)
{
	tim2to5_setreg(&TIM5->CCER, 1, 0, bool);
}
// CNT
void STM32446Tim5_cnt(uint32_t value)
{
	TIM5->CNT = value;
}
uint32_t STM32446Tim5_get_cnt(void)
{
	return TIM5->CNT;
}
// PSC
void STM32446Tim5_psc(uint16_t value)
{
	TIM5->PSC = value;
}
// ARR
void STM32446Tim5_arr(uint32_t value)
{
	TIM5->ARR = value;
}
// CCR1
void STM32446Tim5_ccr1(uint32_t value)
{
	TIM5->CCR1 = value;
}
// CCR2
void STM32446Tim5_ccr2(uint32_t value)
{
	TIM5->CCR2 = value;
}
// CCR3
void STM32446Tim5_ccr3(uint32_t value)
{
	TIM5->CCR3 = value;
}
// CCR4
void STM32446Tim5_ccr4(uint32_t value)
{
	TIM5->CCR4 = value;
}
// DCR
void STM32446Tim5_dbl(uint8_t value)
{
	tim2to5_setreg(&TIM5->DCR, 5, 8, value);
}
void STM32446Tim5_dba(uint8_t value)
{
	tim2to5_setreg(&TIM5->DCR, 5, 0, value);
}
// DMAR
void STM32446Tim5_dmab(uint16_t value)
{
	TIM5->DMAR = value;
}
uint16_t STM32446Tim5_get_dmab(void)
{
	return TIM5->DMAR;
}
// OR
void STM32446Tim5_ti4_rmp(uint8_t value)
{
	tim2to5_setreg(&TIM5->OR, 2, 6, value);
}
/*** TIM2 Auxiliar ***/
STM32446TIM2_CR1 stm32446_tim2_cr1_inic(void)
{
	STM32446TIM2_CR1 stm32446_tim_cr1;
	// CR1
	stm32446_tim_cr1.get_ckd = STM32446Tim2_get_ckd;
	stm32446_tim_cr1.apre = STM32446Tim2_set_apre;
	stm32446_tim_cr1.cms = STM32446Tim2_set_cms;
	stm32446_tim_cr1.dir = STM32446Tim2_set_dir;
	stm32446_tim_cr1.opm = STM32446Tim2_set_opm;
	stm32446_tim_cr1.urs = STM32446Tim2_set_urs;
	stm32446_tim_cr1.udis = STM32446Tim2_set_udis;
	stm32446_tim_cr1.cen = STM32446Tim2_cen;
	return stm32446_tim_cr1;
}
STM32446TIM2_CR2 stm32446_tim2_cr2_inic(void)
{
	STM32446TIM2_CR2 stm32446_tim_cr2;
	// CR2
	stm32446_tim_cr2.ti1s = STM32446Tim2_ti1s;
	stm32446_tim_cr2.mms = STM32446Tim2_mms;
	stm32446_tim_cr2.ccds = STM32446Tim2_ccds;
	return stm32446_tim_cr2;
}
STM32446TIM2_SMCR stm32446_tim2_smcr_inic(void)
{
	STM32446TIM2_SMCR stm32446_tim_smcr;
	// SMCR
	stm32446_tim_smcr.etp = STM32446Tim2_etp;
	stm32446_tim_smcr.ece = STM32446Tim2_ece;
	stm32446_tim_smcr.etps = STM32446Tim2_etps;
	stm32446_tim_smcr.etf = STM32446Tim2_etf;
	stm32446_tim_smcr.msm = STM32446Tim2_msm;
	stm32446_tim_smcr.ts = STM32446Tim2_ts;
	stm32446_tim_smcr.sms = STM32446Tim2_sms;
	return stm32446_tim_smcr;
}
STM32446TIM2_DIER stm32446_tim2_dier_inic(void)
{
	STM32446TIM2_DIER stm32446_tim_dier;
	// DIER
	stm32446_tim_dier.tde = STM32446Tim2_tde;
	stm32446_tim_dier.cc4de = STM32446Tim2_cc4de;
	stm32446_tim_dier.cc3de = STM32446Tim2_cc3de;
	stm32446_tim_dier.cc2de = STM32446Tim2_cc2de;
	stm32446_tim_dier.cc1de = STM32446Tim2_cc1de;
	stm32446_tim_dier.ude = STM32446Tim2_ude;
	stm32446_tim_dier.tie = STM32446Tim2_tie;
	stm32446_tim_dier.cc4ie = STM32446Tim2_cc4ie;
	stm32446_tim_dier.cc3ie = STM32446Tim2_cc3ie;
	stm32446_tim_dier.cc2ie = STM32446Tim2_cc2ie;
	stm32446_tim_dier.cc1ie = STM32446Tim2_cc1ie;
	stm32446_tim_dier.uie = STM32446Tim2_uie;
	return stm32446_tim_dier;
}
STM32446TIM2_SR stm32446_tim2_sr_inic(void)
{
	STM32446TIM2_SR stm32446_tim_sr;
	// SR
	stm32446_tim_sr.cc4of = STM32446Tim2_cc4of;
	stm32446_tim_sr.clear_cc4of = STM32446Tim2_clear_cc4of;
	stm32446_tim_sr.cc3of = STM32446Tim2_cc3of;
	stm32446_tim_sr.clear_cc3of = STM32446Tim2_clear_cc3of;
	stm32446_tim_sr.cc2of = STM32446Tim2_cc2of;
	stm32446_tim_sr.clear_cc2of = STM32446Tim2_clear_cc2of;
	stm32446_tim_sr.cc1of = STM32446Tim2_cc1of;
	stm32446_tim_sr.clear_cc1of = STM32446Tim2_clear_cc1of;
	stm32446_tim_sr.tif = STM32446Tim2_tif;
	stm32446_tim_sr.clear_tif = STM32446Tim2_clear_tif;
	stm32446_tim_sr.cc4if = STM32446Tim2_cc4if;
	stm32446_tim_sr.clear_cc4if = STM32446Tim2_clear_cc4if;
	stm32446_tim_sr.cc3if = STM32446Tim2_cc3if;
	stm32446_tim_sr.clear_cc3if = STM32446Tim2_clear_cc3if;
	stm32446_tim_sr.cc2if = STM32446Tim2_cc2if;
	stm32446_tim_sr.clear_cc2if = STM32446Tim2_clear_cc2if;
	stm32446_tim_sr.cc1if = STM32446Tim2_cc1if;
	stm32446_tim_sr.clear_cc1if = STM32446Tim2_clear_cc1if;
	stm32446_tim_sr.uif = STM32446Tim2_uif;
	stm32446_tim_sr.clear_uif = STM32446Tim2_clear_uif;
	return stm32446_tim_sr;
}
STM32446TIM2_EGR stm32446_tim2_egr_inic(void)
{
	STM32446TIM2_EGR stm32446_tim_egr;
	// EGR
	stm32446_tim_egr.tg = STM32446Tim2_tg;
	stm32446_tim_egr.cc4g = STM32446Tim2_cc4g;
	stm32446_tim_egr.cc3g = STM32446Tim2_cc3g;
	stm32446_tim_egr.cc2g = STM32446Tim2_cc2g;
	stm32446_tim_egr.cc1g = STM32446Tim2_cc1g;
	stm32446_tim_egr.ug = STM32446Tim2_ug;
	return stm32446_tim_egr;
}
STM32446TIM2_CCMR1 stm32446_tim2_ccmr1_inic(void)
{
	STM32446TIM2_CCMR1 stm32446_tim_ccmr1;
	// CCMR1
	stm32446_tim_ccmr1.oc2ce = STM32446Tim2_oc2ce;
	stm32446_tim_ccmr1.oc2m = STM32446Tim2_oc2m;
	stm32446_tim_ccmr1.ic2f = STM32446Tim2_ic2f;
	stm32446_tim_ccmr1.oc2pe = STM32446Tim2_oc2pe;
	stm32446_tim_ccmr1.oc2fe = STM32446Tim2_oc2fe;
	stm32446_tim_ccmr1.ic2psc = STM32446Tim2_ic2psc;
	stm32446_tim_ccmr1.cc2s = STM32446Tim2_cc2s;
	stm32446_tim_ccmr1.oc1ce = STM32446Tim2_oc1ce;
	stm32446_tim_ccmr1.oc1m = STM32446Tim2_oc1m;
	stm32446_tim_ccmr1.ic1f = STM32446Tim2_ic1f;
	stm32446_tim_ccmr1.oc1pe = STM32446Tim2_oc1pe;
	stm32446_tim_ccmr1.oc1fe = STM32446Tim2_oc1fe;
	stm32446_tim_ccmr1.ic1psc = STM32446Tim2_ic1psc;
	stm32446_tim_ccmr1.cc1s = STM32446Tim2_cc1s;
	return stm32446_tim_ccmr1;
}
STM32446TIM2_CCMR2 stm32446_tim2_ccmr2_inic(void)
{
	STM32446TIM2_CCMR2 stm32446_tim_ccmr2;
	// CCMR2
	stm32446_tim_ccmr2.oc4ce = STM32446Tim2_oc4ce;
	stm32446_tim_ccmr2.oc4m = STM32446Tim2_oc4m;
	stm32446_tim_ccmr2.ic4f = STM32446Tim2_ic4f;
	stm32446_tim_ccmr2.oc4pe = STM32446Tim2_oc4pe;
	stm32446_tim_ccmr2.oc4fe = STM32446Tim2_oc4fe;
	stm32446_tim_ccmr2.ic4psc = STM32446Tim2_ic4psc;
	stm32446_tim_ccmr2.cc4s = STM32446Tim2_cc4s;
	stm32446_tim_ccmr2.oc3ce = STM32446Tim2_oc3ce;
	stm32446_tim_ccmr2.oc3m = STM32446Tim2_oc3m;
	stm32446_tim_ccmr2.ic3f = STM32446Tim2_ic3f;
	stm32446_tim_ccmr2.oc3pe = STM32446Tim2_oc3pe;
	stm32446_tim_ccmr2.oc3fe = STM32446Tim2_oc3fe;
	stm32446_tim_ccmr2.ic3psc = STM32446Tim2_ic3psc;
	stm32446_tim_ccmr2.cc3s = STM32446Tim2_cc3s;
	return stm32446_tim_ccmr2;
}
STM32446TIM2_CCER stm32446_tim2_ccer_inic(void)
{
	STM32446TIM2_CCER stm32446_tim_ccer;
	// CCER
	stm32446_tim_ccer.cc4np = STM32446Tim2_cc4np;
	stm32446_tim_ccer.cc4p = STM32446Tim2_cc4p;
	stm32446_tim_ccer.cc4e = STM32446Tim2_cc4e;
	stm32446_tim_ccer.cc3np = STM32446Tim2_cc3np;
	stm32446_tim_ccer.cc3p = STM32446Tim2_cc3p;
	stm32446_tim_ccer.cc3e = STM32446Tim2_cc3e;
	stm32446_tim_ccer.cc2np = STM32446Tim2_cc2np;
	stm32446_tim_ccer.cc2p = STM32446Tim2_cc2p;
	stm32446_tim_ccer.cc2e = STM32446Tim2_cc2e;
	stm32446_tim_ccer.cc1np = STM32446Tim2_cc1np;
	stm32446_tim_ccer.cc1p = STM32446Tim2_cc1p;
	stm32446_tim_ccer.cc1e = STM32446Tim2_cc1e;
	return stm32446_tim_ccer;
}
STM32446TIM2_DCR stm32446_tim2_dcr_inic(void)
{
	STM32446TIM2_DCR stm32446_tim_dcr;
	// CCER
	stm32446_tim_dcr.dbl = STM32446Tim2_dbl;
	stm32446_tim_dcr.dba = STM32446Tim2_dba;
	return stm32446_tim_dcr;
}
/*** TIM2 INIC Procedure & Function Definition ***/
STM32446TIM2obj tim2_inic(void)
{
	STM32446TIM2obj stm32446_tim;
	stm32446_tim.reg = TIM2;
	// CLOCK
	stm32446_tim.clock = STM32446Tim2Clock;
	// NVIC
	stm32446_tim.nvic = STM32446Tim2Nvic;
	/*** TIM2 Bit Mapping Link ***/
	stm32446_tim.cr1 = stm32446_tim2_cr1_inic();
	stm32446_tim.cr2 = stm32446_tim2_cr2_inic();
	stm32446_tim.smcr = stm32446_tim2_smcr_inic();
	stm32446_tim.dier = stm32446_tim2_dier_inic();
	stm32446_tim.sr = stm32446_tim2_sr_inic();
	stm32446_tim.egr = stm32446_tim2_egr_inic();
	stm32446_tim.ccmr1 = stm32446_tim2_ccmr1_inic();
	stm32446_tim.ccmr2 = stm32446_tim2_ccmr2_inic();
	stm32446_tim.ccer = stm32446_tim2_ccer_inic();
	stm32446_tim.dcr = stm32446_tim2_dcr_inic();
	stm32446_tim.cnt = STM32446Tim2_cnt;
	stm32446_tim.get_cnt = STM32446Tim2_get_cnt;
	stm32446_tim.psc = STM32446Tim2_psc;
	stm32446_tim.arr = STM32446Tim2_arr;
	stm32446_tim.ccr1 = STM32446Tim2_ccr1;
	stm32446_tim.ccr2 = STM32446Tim2_ccr2;
	stm32446_tim.ccr3 = STM32446Tim2_ccr3;
	stm32446_tim.ccr4 = STM32446Tim2_ccr4;
	stm32446_tim.dmar = STM32446Tim2_dmab;
	stm32446_tim.or = STM32446Tim2_itr1_rmp;
	return stm32446_tim;
}
/*** TIM3 Auxiliar ***/
STM32446TIM3_CR1 stm32446_tim3_cr1_inic(void)
{
	STM32446TIM3_CR1 stm32446_tim_cr1;
	// CR1
	stm32446_tim_cr1.get_ckd = STM32446Tim3_get_ckd;
	stm32446_tim_cr1.apre = STM32446Tim3_set_apre;
	stm32446_tim_cr1.cms = STM32446Tim3_set_cms;
	stm32446_tim_cr1.dir = STM32446Tim3_set_dir;
	stm32446_tim_cr1.opm = STM32446Tim3_set_opm;
	stm32446_tim_cr1.urs = STM32446Tim3_set_urs;
	stm32446_tim_cr1.udis = STM32446Tim3_set_udis;
	stm32446_tim_cr1.cen = STM32446Tim3_cen;
	return stm32446_tim_cr1;
}
STM32446TIM3_CR2 stm32446_tim3_cr2_inic(void)
{
	STM32446TIM3_CR2 stm32446_tim_cr2;
	// CR2
	stm32446_tim_cr2.ti1s = STM32446Tim3_ti1s;
	stm32446_tim_cr2.mms = STM32446Tim3_mms;
	stm32446_tim_cr2.ccds = STM32446Tim3_ccds;
	return stm32446_tim_cr2;
}
STM32446TIM3_SMCR stm32446_tim3_smcr_inic(void)
{
	STM32446TIM3_SMCR stm32446_tim_smcr;
	// SMCR
	stm32446_tim_smcr.etp = STM32446Tim3_etp;
	stm32446_tim_smcr.ece = STM32446Tim3_ece;
	stm32446_tim_smcr.etps = STM32446Tim3_etps;
	stm32446_tim_smcr.etf = STM32446Tim3_etf;
	stm32446_tim_smcr.msm = STM32446Tim3_msm;
	stm32446_tim_smcr.ts = STM32446Tim3_ts;
	stm32446_tim_smcr.sms = STM32446Tim3_sms;
	return stm32446_tim_smcr;
}
STM32446TIM3_DIER stm32446_tim3_dier_inic(void)
{
	STM32446TIM3_DIER stm32446_tim_dier;
	// DIER
	stm32446_tim_dier.tde = STM32446Tim3_tde;
	stm32446_tim_dier.cc4de = STM32446Tim3_cc4de;
	stm32446_tim_dier.cc3de = STM32446Tim3_cc3de;
	stm32446_tim_dier.cc2de = STM32446Tim3_cc2de;
	stm32446_tim_dier.cc1de = STM32446Tim3_cc1de;
	stm32446_tim_dier.ude = STM32446Tim3_ude;
	stm32446_tim_dier.tie = STM32446Tim3_tie;
	stm32446_tim_dier.cc4ie = STM32446Tim3_cc4ie;
	stm32446_tim_dier.cc3ie = STM32446Tim3_cc3ie;
	stm32446_tim_dier.cc2ie = STM32446Tim3_cc2ie;
	stm32446_tim_dier.cc1ie = STM32446Tim3_cc1ie;
	stm32446_tim_dier.uie = STM32446Tim3_uie;
	return stm32446_tim_dier;
}
STM32446TIM3_SR stm32446_tim3_sr_inic(void)
{
	STM32446TIM3_SR stm32446_tim_sr;
	// SR
	stm32446_tim_sr.cc4of = STM32446Tim3_cc4of;
	stm32446_tim_sr.clear_cc4of = STM32446Tim3_clear_cc4of;
	stm32446_tim_sr.cc3of = STM32446Tim3_cc3of;
	stm32446_tim_sr.clear_cc3of = STM32446Tim3_clear_cc3of;
	stm32446_tim_sr.cc2of = STM32446Tim3_cc2of;
	stm32446_tim_sr.clear_cc2of = STM32446Tim3_clear_cc2of;
	stm32446_tim_sr.cc1of = STM32446Tim3_cc1of;
	stm32446_tim_sr.clear_cc1of = STM32446Tim3_clear_cc1of;
	stm32446_tim_sr.tif = STM32446Tim3_tif;
	stm32446_tim_sr.clear_tif = STM32446Tim3_clear_tif;
	stm32446_tim_sr.cc4if = STM32446Tim3_cc4if;
	stm32446_tim_sr.clear_cc4if = STM32446Tim3_clear_cc4if;
	stm32446_tim_sr.cc3if = STM32446Tim3_cc3if;
	stm32446_tim_sr.clear_cc3if = STM32446Tim3_clear_cc3if;
	stm32446_tim_sr.cc2if = STM32446Tim3_cc2if;
	stm32446_tim_sr.clear_cc2if = STM32446Tim3_clear_cc2if;
	stm32446_tim_sr.cc1if = STM32446Tim3_cc1if;
	stm32446_tim_sr.clear_cc1if = STM32446Tim3_clear_cc1if;
	stm32446_tim_sr.uif = STM32446Tim3_uif;
	stm32446_tim_sr.clear_uif = STM32446Tim3_clear_uif;
	return stm32446_tim_sr;
}
STM32446TIM3_EGR stm32446_tim3_egr_inic(void)
{
	STM32446TIM3_EGR stm32446_tim_egr;
	// EGR
	stm32446_tim_egr.tg = STM32446Tim3_tg;
	stm32446_tim_egr.cc4g = STM32446Tim3_cc4g;
	stm32446_tim_egr.cc3g = STM32446Tim3_cc3g;
	stm32446_tim_egr.cc2g = STM32446Tim3_cc2g;
	stm32446_tim_egr.cc1g = STM32446Tim3_cc1g;
	stm32446_tim_egr.ug = STM32446Tim3_ug;
	return stm32446_tim_egr;
}
STM32446TIM3_CCMR1 stm32446_tim3_ccmr1_inic(void)
{
	STM32446TIM3_CCMR1 stm32446_tim_ccmr1;
	// CCMR1
	stm32446_tim_ccmr1.oc2ce = STM32446Tim3_oc2ce;
	stm32446_tim_ccmr1.oc2m = STM32446Tim3_oc2m;
	stm32446_tim_ccmr1.ic2f = STM32446Tim3_ic2f;
	stm32446_tim_ccmr1.oc2pe = STM32446Tim3_oc2pe;
	stm32446_tim_ccmr1.oc2fe = STM32446Tim3_oc2fe;
	stm32446_tim_ccmr1.ic2psc = STM32446Tim3_ic2psc;
	stm32446_tim_ccmr1.cc2s = STM32446Tim3_cc2s;
	stm32446_tim_ccmr1.oc1ce = STM32446Tim3_oc1ce;
	stm32446_tim_ccmr1.oc1m = STM32446Tim3_oc1m;
	stm32446_tim_ccmr1.ic1f = STM32446Tim3_ic1f;
	stm32446_tim_ccmr1.oc1pe = STM32446Tim3_oc1pe;
	stm32446_tim_ccmr1.oc1fe = STM32446Tim3_oc1fe;
	stm32446_tim_ccmr1.ic1psc = STM32446Tim3_ic1psc;
	stm32446_tim_ccmr1.cc1s = STM32446Tim3_cc1s;
	return stm32446_tim_ccmr1;
}
STM32446TIM3_CCMR2 stm32446_tim3_ccmr2_inic(void)
{
	STM32446TIM3_CCMR2 stm32446_tim_ccmr2;
	// CCMR2
	stm32446_tim_ccmr2.oc4ce = STM32446Tim3_oc4ce;
	stm32446_tim_ccmr2.oc4m = STM32446Tim3_oc4m;
	stm32446_tim_ccmr2.ic4f = STM32446Tim3_ic4f;
	stm32446_tim_ccmr2.oc4pe = STM32446Tim3_oc4pe;
	stm32446_tim_ccmr2.oc4fe = STM32446Tim3_oc4fe;
	stm32446_tim_ccmr2.ic4psc = STM32446Tim3_ic4psc;
	stm32446_tim_ccmr2.cc4s = STM32446Tim3_cc4s;
	stm32446_tim_ccmr2.oc3ce = STM32446Tim3_oc3ce;
	stm32446_tim_ccmr2.oc3m = STM32446Tim3_oc3m;
	stm32446_tim_ccmr2.ic3f = STM32446Tim3_ic3f;
	stm32446_tim_ccmr2.oc3pe = STM32446Tim3_oc3pe;
	stm32446_tim_ccmr2.oc3fe = STM32446Tim3_oc3fe;
	stm32446_tim_ccmr2.ic3psc = STM32446Tim3_ic3psc;
	stm32446_tim_ccmr2.cc3s = STM32446Tim3_cc3s;
	return stm32446_tim_ccmr2;
}
STM32446TIM3_CCER stm32446_tim3_ccer_inic(void)
{
	STM32446TIM3_CCER stm32446_tim_ccer;
	// CCER
	stm32446_tim_ccer.cc4np = STM32446Tim3_cc4np;
	stm32446_tim_ccer.cc4p = STM32446Tim3_cc4p;
	stm32446_tim_ccer.cc4e = STM32446Tim3_cc4e;
	stm32446_tim_ccer.cc3np = STM32446Tim3_cc3np;
	stm32446_tim_ccer.cc3p = STM32446Tim3_cc3p;
	stm32446_tim_ccer.cc3e = STM32446Tim3_cc3e;
	stm32446_tim_ccer.cc2np = STM32446Tim3_cc2np;
	stm32446_tim_ccer.cc2p = STM32446Tim3_cc2p;
	stm32446_tim_ccer.cc2e = STM32446Tim3_cc2e;
	stm32446_tim_ccer.cc1np = STM32446Tim3_cc1np;
	stm32446_tim_ccer.cc1p = STM32446Tim3_cc1p;
	stm32446_tim_ccer.cc1e = STM32446Tim3_cc1e;
	return stm32446_tim_ccer;
}
STM32446TIM3_DCR stm32446_tim3_dcr_inic(void)
{
	STM32446TIM3_DCR stm32446_tim_dcr;
	// CCER
	stm32446_tim_dcr.dbl = STM32446Tim3_dbl;
	stm32446_tim_dcr.dba = STM32446Tim3_dba;
	return stm32446_tim_dcr;
}
/*** TIM3 INIC Procedure & Function Definition ***/
STM32446TIM3obj tim3_inic(void)
{
	STM32446TIM3obj stm32446_tim;
	stm32446_tim.reg = TIM3;
	// CLOCK
	stm32446_tim.clock = STM32446Tim3Clock;
	// NVIC
	stm32446_tim.nvic = STM32446Tim3Nvic;
	/*** TIM3 Bit Mapping Link ***/
	stm32446_tim.cr1 = stm32446_tim3_cr1_inic();
	stm32446_tim.cr2 = stm32446_tim3_cr2_inic();
	stm32446_tim.smcr = stm32446_tim3_smcr_inic();
	stm32446_tim.dier = stm32446_tim3_dier_inic();
	stm32446_tim.sr = stm32446_tim3_sr_inic();
	stm32446_tim.egr = stm32446_tim3_egr_inic();
	stm32446_tim.ccmr1 = stm32446_tim3_ccmr1_inic();
	stm32446_tim.ccmr2 = stm32446_tim3_ccmr2_inic();
	stm32446_tim.ccer = stm32446_tim3_ccer_inic();
	stm32446_tim.dcr = stm32446_tim3_dcr_inic();
	stm32446_tim.cnt = STM32446Tim3_cnt;
	stm32446_tim.get_cnt = STM32446Tim3_get_cnt;
	stm32446_tim.psc = STM32446Tim3_psc;
	stm32446_tim.arr = STM32446Tim3_arr;
	stm32446_tim.ccr1 = STM32446Tim3_ccr1;
	stm32446_tim.ccr2 = STM32446Tim3_ccr2;
	stm32446_tim.ccr3 = STM32446Tim3_ccr3;
	stm32446_tim.ccr4 = STM32446Tim3_ccr4;
	stm32446_tim.dmar = STM32446Tim3_dmab;
	return stm32446_tim;
}
/*** TIM4 Auxiliar ***/
STM32446TIM4_CR1 stm32446_tim4_cr1_inic(void)
{
	STM32446TIM4_CR1 stm32446_tim_cr1;
	// CR1
	stm32446_tim_cr1.get_ckd = STM32446Tim4_get_ckd;
	stm32446_tim_cr1.apre = STM32446Tim4_set_apre;
	stm32446_tim_cr1.cms = STM32446Tim4_set_cms;
	stm32446_tim_cr1.dir = STM32446Tim4_set_dir;
	stm32446_tim_cr1.opm = STM32446Tim4_set_opm;
	stm32446_tim_cr1.urs = STM32446Tim4_set_urs;
	stm32446_tim_cr1.udis = STM32446Tim4_set_udis;
	stm32446_tim_cr1.cen = STM32446Tim4_cen;
	return stm32446_tim_cr1;
}
STM32446TIM4_CR2 stm32446_tim4_cr2_inic(void)
{
	STM32446TIM4_CR2 stm32446_tim_cr2;
	// CR2
	stm32446_tim_cr2.ti1s = STM32446Tim4_ti1s;
	stm32446_tim_cr2.mms = STM32446Tim4_mms;
	stm32446_tim_cr2.ccds = STM32446Tim4_ccds;
	return stm32446_tim_cr2;
}
STM32446TIM4_SMCR stm32446_tim4_smcr_inic(void)
{
	STM32446TIM4_SMCR stm32446_tim_smcr;
	// SMCR
	stm32446_tim_smcr.etp = STM32446Tim4_etp;
	stm32446_tim_smcr.ece = STM32446Tim4_ece;
	stm32446_tim_smcr.etps = STM32446Tim4_etps;
	stm32446_tim_smcr.etf = STM32446Tim4_etf;
	stm32446_tim_smcr.msm = STM32446Tim4_msm;
	stm32446_tim_smcr.ts = STM32446Tim4_ts;
	stm32446_tim_smcr.sms = STM32446Tim4_sms;
	return stm32446_tim_smcr;
}
STM32446TIM4_DIER stm32446_tim4_dier_inic(void)
{
	STM32446TIM4_DIER stm32446_tim_dier;
	// DIER
	stm32446_tim_dier.tde = STM32446Tim4_tde;
	stm32446_tim_dier.cc4de = STM32446Tim4_cc4de;
	stm32446_tim_dier.cc3de = STM32446Tim4_cc3de;
	stm32446_tim_dier.cc2de = STM32446Tim4_cc2de;
	stm32446_tim_dier.cc1de = STM32446Tim4_cc1de;
	stm32446_tim_dier.ude = STM32446Tim4_ude;
	stm32446_tim_dier.tie = STM32446Tim4_tie;
	stm32446_tim_dier.cc4ie = STM32446Tim4_cc4ie;
	stm32446_tim_dier.cc3ie = STM32446Tim4_cc3ie;
	stm32446_tim_dier.cc2ie = STM32446Tim4_cc2ie;
	stm32446_tim_dier.cc1ie = STM32446Tim4_cc1ie;
	stm32446_tim_dier.uie = STM32446Tim4_uie;
	return stm32446_tim_dier;
}
STM32446TIM4_SR stm32446_tim4_sr_inic(void)
{
	STM32446TIM4_SR stm32446_tim_sr;
	// SR
	stm32446_tim_sr.cc4of = STM32446Tim4_cc4of;
	stm32446_tim_sr.clear_cc4of = STM32446Tim4_clear_cc4of;
	stm32446_tim_sr.cc3of = STM32446Tim4_cc3of;
	stm32446_tim_sr.clear_cc3of = STM32446Tim4_clear_cc3of;
	stm32446_tim_sr.cc2of = STM32446Tim4_cc2of;
	stm32446_tim_sr.clear_cc2of = STM32446Tim4_clear_cc2of;
	stm32446_tim_sr.cc1of = STM32446Tim4_cc1of;
	stm32446_tim_sr.clear_cc1of = STM32446Tim4_clear_cc1of;
	stm32446_tim_sr.tif = STM32446Tim4_tif;
	stm32446_tim_sr.clear_tif = STM32446Tim4_clear_tif;
	stm32446_tim_sr.cc4if = STM32446Tim4_cc4if;
	stm32446_tim_sr.clear_cc4if = STM32446Tim4_clear_cc4if;
	stm32446_tim_sr.cc3if = STM32446Tim4_cc3if;
	stm32446_tim_sr.clear_cc3if = STM32446Tim4_clear_cc3if;
	stm32446_tim_sr.cc2if = STM32446Tim4_cc2if;
	stm32446_tim_sr.clear_cc2if = STM32446Tim4_clear_cc2if;
	stm32446_tim_sr.cc1if = STM32446Tim4_cc1if;
	stm32446_tim_sr.clear_cc1if = STM32446Tim4_clear_cc1if;
	stm32446_tim_sr.uif = STM32446Tim4_uif;
	stm32446_tim_sr.clear_uif = STM32446Tim4_clear_uif;
	return stm32446_tim_sr;
}
STM32446TIM4_EGR stm32446_tim4_egr_inic(void)
{
	STM32446TIM4_EGR stm32446_tim_egr;
	// EGR
	stm32446_tim_egr.tg = STM32446Tim4_tg;
	stm32446_tim_egr.cc4g = STM32446Tim4_cc4g;
	stm32446_tim_egr.cc3g = STM32446Tim4_cc3g;
	stm32446_tim_egr.cc2g = STM32446Tim4_cc2g;
	stm32446_tim_egr.cc1g = STM32446Tim4_cc1g;
	stm32446_tim_egr.ug = STM32446Tim4_ug;
	return stm32446_tim_egr;
}
STM32446TIM4_CCMR1 stm32446_tim4_ccmr1_inic(void)
{
	STM32446TIM4_CCMR1 stm32446_tim_ccmr1;
	// CCMR1
	stm32446_tim_ccmr1.oc2ce = STM32446Tim4_oc2ce;
	stm32446_tim_ccmr1.oc2m = STM32446Tim4_oc2m;
	stm32446_tim_ccmr1.ic2f = STM32446Tim4_ic2f;
	stm32446_tim_ccmr1.oc2pe = STM32446Tim4_oc2pe;
	stm32446_tim_ccmr1.oc2fe = STM32446Tim4_oc2fe;
	stm32446_tim_ccmr1.ic2psc = STM32446Tim4_ic2psc;
	stm32446_tim_ccmr1.cc2s = STM32446Tim4_cc2s;
	stm32446_tim_ccmr1.oc1ce = STM32446Tim4_oc1ce;
	stm32446_tim_ccmr1.oc1m = STM32446Tim4_oc1m;
	stm32446_tim_ccmr1.ic1f = STM32446Tim4_ic1f;
	stm32446_tim_ccmr1.oc1pe = STM32446Tim4_oc1pe;
	stm32446_tim_ccmr1.oc1fe = STM32446Tim4_oc1fe;
	stm32446_tim_ccmr1.ic1psc = STM32446Tim4_ic1psc;
	stm32446_tim_ccmr1.cc1s = STM32446Tim4_cc1s;
	return stm32446_tim_ccmr1;
}
STM32446TIM4_CCMR2 stm32446_tim4_ccmr2_inic(void)
{
	STM32446TIM4_CCMR2 stm32446_tim_ccmr2;
	// CCMR2
	stm32446_tim_ccmr2.oc4ce = STM32446Tim4_oc4ce;
	stm32446_tim_ccmr2.oc4m = STM32446Tim4_oc4m;
	stm32446_tim_ccmr2.ic4f = STM32446Tim4_ic4f;
	stm32446_tim_ccmr2.oc4pe = STM32446Tim4_oc4pe;
	stm32446_tim_ccmr2.oc4fe = STM32446Tim4_oc4fe;
	stm32446_tim_ccmr2.ic4psc = STM32446Tim4_ic4psc;
	stm32446_tim_ccmr2.cc4s = STM32446Tim4_cc4s;
	stm32446_tim_ccmr2.oc3ce = STM32446Tim4_oc3ce;
	stm32446_tim_ccmr2.oc3m = STM32446Tim4_oc3m;
	stm32446_tim_ccmr2.ic3f = STM32446Tim4_ic3f;
	stm32446_tim_ccmr2.oc3pe = STM32446Tim4_oc3pe;
	stm32446_tim_ccmr2.oc3fe = STM32446Tim4_oc3fe;
	stm32446_tim_ccmr2.ic3psc = STM32446Tim4_ic3psc;
	stm32446_tim_ccmr2.cc3s = STM32446Tim4_cc3s;
	return stm32446_tim_ccmr2;
}
STM32446TIM4_CCER stm32446_tim4_ccer_inic(void)
{
	STM32446TIM4_CCER stm32446_tim_ccer;
	// CCER
	stm32446_tim_ccer.cc4np = STM32446Tim4_cc4np;
	stm32446_tim_ccer.cc4p = STM32446Tim4_cc4p;
	stm32446_tim_ccer.cc4e = STM32446Tim4_cc4e;
	stm32446_tim_ccer.cc3np = STM32446Tim4_cc3np;
	stm32446_tim_ccer.cc3p = STM32446Tim4_cc3p;
	stm32446_tim_ccer.cc3e = STM32446Tim4_cc3e;
	stm32446_tim_ccer.cc2np = STM32446Tim4_cc2np;
	stm32446_tim_ccer.cc2p = STM32446Tim4_cc2p;
	stm32446_tim_ccer.cc2e = STM32446Tim4_cc2e;
	stm32446_tim_ccer.cc1np = STM32446Tim4_cc1np;
	stm32446_tim_ccer.cc1p = STM32446Tim4_cc1p;
	stm32446_tim_ccer.cc1e = STM32446Tim4_cc1e;
	return stm32446_tim_ccer;
}
STM32446TIM4_DCR stm32446_tim4_dcr_inic(void)
{
	STM32446TIM4_DCR stm32446_tim_dcr;
	// CCER
	stm32446_tim_dcr.dbl = STM32446Tim4_dbl;
	stm32446_tim_dcr.dba = STM32446Tim4_dba;
	return stm32446_tim_dcr;
}
/*** TIM4 INIC Procedure & Function Definition ***/
STM32446TIM4obj tim4_inic(void)
{
	STM32446TIM4obj stm32446_tim;
	stm32446_tim.reg = TIM4;
	// CLOCK
	stm32446_tim.clock = STM32446Tim4Clock;
	// NVIC
	stm32446_tim.nvic = STM32446Tim4Nvic;
	/*** TIM4 Bit Mapping Link ***/
	stm32446_tim.cr1 = stm32446_tim4_cr1_inic();
	stm32446_tim.cr2 = stm32446_tim4_cr2_inic();
	stm32446_tim.smcr = stm32446_tim4_smcr_inic();
	stm32446_tim.dier = stm32446_tim4_dier_inic();
	stm32446_tim.sr = stm32446_tim4_sr_inic();
	stm32446_tim.egr = stm32446_tim4_egr_inic();
	stm32446_tim.ccmr1 = stm32446_tim4_ccmr1_inic();
	stm32446_tim.ccmr2 = stm32446_tim4_ccmr2_inic();
	stm32446_tim.ccer = stm32446_tim4_ccer_inic();
	stm32446_tim.dcr = stm32446_tim4_dcr_inic();
	stm32446_tim.cnt = STM32446Tim4_cnt;
	stm32446_tim.get_cnt = STM32446Tim4_get_cnt;
	stm32446_tim.psc = STM32446Tim4_psc;
	stm32446_tim.arr = STM32446Tim4_arr;
	stm32446_tim.ccr1 = STM32446Tim4_ccr1;
	stm32446_tim.ccr2 = STM32446Tim4_ccr2;
	stm32446_tim.ccr3 = STM32446Tim4_ccr3;
	stm32446_tim.ccr4 = STM32446Tim4_ccr4;
	stm32446_tim.dmar = STM32446Tim4_dmab;
	return stm32446_tim;
}
/*** TIM5 Auxiliar ***/
STM32446TIM5_CR1 stm32446_tim5_cr1_inic(void)
{
	STM32446TIM5_CR1 stm32446_tim_cr1;
	// CR1
	stm32446_tim_cr1.get_ckd = STM32446Tim5_get_ckd;
	stm32446_tim_cr1.apre = STM32446Tim5_set_apre;
	stm32446_tim_cr1.cms = STM32446Tim5_set_cms;
	stm32446_tim_cr1.dir = STM32446Tim5_set_dir;
	stm32446_tim_cr1.opm = STM32446Tim5_set_opm;
	stm32446_tim_cr1.urs = STM32446Tim5_set_urs;
	stm32446_tim_cr1.udis = STM32446Tim5_set_udis;
	stm32446_tim_cr1.cen = STM32446Tim5_cen;
	return stm32446_tim_cr1;
}
STM32446TIM5_CR2 stm32446_tim5_cr2_inic(void)
{
	STM32446TIM5_CR2 stm32446_tim_cr2;
	// CR2
	stm32446_tim_cr2.ti1s = STM32446Tim5_ti1s;
	stm32446_tim_cr2.mms = STM32446Tim5_mms;
	stm32446_tim_cr2.ccds = STM32446Tim5_ccds;
	return stm32446_tim_cr2;
}
STM32446TIM5_SMCR stm32446_tim5_smcr_inic(void)
{
	STM32446TIM5_SMCR stm32446_tim_smcr;
	// SMCR
	stm32446_tim_smcr.etp = STM32446Tim5_etp;
	stm32446_tim_smcr.ece = STM32446Tim5_ece;
	stm32446_tim_smcr.etps = STM32446Tim5_etps;
	stm32446_tim_smcr.etf = STM32446Tim5_etf;
	stm32446_tim_smcr.msm = STM32446Tim5_msm;
	stm32446_tim_smcr.ts = STM32446Tim5_ts;
	stm32446_tim_smcr.sms = STM32446Tim5_sms;
	return stm32446_tim_smcr;
}
STM32446TIM5_DIER stm32446_tim5_dier_inic(void)
{
	STM32446TIM5_DIER stm32446_tim_dier;
	// DIER
	stm32446_tim_dier.tde = STM32446Tim5_tde;
	stm32446_tim_dier.cc4de = STM32446Tim5_cc4de;
	stm32446_tim_dier.cc3de = STM32446Tim5_cc3de;
	stm32446_tim_dier.cc2de = STM32446Tim5_cc2de;
	stm32446_tim_dier.cc1de = STM32446Tim5_cc1de;
	stm32446_tim_dier.ude = STM32446Tim5_ude;
	stm32446_tim_dier.tie = STM32446Tim5_tie;
	stm32446_tim_dier.cc4ie = STM32446Tim5_cc4ie;
	stm32446_tim_dier.cc3ie = STM32446Tim5_cc3ie;
	stm32446_tim_dier.cc2ie = STM32446Tim5_cc2ie;
	stm32446_tim_dier.cc1ie = STM32446Tim5_cc1ie;
	stm32446_tim_dier.uie = STM32446Tim5_uie;
	return stm32446_tim_dier;
}
STM32446TIM5_SR stm32446_tim5_sr_inic(void)
{
	STM32446TIM5_SR stm32446_tim_sr;
	// SR
	stm32446_tim_sr.cc4of = STM32446Tim5_cc4of;
	stm32446_tim_sr.clear_cc4of = STM32446Tim5_clear_cc4of;
	stm32446_tim_sr.cc3of = STM32446Tim5_cc3of;
	stm32446_tim_sr.clear_cc3of = STM32446Tim5_clear_cc3of;
	stm32446_tim_sr.cc2of = STM32446Tim5_cc2of;
	stm32446_tim_sr.clear_cc2of = STM32446Tim5_clear_cc2of;
	stm32446_tim_sr.cc1of = STM32446Tim5_cc1of;
	stm32446_tim_sr.clear_cc1of = STM32446Tim5_clear_cc1of;
	stm32446_tim_sr.tif = STM32446Tim5_tif;
	stm32446_tim_sr.clear_tif = STM32446Tim5_clear_tif;
	stm32446_tim_sr.cc4if = STM32446Tim5_cc4if;
	stm32446_tim_sr.clear_cc4if = STM32446Tim5_clear_cc4if;
	stm32446_tim_sr.cc3if = STM32446Tim5_cc3if;
	stm32446_tim_sr.clear_cc3if = STM32446Tim5_clear_cc3if;
	stm32446_tim_sr.cc2if = STM32446Tim5_cc2if;
	stm32446_tim_sr.clear_cc2if = STM32446Tim5_clear_cc2if;
	stm32446_tim_sr.cc1if = STM32446Tim5_cc1if;
	stm32446_tim_sr.clear_cc1if = STM32446Tim5_clear_cc1if;
	stm32446_tim_sr.uif = STM32446Tim5_uif;
	stm32446_tim_sr.clear_uif = STM32446Tim5_clear_uif;
	return stm32446_tim_sr;
}
STM32446TIM5_EGR stm32446_tim5_egr_inic(void)
{
	STM32446TIM5_EGR stm32446_tim_egr;
	// EGR
	stm32446_tim_egr.tg = STM32446Tim5_tg;
	stm32446_tim_egr.cc4g = STM32446Tim5_cc4g;
	stm32446_tim_egr.cc3g = STM32446Tim5_cc3g;
	stm32446_tim_egr.cc2g = STM32446Tim5_cc2g;
	stm32446_tim_egr.cc1g = STM32446Tim5_cc1g;
	stm32446_tim_egr.ug = STM32446Tim5_ug;
	return stm32446_tim_egr;
}
STM32446TIM5_CCMR1 stm32446_tim5_ccmr1_inic(void)
{
	STM32446TIM5_CCMR1 stm32446_tim_ccmr1;
	// CCMR1
	stm32446_tim_ccmr1.oc2ce = STM32446Tim5_oc2ce;
	stm32446_tim_ccmr1.oc2m = STM32446Tim5_oc2m;
	stm32446_tim_ccmr1.ic2f = STM32446Tim5_ic2f;
	stm32446_tim_ccmr1.oc2pe = STM32446Tim5_oc2pe;
	stm32446_tim_ccmr1.oc2fe = STM32446Tim5_oc2fe;
	stm32446_tim_ccmr1.ic2psc = STM32446Tim5_ic2psc;
	stm32446_tim_ccmr1.cc2s = STM32446Tim5_cc2s;
	stm32446_tim_ccmr1.oc1ce = STM32446Tim5_oc1ce;
	stm32446_tim_ccmr1.oc1m = STM32446Tim5_oc1m;
	stm32446_tim_ccmr1.ic1f = STM32446Tim5_ic1f;
	stm32446_tim_ccmr1.oc1pe = STM32446Tim5_oc1pe;
	stm32446_tim_ccmr1.oc1fe = STM32446Tim5_oc1fe;
	stm32446_tim_ccmr1.ic1psc = STM32446Tim5_ic1psc;
	stm32446_tim_ccmr1.cc1s = STM32446Tim5_cc1s;
	return stm32446_tim_ccmr1;
}
STM32446TIM5_CCMR2 stm32446_tim5_ccmr2_inic(void)
{
	STM32446TIM5_CCMR2 stm32446_tim_ccmr2;
	// CCMR2
	stm32446_tim_ccmr2.oc4ce = STM32446Tim5_oc4ce;
	stm32446_tim_ccmr2.oc4m = STM32446Tim5_oc4m;
	stm32446_tim_ccmr2.ic4f = STM32446Tim5_ic4f;
	stm32446_tim_ccmr2.oc4pe = STM32446Tim5_oc4pe;
	stm32446_tim_ccmr2.oc4fe = STM32446Tim5_oc4fe;
	stm32446_tim_ccmr2.ic4psc = STM32446Tim5_ic4psc;
	stm32446_tim_ccmr2.cc4s = STM32446Tim5_cc4s;
	stm32446_tim_ccmr2.oc3ce = STM32446Tim5_oc3ce;
	stm32446_tim_ccmr2.oc3m = STM32446Tim5_oc3m;
	stm32446_tim_ccmr2.ic3f = STM32446Tim5_ic3f;
	stm32446_tim_ccmr2.oc3pe = STM32446Tim5_oc3pe;
	stm32446_tim_ccmr2.oc3fe = STM32446Tim5_oc3fe;
	stm32446_tim_ccmr2.ic3psc = STM32446Tim5_ic3psc;
	stm32446_tim_ccmr2.cc3s = STM32446Tim5_cc3s;
	return stm32446_tim_ccmr2;
}
STM32446TIM5_CCER stm32446_tim5_ccer_inic(void)
{
	STM32446TIM5_CCER stm32446_tim_ccer;
	// CCER
	stm32446_tim_ccer.cc4np = STM32446Tim5_cc4np;
	stm32446_tim_ccer.cc4p = STM32446Tim5_cc4p;
	stm32446_tim_ccer.cc4e = STM32446Tim5_cc4e;
	stm32446_tim_ccer.cc3np = STM32446Tim5_cc3np;
	stm32446_tim_ccer.cc3p = STM32446Tim5_cc3p;
	stm32446_tim_ccer.cc3e = STM32446Tim5_cc3e;
	stm32446_tim_ccer.cc2np = STM32446Tim5_cc2np;
	stm32446_tim_ccer.cc2p = STM32446Tim5_cc2p;
	stm32446_tim_ccer.cc2e = STM32446Tim5_cc2e;
	stm32446_tim_ccer.cc1np = STM32446Tim5_cc1np;
	stm32446_tim_ccer.cc1p = STM32446Tim5_cc1p;
	stm32446_tim_ccer.cc1e = STM32446Tim5_cc1e;
	return stm32446_tim_ccer;
}
STM32446TIM5_DCR stm32446_tim5_dcr_inic(void)
{
	STM32446TIM5_DCR stm32446_tim_dcr;
	// CCER
	stm32446_tim_dcr.dbl = STM32446Tim5_dbl;
	stm32446_tim_dcr.dba = STM32446Tim5_dba;
	return stm32446_tim_dcr;
}
/*** TIM5 INIC Procedure & Function Definition ***/
STM32446TIM5obj tim5_inic(void)
{
	STM32446TIM5obj stm32446_tim;
	stm32446_tim.reg = TIM5;
	// CLOCK
	stm32446_tim.clock = STM32446Tim5Clock;
	// NVIC
	stm32446_tim.nvic = STM32446Tim5Nvic;
	/*** TIM5 Bit Mapping Link ***/
	stm32446_tim.cr1 = stm32446_tim5_cr1_inic();
	stm32446_tim.cr2 = stm32446_tim5_cr2_inic();
	stm32446_tim.smcr = stm32446_tim5_smcr_inic();
	stm32446_tim.dier = stm32446_tim5_dier_inic();
	stm32446_tim.sr = stm32446_tim5_sr_inic();
	stm32446_tim.egr = stm32446_tim5_egr_inic();
	stm32446_tim.ccmr1 = stm32446_tim5_ccmr1_inic();
	stm32446_tim.ccmr2 = stm32446_tim5_ccmr2_inic();
	stm32446_tim.ccer = stm32446_tim5_ccer_inic();
	stm32446_tim.dcr = stm32446_tim5_dcr_inic();
	stm32446_tim.cnt = STM32446Tim5_cnt;
	stm32446_tim.get_cnt = STM32446Tim5_get_cnt;
	stm32446_tim.psc = STM32446Tim5_psc;
	stm32446_tim.arr = STM32446Tim5_arr;
	stm32446_tim.ccr1 = STM32446Tim5_ccr1;
	stm32446_tim.ccr2 = STM32446Tim5_ccr2;
	stm32446_tim.ccr3 = STM32446Tim5_ccr3;
	stm32446_tim.ccr4 = STM32446Tim5_ccr4;
	stm32446_tim.dmar = STM32446Tim5_dmab;
	stm32446_tim.or = STM32446Tim5_ti4_rmp;
	return stm32446_tim;
}
/*** File Procedure & Function Definition***/
uint32_t tim2to5_readreg(uint32_t reg, uint32_t size_block, uint32_t bit)
{
	if(bit > 31){ bit = 0;} if(size_block > 32){ size_block = 32;}
	uint32_t value = reg;
	uint32_t mask = (unsigned int)((1 << size_block) - 1);
	value &= (mask << bit);
	value = (value >> bit);
	return value;
}
void tim2to5_writereg(volatile uint32_t* reg, uint32_t size_block, uint32_t bit, uint32_t data)
{
	if(bit > 31){ bit = 0;} if(size_block > 32){ size_block = 32;}
	uint32_t value = data;
	uint32_t mask = (unsigned int)((1 << size_block) - 1);
	value &= mask;
	value = (value << bit);
	*reg = value;
}
void tim2to5_setreg(volatile uint32_t* reg, uint32_t size_block, uint32_t bit, uint32_t data)
{
	if(bit > 31){ bit = 0;} if(size_block > 32){ size_block = 32;}
	uint32_t value = data;
	uint32_t mask = (unsigned int)((1 << size_block) - 1);
	value &= mask;
	*reg &= ~(mask << bit);
	*reg |= (value << bit);
}
void tim2to5_setbit(volatile uint32_t* reg, uint32_t size_block, uint32_t bit, uint32_t data)
{
	uint32_t n = 0;
	if(bit > 31){ n = bit/32; bit = bit - (n * 32); } if(size_block > 32){ size_block = 32;}
	uint32_t value = data;
	uint32_t mask = (unsigned int)((1 << size_block) - 1);
	value &= mask;
	*(reg + n ) &= ~(mask << bit);
	*(reg + n ) |= (value << bit);
}
uint32_t tim2to5_getsetbit(volatile uint32_t* reg, uint32_t size_block, uint32_t bit)
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


