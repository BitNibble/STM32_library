/******************************************************************************
	STM32 446 MAPPING
Author: Sergio Santos 
	<sergio.salazar.santos@gmail.com>
License: GNU General Public License
Hardware: STM32-446
Date: 28052023
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
static uint32_t DelayCounter;
static uint32_t mem[4];
static uint32_t nen[4];

/*** File Header ***/
// CORE
/*** SYSTICK ***/
void SystickInic(void);
void STM32446delay_ms(uint32_t ms);
void STM32446delay_10us(uint32_t ten_us);
void STM32446delay_us(uint32_t us);
// INTERRUPT
void SysTick_Handler(void);

// SYSCFG
void STM32446SysCfgEnable(void);
// SRAM
void STM32446SramAccess(void);

/*** MISCELLANEOUS ***/
// MCU
void STM32446RegSetBits( unsigned int* reg, int n_bits, ... );
void STM32446RegResetBits( unsigned int* reg, int n_bits, ... );
void STM32446RegSetup(volatile uint32_t* reg, unsigned int size_block, unsigned int data, unsigned int bit);
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

/**** Procedure & Functions Definitions ***/
/******** STM32F446RE Image Linker ********/
STM32446 STM32446enable(void){
	/*** DEFAULT ***/
	stm32446.query.sysclk = 16000000;
	stm32446.query.PLL_parameter.Source = 16000000;
	mem[0] = 0;
	nen[0] = 0;
	/************* CORE ************/
	// Coprocessor Access Control Register
	stm32446.scb.reg = ((SCB_Type*) STM32446_SCB_BASE;

	// NVIC
	stm32446.nvic.reg = (NVIC_Type*) NVIC_BASE;
	
	// SysTick (Used as Delay Source)
	stm32446.systick.reg = (SysTick_Type*) SysTick_BASE;
	stm32446.systick.delay_ms = STM32446delay_ms;
	stm32446.systick.delay_10us = STM32446delay_10us;
	stm32446.systick.delay_us = STM32446delay_us;
	
	/************ MCU ************/
	// ADC -> ADC1
	stm32446.adc1.common.reg = (ADC_Common_TypeDef*) ADC123_COMMON_BASE;
	stm32446.adc1.reg = (ADC_TypeDef*) ADC1_BASE;
	#if defined(_STM32446ADC_H_)
		stm32446.adc1.enable = STM32446ADC1enable;
		stm32446.adc1.single.inic = STM32446Adc1Inic;
		stm32446.adc1.single.vbat = STM32446Adc1VBAT;
		stm32446.adc1.single.temp = STM32446Adc1TEMP;
		stm32446.adc1.single.start = STM32446Adc1Start;
		stm32446.adc1.single.read = STM32446Adc1Read;
		stm32446.adc1.single.restart = STM32446Adc1Restart;
		stm32446.adc1.single.stop = STM32446Adc1Stop;
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
	#if defined(_STM32446GPIO_H_)
		stm32446.gpioa.enable = STM32446GPIOAenable;
		stm32446.gpioa.moder = STM32446GpioAmoder;
		stm32446.gpioa.ospeedr = STM32446GpioAospeedr;
		stm32446.gpioa.pupdr = STM32446GpioApupdr;
		stm32446.gpioa.reset = STM32446GpioAreset;
		stm32446.gpioa.set = STM32446GpioAset;
		stm32446.gpioa.afr = STM32446GpioAafr;
	#endif

	// GPIOB
	stm32446.gpiob.reg = (GPIO_TypeDef*) GPIOB_BASE;
	#if defined(_STM32446GPIO_H_)
		stm32446.gpiob.enable = STM32446GPIOBenable;
		stm32446.gpiob.moder = STM32446GpioBmoder;
		stm32446.gpiob.ospeedr = STM32446GpioBospeedr;
		stm32446.gpiob.pupdr = STM32446GpioBpupdr;
		stm32446.gpiob.reset = STM32446GpioBreset;
		stm32446.gpiob.set = STM32446GpioBset;
		stm32446.gpiob.afr = STM32446GpioBafr;
	#endif

	// GPIOC
	stm32446.gpioc.reg = (GPIO_TypeDef*) GPIOC_BASE;
	#if defined(_STM32446GPIO_H_)
		stm32446.gpioc.enable = STM32446GPIOCenable;
		stm32446.gpioc.moder = STM32446GpioCmoder;
		stm32446.gpioc.ospeedr = STM32446GpioCospeedr;
		stm32446.gpioc.pupdr = STM32446GpioCpupdr;
		stm32446.gpioc.reset = STM32446GpioCreset;
		stm32446.gpioc.set = STM32446GpioCset;
		stm32446.gpioc.afr = STM32446GpioCafr;
	#endif

	// GPIOD
	stm32446.gpiod.reg = (GPIO_TypeDef*) GPIOD_BASE;
	#if defined(_STM32446GPIO_H_)
		stm32446.gpiod.enable = STM32446GPIODenable;
		stm32446.gpiod.moder = STM32446GpioDmoder;
		stm32446.gpiod.ospeedr = STM32446GpioDospeedr;
		stm32446.gpiod.pupdr = STM32446GpioDpupdr;
		stm32446.gpiod.reset = STM32446GpioDreset;
		stm32446.gpiod.set = STM32446GpioDset;
		stm32446.gpiod.afr = STM32446GpioDafr;
	#endif

	// GPIOE
	stm32446.gpioe.reg = (GPIO_TypeDef*) GPIOE_BASE;
	#if defined(_STM32446GPIO_H_)
		stm32446.gpioe.enable = STM32446GPIOEenable;
		stm32446.gpioe.moder = STM32446GpioEmoder;
		stm32446.gpioe.ospeedr = STM32446GpioEospeedr;
		stm32446.gpioe.pupdr = STM32446GpioEpupdr;
		stm32446.gpioe.reset = STM32446GpioEreset;
		stm32446.gpioe.set = STM32446GpioEset;
		stm32446.gpioe.afr = STM32446GpioEafr;
	#endif

	// GPIOH
	stm32446.gpioh.reg = (GPIO_TypeDef*) GPIOH_BASE;
	#if defined(_STM32446GPIO_H_)
		stm32446.gpioh.enable = STM32446GPIOHenable;
		stm32446.gpioh.moder = STM32446GpioHmoder;
		stm32446.gpioh.ospeedr = STM32446GpioHospeedr;
		stm32446.gpioh.pupdr = STM32446GpioHpupdr;
		stm32446.gpioh.reset = STM32446GpioHreset;
		stm32446.gpioh.set = STM32446GpioHset;
		stm32446.gpioh.afr = STM32446GpioHafr;
	#endif

	// SYSCFG
	stm32446.syscfg.reg = (SYSCFG_TypeDef*) SYSCFG_BASE;
	stm32446.syscfg.enable = STM32446SysCfgEnable;
	
	// PWR
	stm32446.pwr.reg = (PWR_TypeDef*) PWR_BASE;

	// PLL
	#if defined(_STM32446RCC_H_)
		stm32446.rcc.pll.enable = STM32446RccPLLCLKEnable;
		stm32446.rcc.plli2s.enable = STM32446RccPLLI2SEnable;
		stm32446.rcc.pllsai.enable = STM32446RccPLLSAIEnable;
		stm32446.rcc.pll.division = STM32446PLLDivision;
		stm32446.rcc.prescaler = STM32446Prescaler;
		stm32446.rcc.systemclock = SystemClock;
	#endif

	// RCC
	stm32446.rcc.reg = (RCC_TypeDef*) RCC_BASE;
	#if defined(_STM32446RCC_H_)
		stm32446.rcc.enable = STM32446RCCenable;
		stm32446.rcc.henable = STM32446RccHEnable;
		stm32446.rcc.hselect = STM32446RccHSelect;
		stm32446.rcc.lenable = STM32446RccLEnable;
		stm32446.rcc.lselect = STM32446RccLSelect;
	#endif
	
	//RTC
	stm32446.rtc.reg = (RTC_TypeDef*) RTC_BASE;
	#if defined(_STM32446RTC_H_)
		stm32446.rtc.enable = STM32446RTCenable;
		stm32446.rtc.inic = STM32446RtcInic;
		stm32446.rtc.Day = STM32446RtcDay;
		stm32446.rtc.Month = STM32446RtcMonth;
		stm32446.rtc.WeekDay = STM32446RtcWeekDay;
		stm32446.rtc.Year = STM32446RtcYear;
		stm32446.rtc.Hour = STM32446RtcHour;
		stm32446.rtc.Minute = STM32446RtcMinute;
		stm32446.rtc.Second = STM32446RtcSecond;
		stm32446.rtc.dr2vec = STM32446Rtcdr2vec;
		stm32446.rtc.tr2vec = STM32446Rtctr2vec;
		stm32446.rtc.RegWrite = STM32446RtcRegWrite;
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
		stm32446.tim9.inic = STM32446Tim9Inic;
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
		stm32446.usart1.inic = STM32446Usart1Inic;
		stm32446.usart1.transmit = STM32446Usart1Transmit;
		stm32446.usart1.receive = STM32446Usart1Receive;
		stm32446.usart1.stop = STM32446Usart1Stop;
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
	stm32446.func.ftoa = STM32446FUNCftoa;
	stm32446.func.print = STM32446FUNCprint;
	stm32446.func.regsetbits = STM32446RegSetBits;
	stm32446.func.regresetbits = STM32446RegResetBits;
	stm32446.func.regsetup = STM32446RegSetup;
	stm32446.func.vecsetup = STM32446VecSetup;
	
	SystickInic(); // Polling delay source.

	return stm32446;
}

void STM32446Prescaler(unsigned int ahbpre, unsigned int ppre1, unsigned int ppre2, unsigned int rtcpre)
{
	const unsigned int mask = 0x001FFCF0;
	RCC->CFGR &= (unsigned int) ~mask; // clear args

	if(rtcpre > 1 && rtcpre < 32) // 16
		RCC->CFGR |= (rtcpre << 16);

	switch(ppre2){ // 13
		case 2:
			RCC->CFGR |= (4 << 13);
			stm32446.query.CLOCK_prescaler.APB2 = 2;
		break;
		case 4:
			RCC->CFGR |= (5 << 13);
			stm32446.query.CLOCK_prescaler.APB2 = 4;
		break;
		case 8:
			RCC->CFGR |= (6 << 13);
			stm32446.query.CLOCK_prescaler.APB2 = 8;
		break;
		case 16:
			RCC->CFGR |= (7 << 13);
			stm32446.query.CLOCK_prescaler.APB2 = 16;
		break;
		default:
			stm32446.query.CLOCK_prescaler.APB2 = 1;
		break;
	}

	switch(ppre1){ // 10
	case 2:
		RCC->CFGR |= (4 << 10);
		stm32446.query.CLOCK_prescaler.APB1 = 2;
	break;
	case 4:
		RCC->CFGR |= (5 << 10);
		stm32446.query.CLOCK_prescaler.APB1 = 4;
	break;
	case 8:
		RCC->CFGR |= (6 << 10);
		stm32446.query.CLOCK_prescaler.APB1 = 8;
	break;
	case 16:
		RCC->CFGR |= (7 << 10);
		stm32446.query.CLOCK_prescaler.APB1 = 16;
	break;
	default:
		stm32446.query.CLOCK_prescaler.APB1 = 1;
	break;
	}

	switch(ahbpre){ // 4
	case 2:
		RCC->CFGR |= (8 << 4);
		stm32446.query.CLOCK_prescaler.AHB = 2;
	break;
	case 4:
		RCC->CFGR |= (9 << 4);
		stm32446.query.CLOCK_prescaler.AHB = 4;
	break;
	case 8:
		RCC->CFGR |= (10 << 4);
		stm32446.query.CLOCK_prescaler.AHB = 8;
	break;
	case 16:
		RCC->CFGR |= (11 << 4);
		stm32446.query.CLOCK_prescaler.AHB = 16;
	break;
	case 64:
		RCC->CFGR |= (12 << 4);
		stm32446.query.CLOCK_prescaler.AHB = 64;
	break;
	case 128:
		RCC->CFGR |= (13 << 4);
		stm32446.query.CLOCK_prescaler.AHB = 128;
	break;
	case 256:
		RCC->CFGR |= (14 << 4);
		stm32446.query.CLOCK_prescaler.AHB = 256;
	break;
	case 512:
		RCC->CFGR |= (15 << 4);
		stm32446.query.CLOCK_prescaler.AHB = 512;
	break;
	default:
		stm32446.query.CLOCK_prescaler.AHB = 1;
	break;
	}
}

// PLL
void STM32446PLLDivision(unsigned int pllsrc, unsigned int pllm, unsigned int plln, unsigned int pllp, unsigned int pllq, unsigned int pllr)
{
	const unsigned int mask = 0x7F437FFF;
	RCC->PLLCFGR &= (unsigned int) ~mask; // set mask bits LOW


	if(pllr > 1 && pllr < 8){ // PLLR[28]: Main PLL division factor for I2Ss, SAIs, SYSTEM and SPDIF-Rx clocks
		RCC->PLLCFGR |= (pllr << 28);
		stm32446.query.PLL_parameter.R = pllr;
	}

	if(pllq > 1 && pllq < 16){ // PLLQ[24]: Main PLL (PLL) division factor for USB OTG FS, SDIOclocks
		RCC->PLLCFGR |= (pllq << 24);
		stm32446.query.PLL_parameter.Q = pllq;
	}

	if(pllsrc == 1){ // PLLSRC[22]: Main PLL(PLL) and audio PLL (PLLI2S) entry clock source
		stm32446.query.PLL_parameter.Source = 25000000;
		RCC->PLLCFGR |= (1 << 22);
	}else{
		stm32446.query.PLL_parameter.Source = 16000000;
	}

	switch(pllp){ // PLLP[16]: Main PLL (PLL) division factor for main system clock
		case 2:
			stm32446.query.PLL_parameter.P = pllp;
		break;
		case 4:
			RCC->PLLCFGR |= (1 << 16);
			stm32446.query.PLL_parameter.P = pllp;
		break;
		case 6:
			RCC->PLLCFGR |= (2 << 16);
			stm32446.query.PLL_parameter.P = pllp;
		break;
		case 8:
			RCC->PLLCFGR |= (3 << 16);
			stm32446.query.PLL_parameter.P = pllp;
		break;
		default:
			RCC->PLLCFGR |= (1 << 16);
			stm32446.query.PLL_parameter.P = 4;
		break;
	}

	if(plln > 49 && plln < 433){ // PLLN[6]: Main PLL (PLL) multiplication factor for VCO
		RCC->PLLCFGR |= (plln << 6);
		stm32446.query.PLL_parameter.N = plln;
	}

	if(pllm > 1 && pllm < 64){ // PLLM[0]: Division factor for the main PLL (PLL) input clock [2Mhz]
		RCC->PLLCFGR |= pllm;
		stm32446.query.PLL_parameter.M = pllm;
	}
}

uint32_t SystemClock(void) // Query
{
	uint32_t sysclk;
	switch((RCC->CFGR >> 2) & 3) // SWS[2]: System clock switch status
	{
		case 0: // 00: HSI oscillator used as the system clock
			stm32446.query.PLL_parameter.Source = 16000000;
			sysclk= 16000000;
		break;
		case 1: // 01: HSE oscillator used as the system clock
			stm32446.query.PLL_parameter.Source = 25000000;
			sysclk = 25000000;
		break;
		case 2: // 10: PLL used as the system clock
			sysclk = ( stm32446.query.PLL_parameter.Source / stm32446.query.PLL_parameter.M ) * ( stm32446.query.PLL_parameter.N / stm32446.query.PLL_parameter.P );
		break;
		case 3: // 11: PLL_R used as the system clock
			sysclk = ( stm32446.query.PLL_parameter.Source / stm32446.query.PLL_parameter.M ) * ( stm32446.query.PLL_parameter.N / stm32446.query.PLL_parameter.R );
		break;
		default:
		break;
	}
	stm32446.query.sysclk = sysclk;
	return sysclk;
}

// SYSCFG
void STM32446SysCfgEnable(void)
{
	RCC->APB2ENR |= (1 << 14); //syscfg clock enable
}

// SRAM
void STM32446SramAccess(void)
{
	// RM0390 pg 94
	// SRAM access
	// 0 - Power Up SRAM
	PWR->CSR |= (1 << 9); // BRE: Backup regulator enable
	// Check ready flag Bit 3 BRR: Backup regulator ready
	for( ; !(PWR->CSR & (1 << 3) )  ; ); // BRR: Backup regulator ready

	// 1 - Enable the power interface clock by setting the PWREN bits in the RCC_APB1ENR
	RCC->APB1ENR |= (1 << 28); // Power interface clock enable
	//RCC->APB1ENR |= ((1 << 11) | (1 << 28));

	// 2 - Set the DBP bit in the PWR power control register (PWR_CR)
	PWR->CR |= (1 << 8); // Disable backup domain write protection

	// 3 - Enable the backup SRAM clock by setting BKPSRAMEN bit in the RCC_AHB1ENR
	RCC->AHB1ENR |= (1 << 18); // BKPSRAMEN: Backup SRAM interface clock enable
}

/*** MISCELLANEOUS ***/
// Regs
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

void STM32446RegSetup( volatile uint32_t* reg, unsigned int size_block, unsigned int data, unsigned int bit )
{
	unsigned int mask = (unsigned int)(pow(2, size_block) - 1);
	unsigned int location = bit * size_block;
	data &= mask;
	*reg &= ~(mask << location);
	*reg |= (data << location);
}

/*** Version 2
void STM32446RegSetup( volatile uint32_t* reg, uint32_t size_block, uint32_t data, uint32_t bit )
{
	uint32_t mask = (uint32_t)(pow(2, size_block) - 1);
	uint32_t location = bit * size_block;
	data &= mask;
	*reg |= (mask << location);
	*reg &= (data << location) | ~(mask << location);
}
***/

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

/*** SYSTICK ***/
void SystickInic(void)
{
	SysTick->LOAD = (uint32_t)(SystemClock() - 1);
	SysTick->VAL = 0UL;
	SysTick->CTRL |= ((1 << 1) | (1 << 2));
}

void STM32446delay_ms(uint32_t ms)
{
	SysTick->LOAD = (uint32_t)((SystemClock() / 1000) - 1);
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
	SysTick->LOAD = (uint32_t)((SystemClock() / 100000) - 1);
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
	SysTick->LOAD = (uint32_t)((SystemClock() / 1000000) - 1);
	// Enable the SysTick timer
	SysTick->CTRL |= (1 << 0);
	// Wait for a specified number of milliseconds
	DelayCounter = 0;
	while (DelayCounter < us);
	// Disable the SysTick timer
	SysTick->CTRL &= (uint32_t) ~(1 << 0);
}

/*** File Interrupt ***/
void SysTick_Handler(void)
{ // count down to zero systick interrupt and reload.
	DelayCounter++;
}

/***EOF***/

/***
 * Library Scope
 * File Scope
 * Function Scope
 * Precedence Scope
 *
 * */


