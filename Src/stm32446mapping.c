/******************************************************************************
	STM32 446 MAPPING
Author: Sergio Santos 
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
/*** File Library ***/
#include "stm32446mapping.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <math.h>

/*** File Constant & Macros ***/
#define STM32446_SCB_BASE ((0xE000E000UL) + 0x0D00UL))

/*** File Variable ***/
static STM32446 ret;
static volatile uint32_t DelayCounter;
static volatile uint32_t mem[4];
static volatile uint32_t nen[4];

/*** File Header ***/
// SysTick
void SystickInic(void);

// RCC
uint8_t STM32446RccInic(void);
void STM32446RccHEnable(unsigned int hclock);
uint8_t STM32446RccHSelect(uint8_t sysclk);
void STM32446RccLEnable(unsigned int lclock);
void STM32446RccLSelect(uint8_t lclock);
void STM32446Prescaler(unsigned int ahbpre, unsigned int ppre1, unsigned int ppre2, unsigned int rtcpre);
uint32_t SystemClock(void);

// PLL
void STM32446PLLDivision(unsigned int pllsrc, unsigned int pllm, unsigned int plln, unsigned int pllp, unsigned int pllq, unsigned int pllr);
void STM32446RccPLLCLKEnable(void);
void STM32446RccPLLI2SEnable(void);
void STM32446RccPLLSAIEnable(void);

// GPIOA
void STM32446GpioAenable( void );
void STM32446GpioAmoder( unsigned int data, unsigned int pin );
void STM32446GpioAospeedr( unsigned int data, unsigned int pin );
void STM32446GpioApupdr( unsigned int data, unsigned int pin );
void STM32446GpioAreset( unsigned int data );
void STM32446GpioAset( unsigned int data );
void STM32446GpioAafr( unsigned int data, unsigned int pin );

// GPIOB
void STM32446GpioBenable( void );
void STM32446GpioBmoder( unsigned int data, unsigned int pin );
void STM32446GpioBospeedr( unsigned int data, unsigned int pin );
void STM32446GpioBpupdr( unsigned int data, unsigned int pin );
void STM32446GpioBreset( unsigned int data );
void STM32446GpioBset( unsigned int data );
void STM32446GpioBafr( unsigned int data, unsigned int pin );

// GPIOC
void STM32446GpioCenable( void );
void STM32446GpioCmoder( unsigned int data, unsigned int pin );
void STM32446GpioCospeedr( unsigned int data, unsigned int pin );
void STM32446GpioCpupdr( unsigned int data, unsigned int pin );
void STM32446GpioCreset( unsigned int data );
void STM32446GpioCset( unsigned int data );
void STM32446GpioCafr( unsigned int data, unsigned int pin );

// GPIOD
void STM32446GpioDenable( void );
void STM32446GpioDmoder( unsigned int data, unsigned int pin );
void STM32446GpioDospeedr( unsigned int data, unsigned int pin );
void STM32446GpioDpupdr( unsigned int data, unsigned int pin );
void STM32446GpioDreset( unsigned int data );
void STM32446GpioDset( unsigned int data );
void STM32446GpioDafr( unsigned int data, unsigned int pin );

// GPIOE
void STM32446GpioEenable( void );
void STM32446GpioEmoder( unsigned int data, unsigned int pin );
void STM32446GpioEospeedr( unsigned int data, unsigned int pin );
void STM32446GpioEpupdr( unsigned int data, unsigned int pin );
void STM32446GpioEreset( unsigned int data );
void STM32446GpioEset( unsigned int data );
void STM32446GpioEafr( unsigned int data, unsigned int pin );

// GPIOH
void STM32446GpioHenable( void );
void STM32446GpioHmoder( unsigned int data, unsigned int pin );
void STM32446GpioHospeedr( unsigned int data, unsigned int pin );
void STM32446GpioHpupdr( unsigned int data, unsigned int pin );
void STM32446GpioHreset( unsigned int data );
void STM32446GpioHset( unsigned int data );
void STM32446GpioHafr( unsigned int data, unsigned int pin );

// SYSCFG
void STM32446SyscfgEnable(void);

// TIM9
void STM32446Tim9Enable(void);

// MISCELLANEOUS
char STM32446bcd2dec(char num);
char STM32446dec2bcd(char num);
// SYSTICK
void STM32446delay_ms(uint32_t ms);
void STM32446delay_10us(uint32_t ten_us);
void STM32446delay_us(uint32_t us);
// BUTTON
uint32_t STM32446triggerA(uint32_t hllh_io, uint8_t pin, uint32_t counter);
uint32_t STM32446triggerB(uint32_t hl_io, uint32_t lh_io, uint8_t pin, uint32_t counter);
// BYTE
uint16_t STM32ReadHLByte(STM32HighLowByte reg);
uint16_t STM32ReadLHByte(STM32HighLowByte reg);
STM32HighLowByte STM32WriteHLByte(uint16_t val);
STM32HighLowByte STM32WriteLHByte(uint16_t val);
uint16_t STM32SwapByte(uint16_t num);
// GPIO
void STM32446GpioSetpins( GPIO_TypeDef* regs, int n_pin, ... );
void STM32446GpioSetpin( GPIO_TypeDef* regs, int pin );
void STM32446GpioSet( GPIO_TypeDef* regs, int data );
void STM32446GpioResetpins( GPIO_TypeDef* regs, int n_pin, ... );
void STM32446GpioResetpin( GPIO_TypeDef* regs, int pin );
void STM32446GpioReset( GPIO_TypeDef* regs, int data );
void STM32446PinBlock( volatile uint32_t* dest, uint32_t size_block, uint32_t data, uint32_t pin );
// GENERIC
void STM32446Gpiosetupreg(volatile uint32_t* reg, unsigned int size_block, unsigned int data, unsigned int pin);
void STM32446GpioSetup( volatile uint32_t vec[], const unsigned int size_block, unsigned int data, unsigned int block_n );
char* STM32446FUNCftoa(double num, char* res, uint8_t afterpoint);
char* STM32446FUNCprint( char* str, uint8_t size_str, const char* format, ... );

/*** FILE FUNC ***/
// SRAM
void STM32446SramAccess(void);
//COMMON
void STM32446Reverse(char s[]);
int STM32446StringLength (const char string[]);
uint8_t STM32446FUNCintinvstr(int32_t num, char* res, uint8_t n_digit);
// QUERY
uint32_t SystemClock(void);

// Interrupt Prototype
void SysTick_Handler(void);

/**** Procedure & Functions ***/
// STM32446 Image Linker
STM32446 STM32446enable(void){
// Comment out the linked modules to reduce memmory usage.
	mem[0] = 0;
	nen[0] = 0;
	// CORE
	// Coprocessor Access Control Register
	ret.scb.reg = ((SCB_Type*) STM32446_SCB_BASE;

	// STM32446 OBJECTS
	// FLASH
	ret.flash.reg = (FLASH_TypeDef*) FLASH_R_BASE;
	
	// CRC
	ret.crc.reg = (CRC_TypeDef*) CRC_BASE;
	
	// PWR
	ret.pwr.reg = (PWR_TypeDef*) PWR_BASE;
	
	// RCC
	ret.rcc.reg = (RCC_TypeDef*) RCC_BASE;
	ret.rcc.inic = STM32446RccInic;
	ret.rcc.henable = STM32446RccHEnable;
	ret.rcc.hselect = STM32446RccHSelect;
	ret.rcc.lenable = STM32446RccLEnable;
	ret.rcc.lselect = STM32446RccLSelect;
	ret.rcc.prescaler = STM32446Prescaler;
	ret.rcc.systemclock = SystemClock;

	// PLL
	ret.rcc.pll.division = STM32446PLLDivision;
	ret.rcc.pll.enable = STM32446RccPLLCLKEnable;
	ret.rcc.plli2s.enable = STM32446RccPLLI2SEnable;
	ret.rcc.pllsai.enable = STM32446RccPLLSAIEnable;
	
	// GPIOA
	ret.gpioa.reg = (GPIO_TypeDef*) GPIOA_BASE;
	ret.gpioa.enable = STM32446GpioAenable;
	ret.gpioa.moder = STM32446GpioAmoder;
	ret.gpioa.ospeedr = STM32446GpioAospeedr;
	ret.gpioa.pupdr = STM32446GpioApupdr;
	ret.gpioa.reset = STM32446GpioAreset;
	ret.gpioa.set = STM32446GpioAset;
	ret.gpioa.afr = STM32446GpioAafr;
	
	// GPIOB
	ret.gpiob.reg = (GPIO_TypeDef*) GPIOB_BASE;
	ret.gpiob.enable = STM32446GpioBenable;
	ret.gpiob.moder = STM32446GpioBmoder;
	ret.gpiob.ospeedr = STM32446GpioBospeedr;
	ret.gpiob.pupdr = STM32446GpioBpupdr;
	ret.gpiob.reset = STM32446GpioBreset;
	ret.gpiob.set = STM32446GpioBset;
	ret.gpiob.afr = STM32446GpioBafr;
	
	// GPIOC
	ret.gpioc.reg = (GPIO_TypeDef*) GPIOC_BASE;
	ret.gpioc.enable = STM32446GpioCenable;
	ret.gpioc.moder = STM32446GpioCmoder;
	ret.gpioc.ospeedr = STM32446GpioCospeedr;
	ret.gpioc.pupdr = STM32446GpioCpupdr;
	ret.gpioc.reset = STM32446GpioCreset;
	ret.gpioc.set = STM32446GpioCset;
	ret.gpioc.afr = STM32446GpioCafr;
	
	// GPIOD
	ret.gpiod.reg = (GPIO_TypeDef*) GPIOD_BASE;
	ret.gpiod.enable = STM32446GpioDenable;
	ret.gpiod.moder = STM32446GpioDmoder;
	ret.gpiod.ospeedr = STM32446GpioDospeedr;
	ret.gpiod.pupdr = STM32446GpioDpupdr;
	ret.gpiod.reset = STM32446GpioDreset;
	ret.gpiod.set = STM32446GpioDset;
	ret.gpiod.afr = STM32446GpioDafr;

	// GPIOE
	ret.gpioe.reg = (GPIO_TypeDef*) GPIOE_BASE;
	ret.gpioe.enable = STM32446GpioEenable;
	ret.gpioe.moder = STM32446GpioEmoder;
	ret.gpioe.ospeedr = STM32446GpioEospeedr;
	ret.gpioe.pupdr = STM32446GpioEpupdr;
	ret.gpioe.reset = STM32446GpioEreset;
	ret.gpioe.set = STM32446GpioEset;
	ret.gpioe.afr = STM32446GpioEafr;

	// GPIOH
	ret.gpioh.reg = (GPIO_TypeDef*) GPIOH_BASE;
	ret.gpioh.enable = STM32446GpioHenable;
	ret.gpioh.moder = STM32446GpioHmoder;
	ret.gpioh.ospeedr = STM32446GpioHospeedr;
	ret.gpioh.pupdr = STM32446GpioHpupdr;
	ret.gpioh.reset = STM32446GpioHreset;
	ret.gpioh.set = STM32446GpioHset;
	ret.gpioh.afr = STM32446GpioHafr;
	
	// RTC
	ret.rtc.reg = (RTC_TypeDef*) RTC_BASE;
	#if defined(_STM32446RTC_H_)
		ret.rtc.enable = STM32446RTCenable;
	#endif
	
	// SYSCFG
	ret.syscfg.reg = (SYSCFG_TypeDef*) SYSCFG_BASE;
	ret.syscfg.enable = STM32446SyscfgEnable;
	
	// DMA1
	ret.dma1.reg = (DMA_TypeDef*) DMA1_BASE;
	ret.dma1.stream[0].reg = (DMA_Stream_TypeDef*) DMA1_Stream0_BASE;

	// DMA2
	ret.dma2.reg = (DMA_TypeDef*) DMA2_BASE;
	ret.dma2.stream[0].reg = (DMA_Stream_TypeDef*) DMA2_Stream0_BASE;
	
	// NVIC
	ret.nvic.reg = (NVIC_Type*) NVIC_BASE;
	
	// SysTick (Used as Delay Source)
	ret.systick.reg = (SysTick_Type*) SysTick_BASE;
	ret.systick.delay_ms = STM32446delay_ms;
	ret.systick.delay_10us = STM32446delay_10us;
	ret.systick.delay_us = STM32446delay_us;
	
	// random order
	
	// ADC1
	ret.adc1.reg = (ADC_TypeDef*) ADC1_BASE;
	ret.adc1.common.reg = (ADC_Common_TypeDef*) ADC123_COMMON_BASE;
	#if defined(_STM32446ADC_H_)
		ret.adc1.enable = STM32446ADC1enable;
	#endif
	
	// TIM9
	ret.tim9.reg = (TIM_TypeDef*) TIM9_BASE;
	ret.tim9.enable = STM32446Tim9Enable;

	// USART1
	ret.usart1.reg = (USART_TypeDef*) USART1_BASE;
	#if defined(_STM32446USART_H_)
		ret.usart1.enable = STM32446USART1enable;
	#endif
	
	// INIC
	
	// ENABLE

	// QUERY
	ret.query.SystemClock = SystemClock;

	// FUNC
	ret.func.bcd2dec = STM32446bcd2dec;
	ret.func.dec2bcd = STM32446dec2bcd;
	ret.func.triggerA = STM32446triggerA;
	ret.func.triggerB = STM32446triggerB;
	ret.func.ReadHLByte = STM32ReadHLByte;
	ret.func.ReadLHByte = STM32ReadLHByte;
	ret.func.WriteHLByte = STM32WriteHLByte;
	ret.func.WriteLHByte = STM32WriteLHByte;
	ret.func.SwapByte = STM32SwapByte;
	ret.func.setpins = STM32446GpioSetpins;
	ret.func.setpin = STM32446GpioSetpin;
	ret.func.set = STM32446GpioSet;
	ret.func.resetpins = STM32446GpioResetpins;
	ret.func.resetpin = STM32446GpioResetpin;
	ret.func.reset = STM32446GpioReset;
	ret.func.setupreg = STM32446Gpiosetupreg;
	ret.func.pinblock = STM32446PinBlock;
	ret.func.setup = STM32446GpioSetup;
	ret.func.ftoa = STM32446FUNCftoa;
	ret.func.print = STM32446FUNCprint;
	
	SystickInic(); // Polling delay source.
	
	return ret;
}

// RCC
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
			if( set ){ ret.rcc.reg->CR |= ( 1 << 0); set = 0; }else if( ret.rcc.reg->CR & ( 1 << 1) ) rdy = 0;
		}
		else if(hclock == 1){ // HSEON: HSE clock enable
			if( set ){ ret.rcc.reg->CR |= ( 1 << 16); set = 0; }else if( ret.rcc.reg->CR & ( 1 << 17) ) rdy = 0;
		}
		else if(hclock == 2){ // HSEBYP: HSE clock bypass
			if( set ) ret.rcc.reg->CR |= ( 1 << 18 );
			hclock = 1;
		}
		else hclock = 0; // default
	}
}

uint8_t STM32446RccHSelect(uint8_t sysclk)
{
	ret.rcc.reg->CFGR &= (unsigned int) ~(3); // 00: HSI oscillator selected as system clock
	switch(sysclk){
		case 1:
			ret.rcc.reg->CFGR |= 1; // HSE oscillator selected as system clock
		break;
		case 2:
			ret.rcc.reg->CFGR |= 2; // PLL_P selected as system clock
		break;
		case 3:
			ret.rcc.reg->CFGR |= 3; // PLL_R selected as system clock
		break;
		default:
		break;
	}
	return (ret.rcc.reg->CFGR >> 2) & 3;
}

void STM32446RccLEnable(unsigned int lclock)
{
	unsigned int set;
	unsigned int rdy;
	for( set = 1, rdy = 1; rdy ; ){
		if(lclock == 2){ // LSION: Internal low-speed oscillator enable
			if( set ){ ret.rcc.reg->CSR |= ( 1 << 0); set = 0; }else if( ret.rcc.reg->CSR & ( 1 << 1) ) rdy = 0;
		}
		else if(lclock == 1){ // LSEON: External low-speed oscillator enable
			if( set ){ ret.rcc.reg->BDCR |= ( 1 << 0); set = 0; }else if( ret.rcc.reg->BDCR & ( 1 << 1) ) rdy = 0;
		}
		else if(lclock == 4){ // LSEBYP: External low-speed oscillator bypass
			if( set ) ret.rcc.reg->BDCR |= ( 1 << 2 );
			lclock = 1;
		}
		else lclock = 2; // default
	}
}

void STM32446RccLSelect(uint8_t lclock)
{
	ret.rcc.reg->BDCR &= (uint32_t) ~((1 << 9) | (1 << 8)); // RTCSEL[1:0]: RTC clock source selection
	switch(lclock){
		case 2:
			ret.rcc.reg->BDCR |= (1 << 9); // LSI oscillator clock used as the RTC clock
		break;
		case 1:
			ret.rcc.reg->BDCR |= (1 << 8); // LSE oscillator clock used as the RTC clock
		break;
		case 3:
			ret.rcc.reg->BDCR |= ((1 << 8) | (1 << 9)); // HSE oscillator clock divided by a programmable prescaler
		break;
		default:
			ret.rcc.reg->BDCR |= (1 << 8); // LSE oscillator clock used as the RTC clock
		break;
	}
}

void STM32446Prescaler(unsigned int ahbpre, unsigned int ppre1, unsigned int ppre2, unsigned int rtcpre)
{
	const unsigned int mask = 0x001FFCF0;
	ret.rcc.reg->CFGR &= (unsigned int) ~mask; // clear args

	if(rtcpre > 1 && rtcpre < 32) // 16
		ret.rcc.reg->CFGR |= (rtcpre << 16);

	switch(ppre2){ // 13
		case 2:
			ret.rcc.reg->CFGR |= (4 << 13);
			ret.CLOCK_prescaler.APB2 = 2;
		break;
		case 4:
			ret.rcc.reg->CFGR |= (5 << 13);
			ret.CLOCK_prescaler.APB2 = 4;
		break;
		case 8:
			ret.rcc.reg->CFGR |= (6 << 13);
			ret.CLOCK_prescaler.APB2 = 8;
		break;
		case 16:
			ret.rcc.reg->CFGR |= (7 << 13);
			ret.CLOCK_prescaler.APB2 = 16;
		break;
		default:
			ret.CLOCK_prescaler.APB2 = 1;
		break;
	}

	switch(ppre1){ // 10
	case 2:
		ret.rcc.reg->CFGR |= (4 << 10);
		ret.CLOCK_prescaler.APB1 = 2;
	break;
	case 4:
		ret.rcc.reg->CFGR |= (5 << 10);
		ret.CLOCK_prescaler.APB1 = 4;
	break;
	case 8:
		ret.rcc.reg->CFGR |= (6 << 10);
		ret.CLOCK_prescaler.APB1 = 8;
	break;
	case 16:
		ret.rcc.reg->CFGR |= (7 << 10);
		ret.CLOCK_prescaler.APB1 = 16;
	break;
	default:
		ret.CLOCK_prescaler.APB1 = 1;
	break;
	}

	switch(ahbpre){ // 4
	case 2:
		ret.rcc.reg->CFGR |= (8 << 4);
		ret.CLOCK_prescaler.AHB = 2;
	break;
	case 4:
		ret.rcc.reg->CFGR |= (9 << 4);
		ret.CLOCK_prescaler.AHB = 4;
	break;
	case 8:
		ret.rcc.reg->CFGR |= (10 << 4);
		ret.CLOCK_prescaler.AHB = 8;
	break;
	case 16:
		ret.rcc.reg->CFGR |= (11 << 4);
		ret.CLOCK_prescaler.AHB = 16;
	break;
	case 64:
		ret.rcc.reg->CFGR |= (12 << 4);
		ret.CLOCK_prescaler.AHB = 64;
	break;
	case 128:
		ret.rcc.reg->CFGR |= (13 << 4);
		ret.CLOCK_prescaler.AHB = 128;
	break;
	case 256:
		ret.rcc.reg->CFGR |= (14 << 4);
		ret.CLOCK_prescaler.AHB = 256;
	break;
	case 512:
		ret.rcc.reg->CFGR |= (15 << 4);
		ret.CLOCK_prescaler.AHB = 512;
	break;
	default:
		ret.CLOCK_prescaler.AHB = 1;
	break;
	}
}

// PLL
void STM32446PLLDivision(unsigned int pllsrc, unsigned int pllm, unsigned int plln, unsigned int pllp, unsigned int pllq, unsigned int pllr)
{
	const unsigned int mask = 0x7F437FFF;
	ret.rcc.reg->PLLCFGR &= (unsigned int) ~mask; // set mask bits LOW


	if(pllr > 1 && pllr < 8){ // PLLR[28]: Main PLL division factor for I2Ss, SAIs, SYSTEM and SPDIF-Rx clocks
		ret.rcc.reg->PLLCFGR |= (pllr << 28);
		ret.PLL_parameter.R = pllr;
	}

	if(pllq > 1 && pllq < 16){ // PLLQ[24]: Main PLL (PLL) division factor for USB OTG FS, SDIOclocks
		ret.rcc.reg->PLLCFGR |= (pllq << 24);
		ret.PLL_parameter.Q = pllq;
	}

	if(pllsrc == 1){ // PLLSRC[22]: Main PLL(PLL) and audio PLL (PLLI2S) entry clock source
		ret.PLL_parameter.Source = 25000000;
		ret.rcc.reg->PLLCFGR |= (1 << 22);
	}else{
		ret.PLL_parameter.Source = 16000000;
	}

	switch(pllp){ // PLLP[16]: Main PLL (PLL) division factor for main system clock
		case 2:
			ret.PLL_parameter.P = pllp;
		break;
		case 4:
			ret.rcc.reg->PLLCFGR |= (1 << 16);
			ret.PLL_parameter.P = pllp;
		break;
		case 6:
			ret.rcc.reg->PLLCFGR |= (2 << 16);
			ret.PLL_parameter.P = pllp;
		break;
		case 8:
			ret.rcc.reg->PLLCFGR |= (3 << 16);
			ret.PLL_parameter.P = pllp;
		break;
		default:
			ret.rcc.reg->PLLCFGR |= (1 << 16);
			ret.PLL_parameter.P = 4;
		break;
	}

	if(plln > 49 && plln < 433){ // PLLN[6]: Main PLL (PLL) multiplication factor for VCO
		ret.rcc.reg->PLLCFGR |= (plln << 6);
		ret.PLL_parameter.N = plln;
	}

	if(pllm > 1 && pllm < 64){ // PLLM[0]: Division factor for the main PLL (PLL) input clock [2Mhz]
		ret.rcc.reg->PLLCFGR |= pllm;
		ret.PLL_parameter.M = pllm;
	}
}

void STM32446RccPLLCLKEnable(void)
{
	//if(onoff){
		for( ret.rcc.reg->CR |= (1 << 24) ; !(ret.rcc.reg->CR & (1 << 25)) ; ); // PLLON: Main PLL (PLL) enable
	//}else{
		//ret.rcc.reg->CR &= (unsigned int) ~(1 << 24);
	//}
}

void STM32446RccPLLI2SEnable(void)
{
	//if(onoff)
		for( ret.rcc.reg->CR |= (1 << 26) ; !(ret.rcc.reg->CR & (1 << 27)) ; ); // PLLI2SON: PLLI2S enable
	//else
		//ret.rcc.reg->CR &= (unsigned int) ~(1 << 26);
}

void STM32446RccPLLSAIEnable(void)
{
	//if(onoff)
		for( ret.rcc.reg->CR |= (1 << 28) ; !(ret.rcc.reg->CR & (1 << 29)) ; ); // PLLSAION: PLLSAI enable
	//else
		//ret.rcc.reg->CR &= (unsigned int) ~(1 << 28);
}

uint32_t SystemClock(void) // Query
{
	uint32_t sysclk;
	switch((ret.rcc.reg->CFGR >> 2) & 3) // SWS[2]: System clock switch status
	{
		case 0: // 00: HSI oscillator used as the system clock
			ret.PLL_parameter.Source = 16000000;
			sysclk= 16000000;
		break;
		case 1: // 01: HSE oscillator used as the system clock
			ret.PLL_parameter.Source = 25000000;
			sysclk = 25000000;
		break;
		case 2: // 10: PLL used as the system clock
			sysclk = ( ret.PLL_parameter.Source / ret.PLL_parameter.M ) * ( ret.PLL_parameter.N / ret.PLL_parameter.P );
		break;
		case 3: // 11: PLL_R used as the system clock
			sysclk = ( ret.PLL_parameter.Source / ret.PLL_parameter.M ) * ( ret.PLL_parameter.N / ret.PLL_parameter.R );
		break;
		default:
			sysclk= 16000000;
		break;
	}
	return sysclk;
}

// GPIO
// To much resources
void STM32446GpioSetpins( GPIO_TypeDef* regs, int n_pin, ... )
{
	uint8_t i;

	if(n_pin > 0 && n_pin < 33){ // Filter input
		va_list list;
		va_start(list, n_pin);
		for(i = 0; i < n_pin; i++){
			regs->BSRR = (1 << va_arg(list, int));
		}
		va_end(list);
	}
}
// disabled

void STM32446GpioSetpin( GPIO_TypeDef* regs, int pin )
{
	regs->BSRR = (1 << pin);
}

void STM32446GpioSet( GPIO_TypeDef* regs, int data )
{
	regs->BSRR = (unsigned int) data;
}

// To much resources
void STM32446GpioResetpins( GPIO_TypeDef* regs, int n_pin, ... )
{ // slow
	uint8_t i;
	
	if(n_pin > 0 && n_pin < 33){ // Filter input
		va_list list;
		va_start(list, n_pin);
		for(i = 0; i < n_pin; i++){
			regs->BSRR = (unsigned int)((1 << va_arg(list, int)) << 16);
		}
		va_end(list);
	}
}
// disabled

void STM32446GpioResetpin( GPIO_TypeDef* regs, int pin )
{
	regs->BSRR = (unsigned int)((1 << pin) << 16);
}

void STM32446GpioReset( GPIO_TypeDef* regs, int data )
{
	regs->BSRR = (unsigned int)(data << 16);
}

// generic
void STM32446Gpiosetupreg( volatile uint32_t* reg, unsigned int size_block, unsigned int data, unsigned int pin )
{
	unsigned int mask = (unsigned int)(pow(2, size_block) - 1);
	unsigned int location = pin * size_block;
	data &= mask;
	*reg &= ~(mask << location);
	*reg |= (data << location);
}

/*** Version 2
void STM32446Gpiosetupreg( volatile uint32_t* reg, uint32_t size_block, uint32_t data, uint32_t pin )
{
	uint32_t mask = (uint32_t)(pow(2, size_block) - 1);
	uint32_t location = pin * size_block;
	data &= mask;
	*reg |= (mask << location);
	*reg &= (data << location) | ~(mask << location);
}
***/

void STM32446GpioSetup( volatile uint32_t vec[], const unsigned int size_block, unsigned int data, unsigned int block_n )
{
	const unsigned int n_bits = sizeof(data) * 8;
	const unsigned int mask = (unsigned int) (pow(2, size_block) - 1);
	unsigned int index = (block_n * size_block) / n_bits;
	data &= mask;
	vec[index] &= ~( mask << ((block_n * size_block) - (index * n_bits)) );
	vec[index] |= ( data << ((block_n * size_block) - (index * n_bits)) );
}

void STM32446PinBlock( volatile uint32_t* dest, uint32_t size_block, uint32_t data, uint32_t pin )
{
	uint32_t mask = (uint32_t)(pow(2, size_block) - 1);
	data &= mask;
	*dest &= ~(mask << pin);
	*dest |= (data << pin);
}

// GPIOA
void STM32446GpioAenable( void )
{
	ret.rcc.reg->AHB1ENR |= (1 << 0);
}

void STM32446GpioAmoder( unsigned int data, unsigned int pin )
{
	const unsigned int blocksize = 2;
	unsigned int mask = (unsigned int)(pow(2, blocksize) - 1);
	data &= mask;
	ret.gpioa.reg->MODER &= ~(mask << (pin * blocksize));
	ret.gpioa.reg->MODER |= (data << (pin * blocksize));
}

void STM32446GpioAospeedr( unsigned int data, unsigned int pin )
{
	const unsigned int blocksize = 2;
	unsigned int mask = (unsigned int)(pow(2, blocksize) - 1);
	data &= mask;
	ret.gpioa.reg->OSPEEDR &= ~(mask << (pin * blocksize));
	ret.gpioa.reg->OSPEEDR |= (data << (pin * blocksize));
}

void STM32446GpioApupdr( unsigned int data, unsigned int pin )
{
	const unsigned int blocksize = 2;
	unsigned int mask = (unsigned int)(pow(2, blocksize) - 1);
	data &= mask;
	ret.gpioa.reg->PUPDR &= ~(mask << (pin * blocksize));
	ret.gpioa.reg->PUPDR |= (data << (pin * blocksize));
}

void STM32446GpioAreset( unsigned int data )
{
	ret.gpioa.reg->BSRR = (unsigned int)(data << 16);
}

void STM32446GpioAset( unsigned int data )
{
	ret.gpioa.reg->BSRR = (unsigned int)( data );
}

void STM32446GpioAafr( unsigned int data, unsigned int pin )
{
	const unsigned int blocksize = 4;
	const unsigned int n_bits = sizeof(unsigned int) * 8;
	const unsigned int mask = (unsigned int) (pow(2, blocksize) - 1);
	unsigned int index = (pin * blocksize) / n_bits;
	data &= mask;
	if(index < 2){
		ret.gpioa.reg->AFR[index] &= ~( mask << ((pin * blocksize) - (index * n_bits)) );
		ret.gpioa.reg->AFR[index] |= ( data << ((pin * blocksize) - (index * n_bits)) );
	}
}

// GPIOB
void STM32446GpioBenable( void )
{
	ret.rcc.reg->AHB1ENR |= (1 << 1);
}

void STM32446GpioBmoder( unsigned int data, unsigned int pin )
{
	const unsigned int blocksize = 2;
	unsigned int mask = (unsigned int)(pow(2, blocksize) - 1);
	data &= mask;
	ret.gpiob.reg->MODER &= ~(mask << (pin * blocksize));
	ret.gpiob.reg->MODER |= (data << (pin * blocksize));
}

void STM32446GpioBospeedr( unsigned int data, unsigned int pin )
{
	const unsigned int blocksize = 2;
	unsigned int mask = (unsigned int)(pow(2, blocksize) - 1);
	data &= mask;
	ret.gpiob.reg->OSPEEDR &= ~(mask << (pin * blocksize));
	ret.gpiob.reg->OSPEEDR |= (data << (pin * blocksize));
}

void STM32446GpioBpupdr( unsigned int data, unsigned int pin )
{
	const unsigned int blocksize = 2;
	unsigned int mask = (unsigned int)(pow(2, blocksize) - 1);
	data &= mask;
	ret.gpiob.reg->PUPDR &= ~(mask << (pin * blocksize));
	ret.gpiob.reg->PUPDR |= (data << (pin * blocksize));
}

void STM32446GpioBreset( unsigned int data )
{
	ret.gpiob.reg->BSRR = (unsigned int)(data << 16);
}

void STM32446GpioBset( unsigned int data )
{
	ret.gpiob.reg->BSRR = (unsigned int)( data );
}

void STM32446GpioBafr( unsigned int data, unsigned int pin )
{
	const unsigned int blocksize = 4;
	const unsigned int n_bits = sizeof(unsigned int) * 8;
	const unsigned int mask = (unsigned int) (pow(2, blocksize) - 1);
	unsigned int index = (pin * blocksize) / n_bits;
	data &= mask;
	if(index < 2){
		ret.gpiob.reg->AFR[index] &= ~( mask << ((pin * blocksize) - (index * n_bits)) );
		ret.gpiob.reg->AFR[index] |= ( data << ((pin * blocksize) - (index * n_bits)) );
	}
}

// GPIOC
void STM32446GpioCenable( void )
{
	ret.rcc.reg->AHB1ENR |= (1 << 2);
}

void STM32446GpioCmoder( unsigned int data, unsigned int pin )
{
	const unsigned int blocksize = 2;
	unsigned int mask = (unsigned int)(pow(2, blocksize) - 1);
	data &= mask;
	ret.gpioc.reg->MODER &= ~(mask << (pin * blocksize));
	ret.gpioc.reg->MODER |= (data << (pin * blocksize));
}

void STM32446GpioCospeedr( unsigned int data, unsigned int pin )
{
	const unsigned int blocksize = 2;
	unsigned int mask = (unsigned int)(pow(2, blocksize) - 1);
	data &= mask;
	ret.gpioc.reg->OSPEEDR &= ~(mask << (pin * blocksize));
	ret.gpioc.reg->OSPEEDR |= (data << (pin * blocksize));
}

void STM32446GpioCpupdr( unsigned int data, unsigned int pin )
{
	const unsigned int blocksize = 2;
	unsigned int mask = (unsigned int)(pow(2, blocksize) - 1);
	data &= mask;
	ret.gpioc.reg->PUPDR &= ~(mask << (pin * blocksize));
	ret.gpioc.reg->PUPDR |= (data << (pin * blocksize));
}

void STM32446GpioCreset( unsigned int data )
{
	ret.gpioc.reg->BSRR = (unsigned int)(data << 16);
}

void STM32446GpioCset( unsigned int data )
{
	ret.gpioc.reg->BSRR = (unsigned int)( data );
}

void STM32446GpioCafr( unsigned int data, unsigned int pin )
{
	const unsigned int blocksize = 4;
	const unsigned int n_bits = sizeof(unsigned int) * 8;
	const unsigned int mask = (unsigned int) (pow(2, blocksize) - 1);
	unsigned int index = (pin * blocksize) / n_bits;
	data &= mask;
	if(index < 2){
		ret.gpioc.reg->AFR[index] &= ~( mask << ((pin * blocksize) - (index * n_bits)) );
		ret.gpioc.reg->AFR[index] |= ( data << ((pin * blocksize) - (index * n_bits)) );
	}
}

// GPIOD
void STM32446GpioDenable( void )
{
	ret.rcc.reg->AHB1ENR |= (1 << 3);
}

void STM32446GpioDmoder( unsigned int data, unsigned int pin )
{
	const unsigned int blocksize = 2;
	unsigned int mask = (unsigned int)(pow(2, blocksize) - 1);
	data &= mask;
	ret.gpiod.reg->MODER &= ~(mask << (pin * blocksize));
	ret.gpiod.reg->MODER |= (data << (pin * blocksize));
}

void STM32446GpioDospeedr( unsigned int data, unsigned int pin )
{
	const unsigned int blocksize = 2;
	unsigned int mask = (unsigned int)(pow(2, blocksize) - 1);
	data &= mask;
	ret.gpiod.reg->OSPEEDR &= ~(mask << (pin * blocksize));
	ret.gpiod.reg->OSPEEDR |= (data << (pin * blocksize));
}

void STM32446GpioDpupdr( unsigned int data, unsigned int pin )
{
	const unsigned int blocksize = 2;
	unsigned int mask = (unsigned int)(pow(2, blocksize) - 1);
	data &= mask;
	ret.gpiod.reg->PUPDR &= ~(mask << (pin * blocksize));
	ret.gpiod.reg->PUPDR |= (data << (pin * blocksize));
}

void STM32446GpioDreset( unsigned int data )
{
	ret.gpiod.reg->BSRR = (unsigned int)(data << 16);
}

void STM32446GpioDset( unsigned int data )
{
	ret.gpiod.reg->BSRR = (unsigned int)( data );
}

void STM32446GpioDafr( unsigned int data, unsigned int pin )
{
	const unsigned int blocksize = 4;
	const unsigned int n_bits = sizeof(unsigned int) * 8;
	const unsigned int mask = (unsigned int) (pow(2, blocksize) - 1);
	unsigned int index = (pin * blocksize) / n_bits;
	data &= mask;
	if(index < 2){
		ret.gpiod.reg->AFR[index] &= ~( mask << ((pin * blocksize) - (index * n_bits)) );
		ret.gpiod.reg->AFR[index] |= ( data << ((pin * blocksize) - (index * n_bits)) );
	}
}

// GPIOE
void STM32446GpioEenable( void )
{
	ret.rcc.reg->AHB1ENR |= (1 << 4);
}

void STM32446GpioEmoder( unsigned int data, unsigned int pin )
{
	const unsigned int blocksize = 2;
	unsigned int mask = (unsigned int)(pow(2, blocksize) - 1);
	data &= mask;
	ret.gpioe.reg->MODER &= ~(mask << (pin * blocksize));
	ret.gpioe.reg->MODER |= (data << (pin * blocksize));
}

void STM32446GpioEospeedr( unsigned int data, unsigned int pin )
{
	const unsigned int blocksize = 2;
	unsigned int mask = (unsigned int)(pow(2, blocksize) - 1);
	data &= mask;
	ret.gpioe.reg->OSPEEDR &= ~(mask << (pin * blocksize));
	ret.gpioe.reg->OSPEEDR |= (data << (pin * blocksize));
}

void STM32446GpioEpupdr( unsigned int data, unsigned int pin )
{
	const unsigned int blocksize = 2;
	unsigned int mask = (unsigned int)(pow(2, blocksize) - 1);
	data &= mask;
	ret.gpioe.reg->PUPDR &= ~(mask << (pin * blocksize));
	ret.gpioe.reg->PUPDR |= (data << (pin * blocksize));
}

void STM32446GpioEreset( unsigned int data )
{
	ret.gpioe.reg->BSRR = (unsigned int)(data << 16);
}

void STM32446GpioEset( unsigned int data )
{
	ret.gpioe.reg->BSRR = (unsigned int)( data );
}

void STM32446GpioEafr( unsigned int data, unsigned int pin )
{
	const unsigned int blocksize = 4;
	const unsigned int n_bits = sizeof(unsigned int) * 8;
	const unsigned int mask = (unsigned int) (pow(2, blocksize) - 1);
	unsigned int index = (pin * blocksize) / n_bits;
	data &= mask;
	if(index < 2){
		ret.gpioe.reg->AFR[index] &= ~( mask << ((pin * blocksize) - (index * n_bits)) );
		ret.gpioe.reg->AFR[index] |= ( data << ((pin * blocksize) - (index * n_bits)) );
	}
}

// GPIOH
void STM32446GpioHenable( void )
{
	ret.rcc.reg->AHB1ENR |= (1 << 7);
}

void STM32446GpioHmoder( unsigned int data, unsigned int pin )
{
	const unsigned int blocksize = 2;
	unsigned int mask = (unsigned int)(pow(2, blocksize) - 1);
	data &= mask;
	ret.gpioh.reg->MODER &= ~(mask << (pin * blocksize));
	ret.gpioh.reg->MODER |= (data << (pin * blocksize));
}

void STM32446GpioHospeedr( unsigned int data, unsigned int pin )
{
	const unsigned int blocksize = 2;
	unsigned int mask = (unsigned int)(pow(2, blocksize) - 1);
	data &= mask;
	ret.gpioh.reg->OSPEEDR &= ~(mask << (pin * blocksize));
	ret.gpioh.reg->OSPEEDR |= (data << (pin * blocksize));
}

void STM32446GpioHpupdr( unsigned int data, unsigned int pin )
{
	const unsigned int blocksize = 2;
	unsigned int mask = (unsigned int)(pow(2, blocksize) - 1);
	data &= mask;
	ret.gpioh.reg->PUPDR &= ~(mask << (pin * blocksize));
	ret.gpioh.reg->PUPDR |= (data << (pin * blocksize));
}

void STM32446GpioHreset( unsigned int data )
{
	ret.gpioh.reg->BSRR = (unsigned int)(data << 16);
}

void STM32446GpioHset( unsigned int data )
{
	ret.gpioh.reg->BSRR = (unsigned int)( data );
}

void STM32446GpioHafr( unsigned int data, unsigned int pin )
{
	const unsigned int blocksize = 4;
	const unsigned int n_bits = sizeof(unsigned int) * 8;
	const unsigned int mask = (unsigned int) (pow(2, blocksize) - 1);
	unsigned int index = (pin * blocksize) / n_bits;
	data &= mask;
	if(index < 2){
		ret.gpioh.reg->AFR[index] &= ~( mask << ((pin * blocksize) - (index * n_bits)) );
		ret.gpioh.reg->AFR[index] |= ( data << ((pin * blocksize) - (index * n_bits)) );
	}
}

// SYSCFG
void STM32446SyscfgEnable(void)
{
	ret.rcc.reg->APB2ENR |= (1 << 14); //syscfg clock enable
}

// TIM9
void STM32446Tim9Enable(void)
{
	ret.rcc.reg->APB2ENR |= (1 << 16); //timer 9 clock enabled
}

//MISCELLANEOUS
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
	
	switch(nen[0]){
		case 0:
			if(hl_io & (1 << pin)){
				nen[1] = counter;
				nen[0] = 1;
			}
		break;
		case 1:
			if(lh_io & (1 << pin)){
				nen[2] = counter;
				if((nen[2] + 1) > nen[1]){
					nen[3] = nen[2] - nen[1];
				}else{
					nen[3] = ((uint32_t) ~0 - nen[1]) + nen[2];
				}
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

// FILE FUNC
// SRAM
void STM32446SramAccess(void)
{
	// RM0390 pg 94
	// SRAM access
	// 0 - Power Up SRAM
	ret.pwr.reg->CSR |= (1 << 9); // BRE: Backup regulator enable
	// Check ready flag Bit 3 BRR: Backup regulator ready
	for( ; !(ret.pwr.reg->CSR & (1 << 3) )  ; ); // BRR: Backup regulator ready
	
	// 1 - Enable the power interface clock by setting the PWREN bits in the RCC_APB1ENR
	ret.rcc.reg->APB1ENR |= (1 << 28); // Power interface clock enable
	//RCC->APB1ENR |= ((1 << 11) | (1 << 28));

	// 2 - Set the DBP bit in the PWR power control register (PWR_CR)
	ret.pwr.reg->CR |= (1 << 8); // Disable backup domain write protection

	// 3 - Enable the backup SRAM clock by setting BKPSRAMEN bit in the RCC_AHB1ENR
	ret.rcc.reg->AHB1ENR |= (1 << 18); // BKPSRAMEN: Backup SRAM interface clock enable
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

// SYSTICK
void SystickInic(void)
{
	ret.systick.reg->LOAD = (uint32_t)(SystemClock() - 1);
	ret.systick.reg->VAL = 0UL;
	ret.systick.reg->CTRL |= ((1 << 1) | (1 << 2));
}

void STM32446delay_ms(uint32_t ms)
{
	ret.systick.reg->LOAD = (uint32_t)((SystemClock() / 1000) - 1);
	// Enable the SysTick timer
	ret.systick.reg->CTRL |= (1 << 0);
	// Wait for a specified number of milliseconds
	DelayCounter = 0;
	while (DelayCounter < ms);
	// Disable the SysTick timer
	ret.systick.reg->CTRL &= (uint32_t) ~(1 << 0);
}

void STM32446delay_10us(uint32_t ten_us)
{
	ret.systick.reg->LOAD = (uint32_t)((SystemClock() / 100000) - 1);
	// Enable the SysTick timer
	ret.systick.reg->CTRL |= (1 << 0);
	// Wait for a specified number of milliseconds
	DelayCounter = 0;
	while (DelayCounter < ten_us);
	// Disable the SysTick timer
	ret.systick.reg->CTRL &= (uint32_t) ~(1 << 0);
}

void STM32446delay_us(uint32_t us)
{
	ret.systick.reg->LOAD = (uint32_t)((SystemClock() / 1000000) - 1);
	// Enable the SysTick timer
	ret.systick.reg->CTRL |= (1 << 0);
	// Wait for a specified number of milliseconds
	DelayCounter = 0;
	while (DelayCounter < us);
	// Disable the SysTick timer
	ret.systick.reg->CTRL &= (uint32_t) ~(1 << 0);
}

/*** File Interrupt ***/
void SysTick_Handler(void)
{ // count down to zero systick interrupt and reload.
	DelayCounter++;
}

/***EOF***/

/***
 *
 * Start separating modules into libraries to be appended, instead of clustered here.
 *
 *
 * */