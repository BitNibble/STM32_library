/******************************************************************************
	STM32 446 RTC
Author: Sergio Santos 
	<sergio.salazar.santos@gmail.com>
License: GNU General Public License
Hardware: STM32-446
Date: 23052023
Comment:
	
*******************************************************************************/
/*** File Library ***/
#include "stm32446mapping.h"
//#include "stm32446rtc.h" // move this then to stm32446mapping header file.

/*** File Constant & Macros ***/

/*** File Variable ***/
static STM32446 stm32446;
static uint32_t STM32446TimeTr;
static uint32_t STM32446DateDr;

/*** File Header ***/
// RTC
uint8_t STM32446RtcInic(uint8_t clock);
void STM32446RtcDay(uint8_t day);
void STM32446RtcMonth(uint8_t month);
void STM32446RtcWeekDay(uint8_t weekday);
void STM32446RtcYear(uint8_t year);
void STM32446RtcHour(uint8_t hour);
void STM32446RtcMinute(uint8_t minute);
void STM32446RtcSecond(uint8_t second);
void STM32446Rtcdr2vec(char* rtc_vect);
void STM32446Rtctr2vec(char* rtc_vect);
void STM32446RtcRegWrite(volatile uint32_t* reg, uint32_t data);
// RTC
void STM32446RtcEnable(void);
void STM32446RtcSetTr(void);
void STM32446RtcSetDr(void);
uint8_t STM32446RtcAccess(uint8_t clock);

// RTC
STM32446RTC STM32446RTCenable(void)
{
	stm32446 = STM32446enable();
	STM32446RTC rtc;

	rtc.inic = STM32446RtcInic;
	rtc.Day = STM32446RtcDay;
	rtc.Month = STM32446RtcMonth;
	rtc.WeekDay = STM32446RtcWeekDay;
	rtc.Year = STM32446RtcYear;
	rtc.Hour = STM32446RtcHour;
	rtc.Minute = STM32446RtcMinute;
	rtc.Second = STM32446RtcSecond;
	rtc.dr2vec = STM32446Rtcdr2vec;
	rtc.tr2vec = STM32446Rtctr2vec;
	rtc.RegWrite = STM32446RtcRegWrite;

	STM32446RtcEnable();

	return rtc;
}

// RTC
void STM32446RtcEnable(void)
{
	stm32446.rcc.reg->BDCR |= (1 << 15); // RTCEN: RTC clock enable
}

uint8_t STM32446RtcInic(uint8_t clock)
{ // slow
	uint8_t status = 255;
	STM32446TimeTr = stm32446.rtc.reg->TR;
	STM32446DateDr = stm32446.rtc.reg->DR;
	
	status = STM32446RtcAccess(clock);
	
	// Some help from youtube vids
	//stm32446.rcc.reg->CFGR &= (uint32_t) ~((1 << 0) | (1 << 1)); // RCC_CFGR sw[2:0] 00 Bits 1:0
	//stm32446.rcc.reg->CFGR &= (uint32_t) ~((1 << 20) | (1 << 19) | (1 << 18) | (1 << 17) | (1 << 16)); // RCC_CFGR RTCPRE[4:0] 00010: HSE/2 Bits 20:16
	//stm32446.rcc.reg->CFGR |= (uint32_t) (1 << 17); // RCC_CFGR RTCPRE[4:0] 00010: HSE/2 Bits
	
	//STM32446RtcEnable();
	//stm32446.rcc.reg->BDCR |= (1 << 15); // RTCEN: RTC clock enable
	
	// 5 - Enter the "key" to unlock write protection
	stm32446.rtc.reg->WPR |= 0xCA;
	stm32446.rtc.reg->WPR |= 0x53;
	//stm32446.rtc.reg->ISR &= (uint32_t) ~((1 << 3) | (1 << 5) | (1 << 7));

	// 6 - Set INIT bit and wait for ready flag
	stm32446.rtc.reg->ISR |= (1 << 7); // INIT: Initialization mode
	while( !(stm32446.rtc.reg->ISR & (1 << 6)) ); // INITF: Initialization flag
	status = 6;

	// 7 - Adjust prescaler values for RTC to obtain 1 Hz
	//stm32446.rtc-reg->PRER |= 0xF9;
	//stm32446.rtc.reg->PRER |= (0x7F << 16);
	
	// 8 - Write Time and Date values
	//stm32446.rtc.reg->TR |= 0x130000;
	//stm32446.rtc.reg->TR |= 0x5700;
	//stm32446.rtc.reg->DR |= 0x215124;
	
	// 9 - Set BYPSHAD bit
	// must read twice
	//stm32446.rtc.reg->CR |= (1 << 5); // BYPSHAD: Bypass the shadow registers
	// read only once
	stm32446.rtc.reg->CR &= (uint32_t) ~(1 << 5); // BYPSHAD: Disable Bypass the shadow registers
	
	// 10 - Clear INIT bit
	stm32446.rtc.reg->ISR &= (uint32_t) ~(1 << 7);
	
	// 11 - Disable access to RTC registers
	stm32446.pwr.reg->CR &= (uint32_t) ~(1 << 8);

	return status;
}

void STM32446RtcHour(uint8_t hour)
{
	uint8_t t, u;
	const uint32_t mask = 0x003F0000;
	
	t = stm32446.func.dec2bcd(hour / 10);
	u = stm32446.func.dec2bcd(hour % 10);
	STM32446TimeTr = stm32446.rtc.reg->TR;
	STM32446TimeTr &= (uint32_t) ~mask; // clear ht and hu 
	// hu, ht
	STM32446TimeTr |= (uint32_t) ((u << 16) | (t << 20));
	STM32446RtcSetTr();
}

void STM32446RtcMinute(uint8_t minute)
{
	uint8_t t, u;
	const uint32_t mask = 0x00007F00;
	
	t = stm32446.func.dec2bcd(minute / 10);
	u = stm32446.func.dec2bcd(minute % 10);
	STM32446TimeTr = stm32446.rtc.reg->TR;
	STM32446TimeTr &= (uint32_t) ~mask; // clear mnt and mnu 
	// mnu, mnt
	STM32446TimeTr |= (uint32_t) ((u << 8) | (t << 12));
	STM32446RtcSetTr();
}

void STM32446RtcSecond(uint8_t second)
{
	uint8_t t, u;
	const uint32_t mask = 0x0000007F;
	
	t = stm32446.func.dec2bcd(second / 10);
	u = stm32446.func.dec2bcd(second % 10);
	STM32446TimeTr = stm32446.rtc.reg->TR;
	STM32446TimeTr &= (uint32_t) ~mask; // clear st and su 
	// su, st
	STM32446TimeTr |= (uint32_t) ((u << 0) | (t << 4));
	STM32446RtcSetTr();
}

void STM32446RtcYear(uint8_t year)
{
	uint8_t t, u;
	const uint32_t mask = 0x00FF0000;
	
	t = stm32446.func.dec2bcd(year / 10);
	u = stm32446.func.dec2bcd(year % 10);
	STM32446DateDr &= (uint32_t) ~mask; // clear YT and YU 
	// YU, YT
	STM32446DateDr |= (uint32_t) ((u << 16) | (t << 20));
	STM32446RtcSetDr();
}

void STM32446RtcWeekDay(uint8_t weekday)
{
	uint8_t u;
	const uint32_t mask = 0x0000E0000;
	
	u = stm32446.func.dec2bcd(weekday % 10);
	STM32446DateDr &= (uint32_t) ~mask; // clear WDU 
	// WDU
	STM32446DateDr |= (uint32_t) (u << 13);
	STM32446RtcSetDr();
}

void STM32446RtcMonth(uint8_t month)
{
	uint8_t t, u;
	const uint32_t mask = 0x00001F00;
	
	t = stm32446.func.dec2bcd(month / 10);
	u = stm32446.func.dec2bcd(month % 10);
	STM32446DateDr &= (uint32_t) ~mask; // clear MT and MU 
	// MU, MT
	STM32446DateDr |= (uint32_t) ((u << 8) | (t << 12));
	STM32446RtcSetDr();
}

void STM32446RtcDay(uint8_t day)
{
	uint8_t t, u;
	const uint32_t mask = 0x0000003F;
	
	t = stm32446.func.dec2bcd(day / 10);
	u = stm32446.func.dec2bcd(day % 10);
	STM32446DateDr &= (uint32_t) ~mask; // clear DT and DU 
	// DU, DT
	STM32446DateDr |= (uint32_t) ((u << 0) | (t << 4));
	STM32446RtcSetDr();
}

void STM32446RtcRegWrite(volatile uint32_t* reg, uint32_t data)
{
	//1 - Enable access to the RTC registers
	stm32446.pwr.reg->CR |= (1 << 8); // Disable backup domain write protection
	//2 - Enter the "key" to unlock write protection	
	stm32446.rtc.reg->WPR |= 0xCA;
	stm32446.rtc.reg->WPR |= 0x53;
	//3 - Write
	
	*reg = data;
	
	//4 - Disable access to RTC registers	
	stm32446.pwr.reg->CR &= (uint32_t) ~(1 << 8);
}

void STM32446Rtcdr2vec(char* rtc_vect)
{
	uint32_t dr = stm32446.rtc.reg->DR;
	if(stm32446.rtc.reg->ISR & (1 << 5)){ // RSF: Registers synchronization flag
		// YT
		rtc_vect[0] = (uint8_t) (dr >> 20) & 0x0F;
		rtc_vect[0] = stm32446.func.bcd2dec(rtc_vect[0]);
		// YU
		rtc_vect[1] = (uint8_t) (dr >> 16) & 0x0F;
		rtc_vect[1] = stm32446.func.bcd2dec(rtc_vect[1]);
		// WDU
		rtc_vect[2] = (uint8_t) (dr >> 13) & 0x07;
		rtc_vect[2] = stm32446.func.bcd2dec(rtc_vect[2]);
		// MT
		rtc_vect[3] = (uint8_t) (dr >> 12) & 0x01;
		rtc_vect[3] = stm32446.func.bcd2dec(rtc_vect[3]);
		// MU
		rtc_vect[4] = (uint8_t) (dr >> 8) & 0x0F;
		rtc_vect[4] = stm32446.func.bcd2dec(rtc_vect[4]);
		// DT
		rtc_vect[5] = (uint8_t) (dr >> 4) & 0x03;
		rtc_vect[5] = stm32446.func.bcd2dec(rtc_vect[5]);
		// DU
		rtc_vect[6] = (uint8_t) dr & 0x0F;
		rtc_vect[6] = stm32446.func.bcd2dec(rtc_vect[6]);
		// Store Value
		STM32446DateDr = dr;
		// Clear Registers synchronization flag
		stm32446.rtc.reg->ISR &= (uint32_t) ~(1 << 5);
	}
}

void STM32446Rtctr2vec(char* rtc_vect)
{
	uint32_t tr = stm32446.rtc.reg->TR;
	if(stm32446.rtc.reg->ISR & (1 << 5)){ // RSF: Registers synchronization flag
		// ht
		rtc_vect[0] = (uint8_t) (tr >> 20) & 0x03;
		rtc_vect[0] = stm32446.func.bcd2dec(rtc_vect[0]);
		// hu
		rtc_vect[1] = (uint8_t) (tr >> 16) & 0x0F;
		rtc_vect[1] = stm32446.func.bcd2dec(rtc_vect[1]);
		// mnt
		rtc_vect[2] = (uint8_t) (tr >> 12) & 0x07;
		rtc_vect[2] = stm32446.func.bcd2dec(rtc_vect[2]);
		// mnu
		rtc_vect[3] = (uint8_t) (tr >> 8) & 0x0F;
		rtc_vect[3] = stm32446.func.bcd2dec(rtc_vect[3]);
		// st
		rtc_vect[4] = (uint8_t) (tr >> 4) & 0x07;
		rtc_vect[4] = stm32446.func.bcd2dec(rtc_vect[4]);
		// su
		rtc_vect[5] = (uint8_t) tr & 0x0F;
		rtc_vect[5] = stm32446.func.bcd2dec(rtc_vect[5]);
		// Store value
		STM32446TimeTr = tr;
		// Clear Registers synchronization flag
		stm32446.rtc.reg->ISR &= (uint32_t) ~(1 << 5);
	}
}

//RTC
void STM32446RtcSetTr(void)
{
	//1 - Enable access to the RTC registers
	stm32446.pwr.reg->CR |= (1 << 8); // Disable backup domain write protection
	//2 - Enter the "key" to unlock write protection	
	stm32446.rtc.reg->WPR |= 0xCA;
	stm32446.rtc.reg->WPR |= 0x53;
	//3 - Set INIT bit and wait for ready flag
	stm32446.rtc.reg->ISR |= (1 << 7); // INIT: Initialization mode
	while( !(stm32446.rtc.reg->ISR & (1 << 6)) ); // INITF: Initialization flag
	//4 - Setup
	
	stm32446.rtc.reg->TR = STM32446TimeTr;
	
	//5 - Clear INIT bit
	stm32446.rtc.reg->ISR &= (uint32_t) ~(1 << 7);
	//6 - Disable access to RTC registers	
	stm32446.pwr.reg->CR &= (uint32_t) ~(1 << 8);
}

void STM32446RtcSetDr(void)
{
	//1 - Enable access to the RTC registers
	stm32446.pwr.reg->CR |= (1 << 8); // Disable backup domain write protection
	//2 - Enter the "key" to unlock write protection	
	stm32446.rtc.reg->WPR |= 0xCA;
	stm32446.rtc.reg->WPR |= 0x53;
	//3 - Set INIT bit and wait for ready flag
	stm32446.rtc.reg->ISR |= (1 << 7); // INIT: Initialization mode
	while( !(stm32446.rtc.reg->ISR & (1 << 6)) ); // INITF: Initialization flag
	//4 - Setup
	
	stm32446.rtc.reg->DR = STM32446DateDr;
	
	//5 - Clear INIT bit
	stm32446.rtc.reg->ISR &= (uint32_t) ~(1 << 7);
	//6 - Disable access to RTC registers	
	stm32446.pwr.reg->CR &= (uint32_t) ~(1 << 8);
}

uint8_t STM32446RtcAccess(uint8_t clock)
{
	uint8_t status;
	// RM0390 pg 94
	// RTC access
	//1 - Enable the power interface clock by setting the PWREN bits in the RCC_APB1ENR
	stm32446.rcc.reg->APB1ENR |= (1 << 28); // Power interface clock enable
	//RCC->APB1ENR |= ((1 << 11) | (1 << 28));
	//2 - Set the DBP bit in the PWR power control register (PWR_CR)
	stm32446.pwr.reg->CR |= (1 << 8); // Disable backup domain write protection
	//3 - Select the RTC clock source RTC/AWU clock
	stm32446.rcc.lenable(clock);
	status = 1;
	//4 - RTCSEL[1:0]: RTC clock source selection
	stm32446.rcc.lselect(clock);
	status = 2;
	return status;
}

