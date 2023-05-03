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
#include "stm32446mapping.h"
#include <stdarg.h>
#include <math.h>
/*
*** Constant and Macros
*/
#define sperm ~0
#define ass (1)
#define tits (.|.)
#define cameltoe (\/)
/*
*** File Variable
*/
static STM32446 ret;
static volatile uint32_t DelayCounter;
static uint32_t STM32446TimeTr;
static uint32_t STM32446DateDr;
static volatile uint32_t mem[4];
static volatile uint32_t nen[4];
static double STM32446temperature;
/*
***Procedure and Functions Prototypes
*/
// SysTick
void SystickInic(void);

/***INIC***/
uint8_t STM32446PeripheralInic(void);

/***FUNC***/
//RCC
void STM32446RccHEnable(unsigned int hclock);
uint8_t STM32446RccHSelect(uint8_t sysclk);
void STM32446RccLEnable(unsigned int lclock);
void STM32446RccLSelect(uint8_t lclock);
void STM32446Prescaler(unsigned int ahbpre, unsigned int ppre1, unsigned int ppre2, unsigned int rtcpre);

/***PLL***/
void STM32446PLLDivision(unsigned int pllsrc, unsigned int pllm, unsigned int plln, unsigned int pllp, unsigned int pllq, unsigned int pllr);
void STM32446RccPLLCLKEnable(uint8_t onoff);
void STM32446RccPLLI2SEnable(uint8_t onoff);
void STM32446RccPLLSAIEnable(uint8_t onoff);

//GPIOA
void STM32446GpioAmoder( unsigned int data, unsigned int pin );
void STM32446GpioAospeedr( unsigned int data, unsigned int pin );
void STM32446GpioApupdr( unsigned int data, unsigned int pin );
void STM32446GpioAreset( unsigned int data );
void STM32446GpioAset( unsigned int data );
void STM32446GpioAafr( unsigned int data, unsigned int pin );

//GPIOB
void STM32446GpioBmoder( unsigned int data, unsigned int pin );
void STM32446GpioBospeedr( unsigned int data, unsigned int pin );
void STM32446GpioBpupdr( unsigned int data, unsigned int pin );
void STM32446GpioBreset( unsigned int data );
void STM32446GpioBset( unsigned int data );
void STM32446GpioBafr( unsigned int data, unsigned int pin );

//GPIOC
void STM32446GpioCmoder( unsigned int data, unsigned int pin );
void STM32446GpioCospeedr( unsigned int data, unsigned int pin );
void STM32446GpioCpupdr( unsigned int data, unsigned int pin );
void STM32446GpioCreset( unsigned int data );
void STM32446GpioCset( unsigned int data );
void STM32446GpioCafr( unsigned int data, unsigned int pin );

//GPIOD
void STM32446GpioDmoder( unsigned int data, unsigned int pin );
void STM32446GpioDospeedr( unsigned int data, unsigned int pin );
void STM32446GpioDpupdr( unsigned int data, unsigned int pin );
void STM32446GpioDreset( unsigned int data );
void STM32446GpioDset( unsigned int data );
void STM32446GpioDafr( unsigned int data, unsigned int pin );

//GPIOE
void STM32446GpioEmoder( unsigned int data, unsigned int pin );
void STM32446GpioEospeedr( unsigned int data, unsigned int pin );
void STM32446GpioEpupdr( unsigned int data, unsigned int pin );
void STM32446GpioEreset( unsigned int data );
void STM32446GpioEset( unsigned int data );
void STM32446GpioEafr( unsigned int data, unsigned int pin );

//GPIOH
void STM32446GpioHmoder( unsigned int data, unsigned int pin );
void STM32446GpioHospeedr( unsigned int data, unsigned int pin );
void STM32446GpioHpupdr( unsigned int data, unsigned int pin );
void STM32446GpioHreset( unsigned int data );
void STM32446GpioHset( unsigned int data );
void STM32446GpioHafr( unsigned int data, unsigned int pin );

// RTC
uint8_t STM32446RtcInic(uint8_t clock);
void STM32446RtcDay(uint8_t day);
void STM32446RtcMonth(uint8_t month);
void STM32446RtcWeekDay(uint8_t weekday);
void STM32446RtcYear(uint8_t year);
void STM32446RtcHour(uint8_t hour);
void STM32446RtcMinute(uint8_t minute);
void STM32446RtcSecond(uint8_t second);
void STM32446Rtcdr2vec(char* vect);
void STM32446Rtctr2vec(char* vect);
void STM32446RtcRegWrite(volatile uint32_t* reg, uint32_t data);

//ADC1
void STM32446Adc1Inic(void);
void STM32446Adc1VBAT(void);
void STM32446Adc1TEMP(void);
void STM32446Adc1Start(void);
double STM32446Adc1Read(void);
void STM32446Adc1Restart(void);
void STM32446Adc1Stop(void);

//USART1
void STM32446Usart1Inic( uint8_t wordlength, uint8_t samplingmode, double stopbits, uint32_t baudrate );
void STM32446Usart1Transmit(void);
void STM32446Usart1Receive(void);
void STM32446Usart1Parameters( uint8_t wordlength, uint8_t samplingmode, double stopbits, uint32_t baudrate );
void STM32446Usart1Stop(void);

// MISCELLANEOUS
char STM32446bcd2dec(char num);
char STM32446dec2bcd(char num);
/*** SYSTICK ***/
void STM32446delay_ms(uint32_t ms);
void STM32446delay_10us(uint32_t ten_us);
void STM32446delay_us(uint32_t us);
/*** BUTTON ***/
uint32_t STM32446triggerA(uint32_t hllh_io, uint8_t pin, uint32_t counter);
uint32_t STM32446triggerB(uint32_t hl_io, uint32_t lh_io, uint8_t pin, uint32_t counter);
/*** BYTE ***/
uint16_t STM32ReadHLByte(STM32HighLowByte reg);
uint16_t STM32ReadLHByte(STM32HighLowByte reg);
STM32HighLowByte STM32WriteHLByte(uint16_t val);
STM32HighLowByte STM32WriteLHByte(uint16_t val);
uint16_t STM32SwapByte(uint16_t num);
/*** GPIO ***/
void STM32446GpioSetpins( GPIO_TypeDef* regs, int n_pin, ... );
void STM32446GpioSetpin( GPIO_TypeDef* regs, int pin );
void STM32446GpioSet( GPIO_TypeDef* regs, int data );
void STM32446GpioResetpins( GPIO_TypeDef* regs, int n_pin, ... );
void STM32446GpioResetpin( GPIO_TypeDef* regs, int pin );
void STM32446GpioReset( GPIO_TypeDef* regs, int data );
/*** GENERIC ***/
void STM32446Gpiosetupreg(volatile uint32_t* reg, unsigned int size_block, unsigned int data, unsigned int pin);
void STM32446GpioSetup( volatile uint32_t vec[], const unsigned int size_block, unsigned int data, unsigned int block_n );

/***FILE FUNC***/
void STM32446RtcSetTr(void);
void STM32446RtcSetDr(void);
uint8_t STM32446RtcAccess(uint8_t clock);
void STM32446SramAccess(void);

// Template
void template(void);

/*
***Interrupt Prototype
*/

void SysTick_Handler(void);

/*
*** File Procedure and Functions
*/

// STM32446 Image Linker
STM32446 STM32446enable(void){
/******************************************************************************
	Comment out the linked modules to reduce memmory usage.
	
*******************************************************************************/
	mem[0] = 0;
	nen[0] = 0;
	STM32446temperature = 0;
	/*****STM32446 OBJECTS******/
	//FLASH
	ret.flash.reg = (FLASH_TypeDef*) FLASH_R_BASE;
	
	//CRC
	ret.crc.reg = (CRC_TypeDef*) CRC_BASE;
	
	//PWR
	ret.pwr.reg = (PWR_TypeDef*) PWR_BASE;
	
	//RCC
	ret.rcc.reg = (RCC_TypeDef*) RCC_BASE;
	ret.rcc.henable = STM32446RccHEnable;
	ret.rcc.hselect = STM32446RccHSelect;
	ret.rcc.lenable = STM32446RccLEnable;
	ret.rcc.lselect = STM32446RccLSelect;
	ret.rcc.prescaler = STM32446Prescaler;
	/****PLL****/
	ret.rcc.pll.division = STM32446PLLDivision;
	ret.rcc.pll.enable = STM32446RccPLLCLKEnable;
	ret.rcc.plli2s.enable = STM32446RccPLLI2SEnable;
	ret.rcc.pllsai.enable = STM32446RccPLLSAIEnable;
	
	//GPIOA
	ret.gpioa.reg = (GPIO_TypeDef*) GPIOA_BASE;
	ret.gpioa.moder = STM32446GpioAmoder;
	ret.gpioa.ospeedr = STM32446GpioAospeedr;
	ret.gpioa.pupdr = STM32446GpioApupdr;
	ret.gpioa.reset = STM32446GpioAreset;
	ret.gpioa.set = STM32446GpioAset;
	ret.gpioa.afr = STM32446GpioAafr;
	
	//GPIOB
	ret.gpiob.reg = (GPIO_TypeDef*) GPIOB_BASE;
	ret.gpiob.moder = STM32446GpioBmoder;
	ret.gpiob.ospeedr = STM32446GpioBospeedr;
	ret.gpiob.pupdr = STM32446GpioBpupdr;
	ret.gpiob.reset = STM32446GpioBreset;
	ret.gpiob.set = STM32446GpioBset;
	ret.gpiob.afr = STM32446GpioBafr;
	
	//GPIOC
	ret.gpioc.reg = (GPIO_TypeDef*) GPIOC_BASE;
	ret.gpioc.moder = STM32446GpioCmoder;
	ret.gpioc.ospeedr = STM32446GpioCospeedr;
	ret.gpioc.pupdr = STM32446GpioCpupdr;
	ret.gpioc.reset = STM32446GpioCreset;
	ret.gpioc.set = STM32446GpioCset;
	ret.gpioc.afr = STM32446GpioCafr;
	
	//GPIOD
	ret.gpiod.reg = (GPIO_TypeDef*) GPIOD_BASE;
	ret.gpiod.moder = STM32446GpioDmoder;
	ret.gpiod.ospeedr = STM32446GpioDospeedr;
	ret.gpiod.pupdr = STM32446GpioDpupdr;
	ret.gpiod.reset = STM32446GpioDreset;
	ret.gpiod.set = STM32446GpioDset;
	ret.gpiod.afr = STM32446GpioDafr;

	//GPIOE
	ret.gpioe.reg = (GPIO_TypeDef*) GPIOE_BASE;
	ret.gpioe.moder = STM32446GpioEmoder;
	ret.gpioe.ospeedr = STM32446GpioEospeedr;
	ret.gpioe.pupdr = STM32446GpioEpupdr;
	ret.gpioe.reset = STM32446GpioEreset;
	ret.gpioe.set = STM32446GpioEset;
	ret.gpioe.afr = STM32446GpioEafr;

	//GPIOH
	ret.gpioh.reg = (GPIO_TypeDef*) GPIOH_BASE;
	ret.gpioh.moder = STM32446GpioHmoder;
	ret.gpioh.ospeedr = STM32446GpioHospeedr;
	ret.gpioh.pupdr = STM32446GpioHpupdr;
	ret.gpioh.reset = STM32446GpioHreset;
	ret.gpioh.set = STM32446GpioHset;
	ret.gpioh.afr = STM32446GpioHafr;
	
	//RTC
	ret.rtc.reg = (RTC_TypeDef*) RTC_BASE;
	ret.rtc.inic = STM32446RtcInic;
	ret.rtc.Day = STM32446RtcDay;
	ret.rtc.Month = STM32446RtcMonth;
	ret.rtc.WeekDay = STM32446RtcWeekDay;
	ret.rtc.Year = STM32446RtcYear;
	ret.rtc.Hour = STM32446RtcHour;
	ret.rtc.Minute = STM32446RtcMinute;
	ret.rtc.Second = STM32446RtcSecond;
	ret.rtc.dr2vec = STM32446Rtcdr2vec;
	ret.rtc.tr2vec = STM32446Rtctr2vec;
	ret.rtc.RegWrite = STM32446RtcRegWrite;
	
	//SYSCFG
	ret.syscfg.reg = (SYSCFG_TypeDef*) SYSCFG_BASE;
	
	//DMA1
	ret.dma1.reg = (DMA_TypeDef*) DMA1_BASE;
	//DMA2
	ret.dma2.reg = (DMA_TypeDef*) DMA2_BASE;
	
	//NVIC
	ret.nvic.reg = (NVIC_Type*) NVIC_BASE;
	
	//SysTick (Used as Delay Source)
	ret.systick.reg = (SysTick_Type*) SysTick_BASE;
	ret.systick.delay_ms = STM32446delay_ms;
	ret.systick.delay_10us = STM32446delay_10us;
	ret.systick.delay_us = STM32446delay_us;
	
	/**random order**/
	
	//TIM9
	ret.tim9.reg = (TIM_TypeDef*) TIM9_BASE;
	
	//ADC1
	ret.adc1.reg = (ADC_TypeDef*) ADC1_BASE;
	/****single****/
	ret.adc1.single.inic = STM32446Adc1Inic;
	ret.adc1.single.vbat = STM32446Adc1VBAT;
	ret.adc1.single.temp = STM32446Adc1TEMP;
	ret.adc1.single.start = STM32446Adc1Start;
	ret.adc1.single.read = STM32446Adc1Read;
	ret.adc1.single.restart = STM32446Adc1Restart;
	ret.adc1.single.stop = STM32446Adc1Stop;
	
	//ADC COMMON
	ret.adc123.reg = (ADC_Common_TypeDef*) ADC123_COMMON_BASE;
	
	//USART1
	ret.usart1.reg = (USART_TypeDef*) USART1_BASE;
	ret.usart1.inic = STM32446Usart1Inic;
	ret.usart1.transmit = STM32446Usart1Transmit;
	ret.usart1.receive = STM32446Usart1Receive;
	ret.usart1.parameters = STM32446Usart1Parameters;
	ret.usart1.stop = STM32446Usart1Stop;
	
	/*** INICS ***/
	ret.inic.peripheral = STM32446PeripheralInic;
	
	/*** FUNCS ***/
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
	ret.func.setup = STM32446GpioSetup;
	ret.func.test = template;
	
	/****************************************************************************/
	SystickInic(); // Polling delay source.
	/****************************************************************************/
	return ret;
}

/******************************************************************************/
/*******************************/
/*************INICS*************/
/*******************************/
// peripheral
uint8_t STM32446PeripheralInic(void)
{
	uint8_t clkused; // First turn it on then select it or enable it.
	// Setup PLL
	/**************************************************************************
	PLLDIVISIO parameters
	source 0 or 1		M 2 to 63		N 50 to 432		P 2,4,6,8
	Q 2 to 15			R 2 to 7        (2Mhz ideal, N/m  *  clkx)
	**************************************************************************/
	STM32446PLLDivision(0, 8, 400, 2, 8, 4);
	// Enable PLL
	STM32446RccPLLCLKEnable(0); // Only enable when Division is configured correctly.
	/**************************************************************************
	SysClock prescaler parameters
	AHB 1,2,4,8,16,64,128,256,512 		APB1 1,2,4,8,16		APB2 1,2,4,8,16
	RTC 2 to 31
	**************************************************************************/
	//STM32446Prescaler(16, 1, 1, 0); // using PLL at 25Mhz [16 a must]
	STM32446Prescaler(1, 1, 1, 0);
	// System Clock Source
	STM32446RccHEnable(0);
	// System Clock Select or Enable
	clkused = STM32446RccHSelect(0); // SW[1:0]: System clock switch 00 - HSI, 01 - HSE pg133
	// Low Speed Internal Clock turned on as default
	// Internal low-speed oscillator enable and Internal low-speed oscillator ready
	STM32446RccLEnable(2);
	return clkused;
}
/*******************************/
/*************FUNCS*************/
/*******************************/
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
	ret.rcc.reg->CFGR &= ~mask; // clear args

	if(rtcpre > 1 && rtcpre < 32) // 16
		ret.rcc.reg->CFGR |= (rtcpre << 16);

	switch(ppre2){ // 13
		case 2:
			ret.rcc.reg->CFGR |= (4 << 13);
			break;
		case 4:
			ret.rcc.reg->CFGR |= (5 << 13);
			break;
		case 8:
			ret.rcc.reg->CFGR |= (6 << 13);
			break;
		case 16:
			ret.rcc.reg->CFGR |= (7 << 13);
			break;
		default:
			break;
	}

	switch(ppre1){ // 10
	case 2:
		ret.rcc.reg->CFGR |= (4 << 10);
		break;
	case 4:
		ret.rcc.reg->CFGR |= (5 << 10);
		break;
	case 8:
		ret.rcc.reg->CFGR |= (6 << 10);
		break;
	case 16:
		ret.rcc.reg->CFGR |= (7 << 10);
		break;
	default:
		break;
	}

	switch(ahbpre){ // 4
	case 2:
		ret.rcc.reg->CFGR |= (8 << 4);
		break;
	case 4:
		ret.rcc.reg->CFGR |= (9 << 4);
		break;
	case 8:
		ret.rcc.reg->CFGR |= (10 << 4);
		break;
	case 16:
		ret.rcc.reg->CFGR |= (11 << 4);
		break;
	case 64:
		ret.rcc.reg->CFGR |= (12 << 4);
		break;
	case 128:
		ret.rcc.reg->CFGR |= (13 << 4);
		break;
	case 256:
		ret.rcc.reg->CFGR |= (14 << 4);
		break;
	case 512:
		ret.rcc.reg->CFGR |= (15 << 4);
		break;
	default:
		break;
	}
}

/****PLL****/

void STM32446PLLDivision(unsigned int pllsrc, unsigned int pllm, unsigned int plln, unsigned int pllp, unsigned int pllq, unsigned int pllr)
{
	const unsigned int mask = 0x7F437FFF;
	ret.rcc.reg->PLLCFGR |= mask; // set mask bits high

	if(pllr > 1 && pllr < 8) // PLLR[28]: Main PLL division factor for I2Ss, SAIs, SYSTEM and SPDIF-Rx clocks
		ret.rcc.reg->PLLCFGR &= ((unsigned int) ~(7 << 28)) | (pllr << 28);

	if(pllq > 1 && pllq < 16) // PLLQ[24]: Main PLL (PLL) division factor for USB OTG FS, SDIOclocks
		ret.rcc.reg->PLLCFGR &= ((unsigned int) ~(15 << 24)) | (pllq << 24);

	if(pllsrc == 1) // PLLSRC[22]: Main PLL(PLL) and audio PLL (PLLI2S) entry clock source
		ret.rcc.reg->PLLCFGR &= ((unsigned int) ~(1 << 22)) | (pllsrc << 22);
	else
		ret.rcc.reg->PLLCFGR &= (unsigned int) ~(1 << 22);

	switch(pllp){ // PLLP[16]: Main PLL (PLL) division factor for main system clock
		case 2:
			ret.rcc.reg->PLLCFGR &= (unsigned int) ~(3 << 16);
			break;
		case 4:
			ret.rcc.reg->PLLCFGR &= ((unsigned int) ~(3 << 16)) | (1 << 16);
			break;
		case 6:
			ret.rcc.reg->PLLCFGR &= ((unsigned int) ~(3 << 16)) | (2 << 16);
			break;
		case 8:
			ret.rcc.reg->PLLCFGR &= ((unsigned int) ~(3 << 16)) | (3 << 16);
			break;
		default:
			break;
	}

	if(plln > 49 && plln < 433) // PLLN[6]: Main PLL (PLL) multiplication factor for VCO
		ret.rcc.reg->PLLCFGR &= ((unsigned int) ~(511 << 6)) | (plln << 6);

	if(pllm > 1 && pllm < 64) // PLLM[0]: Division factor for the main PLL (PLL) input clock [2Mhz]
		ret.rcc.reg->PLLCFGR &= ((unsigned int) ~(63)) | pllm;
}

void STM32446RccPLLCLKEnable(uint8_t onoff)
{
	if(onoff)
		for( ret.rcc.reg->CR |= (1 << 24) ; !(ret.rcc.reg->CR & (1 << 25)) ; ); // PLLON: Main PLL (PLL) enable
	else
		ret.rcc.reg->CR &= (unsigned int) ~(1 << 24);
}

void STM32446RccPLLI2SEnable(uint8_t onoff)
{
	if(onoff)
		for( ret.rcc.reg->CR |= (1 << 26) ; !(ret.rcc.reg->CR & (1 << 27)) ; ); // PLLI2SON: PLLI2S enable
	else
		ret.rcc.reg->CR &= (unsigned int) ~(1 << 26);
}

void STM32446RccPLLSAIEnable(uint8_t onoff)
{
	if(onoff)
		for( ret.rcc.reg->CR |= (1 << 28) ; !(ret.rcc.reg->CR & (1 << 29)) ; ); // PLLSAION: PLLSAI enable
	else
		ret.rcc.reg->CR &= (unsigned int) ~(1 << 28);
}

// GPIO
/** To much resources **/
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
/** disabled **/

void STM32446GpioSetpin( GPIO_TypeDef* regs, int pin )
{
			regs->BSRR = (1 << pin);
}

void STM32446GpioSet( GPIO_TypeDef* regs, int data )
{
			regs->BSRR = (unsigned int) data;
}

/** To much resources **/
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
/** disabled **/

void STM32446GpioResetpin( GPIO_TypeDef* regs, int pin )
{
			regs->BSRR = (unsigned int)((1 << pin) << 16);
}

void STM32446GpioReset( GPIO_TypeDef* regs, int data )
{
			regs->BSRR = (unsigned int)(data << 16);
}

/***generic***/
void STM32446Gpiosetupreg( volatile uint32_t* reg, unsigned int size_block, unsigned int data, unsigned int pin )
{
	unsigned int mask = (unsigned int)(pow(2, size_block) - 1);
	data &= mask;
	*reg &= ~(mask << (pin * size_block));
	*reg |= (data << (pin * size_block));
	*reg &= (unsigned int) sperm;
}

void STM32446GpioSetup( volatile uint32_t vec[], const unsigned int size_block, unsigned int data, unsigned int block_n )
{
	const unsigned int n_bits = sizeof(data) * 8;
	const unsigned int mask = (unsigned int) (pow(2, size_block) - 1);
	unsigned int index = (block_n * size_block) / n_bits;
	data &= mask;
	vec[index] &= ~( mask << ((block_n * size_block) - (index * n_bits)) );
	vec[index] |= ( data << ((block_n * size_block) - (index * n_bits)) );
	vec[index] &= (unsigned int) sperm;
}
/***generic***/

// GPIOA
void STM32446GpioAmoder( unsigned int data, unsigned int pin )
{
	const unsigned int blocksize = 2;
	unsigned int mask = (unsigned int)(pow(2, blocksize) - 1);
	data &= mask;
	ret.gpioa.reg->MODER &= ~(mask << (pin * blocksize));
	ret.gpioa.reg->MODER |= (data << (pin * blocksize));
	ret.gpioa.reg->MODER &= (unsigned int) sperm;
}

void STM32446GpioAospeedr( unsigned int data, unsigned int pin )
{
	const unsigned int blocksize = 2;
	unsigned int mask = (unsigned int)(pow(2, blocksize) - 1);
	data &= mask;
	ret.gpioa.reg->OSPEEDR &= ~(mask << (pin * blocksize));
	ret.gpioa.reg->OSPEEDR |= (data << (pin * blocksize));
	ret.gpioa.reg->OSPEEDR &= (unsigned int) sperm;
}

void STM32446GpioApupdr( unsigned int data, unsigned int pin )
{
	const unsigned int blocksize = 2;
	unsigned int mask = (unsigned int)(pow(2, blocksize) - 1);
	data &= mask;
	ret.gpioa.reg->PUPDR &= ~(mask << (pin * blocksize));
	ret.gpioa.reg->PUPDR |= (data << (pin * blocksize));
	ret.gpioa.reg->PUPDR &= (unsigned int) sperm;
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
		ret.gpioa.reg->AFR[index] &= (unsigned int) sperm;
	}
}

// GPIOB
void STM32446GpioBmoder( unsigned int data, unsigned int pin )
{
	const unsigned int blocksize = 2;
	unsigned int mask = (unsigned int)(pow(2, blocksize) - 1);
	data &= mask;
	ret.gpiob.reg->MODER &= ~(mask << (pin * blocksize));
	ret.gpiob.reg->MODER |= (data << (pin * blocksize));
	ret.gpiob.reg->MODER &= (unsigned int) sperm;
}

void STM32446GpioBospeedr( unsigned int data, unsigned int pin )
{
	const unsigned int blocksize = 2;
	unsigned int mask = (unsigned int)(pow(2, blocksize) - 1);
	data &= mask;
	ret.gpiob.reg->OSPEEDR &= ~(mask << (pin * blocksize));
	ret.gpiob.reg->OSPEEDR |= (data << (pin * blocksize));
	ret.gpiob.reg->OSPEEDR &= (unsigned int) sperm;
}

void STM32446GpioBpupdr( unsigned int data, unsigned int pin )
{
	const unsigned int blocksize = 2;
	unsigned int mask = (unsigned int)(pow(2, blocksize) - 1);
	data &= mask;
	ret.gpiob.reg->PUPDR &= ~(mask << (pin * blocksize));
	ret.gpiob.reg->PUPDR |= (data << (pin * blocksize));
	ret.gpiob.reg->PUPDR &= (unsigned int) sperm;
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
		ret.gpiob.reg->AFR[index] &= (unsigned int) sperm;
	}
}

// GPIOC
void STM32446GpioCmoder( unsigned int data, unsigned int pin )
{
	const unsigned int blocksize = 2;
	unsigned int mask = (unsigned int)(pow(2, blocksize) - 1);
	data &= mask;
	ret.gpioc.reg->MODER &= ~(mask << (pin * blocksize));
	ret.gpioc.reg->MODER |= (data << (pin * blocksize));
	ret.gpioc.reg->MODER &= (unsigned int) sperm;
}

void STM32446GpioCospeedr( unsigned int data, unsigned int pin )
{
	const unsigned int blocksize = 2;
	unsigned int mask = (unsigned int)(pow(2, blocksize) - 1);
	data &= mask;
	ret.gpioc.reg->OSPEEDR &= ~(mask << (pin * blocksize));
	ret.gpioc.reg->OSPEEDR |= (data << (pin * blocksize));
	ret.gpioc.reg->OSPEEDR &= (unsigned int) sperm;
}

void STM32446GpioCpupdr( unsigned int data, unsigned int pin )
{
	const unsigned int blocksize = 2;
	unsigned int mask = (unsigned int)(pow(2, blocksize) - 1);
	data &= mask;
	ret.gpioc.reg->PUPDR &= ~(mask << (pin * blocksize));
	ret.gpioc.reg->PUPDR |= (data << (pin * blocksize));
	ret.gpioc.reg->PUPDR &= (unsigned int) sperm;
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
		ret.gpioc.reg->AFR[index] &= (unsigned int) sperm;
	}
}

// GPIOD
void STM32446GpioDmoder( unsigned int data, unsigned int pin )
{
	const unsigned int blocksize = 2;
	unsigned int mask = (unsigned int)(pow(2, blocksize) - 1);
	data &= mask;
	ret.gpiod.reg->MODER &= ~(mask << (pin * blocksize));
	ret.gpiod.reg->MODER |= (data << (pin * blocksize));
	ret.gpiod.reg->MODER &= (unsigned int) sperm;
}

void STM32446GpioDospeedr( unsigned int data, unsigned int pin )
{
	const unsigned int blocksize = 2;
	unsigned int mask = (unsigned int)(pow(2, blocksize) - 1);
	data &= mask;
	ret.gpiod.reg->OSPEEDR &= ~(mask << (pin * blocksize));
	ret.gpiod.reg->OSPEEDR |= (data << (pin * blocksize));
	ret.gpiod.reg->OSPEEDR &= (unsigned int) sperm;
}

void STM32446GpioDpupdr( unsigned int data, unsigned int pin )
{
	const unsigned int blocksize = 2;
	unsigned int mask = (unsigned int)(pow(2, blocksize) - 1);
	data &= mask;
	ret.gpiod.reg->PUPDR &= ~(mask << (pin * blocksize));
	ret.gpiod.reg->PUPDR |= (data << (pin * blocksize));
	ret.gpiod.reg->PUPDR &= (unsigned int) sperm;
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
		ret.gpiod.reg->AFR[index] &= (unsigned int) sperm;
	}
}

// GPIOE
void STM32446GpioEmoder( unsigned int data, unsigned int pin )
{
	const unsigned int blocksize = 2;
	unsigned int mask = (unsigned int)(pow(2, blocksize) - 1);
	data &= mask;
	ret.gpioe.reg->MODER &= ~(mask << (pin * blocksize));
	ret.gpioe.reg->MODER |= (data << (pin * blocksize));
	ret.gpioe.reg->MODER &= (unsigned int) sperm;
}

void STM32446GpioEospeedr( unsigned int data, unsigned int pin )
{
	const unsigned int blocksize = 2;
	unsigned int mask = (unsigned int)(pow(2, blocksize) - 1);
	data &= mask;
	ret.gpioe.reg->OSPEEDR &= ~(mask << (pin * blocksize));
	ret.gpioe.reg->OSPEEDR |= (data << (pin * blocksize));
	ret.gpioe.reg->OSPEEDR &= (unsigned int) sperm;
}

void STM32446GpioEpupdr( unsigned int data, unsigned int pin )
{
	const unsigned int blocksize = 2;
	unsigned int mask = (unsigned int)(pow(2, blocksize) - 1);
	data &= mask;
	ret.gpioe.reg->PUPDR &= ~(mask << (pin * blocksize));
	ret.gpioe.reg->PUPDR |= (data << (pin * blocksize));
	ret.gpioe.reg->PUPDR &= (unsigned int) sperm;
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
		ret.gpioe.reg->AFR[index] &= (unsigned int) sperm;
	}
}

// GPIOH
void STM32446GpioHmoder( unsigned int data, unsigned int pin )
{
	const unsigned int blocksize = 2;
	unsigned int mask = (unsigned int)(pow(2, blocksize) - 1);
	data &= mask;
	ret.gpioh.reg->MODER &= ~(mask << (pin * blocksize));
	ret.gpioh.reg->MODER |= (data << (pin * blocksize));
	ret.gpioh.reg->MODER &= (unsigned int) sperm;
}

void STM32446GpioHospeedr( unsigned int data, unsigned int pin )
{
	const unsigned int blocksize = 2;
	unsigned int mask = (unsigned int)(pow(2, blocksize) - 1);
	data &= mask;
	ret.gpioh.reg->OSPEEDR &= ~(mask << (pin * blocksize));
	ret.gpioh.reg->OSPEEDR |= (data << (pin * blocksize));
	ret.gpioh.reg->OSPEEDR &= (unsigned int) sperm;
}

void STM32446GpioHpupdr( unsigned int data, unsigned int pin )
{
	const unsigned int blocksize = 2;
	unsigned int mask = (unsigned int)(pow(2, blocksize) - 1);
	data &= mask;
	ret.gpioh.reg->PUPDR &= ~(mask << (pin * blocksize));
	ret.gpioh.reg->PUPDR |= (data << (pin * blocksize));
	ret.gpioh.reg->PUPDR &= (unsigned int) sperm;
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
		ret.gpioh.reg->AFR[index] &= (unsigned int) sperm;
	}
}

// RTC
uint8_t STM32446RtcInic(uint8_t clock)
{ // slow
	uint8_t status = 255;
	STM32446TimeTr = ret.rtc.reg->TR;
	STM32446DateDr = ret.rtc.reg->DR;
	
	status = STM32446RtcAccess(clock);
	
	//Some help from youtube vids
	//ret.rcc.reg->CFGR &= (uint32_t) ~((1 << 0) | (1 << 1)); // RCC_CFGR sw[2:0] 00 Bits 1:0
	//ret.rcc.reg->CFGR &= (uint32_t) ~((1 << 20) | (1 << 19) | (1 << 18) | (1 << 17) | (1 << 16)); // RCC_CFGR RTCPRE[4:0] 00010: HSE/2 Bits 20:16
	//ret.rcc.reg->CFGR |= (uint32_t) (1 << 17); // RCC_CFGR RTCPRE[4:0] 00010: HSE/2 Bits
	
	ret.rcc.reg->BDCR |= (1 << 15); // RTCEN: RTC clock enable
	
	//5 - Enter the "key" to unlock write protection
	ret.rtc.reg->WPR |= 0xCA;
	ret.rtc.reg->WPR |= 0x53;
	//ret.rtc.reg->ISR &= (uint32_t) ~((1 << 3) | (1 << 5) | (1 << 7));

	//6 - Set INIT bit and wait for ready flag
	ret.rtc.reg->ISR |= (1 << 7); // INIT: Initialization mode
	while( !(ret.rtc.reg->ISR & (1 << 6)) ); // INITF: Initialization flag
	status = 6;

	//7 - Adjust prescaler values for RTC to obtain 1 Hz
	//ret.rtc-reg->PRER |= 0xF9;
	//ret.rtc.reg->PRER |= (0x7F << 16);
	
	//8 - Write Time and Date values
	//ret.rtc.reg->TR |= 0x130000;
	//ret.rtc.reg->TR |= 0x5700;
	//ret.rtc.reg->DR |= 0x215124;
	
	//9 - Set BYPSHAD bit
	// must read twice
	//ret.rtc.reg->CR |= (1 << 5); // BYPSHAD: Bypass the shadow registers
	// read only once
	ret.rtc.reg->CR &= (uint32_t) ~(1 << 5); // BYPSHAD: Disable Bypass the shadow registers
	
	//10 - Clear INIT bit
	ret.rtc.reg->ISR &= (uint32_t) ~(1 << 7);
	
	//11 - Disable access to RTC registers
	ret.pwr.reg->CR &= (uint32_t) ~(1 << 8);

	return status;
}

void STM32446RtcHour(uint8_t hour)
{
	uint8_t t, u;
	const uint32_t mask = 0x003F0000;
	
	t = STM32446dec2bcd(hour / 10);
	u = STM32446dec2bcd(hour % 10);
	STM32446TimeTr = ret.rtc.reg->TR;
	STM32446TimeTr &= (uint32_t) ~mask; // clear ht and hu 
	// hu, ht
	STM32446TimeTr |= (uint32_t) ((u << 16) | (t << 20));
	STM32446RtcSetTr();
}

void STM32446RtcMinute(uint8_t minute)
{
	uint8_t t, u;
	const uint32_t mask = 0x00007F00;
	
	t = STM32446dec2bcd(minute / 10);
	u = STM32446dec2bcd(minute % 10);
	STM32446TimeTr = ret.rtc.reg->TR;
	STM32446TimeTr &= (uint32_t) ~mask; // clear mnt and mnu 
	// mnu, mnt
	STM32446TimeTr |= (uint32_t) ((u << 8) | (t << 12));
	STM32446RtcSetTr();
}

void STM32446RtcSecond(uint8_t second)
{
	uint8_t t, u;
	const uint32_t mask = 0x0000007F;
	
	t = STM32446dec2bcd(second / 10);
	u = STM32446dec2bcd(second % 10);
	STM32446TimeTr = ret.rtc.reg->TR;
	STM32446TimeTr &= (uint32_t) ~mask; // clear st and su 
	// su, st
	STM32446TimeTr |= (uint32_t) ((u << 0) | (t << 4));
	STM32446RtcSetTr();
}

void STM32446RtcYear(uint8_t year)
{
	uint8_t t, u;
	const uint32_t mask = 0x00FF0000;
	
	t = STM32446dec2bcd(year / 10);
	u = STM32446dec2bcd(year % 10);
	STM32446DateDr &= (uint32_t) ~mask; // clear YT and YU 
	// YU, YT
	STM32446DateDr |= (uint32_t) ((u << 16) | (t << 20));
	STM32446RtcSetDr();
}

void STM32446RtcWeekDay(uint8_t weekday)
{
	uint8_t u;
	const uint32_t mask = 0x0000E0000;
	
	u = STM32446dec2bcd(weekday % 10);
	STM32446DateDr &= (uint32_t) ~mask; // clear WDU 
	// WDU
	STM32446DateDr |= (uint32_t) (u << 13);
	STM32446RtcSetDr();
}

void STM32446RtcMonth(uint8_t month)
{
	uint8_t t, u;
	const uint32_t mask = 0x00001F00;
	
	t = STM32446dec2bcd(month / 10);
	u = STM32446dec2bcd(month % 10);
	STM32446DateDr &= (uint32_t) ~mask; // clear MT and MU 
	// MU, MT
	STM32446DateDr |= (uint32_t) ((u << 8) | (t << 12));
	STM32446RtcSetDr();
}

void STM32446RtcDay(uint8_t day)
{
	uint8_t t, u;
	const uint32_t mask = 0x0000003F;
	
	t = STM32446dec2bcd(day / 10);
	u = STM32446dec2bcd(day % 10);
	STM32446DateDr &= (uint32_t) ~mask; // clear DT and DU 
	// DU, DT
	STM32446DateDr |= (uint32_t) ((u << 0) | (t << 4));
	STM32446RtcSetDr();
}

void STM32446RtcRegWrite(volatile uint32_t* reg, uint32_t data)
{
	//1 - Enable access to the RTC registers
	ret.pwr.reg->CR |= (1 << 8); // Disable backup domain write protection
	//2 - Enter the "key" to unlock write protection	
	ret.rtc.reg->WPR |= 0xCA;
	ret.rtc.reg->WPR |= 0x53;
	//3 - Write
	
	*reg = data;
	
	//4 - Disable access to RTC registers	
	ret.pwr.reg->CR &= (uint32_t) ~(1 << 8);
}

void STM32446Rtcdr2vec(char* vect)
{
	uint32_t dr = ret.rtc.reg->DR;
	// YT
	vect[0] = (uint8_t) (dr >> 20) & 0x0F;
	vect[0] = STM32446bcd2dec(vect[0]);
	// YU
	vect[1] = (uint8_t) (dr >> 16) & 0x0F;
	vect[1] = STM32446bcd2dec(vect[1]);
	// WDU
	vect[2] = (uint8_t) (dr >> 13) & 0x07;
	vect[2] = STM32446bcd2dec(vect[2]);
	// MT
	vect[3] = (uint8_t) (dr >> 12) & 0x01;
	vect[3] = STM32446bcd2dec(vect[3]);
	// MU
	vect[4] = (uint8_t) (dr >> 8) & 0x0F;
	vect[4] = STM32446bcd2dec(vect[4]);
	// DT
	vect[5] = (uint8_t) (dr >> 4) & 0x03;
	vect[5] = STM32446bcd2dec(vect[5]);
	// DU
	vect[6] = (uint8_t) dr & 0x0F;
	vect[6] = STM32446bcd2dec(vect[6]);
	// Store Value
	STM32446DateDr = dr;
}

void STM32446Rtctr2vec(char* vect)
{
	uint32_t tr = ret.rtc.reg->TR;
	if(ret.rtc.reg->ISR & (1 << 5)){ // RSF: Registers synchronization flag
		// ht
		vect[0] = (uint8_t) (tr >> 20) & 0x03;
		vect[0] = STM32446bcd2dec(vect[0]);
		// hu
		vect[1] = (uint8_t) (tr >> 16) & 0x0F;
		vect[1] = STM32446bcd2dec(vect[1]);
		// mnt
		vect[2] = (uint8_t) (tr >> 12) & 0x07;
		vect[2] = STM32446bcd2dec(vect[2]);
		// mnu
		vect[3] = (uint8_t) (tr >> 8) & 0x0F;
		vect[3] = STM32446bcd2dec(vect[3]);
		// st
		vect[4] = (uint8_t) (tr >> 4) & 0x07;
		vect[4] = STM32446bcd2dec(vect[4]);
		// su
		vect[5] = (uint8_t) tr & 0x0F;
		vect[5] = STM32446bcd2dec(vect[5]);
		// Store value
		STM32446TimeTr = tr;
		// Clear Registers synchronization flag
		ret.rtc.reg->ISR &= (uint32_t) ~(1 << 5);
	}
}

//ADC1
void STM32446Adc1Inic(void)
{
	/***ADC Clock***/
	//ret.rcc.reg->APB1ENR |= (1 << 29); // DACEN: DAC interface clock enable
	ret.rcc.reg->APB2ENR |= (1 << 8); // ADC1EN: ADC1 clock enable
	/***ADC CONFIG***/
	ret.adc1.reg->CR2 |= (1 << 10); // EOCS: End of conversion selection
	ret.adc123.reg->CCR |= (3 << 16); // ADCPRE: ADC prescaler, 11: PCLK2 divided by 8
	ret.adc1.reg->SMPR1 |= (7 << 24); // SMPx[2:0]: Channel x sampling time selection
	ret.adc1.reg->CR1 |= (1 << 11); // DISCEN: Discontinuous mode on regular channels
	ret.adc1.reg->SQR3 |= 18; // SQ1[4:0]: 1st conversion in regular sequence
}

void STM32446Adc1VBAT(void) // vbat overrides temperature
{
	ret.adc123.reg->CCR |= (1 << 22); // VBATE: VBAT enable
}

void STM32446Adc1TEMP(void)
{
	//Temperature (in ºC) = {(VSENSE V25) / Avg_Slope} + 25
	ret.adc123.reg->CCR |= (1 << 23); // TSVREFE: Temperature sensor and VREFINT enable
}

void STM32446Adc1Start()
{
	// turn on select source and start reading
	ret.adc1.reg->CR2 |= (1 << 0); // ADON: A/D Converter ON / OFF
	//
	ret.adc1.reg->CR2 |= (1 << 30); // SWSTART: Start conversion of regular channels
}


double STM32446Adc1Read(void)
{
	if(ret.adc123.reg->CSR & (1 << 1)){ // EOC1: End of conversion of ADC1
		STM32446temperature = ret.adc1.reg->DR;
		ret.adc1.reg->SR &= (unsigned int) ~(1 << 4); // STRT: Regular channel start flag
	}
	return STM32446temperature;
}

void STM32446Adc1Restart(void)
{
	if(ret.adc123.reg->CSR & (1 << 4)) // STRT1: Regular channel Start flag of ADC1
		;
	else
		ret.adc1.reg->CR2 |= (1 << 30); // SWSTART: Start conversion of regular channels;
}

void STM32446Adc1Stop(void)
{
	ret.adc1.reg->CR2 |= (1 << 0); // ADON: A/D Converter ON / OFF
}

//USART1
void STM32446Usart1Inic( uint8_t wordlength, uint8_t samplingmode, double stopbits, uint32_t baudrate )
{
	// RCC
	ret.rcc.reg->APB2ENR |= (1 << 4); // USART1EN: USART1 clock enable
	// Choose GPIO
	/*****************************************************************
		PA9 - TX		PA10 - RX
		PA11 - CTS		PA12 - RTS

		AF7 and AF8, activation. therfore
	 *****************************************************************/
	ret.gpioa.moder(2,9);
	ret.gpioa.moder(2,10);
	ret.gpioa.afr(7,9);
	ret.gpioa.afr(7,10);
	/******************************************************************************
		Procedure:
	1. Enable the USART by writing the UE bit in USART_CR1 register to 1.
	2. Program the M bit in USART_CR1 to define the word length.
	3. Program the number of stop bits in USART_CR2.
	4. Select DMA enable (DMAT) in USART_CR3 if Multi buffer Communication is to take
	   place. Configure the DMA register as explained in multibuffer communication.
	5. Select the desired baud rate using the USART_BRR register.
	*******************************************************************************/
	ret.usart1.reg->CR1 |= (1 << 13); // UE: USART enable
	STM32446Usart1Parameters( wordlength, samplingmode, stopbits, baudrate ); // Default

}
void STM32446Usart1Transmit(void) //RM0390 pg801
{
	/******************************************************************************
		Procedure:
	6. Set the TE bit in USART_CR1 to send an idle frame as first transmission.
	7. Write the data to send in the USART_DR register (this clears the TXE bit). Repeat this
		for each data to be transmitted in case of single buffer.
	8. After writing the last data into the USART_DR register, wait until TC=1. This indicates
		that the transmission of the last frame is complete. This is required for instance when
		the USART is disabled or enters the Halt mode to avoid corrupting the last transmission.
	*******************************************************************************/
	ret.usart1.reg->CR3 &= (uint32_t) ~(1 << 7); // DMAT: DMA enable transmitter - disabled
	ret.usart1.reg->CR1 |= (1 << 3); // TE: Transmitter enable
	//ret.usart1.reg->DR = 'A';
	//on real application, use fall threw method in main
	//for( ; ret.usart1.reg->SR & (1 << 6); ); // TC: Transmission complete
	// added this as disable after confirmed end of transmission [9]
	//ret.usart1.reg->CR1 &= (uint32_t) ~(1 << 13); // UE: USART disable
	ret.usart1.reg->SR &= ~(1 << 6); // TC: Transmission complete
}

void STM32446Usart1Receive(void) //RM0390 pg804
{
	/******************************************************************************
		Procedure: baud rate register USART_BRR
	6.	Set the RE bit USART_CR1. This enables the receiver that begins searching for a start
		bit.
	 *******************************************************************************/
	ret.usart1.reg->CR3 &= (uint32_t) ~(1 << 6); // DMAR: DMA enable receiver - disabled
	ret.usart1.reg->CR1 |= (1 << 2); // RE: Receiver enable
	ret.usart1.reg->SR &= ~(1 << 5); // RXNE: Read data register not empty
}

void STM32446Usart1Parameters( uint8_t wordlength, uint8_t samplingmode, double stopbits, uint32_t baudrate )
/******************************************************************************
Sets the usart parameters, using real values.
*******************************************************************************/
{
	uint8_t sampling;
	double value, fracpart, intpart;
	
	if(wordlength == 9)
		ret.usart1.reg->CR1 |= (1 << 12); // M: Word length, 1 - 9bit.
	else if(wordlength == 8)
		ret.usart1.reg->CR1 &= (uint32_t) ~(1 << 12); // M: Word length, 0 - 8bit.
	else
		ret.usart1.reg->CR1 &= (uint32_t) ~(1 << 12); // M: Word length, 0 - 8bit, default.
	
	if(samplingmode == 8){
		sampling = 8;
		ret.usart1.reg->CR1 |= (1 << 15); // OVER8: Oversampling mode, 1 - 8.
	}else if(samplingmode == 16){
		sampling = 16;
		ret.usart1.reg->CR1 &= (uint32_t) ~(1 << 15); // OVER8: Oversampling mode, 0 - 16.
	}else{
		sampling = 16;
		ret.usart1.reg->CR1 &= (uint32_t) ~(1 << 15); // OVER8: Oversampling mode, 0 - 16, default.
	}
	
	ret.usart1.reg->CR2 &= (uint32_t) ~((1 << 13) | (1 << 12)); // STOP: STOP bits 00 - 1stopbit, default.
	if(fabs(stopbits - 0.5) < 0.00001) // STOP: STOP bits, 01: 0.5 Stop bit
		ret.usart1.reg->CR2 |= (1 << 12);
	else if(fabs(stopbits - 1) < 0.00001) // STOP: STOP bits, 00: 1 Stop bit.
		ret.usart1.reg->CR2 &= (uint32_t) ~((1 << 13) | (1 << 12));
	else if(fabs(stopbits - 1.5) < 0.00001) // STOP: STOP bits, 11: 1.5 Stop bit
		ret.usart1.reg->CR2 |= ((1 << 13) | (1 << 12));
	else if(fabs(stopbits - 2) < 0.00001) // STOP: STOP bits, 10: 2 Stop bits
		ret.usart1.reg->CR2 |= (1 << 13);
	
	value = (double) SystemCoreClock / ( sampling * baudrate );
	fracpart = modf(value, &intpart);
	
	ret.usart1.reg->BRR = 0; // clean slate, reset.
	if(samplingmode == 16){
		ret.usart1.reg->BRR = (uint32_t) (round(fracpart * 16)); // DIV_Fraction
		ret.usart1.reg->BRR |= ((uint32_t) intpart << 4); // DIV_Mantissa[11:0]
	}else if(samplingmode == 8){
		ret.usart1.reg->BRR = (uint32_t) (round(fracpart * 8)); // DIV_Fraction
		ret.usart1.reg->BRR |= ((uint32_t) intpart << 4); // DIV_Mantissa[11:0]
	}else{
		ret.usart1.reg->BRR = (uint32_t) (round(fracpart * 16)); // DIV_Fraction
		ret.usart1.reg->BRR |= ((uint32_t) intpart << 4); // DIV_Mantissa[11:0], default.
	}
}

void STM32446Usart1Stop(void){
	// added this as disable after confirmed end of transmission [9]
	ret.usart1.reg->CR1 &= (uint32_t) ~(1 << 13); // UE: USART disable
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
					mem[3] = ((uint32_t) sperm - mem[1]) + mem[2];
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
					nen[3] = ((uint32_t) sperm - nen[1]) + nen[2];
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
/********************************/
/***********FILE FUNC************/
/********************************/
//RTC
void STM32446RtcSetTr(void)
{
	//1 - Enable access to the RTC registers
	ret.pwr.reg->CR |= (1 << 8); // Disable backup domain write protection
	//2 - Enter the "key" to unlock write protection	
	ret.rtc.reg->WPR |= 0xCA;
	ret.rtc.reg->WPR |= 0x53;
	//3 - Set INIT bit and wait for ready flag
	ret.rtc.reg->ISR |= (1 << 7); // INIT: Initialization mode
	while( !(ret.rtc.reg->ISR & (1 << 6)) ); // INITF: Initialization flag
	//4 - Setup
	
	ret.rtc.reg->TR = STM32446TimeTr;
	
	//5 - Clear INIT bit
	ret.rtc.reg->ISR &= (uint32_t) ~(1 << 7);
	//6 - Disable access to RTC registers	
	ret.pwr.reg->CR &= (uint32_t) ~(1 << 8);
}

void STM32446RtcSetDr(void)
{
	//1 - Enable access to the RTC registers
	ret.pwr.reg->CR |= (1 << 8); // Disable backup domain write protection
	//2 - Enter the "key" to unlock write protection	
	ret.rtc.reg->WPR |= 0xCA;
	ret.rtc.reg->WPR |= 0x53;
	//3 - Set INIT bit and wait for ready flag
	ret.rtc.reg->ISR |= (1 << 7); // INIT: Initialization mode
	while( !(ret.rtc.reg->ISR & (1 << 6)) ); // INITF: Initialization flag
	//4 - Setup
	
	ret.rtc.reg->DR = STM32446DateDr;
	
	//5 - Clear INIT bit
	ret.rtc.reg->ISR &= (uint32_t) ~(1 << 7);
	//6 - Disable access to RTC registers	
	ret.pwr.reg->CR &= (uint32_t) ~(1 << 8);
}

uint8_t STM32446RtcAccess(uint8_t clock)
{
	uint8_t status;
	//RM0390 pg 94
	//RTC access
	//1 - Enable the power interface clock by setting the PWREN bits in the RCC_APB1ENR
	ret.rcc.reg->APB1ENR |= (1 << 28); // Power interface clock enable
	//RCC->APB1ENR |= ((1 << 11) | (1 << 28));
	//2 - Set the DBP bit in the PWR power control register (PWR_CR)
	ret.pwr.reg->CR |= (1 << 8); // Disable backup domain write protection
	//3 - Select the RTC clock source RTC/AWU clock
	STM32446RccLEnable(clock);
	status = 1;
	//4 - RTCSEL[1:0]: RTC clock source selection
	STM32446RccLSelect(clock);
	status = 2;
	return status;
}


//SRAM
void STM32446SramAccess(void)
{
	//RM0390 pg 94
	//SRAM access
	//0 - Power Up SRAM
	ret.pwr.reg->CSR |= (1 << 9); // BRE: Backup regulator enable
	//Check ready flag Bit 3 BRR: Backup regulator ready
	for( ; !(ret.pwr.reg->CSR & (1 << 3) )  ; ); // BRR: Backup regulator ready
	
	//1 - Enable the power interface clock by setting the PWREN bits in the RCC_APB1ENR
	ret.rcc.reg->APB1ENR |= (1 << 28); // Power interface clock enable
	//RCC->APB1ENR |= ((1 << 11) | (1 << 28));

	//2 - Set the DBP bit in the PWR power control register (PWR_CR)
	ret.pwr.reg->CR |= (1 << 8); // Disable backup domain write protection

	//3 - Enable the backup SRAM clock by setting BKPSRAMEN bit in the RCC_AHB1ENR
	ret.rcc.reg->AHB1ENR |= (1 << 18); // BKPSRAMEN: Backup SRAM interface clock enable
}

// TEMPLATE
void template(void)
{ // the best procedure ever does absolutely nothing
	ret.rcc.reg->APB2ENR |= (1 << 4); // USART1EN: USART1 clock enable
	ret.gpioa.moder(2,9);
	ret.gpioa.moder(2,10);
	ret.gpioa.afr(7,9);
	ret.gpioa.afr(7,10);
	ret.usart1.reg->CR1 |= (1 << 13); // UE: USART enable
	ret.usart1.parameters( 8, 16, 1, 9600 ); // Default
	ret.usart1.reg->CR3 &= (uint32_t) ~(1 << 7); // DMAT: DMA enable transmitter - disabled
	ret.usart1.reg->CR1 |= (1 << 3); // TE: Transmitter enable
}
/*******************************************************************************/
/*******************************************************************************/
// SYSTICK
void SystickInic(void)
{
	ret.systick.reg->LOAD = (uint32_t)(SystemCoreClock - 1);
	ret.systick.reg->VAL = 0UL;
	ret.systick.reg->CTRL |= ((1 << 1) | (1 << 2));
}
void STM32446delay_ms(uint32_t ms)
{
	ret.systick.reg->LOAD = (uint32_t)((SystemCoreClock / 1000) - 1);
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
	ret.systick.reg->LOAD = (uint32_t)((SystemCoreClock / 100000) - 1);
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
	ret.systick.reg->LOAD = (uint32_t)((SystemCoreClock / 1000000) - 1);
	// Enable the SysTick timer
	ret.systick.reg->CTRL |= (1 << 0);
	// Wait for a specified number of milliseconds
	DelayCounter = 0;
	while (DelayCounter < us);
	// Disable the SysTick timer
	ret.systick.reg->CTRL &= (uint32_t) ~(1 << 0);
}

/***Interrupt Procedure***/
void SysTick_Handler(void)
{ // count down to zero systick interrupt and reload.
	DelayCounter++;
}
/********************************COMMENT****************************************
On all periferals, always have to take in cosideration the POWER [pwr] rail, the CLOCK rail [rcc] 
then the pin configuration.

Also be aware of the interrupt flags have to be cleared after being fired and the interrupt been
received.

uvision trial limitation to 32Kb.
*******************************************************************************/

