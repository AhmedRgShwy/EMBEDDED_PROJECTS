/*
 * digitalClock.h
 *
 * Created: 10/31/2016 4:06:54 PM
 *  Author: AhmedShaarawy
 */ 


#ifndef DIGITALCLOCK_H_
#define DIGITALCLOCK_H_
#define F_CPU	8000000ul
#include "timer0.h"
#include "shiftReg74HC595.h"
#include "EXTInterrupt.h"
#include <util/delay.h>

// for future design
#define EDIT_PORT	B
#define EDIT_PIN	4
#define OK_SW_PORT	B
#define OK_SW_PIN	5
// MENUE
#define ALARM		1
#define EDIT_TIME	2
#define EDIT_DATE	3


#define LOOP		while(1)
// when the project goes real make the decision = 1000000 for timer0 pre-scale-8 of 8-mega cpu
#define AM			0x77
#define DISICION	10000	
#define PM			0x73



typedef struct  
{
	U8 digit0, digit1, key:1 ;
}Unit;

typedef struct{
	U8 digit0, digit1, digit2, digit3 ;
	}sYear;
	

void TaskInit(void);
void Task2Init(void);
void TaskLoop(void);
void TaskIntTimer0(void);
void TaskInt0(void);
void TaskInt1(void);
void EditTime(void);


#endif /* DIGITALCLOCK_H_ */