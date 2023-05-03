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
*** File Variable
*/
static STM32F446* stm32f446;
static volatile uint32_t DelayCounter;
static uint32_t STM32446TimeTr;
static uint32_t STM32446DateDr;
static volatile uint32_t mem[4];
static volatile uint32_t nen[4];
/*
***Procedure and Functions Prototypes
*/
// SysTick
void SystickInic(void);

/***INIC***/
uint8_t STM32446PeripheralInic(void);

/***FUNC***/
//GPIO
void STM32446GpioSetpins( GPIO_TypeDef* reg, int n_pin, ... );
void STM32446GpioSetpin( GPIO_TypeDef* reg, int pin );
void STM32446GpioResetpins( GPIO_TypeDef* reg, int n_pin, ... );
void STM32446GpioResetpin( GPIO_TypeDef* reg, int pin );

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
void STM32446Adc1Ex1inic(void);
void STM32446Adc1Disc1(uint32_t counter, uint32_t threshold, uint32_t interval, uint32_t* trigger);

//USART1
void STM32446usart1transmitsetup(void);
void STM32446usart1recievesetup(void);
void STM32446usart1parameters( uint8_t wordlength, uint8_t samplingmode, double stopbits, uint32_t baudrate );

//MISCELLANEOUS
char STM32446bcd2dec(char num);
char STM32446dec2bcd(char num);
void STM32446delay_ms(uint32_t ms);
void STM32446delay_10us(uint32_t us);
uint32_t STM32446triggerA(uint32_t hllh_io, uint8_t pin, uint32_t counter);
uint32_t STM32446triggerB(uint32_t hl_io, uint32_t lh_io, uint8_t pin, uint32_t counter);
uint16_t STM32ReadHLByte(STM32HighLowByte reg);
uint16_t STM32ReadLHByte(STM32HighLowByte reg);
STM32HighLowByte STM32WriteHLByte(uint16_t val);
STM32HighLowByte STM32WriteLHByte(uint16_t val);
uint16_t STM32SwapByte(uint16_t num);

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
void STM32446enable(STM32F446* self){
/******************************************************************************
Comment out the linked modules to reduce memmory usage.
*******************************************************************************/
	mem[0] = 0;
	nen[0] = 0;
	/*****STM32446 OBJECTS******/
	//FLASH
	self->flash.reg = (FLASH_TypeDef*) FLASH_R_BASE;
	
	//CRC
	self->crc.reg = (CRC_TypeDef*) CRC_BASE;
	
	//PWR
	self->pwr.reg = (PWR_TypeDef*) PWR_BASE;
	
	//RCC
	self->rcc.reg = (RCC_TypeDef*) RCC_BASE;
	
	//GPIOA
	self->gpioa.reg = (GPIO_TypeDef*) GPIOA_BASE;
	//GPIOB
	self->gpiob.reg = (GPIO_TypeDef*) GPIOB_BASE;
	//GPIOC
	self->gpioc.reg = (GPIO_TypeDef*) GPIOC_BASE;
	//GPIOD
	self->gpiod.reg = (GPIO_TypeDef*) GPIOD_BASE;
	//GPIOE
	self->gpioe.reg = (GPIO_TypeDef*) GPIOE_BASE;
	//GPIOH
	self->gpioh.reg = (GPIO_TypeDef*) GPIOH_BASE;
	
	//RTC
	self->rtc.reg = (RTC_TypeDef*) RTC_BASE;
	self->rtc.inic = STM32446RtcInic;
	self->rtc.Day = STM32446RtcDay;
	self->rtc.Month = STM32446RtcMonth;
	self->rtc.WeekDay = STM32446RtcWeekDay;
	self->rtc.Year = STM32446RtcYear;
	self->rtc.Hour = STM32446RtcHour;
	self->rtc.Minute = STM32446RtcMinute;
	self->rtc.Second = STM32446RtcSecond;
	self->rtc.dr2vec = STM32446Rtcdr2vec;
	self->rtc.tr2vec = STM32446Rtctr2vec;
	self->rtc.RegWrite = STM32446RtcRegWrite;
	
	//SYSCFG
	self->syscfg.reg = (SYSCFG_TypeDef*) SYSCFG_BASE;
	
	//DMA1
	self->dma1.reg = (DMA_TypeDef*) DMA1_BASE;
	//DMA2
	self->dma2.reg = (DMA_TypeDef*) DMA2_BASE;
	
	//NVIC
	self->nvic.reg = (NVIC_Type*) NVIC_BASE;
	
	//SysTick (Used as Delay Source)
	self->systick.reg = (SysTick_Type*) SysTick_BASE;
	self->systick.delay_ms = STM32446delay_ms;
	self->systick.delay_10us = STM32446delay_10us;
	
	/**random order**/
	
	//TIM9
	self->tim9.reg = (TIM_TypeDef*) TIM9_BASE;
	
	//ADC1
	self->adc1.reg = (ADC_TypeDef*) ADC1_BASE;
	self->adc1.Ex1inic = STM32446Adc1Ex1inic;
	self->adc1.Discontinuous1 = STM32446Adc1Disc1;
	
	//ADC COMMON
	self->adc123.reg =	(ADC_Common_TypeDef*) ADC123_COMMON_BASE;
	
	//USART1
	self->usart1.reg = (USART_TypeDef*) USART1_BASE;
	//ret.usart1.parameters = STM32446usart1parameters; // this exceeds uvision trial version limits, what a bummer.
	
	/*** INICS ***/
	self->inic.peripheral = STM32446PeripheralInic;
	
	/*** FUNCS ***/
	self->func.bcd2dec = STM32446bcd2dec;
	self->func.dec2bcd = STM32446dec2bcd;
	self->func.triggerA = STM32446triggerA;
	self->func.triggerB = STM32446triggerB;
	self->func.ReadHLByte = STM32ReadHLByte;
	self->func.ReadLHByte = STM32ReadLHByte;
	self->func.WriteHLByte = STM32WriteHLByte;
	self->func.WriteLHByte = STM32WriteLHByte;
	self->func.SwapByte = STM32SwapByte;
	self->func.setpins = STM32446GpioSetpins;
	self->func.setpin = STM32446GpioSetpin;
	self->func.resetpins = STM32446GpioResetpins;
	self->func.resetpin = STM32446GpioResetpin;
	
	stm32f446 = self;
	/****************************************************************************/
	SystickInic(); // Polling delay source.
	/****************************************************************************/
}

/******************************************************************************/
/*******************************/
/*************INICS*************/
/*******************************/
// peripheral
uint8_t STM32446PeripheralInic(void)
{
	uint8_t clkused; // First turn it on then select it or enable it.
	// System Clock Source
	stm32f446->rcc.reg->CR |= (1 << 0); // 0 - HSI, 16 - HSE
	for( ; !(stm32f446->rcc.reg->CR & (1 << 1)) ; ); // // 1 - HSI, 17 - HSE
	// System Clock Select or Enable
	stm32f446->rcc.reg->CFGR &= (uint32_t) ~(3 << 0); // SW[1:0]: System clock switch 00 - HSI, 01 - HSE pg133
	// System Clock Selected
	clkused = (uint8_t) (stm32f446->rcc.reg->CFGR >> 2); // SWS[1:0]: System clock switch status pg133
	clkused &= 3;
	
	// Low Speed Internal Clock turned on as default
	stm32f446->rcc.reg->CSR |= (1 << 0); // Internal low-speed oscillator enable
	for( ; !(stm32f446->rcc.reg->CSR & (1 << 1)) ; ); // Internal low-speed oscillator ready
	
	return clkused;
}
/*******************************/
/*************FUNCS*************/
/*******************************/
//GPIO
void STM32446GpioSetpins( GPIO_TypeDef* reg, int n_pin, ... )
{
	uint8_t i;
	int pin[32];

	if(n_pin > 0 && n_pin < 33){ // Filter input
		va_list list;
		va_start(list, n_pin);
		for(i = 0; i < n_pin; i++){
			pin[i] = va_arg(list, int);
			reg->BSRR = (1 << pin[i]);
		}
		va_end(list);
	}
}

void STM32446GpioSetpin( GPIO_TypeDef* reg, int pin )
{
			reg->BSRR = (1 << pin);
}

void STM32446GpioResetpins( GPIO_TypeDef* reg, int n_pin, ... )
{
	uint8_t i;
	int pin[32];
	
	if(n_pin > 0 && n_pin < 33){ // Filter input
		va_list list;
		va_start(list, n_pin);
		for(i = 0; i < n_pin; i++){
			pin[i] = va_arg(list, int);
			reg->BSRR = (unsigned int)((1 << pin[i]) << 16);
		}
		va_end(list);
	}
}

void STM32446GpioResetpin( GPIO_TypeDef* reg, int pin )
{
			reg->BSRR = (unsigned int)((1 << pin) << 16);
}

// RTC
uint8_t STM32446RtcInic(uint8_t clock)
{
	uint8_t status = 255;
	STM32446TimeTr = stm32f446->rtc.reg->TR;
	STM32446DateDr = stm32f446->rtc.reg->DR;
	
	status = STM32446RtcAccess(clock);
	
	//Some help from youtube vids
	//stm32f446->rcc.reg->CFGR &= (uint32_t) ~((1 << 0) | (1 << 1)); // RCC_CFGR sw[2:0] 00 Bits 1:0
	//stm32f446->rcc.reg->CFGR &= (uint32_t) ~((1 << 20) | (1 << 19) | (1 << 18) | (1 << 17) | (1 << 16)); // RCC_CFGR RTCPRE[4:0] 00010: HSE/2 Bits 20:16
	//stm32f446->rcc.reg->CFGR |= (uint32_t) (1 << 17); // RCC_CFGR RTCPRE[4:0] 00010: HSE/2 Bits
	
	stm32f446->rcc.reg->BDCR |= (1 << 15); // RTCEN: RTC clock enable
	
	//5 - Enter the "key" to unlock write protection
	stm32f446->rtc.reg->WPR |= 0xCA;
	stm32f446->rtc.reg->WPR |= 0x53;
	//stm32f446->rtc.reg->ISR &= (uint32_t) ~((1 << 3) | (1 << 5) | (1 << 7));

	//6 - Set INIT bit and wait for ready flag
	stm32f446->rtc.reg->ISR |= (1 << 7); // INIT: Initialization mode
	while( !(stm32f446->rtc.reg->ISR & (1 << 6)) ); // INITF: Initialization flag
	status = 6;

	//7 - Adjust prescaler values for RTC to obtain 1 Hz
	//stm32f446->rtc-reg->PRER |= 0xF9;
	//stm32f446->rtc.reg->PRER |= (0x7F << 16);
	
	//8 - Write Time and Date values
	//stm32f446->rtc.reg->TR |= 0x130000;
	//stm32f446->rtc.reg->TR |= 0x5700;
	//stm32f446->rtc.reg->DR |= 0x215124;
	
	//9 - Set BYPSHAD bit
	// must read twice
	//stm32f446->rtc.reg->CR |= (1 << 5); // BYPSHAD: Bypass the shadow registers
	// read only once
	stm32f446->rtc.reg->CR &= (uint32_t) ~(1 << 5); // BYPSHAD: Disable Bypass the shadow registers
	
	//10 - Clear INIT bit
	stm32f446->rtc.reg->ISR &= (uint32_t) ~(1 << 7);
	
	//11 - Disable access to RTC registers
	stm32f446->pwr.reg->CR &= (uint32_t) ~(1 << 8);

	return status;
}

void STM32446RtcHour(uint8_t hour)
{
	uint8_t t, u;
	const uint32_t mask = 0x003F0000;
	
	t = stm32f446->func.dec2bcd(hour / 10);
	u = stm32f446->func.dec2bcd(hour % 10);
	STM32446TimeTr &= (uint32_t) ~mask; // clear ht and hu 
	// hu, ht
	STM32446TimeTr |= (uint32_t) ((u << 16) | (t << 20));
	STM32446RtcSetTr();
}

void STM32446RtcMinute(uint8_t minute)
{
	uint8_t t, u;
	const uint32_t mask = 0x00007F00;
	
	t = stm32f446->func.dec2bcd(minute / 10);
	u = stm32f446->func.dec2bcd(minute % 10);
	STM32446TimeTr &= (uint32_t) ~mask; // clear mnt and mnu 
	// mnu, mnt
	STM32446TimeTr |= (uint32_t) ((u << 8) | (t << 12));
	STM32446RtcSetTr();
}

void STM32446RtcSecond(uint8_t second)
{
	uint8_t t, u;
	const uint32_t mask = 0x0000007F;
	
	t = stm32f446->func.dec2bcd(second / 10);
	u = stm32f446->func.dec2bcd(second % 10);
	STM32446TimeTr &= (uint32_t) ~mask; // clear st and su 
	// su, st
	STM32446TimeTr |= (uint32_t) ((u << 0) | (t << 4));
	STM32446RtcSetTr();
}

void STM32446RtcYear(uint8_t year)
{
	uint8_t t, u;
	const uint32_t mask = 0x00FF0000;
	
	t = stm32f446->func.dec2bcd(year / 10);
	u = stm32f446->func.dec2bcd(year % 10);
	STM32446DateDr &= (uint32_t) ~mask; // clear YT and YU 
	// YU, YT
	STM32446DateDr |= (uint32_t) ((u << 16) | (t << 20));
	STM32446RtcSetDr();
}

void STM32446RtcWeekDay(uint8_t weekday)
{
	uint8_t u;
	const uint32_t mask = 0x0000E0000;
	
	u = stm32f446->func.dec2bcd(weekday % 10);
	STM32446DateDr &= (uint32_t) ~mask; // clear WDU 
	// WDU
	STM32446DateDr |= (uint32_t) (u << 13);
	STM32446RtcSetDr();
}

void STM32446RtcMonth(uint8_t month)
{
	uint8_t t, u;
	const uint32_t mask = 0x00001F00;
	
	t = stm32f446->func.dec2bcd(month / 10);
	u = stm32f446->func.dec2bcd(month % 10);
	STM32446DateDr &= (uint32_t) ~mask; // clear MT and MU 
	// MU, MT
	STM32446DateDr |= (uint32_t) ((u << 8) | (t << 12));
	STM32446RtcSetDr();
}

void STM32446RtcDay(uint8_t day)
{
	uint8_t t, u;
	const uint32_t mask = 0x0000003F;
	
	t = stm32f446->func.dec2bcd(day / 10);
	u = stm32f446->func.dec2bcd(day % 10);
	STM32446DateDr &= (uint32_t) ~mask; // clear DT and DU 
	// DU, DT
	STM32446DateDr |= (uint32_t) ((u << 0) | (t << 4));
	STM32446RtcSetDr();
}

void STM32446RtcRegWrite(volatile uint32_t* reg, uint32_t data)
{
	//1 - Enable access to the RTC registers
	stm32f446->pwr.reg->CR |= (1 << 8); // Disable backup domain write protection
	//2 - Enter the "key" to unlock write protection	
	stm32f446->rtc.reg->WPR |= 0xCA;
	stm32f446->rtc.reg->WPR |= 0x53;
	//3 - Write
	
	*reg = data;
	
	//4 - Disable access to RTC registers	
	stm32f446->pwr.reg->CR &= (uint32_t) ~(1 << 8);
}

void STM32446Rtcdr2vec(char* vect)
{
	uint32_t dr = stm32f446->rtc.reg->DR;
	// YT
	vect[0] = (uint8_t) (dr >> 20) & 0x0F;
	vect[0] = stm32f446->func.bcd2dec(vect[0]);
	// YU
	vect[1] = (uint8_t) (dr >> 16) & 0x0F;
	vect[1] = stm32f446->func.bcd2dec(vect[1]);
	// WDU
	vect[2] = (uint8_t) (dr >> 13) & 0x07;
	vect[2] = stm32f446->func.bcd2dec(vect[2]);
	// MT
	vect[3] = (uint8_t) (dr >> 12) & 0x01;
	vect[3] = stm32f446->func.bcd2dec(vect[3]);
	// MU
	vect[4] = (uint8_t) (dr >> 8) & 0x0F;
	vect[4] = stm32f446->func.bcd2dec(vect[4]);
	// DT
	vect[5] = (uint8_t) (dr >> 4) & 0x03;
	vect[5] = stm32f446->func.bcd2dec(vect[5]);
	// DU
	vect[6] = (uint8_t) dr & 0x0F;
	vect[6] = stm32f446->func.bcd2dec(vect[6]);
	// Store Value
	STM32446DateDr = dr;
}

void STM32446Rtctr2vec(char* vect)
{
	uint32_t tr = stm32f446->rtc.reg->TR;
	if(stm32f446->rtc.reg->ISR & (1 << 5)){ // RSF: Registers synchronization flag
		// ht
		vect[0] = (uint8_t) (tr >> 20) & 0x03;
		vect[0] = stm32f446->func.bcd2dec(vect[0]);
		// hu
		vect[1] = (uint8_t) (tr >> 16) & 0x0F;
		vect[1] = stm32f446->func.bcd2dec(vect[1]);
		// mnt
		vect[2] = (uint8_t) (tr >> 12) & 0x07;
		vect[2] = stm32f446->func.bcd2dec(vect[2]);
		// mnu
		vect[3] = (uint8_t) (tr >> 8) & 0x0F;
		vect[3] = stm32f446->func.bcd2dec(vect[3]);
		// st
		vect[4] = (uint8_t) (tr >> 4) & 0x07;
		vect[4] = stm32f446->func.bcd2dec(vect[4]);
		// su
		vect[5] = (uint8_t) tr & 0x0F;
		vect[5] = stm32f446->func.bcd2dec(vect[5]);
		// Store value
		STM32446TimeTr = tr;
		// Clear Registers synchronization flag
		stm32f446->rtc.reg->ISR &= (uint32_t) ~(1 << 5);
	}
}

//ADC1
void STM32446Adc1Ex1inic(void)
{
	/***ADC Clock***/
	stm32f446->rcc.reg->APB1ENR |= (1 << 29); // DACEN: DAC interface clock enable
	stm32f446->rcc.reg->APB2ENR |= (1 << 8); // ADC1EN: ADC1 clock enable
	/***ADC CONFIG***/
	stm32f446->adc1.reg->CR2 |= (1 << 10); // EOCS: End of conversion selection
	stm32f446->adc123.reg->CCR |= (3 << 16); // ADCPRE: ADC prescaler, 11: PCLK2 divided by 8
	stm32f446->adc1.reg->SMPR1 |= (7 << 24); // SMPx[2:0]: Channel x sampling time selection
	stm32f446->adc1.reg->CR1 |= (1 << 11); // DISCEN: Discontinuous mode on regular channels
	stm32f446->adc1.reg->SQR3 |= 18; // SQ1[4:0]: 1st conversion in regular sequence
	// turn on select source and start reading
	stm32f446->adc1.reg->CR2 |= (1 << 0); // ADON: A/D Converter ON / OFF
	//Temperature (in °C) = {(VSENSE – V25) / Avg_Slope} + 25
	stm32f446->adc123.reg->CCR |= (1 << 23); // TSVREFE: Temperature sensor and VREFINT enable 
	//stm.adc123.reg->CCR |= (1 << 22); // VBATE: VBAT enable
	stm32f446->adc1.reg->CR2 |= (1 << 30); // SWSTART: Start conversion of regular channels
}

void STM32446Adc1Disc1(uint32_t counter, uint32_t threshold, uint32_t interval, uint32_t* trigger)
{
	if(stm32f446->adc1.reg->SR & (1 << 1)){ // EOC: Regular channel end of conversion
		*trigger = counter + interval;
		if( *trigger > (threshold - 1) )
			*trigger = (*trigger - threshold);
	}else{
		if(*trigger == counter)
			stm32f446->adc1.reg->CR2 |= (1 << 30); // SWSTART: Start conversion of regular channels;	
	}
}

//USART1
void STM32446usart1transmitsetup(void) //RM0390 pg801
{
/******************************************************************************
	Procedure:
1. Enable the USART by writing the UE bit in USART_CR1 register to 1.
2. Program the M bit in USART_CR1 to define the word length.
3. Program the number of stop bits in USART_CR2.
4. Select DMA enable (DMAT) in USART_CR3 if Multi buffer Communication is to take
   place. Configure the DMA register as explained in multibuffer communication.
5. Select the desired baud rate using the USART_BRR register.
6. Set the TE bit in USART_CR1 to send an idle frame as first transmission.
7. Write the data to send in the USART_DR register (this clears the TXE bit). Repeat this
   for each data to be transmitted in case of single buffer.
8. After writing the last data into the USART_DR register, wait until TC=1. This indicates
   that the transmission of the last frame is complete. This is required for instance when
   the USART is disabled or enters the Halt mode to avoid corrupting the last
   transmission.
*******************************************************************************/
	
	stm32f446->usart1.reg->CR1 |= (1 << 13); // UE: USART enable
	
	//stm32f446->usart1.parameters( 8, 16, 1, 9600 ); // Default
	
	stm32f446->usart1.reg->CR3 &= (uint32_t) ~(1 << 7); // DMAT: DMA enable transmitter - disabled
	
	stm32f446->usart1.reg->CR1 |= (1 << 3); // TE: Transmitter enable
	
	stm32f446->usart1.reg->DR = 'A';

	//on real aplication, use fall threw method in main 
	for( ; stm32f446->usart1.reg->SR & (1 << 6); ); // TC: Transmission complete
	
	// added this as disable after confirmed end of transmission [9]
	stm32f446->usart1.reg->CR1 &= (uint32_t) ~(1 << 13); // UE: USART desable
}

void STM32446usart1recievesetup(void) //RM0390 pg804
{
/******************************************************************************
	Procedure:
1.	Enable the USART by writing the UE bit in USART_CR1 register to 1.
2.	Program the M bit in USART_CR1 to define the word length.
3.	Program the number of stop bits in USART_CR2.
4.	Select DMA enable (DMAR) in USART_CR3 if multibuffer communication is to take
		place. Configure the DMA register as explained in multibuffer communication. STEP 3
5.	Select the desired baud rate using the baud rate register USART_BRR
6.	Set the RE bit USART_CR1. This enables the receiver that begins searching for a start
		bit.
*******************************************************************************/
	
	stm32f446->usart1.reg->CR1 |= (1 << 13); // UE: USART enable
	
	//stm32f446->usart1.parameters( 8, 16, 1, 9600 ); // Default
	
	stm32f446->usart1.reg->CR3 &= (uint32_t) ~(1 << 6); // DMAR: DMA enable receiver - disabled
	
	stm32f446->usart1.reg->CR1 |= (1 << 2); // RE: Receiver enable	
}

void STM32446usart1parameters( uint8_t wordlength, uint8_t samplingmode, double stopbits, uint32_t baudrate )
/******************************************************************************
Sets the usart parameters, using real values.
*******************************************************************************/
{
	uint8_t sampling;
	double value, fracpart, intpart;
	
	if(wordlength == 9)
		stm32f446->usart1.reg->CR1 |= (1 << 12); // M: Word length, 1 - 9bit.
	else if(wordlength == 8)
		stm32f446->usart1.reg->CR1 &= (uint32_t) ~(1 << 12); // M: Word length, 0 - 8bit.
	else
		stm32f446->usart1.reg->CR1 &= (uint32_t) ~(1 << 12); // M: Word length, 0 - 8bit, default.
	
	if(samplingmode == 8){
		sampling = 8;
		stm32f446->usart1.reg->CR1 |= (1 << 15); // OVER8: Oversampling mode, 1 - 8.
	}else if(samplingmode == 16){
		sampling = 16;
		stm32f446->usart1.reg->CR1 &= (uint32_t) ~(1 << 15); // OVER8: Oversampling mode, 0 - 16.
	}else{
		sampling = 16;
		stm32f446->usart1.reg->CR1 &= (uint32_t) ~(1 << 15); // OVER8: Oversampling mode, 0 - 16, default.
	}
	
	stm32f446->usart1.reg->CR2 &= (uint32_t) ~((1 << 13) | (1 << 12)); // STOP: STOP bits 00 - 1stopbit, default.
	if(fabs(stopbits - 0.5) < 0.00001) // STOP: STOP bits, 01: 0.5 Stop bit
		stm32f446->usart1.reg->CR2 |= (1 << 12);
	else if(fabs(stopbits - 1) < 0.00001) // STOP: STOP bits, 00: 1 Stop bit.
		stm32f446->usart1.reg->CR2 &= (uint32_t) ~((1 << 13) | (1 << 12));
	else if(fabs(stopbits - 1.5) < 0.00001) // STOP: STOP bits, 11: 1.5 Stop bit
		stm32f446->usart1.reg->CR2 |= ((1 << 13) | (1 << 12));
	else if(fabs(stopbits - 2) < 0.00001) // STOP: STOP bits, 10: 2 Stop bits
		stm32f446->usart1.reg->CR2 |= (1 << 13);
	
	value = (double) SystemCoreClock / ( sampling * baudrate );
	fracpart = modf(value, &intpart);
	
	stm32f446->usart1.reg->BRR = 0; // clean slate, reset.
	if(samplingmode == 16){
		stm32f446->usart1.reg->BRR = (uint32_t) (round(fracpart * 16)); // DIV_Fraction
		stm32f446->usart1.reg->BRR |= ((uint32_t) intpart << 4); // DIV_Mantissa[11:0]
	}else if(samplingmode == 8){
		stm32f446->usart1.reg->BRR = (uint32_t) (round(fracpart * 8)); // DIV_Fraction
		stm32f446->usart1.reg->BRR |= ((uint32_t) intpart << 4); // DIV_Mantissa[11:0]
	}else{
		stm32f446->usart1.reg->BRR = (uint32_t) (round(fracpart * 16)); // DIV_Fraction
		stm32f446->usart1.reg->BRR |= ((uint32_t) intpart << 4); // DIV_Mantissa[11:0], default.
	}
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
					mem[3] = ((uint32_t)~(0) - mem[1]) + mem[2];
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
					nen[3] = ((uint32_t)~(0) - nen[1]) + nen[2];
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
	stm32f446->pwr.reg->CR |= (1 << 8); // Disable backup domain write protection
	//2 - Enter the "key" to unlock write protection	
	stm32f446->rtc.reg->WPR |= 0xCA;
	stm32f446->rtc.reg->WPR |= 0x53;
	//3 - Set INIT bit and wait for ready flag
	stm32f446->rtc.reg->ISR |= (1 << 7); // INIT: Initialization mode
	while( !(stm32f446->rtc.reg->ISR & (1 << 6)) ); // INITF: Initialization flag
	//4 - Setup
	
	stm32f446->rtc.reg->TR = STM32446TimeTr;
	
	//5 - Clear INIT bit
	stm32f446->rtc.reg->ISR &= (uint32_t) ~(1 << 7);
	//6 - Disable access to RTC registers	
	stm32f446->pwr.reg->CR &= (uint32_t) ~(1 << 8);
}

void STM32446RtcSetDr(void)
{
	//1 - Enable access to the RTC registers
	stm32f446->pwr.reg->CR |= (1 << 8); // Disable backup domain write protection
	//2 - Enter the "key" to unlock write protection	
	stm32f446->rtc.reg->WPR |= 0xCA;
	stm32f446->rtc.reg->WPR |= 0x53;
	//3 - Set INIT bit and wait for ready flag
	stm32f446->rtc.reg->ISR |= (1 << 7); // INIT: Initialization mode
	while( !(stm32f446->rtc.reg->ISR & (1 << 6)) ); // INITF: Initialization flag
	//4 - Setup
	
	stm32f446->rtc.reg->DR = STM32446DateDr;
	
	//5 - Clear INIT bit
	stm32f446->rtc.reg->ISR &= (uint32_t) ~(1 << 7);
	//6 - Disable access to RTC registers	
	stm32f446->pwr.reg->CR &= (uint32_t) ~(1 << 8);
}

uint8_t STM32446RtcAccess(uint8_t clock)
{
	uint8_t status;
	
	//RM0390 pg 94
	//RTC access
	//1 - Enable the power interface clock by setting the PWREN bits in the RCC_APB1ENR
	stm32f446->rcc.reg->APB1ENR |= (1 << 28); // Power interface clock enable
	//RCC->APB1ENR |= ((1 << 11) | (1 << 28));

	//2 - Set the DBP bit in the PWR power control register (PWR_CR)
	stm32f446->pwr.reg->CR |= (1 << 8); // Disable backup domain write protection

	//3 - Select the RTC clock source RTC/AWU clock
	switch(clock){
		case 0:
			stm32f446->rcc.reg->CSR |= (1 << 0); // Internal low-speed oscillator turned on
			for( ; !(stm32f446->rcc.reg->CSR & (1 << 1)) ; ); // Internal low-speed oscillator ready
			status = 0;
			break;
		case 1:
			stm32f446->rcc.reg->BDCR |= 1; // Activate LSEON
			for( ; !(stm32f446->rcc.reg->BDCR & 2) ; ); // check flag to see if ready (LSERDY)
			status = 1;
			break;
		case 2:
			//stm32f446->rcc.reg->BDCR |= 4; // Activate LSEBYP
			//stm32f446->rcc.reg->BDCR |= 1; // Activate LSEON
			//for( ; !(stm32446->rcc.reg->BDCR & 2) ; ); // check flag to see if ready (LSERDY)
			status = 2;
			break;
		case 3:
			// LSI
			stm32f446->rcc.reg->CSR |= (1 << 0); // Internal low-speed oscillator turned on
			for( ; !(stm32f446->rcc.reg->CSR & (1 << 1)) ; ); // Internal low-speed oscillator ready
			// LSE
			stm32f446->rcc.reg->BDCR |= (1 << 0); // Activate LSEON
			for( ; !(stm32f446->rcc.reg->BDCR & (1 << 1)) ; ); // check flag to see if ready (LSERDY)
			status = 3;
			break;
		default:
			stm32f446->rcc.reg->CSR |= (1 << 0); // Internal low-speed oscillator turned on
			for( ; !(stm32f446->rcc.reg->CSR & (1 << 1)) ; ); // Internal low-speed oscillator ready
			status = 4;
			break;
	}
	
	//4 - RTCSEL[1:0]: RTC clock source selection
	switch(clock){
		case 0:
			stm32f446->rcc.reg->BDCR &= (uint32_t) ~((1 << 9) | (1 << 8)); // RTCSEL[1:0]: RTC clock source selection
			stm32f446->rcc.reg->BDCR |= (1 << 9); // LSI oscillator clock used as the RTC clock
			status = 5;
			break;
		case 1:
			stm32f446->rcc.reg->BDCR &= (uint32_t) ~((1 << 9) | (1 << 8)); // RTCSEL[1:0]: RTC clock source selection
			stm32f446->rcc.reg->BDCR |= (1 << 8); // LSE oscillator clock used as the RTC clock
			status = 6;
			break;
		case 2:
			stm32f446->rcc.reg->BDCR &= (uint32_t) ~((1 << 9) | (1 << 8)); // RTCSEL[1:0]: RTC clock source selection
			stm32f446->rcc.reg->BDCR |= ((1 << 8) | (1 << 9)); // HSE oscillator clock divided by a programmable prescaler
			status = 7;
			break;
		case 3:
			stm32f446->rcc.reg->BDCR &= (uint32_t) ~((1 << 9) | (1 << 8)); // RTCSEL[1:0]: RTC clock source selection
			stm32f446->rcc.reg->BDCR |= (1 << 9); // LSI oscillator clock used as the RTC clock
			status = 8;
			break;
		default:
			stm32f446->rcc.reg->BDCR &= (uint32_t) ~((1 << 9) | (1 << 8)); // RTCSEL[1:0]: RTC clock source selection
			stm32f446->rcc.reg->BDCR |= (1 << 9); // LSI oscillator clock used as the RTC clock
			break;
	}
	return status;
}

//SRAM
void STM32446SramAccess(void)
{
	//RM0390 pg 94
	//SRAM access
	//0 - Power Up SRAM
	stm32f446->pwr.reg->CSR |= (1 << 9); // BRE: Backup regulator enable
	//Check ready flag Bit 3 BRR: Backup regulator ready
	for( ; !(stm32f446->pwr.reg->CSR & (1 << 3) )  ; ); // BRR: Backup regulator ready
	
	//1 - Enable the power interface clock by setting the PWREN bits in the RCC_APB1ENR
	stm32f446->rcc.reg->APB1ENR |= (1 << 28); // Power interface clock enable
	//RCC->APB1ENR |= ((1 << 11) | (1 << 28));

	//2 - Set the DBP bit in the PWR power control register (PWR_CR)
	stm32f446->pwr.reg->CR |= (1 << 8); // Disable backup domain write protection

	//3 - Enable the backup SRAM clock by setting BKPSRAMEN bit in the RCC_AHB1ENR
	stm32f446->rcc.reg->AHB1ENR |= (1 << 18); // BKPSRAMEN: Backup SRAM interface clock enable
}

// TEMPLATE
void template(void)
{ // the best procedure ever does absolutely nothing
	
}
/*******************************************************************************/
/*******************************************************************************/
// SYSTICK
void SystickInic(void)
{
	stm32f446->systick.reg->LOAD = (uint32_t)(SystemCoreClock - 1);
	stm32f446->systick.reg->VAL = 0UL;
	stm32f446->systick.reg->CTRL |= (1 << 1) |(1 << 2);
}
void STM32446delay_ms(uint32_t ms)
{
	stm32f446->systick.reg->LOAD = (uint32_t)((SystemCoreClock / 1000) - 1);
	// Enable the SysTick timer
	stm32f446->systick.reg->CTRL |= (1 << 0);
	// Wait for a specified number of milliseconds
	DelayCounter = 0;
	while (DelayCounter < ms);
	// Disable the SysTick timer
	stm32f446->systick.reg->CTRL &= (uint32_t)~(1 << 0);
}
void STM32446delay_10us(uint32_t us)
{
	stm32f446->systick.reg->LOAD = (uint32_t)((SystemCoreClock / 100000) - 1);
	// Enable the SysTick timer
	stm32f446->systick.reg->CTRL |= (1 << 0);
	// Wait for a specified number of milliseconds
	DelayCounter = 0;
	while (DelayCounter < us);
	// Disable the SysTick timer
	stm32f446->systick.reg->CTRL &= (uint32_t)~(1 << 0);
}
/***Interrupt Procedure***/
void SysTick_Handler(void)
{ // count down to zero systick interrupt and reload.
	DelayCounter++;
}
/********************************COMMENT****************************************
On all periferals, always have to take in cosideration the POWER [pwr] rail, the CLOCK rail [rcc] 
then the pin configuration.

Also be aware of the interupt flags have to be cleared after being fired and the interrupt been
received.
*******************************************************************************/

