/******************************************************************************
	STM32 446 MAPPING
Author: Sergio Santos 
	<sergio.salazar.santos@gmail.com>
License: GNU General Public License
Hardware: STM32-446
Date: 15062023
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
// CORE
#define STM32446_SCB_BASE ((0xE000E000UL) + 0x0D00UL))

/*** File Variable ***/
static STM32446 stm32446;
static uint32_t DelayCounter;
static uint32_t mem[4];
static uint32_t nen[4];

/*** File Header ***/
/*** TOP ***/
uint32_t STM32446_readreg(uint32_t reg, uint32_t size_block, uint32_t bit);
void STM32446_writereg(volatile uint32_t* reg, uint32_t size_block, uint32_t bit, uint32_t data);
void STM32446_setreg(volatile uint32_t* reg, uint32_t size_block, uint32_t bit, uint32_t data);
void STM32446_setbit(volatile uint32_t* reg, uint32_t size_block, uint32_t bit, uint32_t data);
uint32_t STM32446_getsetbit(volatile uint32_t* reg, uint32_t size_block, uint32_t bit);

/*** SYSTICK ***/
void SystickInic(void);
void STM32446delay_ms(uint32_t ms);
void STM32446delay_10us(uint32_t ten_us);
void STM32446delay_us(uint32_t us);
// INTERRUPT
void SysTick_Handler(void);

// QUERY CLOCK
uint32_t STM32446_getclocksource(void);
uint32_t STM32446_pllsource(void);
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

/*** MISCELLANEOUS ***/
// MCU
void STM32446RegSetBits( unsigned int* reg, int n_bits, ... );
void STM32446RegResetBits( unsigned int* reg, int n_bits, ... );
void STM32446VecSetup( volatile uint32_t vec[], const unsigned int size_block, unsigned int data, unsigned int block_n );
// BUTTON
uint32_t STM32446triggerA(uint32_t hllh_io, uint8_t pin, uint32_t counter);
uint32_t STM32446triggerB(uint32_t hl_io, uint32_t lh_io, uint8_t pin, uint32_t counter);
// BYTE
uint16_t STM32ReadHLByte(STM32HighLowByte reg);
uint16_t STM32ReadLHByte(STM32HighLowByte reg);
STM32HighLowByte STM32WriteHLByte(uint16_t val);
STM32HighLowByte STM32WriteLHByte(uint16_t val);
uint16_t STM32SwapByte(uint16_t num);
// GENERIC
char* STM32446FUNCftoa(double num, char* res, uint8_t afterpoint);
char* STM32446FUNCprint( char* str, uint8_t size_str, const char* format, ... );
char STM32446bcd2dec(char num);
char STM32446dec2bcd(char num);
//COMMON
void STM32446Reverse(char s[]);
int STM32446StringLength (const char string[]);
uint8_t STM32446FUNCintinvstr(int32_t num, char* res, uint8_t n_digit);

/******* STM32F446RE Procedure & Function Definition *******/
STM32446 STM32446enable(void){
	/*** DEFAULT ***/
	mem[0] = 0;
	nen[0] = 0;
	/************* CORE ************/
	// Coprocessor Access Control Register
	stm32446.scb.reg = ((SCB_Type*) STM32446_SCB_BASE;

	// NVIC
	#if defined(_STM32446NVIC_H_)
		stm32446.nvic = nvic_inic();
	#endif

	// SysTick (Used as Delay Source)
	stm32446.systick.reg = (SysTick_Type*) SysTick_BASE;
	stm32446.systick.delay_ms = STM32446delay_ms;
	stm32446.systick.delay_10us = STM32446delay_10us;
	stm32446.systick.delay_us = STM32446delay_us;
	
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
	
	// DMA1
	stm32446.dma1.reg = DMA1;
	stm32446.dma1.stream[0].reg = DMA1_Stream0;

	// DMA2
	stm32446.dma2.reg = DMA2;
	stm32446.dma2.stream[0].reg = DMA2_Stream0;

	// FLASH
	#if defined(_STM32446FLASH_H_)
		stm32446.flash = flash_inic();
	#endif

	#if defined(_STM32446GPIO_H_)
		stm32446.gpioa = gpioa_inic();
		stm32446.gpiob = gpiob_inic();
		stm32446.gpioc = gpioc_inic();
		stm32446.gpiod = gpiod_inic();
		stm32446.gpioe = gpioe_inic();
		stm32446.gpioh = gpioh_inic();
	#endif

	// SYSCFG
	stm32446.syscfg.reg = SYSCFG;
	
	// PWR
	#if defined(_STM32446PWR_H_)
		stm32446.pwr = pwr_inic();
	#endif

	#if defined(_STM32446RCC_H_)
		stm32446.rcc = rcc_inic();
	#endif
	
	#if defined(_STM32446RTC_H_)
		stm32446.rtc = rtc_inic();
	#endif
	
	#if defined(_STM32446SRAM_H_)
		stm32446.sram = sram_inic();
	#endif

	#if defined(_STM32446TIM_H_)
		stm32446.tim1 = tim1_inic();
		stm32446.tim2 = tim2_inic();
		stm32446.tim3 = tim3_inic();
		stm32446.tim4 = tim4_inic();
		stm32446.tim5 = tim5_inic();
		stm32446.tim6 = tim6_inic();
		stm32446.tim7 = tim7_inic();
		stm32446.tim8 = tim8_inic();
		stm32446.tim9 = tim9_inic();
		stm32446.tim10 = tim10_inic();
		stm32446.tim11 = tim11_inic();
		stm32446.tim12 = tim12_inic();
		stm32446.tim13 = tim13_inic();
		stm32446.tim1 = tim1_inic();
	#endif

	#if defined(_STM32446USART_H_)
		stm32446.usart1 = usart1_inic();
		stm32446.usart2 = usart2_inic();
		stm32446.usart3 = usart3_inic();
		stm32446.uart4 = uart4_inic();
		stm32446.uart5 = uart5_inic();
		stm32446.usart6 = usart6_inic();
	#endif

	// QUERY
	stm32446.query.ClockSource = STM32446_getclocksource;
	stm32446.query.PllSource = STM32446_pllsource;
	stm32446.query.CLOCK_prescaler.AHB = STM32446_gethpre;
	stm32446.query.CLOCK_prescaler.APB1 = STM32446_gethppre1;
	stm32446.query.CLOCK_prescaler.APB2 = STM32446_gethppre2;
	stm32446.query.CLOCK_prescaler.RTCclk = STM32446_getrtcpre;
	stm32446.query.CLOCK_prescaler.MCO1 = STM32446_gethmco1pre;
	stm32446.query.CLOCK_prescaler.MCO2 = STM32446_gethmco2pre;
	stm32446.query.PLL_parameter.M = STM32446_getpllm;
	stm32446.query.PLL_parameter.N = STM32446_getplln;
	stm32446.query.PLL_parameter.P = STM32446_getpllp;
	stm32446.query.PLL_parameter.Q = STM32446_getpllq;
	stm32446.query.PLL_parameter.R = STM32446_getpllr;
	stm32446.query.SystemClock = STM32446_getsysclk;

	// FUNC
	stm32446.func.bcd2dec = STM32446bcd2dec;
	stm32446.func.dec2bcd = STM32446dec2bcd;
	stm32446.func.triggerA = STM32446triggerA;
	stm32446.func.triggerB = STM32446triggerB;
	stm32446.func.ReadHLByte = STM32ReadHLByte;
	stm32446.func.ReadLHByte = STM32ReadLHByte;
	stm32446.func.WriteHLByte = STM32WriteHLByte;
	stm32446.func.WriteLHByte = STM32WriteLHByte;
	stm32446.func.SwapByte = STM32SwapByte;
	stm32446.func.ftoa = STM32446FUNCftoa;
	stm32446.func.print = STM32446FUNCprint;
	stm32446.func.regsetbits = STM32446RegSetBits;
	stm32446.func.regresetbits = STM32446RegResetBits;
	stm32446.func.vecsetup = STM32446VecSetup;
	stm32446.func.readreg = STM32446_readreg;
	stm32446.func.writereg = STM32446_writereg;
	stm32446.func.setreg = STM32446_setreg;
	stm32446.func.setbit = STM32446_setbit;
	stm32446.func.getsetbit = STM32446_getsetbit;
	
	SystickInic(); // Polling delay source.

	return stm32446;
}

/*** Query Procedure & Function Definition ***/
uint32_t STM32446_getclocksource(void)
{
	uint32_t reg = RCC->CR;
	uint32_t source;
	if(reg & (1 << 1)){source = HSI_RC;}else if(reg & (1 << 17)){source = HSE_OSC;}

	return source;
}

uint32_t STM32446_pllsource(void)
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

/*** MISCELLANEOUS ***/
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

// Convert Binary Coded Decimal (BCD) to Decimal
char STM32446bcd2dec(char num)
{
	return ((num / 16 * 10) + (num % 16));
}

// Convert Decimal to Binary Coded Decimal (BCD)
char STM32446dec2bcd(char num)
{
	return ((num / 10 * 16) + (num % 10));
}

// triggerA
uint32_t STM32446triggerA(uint32_t hllh_io, uint8_t pin, uint32_t counter)
{
	mem[3] = 0;
	
	switch(mem[0]){
		case 0:
			if(hllh_io & (1 << pin)){
				mem[1] = counter;
				mem[0] = 1;
			}
		break;
		case 1:
			if(hllh_io & (1 << pin)){
				mem[2] = counter;
				if((mem[2] + 1) > mem[1]){
					mem[3] = mem[2] - mem[1];
				}else{
					mem[3] = ((uint32_t) ~0 - mem[1]) + mem[2];
				}
				mem[0] = 0;
			}
		break;
		default:
		break;
	}
	return mem[3];
}

// triggerB
uint32_t STM32446triggerB(uint32_t hl_io, uint32_t lh_io, uint8_t pin, uint32_t counter)
{
	nen[3] = 0;
	
	switch(nen[0]){ // Start value
		case 0:
			nen[1] = counter;
			if(hl_io & (1 << pin))
				nen[0] = 1;
		break;
		case 1:
			nen[2] = counter;
			if(nen[2] == nen[1])
				nen[2] += sizeof(nen[0]) * 8;
			if(lh_io & (1 << pin)){
				nen[3] = nen[2] - nen[1];
				nen[0] = 0;
			}
		break;
		default:
		break;
	}
	return nen[3];
}

uint16_t STM32ReadHLByte(STM32HighLowByte reg)
{
	return (uint16_t)(reg.H << 8) | reg.L;
}

uint16_t STM32ReadLHByte(STM32HighLowByte reg)
{
	return (uint16_t)(reg.L << 8) | reg.H;
}

STM32HighLowByte STM32WriteHLByte(uint16_t val)
{
	STM32HighLowByte reg; reg.H = (uint8_t)(val >> 8); reg.L = (uint8_t)val;
	return reg;
}

STM32HighLowByte STM32WriteLHByte(uint16_t val)
{
	STM32HighLowByte reg; reg.L = (uint8_t)(val >> 8); reg.H = (uint8_t)val; 
	return reg;
}

uint16_t STM32SwapByte(uint16_t num)
{
	uint16_t tp;
	tp = (uint16_t)(num << 8);
	return (num >> 8) | tp;
}

// ftoa
char* STM32446FUNCftoa(double num, char* res, uint8_t afterpoint)
{
	uint32_t ipart;
	double n, fpart;
	uint8_t k = 0;
	int8_t sign;
	if (num < 0){
		n = -num; sign = -1;
	}else{
		n = num; sign = 1;
	}
	ipart = (uint32_t) n; fpart = n - (double)ipart;
	k = STM32446FUNCintinvstr((int)ipart, res, 1);
	if (sign < 0) res[k++] = '-'; else res[k++] = ' ';
	res[k] = '\0';
	STM32446Reverse(res);
	if (afterpoint > 0 && afterpoint < (8 + 1)){
		res[k++] = '.';
		STM32446FUNCintinvstr( (int32_t)(fpart * pow(10, afterpoint)), (res + k), afterpoint );
		STM32446Reverse(res + k);
	}else{
		res[k++] = '.';
		STM32446FUNCintinvstr( (int32_t)(fpart * pow(10, 2)), (res + k), 2 );
		STM32446Reverse(res + k);
	}
	return res;
}

// print
char* STM32446FUNCprint( char* str, uint8_t size_str, const char* format, ... )
{
	va_list aptr;
	int ret;

	va_start(aptr, format);
	ret = vsnprintf( str, size_str, (const char*) format, aptr );
	//ret = vsnprintf( ptr, size_str, format, aptr );
	va_end(aptr);

	if(ret < 0){
		return NULL;
		//str[0]='/0';str[1]='/0';str[2]='/0';str[3]='/0';
	}else
		return str;
}

// Function to count the number of characters in a string
int STM32446StringLength (const char string[])
{
	int count;
	for (count = 0; string[count] != '\0'; count++ ) ;
	return count;
}

// reverse: reverse string s in place
void STM32446Reverse(char s[])
{
	char c;
	int i, j;
	for ( i = 0, j = STM32446StringLength(s) - 1; i < j ; i++, j-- ){
		c = s[i];
		s[i] = s[j];
		s[j] = c;
	}
}

// intinvstr
uint8_t STM32446FUNCintinvstr(int32_t num, char* res, uint8_t n_digit)
{
	uint8_t k = 0;
	for(res[k++] = (char)((num % 10) + '0'); (num /= 10) > 0 ; res[k++] = (char)((num % 10) + '0'));
	for( ; k < n_digit ; res[k++] = '0');
	res[k] = '\0';
	return k;
}

/************************ SYSTICK ************************/
void SystickInic(void)
{
	SysTick->LOAD = (uint32_t)( stm32446.query.SystemClock() - 1);
	SysTick->VAL = 0UL;
	SysTick->CTRL |= ((1 << 1) | (1 << 2));
}

void STM32446delay_ms(uint32_t ms)
{
	SysTick->LOAD = (uint32_t)(( stm32446.query.SystemClock() / 1000 ) - 1);
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
	SysTick->LOAD = (uint32_t)(( stm32446.query.SystemClock() / 100000) - 1);
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
	SysTick->LOAD = (uint32_t)(( stm32446.query.SystemClock() / 1000000) - 1);
	// Enable the SysTick timer
	SysTick->CTRL |= (1 << 0);
	// Wait for a specified number of milliseconds
	DelayCounter = 0;
	while (DelayCounter < us);
	// Disable the SysTick timer
	SysTick->CTRL &= (uint32_t) ~(1 << 0);
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


