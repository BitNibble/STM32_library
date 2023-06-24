/******************************************************************************
	STM32 446 RCC
Author: Sergio Santos 
	<sergio.salazar.santos@gmail.com>
License: GNU General Public License
Hardware: STM32-446
Date: 19062023
Comment:
	
*******************************************************************************/
/*** File Library ***/
#include "stm32446mapping.h"
#include "stm32446rcc.h"

static uint32_t rcc_time_out;

/*** File Procedure & Function Header ***/
uint32_t rcc_readreg(uint32_t reg, uint32_t size_block, uint32_t bit);
void rcc_writereg(volatile uint32_t* reg, uint32_t size_block, uint32_t bit, uint32_t data);
void rcc_setreg(volatile uint32_t* reg, uint32_t size_block, uint32_t bit, uint32_t data);
void rcc_setbit(volatile uint32_t* reg, uint32_t size_block, uint32_t bit, uint32_t data);
uint32_t rcc_getsetbit(volatile uint32_t* reg, uint32_t size_block, uint32_t bit);
STM32446RCC_cr stm32446_rcc_cr_inic(void);
STM32446RCC_pllcfgr stm32446_rcc_pllcfgr_inic(void);
STM32446RCC_cfgr stm32446_rcc_cfgr_inic(void);
STM32446RCC_cir stm32446_rcc_cir_inic(void);
STM32446RCC_ahb1rstr stm32446_rcc_ahb1rstr_inic(void);
STM32446RCC_ahb2rstr stm32446_rcc_ahb2rstr_inic(void);
STM32446RCC_ahb3rstr stm32446_rcc_ahb3rstr_inic(void);
STM32446RCC_apb1rstr stm32446_rcc_apb1rstr_inic(void);
STM32446RCC_apb2rstr stm32446_rcc_apb2rstr_inic(void);
STM32446RCC_ahb1enr stm32446_rcc_ahb1enr_inic(void);
STM32446RCC_ahb2enr stm32446_rcc_ahb2enr_inic(void);
STM32446RCC_ahb3enr stm32446_rcc_ahb3enr_inic(void);
STM32446RCC_apb1enr stm32446_rcc_apb1enr_inic(void);
STM32446RCC_apb2enr stm32446_rcc_apb2enr_inic(void);
STM32446RCC_ahb1lpenr stm32446_rcc_ahb1lpenr_inic(void);
STM32446RCC_ahb2lpenr stm32446_rcc_ahb2lpenr_inic(void);
STM32446RCC_ahb3lpenr stm32446_rcc_ahb3lpenr_inic(void);
STM32446RCC_apb1lpenr stm32446_rcc_apb1lpenr_inic(void);
STM32446RCC_apb2lpenr stm32446_rcc_apb2lpenr_inic(void);
STM32446RCC_bdcr stm32446_rcc_bdcr_inic(void);
STM32446RCC_csr stm32446_rcc_csr_inic(void);
STM32446RCC_sscgr stm32446_rcc_sscgr_inic(void);
STM32446RCC_plli2scfgr stm32446_rcc_plli2scfgr_inic(void);
STM32446RCC_pllsaicfgr stm32446_rcc_pllsaicfgr_inic(void);
STM32446RCC_dckcfgr stm32446_rcc_dckcfgr_inic(void);
STM32446RCC_ckgatenr stm32446_rcc_ckgatenr_inic(void);
STM32446RCC_dckcfgr2 stm32446_rcc_dckcfgr2_inic(void);
/*** Extended ***/
STM32446RCCPLL stm32446_rcc_pll_inic(void);
STM32446RCCPLLI2S stm32446_rcc_plli2s_inic(void);
STM32446RCCPLLSAI stm32446_rcc_pllsai_inic(void);

/*** RCC Procedure & Function Definition ***/
void STM32446RccInic(void)
{
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
	STM32446RccHSelect(0); // SW[1:0]: System clock switch 00 - HSI, 01 - HSE pg133
	// Low Speed Internal Clock turned on as default
	// Internal low-speed oscillator enable and Internal low-speed oscillator ready
	STM32446RccLEnable(2);
	// Low speed oscillator select
	STM32446RccLSelect(2);
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
		for( rcc_time_out = 100, RCC->CR |= (1 << 24) ; !(RCC->CR & (1 << 25)) && rcc_time_out; rcc_time_out-- ); // PLLON: Main PLL (PLL) enable
	//}else{
		//RCC->CR &= (unsigned int) ~(1 << 24);
	//}
}
void STM32446RccPLLI2SEnable(void)
{
	//if(onoff)
		for( rcc_time_out = 100, RCC->CR |= (1 << 26) ; !(RCC->CR & (1 << 27)) && rcc_time_out; rcc_time_out-- ); // PLLI2SON: PLLI2S enable
	//else
		//RCC->CR &= (unsigned int) ~(1 << 26);
}
void STM32446RccPLLSAIEnable(void)
{
	//if(onoff)
		for( rcc_time_out = 100, RCC->CR |= (1 << 28) ; !(RCC->CR & (1 << 29)) && rcc_time_out; rcc_time_out-- ); // PLLSAION: PLLSAI enable
	//else
		//RCC->CR &= (unsigned int) ~(1 << 28);
}
/*** RCC Bit Mapping Definition ***/
// CR
uint8_t STM32446RCC_CR_get_pllsairdy(void)
{
	return rcc_readreg(RCC->CR, 1, 29);
}
void STM32446RCC_CR_pllsaion(uint8_t bool)
{
	rcc_setreg(&RCC->CR, 1, 28, bool);
}
uint8_t STM32446RCC_CR_get_plli2srdy(void)
{
	return rcc_readreg(RCC->CR, 1, 27);
}
void STM32446RCC_CR_plli2son(uint8_t bool)
{
	rcc_setreg(&RCC->CR, 1, 26, bool);
}
uint8_t STM32446RCC_CR_get_pllrdy(void)
{
	return rcc_readreg(RCC->CR, 1, 25);
}
void STM32446RCC_CR_pllon(uint8_t bool)
{
	rcc_setreg(&RCC->CR, 1, 24, bool);
}
void STM32446RCC_CR_csson(uint8_t bool)
{
	rcc_setreg(&RCC->CR, 1, 19, bool);
}
void STM32446RCC_CR_hsebyp(uint8_t bool)
{
	rcc_setreg(&RCC->CR, 1, 18, bool);
}
uint8_t STM32446RCC_CR_get_hserdy(void)
{
	return rcc_readreg(RCC->CR, 1, 17);
}
void STM32446RCC_CR_hseon(uint8_t bool)
{
	rcc_setreg(&RCC->CR, 1, 16, bool);
}
uint8_t STM32446RCC_CR_get_hsical(void)
{
	return rcc_readreg(RCC->CR, 8, 8);
}
void STM32446RCC_CR_hsitrim(uint8_t value)
{
	rcc_setreg(&RCC->CR, 5, 3, value);
}
uint8_t STM32446RCC_CR_get_hsirdy(void)
{
	return rcc_readreg(RCC->CR, 1, 1);
}
void STM32446RCC_CR_hsion(uint8_t bool)
{
	rcc_setreg(&RCC->CR, 1, 0, bool);
}
// PLLCFGR
void STM32446RCC_PLLCFGR_pllr(uint8_t value)
{
	rcc_setreg(&RCC->CR, 3, 28, value);
}
void STM32446RCC_PLLCFGR_pllq(uint8_t value)
{
	rcc_setreg(&RCC->CR, 4, 24, value);
}
void STM32446RCC_PLLCFGR_pllsrc(uint8_t bool)
{
	rcc_setreg(&RCC->CR, 1, 22, bool);
}
void STM32446RCC_PLLCFGR_pllp(uint8_t value)
{
	rcc_setreg(&RCC->CR, 2, 16, value);
}
void STM32446RCC_PLLCFGR_plln(uint16_t value)
{
	rcc_setreg(&RCC->CR, 9, 6, value);
}
void STM32446RCC_PLLCFGR_pllm(uint8_t value)
{
	rcc_setreg(&RCC->CR, 6, 0, value);
}
// CFGR
void STM32446RCC_CFGR_mco2(uint8_t value)
{
	rcc_setreg(&RCC->CFGR, 2, 30, value);
}
void STM32446RCC_CFGR_mco2pre(uint8_t value)
{
	rcc_setreg(&RCC->CFGR, 3, 27, value);
}
void STM32446RCC_CFGR_mco1pre(uint8_t value)
{
	rcc_setreg(&RCC->CFGR, 3, 24, value);
}
void STM32446RCC_CFGR_mco1(uint8_t value)
{
	rcc_setreg(&RCC->CFGR, 2, 21, value);
}
void STM32446RCC_CFGR_rtcpre(uint8_t value)
{
	rcc_setreg(&RCC->CFGR, 5, 16, value);
}
void STM32446RCC_CFGR_ppre2(uint8_t value)
{
	rcc_setreg(&RCC->CFGR, 3, 13, value);
}
void STM32446RCC_CFGR_ppre1(uint8_t value)
{
	rcc_setreg(&RCC->CFGR, 3, 10, value);
}
void STM32446RCC_CFGR_hpre(uint8_t value)
{
	rcc_setreg(&RCC->CFGR, 4, 4, value);
}
uint8_t STM32446RCC_CFGR_get_sws(void)
{
	return rcc_readreg(RCC->CFGR, 2, 2);
}
void STM32446RCC_CFGR_sw(uint8_t value)
{
	rcc_setreg(&RCC->CFGR, 2, 0, value);
}
// CIR
void STM32446RCC_CIR_clear_cssc(void)
{
	rcc_setreg(&RCC->CIR, 1, 23, 1);
}
void STM32446RCC_CIR_clear_pllsairdyc(void)
{
	rcc_setreg(&RCC->CIR, 1, 22, 1);
}
void STM32446RCC_CIR_clear_plli2srdyc(void)
{
	rcc_setreg(&RCC->CIR, 1, 21, 1);
}
void STM32446RCC_CIR_clear_pllrdyc(void)
{
	rcc_setreg(&RCC->CIR, 1, 20, 1);
}
void STM32446RCC_CIR_clear_hserdyc(void)
{
	rcc_setreg(&RCC->CIR, 1, 19, 1);
}
void STM32446RCC_CIR_clear_hsirdyc(void)
{
	rcc_setreg(&RCC->CIR, 1, 18, 1);
}
void STM32446RCC_CIR_clear_lserdyc(void)
{
	rcc_setreg(&RCC->CIR, 1, 17, 1);
}
void STM32446RCC_CIR_clear_lsirdyc(void)
{
	rcc_setreg(&RCC->CIR, 1, 16, 1);
}
void STM32446RCC_CIR_pllsairdyie(uint8_t bool)
{
	rcc_setreg(&RCC->CIR, 1, 14, bool);
}
void STM32446RCC_CIR_plli2srdyie(uint8_t bool)
{
	rcc_setreg(&RCC->CIR, 1, 13, bool);
}
void STM32446RCC_CIR_pllrdyie(uint8_t bool)
{
	rcc_setreg(&RCC->CIR, 1, 12, bool);
}
void STM32446RCC_CIR_hserdyie(uint8_t bool)
{
	rcc_setreg(&RCC->CIR, 1, 11, bool);
}
void STM32446RCC_CIR_hsirdyie(uint8_t bool)
{
	rcc_setreg(&RCC->CIR, 1, 10, bool);
}
void STM32446RCC_CIR_lserdyie(uint8_t bool)
{
	rcc_setreg(&RCC->CIR, 1, 9, bool);
}
void STM32446RCC_CIR_lsirdyie(uint8_t bool)
{
	rcc_setreg(&RCC->CIR, 1, 8, bool);
}
uint8_t STM32446RCC_CIR_get_cssf(void)
{
	return rcc_readreg(RCC->CIR, 1, 7);
}
uint8_t STM32446RCC_CIR_get_pllsairdyf(void)
{
	return rcc_readreg(RCC->CIR, 1, 6);
}
uint8_t STM32446RCC_CIR_get_plli2srdyf(void)
{
	return rcc_readreg(RCC->CIR, 1, 5);
}
uint8_t STM32446RCC_CIR_get_pllrdyf(void)
{
	return rcc_readreg(RCC->CIR, 1, 4);
}
uint8_t STM32446RCC_CIR_get_hserdyf(void)
{
	return rcc_readreg(RCC->CIR, 1, 3);
}
uint8_t STM32446RCC_CIR_get_hsirdyf(void)
{
	return rcc_readreg(RCC->CIR, 1, 2);
}
uint8_t STM32446RCC_CIR_get_lserdyf(void)
{
	return rcc_readreg(RCC->CIR, 1, 1);
}
uint8_t STM32446RCC_CIR_get_lsirdyf(void)
{
	return rcc_readreg(RCC->CIR, 1, 0);
}
// AHB1RSTR
void STM32446RCC_AHB1RSTR_otghsrst(uint8_t bool)
{
	rcc_setreg(&RCC->AHB1RSTR, 1, 29, bool);
}
void STM32446RCC_AHB1RSTR_dma2rst(uint8_t bool)
{
	rcc_setreg(&RCC->AHB1RSTR, 1, 22, bool);
}
void STM32446RCC_AHB1RSTR_dma1rst(uint8_t bool)
{
	rcc_setreg(&RCC->AHB1RSTR, 1, 21, bool);
}
void STM32446RCC_AHB1RSTR_crcrst(uint8_t bool)
{
	rcc_setreg(&RCC->AHB1RSTR, 1, 12, bool);
}
void STM32446RCC_AHB1RSTR_gpiohrst(uint8_t bool)
{
	rcc_setreg(&RCC->AHB1RSTR, 1, 7, bool);
}
void STM32446RCC_AHB1RSTR_gpiogrst(uint8_t bool)
{
	rcc_setreg(&RCC->AHB1RSTR, 1, 6, bool);
}
void STM32446RCC_AHB1RSTR_gpiofrst(uint8_t bool)
{
	rcc_setreg(&RCC->AHB1RSTR, 1, 5, bool);
}
void STM32446RCC_AHB1RSTR_gpioerst(uint8_t bool)
{
	rcc_setreg(&RCC->AHB1RSTR, 1, 4, bool);
}
void STM32446RCC_AHB1RSTR_gpiodrst(uint8_t bool)
{
	rcc_setreg(&RCC->AHB1RSTR, 1, 3, bool);
}
void STM32446RCC_AHB1RSTR_gpiocrst(uint8_t bool)
{
	rcc_setreg(&RCC->AHB1RSTR, 1, 2, bool);
}
void STM32446RCC_AHB1RSTR_gpiobrst(uint8_t bool)
{
	rcc_setreg(&RCC->AHB1RSTR, 1, 1, bool);
}
void STM32446RCC_AHB1RSTR_gpioarst(uint8_t bool)
{
	rcc_setreg(&RCC->AHB1RSTR, 1, 0, bool);
}
// AHB2RSTR
void STM32446RCC_AHB2RSTR_otgfsrst(uint8_t bool)
{
	rcc_setreg(&RCC->AHB2RSTR, 1, 7, bool);
}
void STM32446RCC_AHB2RSTR_dcmirst(uint8_t bool)
{
	rcc_setreg(&RCC->AHB2RSTR, 1, 0, bool);
}
// AHB3RSTR
void STM32446RCC_AHB3RSTR_qspirst(uint8_t bool)
{
	rcc_setreg(&RCC->AHB3RSTR, 1, 1, bool);
}
void STM32446RCC_AHB3RSTR_fmcrst(uint8_t bool)
{
	rcc_setreg(&RCC->AHB3RSTR, 1, 0, bool);
}
// APB1RSTR
void STM32446RCC_APB1RSTR_dacrst(uint8_t bool)
{
	rcc_setreg(&RCC->APB1RSTR, 1, 29, bool);
}
void STM32446RCC_APB1RSTR_pwrrst(uint8_t bool)
{
	rcc_setreg(&RCC->APB1RSTR, 1, 28, bool);
}
void STM32446RCC_APB1RSTR_cecrst(uint8_t bool)
{
	rcc_setreg(&RCC->APB1RSTR, 1, 27, bool);
}
void STM32446RCC_APB1RSTR_can2rst(uint8_t bool)
{
	rcc_setreg(&RCC->APB1RSTR, 1, 26, bool);
}
void STM32446RCC_APB1RSTR_can1rst(uint8_t bool)
{
	rcc_setreg(&RCC->APB1RSTR, 1, 25, bool);
}
void STM32446RCC_APB1RSTR_fmpi2c1rst(uint8_t bool)
{
	rcc_setreg(&RCC->APB1RSTR, 1, 24, bool);
}
void STM32446RCC_APB1RSTR_i2c3rst(uint8_t bool)
{
	rcc_setreg(&RCC->APB1RSTR, 1, 23, bool);
}
void STM32446RCC_APB1RSTR_i2c2rst(uint8_t bool)
{
	rcc_setreg(&RCC->APB1RSTR, 1, 22, bool);
}
void STM32446RCC_APB1RSTR_i2c1rst(uint8_t bool)
{
	rcc_setreg(&RCC->APB1RSTR, 1, 21, bool);
}
void STM32446RCC_APB1RSTR_uart5rst(uint8_t bool)
{
	rcc_setreg(&RCC->APB1RSTR, 1, 20, bool);
}
void STM32446RCC_APB1RSTR_uart4rst(uint8_t bool)
{
	rcc_setreg(&RCC->APB1RSTR, 1, 19, bool);
}
void STM32446RCC_APB1RSTR_usart3rst(uint8_t bool)
{
	rcc_setreg(&RCC->APB1RSTR, 1, 18, bool);
}
void STM32446RCC_APB1RSTR_usart2rst(uint8_t bool)
{
	rcc_setreg(&RCC->APB1RSTR, 1, 17, bool);
}
void STM32446RCC_APB1RSTR_spdifrxrst(uint8_t bool)
{
	rcc_setreg(&RCC->APB1RSTR, 1, 16, bool);
}
void STM32446RCC_APB1RSTR_spi3rst(uint8_t bool)
{
	rcc_setreg(&RCC->APB1RSTR, 1, 15, bool);
}
void STM32446RCC_APB1RSTR_spi2rst(uint8_t bool)
{
	rcc_setreg(&RCC->APB1RSTR, 1, 14, bool);
}
void STM32446RCC_APB1RSTR_wwdgrst(uint8_t bool)
{
	rcc_setreg(&RCC->APB1RSTR, 1, 11, bool);
}
void STM32446RCC_APB1RSTR_tim14rst(uint8_t bool)
{
	rcc_setreg(&RCC->APB1RSTR, 1, 8, bool);
}
void STM32446RCC_APB1RSTR_tim13rst(uint8_t bool)
{
	rcc_setreg(&RCC->APB1RSTR, 1, 7, bool);
}
void STM32446RCC_APB1RSTR_tim12rst(uint8_t bool)
{
	rcc_setreg(&RCC->APB1RSTR, 1, 6, bool);
}
void STM32446RCC_APB1RSTR_tim7rst(uint8_t bool)
{
	rcc_setreg(&RCC->APB1RSTR, 1, 5, bool);
}
void STM32446RCC_APB1RSTR_tim6rst(uint8_t bool)
{
	rcc_setreg(&RCC->APB1RSTR, 1, 4, bool);
}
void STM32446RCC_APB1RSTR_tim5rst(uint8_t bool)
{
	rcc_setreg(&RCC->APB1RSTR, 1, 3, bool);
}
void STM32446RCC_APB1RSTR_tim4rst(uint8_t bool)
{
	rcc_setreg(&RCC->APB1RSTR, 1, 2, bool);
}
void STM32446RCC_APB1RSTR_tim3rst(uint8_t bool)
{
	rcc_setreg(&RCC->APB1RSTR, 1, 1, bool);
}
void STM32446RCC_APB1RSTR_tim2rst(uint8_t bool)
{
	rcc_setreg(&RCC->APB1RSTR, 1, 0, bool);
}
// APB2RSTR
void STM32446RCC_APB2RSTR_sai2rst(uint8_t bool)
{
	rcc_setreg(&RCC->APB2RSTR, 1, 23, bool);
}
void STM32446RCC_APB2RSTR_sai1rst(uint8_t bool)
{
	rcc_setreg(&RCC->APB2RSTR, 1, 22, bool);
}
void STM32446RCC_APB2RSTR_tim11rst(uint8_t bool)
{
	rcc_setreg(&RCC->APB2RSTR, 1, 18, bool);
}
void STM32446RCC_APB2RSTR_tim10rst(uint8_t bool)
{
	rcc_setreg(&RCC->APB2RSTR, 1, 17, bool);
}
void STM32446RCC_APB2RSTR_tim9rst(uint8_t bool)
{
	rcc_setreg(&RCC->APB2RSTR, 1, 16, bool);
}
void STM32446RCC_APB2RSTR_syscfgrst(uint8_t bool)
{
	rcc_setreg(&RCC->APB2RSTR, 1, 14, bool);
}
void STM32446RCC_APB2RSTR_spi4rst(uint8_t bool)
{
	rcc_setreg(&RCC->APB2RSTR, 1, 13, bool);
}
void STM32446RCC_APB2RSTR_spi1rst(uint8_t bool)
{
	rcc_setreg(&RCC->APB2RSTR, 1, 12, bool);
}
void STM32446RCC_APB2RSTR_sdiorst(uint8_t bool)
{
	rcc_setreg(&RCC->APB2RSTR, 1, 11, bool);
}
void STM32446RCC_APB2RSTR_adcrst(uint8_t bool)
{
	rcc_setreg(&RCC->APB2RSTR, 1, 8, bool);
}
void STM32446RCC_APB2RSTR_usart6rst(uint8_t bool)
{
	rcc_setreg(&RCC->APB2RSTR, 1, 5, bool);
}
void STM32446RCC_APB2RSTR_usart1rst(uint8_t bool)
{
	rcc_setreg(&RCC->APB2RSTR, 1, 4, bool);
}
void STM32446RCC_APB2RSTR_tim8rst(uint8_t bool)
{
	rcc_setreg(&RCC->APB2RSTR, 1, 1, bool);
}
void STM32446RCC_APB2RSTR_tim1rst(uint8_t bool)
{
	rcc_setreg(&RCC->APB2RSTR, 1, 0, bool);
}
// AHB1ENR
void STM32446RCC_AHB1ENR_otghsulpien(uint8_t bool)
{
	rcc_setreg(&RCC->AHB1ENR, 1, 30, bool);
}
void STM32446RCC_AHB1ENR_otghsen(uint8_t bool)
{
	rcc_setreg(&RCC->AHB1ENR, 1, 29, bool);
}
void STM32446RCC_AHB1ENR_dma2en(uint8_t bool)
{
	rcc_setreg(&RCC->AHB1ENR, 1, 22, bool);
}
void STM32446RCC_AHB1ENR_dma1en(uint8_t bool)
{
	rcc_setreg(&RCC->AHB1ENR, 1, 21, bool);
}
void STM32446RCC_AHB1ENR_bkpsramen(uint8_t bool)
{
	rcc_setreg(&RCC->AHB1ENR, 1, 18, bool);
}
void STM32446RCC_AHB1ENR_crcen(uint8_t bool)
{
	rcc_setreg(&RCC->AHB1ENR, 1, 12, bool);
}
void STM32446RCC_AHB1ENR_gpiohen(uint8_t bool)
{
	rcc_setreg(&RCC->AHB1ENR, 1, 7, bool);
}
void STM32446RCC_AHB1ENR_gpiogen(uint8_t bool)
{
	rcc_setreg(&RCC->AHB1ENR, 1, 6, bool);
}
void STM32446RCC_AHB1ENR_gpiofen(uint8_t bool)
{
	rcc_setreg(&RCC->AHB1ENR, 1, 5, bool);
}
void STM32446RCC_AHB1ENR_gpioeen(uint8_t bool)
{
	rcc_setreg(&RCC->AHB1ENR, 1, 4, bool);
}
void STM32446RCC_AHB1ENR_gpioden(uint8_t bool)
{
	rcc_setreg(&RCC->AHB1ENR, 1, 3, bool);
}
void STM32446RCC_AHB1ENR_gpiocen(uint8_t bool)
{
	rcc_setreg(&RCC->AHB1ENR, 1, 2, bool);
}
void STM32446RCC_AHB1ENR_gpioben(uint8_t bool)
{
	rcc_setreg(&RCC->AHB1ENR, 1, 1, bool);
}
void STM32446RCC_AHB1ENR_gpioaen(uint8_t bool)
{
	rcc_setreg(&RCC->AHB1ENR, 1, 0, bool);
}
// AHB2ENR
void STM32446RCC_AHB2ENR_otgfsen(uint8_t bool)
{
	rcc_setreg(&RCC->AHB2ENR, 1, 7, bool);
}
void STM32446RCC_AHB2ENR_dcmien(uint8_t bool)
{
	rcc_setreg(&RCC->AHB2ENR, 1, 0, bool);
}
// AHB3ENR
void STM32446RCC_AHB3ENR_qspien(uint8_t bool)
{
	rcc_setreg(&RCC->AHB3ENR, 1, 1, bool);
}
void STM32446RCC_AHB3ENR_fmcen(uint8_t bool)
{
	rcc_setreg(&RCC->AHB3ENR, 1, 0, bool);
}
// APB1ENR
void STM32446RCC_APB1ENR_dacen(uint8_t bool)
{
	rcc_setreg(&RCC->APB1ENR, 1, 29, bool);
}
void STM32446RCC_APB1ENR_pwren(uint8_t bool)
{
	rcc_setreg(&RCC->APB1ENR, 1, 28, bool);
}
void STM32446RCC_APB1ENR_cecen(uint8_t bool)
{
	rcc_setreg(&RCC->APB1ENR, 1, 27, bool);
}
void STM32446RCC_APB1ENR_can2en(uint8_t bool)
{
	rcc_setreg(&RCC->APB1ENR, 1, 26, bool);
}
void STM32446RCC_APB1ENR_can1en(uint8_t bool)
{
	rcc_setreg(&RCC->APB1ENR, 1, 25, bool);
}
void STM32446RCC_APB1ENR_fmpi2c1en(uint8_t bool)
{
	rcc_setreg(&RCC->APB1ENR, 1, 24, bool);
}
void STM32446RCC_APB1ENR_i2c3en(uint8_t bool)
{
	rcc_setreg(&RCC->APB1ENR, 1, 23, bool);
}
void STM32446RCC_APB1ENR_i2c2en(uint8_t bool)
{
	rcc_setreg(&RCC->APB1ENR, 1, 22, bool);
}
void STM32446RCC_APB1ENR_i2c1en(uint8_t bool)
{
	rcc_setreg(&RCC->APB1ENR, 1, 21, bool);
}
void STM32446RCC_APB1ENR_uart5en(uint8_t bool)
{
	rcc_setreg(&RCC->APB1ENR, 1, 20, bool);
}
void STM32446RCC_APB1ENR_uart4en(uint8_t bool)
{
	rcc_setreg(&RCC->APB1ENR, 1, 19, bool);
}
void STM32446RCC_APB1ENR_usart3en(uint8_t bool)
{
	rcc_setreg(&RCC->APB1ENR, 1, 18, bool);
}
void STM32446RCC_APB1ENR_usart2en(uint8_t bool)
{
	rcc_setreg(&RCC->APB1ENR, 1, 17, bool);
}
void STM32446RCC_APB1ENR_spdifrxen(uint8_t bool)
{
	rcc_setreg(&RCC->APB1ENR, 1, 16, bool);
}
void STM32446RCC_APB1ENR_spi3en(uint8_t bool)
{
	rcc_setreg(&RCC->APB1ENR, 1, 15, bool);
}
void STM32446RCC_APB1ENR_spi2en(uint8_t bool)
{
	rcc_setreg(&RCC->APB1ENR, 1, 14, bool);
}
void STM32446RCC_APB1ENR_wwdgen(uint8_t bool)
{
	rcc_setreg(&RCC->APB1ENR, 1, 11, bool);
}
void STM32446RCC_APB1ENR_tim14en(uint8_t bool)
{
	rcc_setreg(&RCC->APB1ENR, 1, 8, bool);
}
void STM32446RCC_APB1ENR_tim13en(uint8_t bool)
{
	rcc_setreg(&RCC->APB1ENR, 1, 7, bool);
}
void STM32446RCC_APB1ENR_tim12en(uint8_t bool)
{
	rcc_setreg(&RCC->APB1ENR, 1, 6, bool);
}
void STM32446RCC_APB1ENR_tim7en(uint8_t bool)
{
	rcc_setreg(&RCC->APB1ENR, 1, 5, bool);
}
void STM32446RCC_APB1ENR_tim6en(uint8_t bool)
{
	rcc_setreg(&RCC->APB1ENR, 1, 4, bool);
}
void STM32446RCC_APB1ENR_tim5en(uint8_t bool)
{
	rcc_setreg(&RCC->APB1ENR, 1, 3, bool);
}
void STM32446RCC_APB1ENR_tim4en(uint8_t bool)
{
	rcc_setreg(&RCC->APB1ENR, 1, 2, bool);
}
void STM32446RCC_APB1ENR_tim3en(uint8_t bool)
{
	rcc_setreg(&RCC->APB1ENR, 1, 1, bool);
}
void STM32446RCC_APB1ENR_tim2en(uint8_t bool)
{
	rcc_setreg(&RCC->APB1ENR, 1, 0, bool);
}
// APB2ENR
void STM32446RCC_APB2ENR_sai2en(uint8_t bool)
{
	rcc_setreg(&RCC->APB2ENR, 1, 23, bool);
}
void STM32446RCC_APB2ENR_sai1en(uint8_t bool)
{
	rcc_setreg(&RCC->APB2ENR, 1, 22, bool);
}
void STM32446RCC_APB2ENR_tim11en(uint8_t bool)
{
	rcc_setreg(&RCC->APB2ENR, 1, 18, bool);
}
void STM32446RCC_APB2ENR_tim10en(uint8_t bool)
{
	rcc_setreg(&RCC->APB2ENR, 1, 17, bool);
}
void STM32446RCC_APB2ENR_tim9en(uint8_t bool)
{
	rcc_setreg(&RCC->APB2ENR, 1, 16, bool);
}
void STM32446RCC_APB2ENR_syscfgen(uint8_t bool)
{
	rcc_setreg(&RCC->APB2ENR, 1, 14, bool);
}
void STM32446RCC_APB2ENR_spi4en(uint8_t bool)
{
	rcc_setreg(&RCC->APB2ENR, 1, 13, bool);
}
void STM32446RCC_APB2ENR_spi1en(uint8_t bool)
{
	rcc_setreg(&RCC->APB2ENR, 1, 12, bool);
}
void STM32446RCC_APB2ENR_sdioen(uint8_t bool)
{
	rcc_setreg(&RCC->APB2ENR, 1, 11, bool);
}
void STM32446RCC_APB2ENR_adc3en(uint8_t bool)
{
	rcc_setreg(&RCC->APB2ENR, 1, 10, bool);
}
void STM32446RCC_APB2ENR_adc2en(uint8_t bool)
{
	rcc_setreg(&RCC->APB2ENR, 1, 9, bool);
}
void STM32446RCC_APB2ENR_adc1en(uint8_t bool)
{
	rcc_setreg(&RCC->APB2ENR, 1, 8, bool);
}
void STM32446RCC_APB2ENR_usart6en(uint8_t bool)
{
	rcc_setreg(&RCC->APB2ENR, 1, 5, bool);
}
void STM32446RCC_APB2ENR_usart1en(uint8_t bool)
{
	rcc_setreg(&RCC->APB2ENR, 1, 4, bool);
}
void STM32446RCC_APB2ENR_tim8en(uint8_t bool)
{
	rcc_setreg(&RCC->APB2ENR, 1, 1, bool);
}
void STM32446RCC_APB2ENR_tim1en(uint8_t bool)
{
	rcc_setreg(&RCC->APB2ENR, 1, 0, bool);
}
//AHB1LPENR
void STM32446RCC_AHB1LPENR_otghsulpilpen(uint8_t bool)
{
	rcc_setreg(&RCC->AHB1LPENR, 1, 30, bool);
}
void STM32446RCC_AHB1LPENR_otghslpen(uint8_t bool)
{
	rcc_setreg(&RCC->AHB1LPENR, 1, 29, bool);
}
void STM32446RCC_AHB1LPENR_dma2lpen(uint8_t bool)
{
	rcc_setreg(&RCC->AHB1LPENR, 1, 22, bool);
}
void STM32446RCC_AHB1LPENR_dma1lpen(uint8_t bool)
{
	rcc_setreg(&RCC->AHB1LPENR, 1, 21, bool);
}
void STM32446RCC_AHB1LPENR_bkpsramlpen(uint8_t bool)
{
	rcc_setreg(&RCC->AHB1LPENR, 1, 18, bool);
}
void STM32446RCC_AHB1LPENR_sram2lpen(uint8_t bool)
{
	rcc_setreg(&RCC->AHB1LPENR, 1, 17, bool);
}
void STM32446RCC_AHB1LPENR_sram1lpen(uint8_t bool)
{
	rcc_setreg(&RCC->AHB1LPENR, 1, 16, bool);
}
void STM32446RCC_AHB1LPENR_flitflpen(uint8_t bool)
{
	rcc_setreg(&RCC->AHB1LPENR, 1, 15, bool);
}
void STM32446RCC_AHB1LPENR_crclpen(uint8_t bool)
{
	rcc_setreg(&RCC->AHB1LPENR, 1, 12, bool);
}
void STM32446RCC_AHB1LPENR_gpiohlpen(uint8_t bool)
{
	rcc_setreg(&RCC->AHB1LPENR, 1, 7, bool);
}
void STM32446RCC_AHB1LPENR_gpioglpen(uint8_t bool)
{
	rcc_setreg(&RCC->AHB1LPENR, 1, 6, bool);
}
void STM32446RCC_AHB1LPENR_gpioflpen(uint8_t bool)
{
	rcc_setreg(&RCC->AHB1LPENR, 1, 5, bool);
}
void STM32446RCC_AHB1LPENR_gpioelpen(uint8_t bool)
{
	rcc_setreg(&RCC->AHB1LPENR, 1, 4, bool);
}
void STM32446RCC_AHB1LPENR_gpiodlpen(uint8_t bool)
{
	rcc_setreg(&RCC->AHB1LPENR, 1, 3, bool);
}
void STM32446RCC_AHB1LPENR_gpioclpen(uint8_t bool)
{
	rcc_setreg(&RCC->AHB1LPENR, 1, 2, bool);
}
void STM32446RCC_AHB1LPENR_gpioblpen(uint8_t bool)
{
	rcc_setreg(&RCC->AHB1LPENR, 1, 1, bool);
}
void STM32446RCC_AHB1LPENR_gpioalpen(uint8_t bool)
{
	rcc_setreg(&RCC->AHB1LPENR, 1, 0, bool);
}
// AHB2LPENR
void STM32446RCC_AHB2LPENR_otgfslpen(uint8_t bool)
{
	rcc_setreg(&RCC->AHB2LPENR, 1, 7, bool);
}
void STM32446RCC_AHB2LPENR_dcmilpen(uint8_t bool)
{
	rcc_setreg(&RCC->AHB2LPENR, 1, 0, bool);
}
// AHB3LPENR
void STM32446RCC_AHB3LPENR_qspilpen(uint8_t bool)
{
	rcc_setreg(&RCC->AHB3LPENR, 1, 1, bool);
}
void STM32446RCC_AHB3LPENR_fmclpen(uint8_t bool)
{
	rcc_setreg(&RCC->AHB3LPENR, 1, 0, bool);
}
// APB1LPENR
void STM32446RCC_APB1LPENR_daclpen(uint8_t bool)
{
	rcc_setreg(&RCC->APB1LPENR, 1, 29, bool);
}
void STM32446RCC_APB1LPENR_pwrlpen(uint8_t bool)
{
	rcc_setreg(&RCC->APB1LPENR, 1, 28, bool);
}
void STM32446RCC_APB1LPENR_ceclpen(uint8_t bool)
{
	rcc_setreg(&RCC->APB1LPENR, 1, 27, bool);
}
void STM32446RCC_APB1LPENR_can2lpen(uint8_t bool)
{
	rcc_setreg(&RCC->APB1LPENR, 1, 26, bool);
}
void STM32446RCC_APB1LPENR_can1lpen(uint8_t bool)
{
	rcc_setreg(&RCC->APB1LPENR, 1, 25, bool);
}
void STM32446RCC_APB1LPENR_fmpi2c1lpen(uint8_t bool)
{
	rcc_setreg(&RCC->APB1LPENR, 1, 24, bool);
}
void STM32446RCC_APB1LPENR_i2c3lpen(uint8_t bool)
{
	rcc_setreg(&RCC->APB1LPENR, 1, 23, bool);
}
void STM32446RCC_APB1LPENR_i2c2lpen(uint8_t bool)
{
	rcc_setreg(&RCC->APB1LPENR, 1, 22, bool);
}
void STM32446RCC_APB1LPENR_i2c1lpen(uint8_t bool)
{
	rcc_setreg(&RCC->APB1LPENR, 1, 21, bool);
}
void STM32446RCC_APB1LPENR_uart5lpen(uint8_t bool)
{
	rcc_setreg(&RCC->APB1LPENR, 1, 20, bool);
}
void STM32446RCC_APB1LPENR_uart4lpen(uint8_t bool)
{
	rcc_setreg(&RCC->APB1LPENR, 1, 19, bool);
}
void STM32446RCC_APB1LPENR_usart3lpen(uint8_t bool)
{
	rcc_setreg(&RCC->APB1LPENR, 1, 18, bool);
}
void STM32446RCC_APB1LPENR_usart2lpen(uint8_t bool)
{
	rcc_setreg(&RCC->APB1LPENR, 1, 17, bool);
}
void STM32446RCC_APB1LPENR_spdifrxlpen(uint8_t bool)
{
	rcc_setreg(&RCC->APB1LPENR, 1, 16, bool);
}
void STM32446RCC_APB1LPENR_spi3lpen(uint8_t bool)
{
	rcc_setreg(&RCC->APB1LPENR, 1, 15, bool);
}
void STM32446RCC_APB1LPENR_spi2lpen(uint8_t bool)
{
	rcc_setreg(&RCC->APB1LPENR, 1, 14, bool);
}
void STM32446RCC_APB1LPENR_wwdglpen(uint8_t bool)
{
	rcc_setreg(&RCC->APB1LPENR, 1, 11, bool);
}
void STM32446RCC_APB1LPENR_tim14lpen(uint8_t bool)
{
	rcc_setreg(&RCC->APB1LPENR, 1, 8, bool);
}
void STM32446RCC_APB1LPENR_tim13lpen(uint8_t bool)
{
	rcc_setreg(&RCC->APB1LPENR, 1, 7, bool);
}
void STM32446RCC_APB1LPENR_tim12lpen(uint8_t bool)
{
	rcc_setreg(&RCC->APB1LPENR, 1, 6, bool);
}
void STM32446RCC_APB1LPENR_tim7lpen(uint8_t bool)
{
	rcc_setreg(&RCC->APB1LPENR, 1, 5, bool);
}
void STM32446RCC_APB1LPENR_tim6lpen(uint8_t bool)
{
	rcc_setreg(&RCC->APB1LPENR, 1, 4, bool);
}
void STM32446RCC_APB1LPENR_tim5lpen(uint8_t bool)
{
	rcc_setreg(&RCC->APB1LPENR, 1, 3, bool);
}
void STM32446RCC_APB1LPENR_tim4lpen(uint8_t bool)
{
	rcc_setreg(&RCC->APB1LPENR, 1, 2, bool);
}
void STM32446RCC_APB1LPENR_tim3lpen(uint8_t bool)
{
	rcc_setreg(&RCC->APB1LPENR, 1, 1, bool);
}
void STM32446RCC_APB1LPENR_tim2lpen(uint8_t bool)
{
	rcc_setreg(&RCC->APB1LPENR, 1, 0, bool);
}
// APB2LPENR
void STM32446RCC_APB2LPENR_sai2lpen(uint8_t bool)
{
	rcc_setreg(&RCC->APB2LPENR, 1, 23, bool);
}
void STM32446RCC_APB2LPENR_sai1lpen(uint8_t bool)
{
	rcc_setreg(&RCC->APB2LPENR, 1, 22, bool);
}
void STM32446RCC_APB2LPENR_tim11lpen(uint8_t bool)
{
	rcc_setreg(&RCC->APB2LPENR, 1, 18, bool);
}
void STM32446RCC_APB2LPENR_tim10lpen(uint8_t bool)
{
	rcc_setreg(&RCC->APB2LPENR, 1, 17, bool);
}
void STM32446RCC_APB2LPENR_tim9lpen(uint8_t bool)
{
	rcc_setreg(&RCC->APB2LPENR, 1, 16, bool);
}
void STM32446RCC_APB2LPENR_syscfglpen(uint8_t bool)
{
	rcc_setreg(&RCC->APB2LPENR, 1, 14, bool);
}
void STM32446RCC_APB2LPENR_spi4lpen(uint8_t bool)
{
	rcc_setreg(&RCC->APB2LPENR, 1, 13, bool);
}
void STM32446RCC_APB2LPENR_spi1lpen(uint8_t bool)
{
	rcc_setreg(&RCC->APB2LPENR, 1, 12, bool);
}
void STM32446RCC_APB2LPENR_sdiolpen(uint8_t bool)
{
	rcc_setreg(&RCC->APB2LPENR, 1, 11, bool);
}
void STM32446RCC_APB2LPENR_adc3lpen(uint8_t bool)
{
	rcc_setreg(&RCC->APB2LPENR, 1, 10, bool);
}
void STM32446RCC_APB2LPENR_adc2lpen(uint8_t bool)
{
	rcc_setreg(&RCC->APB2LPENR, 1, 9, bool);
}
void STM32446RCC_APB2LPENR_adc1lpen(uint8_t bool)
{
	rcc_setreg(&RCC->APB2LPENR, 1, 8, bool);
}
void STM32446RCC_APB2LPENR_usart6lpen(uint8_t bool)
{
	rcc_setreg(&RCC->APB2LPENR, 1, 5, bool);
}
void STM32446RCC_APB2LPENR_usart1lpen(uint8_t bool)
{
	rcc_setreg(&RCC->APB2LPENR, 1, 4, bool);
}
void STM32446RCC_APB2LPENR_tim8lpen(uint8_t bool)
{
	rcc_setreg(&RCC->APB2LPENR, 1, 1, bool);
}
void STM32446RCC_APB2LPENR_tim1lpen(uint8_t bool)
{
	rcc_setreg(&RCC->APB2LPENR, 1, 0, bool);
}
// BDCR
void STM32446RCC_BDCR_bdrst(uint8_t bool)
{
	rcc_setreg(&RCC->BDCR, 1, 16, bool);
}
void STM32446RCC_BDCR_rtcen(uint8_t bool)
{
	rcc_setreg(&RCC->BDCR, 1, 15, bool);
}
void STM32446RCC_BDCR_rtcsel(uint8_t value)
{
	rcc_setreg(&RCC->BDCR, 2, 8, value);
}
void STM32446RCC_BDCR_lsemod(uint8_t bool)
{
	rcc_setreg(&RCC->BDCR, 1, 3, bool);
}
void STM32446RCC_BDCR_lsebyp(uint8_t bool)
{
	rcc_setreg(&RCC->BDCR, 1, 2, bool);
}
uint8_t STM32446RCC_BDCR_get_lserdy(void)
{
	return rcc_readreg(RCC->BDCR, 1, 1);
}
void STM32446RCC_BDCR_lseon(uint8_t bool)
{
	rcc_setreg(&RCC->BDCR, 1, 0, bool);
}
// CSR
uint8_t STM32446RCC_CSR_get_lpwrrstf(void)
{
	return rcc_readreg(RCC->CSR, 1, 31);
}
uint8_t STM32446RCC_CSR_get_wwdgrstf(void)
{
	return rcc_readreg(RCC->CSR, 1, 30);
}
uint8_t STM32446RCC_CSR_get_iwdqrstf(void)
{
	return rcc_readreg(RCC->CSR, 1, 29);
}
uint8_t STM32446RCC_CSR_get_sftrstf(void)
{
	return rcc_readreg(RCC->CSR, 1, 28);
}
uint8_t STM32446RCC_CSR_get_porrstf(void)
{
	return rcc_readreg(RCC->CSR, 1, 27);
}
uint8_t STM32446RCC_CSR_get_pinrstf(void)
{
	return rcc_readreg(RCC->CSR, 1, 26);
}
uint8_t STM32446RCC_CSR_get_borrstf(void)
{
	return rcc_readreg(RCC->CSR, 1, 25);
}
void STM32446RCC_CSR_clear_rmvf(void)
{
	rcc_setreg(&RCC->CSR, 1, 24, 1);
}
uint8_t STM32446RCC_CSR_get_lsirdy(void)
{
	return rcc_readreg(RCC->CSR, 1, 1);
}
void STM32446RCC_CSR_lsion(uint8_t bool)
{
	rcc_setreg(&RCC->CSR, 1, 0, bool);
}
// SSCGR
void STM32446RCC_SSCGR_sscgen(uint8_t bool)
{
	rcc_setreg(&RCC->SSCGR, 1, 31, bool);
}
void STM32446RCC_SSCGR_spreadsel(uint8_t bool)
{
	rcc_setreg(&RCC->SSCGR, 1, 30, bool);
}
void STM32446RCC_SSCGR_incstep(uint8_t value)
{
	rcc_setreg(&RCC->SSCGR, 15, 13, value);
}
void STM32446RCC_SSCGR_modper(uint8_t value)
{
	rcc_setreg(&RCC->SSCGR, 13, 0, value);
}
// PLLI2SCFGR
void STM32446RCC_PLLI2SCFGR_plli2sr(uint8_t value)
{
	rcc_setreg(&RCC->PLLI2SCFGR, 3, 28, value);
}
void STM32446RCC_PLLI2SCFGR_plli2sq(uint8_t value)
{
	rcc_setreg(&RCC->PLLI2SCFGR, 4, 24, value);
}
void STM32446RCC_PLLI2SCFGR_plli2sp(uint8_t value)
{
	rcc_setreg(&RCC->PLLI2SCFGR, 2, 16, value);
}
void STM32446RCC_PLLI2SCFGR_plli2sn(uint16_t value)
{
	rcc_setreg(&RCC->PLLI2SCFGR, 9, 6, value);
}
void STM32446RCC_PLLI2SCFGR_plli2sm(uint8_t value)
{
	rcc_setreg(&RCC->PLLI2SCFGR, 6, 0, value);
}
// PLLSAICFGR
void STM32446RCC_PLLSAICFGR_pllsaiq(uint8_t value)
{
	rcc_setreg(&RCC->PLLSAICFGR, 4, 24, value);
}
void STM32446RCC_PLLSAICFGR_pllsaip(uint8_t value)
{
	rcc_setreg(&RCC->PLLSAICFGR, 2, 16, value);
}
void STM32446RCC_PLLSAICFGR_pllsain(uint16_t value)
{
	rcc_setreg(&RCC->PLLSAICFGR, 9, 6, value);
}
void STM32446RCC_PLLSAICFGR_pllsaim(uint8_t value)
{
	rcc_setreg(&RCC->PLLSAICFGR, 6, 0, value);
}
// DCKCFGR
void STM32446RCC_DCKCFGR_i2s2src(uint8_t value)
{
	rcc_setreg(&RCC->DCKCFGR, 2, 27, value);
}
void STM32446RCC_DCKCFGR_i2s1src(uint8_t value)
{
	rcc_setreg(&RCC->DCKCFGR, 2, 25, value);
}
void STM32446RCC_DCKCFGR_timpre(uint8_t bool)
{
	rcc_setreg(&RCC->DCKCFGR, 1, 24, bool);
}
void STM32446RCC_DCKCFGR_sai2src(uint8_t value)
{
	rcc_setreg(&RCC->DCKCFGR, 2, 22, value);
}
void STM32446RCC_DCKCFGR_sai1src(uint8_t value)
{
	rcc_setreg(&RCC->DCKCFGR, 2, 20, value);
}
void STM32446RCC_DCKCFGR_pllsaidivq(uint8_t value)
{
	rcc_setreg(&RCC->DCKCFGR, 5, 8, value);
}
void STM32446RCC_DCKCFGR_plli2sdivq(uint8_t value)
{
	rcc_setreg(&RCC->DCKCFGR, 5, 0, value);
}
// CKGATENR
void STM32446RCC_CKGATENR_rcc_cken(uint8_t bool)
{
	rcc_setreg(&RCC->CKGATENR, 1, 6, bool);
}
void STM32446RCC_CKGATENR_flitf_cken(uint8_t bool)
{
	rcc_setreg(&RCC->CKGATENR, 1, 5, bool);
}
void STM32446RCC_CKGATENR_sram_cken(uint8_t bool)
{
	rcc_setreg(&RCC->CKGATENR, 1, 4, bool);
}
void STM32446RCC_CKGATENR_spare_cken(uint8_t bool)
{
	rcc_setreg(&RCC->CKGATENR, 1, 3, bool);
}
void STM32446RCC_CKGATENR_cm4dbg_cken(uint8_t bool)
{
	rcc_setreg(&RCC->CKGATENR, 1, 2, bool);
}
void STM32446RCC_CKGATENR_ahb2apb2_cken(uint8_t bool)
{
	rcc_setreg(&RCC->CKGATENR, 1, 1, bool);
}
void STM32446RCC_CKGATENR_ahb2apb1_cken(uint8_t bool)
{
	rcc_setreg(&RCC->CKGATENR, 1, 0, bool);
}
// DCKCFGR2
void STM32446RCC_DCKCFGR2_spdifrxsel(uint8_t bool)
{
	rcc_setreg(&RCC->DCKCFGR2, 1, 29, bool);
}
void STM32446RCC_DCKCFGR2_sdiosel(uint8_t bool)
{
	rcc_setreg(&RCC->DCKCFGR2, 1, 28, bool);
}
void STM32446RCC_DCKCFGR2_ck48msel(uint8_t bool)
{
	rcc_setreg(&RCC->DCKCFGR2, 1, 27, bool);
}
void STM32446RCC_DCKCFGR2_cecsel(uint8_t bool)
{
	rcc_setreg(&RCC->DCKCFGR2, 1, 26, bool);
}
void STM32446RCC_DCKCFGR2_fmpi2c1sel(uint8_t value)
{
	rcc_setreg(&RCC->DCKCFGR2, 2, 22, value);
}
/*** Other ***/
void STM32446RCC_nvic(uint8_t bool)
{
	if(bool){ rcc_setbit(NVIC->ISER, 1, 5, 1); }
	else{ rcc_setbit(NVIC->ICER, 1, 5, 1); }
}
/*** Auxiliar ***/
STM32446RCC_cr stm32446_rcc_cr_inic(void)
{
	STM32446RCC_cr stm32446_rcc_cr;
	// CR
	stm32446_rcc_cr.get_pllsairdy = STM32446RCC_CR_get_pllsairdy;
	stm32446_rcc_cr.pllsaion = STM32446RCC_CR_pllsaion;
	stm32446_rcc_cr.get_plli2srdy = STM32446RCC_CR_get_plli2srdy;
	stm32446_rcc_cr.plli2son = STM32446RCC_CR_plli2son;
	stm32446_rcc_cr.get_pllrdy = STM32446RCC_CR_get_pllrdy;
	stm32446_rcc_cr.pllon = STM32446RCC_CR_pllon;
	stm32446_rcc_cr.csson = STM32446RCC_CR_csson;
	stm32446_rcc_cr.hsebyp = STM32446RCC_CR_hsebyp;
	stm32446_rcc_cr.get_hserdy = STM32446RCC_CR_get_hserdy;
	stm32446_rcc_cr.hseon = STM32446RCC_CR_hseon;
	stm32446_rcc_cr.get_hsical = STM32446RCC_CR_get_hsical;
	stm32446_rcc_cr.hsitrim = STM32446RCC_CR_hsitrim;
	stm32446_rcc_cr.get_hsirdy = STM32446RCC_CR_get_hsirdy;
	stm32446_rcc_cr.hsion = STM32446RCC_CR_hsion;
	return stm32446_rcc_cr;
}
STM32446RCC_pllcfgr stm32446_rcc_pllcfgr_inic(void)
{
	STM32446RCC_pllcfgr stm32446_rcc_pllcfgr;
	// PLLCFGR
	stm32446_rcc_pllcfgr.pllr = STM32446RCC_PLLCFGR_pllr;
	stm32446_rcc_pllcfgr.pllq = STM32446RCC_PLLCFGR_pllq;
	stm32446_rcc_pllcfgr.pllsrc = STM32446RCC_PLLCFGR_pllsrc;
	stm32446_rcc_pllcfgr.pllp = STM32446RCC_PLLCFGR_pllp;
	stm32446_rcc_pllcfgr.plln = STM32446RCC_PLLCFGR_plln;
	stm32446_rcc_pllcfgr.pllm = STM32446RCC_PLLCFGR_pllm;
	return stm32446_rcc_pllcfgr;
}
STM32446RCC_cfgr stm32446_rcc_cfgr_inic(void)
{
	STM32446RCC_cfgr stm32446_rcc_cfgr;
	// CFGR
	stm32446_rcc_cfgr.mco2 = STM32446RCC_CFGR_mco2;
	stm32446_rcc_cfgr.mco2pre = STM32446RCC_CFGR_mco2pre;
	stm32446_rcc_cfgr.mco1pre = STM32446RCC_CFGR_mco1pre;
	stm32446_rcc_cfgr.mco1 = STM32446RCC_CFGR_mco1;
	stm32446_rcc_cfgr.rtcpre = STM32446RCC_CFGR_rtcpre;
	stm32446_rcc_cfgr.ppre2 = STM32446RCC_CFGR_ppre2;
	stm32446_rcc_cfgr.ppre1 = STM32446RCC_CFGR_ppre1;
	stm32446_rcc_cfgr.hpre = STM32446RCC_CFGR_hpre;
	stm32446_rcc_cfgr.get_sws = STM32446RCC_CFGR_get_sws;
	stm32446_rcc_cfgr.sw = STM32446RCC_CFGR_sw;
	return stm32446_rcc_cfgr;
}
STM32446RCC_cir stm32446_rcc_cir_inic(void)
{
	STM32446RCC_cir stm32446_rcc_cir;
	// CIR
	stm32446_rcc_cir.clear_cssc = STM32446RCC_CIR_clear_cssc;
	stm32446_rcc_cir.clear_pllsairdyc = STM32446RCC_CIR_clear_pllsairdyc;
	stm32446_rcc_cir.clear_plli2srdyc = STM32446RCC_CIR_clear_plli2srdyc;
	stm32446_rcc_cir.clear_pllrdyc = STM32446RCC_CIR_clear_pllrdyc;
	stm32446_rcc_cir.clear_hserdyc = STM32446RCC_CIR_clear_hserdyc;
	stm32446_rcc_cir.clear_hsirdyc = STM32446RCC_CIR_clear_hsirdyc;
	stm32446_rcc_cir.clear_lserdyc = STM32446RCC_CIR_clear_lserdyc;
	stm32446_rcc_cir.clear_lsirdyc = STM32446RCC_CIR_clear_lsirdyc;
	stm32446_rcc_cir.pllsairdyie = STM32446RCC_CIR_pllsairdyie;
	stm32446_rcc_cir.plli2srdyie = STM32446RCC_CIR_plli2srdyie;
	stm32446_rcc_cir.pllrdyie = STM32446RCC_CIR_pllrdyie;
	stm32446_rcc_cir.hserdyie = STM32446RCC_CIR_hserdyie;
	stm32446_rcc_cir.hsirdyie = STM32446RCC_CIR_hsirdyie;
	stm32446_rcc_cir.lserdyie = STM32446RCC_CIR_lserdyie;
	stm32446_rcc_cir.lsirdyie = STM32446RCC_CIR_lsirdyie;
	stm32446_rcc_cir.get_cssf = STM32446RCC_CIR_get_cssf;
	stm32446_rcc_cir.get_pllsairdyf = STM32446RCC_CIR_get_pllsairdyf;
	stm32446_rcc_cir.get_plli2srdyf = STM32446RCC_CIR_get_plli2srdyf;
	stm32446_rcc_cir.get_pllrdyf = STM32446RCC_CIR_get_pllrdyf;
	stm32446_rcc_cir.get_hserdyf = STM32446RCC_CIR_get_hserdyf;
	stm32446_rcc_cir.get_hsirdyf = STM32446RCC_CIR_get_hsirdyf;
	stm32446_rcc_cir.get_lserdyf = STM32446RCC_CIR_get_lserdyf;
	stm32446_rcc_cir.get_lsirdyf = STM32446RCC_CIR_get_lsirdyf;
	return stm32446_rcc_cir;
}
STM32446RCC_ahb1rstr stm32446_rcc_ahb1rstr_inic(void)
{
	STM32446RCC_ahb1rstr stm32446_rcc_ahb1rstr;
	// AHB1RSTR
	stm32446_rcc_ahb1rstr.otghsrst = STM32446RCC_AHB1RSTR_otghsrst;
	stm32446_rcc_ahb1rstr.dma2rst = STM32446RCC_AHB1RSTR_dma2rst;
	stm32446_rcc_ahb1rstr.dma1rst = STM32446RCC_AHB1RSTR_dma1rst;
	stm32446_rcc_ahb1rstr.crcrst = STM32446RCC_AHB1RSTR_crcrst;
	stm32446_rcc_ahb1rstr.gpiohrst = STM32446RCC_AHB1RSTR_gpiohrst;
	stm32446_rcc_ahb1rstr.gpiogrst = STM32446RCC_AHB1RSTR_gpiogrst;
	stm32446_rcc_ahb1rstr.gpiofrst = STM32446RCC_AHB1RSTR_gpiofrst;
	stm32446_rcc_ahb1rstr.gpioerst = STM32446RCC_AHB1RSTR_gpioerst;
	stm32446_rcc_ahb1rstr.gpiodrst = STM32446RCC_AHB1RSTR_gpiodrst;
	stm32446_rcc_ahb1rstr.gpiocrst = STM32446RCC_AHB1RSTR_gpiocrst;
	stm32446_rcc_ahb1rstr.gpiobrst = STM32446RCC_AHB1RSTR_gpiobrst;
	stm32446_rcc_ahb1rstr.gpioarst = STM32446RCC_AHB1RSTR_gpioarst;
	return stm32446_rcc_ahb1rstr;
}
STM32446RCC_ahb2rstr stm32446_rcc_ahb2rstr_inic(void)
{
	STM32446RCC_ahb2rstr stm32446_rcc_ahb2rstr;
	// AHB2RSTR
	stm32446_rcc_ahb2rstr.otgfsrst = STM32446RCC_AHB2RSTR_otgfsrst;
	stm32446_rcc_ahb2rstr.dcmirst = STM32446RCC_AHB2RSTR_dcmirst;
	return stm32446_rcc_ahb2rstr;
}
STM32446RCC_ahb3rstr stm32446_rcc_ahb3rstr_inic(void)
{
	STM32446RCC_ahb3rstr stm32446_rcc_ahb3rstr;
	// AHB3RSTR
	stm32446_rcc_ahb3rstr.qspirst = STM32446RCC_AHB3RSTR_qspirst;
	stm32446_rcc_ahb3rstr.fmcrst = STM32446RCC_AHB3RSTR_fmcrst;
	return stm32446_rcc_ahb3rstr;
}
STM32446RCC_apb1rstr stm32446_rcc_apb1rstr_inic(void)
{
	STM32446RCC_apb1rstr stm32446_rcc_apb1rstr;
	// APB1RSTR
	stm32446_rcc_apb1rstr.dacrst = STM32446RCC_APB1RSTR_dacrst;
	stm32446_rcc_apb1rstr.pwrrst = STM32446RCC_APB1RSTR_pwrrst;
	stm32446_rcc_apb1rstr.cecrst = STM32446RCC_APB1RSTR_cecrst;
	stm32446_rcc_apb1rstr.can2rst = STM32446RCC_APB1RSTR_can2rst;
	stm32446_rcc_apb1rstr.can1rst = STM32446RCC_APB1RSTR_can1rst;
	stm32446_rcc_apb1rstr.fmpi2c1rst = STM32446RCC_APB1RSTR_fmpi2c1rst;
	stm32446_rcc_apb1rstr.i2c3rst = STM32446RCC_APB1RSTR_i2c3rst;
	stm32446_rcc_apb1rstr.i2c2rst = STM32446RCC_APB1RSTR_i2c2rst;
	stm32446_rcc_apb1rstr.i2c1rst = STM32446RCC_APB1RSTR_i2c1rst;
	stm32446_rcc_apb1rstr.uart5rst = STM32446RCC_APB1RSTR_uart5rst;
	stm32446_rcc_apb1rstr.uart4rst = STM32446RCC_APB1RSTR_uart4rst;
	stm32446_rcc_apb1rstr.usart3rst = STM32446RCC_APB1RSTR_usart3rst;
	stm32446_rcc_apb1rstr.usart2rst = STM32446RCC_APB1RSTR_usart2rst;
	stm32446_rcc_apb1rstr.spdifrxrst = STM32446RCC_APB1RSTR_spdifrxrst;
	stm32446_rcc_apb1rstr.spi3rst = STM32446RCC_APB1RSTR_spi3rst;
	stm32446_rcc_apb1rstr.spi2rst = STM32446RCC_APB1RSTR_spi2rst;
	stm32446_rcc_apb1rstr.wwdgrst = STM32446RCC_APB1RSTR_wwdgrst;
	stm32446_rcc_apb1rstr.tim14rst = STM32446RCC_APB1RSTR_tim14rst;
	stm32446_rcc_apb1rstr.tim13rst = STM32446RCC_APB1RSTR_tim13rst;
	stm32446_rcc_apb1rstr.tim12rst = STM32446RCC_APB1RSTR_tim12rst;
	stm32446_rcc_apb1rstr.tim7rst = STM32446RCC_APB1RSTR_tim7rst;
	stm32446_rcc_apb1rstr.tim6rst = STM32446RCC_APB1RSTR_tim6rst;
	stm32446_rcc_apb1rstr.tim5rst = STM32446RCC_APB1RSTR_tim5rst;
	stm32446_rcc_apb1rstr.tim4rst = STM32446RCC_APB1RSTR_tim4rst;
	stm32446_rcc_apb1rstr.tim3rst = STM32446RCC_APB1RSTR_tim3rst;
	stm32446_rcc_apb1rstr.tim2rst = STM32446RCC_APB1RSTR_tim2rst;
	return stm32446_rcc_apb1rstr;
}
STM32446RCC_apb2rstr stm32446_rcc_apb2rstr_inic(void)
{
	STM32446RCC_apb2rstr stm32446_rcc_apb2rstr;
	// APB2RSTR
	stm32446_rcc_apb2rstr.sai2rst = STM32446RCC_APB2RSTR_sai2rst;
	stm32446_rcc_apb2rstr.sai1rst = STM32446RCC_APB2RSTR_sai1rst;
	stm32446_rcc_apb2rstr.tim11rst = STM32446RCC_APB2RSTR_tim11rst;
	stm32446_rcc_apb2rstr.tim10rst = STM32446RCC_APB2RSTR_tim10rst;
	stm32446_rcc_apb2rstr.tim9rst = STM32446RCC_APB2RSTR_tim9rst;
	stm32446_rcc_apb2rstr.syscfgrst = STM32446RCC_APB2RSTR_syscfgrst;
	stm32446_rcc_apb2rstr.spi4rst = STM32446RCC_APB2RSTR_spi4rst;
	stm32446_rcc_apb2rstr.spi1rst = STM32446RCC_APB2RSTR_spi1rst;
	stm32446_rcc_apb2rstr.sdiorst = STM32446RCC_APB2RSTR_sdiorst;
	stm32446_rcc_apb2rstr.adcrst = STM32446RCC_APB2RSTR_adcrst;
	stm32446_rcc_apb2rstr.usart6rst = STM32446RCC_APB2RSTR_usart6rst;
	stm32446_rcc_apb2rstr.usart1rst = STM32446RCC_APB2RSTR_usart1rst;
	stm32446_rcc_apb2rstr.tim8rst = STM32446RCC_APB2RSTR_tim8rst;
	stm32446_rcc_apb2rstr.tim1rst = STM32446RCC_APB2RSTR_tim1rst;
	return stm32446_rcc_apb2rstr;
}
STM32446RCC_ahb1enr stm32446_rcc_ahb1enr_inic(void)
{
	STM32446RCC_ahb1enr stm32446_rcc_ahb1enr;
	// AHB1ENR
	stm32446_rcc_ahb1enr.otghsulpien = STM32446RCC_AHB1ENR_otghsulpien;
	stm32446_rcc_ahb1enr.otghsen = STM32446RCC_AHB1ENR_otghsen;
	stm32446_rcc_ahb1enr.dma2en = STM32446RCC_AHB1ENR_dma2en;
	stm32446_rcc_ahb1enr.dma1en = STM32446RCC_AHB1ENR_dma1en;
	stm32446_rcc_ahb1enr.bkpsramen = STM32446RCC_AHB1ENR_bkpsramen;
	stm32446_rcc_ahb1enr.crcen = STM32446RCC_AHB1ENR_crcen;
	stm32446_rcc_ahb1enr.gpiohen = STM32446RCC_AHB1ENR_gpiohen;
	stm32446_rcc_ahb1enr.gpiogen = STM32446RCC_AHB1ENR_gpiogen;
	stm32446_rcc_ahb1enr.gpiofen = STM32446RCC_AHB1ENR_gpiofen;
	stm32446_rcc_ahb1enr.gpioeen = STM32446RCC_AHB1ENR_gpioeen;
	stm32446_rcc_ahb1enr.gpioden = STM32446RCC_AHB1ENR_gpioden;
	stm32446_rcc_ahb1enr.gpiocen = STM32446RCC_AHB1ENR_gpiocen;
	stm32446_rcc_ahb1enr.gpioben = STM32446RCC_AHB1ENR_gpioben;
	stm32446_rcc_ahb1enr.gpioaen = STM32446RCC_AHB1ENR_gpioaen;
	return stm32446_rcc_ahb1enr;
}
STM32446RCC_ahb2enr stm32446_rcc_ahb2enr_inic(void)
{
	STM32446RCC_ahb2enr stm32446_rcc_ahb2enr;
	// AHB2ENR
	stm32446_rcc_ahb2enr.otgfsen = STM32446RCC_AHB2ENR_otgfsen;
	stm32446_rcc_ahb2enr.dcmien = STM32446RCC_AHB2ENR_dcmien;

	return stm32446_rcc_ahb2enr;
}
STM32446RCC_ahb3enr stm32446_rcc_ahb3enr_inic(void)
{
	STM32446RCC_ahb3enr stm32446_rcc_ahb3enr;
	// AHB3ENR
	stm32446_rcc_ahb3enr.qspien = STM32446RCC_AHB3ENR_qspien;
	stm32446_rcc_ahb3enr.fmcen = STM32446RCC_AHB3ENR_fmcen;
	return stm32446_rcc_ahb3enr;
}
STM32446RCC_apb1enr stm32446_rcc_apb1enr_inic(void)
{
	STM32446RCC_apb1enr stm32446_rcc_apb1enr;
	// APB1ENR
	stm32446_rcc_apb1enr.dacen = STM32446RCC_APB1ENR_dacen;
	stm32446_rcc_apb1enr.pwren = STM32446RCC_APB1ENR_pwren;
	stm32446_rcc_apb1enr.cecen = STM32446RCC_APB1ENR_cecen;
	stm32446_rcc_apb1enr.can2en = STM32446RCC_APB1ENR_can2en;
	stm32446_rcc_apb1enr.can1en = STM32446RCC_APB1ENR_can1en;
	stm32446_rcc_apb1enr.fmpi2c1en = STM32446RCC_APB1ENR_fmpi2c1en;
	stm32446_rcc_apb1enr.i2c3en = STM32446RCC_APB1ENR_i2c3en;
	stm32446_rcc_apb1enr.i2c2en = STM32446RCC_APB1ENR_i2c2en;
	stm32446_rcc_apb1enr.i2c1en = STM32446RCC_APB1ENR_i2c1en;
	stm32446_rcc_apb1enr.uart5en = STM32446RCC_APB1ENR_uart5en;
	stm32446_rcc_apb1enr.uart4en = STM32446RCC_APB1ENR_uart4en;
	stm32446_rcc_apb1enr.usart3en = STM32446RCC_APB1ENR_usart3en;
	stm32446_rcc_apb1enr.usart2en = STM32446RCC_APB1ENR_usart2en;
	stm32446_rcc_apb1enr.spdifrxen = STM32446RCC_APB1ENR_spdifrxen;
	stm32446_rcc_apb1enr.spi3en = STM32446RCC_APB1ENR_spi3en;
	stm32446_rcc_apb1enr.spi2en = STM32446RCC_APB1ENR_spi2en;
	stm32446_rcc_apb1enr.wwdgen = STM32446RCC_APB1ENR_wwdgen;
	stm32446_rcc_apb1enr.tim14en = STM32446RCC_APB1ENR_tim14en;
	stm32446_rcc_apb1enr.tim13en = STM32446RCC_APB1ENR_tim13en;
	stm32446_rcc_apb1enr.tim12en = STM32446RCC_APB1ENR_tim12en;
	stm32446_rcc_apb1enr.tim7en = STM32446RCC_APB1ENR_tim7en;
	stm32446_rcc_apb1enr.tim6en = STM32446RCC_APB1ENR_tim6en;
	stm32446_rcc_apb1enr.tim5en = STM32446RCC_APB1ENR_tim5en;
	stm32446_rcc_apb1enr.tim4en = STM32446RCC_APB1ENR_tim4en;
	stm32446_rcc_apb1enr.tim3en = STM32446RCC_APB1ENR_tim3en;
	stm32446_rcc_apb1enr.tim2en = STM32446RCC_APB1ENR_tim2en;
	return stm32446_rcc_apb1enr;
}
STM32446RCC_apb2enr stm32446_rcc_apb2enr_inic(void)
{
	STM32446RCC_apb2enr stm32446_rcc_apb2enr;
	// APB2ENR
	stm32446_rcc_apb2enr.sai2en = STM32446RCC_APB2ENR_sai2en;
	stm32446_rcc_apb2enr.sai1en = STM32446RCC_APB2ENR_sai1en;
	stm32446_rcc_apb2enr.tim11en = STM32446RCC_APB2ENR_tim11en;
	stm32446_rcc_apb2enr.tim10en = STM32446RCC_APB2ENR_tim10en;
	stm32446_rcc_apb2enr.tim9en = STM32446RCC_APB2ENR_tim9en;
	stm32446_rcc_apb2enr.syscfgen = STM32446RCC_APB2ENR_syscfgen;
	stm32446_rcc_apb2enr.spi4en = STM32446RCC_APB2ENR_spi4en;
	stm32446_rcc_apb2enr.spi1en = STM32446RCC_APB2ENR_spi1en;
	stm32446_rcc_apb2enr.sdioen = STM32446RCC_APB2ENR_sdioen;
	stm32446_rcc_apb2enr.adc3en = STM32446RCC_APB2ENR_adc3en;
	stm32446_rcc_apb2enr.adc2en = STM32446RCC_APB2ENR_adc2en;
	stm32446_rcc_apb2enr.adc1en = STM32446RCC_APB2ENR_adc1en;
	stm32446_rcc_apb2enr.usart6en = STM32446RCC_APB2ENR_usart6en;
	stm32446_rcc_apb2enr.usart1en = STM32446RCC_APB2ENR_usart1en;
	stm32446_rcc_apb2enr.tim8en = STM32446RCC_APB2ENR_tim8en;
	stm32446_rcc_apb2enr.tim1en = STM32446RCC_APB2ENR_tim1en;
	return stm32446_rcc_apb2enr;
}
STM32446RCC_ahb1lpenr stm32446_rcc_ahb1lpenr_inic(void)
{
	STM32446RCC_ahb1lpenr stm32446_rcc_ahb1lpenr;
	//AHB1LPENR
	stm32446_rcc_ahb1lpenr.otghsulpilpen = STM32446RCC_AHB1LPENR_otghsulpilpen;
	stm32446_rcc_ahb1lpenr.otghslpen = STM32446RCC_AHB1LPENR_otghslpen;
	stm32446_rcc_ahb1lpenr.dma2lpen = STM32446RCC_AHB1LPENR_dma2lpen;
	stm32446_rcc_ahb1lpenr.dma1lpen = STM32446RCC_AHB1LPENR_dma1lpen;
	stm32446_rcc_ahb1lpenr.bkpsramlpen = STM32446RCC_AHB1LPENR_bkpsramlpen;
	stm32446_rcc_ahb1lpenr.sram2lpen = STM32446RCC_AHB1LPENR_sram2lpen;
	stm32446_rcc_ahb1lpenr.sram1lpen = STM32446RCC_AHB1LPENR_sram1lpen;
	stm32446_rcc_ahb1lpenr.flitflpen = STM32446RCC_AHB1LPENR_flitflpen;
	stm32446_rcc_ahb1lpenr.crclpen = STM32446RCC_AHB1LPENR_crclpen;
	stm32446_rcc_ahb1lpenr.gpiohlpen = STM32446RCC_AHB1LPENR_gpiohlpen;
	stm32446_rcc_ahb1lpenr.gpioglpen = STM32446RCC_AHB1LPENR_gpioglpen;
	stm32446_rcc_ahb1lpenr.gpioflpen = STM32446RCC_AHB1LPENR_gpioflpen;
	stm32446_rcc_ahb1lpenr.gpioelpen = STM32446RCC_AHB1LPENR_gpioelpen;
	stm32446_rcc_ahb1lpenr.gpiodlpen = STM32446RCC_AHB1LPENR_gpiodlpen;
	stm32446_rcc_ahb1lpenr.gpioclpen = STM32446RCC_AHB1LPENR_gpioclpen;
	stm32446_rcc_ahb1lpenr.gpioblpen = STM32446RCC_AHB1LPENR_gpioblpen;
	stm32446_rcc_ahb1lpenr.gpioalpen = STM32446RCC_AHB1LPENR_gpioalpen;

	return stm32446_rcc_ahb1lpenr;
}
STM32446RCC_ahb2lpenr stm32446_rcc_ahb2lpenr_inic(void)
{
	STM32446RCC_ahb2lpenr stm32446_rcc_ahb2lpenr;
	// AHB2LPENR
	stm32446_rcc_ahb2lpenr.otgfslpen = STM32446RCC_AHB2LPENR_otgfslpen;
	stm32446_rcc_ahb2lpenr.dcmilpen = STM32446RCC_AHB2LPENR_dcmilpen;
	return stm32446_rcc_ahb2lpenr;
}
STM32446RCC_ahb3lpenr stm32446_rcc_ahb3lpenr_inic(void)
{
	STM32446RCC_ahb3lpenr stm32446_rcc_ahb3lpenr;
	// AHB3LPENR
	stm32446_rcc_ahb3lpenr.qspilpen = STM32446RCC_AHB3LPENR_qspilpen;
	stm32446_rcc_ahb3lpenr.fmclpen = STM32446RCC_AHB3LPENR_fmclpen;
	return stm32446_rcc_ahb3lpenr;
}
STM32446RCC_apb1lpenr stm32446_rcc_apb1lpenr_inic(void)
{
	STM32446RCC_apb1lpenr stm32446_rcc_apb1lpenr;
	// APB1LPENR
	stm32446_rcc_apb1lpenr.daclpen = STM32446RCC_APB1LPENR_daclpen;
	stm32446_rcc_apb1lpenr.pwrlpen = STM32446RCC_APB1LPENR_pwrlpen;
	stm32446_rcc_apb1lpenr.ceclpen = STM32446RCC_APB1LPENR_ceclpen;
	stm32446_rcc_apb1lpenr.can2lpen = STM32446RCC_APB1LPENR_can2lpen;
	stm32446_rcc_apb1lpenr.can1lpen = STM32446RCC_APB1LPENR_can1lpen;
	stm32446_rcc_apb1lpenr.fmpi2c1lpen = STM32446RCC_APB1LPENR_fmpi2c1lpen;
	stm32446_rcc_apb1lpenr.i2c3lpen = STM32446RCC_APB1LPENR_i2c3lpen;
	stm32446_rcc_apb1lpenr.i2c2lpen = STM32446RCC_APB1LPENR_i2c2lpen;
	stm32446_rcc_apb1lpenr.i2c1lpen = STM32446RCC_APB1LPENR_i2c1lpen;
	stm32446_rcc_apb1lpenr.uart5lpen = STM32446RCC_APB1LPENR_uart5lpen;
	stm32446_rcc_apb1lpenr.uart4lpen = STM32446RCC_APB1LPENR_uart4lpen;
	stm32446_rcc_apb1lpenr.usart3lpen = STM32446RCC_APB1LPENR_usart3lpen;
	stm32446_rcc_apb1lpenr.usart2lpen = STM32446RCC_APB1LPENR_usart2lpen;
	stm32446_rcc_apb1lpenr.spdifrxlpen = STM32446RCC_APB1LPENR_spdifrxlpen;
	stm32446_rcc_apb1lpenr.spi3lpen = STM32446RCC_APB1LPENR_spi3lpen;
	stm32446_rcc_apb1lpenr.spi2lpen = STM32446RCC_APB1LPENR_spi2lpen;
	stm32446_rcc_apb1lpenr.wwdglpen = STM32446RCC_APB1LPENR_wwdglpen;
	stm32446_rcc_apb1lpenr.tim14lpen = STM32446RCC_APB1LPENR_tim14lpen;
	stm32446_rcc_apb1lpenr.tim13lpen = STM32446RCC_APB1LPENR_tim13lpen;
	stm32446_rcc_apb1lpenr.tim12lpen = STM32446RCC_APB1LPENR_tim12lpen;
	stm32446_rcc_apb1lpenr.tim7lpen = STM32446RCC_APB1LPENR_tim7lpen;
	stm32446_rcc_apb1lpenr.tim6lpen = STM32446RCC_APB1LPENR_tim6lpen;
	stm32446_rcc_apb1lpenr.tim5lpen = STM32446RCC_APB1LPENR_tim5lpen;
	stm32446_rcc_apb1lpenr.tim4lpen = STM32446RCC_APB1LPENR_tim4lpen;
	stm32446_rcc_apb1lpenr.tim3lpen = STM32446RCC_APB1LPENR_tim3lpen;
	stm32446_rcc_apb1lpenr.tim2lpen = STM32446RCC_APB1LPENR_tim2lpen;
	return stm32446_rcc_apb1lpenr;
}
STM32446RCC_apb2lpenr stm32446_rcc_apb2lpenr_inic(void)
{
	STM32446RCC_apb2lpenr stm32446_rcc_apb2lpenr;
	// APB2LPENR
	stm32446_rcc_apb2lpenr.sai2lpen = STM32446RCC_APB2LPENR_sai2lpen;
	stm32446_rcc_apb2lpenr.sai1lpen = STM32446RCC_APB2LPENR_sai1lpen;
	stm32446_rcc_apb2lpenr.tim11lpen = STM32446RCC_APB2LPENR_tim11lpen;
	stm32446_rcc_apb2lpenr.tim10lpen = STM32446RCC_APB2LPENR_tim10lpen;
	stm32446_rcc_apb2lpenr.tim9lpen = STM32446RCC_APB2LPENR_tim9lpen;
	stm32446_rcc_apb2lpenr.syscfglpen = STM32446RCC_APB2LPENR_syscfglpen;
	stm32446_rcc_apb2lpenr.spi4lpen = STM32446RCC_APB2LPENR_spi4lpen;
	stm32446_rcc_apb2lpenr.sai1lpen = STM32446RCC_APB2LPENR_spi1lpen;
	stm32446_rcc_apb2lpenr.sdiolpen = STM32446RCC_APB2LPENR_sdiolpen;
	stm32446_rcc_apb2lpenr.adc3lpen = STM32446RCC_APB2LPENR_adc3lpen;
	stm32446_rcc_apb2lpenr.adc2lpen = STM32446RCC_APB2LPENR_adc2lpen;
	stm32446_rcc_apb2lpenr.adc1lpen = STM32446RCC_APB2LPENR_adc1lpen;
	stm32446_rcc_apb2lpenr.usart6lpen = STM32446RCC_APB2LPENR_usart6lpen;
	stm32446_rcc_apb2lpenr.usart1lpen = STM32446RCC_APB2LPENR_usart1lpen;
	stm32446_rcc_apb2lpenr.tim8lpen = STM32446RCC_APB2LPENR_tim8lpen;
	stm32446_rcc_apb2lpenr.tim1lpen = STM32446RCC_APB2LPENR_tim1lpen;
	return stm32446_rcc_apb2lpenr;
}
STM32446RCC_bdcr stm32446_rcc_bdcr_inic(void)
{
	STM32446RCC_bdcr stm32446_rcc_bdcr;
	// BDCR
	stm32446_rcc_bdcr.bdrst = STM32446RCC_BDCR_bdrst;
	stm32446_rcc_bdcr.rtcen = STM32446RCC_BDCR_rtcen;
	stm32446_rcc_bdcr.rtcsel = STM32446RCC_BDCR_rtcsel;
	stm32446_rcc_bdcr.lsemod = STM32446RCC_BDCR_lsemod;
	stm32446_rcc_bdcr.lsebyp = STM32446RCC_BDCR_lsebyp;
	stm32446_rcc_bdcr.get_lserdy = STM32446RCC_BDCR_get_lserdy;
	stm32446_rcc_bdcr.lseon = STM32446RCC_BDCR_lseon;
	return stm32446_rcc_bdcr;
}
STM32446RCC_csr stm32446_rcc_csr_inic(void)
{
	STM32446RCC_csr stm32446_rcc_csr;
	// CSR
	stm32446_rcc_csr.get_lpwrrstf = STM32446RCC_CSR_get_lpwrrstf;
	stm32446_rcc_csr.get_wwdgrstf = STM32446RCC_CSR_get_wwdgrstf;
	stm32446_rcc_csr.get_iwdqrstf = STM32446RCC_CSR_get_iwdqrstf;
	stm32446_rcc_csr.get_sftrstf = STM32446RCC_CSR_get_sftrstf;
	stm32446_rcc_csr.get_porrstf = STM32446RCC_CSR_get_porrstf;
	stm32446_rcc_csr.get_pinrstf = STM32446RCC_CSR_get_pinrstf;
	stm32446_rcc_csr.get_borrstf = STM32446RCC_CSR_get_borrstf;
	stm32446_rcc_csr.clear_rmvf = STM32446RCC_CSR_clear_rmvf;
	stm32446_rcc_csr.get_lsirdy = STM32446RCC_CSR_get_lsirdy;
	stm32446_rcc_csr.lsion = STM32446RCC_CSR_lsion;
	return stm32446_rcc_csr;
}
STM32446RCC_sscgr stm32446_rcc_sscgr_inic(void)
{
	STM32446RCC_sscgr stm32446_rcc_sscgr;
	// SSCGR
	stm32446_rcc_sscgr.sscgen = STM32446RCC_SSCGR_sscgen;
	stm32446_rcc_sscgr.spreadsel = STM32446RCC_SSCGR_spreadsel;
	stm32446_rcc_sscgr.incstep = STM32446RCC_SSCGR_incstep;
	stm32446_rcc_sscgr.modper = STM32446RCC_SSCGR_modper;
	return stm32446_rcc_sscgr;
}
STM32446RCC_plli2scfgr stm32446_rcc_plli2scfgr_inic(void)
{
	STM32446RCC_plli2scfgr stm32446_rcc_plli2scfgr;
	// PLLI2SCFGR
	stm32446_rcc_plli2scfgr.plli2sr = STM32446RCC_PLLI2SCFGR_plli2sr;
	stm32446_rcc_plli2scfgr.plli2sq = STM32446RCC_PLLI2SCFGR_plli2sq;
	stm32446_rcc_plli2scfgr.plli2sp = STM32446RCC_PLLI2SCFGR_plli2sp;
	stm32446_rcc_plli2scfgr.plli2sn = STM32446RCC_PLLI2SCFGR_plli2sn;
	stm32446_rcc_plli2scfgr.plli2sm = STM32446RCC_PLLI2SCFGR_plli2sm;
	return stm32446_rcc_plli2scfgr;
}
STM32446RCC_pllsaicfgr stm32446_rcc_pllsaicfgr_inic(void)
{
	STM32446RCC_pllsaicfgr stm32446_rcc_pllsaicfgr;
	// PLLSAICFGR
	stm32446_rcc_pllsaicfgr.pllsaiq = STM32446RCC_PLLSAICFGR_pllsaiq;
	stm32446_rcc_pllsaicfgr.pllsaip = STM32446RCC_PLLSAICFGR_pllsaip;
	stm32446_rcc_pllsaicfgr.pllsain = STM32446RCC_PLLSAICFGR_pllsain;
	stm32446_rcc_pllsaicfgr.pllsaim = STM32446RCC_PLLSAICFGR_pllsaim;
	return stm32446_rcc_pllsaicfgr;
}
STM32446RCC_dckcfgr stm32446_rcc_dckcfgr_inic(void)
{
	STM32446RCC_dckcfgr stm32446_rcc_dckcfgr;
	// DCKCFGR
	stm32446_rcc_dckcfgr.i2s2src = STM32446RCC_DCKCFGR_i2s2src;
	stm32446_rcc_dckcfgr.i2s1src = STM32446RCC_DCKCFGR_i2s1src;
	stm32446_rcc_dckcfgr.timpre = STM32446RCC_DCKCFGR_timpre;
	stm32446_rcc_dckcfgr.sai2src = STM32446RCC_DCKCFGR_sai2src;
	stm32446_rcc_dckcfgr.sai1src = STM32446RCC_DCKCFGR_sai1src;
	stm32446_rcc_dckcfgr.pllsaidivq = STM32446RCC_DCKCFGR_pllsaidivq;
	stm32446_rcc_dckcfgr.plli2sdivq = STM32446RCC_DCKCFGR_plli2sdivq;
	return stm32446_rcc_dckcfgr;
}
STM32446RCC_ckgatenr stm32446_rcc_ckgatenr_inic(void)
{
	STM32446RCC_ckgatenr stm32446_rcc_ckgatenr;
	// CKGATENR
	stm32446_rcc_ckgatenr.rcc_cken = STM32446RCC_CKGATENR_rcc_cken;
	stm32446_rcc_ckgatenr.flitf_cken = STM32446RCC_CKGATENR_flitf_cken;
	stm32446_rcc_ckgatenr.sram_cken = STM32446RCC_CKGATENR_sram_cken;
	stm32446_rcc_ckgatenr.spare_cken = STM32446RCC_CKGATENR_spare_cken;
	stm32446_rcc_ckgatenr.cm4dbg_cken = STM32446RCC_CKGATENR_cm4dbg_cken;
	stm32446_rcc_ckgatenr.ahb2apb2_cken = STM32446RCC_CKGATENR_ahb2apb2_cken;
	stm32446_rcc_ckgatenr.ahb2apb1_cken = STM32446RCC_CKGATENR_ahb2apb1_cken;
	return stm32446_rcc_ckgatenr;
}
STM32446RCC_dckcfgr2 stm32446_rcc_dckcfgr2_inic(void)
{
	STM32446RCC_dckcfgr2 stm32446_rcc_dckcfgr2;
	// DCKCFGR2
	stm32446_rcc_dckcfgr2.spdifrxsel = STM32446RCC_DCKCFGR2_spdifrxsel;
	stm32446_rcc_dckcfgr2.sdiosel = STM32446RCC_DCKCFGR2_sdiosel;
	stm32446_rcc_dckcfgr2.ck48msel = STM32446RCC_DCKCFGR2_ck48msel;
	stm32446_rcc_dckcfgr2.cecsel = STM32446RCC_DCKCFGR2_cecsel;
	stm32446_rcc_dckcfgr2.fmpi2c1sel = STM32446RCC_DCKCFGR2_fmpi2c1sel;
	return stm32446_rcc_dckcfgr2;
}
/*** Extended ***/
STM32446RCCPLL stm32446_rcc_pll_inic(void)
{
	STM32446RCCPLL stm32446_rcc_pll;
	stm32446_rcc_pll.division = STM32446PLLDivision;
	stm32446_rcc_pll.enable = STM32446RccPLLCLKEnable;
	return stm32446_rcc_pll;
}
STM32446RCCPLLI2S stm32446_rcc_plli2s_inic(void)
{
	STM32446RCCPLLI2S stm32446_rcc_plli2s;
	stm32446_rcc_plli2s.enable = STM32446RccPLLI2SEnable;
	return stm32446_rcc_plli2s;
}
STM32446RCCPLLSAI stm32446_rcc_pllsai_inic(void)
{
	STM32446RCCPLLSAI stm32446_rcc_pllsai;
	stm32446_rcc_pllsai.enable = STM32446RccPLLSAIEnable;
	return stm32446_rcc_pllsai;
}
/*** INIC Procedure & Function Definition ***/
STM32446RCCobj rcc_inic(void)
{
	STM32446RCCobj stm32446_rcc;
	stm32446_rcc.reg = RCC;
	/*** RCC Bit Mapping Link ***/
	stm32446_rcc.cr = stm32446_rcc_cr_inic();
	stm32446_rcc.pllcfgr = stm32446_rcc_pllcfgr_inic();
	stm32446_rcc.cfgr = stm32446_rcc_cfgr_inic();
	stm32446_rcc.cir = stm32446_rcc_cir_inic();
	stm32446_rcc.ahb1rstr = stm32446_rcc_ahb1rstr_inic();
	stm32446_rcc.ahb2rstr = stm32446_rcc_ahb2rstr_inic();
	stm32446_rcc.ahb3rstr = stm32446_rcc_ahb3rstr_inic();
	stm32446_rcc.apb1rstr = stm32446_rcc_apb1rstr_inic();
	stm32446_rcc.apb2rstr = stm32446_rcc_apb2rstr_inic();
	stm32446_rcc.ahb1enr = stm32446_rcc_ahb1enr_inic();
	stm32446_rcc.ahb2enr = stm32446_rcc_ahb2enr_inic();
	stm32446_rcc.ahb3enr = stm32446_rcc_ahb3enr_inic();
	stm32446_rcc.apb1enr = stm32446_rcc_apb1enr_inic();
	stm32446_rcc.apb2enr = stm32446_rcc_apb2enr_inic();
	stm32446_rcc.ahb1lpenr = stm32446_rcc_ahb1lpenr_inic();
	stm32446_rcc.ahb2lpenr = stm32446_rcc_ahb2lpenr_inic();
	stm32446_rcc.ahb3lpenr = stm32446_rcc_ahb3lpenr_inic();
	stm32446_rcc.apb1lpenr = stm32446_rcc_apb1lpenr_inic();
	stm32446_rcc.apb2lpenr = stm32446_rcc_apb2lpenr_inic();
	stm32446_rcc.bdcr = stm32446_rcc_bdcr_inic();
	stm32446_rcc.csr = stm32446_rcc_csr_inic();
	stm32446_rcc.sscgr = stm32446_rcc_sscgr_inic();
	stm32446_rcc.plli2scfgr = stm32446_rcc_plli2scfgr_inic();
	stm32446_rcc.pllsaicfgr = stm32446_rcc_pllsaicfgr_inic();
	stm32446_rcc.dckcfgr = stm32446_rcc_dckcfgr_inic();
	stm32446_rcc.ckgatenr = stm32446_rcc_ckgatenr_inic();
	stm32446_rcc.dckcfgr2 = stm32446_rcc_dckcfgr2_inic();
	/*** PLL ***/
	stm32446_rcc.pll = stm32446_rcc_pll_inic();
	stm32446_rcc.plli2s = stm32446_rcc_plli2s_inic();
	stm32446_rcc.pllsai = stm32446_rcc_pllsai_inic();
	stm32446_rcc.prescaler = STM32446Prescaler;
	/*** Other ***/
	stm32446_rcc.pll_division = STM32446PLLDivision;
	stm32446_rcc.pllclk_enable = STM32446RccPLLCLKEnable;
	stm32446_rcc.plli2s_enable = STM32446RccPLLI2SEnable;
	stm32446_rcc.pllsai_enable = STM32446RccPLLSAIEnable;
	stm32446_rcc.inic = STM32446RccInic;
	stm32446_rcc.henable = STM32446RccHEnable;
	stm32446_rcc.hselect = STM32446RccHSelect;
	stm32446_rcc.lenable = STM32446RccLEnable;
	stm32446_rcc.lselect = STM32446RccLSelect;
	/*** Nvic ***/
	stm32446_rcc.nvic = STM32446RCC_nvic;
	return stm32446_rcc;
}
/*** File Procedure & Function Definition ***/
uint32_t rcc_readreg(uint32_t reg, uint32_t size_block, uint32_t bit)
{
	if(bit > 31){ bit = 0;} if(size_block > 32){ size_block = 32;}
	uint32_t value = reg;
	uint32_t mask = (unsigned int)((1 << size_block) - 1);
	value &= (mask << bit);
	value = (value >> bit);
	return value;
}
void rcc_writereg(volatile uint32_t* reg, uint32_t size_block, uint32_t bit, uint32_t data)
{
	if(bit > 31){ bit = 0;} if(size_block > 32){ size_block = 32;}
	uint32_t value = data;
	uint32_t mask = (unsigned int)((1 << size_block) - 1);
	value &= mask;
	value = (value << bit);
	*reg = value;
}
void rcc_setreg(volatile uint32_t* reg, uint32_t size_block, uint32_t bit, uint32_t data)
{
	if(bit > 31){ bit = 0;} if(size_block > 32){ size_block = 32;}
	uint32_t value = data;
	uint32_t mask = (unsigned int)((1 << size_block) - 1);
	value &= mask;
	*reg &= ~(mask << bit);
	*reg |= (value << bit);
}
void rcc_setbit(volatile uint32_t* reg, uint32_t size_block, uint32_t bit, uint32_t data)
{
	uint32_t n = 0;
	if(bit > 31){ n = bit/32; bit = bit - (n * 32); } if(size_block > 32){ size_block = 32;}
	uint32_t value = data;
	uint32_t mask = (unsigned int)((1 << size_block) - 1);
	value &= mask;
	*(reg + n ) &= ~(mask << bit);
	*(reg + n ) |= (value << bit);
}
uint32_t rcc_getsetbit(volatile uint32_t* reg, uint32_t size_block, uint32_t bit)
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


