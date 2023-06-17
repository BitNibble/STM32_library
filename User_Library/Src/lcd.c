/*************************************************************************
	LCD
Author: Sergio Santos 
	<sergio.salazar.santos@gmail.com>
License: GNU General Public License
Hardware: STM32
Date: 28052023
Comment:
	STM32F446RE
	- Make sure the delay are working in the inic function.
************************************************************************/
/*** File Library ***/
#include "lcd.h"

/*** File Constant & Macro ***/
// CMD RS
#define INST 0
#define DATA 1
#define LCDCMDMASK ((1 << RS) | (1 << RW) | (1 << EN))

/*** File Variable ***/
static STM32446 stm;
static GPIO_TypeDef* ireg;
static uint32_t lcd0_detect;

/*** File Header ***/
void LCD0_inic(void);
void LCD0_write(char c, unsigned short D_I);
char LCD0_read(unsigned short D_I);
void LCD0_BF(void);
void LCD0_putch(char c);
char LCD0_getch(void);
void LCD0_string(const char* s); // RAW
void LCD0_string_size(const char* s, uint32_t size); // RAW
void LCD0_hspace(uint32_t n);
void LCD0_clear(void);
void LCD0_gotoxy(unsigned int y, unsigned int x);
void LCD0_reboot(void);
// Common
void LCD0_strobe(void);
void lcd_setpin( GPIO_TypeDef* reg, int pin );
void lcd_resetpin( GPIO_TypeDef* reg, int pin );
uint32_t lcd_readreg(uint32_t reg, uint32_t size_block, uint32_t bit);
void lcd_writereg(volatile uint32_t* reg, uint32_t size_block, uint32_t bit, uint32_t data);
void lcd_setreg(volatile uint32_t* reg, uint32_t size_block, uint32_t bit, uint32_t data);
void lcd_setbit(volatile uint32_t* reg, uint32_t size_block, uint32_t bit, uint32_t data);
uint32_t lcd_getsetbit(volatile uint32_t* reg, uint32_t size_block, uint32_t bit);

/*** LCD0 Procedure & Function Definition ***/
LCD0 LCD0enable(GPIO_TypeDef* reg)
{
	// ALLOCACAO MEMORIA PARA Estrutura
	LCD0 lcd0;
	stm = STM32446enable();

	// LOCAL VARIABLES
	// import parameters
	ireg = reg;
	// initialize variables
	// Direccionar apontadores para PROTOTIPOS
	lcd0.write = LCD0_write;
	lcd0.read = LCD0_read;
	lcd0.BF = LCD0_BF;
	lcd0.putch = LCD0_putch;
	lcd0.getch = LCD0_getch;
	lcd0.string = LCD0_string; // RAW
	lcd0.string_size = LCD0_string_size; // RAW
	lcd0.hspace = LCD0_hspace;
	lcd0.clear = LCD0_clear;
	lcd0.gotoxy = LCD0_gotoxy;
	lcd0.reboot = LCD0_reboot;
	// LCD INIC
	LCD0_inic();
	
	return lcd0;
}

void LCD0_inic(void)
{
	// uint8_t repeat;
	// LCD INIC
	ireg->MODER &= (uint32_t) ~((3 << (RS * 2)) | (3 << (RW * 2)) | (3 << (EN * 2))); // control pins as output
	ireg->MODER |= ((1 << (RS * 2)) | (1 << (RW * 2)) | (1 << (EN * 2))); // control pins as output
	
	ireg->PUPDR &= (uint32_t) ~((3 << (DB4 * 2)) | (3 << (DB5 * 2)) | (3 << (DB6 * 2)) | (3 << (DB7 * 2))); // enable pull up resistors
	ireg->PUPDR |= ((1 << (DB4 * 2)) | (1 << (DB5 * 2)) | (1 << (DB6 * 2)) | (1 << (DB7 * 2))); // enable pull up resistors

	ireg->MODER &= (uint32_t) ~(3 << (NC * 2)); // reboot detect input
	
	ireg->PUPDR &= (uint32_t) ~(3 << (NC * 2)); // pull up resistors
	ireg->PUPDR |= (1 << (NC * 2)); // pull up resistors

	ireg->OSPEEDR &= (uint32_t) ~( (3 << (RS * 2)) | (3 << (RW * 2)) | (3 << (EN * 2)) | (3 << (DB4 * 2)) | (3 << (DB5 * 2)) | (3 << (DB6 * 2)) | (3 << (DB7 * 2)) ); // set speed
	ireg->OSPEEDR |= ( (3 << (RS * 2)) | (3 << (RW * 2)) | (3 << (EN * 2)) | (3 << (DB4 * 2)) | (3 << (DB5 * 2)) | (3 << (DB6 * 2)) | (3 << (DB7 * 2)) ); // set speed
	 
	lcd0_detect = ireg->IDR & (1 << NC);
	
	// INICIALIZACAO LCD datasheet
	stm.systick.delay_ms(20); // using clock at 16Mhz
	LCD0_write(0x38, INST); // function set
	stm.systick.delay_10us(4);
	LCD0_write(0x38, INST); // function set
	stm.systick.delay_10us(10);
	LCD0_write(0x38, INST); // function set
	stm.systick.delay_10us(4);
	LCD0_write(0x28, INST); // function set 2B
	stm.systick.delay_10us(4);
	LCD0_write(0x28, INST); // function set 2B
	stm.systick.delay_10us(4);
	
	// for(repeat = 2 ; repeat ; repeat--){
		// repeat twice in 4 bit length
		LCD0_write(0x28, INST); // function set 2B
		LCD0_BF();
		LCD0_write(0x28, INST); // function set 2B
		LCD0_BF();

		LCD0_write(0x0C, INST); // display on/off control
		LCD0_BF();
		LCD0_write(0x0C, INST); // display on/off control
		LCD0_BF();

		LCD0_write(0x01, INST); // clear display
		LCD0_BF();
		LCD0_write(0x01, INST); // clear display
		LCD0_BF();

		LCD0_write(0x06, INST); // entry mode set (crazy settings)
		LCD0_BF();
		LCD0_write(0x06, INST); // entry mode set (crazy settings)
		LCD0_BF();
	// }
	// INICIALIZATION END
	// LCD0_write(0x1F, INST); // cursor or display shift
	// stm.systick.delay_10us(4);
	// LCD0_write(0x03, INST); // return home
	// stm.systick.delay_ms(10);
	LCD0_gotoxy(0,0);
}
void LCD0_write(char c, unsigned short D_I)
{ // write to LCD
	lcd_resetpin(ireg,RW); // lcd as input
	ireg->MODER &= (uint32_t) ~((3 << (DB4 *2)) | (3 << (DB5* 2)) | (3 << (DB6* 2)) | (3 << (DB7 * 2))); // mcu as output
	ireg->MODER |= ((1 << (DB4 *2)) | (1 << (DB5* 2)) | (1 << (DB6* 2)) | (1 << (DB7 * 2))); // mcu as output
	
	if(D_I) lcd_setpin(ireg, RS); else lcd_resetpin(ireg, RS);
	LCD0_strobe( );
	
	if(c & 0x80) lcd_setpin(ireg,DB7); else lcd_resetpin(ireg,DB7);
	if(c & 0x40) lcd_setpin(ireg,DB6); else lcd_resetpin(ireg,DB6);
	if(c & 0x20) lcd_setpin(ireg,DB5); else lcd_resetpin(ireg,DB5);
	if(c & 0x10) lcd_setpin(ireg,DB4); else lcd_resetpin(ireg,DB4);
	
	if(D_I) lcd_setpin(ireg, RS); else lcd_resetpin(ireg, RS);
	LCD0_strobe( );
	
	if(c & 0x08) lcd_setpin(ireg,DB7); else lcd_resetpin(ireg,DB7);
	if(c & 0x04) lcd_setpin(ireg,DB6); else lcd_resetpin(ireg,DB6);
	if(c & 0x02) lcd_setpin(ireg,DB5); else lcd_resetpin(ireg,DB5);
	if(c & 0x01) lcd_setpin(ireg,DB4); else lcd_resetpin(ireg,DB4);
	
	lcd_resetpin(ireg, EN);
}

char LCD0_read(unsigned short D_I)
{ // Read from LCD
	uint32_t data = 0;
	uint8_t c = 0;
	ireg->MODER &= (uint32_t) ~((3 << (DB4 * 2)) | (3 << (DB5 * 2)) | (3 << (DB6 * 2)) | (3 << (DB7 * 2))); // mcu as input
	lcd_setpin(ireg, RW); // lcd as output
	
	if(D_I) lcd_setpin(ireg, RS); else lcd_resetpin(ireg, RS);
	LCD0_strobe( );
	data = ireg->IDR; // read data
	
	if(data & (1 << DB7)) c |= 1 << 7; else c &= ~(1 << 7);
	if(data & (1 << DB6)) c |= 1 << 6; else c &= ~(1 << 6);
	if(data & (1 << DB5)) c |= 1 << 5; else c &= ~(1 << 5);
	if(data & (1 << DB4)) c |= 1 << 4; else c &= ~(1 << 4);
	
	if(D_I) lcd_setpin(ireg, RS); else lcd_resetpin(ireg, RS);
	LCD0_strobe( );
	data = ireg->IDR; // read data

	if(data & (1 << DB7)) c |= 1 << 3; else c &= ~(1 << 3);
	if(data & (1 << DB6)) c |= 1 << 2; else c &= ~(1 << 2);
	if(data & (1 << DB5)) c |= 1 << 1; else c &= ~(1 << 1);
	if(data & (1 << DB4)) c |= 1 << 0; else c &= ~(1 << 0);
	
	lcd_resetpin(ireg, EN);

	return c;
}

void LCD0_BF(void)
//	It has to read at minimum one equal and exit
//	immediately if not equal, weird property.
{
	uint8_t i;
	char inst = 0x80;
	for(i=0; 0x80 & inst; i++){
		inst = LCD0_read(INST);
		if(i > 10) // 1
			break;
	}
}

char LCD0_getch(void)
{
	char c;
	c = LCD0_read(DATA);
	LCD0_BF();
	return c;
}

void LCD0_putch(char c)
{
	LCD0_write(c, DATA);
	LCD0_BF();
}

void LCD0_string(const char* s)
{
	char tmp;
	while(*s){
		tmp = *(s++);
		LCD0_putch(tmp);
	}
}

void LCD0_string_size(const char* s, uint32_t size)
{
	char tmp;
	uint32_t pos = 0;
	while(*s){
		tmp=*(s++);
		pos++;
		if(pos > size) // 1 TO SIZE+1
			break;
		LCD0_putch(tmp);
	}
	while(pos < size){ // TO SIZE
		LCD0_putch(' ');
		pos++;
	}
}

void LCD0_hspace(uint32_t n)
{
	for(; n; n--){
		LCD0_putch(' ');
	}
}

void LCD0_clear(void)
{
	LCD0_write(0x01, INST);
	stm.systick.delay_ms(2);
}

void LCD0_gotoxy(unsigned int y, unsigned int x)
{
	switch(y){
		case 0:
			LCD0_write((char)(0x80 + x), INST);
			LCD0_BF();
		break;
		case 1:
			LCD0_write((char)(0xC0 + x), INST);
			LCD0_BF();
		break;
		case 2:
			LCD0_write((char)(0x94 + x), INST); // 0x94
			LCD0_BF();
		break;
		case 3:
			LCD0_write((char)(0xD4 + x), INST); // 0xD4
			LCD0_BF();
		break;
		default:
		break;
	}
}

void LCD0_strobe(void)
{
	lcd_resetpin(ireg, EN);
	lcd_setpin(ireg, EN);
}

void LCD0_reboot(void)
{
	// low high detect pin NC
	uint32_t i;
	uint32_t tmp;
	tmp = ireg->IDR & (1 << NC);
	i = tmp ^ lcd0_detect;
	i &= tmp;
	if(i)
		LCD0_inic();
	lcd0_detect = tmp;
}

/*** COMMON ***/
void lcd_setpin( GPIO_TypeDef* reg, int pin )
{
	reg->BSRR = (1 << pin);
}

void lcd_resetpin( GPIO_TypeDef* reg, int pin )
{
	reg->BSRR = (unsigned int)((1 << pin) << 16);
}

uint32_t lcd_readreg(uint32_t reg, uint32_t size_block, uint32_t bit)
{
	if(bit > 31){ bit = 0;} if(size_block > 32){ size_block = 32;}
	uint32_t value = reg;
	uint32_t mask = (unsigned int)((1 << size_block) - 1);
	value &= (mask << bit);
	value = (value >> bit);
	return value;
}

void lcd_writereg(volatile uint32_t* reg, uint32_t size_block, uint32_t bit, uint32_t data)
{
	if(bit > 31){ bit = 0;} if(size_block > 32){ size_block = 32;}
	uint32_t value = data;
	uint32_t mask = (unsigned int)((1 << size_block) - 1);
	value &= mask;
	value = (value << bit);
	*reg = value;
}

void lcd_setreg(volatile uint32_t* reg, uint32_t size_block, uint32_t bit, uint32_t data)
{
	if(bit > 31){ bit = 0;} if(size_block > 32){ size_block = 32;}
	uint32_t value = data;
	uint32_t mask = (unsigned int)((1 << size_block) - 1);
	value &= mask;
	*reg &= ~(mask << bit);
	*reg |= (value << bit);
}

void lcd_setbit(volatile uint32_t* reg, uint32_t size_block, uint32_t bit, uint32_t data)
{
	uint32_t n = 0;
	if(bit > 31){ n = bit/32; bit = bit - (n * 32); } if(size_block > 32){ size_block = 32;}
	uint32_t value = data;
	uint32_t mask = (unsigned int)((1 << size_block) - 1);
	value &= mask;
	*(reg + n ) &= ~(mask << bit);
	*(reg + n ) |= (value << bit);
}

uint32_t lcd_getsetbit(volatile uint32_t* reg, uint32_t size_block, uint32_t bit)
{
	uint32_t n = 0;
	if(bit > 31){ n = bit/32; bit = bit - (n * 32); } if(size_block > 32){ size_block = 32;}
	uint32_t value = *(reg + n );
	uint32_t mask = (unsigned int)((1 << size_block) - 1);
	value &= (mask << bit);
	value = (value >> bit);
	return value;
}

/*** File Interrupt ***/
/******************************************************************************
void LCD0_BF(void)
//	It has to read at minimum one equal and exit
//	immediately if not equal, weird property.
{
	for( ; 0x80 & LCD0_read(INST) ; );
}

void LCD0_BF(void)
//	It has to read at minimum one equal and exit
//	immediately if not equal, weird property.
{
	uint8_t i;
	char inst = 0x80;
	for(i=0; 0x80 & inst; i++){
		inst = LCD0_read(INST);
		if(i > 3)
			break;
	}
}
*******************************************************************************/

/*** File Interrupt ***/

/***EOF***/


