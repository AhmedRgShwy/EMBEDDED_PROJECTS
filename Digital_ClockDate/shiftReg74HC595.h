/*
 * shiftReg74HC595.h
 *
 * Created: 10/31/2016 7:50:10 PM
 *  Author: AhmedShaarawy
 */ 



#ifndef SHIFTREG74HC595_H_
#define SHIFTREG74HC595_H_
#include "atmega32_lib.h"
#define F_CPU	8000000ul
#include <util/delay.h>



///////// CONNECTIONS //////////
// "DS" data serial, "SH" shift
//  "CLK" clock, "ST" store
////////////////////////////////
/////////// MODULE 1 ///////////
#define HC595_DS_PORT		B
#define HC595_DS_PIN		0
#define HC595_SH_CLK_PORT	B
#define HC595_SH_CLK_PIN	1
#define HC595_ST_CLK_PORT	B
#define HC595_ST_CLK_PIN	3
////////////////////////////////

/////////// MODULE 2 ///////////
#define HC595_DS_PORT_2		C
#define HC595_DS_PIN_2		0
#define HC595_SH_CLK_PORT_2	C
#define HC595_SH_CLK_PIN_2	1
#define HC595_ST_CLK_PORT_2	C
#define HC595_ST_CLK_PIN_2	2
////////////////////////////////



/////////// MODULE 1 //////////
void HC595Init(void);
void HC595Pulse(void);
void HC595Latch(void);
void HC595Write(U8 data);
///////////////////////////////

/////////// MODULE 2 //////////
void HC595Init_2(void);
void HC595Pulse_2(void);
void HC595Latch_2(void);
void HC595Write_2(U8 data);
///////////////////////////////


#endif /* SHIFTREG74HC595_H_ */