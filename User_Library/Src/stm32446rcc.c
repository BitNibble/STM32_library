/******************************************************************************
	STM32 446 RCC
Author: Sergio Santos 
	<sergio.salazar.santos@gmail.com>
License: GNU General Public License
Hardware: STM32-446
Date: 02062023
Comment:
	
*******************************************************************************/
/*** File Library ***/
#include "stm32446mapping.h"
#include "stm32446rcc.h"

/*** File Procedure & Function Header ***/
uint32_t rcc_getbit(uint32_t reg, uint32_t size_block, uint32_t bit);
void rcc_setbit(volatile uint32_t* reg, uint32_t size_block, uint32_t bit, uint32_t data);
uint32_t rcc_getsetbit(volatile uint32_t* reg, uint32_t size_block, uint32_t bit);

/*** RCC Procedure & Function Definition ***/
uint8_t STM32446RccInic(void)
{
	uint8_t clkused; // First turn it on then select it or enable it.
	// Setup PLL
	// PLLDIVISION parameters
	// source 0 or 1		M 2 to 63		N 50 to 432		P 2,4,6,8
	// Q 2 to 15			R 2 to 7        (2Mhz ideal, N/m  *  clkx)

	STM32446PLLDivision(0, 8, 336, 2, 14, 7); // 0,8,360,4,15,6; 0,8,336,2,14,7;
	// Enable PLL
	// STM32446RccPLLCLKEnable(); // Only enable when Division is configured correctly.

	// SysClock prescaler parameters
	// AHB 1,2,4,8,16,64,128,256,512 		APB1 1,2,4,8,16		APB2 1,2,4,8,16
	// RTC 2 to 31

	// STM32446Prescaler(8, 1, 1, 0);
	// STM32446Prescaler(2, 1, 1, 0);
	STM32446Prescaler(1, 1, 1, 0);
	// System Clock Source
	STM32446RccHEnable(0);
	// System Clock Select or Enable
	clkused = STM32446RccHSelect(0); // SW[1:0]: System clock switch 00 - HSI, 01 - HSE pg133
	// Low Speed Internal Clock turned on as default
	// Internal low-speed oscillator enable and Internal low-speed oscillator ready
	STM32446RccLEnable(2);
	// Low speed oscillator select
	STM32446RccLSelect(2);
	return clkused;
}

// RCC
void STM32446RccHEnable(uint8_t hclock)
{
	uint8_t set;
	uint8_t rdy;
	for( set = 1, rdy = 1; rdy ; ){
		if(hclock == 0){ // HSION: Internal high-speed clock enable
			if( set ){ RCC->CR |= ( 1 << 0); set = 0; }else if( RCC->CR & ( 1 << 1) ) rdy = 0;
		}
		else if(hclock == 1){ // HSEON: HSE clock enable
			if( set ){ RCC->CR |= ( 1 << 16); set = 0; }else if( RCC->CR & ( 1 << 17) ) rdy = 0;
		}
		else if(hclock == 2){ // HSEBYP: HSE clock bypass
			if( set ) RCC->CR |= ( 1 << 18 );
			hclock = 1;
		}
		else hclock = 0; // default
	}
}

uint8_t STM32446RccHSelect(uint8_t hclock)
{ // SW[1:0]: System clock switch 00 - HSI, 01 - HSE pg133
	RCC->CFGR &= (unsigned int) ~(3); // 00: HSI oscillator selected as system clock
	switch(hclock){
		case 1:
			RCC->CFGR |= 1; // HSE oscillator selected as system clock
		break;
		case 2:
			RCC->CFGR |= 2; // PLL_P selected as system clock
		break;
		case 3:
			RCC->CFGR |= 3; // PLL_R selected as system clock
		break;
		default:
		break;
	}
	return (RCC->CFGR >> 2) & 3;
}

void STM32446RccLEnable(uint8_t lclock)
{
	uint8_t set;
	uint8_t rdy;
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

void STM32446RccLSelect(uint8_t lclock)
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

void STM32446Prescaler(uint16_t ahbpre, uint8_t ppre1, uint8_t ppre2, uint8_t rtcpre)
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
void STM32446PLLDivision(uint8_t pllsrc, uint8_t pllm, uint16_t plln, uint8_t pllp, uint8_t pllq, uint8_t pllr)
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

void STM32446RccPLLCLKEnable(void)
{
	//if(onoff){
		for( RCC->CR |= (1 << 24) ; !(RCC->CR & (1 << 25)) ; ); // PLLON: Main PLL (PLL) enable
	//}else{
		//RCC->CR &= (unsigned int) ~(1 << 24);
	//}
}

void STM32446RccPLLI2SEnable(void)
{
	//if(onoff)
		for( RCC->CR |= (1 << 26) ; !(RCC->CR & (1 << 27)) ; ); // PLLI2SON: PLLI2S enable
	//else
		//RCC->CR &= (unsigned int) ~(1 << 26);
}

void STM32446RccPLLSAIEnable(void)
{
	//if(onoff)
		for( RCC->CR |= (1 << 28) ; !(RCC->CR & (1 << 29)) ; ); // PLLSAION: PLLSAI enable
	//else
		//RCC->CR &= (unsigned int) ~(1 << 28);
}

/*** RCC Bit Mapping Definition ***/
// CR
uint8_t STM32446RCC_CR_get_pllsairdy(void)
{
	return rcc_getbit(RCC->CR, 1, 29);
}
void STM32446RCC_CR_pllsaion(uint8_t bool)
{
	rcc_setbit(&RCC->CR, 1, 28, bool);
}
uint8_t STM32446RCC_CR_get_plli2srdy(void)
{
	return rcc_getbit(RCC->CR, 1, 27);
}
void STM32446RCC_CR_plli2son(uint8_t bool)
{
	rcc_setbit(&RCC->CR, 1, 26, bool);
}
uint8_t STM32446RCC_CR_get_pllrdy(void)
{
	return rcc_getbit(RCC->CR, 1, 25);
}
void STM32446RCC_CR_pllon(uint8_t bool)
{
	rcc_setbit(&RCC->CR, 1, 24, bool);
}
void STM32446RCC_CR_csson(uint8_t bool)
{
	rcc_setbit(&RCC->CR, 1, 19, bool);
}
void STM32446RCC_CR_hsebyp(uint8_t bool)
{
	rcc_setbit(&RCC->CR, 1, 18, bool);
}
uint8_t STM32446RCC_CR_get_hserdy(void)
{
	return rcc_getbit(RCC->CR, 1, 17);
}
void STM32446RCC_CR_hseon(uint8_t bool)
{
	rcc_setbit(&RCC->CR, 1, 16, bool);
}
uint8_t STM32446RCC_CR_get_hsical(void)
{
	return rcc_getbit(RCC->CR, 8, 8);
}
void STM32446RCC_CR_hsitrim(uint8_t value)
{
	rcc_setbit(&RCC->CR, 5, 3, value);
}
uint8_t STM32446RCC_CR_get_hsirdy(void)
{
	return rcc_getbit(RCC->CR, 1, 1);
}
void STM32446RCC_CR_hsion(uint8_t bool)
{
	rcc_setbit(&RCC->CR, 1, 0, bool);
}

// PLLCFGR
void STM32446RCC_PLLCFGR_pllr(uint8_t value)
{
	rcc_setbit(&RCC->CR, 3, 28, value);
}
void STM32446RCC_PLLCFGR_pllq(uint8_t value)
{
	rcc_setbit(&RCC->CR, 4, 24, value);
}
void STM32446RCC_PLLCFGR_pllsrc(uint8_t bool)
{
	rcc_setbit(&RCC->CR, 1, 22, bool);
}
void STM32446RCC_PLLCFGR_pllp(uint8_t value)
{
	rcc_setbit(&RCC->CR, 2, 16, value);
}
void STM32446RCC_PLLCFGR_plln(uint16_t value)
{
	rcc_setbit(&RCC->CR, 9, 6, value);
}
void STM32446RCC_PLLCFGR_pllm(uint8_t value)
{
	rcc_setbit(&RCC->CR, 6, 0, value);
}

// CFGR
void STM32446RCC_CFGR_mco2(uint8_t value)
{
	rcc_setbit(&RCC->CFGR, 2, 30, value);
}
void STM32446RCC_CFGR_mco2pre(uint8_t value)
{
	rcc_setbit(&RCC->CFGR, 3, 27, value);
}
void STM32446RCC_CFGR_mco1pre(uint8_t value)
{
	rcc_setbit(&RCC->CFGR, 3, 24, value);
}
void STM32446RCC_CFGR_mco1(uint8_t value)
{
	rcc_setbit(&RCC->CFGR, 2, 21, value);
}
void STM32446RCC_CFGR_rtcpre(uint8_t value)
{
	rcc_setbit(&RCC->CFGR, 5, 16, value);
}
void STM32446RCC_CFGR_ppre2(uint8_t value)
{
	rcc_setbit(&RCC->CFGR, 3, 13, value);
}
void STM32446RCC_CFGR_ppre1(uint8_t value)
{
	rcc_setbit(&RCC->CFGR, 3, 10, value);
}
void STM32446RCC_CFGR_hpre(uint8_t value)
{
	rcc_setbit(&RCC->CFGR, 4, 4, value);
}
uint8_t STM32446RCC_CFGR_get_sws(void)
{
	return rcc_getbit(RCC->CFGR, 2, 2);
}
void STM32446RCC_CFGR_sw(uint8_t value)
{
	rcc_setbit(&RCC->CFGR, 2, 0, value);
}

// CIR
void STM32446RCC_CIR_clear_cssc(void)
{
	rcc_setbit(&RCC->CIR, 1, 23, 1);
}
void STM32446RCC_CIR_clear_pllsairdyc(void)
{
	rcc_setbit(&RCC->CIR, 1, 22, 1);
}
void STM32446RCC_CIR_clear_plli2srdyc(void)
{
	rcc_setbit(&RCC->CIR, 1, 21, 1);
}
void STM32446RCC_CIR_clear_pllrdyc(void)
{
	rcc_setbit(&RCC->CIR, 1, 20, 1);
}
void STM32446RCC_CIR_clear_hserdyc(void)
{
	rcc_setbit(&RCC->CIR, 1, 19, 1);
}
void STM32446RCC_CIR_clear_hsirdyc(void)
{
	rcc_setbit(&RCC->CIR, 1, 18, 1);
}
void STM32446RCC_CIR_clear_lserdyc(void)
{
	rcc_setbit(&RCC->CIR, 1, 17, 1);
}
void STM32446RCC_CIR_clear_lsirdyc(void)
{
	rcc_setbit(&RCC->CIR, 1, 16, 1);
}
void STM32446RCC_CIR_pllsairdyie(uint8_t bool)
{
	rcc_setbit(&RCC->CIR, 1, 14, bool);
}
void STM32446RCC_CIR_plli2srdyie(uint8_t bool)
{
	rcc_setbit(&RCC->CIR, 1, 13, bool);
}
void STM32446RCC_CIR_pllrdyie(uint8_t bool)
{
	rcc_setbit(&RCC->CIR, 1, 12, bool);
}
void STM32446RCC_CIR_hserdyie(uint8_t bool)
{
	rcc_setbit(&RCC->CIR, 1, 11, bool);
}
void STM32446RCC_CIR_hsirdyie(uint8_t bool)
{
	rcc_setbit(&RCC->CIR, 1, 10, bool);
}
void STM32446RCC_CIR_lserdyie(uint8_t bool)
{
	rcc_setbit(&RCC->CIR, 1, 9, bool);
}
void STM32446RCC_CIR_lsirdyie(uint8_t bool)
{
	rcc_setbit(&RCC->CIR, 1, 8, bool);
}
uint8_t STM32446RCC_CIR_get_cssf(void)
{
	return rcc_getbit(RCC->CIR, 1, 7);
}
uint8_t STM32446RCC_CIR_get_pllsairdyf(void)
{
	return rcc_getbit(RCC->CIR, 1, 6);
}
uint8_t STM32446RCC_CIR_get_plli2srdyf(void)
{
	return rcc_getbit(RCC->CIR, 1, 5);
}
uint8_t STM32446RCC_CIR_get_pllrdyf(void)
{
	return rcc_getbit(RCC->CIR, 1, 4);
}
uint8_t STM32446RCC_CIR_get_hserdyf(void)
{
	return rcc_getbit(RCC->CIR, 1, 3);
}
uint8_t STM32446RCC_CIR_get_hsirdyf(void)
{
	return rcc_getbit(RCC->CIR, 1, 2);
}
uint8_t STM32446RCC_CIR_get_lserdyf(void)
{
	return rcc_getbit(RCC->CIR, 1, 1);
}
uint8_t STM32446RCC_CIR_get_lsirdyf(void)
{
	return rcc_getbit(RCC->CIR, 1, 0);
}

// AHB1RSTR
void STM32446RCC_AHB1RSTR_otghsrst(uint8_t bool)
{
	rcc_setbit(&RCC->AHB1RSTR, 1, 29, bool);
}
void STM32446RCC_AHB1RSTR_dma2rst(uint8_t bool)
{
	rcc_setbit(&RCC->AHB1RSTR, 1, 22, bool);
}
void STM32446RCC_AHB1RSTR_dma1rst(uint8_t bool)
{
	rcc_setbit(&RCC->AHB1RSTR, 1, 21, bool);
}
void STM32446RCC_AHB1RSTR_crcrst(uint8_t bool)
{
	rcc_setbit(&RCC->AHB1RSTR, 1, 12, bool);
}
void STM32446RCC_AHB1RSTR_gpiohrst(uint8_t bool)
{
	rcc_setbit(&RCC->AHB1RSTR, 1, 7, bool);
}
void STM32446RCC_AHB1RSTR_gpiogrst(uint8_t bool)
{
	rcc_setbit(&RCC->AHB1RSTR, 1, 6, bool);
}
void STM32446RCC_AHB1RSTR_gpiofrst(uint8_t bool)
{
	rcc_setbit(&RCC->AHB1RSTR, 1, 5, bool);
}
void STM32446RCC_AHB1RSTR_gpioerst(uint8_t bool)
{
	rcc_setbit(&RCC->AHB1RSTR, 1, 4, bool);
}
void STM32446RCC_AHB1RSTR_gpiodrst(uint8_t bool)
{
	rcc_setbit(&RCC->AHB1RSTR, 1, 3, bool);
}
void STM32446RCC_AHB1RSTR_gpiocrst(uint8_t bool)
{
	rcc_setbit(&RCC->AHB1RSTR, 1, 2, bool);
}
void STM32446RCC_AHB1RSTR_gpiobrst(uint8_t bool)
{
	rcc_setbit(&RCC->AHB1RSTR, 1, 1, bool);
}
void STM32446RCC_AHB1RSTR_gpioarst(uint8_t bool)
{
	rcc_setbit(&RCC->AHB1RSTR, 1, 0, bool);
}

// AHB2RSTR
void STM32446RCC_AHB2RSTR_otgfsrst(uint8_t bool)
{
	rcc_setbit(&RCC->AHB2RSTR, 1, 7, bool);
}
void STM32446RCC_AHB2RSTR_dcmirst(uint8_t bool)
{
	rcc_setbit(&RCC->AHB2RSTR, 1, 0, bool);
}

// AHB3RSTR
void STM32446RCC_AHB3RSTR_qspirst(uint8_t bool)
{
	rcc_setbit(&RCC->AHB3RSTR, 1, 1, bool);
}
void STM32446RCC_AHB3RSTR_fmcrst(uint8_t bool)
{
	rcc_setbit(&RCC->AHB3RSTR, 1, 0, bool);
}

// APB1RSTR
void STM32446RCC_APB1RSTR_dacrst(uint8_t bool)
{
	rcc_setbit(&RCC->APB1RSTR, 1, 29, bool);
}
void STM32446RCC_APB1RSTR_pwrrst(uint8_t bool)
{
	rcc_setbit(&RCC->APB1RSTR, 1, 28, bool);
}
void STM32446RCC_APB1RSTR_cecrst(uint8_t bool)
{
	rcc_setbit(&RCC->APB1RSTR, 1, 27, bool);
}
void STM32446RCC_APB1RSTR_can2rst(uint8_t bool)
{
	rcc_setbit(&RCC->APB1RSTR, 1, 26, bool);
}
void STM32446RCC_APB1RSTR_can1rst(uint8_t bool)
{
	rcc_setbit(&RCC->APB1RSTR, 1, 25, bool);
}
void STM32446RCC_APB1RSTR_fmpi2c1rst(uint8_t bool)
{
	rcc_setbit(&RCC->APB1RSTR, 1, 24, bool);
}
void STM32446RCC_APB1RSTR_i2c3rst(uint8_t bool)
{
	rcc_setbit(&RCC->APB1RSTR, 1, 23, bool);
}
void STM32446RCC_APB1RSTR_i2c2rst(uint8_t bool)
{
	rcc_setbit(&RCC->APB1RSTR, 1, 22, bool);
}
void STM32446RCC_APB1RSTR_i2c1rst(uint8_t bool)
{
	rcc_setbit(&RCC->APB1RSTR, 1, 21, bool);
}
void STM32446RCC_APB1RSTR_uart5rst(uint8_t bool)
{
	rcc_setbit(&RCC->APB1RSTR, 1, 20, bool);
}
void STM32446RCC_APB1RSTR_uart4rst(uint8_t bool)
{
	rcc_setbit(&RCC->APB1RSTR, 1, 19, bool);
}
void STM32446RCC_APB1RSTR_usart3rst(uint8_t bool)
{
	rcc_setbit(&RCC->APB1RSTR, 1, 18, bool);
}
void STM32446RCC_APB1RSTR_usart2rst(uint8_t bool)
{
	rcc_setbit(&RCC->APB1RSTR, 1, 17, bool);
}
void STM32446RCC_APB1RSTR_spdifrxrst(uint8_t bool)
{
	rcc_setbit(&RCC->APB1RSTR, 1, 16, bool);
}
void STM32446RCC_APB1RSTR_spi3rst(uint8_t bool)
{
	rcc_setbit(&RCC->APB1RSTR, 1, 15, bool);
}
void STM32446RCC_APB1RSTR_spi2rst(uint8_t bool)
{
	rcc_setbit(&RCC->APB1RSTR, 1, 14, bool);
}
void STM32446RCC_APB1RSTR_wwdgrst(uint8_t bool)
{
	rcc_setbit(&RCC->APB1RSTR, 1, 11, bool);
}
void STM32446RCC_APB1RSTR_tim14rst(uint8_t bool)
{
	rcc_setbit(&RCC->APB1RSTR, 1, 8, bool);
}
void STM32446RCC_APB1RSTR_tim13rst(uint8_t bool)
{
	rcc_setbit(&RCC->APB1RSTR, 1, 7, bool);
}
void STM32446RCC_APB1RSTR_tim12rst(uint8_t bool)
{
	rcc_setbit(&RCC->APB1RSTR, 1, 6, bool);
}
void STM32446RCC_APB1RSTR_tim7rst(uint8_t bool)
{
	rcc_setbit(&RCC->APB1RSTR, 1, 5, bool);
}
void STM32446RCC_APB1RSTR_tim6rst(uint8_t bool)
{
	rcc_setbit(&RCC->APB1RSTR, 1, 4, bool);
}
void STM32446RCC_APB1RSTR_tim5rst(uint8_t bool)
{
	rcc_setbit(&RCC->APB1RSTR, 1, 3, bool);
}
void STM32446RCC_APB1RSTR_tim4rst(uint8_t bool)
{
	rcc_setbit(&RCC->APB1RSTR, 1, 2, bool);
}
void STM32446RCC_APB1RSTR_tim3rst(uint8_t bool)
{
	rcc_setbit(&RCC->APB1RSTR, 1, 1, bool);
}
void STM32446RCC_APB1RSTR_tim2rst(uint8_t bool)
{
	rcc_setbit(&RCC->APB1RSTR, 1, 0, bool);
}

// APB2RSTR
void STM32446RCC_APB2RSTR_sai2rst(uint8_t bool)
{
	rcc_setbit(&RCC->APB2RSTR, 1, 23, bool);
}
void STM32446RCC_APB2RSTR_sai1rst(uint8_t bool)
{
	rcc_setbit(&RCC->APB2RSTR, 1, 22, bool);
}
void STM32446RCC_APB2RSTR_tim11rst(uint8_t bool)
{
	rcc_setbit(&RCC->APB2RSTR, 1, 18, bool);
}
void STM32446RCC_APB2RSTR_tim10rst(uint8_t bool)
{
	rcc_setbit(&RCC->APB2RSTR, 1, 17, bool);
}
void STM32446RCC_APB2RSTR_tim9rst(uint8_t bool)
{
	rcc_setbit(&RCC->APB2RSTR, 1, 16, bool);
}
void STM32446RCC_APB2RSTR_syscfgrst(uint8_t bool)
{
	rcc_setbit(&RCC->APB2RSTR, 1, 14, bool);
}
void STM32446RCC_APB2RSTR_spi4rst(uint8_t bool)
{
	rcc_setbit(&RCC->APB2RSTR, 1, 13, bool);
}
void STM32446RCC_APB2RSTR_spi1rst(uint8_t bool)
{
	rcc_setbit(&RCC->APB2RSTR, 1, 12, bool);
}
void STM32446RCC_APB2RSTR_sdiorst(uint8_t bool)
{
	rcc_setbit(&RCC->APB2RSTR, 1, 11, bool);
}
void STM32446RCC_APB2RSTR_adcrst(uint8_t bool)
{
	rcc_setbit(&RCC->APB2RSTR, 1, 8, bool);
}
void STM32446RCC_APB2RSTR_usart6rst(uint8_t bool)
{
	rcc_setbit(&RCC->APB2RSTR, 1, 5, bool);
}
void STM32446RCC_APB2RSTR_usart1rst(uint8_t bool)
{
	rcc_setbit(&RCC->APB2RSTR, 1, 4, bool);
}
void STM32446RCC_APB2RSTR_tim8rst(uint8_t bool)
{
	rcc_setbit(&RCC->APB2RSTR, 1, 1, bool);
}
void STM32446RCC_APB2RSTR_tim1rst(uint8_t bool)
{
	rcc_setbit(&RCC->APB2RSTR, 1, 0, bool);
}

// AHB1ENR
void STM32446RCC_AHB1ENR_otghsulpien(uint8_t bool)
{
	rcc_setbit(&RCC->AHB1ENR, 1, 30, bool);
}
void STM32446RCC_AHB1ENR_otghsen(uint8_t bool)
{
	rcc_setbit(&RCC->AHB1ENR, 1, 29, bool);
}
void STM32446RCC_AHB1ENR_dma2en(uint8_t bool)
{
	rcc_setbit(&RCC->AHB1ENR, 1, 22, bool);
}
void STM32446RCC_AHB1ENR_dma1en(uint8_t bool)
{
	rcc_setbit(&RCC->AHB1ENR, 1, 21, bool);
}
void STM32446RCC_AHB1ENR_bkpsramen(uint8_t bool)
{
	rcc_setbit(&RCC->AHB1ENR, 1, 18, bool);
}
void STM32446RCC_AHB1ENR_crcen(uint8_t bool)
{
	rcc_setbit(&RCC->AHB1ENR, 1, 12, bool);
}
void STM32446RCC_AHB1ENR_gpiohen(uint8_t bool)
{
	rcc_setbit(&RCC->AHB1ENR, 1, 7, bool);
}
void STM32446RCC_AHB1ENR_gpiogen(uint8_t bool)
{
	rcc_setbit(&RCC->AHB1ENR, 1, 6, bool);
}
void STM32446RCC_AHB1ENR_gpiofen(uint8_t bool)
{
	rcc_setbit(&RCC->AHB1ENR, 1, 5, bool);
}
void STM32446RCC_AHB1ENR_gpioeen(uint8_t bool)
{
	rcc_setbit(&RCC->AHB1ENR, 1, 4, bool);
}
void STM32446RCC_AHB1ENR_gpioden(uint8_t bool)
{
	rcc_setbit(&RCC->AHB1ENR, 1, 3, bool);
}
void STM32446RCC_AHB1ENR_gpiocen(uint8_t bool)
{
	rcc_setbit(&RCC->AHB1ENR, 1, 2, bool);
}
void STM32446RCC_AHB1ENR_gpioben(uint8_t bool)
{
	rcc_setbit(&RCC->AHB1ENR, 1, 1, bool);
}
void STM32446RCC_AHB1ENR_gpioaen(uint8_t bool)
{
	rcc_setbit(&RCC->AHB1ENR, 1, 0, bool);
}

// AHB2ENR
void STM32446RCC_AHB2ENR_otgfsen(uint8_t bool)
{
	rcc_setbit(&RCC->AHB2ENR, 1, 7, bool);
}
void STM32446RCC_AHB2ENR_dcmien(uint8_t bool)
{
	rcc_setbit(&RCC->AHB2ENR, 1, 0, bool);
}

// AHB3ENR
void STM32446RCC_AHB3ENR_qspien(uint8_t bool)
{
	rcc_setbit(&RCC->AHB3ENR, 1, 1, bool);
}
void STM32446RCC_AHB3ENR_fmcen(uint8_t bool)
{
	rcc_setbit(&RCC->AHB3ENR, 1, 0, bool);
}

// APB1ENR
void STM32446RCC_APB1ENR_dacen(uint8_t bool)
{
	rcc_setbit(&RCC->APB1ENR, 1, 29, bool);
}
void STM32446RCC_APB1ENR_pwren(uint8_t bool)
{
	rcc_setbit(&RCC->APB1ENR, 1, 28, bool);
}
void STM32446RCC_APB1ENR_cecen(uint8_t bool)
{
	rcc_setbit(&RCC->APB1ENR, 1, 27, bool);
}
void STM32446RCC_APB1ENR_can2en(uint8_t bool)
{
	rcc_setbit(&RCC->APB1ENR, 1, 26, bool);
}
void STM32446RCC_APB1ENR_can1en(uint8_t bool)
{
	rcc_setbit(&RCC->APB1ENR, 1, 25, bool);
}
void STM32446RCC_APB1ENR_fmpi2c1en(uint8_t bool)
{
	rcc_setbit(&RCC->APB1ENR, 1, 24, bool);
}
void STM32446RCC_APB1ENR_i2c3en(uint8_t bool)
{
	rcc_setbit(&RCC->APB1ENR, 1, 23, bool);
}
void STM32446RCC_APB1ENR_i2c2en(uint8_t bool)
{
	rcc_setbit(&RCC->APB1ENR, 1, 22, bool);
}
void STM32446RCC_APB1ENR_i2c1en(uint8_t bool)
{
	rcc_setbit(&RCC->APB1ENR, 1, 21, bool);
}
void STM32446RCC_APB1ENR_uart5en(uint8_t bool)
{
	rcc_setbit(&RCC->APB1ENR, 1, 20, bool);
}
void STM32446RCC_APB1ENR_uart4en(uint8_t bool)
{
	rcc_setbit(&RCC->APB1ENR, 1, 19, bool);
}
void STM32446RCC_APB1ENR_usart3en(uint8_t bool)
{
	rcc_setbit(&RCC->APB1ENR, 1, 18, bool);
}
void STM32446RCC_APB1ENR_usart2en(uint8_t bool)
{
	rcc_setbit(&RCC->APB1ENR, 1, 17, bool);
}
void STM32446RCC_APB1ENR_spdifrxen(uint8_t bool)
{
	rcc_setbit(&RCC->APB1ENR, 1, 16, bool);
}
void STM32446RCC_APB1ENR_spi3en(uint8_t bool)
{
	rcc_setbit(&RCC->APB1ENR, 1, 15, bool);
}
void STM32446RCC_APB1ENR_spi2en(uint8_t bool)
{
	rcc_setbit(&RCC->APB1ENR, 1, 14, bool);
}
void STM32446RCC_APB1ENR_wwdgen(uint8_t bool)
{
	rcc_setbit(&RCC->APB1ENR, 1, 11, bool);
}
void STM32446RCC_APB1ENR_tim14en(uint8_t bool)
{
	rcc_setbit(&RCC->APB1ENR, 1, 8, bool);
}
void STM32446RCC_APB1ENR_tim13en(uint8_t bool)
{
	rcc_setbit(&RCC->APB1ENR, 1, 7, bool);
}
void STM32446RCC_APB1ENR_tim12en(uint8_t bool)
{
	rcc_setbit(&RCC->APB1ENR, 1, 6, bool);
}
void STM32446RCC_APB1ENR_tim7en(uint8_t bool)
{
	rcc_setbit(&RCC->APB1ENR, 1, 5, bool);
}
void STM32446RCC_APB1ENR_tim6en(uint8_t bool)
{
	rcc_setbit(&RCC->APB1ENR, 1, 4, bool);
}
void STM32446RCC_APB1ENR_tim5en(uint8_t bool)
{
	rcc_setbit(&RCC->APB1ENR, 1, 3, bool);
}
void STM32446RCC_APB1ENR_tim4en(uint8_t bool)
{
	rcc_setbit(&RCC->APB1ENR, 1, 2, bool);
}
void STM32446RCC_APB1ENR_tim3en(uint8_t bool)
{
	rcc_setbit(&RCC->APB1ENR, 1, 1, bool);
}
void STM32446RCC_APB1ENR_tim2en(uint8_t bool)
{
	rcc_setbit(&RCC->APB1ENR, 1, 0, bool);
}

// APB2ENR
void STM32446RCC_APB2ENR_sai2en(uint8_t bool)
{
	rcc_setbit(&RCC->APB2ENR, 1, 23, bool);
}
void STM32446RCC_APB2ENR_sai1en(uint8_t bool)
{
	rcc_setbit(&RCC->APB2ENR, 1, 22, bool);
}
void STM32446RCC_APB2ENR_tim11en(uint8_t bool)
{
	rcc_setbit(&RCC->APB2ENR, 1, 18, bool);
}
void STM32446RCC_APB2ENR_tim10en(uint8_t bool)
{
	rcc_setbit(&RCC->APB2ENR, 1, 17, bool);
}
void STM32446RCC_APB2ENR_tim9en(uint8_t bool)
{
	rcc_setbit(&RCC->APB2ENR, 1, 16, bool);
}
void STM32446RCC_APB2ENR_syscfgen(uint8_t bool)
{
	rcc_setbit(&RCC->APB2ENR, 1, 14, bool);
}
void STM32446RCC_APB2ENR_spi4en(uint8_t bool)
{
	rcc_setbit(&RCC->APB2ENR, 1, 13, bool);
}
void STM32446RCC_APB2ENR_spi1en(uint8_t bool)
{
	rcc_setbit(&RCC->APB2ENR, 1, 12, bool);
}
void STM32446RCC_APB2ENR_sdioen(uint8_t bool)
{
	rcc_setbit(&RCC->APB2ENR, 1, 11, bool);
}
void STM32446RCC_APB2ENR_adc3en(uint8_t bool)
{
	rcc_setbit(&RCC->APB2ENR, 1, 10, bool);
}
void STM32446RCC_APB2ENR_adc2en(uint8_t bool)
{
	rcc_setbit(&RCC->APB2ENR, 1, 9, bool);
}
void STM32446RCC_APB2ENR_adc1en(uint8_t bool)
{
	rcc_setbit(&RCC->APB2ENR, 1, 8, bool);
}
void STM32446RCC_APB2ENR_usart6en(uint8_t bool)
{
	rcc_setbit(&RCC->APB2ENR, 1, 5, bool);
}
void STM32446RCC_APB2ENR_usart1en(uint8_t bool)
{
	rcc_setbit(&RCC->APB2ENR, 1, 4, bool);
}
void STM32446RCC_APB2ENR_tim8en(uint8_t bool)
{
	rcc_setbit(&RCC->APB2ENR, 1, 1, bool);
}
void STM32446RCC_APB2ENR_tim1en(uint8_t bool)
{
	rcc_setbit(&RCC->APB2ENR, 1, 0, bool);
}

//AHB1LPENR
void STM32446RCC_AHB1LPENR_otghsulpilpen(uint8_t bool)
{
	rcc_setbit(&RCC->AHB1LPENR, 1, 30, bool);
}
void STM32446RCC_AHB1LPENR_otghslpen(uint8_t bool)
{
	rcc_setbit(&RCC->AHB1LPENR, 1, 29, bool);
}
void STM32446RCC_AHB1LPENR_dma2lpen(uint8_t bool)
{
	rcc_setbit(&RCC->AHB1LPENR, 1, 22, bool);
}
void STM32446RCC_AHB1LPENR_dma1lpen(uint8_t bool)
{
	rcc_setbit(&RCC->AHB1LPENR, 1, 21, bool);
}
void STM32446RCC_AHB1LPENR_bkpsramlpen(uint8_t bool)
{
	rcc_setbit(&RCC->AHB1LPENR, 1, 18, bool);
}
void STM32446RCC_AHB1LPENR_sram2lpen(uint8_t bool)
{
	rcc_setbit(&RCC->AHB1LPENR, 1, 17, bool);
}
void STM32446RCC_AHB1LPENR_sram1lpen(uint8_t bool)
{
	rcc_setbit(&RCC->AHB1LPENR, 1, 16, bool);
}
void STM32446RCC_AHB1LPENR_flitflpen(uint8_t bool)
{
	rcc_setbit(&RCC->AHB1LPENR, 1, 15, bool);
}
void STM32446RCC_AHB1LPENR_crclpen(uint8_t bool)
{
	rcc_setbit(&RCC->AHB1LPENR, 1, 12, bool);
}
void STM32446RCC_AHB1LPENR_gpiohlpen(uint8_t bool)
{
	rcc_setbit(&RCC->AHB1LPENR, 1, 7, bool);
}
void STM32446RCC_AHB1LPENR_gpioglpen(uint8_t bool)
{
	rcc_setbit(&RCC->AHB1LPENR, 1, 6, bool);
}
void STM32446RCC_AHB1LPENR_gpioflpen(uint8_t bool)
{
	rcc_setbit(&RCC->AHB1LPENR, 1, 5, bool);
}
void STM32446RCC_AHB1LPENR_gpioelpen(uint8_t bool)
{
	rcc_setbit(&RCC->AHB1LPENR, 1, 4, bool);
}
void STM32446RCC_AHB1LPENR_gpiodlpen(uint8_t bool)
{
	rcc_setbit(&RCC->AHB1LPENR, 1, 3, bool);
}
void STM32446RCC_AHB1LPENR_gpioclpen(uint8_t bool)
{
	rcc_setbit(&RCC->AHB1LPENR, 1, 2, bool);
}
void STM32446RCC_AHB1LPENR_gpioblpen(uint8_t bool)
{
	rcc_setbit(&RCC->AHB1LPENR, 1, 1, bool);
}
void STM32446RCC_AHB1LPENR_gpioalpen(uint8_t bool)
{
	rcc_setbit(&RCC->AHB1LPENR, 1, 0, bool);
}

// AHB2LPENR
void STM32446RCC_AHB2LPENR_otgfslpen(uint8_t bool)
{
	rcc_setbit(&RCC->AHB2LPENR, 1, 7, bool);
}
void STM32446RCC_AHB2LPENR_dcmilpen(uint8_t bool)
{
	rcc_setbit(&RCC->AHB2LPENR, 1, 0, bool);
}

// AHB3LPENR
void STM32446RCC_AHB3LPENR_qspilpen(uint8_t bool)
{
	rcc_setbit(&RCC->AHB3LPENR, 1, 1, bool);
}
void STM32446RCC_AHB3LPENR_fmclpen(uint8_t bool)
{
	rcc_setbit(&RCC->AHB3LPENR, 1, 0, bool);
}

// APB1LPENR
void STM32446RCC_APB1LPENR_daclpen(uint8_t bool)
{
	rcc_setbit(&RCC->APB1LPENR, 1, 29, bool);
}
void STM32446RCC_APB1LPENR_pwrlpen(uint8_t bool)
{
	rcc_setbit(&RCC->APB1LPENR, 1, 28, bool);
}
void STM32446RCC_APB1LPENR_ceclpen(uint8_t bool)
{
	rcc_setbit(&RCC->APB1LPENR, 1, 27, bool);
}
void STM32446RCC_APB1LPENR_can2lpen(uint8_t bool)
{
	rcc_setbit(&RCC->APB1LPENR, 1, 26, bool);
}
void STM32446RCC_APB1LPENR_can1lpen(uint8_t bool)
{
	rcc_setbit(&RCC->APB1LPENR, 1, 25, bool);
}
void STM32446RCC_APB1LPENR_fmpi2c1lpen(uint8_t bool)
{
	rcc_setbit(&RCC->APB1LPENR, 1, 24, bool);
}
void STM32446RCC_APB1LPENR_i2c3lpen(uint8_t bool)
{
	rcc_setbit(&RCC->APB1LPENR, 1, 23, bool);
}
void STM32446RCC_APB1LPENR_i2c2lpen(uint8_t bool)
{
	rcc_setbit(&RCC->APB1LPENR, 1, 22, bool);
}
void STM32446RCC_APB1LPENR_i2c1lpen(uint8_t bool)
{
	rcc_setbit(&RCC->APB1LPENR, 1, 21, bool);
}
void STM32446RCC_APB1LPENR_uart5lpen(uint8_t bool)
{
	rcc_setbit(&RCC->APB1LPENR, 1, 20, bool);
}
void STM32446RCC_APB1LPENR_uart4lpen(uint8_t bool)
{
	rcc_setbit(&RCC->APB1LPENR, 1, 19, bool);
}
void STM32446RCC_APB1LPENR_usart3lpen(uint8_t bool)
{
	rcc_setbit(&RCC->APB1LPENR, 1, 18, bool);
}
void STM32446RCC_APB1LPENR_usart2lpen(uint8_t bool)
{
	rcc_setbit(&RCC->APB1LPENR, 1, 17, bool);
}
void STM32446RCC_APB1LPENR_spdifrxlpen(uint8_t bool)
{
	rcc_setbit(&RCC->APB1LPENR, 1, 16, bool);
}
void STM32446RCC_APB1LPENR_spi3lpen(uint8_t bool)
{
	rcc_setbit(&RCC->APB1LPENR, 1, 15, bool);
}
void STM32446RCC_APB1LPENR_spi2lpen(uint8_t bool)
{
	rcc_setbit(&RCC->APB1LPENR, 1, 14, bool);
}
void STM32446RCC_APB1LPENR_wwdglpen(uint8_t bool)
{
	rcc_setbit(&RCC->APB1LPENR, 1, 11, bool);
}
void STM32446RCC_APB1LPENR_tim14lpen(uint8_t bool)
{
	rcc_setbit(&RCC->APB1LPENR, 1, 8, bool);
}
void STM32446RCC_APB1LPENR_tim13lpen(uint8_t bool)
{
	rcc_setbit(&RCC->APB1LPENR, 1, 7, bool);
}
void STM32446RCC_APB1LPENR_tim12lpen(uint8_t bool)
{
	rcc_setbit(&RCC->APB1LPENR, 1, 6, bool);
}
void STM32446RCC_APB1LPENR_tim7lpen(uint8_t bool)
{
	rcc_setbit(&RCC->APB1LPENR, 1, 5, bool);
}
void STM32446RCC_APB1LPENR_tim6lpen(uint8_t bool)
{
	rcc_setbit(&RCC->APB1LPENR, 1, 4, bool);
}
void STM32446RCC_APB1LPENR_tim5lpen(uint8_t bool)
{
	rcc_setbit(&RCC->APB1LPENR, 1, 3, bool);
}
void STM32446RCC_APB1LPENR_tim4lpen(uint8_t bool)
{
	rcc_setbit(&RCC->APB1LPENR, 1, 2, bool);
}
void STM32446RCC_APB1LPENR_tim3lpen(uint8_t bool)
{
	rcc_setbit(&RCC->APB1LPENR, 1, 1, bool);
}
void STM32446RCC_APB1LPENR_tim2lpen(uint8_t bool)
{
	rcc_setbit(&RCC->APB1LPENR, 1, 0, bool);
}

// APB2LPENR
void STM32446RCC_APB2LPENR_sai2lpen(uint8_t bool)
{
	rcc_setbit(&RCC->APB2LPENR, 1, 23, bool);
}
void STM32446RCC_APB2LPENR_sai1lpen(uint8_t bool)
{
	rcc_setbit(&RCC->APB2LPENR, 1, 22, bool);
}
void STM32446RCC_APB2LPENR_tim11lpen(uint8_t bool)
{
	rcc_setbit(&RCC->APB2LPENR, 1, 18, bool);
}
void STM32446RCC_APB2LPENR_tim10lpen(uint8_t bool)
{
	rcc_setbit(&RCC->APB2LPENR, 1, 17, bool);
}
void STM32446RCC_APB2LPENR_tim9lpen(uint8_t bool)
{
	rcc_setbit(&RCC->APB2LPENR, 1, 16, bool);
}
void STM32446RCC_APB2LPENR_syscfglpen(uint8_t bool)
{
	rcc_setbit(&RCC->APB2LPENR, 1, 14, bool);
}
void STM32446RCC_APB2LPENR_spi4lpen(uint8_t bool)
{
	rcc_setbit(&RCC->APB2LPENR, 1, 13, bool);
}
void STM32446RCC_APB2LPENR_spi1lpen(uint8_t bool)
{
	rcc_setbit(&RCC->APB2LPENR, 1, 12, bool);
}
void STM32446RCC_APB2LPENR_sdiolpen(uint8_t bool)
{
	rcc_setbit(&RCC->APB2LPENR, 1, 11, bool);
}
void STM32446RCC_APB2LPENR_adc3lpen(uint8_t bool)
{
	rcc_setbit(&RCC->APB2LPENR, 1, 10, bool);
}
void STM32446RCC_APB2LPENR_adc2lpen(uint8_t bool)
{
	rcc_setbit(&RCC->APB2LPENR, 1, 9, bool);
}
void STM32446RCC_APB2LPENR_adc1lpen(uint8_t bool)
{
	rcc_setbit(&RCC->APB2LPENR, 1, 8, bool);
}
void STM32446RCC_APB2LPENR_usart6lpen(uint8_t bool)
{
	rcc_setbit(&RCC->APB2LPENR, 1, 5, bool);
}
void STM32446RCC_APB2LPENR_usart1lpen(uint8_t bool)
{
	rcc_setbit(&RCC->APB2LPENR, 1, 4, bool);
}
void STM32446RCC_APB2LPENR_tim8lpen(uint8_t bool)
{
	rcc_setbit(&RCC->APB2LPENR, 1, 1, bool);
}
void STM32446RCC_APB2LPENR_tim1lpen(uint8_t bool)
{
	rcc_setbit(&RCC->APB2LPENR, 1, 0, bool);
}

// BDCR
void STM32446RCC_BDCR_bdrst(uint8_t bool)
{
	rcc_setbit(&RCC->BDCR, 1, 16, bool);
}
void STM32446RCC_BDCR_rtcen(uint8_t bool)
{
	rcc_setbit(&RCC->BDCR, 1, 15, bool);
}
void STM32446RCC_BDCR_rtcsel(uint8_t value)
{
	rcc_setbit(&RCC->BDCR, 2, 8, value);
}
void STM32446RCC_BDCR_lsemod(uint8_t bool)
{
	rcc_setbit(&RCC->BDCR, 1, 3, bool);
}
void STM32446RCC_BDCR_lsebyp(uint8_t bool)
{
	rcc_setbit(&RCC->BDCR, 1, 2, bool);
}
uint8_t STM32446RCC_BDCR_get_lserdy(void)
{
	return rcc_getbit(RCC->BDCR, 1, 1);
}
void STM32446RCC_BDCR_lseon(uint8_t bool)
{
	rcc_setbit(&RCC->BDCR, 1, 0, bool);
}

// CSR
uint8_t STM32446RCC_CSR_get_lpwrrstf(void)
{
	return rcc_getbit(RCC->CSR, 1, 31);
}
uint8_t STM32446RCC_CSR_get_wwdgrstf(void)
{
	return rcc_getbit(RCC->CSR, 1, 30);
}
uint8_t STM32446RCC_CSR_get_iwdqrstf(void)
{
	return rcc_getbit(RCC->CSR, 1, 29);
}
uint8_t STM32446RCC_CSR_get_sftrstf(void)
{
	return rcc_getbit(RCC->CSR, 1, 28);
}
uint8_t STM32446RCC_CSR_get_porrstf(void)
{
	return rcc_getbit(RCC->CSR, 1, 27);
}
uint8_t STM32446RCC_CSR_get_pinrstf(void)
{
	return rcc_getbit(RCC->CSR, 1, 26);
}
uint8_t STM32446RCC_CSR_get_borrstf(void)
{
	return rcc_getbit(RCC->CSR, 1, 25);
}
void STM32446RCC_CSR_clear_rmvf(void)
{
	rcc_setbit(&RCC->CSR, 1, 24, 1);
}
uint8_t STM32446RCC_CSR_get_lsirdy(void)
{
	return rcc_getbit(RCC->CSR, 1, 1);
}
void STM32446RCC_CSR_lsion(uint8_t bool)
{
	rcc_setbit(&RCC->CSR, 1, 0, bool);
}

// SSCGR
void STM32446RCC_SSCGR_sscgen(uint8_t bool)
{
	rcc_setbit(&RCC->SSCGR, 1, 31, bool);
}
void STM32446RCC_SSCGR_spreadsel(uint8_t bool)
{
	rcc_setbit(&RCC->SSCGR, 1, 30, bool);
}
void STM32446RCC_SSCGR_incstep(uint8_t value)
{
	rcc_setbit(&RCC->SSCGR, 15, 13, value);
}
void STM32446RCC_SSCGR_modper(uint8_t value)
{
	rcc_setbit(&RCC->SSCGR, 13, 0, value);
}

// PLLI2SCFGR
void STM32446RCC_PLLI2SCFGR_plli2sr(uint8_t value)
{
	rcc_setbit(&RCC->PLLI2SCFGR, 3, 28, value);
}
void STM32446RCC_PLLI2SCFGR_plli2sq(uint8_t value)
{
	rcc_setbit(&RCC->PLLI2SCFGR, 4, 24, value);
}
void STM32446RCC_PLLI2SCFGR_plli2sp(uint8_t value)
{
	rcc_setbit(&RCC->PLLI2SCFGR, 2, 16, value);
}
void STM32446RCC_PLLI2SCFGR_plli2sn(uint16_t value)
{
	rcc_setbit(&RCC->PLLI2SCFGR, 9, 6, value);
}
void STM32446RCC_PLLI2SCFGR_plli2sm(uint8_t value)
{
	rcc_setbit(&RCC->PLLI2SCFGR, 6, 0, value);
}

// PLLSAICFGR
void STM32446RCC_PLLSAICFGR_pllsaiq(uint8_t value)
{
	rcc_setbit(&RCC->PLLSAICFGR, 4, 24, value);
}
void STM32446RCC_PLLSAICFGR_pllsaip(uint8_t value)
{
	rcc_setbit(&RCC->PLLSAICFGR, 2, 16, value);
}
void STM32446RCC_PLLSAICFGR_pllsain(uint16_t value)
{
	rcc_setbit(&RCC->PLLSAICFGR, 9, 6, value);
}
void STM32446RCC_PLLSAICFGR_pllsaim(uint8_t value)
{
	rcc_setbit(&RCC->PLLSAICFGR, 6, 0, value);
}

// DCKCFGR
void STM32446RCC_DCKCFGR_i2s2src(uint8_t value)
{
	rcc_setbit(&RCC->DCKCFGR, 2, 27, value);
}
void STM32446RCC_DCKCFGR_i2s1src(uint8_t value)
{
	rcc_setbit(&RCC->DCKCFGR, 2, 25, value);
}
void STM32446RCC_DCKCFGR_timpre(uint8_t bool)
{
	rcc_setbit(&RCC->DCKCFGR, 1, 24, bool);
}
void STM32446RCC_DCKCFGR_sai2src(uint8_t value)
{
	rcc_setbit(&RCC->DCKCFGR, 2, 22, value);
}
void STM32446RCC_DCKCFGR_sai1src(uint8_t value)
{
	rcc_setbit(&RCC->DCKCFGR, 2, 20, value);
}
void STM32446RCC_DCKCFGR_pllsaidivq(uint8_t value)
{
	rcc_setbit(&RCC->DCKCFGR, 5, 8, value);
}
void STM32446RCC_DCKCFGR_plli2sdivq(uint8_t value)
{
	rcc_setbit(&RCC->DCKCFGR, 5, 0, value);
}

// CKGATENR
void STM32446RCC_CKGATENR_rcc_cken(uint8_t bool)
{
	rcc_setbit(&RCC->CKGATENR, 1, 6, bool);
}
void STM32446RCC_CKGATENR_flitf_cken(uint8_t bool)
{
	rcc_setbit(&RCC->CKGATENR, 1, 5, bool);
}
void STM32446RCC_CKGATENR_sram_cken(uint8_t bool)
{
	rcc_setbit(&RCC->CKGATENR, 1, 4, bool);
}
void STM32446RCC_CKGATENR_spare_cken(uint8_t bool)
{
	rcc_setbit(&RCC->CKGATENR, 1, 3, bool);
}
void STM32446RCC_CKGATENR_cm4dbg_cken(uint8_t bool)
{
	rcc_setbit(&RCC->CKGATENR, 1, 2, bool);
}
void STM32446RCC_CKGATENR_ahb2apb2_cken(uint8_t bool)
{
	rcc_setbit(&RCC->CKGATENR, 1, 1, bool);
}
void STM32446RCC_CKGATENR_ahb2apb1_cken(uint8_t bool)
{
	rcc_setbit(&RCC->CKGATENR, 1, 0, bool);
}

// DCKCFGR2
void STM32446RCC_DCKCFGR2_spdifrxsel(uint8_t bool)
{
	rcc_setbit(&RCC->DCKCFGR2, 1, 29, bool);
}
void STM32446RCC_DCKCFGR2_sdiosel(uint8_t bool)
{
	rcc_setbit(&RCC->DCKCFGR2, 1, 28, bool);
}
void STM32446RCC_DCKCFGR2_ck48msel(uint8_t bool)
{
	rcc_setbit(&RCC->DCKCFGR2, 1, 27, bool);
}
void STM32446RCC_DCKCFGR2_cecsel(uint8_t bool)
{
	rcc_setbit(&RCC->DCKCFGR2, 1, 26, bool);
}
void STM32446RCC_DCKCFGR2_fmpi2c1sel(uint8_t value)
{
	rcc_setbit(&RCC->DCKCFGR2, 2, 22, value);
}

/*** File Procedure & Function Definition ***/
uint32_t rcc_getbit(uint32_t reg, uint32_t size_block, uint32_t bit)
{
	uint32_t value = 0; uint32_t tmp = 0;
	uint32_t mask = (unsigned int)((1 << size_block) - 1);
	mask = (mask << bit);
	tmp = mask & reg;
	value = (tmp >> bit);
	return value;
}

void rcc_setbit(volatile uint32_t* reg, uint32_t size_block, uint32_t bit, uint32_t data)
{
	uint32_t n = 0;
	if(bit > 31){ n = bit/32; bit = bit - (n * 32); }
	uint32_t value = 0;
	uint32_t mask = (unsigned int)((1 << size_block) - 1);
	value = data & mask;
	*(reg + n ) &= ~(mask << bit);
	*(reg + n ) |= (value << bit);
}

uint32_t rcc_getsetbit(volatile uint32_t* reg, uint32_t size_block, uint32_t bit)
{
	uint32_t n = 0;
	if(bit > 31){ n = bit/32; bit = bit - (n * 32); }
	uint32_t value = 0;
	uint32_t mask = (unsigned int)((1 << size_block) - 1);
	value = *(reg + n ) & (mask << bit);
	value = (value >> bit);
	return value;
}

/*** EOF ***/

/*
 * Everytime a library header is called, it is a copy.
 *
 *
 */



