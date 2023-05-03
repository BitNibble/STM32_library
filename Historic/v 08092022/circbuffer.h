/******************************************************************************
	CIRCBUFFER
Author: Sergio Santos
	<sergio.salazar.santos@gmail.com>
License: GNU General Public License
Hardware: all
Date: 07092022
Comment:
	Circular Buffer
*******************************************************************************/
#ifndef _CIRCBUFFER_H_
	#define _CIRCBUFFER_H_
/***Library***/
#include <inttypes.h>
/***Constant & Macro***/
/***Global Variable***/
struct circ_buf_template
{
	uint8_t* tail;
	uint8_t* head;
	uint8_t* buff;
	uint8_t* orig;
	uint8_t* end;
	uint8_t (*get)(struct circ_buf_template* circ);
	void (*put)(struct circ_buf_template* circ, uint8_t data);
	void (*putstr)(struct circ_buf_template* circ, const char* str);
	void (*getstr)(struct circ_buf_template* circ, uint8_t* str);
} ;
typedef struct circ_buf_template circbuff;
/***Header***/
circbuff CIRCBUFFenable(uint8_t size_buff, uint8_t* buff);
#endif
/********************************Comment***************************************
*******************************************************************************/
/***EOF***/

