/*************************************************************************
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
*************************************************************************/
#include "stm32446mapping.h"
#include "stm32446addresses.h"
#include <math.h>

/*
*** File Variable
*/

static STM32446 ret;

static const uint32_t SystemCoreClock = 16000000;

static volatile uint32_t DelayCounter;

static uint32_t STM32446TimeTr;
static uint32_t STM32446DateDr;

static volatile uint32_t mem[4];
static volatile uint32_t nen[4];

/*
*** Procedure and Functions Prototypes
*/

/***
**** INIC
***/
uint8_t STM32446PeripheralInic(void);

/***
**** FUNC
***/

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
void STM32446RtcRegWrite(uint32_t* reg, uint32_t data);

// ADC1
void STM32446Adc1Ex1inic(void);
void STM32446Adc1Disc1(uint32_t counter, uint32_t threshold, uint32_t interval, uint32_t* trigger);

// USART1
void STM32446usart1parameters( uint8_t wordlength, uint8_t samplingmode, double stopbits, uint32_t baudrate );

// MISCELLANEOUS
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

/***
**** FILE FUNC
***/

// SysTick
void SystickInic(void);
// RTC
void STM32446RtcSetTr(void);
void STM32446RtcSetDr(void);
uint8_t STM32446RtcAccess(uint8_t clock);
// SRAM
void STM32446SramAccess(void);
// USART1
void STM32446usart1transmitsetup(void);
void STM32446usart1recievesetup(void);
// Template
void template(void);

/*
*** Interrupt Prototype
*/

void SysTick_Handler(void);

/*
*** File Procedure and Functions
*/

STM32446 STM32446enable(void){
	mem[0] = 0;
	nen[0] = 0;
	
	/***INICS***/
	ret.inic.peripheral = STM32446PeripheralInic;
	
	/***FUNCS***/
	// FLASH
	ret.flash.reg = (STM32446Flash*) FLASH_R_BASE;
	// CRC
	ret.crc.reg = (STM32446Crc*) CRC_BASE;
	// PWR
	ret.pwr.reg = (STM32446Pwr*) PWR_BASE;
	// RCC
	ret.rcc.reg = (STM32446Rcc*) RCC_BASE;
	// GPIOA
	ret.gpioa.reg = (STM32446Gpio*) GPIOA_BASE;
	// GPIOB
	ret.gpiob.reg = (STM32446Gpio*) GPIOB_BASE;
	// GPIOC
	ret.gpioc.reg = (STM32446Gpio*) GPIOC_BASE;
	// GPIOD
	ret.gpiod.reg = (STM32446Gpio*) GPIOD_BASE;
	// GPIOE
	ret.gpioe.reg = (STM32446Gpio*) GPIOE_BASE;
	// GPIOH
	ret.gpioh.reg = (STM32446Gpio*) GPIOH_BASE;
	// RTC
	ret.rtc.reg = (STM32446Rtc*) RTC_BASE;
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
	// SYSCFG
	ret.syscfg.reg = (STM32446SysCfg*) SYSCFG_BASE;
	// DMA1
	ret.dma1.reg = (STM32446Dma1*) DMA1_BASE;
	// DMA2
	ret.dma2.reg = (STM32446Dma2*) DMA2_BASE;
	//NVIC
	ret.nvic.reg = (STM32446Nvic*) STM32446Nvicaddr;
	// SysTick
	ret.systick.reg = (STM32446Systick*) SysTick_BASE;
	ret.systick.delay_ms = STM32446delay_ms;
	ret.systick.delay_10us = STM32446delay_10us;
	/**random order**/
	// TIM9
	ret.tim9.reg = (STM32446Tim9*) TIM9_BASE;
	// ADC1
	ret.adc1.reg = (STM32446Adc*) ADC1_BASE;
	ret.adc1.Ex1inic = STM32446Adc1Ex1inic;
	ret.adc1.Discontinuous1 = STM32446Adc1Disc1;
	// ADC COMMON
	ret.adc123.reg =	(STM32446AdcCommon*) ADC123_COMMON_BASE;
	// USART1
	ret.usart1.reg = (STM32446Usart*) USART1_BASE;
	ret.usart1.parameters = STM32446usart1parameters;
	
	// MISCELLANEOUS
	ret.func.bcd2dec = STM32446bcd2dec;
	ret.func.dec2bcd = STM32446dec2bcd;
	ret.func.triggerA = STM32446triggerA;
	ret.func.triggerB = STM32446triggerB;
	ret.func.ReadHLByte = STM32ReadHLByte;
	ret.func.ReadLHByte = STM32ReadLHByte;
	ret.func.WriteHLByte = STM32WriteHLByte;
	ret.func.WriteLHByte = STM32WriteLHByte;
	ret.func.SwapByte = STM32SwapByte;
	
	/***FILE FUNC***/
	//SysTick
	SystickInic(); // Polling delay source.
	
	/***return copy of linked structs***/
	return ret;
}

/***Procedure and Funstions***/
// SYSTICK
void SystickInic(void)
{
	ret.systick.reg->load = (uint32_t)(SystemCoreClock - 1);
	ret.systick.reg->val = 0UL;
	ret.systick.reg->ctrl |= (1 << 1) |(1 << 2);
}
void STM32446delay_ms(uint32_t ms)
{
	ret.systick.reg->load = (uint32_t)((SystemCoreClock / 1000) - 1);
	// Enable the SysTick timer
	ret.systick.reg->ctrl |= (1 << 0);
	// Wait for a specified number of milliseconds
	DelayCounter = 0;
	while (DelayCounter < ms);
	// Disable the SysTick timer
	ret.systick.reg->ctrl &= (uint32_t)~(1 << 0);
}
void STM32446delay_10us(uint32_t us)
{
	ret.systick.reg->load = (uint32_t)((SystemCoreClock / 100000) - 1);
	// Enable the SysTick timer
	ret.systick.reg->ctrl |= (1 << 0);
	// Wait for a specified number of milliseconds
	DelayCounter = 0;
	while (DelayCounter < us);
	// Disable the SysTick timer
	ret.systick.reg->ctrl &= (uint32_t)~(1 << 0);
}
/***Interrupt Procedure***/
void SysTick_Handler(void)
{ // count down to zero systick interrupt and reload.
	DelayCounter++;
}

/*************INICS*************/

// peripheral
uint8_t STM32446PeripheralInic(void)
{
	uint8_t clkused; // First turn it on then select it or enable it.
	// System Clock Source
	ret.rcc.reg->cr |= (1 << 0); // 0 - HSI, 16 - HSE
	for( ; !(ret.rcc.reg->cr & (1 << 1)) ; ); // // 1 - HSI, 17 - HSE
	// System Clock Select or Enable
	ret.rcc.reg->cfgr &= (uint32_t) ~(3 << 0); // SW[1:0]: System clock switch 00 - HSI, 01 - HSE pg133
	// System Clock Selected
	clkused = (uint8_t) (ret.rcc.reg->cfgr >> 2); // SWS[1:0]: System clock switch status pg133
	clkused &= 3;
	
	// Low Speed Internal Clock turned on as default
	ret.rcc.reg->csr |= (1 << 0); // Internal low-speed oscillator enable
	for( ; !(ret.rcc.reg->csr & (1 << 1)) ; ); // Internal low-speed oscillator ready
	
	return clkused;
}

/*************FUNCS*************/

// RTC
uint8_t STM32446RtcInic(uint8_t clock)
{
	uint8_t status = 255;
	STM32446TimeTr = ret.rtc.reg->tr;
	STM32446DateDr = ret.rtc.reg->dr;
	
	status = STM32446RtcAccess(clock);
	
	//Some help from youtube vids
	//ret.rcc.reg->cfgr &= (uint32_t) ~((1 << 0) | (1 << 1)); // RCC_CFGR sw[2:0] 00 Bits 1:0
	//ret.rcc.reg->cfgr &= (uint32_t) ~((1 << 20) | (1 << 19) | (1 << 18) | (1 << 17) | (1 << 16)); // RCC_CFGR RTCPRE[4:0] 00010: HSE/2 Bits 20:16
	//ret.rcc.reg->cfgr |= (uint32_t) (1 << 17); // RCC_CFGR RTCPRE[4:0] 00010: HSE/2 Bits
	
	ret.rcc.reg->bdcr |= (1 << 15); // RTCEN: RTC clock enable
	
	//5 - Enter the "key" to unlock write protection
	ret.rtc.reg->wpr |= 0xCA;
	ret.rtc.reg->wpr |= 0x53;
	//ret.rtc.reg->isr &= (uint32_t) ~((1 << 3) | (1 << 5) | (1 << 7));

	//6 - Set INIT bit and wait for ready flag
	ret.rtc.reg->isr |= (1 << 7); // INIT: Initialization mode
	while( !(ret.rtc.reg->isr & (1 << 6)) ); // INITF: Initialization flag
	status = 6;

	//7 - Adjust prescaler values for RTC to obtain 1 Hz
	//ret.rtc-reg->prer |= 0xF9;
	//ret.rtc.reg->prer |= (0x7F << 16);
	
	//8 - Write Time and Date values
	//ret.rtc.reg->tr |= 0x130000;
	//ret.rtc.reg->tr |= 0x5700;
	//ret.rtc.reg->dr |= 0x215124;
	
	//9 - Set BYPSHAD bit
	// must read twice
	//ret.rtc.reg->cr |= (1 << 5); // BYPSHAD: Bypass the shadow registers
	// read only once
	ret.rtc.reg->cr &= (uint32_t) ~(1 << 5); // BYPSHAD: Disable Bypass the shadow registers
	
	//10 - Clear INIT bit
	ret.rtc.reg->isr &= (uint32_t) ~(1 << 7);
	
	//11 - Disable access to RTC registers
	ret.pwr.reg->cr &= (uint32_t) ~(1 << 8);

	return status;
}

void STM32446RtcHour(uint8_t hour)
{
	uint8_t t, u;
	const uint32_t mask = 0x003F0000;
	
	t = ret.func.dec2bcd(hour / 10);
	u = ret.func.dec2bcd(hour % 10);
	STM32446TimeTr &= (uint32_t) ~mask; // clear ht and hu 
	// hu, ht
	STM32446TimeTr |= (uint32_t) ((u << 16) | (t << 20));
	STM32446RtcSetTr();
}

void STM32446RtcMinute(uint8_t minute)
{
	uint8_t t, u;
	const uint32_t mask = 0x00007F00;
	
	t = ret.func.dec2bcd(minute / 10);
	u = ret.func.dec2bcd(minute % 10);
	STM32446TimeTr &= (uint32_t) ~mask; // clear mnt and mnu 
	// mnu, mnt
	STM32446TimeTr |= (uint32_t) ((u << 8) | (t << 12));
	STM32446RtcSetTr();
}

void STM32446RtcSecond(uint8_t second)
{
	uint8_t t, u;
	const uint32_t mask = 0x0000007F;
	
	t = ret.func.dec2bcd(second / 10);
	u = ret.func.dec2bcd(second % 10);
	STM32446TimeTr &= (uint32_t) ~mask; // clear st and su 
	// su, st
	STM32446TimeTr |= (uint32_t) ((u << 0) | (t << 4));
	STM32446RtcSetTr();
}

void STM32446RtcYear(uint8_t year)
{
	uint8_t t, u;
	const uint32_t mask = 0x00FF0000;
	
	t = ret.func.dec2bcd(year / 10);
	u = ret.func.dec2bcd(year % 10);
	STM32446DateDr &= (uint32_t) ~mask; // clear YT and YU 
	// YU, YT
	STM32446DateDr |= (uint32_t) ((u << 16) | (t << 20));
	STM32446RtcSetDr();
}

void STM32446RtcWeekDay(uint8_t weekday)
{
	uint8_t u;
	const uint32_t mask = 0x0000E0000;
	
	u = ret.func.dec2bcd(weekday % 10);
	STM32446DateDr &= (uint32_t) ~mask; // clear WDU 
	// WDU
	STM32446DateDr |= (uint32_t) (u << 13);
	STM32446RtcSetDr();
}

void STM32446RtcMonth(uint8_t month)
{
	uint8_t t, u;
	const uint32_t mask = 0x00001F00;
	
	t = ret.func.dec2bcd(month / 10);
	u = ret.func.dec2bcd(month % 10);
	STM32446DateDr &= (uint32_t) ~mask; // clear MT and MU 
	// MU, MT
	STM32446DateDr |= (uint32_t) ((u << 8) | (t << 12));
	STM32446RtcSetDr();
}

void STM32446RtcDay(uint8_t day)
{
	uint8_t t, u;
	const uint32_t mask = 0x0000003F;
	
	t = ret.func.dec2bcd(day / 10);
	u = ret.func.dec2bcd(day % 10);
	STM32446DateDr &= (uint32_t) ~mask; // clear DT and DU 
	// DU, DT
	STM32446DateDr |= (uint32_t) ((u << 0) | (t << 4));
	STM32446RtcSetDr();
}

void STM32446RtcRegWrite(uint32_t* reg, uint32_t data)
{
	//1 - Enable access to the RTC registers
	ret.pwr.reg->cr |= (1 << 8); // Disable backup domain write protection
	//2 - Enter the "key" to unlock write protection	
	ret.rtc.reg->wpr |= 0xCA;
	ret.rtc.reg->wpr |= 0x53;
	//3 - Write
	
	*reg = data;
	
	//4 - Disable access to RTC registers	
	ret.pwr.reg->cr &= (uint32_t) ~(1 << 8);
}

void STM32446Rtcdr2vec(char* vect)
{
	uint32_t dr = ret.rtc.reg->dr;
	// YT
	vect[0] = (uint8_t) (dr >> 20) & 0x0F;
	vect[0] = ret.func.bcd2dec(vect[0]);
	// YU
	vect[1] = (uint8_t) (dr >> 16) & 0x0F;
	vect[1] = ret.func.bcd2dec(vect[1]);
	// WDU
	vect[2] = (uint8_t) (dr >> 13) & 0x07;
	vect[2] = ret.func.bcd2dec(vect[2]);
	// MT
	vect[3] = (uint8_t) (dr >> 12) & 0x01;
	vect[3] = ret.func.bcd2dec(vect[3]);
	// MU
	vect[4] = (uint8_t) (dr >> 8) & 0x0F;
	vect[4] = ret.func.bcd2dec(vect[4]);
	// DT
	vect[5] = (uint8_t) (dr >> 4) & 0x03;
	vect[5] = ret.func.bcd2dec(vect[5]);
	// DU
	vect[6] = (uint8_t) dr & 0x0F;
	vect[6] = ret.func.bcd2dec(vect[6]);
	// Store Value
	STM32446DateDr = dr;
}

void STM32446Rtctr2vec(char* vect)
{
	uint32_t tr = ret.rtc.reg->tr;
	if(ret.rtc.reg->isr & (1 << 5)){ // RSF: Registers synchronization flag
		// ht
		vect[0] = (uint8_t) (tr >> 20) & 0x03;
		vect[0] = ret.func.bcd2dec(vect[0]);
		// hu
		vect[1] = (uint8_t) (tr >> 16) & 0x0F;
		vect[1] = ret.func.bcd2dec(vect[1]);
		// mnt
		vect[2] = (uint8_t) (tr >> 12) & 0x07;
		vect[2] = ret.func.bcd2dec(vect[2]);
		// mnu
		vect[3] = (uint8_t) (tr >> 8) & 0x0F;
		vect[3] = ret.func.bcd2dec(vect[3]);
		// st
		vect[4] = (uint8_t) (tr >> 4) & 0x07;
		vect[4] = ret.func.bcd2dec(vect[4]);
		// su
		vect[5] = (uint8_t) tr & 0x0F;
		vect[5] = ret.func.bcd2dec(vect[5]);
		// Store value
		STM32446TimeTr = tr;
		// Clear Registers synchronization flag
		ret.rtc.reg->isr &= (uint32_t) ~(1 << 5);
	}
}

// ADC1
void STM32446Adc1Ex1inic(void)
{
	/***ADC Clock***/
	ret.rcc.reg->apb1enr |= (1 << 29); // DACEN: DAC interface clock enable
	ret.rcc.reg->apb2enr |= (1 << 8); // ADC1EN: ADC1 clock enable
	/***ADC CONFIG***/
	ret.adc1.reg->cr2 |= (1 << 10); // EOCS: End of conversion selection
	ret.adc123.reg->ccr |= (3 << 16); // ADCPRE: ADC prescaler, 11: PCLK2 divided by 8
	ret.adc1.reg->smpr1 |= (7 << 24); // SMPx[2:0]: Channel x sampling time selection
	ret.adc1.reg->cr1 |= (1 << 11); // DISCEN: Discontinuous mode on regular channels
	ret.adc1.reg->sqr3 |= 18; // SQ1[4:0]: 1st conversion in regular sequence
	// turn on select source and start reading
	ret.adc1.reg->cr2 |= (1 << 0); // ADON: A/D Converter ON / OFF
	//Temperature (in °C) = {(VSENSE – V25) / Avg_Slope} + 25
	ret.adc123.reg->ccr |= (1 << 23); // TSVREFE: Temperature sensor and VREFINT enable 
	//stm.adc123.reg->ccr |= (1 << 22); // VBATE: VBAT enable
	ret.adc1.reg->cr2 |= (1 << 30); // SWSTART: Start conversion of regular channels
}

void STM32446Adc1Disc1(uint32_t counter, uint32_t threshold, uint32_t interval, uint32_t* trigger)
{
	if(ret.adc1.reg->sr & (1 << 1)){ // EOC: Regular channel end of conversion
		*trigger = counter + interval;
		if( *trigger > (threshold - 1) )
			*trigger = (*trigger - threshold);
	}else{
		if(*trigger == counter)
			ret.adc1.reg->cr2 |= (1 << 30); // SWSTART: Start conversion of regular channels;	
	}
}

// USART1

void STM32446usart1parameters( uint8_t wordlength, uint8_t samplingmode, double stopbits, uint32_t baudrate )
/*******************************************************************************
Sets the usart parameters, using real values.
*******************************************************************************/
{
	uint8_t sampling;
	double value, fracpart, intpart;
	
	if(wordlength == 9)
		ret.usart1.reg->cr1 |= (1 << 12); // M: Word length, 1 - 9bit.
	else if(wordlength == 8)
		ret.usart1.reg->cr1 &= (uint32_t) ~(1 << 12); // M: Word length, 0 - 8bit.
	else
		ret.usart1.reg->cr1 &= (uint32_t) ~(1 << 12); // M: Word length, 0 - 8bit, default.
	
	if(samplingmode == 8){
		sampling = 8;
		ret.usart1.reg->cr1 |= (1 << 15); // OVER8: Oversampling mode, 1 - 8.
	}else if(samplingmode == 16){
		sampling = 16;
		ret.usart1.reg->cr1 &= (uint32_t) ~(1 << 15); // OVER8: Oversampling mode, 0 - 16.
	}else{
		sampling = 16;
		ret.usart1.reg->cr1 &= (uint32_t) ~(1 << 15); // OVER8: Oversampling mode, 0 - 16, default.
	}
	
	ret.usart1.reg->cr2 &= (uint32_t) ~((1 << 13) | (1 << 12)); // STOP: STOP bits 00 - 1stopbit, default.
	if(fabs(stopbits - 0.5) < 0.00001) // STOP: STOP bits, 01: 0.5 Stop bit
		ret.usart1.reg->cr2 |= (1 << 12);
	else if(fabs(stopbits - 1) < 0.00001) // STOP: STOP bits, 00: 1 Stop bit.
		ret.usart1.reg->cr2 &= (uint32_t) ~((1 << 13) | (1 << 12));
	else if(fabs(stopbits - 1.5) < 0.00001) // STOP: STOP bits, 11: 1.5 Stop bit
		ret.usart1.reg->cr2 |= ((1 << 13) | (1 << 12));
	else if(fabs(stopbits - 2) < 0.00001) // STOP: STOP bits, 10: 2 Stop bits
		ret.usart1.reg->cr2 |= (1 << 13);
	
	value = (double) SystemCoreClock / ( sampling * baudrate );
	fracpart = modf(value, &intpart);
	
	ret.usart1.reg->brr = 0; // clean slate, reset.
	if(samplingmode == 16){
		ret.usart1.reg->brr = (uint32_t) (round(fracpart * 16)); // DIV_Fraction
		ret.usart1.reg->brr |= ((uint32_t) intpart << 4); // DIV_Mantissa[11:0]
	}else if(samplingmode == 8){
		ret.usart1.reg->brr = (uint32_t) (round(fracpart * 8)); // DIV_Fraction
		ret.usart1.reg->brr |= ((uint32_t) intpart << 4); // DIV_Mantissa[11:0]
	}else{
		ret.usart1.reg->brr = (uint32_t) (round(fracpart * 16)); // DIV_Fraction
		ret.usart1.reg->brr |= ((uint32_t) intpart << 4); // DIV_Mantissa[11:0], default.
	}
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

/***********FILE FUNC************/

// RTC
void STM32446RtcSetTr(void)
{
	//1 - Enable access to the RTC registers
	ret.pwr.reg->cr |= (1 << 8); // Disable backup domain write protection
	//2 - Enter the "key" to unlock write protection	
	ret.rtc.reg->wpr |= 0xCA;
	ret.rtc.reg->wpr |= 0x53;
	//3 - Set INIT bit and wait for ready flag
	ret.rtc.reg->isr |= (1 << 7); // INIT: Initialization mode
	while( !(ret.rtc.reg->isr & (1 << 6)) ); // INITF: Initialization flag
	//4 - Setup
	
	ret.rtc.reg->tr = STM32446TimeTr;
	
	//5 - Clear INIT bit
	ret.rtc.reg->isr &= (uint32_t) ~(1 << 7);
	//6 - Disable access to RTC registers	
	ret.pwr.reg->cr &= (uint32_t) ~(1 << 8);
}

void STM32446RtcSetDr(void)
{
	//1 - Enable access to the RTC registers
	ret.pwr.reg->cr |= (1 << 8); // Disable backup domain write protection
	//2 - Enter the "key" to unlock write protection	
	ret.rtc.reg->wpr |= 0xCA;
	ret.rtc.reg->wpr |= 0x53;
	//3 - Set INIT bit and wait for ready flag
	ret.rtc.reg->isr |= (1 << 7); // INIT: Initialization mode
	while( !(ret.rtc.reg->isr & (1 << 6)) ); // INITF: Initialization flag
	//4 - Setup
	
	ret.rtc.reg->dr = STM32446DateDr;
	
	//5 - Clear INIT bit
	ret.rtc.reg->isr &= (uint32_t) ~(1 << 7);
	//6 - Disable access to RTC registers	
	ret.pwr.reg->cr &= (uint32_t) ~(1 << 8);
}

uint8_t STM32446RtcAccess(uint8_t clock)
{
	uint8_t status;
	
	//RM0390 pg 94
	//RTC access
	//1 - Enable the power interface clock by setting the PWREN bits in the RCC_APB1ENR
	ret.rcc.reg->apb1enr |= (1 << 28); // Power interface clock enable
	//RCC->APB1ENR |= ((1 << 11) | (1 << 28));

	//2 - Set the DBP bit in the PWR power control register (PWR_CR)
	ret.pwr.reg->cr |= (1 << 8); // Disable backup domain write protection

	//3 - Select the RTC clock source RTC/AWU clock
	switch(clock){
		case 0:
			ret.rcc.reg->csr |= (1 << 0); // Internal low-speed oscillator turned on
			for( ; !(ret.rcc.reg->csr & (1 << 1)) ; ); // Internal low-speed oscillator ready
			status = 0;
			break;		
		case 1:
			ret.rcc.reg->bdcr |= 1; // Activate LSEON
			for( ; !(ret.rcc.reg->bdcr & 2) ; ); // check flag to see if ready (LSERDY)
			status = 1;
			break;
		case 2:
			//ret.rcc.reg->bdcr |= 4; // Activate LSEBYP
			//ret.rcc.reg->bdcr |= 1; // Activate LSEON
			//for( ; !(ret.rcc.reg->bdcr & 2) ; ); // check flag to see if ready (LSERDY)
			status = 2;
			break;
		case 3:
			// LSI
			ret.rcc.reg->csr |= (1 << 0); // Internal low-speed oscillator turned on
			for( ; !(ret.rcc.reg->csr & (1 << 1)) ; ); // Internal low-speed oscillator ready
			// LSE
			ret.rcc.reg->bdcr |= (1 << 0); // Activate LSEON
			for( ; !(ret.rcc.reg->bdcr & (1 << 1)) ; ); // check flag to see if ready (LSERDY)
			status = 3;
			break;
		default:
			ret.rcc.reg->csr |= (1 << 0); // Internal low-speed oscillator turned on
			for( ; !(ret.rcc.reg->csr & (1 << 1)) ; ); // Internal low-speed oscillator ready
			status = 4;
			break;
	}
	
	//4 - RTCSEL[1:0]: RTC clock source selection
	switch(clock){
		case 0:
			ret.rcc.reg->bdcr &= (uint32_t) ~((1 << 9) | (1 << 8)); // RTCSEL[1:0]: RTC clock source selection
			ret.rcc.reg->bdcr |= (1 << 9); // LSI oscillator clock used as the RTC clock
			status = 5;
			break;
		case 1:
			ret.rcc.reg->bdcr &= (uint32_t) ~((1 << 9) | (1 << 8)); // RTCSEL[1:0]: RTC clock source selection
			ret.rcc.reg->bdcr |= (1 << 8); // LSE oscillator clock used as the RTC clock
			status = 6;
			break;
		case 2:
			ret.rcc.reg->bdcr &= (uint32_t) ~((1 << 9) | (1 << 8)); // RTCSEL[1:0]: RTC clock source selection
			ret.rcc.reg->bdcr |= ((1 << 8) | (1 << 9)); // HSE oscillator clock divided by a programmable prescaler
			status = 7;
			break;
		case 3:
			ret.rcc.reg->bdcr &= (uint32_t) ~((1 << 9) | (1 << 8)); // RTCSEL[1:0]: RTC clock source selection
			ret.rcc.reg->bdcr |= (1 << 9); // LSI oscillator clock used as the RTC clock
			status = 8;
			break;
		default:
			ret.rcc.reg->bdcr &= (uint32_t) ~((1 << 9) | (1 << 8)); // RTCSEL[1:0]: RTC clock source selection
			ret.rcc.reg->bdcr |= (1 << 9); // LSI oscillator clock used as the RTC clock
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
	ret.pwr.reg->csr |= (1 << 9); // BRE: Backup regulator enable
	//Check ready flag Bit 3 BRR: Backup regulator ready
	for( ; !(ret.pwr.reg->csr & (1 << 3) )  ; ); // BRR: Backup regulator ready
	
	//1 - Enable the power interface clock by setting the PWREN bits in the RCC_APB1ENR
	ret.rcc.reg->apb1enr |= (1 << 28); // Power interface clock enable
	//RCC->APB1ENR |= ((1 << 11) | (1 << 28));

	//2 - Set the DBP bit in the PWR power control register (PWR_CR)
	ret.pwr.reg->cr |= (1 << 8); // Disable backup domain write protection

	//3 - Enable the backup SRAM clock by setting BKPSRAMEN bit in the RCC_AHB1ENR
	ret.rcc.reg->ahb1enr |= (1 << 18); // BKPSRAMEN: Backup SRAM interface clock enable
}

//USART1
void STM32446usart1transmitsetup(void) //RM0390 pg801
{
/***********************************************************************
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
**********************************************************************/
	
	ret.usart1.reg->cr1 |= (1 << 13); // UE: USART enable
	
	//ret.usart1.parameters( 8, 16, 1, 9600 ); // Default
	
	ret.usart1.reg->cr3 &= (uint32_t) ~(1 << 7); // DMAT: DMA enable transmitter - disabled
	
	ret.usart1.reg->cr1 |= (1 << 3); // TE: Transmitter enable
	
	ret.usart1.reg->dr = 'A';

	//on real aplication, use fall threw method in main 
	for( ; ret.usart1.reg->sr & (1 << 6); ); // TC: Transmission complete
	
	// added this as disable after confirmed end of transmission [9]
	ret.usart1.reg->cr1 &= (uint32_t) ~(1 << 13); // UE: USART desable
}

void STM32446usart1recievesetup(void) //RM0390 pg804
{
/***********************************************************************
	Procedure:
1.	Enable the USART by writing the UE bit in USART_CR1 register to 1.
2.	Program the M bit in USART_CR1 to define the word length.
3.	Program the number of stop bits in USART_CR2.
4.	Select DMA enable (DMAR) in USART_CR3 if multibuffer communication is to take
		place. Configure the DMA register as explained in multibuffer communication. STEP 3
5.	Select the desired baud rate using the baud rate register USART_BRR
6.	Set the RE bit USART_CR1. This enables the receiver that begins searching for a start
		bit.
**********************************************************************/
	
	ret.usart1.reg->cr1 |= (1 << 13); // UE: USART enable
	
	//ret.usart1.parameters( 8, 16, 1, 9600 ); // Default
	
	ret.usart1.reg->cr3 &= (uint32_t) ~(1 << 6); // DMAR: DMA enable receiver - disabled
	
	ret.usart1.reg->cr1 |= (1 << 2); // RE: Receiver enable	
}

// TEMPLATE
void template(void)
{ // the best procedure ever does absolutely nothing
	
}

/***EOF***/
/*** COMMENT
Make everything the most user friendly possible.
Connect existing libs, to facilitate expansion, and reduce code burden.

***/

