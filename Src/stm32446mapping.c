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
// CORE
#define STM32446_SCB_BASE ((0xE000E000UL) + 0x0D00UL))

/*** File Variable ***/
static STM32446 stm32446;

uint32_t DelayCounter;
uint32_t mem[4];
uint32_t nen[4];

/*** File Header ***/
// CORE
// SYSTICK
void SystickInic(void);
void STM32446delay_ms(uint32_t ms);
void STM32446delay_10us(uint32_t ten_us);
void STM32446delay_us(uint32_t us);

// MCU
// GPIO
void STM32446GpioSetpins( GPIO_TypeDef* regs, int n_pin, ... );
void STM32446GpioSetpin( GPIO_TypeDef* regs, int pin );
void STM32446GpioSet( GPIO_TypeDef* regs, int data );
void STM32446GpioResetpins( GPIO_TypeDef* regs, int n_pin, ... );
void STM32446GpioResetpin( GPIO_TypeDef* regs, int pin );
void STM32446GpioReset( GPIO_TypeDef* regs, int data );
void STM32446PinBlock( volatile uint32_t* dest, uint32_t size_block, uint32_t data, uint32_t pin );

// GPIO -> GPIOA
void STM32446GpioAenable( void );
void STM32446GpioAmoder( unsigned int data, unsigned int pin );
void STM32446GpioAospeedr( unsigned int data, unsigned int pin );
void STM32446GpioApupdr( unsigned int data, unsigned int pin );
void STM32446GpioAreset( unsigned int data );
void STM32446GpioAset( unsigned int data );
void STM32446GpioAafr( unsigned int data, unsigned int pin );

// GPIO -> GPIOB
void STM32446GpioBenable( void );
void STM32446GpioBmoder( unsigned int data, unsigned int pin );
void STM32446GpioBospeedr( unsigned int data, unsigned int pin );
void STM32446GpioBpupdr( unsigned int data, unsigned int pin );
void STM32446GpioBreset( unsigned int data );
void STM32446GpioBset( unsigned int data );
void STM32446GpioBafr( unsigned int data, unsigned int pin );

// GPIO -> GPIOC
void STM32446GpioCenable( void );
void STM32446GpioCmoder( unsigned int data, unsigned int pin );
void STM32446GpioCospeedr( unsigned int data, unsigned int pin );
void STM32446GpioCpupdr( unsigned int data, unsigned int pin );
void STM32446GpioCreset( unsigned int data );
void STM32446GpioCset( unsigned int data );
void STM32446GpioCafr( unsigned int data, unsigned int pin );

// GPIO -> GPIOD
void STM32446GpioDenable( void );
void STM32446GpioDmoder( unsigned int data, unsigned int pin );
void STM32446GpioDospeedr( unsigned int data, unsigned int pin );
void STM32446GpioDpupdr( unsigned int data, unsigned int pin );
void STM32446GpioDreset( unsigned int data );
void STM32446GpioDset( unsigned int data );
void STM32446GpioDafr( unsigned int data, unsigned int pin );

// GPIO -> GPIOE
void STM32446GpioEenable( void );
void STM32446GpioEmoder( unsigned int data, unsigned int pin );
void STM32446GpioEospeedr( unsigned int data, unsigned int pin );
void STM32446GpioEpupdr( unsigned int data, unsigned int pin );
void STM32446GpioEreset( unsigned int data );
void STM32446GpioEset( unsigned int data );
void STM32446GpioEafr( unsigned int data, unsigned int pin );

// GPIO -> GPIOH
void STM32446GpioHenable( void );
void STM32446GpioHmoder( unsigned int data, unsigned int pin );
void STM32446GpioHospeedr( unsigned int data, unsigned int pin );
void STM32446GpioHpupdr( unsigned int data, unsigned int pin );
void STM32446GpioHreset( unsigned int data );
void STM32446GpioHset( unsigned int data );
void STM32446GpioHafr( unsigned int data, unsigned int pin );

// SYSCFG
void STM32446SysCfgEnable(void);

// PLL
void STM32446PLLDivision(unsigned int pllsrc, unsigned int pllm, unsigned int plln, unsigned int pllp, unsigned int pllq, unsigned int pllr);
void STM32446RccPLLCLKEnable(void);
void STM32446RccPLLI2SEnable(void);
void STM32446RccPLLSAIEnable(void);

// RCC
uint8_t STM32446RccInic(void);
void STM32446RccHEnable(unsigned int hclock);
uint8_t STM32446RccHSelect(uint8_t hclock);
void STM32446RccLEnable(unsigned int lclock);
void STM32446RccLSelect(uint8_t lclock);
void STM32446Prescaler(unsigned int ahbpre, unsigned int ppre1, unsigned int ppre2, unsigned int rtcpre);
uint32_t SystemClock(void);

/*** MISCELLANEOUS ***/
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
void STM32446Gpiosetupreg(volatile uint32_t* reg, unsigned int size_block, unsigned int data, unsigned int pin);
void STM32446GpioSetup( volatile uint32_t vec[], const unsigned int size_block, unsigned int data, unsigned int block_n );
char* STM32446FUNCftoa(double num, char* res, uint8_t afterpoint);
char* STM32446FUNCprint( char* str, uint8_t size_str, const char* format, ... );
char STM32446bcd2dec(char num);
char STM32446dec2bcd(char num);

/*** FILE FUNC ***/
// SRAM
void STM32446SramAccess(void);
//COMMON
void STM32446Reverse(char s[]);
int STM32446StringLength (const char string[]);
uint8_t STM32446FUNCintinvstr(int32_t num, char* res, uint8_t n_digit);
// QUERY
uint32_t SystemClock(void);

/*** INTERRUPT ***/
// Systick
void SysTick_Handler(void);

/**** Procedure & Functions ***/
// STM32F446RE Image Linker
STM32446 STM32446enable(void){
	// Comment out the linked modules to reduce memmory usage.
	mem[0] = 0;
	nen[0] = 0;
	// CORE
	// Coprocessor Access Control Register
	stm32446.scb.reg = ((SCB_Type*) STM32446_SCB_BASE;

	// NVIC
	stm32446.nvic.reg = (NVIC_Type*) NVIC_BASE;
	
	// SysTick (Used as Delay Source)
	stm32446.systick.reg = (SysTick_Type*) SysTick_BASE;
	stm32446.systick.delay_ms = STM32446delay_ms;
	stm32446.systick.delay_10us = STM32446delay_10us;
	stm32446.systick.delay_us = STM32446delay_us;
	
	// STM32F446RE OBJECTS
	// ADC -> ADC1
	stm32446.adc1.common.reg = (ADC_Common_TypeDef*) ADC123_COMMON_BASE;
	stm32446.adc1.reg = (ADC_TypeDef*) ADC1_BASE;
	#if defined(_STM32446ADC_H_)
		stm32446.adc1.enable = STM32446ADC1enable;
	#endif

	// ADC -> ADC2
	stm32446.adc2.common.reg = (ADC_Common_TypeDef*) ADC123_COMMON_BASE;
	stm32446.adc2.reg = (ADC_TypeDef*) ADC2_BASE;
	#if defined(_STM32446ADC_H_)
		stm32446.adc2.enable = NULL;
	#endif

	// ADC -> ADC3
	stm32446.adc3.common.reg = (ADC_Common_TypeDef*) ADC123_COMMON_BASE;
	stm32446.adc3.reg = (ADC_TypeDef*) ADC3_BASE;
	#if defined(_STM32446ADC_H_)
		stm32446.adc3.enable = NULL;
	#endif

	// CRC
	stm32446.crc.reg = (CRC_TypeDef*) CRC_BASE;
	
	// DMA1
	stm32446.dma1.reg = (DMA_TypeDef*) DMA1_BASE;
	stm32446.dma1.stream[0].reg = (DMA_Stream_TypeDef*) DMA1_Stream0_BASE;

	// DMA2
	stm32446.dma2.reg = (DMA_TypeDef*) DMA2_BASE;
	stm32446.dma2.stream[0].reg = (DMA_Stream_TypeDef*) DMA2_Stream0_BASE;

	// FLASH
	stm32446.flash.reg = (FLASH_TypeDef*) FLASH_R_BASE;
	
	// GPIOA
	stm32446.gpioa.reg = (GPIO_TypeDef*) GPIOA_BASE;
	stm32446.gpioa.enable = STM32446GpioAenable;
	stm32446.gpioa.moder = STM32446GpioAmoder;
	stm32446.gpioa.ospeedr = STM32446GpioAospeedr;
	stm32446.gpioa.pupdr = STM32446GpioApupdr;
	stm32446.gpioa.reset = STM32446GpioAreset;
	stm32446.gpioa.set = STM32446GpioAset;
	stm32446.gpioa.afr = STM32446GpioAafr;
	
	// GPIOB
	stm32446.gpiob.reg = (GPIO_TypeDef*) GPIOB_BASE;
	stm32446.gpiob.enable = STM32446GpioBenable;
	stm32446.gpiob.moder = STM32446GpioBmoder;
	stm32446.gpiob.ospeedr = STM32446GpioBospeedr;
	stm32446.gpiob.pupdr = STM32446GpioBpupdr;
	stm32446.gpiob.reset = STM32446GpioBreset;
	stm32446.gpiob.set = STM32446GpioBset;
	stm32446.gpiob.afr = STM32446GpioBafr;
	
	// GPIOC
	stm32446.gpioc.reg = (GPIO_TypeDef*) GPIOC_BASE;
	stm32446.gpioc.enable = STM32446GpioCenable;
	stm32446.gpioc.moder = STM32446GpioCmoder;
	stm32446.gpioc.ospeedr = STM32446GpioCospeedr;
	stm32446.gpioc.pupdr = STM32446GpioCpupdr;
	stm32446.gpioc.reset = STM32446GpioCreset;
	stm32446.gpioc.set = STM32446GpioCset;
	stm32446.gpioc.afr = STM32446GpioCafr;
	
	// GPIOD
	stm32446.gpiod.reg = (GPIO_TypeDef*) GPIOD_BASE;
	stm32446.gpiod.enable = STM32446GpioDenable;
	stm32446.gpiod.moder = STM32446GpioDmoder;
	stm32446.gpiod.ospeedr = STM32446GpioDospeedr;
	stm32446.gpiod.pupdr = STM32446GpioDpupdr;
	stm32446.gpiod.reset = STM32446GpioDreset;
	stm32446.gpiod.set = STM32446GpioDset;
	stm32446.gpiod.afr = STM32446GpioDafr;

	// GPIOE
	stm32446.gpioe.reg = (GPIO_TypeDef*) GPIOE_BASE;
	stm32446.gpioe.enable = STM32446GpioEenable;
	stm32446.gpioe.moder = STM32446GpioEmoder;
	stm32446.gpioe.ospeedr = STM32446GpioEospeedr;
	stm32446.gpioe.pupdr = STM32446GpioEpupdr;
	stm32446.gpioe.reset = STM32446GpioEreset;
	stm32446.gpioe.set = STM32446GpioEset;
	stm32446.gpioe.afr = STM32446GpioEafr;

	// GPIOH
	stm32446.gpioh.reg = (GPIO_TypeDef*) GPIOH_BASE;
	stm32446.gpioh.enable = STM32446GpioHenable;
	stm32446.gpioh.moder = STM32446GpioHmoder;
	stm32446.gpioh.ospeedr = STM32446GpioHospeedr;
	stm32446.gpioh.pupdr = STM32446GpioHpupdr;
	stm32446.gpioh.reset = STM32446GpioHreset;
	stm32446.gpioh.set = STM32446GpioHset;
	stm32446.gpioh.afr = STM32446GpioHafr;

	// SYSCFG
	stm32446.syscfg.reg = (SYSCFG_TypeDef*) SYSCFG_BASE;
	stm32446.syscfg.enable = STM32446SysCfgEnable;
	
	// PWR
	stm32446.pwr.reg = (PWR_TypeDef*) PWR_BASE;

	// PLL
	stm32446.rcc.pll.division = STM32446PLLDivision;
	stm32446.rcc.pll.enable = STM32446RccPLLCLKEnable;
	stm32446.rcc.plli2s.enable = STM32446RccPLLI2SEnable;
	stm32446.rcc.pllsai.enable = STM32446RccPLLSAIEnable;

	// RCC
	stm32446.rcc.reg = (RCC_TypeDef*) RCC_BASE;
	stm32446.rcc.inic = STM32446RccInic;
	stm32446.rcc.henable = STM32446RccHEnable;
	stm32446.rcc.hselect = STM32446RccHSelect;
	stm32446.rcc.lenable = STM32446RccLEnable;
	stm32446.rcc.lselect = STM32446RccLSelect;
	stm32446.rcc.prescaler = STM32446Prescaler;
	stm32446.rcc.systemclock = SystemClock;
	
	// RTC
	stm32446.rtc.reg = (RTC_TypeDef*) RTC_BASE;
	#if defined(_STM32446RTC_H_)
		stm32446.rtc.enable = STM32446RTCenable;
	#endif
	
	// TIM -> TIM1
	stm32446.tim1.reg = (TIM_TypeDef*) TIM1_BASE;
	#if defined(_STM32446TIM_H_)
		stm32446.tim1.enable = NULL;
	#endif

	// TIM -> TIM2
	stm32446.tim2.reg = (TIM_TypeDef*) TIM2_BASE;
	#if defined(_STM32446TIM_H_)
		stm32446.tim2.enable = NULL;
	#endif

	// TIM -> TIM3
	stm32446.tim3.reg = (TIM_TypeDef*) TIM3_BASE;
	#if defined(_STM32446TIM_H_)
		stm32446.tim3.enable = NULL;
	#endif

	// TIM -> TIM4
	stm32446.tim4.reg = (TIM_TypeDef*) TIM4_BASE;
	#if defined(_STM32446TIM_H_)
		stm32446.tim4.enable = NULL;
	#endif

	// TIM -> TIM5
	stm32446.tim5.reg = (TIM_TypeDef*) TIM5_BASE;
	#if defined(_STM32446TIM_H_)
		stm32446.tim5.enable = NULL;
	#endif

	// TIM -> TIM6
	stm32446.tim6.reg = (TIM_TypeDef*) TIM6_BASE;
	#if defined(_STM32446TIM_H_)
		stm32446.tim6.enable = NULL;
	#endif

	// TIM -> TIM7
	stm32446.tim7.reg = (TIM_TypeDef*) TIM7_BASE;
	#if defined(_STM32446TIM_H_)
		stm32446.tim7.enable = NULL;
	#endif

	// TIM -> TIM8
	stm32446.tim8.reg = (TIM_TypeDef*) TIM8_BASE;
	#if defined(_STM32446TIM_H_)
		stm32446.tim8.enable = NULL;
	#endif

	// TIM -> TIM9
	stm32446.tim9.reg = (TIM_TypeDef*) TIM9_BASE;
	#if defined(_STM32446TIM_H_)
		stm32446.tim9.enable = STM32446TIM9enable;
	#endif

	// TIM -> TIM10
	stm32446.tim10.reg = (TIM_TypeDef*) TIM10_BASE;
	#if defined(_STM32446TIM_H_)
		stm32446.tim10.enable = NULL;
	#endif

	// TIM -> TIM11
	stm32446.tim11.reg = (TIM_TypeDef*) TIM11_BASE;
	#if defined(_STM32446TIM_H_)
		stm32446.tim11.enable = NULL;
	#endif

	// TIM -> TIM12
	stm32446.tim12.reg = (TIM_TypeDef*) TIM12_BASE;
	#if defined(_STM32446TIM_H_)
		stm32446.tim12.enable = NULL;
	#endif

	// TIM -> TIM13
	stm32446.tim13.reg = (TIM_TypeDef*) TIM13_BASE;
	#if defined(_STM32446TIM_H_)
		stm32446.tim13.enable = NULL;
	#endif

	// TIM -> TIM14
	stm32446.tim14.reg = (TIM_TypeDef*) TIM14_BASE;
	#if defined(_STM32446TIM_H_)
		stm32446.tim14.enable = NULL;
	#endif

	// USART -> USART1
	stm32446.usart1.reg = (USART_TypeDef*) USART1_BASE;
	#if defined(_STM32446USART_H_)
		stm32446.usart1.enable = STM32446USART1enable;
	#endif
	
	// USART -> USART2
	stm32446.usart2.reg = (USART_TypeDef*) USART2_BASE;
	#if defined(_STM32446USART_H_)
		stm32446.usart2.enable = NULL;
	#endif

	// USART -> USART3
	stm32446.usart3.reg = (USART_TypeDef*) USART3_BASE;
	#if defined(_STM32446USART_H_)
		stm32446.usart3.enable = NULL;
	#endif

	// USART -> USART4
	stm32446.usart4.reg = (USART_TypeDef*) UART4_BASE;
	#if defined(_STM32446USART_H_)
		stm32446.usart4.enable = NULL;
	#endif

	// USART -> USART5
	stm32446.usart5.reg = (USART_TypeDef*) UART5_BASE;
	#if defined(_STM32446USART_H_)
		stm32446.usart5.enable = NULL;
	#endif

	// USART -> USART6
	stm32446.usart6.reg = (USART_TypeDef*) USART6_BASE;
	#if defined(_STM32446USART_H_)
		stm32446.usart6.enable = NULL;
	#endif
	
	// INIC
	
	// ENABLE

	// QUERY
	stm32446.query.SystemClock = SystemClock;

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
	stm32446.func.setpins = STM32446GpioSetpins;
	stm32446.func.setpin = STM32446GpioSetpin;
	stm32446.func.set = STM32446GpioSet;
	stm32446.func.resetpins = STM32446GpioResetpins;
	stm32446.func.resetpin = STM32446GpioResetpin;
	stm32446.func.reset = STM32446GpioReset;
	stm32446.func.setupreg = STM32446Gpiosetupreg;
	stm32446.func.pinblock = STM32446PinBlock;
	stm32446.func.setup = STM32446GpioSetup;
	stm32446.func.ftoa = STM32446FUNCftoa;
	stm32446.func.print = STM32446FUNCprint;
	
	SystickInic(); // Polling delay source.

	return stm32446;
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
			if( set ){ stm32446.rcc.reg->CR |= ( 1 << 0); set = 0; }else if( stm32446.rcc.reg->CR & ( 1 << 1) ) rdy = 0;
		}
		else if(hclock == 1){ // HSEON: HSE clock enable
			if( set ){ stm32446.rcc.reg->CR |= ( 1 << 16); set = 0; }else if( stm32446.rcc.reg->CR & ( 1 << 17) ) rdy = 0;
		}
		else if(hclock == 2){ // HSEBYP: HSE clock bypass
			if( set ) stm32446.rcc.reg->CR |= ( 1 << 18 );
			hclock = 1;
		}
		else hclock = 0; // default
	}
}

uint8_t STM32446RccHSelect(uint8_t hclock)
{ // SW[1:0]: System clock switch 00 - HSI, 01 - HSE pg133
	stm32446.rcc.reg->CFGR &= (unsigned int) ~(3); // 00: HSI oscillator selected as system clock
	switch(hclock){
		case 1:
			stm32446.rcc.reg->CFGR |= 1; // HSE oscillator selected as system clock
		break;
		case 2:
			stm32446.rcc.reg->CFGR |= 2; // PLL_P selected as system clock
		break;
		case 3:
			stm32446.rcc.reg->CFGR |= 3; // PLL_R selected as system clock
		break;
		default:
		break;
	}
	return (stm32446.rcc.reg->CFGR >> 2) & 3;
}

void STM32446RccLEnable(unsigned int lclock)
{
	unsigned int set;
	unsigned int rdy;
	for( set = 1, rdy = 1; rdy ; ){
		if(lclock == 2){ // LSION: Internal low-speed oscillator enable
			if( set ){ stm32446.rcc.reg->CSR |= ( 1 << 0); set = 0; }else if( stm32446.rcc.reg->CSR & ( 1 << 1) ) rdy = 0;
		}
		else if(lclock == 1){ // LSEON: External low-speed oscillator enable
			if( set ){ stm32446.rcc.reg->BDCR |= ( 1 << 0); set = 0; }else if( stm32446.rcc.reg->BDCR & ( 1 << 1) ) rdy = 0;
		}
		else if(lclock == 4){ // LSEBYP: External low-speed oscillator bypass
			if( set ) stm32446.rcc.reg->BDCR |= ( 1 << 2 );
			lclock = 1;
		}
		else lclock = 2; // default
	}
}

void STM32446RccLSelect(uint8_t lclock)
{
	stm32446.rcc.reg->BDCR &= (uint32_t) ~((1 << 9) | (1 << 8)); // RTCSEL[1:0]: RTC clock source selection
	switch(lclock){
		case 2:
			stm32446.rcc.reg->BDCR |= (1 << 9); // LSI oscillator clock used as the RTC clock
		break;
		case 1:
			stm32446.rcc.reg->BDCR |= (1 << 8); // LSE oscillator clock used as the RTC clock
		break;
		case 3:
			stm32446.rcc.reg->BDCR |= ((1 << 8) | (1 << 9)); // HSE oscillator clock divided by a programmable prescaler
		break;
		default:
			stm32446.rcc.reg->BDCR |= (1 << 8); // LSE oscillator clock used as the RTC clock
		break;
	}
}

void STM32446Prescaler(unsigned int ahbpre, unsigned int ppre1, unsigned int ppre2, unsigned int rtcpre)
{
	const unsigned int mask = 0x001FFCF0;
	stm32446.rcc.reg->CFGR &= (unsigned int) ~mask; // clear args

	if(rtcpre > 1 && rtcpre < 32) // 16
		stm32446.rcc.reg->CFGR |= (rtcpre << 16);

	switch(ppre2){ // 13
		case 2:
			stm32446.rcc.reg->CFGR |= (4 << 13);
			stm32446.CLOCK_prescaler.APB2 = 2;
		break;
		case 4:
			stm32446.rcc.reg->CFGR |= (5 << 13);
			stm32446.CLOCK_prescaler.APB2 = 4;
		break;
		case 8:
			stm32446.rcc.reg->CFGR |= (6 << 13);
			stm32446.CLOCK_prescaler.APB2 = 8;
		break;
		case 16:
			stm32446.rcc.reg->CFGR |= (7 << 13);
			stm32446.CLOCK_prescaler.APB2 = 16;
		break;
		default:
			stm32446.CLOCK_prescaler.APB2 = 1;
		break;
	}

	switch(ppre1){ // 10
	case 2:
		stm32446.rcc.reg->CFGR |= (4 << 10);
		stm32446.CLOCK_prescaler.APB1 = 2;
	break;
	case 4:
		stm32446.rcc.reg->CFGR |= (5 << 10);
		stm32446.CLOCK_prescaler.APB1 = 4;
	break;
	case 8:
		stm32446.rcc.reg->CFGR |= (6 << 10);
		stm32446.CLOCK_prescaler.APB1 = 8;
	break;
	case 16:
		stm32446.rcc.reg->CFGR |= (7 << 10);
		stm32446.CLOCK_prescaler.APB1 = 16;
	break;
	default:
		stm32446.CLOCK_prescaler.APB1 = 1;
	break;
	}

	switch(ahbpre){ // 4
	case 2:
		stm32446.rcc.reg->CFGR |= (8 << 4);
		stm32446.CLOCK_prescaler.AHB = 2;
	break;
	case 4:
		stm32446.rcc.reg->CFGR |= (9 << 4);
		stm32446.CLOCK_prescaler.AHB = 4;
	break;
	case 8:
		stm32446.rcc.reg->CFGR |= (10 << 4);
		stm32446.CLOCK_prescaler.AHB = 8;
	break;
	case 16:
		stm32446.rcc.reg->CFGR |= (11 << 4);
		stm32446.CLOCK_prescaler.AHB = 16;
	break;
	case 64:
		stm32446.rcc.reg->CFGR |= (12 << 4);
		stm32446.CLOCK_prescaler.AHB = 64;
	break;
	case 128:
		stm32446.rcc.reg->CFGR |= (13 << 4);
		stm32446.CLOCK_prescaler.AHB = 128;
	break;
	case 256:
		stm32446.rcc.reg->CFGR |= (14 << 4);
		stm32446.CLOCK_prescaler.AHB = 256;
	break;
	case 512:
		stm32446.rcc.reg->CFGR |= (15 << 4);
		stm32446.CLOCK_prescaler.AHB = 512;
	break;
	default:
		stm32446.CLOCK_prescaler.AHB = 1;
	break;
	}
}

// PLL
void STM32446PLLDivision(unsigned int pllsrc, unsigned int pllm, unsigned int plln, unsigned int pllp, unsigned int pllq, unsigned int pllr)
{
	const unsigned int mask = 0x7F437FFF;
	stm32446.rcc.reg->PLLCFGR &= (unsigned int) ~mask; // set mask bits LOW


	if(pllr > 1 && pllr < 8){ // PLLR[28]: Main PLL division factor for I2Ss, SAIs, SYSTEM and SPDIF-Rx clocks
		stm32446.rcc.reg->PLLCFGR |= (pllr << 28);
		stm32446.PLL_parameter.R = pllr;
	}

	if(pllq > 1 && pllq < 16){ // PLLQ[24]: Main PLL (PLL) division factor for USB OTG FS, SDIOclocks
		stm32446.rcc.reg->PLLCFGR |= (pllq << 24);
		stm32446.PLL_parameter.Q = pllq;
	}

	if(pllsrc == 1){ // PLLSRC[22]: Main PLL(PLL) and audio PLL (PLLI2S) entry clock source
		stm32446.PLL_parameter.Source = 25000000;
		stm32446.rcc.reg->PLLCFGR |= (1 << 22);
	}else{
		stm32446.PLL_parameter.Source = 16000000;
	}

	switch(pllp){ // PLLP[16]: Main PLL (PLL) division factor for main system clock
		case 2:
			stm32446.PLL_parameter.P = pllp;
		break;
		case 4:
			stm32446.rcc.reg->PLLCFGR |= (1 << 16);
			stm32446.PLL_parameter.P = pllp;
		break;
		case 6:
			stm32446.rcc.reg->PLLCFGR |= (2 << 16);
			stm32446.PLL_parameter.P = pllp;
		break;
		case 8:
			stm32446.rcc.reg->PLLCFGR |= (3 << 16);
			stm32446.PLL_parameter.P = pllp;
		break;
		default:
			stm32446.rcc.reg->PLLCFGR |= (1 << 16);
			stm32446.PLL_parameter.P = 4;
		break;
	}

	if(plln > 49 && plln < 433){ // PLLN[6]: Main PLL (PLL) multiplication factor for VCO
		stm32446.rcc.reg->PLLCFGR |= (plln << 6);
		stm32446.PLL_parameter.N = plln;
	}

	if(pllm > 1 && pllm < 64){ // PLLM[0]: Division factor for the main PLL (PLL) input clock [2Mhz]
		stm32446.rcc.reg->PLLCFGR |= pllm;
		stm32446.PLL_parameter.M = pllm;
	}
}

void STM32446RccPLLCLKEnable(void)
{
	//if(onoff){
		for( stm32446.rcc.reg->CR |= (1 << 24) ; !(stm32446.rcc.reg->CR & (1 << 25)) ; ); // PLLON: Main PLL (PLL) enable
	//}else{
		//stm32446.rcc.reg->CR &= (unsigned int) ~(1 << 24);
	//}
}

void STM32446RccPLLI2SEnable(void)
{
	//if(onoff)
		for( stm32446.rcc.reg->CR |= (1 << 26) ; !(stm32446.rcc.reg->CR & (1 << 27)) ; ); // PLLI2SON: PLLI2S enable
	//else
		//stm32446.rcc.reg->CR &= (unsigned int) ~(1 << 26);
}

void STM32446RccPLLSAIEnable(void)
{
	//if(onoff)
		for( stm32446.rcc.reg->CR |= (1 << 28) ; !(stm32446.rcc.reg->CR & (1 << 29)) ; ); // PLLSAION: PLLSAI enable
	//else
		//stm32446.rcc.reg->CR &= (unsigned int) ~(1 << 28);
}

uint32_t SystemClock(void) // Query
{
	uint32_t sysclk;
	switch((stm32446.rcc.reg->CFGR >> 2) & 3) // SWS[2]: System clock switch status
	{
		case 0: // 00: HSI oscillator used as the system clock
			stm32446.PLL_parameter.Source = 16000000;
			sysclk= 16000000;
		break;
		case 1: // 01: HSE oscillator used as the system clock
			stm32446.PLL_parameter.Source = 25000000;
			sysclk = 25000000;
		break;
		case 2: // 10: PLL used as the system clock
			sysclk = ( stm32446.PLL_parameter.Source / stm32446.PLL_parameter.M ) * ( stm32446.PLL_parameter.N / stm32446.PLL_parameter.P );
		break;
		case 3: // 11: PLL_R used as the system clock
			sysclk = ( stm32446.PLL_parameter.Source / stm32446.PLL_parameter.M ) * ( stm32446.PLL_parameter.N / stm32446.PLL_parameter.R );
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
	stm32446.rcc.reg->AHB1ENR |= (1 << 0);
}

void STM32446GpioAmoder( unsigned int data, unsigned int pin )
{
	const unsigned int blocksize = 2;
	unsigned int mask = (unsigned int)(pow(2, blocksize) - 1);
	data &= mask;
	stm32446.gpioa.reg->MODER &= ~(mask << (pin * blocksize));
	stm32446.gpioa.reg->MODER |= (data << (pin * blocksize));
}

void STM32446GpioAospeedr( unsigned int data, unsigned int pin )
{
	const unsigned int blocksize = 2;
	unsigned int mask = (unsigned int)(pow(2, blocksize) - 1);
	data &= mask;
	stm32446.gpioa.reg->OSPEEDR &= ~(mask << (pin * blocksize));
	stm32446.gpioa.reg->OSPEEDR |= (data << (pin * blocksize));
}

void STM32446GpioApupdr( unsigned int data, unsigned int pin )
{
	const unsigned int blocksize = 2;
	unsigned int mask = (unsigned int)(pow(2, blocksize) - 1);
	data &= mask;
	stm32446.gpioa.reg->PUPDR &= ~(mask << (pin * blocksize));
	stm32446.gpioa.reg->PUPDR |= (data << (pin * blocksize));
}

void STM32446GpioAreset( unsigned int data )
{
	stm32446.gpioa.reg->BSRR = (unsigned int)(data << 16);
}

void STM32446GpioAset( unsigned int data )
{
	stm32446.gpioa.reg->BSRR = (unsigned int)( data );
}

void STM32446GpioAafr( unsigned int data, unsigned int pin )
{
	const unsigned int blocksize = 4;
	const unsigned int n_bits = sizeof(unsigned int) * 8;
	const unsigned int mask = (unsigned int) (pow(2, blocksize) - 1);
	unsigned int index = (pin * blocksize) / n_bits;
	data &= mask;
	if(index < 2){
		stm32446.gpioa.reg->AFR[index] &= ~( mask << ((pin * blocksize) - (index * n_bits)) );
		stm32446.gpioa.reg->AFR[index] |= ( data << ((pin * blocksize) - (index * n_bits)) );
	}
}

// GPIOB
void STM32446GpioBenable( void )
{
	stm32446.rcc.reg->AHB1ENR |= (1 << 1);
}

void STM32446GpioBmoder( unsigned int data, unsigned int pin )
{
	const unsigned int blocksize = 2;
	unsigned int mask = (unsigned int)(pow(2, blocksize) - 1);
	data &= mask;
	stm32446.gpiob.reg->MODER &= ~(mask << (pin * blocksize));
	stm32446.gpiob.reg->MODER |= (data << (pin * blocksize));
}

void STM32446GpioBospeedr( unsigned int data, unsigned int pin )
{
	const unsigned int blocksize = 2;
	unsigned int mask = (unsigned int)(pow(2, blocksize) - 1);
	data &= mask;
	stm32446.gpiob.reg->OSPEEDR &= ~(mask << (pin * blocksize));
	stm32446.gpiob.reg->OSPEEDR |= (data << (pin * blocksize));
}

void STM32446GpioBpupdr( unsigned int data, unsigned int pin )
{
	const unsigned int blocksize = 2;
	unsigned int mask = (unsigned int)(pow(2, blocksize) - 1);
	data &= mask;
	stm32446.gpiob.reg->PUPDR &= ~(mask << (pin * blocksize));
	stm32446.gpiob.reg->PUPDR |= (data << (pin * blocksize));
}

void STM32446GpioBreset( unsigned int data )
{
	stm32446.gpiob.reg->BSRR = (unsigned int)(data << 16);
}

void STM32446GpioBset( unsigned int data )
{
	stm32446.gpiob.reg->BSRR = (unsigned int)( data );
}

void STM32446GpioBafr( unsigned int data, unsigned int pin )
{
	const unsigned int blocksize = 4;
	const unsigned int n_bits = sizeof(unsigned int) * 8;
	const unsigned int mask = (unsigned int) (pow(2, blocksize) - 1);
	unsigned int index = (pin * blocksize) / n_bits;
	data &= mask;
	if(index < 2){
		stm32446.gpiob.reg->AFR[index] &= ~( mask << ((pin * blocksize) - (index * n_bits)) );
		stm32446.gpiob.reg->AFR[index] |= ( data << ((pin * blocksize) - (index * n_bits)) );
	}
}

// GPIOC
void STM32446GpioCenable( void )
{
	stm32446.rcc.reg->AHB1ENR |= (1 << 2);
}

void STM32446GpioCmoder( unsigned int data, unsigned int pin )
{
	const unsigned int blocksize = 2;
	unsigned int mask = (unsigned int)(pow(2, blocksize) - 1);
	data &= mask;
	stm32446.gpioc.reg->MODER &= ~(mask << (pin * blocksize));
	stm32446.gpioc.reg->MODER |= (data << (pin * blocksize));
}

void STM32446GpioCospeedr( unsigned int data, unsigned int pin )
{
	const unsigned int blocksize = 2;
	unsigned int mask = (unsigned int)(pow(2, blocksize) - 1);
	data &= mask;
	stm32446.gpioc.reg->OSPEEDR &= ~(mask << (pin * blocksize));
	stm32446.gpioc.reg->OSPEEDR |= (data << (pin * blocksize));
}

void STM32446GpioCpupdr( unsigned int data, unsigned int pin )
{
	const unsigned int blocksize = 2;
	unsigned int mask = (unsigned int)(pow(2, blocksize) - 1);
	data &= mask;
	stm32446.gpioc.reg->PUPDR &= ~(mask << (pin * blocksize));
	stm32446.gpioc.reg->PUPDR |= (data << (pin * blocksize));
}

void STM32446GpioCreset( unsigned int data )
{
	stm32446.gpioc.reg->BSRR = (unsigned int)(data << 16);
}

void STM32446GpioCset( unsigned int data )
{
	stm32446.gpioc.reg->BSRR = (unsigned int)( data );
}

void STM32446GpioCafr( unsigned int data, unsigned int pin )
{
	const unsigned int blocksize = 4;
	const unsigned int n_bits = sizeof(unsigned int) * 8;
	const unsigned int mask = (unsigned int) (pow(2, blocksize) - 1);
	unsigned int index = (pin * blocksize) / n_bits;
	data &= mask;
	if(index < 2){
		stm32446.gpioc.reg->AFR[index] &= ~( mask << ((pin * blocksize) - (index * n_bits)) );
		stm32446.gpioc.reg->AFR[index] |= ( data << ((pin * blocksize) - (index * n_bits)) );
	}
}

// GPIOD
void STM32446GpioDenable( void )
{
	stm32446.rcc.reg->AHB1ENR |= (1 << 3);
}

void STM32446GpioDmoder( unsigned int data, unsigned int pin )
{
	const unsigned int blocksize = 2;
	unsigned int mask = (unsigned int)(pow(2, blocksize) - 1);
	data &= mask;
	stm32446.gpiod.reg->MODER &= ~(mask << (pin * blocksize));
	stm32446.gpiod.reg->MODER |= (data << (pin * blocksize));
}

void STM32446GpioDospeedr( unsigned int data, unsigned int pin )
{
	const unsigned int blocksize = 2;
	unsigned int mask = (unsigned int)(pow(2, blocksize) - 1);
	data &= mask;
	stm32446.gpiod.reg->OSPEEDR &= ~(mask << (pin * blocksize));
	stm32446.gpiod.reg->OSPEEDR |= (data << (pin * blocksize));
}

void STM32446GpioDpupdr( unsigned int data, unsigned int pin )
{
	const unsigned int blocksize = 2;
	unsigned int mask = (unsigned int)(pow(2, blocksize) - 1);
	data &= mask;
	stm32446.gpiod.reg->PUPDR &= ~(mask << (pin * blocksize));
	stm32446.gpiod.reg->PUPDR |= (data << (pin * blocksize));
}

void STM32446GpioDreset( unsigned int data )
{
	stm32446.gpiod.reg->BSRR = (unsigned int)(data << 16);
}

void STM32446GpioDset( unsigned int data )
{
	stm32446.gpiod.reg->BSRR = (unsigned int)( data );
}

void STM32446GpioDafr( unsigned int data, unsigned int pin )
{
	const unsigned int blocksize = 4;
	const unsigned int n_bits = sizeof(unsigned int) * 8;
	const unsigned int mask = (unsigned int) (pow(2, blocksize) - 1);
	unsigned int index = (pin * blocksize) / n_bits;
	data &= mask;
	if(index < 2){
		stm32446.gpiod.reg->AFR[index] &= ~( mask << ((pin * blocksize) - (index * n_bits)) );
		stm32446.gpiod.reg->AFR[index] |= ( data << ((pin * blocksize) - (index * n_bits)) );
	}
}

// GPIOE
void STM32446GpioEenable( void )
{
	stm32446.rcc.reg->AHB1ENR |= (1 << 4);
}

void STM32446GpioEmoder( unsigned int data, unsigned int pin )
{
	const unsigned int blocksize = 2;
	unsigned int mask = (unsigned int)(pow(2, blocksize) - 1);
	data &= mask;
	stm32446.gpioe.reg->MODER &= ~(mask << (pin * blocksize));
	stm32446.gpioe.reg->MODER |= (data << (pin * blocksize));
}

void STM32446GpioEospeedr( unsigned int data, unsigned int pin )
{
	const unsigned int blocksize = 2;
	unsigned int mask = (unsigned int)(pow(2, blocksize) - 1);
	data &= mask;
	stm32446.gpioe.reg->OSPEEDR &= ~(mask << (pin * blocksize));
	stm32446.gpioe.reg->OSPEEDR |= (data << (pin * blocksize));
}

void STM32446GpioEpupdr( unsigned int data, unsigned int pin )
{
	const unsigned int blocksize = 2;
	unsigned int mask = (unsigned int)(pow(2, blocksize) - 1);
	data &= mask;
	stm32446.gpioe.reg->PUPDR &= ~(mask << (pin * blocksize));
	stm32446.gpioe.reg->PUPDR |= (data << (pin * blocksize));
}

void STM32446GpioEreset( unsigned int data )
{
	stm32446.gpioe.reg->BSRR = (unsigned int)(data << 16);
}

void STM32446GpioEset( unsigned int data )
{
	stm32446.gpioe.reg->BSRR = (unsigned int)( data );
}

void STM32446GpioEafr( unsigned int data, unsigned int pin )
{
	const unsigned int blocksize = 4;
	const unsigned int n_bits = sizeof(unsigned int) * 8;
	const unsigned int mask = (unsigned int) (pow(2, blocksize) - 1);
	unsigned int index = (pin * blocksize) / n_bits;
	data &= mask;
	if(index < 2){
		stm32446.gpioe.reg->AFR[index] &= ~( mask << ((pin * blocksize) - (index * n_bits)) );
		stm32446.gpioe.reg->AFR[index] |= ( data << ((pin * blocksize) - (index * n_bits)) );
	}
}

// GPIOH
void STM32446GpioHenable( void )
{
	stm32446.rcc.reg->AHB1ENR |= (1 << 7);
}

void STM32446GpioHmoder( unsigned int data, unsigned int pin )
{
	const unsigned int blocksize = 2;
	unsigned int mask = (unsigned int)(pow(2, blocksize) - 1);
	data &= mask;
	stm32446.gpioh.reg->MODER &= ~(mask << (pin * blocksize));
	stm32446.gpioh.reg->MODER |= (data << (pin * blocksize));
}

void STM32446GpioHospeedr( unsigned int data, unsigned int pin )
{
	const unsigned int blocksize = 2;
	unsigned int mask = (unsigned int)(pow(2, blocksize) - 1);
	data &= mask;
	stm32446.gpioh.reg->OSPEEDR &= ~(mask << (pin * blocksize));
	stm32446.gpioh.reg->OSPEEDR |= (data << (pin * blocksize));
}

void STM32446GpioHpupdr( unsigned int data, unsigned int pin )
{
	const unsigned int blocksize = 2;
	unsigned int mask = (unsigned int)(pow(2, blocksize) - 1);
	data &= mask;
	stm32446.gpioh.reg->PUPDR &= ~(mask << (pin * blocksize));
	stm32446.gpioh.reg->PUPDR |= (data << (pin * blocksize));
}

void STM32446GpioHreset( unsigned int data )
{
	stm32446.gpioh.reg->BSRR = (unsigned int)(data << 16);
}

void STM32446GpioHset( unsigned int data )
{
	stm32446.gpioh.reg->BSRR = (unsigned int)( data );
}

void STM32446GpioHafr( unsigned int data, unsigned int pin )
{
	const unsigned int blocksize = 4;
	const unsigned int n_bits = sizeof(unsigned int) * 8;
	const unsigned int mask = (unsigned int) (pow(2, blocksize) - 1);
	unsigned int index = (pin * blocksize) / n_bits;
	data &= mask;
	if(index < 2){
		stm32446.gpioh.reg->AFR[index] &= ~( mask << ((pin * blocksize) - (index * n_bits)) );
		stm32446.gpioh.reg->AFR[index] |= ( data << ((pin * blocksize) - (index * n_bits)) );
	}
}

// SYSCFG
void STM32446SysCfgEnable(void)
{
	stm32446.rcc.reg->APB2ENR |= (1 << 14); //syscfg clock enable
}

// MISCELLANEOUS
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

// FILE FUNC
// SRAM
void STM32446SramAccess(void)
{
	// RM0390 pg 94
	// SRAM access
	// 0 - Power Up SRAM
	stm32446.pwr.reg->CSR |= (1 << 9); // BRE: Backup regulator enable
	// Check ready flag Bit 3 BRR: Backup regulator ready
	for( ; !(stm32446.pwr.reg->CSR & (1 << 3) )  ; ); // BRR: Backup regulator ready
	
	// 1 - Enable the power interface clock by setting the PWREN bits in the RCC_APB1ENR
	stm32446.rcc.reg->APB1ENR |= (1 << 28); // Power interface clock enable
	//RCC->APB1ENR |= ((1 << 11) | (1 << 28));

	// 2 - Set the DBP bit in the PWR power control register (PWR_CR)
	stm32446.pwr.reg->CR |= (1 << 8); // Disable backup domain write protection

	// 3 - Enable the backup SRAM clock by setting BKPSRAMEN bit in the RCC_AHB1ENR
	stm32446.rcc.reg->AHB1ENR |= (1 << 18); // BKPSRAMEN: Backup SRAM interface clock enable
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
	stm32446.systick.reg->LOAD = (uint32_t)(SystemClock() - 1);
	stm32446.systick.reg->VAL = 0UL;
	stm32446.systick.reg->CTRL |= ((1 << 1) | (1 << 2));
}

void STM32446delay_ms(uint32_t ms)
{
	stm32446.systick.reg->LOAD = (uint32_t)((SystemClock() / 1000) - 1);
	// Enable the SysTick timer
	stm32446.systick.reg->CTRL |= (1 << 0);
	// Wait for a specified number of milliseconds
	DelayCounter = 0;
	while (DelayCounter < ms);
	// Disable the SysTick timer
	stm32446.systick.reg->CTRL &= (uint32_t) ~(1 << 0);
}

void STM32446delay_10us(uint32_t ten_us)
{
	stm32446.systick.reg->LOAD = (uint32_t)((SystemClock() / 100000) - 1);
	// Enable the SysTick timer
	stm32446.systick.reg->CTRL |= (1 << 0);
	// Wait for a specified number of milliseconds
	DelayCounter = 0;
	while (DelayCounter < ten_us);
	// Disable the SysTick timer
	stm32446.systick.reg->CTRL &= (uint32_t) ~(1 << 0);
}

void STM32446delay_us(uint32_t us)
{
	stm32446.systick.reg->LOAD = (uint32_t)((SystemClock() / 1000000) - 1);
	// Enable the SysTick timer
	stm32446.systick.reg->CTRL |= (1 << 0);
	// Wait for a specified number of milliseconds
	DelayCounter = 0;
	while (DelayCounter < us);
	// Disable the SysTick timer
	stm32446.systick.reg->CTRL &= (uint32_t) ~(1 << 0);
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


