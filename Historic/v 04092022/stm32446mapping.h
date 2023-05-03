/******************************************************************************
	STM32 446 MAPPING
Author: Sergio Manuel Santos
	<sergio.salazar.santos@gmail.com>
License: GNU General Public License
Hardware: STM32-446
Date: 07062022 inic
Comment:
	manual um1724, m0390, pm0056, pm0214, and other sources.
	Virtual Image STM32-446, mapping.
	Still in progress 03082022, increment has go along.
	Stable.
*******************************************************************************/
#ifndef _STM32446MAPPING_H_
	#define _STM32446MAPPING_H_

/*
*** Libraries
*/

#include <inttypes.h>

#include "stm32f4xx.h"
#include "stm32f446xx.h"
#include "core_cm4.h"

/******************************************************************************/
/******************************************************************************/

// Low Byte High Byte
typedef struct
{
	uint8_t H;
	uint8_t L;
} STM32HighLowByte;

// Low Word High Word
//typedef struct
//{
//	uint16_t H;
//	uint16_t L;
//}STM32446HighLowWord;

/*
*** STM32446 OBJECTS
*/

// FLASH
typedef struct
{
	FLASH_TypeDef* reg;
}STM32446FLASHobj;

// CRC
typedef struct
{
	CRC_TypeDef* reg;
}STM32446CRCobj;

// PWR
typedef struct
{
	PWR_TypeDef* reg;
}STM32446PWRobj;

// RCC
typedef struct
{
	void (*division)(unsigned int pllsrc, unsigned int pllm, unsigned int plln, unsigned int pllp, unsigned int pllq, unsigned int pllr);
	void (*enable)(uint8_t onoff);
}STM32446RCCPLL;

typedef struct
{
	void (*enable)(uint8_t onoff);
}STM32446RCCPLLI2S;

typedef struct
{
	void (*enable)(uint8_t onoff);
}STM32446RCCPLLSAI;

typedef struct
{
	RCC_TypeDef* reg;
	void (*henable)(unsigned int hclock);
	uint8_t (*hselect)(uint8_t sysclk);
	void (*lenable)(unsigned int lclock);
	void (*lselect)(uint8_t lclock);
	void (*prescaler)(unsigned int ahbpre, unsigned int ppre1, unsigned int ppre2, unsigned int rtcpre);
	STM32446RCCPLL pll;
	STM32446RCCPLLI2S plli2s;
	STM32446RCCPLLSAI pllsai;
}STM32446RCCobj;

// GPIOA
typedef struct
{
	GPIO_TypeDef* reg;
	void (*moder)( unsigned int data, unsigned int pin );
	void (*ospeedr)( unsigned int data, unsigned int pin );
	void (*pupdr)( unsigned int data, unsigned int pin );
	void (*afr)( unsigned int data, unsigned int pin );
	void (*reset)( unsigned int data );
	void (*set)( unsigned int data );
}STM32446GpioAobj;

// GPIOB
typedef struct
{
	GPIO_TypeDef* reg;
	void (*moder)( unsigned int data, unsigned int pin );
	void (*ospeedr)( unsigned int data, unsigned int pin );
	void (*pupdr)( unsigned int data, unsigned int pin );
	void (*afr)( unsigned int data, unsigned int pin );
	void (*reset)( unsigned int data );
	void (*set)( unsigned int data );
}STM32446GpioBobj;

// GPIOC
typedef struct
{
	GPIO_TypeDef* reg;
	void (*moder)( unsigned int data, unsigned int pin );
	void (*ospeedr)( unsigned int data, unsigned int pin );
	void (*pupdr)( unsigned int data, unsigned int pin );
	void (*afr)( unsigned int data, unsigned int pin );
	void (*reset)( unsigned int data );
	void (*set)( unsigned int data );
}STM32446GpioCobj;

// GPIOD
typedef struct
{
	GPIO_TypeDef* reg;
	void (*moder)( unsigned int data, unsigned int pin );
	void (*ospeedr)( unsigned int data, unsigned int pin );
	void (*pupdr)( unsigned int data, unsigned int pin );
	void (*afr)( unsigned int data, unsigned int pin );
	void (*reset)( unsigned int data );
	void (*set)( unsigned int data );
}STM32446GpioDobj;
// GPIOE
typedef struct
{
	GPIO_TypeDef* reg;
	void (*moder)( unsigned int data, unsigned int pin );
	void (*ospeedr)( unsigned int data, unsigned int pin );
	void (*pupdr)( unsigned int data, unsigned int pin );
	void (*afr)( unsigned int data, unsigned int pin );
	void (*reset)( unsigned int data );
	void (*set)( unsigned int data );
}STM32446GpioEobj;
// GPIOF
typedef struct
{
	GPIO_TypeDef* reg;
}STM32446GpioFobj;
// GPIOG
typedef struct
{
	GPIO_TypeDef* reg;
}STM32446GpioGobj;
// GPIOH
typedef struct
{
	GPIO_TypeDef* reg;
	void (*moder)( unsigned int data, unsigned int pin );
	void (*ospeedr)( unsigned int data, unsigned int pin );
	void (*pupdr)( unsigned int data, unsigned int pin );
	void (*afr)( unsigned int data, unsigned int pin );
	void (*reset)( unsigned int data );
	void (*set)( unsigned int data );
}STM32446GpioHobj;

// RTC
typedef struct
{
	RTC_TypeDef* reg;
	uint8_t (*inic)(uint8_t clock);
	void (*Day)(uint8_t day);
	void (*Month)(uint8_t month);
	void (*WeekDay)(uint8_t weekday);
	void (*Year)(uint8_t year);
	void (*Hour)(uint8_t hour);
	void (*Minute)(uint8_t minute);
	void (*Second)(uint8_t second);
	void (*dr2vec)(char* vect);
	void (*tr2vec)(char* vect);
	void (*RegWrite)(volatile uint32_t* reg, uint32_t data);
}STM32446RTCobj;

// SYSCFG
typedef struct
{
	SYSCFG_TypeDef* reg;
}STM32446SYSCFGobj;

// DMA1
typedef struct
{
	DMA_TypeDef* reg;
}STM32446DMA1obj;

// DMA2
typedef struct
{
	DMA_TypeDef* reg;
}STM32446DMA2obj;

// NVIC
typedef struct
{
	NVIC_Type* reg;
}STM32446NVICobj;

// SysTick
typedef struct
{
	SysTick_Type* reg;
	void (*delay_ms)(uint32_t ms); // It uses Systick
	void (*delay_10us)(uint32_t us); // It uses Systick
}STM32446SysTickobj;

/**random order**/

//TIM9
typedef struct
{
	TIM_TypeDef* reg;
}STM32446TIM9obj;

//ADC1
/*** types of ADC1 applications ***/
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

/*** Registry structs ***/
typedef struct
{
	ADC_TypeDef* reg;
	STM32446ADC1single single;
}STM32446ADC1obj;

//ADC COMMON
typedef struct
{
	ADC_Common_TypeDef* reg;
}STM32446ADCCOMMONobj;

//USART1
typedef struct
{
	USART_TypeDef* reg;
	void (*parameters)( uint8_t wordlength, uint8_t samplingmode, double stopbits, uint32_t baudrate );
	void (*test)(void);
}STM32446USART1obj;
/*
*** INIC
*/
typedef struct
{
	uint8_t (*peripheral)(void);
}STM32446inic;
/*
*** FUNC
*/
typedef struct
{
	char (*bcd2dec)(char num);
	char (*dec2bcd)(char num);
	uint32_t (*triggerA)(uint32_t hllh_io, uint8_t pin, uint32_t counter);
	uint32_t (*triggerB)(uint32_t hl_io, uint32_t lh_io, uint8_t pin, uint32_t counter);
	uint16_t (*ReadHLByte)(STM32HighLowByte reg);
	uint16_t (*ReadLHByte)(STM32HighLowByte reg);
	STM32HighLowByte (*WriteHLByte)(uint16_t val);
	STM32HighLowByte (*WriteLHByte)(uint16_t val);
	uint16_t (*SwapByte)(uint16_t num);
	void (*setpins)( GPIO_TypeDef* regs, int n_pin, ... ); // BSRR
	void (*setpin)( GPIO_TypeDef* regs, int pin ); // BSRR
	void (*set)( GPIO_TypeDef* regs, int data ); // BSRR
	void (*resetpins)( GPIO_TypeDef* regs, int n_pin, ... ); // BSRR
	void (*resetpin)( GPIO_TypeDef* regs, int pin); // BSRR
	void (*reset)( GPIO_TypeDef* regs, int data); // BSRR
	void (*setupreg)(unsigned int blocksize, volatile uint32_t* reg, unsigned int data, unsigned int pin); // GENERIC &|
	
}STM32446function;

/******************************************************************************/
/******************************************************************************/

/*
*** STM32446 IMAGE Linker
*/

typedef struct
{
	/*****************************/
	/*******STM32446 STRUCTS******/
	/*****************************/
	// STM32446 FLASH OBJECT
	STM32446FLASHobj flash;
	// STM32446 CRC OBJECT
	STM32446CRCobj crc;
	// STM32446 PWR OBJECT
	STM32446PWRobj pwr;
	// STM32446 RCC OBJECT
	STM32446RCCobj rcc;
	// STM32446 GPIOA OBJECT
	STM32446GpioAobj gpioa;
	// STM32446 GPIOB OBJECT
	STM32446GpioBobj gpiob;
	// STM32446 GPIOC OBJECT
	STM32446GpioCobj gpioc;
	// STM32446 GPIOD OBJECT
	STM32446GpioDobj gpiod;
	// STM32446 GPIOE OBJECT
	STM32446GpioEobj gpioe;
	// STM32446 GPIOH OBJECT
	STM32446GpioHobj gpioh;
	// STM32446 RTC OBJECT
	STM32446RTCobj rtc;
	// STM32446 SYSCFG OBJECT
	STM32446SYSCFGobj syscfg;
	// STM32446 DMA1 OBJECT
	STM32446DMA1obj dma1;
	// STM32446 DMA2 OBJECT
	STM32446DMA2obj dma2;
	// STM32446 NVIC OBJECT
	STM32446NVICobj nvic;
	// STM32446 SysTick OBJECT
	STM32446SysTickobj systick;
	/**random order**/
	//STM32446 TIM9 OBJECT
	STM32446TIM9obj tim9;
	//STM32446 ADC1 OBJECT
	STM32446ADC1obj adc1;
	//STM32446 ADC COMMON OBJECT
	STM32446ADCCOMMONobj adc123;
	//STM32446 USART1 OBJECT
	STM32446USART1obj usart1;
	
	/*****************************/
	/********INIC STRUCT**********/
	/*****************************/
	STM32446inic inic;
	/*****************************/
	/******FUNCTION STRUCT********/
	/*****************************/
	STM32446function func;
	/****************************************************************************/
}STM32446;
/*
*** Procedure and Function Prototype
*/
STM32446 STM32446enable(void);

#endif
/***Interrupt Prototype***/

/********************************COMMENT****************************************

*******************************************************************************/

