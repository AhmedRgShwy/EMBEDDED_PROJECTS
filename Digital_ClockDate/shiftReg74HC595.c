/*
 * shiftReg74HC595.c
 *
 * Created: 10/31/2016 7:49:57 PM
 *  Author: AhmedShaarawy
 */ 

#include "shiftReg74HC595.h"


///////////////////////////// MODULE 1 ////////////////////////////
void HC595Init(void)
{
	// direction setting
	DDR(HC595_DS_PORT)|= (1<<HC595_DS_PIN)|(1<<HC595_SH_CLK_PIN)|(1<<HC595_ST_CLK_PIN) ;
}


// pulse for sending each serial bit
void HC595Pulse(void)
{
	SET_PIN(HC595_SH_CLK_PORT,HC595_SH_CLK_PIN);
	CLR_PIN(HC595_SH_CLK_PORT,HC595_SH_CLK_PIN);
}


// clock for output the parallel 8bits
void HC595Latch(void)
{
	SET_PIN(HC595_ST_CLK_PORT,HC595_ST_CLK_PIN);
	_delay_ms(1);
	CLR_PIN(HC595_ST_CLK_PORT,HC595_ST_CLK_PIN);
	_delay_ms(1);
}



void HC595Write(U8 data)
{
	U8 i;
	for( i=0 ; i<8 ; i++, data<<=1)
	{
		if(data&0x80)
			SET_PIN(HC595_DS_PORT,HC595_DS_PIN);
		else
			CLR_PIN(HC595_DS_PORT,HC595_DS_PIN);
		HC595Pulse();
	}
	HC595Latch();
	_delay_ms(2);
}
///////////////////////////////////////////////////////////////////






///////////////////////////// MODULE 2 ////////////////////////////
void HC595Init_2(void)
{
	// direction setting
	DDR(HC595_DS_PORT_2)|= (1<<HC595_DS_PIN_2)|(1<<HC595_SH_CLK_PIN_2)|(1<<HC595_ST_CLK_PIN_2) ;
}


// pulse for sending each serial bit
void HC595Pulse_2(void)
{
	SET_PIN(HC595_SH_CLK_PORT_2,HC595_SH_CLK_PIN_2);
	CLR_PIN(HC595_SH_CLK_PORT_2,HC595_SH_CLK_PIN_2);
}


// clock for output the parallel 8bits
void HC595Latch_2(void)
{
	SET_PIN(HC595_ST_CLK_PORT_2,HC595_ST_CLK_PIN_2);
	_delay_ms(1);
	CLR_PIN(HC595_ST_CLK_PORT_2,HC595_ST_CLK_PIN_2);
	_delay_ms(1);
}



void HC595Write_2(U8 data)
{
	U8 i;
	for( i=0 ; i<8 ; i++, data<<=1)
	{
		if(data&0x80)
		SET_PIN(HC595_DS_PORT_2,HC595_DS_PIN_2);
		else
		CLR_PIN(HC595_DS_PORT_2,HC595_DS_PIN_2);
		HC595Pulse_2();
	}
	HC595Latch_2();
	_delay_ms(2);
}
///////////////////////////////////////////////////////////////////