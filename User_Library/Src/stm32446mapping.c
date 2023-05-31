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
/*** TOP ***/
uint32_t STM32446_getbit(uint32_t reg, uint32_t size_block, uint32_t bit);
void STM32446_setbit(volatile uint32_t* reg, uint32_t size_block, uint32_t bit, uint32_t data);

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

// QUERY CLOCK
uint32_t STM32446_getclocksource(void);
uint32_t STM32446_getsysclk(void);
uint32_t STM32446_pllsource(void);
uint32_t STM32446_gethpre(void);
uint32_t STM32446_gethppre1(void);
uint32_t STM32446_gethppre2(void);
uint32_t STM32446_getrtcpre(void);
uint32_t STM32446_gethmco1pre(void);
uint32_t STM32446_gethmco2pre(void);
uint32_t STM32446_getpllm(void);
uint32_t STM32446_getplln(void);
uint32_t STM32446_getpllp(void);
uint32_t STM32446_getpllq(void);
uint32_t STM32446_getpllr(void);

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

/**** Procedure & Function Definition ***/
/******* STM32F446RE Image Linker *******/
STM32446 STM32446enable(void){
	/*** DEFAULT ***/
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
		// CLOCK
		stm32446.tim9.clock = STM32446Tim9Clock;
		// INIC
		stm32446.tim9.inic = STM32446Tim9Inic;
		// CR1
		stm32446.tim9.cr1.get_ckd = STM32446Tim9_get_ckd;
		stm32446.tim9.cr1.apre = STM32446Tim9_set_apre;
		stm32446.tim9.cr1.opm = STM32446Tim9_set_opm;
		stm32446.tim9.cr1.urs = STM32446Tim9_set_urs;
		stm32446.tim9.cr1.udis = STM32446Tim9_set_udis;
		stm32446.tim9.cr1.cen = STM32446Tim9_cen;
		// SMCR
		stm32446.tim9.smcr.msm = STM32446Tim9_msm;
		stm32446.tim9.smcr.ts = STM32446Tim9_ts;
		stm32446.tim9.smcr.sms = STM32446Tim9_sms;
		// DIER
		stm32446.tim9.dier.tie = STM32446Tim9_tie;
		stm32446.tim9.dier.cc2ie = STM32446Tim9_cc2ie;
		stm32446.tim9.dier.cc1ie = STM32446Tim9_cc1ie;
		stm32446.tim9.dier.uie = STM32446Tim9_uie;
		// SR
		stm32446.tim9.sr.cc2of = STM32446Tim9_cc2of;
		stm32446.tim9.sr.clear_cc2of = STM32446Tim9_clear_cc2of;
		stm32446.tim9.sr.cc1of = STM32446Tim9_cc1of;
		stm32446.tim9.sr.clear_cc1of = STM32446Tim9_clear_cc1of;
		stm32446.tim9.sr.tif = STM32446Tim9_tif;
		stm32446.tim9.sr.clear_tif = STM32446Tim9_clear_tif;
		stm32446.tim9.sr.cc2if = STM32446Tim9_cc2if;
		stm32446.tim9.sr.clear_cc2if = STM32446Tim9_clear_cc2if;
		stm32446.tim9.sr.cc1if = STM32446Tim9_cc1if;
		stm32446.tim9.sr.clear_cc1if = STM32446Tim9_clear_cc1if;
		stm32446.tim9.sr.uif = STM32446Tim9_uif;
		stm32446.tim9.sr.clear_uif = STM32446Tim9_clear_uif;
		// EGR
		stm32446.tim9.egr.tg = STM32446Tim9_tg;
		stm32446.tim9.egr.cc2g = STM32446Tim9_cc2g;
		stm32446.tim9.egr.cc1g = STM32446Tim9_cc1g;
		stm32446.tim9.egr.ug = STM32446Tim9_ug;
		// CCMR1
		stm32446.tim9.ccmr1.oc2m = STM32446Tim9_oc2m;
		stm32446.tim9.ccmr1.ic2f = STM32446Tim9_ic2f;
		stm32446.tim9.ccmr1.oc2pe = STM32446Tim9_oc2pe;
		stm32446.tim9.ccmr1.oc2fe = STM32446Tim9_oc2fe;
		stm32446.tim9.ccmr1.ic2psc = STM32446Tim9_ic2psc;
		stm32446.tim9.ccmr1.cc2s = STM32446Tim9_cc2s;
		stm32446.tim9.ccmr1.oc1m = STM32446Tim9_oc1m;
		stm32446.tim9.ccmr1.ic1f = STM32446Tim9_ic1f;
		stm32446.tim9.ccmr1.oc1pe = STM32446Tim9_oc1pe;
		stm32446.tim9.ccmr1.oc1fe = STM32446Tim9_oc1fe;
		stm32446.tim9.ccmr1.ic1psc = STM32446Tim9_ic1psc;
		stm32446.tim9.ccmr1.cc1s = STM32446Tim9_cc1s;
		// CCER
		stm32446.tim9.ccer.cc2np = STM32446Tim9_cc2np;
		stm32446.tim9.ccer.cc2p = STM32446Tim9_cc2p;
		stm32446.tim9.ccer.cc2e = STM32446Tim9_cc2e;
		stm32446.tim9.ccer.cc1np = STM32446Tim9_cc1np;
		stm32446.tim9.ccer.cc1p = STM32446Tim9_cc1p;
		stm32446.tim9.ccer.cc1e = STM32446Tim9_cc1e;
		// CNT
		stm32446.tim9.cnt = STM32446Tim9_cnt;
		stm32446.tim9.get_cnt = STM32446Tim9_get_cnt;
		// ARR
		stm32446.tim9.arr = STM32446Tim9_arr;
		// CCR1
		stm32446.tim9.ccr1 = STM32446Tim9_ccr1;
		// CCR2
		stm32446.tim9.ccr2 = STM32446Tim9_ccr2;
		// PSC
		stm32446.tim9.psc = STM32446Tim9_psc;
		// INIC
		stm32446.tim9.inic = STM32446Tim9Inic;
		// INTERRUPT
		stm32446.tim9.nvict1t9 = STM32446Tim9EnableInterrupt;
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
	stm32446.query.ClockSource = STM32446_getclocksource;
	stm32446.query.SystemClock = STM32446_getsysclk;
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
	stm32446.func.getbit = STM32446_getbit;
	stm32446.func.setbit = STM32446_setbit;
	
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
		break;
		case 4:
			RCC->CFGR |= (5 << 13);
		break;
		case 8:
			RCC->CFGR |= (6 << 13);
		break;
		case 16:
			RCC->CFGR |= (7 << 13);
		break;
		default:
		break;
	}

	switch(ppre1){ // 10
	case 2:
		RCC->CFGR |= (4 << 10);
	break;
	case 4:
		RCC->CFGR |= (5 << 10);
	break;
	case 8:
		RCC->CFGR |= (6 << 10);
	break;
	case 16:
		RCC->CFGR |= (7 << 10);
	break;
	default:
	break;
	}

	switch(ahbpre){ // 4
	case 2:
		RCC->CFGR |= (8 << 4);
	break;
	case 4:
		RCC->CFGR |= (9 << 4);
	break;
	case 8:
		RCC->CFGR |= (10 << 4);
	break;
	case 16:
		RCC->CFGR |= (11 << 4);
	break;
	case 64:
		RCC->CFGR |= (12 << 4);
	break;
	case 128:
		RCC->CFGR |= (13 << 4);
	break;
	case 256:
		RCC->CFGR |= (14 << 4);
	break;
	case 512:
		RCC->CFGR |= (15 << 4);
	break;
	default:
	break;
	}
}

// PLL
void STM32446PLLDivision(unsigned int pllsrc, unsigned int pllm, unsigned int plln, unsigned int pllp, unsigned int pllq, unsigned int pllr)
{
	const unsigned int mask = 0x7F437FFF;
	RCC->PLLCFGR &= (unsigned int) ~mask; // clear args


	if(pllr > 1 && pllr < 8){ // PLLR[28]: Main PLL division factor for I2Ss, SAIs, SYSTEM and SPDIF-Rx clocks
		RCC->PLLCFGR |= (pllr << 28);
	}

	if(pllq > 1 && pllq < 16){ // PLLQ[24]: Main PLL (PLL) division factor for USB OTG FS, SDIOclocks
		RCC->PLLCFGR |= (pllq << 24);
	}

	if(pllsrc == 1) // PLLSRC[22]: Main PLL(PLL) and audio PLL (PLLI2S) entry clock source
		RCC->PLLCFGR |= (1 << 22);

	switch(pllp){ // PLLP[16]: Main PLL (PLL) division factor for main system clock
		case 4:
			RCC->PLLCFGR |= (1 << 16);
		break;
		case 6:
			RCC->PLLCFGR |= (2 << 16);
		break;
		case 8:
			RCC->PLLCFGR |= (3 << 16);
		break;
		default:
		break;
	}

	if(plln > 49 && plln < 433){ // PLLN[6]: Main PLL (PLL) multiplication factor for VCO
		RCC->PLLCFGR |= (plln << 6);
	}

	if(pllm > 1 && pllm < 64){ // PLLM[0]: Division factor for the main PLL (PLL) input clock [2Mhz]
		RCC->PLLCFGR |= pllm;
	}
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

uint32_t STM32446_getclocksource(void)
{
	uint32_t reg = RCC->CR;
	uint32_t source;
	if(reg & (1 << 1)){source = HSI_RC;}else if(reg & (1 << 17)){source = HSE_OSC;}

	return source;
}

uint32_t STM32446_getsysclk(void)
{
	uint32_t value = STM32446_getbit(RCC->CFGR, 2, 2);

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

uint32_t STM32446_pllsource(void)
{
	uint32_t reg = RCC->CFGR;
	uint32_t source;

	if(reg & (1 << 22)) source = HSE_OSC; else source = HSI_RC;

	return source;
}

uint32_t STM32446_gethpre(void)
{
	uint32_t value = STM32446_getbit(RCC->CFGR, 4, 4);

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

uint32_t STM32446_gethppre1(void)
{
	uint32_t value = STM32446_getbit(RCC->CFGR, 3, 10);

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
		default:
			value = 1;
		break;
	}
	return value;
}

uint32_t STM32446_gethppre2(void)
{
	uint32_t value = STM32446_getbit(RCC->CFGR, 3, 13);

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
		default:
			value = 1;
		break;
	}
	return value;
}

uint32_t STM32446_getrtcpre(void)
{
	return STM32446_getbit(RCC->CFGR, 5, 16);
}

uint32_t STM32446_gethmco1pre(void)
{
	uint32_t value = STM32446_getbit(RCC->CFGR, 3, 24);

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
		default:
			value = 1;
		break;
	}
	return value;
}

uint32_t STM32446_gethmco2pre(void)
{
	uint32_t value = STM32446_getbit(RCC->CFGR, 3, 27);

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
		default:
			value = 1;
		break;
		}
	return value;
}

uint32_t STM32446_getpllm(void)
{
	return STM32446_getbit(RCC->PLLCFGR, 6, 0);
}

uint32_t STM32446_getplln(void)
{
	return STM32446_getbit(RCC->PLLCFGR, 9, 6);
}

uint32_t STM32446_getpllp(void)
{
	uint32_t value = STM32446_getbit(RCC->PLLCFGR, 2, 16);

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

uint32_t STM32446_getpllq(void)
{
	return STM32446_getbit(RCC->PLLCFGR, 4, 24);
}

uint32_t STM32446_getpllr(void)
{
	return STM32446_getbit(RCC->PLLCFGR, 3, 28);
}

uint32_t STM32446_getbit(uint32_t reg, uint32_t size_block, uint32_t bit)
{
	uint32_t value = 0; uint32_t tmp = 0;
	uint32_t mask = (unsigned int)((1 << size_block) - 1);
	mask = (mask << bit);
	tmp = mask & reg;
	value = (tmp >> bit);
	return value;
}

void STM32446_setbit(volatile uint32_t* reg, uint32_t size_block, uint32_t bit, uint32_t data)
{
	uint32_t value = 0;
	uint32_t mask = (unsigned int)((1 << size_block) - 1);
	value = data & mask;
	*reg &= ~(mask << bit);
	*reg |= (value << bit);
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

/*** SYSTICK ***/
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


