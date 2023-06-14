/******************************************************************************
	CIRCBUFFER
Author: Sergio Santos
	<sergio.salazar.santos@gmail.com>
License: GNU General Public License
Hardware: all
Date: 15062023
Comment:
	Circular Buffer
*******************************************************************************/
#ifndef _CIRCBUFFER_H_
	#define _CIRCBUFFER_H_

/*** File Library ***/
#include <inttypes.h>

/*** CIRCBUFFER par TypeDef ***/
typedef struct
{
	char* tail;
	char* head;
	char* orig;
	char* end;
}CIRCBUFFER_par;

/*** CIRCBUFFER TypeDef ***/
struct circ_buf_template
{
	CIRCBUFFER_par par;
	uint8_t (*get)(CIRCBUFFER_par* par);
	void (*put)(CIRCBUFFER_par* par, char data);
	void (*putstr)(CIRCBUFFER_par* par, const char* str);
	void (*getstr)(CIRCBUFFER_par* par, char* str);
};
typedef struct circ_buf_template circbuff;

circbuff CIRCBUFFenable(uint8_t size_buff, char* buff);

#endif

/***EOF***/

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


