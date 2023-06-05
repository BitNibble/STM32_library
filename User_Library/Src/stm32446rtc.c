/******************************************************************************
	STM32 446 RTC
Author: Sergio Santos 
	<sergio.salazar.santos@gmail.com>
License: GNU General Public License
Hardware: STM32-446
Date: 02062023
Comment:
	
*******************************************************************************/
/*** File Library ***/
#include "stm32446mapping.h"
#include "stm32446rtc.h"

static uint32_t STM32446TimeTr;
static uint32_t STM32446DateDr;

/*** File Procedure & Function Header ***/
uint32_t rtc_getbit(uint32_t reg, uint32_t size_block, uint32_t bit);
void rtc_setbit(volatile uint32_t* reg, uint32_t size_block, uint32_t bit, uint32_t data);
uint32_t STM32446_getsetbit(volatile uint32_t* reg, uint32_t size_block, uint32_t bit);
void STM32446RtcSetTr(void);
void STM32446RtcSetDr(void);
uint8_t STM32446RtcAccess(uint8_t clock);
char rtc_bcd2dec(char num);
char rtc_dec2bcd(char num);
void rtc_lenable(unsigned int lclock);
void rtc_lselect(uint8_t lclock);

void STM32446RtcClock(void)
{
	RCC->BDCR |= (1 << 15); // RTCEN: RTC clock enable
}

uint8_t STM32446RtcInic(uint8_t clock)
{ // slow
	uint8_t status = 255;
	STM32446TimeTr = RTC->TR;
	STM32446DateDr = RTC->DR;
	
	status = STM32446RtcAccess(clock);
	
	// Some help from youtube vids
	//RCC->CFGR &= (uint32_t) ~((1 << 0) | (1 << 1)); // RCC_CFGR sw[2:0] 00 Bits 1:0
	//RCC->CFGR &= (uint32_t) ~((1 << 20) | (1 << 19) | (1 << 18) | (1 << 17) | (1 << 16)); // RCC_CFGR RTCPRE[4:0] 00010: HSE/2 Bits 20:16
	//RCC->CFGR |= (uint32_t) (1 << 17); // RCC_CFGR RTCPRE[4:0] 00010: HSE/2 Bits
	
	//STM32446RtcEnable();
	//RCC->BDCR |= (1 << 15); // RTCEN: RTC clock enable
	
	// 5 - Enter the "key" to unlock write protection
	RTC->WPR |= 0xCA;
	RTC->WPR |= 0x53;
	//RTC->ISR &= (uint32_t) ~((1 << 3) | (1 << 5) | (1 << 7));

	// 6 - Set INIT bit and wait for ready flag
	RTC->ISR |= (1 << 7); // INIT: Initialization mode
	while( !(RTC->ISR & (1 << 6)) ); // INITF: Initialization flag
	status = 6;

	// 7 - Adjust prescaler values for RTC to obtain 1 Hz
	//RTC->PRER |= 0xF9;
	//RTC->PRER |= (0x7F << 16);
	
	// 8 - Write Time and Date values
	//RTC->TR |= 0x130000;
	//RTC->TR |= 0x5700;
	//RTC->DR |= 0x215124;
	
	// 9 - Set BYPSHAD bit
	// must read twice
	//RTC->CR |= (1 << 5); // BYPSHAD: Bypass the shadow registers
	// read only once
	RTC->CR &= (uint32_t) ~(1 << 5); // BYPSHAD: Disable Bypass the shadow registers
	
	// 10 - Clear INIT bit
	RTC->ISR &= (uint32_t) ~(1 << 7);
	
	// 11 - Disable access to RTC registers
	PWR->CR &= (uint32_t) ~(1 << 8);

	return status;
}

void STM32446RtcHour(uint8_t hour)
{
	uint8_t t, u;
	const uint32_t mask = 0x003F0000;
	
	t = rtc_dec2bcd(hour / 10);
	u = rtc_dec2bcd(hour % 10);
	STM32446TimeTr = RTC->TR;
	STM32446TimeTr &= (uint32_t) ~mask; // clear ht and hu 
	// hu, ht
	STM32446TimeTr |= (uint32_t) ((u << 16) | (t << 20));
	STM32446RtcSetTr();
}

void STM32446RtcMinute(uint8_t minute)
{
	uint8_t t, u;
	const uint32_t mask = 0x00007F00;
	
	t = rtc_dec2bcd(minute / 10);
	u = rtc_dec2bcd(minute % 10);
	STM32446TimeTr = RTC->TR;
	STM32446TimeTr &= (uint32_t) ~mask; // clear mnt and mnu 
	// mnu, mnt
	STM32446TimeTr |= (uint32_t) ((u << 8) | (t << 12));
	STM32446RtcSetTr();
}

void STM32446RtcSecond(uint8_t second)
{
	uint8_t t, u;
	const uint32_t mask = 0x0000007F;
	
	t = rtc_dec2bcd(second / 10);
	u = rtc_dec2bcd(second % 10);
	STM32446TimeTr = RTC->TR;
	STM32446TimeTr &= (uint32_t) ~mask; // clear st and su 
	// su, st
	STM32446TimeTr |= (uint32_t) ((u << 0) | (t << 4));
	STM32446RtcSetTr();
}

void STM32446RtcYear(uint8_t year)
{
	uint8_t t, u;
	const uint32_t mask = 0x00FF0000;
	
	t = rtc_dec2bcd(year / 10);
	u = rtc_dec2bcd(year % 10);
	STM32446DateDr &= (uint32_t) ~mask; // clear YT and YU 
	// YU, YT
	STM32446DateDr |= (uint32_t) ((u << 16) | (t << 20));
	STM32446RtcSetDr();
}

void STM32446RtcWeekDay(uint8_t weekday)
{
	uint8_t u;
	const uint32_t mask = 0x0000E0000;
	
	u = rtc_dec2bcd(weekday % 10);
	STM32446DateDr &= (uint32_t) ~mask; // clear WDU 
	// WDU
	STM32446DateDr |= (uint32_t) (u << 13);
	STM32446RtcSetDr();
}

void STM32446RtcMonth(uint8_t month)
{
	uint8_t t, u;
	const uint32_t mask = 0x00001F00;
	
	t = rtc_dec2bcd(month / 10);
	u = rtc_dec2bcd(month % 10);
	STM32446DateDr &= (uint32_t) ~mask; // clear MT and MU 
	// MU, MT
	STM32446DateDr |= (uint32_t) ((u << 8) | (t << 12));
	STM32446RtcSetDr();
}

void STM32446RtcDay(uint8_t day)
{
	uint8_t t, u;
	const uint32_t mask = 0x0000003F;
	
	t = rtc_dec2bcd(day / 10);
	u = rtc_dec2bcd(day % 10);
	STM32446DateDr &= (uint32_t) ~mask; // clear DT and DU 
	// DU, DT
	STM32446DateDr |= (uint32_t) ((u << 0) | (t << 4));
	STM32446RtcSetDr();
}

void STM32446RtcRegWrite(volatile uint32_t* reg, uint32_t data)
{
	//1 - Enable access to the RTC registers
	PWR->CR |= (1 << 8); // Disable backup domain write protection
	//2 - Enter the "key" to unlock write protection	
	RTC->WPR |= 0xCA;
	RTC->WPR |= 0x53;
	//3 - Write
	
	*reg = data;
	
	//4 - Disable access to RTC registers	
	PWR->CR &= (uint32_t) ~(1 << 8);
}

void STM32446Rtcdr2vec(char* rtc_vect)
{
	uint32_t dr = RTC->DR;
	if(RTC->ISR & (1 << 5)){ // RSF: Registers synchronization flag
		// YT
		rtc_vect[0] = (uint8_t) (dr >> 20) & 0x0F;
		rtc_vect[0] = rtc_bcd2dec(rtc_vect[0]);
		// YU
		rtc_vect[1] = (uint8_t) (dr >> 16) & 0x0F;
		rtc_vect[1] = rtc_bcd2dec(rtc_vect[1]);
		// WDU
		rtc_vect[2] = (uint8_t) (dr >> 13) & 0x07;
		rtc_vect[2] = rtc_bcd2dec(rtc_vect[2]);
		// MT
		rtc_vect[3] = (uint8_t) (dr >> 12) & 0x01;
		rtc_vect[3] = rtc_bcd2dec(rtc_vect[3]);
		// MU
		rtc_vect[4] = (uint8_t) (dr >> 8) & 0x0F;
		rtc_vect[4] = rtc_bcd2dec(rtc_vect[4]);
		// DT
		rtc_vect[5] = (uint8_t) (dr >> 4) & 0x03;
		rtc_vect[5] = rtc_bcd2dec(rtc_vect[5]);
		// DU
		rtc_vect[6] = (uint8_t) dr & 0x0F;
		rtc_vect[6] = rtc_bcd2dec(rtc_vect[6]);
		// Store Value
		STM32446DateDr = dr;
		// Clear Registers synchronization flag
		RTC->ISR &= (uint32_t) ~(1 << 5);
	}
}

void STM32446Rtctr2vec(char* rtc_vect)
{
	uint32_t tr = RTC->TR;
	if(RTC->ISR & (1 << 5)){ // RSF: Registers synchronization flag
		// ht
		rtc_vect[0] = (uint8_t) (tr >> 20) & 0x03;
		rtc_vect[0] = rtc_bcd2dec(rtc_vect[0]);
		// hu
		rtc_vect[1] = (uint8_t) (tr >> 16) & 0x0F;
		rtc_vect[1] = rtc_bcd2dec(rtc_vect[1]);
		// mnt
		rtc_vect[2] = (uint8_t) (tr >> 12) & 0x07;
		rtc_vect[2] = rtc_bcd2dec(rtc_vect[2]);
		// mnu
		rtc_vect[3] = (uint8_t) (tr >> 8) & 0x0F;
		rtc_vect[3] = rtc_bcd2dec(rtc_vect[3]);
		// st
		rtc_vect[4] = (uint8_t) (tr >> 4) & 0x07;
		rtc_vect[4] = rtc_bcd2dec(rtc_vect[4]);
		// su
		rtc_vect[5] = (uint8_t) tr & 0x0F;
		rtc_vect[5] = rtc_bcd2dec(rtc_vect[5]);
		// Store value
		STM32446TimeTr = tr;
		// Clear Registers synchronization flag
		RTC->ISR &= (uint32_t) ~(1 << 5);
	}
}

/*** File Procedure & Function Definition ***/
//RTC
void STM32446RtcSetTr(void)
{
	//1 - Enable access to the RTC registers
	PWR->CR |= (1 << 8); // Disable backup domain write protection
	//2 - Enter the "key" to unlock write protection	
	RTC->WPR |= 0xCA;
	RTC->WPR |= 0x53;
	//3 - Set INIT bit and wait for ready flag
	RTC->ISR |= (1 << 7); // INIT: Initialization mode
	while( !(RTC->ISR & (1 << 6)) ); // INITF: Initialization flag
	//4 - Setup
	
	RTC->TR = STM32446TimeTr;
	
	//5 - Clear INIT bit
	RTC->ISR &= (uint32_t) ~(1 << 7);
	//6 - Disable access to RTC registers	
	PWR->CR &= (uint32_t) ~(1 << 8);
}

void STM32446RtcSetDr(void)
{
	//1 - Enable access to the RTC registers
	PWR->CR |= (1 << 8); // Disable backup domain write protection
	//2 - Enter the "key" to unlock write protection	
	RTC->WPR |= 0xCA;
	RTC->WPR |= 0x53;
	//3 - Set INIT bit and wait for ready flag
	RTC->ISR |= (1 << 7); // INIT: Initialization mode
	while( !(RTC->ISR & (1 << 6)) ); // INITF: Initialization flag
	//4 - Setup
	
	RTC->DR = STM32446DateDr;
	
	//5 - Clear INIT bit
	RTC->ISR &= (uint32_t) ~(1 << 7);
	//6 - Disable access to RTC registers	
	PWR->CR &= (uint32_t) ~(1 << 8);
}

uint8_t STM32446RtcAccess(uint8_t clock)
{
	uint8_t status;
	// RM0390 pg 94
	// RTC access
	//1 - Enable the power interface clock by setting the PWREN bits in the RCC_APB1ENR
	RCC->APB1ENR |= (1 << 28); // Power interface clock enable
	//RCC->APB1ENR |= ((1 << 11) | (1 << 28));
	//2 - Set the DBP bit in the PWR power control register (PWR_CR)
	PWR->CR |= (1 << 8); // Disable backup domain write protection
	//3 - Select the RTC clock source RTC/AWU clock
	rtc_lenable(clock);
	status = 1;
	//4 - RTCSEL[1:0]: RTC clock source selection
	rtc_lselect(clock);
	status = 2;
	return status;
}

/*** COMMON ***/
char rtc_bcd2dec(char num)
{
	return ((num / 16 * 10) + (num % 16));
}

char rtc_dec2bcd(char num)
{
	return ((num / 10 * 16) + (num % 10));
}

void rtc_lenable(unsigned int lclock)
{
	unsigned int set;
	unsigned int rdy;
	for( set = 1, rdy = 1; rdy ; ){
		if(lclock == 2){ // LSION: Internal low-speed oscillator enable
			if( set ){ RCC->CSR |= ( 1 << 0); set = 0; }else if( RCC->CSR & ( 1 << 1) ) rdy = 0;
		}
		else if(lclock == 1){ // LSEON: External low-speed oscillator enable
			if( set ){ RCC->BDCR |= ( 1 << 0); set = 0; }else if( RCC->BDCR & ( 1 << 1) ) rdy = 0;
		}
		else if(lclock == 4){ // LSEBYP: External low-speed oscillator bypass
			if( set ) RCC->BDCR |= ( 1 << 2 );
			lclock = 1;
		}
		else lclock = 2; // default
	}
}

void rtc_lselect(uint8_t lclock)
{
	RCC->BDCR &= (uint32_t) ~((1 << 9) | (1 << 8)); // RTCSEL[1:0]: RTC clock source selection
	switch(lclock){
		case 2:
			RCC->BDCR |= (1 << 9); // LSI oscillator clock used as the RTC clock
		break;
		case 1:
			RCC->BDCR |= (1 << 8); // LSE oscillator clock used as the RTC clock
		break;
		case 3:
			RCC->BDCR |= ((1 << 8) | (1 << 9)); // HSE oscillator clock divided by a programmable prescaler
		break;
		default:
			RCC->BDCR |= (1 << 8); // LSE oscillator clock used as the RTC clock
		break;
	}
}

uint32_t rtc_getbit(uint32_t reg, uint32_t size_block, uint32_t bit)
{
	uint32_t value = 0; uint32_t tmp = 0;

	uint32_t mask = (unsigned int)((1 << size_block) - 1);
	mask = (mask << bit);
	tmp = mask & reg;
	value = (tmp >> bit);
	return value;
}

void rtc_setbit(volatile uint32_t* reg, uint32_t size_block, uint32_t bit, uint32_t data)
{
	uint32_t n = 0;
	if(bit > 31){ n = bit/32; bit = bit - (n * 32); }
	uint32_t value = 0;
	uint32_t mask = (unsigned int)((1 << size_block) - 1);
	value = data & mask;
	*(reg + n ) &= ~(mask << bit);
	*(reg + n ) |= (value << bit);
}

uint32_t rtc_getsetbit(volatile uint32_t* reg, uint32_t size_block, uint32_t bit)
{
	uint32_t n = 0;
	if(bit > 31){ n = bit/32; bit = bit - (n * 32); }
	uint32_t value = 0;
	uint32_t mask = (unsigned int)((1 << size_block) - 1);
	value = *(reg + n ) & ~(mask << bit);
	value = (value >> bit);
	return value;
}

/*** EOF ***/


