/******************************************************************************
	STM32 446 MAPPING
Author: Sergio Santos 
	<sergio.salazar.santos@gmail.com>
License: GNU General Public License
Hardware: STM32-446
Date: 22062023
Comment:
	-manual um1724, m0390, pm0056, pm0214, and other sources.
	-Virtual Image STM32-446, mapping.
	-Still in progress 15062023, increment has go along.
	-Dependent on CMSIS
	-Stable.
*******************************************************************************/
/*** File Library ***/
#include "stm32446mapping.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <math.h>
/*** File Constant & Macros ***/
// CPACR is located at address 0xE000ED88
#define STM32446_SCB_BASE ((0xE000E000UL) + 0x0D00UL))
/*** File Variable ***/
static uint32_t DelayCounter;
/*** File Header ***/
uint32_t STM32446_readreg(uint32_t reg, uint32_t size_block, uint32_t bit);
void STM32446_writereg(volatile uint32_t* reg, uint32_t size_block, uint32_t bit, uint32_t data);
void STM32446_setreg(volatile uint32_t* reg, uint32_t size_block, uint32_t bit, uint32_t data);
void STM32446_setbit(volatile uint32_t* reg, uint32_t size_block, uint32_t bit, uint32_t data);
uint32_t STM32446_getsetbit(volatile uint32_t* reg, uint32_t size_block, uint32_t bit);
// QUERY
STM32446CLOCK_prescaler CLOCK_prescaler_inic(void);
STM32446PLL_parameter PLL_parameter_inic(void);
STM32446Query query_inic(void);
uint32_t STM32446_getclocksource(void);
uint32_t STM32446_getpllsource(void);
uint16_t STM32446_gethpre(void);
uint8_t STM32446_gethppre1(void);
uint8_t STM32446_gethppre2(void);
uint8_t STM32446_getrtcpre(void);
uint8_t STM32446_gethmco1pre(void);
uint8_t STM32446_gethmco2pre(void);
uint8_t STM32446_getpllm(void);
uint16_t STM32446_getplln(void);
uint8_t STM32446_getpllp(void);
uint8_t STM32446_getpllq(void);
uint8_t STM32446_getpllr(void);
uint32_t STM32446_getsysclk(void);
// SysTick
STM32446SysTickobj systick_inic(void);
void SystickInic(void);
void STM32446delay_ms(uint32_t ms);
void STM32446delay_10us(uint32_t ten_us);
void STM32446delay_us(uint32_t us);
/******* STM32F446RE Procedure & Function Definition *******/
STM32446 STM32446enable(void){
	STM32446 stm32446;
	/************* CORE ************/
	// Coprocessor Access Control Register
	stm32446.scb.reg = ((SCB_Type*) STM32446_SCB_BASE;
	// NVIC
	#if defined(_STM32446NVIC_H_)
		stm32446.nvic = nvic_inic();
	#endif
	// SysTick (Used as Delay Source)
	stm32446.systick = systick_inic();
	/************ MCU ************/
	// ADC -> ADC1
	#if defined(_STM32446ADC_H_)
		stm32446.adc1 = adc1_inic();
		stm32446.adc2 = adc2_inic();
		stm32446.adc3 = adc3_inic();
	#endif
	// CRC
	#if defined(_STM32446CRC_H_)
		stm32446.crc = crc_inic();
	#endif
	#if defined(_STM32446DMA_H_)
	// DMA1
		stm32446.dma1 = dma1_inic();
	// DMA2
		stm32446.dma2 = dma2_inic();
	#endif
	// FLASH
	#if defined(_STM32446FLASH_H_)
		stm32446.flash = flash_inic();
	#endif
	// GPIO
	#if defined(_STM32446GPIO_H_)
		stm32446.gpioa = gpioa_inic();
		stm32446.gpiob = gpiob_inic();
		stm32446.gpioc = gpioc_inic();
		stm32446.gpiod = gpiod_inic();
		stm32446.gpioe = gpioe_inic();
		stm32446.gpioh = gpioh_inic();
	#endif
	// SYSCFG
	#if defined(_STM32446SYSCFG_H_)
		stm32446.syscfg.reg = SYSCFG;
	#endif
	// PWR
	#if defined(_STM32446PWR_H_)
		stm32446.pwr = pwr_inic();
	#endif
	// RCC
	#if defined(_STM32446RCC_H_)
		stm32446.rcc = rcc_inic();
	#endif
	// RTC
	#if defined(_STM32446RTC_H_)
		stm32446.rtc = rtc_inic();
	#endif
	// SRAM
	#if defined(_STM32446SRAM_H_)
		stm32446.sram = sram_inic();
	#endif
	// TIM
	#if defined(_STM32446TIM1AND8_H_)
		stm32446.tim1 = tim1_inic();
		stm32446.tim8 = tim8_inic();
	#endif
	#if defined(_STM32446TIM2TO5_H_)
		stm32446.tim2 = tim2_inic();
		stm32446.tim3 = tim3_inic();
		stm32446.tim4 = tim4_inic();
		stm32446.tim5 = tim5_inic();
	#endif
	#if defined(_STM32446TIM6AND7_H_)
		stm32446.tim6 = tim6_inic();
		stm32446.tim7 = tim7_inic();
	#endif
	#if defined(_STM32446TIM9TO14_H_)
		stm32446.tim9 = tim9_inic();
		stm32446.tim10 = tim10_inic();
		stm32446.tim11 = tim11_inic();
		stm32446.tim12 = tim12_inic();
		stm32446.tim13 = tim13_inic();
		stm32446.tim14 = tim14_inic();
	#endif
	// USART
	#if defined(_STM32446USART_H_)
		stm32446.usart1 = usart1_inic();
		stm32446.usart2 = usart2_inic();
		stm32446.usart3 = usart3_inic();
		stm32446.uart4 = uart4_inic();
		stm32446.uart5 = uart5_inic();
		stm32446.usart6 = usart6_inic();
	#endif
	// QUERY
	stm32446.query = query_inic();
	// PRIVATE
	#if defined(_FUNCTION_H_)
		stm32446.func = FUNCenable();
	#endif
	
	SystickInic(); // Polling delay source.

	return stm32446;
}
/*** Query ***/
STM32446CLOCK_prescaler CLOCK_prescaler_inic(void)
{
	STM32446CLOCK_prescaler stm32446_CLOCK_prescaler;
	stm32446_CLOCK_prescaler.AHB = STM32446_gethpre;
	stm32446_CLOCK_prescaler.APB1 = STM32446_gethppre1;
	stm32446_CLOCK_prescaler.APB2 = STM32446_gethppre2;
	stm32446_CLOCK_prescaler.RTCclk = STM32446_getrtcpre;
	stm32446_CLOCK_prescaler.MCO1 = STM32446_gethmco1pre;
	stm32446_CLOCK_prescaler.MCO2 = STM32446_gethmco2pre;
	return stm32446_CLOCK_prescaler;
}
STM32446PLL_parameter PLL_parameter_inic(void)
{
	STM32446PLL_parameter stm32446_PLL_parameter;
	stm32446_PLL_parameter.M = STM32446_getpllm;
	stm32446_PLL_parameter.N = STM32446_getplln;
	stm32446_PLL_parameter.P = STM32446_getpllp;
	stm32446_PLL_parameter.Q = STM32446_getpllq;
	stm32446_PLL_parameter.R = STM32446_getpllr;
	return stm32446_PLL_parameter;
}
STM32446Query query_inic(void)
{
	STM32446Query stm32446_query;
	stm32446_query.CLOCK_prescaler = CLOCK_prescaler_inic();
	stm32446_query.PLL_parameter = PLL_parameter_inic();
	stm32446_query.ClockSource = STM32446_getclocksource;
	stm32446_query.PllSource = STM32446_getpllsource;
	stm32446_query.SystemClock = STM32446_getsysclk;
	return stm32446_query;
}
uint32_t STM32446_getclocksource(void)
{
	uint32_t reg = RCC->CR;
	uint32_t source;
	if(reg & (1 << 1)){source = HSI_RC;}else if(reg & (1 << 17)){source = HSE_OSC;}
	return source;
}
uint32_t STM32446_getpllsource(void)
{
	uint32_t reg = RCC->CFGR;
	uint32_t source;
	if(reg & (1 << 22)) source = HSE_OSC; else source = HSI_RC;
	return source;
}
uint16_t STM32446_gethpre(void)
{
	uint32_t value = STM32446_readreg(RCC->CFGR, 4, 4);
	switch(value)
	{
		case 0b1000:
			value = 2;
		break;
		case 0b1001:
			value = 4;
		break;
		case 0b1010:
			value = 8;
		break;
		case 0b1011:
			value = 16;
		break;
		case 0b1100:
			value = 64;
		break;
		case 0b1101:
			value = 128;
		break;
		case 0b1110:
			value = 256;
		break;
		case 0b1111:
			value = 512;
		break;
		default:
			value = 1;
		break;
	}
	return value;
}
uint8_t STM32446_gethppre1(void)
{
	uint32_t value = STM32446_readreg(RCC->CFGR, 3, 10);
	switch(value)
	{
		case 0b100:
			value = 2;
		break;
		case 0b101:
			value = 4;
		break;
		case 0b110:
			value = 8;
		break;
		case 0b111:
			value = 16;
		break;
		default:
			value = 1;
		break;
	}
	return value;
}
uint8_t STM32446_gethppre2(void)
{
	uint32_t value = STM32446_readreg(RCC->CFGR, 3, 13);
	switch(value)
	{
		case 0b100:
			value = 2;
		break;
		case 0b101:
			value = 4;
		break;
		case 0b110:
			value = 8;
		break;
		case 0b111:
			value = 16;
		break;
		default:
			value = 1;
		break;
	}
	return value;
}
uint8_t STM32446_getrtcpre(void)
{
	return STM32446_readreg(RCC->CFGR, 5, 16);
}
uint8_t STM32446_gethmco1pre(void)
{
	uint32_t value = STM32446_readreg(RCC->CFGR, 3, 24);
	switch(value)
	{
		case 0b100:
			value = 2;
		break;
		case 0b101:
			value = 3;
		break;
		case 0b110:
			value = 4;
		break;
		case 0b111:
			value = 5;
		break;
		default:
			value = 1;
		break;
	}
	return value;
}
uint8_t STM32446_gethmco2pre(void)
{
	uint32_t value = STM32446_readreg(RCC->CFGR, 3, 27);
	switch(value)
	{
		case 0b100:
			value = 2;
		break;
		case 0b101:
			value = 3;
		break;
		case 0b110:
			value = 4;
		break;
		case 0b111:
			value = 5;
		break;
		default:
			value = 1;
		break;
		}
	return value;
}
uint8_t STM32446_getpllm(void)
{
	return STM32446_readreg(RCC->PLLCFGR, 6, 0);
}
uint16_t STM32446_getplln(void)
{
	return STM32446_readreg(RCC->PLLCFGR, 9, 6);
}
uint8_t STM32446_getpllp(void)
{
	uint32_t value = STM32446_readreg(RCC->PLLCFGR, 2, 16);
	switch(value)
	{
		case 0b00:
			value = 2;
		break;
		case 0b01:
			value = 4;
		break;
		case 0b10:
			value = 6;
		break;
		case 0b11:
			value = 8;
		break;
		default:
		break;
	}
	return value;
}
uint8_t STM32446_getpllq(void)
{
	return STM32446_readreg(RCC->PLLCFGR, 4, 24);
}
uint8_t STM32446_getpllr(void)
{
	return STM32446_readreg(RCC->PLLCFGR, 3, 28);
}
uint32_t STM32446_getsysclk(void)
{
	uint32_t value = STM32446_readreg(RCC->CFGR, 2, 2);
	switch(value) // SWS[2]: System clock switch status
	{
		case 1: // 01: HSE oscillator used as the system clock
			value = HSE_OSC;
		break;
		case 2: // 10: PLL used as the system clock
			value = ( STM32446_getclocksource() / STM32446_getpllm() ) * ( STM32446_getplln() / STM32446_getpllp() );
		break;
		case 3: // 11: PLL_R used as the system clock
			value = ( STM32446_getclocksource() / STM32446_getpllm() ) * ( STM32446_getplln() / STM32446_getpllr() );
		break;
		default: // 00: HSI oscillator used as the system clock
			value = HSI_RC;
		break;
	}
	return value;
}
/*** SysTick ****/
STM32446SysTickobj systick_inic(void)
{
	STM32446SysTickobj stm32446_systick;
	stm32446_systick.reg = (SysTick_Type*) SysTick_BASE;
	stm32446_systick.delay_ms = STM32446delay_ms;
	stm32446_systick.delay_10us = STM32446delay_10us;
	stm32446_systick.delay_us = STM32446delay_us;
	return stm32446_systick;
}
void SystickInic(void)
{
	SysTick->LOAD = (uint32_t)( STM32446_getsysclk() - 1);
	SysTick->VAL = 0UL;
	SysTick->CTRL |= ((1 << 1) | (1 << 2));
}
void STM32446delay_ms(uint32_t ms)
{
	SysTick->LOAD = (uint32_t)(( STM32446_getsysclk() / 1000 ) - 1);
	// Enable the SysTick timer
	SysTick->CTRL |= (1 << 0);
	// Wait for a specified number of milliseconds
	DelayCounter = 0;
	while (DelayCounter < ms);
	// Disable the SysTick timer
	SysTick->CTRL &= (uint32_t) ~(1 << 0);
}
void STM32446delay_10us(uint32_t ten_us)
{
	SysTick->LOAD = (uint32_t)(( STM32446_getsysclk() / 100000) - 1);
	// Enable the SysTick timer
	SysTick->CTRL |= (1 << 0);
	// Wait for a specified number of milliseconds
	DelayCounter = 0;
	while (DelayCounter < ten_us);
	// Disable the SysTick timer
	SysTick->CTRL &= (uint32_t) ~(1 << 0);
}
void STM32446delay_us(uint32_t us)
{
	SysTick->LOAD = (uint32_t)(( STM32446_getsysclk() / 1000000) - 1);
	// Enable the SysTick timer
	SysTick->CTRL |= (1 << 0);
	// Wait for a specified number of milliseconds
	DelayCounter = 0;
	while (DelayCounter < us);
	// Disable the SysTick timer
	SysTick->CTRL &= (uint32_t) ~(1 << 0);
}
/*** File Procedure & Function Definition ***/
uint32_t STM32446_readreg(uint32_t reg, uint32_t size_block, uint32_t bit)
{
	if(bit > 31){ bit = 0;} if(size_block > 32){ size_block = 32;}
	uint32_t value = reg;
	uint32_t mask = (unsigned int)((1 << size_block) - 1);
	value &= (mask << bit);
	value = (value >> bit);
	return value;
}
void STM32446_writereg(volatile uint32_t* reg, uint32_t size_block, uint32_t bit, uint32_t data)
{
	if(bit > 31){ bit = 0;} if(size_block > 32){ size_block = 32;}
	uint32_t value = data;
	uint32_t mask = (unsigned int)((1 << size_block) - 1);
	value &= mask;
	value = (value << bit);
	*reg = value;
}
void STM32446_setreg(volatile uint32_t* reg, uint32_t size_block, uint32_t bit, uint32_t data)
{
	if(bit > 31){ bit = 0;} if(size_block > 32){ size_block = 32;}
	uint32_t value = data;
	uint32_t mask = (unsigned int)((1 << size_block) - 1);
	value &= mask;
	*reg &= ~(mask << bit);
	*reg |= (value << bit);
}
void STM32446_setbit(volatile uint32_t* reg, uint32_t size_block, uint32_t bit, uint32_t data)
{
	uint32_t n = 0;
	if(bit > 31){ n = bit/32; bit = bit - (n * 32); } if(size_block > 32){ size_block = 32;}
	uint32_t value = data;
	uint32_t mask = (unsigned int)((1 << size_block) - 1);
	value &= mask;
	*(reg + n ) &= ~(mask << bit);
	*(reg + n ) |= (value << bit);
}
uint32_t STM32446_getsetbit(volatile uint32_t* reg, uint32_t size_block, uint32_t bit)
{
	uint32_t n = 0;
	if(bit > 31){ n = bit/32; bit = bit - (n * 32); } if(size_block > 32){ size_block = 32;}
	uint32_t value = *(reg + n );
	uint32_t mask = (unsigned int)((1 << size_block) - 1);
	value &= (mask << bit);
	value = (value >> bit);
	return value;
}
void STM32446RegSetBits( unsigned int* reg, int n_bits, ... )
{
	uint8_t i;
	if(n_bits > 0 && n_bits < 33){ // Filter input
		va_list list;
		va_start(list, n_bits);
		for(i = 0; i < n_bits; i++){
			*reg |= (unsigned int)(1 << va_arg(list, int));
		}
		va_end(list);
	}
}
void STM32446RegResetBits( unsigned int* reg, int n_bits, ... )
{
	uint8_t i;
	if(n_bits > 0 && n_bits < 33){ // Filter input
		va_list list;
		va_start(list, n_bits);
		for(i = 0; i < n_bits; i++){
			*reg &= (unsigned int)~((1 << va_arg(list, int)) << 16);
		}
		va_end(list);
	}
}
void STM32446VecSetup( volatile uint32_t vec[], const unsigned int size_block, unsigned int data, unsigned int block_n )
{
	const unsigned int n_bits = sizeof(data) * 8;
	const unsigned int mask = (unsigned int) (pow(2, size_block) - 1);
	unsigned int index = (block_n * size_block) / n_bits;
	data &= mask;
	vec[index] &= ~( mask << ((block_n * size_block) - (index * n_bits)) );
	vec[index] |= ( data << ((block_n * size_block) - (index * n_bits)) );
}
/*** File Interrupt Definition ***/
void SysTick_Handler(void)
{ // count down to zero systick interrupt and reload.
	DelayCounter++;
}

/***EOF***/

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

/*********
1º Make struct
2º Make SUB struct with vars
3º Make Function pointers
4º Make Function that returns SUB struct with initialised vars
5º Make Functions that initialises SUB struct links
6º Make Function that returns the struct with the above functions
*********/


