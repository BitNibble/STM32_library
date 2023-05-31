/******************************************************************************
	STM32 446 TIM
Author: Sergio Santos 
	<sergio.salazar.santos@gmail.com>
License: GNU General Public License
Hardware: STM32-446
Date: 28052023
Comment:
	
*******************************************************************************/
/*** File Library ***/
#include <stm32446mapping.h>
#include "stm32446tim.h"

uint32_t tim_getbit(uint32_t reg, uint32_t size_block, uint32_t bit);
void tim_setbit(volatile uint32_t* reg, uint32_t size_block, uint32_t bit, uint32_t data);

/*** TIM 9 ***/
STM32446TIM9 STM32446TIM9enable(void)
{
	STM32446TIM9 tim9;

	tim9.reg = (TIM_TypeDef*) TIM9_BASE;
	tim9.inic = STM32446Tim9Inic;


	RCC->APB2ENR |= (1 << 16); //timer 9 clock enabled
	return tim9;
}

void STM32446Tim9Inic(void)
{
	//RCC->APB2ENR |= (1 << 16); //timer 9 clock enabled
	//RCC->APB2ENR |= (1 << 14); //syscfg clock enable
	NVIC->ISER[0] |= (1 << 24); // enable interrupt tim 1 brk and tim 9 global (IRGn 24)
	//NVIC->ICER[0] |= (1 << 24);
	TIM9->ARR = 45535;
	TIM9->CCR1 = 7530;
	TIM9->PSC = 20;
	TIM9->DIER |= 3; //3 | (1 << 6);
	//TIM9->CCMR1 |= (3 << 2);
	//TIM9->CCMR1 |= (3 << 4);
	//TIM9->CCER |= 1;
	TIM9->CR1 |= 1 | (1 << 7);
}

/*** TIM 10 ***/
// Future Implementation

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
	uint32_t value = 0;
	uint32_t mask = (unsigned int)((1 << size_block) - 1);
	value = data & mask;
	*reg &= ~(mask << bit);
	*reg |= (value << bit);
}

/*** File Interrupt ***/
// void TIM1_BRK_TIM9_IRQHandler(void){ // receive interrupt flags }

/*** EOF ***/


