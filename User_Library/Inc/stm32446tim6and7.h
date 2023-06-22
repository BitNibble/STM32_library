/******************************************************************************
	STM32 446 TIM 6 and 7
Author: Sergio Santos 
	<sergio.salazar.santos@gmail.com>
License: GNU General Public License
Hardware: STM32-446
Date: 22062023
Comment:
	
*******************************************************************************/
#ifndef _STM32446TIM6AND7_H_
	#define _STM32446TIM6AND7_H_
/*** Library ***/
#include <inttypes.h>
/*** TIMER Bit Mapping TypeDef ***/
// CR1
typedef struct{
	void (*apre)(uint8_t bool);
	void (*opm)(uint8_t bool);
	void (*urs)(uint8_t bool);
	void (*udis)(uint8_t bool);
	void (*cen)(uint8_t bool);
}STM32446TIM6_CR1, STM32446TIM7_CR1;
// CR2
typedef struct{
	void (*mms)(uint8_t value);
}STM32446TIM6_CR2, STM32446TIM7_CR2;
// DIER
typedef struct{
	void (*ude)(uint8_t bool);
	void (*uie)(uint8_t bool);
}STM32446TIM6_DIER, STM32446TIM7_DIER;
// SR
typedef struct{
	uint8_t (*uif)(void);
	void (*clear_uif)(void);
}STM32446TIM6_SR, STM32446TIM7_SR;
// EGR
typedef struct{
	void (*ug)(void);
}STM32446TIM6_EGR, STM32446TIM7_EGR;
/*** TIMER TypeDef***/
// ( 6 and 7 ) TIM 
typedef struct
{
	TIM_TypeDef* reg;
	/*** Bit Mapping ***/
	STM32446TIM6_CR1 cr1;
	STM32446TIM6_CR2 cr2;
	STM32446TIM6_DIER dier;
	STM32446TIM6_SR sr;
	STM32446TIM6_EGR egr;
	void (*cnt)(uint16_t value);
	uint16_t (*get_cnt)(void);
	void (*psc)(uint16_t value);
	void (*arr)(uint16_t value);
	/*** Other ***/
	void (*clock)(uint8_t bool);
	void (*nvic)(uint8_t bool);
}STM32446TIM6obj, STM32446TIM7obj;
/************************/
/*** INIC TIM 6 AND 7 ***/
/***********************/
STM32446TIM6obj tim6_inic(void);
STM32446TIM7obj tim7_inic(void);
/****************************************/
/*** TIM6 Procedure & Function Header ***/
/****************************************/
void STM32446Tim6Clock(uint8_t bool);
void STM32446Tim6Nvic(uint8_t bool);
/*** TIM6 Bit Mapping Header ***/
// CR1
void STM32446Tim6_set_apre(uint8_t bool);
void STM32446Tim6_set_opm(uint8_t bool);
void STM32446Tim6_set_urs(uint8_t bool);
void STM32446Tim6_set_udis(uint8_t bool);
void STM32446Tim6_cen(uint8_t bool);
// CR2
void STM32446Tim6_mms(uint8_t value);
// DIER
void STM32446Tim6_ude(uint8_t bool);
void STM32446Tim6_uie(uint8_t bool);
// SR
uint8_t STM32446Tim6_uif(void);
void STM32446Tim6_clear_uif(void);
// EGR
void STM32446Tim6_ug(void);
// CNT
void STM32446Tim6_cnt(uint16_t value);
uint16_t STM32446Tim6_get_cnt(void);
// PSC
void STM32446Tim6_psc(uint16_t value);
// ARR
void STM32446Tim6_arr(uint16_t value);
/****************************************/
/*** TIM7 Procedure & Function Header ***/
/****************************************/
void STM32446Tim7Clock(uint8_t bool);
void STM32446Tim7Nvic(uint8_t bool);
/*** TIM7 Bit Mapping Header ***/
// CR1
void STM32446Tim7_set_apre(uint8_t bool);
void STM32446Tim7_set_opm(uint8_t bool);
void STM32446Tim7_set_urs(uint8_t bool);
void STM32446Tim7_set_udis(uint8_t bool);
void STM32446Tim7_cen(uint8_t bool);
// CR2
void STM32446Tim7_mms(uint8_t value);
// DIER
void STM32446Tim7_ude(uint8_t bool);
void STM32446Tim7_uie(uint8_t bool);
// SR
uint8_t STM32446Tim7_uif(void);
void STM32446Tim7_clear_uif(void);
// EGR
void STM32446Tim7_ug(void);
// CNT
void STM32446Tim7_cnt(uint16_t value);
uint16_t STM32446Tim7_get_cnt(void);
// PSC
void STM32446Tim7_psc(uint16_t value);
// ARR
void STM32446Tim7_arr(uint16_t value);
/****************************************/

/*** INTERRUPT HEADER ***/
void TIM6_DAC_IRQHandler(void);
void TIM7_IRQHandler(void);

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


