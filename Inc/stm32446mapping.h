/******************************************************************************
	STM32 446 MAPPING
Author: Sergio Manuel Santos
	<sergio.salazar.santos@gmail.com>
License: GNU General Public License
Hardware: STM32-446
Date: 20052023
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

/*** Module Library ***/
// Comment out modules not being used
#include "stm32446adc.h"
#include "stm32446rtc.h"
#include "stm32446usart.h"
#include "stm32446tim.h"

/***Global Define and Macros***/

/*** Global Variable ***/
// PARAMETER
typedef struct
{
	uint8_t L;
	uint8_t H;
} STM32HighLowByte;

// Low Word High Word
//typedef struct
//{
//	uint16_t H;
//	uint16_t L;
//}STM32446HighLowWord;

typedef struct
{
	uint16_t AHB;
	uint8_t APB1;
	uint8_t APB2;
}STM32446CLOCK_prescaler;

typedef struct
{
	uint32_t Source;
	uint8_t M;
	uint16_t N;
	uint8_t P;
	uint8_t Q;
	uint8_t R;
}STM32446PLL_parameter;

typedef struct
{
	uint32_t (*SystemClock)(void);
}STM32446Query;

/*** STM32F446RE ***/
/*** CORE ***/
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

/*** MCU ***/
// ADC_Common
typedef struct
{
	ADC_Common_TypeDef* reg;
}STM32446ADCCOMMONobj;

// ADC -> ADC1
typedef struct
{
	ADC_TypeDef* reg;
	STM32446ADCCOMMONobj common;
	#if defined(_STM32446ADC_H_)
		STM32446ADC1 (*enable)(void);
	#endif
}STM32446ADC1obj;

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

// CAN
typedef struct
{
	CAN_TypeDef* reg;
}STM32446CANobj;

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
	void (*enable)(void);
	void (*moder)( unsigned int data, unsigned int pin );
	void (*ospeedr)( unsigned int data, unsigned int pin );
	void (*pupdr)( unsigned int data, unsigned int pin );
	void (*afr)( unsigned int data, unsigned int pin );
	void (*reset)( unsigned int data );
	void (*set)( unsigned int data );
}STM32446GpioAobj;

// GPIO -> GPIOB
typedef struct
{
	GPIO_TypeDef* reg;
	void (*enable)(void);
	void (*moder)( unsigned int data, unsigned int pin );
	void (*ospeedr)( unsigned int data, unsigned int pin );
	void (*pupdr)( unsigned int data, unsigned int pin );
	void (*afr)( unsigned int data, unsigned int pin );
	void (*reset)( unsigned int data );
	void (*set)( unsigned int data );
}STM32446GpioBobj;

// GPIO -> GPIOC
typedef struct
{
	GPIO_TypeDef* reg;
	void (*enable)(void);
	void (*moder)( unsigned int data, unsigned int pin );
	void (*ospeedr)( unsigned int data, unsigned int pin );
	void (*pupdr)( unsigned int data, unsigned int pin );
	void (*afr)( unsigned int data, unsigned int pin );
	void (*reset)( unsigned int data );
	void (*set)( unsigned int data );
}STM32446GpioCobj;

// GPIO -> GPIOD
typedef struct
{
	GPIO_TypeDef* reg;
	void (*enable)(void);
	void (*moder)( unsigned int data, unsigned int pin );
	void (*ospeedr)( unsigned int data, unsigned int pin );
	void (*pupdr)( unsigned int data, unsigned int pin );
	void (*afr)( unsigned int data, unsigned int pin );
	void (*reset)( unsigned int data );
	void (*set)( unsigned int data );
}STM32446GpioDobj;

// GPIO -> GPIOE
typedef struct
{
	GPIO_TypeDef* reg;
	void (*enable)(void);
	void (*moder)( unsigned int data, unsigned int pin );
	void (*ospeedr)( unsigned int data, unsigned int pin );
	void (*pupdr)( unsigned int data, unsigned int pin );
	void (*afr)( unsigned int data, unsigned int pin );
	void (*reset)( unsigned int data );
	void (*set)( unsigned int data );
}STM32446GpioEobj;

// GPIO -> GPIOF
typedef struct
{
	GPIO_TypeDef* reg;
}STM32446GpioFobj;

// GPIO -> GPIOG
typedef struct
{
	GPIO_TypeDef* reg;
}STM32446GpioGobj;

// GPIO -> GPIOH
typedef struct
{
	GPIO_TypeDef* reg;
	void (*enable)(void);
	void (*moder)( unsigned int data, unsigned int pin );
	void (*ospeedr)( unsigned int data, unsigned int pin );
	void (*pupdr)( unsigned int data, unsigned int pin );
	void (*afr)( unsigned int data, unsigned int pin );
	void (*reset)( unsigned int data );
	void (*set)( unsigned int data );
}STM32446GpioHobj;

// SYSCFG
typedef struct
{
	SYSCFG_TypeDef* reg;
	void (*enable)(void);
}STM32446SYSCFGobj;

// I2C
typedef struct
{
	I2C_TypeDef* reg;
}STM32446I2Cobj;

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

// RCC -> PLL
typedef struct
{
	void (*division)(unsigned int pllsrc, unsigned int pllm, unsigned int plln, unsigned int pllp, unsigned int pllq, unsigned int pllr);
	void (*enable)(void);
}STM32446RCCPLL;

// RCC -> PLLI2S
typedef struct
{
	void (*enable)(void);
}STM32446RCCPLLI2S;

// RCC -> PLLSAI
typedef struct
{
	void (*enable)(void);
}STM32446RCCPLLSAI;

// RCC -> RCC
typedef struct
{
	RCC_TypeDef* reg;
	uint8_t (*inic)(void);
	void (*henable)(unsigned int hclock);
	uint8_t (*hselect)(uint8_t sysclk);
	void (*lenable)(unsigned int lclock);
	void (*lselect)(uint8_t lclock);
	void (*prescaler)(unsigned int ahbpre, unsigned int ppre1, unsigned int ppre2, unsigned int rtcpre);
	uint32_t (*systemclock)(void);
	STM32446RCCPLL pll;
	STM32446RCCPLLI2S plli2s;
	STM32446RCCPLLSAI pllsai;
}STM32446RCCobj;

// RTC
typedef struct
{
	RTC_TypeDef* reg;
	#if defined(_STM32446RTC_H_)
		STM32446RTC (*enable)(void);
	#endif
}STM32446RTCobj;

// SAI
typedef struct
{
	SAI_TypeDef* reg;
}STM32446SAIobj;

// SAI_Block
typedef struct
{
	SAI_Block_TypeDef* reg;
}STM32446SAI_Blockobj;

// SDIO
typedef struct
{
	SDIO_TypeDef* reg;
}STM32446SDIOobj;

// SPI
typedef struct
{
	SPI_TypeDef* reg;
}STM32446SPIobj;

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

// TIM -> TIM9
typedef struct
{
	TIM_TypeDef* reg;
	#if defined(_STM32446TIM_H_)
		STM32446TIM9 (*enable)(void);
	#endif
}STM32446TIM9obj;

// USART -> USART1
typedef struct
{
	USART_TypeDef* reg;
	#if defined(_STM32446USART_H_)
		STM32446USART1 (*enable)(void);
	#endif
}STM32446USART1obj;

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
// INIC
typedef struct
{
	void (*template)(void);
}STM32446_inic;

// ENABLE
typedef struct
{
	void (*template)(void);
}STM32446_enable;

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
	void (*setpins)( GPIO_TypeDef* regs, int n_pin, ... ); // BSRR
	void (*setpin)( GPIO_TypeDef* regs, int pin ); // BSRR
	void (*set)( GPIO_TypeDef* regs, int data ); // BSRR
	void (*resetpins)( GPIO_TypeDef* regs, int n_pin, ... ); // BSRR
	void (*resetpin)( GPIO_TypeDef* regs, int pin); // BSRR
	void (*reset)( GPIO_TypeDef* regs, int data); // BSRR
	void (*setupreg)(volatile uint32_t* reg, unsigned int size_block, unsigned int data, unsigned int pin); // GENERIC & |
	void (*pinblock)( volatile uint32_t* dest, uint32_t size_block, uint32_t data, uint32_t pin );
	void (*setup)( volatile uint32_t vec[], const unsigned int size_block, unsigned int data, unsigned int block_n ); // GENERIN [] & |
	char* (*ftoa)(double num, char* res, uint8_t afterpoint);
	char* (*print)( char* str, uint8_t size_str, const char* format, ... );
	void (*test)(void);
}STM32446_function;

/*** STM32F446RE IMAGE Linker ***/
typedef struct
{
	// PARAMETER
	STM32HighLowByte HLbyte;
	STM32446CLOCK_prescaler CLOCK_prescaler;
	STM32446PLL_parameter PLL_parameter;
	STM32446Query query;
	// CORE
	STM32446SCBobj scb;
	STM32446NVICobj nvic;
	STM32446SysTickobj systick;
	// MCU
	STM32446ADC1obj adc1;
	STM32446CRCobj crc;
	STM32446DMA1obj dma1;
	STM32446DMA2obj dma2;
	STM32446FLASHobj flash;
	STM32446GpioAobj gpioa;
	STM32446GpioBobj gpiob;
	STM32446GpioCobj gpioc;
	STM32446GpioDobj gpiod;
	STM32446GpioEobj gpioe;
	STM32446GpioHobj gpioh;
	STM32446SYSCFGobj syscfg;
	STM32446PWRobj pwr;
	STM32446RCCobj rcc;
	STM32446RTCobj rtc;
	STM32446TIM9obj tim9;
	STM32446USART1obj usart1;
	
	// INIC
	STM32446_inic inic;
	// ENABLE
	STM32446_enable enable;
	//FUNCTION
	STM32446_function func;
}STM32446;

/*** Global Procedure & Function ***/
STM32446 STM32446enable(void);

#endif
/***EOF***/


