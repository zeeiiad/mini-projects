/*********************************************************
 * Module:      ATmega32 Timer1
 * File Name:   Timer1.h
 * Description: Header File for ATmega32 Timer1 Driver
 * Author:      Ziad Hesham Ghonim
 *********************************************************/

#include "Timer1.h"
#include "Common_Macros.h"
#include <avr/io.h>
#include <avr/interrupt.h>

/*******************************************************************************
                               Global Variables
 *******************************************************************************/
/* Global variable to hold the address of the call back function in the application */
static volatile void (*g_callBackPtr)(void) = NULL_PTR;

/*******************************************************************************
                                    ISR
 *******************************************************************************/
ISR(TIMER1_COMPA_vect)
{
	if(g_callBackPtr != NULL_PTR)
	{
		/* Call the callback function in the application */
		(*g_callBackPtr)();
	}
}

/*********************************************************
                   Functions Declaration
 *********************************************************/

/******************************************
 Description :
 * Function to initialize the Timer driver.
 ******************************************/
void Timer1_init(const Timer1_ConfigType * Config_Ptr)
{

	TCNT1  = Config_Ptr->initial_value;

	if(Config_Ptr->mode==CTC)
	{
		SET_BIT(TCCR1A,FOC1A);
		SET_BIT(TCCR1B,WGM12);
		OCR1A  = Config_Ptr->compare_value;
	}

	if((Config_Ptr->mode==NORMAL) && (Config_Ptr->tech==INTERRUPT))
	{
		SET_BIT(TIMSK,TOIE1);
	}

	else if((Config_Ptr->mode==CTC) && (Config_Ptr->tech==INTERRUPT))
	{
		SET_BIT(TIMSK,OCIE1A);
	}

	TCCR1B |= Config_Ptr->prescaler;
}

/**********************************
 Description :
 *  Function to disable the Timer1.
 **********************************/
void Timer1_deInit(void)
{
	TCNT1 = 0;
	OCR1A = 0;
	TCCR1A= 0;
	TCCR1B= 0;
	TIMSK = 0;
}

/*************************************************
 Description :
 *  Function to set the Call Back function address
 *************************************************/
void Timer1_setCallBack(void(*a_ptr)(void))
{
	/* save the address of the call back function in the global address*/
	g_callBackPtr = a_ptr;
}
