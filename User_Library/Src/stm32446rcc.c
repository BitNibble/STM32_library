/******************************************************************************
	STM32 446 RCC
Author: Sergio Santos 
	<sergio.salazar.santos@gmail.com>
License: GNU General Public License
Hardware: STM32-446
Date: 02062023
Comment:
	
*******************************************************************************/
/*** File Library ***/
#include "stm32446mapping.h"
#include "stm32446rcc.h"

/*** File Procedure & Funtion Header ***/
uint32_t rcc_getbit(uint32_t reg, uint32_t size_block, uint32_t bit);
void rcc_setbit(volatile uint32_t* reg, uint32_t size_block, uint32_t bit, uint32_t data);
uint32_t rcc_getsetbit(volatile uint32_t* reg, uint32_t size_block, uint32_t bit);

uint8_t STM32446RccInic(void)
{
	uint8_t clkused; // First turn it on then select it or enable it.
	// Setup PLL
	// PLLDIVISION parameters
	// source 0 or 1		M 2 to 63		N 50 to 432		P 2,4,6,8
	// Q 2 to 15			R 2 to 7        (2Mhz ideal, N/m  *  clkx)

	STM32446PLLDivision(0, 8, 336, 2, 14, 7); // 0,8,360,4,15,6; 0,8,336,2,14,7;
	// Enable PLL
	// STM32446RccPLLCLKEnable(); // Only enable when Division is configured correctly.

	// SysClock prescaler parameters
	// AHB 1,2,4,8,16,64,128,256,512 		APB1 1,2,4,8,16		APB2 1,2,4,8,16
	// RTC 2 to 31

	// STM32446Prescaler(8, 1, 1, 0);
	// STM32446Prescaler(2, 1, 1, 0);
	STM32446Prescaler(1, 1, 1, 0);
	// System Clock Source
	STM32446RccHEnable(0);
	// System Clock Select or Enable
	clkused = STM32446RccHSelect(0); // SW[1:0]: System clock switch 00 - HSI, 01 - HSE pg133
	// Low Speed Internal Clock turned on as default
	// Internal low-speed oscillator enable and Internal low-speed oscillator ready
	STM32446RccLEnable(2);
	// Low speed oscillator select
	STM32446RccLSelect(2);
	return clkused;
}

// RCC
void STM32446RccHEnable(unsigned int hclock)
{
	unsigned int set;
	unsigned int rdy;
	for( set = 1, rdy = 1; rdy ; ){
		if(hclock == 0){ // HSION: Internal high-speed clock enable
			if( set ){ RCC->CR |= ( 1 << 0); set = 0; }else if( RCC->CR & ( 1 << 1) ) rdy = 0;
		}
		else if(hclock == 1){ // HSEON: HSE clock enable
			if( set ){ RCC->CR |= ( 1 << 16); set = 0; }else if( RCC->CR & ( 1 << 17) ) rdy = 0;
		}
		else if(hclock == 2){ // HSEBYP: HSE clock bypass
			if( set ) RCC->CR |= ( 1 << 18 );
			hclock = 1;
		}
		else hclock = 0; // default
	}
}

uint8_t STM32446RccHSelect(uint8_t hclock)
{ // SW[1:0]: System clock switch 00 - HSI, 01 - HSE pg133
	RCC->CFGR &= (unsigned int) ~(3); // 00: HSI oscillator selected as system clock
	switch(hclock){
		case 1:
			RCC->CFGR |= 1; // HSE oscillator selected as system clock
		break;
		case 2:
			RCC->CFGR |= 2; // PLL_P selected as system clock
		break;
		case 3:
			RCC->CFGR |= 3; // PLL_R selected as system clock
		break;
		default:
		break;
	}
	return (RCC->CFGR >> 2) & 3;
}

void STM32446RccLEnable(unsigned int lclock)
{
	unsigned int set;
	unsigned int rdy;
	for( set = 1, rdy = 1; rdy ; ){
		if(lclock == 2){ // LSION: Internal low-speed oscillator enable
			if( set ){ RCC->CSR |= ( 1 << 0); set = 0; }else if( RCC->CSR & ( 1 << 1) ) rdy = 0;
		}
		else if(lclock == 1){ // LSEON: External low-speed oscillator enable
			if( set ){ RCC->BDCR |= ( 1 << 0); set = 0; }else if( RCC->BDCR & ( 1 << 1) ) rdy = 0;
		}
		else if(lclock == 4){ // LSEBYP: External low-speed oscillator bypass
			if( set ) RCC->BDCR |= ( 1 << 2 );
			lclock = 1;
		}
		else lclock = 2; // default
	}
}

void STM32446RccLSelect(uint8_t lclock)
{
	RCC->BDCR &= (uint32_t) ~((1 << 9) | (1 << 8)); // RTCSEL[1:0]: RTC clock source selection
	switch(lclock){
		case 2:
			RCC->BDCR |= (1 << 9); // LSI oscillator clock used as the RTC clock
		break;
		case 1:
			RCC->BDCR |= (1 << 8); // LSE oscillator clock used as the RTC clock
		break;
		case 3:
			RCC->BDCR |= ((1 << 8) | (1 << 9)); // HSE oscillator clock divided by a programmable prescaler
		break;
		default:
			RCC->BDCR |= (1 << 8); // LSE oscillator clock used as the RTC clock
		break;
	}
}

void STM32446RccPLLCLKEnable(void)
{
	//if(onoff){
		for( RCC->CR |= (1 << 24) ; !(RCC->CR & (1 << 25)) ; ); // PLLON: Main PLL (PLL) enable
	//}else{
		//RCC->CR &= (unsigned int) ~(1 << 24);
	//}
}

void STM32446RccPLLI2SEnable(void)
{
	//if(onoff)
		for( RCC->CR |= (1 << 26) ; !(RCC->CR & (1 << 27)) ; ); // PLLI2SON: PLLI2S enable
	//else
		//RCC->CR &= (unsigned int) ~(1 << 26);
}

void STM32446RccPLLSAIEnable(void)
{
	//if(onoff)
		for( RCC->CR |= (1 << 28) ; !(RCC->CR & (1 << 29)) ; ); // PLLSAION: PLLSAI enable
	//else
		//RCC->CR &= (unsigned int) ~(1 << 28);
}

uint32_t rcc_getbit(uint32_t reg, uint32_t size_block, uint32_t bit)
{
	uint32_t value = 0; uint32_t tmp = 0;

	uint32_t mask = (unsigned int)((1 << size_block) - 1);
	mask = (mask << bit);
	tmp = mask & reg;
	value = (tmp >> bit);
	return value;
}

void rcc_setbit(volatile uint32_t* reg, uint32_t size_block, uint32_t bit, uint32_t data)
{
	uint32_t n = 0;
	if(bit > 31){ n = bit/32; bit = bit - (n * 32); }
	uint32_t value = 0;
	uint32_t mask = (unsigned int)((1 << size_block) - 1);
	value = data & mask;
	*(reg + n ) &= ~(mask << bit);
	*(reg + n ) |= (value << bit);
}

uint32_t rcc_getsetbit(volatile uint32_t* reg, uint32_t size_block, uint32_t bit)
{
	uint32_t n = 0;
	if(bit > 31){ n = bit/32; bit = bit - (n * 32); }
	uint32_t value = 0;
	uint32_t mask = (unsigned int)((1 << size_block) - 1);
	value = *(reg + n ) & ~(mask << bit);
	value = (value >> bit);
	return value;
}

/*** EOF ***/

/*
 * Everytime a library header is called, it is a copy.
 *
 *
 */


