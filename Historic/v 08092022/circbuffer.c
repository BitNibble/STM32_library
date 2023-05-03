/******************************************************************************
	CIRCBUFFER
Author: Sergio Santos
	<sergio.salazar.santos@gmail.com>
License: GNU General Public License
Hardware: all
Date: 07092022
Comment:
    Circular Buffer
******************************************************************************/
/***Library***/
#include <stdio.h>
#include <string.h>
#include "circbuffer.h"
/***Constant & Macro***/
/***Global File Variable***/
static volatile uint8_t CIRCi;
/***Header***/
/******************************************************************************/
uint8_t CIRC_get(struct circ_buf_template* circ);
void CIRC_put(struct circ_buf_template* circ, uint8_t data);
void CIRC_putstr(struct circ_buf_template* circ, const char* str);
void CIRC_fputstr(struct circ_buf_template* circ, const char* str);
void CIRC_freset(void);
void CIRC_getstr(struct circ_buf_template* circ, uint8_t* str);
/***Procedure & Function***/
/******************************************************************************/
circbuff CIRCBUFFenable( uint8_t size_buff, uint8_t* buff )
{
	// OBJECT STRUCT
	struct circ_buf_template circ;
	// inic VAR
	CIRCi = 0;
	circ.tail = circ.head = circ.buff = buff;
	circ.orig = buff;
	circ.end = buff + ( size_buff - 1 ); // generic
	// function pointers
	circ.get = CIRC_get;
	circ.put = CIRC_put;
	circ.putstr = CIRC_putstr;
	circ.getstr = CIRC_getstr;
	/******/
	return circ; // return copy
}
/******************************************************************************/
uint8_t CIRC_get( struct circ_buf_template* circ ){
	uint8_t* tail; uint8_t* next;
	tail = circ->tail;
	
	if( tail == circ->end ){
		next = circ->orig;
	}else{
		next = tail + 1;
	}

	if( tail == circ->head ){
		*tail = 0; // flag null
	}else{
		circ->tail = next;
		tail = next;
	}

	return *tail;
}

void CIRC_put( struct circ_buf_template* circ, uint8_t data ){
	uint8_t* head; uint8_t* next;
	head = circ->head;

	if( head == circ->end ){
		next = circ->orig;
	}else{
		next = head + 1;
	}
	
	if( next == circ->tail ){
		;
	}else{
		*next = data;
		circ->head = next;
	}
}

void CIRC_putstr(struct circ_buf_template* circ, const char* str){
	uint8_t i;
	for(i = 0; i < (strlen(str)+1) ; ){
		CIRC_put(circ, str[i++]);
	}
}

void CIRC_getstr(struct circ_buf_template* circ, uint8_t* str){
	uint8_t i;
	for(i = 0; (str[i++] = CIRC_get(circ))  ; );
}

void CIRC_fputstr(struct circ_buf_template* circ, const char* str){
	if( CIRCi < (strlen(str)+1) ){
		CIRC_put(circ, str[CIRCi++]);
	}
}

void CIRC_freset(void){
	if( CIRCi )
		CIRCi = 0;
}

/******************************************************************************/
/***Interrupt***/
/******************************Comment*****************************************
	Simple and concise, nice.
*******************************************************************************/
/***EOF***/

