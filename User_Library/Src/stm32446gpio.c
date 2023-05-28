/******************************************************************************
	STM32 446 GPIO
Author: Sergio Santos 
	<sergio.salazar.santos@gmail.com>
License: GNU General Public License
Hardware: STM32-446
Date: 28052023
Comment:
	File Vars, File Function Header, Library Function Definitions.
	
*******************************************************************************/
/*** File Library ***/
#include <stm32f446xx.h>
#include "stm32446gpio.h"
#include "math.h"

void STM32446GpioAenable( void );
void STM32446GpioBenable( void );
void STM32446GpioCenable( void );
void STM32446GpioDenable( void );
void STM32446GpioEenable( void );
void STM32446GpioFenable( void );
void STM32446GpioGenable( void );
void STM32446GpioHenable( void );

/*** GPIOA ***/
// GPIO -> GPIOA
STM32446GPIOA STM32446GPIOAenable(void)
{
	STM32446GPIOA gpioa;
	// GPIOA
	gpioa.reg = (GPIO_TypeDef*) GPIOA_BASE;
	gpioa.moder = STM32446GpioAmoder;
	gpioa.ospeedr = STM32446GpioAospeedr;
	gpioa.pupdr = STM32446GpioApupdr;
	gpioa.reset = STM32446GpioAreset;
	gpioa.set = STM32446GpioAset;
	gpioa.afr = STM32446GpioAafr;

	STM32446GpioAenable( );

	return gpioa;
}

void STM32446GpioAenable( void )
{
	RCC->AHB1ENR |= (1 << 0);
}

void STM32446GpioAmoder( unsigned int data, unsigned int pin )
{
	const unsigned int blocksize = 2;
	unsigned int mask = (unsigned int)(pow(2, blocksize) - 1);
	data &= mask;
	GPIOA->MODER &= ~(mask << (pin * blocksize));
	GPIOA->MODER |= (data << (pin * blocksize));
}

void STM32446GpioAospeedr( unsigned int data, unsigned int pin )
{
	const unsigned int blocksize = 2;
	unsigned int mask = (unsigned int)(pow(2, blocksize) - 1);
	data &= mask;
	GPIOA->OSPEEDR &= ~(mask << (pin * blocksize));
	GPIOA->OSPEEDR |= (data << (pin * blocksize));
}

void STM32446GpioApupdr( unsigned int data, unsigned int pin )
{
	const unsigned int blocksize = 2;
	unsigned int mask = (unsigned int)(pow(2, blocksize) - 1);
	data &= mask;
	GPIOA->PUPDR &= ~(mask << (pin * blocksize));
	GPIOA->PUPDR |= (data << (pin * blocksize));
}

void STM32446GpioAreset( unsigned int data )
{
	GPIOA->BSRR = (unsigned int)(data << 16);
}

void STM32446GpioAset( unsigned int data )
{
	GPIOA->BSRR = (unsigned int)( data );
}

void STM32446GpioAafr( unsigned int data, unsigned int pin )
{
	const unsigned int blocksize = 4;
	const unsigned int n_bits = sizeof(unsigned int) * 8;
	const unsigned int mask = (unsigned int) (pow(2, blocksize) - 1);
	unsigned int index = (pin * blocksize) / n_bits;
	data &= mask;
	if(index < 2){
		GPIOA->AFR[index] &= ~( mask << ((pin * blocksize) - (index * n_bits)) );
		GPIOA->AFR[index] |= ( data << ((pin * blocksize) - (index * n_bits)) );
	}
}

/*** GPIOB ***/
// GPIO -> GPIOB
STM32446GPIOB STM32446GPIOBenable(void)
{
	STM32446GPIOB gpiob;
	// GPIOB
	gpiob.reg = (GPIO_TypeDef*) GPIOB_BASE;
	gpiob.moder = STM32446GpioBmoder;
	gpiob.ospeedr = STM32446GpioBospeedr;
	gpiob.pupdr = STM32446GpioBpupdr;
	gpiob.reset = STM32446GpioBreset;
	gpiob.set = STM32446GpioBset;
	gpiob.afr = STM32446GpioBafr;

	STM32446GpioBenable( );

	return gpiob;
}

void STM32446GpioBenable( void )
{
	RCC->AHB1ENR |= (1 << 1);
}

void STM32446GpioBmoder( unsigned int data, unsigned int pin )
{
	const unsigned int blocksize = 2;
	unsigned int mask = (unsigned int)(pow(2, blocksize) - 1);
	data &= mask;
	GPIOB->MODER &= ~(mask << (pin * blocksize));
	GPIOB->MODER |= (data << (pin * blocksize));
}

void STM32446GpioBospeedr( unsigned int data, unsigned int pin )
{
	const unsigned int blocksize = 2;
	unsigned int mask = (unsigned int)(pow(2, blocksize) - 1);
	data &= mask;
	GPIOB->OSPEEDR &= ~(mask << (pin * blocksize));
	GPIOB->OSPEEDR |= (data << (pin * blocksize));
}

void STM32446GpioBpupdr( unsigned int data, unsigned int pin )
{
	const unsigned int blocksize = 2;
	unsigned int mask = (unsigned int)(pow(2, blocksize) - 1);
	data &= mask;
	GPIOB->PUPDR &= ~(mask << (pin * blocksize));
	GPIOB->PUPDR |= (data << (pin * blocksize));
}

void STM32446GpioBreset( unsigned int data )
{
	GPIOB->BSRR = (unsigned int)(data << 16);
}

void STM32446GpioBset( unsigned int data )
{
	GPIOB->BSRR = (unsigned int)( data );
}

void STM32446GpioBafr( unsigned int data, unsigned int pin )
{
	const unsigned int blocksize = 4;
	const unsigned int n_bits = sizeof(unsigned int) * 8;
	const unsigned int mask = (unsigned int) (pow(2, blocksize) - 1);
	unsigned int index = (pin * blocksize) / n_bits;
	data &= mask;
	if(index < 2){
		GPIOB->AFR[index] &= ~( mask << ((pin * blocksize) - (index * n_bits)) );
		GPIOB->AFR[index] |= ( data << ((pin * blocksize) - (index * n_bits)) );
	}
}

/*** GPIOC ***/
// GPIO -> GPIOC
STM32446GPIOC STM32446GPIOCenable(void)
{
	STM32446GPIOC gpioc;
	// GPIOC
	gpioc.reg = (GPIO_TypeDef*) GPIOC_BASE;
	gpioc.moder = STM32446GpioCmoder;
	gpioc.ospeedr = STM32446GpioCospeedr;
	gpioc.pupdr = STM32446GpioCpupdr;
	gpioc.reset = STM32446GpioCreset;
	gpioc.set = STM32446GpioCset;
	gpioc.afr = STM32446GpioCafr;

	STM32446GpioCenable( );

	return gpioc;
}

void STM32446GpioCenable( void )
{
	RCC->AHB1ENR |= (1 << 2);
}

void STM32446GpioCmoder( unsigned int data, unsigned int pin )
{
	const unsigned int blocksize = 2;
	unsigned int mask = (unsigned int)(pow(2, blocksize) - 1);
	data &= mask;
	GPIOC->MODER &= ~(mask << (pin * blocksize));
	GPIOC->MODER |= (data << (pin * blocksize));
}

void STM32446GpioCospeedr( unsigned int data, unsigned int pin )
{
	const unsigned int blocksize = 2;
	unsigned int mask = (unsigned int)(pow(2, blocksize) - 1);
	data &= mask;
	GPIOC->OSPEEDR &= ~(mask << (pin * blocksize));
	GPIOC->OSPEEDR |= (data << (pin * blocksize));
}

void STM32446GpioCpupdr( unsigned int data, unsigned int pin )
{
	const unsigned int blocksize = 2;
	unsigned int mask = (unsigned int)(pow(2, blocksize) - 1);
	data &= mask;
	GPIOC->PUPDR &= ~(mask << (pin * blocksize));
	GPIOC->PUPDR |= (data << (pin * blocksize));
}

void STM32446GpioCreset( unsigned int data )
{
	GPIOC->BSRR = (unsigned int)(data << 16);
}

void STM32446GpioCset( unsigned int data )
{
	GPIOC->BSRR = (unsigned int)( data );
}

void STM32446GpioCafr( unsigned int data, unsigned int pin )
{
	const unsigned int blocksize = 4;
	const unsigned int n_bits = sizeof(unsigned int) * 8;
	const unsigned int mask = (unsigned int) (pow(2, blocksize) - 1);
	unsigned int index = (pin * blocksize) / n_bits;
	data &= mask;
	if(index < 2){
		GPIOC->AFR[index] &= ~( mask << ((pin * blocksize) - (index * n_bits)) );
		GPIOC->AFR[index] |= ( data << ((pin * blocksize) - (index * n_bits)) );
	}
}

/*** GPIOD ***/
// GPIO -> GPIOD
STM32446GPIOD STM32446GPIODenable(void)
{
	STM32446GPIOD gpiod;
	// GPIOD
	gpiod.reg = (GPIO_TypeDef*) GPIOD_BASE;
	gpiod.moder = STM32446GpioDmoder;
	gpiod.ospeedr = STM32446GpioDospeedr;
	gpiod.pupdr = STM32446GpioDpupdr;
	gpiod.reset = STM32446GpioDreset;
	gpiod.set = STM32446GpioDset;
	gpiod.afr = STM32446GpioDafr;

	STM32446GpioDenable( );

	return gpiod;
}

void STM32446GpioDenable( void )
{
	RCC->AHB1ENR |= (1 << 3);
}

void STM32446GpioDmoder( unsigned int data, unsigned int pin )
{
	const unsigned int blocksize = 2;
	unsigned int mask = (unsigned int)(pow(2, blocksize) - 1);
	data &= mask;
	GPIOD->MODER &= ~(mask << (pin * blocksize));
	GPIOD->MODER |= (data << (pin * blocksize));
}

void STM32446GpioDospeedr( unsigned int data, unsigned int pin )
{
	const unsigned int blocksize = 2;
	unsigned int mask = (unsigned int)(pow(2, blocksize) - 1);
	data &= mask;
	GPIOD->OSPEEDR &= ~(mask << (pin * blocksize));
	GPIOD->OSPEEDR |= (data << (pin * blocksize));
}

void STM32446GpioDpupdr( unsigned int data, unsigned int pin )
{
	const unsigned int blocksize = 2;
	unsigned int mask = (unsigned int)(pow(2, blocksize) - 1);
	data &= mask;
	GPIOD->PUPDR &= ~(mask << (pin * blocksize));
	GPIOD->PUPDR |= (data << (pin * blocksize));
}

void STM32446GpioDreset( unsigned int data )
{
	GPIOD->BSRR = (unsigned int)(data << 16);
}

void STM32446GpioDset( unsigned int data )
{
	GPIOD->BSRR = (unsigned int)( data );
}

void STM32446GpioDafr( unsigned int data, unsigned int pin )
{
	const unsigned int blocksize = 4;
	const unsigned int n_bits = sizeof(unsigned int) * 8;
	const unsigned int mask = (unsigned int) (pow(2, blocksize) - 1);
	unsigned int index = (pin * blocksize) / n_bits;
	data &= mask;
	if(index < 2){
		GPIOD->AFR[index] &= ~( mask << ((pin * blocksize) - (index * n_bits)) );
		GPIOD->AFR[index] |= ( data << ((pin * blocksize) - (index * n_bits)) );
	}
}

/*** GPIOE ***/
// GPIO -> GPIOE
STM32446GPIOE STM32446GPIOEenable(void)
{
	STM32446GPIOE gpioe;
	// GPIOE
	gpioe.reg = (GPIO_TypeDef*) GPIOE_BASE;
	gpioe.moder = STM32446GpioEmoder;
	gpioe.ospeedr = STM32446GpioEospeedr;
	gpioe.pupdr = STM32446GpioEpupdr;
	gpioe.reset = STM32446GpioEreset;
	gpioe.set = STM32446GpioEset;
	gpioe.afr = STM32446GpioEafr;

	STM32446GpioEenable( );

	return gpioe;
}

void STM32446GpioEenable( void )
{
	RCC->AHB1ENR |= (1 << 4);
}

void STM32446GpioEmoder( unsigned int data, unsigned int pin )
{
	const unsigned int blocksize = 2;
	unsigned int mask = (unsigned int)(pow(2, blocksize) - 1);
	data &= mask;
	GPIOE->MODER &= ~(mask << (pin * blocksize));
	GPIOE->MODER |= (data << (pin * blocksize));
}

void STM32446GpioEospeedr( unsigned int data, unsigned int pin )
{
	const unsigned int blocksize = 2;
	unsigned int mask = (unsigned int)(pow(2, blocksize) - 1);
	data &= mask;
	GPIOE->OSPEEDR &= ~(mask << (pin * blocksize));
	GPIOE->OSPEEDR |= (data << (pin * blocksize));
}

void STM32446GpioEpupdr( unsigned int data, unsigned int pin )
{
	const unsigned int blocksize = 2;
	unsigned int mask = (unsigned int)(pow(2, blocksize) - 1);
	data &= mask;
	GPIOE->PUPDR &= ~(mask << (pin * blocksize));
	GPIOE->PUPDR |= (data << (pin * blocksize));
}

void STM32446GpioEreset( unsigned int data )
{
	GPIOE->BSRR = (unsigned int)(data << 16);
}

void STM32446GpioEset( unsigned int data )
{
	GPIOE->BSRR = (unsigned int)( data );
}

void STM32446GpioEafr( unsigned int data, unsigned int pin )
{
	const unsigned int blocksize = 4;
	const unsigned int n_bits = sizeof(unsigned int) * 8;
	const unsigned int mask = (unsigned int) (pow(2, blocksize) - 1);
	unsigned int index = (pin * blocksize) / n_bits;
	data &= mask;
	if(index < 2){
		GPIOE->AFR[index] &= ~( mask << ((pin * blocksize) - (index * n_bits)) );
		GPIOE->AFR[index] |= ( data << ((pin * blocksize) - (index * n_bits)) );
	}
}

/*** GPIOF ***/
// GPIO -> GPIOF
STM32446GPIOF STM32446GPIOFenable(void)
{
	STM32446GPIOF gpiof;
	// GPIOF
	gpiof.reg = (GPIO_TypeDef*) GPIOF_BASE;
	gpiof.moder = STM32446GpioFmoder;
	gpiof.ospeedr = STM32446GpioFospeedr;
	gpiof.pupdr = STM32446GpioFpupdr;
	gpiof.reset = STM32446GpioFreset;
	gpiof.set = STM32446GpioFset;
	gpiof.afr = STM32446GpioFafr;

	STM32446GpioFenable( );

	return gpiof;
}

void STM32446GpioFenable( void )
{
	RCC->AHB1ENR |= (1 << 5);
}

void STM32446GpioFmoder( unsigned int data, unsigned int pin )
{
	const unsigned int blocksize = 2;
	unsigned int mask = (unsigned int)(pow(2, blocksize) - 1);
	data &= mask;
	GPIOF->MODER &= ~(mask << (pin * blocksize));
	GPIOF->MODER |= (data << (pin * blocksize));
}

void STM32446GpioFospeedr( unsigned int data, unsigned int pin )
{
	const unsigned int blocksize = 2;
	unsigned int mask = (unsigned int)(pow(2, blocksize) - 1);
	data &= mask;
	GPIOF->OSPEEDR &= ~(mask << (pin * blocksize));
	GPIOF->OSPEEDR |= (data << (pin * blocksize));
}

void STM32446GpioFpupdr( unsigned int data, unsigned int pin )
{
	const unsigned int blocksize = 2;
	unsigned int mask = (unsigned int)(pow(2, blocksize) - 1);
	data &= mask;
	GPIOF->PUPDR &= ~(mask << (pin * blocksize));
	GPIOF->PUPDR |= (data << (pin * blocksize));
}

void STM32446GpioFreset( unsigned int data )
{
	GPIOF->BSRR = (unsigned int)(data << 16);
}

void STM32446GpioFset( unsigned int data )
{
	GPIOF->BSRR = (unsigned int)( data );
}

void STM32446GpioFafr( unsigned int data, unsigned int pin )
{
	const unsigned int blocksize = 4;
	const unsigned int n_bits = sizeof(unsigned int) * 8;
	const unsigned int mask = (unsigned int) (pow(2, blocksize) - 1);
	unsigned int index = (pin * blocksize) / n_bits;
	data &= mask;
	if(index < 2){
		GPIOF->AFR[index] &= ~( mask << ((pin * blocksize) - (index * n_bits)) );
		GPIOF->AFR[index] |= ( data << ((pin * blocksize) - (index * n_bits)) );
	}
}

/*** GPIOG ***/
// GPIO -> GPIOG
STM32446GPIOG STM32446GPIOGenable(void)
{
	STM32446GPIOG gpiog;
	// GPIOG
	gpiog.reg = (GPIO_TypeDef*) GPIOG_BASE;
	gpiog.moder = STM32446GpioGmoder;
	gpiog.ospeedr = STM32446GpioGospeedr;
	gpiog.pupdr = STM32446GpioGpupdr;
	gpiog.reset = STM32446GpioGreset;
	gpiog.set = STM32446GpioGset;
	gpiog.afr = STM32446GpioGafr;

	STM32446GpioGenable( );

	return gpiog;
}

void STM32446GpioGenable( void )
{
	RCC->AHB1ENR |= (1 << 6);
}

void STM32446GpioGmoder( unsigned int data, unsigned int pin )
{
	const unsigned int blocksize = 2;
	unsigned int mask = (unsigned int)(pow(2, blocksize) - 1);
	data &= mask;
	GPIOG->MODER &= ~(mask << (pin * blocksize));
	GPIOG->MODER |= (data << (pin * blocksize));
}

void STM32446GpioGospeedr( unsigned int data, unsigned int pin )
{
	const unsigned int blocksize = 2;
	unsigned int mask = (unsigned int)(pow(2, blocksize) - 1);
	data &= mask;
	GPIOG->OSPEEDR &= ~(mask << (pin * blocksize));
	GPIOG->OSPEEDR |= (data << (pin * blocksize));
}

void STM32446GpioGpupdr( unsigned int data, unsigned int pin )
{
	const unsigned int blocksize = 2;
	unsigned int mask = (unsigned int)(pow(2, blocksize) - 1);
	data &= mask;
	GPIOG->PUPDR &= ~(mask << (pin * blocksize));
	GPIOG->PUPDR |= (data << (pin * blocksize));
}

void STM32446GpioGreset( unsigned int data )
{
	GPIOG->BSRR = (unsigned int)(data << 16);
}

void STM32446GpioGset( unsigned int data )
{
	GPIOG->BSRR = (unsigned int)( data );
}

void STM32446GpioGafr( unsigned int data, unsigned int pin )
{
	const unsigned int blocksize = 4;
	const unsigned int n_bits = sizeof(unsigned int) * 8;
	const unsigned int mask = (unsigned int) (pow(2, blocksize) - 1);
	unsigned int index = (pin * blocksize) / n_bits;
	data &= mask;
	if(index < 2){
		GPIOG->AFR[index] &= ~( mask << ((pin * blocksize) - (index * n_bits)) );
		GPIOG->AFR[index] |= ( data << ((pin * blocksize) - (index * n_bits)) );
	}
}

/*** GPIOH ***/
// GPIO -> GPIOH
STM32446GPIOH STM32446GPIOHenable(void)
{
	STM32446GPIOH gpioh;
	// GPIOH
	gpioh.reg = (GPIO_TypeDef*) GPIOH_BASE;
	gpioh.moder = STM32446GpioHmoder;
	gpioh.ospeedr = STM32446GpioHospeedr;
	gpioh.pupdr = STM32446GpioHpupdr;
	gpioh.reset = STM32446GpioHreset;
	gpioh.set = STM32446GpioHset;
	gpioh.afr = STM32446GpioHafr;

	STM32446GpioHenable( );

	return gpioh;
}

void STM32446GpioHenable( void )
{
	RCC->AHB1ENR |= (1 << 7);
}

void STM32446GpioHmoder( unsigned int data, unsigned int pin )
{
	const unsigned int blocksize = 2;
	unsigned int mask = (unsigned int)(pow(2, blocksize) - 1);
	data &= mask;
	GPIOH->MODER &= ~(mask << (pin * blocksize));
	GPIOH->MODER |= (data << (pin * blocksize));
}

void STM32446GpioHospeedr( unsigned int data, unsigned int pin )
{
	const unsigned int blocksize = 2;
	unsigned int mask = (unsigned int)(pow(2, blocksize) - 1);
	data &= mask;
	GPIOH->OSPEEDR &= ~(mask << (pin * blocksize));
	GPIOH->OSPEEDR |= (data << (pin * blocksize));
}

void STM32446GpioHpupdr( unsigned int data, unsigned int pin )
{
	const unsigned int blocksize = 2;
	unsigned int mask = (unsigned int)(pow(2, blocksize) - 1);
	data &= mask;
	GPIOH->PUPDR &= ~(mask << (pin * blocksize));
	GPIOH->PUPDR |= (data << (pin * blocksize));
}

void STM32446GpioHreset( unsigned int data )
{
	GPIOH->BSRR = (unsigned int)(data << 16);
}

void STM32446GpioHset( unsigned int data )
{
	GPIOH->BSRR = (unsigned int)( data );
}

void STM32446GpioHafr( unsigned int data, unsigned int pin )
{
	const unsigned int blocksize = 4;
	const unsigned int n_bits = sizeof(unsigned int) * 8;
	const unsigned int mask = (unsigned int) (pow(2, blocksize) - 1);
	unsigned int index = (pin * blocksize) / n_bits;
	data &= mask;
	if(index < 2){
		GPIOH->AFR[index] &= ~( mask << ((pin * blocksize) - (index * n_bits)) );
		GPIOH->AFR[index] |= ( data << ((pin * blocksize) - (index * n_bits)) );
	}
}

/**** EOF ****/

/*
 * More Interested in finding the best work flow, then coding itself. Because that will become redundant after
 * achieving the objective.
 *
 * **/


