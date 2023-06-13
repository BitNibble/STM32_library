/******************************************************************************
	BUFFER
Author: Sergio Santos
	<sergio.salazar.santos@gmail.com>
License: GNU General Public License
Hardware: all
Date: 17112022
Comment:
	Circular Buffer
*******************************************************************************/
#ifndef _BUFFER_H_
	#define _BUFFER_H_

/*** File Library ***/
#include <inttypes.h>

/*** File Constant & Macro ***/
#define BUFFvar char

/*** File TypeDef ***/
typedef struct {
	BUFFvar* orig;
	BUFFvar* head;
	BUFFvar* end;
}bufferparameter;

/*** BUFFER TypeDef ***/
struct buffer
{
	bufferparameter par;
	void (*push)(bufferparameter* par, BUFFvar data);
	BUFFvar* (*raw)(bufferparameter* par);
	void (*flush)(bufferparameter* par);
};
typedef struct buffer BUFF;

BUFF BUFFenable(uint8_t size_buff, BUFFvar* buff);

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


