/******************************************************************************
	STM32 446 COMMON
Author: Sergio Santos 
	<sergio.salazar.santos@gmail.com>
License: GNU General Public License
Hardware: STM32-446
Date: 28052023
Comment:
	Common Code
*******************************************************************************/
#ifndef _STM32446COMMON_H_
	#define _STM32446COMMON_H_

/********** Global TypeDef ***********/
typedef struct
{
	uint8_t L;
	uint8_t H;
} STM32HighLowByte;

// Low Word High Word
//typedef struct
//{
//	uint16_t H;
//	uint16_t L;
//}STM32446HighLowWord;

typedef struct
{
	uint32_t (*AHB)(void);
	uint32_t (*APB1)(void);
	uint32_t (*APB2)(void);
	uint32_t (*RTCclk)(void);
	uint32_t (*MCO1)(void);
	uint32_t (*MCO2)(void);
}STM32446CLOCK_prescaler;

typedef struct
{
	uint32_t (*M)(void);
	uint32_t (*N)(void);
	uint32_t (*P)(void);
	uint32_t (*Q)(void);
	uint32_t (*R)(void);
}STM32446PLL_parameter;

/************** QUERY TypeDef ****************/
typedef struct
{
	STM32446CLOCK_prescaler CLOCK_prescaler;
	STM32446PLL_parameter PLL_parameter;
	uint32_t (*ClockSource)(void);
	uint32_t (*SystemClock)(void);
	uint32_t (*PllSource)(void);
}STM32446Query;

/***** Peripheral COMMON TypeDef *****/
/*** ADC_Common ***/
typedef struct
{
	ADC_Common_TypeDef* reg;
}STM32446ADCCOMMONobj;

typedef struct
{
	void (*inic)(void);
	void (*vbat)(void);
	void (*temp)(void);
	void (*start)(void);
	double (*read)(void);
	void (*restart)(void);
	void (*stop)(void);
}STM32446ADC1single;

/*** RCC_Common ***/
// RCC -> PLL
typedef struct
{
	void (*division)(unsigned int pllsrc, unsigned int pllm, unsigned int plln, unsigned int pllp, unsigned int pllq, unsigned int pllr);
	void (*enable)(void);
}STM32446RCCPLL;

// RCC -> PLLI2S
typedef struct
{
	void (*enable)(void);
}STM32446RCCPLLI2S;

// RCC -> PLLSAI
typedef struct
{
	void (*enable)(void);
}STM32446RCCPLLSAI;

/*** TIMER9_Common ***/
typedef struct{
	uint8_t (*get_ckd)(void);
	void (*apre)(uint8_t bool);
	void (*opm)(uint8_t bool);
	void (*urs)(uint8_t bool);
	void (*udis)(uint8_t bool);
	void (*cen)(uint8_t bool);
}STM32446TIM9_CR1;

typedef struct{
	void (*msm)(uint8_t bool);
	void (*ts)(uint8_t ts);
	void (*sms)(uint8_t sms);
}STM32446TIM9_SMCR;

typedef struct{
	void (*tie)(uint8_t bool);
	void (*cc2ie)(uint8_t bool);
	void (*cc1ie)(uint8_t bool);
	void (*uie)(uint8_t bool);
}STM32446TIM9_DIER;

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
}STM32446TIM9_SR;

typedef struct{
	void (*tg)(void);
	void (*cc2g)(void);
	void (*cc1g)(void);
	void (*ug)(void);
}STM32446TIM9_EGR;

typedef struct{
	void (*oc2m)(uint8_t oc2m);
	void (*ic2f)(uint8_t ic2f);
	void (*oc2pe)(uint8_t bool);
	void (*oc2fe)(uint8_t bool);
	void (*ic2psc)(uint8_t ic2psc);
	void (*cc2s)(uint8_t cc2s);
	void (*oc1m)(uint8_t oc1m);
	void (*ic1f)(uint8_t ic1f);
	void (*oc1pe)(uint8_t bool);
	void (*oc1fe)(uint8_t bool);
	void (*ic1psc)(uint8_t ic1psc);
	void (*cc1s)(uint8_t cc1s);
}STM32446TIM9_CCMR1;

typedef struct{
	void (*cc2np)(uint8_t bool);
	void (*cc2p)(uint8_t bool);
	void (*cc2e)(uint8_t bool);
	void (*cc1np)(uint8_t bool);
	void (*cc1p)(uint8_t bool);
	void (*cc1e)(uint8_t bool);
}STM32446TIM9_CCER;

#endif

/*** EOF ***/


