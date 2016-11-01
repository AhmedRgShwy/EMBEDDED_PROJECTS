/*
 * timer0.h
 *
 * Created: 10/31/2016 4:08:31 PM
 *  Author: AhmedShaarawy
 */ 


#ifndef TIMER0_H_
#define TIMER0_H_

#include "atmega32_lib.h"
#include <avr/interrupt.h>


#define HoldTimer0()	TCCR0= 0x00
#define ReturnTimer0()	TIMSK &= ~0x01; TCCR0= 0x02		// 0x02 normal mode, disable OC0 and pre-scale 8

void timer0Init(void);


#endif /* TIMER0_H_ */