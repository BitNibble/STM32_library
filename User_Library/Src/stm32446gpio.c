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
#include "stm32446mapping.h"
#include "stm32446gpio.h"
#include "math.h"

/*** File Procedure & Function Header ***/
uint32_t gpio_readreg(uint32_t reg, uint32_t size_block, uint32_t bit);
void gpio_writereg(volatile uint32_t* reg, uint32_t size_block, uint32_t bit, uint32_t data);
void gpio_setreg(volatile uint32_t* reg, uint32_t size_block, uint32_t bit, uint32_t data);
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

/*** INIC Procedure & Function Definition ***/
STM32446GpioAobj gpioa_inic(void)
{
	STM32446GpioAobj stm32446_gpioa;
	// GPIOA
	stm32446_gpioa.reg = GPIOA;
	/*** GPIOA RCC Clock Enable ***/
	stm32446_gpioa.clock = STM32446GpioAclock;
	/*** GPIOA Bit Mapping Link ***/
	stm32446_gpioa.moder = STM32446GpioAmoder;
	stm32446_gpioa.ospeedr = STM32446GpioAospeedr;
	stm32446_gpioa.pupdr = STM32446GpioApupdr;
	stm32446_gpioa.reset = STM32446GpioAreset;
	stm32446_gpioa.set = STM32446GpioAset;
	stm32446_gpioa.afr = STM32446GpioAafr;
	/*** Other ***/
	stm32446_gpioa.func.readreg = gpio_readreg;
	stm32446_gpioa.func.writereg = gpio_writereg;
	stm32446_gpioa.func.setreg = gpio_setreg;
	stm32446_gpioa.func.setbit = gpio_setbit;
	stm32446_gpioa.func.getsetbit = gpio_getsetbit;

	return stm32446_gpioa;
}

STM32446GpioBobj gpiob_inic(void)
{
	STM32446GpioBobj stm32446_gpiob;
	// GPIOB
	stm32446_gpiob.reg = GPIOB;
	/*** GPIOB RCC Clock Enable ***/
	stm32446_gpiob.clock = STM32446GpioBclock;
	/*** GPIOB Bit Mapping Link ***/
	stm32446_gpiob.moder = STM32446GpioBmoder;
	stm32446_gpiob.ospeedr = STM32446GpioBospeedr;
	stm32446_gpiob.pupdr = STM32446GpioBpupdr;
	stm32446_gpiob.reset = STM32446GpioBreset;
	stm32446_gpiob.set = STM32446GpioBset;
	stm32446_gpiob.afr = STM32446GpioBafr;
	/*** Other ***/
	stm32446_gpiob.func.readreg = gpio_readreg;
	stm32446_gpiob.func.writereg = gpio_writereg;
	stm32446_gpiob.func.setreg = gpio_setreg;
	stm32446_gpiob.func.setbit = gpio_setbit;
	stm32446_gpiob.func.getsetbit = gpio_getsetbit;

	return stm32446_gpiob;
}

STM32446GpioCobj gpioc_inic(void)
{
	STM32446GpioCobj stm32446_gpioc;
	// GPIOC
	stm32446_gpioc.reg = GPIOC;
	/*** GPIOC RCC Clock Enable ***/
	stm32446_gpioc.clock = STM32446GpioCclock;
	/*** GPIOC Bit Mapping Link ***/
	stm32446_gpioc.moder = STM32446GpioCmoder;
	stm32446_gpioc.ospeedr = STM32446GpioCospeedr;
	stm32446_gpioc.pupdr = STM32446GpioCpupdr;
	stm32446_gpioc.reset = STM32446GpioCreset;
	stm32446_gpioc.set = STM32446GpioCset;
	stm32446_gpioc.afr = STM32446GpioCafr;
	/*** Other ***/
	stm32446_gpioc.func.readreg = gpio_readreg;
	stm32446_gpioc.func.writereg = gpio_writereg;
	stm32446_gpioc.func.setreg = gpio_setreg;
	stm32446_gpioc.func.setbit = gpio_setbit;
	stm32446_gpioc.func.getsetbit = gpio_getsetbit;

	return stm32446_gpioc;
}

STM32446GpioDobj gpiod_inic(void)
{
	STM32446GpioDobj stm32446_gpiod;
	// GPIOD
	stm32446_gpiod.reg = GPIOD;
	/*** GPIOD RCC Clock Enable ***/
	stm32446_gpiod.clock = STM32446GpioDclock;
	/*** GPIOD Bit Mapping Link ***/
	stm32446_gpiod.moder = STM32446GpioDmoder;
	stm32446_gpiod.ospeedr = STM32446GpioDospeedr;
	stm32446_gpiod.pupdr = STM32446GpioDpupdr;
	stm32446_gpiod.reset = STM32446GpioDreset;
	stm32446_gpiod.set = STM32446GpioDset;
	stm32446_gpiod.afr = STM32446GpioDafr;
	/*** Other ***/
	stm32446_gpiod.func.readreg = gpio_readreg;
	stm32446_gpiod.func.writereg = gpio_writereg;
	stm32446_gpiod.func.setreg = gpio_setreg;
	stm32446_gpiod.func.setbit = gpio_setbit;
	stm32446_gpiod.func.getsetbit = gpio_getsetbit;

	return stm32446_gpiod;
}

STM32446GpioEobj gpioe_inic(void)
{
	STM32446GpioEobj stm32446_gpioe;
	// GPIOE
	stm32446_gpioe.reg = GPIOE;
	/*** GPIOE RCC Clock Enable ***/
	stm32446_gpioe.clock = STM32446GpioEclock;
	/*** GPIOE Bit Mapping Link ***/
	stm32446_gpioe.moder = STM32446GpioEmoder;
	stm32446_gpioe.ospeedr = STM32446GpioEospeedr;
	stm32446_gpioe.pupdr = STM32446GpioEpupdr;
	stm32446_gpioe.reset = STM32446GpioEreset;
	stm32446_gpioe.set = STM32446GpioEset;
	stm32446_gpioe.afr = STM32446GpioEafr;
	/*** Other ***/
	stm32446_gpioe.func.readreg = gpio_readreg;
	stm32446_gpioe.func.writereg = gpio_writereg;
	stm32446_gpioe.func.setreg = gpio_setreg;
	stm32446_gpioe.func.setbit = gpio_setbit;
	stm32446_gpioe.func.getsetbit = gpio_getsetbit;

	return stm32446_gpioe;
}

STM32446GpioHobj gpioh_inic(void)
{
	STM32446GpioHobj stm32446_gpioh;
	// GPIOH
	stm32446_gpioh.reg = GPIOH;
	/*** GPIOH RCC Clock Enable ***/
	stm32446_gpioh.clock = STM32446GpioHclock;
	/*** GPIOH Bit Mapping Link ***/
	stm32446_gpioh.moder = STM32446GpioHmoder;
	stm32446_gpioh.ospeedr = STM32446GpioHospeedr;
	stm32446_gpioh.pupdr = STM32446GpioHpupdr;
	stm32446_gpioh.reset = STM32446GpioHreset;
	stm32446_gpioh.set = STM32446GpioHset;
	stm32446_gpioh.afr = STM32446GpioHafr;
	/*** Other ***/
	stm32446_gpioh.func.readreg = gpio_readreg;
	stm32446_gpioh.func.writereg = gpio_writereg;
	stm32446_gpioh.func.setreg = gpio_setreg;
	stm32446_gpioh.func.setbit = gpio_setbit;
	stm32446_gpioh.func.getsetbit = gpio_getsetbit;

	return stm32446_gpioh;
}

/*** File Procedure & Function Definition ***/
uint32_t gpio_readreg(uint32_t reg, uint32_t size_block, uint32_t bit)
{
	if(bit > 31){ bit = 0;} if(size_block > 32){ size_block = 32;}
	uint32_t value = reg;
	uint32_t mask = (unsigned int)((1 << size_block) - 1);
	value &= (mask << bit);
	value = (value >> bit);
	return value;
}

void gpio_writereg(volatile uint32_t* reg, uint32_t size_block, uint32_t bit, uint32_t data)
{
	if(bit > 31){ bit = 0;} if(size_block > 32){ size_block = 32;}
	uint32_t value = data;
	uint32_t mask = (unsigned int)((1 << size_block) - 1);
	value &= mask;
	value = (value << bit);
	*reg = value;
}

void gpio_setreg(volatile uint32_t* reg, uint32_t size_block, uint32_t bit, uint32_t data)
{
	if(bit > 31){ bit = 0;} if(size_block > 32){ size_block = 32;}
	uint32_t value = data;
	uint32_t mask = (unsigned int)((1 << size_block) - 1);
	value &= mask;
	*reg &= ~(mask << bit);
	*reg |= (value << bit);
}

void gpio_setbit(volatile uint32_t* reg, uint32_t size_block, uint32_t bit, uint32_t data)
{
	uint32_t n = 0;
	if(bit > 31){ n = bit/32; bit = bit - (n * 32); } if(size_block > 32){ size_block = 32;}
	uint32_t value = data;
	uint32_t mask = (unsigned int)((1 << size_block) - 1);
	value &= mask;
	*(reg + n ) &= ~(mask << bit);
	*(reg + n ) |= (value << bit);
}

uint32_t gpio_getsetbit(volatile uint32_t* reg, uint32_t size_block, uint32_t bit)
{
	uint32_t n = 0;
	if(bit > 31){ n = bit/32; bit = bit - (n * 32); } if(size_block > 32){ size_block = 32;}
	uint32_t value = *(reg + n );
	uint32_t mask = (unsigned int)((1 << size_block) - 1);
	value &= (mask << bit);
	value = (value >> bit);
	return value;
}

/**** EOF ****/

/*
 * More Interested in finding the best work flow, then coding itself. Because that will become redundant after
 * achieving the objective.
 *
 * **/


