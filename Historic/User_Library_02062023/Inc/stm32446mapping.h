/******************************************************************************
	STM32 446 MAPPING
Author: Sergio Manuel Santos
	<sergio.salazar.santos@gmail.com>
License: GNU General Public License
Hardware: STM32-446
Date: 28052023
Comment:
	-manual um1724, m0390, pm0056, pm0214, and other sources.
	-Virtual Image STM32-446, mapping.
	-Still in progress 03082022, increment has go along.
	-Stable.
	-Dependent on CMSIS
*******************************************************************************/
#ifndef _STM32446MAPPING_H_
	#define _STM32446MAPPING_H_

/*** Global Libraries ***/
#include <inttypes.h>
// SELECTION OF CHIP (CMSIS Access to its libraries)
#ifndef STM32F446xx
	#define STM32F446xx
#endif
#include "stm32f4xx.h"
#include "stm32446common.h"

/*** Define & Macros***/
#define HSI_RC 16000000UL
#define HSE_OSC 25000000UL

/*** Module Library ***/
// Comment out modules not being used
#include "stm32446rcc.h"
#include "stm32446gpio.h"
#include "stm32446adc.h"
#include "stm32446rtc.h"
#include "stm32446usart.h"
#include "stm32446tim.h"

/************ STM32F446RE ************/
/************ CORE ************/
// SCB
typedef struct
{
	SCB_Type* reg;
}STM32446SCBobj;

// NVIC
typedef struct
{
	NVIC_Type* reg;
}STM32446NVICobj;

// SysTick
typedef struct
{
	SysTick_Type* reg;
	void (*delay_ms)(uint32_t ms); // It uses Systick
	void (*delay_10us)(uint32_t ten_us); // It uses Systick
	void (*delay_us)(uint32_t us);
}STM32446SysTickobj;

/************ MCU ************/
// ADC -> ADC1
typedef struct
{
	ADC_TypeDef* reg;
	STM32446ADCCOMMONobj common;
	#if defined(_STM32446ADC_H_)
		STM32446ADC1 (*enable)(void);
		STM32446ADC1single single;
		void (*clock)(void);
	#endif
}STM32446ADC1obj;

// ADC -> ADC2
typedef struct
{
	ADC_TypeDef* reg;
	STM32446ADCCOMMONobj common;
	#if defined(_STM32446ADC_H_)
		void (*enable)(void);
	#endif
}STM32446ADC2obj;

// ADC -> ADC3
typedef struct
{
	ADC_TypeDef* reg;
	STM32446ADCCOMMONobj common;
	#if defined(_STM32446ADC_H_)
		void (*enable)(void);
	#endif
}STM32446ADC3obj;

// CAN_TxMailBox
typedef struct
{
	CAN_TxMailBox_TypeDef* reg;
}STM32446CAN_TxMailBoxobj;

// CAN_FIFOMailBox
typedef struct
{
	CAN_FIFOMailBox_TypeDef* reg;
}STM32446CAN_FIFOMailBoxobj;

// CAN_FilterRegister
typedef struct
{
	CAN_FilterRegister_TypeDef* reg;
}STM32446CAN_FilterRegisterobj;

// CAN -> CAN1
typedef struct
{
	CAN_TypeDef* reg;
}STM32446CAN1obj;

// CAN -> CAN2
typedef struct
{
	CAN_TypeDef* reg;
}STM32446CAN2obj;

// CEC
typedef struct
{
	CEC_TypeDef* reg;
}STM32446CECobj;

// CRC
typedef struct
{
	CRC_TypeDef* reg;
}STM32446CRCobj;

// DAC
typedef struct
{
	DAC_TypeDef* reg;
}STM32446DACobj;

// DBGMCU
typedef struct
{
	DBGMCU_TypeDef* reg;
}STM32446DBGMCUobj;

// DCMI
typedef struct
{
	DCMI_TypeDef* reg;
}STM32446DCMIobj;

// DMA_Stream
typedef struct
{
	DMA_Stream_TypeDef* reg;
}STM32446DMAStream;

// DMA -> DMA1
typedef struct
{
	DMA_TypeDef* reg;
	STM32446DMAStream stream[8];
}STM32446DMA1obj;

// DMA -> DMA2
typedef struct
{
	DMA_TypeDef* reg;
	STM32446DMAStream stream[8];
}STM32446DMA2obj;

// EXTI
typedef struct
{
	EXTI_TypeDef* reg;
}STM32446EXTIobj;

// FLASH
typedef struct
{
	FLASH_TypeDef* reg;
}STM32446FLASHobj;

// FMC_Bank1
typedef struct
{
	FMC_Bank1_TypeDef* reg;
}STM32446FMC_Bank1obj;

// FMC_Bank1E
typedef struct
{
	FMC_Bank1E_TypeDef* reg;
}STM32446FMC_Bank1Eobj;

// FMC_Bank3
typedef struct
{
	FMC_Bank3_TypeDef* reg;
}STM32446FMC_Bank3obj;

// FMC_Bank5_6
typedef struct
{
	FMC_Bank5_6_TypeDef* reg;
}STM32446FMC_Bank5_6obj;

// GPIO -> GPIOA
typedef struct
{
	GPIO_TypeDef* reg;
	#if defined(_STM32446GPIO_H_)
		STM32446GPIOA (*enable)(void);
		void (*clock)(void);
		void (*moder)( unsigned int data, unsigned int pin );
		void (*ospeedr)( unsigned int data, unsigned int pin );
		void (*pupdr)( unsigned int data, unsigned int pin );
		void (*afr)( unsigned int data, unsigned int pin );
		void (*reset)( unsigned int data );
		void (*set)( unsigned int data );
	#endif
}STM32446GpioAobj;

// GPIO -> GPIOB
typedef struct
{
	GPIO_TypeDef* reg;
	#if defined(_STM32446GPIO_H_)
		STM32446GPIOB (*enable)(void);
		void (*clock)(void);
		void (*moder)( unsigned int data, unsigned int pin );
		void (*ospeedr)( unsigned int data, unsigned int pin );
		void (*pupdr)( unsigned int data, unsigned int pin );
		void (*afr)( unsigned int data, unsigned int pin );
		void (*reset)( unsigned int data );
		void (*set)( unsigned int data );
	#endif
}STM32446GpioBobj;

// GPIO -> GPIOC
typedef struct
{
	GPIO_TypeDef* reg;
	#if defined(_STM32446GPIO_H_)
		STM32446GPIOC (*enable)(void);
		void (*clock)(void);
		void (*moder)( unsigned int data, unsigned int pin );
		void (*ospeedr)( unsigned int data, unsigned int pin );
		void (*pupdr)( unsigned int data, unsigned int pin );
		void (*afr)( unsigned int data, unsigned int pin );
		void (*reset)( unsigned int data );
		void (*set)( unsigned int data );
	#endif
}STM32446GpioCobj;

// GPIO -> GPIOD
typedef struct
{
	GPIO_TypeDef* reg;
	#if defined(_STM32446GPIO_H_)
		STM32446GPIOD (*enable)(void);
		void (*clock)(void);
		void (*moder)( unsigned int data, unsigned int pin );
		void (*ospeedr)( unsigned int data, unsigned int pin );
		void (*pupdr)( unsigned int data, unsigned int pin );
		void (*afr)( unsigned int data, unsigned int pin );
		void (*reset)( unsigned int data );
		void (*set)( unsigned int data );
	#endif
}STM32446GpioDobj;

// GPIO -> GPIOE
typedef struct
{
	GPIO_TypeDef* reg;
	#if defined(_STM32446GPIO_H_)
		STM32446GPIOE (*enable)(void);
		void (*clock)(void);
		void (*moder)( unsigned int data, unsigned int pin );
		void (*ospeedr)( unsigned int data, unsigned int pin );
		void (*pupdr)( unsigned int data, unsigned int pin );
		void (*afr)( unsigned int data, unsigned int pin );
		void (*reset)( unsigned int data );
		void (*set)( unsigned int data );
	#endif
}STM32446GpioEobj;

// GPIO -> GPIOF
typedef struct
{
	GPIO_TypeDef* reg;
	#if defined(_STM32446GPIO_H_)
		STM32446GPIOF (*enable)(void);
		void (*clock)(void);
		void (*moder)( unsigned int data, unsigned int pin );
		void (*ospeedr)( unsigned int data, unsigned int pin );
		void (*pupdr)( unsigned int data, unsigned int pin );
		void (*afr)( unsigned int data, unsigned int pin );
		void (*reset)( unsigned int data );
		void (*set)( unsigned int data );
	#endif
}STM32446GpioFobj;

// GPIO -> GPIOG
typedef struct
{
	GPIO_TypeDef* reg;
	#if defined(_STM32446GPIO_H_)
		STM32446GPIOG (*enable)(void);
		void (*clock)(void);
		void (*moder)( unsigned int data, unsigned int pin );
		void (*ospeedr)( unsigned int data, unsigned int pin );
		void (*pupdr)( unsigned int data, unsigned int pin );
		void (*afr)( unsigned int data, unsigned int pin );
		void (*reset)( unsigned int data );
		void (*set)( unsigned int data );
	#endif
}STM32446GpioGobj;

// GPIO -> GPIOH
typedef struct
{
	GPIO_TypeDef* reg;
	#if defined(_STM32446GPIO_H_)
		STM32446GPIOH (*enable)(void);
		void (*clock)(void);
		void (*moder)( unsigned int data, unsigned int pin );
		void (*ospeedr)( unsigned int data, unsigned int pin );
		void (*pupdr)( unsigned int data, unsigned int pin );
		void (*afr)( unsigned int data, unsigned int pin );
		void (*reset)( unsigned int data );
		void (*set)( unsigned int data );
	#endif
}STM32446GpioHobj;

// SYSCFG
typedef struct
{
	SYSCFG_TypeDef* reg;
	void (*enable)(void);
}STM32446SYSCFGobj;

// I2C -> I2C1
typedef struct
{
	I2C_TypeDef* reg;
}STM32446I2C1obj;

// I2C -> I2C2
typedef struct
{
	I2C_TypeDef* reg;
}STM32446I2C2obj;

// I2C -> I2C3
typedef struct
{
	I2C_TypeDef* reg;
}STM32446I2C3obj;

// FMPI2C
typedef struct
{
	FMPI2C_TypeDef* reg;
}STM32446FMPI2Cobj;

// IWDG
typedef struct
{
	IWDG_TypeDef* reg;
}STM32446IWDGobj;

// PWR
typedef struct
{
	PWR_TypeDef* reg;
}STM32446PWRobj;

// RCC
typedef struct
{
	RCC_TypeDef* reg;
	#if defined(_STM32446RCC_H_)
		STM32446RCC (*enable)(void);
		void (*henable)(unsigned int hclock);
		uint8_t (*hselect)(uint8_t sysclk);
		void (*lenable)(unsigned int lclock);
		void (*lselect)(uint8_t lclock);
		void (*prescaler)(unsigned int ahbpre, unsigned int ppre1, unsigned int ppre2, unsigned int rtcpre);
		STM32446RCCPLL pll;
		STM32446RCCPLLI2S plli2s;
		STM32446RCCPLLSAI pllsai;
	#endif
}STM32446RCCobj;

// RTC
typedef struct
{
	RTC_TypeDef* reg;
	#if defined(_STM32446RTC_H_)
		STM32446RTC (*enable)(void);
		void (*clock)(void);
		uint8_t (*inic)(uint8_t clock);
		void (*Day)(uint8_t day);
		void (*Month)(uint8_t month);
		void (*WeekDay)(uint8_t weekday);
		void (*Year)(uint8_t year);
		void (*Hour)(uint8_t hour);
		void (*Minute)(uint8_t minute);
		void (*Second)(uint8_t second);
		void (*dr2vec)(char* rtc_vect);
		void (*tr2vec)(char* rtc_vect);
		void (*RegWrite)(volatile uint32_t* reg, uint32_t data);
	#endif
}STM32446RTCobj;

// SAI -> SAI1
typedef struct
{
	SAI_TypeDef* reg;
}STM32446SAI1obj;

// SAI1_Block -> SAI1_BlockA
typedef struct
{
	SAI_Block_TypeDef* reg;
}STM32446SAI1_BlockAobj;

// SAI1_Block -> SAI1_BlockB
typedef struct
{
	SAI_Block_TypeDef* reg;
}STM32446SAI1_BlockBobj;

// SAI -> SAI2
typedef struct
{
	SAI_TypeDef* reg;
}STM32446SAI2obj;

// SAI2_Block -> SAI2_BlockA
typedef struct
{
	SAI_Block_TypeDef* reg;
}STM32446SAI2_BlockAobj;

// SAI2_Block -> SAI2_BlockB
typedef struct
{
	SAI_Block_TypeDef* reg;
}STM32446SAI2_BlockBobj;

// SDIO
typedef struct
{
	SDIO_TypeDef* reg;
}STM32446SDIOobj;

// SPI -> SPI1
typedef struct
{
	SPI_TypeDef* reg;
}STM32446SPI1obj;

// SPI -> SPI2
typedef struct
{
	SPI_TypeDef* reg;
}STM32446SPI2obj;

// SPI -> SPI3
typedef struct
{
	SPI_TypeDef* reg;
}STM32446SPI3obj;

// SPI -> SPI4
typedef struct
{
	SPI_TypeDef* reg;
}STM32446SPI4obj;

// QUADSPI
typedef struct
{
	QUADSPI_TypeDef* reg;
}STM32446QUADSPIobj;

// SPDIFRX
typedef struct
{
	SPDIFRX_TypeDef* reg;
}STM32446SPDIFRXobj;

// TIM -> TIM1
typedef struct
{
	TIM_TypeDef* reg;
	#if defined(_STM32446TIM_H_)
		void (*enable)(void);
	#endif
}STM32446TIM1obj;

// TIM -> TIM2
typedef struct
{
	TIM_TypeDef* reg;
	#if defined(_STM32446TIM_H_)
		void (*enable)(void);
	#endif
}STM32446TIM2obj;

// TIM -> TIM3
typedef struct
{
	TIM_TypeDef* reg;
	#if defined(_STM32446TIM_H_)
		void (*enable)(void);
	#endif
}STM32446TIM3obj;

// TIM -> TIM4
typedef struct
{
	TIM_TypeDef* reg;
	#if defined(_STM32446TIM_H_)
		void (*enable)(void);
	#endif
}STM32446TIM4obj;

// TIM -> TIM5
typedef struct
{
	TIM_TypeDef* reg;
	#if defined(_STM32446TIM_H_)
		void (*enable)(void);
	#endif
}STM32446TIM5obj;

// TIM -> TIM6
typedef struct
{
	TIM_TypeDef* reg;
	#if defined(_STM32446TIM_H_)
		void (*enable)(void);
	#endif
}STM32446TIM6obj;

// TIM -> TIM7
typedef struct
{
	TIM_TypeDef* reg;
	#if defined(_STM32446TIM_H_)
		void (*enable)(void);
	#endif
}STM32446TIM7obj;

// TIM -> TIM8
typedef struct
{
	TIM_TypeDef* reg;
	#if defined(_STM32446TIM_H_)
		void (*enable)(void);
	#endif
}STM32446TIM8obj;

// TIM -> TIM9
typedef struct
{
	TIM_TypeDef* reg;
	#if defined(_STM32446TIM_H_)
		STM32446TIM9 (*enable)(void);
		STM32446TIM9_CR1 cr1;
		STM32446TIM9_SMCR smcr;
		STM32446TIM9_DIER dier;
		STM32446TIM9_SR sr;
		STM32446TIM9_EGR egr;
		STM32446TIM9_CCMR1 ccmr1;
		STM32446TIM9_CCER ccer;
		void (*cnt)(uint16_t value);
		uint16_t (*get_cnt)(void);
		void (*arr)(uint16_t value);
		void (*ccr1)(uint16_t value);
		void (*ccr2)(uint16_t value);
		void (*psc)(uint16_t value);
		void (*clock)(void);
		void (*inic)(void);
		void (*nvict1t9)(void);
	#endif
}STM32446TIM9obj;

// TIM -> TIM10
typedef struct
{
	TIM_TypeDef* reg;
	#if defined(_STM32446TIM_H_)
		void (*enable)(void);
	#endif
}STM32446TIM10obj;

// TIM -> TIM11
typedef struct
{
	TIM_TypeDef* reg;
	#if defined(_STM32446TIM_H_)
		void (*enable)(void);
	#endif
}STM32446TIM11obj;

// TIM -> TIM12
typedef struct
{
	TIM_TypeDef* reg;
	#if defined(_STM32446TIM_H_)
		void (*enable)(void);
	#endif
}STM32446TIM12obj;

// TIM -> TIM13
typedef struct
{
	TIM_TypeDef* reg;
	#if defined(_STM32446TIM_H_)
		void (*enable)(void);
	#endif
}STM32446TIM13obj;

// TIM -> TIM14
typedef struct
{
	TIM_TypeDef* reg;
	#if defined(_STM32446TIM_H_)
		void (*enable)(void);
	#endif
}STM32446TIM14obj;

// USART -> USART1
typedef struct
{
	USART_TypeDef* reg;
	#if defined(_STM32446USART_H_)
		STM32446USART1_SR sr;
		STM32446USART1_BRR brr;
		STM32446USART1_CR1 cr1;
		STM32446USART1_CR2 cr2;
		STM32446USART1_CR3 cr3;
		STM32446USART1_GTPR gtpr;
		void (*dr)(uint16_t);
		uint16_t (*get_dr)(void);
		// Other
		STM32446USART1 (*enable)(void);
		void (*clock)(void);
		void (*inic)( uint8_t wordlength, uint8_t samplingmode, double stopbits, uint32_t baudrate );
		void (*transmit)(void);
		void (*receive)(void);
		void (*stop)(void);
	#endif
}STM32446USART1obj;

// USART -> USART2
typedef struct
{
	USART_TypeDef* reg;
	#if defined(_STM32446USART_H_)
		void (*enable)(void);
	#endif
}STM32446USART2obj;

// USART -> USART3
typedef struct
{
	USART_TypeDef* reg;
	#if defined(_STM32446USART_H_)
		void (*enable)(void);
	#endif
}STM32446USART3obj;

// USART -> USART4
typedef struct
{
	USART_TypeDef* reg;
	#if defined(_STM32446USART_H_)
		void (*enable)(void);
	#endif
}STM32446USART4obj;

// USART -> USART5
typedef struct
{
	USART_TypeDef* reg;
	#if defined(_STM32446USART_H_)
		void (*enable)(void);
	#endif
}STM32446USART5obj;

// USART -> USART6
typedef struct
{
	USART_TypeDef* reg;
	#if defined(_STM32446USART_H_)
		void (*enable)(void);
	#endif
}STM32446USART6obj;

// WWDG
typedef struct
{
	WWDG_TypeDef* reg;
}STM32446WWDGobj;

// USB_OTG_Global
typedef struct
{
	USB_OTG_GlobalTypeDef* reg;
}STM32446USB_OTG_Globalobj;

// USB_OTG_Device
typedef struct
{
	USB_OTG_DeviceTypeDef* reg;
}STM32446USB_OTG_Deviceobj;

// USB_OTG_INEndpoint
typedef struct
{
	USB_OTG_INEndpointTypeDef* reg;
}STM32446USB_OTG_INEndpointobj;

// USB_OTG_OUTEndpoint
typedef struct
{
	USB_OTG_OUTEndpointTypeDef* reg;
}STM32446USB_OTG_OUTEndpointobj;

// USB_OTG_Host
typedef struct
{
	USB_OTG_HostTypeDef* reg;
}STM32446USB_OTG_Hostobj;

// USB_OTG_HostChannel
typedef struct
{
	USB_OTG_HostChannelTypeDef* reg;
}STM32446USB_OTG_HostChannelobj;

/***  MISCELLANEOUS ***/
// FUNC
typedef struct
{
	char (*bcd2dec)(char num);
	char (*dec2bcd)(char num);
	uint32_t (*triggerA)(uint32_t hllh_io, uint8_t pin, uint32_t counter);
	uint32_t (*triggerB)(uint32_t hl_io, uint32_t lh_io, uint8_t pin, uint32_t counter);
	uint16_t (*ReadHLByte)(STM32HighLowByte reg);
	uint16_t (*ReadLHByte)(STM32HighLowByte reg);
	STM32HighLowByte (*WriteHLByte)(uint16_t val);
	STM32HighLowByte (*WriteLHByte)(uint16_t val);
	uint16_t (*SwapByte)(uint16_t num);
	char* (*ftoa)(double num, char* res, uint8_t afterpoint);
	char* (*print)( char* str, uint8_t size_str, const char* format, ... );
	void (*regsetbits)( unsigned int* reg, int n_bits, ... );
	void (*regresetbits)( unsigned int* reg, int n_bits, ... );
	void (*vecsetup)( volatile uint32_t vec[], const unsigned int size_block, unsigned int data, unsigned int block_n );
	uint32_t (*getbit)(uint32_t reg, uint32_t size_block, uint32_t bit);
	void (*setbit)(volatile uint32_t* reg, uint32_t size_block, uint32_t bit, uint32_t data);
}STM32446_function;

/*** STM32F446 ***/
typedef struct
{
	// PARAMETER
	STM32HighLowByte HLbyte;
	STM32446Query query;
	// CORE
	STM32446SCBobj scb;
	STM32446NVICobj nvic;
	STM32446SysTickobj systick;
	// MCU
	STM32446ADC1obj adc1;
	STM32446ADC2obj adc2;
	STM32446ADC3obj adc3;
	STM32446CRCobj crc;
	STM32446DMA1obj dma1;
	STM32446DMA2obj dma2;
	STM32446FLASHobj flash;
	STM32446GpioAobj gpioa;
	STM32446GpioBobj gpiob;
	STM32446GpioCobj gpioc;
	STM32446GpioDobj gpiod;
	STM32446GpioEobj gpioe;
	STM32446GpioFobj gpiof;
	STM32446GpioGobj gpiog;
	STM32446GpioHobj gpioh;
	STM32446SYSCFGobj syscfg;
	STM32446PWRobj pwr;
	STM32446RCCobj rcc;
	STM32446RTCobj rtc;
	STM32446TIM1obj tim1;
	STM32446TIM2obj tim2;
	STM32446TIM3obj tim3;
	STM32446TIM4obj tim4;
	STM32446TIM5obj tim5;
	STM32446TIM6obj tim6;
	STM32446TIM7obj tim7;
	STM32446TIM8obj tim8;
	STM32446TIM9obj tim9;
	STM32446TIM10obj tim10;
	STM32446TIM11obj tim11;
	STM32446TIM12obj tim12;
	STM32446TIM13obj tim13;
	STM32446TIM14obj tim14;
	STM32446USART1obj usart1;
	STM32446USART2obj usart2;
	STM32446USART3obj usart3;
	STM32446USART4obj usart4;
	STM32446USART5obj usart5;
	STM32446USART6obj usart6;
	//FUNCTION
	STM32446_function func;
}STM32446;

STM32446 STM32446enable(void);

#endif

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

Make more query functions into the system especially about the clock and pll, so it can be reached threw out all the code.
******/


