/******************************************************************************
	STM32 446 GPIO
Author: Sergio Santos 
	<sergio.salazar.santos@gmail.com>
License: GNU General Public License
Hardware: STM32-446
Date: 02062023
Comment:
	TypeDef Pointer Structures, Library Function Headers.
*******************************************************************************/
#ifndef _STM32446GPIO_H_
	#define _STM32446GPIO_H_

/*** File Library ***/
#include <inttypes.h>

/*** GPIO TypeDef ***/
typedef struct
{
	uint32_t (*readreg)(uint32_t reg, uint32_t size_block, uint32_t bit);
	void (*writereg)(volatile uint32_t* reg, uint32_t size_block, uint32_t bit, uint32_t data);
	uint32_t (*getbit)(uint32_t reg, uint32_t size_block, uint32_t bit);
	void (*setreg)(volatile uint32_t* reg, uint32_t size_block, uint32_t bit, uint32_t data);
	void (*setbit)(volatile uint32_t* reg, uint32_t size_block, uint32_t bit, uint32_t data);
	uint32_t (*getsetbit)(volatile uint32_t* reg, uint32_t size_block, uint32_t bit);
}STM32446GpioFunc;

// GPIO -> GPIOA
typedef struct
{
	GPIO_TypeDef* reg;
	#if defined(_STM32446GPIO_H_)
		/*** Bit Mapping ***/
		void (*moder)( unsigned int data, unsigned int pin );
		void (*ospeedr)( unsigned int data, unsigned int pin );
		void (*pupdr)( unsigned int data, unsigned int pin );
		void (*afr)( unsigned int data, unsigned int pin );
		void (*reset)( unsigned int data );
		void (*set)( unsigned int data );
		/*** Other ***/
		void (*clock)(void);
		STM32446GpioFunc func;
	#endif
}STM32446GpioAobj;

// GPIO -> GPIOB
typedef struct
{
	GPIO_TypeDef* reg;
	#if defined(_STM32446GPIO_H_)
		/*** Bit Mapping ***/
		void (*moder)( unsigned int data, unsigned int pin );
		void (*ospeedr)( unsigned int data, unsigned int pin );
		void (*pupdr)( unsigned int data, unsigned int pin );
		void (*afr)( unsigned int data, unsigned int pin );
		void (*reset)( unsigned int data );
		void (*set)( unsigned int data );
		/*** Other ***/
		void (*clock)(void);
		STM32446GpioFunc func;
	#endif
}STM32446GpioBobj;

// GPIO -> GPIOC
typedef struct
{
	GPIO_TypeDef* reg;
	#if defined(_STM32446GPIO_H_)
		/*** Bit Mapping ***/
		void (*moder)( unsigned int data, unsigned int pin );
		void (*ospeedr)( unsigned int data, unsigned int pin );
		void (*pupdr)( unsigned int data, unsigned int pin );
		void (*afr)( unsigned int data, unsigned int pin );
		void (*reset)( unsigned int data );
		void (*set)( unsigned int data );
		/*** Other ***/
		void (*clock)(void);
		STM32446GpioFunc func;
	#endif
}STM32446GpioCobj;

// GPIO -> GPIOD
typedef struct
{
	GPIO_TypeDef* reg;
	#if defined(_STM32446GPIO_H_)
		/*** Bit Mapping ***/
		void (*moder)( unsigned int data, unsigned int pin );
		void (*ospeedr)( unsigned int data, unsigned int pin );
		void (*pupdr)( unsigned int data, unsigned int pin );
		void (*afr)( unsigned int data, unsigned int pin );
		void (*reset)( unsigned int data );
		void (*set)( unsigned int data );
		/*** Other ***/
		void (*clock)(void);
		STM32446GpioFunc func;
	#endif
}STM32446GpioDobj;

// GPIO -> GPIOE
typedef struct
{
	GPIO_TypeDef* reg;
	#if defined(_STM32446GPIO_H_)
		/*** Bit Mapping ***/
		void (*moder)( unsigned int data, unsigned int pin );
		void (*ospeedr)( unsigned int data, unsigned int pin );
		void (*pupdr)( unsigned int data, unsigned int pin );
		void (*afr)( unsigned int data, unsigned int pin );
		void (*reset)( unsigned int data );
		void (*set)( unsigned int data );
		/*** Other ***/
		void (*clock)(void);
		STM32446GpioFunc func;
	#endif
}STM32446GpioEobj;

// GPIO -> GPIOF
typedef struct
{
	GPIO_TypeDef* reg;
	#if defined(_STM32446GPIO_H_)
		/*** Bit Mapping ***/
		void (*moder)( unsigned int data, unsigned int pin );
		void (*ospeedr)( unsigned int data, unsigned int pin );
		void (*pupdr)( unsigned int data, unsigned int pin );
		void (*afr)( unsigned int data, unsigned int pin );
		void (*reset)( unsigned int data );
		void (*set)( unsigned int data );
		/*** Other ***/
		void (*clock)(void);
		STM32446GpioFunc func;
	#endif
}STM32446GpioFobj;

// GPIO -> GPIOG
typedef struct
{
	GPIO_TypeDef* reg;
	#if defined(_STM32446GPIO_H_)
		/*** Bit Mapping ***/
		void (*moder)( unsigned int data, unsigned int pin );
		void (*ospeedr)( unsigned int data, unsigned int pin );
		void (*pupdr)( unsigned int data, unsigned int pin );
		void (*afr)( unsigned int data, unsigned int pin );
		void (*reset)( unsigned int data );
		void (*set)( unsigned int data );
		/*** Other ***/
		void (*clock)(void);
		STM32446GpioFunc func;
	#endif
}STM32446GpioGobj;

// GPIO -> GPIOH
typedef struct
{
	GPIO_TypeDef* reg;
	#if defined(_STM32446GPIO_H_)
		/*** Bit Mapping ***/
		void (*moder)( unsigned int data, unsigned int pin );
		void (*ospeedr)( unsigned int data, unsigned int pin );
		void (*pupdr)( unsigned int data, unsigned int pin );
		void (*afr)( unsigned int data, unsigned int pin );
		void (*reset)( unsigned int data );
		void (*set)( unsigned int data );
		/*** Other ***/
		void (*clock)(void);
		STM32446GpioFunc func;
	#endif
}STM32446GpioHobj;

/***** GPIO Procedure & Funtion Header ******/
void STM32446GpioAclock( void );
void STM32446GpioAmoder( unsigned int data, unsigned int pin );
void STM32446GpioAospeedr( unsigned int data, unsigned int pin );
void STM32446GpioApupdr( unsigned int data, unsigned int pin );
void STM32446GpioAreset( unsigned int data );
void STM32446GpioAset( unsigned int data );
void STM32446GpioAafr( unsigned int data, unsigned int pin );

void STM32446GpioBclock( void );
void STM32446GpioBmoder( unsigned int data, unsigned int pin );
void STM32446GpioBospeedr( unsigned int data, unsigned int pin );
void STM32446GpioBpupdr( unsigned int data, unsigned int pin );
void STM32446GpioBreset( unsigned int data );
void STM32446GpioBset( unsigned int data );
void STM32446GpioBafr( unsigned int data, unsigned int pin );

void STM32446GpioCclock( void );
void STM32446GpioCmoder( unsigned int data, unsigned int pin );
void STM32446GpioCospeedr( unsigned int data, unsigned int pin );
void STM32446GpioCpupdr( unsigned int data, unsigned int pin );
void STM32446GpioCreset( unsigned int data );
void STM32446GpioCset( unsigned int data );
void STM32446GpioCafr( unsigned int data, unsigned int pin );

void STM32446GpioDclock( void );
void STM32446GpioDmoder( unsigned int data, unsigned int pin );
void STM32446GpioDospeedr( unsigned int data, unsigned int pin );
void STM32446GpioDpupdr( unsigned int data, unsigned int pin );
void STM32446GpioDreset( unsigned int data );
void STM32446GpioDset( unsigned int data );
void STM32446GpioDafr( unsigned int data, unsigned int pin );

void STM32446GpioEclock( void );
void STM32446GpioEmoder( unsigned int data, unsigned int pin );
void STM32446GpioEospeedr( unsigned int data, unsigned int pin );
void STM32446GpioEpupdr( unsigned int data, unsigned int pin );
void STM32446GpioEreset( unsigned int data );
void STM32446GpioEset( unsigned int data );
void STM32446GpioEafr( unsigned int data, unsigned int pin );

void STM32446GpioFclock( void );
void STM32446GpioFmoder( unsigned int data, unsigned int pin );
void STM32446GpioFospeedr( unsigned int data, unsigned int pin );
void STM32446GpioFpupdr( unsigned int data, unsigned int pin );
void STM32446GpioFreset( unsigned int data );
void STM32446GpioFset( unsigned int data );
void STM32446GpioFafr( unsigned int data, unsigned int pin );

void STM32446GpioGclock( void );
void STM32446GpioGmoder( unsigned int data, unsigned int pin );
void STM32446GpioGospeedr( unsigned int data, unsigned int pin );
void STM32446GpioGpupdr( unsigned int data, unsigned int pin );
void STM32446GpioGreset( unsigned int data );
void STM32446GpioGset( unsigned int data );
void STM32446GpioGafr( unsigned int data, unsigned int pin );

void STM32446GpioHclock( void );
void STM32446GpioHmoder( unsigned int data, unsigned int pin );
void STM32446GpioHospeedr( unsigned int data, unsigned int pin );
void STM32446GpioHpupdr( unsigned int data, unsigned int pin );
void STM32446GpioHreset( unsigned int data );
void STM32446GpioHset( unsigned int data );
void STM32446GpioHafr( unsigned int data, unsigned int pin );

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


