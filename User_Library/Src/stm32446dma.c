/******************************************************************************
	STM32 446 DMA
Author: Sergio Santos 
	<sergio.salazar.santos@gmail.com>
License: GNU General Public License
Hardware: STM32-446
Date: 27062023
Comment:

*******************************************************************************/
/*** File Library ***/
#include "stm32446mapping.h"
#include "stm32446dma.h"

static uint32_t time_out;

/*** File Procedure & Function Header ***/
uint32_t dma_readreg(uint32_t reg, uint32_t size_block, uint32_t bit);
void dma_writereg(volatile uint32_t* reg, uint32_t size_block, uint32_t bit, uint32_t data);
void dma_setreg(volatile uint32_t* reg, uint32_t size_block, uint32_t bit, uint32_t data);
void dma_setbit(volatile uint32_t* reg, uint32_t size_block, uint32_t bit, uint32_t data);
uint32_t dma_getsetbit(volatile uint32_t* reg, uint32_t size_block, uint32_t bit);
/*** REG INIC ***/
STM32446DMA_sr stm32446_dma1_sr_inic(void);
STM32446DMA_STREAM_cr stm32446_dma1_stream0_cr_inic(void);
void stm32446_dma1_stream0_ndt(uint16_t value);
void stm32446_dma1_stream0_par(volatile long unsigned int periferal_addr);
void stm32446_dma1_stream0_m0a(volatile long unsigned int mem0_addr);
void stm32446_dma1_stream0_m1a(volatile long unsigned int mem1_addr);
STM32446DMA_STREAM_fcr stm32446_dma1_stream0_fcr_inic(void);
STM32446DMA_STREAM_cr stm32446_dma1_stream1_cr_inic(void);
void stm32446_dma1_stream1_ndt(uint16_t value);
void stm32446_dma1_stream1_par(volatile long unsigned int periferal_addr);
void stm32446_dma1_stream1_m0a(volatile long unsigned int mem0_addr);
void stm32446_dma1_stream1_m1a(volatile long unsigned int mem1_addr);
STM32446DMA_STREAM_fcr stm32446_dma1_stream1_fcr_inic(void);
STM32446DMA_STREAM_cr stm32446_dma1_stream2_cr_inic(void);
void stm32446_dma1_stream2_ndt(uint16_t value);
void stm32446_dma1_stream2_par(volatile long unsigned int periferal_addr);
void stm32446_dma1_stream2_m0a(volatile long unsigned int mem0_addr);
void stm32446_dma1_stream2_m1a(volatile long unsigned int mem1_addr);
STM32446DMA_STREAM_fcr stm32446_dma1_stream2_fcr_inic(void);
STM32446DMA_STREAM_cr stm32446_dma1_stream3_cr_inic(void);
void stm32446_dma1_stream3_ndt(uint16_t value);
void stm32446_dma1_stream3_par(volatile long unsigned int periferal_addr);
void stm32446_dma1_stream3_m0a(volatile long unsigned int mem0_addr);
void stm32446_dma1_stream3_m1a(volatile long unsigned int mem1_addr);
STM32446DMA_STREAM_fcr stm32446_dma1_stream3_fcr_inic(void);
STM32446DMA_STREAM_cr stm32446_dma1_stream4_cr_inic(void);
void stm32446_dma1_stream4_ndt(uint16_t value);
void stm32446_dma1_stream4_par(volatile long unsigned int periferal_addr);
void stm32446_dma1_stream4_m0a(volatile long unsigned int mem0_addr);
void stm32446_dma1_stream4_m1a(volatile long unsigned int mem1_addr);
STM32446DMA_STREAM_fcr stm32446_dma1_stream4_fcr_inic(void);
STM32446DMA_STREAM_cr stm32446_dma1_stream5_cr_inic(void);
void stm32446_dma1_stream5_ndt(uint16_t value);
void stm32446_dma1_stream5_par(volatile long unsigned int periferal_addr);
void stm32446_dma1_stream5_m0a(volatile long unsigned int mem0_addr);
void stm32446_dma1_stream5_m1a(volatile long unsigned int mem1_addr);
STM32446DMA_STREAM_fcr stm32446_dma1_stream5_fcr_inic(void);
STM32446DMA_STREAM_cr stm32446_dma1_stream6_cr_inic(void);
void stm32446_dma1_stream6_ndt(uint16_t value);
void stm32446_dma1_stream6_par(volatile long unsigned int periferal_addr);
void stm32446_dma1_stream6_m0a(volatile long unsigned int mem0_addr);
void stm32446_dma1_stream6_m1a(volatile long unsigned int mem1_addr);
STM32446DMA_STREAM_fcr stm32446_dma1_stream6_fcr_inic(void);
STM32446DMA_STREAM_cr stm32446_dma1_stream7_cr_inic(void);
void stm32446_dma1_stream7_ndt(uint16_t value);
void stm32446_dma1_stream7_par(volatile long unsigned int periferal_addr);
void stm32446_dma1_stream7_m0a(volatile long unsigned int mem0_addr);
void stm32446_dma1_stream7_m1a(volatile long unsigned int mem1_addr);
STM32446DMA_STREAM_fcr stm32446_dma1_stream7_fcr_inic(void);
STM32446DMA_func stm32446_dma1_func_inic(void);
STM32446DMA_sr stm32446_dma2_sr_inic(void);
STM32446DMA_STREAM_cr stm32446_dma2_stream0_cr_inic(void);
void stm32446_dma2_stream0_ndt(uint16_t value);
void stm32446_dma2_stream0_par(volatile long unsigned int periferal_addr);
void stm32446_dma2_stream0_m0a(volatile long unsigned int mem0_addr);
void stm32446_dma2_stream0_m1a(volatile long unsigned int mem1_addr);
STM32446DMA_STREAM_fcr stm32446_dma2_stream0_fcr_inic(void);
STM32446DMA_STREAM_cr stm32446_dma2_stream1_cr_inic(void);
void stm32446_dma2_stream1_ndt(uint16_t value);
void stm32446_dma2_stream1_par(volatile long unsigned int periferal_addr);
void stm32446_dma2_stream1_m0a(volatile long unsigned int mem0_addr);
void stm32446_dma2_stream1_m1a(volatile long unsigned int mem1_addr);
STM32446DMA_STREAM_fcr stm32446_dma2_stream1_fcr_inic(void);
STM32446DMA_STREAM_cr stm32446_dma2_stream2_cr_inic(void);
void stm32446_dma2_stream2_ndt(uint16_t value);
void stm32446_dma2_stream2_par(volatile long unsigned int periferal_addr);
void stm32446_dma2_stream2_m0a(volatile long unsigned int mem0_addr);
void stm32446_dma2_stream2_m1a(volatile long unsigned int mem1_addr);
STM32446DMA_STREAM_fcr stm32446_dma2_stream2_fcr_inic(void);
STM32446DMA_STREAM_cr stm32446_dma2_stream3_cr_inic(void);
void stm32446_dma2_stream3_ndt(uint16_t value);
void stm32446_dma2_stream3_par(volatile long unsigned int periferal_addr);
void stm32446_dma2_stream3_m0a(volatile long unsigned int mem0_addr);
void stm32446_dma2_stream3_m1a(volatile long unsigned int mem1_addr);
STM32446DMA_STREAM_fcr stm32446_dma2_stream3_fcr_inic(void);
STM32446DMA_STREAM_cr stm32446_dma2_stream4_cr_inic(void);
void stm32446_dma2_stream4_ndt(uint16_t value);
void stm32446_dma2_stream4_par(volatile long unsigned int periferal_addr);
void stm32446_dma2_stream4_m0a(volatile long unsigned int mem0_addr);
void stm32446_dma2_stream4_m1a(volatile long unsigned int mem1_addr);
STM32446DMA_STREAM_fcr stm32446_dma2_stream4_fcr_inic(void);
STM32446DMA_STREAM_cr stm32446_dma2_stream5_cr_inic(void);
void stm32446_dma2_stream5_ndt(uint16_t value);
void stm32446_dma2_stream5_par(volatile long unsigned int periferal_addr);
void stm32446_dma2_stream5_m0a(volatile long unsigned int mem0_addr);
void stm32446_dma2_stream5_m1a(volatile long unsigned int mem1_addr);
STM32446DMA_STREAM_fcr stm32446_dma2_stream5_fcr_inic(void);
STM32446DMA_STREAM_cr stm32446_dma2_stream6_cr_inic(void);
void stm32446_dma2_stream6_ndt(uint16_t value);
void stm32446_dma2_stream6_par(volatile long unsigned int periferal_addr);
void stm32446_dma2_stream6_m0a(volatile long unsigned int mem0_addr);
void stm32446_dma2_stream6_m1a(volatile long unsigned int mem1_addr);
STM32446DMA_STREAM_fcr stm32446_dma2_stream6_fcr_inic(void);
STM32446DMA_STREAM_cr stm32446_dma2_stream7_cr_inic(void);
void stm32446_dma2_stream7_ndt(uint16_t value);
void stm32446_dma2_stream7_par(volatile long unsigned int periferal_addr);
void stm32446_dma2_stream7_m0a(volatile long unsigned int mem0_addr);
void stm32446_dma2_stream7_m1a(volatile long unsigned int mem1_addr);
STM32446DMA_STREAM_fcr stm32446_dma2_stream7_fcr_inic(void);
STM32446DMA_func stm32446_dma2_func_inic(void);
/*******************************************/
/*** DMA Procedure & Function Definition ***/
/*******************************************/
void STM32446Dma1Clock(uint8_t bool)
{
	if(bool){ RCC->AHB1ENR |= (1 << 21); }
	else{ RCC->AHB1ENR &= ~(1 << 21); }
}
void STM32446Dma2Clock(uint8_t bool)
{
	if(bool){ RCC->AHB1ENR |= (1 << 22); }
	else{ RCC->AHB1ENR &= ~(1 << 22); }
}
/********************************************/
/************* DMA1 Bit Mapping *************/
/********************************************/
// SR
uint8_t STM32446DMA1_sr_tcif(uint8_t stream_n)
{
	uint8_t value;
	switch(stream_n){
		case 0:
			value = dma_readreg(DMA1->LISR, 1, 5);
		break;
		case 1:
			value = dma_readreg(DMA1->LISR, 1, 11);
		break;
		case 2:
			value = dma_readreg(DMA1->LISR, 1, 21);
		break;
		case 3:
			value = dma_readreg(DMA1->LISR, 1, 27);
		break;
		case 4:
			value = dma_readreg(DMA1->HISR, 1, 5);
		break;
		case 5:
			value = dma_readreg(DMA1->HISR, 1, 11);
		break;
		case 6:
			value = dma_readreg(DMA1->HISR, 1, 21);
		break;
		case 7:
			value = dma_readreg(DMA1->HISR, 1, 27);
		break;
	default: break;
	}
	return value;
}
void STM32446DMA1_sr_clear_tcif(uint8_t stream_n)
{
	switch(stream_n){
		case 0:
			dma_setreg(&DMA1->LIFCR, 1, 5, 1);
		break;
		case 1:
			dma_setreg(&DMA1->LIFCR, 1, 11, 1);
		break;
		case 2:
			dma_setreg(&DMA1->LIFCR, 1, 21, 1);
		break;
		case 3:
			dma_setreg(&DMA1->LIFCR, 1, 27, 1);
		break;
		case 4:
			dma_setreg(&DMA1->HIFCR, 1, 5, 1);
		break;
		case 5:
			dma_setreg(&DMA1->HIFCR, 1, 11, 1);
		break;
		case 6:
			dma_setreg(&DMA1->HIFCR, 1, 21, 1);
		break;
		case 7:
			dma_setreg(&DMA1->HIFCR, 1, 27, 1);
		break;
		default: break;
	}
}
uint8_t STM32446DMA1_sr_htif(uint8_t stream_n)
{
	uint8_t value;
	switch(stream_n){
		case 0:
			value = dma_readreg(DMA1->LISR, 1, 4);
		break;
		case 1:
			value = dma_readreg(DMA1->LISR, 1, 10);
		break;
		case 2:
			value = dma_readreg(DMA1->LISR, 1, 20);
		break;
		case 3:
			value = dma_readreg(DMA1->LISR, 1, 26);
		break;
		case 4:
			value = dma_readreg(DMA1->HISR, 1, 4);
		break;
		case 5:
			value = dma_readreg(DMA1->HISR, 1, 10);
		break;
		case 6:
			value = dma_readreg(DMA1->HISR, 1, 20);
		break;
		case 7:
			value = dma_readreg(DMA1->HISR, 1, 26);
		break;
	default: break;
	}
	return value;
}
void STM32446DMA1_sr_clear_htif(uint8_t stream_n)
{
	switch(stream_n){
		case 0:
			dma_setreg(&DMA1->LIFCR, 1, 4, 1);
		break;
		case 1:
			dma_setreg(&DMA1->LIFCR, 1, 10, 1);
		break;
		case 2:
			dma_setreg(&DMA1->LIFCR, 1, 20, 1);
		break;
		case 3:
			dma_setreg(&DMA1->LIFCR, 1, 26, 1);
		break;
		case 4:
			dma_setreg(&DMA1->HIFCR, 1, 4, 1);
		break;
		case 5:
			dma_setreg(&DMA1->HIFCR, 1, 10, 1);
		break;
		case 6:
			dma_setreg(&DMA1->HIFCR, 1, 20, 1);
		break;
		case 7:
			dma_setreg(&DMA1->HIFCR, 1, 26, 1);
		break;
		default: break;
	}
}
uint8_t STM32446DMA1_sr_teif(uint8_t stream_n)
{
	uint8_t value;
	switch(stream_n){
		case 0:
			value = dma_readreg(DMA1->LISR, 1, 3);
		break;
		case 1:
			value = dma_readreg(DMA1->LISR, 1, 9);
		break;
		case 2:
			value = dma_readreg(DMA1->LISR, 1, 19);
		break;
		case 3:
			value = dma_readreg(DMA1->LISR, 1, 25);
		break;
		case 4:
			value = dma_readreg(DMA1->HISR, 1, 3);
		break;
		case 5:
			value = dma_readreg(DMA1->HISR, 1, 9);
		break;
		case 6:
			value = dma_readreg(DMA1->HISR, 1, 19);
		break;
		case 7:
			value = dma_readreg(DMA1->HISR, 1, 25);
		break;
	default: break;
	}
	return value;
}
void STM32446DMA1_sr_clear_teif(uint8_t stream_n)
{
	switch(stream_n){
		case 0:
			dma_setreg(&DMA1->LIFCR, 1, 3, 1);
		break;
		case 1:
			dma_setreg(&DMA1->LIFCR, 1, 9, 1);
		break;
		case 2:
			dma_setreg(&DMA1->LIFCR, 1, 19, 1);
		break;
		case 3:
			dma_setreg(&DMA1->LIFCR, 1, 25, 1);
		break;
		case 4:
			dma_setreg(&DMA1->HIFCR, 1, 3, 1);
		break;
		case 5:
			dma_setreg(&DMA1->HIFCR, 1, 9, 1);
		break;
		case 6:
			dma_setreg(&DMA1->HIFCR, 1, 19, 1);
		break;
		case 7:
			dma_setreg(&DMA1->HIFCR, 1, 25, 1);
		break;
		default: break;
	}
}
uint8_t STM32446DMA1_sr_dmeif(uint8_t stream_n)
{
	uint8_t value;
	switch(stream_n){
		case 0:
			value = dma_readreg(DMA1->LISR, 1, 2);
		break;
		case 1:
			value = dma_readreg(DMA1->LISR, 1, 8);
		break;
		case 2:
			value = dma_readreg(DMA1->LISR, 1, 18);
		break;
		case 3:
			value = dma_readreg(DMA1->LISR, 1, 24);
		break;
		case 4:
			value = dma_readreg(DMA1->HISR, 1, 2);
		break;
		case 5:
			value = dma_readreg(DMA1->HISR, 1, 8);
		break;
		case 6:
			value = dma_readreg(DMA1->HISR, 1, 18);
		break;
		case 7:
			value = dma_readreg(DMA1->HISR, 1, 24);
		break;
	default: break;
	}
	return value;
}
void STM32446DMA1_sr_clear_dmeif(uint8_t stream_n)
{
	switch(stream_n){
		case 0:
			dma_setreg(&DMA1->LIFCR, 1, 2, 1);
		break;
		case 1:
			dma_setreg(&DMA1->LIFCR, 1, 8, 1);
		break;
		case 2:
			dma_setreg(&DMA1->LIFCR, 1, 18, 1);
		break;
		case 3:
			dma_setreg(&DMA1->LIFCR, 1, 24, 1);
		break;
		case 4:
			dma_setreg(&DMA1->HIFCR, 1, 2, 1);
		break;
		case 5:
			dma_setreg(&DMA1->HIFCR, 1, 8, 1);
		break;
		case 6:
			dma_setreg(&DMA1->HIFCR, 1, 18, 1);
		break;
		case 7:
			dma_setreg(&DMA1->HIFCR, 1, 24, 1);
		break;
		default: break;
	}
}
uint8_t STM32446DMA1_sr_feif(uint8_t stream_n)
{
	uint8_t value;
	switch(stream_n){
		case 0:
			value = dma_readreg(DMA1->LISR, 1, 0);
		break;
		case 1:
			value = dma_readreg(DMA1->LISR, 1, 6);
		break;
		case 2:
			value = dma_readreg(DMA1->LISR, 1, 16);
		break;
		case 3:
			value = dma_readreg(DMA1->LISR, 1, 22);
		break;
		case 4:
			value = dma_readreg(DMA1->HISR, 1, 0);
		break;
		case 5:
			value = dma_readreg(DMA1->HISR, 1, 6);
		break;
		case 6:
			value = dma_readreg(DMA1->HISR, 1, 16);
		break;
		case 7:
			value = dma_readreg(DMA1->HISR, 1, 22);
		break;
	default: break;
	}
	return value;
}
void STM32446DMA1_sr_clear_feif(uint8_t stream_n)
{
	switch(stream_n){
		case 0:
			dma_setreg(&DMA1->LIFCR, 1, 0, 1);
		break;
		case 1:
			dma_setreg(&DMA1->LIFCR, 1, 6, 1);
		break;
		case 2:
			dma_setreg(&DMA1->LIFCR, 1, 16, 1);
		break;
		case 3:
			dma_setreg(&DMA1->LIFCR, 1, 22, 1);
		break;
		case 4:
			dma_setreg(&DMA1->HIFCR, 1, 0, 1);
		break;
		case 5:
			dma_setreg(&DMA1->HIFCR, 1, 6, 1);
		break;
		case 6:
			dma_setreg(&DMA1->HIFCR, 1, 16, 1);
		break;
		case 7:
			dma_setreg(&DMA1->HIFCR, 1, 22, 1);
		break;
		default: break;
	}
}
/*** Inic SR ***/
STM32446DMA_sr stm32446_dma1_sr_inic(void)
{
	STM32446DMA_sr stm32446_dma_sr;
	// SR
	stm32446_dma_sr.tcif = STM32446DMA1_sr_tcif;
	stm32446_dma_sr.clear_tcif = STM32446DMA1_sr_clear_tcif;
	stm32446_dma_sr.htif = STM32446DMA1_sr_htif;
	stm32446_dma_sr.clear_htif = STM32446DMA1_sr_clear_htif;
	stm32446_dma_sr.teif = STM32446DMA1_sr_teif;
	stm32446_dma_sr.clear_teif = STM32446DMA1_sr_clear_teif;
	stm32446_dma_sr.dmeif = STM32446DMA1_sr_dmeif;
	stm32446_dma_sr.clear_dmeif = STM32446DMA1_sr_clear_dmeif;
	stm32446_dma_sr.feif = STM32446DMA1_sr_feif;
	stm32446_dma_sr.clear_feif = STM32446DMA1_sr_clear_feif;
	return stm32446_dma_sr;
}
// DMA1 STREAM0 CR
void STM32446DMA1_stream0_cr_chsel(uint8_t value)
{
	dma_setreg(&DMA1_Stream0->CR, 3, 25, value);
}
void STM32446DMA1_stream0_cr_mburst(uint8_t value)
{
	dma_setreg(&DMA1_Stream0->CR, 2, 23, value);
}
void STM32446DMA1_stream0_cr_pburst(uint8_t value)
{
	dma_setreg(&DMA1_Stream0->CR, 2, 21, value);
}
void STM32446DMA1_stream0_cr_ct(uint8_t bool)
{
	dma_setreg(&DMA1_Stream0->CR, 1, 19, bool);
}
void STM32446DMA1_stream0_cr_dbm(uint8_t bool)
{
	dma_setreg(&DMA1_Stream0->CR, 1, 18, bool);
}
void STM32446DMA1_stream0_cr_pl(uint8_t value)
{
	dma_setreg(&DMA1_Stream0->CR, 2, 16, value);
}
void STM32446DMA1_stream0_cr_pincos(uint8_t bool)
{
	dma_setreg(&DMA1_Stream0->CR, 1, 15, bool);
}
void STM32446DMA1_stream0_cr_msize(uint8_t value)
{
	dma_setreg(&DMA1_Stream0->CR, 2, 13, value);
}
void STM32446DMA1_stream0_cr_psize(uint8_t value)
{
	dma_setreg(&DMA1_Stream0->CR, 2, 11, value);
}
void STM32446DMA1_stream0_cr_minc(uint8_t bool)
{
	dma_setreg(&DMA1_Stream0->CR, 1, 10, bool);
}
void STM32446DMA1_stream0_cr_pinc(uint8_t bool)
{
	dma_setreg(&DMA1_Stream0->CR, 1, 9, bool);
}
void STM32446DMA1_stream0_cr_circ(uint8_t bool)
{
	dma_setreg(&DMA1_Stream0->CR, 1, 8, bool);
}
void STM32446DMA1_stream0_cr_dir(uint8_t value)
{
	dma_setreg(&DMA1_Stream0->CR, 2, 7, value);
}
void STM32446DMA1_stream0_cr_pfctrl(uint8_t bool)
{
	dma_setreg(&DMA1_Stream0->CR, 1, 5, bool);
}
void STM32446DMA1_stream0_cr_tcie(uint8_t bool)
{
	dma_setreg(&DMA1_Stream0->CR, 1, 4, bool);
}
void STM32446DMA1_stream0_cr_htie(uint8_t bool)
{
	dma_setreg(&DMA1_Stream0->CR, 1, 3, bool);
}
void STM32446DMA1_stream0_cr_teie(uint8_t bool)
{
	dma_setreg(&DMA1_Stream0->CR, 1, 2, bool);
}
void STM32446DMA1_stream0_cr_dmeie(uint8_t bool)
{
	dma_setreg(&DMA1_Stream0->CR, 1, 1, bool);
}
void STM32446DMA1_stream0_cr_en(uint8_t bool)
{
	dma_setreg(&DMA1_Stream0->CR, 1, 0, bool);
}
/*** Inic DMA1 STREAM0 CR ***/
STM32446DMA_STREAM_cr stm32446_dma1_stream0_cr_inic(void)
{
	STM32446DMA_STREAM_cr stm32446_dma_stream_cr;
	// CR
	stm32446_dma_stream_cr.chsel = STM32446DMA1_stream0_cr_chsel;
	stm32446_dma_stream_cr.mburst = STM32446DMA1_stream0_cr_mburst;
	stm32446_dma_stream_cr.pburst = STM32446DMA1_stream0_cr_pburst;
	stm32446_dma_stream_cr.ct = STM32446DMA1_stream0_cr_ct;
	stm32446_dma_stream_cr.dbm = STM32446DMA1_stream0_cr_dbm;
	stm32446_dma_stream_cr.pl = STM32446DMA1_stream0_cr_pl;
	stm32446_dma_stream_cr.pincos = STM32446DMA1_stream0_cr_pincos;
	stm32446_dma_stream_cr.msize = STM32446DMA1_stream0_cr_msize;
	stm32446_dma_stream_cr.psize = STM32446DMA1_stream0_cr_psize;
	stm32446_dma_stream_cr.minc = STM32446DMA1_stream0_cr_minc;
	stm32446_dma_stream_cr.pinc = STM32446DMA1_stream0_cr_pinc;
	stm32446_dma_stream_cr.circ = STM32446DMA1_stream0_cr_circ;
	stm32446_dma_stream_cr.dir = STM32446DMA1_stream0_cr_dir;
	stm32446_dma_stream_cr.pfctrl = STM32446DMA1_stream0_cr_pfctrl;
	stm32446_dma_stream_cr.tcie = STM32446DMA1_stream0_cr_tcie;
	stm32446_dma_stream_cr.htie = STM32446DMA1_stream0_cr_htie;
	stm32446_dma_stream_cr.teie = STM32446DMA1_stream0_cr_teie;
	stm32446_dma_stream_cr.dmeie = STM32446DMA1_stream0_cr_dmeie;
	stm32446_dma_stream_cr.en = STM32446DMA1_stream0_cr_en;
	return stm32446_dma_stream_cr;
}
/*** Inic DMA1 STREAM0 Function ***/
void stm32446_dma1_stream0_ndt(uint16_t value)
{
	DMA1_Stream0->NDTR = value;
}
void stm32446_dma1_stream0_par(volatile long unsigned int periferal_addr)
{
	DMA1_Stream0->PAR = periferal_addr;
}
void stm32446_dma1_stream0_m0a(volatile long unsigned int mem0_addr)
{
	DMA1_Stream0->M0AR = mem0_addr;
}
void stm32446_dma1_stream0_m1a(volatile long unsigned int mem1_addr)
{
	DMA1_Stream0->M1AR = mem1_addr;
}
// DMA1 STREAM1 CR
void STM32446DMA1_stream1_cr_chsel(uint8_t value)
{
	dma_setreg(&DMA1_Stream1->CR, 3, 25, value);
}
void STM32446DMA1_stream1_cr_mburst(uint8_t value)
{
	dma_setreg(&DMA1_Stream1->CR, 2, 23, value);
}
void STM32446DMA1_stream1_cr_pburst(uint8_t value)
{
	dma_setreg(&DMA1_Stream1->CR, 2, 21, value);
}
void STM32446DMA1_stream1_cr_ct(uint8_t bool)
{
	dma_setreg(&DMA1_Stream1->CR, 1, 19, bool);
}
void STM32446DMA1_stream1_cr_dbm(uint8_t bool)
{
	dma_setreg(&DMA1_Stream1->CR, 1, 18, bool);
}
void STM32446DMA1_stream1_cr_pl(uint8_t value)
{
	dma_setreg(&DMA1_Stream1->CR, 2, 16, value);
}
void STM32446DMA1_stream1_cr_pincos(uint8_t bool)
{
	dma_setreg(&DMA1_Stream1->CR, 1, 15, bool);
}
void STM32446DMA1_stream1_cr_msize(uint8_t value)
{
	dma_setreg(&DMA1_Stream1->CR, 2, 13, value);
}
void STM32446DMA1_stream1_cr_psize(uint8_t value)
{
	dma_setreg(&DMA1_Stream1->CR, 2, 11, value);
}
void STM32446DMA1_stream1_cr_minc(uint8_t bool)
{
	dma_setreg(&DMA1_Stream1->CR, 1, 10, bool);
}
void STM32446DMA1_stream1_cr_pinc(uint8_t bool)
{
	dma_setreg(&DMA1_Stream1->CR, 1, 9, bool);
}
void STM32446DMA1_stream1_cr_circ(uint8_t bool)
{
	dma_setreg(&DMA1_Stream1->CR, 1, 8, bool);
}
void STM32446DMA1_stream1_cr_dir(uint8_t value)
{
	dma_setreg(&DMA1_Stream1->CR, 2, 7, value);
}
void STM32446DMA1_stream1_cr_pfctrl(uint8_t bool)
{
	dma_setreg(&DMA1_Stream1->CR, 1, 5, bool);
}
void STM32446DMA1_stream1_cr_tcie(uint8_t bool)
{
	dma_setreg(&DMA1_Stream1->CR, 1, 4, bool);
}
void STM32446DMA1_stream1_cr_htie(uint8_t bool)
{
	dma_setreg(&DMA1_Stream1->CR, 1, 3, bool);
}
void STM32446DMA1_stream1_cr_teie(uint8_t bool)
{
	dma_setreg(&DMA1_Stream1->CR, 1, 2, bool);
}
void STM32446DMA1_stream1_cr_dmeie(uint8_t bool)
{
	dma_setreg(&DMA1_Stream1->CR, 1, 1, bool);
}
void STM32446DMA1_stream1_cr_en(uint8_t bool)
{
	dma_setreg(&DMA1_Stream1->CR, 1, 0, bool);
}
/*** Inic DMA1 STREAM1 CR ***/
STM32446DMA_STREAM_cr stm32446_dma1_stream1_cr_inic(void)
{
	STM32446DMA_STREAM_cr stm32446_dma_stream_cr;
	// CR
	stm32446_dma_stream_cr.chsel = STM32446DMA1_stream1_cr_chsel;
	stm32446_dma_stream_cr.mburst = STM32446DMA1_stream1_cr_mburst;
	stm32446_dma_stream_cr.pburst = STM32446DMA1_stream1_cr_pburst;
	stm32446_dma_stream_cr.ct = STM32446DMA1_stream1_cr_ct;
	stm32446_dma_stream_cr.dbm = STM32446DMA1_stream1_cr_dbm;
	stm32446_dma_stream_cr.pl = STM32446DMA1_stream1_cr_pl;
	stm32446_dma_stream_cr.pincos = STM32446DMA1_stream1_cr_pincos;
	stm32446_dma_stream_cr.msize = STM32446DMA1_stream1_cr_msize;
	stm32446_dma_stream_cr.psize = STM32446DMA1_stream1_cr_psize;
	stm32446_dma_stream_cr.minc = STM32446DMA1_stream1_cr_minc;
	stm32446_dma_stream_cr.pinc = STM32446DMA1_stream1_cr_pinc;
	stm32446_dma_stream_cr.circ = STM32446DMA1_stream1_cr_circ;
	stm32446_dma_stream_cr.dir = STM32446DMA1_stream1_cr_dir;
	stm32446_dma_stream_cr.pfctrl = STM32446DMA1_stream1_cr_pfctrl;
	stm32446_dma_stream_cr.tcie = STM32446DMA1_stream1_cr_tcie;
	stm32446_dma_stream_cr.htie = STM32446DMA1_stream1_cr_htie;
	stm32446_dma_stream_cr.teie = STM32446DMA1_stream1_cr_teie;
	stm32446_dma_stream_cr.dmeie = STM32446DMA1_stream1_cr_dmeie;
	stm32446_dma_stream_cr.en = STM32446DMA1_stream1_cr_en;
	return stm32446_dma_stream_cr;
}
/*** Inic DMA1 STREAM1 Function ***/
void stm32446_dma1_stream1_ndt(uint16_t value)
{
	DMA1_Stream1->NDTR = value;
}
void stm32446_dma1_stream1_par(volatile long unsigned int periferal_addr)
{
	DMA1_Stream1->PAR = periferal_addr;
}
void stm32446_dma1_stream1_m0a(volatile long unsigned int mem0_addr)
{
	DMA1_Stream1->M0AR = mem0_addr;
}
void stm32446_dma1_stream1_m1a(volatile long unsigned int mem1_addr)
{
	DMA1_Stream1->M1AR = mem1_addr;
}
// DMA1 STREAM2 CR
void STM32446DMA1_stream2_cr_chsel(uint8_t value)
{
	dma_setreg(&DMA1_Stream2->CR, 3, 25, value);
}
void STM32446DMA1_stream2_cr_mburst(uint8_t value)
{
	dma_setreg(&DMA1_Stream2->CR, 2, 23, value);
}
void STM32446DMA1_stream2_cr_pburst(uint8_t value)
{
	dma_setreg(&DMA1_Stream2->CR, 2, 21, value);
}
void STM32446DMA1_stream2_cr_ct(uint8_t bool)
{
	dma_setreg(&DMA1_Stream2->CR, 1, 19, bool);
}
void STM32446DMA1_stream2_cr_dbm(uint8_t bool)
{
	dma_setreg(&DMA1_Stream2->CR, 1, 18, bool);
}
void STM32446DMA1_stream2_cr_pl(uint8_t value)
{
	dma_setreg(&DMA1_Stream2->CR, 2, 16, value);
}
void STM32446DMA1_stream2_cr_pincos(uint8_t bool)
{
	dma_setreg(&DMA1_Stream2->CR, 1, 15, bool);
}
void STM32446DMA1_stream2_cr_msize(uint8_t value)
{
	dma_setreg(&DMA1_Stream2->CR, 2, 13, value);
}
void STM32446DMA1_stream2_cr_psize(uint8_t value)
{
	dma_setreg(&DMA1_Stream2->CR, 2, 11, value);
}
void STM32446DMA1_stream2_cr_minc(uint8_t bool)
{
	dma_setreg(&DMA1_Stream2->CR, 1, 10, bool);
}
void STM32446DMA1_stream2_cr_pinc(uint8_t bool)
{
	dma_setreg(&DMA1_Stream2->CR, 1, 9, bool);
}
void STM32446DMA1_stream2_cr_circ(uint8_t bool)
{
	dma_setreg(&DMA1_Stream2->CR, 1, 8, bool);
}
void STM32446DMA1_stream2_cr_dir(uint8_t value)
{
	dma_setreg(&DMA1_Stream2->CR, 2, 7, value);
}
void STM32446DMA1_stream2_cr_pfctrl(uint8_t bool)
{
	dma_setreg(&DMA1_Stream2->CR, 1, 5, bool);
}
void STM32446DMA1_stream2_cr_tcie(uint8_t bool)
{
	dma_setreg(&DMA1_Stream2->CR, 1, 4, bool);
}
void STM32446DMA1_stream2_cr_htie(uint8_t bool)
{
	dma_setreg(&DMA1_Stream2->CR, 1, 3, bool);
}
void STM32446DMA1_stream2_cr_teie(uint8_t bool)
{
	dma_setreg(&DMA1_Stream2->CR, 1, 2, bool);
}
void STM32446DMA1_stream2_cr_dmeie(uint8_t bool)
{
	dma_setreg(&DMA1_Stream2->CR, 1, 1, bool);
}
void STM32446DMA1_stream2_cr_en(uint8_t bool)
{
	dma_setreg(&DMA1_Stream2->CR, 1, 0, bool);
}
/*** Inic DMA1 STREAM2 CR ***/
STM32446DMA_STREAM_cr stm32446_dma1_stream2_cr_inic(void)
{
	STM32446DMA_STREAM_cr stm32446_dma_stream_cr;
	// CR
	stm32446_dma_stream_cr.chsel = STM32446DMA1_stream2_cr_chsel;
	stm32446_dma_stream_cr.mburst = STM32446DMA1_stream2_cr_mburst;
	stm32446_dma_stream_cr.pburst = STM32446DMA1_stream2_cr_pburst;
	stm32446_dma_stream_cr.ct = STM32446DMA1_stream2_cr_ct;
	stm32446_dma_stream_cr.dbm = STM32446DMA1_stream2_cr_dbm;
	stm32446_dma_stream_cr.pl = STM32446DMA1_stream2_cr_pl;
	stm32446_dma_stream_cr.pincos = STM32446DMA1_stream2_cr_pincos;
	stm32446_dma_stream_cr.msize = STM32446DMA1_stream2_cr_msize;
	stm32446_dma_stream_cr.psize = STM32446DMA1_stream2_cr_psize;
	stm32446_dma_stream_cr.minc = STM32446DMA1_stream2_cr_minc;
	stm32446_dma_stream_cr.pinc = STM32446DMA1_stream2_cr_pinc;
	stm32446_dma_stream_cr.circ = STM32446DMA1_stream2_cr_circ;
	stm32446_dma_stream_cr.dir = STM32446DMA1_stream2_cr_dir;
	stm32446_dma_stream_cr.pfctrl = STM32446DMA1_stream2_cr_pfctrl;
	stm32446_dma_stream_cr.tcie = STM32446DMA1_stream2_cr_tcie;
	stm32446_dma_stream_cr.htie = STM32446DMA1_stream2_cr_htie;
	stm32446_dma_stream_cr.teie = STM32446DMA1_stream2_cr_teie;
	stm32446_dma_stream_cr.dmeie = STM32446DMA1_stream2_cr_dmeie;
	stm32446_dma_stream_cr.en = STM32446DMA1_stream2_cr_en;
	return stm32446_dma_stream_cr;
}
/*** Inic DMA1 STREAM2 Function ***/
void stm32446_dma1_stream2_ndt(uint16_t value)
{
	DMA1_Stream2->NDTR = value;
}
void stm32446_dma1_stream2_par(volatile long unsigned int periferal_addr)
{
	DMA1_Stream2->PAR = periferal_addr;
}
void stm32446_dma1_stream2_m0a(volatile long unsigned int mem0_addr)
{
	DMA1_Stream2->M0AR = mem0_addr;
}
void stm32446_dma1_stream2_m1a(volatile long unsigned int mem1_addr)
{
	DMA1_Stream2->M1AR = mem1_addr;
}
// DMA1 STREAM3 CR
void STM32446DMA1_stream3_cr_chsel(uint8_t value)
{
	dma_setreg(&DMA1_Stream3->CR, 3, 25, value);
}
void STM32446DMA1_stream3_cr_mburst(uint8_t value)
{
	dma_setreg(&DMA1_Stream3->CR, 2, 23, value);
}
void STM32446DMA1_stream3_cr_pburst(uint8_t value)
{
	dma_setreg(&DMA1_Stream3->CR, 2, 21, value);
}
void STM32446DMA1_stream3_cr_ct(uint8_t bool)
{
	dma_setreg(&DMA1_Stream3->CR, 1, 19, bool);
}
void STM32446DMA1_stream3_cr_dbm(uint8_t bool)
{
	dma_setreg(&DMA1_Stream3->CR, 1, 18, bool);
}
void STM32446DMA1_stream3_cr_pl(uint8_t value)
{
	dma_setreg(&DMA1_Stream3->CR, 2, 16, value);
}
void STM32446DMA1_stream3_cr_pincos(uint8_t bool)
{
	dma_setreg(&DMA1_Stream3->CR, 1, 15, bool);
}
void STM32446DMA1_stream3_cr_msize(uint8_t value)
{
	dma_setreg(&DMA1_Stream3->CR, 2, 13, value);
}
void STM32446DMA1_stream3_cr_psize(uint8_t value)
{
	dma_setreg(&DMA1_Stream3->CR, 2, 11, value);
}
void STM32446DMA1_stream3_cr_minc(uint8_t bool)
{
	dma_setreg(&DMA1_Stream3->CR, 1, 10, bool);
}
void STM32446DMA1_stream3_cr_pinc(uint8_t bool)
{
	dma_setreg(&DMA1_Stream3->CR, 1, 9, bool);
}
void STM32446DMA1_stream3_cr_circ(uint8_t bool)
{
	dma_setreg(&DMA1_Stream3->CR, 1, 8, bool);
}
void STM32446DMA1_stream3_cr_dir(uint8_t value)
{
	dma_setreg(&DMA1_Stream3->CR, 2, 7, value);
}
void STM32446DMA1_stream3_cr_pfctrl(uint8_t bool)
{
	dma_setreg(&DMA1_Stream3->CR, 1, 5, bool);
}
void STM32446DMA1_stream3_cr_tcie(uint8_t bool)
{
	dma_setreg(&DMA1_Stream3->CR, 1, 4, bool);
}
void STM32446DMA1_stream3_cr_htie(uint8_t bool)
{
	dma_setreg(&DMA1_Stream3->CR, 1, 3, bool);
}
void STM32446DMA1_stream3_cr_teie(uint8_t bool)
{
	dma_setreg(&DMA1_Stream3->CR, 1, 2, bool);
}
void STM32446DMA1_stream3_cr_dmeie(uint8_t bool)
{
	dma_setreg(&DMA1_Stream3->CR, 1, 1, bool);
}
void STM32446DMA1_stream3_cr_en(uint8_t bool)
{
	dma_setreg(&DMA1_Stream3->CR, 1, 0, bool);
}
/*** Inic DMA1 STREAM3 CR ***/
STM32446DMA_STREAM_cr stm32446_dma1_stream3_cr_inic(void)
{
	STM32446DMA_STREAM_cr stm32446_dma_stream_cr;
	// CR
	stm32446_dma_stream_cr.chsel = STM32446DMA1_stream3_cr_chsel;
	stm32446_dma_stream_cr.mburst = STM32446DMA1_stream3_cr_mburst;
	stm32446_dma_stream_cr.pburst = STM32446DMA1_stream3_cr_pburst;
	stm32446_dma_stream_cr.ct = STM32446DMA1_stream3_cr_ct;
	stm32446_dma_stream_cr.dbm = STM32446DMA1_stream3_cr_dbm;
	stm32446_dma_stream_cr.pl = STM32446DMA1_stream3_cr_pl;
	stm32446_dma_stream_cr.pincos = STM32446DMA1_stream3_cr_pincos;
	stm32446_dma_stream_cr.msize = STM32446DMA1_stream3_cr_msize;
	stm32446_dma_stream_cr.psize = STM32446DMA1_stream3_cr_psize;
	stm32446_dma_stream_cr.minc = STM32446DMA1_stream3_cr_minc;
	stm32446_dma_stream_cr.pinc = STM32446DMA1_stream3_cr_pinc;
	stm32446_dma_stream_cr.circ = STM32446DMA1_stream3_cr_circ;
	stm32446_dma_stream_cr.dir = STM32446DMA1_stream3_cr_dir;
	stm32446_dma_stream_cr.pfctrl = STM32446DMA1_stream3_cr_pfctrl;
	stm32446_dma_stream_cr.tcie = STM32446DMA1_stream3_cr_tcie;
	stm32446_dma_stream_cr.htie = STM32446DMA1_stream3_cr_htie;
	stm32446_dma_stream_cr.teie = STM32446DMA1_stream3_cr_teie;
	stm32446_dma_stream_cr.dmeie = STM32446DMA1_stream3_cr_dmeie;
	stm32446_dma_stream_cr.en = STM32446DMA1_stream3_cr_en;
	return stm32446_dma_stream_cr;
}
/*** Inic DMA1 STREAM3 Function ***/
void stm32446_dma1_stream3_ndt(uint16_t value)
{
	DMA1_Stream3->NDTR = value;
}
void stm32446_dma1_stream3_par(volatile long unsigned int periferal_addr)
{
	DMA1_Stream3->PAR = periferal_addr;
}
void stm32446_dma1_stream3_m0a(volatile long unsigned int mem0_addr)
{
	DMA1_Stream3->M0AR = mem0_addr;
}
void stm32446_dma1_stream3_m1a(volatile long unsigned int mem1_addr)
{
	DMA1_Stream3->M1AR = mem1_addr;
}
// DMA1 STREAM4 CR
void STM32446DMA1_stream4_cr_chsel(uint8_t value)
{
	dma_setreg(&DMA1_Stream4->CR, 3, 25, value);
}
void STM32446DMA1_stream4_cr_mburst(uint8_t value)
{
	dma_setreg(&DMA1_Stream4->CR, 2, 23, value);
}
void STM32446DMA1_stream4_cr_pburst(uint8_t value)
{
	dma_setreg(&DMA1_Stream4->CR, 2, 21, value);
}
void STM32446DMA1_stream4_cr_ct(uint8_t bool)
{
	dma_setreg(&DMA1_Stream4->CR, 1, 19, bool);
}
void STM32446DMA1_stream4_cr_dbm(uint8_t bool)
{
	dma_setreg(&DMA1_Stream4->CR, 1, 18, bool);
}
void STM32446DMA1_stream4_cr_pl(uint8_t value)
{
	dma_setreg(&DMA1_Stream4->CR, 2, 16, value);
}
void STM32446DMA1_stream4_cr_pincos(uint8_t bool)
{
	dma_setreg(&DMA1_Stream4->CR, 1, 15, bool);
}
void STM32446DMA1_stream4_cr_msize(uint8_t value)
{
	dma_setreg(&DMA1_Stream4->CR, 2, 13, value);
}
void STM32446DMA1_stream4_cr_psize(uint8_t value)
{
	dma_setreg(&DMA1_Stream4->CR, 2, 11, value);
}
void STM32446DMA1_stream4_cr_minc(uint8_t bool)
{
	dma_setreg(&DMA1_Stream4->CR, 1, 10, bool);
}
void STM32446DMA1_stream4_cr_pinc(uint8_t bool)
{
	dma_setreg(&DMA1_Stream4->CR, 1, 9, bool);
}
void STM32446DMA1_stream4_cr_circ(uint8_t bool)
{
	dma_setreg(&DMA1_Stream4->CR, 1, 8, bool);
}
void STM32446DMA1_stream4_cr_dir(uint8_t value)
{
	dma_setreg(&DMA1_Stream4->CR, 2, 7, value);
}
void STM32446DMA1_stream4_cr_pfctrl(uint8_t bool)
{
	dma_setreg(&DMA1_Stream4->CR, 1, 5, bool);
}
void STM32446DMA1_stream4_cr_tcie(uint8_t bool)
{
	dma_setreg(&DMA1_Stream4->CR, 1, 4, bool);
}
void STM32446DMA1_stream4_cr_htie(uint8_t bool)
{
	dma_setreg(&DMA1_Stream4->CR, 1, 3, bool);
}
void STM32446DMA1_stream4_cr_teie(uint8_t bool)
{
	dma_setreg(&DMA1_Stream4->CR, 1, 2, bool);
}
void STM32446DMA1_stream4_cr_dmeie(uint8_t bool)
{
	dma_setreg(&DMA1_Stream4->CR, 1, 1, bool);
}
void STM32446DMA1_stream4_cr_en(uint8_t bool)
{
	dma_setreg(&DMA1_Stream4->CR, 1, 0, bool);
}
/*** Inic DMA1 STREAM4 CR ***/
STM32446DMA_STREAM_cr stm32446_dma1_stream4_cr_inic(void)
{
	STM32446DMA_STREAM_cr stm32446_dma_stream_cr;
	// CR
	stm32446_dma_stream_cr.chsel = STM32446DMA1_stream4_cr_chsel;
	stm32446_dma_stream_cr.mburst = STM32446DMA1_stream4_cr_mburst;
	stm32446_dma_stream_cr.pburst = STM32446DMA1_stream4_cr_pburst;
	stm32446_dma_stream_cr.ct = STM32446DMA1_stream4_cr_ct;
	stm32446_dma_stream_cr.dbm = STM32446DMA1_stream4_cr_dbm;
	stm32446_dma_stream_cr.pl = STM32446DMA1_stream4_cr_pl;
	stm32446_dma_stream_cr.pincos = STM32446DMA1_stream4_cr_pincos;
	stm32446_dma_stream_cr.msize = STM32446DMA1_stream4_cr_msize;
	stm32446_dma_stream_cr.psize = STM32446DMA1_stream4_cr_psize;
	stm32446_dma_stream_cr.minc = STM32446DMA1_stream4_cr_minc;
	stm32446_dma_stream_cr.pinc = STM32446DMA1_stream4_cr_pinc;
	stm32446_dma_stream_cr.circ = STM32446DMA1_stream4_cr_circ;
	stm32446_dma_stream_cr.dir = STM32446DMA1_stream4_cr_dir;
	stm32446_dma_stream_cr.pfctrl = STM32446DMA1_stream4_cr_pfctrl;
	stm32446_dma_stream_cr.tcie = STM32446DMA1_stream4_cr_tcie;
	stm32446_dma_stream_cr.htie = STM32446DMA1_stream4_cr_htie;
	stm32446_dma_stream_cr.teie = STM32446DMA1_stream4_cr_teie;
	stm32446_dma_stream_cr.dmeie = STM32446DMA1_stream4_cr_dmeie;
	stm32446_dma_stream_cr.en = STM32446DMA1_stream4_cr_en;
	return stm32446_dma_stream_cr;
}
/*** Inic DMA1 STREAM4 Function ***/
void stm32446_dma1_stream4_ndt(uint16_t value)
{
	DMA1_Stream4->NDTR = value;
}
void stm32446_dma1_stream4_par(volatile long unsigned int periferal_addr)
{
	DMA1_Stream4->PAR = periferal_addr;
}
void stm32446_dma1_stream4_m0a(volatile long unsigned int mem0_addr)
{
	DMA1_Stream4->M0AR = mem0_addr;
}
void stm32446_dma1_stream4_m1a(volatile long unsigned int mem1_addr)
{
	DMA1_Stream4->M1AR = mem1_addr;
}
// DMA1 STREAM5 CR
void STM32446DMA1_stream5_cr_chsel(uint8_t value)
{
	dma_setreg(&DMA1_Stream5->CR, 3, 25, value);
}
void STM32446DMA1_stream5_cr_mburst(uint8_t value)
{
	dma_setreg(&DMA1_Stream5->CR, 2, 23, value);
}
void STM32446DMA1_stream5_cr_pburst(uint8_t value)
{
	dma_setreg(&DMA1_Stream5->CR, 2, 21, value);
}
void STM32446DMA1_stream5_cr_ct(uint8_t bool)
{
	dma_setreg(&DMA1_Stream5->CR, 1, 19, bool);
}
void STM32446DMA1_stream5_cr_dbm(uint8_t bool)
{
	dma_setreg(&DMA1_Stream5->CR, 1, 18, bool);
}
void STM32446DMA1_stream5_cr_pl(uint8_t value)
{
	dma_setreg(&DMA1_Stream5->CR, 2, 16, value);
}
void STM32446DMA1_stream5_cr_pincos(uint8_t bool)
{
	dma_setreg(&DMA1_Stream5->CR, 1, 15, bool);
}
void STM32446DMA1_stream5_cr_msize(uint8_t value)
{
	dma_setreg(&DMA1_Stream5->CR, 2, 13, value);
}
void STM32446DMA1_stream5_cr_psize(uint8_t value)
{
	dma_setreg(&DMA1_Stream5->CR, 2, 11, value);
}
void STM32446DMA1_stream5_cr_minc(uint8_t bool)
{
	dma_setreg(&DMA1_Stream5->CR, 1, 10, bool);
}
void STM32446DMA1_stream5_cr_pinc(uint8_t bool)
{
	dma_setreg(&DMA1_Stream5->CR, 1, 9, bool);
}
void STM32446DMA1_stream5_cr_circ(uint8_t bool)
{
	dma_setreg(&DMA1_Stream5->CR, 1, 8, bool);
}
void STM32446DMA1_stream5_cr_dir(uint8_t value)
{
	dma_setreg(&DMA1_Stream5->CR, 2, 7, value);
}
void STM32446DMA1_stream5_cr_pfctrl(uint8_t bool)
{
	dma_setreg(&DMA1_Stream5->CR, 1, 5, bool);
}
void STM32446DMA1_stream5_cr_tcie(uint8_t bool)
{
	dma_setreg(&DMA1_Stream5->CR, 1, 4, bool);
}
void STM32446DMA1_stream5_cr_htie(uint8_t bool)
{
	dma_setreg(&DMA1_Stream5->CR, 1, 3, bool);
}
void STM32446DMA1_stream5_cr_teie(uint8_t bool)
{
	dma_setreg(&DMA1_Stream5->CR, 1, 2, bool);
}
void STM32446DMA1_stream5_cr_dmeie(uint8_t bool)
{
	dma_setreg(&DMA1_Stream5->CR, 1, 1, bool);
}
void STM32446DMA1_stream5_cr_en(uint8_t bool)
{
	dma_setreg(&DMA1_Stream5->CR, 1, 0, bool);
}
/*** Inic DMA1 STREAM5 CR ***/
STM32446DMA_STREAM_cr stm32446_dma1_stream5_cr_inic(void)
{
	STM32446DMA_STREAM_cr stm32446_dma_stream_cr;
	// CR
	stm32446_dma_stream_cr.chsel = STM32446DMA1_stream5_cr_chsel;
	stm32446_dma_stream_cr.mburst = STM32446DMA1_stream5_cr_mburst;
	stm32446_dma_stream_cr.pburst = STM32446DMA1_stream5_cr_pburst;
	stm32446_dma_stream_cr.ct = STM32446DMA1_stream5_cr_ct;
	stm32446_dma_stream_cr.dbm = STM32446DMA1_stream5_cr_dbm;
	stm32446_dma_stream_cr.pl = STM32446DMA1_stream5_cr_pl;
	stm32446_dma_stream_cr.pincos = STM32446DMA1_stream5_cr_pincos;
	stm32446_dma_stream_cr.msize = STM32446DMA1_stream5_cr_msize;
	stm32446_dma_stream_cr.psize = STM32446DMA1_stream5_cr_psize;
	stm32446_dma_stream_cr.minc = STM32446DMA1_stream5_cr_minc;
	stm32446_dma_stream_cr.pinc = STM32446DMA1_stream5_cr_pinc;
	stm32446_dma_stream_cr.circ = STM32446DMA1_stream5_cr_circ;
	stm32446_dma_stream_cr.dir = STM32446DMA1_stream5_cr_dir;
	stm32446_dma_stream_cr.pfctrl = STM32446DMA1_stream5_cr_pfctrl;
	stm32446_dma_stream_cr.tcie = STM32446DMA1_stream5_cr_tcie;
	stm32446_dma_stream_cr.htie = STM32446DMA1_stream5_cr_htie;
	stm32446_dma_stream_cr.teie = STM32446DMA1_stream5_cr_teie;
	stm32446_dma_stream_cr.dmeie = STM32446DMA1_stream5_cr_dmeie;
	stm32446_dma_stream_cr.en = STM32446DMA1_stream5_cr_en;
	return stm32446_dma_stream_cr;
}
/*** Inic DMA1 STREAM5 Function ***/
void stm32446_dma1_stream5_ndt(uint16_t value)
{
	DMA1_Stream5->NDTR = value;
}
void stm32446_dma1_stream5_par(volatile long unsigned int periferal_addr)
{
	DMA1_Stream5->PAR = periferal_addr;
}
void stm32446_dma1_stream5_m0a(volatile long unsigned int mem0_addr)
{
	DMA1_Stream5->M0AR = mem0_addr;
}
void stm32446_dma1_stream5_m1a(volatile long unsigned int mem1_addr)
{
	DMA1_Stream5->M1AR = mem1_addr;
}
// DMA1 STREAM6 CR
void STM32446DMA1_stream6_cr_chsel(uint8_t value)
{
	dma_setreg(&DMA1_Stream6->CR, 3, 25, value);
}
void STM32446DMA1_stream6_cr_mburst(uint8_t value)
{
	dma_setreg(&DMA1_Stream6->CR, 2, 23, value);
}
void STM32446DMA1_stream6_cr_pburst(uint8_t value)
{
	dma_setreg(&DMA1_Stream6->CR, 2, 21, value);
}
void STM32446DMA1_stream6_cr_ct(uint8_t bool)
{
	dma_setreg(&DMA1_Stream6->CR, 1, 19, bool);
}
void STM32446DMA1_stream6_cr_dbm(uint8_t bool)
{
	dma_setreg(&DMA1_Stream6->CR, 1, 18, bool);
}
void STM32446DMA1_stream6_cr_pl(uint8_t value)
{
	dma_setreg(&DMA1_Stream6->CR, 2, 16, value);
}
void STM32446DMA1_stream6_cr_pincos(uint8_t bool)
{
	dma_setreg(&DMA1_Stream6->CR, 1, 15, bool);
}
void STM32446DMA1_stream6_cr_msize(uint8_t value)
{
	dma_setreg(&DMA1_Stream6->CR, 2, 13, value);
}
void STM32446DMA1_stream6_cr_psize(uint8_t value)
{
	dma_setreg(&DMA1_Stream6->CR, 2, 11, value);
}
void STM32446DMA1_stream6_cr_minc(uint8_t bool)
{
	dma_setreg(&DMA1_Stream6->CR, 1, 10, bool);
}
void STM32446DMA1_stream6_cr_pinc(uint8_t bool)
{
	dma_setreg(&DMA1_Stream6->CR, 1, 9, bool);
}
void STM32446DMA1_stream6_cr_circ(uint8_t bool)
{
	dma_setreg(&DMA1_Stream6->CR, 1, 8, bool);
}
void STM32446DMA1_stream6_cr_dir(uint8_t value)
{
	dma_setreg(&DMA1_Stream6->CR, 2, 7, value);
}
void STM32446DMA1_stream6_cr_pfctrl(uint8_t bool)
{
	dma_setreg(&DMA1_Stream6->CR, 1, 5, bool);
}
void STM32446DMA1_stream6_cr_tcie(uint8_t bool)
{
	dma_setreg(&DMA1_Stream6->CR, 1, 4, bool);
}
void STM32446DMA1_stream6_cr_htie(uint8_t bool)
{
	dma_setreg(&DMA1_Stream6->CR, 1, 3, bool);
}
void STM32446DMA1_stream6_cr_teie(uint8_t bool)
{
	dma_setreg(&DMA1_Stream6->CR, 1, 2, bool);
}
void STM32446DMA1_stream6_cr_dmeie(uint8_t bool)
{
	dma_setreg(&DMA1_Stream6->CR, 1, 1, bool);
}
void STM32446DMA1_stream6_cr_en(uint8_t bool)
{
	dma_setreg(&DMA1_Stream6->CR, 1, 0, bool);
}
/*** Inic DMA1 STREAM6 CR ***/
STM32446DMA_STREAM_cr stm32446_dma1_stream6_cr_inic(void)
{
	STM32446DMA_STREAM_cr stm32446_dma_stream_cr;
	// CR
	stm32446_dma_stream_cr.chsel = STM32446DMA1_stream6_cr_chsel;
	stm32446_dma_stream_cr.mburst = STM32446DMA1_stream6_cr_mburst;
	stm32446_dma_stream_cr.pburst = STM32446DMA1_stream6_cr_pburst;
	stm32446_dma_stream_cr.ct = STM32446DMA1_stream6_cr_ct;
	stm32446_dma_stream_cr.dbm = STM32446DMA1_stream6_cr_dbm;
	stm32446_dma_stream_cr.pl = STM32446DMA1_stream6_cr_pl;
	stm32446_dma_stream_cr.pincos = STM32446DMA1_stream6_cr_pincos;
	stm32446_dma_stream_cr.msize = STM32446DMA1_stream6_cr_msize;
	stm32446_dma_stream_cr.psize = STM32446DMA1_stream6_cr_psize;
	stm32446_dma_stream_cr.minc = STM32446DMA1_stream6_cr_minc;
	stm32446_dma_stream_cr.pinc = STM32446DMA1_stream6_cr_pinc;
	stm32446_dma_stream_cr.circ = STM32446DMA1_stream6_cr_circ;
	stm32446_dma_stream_cr.dir = STM32446DMA1_stream6_cr_dir;
	stm32446_dma_stream_cr.pfctrl = STM32446DMA1_stream6_cr_pfctrl;
	stm32446_dma_stream_cr.tcie = STM32446DMA1_stream6_cr_tcie;
	stm32446_dma_stream_cr.htie = STM32446DMA1_stream6_cr_htie;
	stm32446_dma_stream_cr.teie = STM32446DMA1_stream6_cr_teie;
	stm32446_dma_stream_cr.dmeie = STM32446DMA1_stream6_cr_dmeie;
	stm32446_dma_stream_cr.en = STM32446DMA1_stream6_cr_en;
	return stm32446_dma_stream_cr;
}
/*** Inic DMA1 STREAM6 Function ***/
void stm32446_dma1_stream6_ndt(uint16_t value)
{
	DMA1_Stream6->NDTR = value;
}
void stm32446_dma1_stream6_par(volatile long unsigned int periferal_addr)
{
	DMA1_Stream6->PAR = periferal_addr;
}
void stm32446_dma1_stream6_m0a(volatile long unsigned int mem0_addr)
{
	DMA1_Stream6->M0AR = mem0_addr;
}
void stm32446_dma1_stream6_m1a(volatile long unsigned int mem1_addr)
{
	DMA1_Stream6->M1AR = mem1_addr;
}
// DMA1 STREAM7 CR
void STM32446DMA1_stream7_cr_chsel(uint8_t value)
{
	dma_setreg(&DMA1_Stream7->CR, 3, 25, value);
}
void STM32446DMA1_stream7_cr_mburst(uint8_t value)
{
	dma_setreg(&DMA1_Stream7->CR, 2, 23, value);
}
void STM32446DMA1_stream7_cr_pburst(uint8_t value)
{
	dma_setreg(&DMA1_Stream7->CR, 2, 21, value);
}
void STM32446DMA1_stream7_cr_ct(uint8_t bool)
{
	dma_setreg(&DMA1_Stream7->CR, 1, 19, bool);
}
void STM32446DMA1_stream7_cr_dbm(uint8_t bool)
{
	dma_setreg(&DMA1_Stream7->CR, 1, 18, bool);
}
void STM32446DMA1_stream7_cr_pl(uint8_t value)
{
	dma_setreg(&DMA1_Stream7->CR, 2, 16, value);
}
void STM32446DMA1_stream7_cr_pincos(uint8_t bool)
{
	dma_setreg(&DMA1_Stream7->CR, 1, 15, bool);
}
void STM32446DMA1_stream7_cr_msize(uint8_t value)
{
	dma_setreg(&DMA1_Stream7->CR, 2, 13, value);
}
void STM32446DMA1_stream7_cr_psize(uint8_t value)
{
	dma_setreg(&DMA1_Stream7->CR, 2, 11, value);
}
void STM32446DMA1_stream7_cr_minc(uint8_t bool)
{
	dma_setreg(&DMA1_Stream7->CR, 1, 10, bool);
}
void STM32446DMA1_stream7_cr_pinc(uint8_t bool)
{
	dma_setreg(&DMA1_Stream7->CR, 1, 9, bool);
}
void STM32446DMA1_stream7_cr_circ(uint8_t bool)
{
	dma_setreg(&DMA1_Stream7->CR, 1, 8, bool);
}
void STM32446DMA1_stream7_cr_dir(uint8_t value)
{
	dma_setreg(&DMA1_Stream7->CR, 2, 7, value);
}
void STM32446DMA1_stream7_cr_pfctrl(uint8_t bool)
{
	dma_setreg(&DMA1_Stream7->CR, 1, 5, bool);
}
void STM32446DMA1_stream7_cr_tcie(uint8_t bool)
{
	dma_setreg(&DMA1_Stream7->CR, 1, 4, bool);
}
void STM32446DMA1_stream7_cr_htie(uint8_t bool)
{
	dma_setreg(&DMA1_Stream7->CR, 1, 3, bool);
}
void STM32446DMA1_stream7_cr_teie(uint8_t bool)
{
	dma_setreg(&DMA1_Stream7->CR, 1, 2, bool);
}
void STM32446DMA1_stream7_cr_dmeie(uint8_t bool)
{
	dma_setreg(&DMA1_Stream7->CR, 1, 1, bool);
}
void STM32446DMA1_stream7_cr_en(uint8_t bool)
{
	dma_setreg(&DMA1_Stream7->CR, 1, 0, bool);
}
/*** Inic DMA1 STREAM7 CR ***/
STM32446DMA_STREAM_cr stm32446_dma1_stream7_cr_inic(void)
{
	STM32446DMA_STREAM_cr stm32446_dma_stream_cr;
	// CR
	stm32446_dma_stream_cr.chsel = STM32446DMA1_stream7_cr_chsel;
	stm32446_dma_stream_cr.mburst = STM32446DMA1_stream7_cr_mburst;
	stm32446_dma_stream_cr.pburst = STM32446DMA1_stream7_cr_pburst;
	stm32446_dma_stream_cr.ct = STM32446DMA1_stream7_cr_ct;
	stm32446_dma_stream_cr.dbm = STM32446DMA1_stream7_cr_dbm;
	stm32446_dma_stream_cr.pl = STM32446DMA1_stream7_cr_pl;
	stm32446_dma_stream_cr.pincos = STM32446DMA1_stream7_cr_pincos;
	stm32446_dma_stream_cr.msize = STM32446DMA1_stream7_cr_msize;
	stm32446_dma_stream_cr.psize = STM32446DMA1_stream7_cr_psize;
	stm32446_dma_stream_cr.minc = STM32446DMA1_stream7_cr_minc;
	stm32446_dma_stream_cr.pinc = STM32446DMA1_stream7_cr_pinc;
	stm32446_dma_stream_cr.circ = STM32446DMA1_stream7_cr_circ;
	stm32446_dma_stream_cr.dir = STM32446DMA1_stream7_cr_dir;
	stm32446_dma_stream_cr.pfctrl = STM32446DMA1_stream7_cr_pfctrl;
	stm32446_dma_stream_cr.tcie = STM32446DMA1_stream7_cr_tcie;
	stm32446_dma_stream_cr.htie = STM32446DMA1_stream7_cr_htie;
	stm32446_dma_stream_cr.teie = STM32446DMA1_stream7_cr_teie;
	stm32446_dma_stream_cr.dmeie = STM32446DMA1_stream7_cr_dmeie;
	stm32446_dma_stream_cr.en = STM32446DMA1_stream7_cr_en;
	return stm32446_dma_stream_cr;
}
/*** Inic DMA1 STREAM7 Function ***/
void stm32446_dma1_stream7_ndt(uint16_t value)
{
	DMA1_Stream7->NDTR = value;
}
void stm32446_dma1_stream7_par(volatile long unsigned int periferal_addr)
{
	DMA1_Stream7->PAR = periferal_addr;
}
void stm32446_dma1_stream7_m0a(volatile long unsigned int mem0_addr)
{
	DMA1_Stream7->M0AR = mem0_addr;
}
void stm32446_dma1_stream7_m1a(volatile long unsigned int mem1_addr)
{
	DMA1_Stream7->M1AR = mem1_addr;
}
// DMA1 STREAM0 FCR
void STM32446DMA1_stream0_fcr_feie(uint8_t bool)
{
	dma_setreg(&DMA1_Stream0->FCR, 1, 7, bool);
}
void STM32446DMA1_stream0_fcr_fs(uint8_t value)
{
	dma_setreg(&DMA1_Stream0->FCR, 3, 3, value);
}
void STM32446DMA1_stream0_fcr_dmdis(uint8_t bool)
{
	dma_setreg(&DMA1_Stream0->FCR, 1, 2, bool);
}
void STM32446DMA1_stream0_fcr_fth(uint8_t value)
{
	dma_setreg(&DMA1_Stream0->FCR, 2, 0, value);
}
/*** Inic DMA1 STREAM0 FCR ***/
STM32446DMA_STREAM_fcr stm32446_dma1_stream0_fcr_inic(void)
{
	STM32446DMA_STREAM_fcr stm32446_dma_stream_fcr;
	// FCR
	stm32446_dma_stream_fcr.feie = STM32446DMA1_stream0_fcr_feie;
	stm32446_dma_stream_fcr.fs = STM32446DMA1_stream0_fcr_fs;
	stm32446_dma_stream_fcr.dmdis = STM32446DMA1_stream0_fcr_dmdis;
	stm32446_dma_stream_fcr.fth = STM32446DMA1_stream0_fcr_fth;
	return stm32446_dma_stream_fcr;
}
// DMA1 STREAM1 FCR
void STM32446DMA1_stream1_fcr_feie(uint8_t bool)
{
	dma_setreg(&DMA1_Stream1->FCR, 1, 7, bool);
}
void STM32446DMA1_stream1_fcr_fs(uint8_t value)
{
	dma_setreg(&DMA1_Stream1->FCR, 3, 3, value);
}
void STM32446DMA1_stream1_fcr_dmdis(uint8_t bool)
{
	dma_setreg(&DMA1_Stream1->FCR, 1, 2, bool);
}
void STM32446DMA1_stream1_fcr_fth(uint8_t value)
{
	dma_setreg(&DMA1_Stream1->FCR, 2, 0, value);
}
/*** Inic DMA1 STREAM1 FCR ***/
STM32446DMA_STREAM_fcr stm32446_dma1_stream1_fcr_inic(void)
{
	STM32446DMA_STREAM_fcr stm32446_dma_stream_fcr;
	// FCR
	stm32446_dma_stream_fcr.feie = STM32446DMA1_stream1_fcr_feie;
	stm32446_dma_stream_fcr.fs = STM32446DMA1_stream1_fcr_fs;
	stm32446_dma_stream_fcr.dmdis = STM32446DMA1_stream1_fcr_dmdis;
	stm32446_dma_stream_fcr.fth = STM32446DMA1_stream1_fcr_fth;
	return stm32446_dma_stream_fcr;
}
// DMA1 STREAM2 FCR
void STM32446DMA1_stream2_fcr_feie(uint8_t bool)
{
	dma_setreg(&DMA1_Stream2->FCR, 1, 7, bool);
}
void STM32446DMA1_stream2_fcr_fs(uint8_t value)
{
	dma_setreg(&DMA1_Stream2->FCR, 3, 3, value);
}
void STM32446DMA1_stream2_fcr_dmdis(uint8_t bool)
{
	dma_setreg(&DMA1_Stream2->FCR, 1, 2, bool);
}
void STM32446DMA1_stream2_fcr_fth(uint8_t value)
{
	dma_setreg(&DMA1_Stream2->FCR, 2, 0, value);
}
/*** Inic DMA1 STREAM2 FCR ***/
STM32446DMA_STREAM_fcr stm32446_dma1_stream2_fcr_inic(void)
{
	STM32446DMA_STREAM_fcr stm32446_dma_stream_fcr;
	// FCR
	stm32446_dma_stream_fcr.feie = STM32446DMA1_stream2_fcr_feie;
	stm32446_dma_stream_fcr.fs = STM32446DMA1_stream2_fcr_fs;
	stm32446_dma_stream_fcr.dmdis = STM32446DMA1_stream2_fcr_dmdis;
	stm32446_dma_stream_fcr.fth = STM32446DMA1_stream2_fcr_fth;
	return stm32446_dma_stream_fcr;
}
// DMA1 STREAM3 FCR
void STM32446DMA1_stream3_fcr_feie(uint8_t bool)
{
	dma_setreg(&DMA1_Stream3->FCR, 1, 7, bool);
}
void STM32446DMA1_stream3_fcr_fs(uint8_t value)
{
	dma_setreg(&DMA1_Stream3->FCR, 3, 3, value);
}
void STM32446DMA1_stream3_fcr_dmdis(uint8_t bool)
{
	dma_setreg(&DMA1_Stream3->FCR, 1, 2, bool);
}
void STM32446DMA1_stream3_fcr_fth(uint8_t value)
{
	dma_setreg(&DMA1_Stream3->FCR, 2, 0, value);
}
/*** Inic DMA1 STREAM3 FCR ***/
STM32446DMA_STREAM_fcr stm32446_dma1_stream3_fcr_inic(void)
{
	STM32446DMA_STREAM_fcr stm32446_dma_stream_fcr;
	// FCR
	stm32446_dma_stream_fcr.feie = STM32446DMA1_stream3_fcr_feie;
	stm32446_dma_stream_fcr.fs = STM32446DMA1_stream3_fcr_fs;
	stm32446_dma_stream_fcr.dmdis = STM32446DMA1_stream3_fcr_dmdis;
	stm32446_dma_stream_fcr.fth = STM32446DMA1_stream3_fcr_fth;
	return stm32446_dma_stream_fcr;
}
// DMA1 STREAM4 FCR
void STM32446DMA1_stream4_fcr_feie(uint8_t bool)
{
	dma_setreg(&DMA1_Stream4->FCR, 1, 7, bool);
}
void STM32446DMA1_stream4_fcr_fs(uint8_t value)
{
	dma_setreg(&DMA1_Stream4->FCR, 3, 3, value);
}
void STM32446DMA1_stream4_fcr_dmdis(uint8_t bool)
{
	dma_setreg(&DMA1_Stream4->FCR, 1, 2, bool);
}
void STM32446DMA1_stream4_fcr_fth(uint8_t value)
{
	dma_setreg(&DMA1_Stream4->FCR, 2, 0, value);
}
/*** Inic DMA1 STREAM4 FCR ***/
STM32446DMA_STREAM_fcr stm32446_dma1_stream4_fcr_inic(void)
{
	STM32446DMA_STREAM_fcr stm32446_dma_stream_fcr;
	// FCR
	stm32446_dma_stream_fcr.feie = STM32446DMA1_stream4_fcr_feie;
	stm32446_dma_stream_fcr.fs = STM32446DMA1_stream4_fcr_fs;
	stm32446_dma_stream_fcr.dmdis = STM32446DMA1_stream4_fcr_dmdis;
	stm32446_dma_stream_fcr.fth = STM32446DMA1_stream4_fcr_fth;
	return stm32446_dma_stream_fcr;
}
// DMA1 STREAM5 FCR
void STM32446DMA1_stream5_fcr_feie(uint8_t bool)
{
	dma_setreg(&DMA1_Stream5->FCR, 1, 7, bool);
}
void STM32446DMA1_stream5_fcr_fs(uint8_t value)
{
	dma_setreg(&DMA1_Stream5->FCR, 3, 3, value);
}
void STM32446DMA1_stream5_fcr_dmdis(uint8_t bool)
{
	dma_setreg(&DMA1_Stream5->FCR, 1, 2, bool);
}
void STM32446DMA1_stream5_fcr_fth(uint8_t value)
{
	dma_setreg(&DMA1_Stream5->FCR, 2, 0, value);
}
/*** Inic DMA1 STREAM5 FCR ***/
STM32446DMA_STREAM_fcr stm32446_dma1_stream5_fcr_inic(void)
{
	STM32446DMA_STREAM_fcr stm32446_dma_stream_fcr;
	// FCR
	stm32446_dma_stream_fcr.feie = STM32446DMA1_stream5_fcr_feie;
	stm32446_dma_stream_fcr.fs = STM32446DMA1_stream5_fcr_fs;
	stm32446_dma_stream_fcr.dmdis = STM32446DMA1_stream5_fcr_dmdis;
	stm32446_dma_stream_fcr.fth = STM32446DMA1_stream5_fcr_fth;
	return stm32446_dma_stream_fcr;
}
// DMA1 STREAM6 FCR
void STM32446DMA1_stream6_fcr_feie(uint8_t bool)
{
	dma_setreg(&DMA1_Stream6->FCR, 1, 7, bool);
}
void STM32446DMA1_stream6_fcr_fs(uint8_t value)
{
	dma_setreg(&DMA1_Stream6->FCR, 3, 3, value);
}
void STM32446DMA1_stream6_fcr_dmdis(uint8_t bool)
{
	dma_setreg(&DMA1_Stream6->FCR, 1, 2, bool);
}
void STM32446DMA1_stream6_fcr_fth(uint8_t value)
{
	dma_setreg(&DMA1_Stream6->FCR, 2, 0, value);
}
/*** Inic DMA1 STREAM6 FCR ***/
STM32446DMA_STREAM_fcr stm32446_dma1_stream6_fcr_inic(void)
{
	STM32446DMA_STREAM_fcr stm32446_dma_stream_fcr;
	// FCR
	stm32446_dma_stream_fcr.feie = STM32446DMA1_stream6_fcr_feie;
	stm32446_dma_stream_fcr.fs = STM32446DMA1_stream6_fcr_fs;
	stm32446_dma_stream_fcr.dmdis = STM32446DMA1_stream6_fcr_dmdis;
	stm32446_dma_stream_fcr.fth = STM32446DMA1_stream6_fcr_fth;
	return stm32446_dma_stream_fcr;
}
// DMA1 STREAM0 FCR
void STM32446DMA1_stream7_fcr_feie(uint8_t bool)
{
	dma_setreg(&DMA1_Stream7->FCR, 1, 7, bool);
}
void STM32446DMA1_stream7_fcr_fs(uint8_t value)
{
	dma_setreg(&DMA1_Stream7->FCR, 3, 3, value);
}
void STM32446DMA1_stream7_fcr_dmdis(uint8_t bool)
{
	dma_setreg(&DMA1_Stream7->FCR, 1, 2, bool);
}
void STM32446DMA1_stream7_fcr_fth(uint8_t value)
{
	dma_setreg(&DMA1_Stream7->FCR, 2, 0, value);
}
/*** Inic DMA1 STREAM7 FCR ***/
STM32446DMA_STREAM_fcr stm32446_dma1_stream7_fcr_inic(void)
{
	STM32446DMA_STREAM_fcr stm32446_dma_stream_fcr;
	// FCR
	stm32446_dma_stream_fcr.feie = STM32446DMA1_stream7_fcr_feie;
	stm32446_dma_stream_fcr.fs = STM32446DMA1_stream7_fcr_fs;
	stm32446_dma_stream_fcr.dmdis = STM32446DMA1_stream7_fcr_dmdis;
	stm32446_dma_stream_fcr.fth = STM32446DMA1_stream7_fcr_fth;
	return stm32446_dma_stream_fcr;
}
/*** FUNC ***/
void dma1_circ_cfg(volatile long unsigned int* p_addr, volatile long unsigned int* m_addr, uint8_t stream_n, uint8_t channel_n, uint16_t quant_d, uint8_t p_size, uint8_t m_size, uint8_t priority, uint8_t dir)
{
	dma_setreg(&RCC->AHB1ENR, 1, 22, 1);
	// Filter to Default
	if(stream_n > 7){ stream_n = 0;}
	if(channel_n > 7){ channel_n = 0;}
	if(quant_d > 65535){ quant_d = 1;}
	if(p_size > 2){ p_size = 0;}
	if(m_size > 2){ m_size = 0;}
	if(priority > 3){ priority = 0;}
	if( p_addr && m_addr ){
		/*** Verify Ready for Parameter ***/
		dma_setreg(&(DMA1_Stream0 + stream_n)->CR, 1, 0, 0);
		for(time_out = 200; dma_readreg((DMA1_Stream0 + stream_n)->CR, 1, 0) && time_out; time_out--);
		/*** Parameter Configure ***/
		(DMA1_Stream0 + stream_n)->PAR = (volatile long unsigned int) p_addr;
		(DMA1_Stream0 + stream_n)->M0AR = (volatile long unsigned int) m_addr;
		dma_setreg(&(DMA1_Stream0 + stream_n)->CR, 1, 5, 0); // 0 -> dma, 1 -> peri
		dma_setreg(&(DMA1_Stream0 + stream_n)->CR, 3, 25, channel_n); // channel
		(DMA1_Stream0 + stream_n)->NDTR = quant_d; //
		dma_setreg(&(DMA1_Stream0 + stream_n)->CR, 2, 13, m_size); // msize 2 -> 32bit
		dma_setreg(&(DMA1_Stream0 + stream_n)->CR, 2, 11, p_size); // psize 1 -> 16bit
		dma_setreg(&(DMA1_Stream0 + stream_n)->CR, 2, 16, priority); // priority
		if(dir){
			dma_setreg(&(DMA1_Stream0 + stream_n)->CR, 2, 6, 1); // DIR
			dma_setreg(&(DMA1_Stream0 + stream_n)->CR, 1, 9, 1); // PINC
			dma_setreg(&(DMA1_Stream0 + stream_n)->CR, 1, 10, 0); // MINC
		}else{
			dma_setreg(&(DMA1_Stream0 + stream_n)->CR, 2, 6, 0); // DIR
			dma_setreg(&(DMA1_Stream0 + stream_n)->CR, 1, 9, 0); // PINC
			dma_setreg(&(DMA1_Stream0 + stream_n)->CR, 1, 10, 1); // MINC
		}
		dma_setreg(&(DMA1_Stream0 + stream_n)->CR, 1, 8, 1); // CIRC
		dma_setreg(&(DMA1_Stream0 + stream_n)->CR, 1, 0, 1); // ENABLE
	}
}
/*** Inic FUNC ***/
STM32446DMA_func stm32446_dma1_func_inic(void)
{
	STM32446DMA_func stm32446_dma_func;

	stm32446_dma_func.circ_cfg = dma1_circ_cfg;

	return stm32446_dma_func;
}
/****************************************************/
/**** DMA1 INIC Procedure & Function Definition *****/
/****************************************************/
STM32446DMA1obj dma1_inic(void)
{
	STM32446DMA1obj stm32446_dma;
	stm32446_dma.reg = DMA1;
	stm32446_dma.stream[0].reg = DMA1_Stream0;
	/*** DMA1 Bit Mapping Link ***/
	stm32446_dma.sr = stm32446_dma1_sr_inic();
	stm32446_dma.stream[0].cr = stm32446_dma1_stream0_cr_inic();
	stm32446_dma.stream[0].fcr = stm32446_dma1_stream0_fcr_inic();
	stm32446_dma.stream[0].ndt = stm32446_dma1_stream0_ndt;
	stm32446_dma.stream[0].par = stm32446_dma1_stream0_par;
	stm32446_dma.stream[0].m0a = stm32446_dma1_stream0_m0a;
	stm32446_dma.stream[0].m1a = stm32446_dma1_stream0_m1a;
	stm32446_dma.stream[1].cr = stm32446_dma1_stream1_cr_inic();
	stm32446_dma.stream[1].fcr = stm32446_dma1_stream1_fcr_inic();
	stm32446_dma.stream[1].ndt = stm32446_dma1_stream1_ndt;
	stm32446_dma.stream[1].par = stm32446_dma1_stream1_par;
	stm32446_dma.stream[1].m0a = stm32446_dma1_stream1_m0a;
	stm32446_dma.stream[1].m1a = stm32446_dma1_stream1_m1a;
	stm32446_dma.stream[2].cr = stm32446_dma1_stream2_cr_inic();
	stm32446_dma.stream[2].fcr = stm32446_dma1_stream2_fcr_inic();
	stm32446_dma.stream[2].ndt = stm32446_dma1_stream2_ndt;
	stm32446_dma.stream[2].par = stm32446_dma1_stream2_par;
	stm32446_dma.stream[2].m0a = stm32446_dma1_stream2_m0a;
	stm32446_dma.stream[2].m1a = stm32446_dma1_stream2_m1a;
	stm32446_dma.stream[3].cr = stm32446_dma1_stream3_cr_inic();
	stm32446_dma.stream[3].fcr = stm32446_dma1_stream3_fcr_inic();
	stm32446_dma.stream[3].ndt = stm32446_dma1_stream3_ndt;
	stm32446_dma.stream[3].par = stm32446_dma1_stream3_par;
	stm32446_dma.stream[3].m0a = stm32446_dma1_stream3_m0a;
	stm32446_dma.stream[3].m1a = stm32446_dma1_stream3_m1a;
	stm32446_dma.stream[4].cr = stm32446_dma1_stream4_cr_inic();
	stm32446_dma.stream[4].fcr = stm32446_dma1_stream4_fcr_inic();
	stm32446_dma.stream[4].ndt = stm32446_dma1_stream4_ndt;
	stm32446_dma.stream[4].par = stm32446_dma1_stream4_par;
	stm32446_dma.stream[4].m0a = stm32446_dma1_stream4_m0a;
	stm32446_dma.stream[4].m1a = stm32446_dma1_stream4_m1a;
	stm32446_dma.stream[5].cr = stm32446_dma1_stream5_cr_inic();
	stm32446_dma.stream[5].fcr = stm32446_dma1_stream5_fcr_inic();
	stm32446_dma.stream[5].ndt = stm32446_dma1_stream5_ndt;
	stm32446_dma.stream[5].par = stm32446_dma1_stream5_par;
	stm32446_dma.stream[5].m0a = stm32446_dma1_stream5_m0a;
	stm32446_dma.stream[5].m1a = stm32446_dma1_stream5_m1a;
	stm32446_dma.stream[6].cr = stm32446_dma1_stream6_cr_inic();
	stm32446_dma.stream[6].fcr = stm32446_dma1_stream6_fcr_inic();
	stm32446_dma.stream[6].ndt = stm32446_dma1_stream6_ndt;
	stm32446_dma.stream[6].par = stm32446_dma1_stream6_par;
	stm32446_dma.stream[6].m0a = stm32446_dma1_stream6_m0a;
	stm32446_dma.stream[6].m1a = stm32446_dma1_stream6_m1a;
	stm32446_dma.stream[7].cr = stm32446_dma1_stream7_cr_inic();
	stm32446_dma.stream[7].fcr = stm32446_dma1_stream7_fcr_inic();
	stm32446_dma.stream[7].ndt = stm32446_dma1_stream7_ndt;
	stm32446_dma.stream[7].par = stm32446_dma1_stream7_par;
	stm32446_dma.stream[7].m0a = stm32446_dma1_stream7_m0a;
	stm32446_dma.stream[7].m1a = stm32446_dma1_stream7_m1a;
	/*** Other ***/
	stm32446_dma.func = stm32446_dma1_func_inic();
	stm32446_dma.clock = STM32446Dma1Clock;
	return stm32446_dma;
}
/********************************************/
/************* DMA2 Bit Mapping *************/
/********************************************/
// SR
uint8_t STM32446DMA2_sr_tcif(uint8_t stream_n)
{
	uint8_t value;
	switch(stream_n){
		case 0:
			value = dma_readreg(DMA2->LISR, 1, 5);
		break;
		case 1:
			value = dma_readreg(DMA2->LISR, 1, 11);
		break;
		case 2:
			value = dma_readreg(DMA2->LISR, 1, 21);
		break;
		case 3:
			value = dma_readreg(DMA2->LISR, 1, 27);
		break;
		case 4:
			value = dma_readreg(DMA2->HISR, 1, 5);
		break;
		case 5:
			value = dma_readreg(DMA2->HISR, 1, 11);
		break;
		case 6:
			value = dma_readreg(DMA2->HISR, 1, 21);
		break;
		case 7:
			value = dma_readreg(DMA2->HISR, 1, 27);
		break;
	default: break;
	}
	return value;
}
void STM32446DMA2_sr_clear_tcif(uint8_t stream_n)
{
	switch(stream_n){
		case 0:
			dma_setreg(&DMA2->LIFCR, 1, 5, 1);
		break;
		case 1:
			dma_setreg(&DMA2->LIFCR, 1, 11, 1);
		break;
		case 2:
			dma_setreg(&DMA2->LIFCR, 1, 21, 1);
		break;
		case 3:
			dma_setreg(&DMA2->LIFCR, 1, 27, 1);
		break;
		case 4:
			dma_setreg(&DMA2->HIFCR, 1, 5, 1);
		break;
		case 5:
			dma_setreg(&DMA2->HIFCR, 1, 11, 1);
		break;
		case 6:
			dma_setreg(&DMA2->HIFCR, 1, 21, 1);
		break;
		case 7:
			dma_setreg(&DMA2->HIFCR, 1, 27, 1);
		break;
		default: break;
	}
}
uint8_t STM32446DMA2_sr_htif(uint8_t stream_n)
{
	uint8_t value;
	switch(stream_n){
		case 0:
			value = dma_readreg(DMA2->LISR, 1, 4);
		break;
		case 1:
			value = dma_readreg(DMA2->LISR, 1, 10);
		break;
		case 2:
			value = dma_readreg(DMA2->LISR, 1, 20);
		break;
		case 3:
			value = dma_readreg(DMA2->LISR, 1, 26);
		break;
		case 4:
			value = dma_readreg(DMA2->HISR, 1, 4);
		break;
		case 5:
			value = dma_readreg(DMA2->HISR, 1, 10);
		break;
		case 6:
			value = dma_readreg(DMA2->HISR, 1, 20);
		break;
		case 7:
			value = dma_readreg(DMA2->HISR, 1, 26);
		break;
	default: break;
	}
	return value;
}
void STM32446DMA2_sr_clear_htif(uint8_t stream_n)
{
	switch(stream_n){
		case 0:
			dma_setreg(&DMA2->LIFCR, 1, 4, 1);
		break;
		case 1:
			dma_setreg(&DMA2->LIFCR, 1, 10, 1);
		break;
		case 2:
			dma_setreg(&DMA2->LIFCR, 1, 20, 1);
		break;
		case 3:
			dma_setreg(&DMA2->LIFCR, 1, 26, 1);
		break;
		case 4:
			dma_setreg(&DMA2->HIFCR, 1, 4, 1);
		break;
		case 5:
			dma_setreg(&DMA2->HIFCR, 1, 10, 1);
		break;
		case 6:
			dma_setreg(&DMA2->HIFCR, 1, 20, 1);
		break;
		case 7:
			dma_setreg(&DMA2->HIFCR, 1, 26, 1);
		break;
		default: break;
	}
}
uint8_t STM32446DMA2_sr_teif(uint8_t stream_n)
{
	uint8_t value;
	switch(stream_n){
		case 0:
			value = dma_readreg(DMA2->LISR, 1, 3);
		break;
		case 1:
			value = dma_readreg(DMA2->LISR, 1, 9);
		break;
		case 2:
			value = dma_readreg(DMA2->LISR, 1, 19);
		break;
		case 3:
			value = dma_readreg(DMA2->LISR, 1, 25);
		break;
		case 4:
			value = dma_readreg(DMA2->HISR, 1, 3);
		break;
		case 5:
			value = dma_readreg(DMA2->HISR, 1, 9);
		break;
		case 6:
			value = dma_readreg(DMA2->HISR, 1, 19);
		break;
		case 7:
			value = dma_readreg(DMA2->HISR, 1, 25);
		break;
	default: break;
	}
	return value;
}
void STM32446DMA2_sr_clear_teif(uint8_t stream_n)
{
	switch(stream_n){
		case 0:
			dma_setreg(&DMA2->LIFCR, 1, 3, 1);
		break;
		case 1:
			dma_setreg(&DMA2->LIFCR, 1, 9, 1);
		break;
		case 2:
			dma_setreg(&DMA2->LIFCR, 1, 19, 1);
		break;
		case 3:
			dma_setreg(&DMA2->LIFCR, 1, 25, 1);
		break;
		case 4:
			dma_setreg(&DMA2->HIFCR, 1, 3, 1);
		break;
		case 5:
			dma_setreg(&DMA2->HIFCR, 1, 9, 1);
		break;
		case 6:
			dma_setreg(&DMA2->HIFCR, 1, 19, 1);
		break;
		case 7:
			dma_setreg(&DMA2->HIFCR, 1, 25, 1);
		break;
		default: break;
	}
}
uint8_t STM32446DMA2_sr_dmeif(uint8_t stream_n)
{
	uint8_t value;
	switch(stream_n){
		case 0:
			value = dma_readreg(DMA2->LISR, 1, 2);
		break;
		case 1:
			value = dma_readreg(DMA2->LISR, 1, 8);
		break;
		case 2:
			value = dma_readreg(DMA2->LISR, 1, 18);
		break;
		case 3:
			value = dma_readreg(DMA2->LISR, 1, 24);
		break;
		case 4:
			value = dma_readreg(DMA2->HISR, 1, 2);
		break;
		case 5:
			value = dma_readreg(DMA2->HISR, 1, 8);
		break;
		case 6:
			value = dma_readreg(DMA2->HISR, 1, 18);
		break;
		case 7:
			value = dma_readreg(DMA2->HISR, 1, 24);
		break;
	default: break;
	}
	return value;
}
void STM32446DMA2_sr_clear_dmeif(uint8_t stream_n)
{
	switch(stream_n){
		case 0:
			dma_setreg(&DMA2->LIFCR, 1, 2, 1);
		break;
		case 1:
			dma_setreg(&DMA2->LIFCR, 1, 8, 1);
		break;
		case 2:
			dma_setreg(&DMA2->LIFCR, 1, 18, 1);
		break;
		case 3:
			dma_setreg(&DMA2->LIFCR, 1, 24, 1);
		break;
		case 4:
			dma_setreg(&DMA2->HIFCR, 1, 2, 1);
		break;
		case 5:
			dma_setreg(&DMA2->HIFCR, 1, 8, 1);
		break;
		case 6:
			dma_setreg(&DMA2->HIFCR, 1, 18, 1);
		break;
		case 7:
			dma_setreg(&DMA2->HIFCR, 1, 24, 1);
		break;
		default: break;
	}
}
uint8_t STM32446DMA2_sr_feif(uint8_t stream_n)
{
	uint8_t value;
	switch(stream_n){
		case 0:
			value = dma_readreg(DMA2->LISR, 1, 0);
		break;
		case 1:
			value = dma_readreg(DMA2->LISR, 1, 6);
		break;
		case 2:
			value = dma_readreg(DMA2->LISR, 1, 16);
		break;
		case 3:
			value = dma_readreg(DMA2->LISR, 1, 22);
		break;
		case 4:
			value = dma_readreg(DMA2->HISR, 1, 0);
		break;
		case 5:
			value = dma_readreg(DMA2->HISR, 1, 6);
		break;
		case 6:
			value = dma_readreg(DMA2->HISR, 1, 16);
		break;
		case 7:
			value = dma_readreg(DMA2->HISR, 1, 22);
		break;
	default: break;
	}
	return value;
}
void STM32446DMA2_sr_clear_feif(uint8_t stream_n)
{
	switch(stream_n){
		case 0:
			dma_setreg(&DMA2->LIFCR, 1, 0, 1);
		break;
		case 1:
			dma_setreg(&DMA2->LIFCR, 1, 6, 1);
		break;
		case 2:
			dma_setreg(&DMA2->LIFCR, 1, 16, 1);
		break;
		case 3:
			dma_setreg(&DMA2->LIFCR, 1, 22, 1);
		break;
		case 4:
			dma_setreg(&DMA2->HIFCR, 1, 0, 1);
		break;
		case 5:
			dma_setreg(&DMA2->HIFCR, 1, 6, 1);
		break;
		case 6:
			dma_setreg(&DMA2->HIFCR, 1, 16, 1);
		break;
		case 7:
			dma_setreg(&DMA2->HIFCR, 1, 22, 1);
		break;
		default: break;
	}
}
/*** Inic SR ***/
STM32446DMA_sr stm32446_dma2_sr_inic(void)
{
	STM32446DMA_sr stm32446_dma_sr;
	// SR
	stm32446_dma_sr.tcif = STM32446DMA2_sr_tcif;
	stm32446_dma_sr.clear_tcif = STM32446DMA2_sr_clear_tcif;
	stm32446_dma_sr.htif = STM32446DMA2_sr_htif;
	stm32446_dma_sr.clear_htif = STM32446DMA2_sr_clear_htif;
	stm32446_dma_sr.teif = STM32446DMA2_sr_teif;
	stm32446_dma_sr.clear_teif = STM32446DMA2_sr_clear_teif;
	stm32446_dma_sr.dmeif = STM32446DMA2_sr_dmeif;
	stm32446_dma_sr.clear_dmeif = STM32446DMA2_sr_clear_dmeif;
	stm32446_dma_sr.feif = STM32446DMA2_sr_feif;
	stm32446_dma_sr.clear_feif = STM32446DMA2_sr_clear_feif;
	return stm32446_dma_sr;
}
// DMA2 STREAM0 CR
void STM32446DMA2_stream0_cr_chsel(uint8_t value)
{
	dma_setreg(&DMA2_Stream0->CR, 3, 25, value);
}
void STM32446DMA2_stream0_cr_mburst(uint8_t value)
{
	dma_setreg(&DMA2_Stream0->CR, 2, 23, value);
}
void STM32446DMA2_stream0_cr_pburst(uint8_t value)
{
	dma_setreg(&DMA2_Stream0->CR, 2, 21, value);
}
void STM32446DMA2_stream0_cr_ct(uint8_t bool)
{
	dma_setreg(&DMA2_Stream0->CR, 1, 19, bool);
}
void STM32446DMA2_stream0_cr_dbm(uint8_t bool)
{
	dma_setreg(&DMA2_Stream0->CR, 1, 18, bool);
}
void STM32446DMA2_stream0_cr_pl(uint8_t value)
{
	dma_setreg(&DMA2_Stream0->CR, 2, 16, value);
}
void STM32446DMA2_stream0_cr_pincos(uint8_t bool)
{
	dma_setreg(&DMA2_Stream0->CR, 1, 15, bool);
}
void STM32446DMA2_stream0_cr_msize(uint8_t value)
{
	dma_setreg(&DMA2_Stream0->CR, 2, 13, value);
}
void STM32446DMA2_stream0_cr_psize(uint8_t value)
{
	dma_setreg(&DMA2_Stream0->CR, 2, 11, value);
}
void STM32446DMA2_stream0_cr_minc(uint8_t bool)
{
	dma_setreg(&DMA2_Stream0->CR, 1, 10, bool);
}
void STM32446DMA2_stream0_cr_pinc(uint8_t bool)
{
	dma_setreg(&DMA2_Stream0->CR, 1, 9, bool);
}
void STM32446DMA2_stream0_cr_circ(uint8_t bool)
{
	dma_setreg(&DMA2_Stream0->CR, 1, 8, bool);
}
void STM32446DMA2_stream0_cr_dir(uint8_t value)
{
	dma_setreg(&DMA2_Stream0->CR, 2, 7, value);
}
void STM32446DMA2_stream0_cr_pfctrl(uint8_t bool)
{
	dma_setreg(&DMA2_Stream0->CR, 1, 5, bool);
}
void STM32446DMA2_stream0_cr_tcie(uint8_t bool)
{
	dma_setreg(&DMA2_Stream0->CR, 1, 4, bool);
}
void STM32446DMA2_stream0_cr_htie(uint8_t bool)
{
	dma_setreg(&DMA2_Stream0->CR, 1, 3, bool);
}
void STM32446DMA2_stream0_cr_teie(uint8_t bool)
{
	dma_setreg(&DMA2_Stream0->CR, 1, 2, bool);
}
void STM32446DMA2_stream0_cr_dmeie(uint8_t bool)
{
	dma_setreg(&DMA2_Stream0->CR, 1, 1, bool);
}
void STM32446DMA2_stream0_cr_en(uint8_t bool)
{
	dma_setreg(&DMA2_Stream0->CR, 1, 0, bool);
}
/*** Inic DMA2 STREAM0 CR ***/
STM32446DMA_STREAM_cr stm32446_dma2_stream0_cr_inic(void)
{
	STM32446DMA_STREAM_cr stm32446_dma_stream_cr;
	// CR
	stm32446_dma_stream_cr.chsel = STM32446DMA2_stream0_cr_chsel;
	stm32446_dma_stream_cr.mburst = STM32446DMA2_stream0_cr_mburst;
	stm32446_dma_stream_cr.pburst = STM32446DMA2_stream0_cr_pburst;
	stm32446_dma_stream_cr.ct = STM32446DMA2_stream0_cr_ct;
	stm32446_dma_stream_cr.dbm = STM32446DMA2_stream0_cr_dbm;
	stm32446_dma_stream_cr.pl = STM32446DMA2_stream0_cr_pl;
	stm32446_dma_stream_cr.pincos = STM32446DMA2_stream0_cr_pincos;
	stm32446_dma_stream_cr.msize = STM32446DMA2_stream0_cr_msize;
	stm32446_dma_stream_cr.psize = STM32446DMA2_stream0_cr_psize;
	stm32446_dma_stream_cr.minc = STM32446DMA2_stream0_cr_minc;
	stm32446_dma_stream_cr.pinc = STM32446DMA2_stream0_cr_pinc;
	stm32446_dma_stream_cr.circ = STM32446DMA2_stream0_cr_circ;
	stm32446_dma_stream_cr.dir = STM32446DMA2_stream0_cr_dir;
	stm32446_dma_stream_cr.pfctrl = STM32446DMA2_stream0_cr_pfctrl;
	stm32446_dma_stream_cr.tcie = STM32446DMA2_stream0_cr_tcie;
	stm32446_dma_stream_cr.htie = STM32446DMA2_stream0_cr_htie;
	stm32446_dma_stream_cr.teie = STM32446DMA2_stream0_cr_teie;
	stm32446_dma_stream_cr.dmeie = STM32446DMA2_stream0_cr_dmeie;
	stm32446_dma_stream_cr.en = STM32446DMA2_stream0_cr_en;
	return stm32446_dma_stream_cr;
}
/*** Inic DMA2 STREAM0 Function ***/
void stm32446_dma2_stream0_ndt(uint16_t value)
{
	DMA2_Stream0->NDTR = value;
}
void stm32446_dma2_stream0_par(volatile long unsigned int periferal_addr)
{
	DMA2_Stream0->PAR = periferal_addr;
}
void stm32446_dma2_stream0_m0a(volatile long unsigned int mem0_addr)
{
	DMA2_Stream0->M0AR = mem0_addr;
}
void stm32446_dma2_stream0_m1a(volatile long unsigned int mem1_addr)
{
	DMA2_Stream0->M1AR = mem1_addr;
}
// DMA2 STREAM1 CR
void STM32446DMA2_stream1_cr_chsel(uint8_t value)
{
	dma_setreg(&DMA2_Stream1->CR, 3, 25, value);
}
void STM32446DMA2_stream1_cr_mburst(uint8_t value)
{
	dma_setreg(&DMA2_Stream1->CR, 2, 23, value);
}
void STM32446DMA2_stream1_cr_pburst(uint8_t value)
{
	dma_setreg(&DMA2_Stream1->CR, 2, 21, value);
}
void STM32446DMA2_stream1_cr_ct(uint8_t bool)
{
	dma_setreg(&DMA2_Stream1->CR, 1, 19, bool);
}
void STM32446DMA2_stream1_cr_dbm(uint8_t bool)
{
	dma_setreg(&DMA2_Stream1->CR, 1, 18, bool);
}
void STM32446DMA2_stream1_cr_pl(uint8_t value)
{
	dma_setreg(&DMA2_Stream1->CR, 2, 16, value);
}
void STM32446DMA2_stream1_cr_pincos(uint8_t bool)
{
	dma_setreg(&DMA2_Stream1->CR, 1, 15, bool);
}
void STM32446DMA2_stream1_cr_msize(uint8_t value)
{
	dma_setreg(&DMA2_Stream1->CR, 2, 13, value);
}
void STM32446DMA2_stream1_cr_psize(uint8_t value)
{
	dma_setreg(&DMA2_Stream1->CR, 2, 11, value);
}
void STM32446DMA2_stream1_cr_minc(uint8_t bool)
{
	dma_setreg(&DMA2_Stream1->CR, 1, 10, bool);
}
void STM32446DMA2_stream1_cr_pinc(uint8_t bool)
{
	dma_setreg(&DMA2_Stream1->CR, 1, 9, bool);
}
void STM32446DMA2_stream1_cr_circ(uint8_t bool)
{
	dma_setreg(&DMA2_Stream1->CR, 1, 8, bool);
}
void STM32446DMA2_stream1_cr_dir(uint8_t value)
{
	dma_setreg(&DMA2_Stream1->CR, 2, 7, value);
}
void STM32446DMA2_stream1_cr_pfctrl(uint8_t bool)
{
	dma_setreg(&DMA2_Stream1->CR, 1, 5, bool);
}
void STM32446DMA2_stream1_cr_tcie(uint8_t bool)
{
	dma_setreg(&DMA2_Stream1->CR, 1, 4, bool);
}
void STM32446DMA2_stream1_cr_htie(uint8_t bool)
{
	dma_setreg(&DMA2_Stream1->CR, 1, 3, bool);
}
void STM32446DMA2_stream1_cr_teie(uint8_t bool)
{
	dma_setreg(&DMA2_Stream1->CR, 1, 2, bool);
}
void STM32446DMA2_stream1_cr_dmeie(uint8_t bool)
{
	dma_setreg(&DMA2_Stream1->CR, 1, 1, bool);
}
void STM32446DMA2_stream1_cr_en(uint8_t bool)
{
	dma_setreg(&DMA2_Stream1->CR, 1, 0, bool);
}
/*** Inic DMA2 STREAM1 CR ***/
STM32446DMA_STREAM_cr stm32446_dma2_stream1_cr_inic(void)
{
	STM32446DMA_STREAM_cr stm32446_dma_stream_cr;
	// CR
	stm32446_dma_stream_cr.chsel = STM32446DMA2_stream1_cr_chsel;
	stm32446_dma_stream_cr.mburst = STM32446DMA2_stream1_cr_mburst;
	stm32446_dma_stream_cr.pburst = STM32446DMA2_stream1_cr_pburst;
	stm32446_dma_stream_cr.ct = STM32446DMA2_stream1_cr_ct;
	stm32446_dma_stream_cr.dbm = STM32446DMA2_stream1_cr_dbm;
	stm32446_dma_stream_cr.pl = STM32446DMA2_stream1_cr_pl;
	stm32446_dma_stream_cr.pincos = STM32446DMA2_stream1_cr_pincos;
	stm32446_dma_stream_cr.msize = STM32446DMA2_stream1_cr_msize;
	stm32446_dma_stream_cr.psize = STM32446DMA2_stream1_cr_psize;
	stm32446_dma_stream_cr.minc = STM32446DMA2_stream1_cr_minc;
	stm32446_dma_stream_cr.pinc = STM32446DMA2_stream1_cr_pinc;
	stm32446_dma_stream_cr.circ = STM32446DMA2_stream1_cr_circ;
	stm32446_dma_stream_cr.dir = STM32446DMA2_stream1_cr_dir;
	stm32446_dma_stream_cr.pfctrl = STM32446DMA2_stream1_cr_pfctrl;
	stm32446_dma_stream_cr.tcie = STM32446DMA2_stream1_cr_tcie;
	stm32446_dma_stream_cr.htie = STM32446DMA2_stream1_cr_htie;
	stm32446_dma_stream_cr.teie = STM32446DMA2_stream1_cr_teie;
	stm32446_dma_stream_cr.dmeie = STM32446DMA2_stream1_cr_dmeie;
	stm32446_dma_stream_cr.en = STM32446DMA2_stream1_cr_en;
	return stm32446_dma_stream_cr;
}
/*** Inic DMA2 STREAM1 Function ***/
void stm32446_dma2_stream1_ndt(uint16_t value)
{
	DMA2_Stream1->NDTR = value;
}
void stm32446_dma2_stream1_par(volatile long unsigned int periferal_addr)
{
	DMA2_Stream1->PAR = periferal_addr;
}
void stm32446_dma2_stream1_m0a(volatile long unsigned int mem0_addr)
{
	DMA2_Stream1->M0AR = mem0_addr;
}
void stm32446_dma2_stream1_m1a(volatile long unsigned int mem1_addr)
{
	DMA2_Stream1->M1AR = mem1_addr;
}
// DMA2 STREAM2 CR
void STM32446DMA2_stream2_cr_chsel(uint8_t value)
{
	dma_setreg(&DMA2_Stream2->CR, 3, 25, value);
}
void STM32446DMA2_stream2_cr_mburst(uint8_t value)
{
	dma_setreg(&DMA2_Stream2->CR, 2, 23, value);
}
void STM32446DMA2_stream2_cr_pburst(uint8_t value)
{
	dma_setreg(&DMA2_Stream2->CR, 2, 21, value);
}
void STM32446DMA2_stream2_cr_ct(uint8_t bool)
{
	dma_setreg(&DMA2_Stream2->CR, 1, 19, bool);
}
void STM32446DMA2_stream2_cr_dbm(uint8_t bool)
{
	dma_setreg(&DMA2_Stream2->CR, 1, 18, bool);
}
void STM32446DMA2_stream2_cr_pl(uint8_t value)
{
	dma_setreg(&DMA2_Stream2->CR, 2, 16, value);
}
void STM32446DMA2_stream2_cr_pincos(uint8_t bool)
{
	dma_setreg(&DMA2_Stream2->CR, 1, 15, bool);
}
void STM32446DMA2_stream2_cr_msize(uint8_t value)
{
	dma_setreg(&DMA2_Stream2->CR, 2, 13, value);
}
void STM32446DMA2_stream2_cr_psize(uint8_t value)
{
	dma_setreg(&DMA2_Stream2->CR, 2, 11, value);
}
void STM32446DMA2_stream2_cr_minc(uint8_t bool)
{
	dma_setreg(&DMA2_Stream2->CR, 1, 10, bool);
}
void STM32446DMA2_stream2_cr_pinc(uint8_t bool)
{
	dma_setreg(&DMA2_Stream2->CR, 1, 9, bool);
}
void STM32446DMA2_stream2_cr_circ(uint8_t bool)
{
	dma_setreg(&DMA2_Stream2->CR, 1, 8, bool);
}
void STM32446DMA2_stream2_cr_dir(uint8_t value)
{
	dma_setreg(&DMA2_Stream2->CR, 2, 7, value);
}
void STM32446DMA2_stream2_cr_pfctrl(uint8_t bool)
{
	dma_setreg(&DMA2_Stream2->CR, 1, 5, bool);
}
void STM32446DMA2_stream2_cr_tcie(uint8_t bool)
{
	dma_setreg(&DMA2_Stream2->CR, 1, 4, bool);
}
void STM32446DMA2_stream2_cr_htie(uint8_t bool)
{
	dma_setreg(&DMA2_Stream2->CR, 1, 3, bool);
}
void STM32446DMA2_stream2_cr_teie(uint8_t bool)
{
	dma_setreg(&DMA2_Stream2->CR, 1, 2, bool);
}
void STM32446DMA2_stream2_cr_dmeie(uint8_t bool)
{
	dma_setreg(&DMA2_Stream2->CR, 1, 1, bool);
}
void STM32446DMA2_stream2_cr_en(uint8_t bool)
{
	dma_setreg(&DMA2_Stream2->CR, 1, 0, bool);
}
/*** Inic DMA2 STREAM2 CR ***/
STM32446DMA_STREAM_cr stm32446_dma2_stream2_cr_inic(void)
{
	STM32446DMA_STREAM_cr stm32446_dma_stream_cr;
	// CR
	stm32446_dma_stream_cr.chsel = STM32446DMA2_stream2_cr_chsel;
	stm32446_dma_stream_cr.mburst = STM32446DMA2_stream2_cr_mburst;
	stm32446_dma_stream_cr.pburst = STM32446DMA2_stream2_cr_pburst;
	stm32446_dma_stream_cr.ct = STM32446DMA2_stream2_cr_ct;
	stm32446_dma_stream_cr.dbm = STM32446DMA2_stream2_cr_dbm;
	stm32446_dma_stream_cr.pl = STM32446DMA2_stream2_cr_pl;
	stm32446_dma_stream_cr.pincos = STM32446DMA2_stream2_cr_pincos;
	stm32446_dma_stream_cr.msize = STM32446DMA2_stream2_cr_msize;
	stm32446_dma_stream_cr.psize = STM32446DMA2_stream2_cr_psize;
	stm32446_dma_stream_cr.minc = STM32446DMA2_stream2_cr_minc;
	stm32446_dma_stream_cr.pinc = STM32446DMA2_stream2_cr_pinc;
	stm32446_dma_stream_cr.circ = STM32446DMA2_stream2_cr_circ;
	stm32446_dma_stream_cr.dir = STM32446DMA2_stream2_cr_dir;
	stm32446_dma_stream_cr.pfctrl = STM32446DMA2_stream2_cr_pfctrl;
	stm32446_dma_stream_cr.tcie = STM32446DMA2_stream2_cr_tcie;
	stm32446_dma_stream_cr.htie = STM32446DMA2_stream2_cr_htie;
	stm32446_dma_stream_cr.teie = STM32446DMA2_stream2_cr_teie;
	stm32446_dma_stream_cr.dmeie = STM32446DMA2_stream2_cr_dmeie;
	stm32446_dma_stream_cr.en = STM32446DMA2_stream2_cr_en;
	return stm32446_dma_stream_cr;
}
/*** Inic DMA2 STREAM2 Function ***/
void stm32446_dma2_stream2_ndt(uint16_t value)
{
	DMA2_Stream2->NDTR = value;
}
void stm32446_dma2_stream2_par(volatile long unsigned int periferal_addr)
{
	DMA2_Stream2->PAR = periferal_addr;
}
void stm32446_dma2_stream2_m0a(volatile long unsigned int mem0_addr)
{
	DMA2_Stream2->M0AR = mem0_addr;
}
void stm32446_dma2_stream2_m1a(volatile long unsigned int mem1_addr)
{
	DMA2_Stream2->M1AR = mem1_addr;
}
// DMA2 STREAM3 CR
void STM32446DMA2_stream3_cr_chsel(uint8_t value)
{
	dma_setreg(&DMA2_Stream3->CR, 3, 25, value);
}
void STM32446DMA2_stream3_cr_mburst(uint8_t value)
{
	dma_setreg(&DMA2_Stream3->CR, 2, 23, value);
}
void STM32446DMA2_stream3_cr_pburst(uint8_t value)
{
	dma_setreg(&DMA2_Stream3->CR, 2, 21, value);
}
void STM32446DMA2_stream3_cr_ct(uint8_t bool)
{
	dma_setreg(&DMA2_Stream3->CR, 1, 19, bool);
}
void STM32446DMA2_stream3_cr_dbm(uint8_t bool)
{
	dma_setreg(&DMA2_Stream3->CR, 1, 18, bool);
}
void STM32446DMA2_stream3_cr_pl(uint8_t value)
{
	dma_setreg(&DMA2_Stream3->CR, 2, 16, value);
}
void STM32446DMA2_stream3_cr_pincos(uint8_t bool)
{
	dma_setreg(&DMA2_Stream3->CR, 1, 15, bool);
}
void STM32446DMA2_stream3_cr_msize(uint8_t value)
{
	dma_setreg(&DMA2_Stream3->CR, 2, 13, value);
}
void STM32446DMA2_stream3_cr_psize(uint8_t value)
{
	dma_setreg(&DMA2_Stream3->CR, 2, 11, value);
}
void STM32446DMA2_stream3_cr_minc(uint8_t bool)
{
	dma_setreg(&DMA2_Stream3->CR, 1, 10, bool);
}
void STM32446DMA2_stream3_cr_pinc(uint8_t bool)
{
	dma_setreg(&DMA2_Stream3->CR, 1, 9, bool);
}
void STM32446DMA2_stream3_cr_circ(uint8_t bool)
{
	dma_setreg(&DMA2_Stream3->CR, 1, 8, bool);
}
void STM32446DMA2_stream3_cr_dir(uint8_t value)
{
	dma_setreg(&DMA2_Stream3->CR, 2, 7, value);
}
void STM32446DMA2_stream3_cr_pfctrl(uint8_t bool)
{
	dma_setreg(&DMA2_Stream3->CR, 1, 5, bool);
}
void STM32446DMA2_stream3_cr_tcie(uint8_t bool)
{
	dma_setreg(&DMA2_Stream3->CR, 1, 4, bool);
}
void STM32446DMA2_stream3_cr_htie(uint8_t bool)
{
	dma_setreg(&DMA2_Stream3->CR, 1, 3, bool);
}
void STM32446DMA2_stream3_cr_teie(uint8_t bool)
{
	dma_setreg(&DMA2_Stream3->CR, 1, 2, bool);
}
void STM32446DMA2_stream3_cr_dmeie(uint8_t bool)
{
	dma_setreg(&DMA2_Stream3->CR, 1, 1, bool);
}
void STM32446DMA2_stream3_cr_en(uint8_t bool)
{
	dma_setreg(&DMA2_Stream3->CR, 1, 0, bool);
}
/*** Inic DMA2 STREAM3 CR ***/
STM32446DMA_STREAM_cr stm32446_dma2_stream3_cr_inic(void)
{
	STM32446DMA_STREAM_cr stm32446_dma_stream_cr;
	// CR
	stm32446_dma_stream_cr.chsel = STM32446DMA2_stream3_cr_chsel;
	stm32446_dma_stream_cr.mburst = STM32446DMA2_stream3_cr_mburst;
	stm32446_dma_stream_cr.pburst = STM32446DMA2_stream3_cr_pburst;
	stm32446_dma_stream_cr.ct = STM32446DMA2_stream3_cr_ct;
	stm32446_dma_stream_cr.dbm = STM32446DMA2_stream3_cr_dbm;
	stm32446_dma_stream_cr.pl = STM32446DMA2_stream3_cr_pl;
	stm32446_dma_stream_cr.pincos = STM32446DMA2_stream3_cr_pincos;
	stm32446_dma_stream_cr.msize = STM32446DMA2_stream3_cr_msize;
	stm32446_dma_stream_cr.psize = STM32446DMA2_stream3_cr_psize;
	stm32446_dma_stream_cr.minc = STM32446DMA2_stream3_cr_minc;
	stm32446_dma_stream_cr.pinc = STM32446DMA2_stream3_cr_pinc;
	stm32446_dma_stream_cr.circ = STM32446DMA2_stream3_cr_circ;
	stm32446_dma_stream_cr.dir = STM32446DMA2_stream3_cr_dir;
	stm32446_dma_stream_cr.pfctrl = STM32446DMA2_stream3_cr_pfctrl;
	stm32446_dma_stream_cr.tcie = STM32446DMA2_stream3_cr_tcie;
	stm32446_dma_stream_cr.htie = STM32446DMA2_stream3_cr_htie;
	stm32446_dma_stream_cr.teie = STM32446DMA2_stream3_cr_teie;
	stm32446_dma_stream_cr.dmeie = STM32446DMA2_stream3_cr_dmeie;
	stm32446_dma_stream_cr.en = STM32446DMA2_stream3_cr_en;
	return stm32446_dma_stream_cr;
}
/*** Inic DMA2 STREAM3 Function ***/
void stm32446_dma2_stream3_ndt(uint16_t value)
{
	DMA2_Stream3->NDTR = value;
}
void stm32446_dma2_stream3_par(volatile long unsigned int periferal_addr)
{
	DMA2_Stream3->PAR = periferal_addr;
}
void stm32446_dma2_stream3_m0a(volatile long unsigned int mem0_addr)
{
	DMA2_Stream3->M0AR = mem0_addr;
}
void stm32446_dma2_stream3_m1a(volatile long unsigned int mem1_addr)
{
	DMA2_Stream3->M1AR = mem1_addr;
}
// DMA2 STREAM4 CR
void STM32446DMA2_stream4_cr_chsel(uint8_t value)
{
	dma_setreg(&DMA2_Stream4->CR, 3, 25, value);
}
void STM32446DMA2_stream4_cr_mburst(uint8_t value)
{
	dma_setreg(&DMA2_Stream4->CR, 2, 23, value);
}
void STM32446DMA2_stream4_cr_pburst(uint8_t value)
{
	dma_setreg(&DMA2_Stream4->CR, 2, 21, value);
}
void STM32446DMA2_stream4_cr_ct(uint8_t bool)
{
	dma_setreg(&DMA2_Stream4->CR, 1, 19, bool);
}
void STM32446DMA2_stream4_cr_dbm(uint8_t bool)
{
	dma_setreg(&DMA2_Stream4->CR, 1, 18, bool);
}
void STM32446DMA2_stream4_cr_pl(uint8_t value)
{
	dma_setreg(&DMA2_Stream4->CR, 2, 16, value);
}
void STM32446DMA2_stream4_cr_pincos(uint8_t bool)
{
	dma_setreg(&DMA2_Stream4->CR, 1, 15, bool);
}
void STM32446DMA2_stream4_cr_msize(uint8_t value)
{
	dma_setreg(&DMA2_Stream4->CR, 2, 13, value);
}
void STM32446DMA2_stream4_cr_psize(uint8_t value)
{
	dma_setreg(&DMA2_Stream4->CR, 2, 11, value);
}
void STM32446DMA2_stream4_cr_minc(uint8_t bool)
{
	dma_setreg(&DMA2_Stream4->CR, 1, 10, bool);
}
void STM32446DMA2_stream4_cr_pinc(uint8_t bool)
{
	dma_setreg(&DMA2_Stream4->CR, 1, 9, bool);
}
void STM32446DMA2_stream4_cr_circ(uint8_t bool)
{
	dma_setreg(&DMA2_Stream4->CR, 1, 8, bool);
}
void STM32446DMA2_stream4_cr_dir(uint8_t value)
{
	dma_setreg(&DMA2_Stream4->CR, 2, 7, value);
}
void STM32446DMA2_stream4_cr_pfctrl(uint8_t bool)
{
	dma_setreg(&DMA2_Stream4->CR, 1, 5, bool);
}
void STM32446DMA2_stream4_cr_tcie(uint8_t bool)
{
	dma_setreg(&DMA2_Stream4->CR, 1, 4, bool);
}
void STM32446DMA2_stream4_cr_htie(uint8_t bool)
{
	dma_setreg(&DMA2_Stream4->CR, 1, 3, bool);
}
void STM32446DMA2_stream4_cr_teie(uint8_t bool)
{
	dma_setreg(&DMA2_Stream4->CR, 1, 2, bool);
}
void STM32446DMA2_stream4_cr_dmeie(uint8_t bool)
{
	dma_setreg(&DMA2_Stream4->CR, 1, 1, bool);
}
void STM32446DMA2_stream4_cr_en(uint8_t bool)
{
	dma_setreg(&DMA2_Stream4->CR, 1, 0, bool);
}
/*** Inic DMA2 STREAM4 CR ***/
STM32446DMA_STREAM_cr stm32446_dma2_stream4_cr_inic(void)
{
	STM32446DMA_STREAM_cr stm32446_dma_stream_cr;
	// CR
	stm32446_dma_stream_cr.chsel = STM32446DMA2_stream4_cr_chsel;
	stm32446_dma_stream_cr.mburst = STM32446DMA2_stream4_cr_mburst;
	stm32446_dma_stream_cr.pburst = STM32446DMA2_stream4_cr_pburst;
	stm32446_dma_stream_cr.ct = STM32446DMA2_stream4_cr_ct;
	stm32446_dma_stream_cr.dbm = STM32446DMA2_stream4_cr_dbm;
	stm32446_dma_stream_cr.pl = STM32446DMA2_stream4_cr_pl;
	stm32446_dma_stream_cr.pincos = STM32446DMA2_stream4_cr_pincos;
	stm32446_dma_stream_cr.msize = STM32446DMA2_stream4_cr_msize;
	stm32446_dma_stream_cr.psize = STM32446DMA2_stream4_cr_psize;
	stm32446_dma_stream_cr.minc = STM32446DMA2_stream4_cr_minc;
	stm32446_dma_stream_cr.pinc = STM32446DMA2_stream4_cr_pinc;
	stm32446_dma_stream_cr.circ = STM32446DMA2_stream4_cr_circ;
	stm32446_dma_stream_cr.dir = STM32446DMA2_stream4_cr_dir;
	stm32446_dma_stream_cr.pfctrl = STM32446DMA2_stream4_cr_pfctrl;
	stm32446_dma_stream_cr.tcie = STM32446DMA2_stream4_cr_tcie;
	stm32446_dma_stream_cr.htie = STM32446DMA2_stream4_cr_htie;
	stm32446_dma_stream_cr.teie = STM32446DMA2_stream4_cr_teie;
	stm32446_dma_stream_cr.dmeie = STM32446DMA2_stream4_cr_dmeie;
	stm32446_dma_stream_cr.en = STM32446DMA2_stream4_cr_en;
	return stm32446_dma_stream_cr;
}
/*** Inic DMA2 STREAM4 Function ***/
void stm32446_dma2_stream4_ndt(uint16_t value)
{
	DMA2_Stream4->NDTR = value;
}
void stm32446_dma2_stream4_par(volatile long unsigned int periferal_addr)
{
	DMA2_Stream4->PAR = periferal_addr;
}
void stm32446_dma2_stream4_m0a(volatile long unsigned int mem0_addr)
{
	DMA2_Stream4->M0AR = mem0_addr;
}
void stm32446_dma2_stream4_m1a(volatile long unsigned int mem1_addr)
{
	DMA2_Stream4->M1AR = mem1_addr;
}
// DMA2 STREAM5 CR
void STM32446DMA2_stream5_cr_chsel(uint8_t value)
{
	dma_setreg(&DMA2_Stream5->CR, 3, 25, value);
}
void STM32446DMA2_stream5_cr_mburst(uint8_t value)
{
	dma_setreg(&DMA2_Stream5->CR, 2, 23, value);
}
void STM32446DMA2_stream5_cr_pburst(uint8_t value)
{
	dma_setreg(&DMA2_Stream5->CR, 2, 21, value);
}
void STM32446DMA2_stream5_cr_ct(uint8_t bool)
{
	dma_setreg(&DMA2_Stream5->CR, 1, 19, bool);
}
void STM32446DMA2_stream5_cr_dbm(uint8_t bool)
{
	dma_setreg(&DMA2_Stream5->CR, 1, 18, bool);
}
void STM32446DMA2_stream5_cr_pl(uint8_t value)
{
	dma_setreg(&DMA2_Stream5->CR, 2, 16, value);
}
void STM32446DMA2_stream5_cr_pincos(uint8_t bool)
{
	dma_setreg(&DMA2_Stream5->CR, 1, 15, bool);
}
void STM32446DMA2_stream5_cr_msize(uint8_t value)
{
	dma_setreg(&DMA2_Stream5->CR, 2, 13, value);
}
void STM32446DMA2_stream5_cr_psize(uint8_t value)
{
	dma_setreg(&DMA2_Stream5->CR, 2, 11, value);
}
void STM32446DMA2_stream5_cr_minc(uint8_t bool)
{
	dma_setreg(&DMA2_Stream5->CR, 1, 10, bool);
}
void STM32446DMA2_stream5_cr_pinc(uint8_t bool)
{
	dma_setreg(&DMA2_Stream5->CR, 1, 9, bool);
}
void STM32446DMA2_stream5_cr_circ(uint8_t bool)
{
	dma_setreg(&DMA2_Stream5->CR, 1, 8, bool);
}
void STM32446DMA2_stream5_cr_dir(uint8_t value)
{
	dma_setreg(&DMA2_Stream5->CR, 2, 7, value);
}
void STM32446DMA2_stream5_cr_pfctrl(uint8_t bool)
{
	dma_setreg(&DMA2_Stream5->CR, 1, 5, bool);
}
void STM32446DMA2_stream5_cr_tcie(uint8_t bool)
{
	dma_setreg(&DMA2_Stream5->CR, 1, 4, bool);
}
void STM32446DMA2_stream5_cr_htie(uint8_t bool)
{
	dma_setreg(&DMA2_Stream5->CR, 1, 3, bool);
}
void STM32446DMA2_stream5_cr_teie(uint8_t bool)
{
	dma_setreg(&DMA2_Stream5->CR, 1, 2, bool);
}
void STM32446DMA2_stream5_cr_dmeie(uint8_t bool)
{
	dma_setreg(&DMA2_Stream5->CR, 1, 1, bool);
}
void STM32446DMA2_stream5_cr_en(uint8_t bool)
{
	dma_setreg(&DMA2_Stream5->CR, 1, 0, bool);
}
/*** Inic DMA2 STREAM5 CR ***/
STM32446DMA_STREAM_cr stm32446_dma2_stream5_cr_inic(void)
{
	STM32446DMA_STREAM_cr stm32446_dma_stream_cr;
	// CR
	stm32446_dma_stream_cr.chsel = STM32446DMA2_stream5_cr_chsel;
	stm32446_dma_stream_cr.mburst = STM32446DMA2_stream5_cr_mburst;
	stm32446_dma_stream_cr.pburst = STM32446DMA2_stream5_cr_pburst;
	stm32446_dma_stream_cr.ct = STM32446DMA2_stream5_cr_ct;
	stm32446_dma_stream_cr.dbm = STM32446DMA2_stream5_cr_dbm;
	stm32446_dma_stream_cr.pl = STM32446DMA2_stream5_cr_pl;
	stm32446_dma_stream_cr.pincos = STM32446DMA2_stream5_cr_pincos;
	stm32446_dma_stream_cr.msize = STM32446DMA2_stream5_cr_msize;
	stm32446_dma_stream_cr.psize = STM32446DMA2_stream5_cr_psize;
	stm32446_dma_stream_cr.minc = STM32446DMA2_stream5_cr_minc;
	stm32446_dma_stream_cr.pinc = STM32446DMA2_stream5_cr_pinc;
	stm32446_dma_stream_cr.circ = STM32446DMA2_stream5_cr_circ;
	stm32446_dma_stream_cr.dir = STM32446DMA2_stream5_cr_dir;
	stm32446_dma_stream_cr.pfctrl = STM32446DMA2_stream5_cr_pfctrl;
	stm32446_dma_stream_cr.tcie = STM32446DMA2_stream5_cr_tcie;
	stm32446_dma_stream_cr.htie = STM32446DMA2_stream5_cr_htie;
	stm32446_dma_stream_cr.teie = STM32446DMA2_stream5_cr_teie;
	stm32446_dma_stream_cr.dmeie = STM32446DMA2_stream5_cr_dmeie;
	stm32446_dma_stream_cr.en = STM32446DMA2_stream5_cr_en;
	return stm32446_dma_stream_cr;
}
/*** Inic DMA2 STREAM5 Function ***/
void stm32446_dma2_stream5_ndt(uint16_t value)
{
	DMA2_Stream5->NDTR = value;
}
void stm32446_dma2_stream5_par(volatile long unsigned int periferal_addr)
{
	DMA2_Stream5->PAR = periferal_addr;
}
void stm32446_dma2_stream5_m0a(volatile long unsigned int mem0_addr)
{
	DMA2_Stream5->M0AR = mem0_addr;
}
void stm32446_dma2_stream5_m1a(volatile long unsigned int mem1_addr)
{
	DMA2_Stream5->M1AR = mem1_addr;
}
// DMA2 STREAM6 CR
void STM32446DMA2_stream6_cr_chsel(uint8_t value)
{
	dma_setreg(&DMA2_Stream6->CR, 3, 25, value);
}
void STM32446DMA2_stream6_cr_mburst(uint8_t value)
{
	dma_setreg(&DMA2_Stream6->CR, 2, 23, value);
}
void STM32446DMA2_stream6_cr_pburst(uint8_t value)
{
	dma_setreg(&DMA2_Stream6->CR, 2, 21, value);
}
void STM32446DMA2_stream6_cr_ct(uint8_t bool)
{
	dma_setreg(&DMA2_Stream6->CR, 1, 19, bool);
}
void STM32446DMA2_stream6_cr_dbm(uint8_t bool)
{
	dma_setreg(&DMA2_Stream6->CR, 1, 18, bool);
}
void STM32446DMA2_stream6_cr_pl(uint8_t value)
{
	dma_setreg(&DMA2_Stream6->CR, 2, 16, value);
}
void STM32446DMA2_stream6_cr_pincos(uint8_t bool)
{
	dma_setreg(&DMA2_Stream6->CR, 1, 15, bool);
}
void STM32446DMA2_stream6_cr_msize(uint8_t value)
{
	dma_setreg(&DMA2_Stream6->CR, 2, 13, value);
}
void STM32446DMA2_stream6_cr_psize(uint8_t value)
{
	dma_setreg(&DMA2_Stream6->CR, 2, 11, value);
}
void STM32446DMA2_stream6_cr_minc(uint8_t bool)
{
	dma_setreg(&DMA2_Stream6->CR, 1, 10, bool);
}
void STM32446DMA2_stream6_cr_pinc(uint8_t bool)
{
	dma_setreg(&DMA2_Stream6->CR, 1, 9, bool);
}
void STM32446DMA2_stream6_cr_circ(uint8_t bool)
{
	dma_setreg(&DMA2_Stream6->CR, 1, 8, bool);
}
void STM32446DMA2_stream6_cr_dir(uint8_t value)
{
	dma_setreg(&DMA2_Stream6->CR, 2, 7, value);
}
void STM32446DMA2_stream6_cr_pfctrl(uint8_t bool)
{
	dma_setreg(&DMA2_Stream6->CR, 1, 5, bool);
}
void STM32446DMA2_stream6_cr_tcie(uint8_t bool)
{
	dma_setreg(&DMA2_Stream6->CR, 1, 4, bool);
}
void STM32446DMA2_stream6_cr_htie(uint8_t bool)
{
	dma_setreg(&DMA2_Stream6->CR, 1, 3, bool);
}
void STM32446DMA2_stream6_cr_teie(uint8_t bool)
{
	dma_setreg(&DMA2_Stream6->CR, 1, 2, bool);
}
void STM32446DMA2_stream6_cr_dmeie(uint8_t bool)
{
	dma_setreg(&DMA2_Stream6->CR, 1, 1, bool);
}
void STM32446DMA2_stream6_cr_en(uint8_t bool)
{
	dma_setreg(&DMA2_Stream6->CR, 1, 0, bool);
}
/*** Inic DMA2 STREAM6 CR ***/
STM32446DMA_STREAM_cr stm32446_dma2_stream6_cr_inic(void)
{
	STM32446DMA_STREAM_cr stm32446_dma_stream_cr;
	// CR
	stm32446_dma_stream_cr.chsel = STM32446DMA2_stream6_cr_chsel;
	stm32446_dma_stream_cr.mburst = STM32446DMA2_stream6_cr_mburst;
	stm32446_dma_stream_cr.pburst = STM32446DMA2_stream6_cr_pburst;
	stm32446_dma_stream_cr.ct = STM32446DMA2_stream6_cr_ct;
	stm32446_dma_stream_cr.dbm = STM32446DMA2_stream6_cr_dbm;
	stm32446_dma_stream_cr.pl = STM32446DMA2_stream6_cr_pl;
	stm32446_dma_stream_cr.pincos = STM32446DMA2_stream6_cr_pincos;
	stm32446_dma_stream_cr.msize = STM32446DMA2_stream6_cr_msize;
	stm32446_dma_stream_cr.psize = STM32446DMA2_stream6_cr_psize;
	stm32446_dma_stream_cr.minc = STM32446DMA2_stream6_cr_minc;
	stm32446_dma_stream_cr.pinc = STM32446DMA2_stream6_cr_pinc;
	stm32446_dma_stream_cr.circ = STM32446DMA2_stream6_cr_circ;
	stm32446_dma_stream_cr.dir = STM32446DMA2_stream6_cr_dir;
	stm32446_dma_stream_cr.pfctrl = STM32446DMA2_stream6_cr_pfctrl;
	stm32446_dma_stream_cr.tcie = STM32446DMA2_stream6_cr_tcie;
	stm32446_dma_stream_cr.htie = STM32446DMA2_stream6_cr_htie;
	stm32446_dma_stream_cr.teie = STM32446DMA2_stream6_cr_teie;
	stm32446_dma_stream_cr.dmeie = STM32446DMA2_stream6_cr_dmeie;
	stm32446_dma_stream_cr.en = STM32446DMA2_stream6_cr_en;
	return stm32446_dma_stream_cr;
}
/*** Inic DMA2 STREAM6 Function ***/
void stm32446_dma2_stream6_ndt(uint16_t value)
{
	DMA2_Stream6->NDTR = value;
}
void stm32446_dma2_stream6_par(volatile long unsigned int periferal_addr)
{
	DMA2_Stream6->PAR = periferal_addr;
}
void stm32446_dma2_stream6_m0a(volatile long unsigned int mem0_addr)
{
	DMA2_Stream6->M0AR = mem0_addr;
}
void stm32446_dma2_stream6_m1a(volatile long unsigned int mem1_addr)
{
	DMA2_Stream6->M1AR = mem1_addr;
}
// DMA2 STREAM7 CR
void STM32446DMA2_stream7_cr_chsel(uint8_t value)
{
	dma_setreg(&DMA2_Stream7->CR, 3, 25, value);
}
void STM32446DMA2_stream7_cr_mburst(uint8_t value)
{
	dma_setreg(&DMA2_Stream7->CR, 2, 23, value);
}
void STM32446DMA2_stream7_cr_pburst(uint8_t value)
{
	dma_setreg(&DMA2_Stream7->CR, 2, 21, value);
}
void STM32446DMA2_stream7_cr_ct(uint8_t bool)
{
	dma_setreg(&DMA2_Stream7->CR, 1, 19, bool);
}
void STM32446DMA2_stream7_cr_dbm(uint8_t bool)
{
	dma_setreg(&DMA2_Stream7->CR, 1, 18, bool);
}
void STM32446DMA2_stream7_cr_pl(uint8_t value)
{
	dma_setreg(&DMA2_Stream7->CR, 2, 16, value);
}
void STM32446DMA2_stream7_cr_pincos(uint8_t bool)
{
	dma_setreg(&DMA2_Stream7->CR, 1, 15, bool);
}
void STM32446DMA2_stream7_cr_msize(uint8_t value)
{
	dma_setreg(&DMA2_Stream7->CR, 2, 13, value);
}
void STM32446DMA2_stream7_cr_psize(uint8_t value)
{
	dma_setreg(&DMA2_Stream7->CR, 2, 11, value);
}
void STM32446DMA2_stream7_cr_minc(uint8_t bool)
{
	dma_setreg(&DMA2_Stream7->CR, 1, 10, bool);
}
void STM32446DMA2_stream7_cr_pinc(uint8_t bool)
{
	dma_setreg(&DMA2_Stream7->CR, 1, 9, bool);
}
void STM32446DMA2_stream7_cr_circ(uint8_t bool)
{
	dma_setreg(&DMA2_Stream7->CR, 1, 8, bool);
}
void STM32446DMA2_stream7_cr_dir(uint8_t value)
{
	dma_setreg(&DMA2_Stream7->CR, 2, 7, value);
}
void STM32446DMA2_stream7_cr_pfctrl(uint8_t bool)
{
	dma_setreg(&DMA2_Stream7->CR, 1, 5, bool);
}
void STM32446DMA2_stream7_cr_tcie(uint8_t bool)
{
	dma_setreg(&DMA2_Stream7->CR, 1, 4, bool);
}
void STM32446DMA2_stream7_cr_htie(uint8_t bool)
{
	dma_setreg(&DMA2_Stream7->CR, 1, 3, bool);
}
void STM32446DMA2_stream7_cr_teie(uint8_t bool)
{
	dma_setreg(&DMA2_Stream7->CR, 1, 2, bool);
}
void STM32446DMA2_stream7_cr_dmeie(uint8_t bool)
{
	dma_setreg(&DMA2_Stream7->CR, 1, 1, bool);
}
void STM32446DMA2_stream7_cr_en(uint8_t bool)
{
	dma_setreg(&DMA2_Stream7->CR, 1, 0, bool);
}
/*** Inic DMA2 STREAM7 CR ***/
STM32446DMA_STREAM_cr stm32446_dma2_stream7_cr_inic(void)
{
	STM32446DMA_STREAM_cr stm32446_dma_stream_cr;
	// CR
	stm32446_dma_stream_cr.chsel = STM32446DMA2_stream7_cr_chsel;
	stm32446_dma_stream_cr.mburst = STM32446DMA2_stream7_cr_mburst;
	stm32446_dma_stream_cr.pburst = STM32446DMA2_stream7_cr_pburst;
	stm32446_dma_stream_cr.ct = STM32446DMA2_stream7_cr_ct;
	stm32446_dma_stream_cr.dbm = STM32446DMA2_stream7_cr_dbm;
	stm32446_dma_stream_cr.pl = STM32446DMA2_stream7_cr_pl;
	stm32446_dma_stream_cr.pincos = STM32446DMA2_stream7_cr_pincos;
	stm32446_dma_stream_cr.msize = STM32446DMA2_stream7_cr_msize;
	stm32446_dma_stream_cr.psize = STM32446DMA2_stream7_cr_psize;
	stm32446_dma_stream_cr.minc = STM32446DMA2_stream7_cr_minc;
	stm32446_dma_stream_cr.pinc = STM32446DMA2_stream7_cr_pinc;
	stm32446_dma_stream_cr.circ = STM32446DMA2_stream7_cr_circ;
	stm32446_dma_stream_cr.dir = STM32446DMA2_stream7_cr_dir;
	stm32446_dma_stream_cr.pfctrl = STM32446DMA2_stream7_cr_pfctrl;
	stm32446_dma_stream_cr.tcie = STM32446DMA2_stream7_cr_tcie;
	stm32446_dma_stream_cr.htie = STM32446DMA2_stream7_cr_htie;
	stm32446_dma_stream_cr.teie = STM32446DMA2_stream7_cr_teie;
	stm32446_dma_stream_cr.dmeie = STM32446DMA2_stream7_cr_dmeie;
	stm32446_dma_stream_cr.en = STM32446DMA2_stream7_cr_en;
	return stm32446_dma_stream_cr;
}
/*** Inic DMA2 STREAM7 Function ***/
void stm32446_dma2_stream7_ndt(uint16_t value)
{
	DMA2_Stream7->NDTR = value;
}
void stm32446_dma2_stream7_par(volatile long unsigned int periferal_addr)
{
	DMA2_Stream7->PAR = periferal_addr;
}
void stm32446_dma2_stream7_m0a(volatile long unsigned int mem0_addr)
{
	DMA2_Stream7->M0AR = mem0_addr;
}
void stm32446_dma2_stream7_m1a(volatile long unsigned int mem1_addr)
{
	DMA2_Stream7->M1AR = mem1_addr;
}
// DMA2 STREAM0 FCR
void STM32446DMA2_stream0_fcr_feie(uint8_t bool)
{
	dma_setreg(&DMA2_Stream0->FCR, 1, 7, bool);
}
void STM32446DMA2_stream0_fcr_fs(uint8_t value)
{
	dma_setreg(&DMA2_Stream0->FCR, 3, 3, value);
}
void STM32446DMA2_stream0_fcr_dmdis(uint8_t bool)
{
	dma_setreg(&DMA2_Stream0->FCR, 1, 2, bool);
}
void STM32446DMA2_stream0_fcr_fth(uint8_t value)
{
	dma_setreg(&DMA2_Stream0->FCR, 2, 0, value);
}
/*** Inic DMA2 STREAM0 FCR ***/
STM32446DMA_STREAM_fcr stm32446_dma2_stream0_fcr_inic(void)
{
	STM32446DMA_STREAM_fcr stm32446_dma_stream_fcr;
	// FCR
	stm32446_dma_stream_fcr.feie = STM32446DMA2_stream0_fcr_feie;
	stm32446_dma_stream_fcr.fs = STM32446DMA2_stream0_fcr_fs;
	stm32446_dma_stream_fcr.dmdis = STM32446DMA2_stream0_fcr_dmdis;
	stm32446_dma_stream_fcr.fth = STM32446DMA2_stream0_fcr_fth;
	return stm32446_dma_stream_fcr;
}
// DMA2 STREAM1 FCR
void STM32446DMA2_stream1_fcr_feie(uint8_t bool)
{
	dma_setreg(&DMA2_Stream1->FCR, 1, 7, bool);
}
void STM32446DMA2_stream1_fcr_fs(uint8_t value)
{
	dma_setreg(&DMA2_Stream1->FCR, 3, 3, value);
}
void STM32446DMA2_stream1_fcr_dmdis(uint8_t bool)
{
	dma_setreg(&DMA2_Stream1->FCR, 1, 2, bool);
}
void STM32446DMA2_stream1_fcr_fth(uint8_t value)
{
	dma_setreg(&DMA2_Stream1->FCR, 2, 0, value);
}
/*** Inic DMA2 STREAM1 FCR ***/
STM32446DMA_STREAM_fcr stm32446_dma2_stream1_fcr_inic(void)
{
	STM32446DMA_STREAM_fcr stm32446_dma_stream_fcr;
	// FCR
	stm32446_dma_stream_fcr.feie = STM32446DMA2_stream1_fcr_feie;
	stm32446_dma_stream_fcr.fs = STM32446DMA2_stream1_fcr_fs;
	stm32446_dma_stream_fcr.dmdis = STM32446DMA2_stream1_fcr_dmdis;
	stm32446_dma_stream_fcr.fth = STM32446DMA2_stream1_fcr_fth;
	return stm32446_dma_stream_fcr;
}
// DMA2 STREAM2 FCR
void STM32446DMA2_stream2_fcr_feie(uint8_t bool)
{
	dma_setreg(&DMA2_Stream2->FCR, 1, 7, bool);
}
void STM32446DMA2_stream2_fcr_fs(uint8_t value)
{
	dma_setreg(&DMA2_Stream2->FCR, 3, 3, value);
}
void STM32446DMA2_stream2_fcr_dmdis(uint8_t bool)
{
	dma_setreg(&DMA2_Stream2->FCR, 1, 2, bool);
}
void STM32446DMA2_stream2_fcr_fth(uint8_t value)
{
	dma_setreg(&DMA2_Stream2->FCR, 2, 0, value);
}
/*** Inic DMA2 STREAM2 FCR ***/
STM32446DMA_STREAM_fcr stm32446_dma2_stream2_fcr_inic(void)
{
	STM32446DMA_STREAM_fcr stm32446_dma_stream_fcr;
	// FCR
	stm32446_dma_stream_fcr.feie = STM32446DMA2_stream2_fcr_feie;
	stm32446_dma_stream_fcr.fs = STM32446DMA2_stream2_fcr_fs;
	stm32446_dma_stream_fcr.dmdis = STM32446DMA2_stream2_fcr_dmdis;
	stm32446_dma_stream_fcr.fth = STM32446DMA2_stream2_fcr_fth;
	return stm32446_dma_stream_fcr;
}
// DMA2 STREAM3 FCR
void STM32446DMA2_stream3_fcr_feie(uint8_t bool)
{
	dma_setreg(&DMA2_Stream3->FCR, 1, 7, bool);
}
void STM32446DMA2_stream3_fcr_fs(uint8_t value)
{
	dma_setreg(&DMA2_Stream3->FCR, 3, 3, value);
}
void STM32446DMA2_stream3_fcr_dmdis(uint8_t bool)
{
	dma_setreg(&DMA2_Stream3->FCR, 1, 2, bool);
}
void STM32446DMA2_stream3_fcr_fth(uint8_t value)
{
	dma_setreg(&DMA2_Stream3->FCR, 2, 0, value);
}
/*** Inic DMA2 STREAM3 FCR ***/
STM32446DMA_STREAM_fcr stm32446_dma2_stream3_fcr_inic(void)
{
	STM32446DMA_STREAM_fcr stm32446_dma_stream_fcr;
	// FCR
	stm32446_dma_stream_fcr.feie = STM32446DMA2_stream3_fcr_feie;
	stm32446_dma_stream_fcr.fs = STM32446DMA2_stream3_fcr_fs;
	stm32446_dma_stream_fcr.dmdis = STM32446DMA2_stream3_fcr_dmdis;
	stm32446_dma_stream_fcr.fth = STM32446DMA2_stream3_fcr_fth;
	return stm32446_dma_stream_fcr;
}
// DMA1 STREAM4 FCR
void STM32446DMA2_stream4_fcr_feie(uint8_t bool)
{
	dma_setreg(&DMA2_Stream4->FCR, 1, 7, bool);
}
void STM32446DMA2_stream4_fcr_fs(uint8_t value)
{
	dma_setreg(&DMA2_Stream4->FCR, 3, 3, value);
}
void STM32446DMA2_stream4_fcr_dmdis(uint8_t bool)
{
	dma_setreg(&DMA2_Stream4->FCR, 1, 2, bool);
}
void STM32446DMA2_stream4_fcr_fth(uint8_t value)
{
	dma_setreg(&DMA2_Stream4->FCR, 2, 0, value);
}
/*** Inic DMA2 STREAM4 FCR ***/
STM32446DMA_STREAM_fcr stm32446_dma2_stream4_fcr_inic(void)
{
	STM32446DMA_STREAM_fcr stm32446_dma_stream_fcr;
	// FCR
	stm32446_dma_stream_fcr.feie = STM32446DMA2_stream4_fcr_feie;
	stm32446_dma_stream_fcr.fs = STM32446DMA2_stream4_fcr_fs;
	stm32446_dma_stream_fcr.dmdis = STM32446DMA2_stream4_fcr_dmdis;
	stm32446_dma_stream_fcr.fth = STM32446DMA2_stream4_fcr_fth;
	return stm32446_dma_stream_fcr;
}
// DMA1 STREAM5 FCR
void STM32446DMA2_stream5_fcr_feie(uint8_t bool)
{
	dma_setreg(&DMA2_Stream5->FCR, 1, 7, bool);
}
void STM32446DMA2_stream5_fcr_fs(uint8_t value)
{
	dma_setreg(&DMA2_Stream5->FCR, 3, 3, value);
}
void STM32446DMA2_stream5_fcr_dmdis(uint8_t bool)
{
	dma_setreg(&DMA2_Stream5->FCR, 1, 2, bool);
}
void STM32446DMA2_stream5_fcr_fth(uint8_t value)
{
	dma_setreg(&DMA2_Stream5->FCR, 2, 0, value);
}
/*** Inic DMA2 STREAM5 FCR ***/
STM32446DMA_STREAM_fcr stm32446_dma2_stream5_fcr_inic(void)
{
	STM32446DMA_STREAM_fcr stm32446_dma_stream_fcr;
	// FCR
	stm32446_dma_stream_fcr.feie = STM32446DMA2_stream5_fcr_feie;
	stm32446_dma_stream_fcr.fs = STM32446DMA2_stream5_fcr_fs;
	stm32446_dma_stream_fcr.dmdis = STM32446DMA2_stream5_fcr_dmdis;
	stm32446_dma_stream_fcr.fth = STM32446DMA2_stream5_fcr_fth;
	return stm32446_dma_stream_fcr;
}
// DMA1 STREAM6 FCR
void STM32446DMA2_stream6_fcr_feie(uint8_t bool)
{
	dma_setreg(&DMA2_Stream6->FCR, 1, 7, bool);
}
void STM32446DMA2_stream6_fcr_fs(uint8_t value)
{
	dma_setreg(&DMA2_Stream6->FCR, 3, 3, value);
}
void STM32446DMA2_stream6_fcr_dmdis(uint8_t bool)
{
	dma_setreg(&DMA2_Stream6->FCR, 1, 2, bool);
}
void STM32446DMA2_stream6_fcr_fth(uint8_t value)
{
	dma_setreg(&DMA2_Stream6->FCR, 2, 0, value);
}
/*** Inic DMA2 STREAM6 FCR ***/
STM32446DMA_STREAM_fcr stm32446_dma2_stream6_fcr_inic(void)
{
	STM32446DMA_STREAM_fcr stm32446_dma_stream_fcr;
	// FCR
	stm32446_dma_stream_fcr.feie = STM32446DMA2_stream6_fcr_feie;
	stm32446_dma_stream_fcr.fs = STM32446DMA2_stream6_fcr_fs;
	stm32446_dma_stream_fcr.dmdis = STM32446DMA2_stream6_fcr_dmdis;
	stm32446_dma_stream_fcr.fth = STM32446DMA2_stream6_fcr_fth;
	return stm32446_dma_stream_fcr;
}
// DMA2 STREAM0 FCR
void STM32446DMA2_stream7_fcr_feie(uint8_t bool)
{
	dma_setreg(&DMA2_Stream7->FCR, 1, 7, bool);
}
void STM32446DMA2_stream7_fcr_fs(uint8_t value)
{
	dma_setreg(&DMA2_Stream7->FCR, 3, 3, value);
}
void STM32446DMA2_stream7_fcr_dmdis(uint8_t bool)
{
	dma_setreg(&DMA2_Stream7->FCR, 1, 2, bool);
}
void STM32446DMA2_stream7_fcr_fth(uint8_t value)
{
	dma_setreg(&DMA2_Stream7->FCR, 2, 0, value);
}
/*** Inic DMA2 STREAM7 FCR ***/
STM32446DMA_STREAM_fcr stm32446_dma2_stream7_fcr_inic(void)
{
	STM32446DMA_STREAM_fcr stm32446_dma_stream_fcr;
	// FCR
	stm32446_dma_stream_fcr.feie = STM32446DMA2_stream7_fcr_feie;
	stm32446_dma_stream_fcr.fs = STM32446DMA2_stream7_fcr_fs;
	stm32446_dma_stream_fcr.dmdis = STM32446DMA2_stream7_fcr_dmdis;
	stm32446_dma_stream_fcr.fth = STM32446DMA2_stream7_fcr_fth;
	return stm32446_dma_stream_fcr;
}
/*** FUNC ***/
void dma2_circ_cfg(volatile long unsigned int* p_addr, volatile long unsigned int* m_addr, uint8_t stream_n, uint8_t channel_n, uint16_t quant_d, uint8_t p_size, uint8_t m_size, uint8_t priority, uint8_t dir)
{
	// Filter to Default
	if(stream_n > 7){ stream_n = 0;}
	if(channel_n > 7){ channel_n = 0;}
	if(quant_d > 65535){ quant_d = 1;}
	if(p_size > 2){ p_size = 0;}
	if(m_size > 2){ m_size = 0;}
	if(priority > 3){ priority = 0;}
	if( p_addr && m_addr ){
		/*** Verify Ready for Parameter ***/
		dma_setreg(&(DMA2_Stream0 + stream_n)->CR, 1, 0, 0);
		for(time_out = 200; dma_readreg((DMA2_Stream0 + stream_n)->CR, 1, 0) && time_out; time_out--);
		/*** Parameter Configure ***/
		(DMA2_Stream0 + stream_n)->PAR = (volatile long unsigned int) p_addr;
		(DMA2_Stream0 + stream_n)->M0AR = (volatile long unsigned int) m_addr;
		dma_setreg(&(DMA2_Stream0 + stream_n)->CR, 1, 5, 0); // 0 -> dma, 1 -> peri
		dma_setreg(&(DMA2_Stream0 + stream_n)->CR, 3, 25, channel_n); // channel
		(DMA2_Stream0 + stream_n)->NDTR = quant_d; //
		dma_setreg(&(DMA2_Stream0 + stream_n)->CR, 2, 13, m_size); // msize 2 -> 32bit
		dma_setreg(&(DMA2_Stream0 + stream_n)->CR, 2, 11, p_size); // psize 1 -> 16bit
		dma_setreg(&(DMA2_Stream0 + stream_n)->CR, 2, 16, priority); // priority
		if(dir){
			dma_setreg(&(DMA2_Stream0 + stream_n)->CR, 2, 6, 1); // DIR
			dma_setreg(&(DMA2_Stream0 + stream_n)->CR, 1, 9, 1); // PINC
			dma_setreg(&(DMA2_Stream0 + stream_n)->CR, 1, 10, 0); // MINC
		}else{
			dma_setreg(&(DMA2_Stream0 + stream_n)->CR, 2, 6, 0); // DIR
			dma_setreg(&(DMA2_Stream0 + stream_n)->CR, 1, 9, 0); // PINC
			dma_setreg(&(DMA2_Stream0 + stream_n)->CR, 1, 10, 1); // MINC
		}
		dma_setreg(&(DMA2_Stream0 + stream_n)->CR, 1, 8, 1); // CIRC
		dma_setreg(&(DMA2_Stream0 + stream_n)->CR, 1, 0, 1); // ENABLE
	}
}
/*** Inic FUNC ***/
STM32446DMA_func stm32446_dma2_func_inic(void)
{
	STM32446DMA_func stm32446_dma_func;

	stm32446_dma_func.circ_cfg = dma2_circ_cfg;

	return stm32446_dma_func;
}
/****************************************************/
/**** DMA2 INIC Procedure & Function Definition *****/
/****************************************************/
STM32446DMA2obj dma2_inic(void)
{
	STM32446DMA2obj stm32446_dma;
	stm32446_dma.reg = DMA2;
	stm32446_dma.stream[0].reg = DMA2_Stream0;
	/*** DMA2 Bit Mapping Link ***/
	stm32446_dma.sr = stm32446_dma2_sr_inic();
	stm32446_dma.stream[0].cr = stm32446_dma2_stream0_cr_inic();
	stm32446_dma.stream[0].fcr = stm32446_dma2_stream0_fcr_inic();
	stm32446_dma.stream[0].ndt = stm32446_dma2_stream0_ndt;
	stm32446_dma.stream[0].par = stm32446_dma2_stream0_par;
	stm32446_dma.stream[0].m0a = stm32446_dma2_stream0_m0a;
	stm32446_dma.stream[0].m1a = stm32446_dma2_stream0_m1a;
	stm32446_dma.stream[1].cr = stm32446_dma2_stream1_cr_inic();
	stm32446_dma.stream[1].fcr = stm32446_dma2_stream1_fcr_inic();
	stm32446_dma.stream[1].ndt = stm32446_dma2_stream1_ndt;
	stm32446_dma.stream[1].par = stm32446_dma2_stream1_par;
	stm32446_dma.stream[1].m0a = stm32446_dma2_stream1_m0a;
	stm32446_dma.stream[1].m1a = stm32446_dma2_stream1_m1a;
	stm32446_dma.stream[2].cr = stm32446_dma2_stream2_cr_inic();
	stm32446_dma.stream[2].fcr = stm32446_dma2_stream2_fcr_inic();
	stm32446_dma.stream[2].ndt = stm32446_dma2_stream2_ndt;
	stm32446_dma.stream[2].par = stm32446_dma2_stream2_par;
	stm32446_dma.stream[2].m0a = stm32446_dma2_stream2_m0a;
	stm32446_dma.stream[2].m1a = stm32446_dma2_stream2_m1a;
	stm32446_dma.stream[3].cr = stm32446_dma2_stream3_cr_inic();
	stm32446_dma.stream[3].fcr = stm32446_dma2_stream3_fcr_inic();
	stm32446_dma.stream[3].ndt = stm32446_dma2_stream3_ndt;
	stm32446_dma.stream[3].par = stm32446_dma2_stream3_par;
	stm32446_dma.stream[3].m0a = stm32446_dma2_stream3_m0a;
	stm32446_dma.stream[3].m1a = stm32446_dma2_stream3_m1a;
	stm32446_dma.stream[4].cr = stm32446_dma2_stream4_cr_inic();
	stm32446_dma.stream[4].fcr = stm32446_dma2_stream4_fcr_inic();
	stm32446_dma.stream[4].ndt = stm32446_dma2_stream4_ndt;
	stm32446_dma.stream[4].par = stm32446_dma2_stream4_par;
	stm32446_dma.stream[4].m0a = stm32446_dma2_stream4_m0a;
	stm32446_dma.stream[4].m1a = stm32446_dma2_stream4_m1a;
	stm32446_dma.stream[5].cr = stm32446_dma2_stream5_cr_inic();
	stm32446_dma.stream[5].fcr = stm32446_dma2_stream5_fcr_inic();
	stm32446_dma.stream[5].ndt = stm32446_dma2_stream5_ndt;
	stm32446_dma.stream[5].par = stm32446_dma2_stream5_par;
	stm32446_dma.stream[5].m0a = stm32446_dma2_stream5_m0a;
	stm32446_dma.stream[5].m1a = stm32446_dma2_stream5_m1a;
	stm32446_dma.stream[6].cr = stm32446_dma2_stream6_cr_inic();
	stm32446_dma.stream[6].fcr = stm32446_dma2_stream6_fcr_inic();
	stm32446_dma.stream[6].ndt = stm32446_dma2_stream6_ndt;
	stm32446_dma.stream[6].par = stm32446_dma2_stream6_par;
	stm32446_dma.stream[6].m0a = stm32446_dma2_stream6_m0a;
	stm32446_dma.stream[6].m1a = stm32446_dma2_stream6_m1a;
	stm32446_dma.stream[7].cr = stm32446_dma2_stream7_cr_inic();
	stm32446_dma.stream[7].fcr = stm32446_dma2_stream7_fcr_inic();
	stm32446_dma.stream[7].ndt = stm32446_dma2_stream7_ndt;
	stm32446_dma.stream[7].par = stm32446_dma2_stream7_par;
	stm32446_dma.stream[7].m0a = stm32446_dma2_stream7_m0a;
	stm32446_dma.stream[7].m1a = stm32446_dma2_stream7_m1a;
	/*** Other ***/
	stm32446_dma.func = stm32446_dma2_func_inic();
	stm32446_dma.clock = STM32446Dma2Clock;
	return stm32446_dma;
}
/*********************************************/
/*** File Procedure & Function Definition ***/
/********************************************/
uint32_t dma_readreg(uint32_t reg, uint32_t size_block, uint32_t bit)
{
	if(bit > 31){ bit = 0;} if(size_block > 32){ size_block = 32;}
	uint32_t value = reg;
	uint32_t mask = (unsigned int)((1 << size_block) - 1);
	value &= (mask << bit);
	value = (value >> bit);
	return value;
}
void dma_writereg(volatile uint32_t* reg, uint32_t size_block, uint32_t bit, uint32_t data)
{
	if(bit > 31){ bit = 0;} if(size_block > 32){ size_block = 32;}
	uint32_t value = data;
	uint32_t mask = (unsigned int)((1 << size_block) - 1);
	value &= mask;
	value = (value << bit);
	*reg = value;
}
void dma_setreg(volatile uint32_t* reg, uint32_t size_block, uint32_t bit, uint32_t data)
{
	if(bit > 31){ bit = 0;} if(size_block > 32){ size_block = 32;}
	uint32_t value = data;
	uint32_t mask = (unsigned int)((1 << size_block) - 1);
	value &= mask;
	*reg &= ~(mask << bit);
	*reg |= (value << bit);
}
void dma_setbit(volatile uint32_t* reg, uint32_t size_block, uint32_t bit, uint32_t data)
{
	uint32_t n = 0;
	if(bit > 31){ n = bit/32; bit = bit - (n * 32); } if(size_block > 32){ size_block = 32;}
	uint32_t value = data;
	uint32_t mask = (unsigned int)((1 << size_block) - 1);
	value &= mask;
	*(reg + n ) &= ~(mask << bit);
	*(reg + n ) |= (value << bit);
}
uint32_t dma_getsetbit(volatile uint32_t* reg, uint32_t size_block, uint32_t bit)
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


