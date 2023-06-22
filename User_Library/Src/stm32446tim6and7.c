/******************************************************************************
	STM32 446 TIM 6 and 7
Author: Sergio Santos 
	<sergio.salazar.santos@gmail.com>
License: GNU General Public License
Hardware: STM32-446
Date: 22062023
Comment:
	
*******************************************************************************/
/*** File Library ***/
#include "stm32446mapping.h"
#include "stm32446tim6and7.h"

/*** File Procedure & Function Header ***/
uint32_t tim6and7_readreg(uint32_t reg, uint32_t size_block, uint32_t bit);
void tim6and7_writereg(volatile uint32_t* reg, uint32_t size_block, uint32_t bit, uint32_t data);
void tim6and7_setreg(volatile uint32_t* reg, uint32_t size_block, uint32_t bit, uint32_t data);
void tim6and7_setbit(volatile uint32_t* reg, uint32_t size_block, uint32_t bit, uint32_t data);
uint32_t tim6and7_getsetbit(volatile uint32_t* reg, uint32_t size_block, uint32_t bit);
/*** Auxiliar ***/
STM32446TIM6_CR1 stm32446_tim6_cr1_inic(void);
STM32446TIM6_CR2 stm32446_tim6_cr2_inic(void);
STM32446TIM6_DIER stm32446_tim6_dier_inic(void);
STM32446TIM6_SR stm32446_tim6_sr_inic(void);
STM32446TIM6_EGR stm32446_tim6_egr_inic(void);
STM32446TIM7_CR1 stm32446_tim7_cr1_inic(void);
STM32446TIM7_CR2 stm32446_tim7_cr2_inic(void);
STM32446TIM7_DIER stm32446_tim7_dier_inic(void);
STM32446TIM7_SR stm32446_tim7_sr_inic(void);
STM32446TIM7_EGR stm32446_tim7_egr_inic(void);
/*** TIMER Procedure & Function Definition ***/
/************/
/*** TIM6 ***/
/************/
void STM32446Tim6Clock(uint8_t bool)
{
	if(bool){
		RCC->APB1ENR |= (1 << 4); // timer 6 clock enabled
	}else{
		RCC->APB1ENR &= ~(1 << 4); //timer 6 clock disabled
	}
}
void STM32446Tim6Nvic(uint8_t bool)
{ // 54
	if(bool){tim6and7_setbit(NVIC->ISER, 1, 54, 1);}else{tim6and7_setbit(NVIC->ICER, 1, 54, 1);}
}
/************************/
/*** TIM6 Bit Mapping ***/
/************************/
// CR1
void STM32446Tim6_set_apre(uint8_t bool)
{
	tim6and7_setreg(&TIM6->CR1, 1, 7, bool);
}
void STM32446Tim6_set_opm(uint8_t bool)
{
	tim6and7_setreg(&TIM6->CR1, 1, 3, bool);
}
void STM32446Tim6_set_urs(uint8_t bool)
{
	tim6and7_setreg(&TIM6->CR1, 1, 2, bool);
}
void STM32446Tim6_set_udis(uint8_t bool)
{
	tim6and7_setreg(&TIM6->CR1, 1, 1, bool);
}
void STM32446Tim6_cen(uint8_t bool)
{
	tim6and7_setreg(&TIM6->CR1, 1, 0, bool);
}
// CR2
void STM32446Tim6_mms(uint8_t value)
{
	tim6and7_setreg(&TIM6->CR2, 3, 4, value);
}
// DIER
void STM32446Tim6_ude(uint8_t bool)
{
	tim6and7_setreg(&TIM6->DIER, 1, 8, bool);
}
void STM32446Tim6_uie(uint8_t bool)
{
	tim6and7_setreg(&TIM6->DIER, 1, 0, bool);
}
// SR
uint8_t STM32446Tim6_uif(void)
{
	return tim6and7_readreg(TIM6->SR, 1, 0);
}
void STM32446Tim6_clear_uif(void)
{
	tim6and7_setreg(&TIM6->SR, 1, 0, 0);
}
// EGR
void STM32446Tim6_ug(void)
{
	tim6and7_setreg(&TIM6->EGR, 1, 0, 1);
}
// CNT
void STM32446Tim6_cnt(uint16_t value)
{
	TIM6->CNT = value;
}
uint16_t STM32446Tim6_get_cnt(void)
{
	return TIM6->CNT;
}
// PSC
void STM32446Tim6_psc(uint16_t value)
{
	TIM6->PSC = value;
}
// ARR
void STM32446Tim6_arr(uint16_t value)
{
	TIM6->ARR = value;
}
/************/
/*** TIM7 ***/
/************/
void STM32446Tim7Clock(uint8_t bool)
{
	if(bool){
		RCC->APB1ENR |= (1 << 5); // timer 7 clock enabled
	}else{
		RCC->APB1ENR &= ~(1 << 5); //timer 7 clock disabled
	}
}
void STM32446Tim7Nvic(uint8_t bool)
{ // 55
	if(bool){tim6and7_setbit(NVIC->ISER, 1, 55, 1);}else{tim6and7_setbit(NVIC->ICER, 1, 55, 1);}
}
/************************/
/*** TIM7 Bit Mapping ***/
/************************/
// CR1
void STM32446Tim7_set_apre(uint8_t bool)
{
	tim6and7_setreg(&TIM7->CR1, 1, 7, bool);
}
void STM32446Tim7_set_opm(uint8_t bool)
{
	tim6and7_setreg(&TIM7->CR1, 1, 3, bool);
}
void STM32446Tim7_set_urs(uint8_t bool)
{
	tim6and7_setreg(&TIM7->CR1, 1, 2, bool);
}
void STM32446Tim7_set_udis(uint8_t bool)
{
	tim6and7_setreg(&TIM7->CR1, 1, 1, bool);
}
void STM32446Tim7_cen(uint8_t bool)
{
	tim6and7_setreg(&TIM7->CR1, 1, 0, bool);
}
// CR2
void STM32446Tim7_mms(uint8_t value)
{
	tim6and7_setreg(&TIM7->CR2, 3, 4, value);
}
// DIER
void STM32446Tim7_ude(uint8_t bool)
{
	tim6and7_setreg(&TIM7->DIER, 1, 8, bool);
}
void STM32446Tim7_uie(uint8_t bool)
{
	tim6and7_setreg(&TIM7->DIER, 1, 0, bool);
}
// SR
uint8_t STM32446Tim7_uif(void)
{
	return tim6and7_readreg(TIM7->SR, 1, 0);
}
void STM32446Tim7_clear_uif(void)
{
	tim6and7_setreg(&TIM7->SR, 1, 0, 0);
}
// EGR
void STM32446Tim7_ug(void)
{
	tim6and7_setreg(&TIM7->EGR, 1, 0, 1);
}
// CNT
void STM32446Tim7_cnt(uint16_t value)
{
	TIM7->CNT = value;
}
uint16_t STM32446Tim7_get_cnt(void)
{
	return TIM7->CNT;
}
// PSC
void STM32446Tim7_psc(uint16_t value)
{
	TIM7->PSC = value;
}
// ARR
void STM32446Tim7_arr(uint16_t value)
{
	TIM7->ARR = value;
}
/********************************************/
/*** INIC Procedure & Function Definition ***/
/********************************************/
/*** TIM6 Auxiliar ***/
STM32446TIM6_CR1 stm32446_tim6_cr1_inic(void)
{
	STM32446TIM6_CR1 stm32446_tim_cr1;
	// CR1
	stm32446_tim_cr1.apre = STM32446Tim6_set_apre;
	stm32446_tim_cr1.opm = STM32446Tim6_set_opm;
	stm32446_tim_cr1.urs = STM32446Tim6_set_urs;
	stm32446_tim_cr1.udis = STM32446Tim6_set_udis;
	stm32446_tim_cr1.cen = STM32446Tim6_cen;
	return stm32446_tim_cr1;
}
STM32446TIM6_CR2 stm32446_tim6_cr2_inic(void)
{
	STM32446TIM6_CR2 stm32446_tim_cr2;
	// CR2
	stm32446_tim_cr2.mms = STM32446Tim6_mms;
	return stm32446_tim_cr2;
}
STM32446TIM6_DIER stm32446_tim6_dier_inic(void)
{
	STM32446TIM6_DIER stm32446_tim_dier;
	// DIER
	stm32446_tim_dier.ude = STM32446Tim6_ude;
	stm32446_tim_dier.uie = STM32446Tim6_uie;
	return stm32446_tim_dier;
}
STM32446TIM6_SR stm32446_tim6_sr_inic(void)
{
	STM32446TIM6_SR stm32446_tim_sr;
	// SR
	stm32446_tim_sr.uif = STM32446Tim6_uif;
	stm32446_tim_sr.clear_uif = STM32446Tim6_clear_uif;
	return stm32446_tim_sr;
}
STM32446TIM6_EGR stm32446_tim6_egr_inic(void)
{
	STM32446TIM6_EGR stm32446_tim_egr;
	// EGR
	stm32446_tim_egr.ug = STM32446Tim6_ug;
	return stm32446_tim_egr;
}
/*** TIM6 INIC Procedure & Function Definition ***/
STM32446TIM6obj tim6_inic(void)
{
	STM32446TIM6obj stm32446_tim;
	stm32446_tim.reg = TIM6;
	// CLOCK
	stm32446_tim.clock = STM32446Tim6Clock;
	// NVIC
	stm32446_tim.nvic = STM32446Tim6Nvic;
	/*** TIM6 Bit Mapping Link ***/
	stm32446_tim.cr1 = stm32446_tim6_cr1_inic();
	stm32446_tim.cr2 = stm32446_tim6_cr2_inic();
	stm32446_tim.dier = stm32446_tim6_dier_inic();
	stm32446_tim.sr = stm32446_tim6_sr_inic();
	stm32446_tim.egr = stm32446_tim6_egr_inic();
	stm32446_tim.cnt = STM32446Tim6_cnt;
	stm32446_tim.get_cnt = STM32446Tim6_get_cnt;
	stm32446_tim.psc = STM32446Tim6_psc;
	stm32446_tim.arr = STM32446Tim6_arr;
	return stm32446_tim;
}
/*** TIM7 Auxiliar ***/
STM32446TIM7_CR1 stm32446_tim7_cr1_inic(void)
{
	STM32446TIM7_CR1 stm32446_tim_cr1;
	// CR1
	stm32446_tim_cr1.apre = STM32446Tim7_set_apre;
	stm32446_tim_cr1.opm = STM32446Tim7_set_opm;
	stm32446_tim_cr1.urs = STM32446Tim7_set_urs;
	stm32446_tim_cr1.udis = STM32446Tim7_set_udis;
	stm32446_tim_cr1.cen = STM32446Tim7_cen;
	return stm32446_tim_cr1;
}
STM32446TIM7_CR2 stm32446_tim7_cr2_inic(void)
{
	STM32446TIM7_CR2 stm32446_tim_cr2;
	// CR2
	stm32446_tim_cr2.mms = STM32446Tim7_mms;
	return stm32446_tim_cr2;
}
STM32446TIM7_DIER stm32446_tim7_dier_inic(void)
{
	STM32446TIM7_DIER stm32446_tim_dier;
	// DIER
	stm32446_tim_dier.ude = STM32446Tim7_ude;
	stm32446_tim_dier.uie = STM32446Tim7_uie;
	return stm32446_tim_dier;
}
STM32446TIM7_SR stm32446_tim7_sr_inic(void)
{
	STM32446TIM7_SR stm32446_tim_sr;
	// SR
	stm32446_tim_sr.uif = STM32446Tim7_uif;
	stm32446_tim_sr.clear_uif = STM32446Tim7_clear_uif;
	return stm32446_tim_sr;
}
STM32446TIM7_EGR stm32446_tim7_egr_inic(void)
{
	STM32446TIM7_EGR stm32446_tim_egr;
	// EGR
	stm32446_tim_egr.ug = STM32446Tim7_ug;
	return stm32446_tim_egr;
}
/*** TIM7 INIC Procedure & Function Definition ***/
STM32446TIM7obj tim7_inic(void)
{
	STM32446TIM7obj stm32446_tim;
	stm32446_tim.reg = TIM7;
	// CLOCK
	stm32446_tim.clock = STM32446Tim7Clock;
	// NVIC
	stm32446_tim.nvic = STM32446Tim7Nvic;
	/*** TIM7 Bit Mapping Link ***/
	stm32446_tim.cr1 = stm32446_tim7_cr1_inic();
	stm32446_tim.cr2 = stm32446_tim7_cr2_inic();
	stm32446_tim.dier = stm32446_tim7_dier_inic();
	stm32446_tim.sr = stm32446_tim7_sr_inic();
	stm32446_tim.egr = stm32446_tim7_egr_inic();
	stm32446_tim.cnt = STM32446Tim7_cnt;
	stm32446_tim.get_cnt = STM32446Tim7_get_cnt;
	stm32446_tim.psc = STM32446Tim7_psc;
	stm32446_tim.arr = STM32446Tim7_arr;
	return stm32446_tim;
}
/*** File Procedure & Function Definition***/
uint32_t tim6and7_readreg(uint32_t reg, uint32_t size_block, uint32_t bit)
{
	if(bit > 31){ bit = 0;} if(size_block > 32){ size_block = 32;}
	uint32_t value = reg;
	uint32_t mask = (unsigned int)((1 << size_block) - 1);
	value &= (mask << bit);
	value = (value >> bit);
	return value;
}
void tim6and7_writereg(volatile uint32_t* reg, uint32_t size_block, uint32_t bit, uint32_t data)
{
	if(bit > 31){ bit = 0;} if(size_block > 32){ size_block = 32;}
	uint32_t value = data;
	uint32_t mask = (unsigned int)((1 << size_block) - 1);
	value &= mask;
	value = (value << bit);
	*reg = value;
}
void tim6and7_setreg(volatile uint32_t* reg, uint32_t size_block, uint32_t bit, uint32_t data)
{
	if(bit > 31){ bit = 0;} if(size_block > 32){ size_block = 32;}
	uint32_t value = data;
	uint32_t mask = (unsigned int)((1 << size_block) - 1);
	value &= mask;
	*reg &= ~(mask << bit);
	*reg |= (value << bit);
}
void tim6and7_setbit(volatile uint32_t* reg, uint32_t size_block, uint32_t bit, uint32_t data)
{
	uint32_t n = 0;
	if(bit > 31){ n = bit/32; bit = bit - (n * 32); } if(size_block > 32){ size_block = 32;}
	uint32_t value = data;
	uint32_t mask = (unsigned int)((1 << size_block) - 1);
	value &= mask;
	*(reg + n ) &= ~(mask << bit);
	*(reg + n ) |= (value << bit);
}
uint32_t tim6and7_getsetbit(volatile uint32_t* reg, uint32_t size_block, uint32_t bit)
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


