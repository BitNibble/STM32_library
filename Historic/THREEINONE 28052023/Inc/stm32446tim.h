/******************************************************************************
	STM32 446 TIM
Author: Sergio Santos 
	<sergio.salazar.santos@gmail.com>
License: GNU General Public License
Hardware: STM32-446
Date: 23052023
Comment:
	
*******************************************************************************/
#ifndef _STM32446TIM_H_
	#define _STM32446TIM_H_

/*** Library ***/
#include <inttypes.h>

// TIM -> TIM1
typedef struct
{
	TIM_TypeDef* reg;
	void (*enable)(void);
}STM32446TIM1obj;

// TIM -> TIM2
typedef struct
{
	TIM_TypeDef* reg;
	void (*enable)(void);
}STM32446TIM2obj;

// TIM -> TIM3
typedef struct
{
	TIM_TypeDef* reg;
	void (*enable)(void);
}STM32446TIM3obj;

// TIM -> TIM4
typedef struct
{
	TIM_TypeDef* reg;
	void (*enable)(void);
}STM32446TIM4obj;

// TIM -> TIM5
typedef struct
{
	TIM_TypeDef* reg;
	void (*enable)(void);
}STM32446TIM5obj;

// TIM -> TIM6
typedef struct
{
	TIM_TypeDef* reg;
	void (*enable)(void);
}STM32446TIM6obj;

// TIM -> TIM7
typedef struct
{
	TIM_TypeDef* reg;
	void (*enable)(void);
}STM32446TIM7obj;

// TIM -> TIM8
typedef struct
{
	TIM_TypeDef* reg;
	void (*enable)(void);
}STM32446TIM8obj;

typedef struct{
	TIM_TypeDef* reg;
	void (*inic)(void);
}STM32446TIM9;

STM32446TIM9 STM32446TIM9enable(void);

// TIM -> TIM9
typedef struct
{
	TIM_TypeDef* reg;
	STM32446TIM9 (*enable)(void);
	void (*inic)(void);
}STM32446TIM9obj;

// TIM -> TIM10
typedef struct
{
	TIM_TypeDef* reg;
	void (*enable)(void);
}STM32446TIM10obj;

// TIM -> TIM11
typedef struct
{
	TIM_TypeDef* reg;
	void (*enable)(void);
}STM32446TIM11obj;

// TIM -> TIM12
typedef struct
{
	TIM_TypeDef* reg;
	void (*enable)(void);
}STM32446TIM12obj;

// TIM -> TIM13
typedef struct
{
	TIM_TypeDef* reg;
	void (*enable)(void);
}STM32446TIM13obj;

// TIM -> TIM14
typedef struct
{
	TIM_TypeDef* reg;
	void (*enable)(void);
}STM32446TIM14obj;

/*** TIM 9 ***/
// TIM9
void STM32446Tim9Inic(void);
// TIM9
//void STM32446Tim9Enable(void);

#endif
/*** EOF ***/

