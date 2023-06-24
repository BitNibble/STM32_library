/******************************************************************************
	STM32 446 RTC
Author: Sergio Santos 
	<sergio.salazar.santos@gmail.com>
License: GNU General Public License
Hardware: STM32-446
Date: 19062023
Comment:
	
*******************************************************************************/
/*** File Library ***/
#include "stm32446mapping.h"
#include "stm32446rtc.h"

static uint32_t rtc_time_out;

/*** File Procedure & Function Header ***/
uint32_t rtc_readreg(uint32_t reg, uint32_t size_block, uint32_t bit);
void rtc_writereg(volatile uint32_t* reg, uint32_t size_block, uint32_t bit, uint32_t data);
void rtc_setreg(volatile uint32_t* reg, uint32_t size_block, uint32_t bit, uint32_t data);
void rtc_setbit(volatile uint32_t* reg, uint32_t size_block, uint32_t bit, uint32_t data);
uint32_t rtc_getsetbit(volatile uint32_t* reg, uint32_t size_block, uint32_t bit);
void STM32446PwrClock(uint8_t bool);
void STM32446BckSramClock(uint8_t bool);
void STM32446RtcWriteEnable(void);
void STM32446RtcWriteDisable(void);
void STM32446RtcRegUnlock(void);
void STM32446RtcRegWrite(volatile uint32_t* rtc_reg, uint32_t value);
void STM32446RtcStopRead(void);
void STM32446RtcWaitRead(void);
void STM32446RtcSetTr(uint32_t value);
void STM32446RtcSetDr(uint32_t value);
uint8_t rtc_get_stsu(void);
uint8_t rtc_get_st(void);
uint8_t rtc_get_su(void);
uint16_t rtc_get_ss(void);
char rtc_bcd2dec(char num);
char rtc_dec2bcd(char num);
void rtc_lenable(unsigned int lclock);
void rtc_lselect(uint8_t lclock);
/*** Procedure & Function Header ***/

/*** Procedure & Function Definition ***/
void STM32446RtcClock(uint8_t bool)
{
	if(bool){ RCC->BDCR |= (1 <<  15); } // RTCEN: RTC clock enable
	else{ RCC->BDCR &= ~(1 <<  15); } // RTCEN: RTC clock disable
}
void STM32446RtcNvic(uint8_t value)
{ // 3, 41
	switch(value){
		case 0b01:
			rtc_setbit(NVIC->ISER, 1, 3, 1);
		break;
		case 0b10:
			rtc_setbit(NVIC->ISER, 1, 41, 1);
		break;
		case 0b101:
			rtc_setbit(NVIC->ICER, 1, 3, 1);
		break;
		case 0b110:
			rtc_setbit(NVIC->ICER, 1, 41, 1);
		break;
	default:
	break;
	}
}
void STM32446RtcInic(uint8_t clock)
{ // RM0390 pg657
	rtc_lenable(clock);
	rtc_lselect(clock);
	STM32446PwrClock(1);
	STM32446RtcClock(1);
	STM32446RtcStopRead();
	//STM32446RtcWriteEnable();
	//STM32446RtcRegUnlock();
	//STM32446RtcRegWrite(&RTC->TR, 0x130000);
	//STM32446RtcRegWrite(&RTC->DR, 0x215124);
	//RTC->CR &= (uint32_t) ~(1 << 5); // BYPSHAD: Disable Bypass the shadow registers
	//STM32446RtcWriteDisable();
}

void STM32446RtcBckWrite(uint8_t n, uint8_t data)
{
	STM32446PwrClock(1);
	STM32446BckSramClock(1);
	STM32446RtcWriteEnable();
	if(n < 80){
		rtc_setbit(&RTC->BKP0R, 8, (n * 8), data);
	}
	STM32446RtcWriteDisable();
}

uint8_t STM32446RtcBckRead(uint8_t n)
{
	uint8_t value = 0;
	if(n < 80){
		value = rtc_getsetbit(&RTC->BKP0R, 8, (n * 8));
	}
	return value;
}

void STM32446RtcHour(uint8_t hour)
{
	uint32_t Time;
	uint8_t t, u;
	const uint32_t mask = 0x003F0000;
	
	t = rtc_dec2bcd(hour / 10);
	u = rtc_dec2bcd(hour % 10);
	STM32446RtcWaitRead();
	Time = RTC->TR;
	Time &= (uint32_t) ~mask; // clear ht and hu
	// hu, ht
	Time |= (uint32_t) ((u << 16) | (t << 20));
	STM32446RtcSetTr(Time);
}

void STM32446RtcMinute(uint8_t minute)
{
	uint32_t Time;
	uint8_t t, u;
	const uint32_t mask = 0x00007F00;
	
	t = rtc_dec2bcd(minute / 10);
	u = rtc_dec2bcd(minute % 10);
	STM32446RtcWaitRead();
	Time = RTC->TR;
	Time &= (uint32_t) ~mask; // clear mnt and mnu
	// mnu, mnt
	Time |= (uint32_t) ((u << 8) | (t << 12));
	STM32446RtcSetTr(Time);
}

void STM32446RtcSecond(uint8_t second)
{
	uint32_t Time;
	uint8_t t, u;
	const uint32_t mask = 0x0000007F;
	
	t = rtc_dec2bcd(second / 10);
	u = rtc_dec2bcd(second % 10);
	STM32446RtcWaitRead();
	Time = RTC->TR;
	Time &= (uint32_t) ~mask; // clear st and su
	// su, st
	Time |= (uint32_t) ((u << 0) | (t << 4));
	STM32446RtcSetTr(Time);
}

void STM32446RtcYear(uint8_t year)
{
	uint32_t Date;
	uint8_t t, u;
	const uint32_t mask = 0x00FF0000;
	
	t = rtc_dec2bcd(year / 10);
	u = rtc_dec2bcd(year % 10);
	STM32446RtcWaitRead();
	Date = RTC->DR;
	Date &= (uint32_t) ~mask; // clear YT and YU
	// YU, YT
	Date |= (uint32_t) ((u << 16) | (t << 20));
	STM32446RtcSetDr(Date);
}

void STM32446RtcMonth(uint8_t month)
{
	uint32_t Date;
	uint8_t t, u;
	const uint32_t mask = 0x00001F00;
	
	t = rtc_dec2bcd(month / 10);
	u = rtc_dec2bcd(month % 10);
	STM32446RtcWaitRead();
	Date = RTC->DR;
	Date &= (uint32_t) ~mask; // clear MT and MU
	// MU, MT
	Date |= (uint32_t) ((u << 8) | (t << 12));
	STM32446RtcSetDr(Date);
}

void STM32446RtcWeekDay(uint8_t weekday)
{
	uint32_t Date;
	uint8_t u;
	const uint32_t mask = 0x0000E0000;
	
	u = rtc_dec2bcd(weekday % 10);
	STM32446RtcWaitRead();
	Date = RTC->DR;
	Date &= (uint32_t) ~mask; // clear WDU
	// WDU
	Date |= (uint32_t) (u << 13);
	STM32446RtcSetDr(Date);
}

void STM32446RtcDay(uint8_t day)
{
	uint32_t Date;
	uint8_t t, u;
	const uint32_t mask = 0x0000003F;
	
	t = rtc_dec2bcd(day / 10);
	u = rtc_dec2bcd(day % 10);
	STM32446RtcWaitRead();
	Date = RTC->DR;
	Date &= (uint32_t) ~mask; // clear DT and DU
	// DU, DT
	Date |= (uint32_t) ((u << 0) | (t << 4));
	STM32446RtcSetDr(Date);
}

void STM32446Rtcdr2vec(char* rtc_vect)
{
	if(RTC->ISR & (1 << 5)){ // RSF: Registers synchronisation flag
		uint32_t dr = RTC->DR;
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
		// Clear Registers synchronisation flag
		RTC->ISR &= (uint32_t) ~(1 << 5);
	}
}

void STM32446Rtctr2vec(char* rtc_vect)
{
	if(RTC->ISR & (1 << 5)){ // RSF: Registers synchronisation flag
		uint32_t tr = RTC->TR;
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
		// Clear Registers synchronisation flag
		RTC->ISR &= (uint32_t) ~(1 << 5);
	}
}

uint8_t rtc_get_stsu(void)
{ // BCD
	uint32_t tr = RTC->TR;
	return (uint8_t) (tr & 0x007F);
}
uint8_t rtc_get_st(void)
{ // BCD
	uint32_t tr = RTC->TR;
	return (uint8_t) (tr >> 4) & 0x07;
}
uint8_t rtc_get_su(void)
{ // BCD
	uint32_t tr = RTC->TR;
	return (uint8_t) tr & 0x0F;
}
uint16_t rtc_get_ss(void)
{
	return RTC->SSR;
}

/*** RTC Procedure & Function Definition ***/
STM32446RTCobj rtc_inic(void)
{
	STM32446RTCobj stm32446_rtc;
	stm32446_rtc.reg = RTC;
	/*** Link ***/
	stm32446_rtc.clock = STM32446RtcClock;
	stm32446_rtc.nvic = STM32446RtcNvic;
	stm32446_rtc.inic = STM32446RtcInic;
	stm32446_rtc.Day = STM32446RtcDay;
	stm32446_rtc.Month = STM32446RtcMonth;
	stm32446_rtc.WeekDay = STM32446RtcWeekDay;
	stm32446_rtc.Year = STM32446RtcYear;
	stm32446_rtc.Hour = STM32446RtcHour;
	stm32446_rtc.Minute = STM32446RtcMinute;
	stm32446_rtc.Second = STM32446RtcSecond;
	stm32446_rtc.dr2vec = STM32446Rtcdr2vec;
	stm32446_rtc.tr2vec = STM32446Rtctr2vec;
	stm32446_rtc.BckWrite = STM32446RtcBckWrite;
	stm32446_rtc.BckRead = STM32446RtcBckRead;
	stm32446_rtc.get_stsu = rtc_get_stsu;
	stm32446_rtc.get_ss = rtc_get_ss;
	return stm32446_rtc;
}

/*** AUX Procedure & Function Definition ***/
void STM32446PwrClock(uint8_t bool)
{
	rtc_setreg(&RCC->APB1ENR, 1, 28, bool); // Power interface clock enable
}
void STM32446BckSramClock(uint8_t bool)
{
	rtc_setreg(&RCC->AHB1ENR, 1, 18, bool); // Backup SRAM interface clock enable
}
void STM32446RtcWriteEnable(void)
{
	PWR->CR |= (1 << 8); // Disable protection
}
void STM32446RtcWriteDisable(void)
{
	PWR->CR &= (uint32_t) ~(1 << 8); // Enable protection
}
void STM32446RtcRegUnlock(void)
{
	RTC->WPR |= RTC_KEY1;
	RTC->WPR |= RTC_KEY2;
}
void STM32446RtcRegWrite(volatile uint32_t* rtc_reg, uint32_t value)
{
	RTC->ISR |= (1 << 7); // INIT
	for( rtc_time_out = 100; !(RTC->ISR & (1 << 6)) && rtc_time_out; rtc_time_out-- ); // INITF: Initialisation flag
	*rtc_reg = value;
	RTC->ISR &= (uint32_t) ~(1 << 7);
}
void STM32446RtcStopRead(void)
{
	RTC->ISR &= ~(1 << 5);
}
void STM32446RtcWaitRead(void)
{ // Wait Data Ready
	for(rtc_time_out = 200; !(RTC->ISR & (1 << 5)) && rtc_time_out; rtc_time_out--);
}
//RTC
void STM32446RtcSetTr(uint32_t value)
{
	STM32446RtcWriteEnable();
	STM32446RtcRegUnlock();
	STM32446RtcRegWrite(&RTC->TR, value);
	STM32446RtcWriteDisable();
}
void STM32446RtcSetDr(uint32_t value)
{
	STM32446RtcWriteEnable();
	STM32446RtcRegUnlock();
	STM32446RtcRegWrite(&RTC->DR, value);
	STM32446RtcWriteDisable();
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
			RCC->BDCR |= (1 << 9); // LSI oscillator clock used as the RTC clock
		break;
	}
}

/*** File Procedure & Function Definition ***/
uint32_t rtc_readreg(uint32_t reg, uint32_t size_block, uint32_t bit)
{
	if(bit > 31){ bit = 0;} if(size_block > 32){ size_block = 32;}
	uint32_t value = reg;
	uint32_t mask = (unsigned int)((1 << size_block) - 1);
	value &= (mask << bit);
	value = (value >> bit);
	return value;
}
void rtc_writereg(volatile uint32_t* reg, uint32_t size_block, uint32_t bit, uint32_t data)
{
	if(bit > 31){ bit = 0;} if(size_block > 32){ size_block = 32;}
	uint32_t value = data;
	uint32_t mask = (unsigned int)((1 << size_block) - 1);
	value &= mask;
	value = (value << bit);
	*reg = value;
}
void rtc_setreg(volatile uint32_t* reg, uint32_t size_block, uint32_t bit, uint32_t data)
{
	if(bit > 31){ bit = 0;} if(size_block > 32){ size_block = 32;}
	uint32_t value = data;
	uint32_t mask = (unsigned int)((1 << size_block) - 1);
	value &= mask;
	*reg &= ~(mask << bit);
	*reg |= (value << bit);
}
void rtc_setbit(volatile uint32_t* reg, uint32_t size_block, uint32_t bit, uint32_t data)
{
	uint32_t n = 0;
	if(bit > 31){ n = bit/32; bit = bit - (n * 32); } if(size_block > 32){ size_block = 32;}
	uint32_t value = data;
	uint32_t mask = (unsigned int)((1 << size_block) - 1);
	value &= mask;
	*(reg + n ) &= ~(mask << bit);
	*(reg + n ) |= (value << bit);
}
uint32_t rtc_getsetbit(volatile uint32_t* reg, uint32_t size_block, uint32_t bit)
{
	uint32_t n = 0;
	if(bit > 31){ n = bit/32; bit = bit - (n * 32); } if(size_block > 32){ size_block = 32;}
	uint32_t value = *(reg + n );
	uint32_t mask = (unsigned int)((1 << size_block) - 1);
	value &= (mask << bit);
	value = (value >> bit);
	return value;
}

/*** EOF ***/

/******
1º Sequence
2º Scope
	- Library Scope
	- File Scope
	- Function Scope
	- Precedence Scope
3º Pointer and Variable
4º Casting
******/


