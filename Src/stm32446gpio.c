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
#include "stm32446mapping.h"
#include "stm32446gpio.h"
#include "math.h"

static STM32446 stm32446;
static STM32446GPIOA gpioa;
static STM32446GPIOB gpiob;
static STM32446GPIOC gpioc;
static STM32446GPIOD gpiod;
static STM32446GPIOE gpioe;
static STM32446GPIOF gpiof;
static STM32446GPIOG gpiog;
static STM32446GPIOH gpioh;

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
	stm32446 = STM32446enable();

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
	stm32446.rcc.reg->AHB1ENR |= (1 << 0);
}

void STM32446GpioAmoder( unsigned int data, unsigned int pin )
{
	const unsigned int blocksize = 2;
	unsigned int mask = (unsigned int)(pow(2, blocksize) - 1);
	data &= mask;
	gpioa.reg->MODER &= ~(mask << (pin * blocksize));
	gpioa.reg->MODER |= (data << (pin * blocksize));
}

void STM32446GpioAospeedr( unsigned int data, unsigned int pin )
{
	const unsigned int blocksize = 2;
	unsigned int mask = (unsigned int)(pow(2, blocksize) - 1);
	data &= mask;
	gpioa.reg->OSPEEDR &= ~(mask << (pin * blocksize));
	gpioa.reg->OSPEEDR |= (data << (pin * blocksize));
}

void STM32446GpioApupdr( unsigned int data, unsigned int pin )
{
	const unsigned int blocksize = 2;
	unsigned int mask = (unsigned int)(pow(2, blocksize) - 1);
	data &= mask;
	gpioa.reg->PUPDR &= ~(mask << (pin * blocksize));
	gpioa.reg->PUPDR |= (data << (pin * blocksize));
}

void STM32446GpioAreset( unsigned int data )
{
	gpioa.reg->BSRR = (unsigned int)(data << 16);
}

void STM32446GpioAset( unsigned int data )
{
	gpioa.reg->BSRR = (unsigned int)( data );
}

void STM32446GpioAafr( unsigned int data, unsigned int pin )
{
	const unsigned int blocksize = 4;
	const unsigned int n_bits = sizeof(unsigned int) * 8;
	const unsigned int mask = (unsigned int) (pow(2, blocksize) - 1);
	unsigned int index = (pin * blocksize) / n_bits;
	data &= mask;
	if(index < 2){
		gpioa.reg->AFR[index] &= ~( mask << ((pin * blocksize) - (index * n_bits)) );
		gpioa.reg->AFR[index] |= ( data << ((pin * blocksize) - (index * n_bits)) );
	}
}

/*** GPIOB ***/
// GPIO -> GPIOB
STM32446GPIOB STM32446GPIOBenable(void)
{
	stm32446 = STM32446enable();

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
	stm32446.rcc.reg->AHB1ENR |= (1 << 1);
}

void STM32446GpioBmoder( unsigned int data, unsigned int pin )
{
	const unsigned int blocksize = 2;
	unsigned int mask = (unsigned int)(pow(2, blocksize) - 1);
	data &= mask;
	gpiob.reg->MODER &= ~(mask << (pin * blocksize));
	gpiob.reg->MODER |= (data << (pin * blocksize));
}

void STM32446GpioBospeedr( unsigned int data, unsigned int pin )
{
	const unsigned int blocksize = 2;
	unsigned int mask = (unsigned int)(pow(2, blocksize) - 1);
	data &= mask;
	gpiob.reg->OSPEEDR &= ~(mask << (pin * blocksize));
	gpiob.reg->OSPEEDR |= (data << (pin * blocksize));
}

void STM32446GpioBpupdr( unsigned int data, unsigned int pin )
{
	const unsigned int blocksize = 2;
	unsigned int mask = (unsigned int)(pow(2, blocksize) - 1);
	data &= mask;
	gpiob.reg->PUPDR &= ~(mask << (pin * blocksize));
	gpiob.reg->PUPDR |= (data << (pin * blocksize));
}

void STM32446GpioBreset( unsigned int data )
{
	gpiob.reg->BSRR = (unsigned int)(data << 16);
}

void STM32446GpioBset( unsigned int data )
{
	gpiob.reg->BSRR = (unsigned int)( data );
}

void STM32446GpioBafr( unsigned int data, unsigned int pin )
{
	const unsigned int blocksize = 4;
	const unsigned int n_bits = sizeof(unsigned int) * 8;
	const unsigned int mask = (unsigned int) (pow(2, blocksize) - 1);
	unsigned int index = (pin * blocksize) / n_bits;
	data &= mask;
	if(index < 2){
		gpiob.reg->AFR[index] &= ~( mask << ((pin * blocksize) - (index * n_bits)) );
		gpiob.reg->AFR[index] |= ( data << ((pin * blocksize) - (index * n_bits)) );
	}
}

/*** GPIOC ***/
// GPIO -> GPIOC
STM32446GPIOC STM32446GPIOCenable(void)
{
	stm32446 = STM32446enable();

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
	stm32446.rcc.reg->AHB1ENR |= (1 << 2);
}

void STM32446GpioCmoder( unsigned int data, unsigned int pin )
{
	const unsigned int blocksize = 2;
	unsigned int mask = (unsigned int)(pow(2, blocksize) - 1);
	data &= mask;
	gpioc.reg->MODER &= ~(mask << (pin * blocksize));
	gpioc.reg->MODER |= (data << (pin * blocksize));
}

void STM32446GpioCospeedr( unsigned int data, unsigned int pin )
{
	const unsigned int blocksize = 2;
	unsigned int mask = (unsigned int)(pow(2, blocksize) - 1);
	data &= mask;
	gpioc.reg->OSPEEDR &= ~(mask << (pin * blocksize));
	gpioc.reg->OSPEEDR |= (data << (pin * blocksize));
}

void STM32446GpioCpupdr( unsigned int data, unsigned int pin )
{
	const unsigned int blocksize = 2;
	unsigned int mask = (unsigned int)(pow(2, blocksize) - 1);
	data &= mask;
	gpioc.reg->PUPDR &= ~(mask << (pin * blocksize));
	gpioc.reg->PUPDR |= (data << (pin * blocksize));
}

void STM32446GpioCreset( unsigned int data )
{
	gpioc.reg->BSRR = (unsigned int)(data << 16);
}

void STM32446GpioCset( unsigned int data )
{
	gpioc.reg->BSRR = (unsigned int)( data );
}

void STM32446GpioCafr( unsigned int data, unsigned int pin )
{
	const unsigned int blocksize = 4;
	const unsigned int n_bits = sizeof(unsigned int) * 8;
	const unsigned int mask = (unsigned int) (pow(2, blocksize) - 1);
	unsigned int index = (pin * blocksize) / n_bits;
	data &= mask;
	if(index < 2){
		gpioc.reg->AFR[index] &= ~( mask << ((pin * blocksize) - (index * n_bits)) );
		gpioc.reg->AFR[index] |= ( data << ((pin * blocksize) - (index * n_bits)) );
	}
}

/*** GPIOD ***/
// GPIO -> GPIOD
STM32446GPIOD STM32446GPIODenable(void)
{
	stm32446 = STM32446enable();

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
	stm32446.rcc.reg->AHB1ENR |= (1 << 3);
}

void STM32446GpioDmoder( unsigned int data, unsigned int pin )
{
	const unsigned int blocksize = 2;
	unsigned int mask = (unsigned int)(pow(2, blocksize) - 1);
	data &= mask;
	gpiod.reg->MODER &= ~(mask << (pin * blocksize));
	gpiod.reg->MODER |= (data << (pin * blocksize));
}

void STM32446GpioDospeedr( unsigned int data, unsigned int pin )
{
	const unsigned int blocksize = 2;
	unsigned int mask = (unsigned int)(pow(2, blocksize) - 1);
	data &= mask;
	gpiod.reg->OSPEEDR &= ~(mask << (pin * blocksize));
	gpiod.reg->OSPEEDR |= (data << (pin * blocksize));
}

void STM32446GpioDpupdr( unsigned int data, unsigned int pin )
{
	const unsigned int blocksize = 2;
	unsigned int mask = (unsigned int)(pow(2, blocksize) - 1);
	data &= mask;
	gpiod.reg->PUPDR &= ~(mask << (pin * blocksize));
	gpiod.reg->PUPDR |= (data << (pin * blocksize));
}

void STM32446GpioDreset( unsigned int data )
{
	gpiod.reg->BSRR = (unsigned int)(data << 16);
}

void STM32446GpioDset( unsigned int data )
{
	gpiod.reg->BSRR = (unsigned int)( data );
}

void STM32446GpioDafr( unsigned int data, unsigned int pin )
{
	const unsigned int blocksize = 4;
	const unsigned int n_bits = sizeof(unsigned int) * 8;
	const unsigned int mask = (unsigned int) (pow(2, blocksize) - 1);
	unsigned int index = (pin * blocksize) / n_bits;
	data &= mask;
	if(index < 2){
		gpiod.reg->AFR[index] &= ~( mask << ((pin * blocksize) - (index * n_bits)) );
		gpiod.reg->AFR[index] |= ( data << ((pin * blocksize) - (index * n_bits)) );
	}
}

/*** GPIOE ***/
// GPIO -> GPIOE
STM32446GPIOE STM32446GPIOEenable(void)
{
	stm32446 = STM32446enable();

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
	stm32446.rcc.reg->AHB1ENR |= (1 << 4);
}

void STM32446GpioEmoder( unsigned int data, unsigned int pin )
{
	const unsigned int blocksize = 2;
	unsigned int mask = (unsigned int)(pow(2, blocksize) - 1);
	data &= mask;
	gpioe.reg->MODER &= ~(mask << (pin * blocksize));
	gpioe.reg->MODER |= (data << (pin * blocksize));
}

void STM32446GpioEospeedr( unsigned int data, unsigned int pin )
{
	const unsigned int blocksize = 2;
	unsigned int mask = (unsigned int)(pow(2, blocksize) - 1);
	data &= mask;
	gpioe.reg->OSPEEDR &= ~(mask << (pin * blocksize));
	gpioe.reg->OSPEEDR |= (data << (pin * blocksize));
}

void STM32446GpioEpupdr( unsigned int data, unsigned int pin )
{
	const unsigned int blocksize = 2;
	unsigned int mask = (unsigned int)(pow(2, blocksize) - 1);
	data &= mask;
	gpioe.reg->PUPDR &= ~(mask << (pin * blocksize));
	gpioe.reg->PUPDR |= (data << (pin * blocksize));
}

void STM32446GpioEreset( unsigned int data )
{
	gpioe.reg->BSRR = (unsigned int)(data << 16);
}

void STM32446GpioEset( unsigned int data )
{
	gpioe.reg->BSRR = (unsigned int)( data );
}

void STM32446GpioEafr( unsigned int data, unsigned int pin )
{
	const unsigned int blocksize = 4;
	const unsigned int n_bits = sizeof(unsigned int) * 8;
	const unsigned int mask = (unsigned int) (pow(2, blocksize) - 1);
	unsigned int index = (pin * blocksize) / n_bits;
	data &= mask;
	if(index < 2){
		gpioe.reg->AFR[index] &= ~( mask << ((pin * blocksize) - (index * n_bits)) );
		gpioe.reg->AFR[index] |= ( data << ((pin * blocksize) - (index * n_bits)) );
	}
}

/*** GPIOF ***/
// GPIO -> GPIOF
STM32446GPIOF STM32446GPIOFenable(void)
{
	stm32446 = STM32446enable();

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
	stm32446.rcc.reg->AHB1ENR |= (1 << 5);
}

void STM32446GpioFmoder( unsigned int data, unsigned int pin )
{
	const unsigned int blocksize = 2;
	unsigned int mask = (unsigned int)(pow(2, blocksize) - 1);
	data &= mask;
	gpiof.reg->MODER &= ~(mask << (pin * blocksize));
	gpiof.reg->MODER |= (data << (pin * blocksize));
}

void STM32446GpioFospeedr( unsigned int data, unsigned int pin )
{
	const unsigned int blocksize = 2;
	unsigned int mask = (unsigned int)(pow(2, blocksize) - 1);
	data &= mask;
	gpiof.reg->OSPEEDR &= ~(mask << (pin * blocksize));
	gpiof.reg->OSPEEDR |= (data << (pin * blocksize));
}

void STM32446GpioFpupdr( unsigned int data, unsigned int pin )
{
	const unsigned int blocksize = 2;
	unsigned int mask = (unsigned int)(pow(2, blocksize) - 1);
	data &= mask;
	gpiof.reg->PUPDR &= ~(mask << (pin * blocksize));
	gpiof.reg->PUPDR |= (data << (pin * blocksize));
}

void STM32446GpioFreset( unsigned int data )
{
	gpiof.reg->BSRR = (unsigned int)(data << 16);
}

void STM32446GpioFset( unsigned int data )
{
	gpiof.reg->BSRR = (unsigned int)( data );
}

void STM32446GpioFafr( unsigned int data, unsigned int pin )
{
	const unsigned int blocksize = 4;
	const unsigned int n_bits = sizeof(unsigned int) * 8;
	const unsigned int mask = (unsigned int) (pow(2, blocksize) - 1);
	unsigned int index = (pin * blocksize) / n_bits;
	data &= mask;
	if(index < 2){
		gpiof.reg->AFR[index] &= ~( mask << ((pin * blocksize) - (index * n_bits)) );
		gpiof.reg->AFR[index] |= ( data << ((pin * blocksize) - (index * n_bits)) );
	}
}

/*** GPIOG ***/
// GPIO -> GPIOG
STM32446GPIOG STM32446GPIOGenable(void)
{
	stm32446 = STM32446enable();

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
	stm32446.rcc.reg->AHB1ENR |= (1 << 6);
}

void STM32446GpioGmoder( unsigned int data, unsigned int pin )
{
	const unsigned int blocksize = 2;
	unsigned int mask = (unsigned int)(pow(2, blocksize) - 1);
	data &= mask;
	gpiog.reg->MODER &= ~(mask << (pin * blocksize));
	gpiog.reg->MODER |= (data << (pin * blocksize));
}

void STM32446GpioGospeedr( unsigned int data, unsigned int pin )
{
	const unsigned int blocksize = 2;
	unsigned int mask = (unsigned int)(pow(2, blocksize) - 1);
	data &= mask;
	gpiog.reg->OSPEEDR &= ~(mask << (pin * blocksize));
	gpiog.reg->OSPEEDR |= (data << (pin * blocksize));
}

void STM32446GpioGpupdr( unsigned int data, unsigned int pin )
{
	const unsigned int blocksize = 2;
	unsigned int mask = (unsigned int)(pow(2, blocksize) - 1);
	data &= mask;
	gpiog.reg->PUPDR &= ~(mask << (pin * blocksize));
	gpiog.reg->PUPDR |= (data << (pin * blocksize));
}

void STM32446GpioGreset( unsigned int data )
{
	gpiog.reg->BSRR = (unsigned int)(data << 16);
}

void STM32446GpioGset( unsigned int data )
{
	gpiog.reg->BSRR = (unsigned int)( data );
}

void STM32446GpioGafr( unsigned int data, unsigned int pin )
{
	const unsigned int blocksize = 4;
	const unsigned int n_bits = sizeof(unsigned int) * 8;
	const unsigned int mask = (unsigned int) (pow(2, blocksize) - 1);
	unsigned int index = (pin * blocksize) / n_bits;
	data &= mask;
	if(index < 2){
		gpiog.reg->AFR[index] &= ~( mask << ((pin * blocksize) - (index * n_bits)) );
		gpiog.reg->AFR[index] |= ( data << ((pin * blocksize) - (index * n_bits)) );
	}
}

/*** GPIOH ***/
// GPIO -> GPIOH
STM32446GPIOH STM32446GPIOHenable(void)
{
	stm32446 = STM32446enable();

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
	stm32446.rcc.reg->AHB1ENR |= (1 << 7);
}

void STM32446GpioHmoder( unsigned int data, unsigned int pin )
{
	const unsigned int blocksize = 2;
	unsigned int mask = (unsigned int)(pow(2, blocksize) - 1);
	data &= mask;
	gpioh.reg->MODER &= ~(mask << (pin * blocksize));
	gpioh.reg->MODER |= (data << (pin * blocksize));
}

void STM32446GpioHospeedr( unsigned int data, unsigned int pin )
{
	const unsigned int blocksize = 2;
	unsigned int mask = (unsigned int)(pow(2, blocksize) - 1);
	data &= mask;
	gpioh.reg->OSPEEDR &= ~(mask << (pin * blocksize));
	gpioh.reg->OSPEEDR |= (data << (pin * blocksize));
}

void STM32446GpioHpupdr( unsigned int data, unsigned int pin )
{
	const unsigned int blocksize = 2;
	unsigned int mask = (unsigned int)(pow(2, blocksize) - 1);
	data &= mask;
	gpioh.reg->PUPDR &= ~(mask << (pin * blocksize));
	gpioh.reg->PUPDR |= (data << (pin * blocksize));
}

void STM32446GpioHreset( unsigned int data )
{
	gpioh.reg->BSRR = (unsigned int)(data << 16);
}

void STM32446GpioHset( unsigned int data )
{
	gpioh.reg->BSRR = (unsigned int)( data );
}

void STM32446GpioHafr( unsigned int data, unsigned int pin )
{
	const unsigned int blocksize = 4;
	const unsigned int n_bits = sizeof(unsigned int) * 8;
	const unsigned int mask = (unsigned int) (pow(2, blocksize) - 1);
	unsigned int index = (pin * blocksize) / n_bits;
	data &= mask;
	if(index < 2){
		gpioh.reg->AFR[index] &= ~( mask << ((pin * blocksize) - (index * n_bits)) );
		gpioh.reg->AFR[index] |= ( data << ((pin * blocksize) - (index * n_bits)) );
	}
}

/**** EOF ****/


