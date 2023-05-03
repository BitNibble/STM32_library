/*************************************************************************
	LCD
Author: Sergio Santos 
	<sergio.salazar.santos@gmail.com>
License: GNU General Public License
Hardware: all
Date: 25102020
Comment:
	Tested Atemga128 16Mhz and Atmega328 8Mhz and STM32F446RE
************************************************************************/
/***Library***/
#include "stm32446mapping.h"
#include "lcd.h"
/***Constant & Macro***/
//CMD RS
#define INST 0
#define DATA 1
//ticks depends on CPU frequency this case 16Mhz
#define LCD_N_TICKS 31
#define BIT_N_TICKS 15
#define LCDCMDMASK ((1 << RS) | (1 << RW) | (1 << EN))
/***Global File Variable***/
static STM32446 stm;
static volatile uint32_t *lcd0_DDR;
static volatile uint32_t *lcd0_PUPDR;
static volatile uint32_t *lcd0_PIN;
static volatile uint32_t *lcd0_PORT;
static uint32_t lcd0_detect;
/***Header***/
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
void LCD_ticks(uint32_t num);
/***Procedure & Function***/
LCD0 LCD0enable(volatile uint32_t *ddr, volatile uint32_t *pupdr, volatile uint32_t *pin, volatile uint32_t *port)
{
	//ALLOCAÇÂO MEMORIA PARA Estrutura
	LCD0 lcd0;
	stm = STM32446enable();
	//LOCAL VARIABLES
	//import parameters
	lcd0_DDR = ddr;
	lcd0_PUPDR = pupdr;
	lcd0_PIN = pin;
	lcd0_PORT = port;
	//initialize variables
	//Direccionar apontadores para PROTOTIPOS
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
	//LCD INIC
	LCD0_inic();
	//
	return lcd0;
}
void LCD0_inic(void)
{
	//LCD INIC
	*lcd0_DDR |= ((1 << (RS * 2)) | (1 << (RW * 2)) | (1 << (EN * 2))); // control pins as output
	*lcd0_DDR &= (uint32_t) ~((2 << (RS * 2)) | (2 << (RW * 2)) | (2 << (EN * 2))); // control pins as output
	
	*lcd0_DDR &= (uint32_t) ~(1 << (NC * 2)); // reboot detect input
	*lcd0_DDR &= (uint32_t) ~(2 << (NC * 2)); //reboot detect input
	*lcd0_PUPDR |= (1 << (NC * 2)); // pull up resistors
	*lcd0_PUPDR &= (uint32_t) ~(2 << (NC * 2)); // pull up resistors 
	
	lcd0_detect = *lcd0_PIN & (1 << NC);
	
	/***INICIALIZACAO LCD**datasheet*/
	stm.systick.delay_ms(40);
	LCD0_write(0x33, INST); //function set
	stm.systick.delay_10us(4);
	LCD0_write(0x33, INST); //function set
	stm.systick.delay_10us(4);
	LCD0_write(0x2B, INST); //function set
	stm.systick.delay_10us(4);
	LCD0_write(0x0C, INST);// display on/off control
	stm.systick.delay_10us(4);
	LCD0_write(0x01, INST);// clear display
	stm.systick.delay_ms(2);
	LCD0_write(0x06, INST);// entry mode set (crazy settings)
	stm.systick.delay_10us(4);
	/***INICIALIZATION END***/
	//LCD0_write(0x1F, INST);// cursor or display shift
	//stm.systick.delay_10us(4);
	//LCD0_write(0x03, INST);// return home
	//stm.systick.delay_ms(2);
}
void LCD0_write(char c, unsigned short D_I)
{ // write to LCD
	*lcd0_PORT &= (uint32_t)~(1 << RW); // lcd as input
	
	if(D_I) *lcd0_PORT |= (uint32_t)(1 << RS); else *lcd0_PORT &= (uint32_t)~(1 << RS); 
	
	*lcd0_DDR |= ((1 << (DB4 *2)) | (1 << (DB5* 2)) | (1 << (DB6* 2)) | (1 << (DB7 * 2))); // mcu as output
	*lcd0_DDR &= (uint32_t) ~((2 << (DB4 *2)) | (2 << (DB5* 2)) | (2 << (DB6* 2)) | (2 << (DB7 * 2))); // mcu as output
	
	*lcd0_PUPDR &= (uint32_t) ~((1 << (DB4 * 2)) | (1 << (DB5 * 2)) | (1 << (DB6 * 2)) | (1 << (DB7 * 2))); // disable pull up resistors
	*lcd0_PUPDR &= (uint32_t) ~((2 << (DB4 * 2)) | (2 << (DB5 * 2)) | (2 << (DB6 * 2)) | (2 << (DB7 * 2))); // disable pull up resistors
	
	*lcd0_PORT |= (1 << EN); // lcd enabled
	
	if(c & 0x80) *lcd0_PORT |= (uint32_t) 1 << DB7; else *lcd0_PORT &= (uint32_t) ~(1 << DB7);
	if(c & 0x40) *lcd0_PORT |= (uint32_t) 1 << DB6; else *lcd0_PORT &= (uint32_t) ~(1 << DB6);
	if(c & 0x20) *lcd0_PORT |= (uint32_t) 1 << DB5; else *lcd0_PORT &= (uint32_t) ~(1 << DB5);
	if(c & 0x10) *lcd0_PORT |= (uint32_t) 1 << DB4; else *lcd0_PORT &= (uint32_t) ~(1 << DB4); 
	
	*lcd0_PORT &= (uint32_t) ~(1 << EN); // shift to lcd
	
	// Second nibble
	 
	*lcd0_PORT &= (uint32_t) ~(1 << RW); // lcd as input
	
	if(D_I) *lcd0_PORT |= (uint32_t) (1 << RS); else *lcd0_PORT &= (uint32_t) ~(1 << RS); 
	
	*lcd0_PORT |= (uint32_t)(1 << EN); // lcd enabled
	
	if(c & 0x08) *lcd0_PORT |= (uint32_t) 1 << DB7; else *lcd0_PORT &= (uint32_t) ~(1 << DB7);
	if(c & 0x04) *lcd0_PORT |= (uint32_t) 1 << DB6; else *lcd0_PORT &= (uint32_t) ~(1 << DB6);
	if(c & 0x02) *lcd0_PORT |= (uint32_t) 1 << DB5; else *lcd0_PORT &= (uint32_t) ~(1 << DB5);
	if(c & 0x01) *lcd0_PORT |= (uint32_t) 1 << DB4; else *lcd0_PORT &= (uint32_t) ~(1 << DB4); 
	
	*lcd0_PORT &= (uint32_t) ~(1 << EN); // shift to lcd
}
char LCD0_read(unsigned short D_I)
{ // Read from LCD
	uint32_t data = 0;
	uint8_t c = 0;
	*lcd0_DDR &= (uint32_t) ~((1 << (DB4 * 2)) | (1 << (DB5 * 2)) | (1 << (DB6 * 2)) | (1 << (DB7 * 2))); // mcu as input
	*lcd0_DDR &= (uint32_t) ~((2 << (DB4 * 2)) | (2 << (DB5 * 2)) | (2 << (DB6 * 2)) | (2 << (DB7 * 2))); // mcu as input
	
	*lcd0_PUPDR |= ((1 << (DB4 * 2)) | (1 << (DB5 * 2)) | (1 << (DB6 * 2)) | (1 << (DB7 * 2))); // enable pull up resistors
	*lcd0_PUPDR &= (uint32_t) ~((2 << (DB4 * 2)) | (2 << (DB5 * 2)) | (2 << (DB6 * 2)) | (2 << (DB7 * 2))); // enable pull up resistors 
	
	//First nibble
	*lcd0_PORT |= (1 << RW); // lcd as output
	
	if(D_I) *lcd0_PORT |= (uint32_t) (1 << RS); else *lcd0_PORT &= (uint32_t) ~(1 << RS); 
	
	*lcd0_PORT |= (1 << EN); // lcd enable (shift out)
	data = *lcd0_PIN; // read data 
	*lcd0_PORT &= (uint32_t) ~(1 << EN); // lcd disable
	
	if(data & (1 << DB7)) c |= 1 << 7; else c &= ~(1 << 7);
	if(data & (1 << DB6)) c |= 1 << 6; else c &= ~(1 << 6);
	if(data & (1 << DB5)) c |= 1 << 5; else c &= ~(1 << 5);
	if(data & (1 << DB4)) c |= 1 << 4; else c &= ~(1 << 4);
	
	// Second nibble
	*lcd0_PORT |= (1 << RW); // lcd as output
	
	if(D_I) *lcd0_PORT |= (uint32_t) (1 << RS); else *lcd0_PORT &= (uint32_t) ~(1 << RS); 
	
	*lcd0_PORT |= (1 << EN); // lcd enable (shift out)
	data = *lcd0_PIN; // read data
	*lcd0_PORT &= (uint32_t) ~(1 << EN); // lcd disable
	
	if(data & (1 << DB7)) c |= 1 << 3; else c &= ~(1 << 3);
	if(data & (1 << DB6)) c |= 1 << 2; else c &= ~(1 << 2);
	if(data & (1 << DB5)) c |= 1 << 1; else c &= ~(1 << 1);
	if(data & (1 << DB4)) c |= 1 << 0; else c &= ~(1 << 0);
	
	return c;
}
void LCD0_BF(void)
/***
	It has to read at minimum one equal and exit 
	immediately if not equal, weird property.
***/
{
	uint8_t i;
	char inst = 0x80;
	for(i=0; 0x80 & inst; i++){
		inst = LCD0_read(INST);
		if(i > 1)
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
void LCD0_reboot(void)
{
	//low high detect pin NC
	uint32_t i;
	uint32_t tmp;
	tmp = *lcd0_PIN & (1 << NC);
	i = tmp ^ lcd0_detect;
	i &= tmp;
	if(i)
		LCD0_inic();
	lcd0_detect = tmp;
}
/*************************/
void LCD_ticks(uint32_t num)
{
	uint32_t count;
	for(count = 0; count < num; count++) ;
}
/***Interrupt***/
/***EOF***/

