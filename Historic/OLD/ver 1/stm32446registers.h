/************************************************************************
	STM32 446 REGISTERS
Author: Sergio Manuel Santos
	<sergio.salazar.santos@gmail.com>
License: GNU General Public License
Hardware: STM32-446
Date: anytime
Comment:
	Stable.
************************************************************************/
#ifndef _STM32446REGISTERS_H_
	#define _STM32446REGISTERS_H_
	
#include <inttypes.h>

/***** STM32 F446 START *****/

// General-purpose Registers (GPR)
typedef struct
{
	uint32_t r0;
	uint32_t r1;
	uint32_t r2;
	uint32_t r3;
	uint32_t r4;
	uint32_t r5;
	uint32_t r6;
	uint32_t r7;
	uint32_t r8;
	uint32_t r9;
	uint32_t r10;
	uint32_t r11;
	uint32_t r12;
}STM32446Gpr;

// Processor Core Registers (PCR)
typedef struct
{
	uint32_t sp;
	uint32_t lr;
	uint32_t pc;
	uint32_t psr;
	uint32_t primask;
	uint32_t faultmask;
	uint32_t basepri;
	uint32_t control;
}STM32446Pcr;

// Memory protection unit (MPU)
typedef struct
{
	uint32_t typer;
	uint32_t ctrl;
	uint32_t rnr;
	uint32_t rbar;
	uint32_t rasr;
	uint32_t rbara1;
	uint32_t rasra1;
	uint32_t rbara2;
	uint32_t rasra2;
	uint32_t rbara3;
	uint32_t rasra3;
}STM32446Mpu;

/**
// System Control Block (SCB)
typedef struct
{ // 0xE000 E008
	uint32_t actrl; // 0xE000E008
	uint32_t fill1[829]; // ((0xE000ED00 - 0xE000E008) / 4)  - 1
	uint32_t cpuid; // 0xE000ED00
	uint32_t icsr; // 0xE000ED04
	uint32_t vtor; // 0xE000ED08
	uint32_t aircr; // 0xE000ED0C
	uint32_t scr; // 0xE000ED10
	uint32_t ccr; // 0xE000ED14
	uint32_t shpr1; // 0xE000ED18
	uint32_t shpr2; // 0xE000ED1C
	uint32_t shpr3; // 0xE000ED20
	uint32_t shcsr; // 0xE000ED24
	uint32_t cfsr; // 0xE000ED28
	uint32_t hfsr; // 0xE000ED2C
	uint32_t fill2; // ((0xE000ED34 - 0xE000ED2C) / 4)  - 1
	uint32_t mmar; // 0xE000ED34
	uint32_t bfar; // 0xE000ED38
	uint32_t afsr; // 0xE000ED3C
}STM32446Scb;
**/

/**
// Floating Point Unit (FPU)
typedef struct
{ // 0xE000 ED00
	uint32_t fill[34];
	uint32_t cpacr; // 0xE000ED88
	uint32_t fill[106]; // ((0xE000EF34 - 0xE000ED88) / 4)  - 1
	uint32_t fpccr; // 0xE000EF34
	uint32_t fpcar; // 0xE000EF38
	uint32_t fpdscr; // 0xE000EF3C
}STM32446Fpu;
**/

/******MANUAL RM0390******/

// 3 - Embedded Flash memory interface (FLASH) 0x4002 3C00 - 0x4002 3FFF pg87
typedef struct
{ // 0x4002 3C00
	uint32_t acr;
	uint32_t keyr; // KEY1 = 0x45670123, KEY2 = 0xCDEF89AB to access FLASH_CR
	uint32_t optkeyr;
	uint32_t sr;
	uint32_t cr;
	uint32_t optcr; // Reset value: 0x0FFF AAED
	uint32_t optcr1;
}STM32446Flash;

// 4 - CRC calculation unit (CRC) 0x4002 3000 - 0x4002 33FF pg91
typedef struct
{ // 0x4002 3000
	uint32_t dr;
	uint32_t idr;
	uint32_t cr;
}STM32446Crc;

// 5 - Power controller (PWR) 0x4000 7000 - 0x4000 73FF pg115
typedef struct
{ // 0x4000 7000
	uint32_t cr;
	uint32_t csr;
}STM32446Pwr;

// 6 - Reset and clock control (RCC) 0x4002 3800 - 0x4002 3BFF pg172
typedef struct
{ // 0x4002 3800
	uint32_t cr;
	uint32_t pllcfgr;
	uint32_t cfgr;
	uint32_t cir;
	uint32_t ahb1rstr;
	uint32_t ahb2rstr;
	uint32_t ahb3rstr;
	uint32_t fill1;
	uint32_t apb1rstr;
	uint32_t apb2rstr;
	uint32_t fill2[2];
	uint32_t ahb1enr;
	uint32_t ahb2enr;
	uint32_t ahb3enr;
	uint32_t fill3;
	uint32_t apb1enr;
	uint32_t apb2enr;
	uint32_t fill4[2];
	uint32_t ahb1lpenr;
	uint32_t ahb2lpenr;
	uint32_t ahb3lpenr;
	uint32_t fill5;
	uint32_t apb1lpenr;
	uint32_t apb2lpenr;
	uint32_t fill6[2];
	uint32_t bdcr;
	uint32_t csr;
	uint32_t fill7[2];
	uint32_t sscgr;
	uint32_t plli2scfgr;
	uint32_t dckcfgr;
  uint32_t ckgatenr;
  uint32_t dckcfgr2;
}STM32446Rcc;

// 7 - General-purpose I/Os (GPIO) pg193
typedef struct
{
	uint32_t moder;
	uint32_t otyper;
	uint32_t ospeedr;
	uint32_t pupdr;
	uint32_t idr;
	uint32_t odr;
	uint32_t bsrr;
	uint32_t lckr;
	uint32_t afrl;
	uint32_t ofrh;
}STM32446Gpio;

// 8 - System configuration controller (SYSCFG) 0x4001 3800 - 0x4001 3BFF pg202
typedef struct
{ // 0x4001 3800
	uint32_t memrmp;
	uint32_t pmc;
	uint32_t exticr1;
	uint32_t exticr2;
	uint32_t exticr3;
	uint32_t exticr4;
	uint32_t fill[2];
	uint32_t cmpcr;
	uint32_t fill2[2];
  uint32_t cfgr;    
}STM32446SysCfg;

// 9 - Direct memory access controller (DMA) DMA Stream pg235
typedef struct
{
	uint32_t scr;
	uint32_t sndtr;
	uint32_t spar;
	uint32_t sm0ar;
	uint32_t sm1ar;
	uint32_t sfcr;
}STM32446Dmastream;

// 9 - Direct memory access controller (DMA) DMA1 controller (DMA1) 0x4002 6000 - 0x4002 63FF pg235
typedef struct
{ // 0x4002 6000
	uint32_t lisr;
	uint32_t hisr;
	uint32_t lifcr;
	uint32_t hifcr;
	STM32446Dmastream stream[8];
}STM32446Dma1;

// 9 - Direct memory access controller (DMA) DMA2 controller (DMA2)  0x4002 6400 - 0x4002 67FF pg235
typedef struct
{ // 0x4002 6400
	uint32_t lisr;
	uint32_t hisr;
	uint32_t lifcr;
	uint32_t hifcr;
	STM32446Dmastream stream[8];
}STM32446Dma2;

// 10 - Interrupts and events pg250
// Nested Vectored Interrupt Controller (NVIC)
typedef struct
{ // 0xE000E100
	uint32_t iser[8]; // ((0xE000E11F - 0xE000E100) / 4) + 1
	uint32_t fill1[24]; // ((0XE000E180 - 0xE000E11F) / 4)
	uint32_t icer[8]; // ((0XE000E19F - 0xE000E180) / 4) + 1
	uint32_t fill2[24]; // ((0XE000E200 - 0xE000E19F) / 4)
	uint32_t ispr[8]; // ((0XE000E21F - 0xE000E200) / 4) + 1
	uint32_t fill3[24]; // ((0XE000E280 - 0xE000E21F) / 4)
	uint32_t icpr[8]; // ((0XE000E29F - 0xE000E280) / 4) + 1
	uint32_t fill4[24]; // ((0XE000E300 - 0xE000E29F) / 4)
	uint32_t iabr[8]; // ((0xE000E31F - 0xE000E300) / 4) + 1
	uint32_t fill5[56]; // ((0XE000E400 - 0xE000E31F) / 4)
	uint32_t ipr[60]; // ((0xE000E4EF - 0xE000E400)) + 1
	uint32_t fill6[644]; // ((0xE000EF00 - 0xE000E4EF) / 4)
	uint32_t stir; // 0xE000EF00
}STM32446Nvic;

// SysTick Timer (STK)
typedef struct
{ // 0xE000 E010
	uint32_t ctrl; // 0xE000E010 , 0 - enable, 1 - tickint, 2 - slksource, 16 - countflag
	uint32_t load; // 0xE000E014
	uint32_t val; // 0xE000E018
	uint32_t calib; // 0xE000E01C
}STM32446Systick;

// Interrupts and events (EXTI) 0x4001 3C00 - 0x4001 3FFF pg250
typedef struct
{ // 0x4001 3C00
	uint32_t imr;
	uint32_t emr;
	uint32_t rtsr;
	uint32_t ftsr;
	uint32_t swier;
	uint32_t pr;
}STM32446Exti;

// 11 - Flexible memory controller (FMC) pg323
typedef struct
{
	uint32_t bcr[4];
	uint32_t btr[4];
	uint32_t bwtr[4];
	uint32_t pcr;
	uint32_t sr;
	uint32_t pmem;
	uint32_t patt;
	uint32_t eccr;
	uint32_t sdcr[2];
	uint32_t sdtr[2];
	uint32_t sdcmr;
	uint32_t sdrtr;
	uint32_t sdsr;
}STM32446Fmc;

// 12 - Quad-SPI interface (QUADSPI) pg354

// 13 - Analog-to-digital converter (ADC) 0x4001 2000 - 0x4001 23FF pg399
typedef struct
{ // 0x4001 2000 2100 2200
	uint32_t sr;
	uint32_t cr1;
	uint32_t cr2;
	uint32_t smpr1;
	uint32_t smpr2;
	uint32_t jofr1;
	uint32_t jofr2;
	uint32_t jofr3;
	uint32_t jofr4;
	uint32_t htr;
	uint32_t ltr;
	uint32_t sqr1;
	uint32_t sqr2;
	uint32_t sqr3;
	uint32_t jsqr;
	uint32_t jdr1;
	uint32_t jdr2;
	uint32_t jdr3;
	uint32_t jdr4;
	uint32_t dr;
}STM32446Adc;

typedef struct
{
  uint32_t csr;
  uint32_t ccr;
  uint32_t cdr;
}STM32446AdcCommon;

// 14 - Digital-to-analog converter (DAC) pg423

typedef struct
{
  uint32_t cr;
  uint32_t swtrigr;
  uint32_t dhr12r1;
  uint32_t dhr12l1;
  uint32_t dhr8r1;
  uint32_t dhr12r2;
  uint32_t dhr12l2;
  uint32_t dhr8r2;
  uint32_t dhr12rd;
  uint32_t dhr12ld;
  uint32_t dhr8rd;
  uint32_t dor1;
  uint32_t dor2;
  uint32_t sr;
} STM32446Dac;

// 15 - Digital camera interface (DCMI) pg447

typedef struct
{
  uint32_t cr;
  uint32_t sr;
  uint32_t risr;
  uint32_t ier;
  uint32_t misr;
  uint32_t icr;
  uint32_t escr;
  uint32_t esur;
  uint32_t cwstrtr;
  uint32_t cwsizer;
  uint32_t dr;
} STM32446Dcmi;

// 16 - Advanced-control timers (TIM1&TIM8) 0x4001 0000 - 0x4001 03FF pg518
typedef struct STM32446Tim1{ // 0x4001 0000
	uint32_t cr1;
	uint32_t cr2;
	uint32_t smcr;
	uint32_t dier;
	uint32_t sr;
	uint32_t egr;
	uint32_t ccmr1;
	uint32_t ccmr2;
	uint32_t ccer;
	uint32_t cnt;
	uint32_t psc;
	uint32_t arr;
	uint32_t rcr;
	uint32_t ccr1;
	uint32_t ccr2;
	uint32_t ccr3;
	uint32_t ccr4;
	uint32_t bdtr;
	uint32_t dcr;
	uint32_t dmar;
}STM32446Tim1;

// 17 - General-purpose timers (TIM2 to TIM5) 0x4000 0000 - 0x4000 03FF pg579
typedef struct STM32446Tim2{ // 0x4000 0000
	uint32_t cr1;
	uint32_t cr2;
	uint32_t smcr;
	uint32_t dier;
	uint32_t sr;
	uint32_t egr;
	uint32_t ccmr1;
	uint32_t ccmr2;
	uint32_t ccer1;
	uint32_t cnt;
	uint32_t psc;
	uint32_t arr;
	uint32_t fill1;
	uint32_t ccr1;
	uint32_t ccr2;
	uint32_t ccr3;
	uint32_t ccr4;
	uint32_t fill2;
	uint32_t dcr;
	uint32_t dmar;
	uint32_t or;
}STM32446Tim2;

// 17 - Advanced-control timer (TIM3) 0x4000 0400 - 0x4000 07FF pg364
typedef struct STM32446Tim3{ // 0x4000 0400
	uint32_t cr1;
	uint32_t cr2;
	uint32_t smcr;
	uint32_t dier;
	uint32_t sr;
	uint32_t egr;
	uint32_t ccmr1;
	uint32_t ccmr2;
	uint32_t ccer1;
	uint32_t cnt;
	uint32_t psc;
	uint32_t arr;
	uint32_t fill1;
	uint32_t ccr1;
	uint32_t ccr2;
	uint32_t ccr3;
	uint32_t ccr4;
	uint32_t fill2;
	uint32_t dcr;
	uint32_t dmar;
}STM32446Tim3;

// 17 - Advanced-control timer (TIM4) 0x4000 0800 - 0x4000 0BFF pg364
typedef struct STM32446Tim4{ // 0x4000 0800
	uint32_t cr1;
	uint32_t cr2;
	uint32_t smcr;
	uint32_t dier;
	uint32_t sr;
	uint32_t egr;
	uint32_t ccmr1;
	uint32_t ccmr2;
	uint32_t ccer;
	uint32_t cnt;
	uint32_t psc;
	uint32_t arr;
	uint32_t fill1;
	uint32_t ccr1;
	uint32_t ccr2;
	uint32_t ccr3;
	uint32_t ccr4;
	uint32_t fill2;
	uint32_t dcr;
	uint32_t dmar;
}STM32446Tim4;

// 17 - Advanced-control timer (TIM5) 0x4000 0C00 - 0x4000 0FFF pg364
typedef struct STM32446Tim5{ // 0x4000 0C00
	uint32_t cr1;
	uint32_t cr2;
	uint32_t smcr;
	uint32_t dier;
	uint32_t sr;
	uint32_t egr;
	uint32_t ccmr1;
	uint32_t ccmr2;
	uint32_t ccer;
	uint32_t cnt;
	uint32_t psc;
	uint32_t arr;
	uint32_t fill1;
	uint32_t ccr1;
	uint32_t ccr2;
	uint32_t ccr3;
	uint32_t ccr4;
	uint32_t fill2;
	uint32_t dcr;
	uint32_t dmar;
	uint32_t or;
}STM32446Tim5;

// 18 - General-purpose timers (TIM9 to TIM14) 0x4001 4000 - 0x4001 43FF pg615 pg626
typedef struct
{ // 0x4001 4000
	uint32_t cr1;
	uint32_t fill1;
	uint32_t smcr;
	uint32_t dier;
	uint32_t sr;
	uint32_t egr;
	uint32_t ccmr1;
	uint32_t fill2;
	uint32_t ccer;
	uint32_t cnt;
	uint32_t psc;
	uint32_t arr;
	uint32_t fill3;
	uint32_t ccr1;
	uint32_t ccr2;
	uint32_t fill4;
	uint32_t fill5;
	uint32_t fill6;
	uint32_t fill7;
	uint32_t fill8;
	uint32_t fill9;
}STM32446Tim9;

// 18 - Advanced-control timer (TIM10) 0x4001 4400 - 0x4001 47FF pg408
typedef struct STM32446Tim10{ // 0x4001 4400
	uint32_t cr1;
	uint32_t fill1;
	uint32_t fill2;
	uint32_t fill3;
	uint32_t sr;
	uint32_t egr;
	uint32_t ccmr1;
	uint32_t fill4;
	uint32_t ccer;
	uint32_t cnt;
	uint32_t psc;
	uint32_t arr;
	uint32_t fill5;
	uint32_t ccr1;
	uint32_t fill6;
	uint32_t fill7;
	uint32_t fill8;
	uint32_t fill9;
	uint32_t fill10;
	uint32_t fill11;
	uint32_t or;
}STM32446Tim10;

// 18 - Advanced-control timer (TIM11) 0x4001 4800 - 0x4001 4BFF pg408
typedef struct STM32446Tim11{ // 0x4001 4800
	uint32_t cr1;
	uint32_t fill1;
	uint32_t fill2;
	uint32_t fill3;
	uint32_t sr;
	uint32_t egr;
	uint32_t ccmr1;
	uint32_t fill4;
	uint32_t ccer;
	uint32_t cnt;
	uint32_t psc;
	uint32_t arr;
	uint32_t fill5;
	uint32_t ccr1;
	uint32_t fill6;
	uint32_t fill7;
	uint32_t fill8;
	uint32_t fill9;
	uint32_t fill10;
	uint32_t fill11;
	uint32_t or;
}STM32446Tim11;

// 19 - Basic timers (TIM6&TIM7) pg639

// 20 - Independent watchdog (IWDG) 0x4000 3000 - 0x4000 33FF pg645
typedef struct STM32446Iwdg{ // 0x4000 3000
	uint32_t kr;
	uint32_t pr;
	uint32_t rlr;
	uint32_t sr;
}STM32446IWdg;

// 21 - Window watchdog (WWDG) 0x4000 2C00 - 0x4000 2FFF pg652
typedef struct STM32446Wwdg{ // 0x4000 2C00
	uint32_t cr;
	uint32_t cfr;
	uint32_t sr;
}STM32446WWdg;

// 22 - Real-time clock (RTC) 0x4000 2800 - 0x4000 2BFF pg690
typedef struct STM32446Rtc{ // 0x4000 2800
	uint32_t tr;
	uint32_t dr;
	uint32_t cr;
	uint32_t isr;
	uint32_t prer;
	uint32_t wutr;
	uint32_t calibr;
	uint32_t alrmar;
	uint32_t alrmbr;
	uint32_t wpr;
	uint32_t ssr;
	uint32_t shiftr;
	uint32_t tstr;
	uint32_t tsdr;
	uint32_t tsssr;
	uint32_t calr;
	uint32_t tafcr;
	uint32_t alrmassr;
	uint32_t alrmbssr;
	uint32_t fill;
	uint32_t bkpr[20];
}STM32446Rtc;

// 23 - Fast-mode Plus Inter-integrated circuit (FMPI2C) interface pg757

// 24 - Inter-integrated circuit interface (I2C1) 0x4000 5400 - 0x4000 57FF pg793
typedef struct
{ // 0x4000 5400
	uint32_t cr1;
	uint32_t cr2;
	uint32_t oar1;
	uint32_t oar2;
	uint32_t dr;
	uint32_t sr1;
	uint32_t sr2;
	uint32_t ccr;
	uint32_t trise;
	uint32_t fltr;
}STM32446I2c1;

// 24 - Inter-integrated circuit interface (I2C2) 0x4000 5800 - 0x4000 5BFF pg793
typedef struct
{ // 0x4000 5800
	uint32_t cr1;
	uint32_t cr2;
	uint32_t oar1;
	uint32_t oar2;
	uint32_t dr;
	uint32_t sr1;
	uint32_t sr2;
	uint32_t ccr;
	uint32_t trise;
	uint32_t fltr;
}STM32446I2c2;

// 24 - Inter-integrated circuit interface (I2C3)  0x4000 5C00 - 0x4000 5FFF pg793
typedef struct
{ // 0x4000 5C00
	uint32_t cr1;
	uint32_t cr2;
	uint32_t oar1;
	uint32_t oar2;
	uint32_t dr;
	uint32_t sr1;
	uint32_t sr2;
	uint32_t ccr;
	uint32_t trise;
	uint32_t fltr;
}STM32446I2c3;

// 25 - Universal synchronous asynchronous receiver transmitter (USART1) 0x4001 1000 - 0x4001 13FF pg845
typedef struct
{ // 0x4001 1000
	uint32_t sr;
	uint32_t dr;
	uint32_t brr;
	uint32_t cr1;
	uint32_t cr2;
	uint32_t cr3;
	uint32_t gtpr;
}STM32446Usart;

// 26 - Serial peripheral interface/ inter-IC sound (SPI/I2S) 0x4001 3000 - 0x4001 33FF pg896
typedef struct STM32446Spi1i2s1{ // 0x4001 3000
	uint32_t cr1;
	uint32_t cr2;
	uint32_t sr;
	uint32_t dr;
	uint32_t crcpr;
	uint32_t rxcrcr;
	uint32_t txcrcr;
	uint32_t i2scfgr;
	uint32_t i2spr;
}STM32446Spi1i2s1;

// 26 - Inter-integrated circuit interface (I2S2ext)  0x4000 3400 - 0x4000 37FF pg896
typedef struct STM32446I2s2ext{ // 0x4000 3400
	uint32_t cr1;
	uint32_t cr2;
	uint32_t sr;
	uint32_t dr;
	uint32_t crcpr;
	uint32_t rxcrcr;
	uint32_t txcrcr;
	uint32_t i2scfgr;
	uint32_t i2spr;
}STM32446I2s2ext;

// 26 - Serial peripheral interface (SPI2/I2S2) 0x4000 3800 - 0x4000 3BFF pg896
typedef struct STM32446Spi2i2s2{ // 0x4000 3800
	uint32_t cr1;
	uint32_t cr2;
	uint32_t sr;
	uint32_t dr;
	uint32_t crcpr;
	uint32_t rxcrcr;
	uint32_t txcrcr;
	uint32_t i2scfgr;
	uint32_t i2spr;
}STM32446Spi2i2s2;

// 26 - Serial peripheral interface (SPI3/I2S3) 0x4000 3C00 - 0x4000 3FFF pg896
typedef struct STM32446Spi3i2s3{ // 0x4000 3C00
	uint32_t cr1;
	uint32_t cr2;
	uint32_t sr;
	uint32_t dr;
	uint32_t crcpr;
	uint32_t rxcrcr;
	uint32_t txcrcr;
	uint32_t i2scfgr;
	uint32_t i2spr;
}STM32446Spi3i2s3;

// 26 - Inter-integrated circuit interface (I2S3ext)  0x4000 4000 - 0x4000 43FF pg896
typedef struct STM32446I2s3ext{ // 0x4000 4000
	uint32_t cr1;
	uint32_t cr2;
	uint32_t sr;
	uint32_t dr;
	uint32_t crcpr;
	uint32_t rxcrcr;
	uint32_t txcrcr;
	uint32_t i2scfgr;
	uint32_t i2spr;
}STM32446I2s3ext;

// 26 - Serial peripheral interface (SPI4/I2S4) 0x4001 3400 - 0x4001 37FF pg896
typedef struct STM32446Spi4i2s4{ // 0x4001 3400
	uint32_t cr1;
	uint32_t cr2;
	uint32_t sr;
	uint32_t dr;
	uint32_t crcpr;
	uint32_t rxcrcr;
	uint32_t txcrcr;
	uint32_t i2scfgr;
	uint32_t i2spr;
}STM32446Spi4i2s4;

// 26 - Serial peripheral interface (SPI5/I2S5) 0x4001 5000 - 0x4001 53FFF pg896
typedef struct STM32446Spi5i2s5{ // 0x4001 5000
	uint32_t cr1;
	uint32_t cr2;
	uint32_t sr;
	uint32_t dr;
	uint32_t crcpr;
	uint32_t rxcrcr;
	uint32_t txcrcr;
	uint32_t i2scfgr;
	uint32_t i2spr;
}STM32446Spi5i2s5;

// 27 - SPDIF receiver interface (SPDIFRX) pg931

// 28 - Serial audio interface (SAI) pg985

// 29 - Secure digital input/output interface (SDIO) 0x4001 2C00 - 0x4001 2FFF pg1044
typedef struct
{ // 0x4001 2C00
	uint32_t power;
	uint32_t clkcr;
	uint32_t arg;
	uint32_t cmd;
	uint32_t respcmd;
	uint32_t resp1;
	uint32_t resp2;
	uint32_t resp3;
	uint32_t resp4;
	uint32_t dtimer;
	uint32_t dlen;
	uint32_t dctrl;
	uint32_t dcount;
	uint32_t sta;
	uint32_t icr;
	uint32_t mask;
	uint32_t fill1[2]; // ((ADDRafter - ADDRbefore) / 4) - 1
	uint32_t fifocnt;
	uint32_t fill2[13]; // ((ADDRafter - ADDRbefore) / 4) - 1
	uint32_t fifo;
}STM32446SDio;

// 30 - Controller area network (bxCAN) pg1086

// 31 - USB on-the-go full-speed (OTG_FS) 0x5000 0000 - 0x5003 FFFF pg1205

// 32 - HDMI-CEC controller (CEC) pg1300
typedef struct
{
  uint32_t cr;
  uint32_t cfgr;
  uint32_t txdr;
  uint32_t rxdr;
  uint32_t isr;
  uint32_t ier;
}STM32446Cec;

// 33 - Debug support (DBG) pg1333
typedef struct
{ // 0xE004 2000
	uint32_t idcode; // Address: 0xE004 2000
	uint32_t cr; // Address: 0xE004 2004
	uint32_t apb1fz; // Address : 0xE004 2008
	uint32_t apb2fz; // Address: 0xE004 200C
}STM32446DbgMcu;

// 34 - Device electronic signature pg
typedef struct
{ // Base address: 0x1FFF 7A10
	uint32_t uid[3];
}STM32446DeviceId;

typedef struct
{ // Base address: 0x1FFF 7A22
	uint32_t fsize;
}STM32446FlashSize;

// 35 - Revision history

/************/

// TPIU (trace port interface unit) pg822
typedef struct
{ // 0xE004 0004
	uint32_t CurrentPortSize; // 0xE0040004
	uint32_t fill1[58]; // ((0xE00400F0 - 0xE0040004) / 4) - 1
	uint32_t SelectedPinProtocol; // 0xE00400F0
	uint32_t fill2[131]; // ((0xE0040300 - 0xE00400F0) / 4) - 1
	uint32_t FormatterAndFlushStatus; // 0xE0040300
	uint32_t FormatterAndFlushControl; // 0xE0040304
}STM32446TPiu;

/******MANUAL RM0390******/


/***** STM32 F446 END *****/
#endif

