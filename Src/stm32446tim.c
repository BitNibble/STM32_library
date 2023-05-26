/******************************************************************************
	STM32 446 TIM
Author: Sergio Santos 
	<sergio.salazar.santos@gmail.com>
License: GNU General Public License
Hardware: STM32-446
Date: 23052023
Comment:
	
*******************************************************************************/
/*** File Library ***/
#include "stm32446mapping.h"
//#include "stm32446tim.h" // move this then to stm32446mapping header file.
#include <math.h>

/*** File Constant & Macros ***/

/*** File Variable ***/
static STM32446 stm32446;

/*** File Header ***/
// TIM9
void STM32446Tim9Inic(void);
// TIM9
void STM32446Tim9Enable(void);

// TIM9
STM32446TIM9 STM32446TIM9enable(void)
{
	stm32446 = STM32446enable();
	STM32446TIM9 tim9;

	tim9.inic = STM32446Tim9Inic;

	STM32446Tim9Enable();

	return tim9;
}

// TIM9
void STM32446Tim9Enable(void)
{
	stm32446.rcc.reg->APB2ENR |= (1 << 16); //timer 9 clock enabled
}

void STM32446Tim9Inic(void)
{
	//stm.rcc.reg->APB2ENR |= (1 << 16); //timer 9 clock enabled
	//stm.rcc.reg->APB2ENR |= (1 << 14); //syscfg clock enable
	stm32446.nvic.reg->ISER[0] |= (1 << 24); // enable interrupt tim 1 brk and tim 9 global (IRGn 24)
	//stm.nvic.reg->ICER[0] |= (1 << 24);
	stm32446.tim9.reg->ARR = 45535;
	stm32446.tim9.reg->CCR1 = 7530;
	stm32446.tim9.reg->PSC = 20;
	stm32446.tim9.reg->DIER |= 3; //3 | (1 << 6);
	//stm32446.tim9.reg->CCMR1 |= (3 << 2);
	//stm32446.tim9.reg->CCMR1 |= (3 << 4);
	//stm32446.tim9.reg->CCER |= 1;
	stm32446.tim9.reg->CR1 |= 1 | (1 << 7);
}

/*** File Interrupt ***/
// void TIM1_BRK_TIM9_IRQHandler(void){ }

