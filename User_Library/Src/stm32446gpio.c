/******************************************************************************
	STM32 446 GPIO
Author: Sergio Santos 
	<sergio.salazar.santos@gmail.com>
License: GNU General Public License
Hardware: STM32-446
Date: 02062023
Comment:
	File Vars, File Function Header, Library Function Definitions.
	
*******************************************************************************/
/*** File Library ***/
#include <stm32446mapping.h>
#include "stm32446gpio.h"
#include "math.h"

/*** File Procedure & Funtion Header ***/
uint32_t gpio_getbit(uint32_t reg, uint32_t size_block, uint32_t bit);
void gpio_setbit(volatile uint32_t* reg, uint32_t size_block, uint32_t bit, uint32_t data);
uint32_t gpio_getsetbit(volatile uint32_t* reg, uint32_t size_block, uint32_t bit);

/*** GPIO Procedure & Function Definition ***/
/*** GPIOA ***/
void STM32446GpioAclock( void )
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
void STM32446GpioBclock( void )
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
void STM32446GpioCclock( void )
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
void STM32446GpioDclock( void )
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
void STM32446GpioEclock( void )
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
void STM32446GpioFclock( void )
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
void STM32446GpioGclock( void )
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
void STM32446GpioHclock( void )
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

/*** File Procedure & Funtion Definition ***/
uint32_t gpio_getbit(uint32_t reg, uint32_t size_block, uint32_t bit)
{
	uint32_t value = 0; uint32_t tmp = 0;

	uint32_t mask = (unsigned int)((1 << size_block) - 1);
	mask = (mask << bit);
	tmp = mask & reg;
	value = (tmp >> bit);
	return value;
}

void gpio_setbit(volatile uint32_t* reg, uint32_t size_block, uint32_t bit, uint32_t data)
{
	uint32_t n = 0;
	if(bit > 31){ n = bit/32; bit = bit - (n * 32); }
	uint32_t value = 0;
	uint32_t mask = (unsigned int)((1 << size_block) - 1);
	value = data & mask;
	*(reg + n ) &= ~(mask << bit);
	*(reg + n ) |= (value << bit);
}

uint32_t gpio_getsetbit(volatile uint32_t* reg, uint32_t size_block, uint32_t bit)
{
	uint32_t n = 0;
	if(bit > 31){ n = bit/32; bit = bit - (n * 32); }
	uint32_t value = 0;
	uint32_t mask = (unsigned int)((1 << size_block) - 1);
	value = *(reg + n ) & ~(mask << bit);
	value = (value >> bit);
	return value;
}

/**** EOF ****/

/*
 * More Interested in finding the best work flow, then coding itself. Because that will become redundant after
 * achieving the objective.
 *
 * **/


