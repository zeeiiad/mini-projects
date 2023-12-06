/*********************************************************
 * Module:      ATmega32 Timer1
 * File Name:   Timer1.h
 * Description: Header File for AVR ATmega32 Timer1 Driver
 * Author:      Ziad Hesham Ghonim
 *********************************************************/

#ifndef TIMER1_H_
#define TIMER1_H_

#include "Standard_types.h"

/*******************************************************************************
                             Types Declaration
 *******************************************************************************/
typedef enum
{
	NORMAL,CTC=4
}Timer1_Mode;

typedef enum
{
	POLLING,INTERRUPT
}Timer1_Technique;

typedef enum
{
	NO_CLOCK,             //timer/counter stopped
	CLK_1,                //no_prescalling
	CLK_8,CLK_64,CLK_256,CLK_1024,
	EXTERNAL_CLK_FALLING_EDGE,
	EXTERNAL_CLK_RISING_EDGE
}Timer1_Prescaler;

typedef struct
{
	Timer1_Mode mode;
	Timer1_Technique tech;
	uint16 initial_value;
	uint16 compare_value;         // it will be used in compare mode only.
	Timer1_Prescaler prescaler;
} Timer1_ConfigType;

/*********************************************************
                   Functions Prototype
 *********************************************************/

/******************************************
 Description :
 * Function to initialize the Timer driver.
 ******************************************/
void Timer1_init(const Timer1_ConfigType * Config_Ptr);

/**********************************
 Description :
 *  Function to disable the Timer1.
 **********************************/
void Timer1_deInit(void);

/*************************************************
 Description :
 *  Function to set the Call Back function address
 *************************************************/
void Timer1_setCallBack(void(*a_ptr)(void));

#endif /* TIMER1_H_ */
