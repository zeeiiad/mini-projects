/*********************************************************
 * Module:      PWM Mode
 * File Name:   PWM_Timer0.c
 * Description: Source File for PWM_Timer0 Driver
 * Author:      Ziad Hesham Ghonim
 *********************************************************/
#include "My_Common_Macros.h"
#include "PWM_Timer0.h"
#include "My_GPIO.h"
#include <avr/io.h>

/*******************************************************************************
                             Functions Definitions
 *******************************************************************************/

/********************************************************************************************************
 Description :
 * The function responsible for trigger the Timer0 with the PWM Mode.
 * Setup the PWM mode with Non-Inverting.
 * Setup the prescaler with F_CPU/8.
 * Setup the compare value based on the required input duty cycle
 * Setup the direction for OC0 as output pin through the GPIO driver.
 * The generated PWM signal frequency will be 500Hz to control the DC Motor speed.
 *********************************************************************************************************/
void PWM_Timer0_Start(uint8 duty_cycle)
{
	TCNT0 = 0;
	OCR0  = (uint8)((float32)((float32)duty_cycle/100) * 255);
	SET_BIT(TCCR0,WGM00);
	SET_BIT(TCCR0,WGM01);
	SET_BIT(TCCR0,COM01);
	SET_BIT(TCCR0,CS01);
	GPIO_setupPinDirection(PORTB_ID,PIN3_ID,PIN_OUTPUT);
}
