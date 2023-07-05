/*********************************************************
 * Module:      PWM Mode
 * File Name:   PWM_Timer0.h
 * Description: Header File for PWM_Timer0 Driver
 * Author:      Ziad Hesham Ghonim
 *********************************************************/

#ifndef PWM_TIMER0_H_
#define PWM_TIMER0_H_

#include "My_Standard_types.h"

/*********************************************************
                   Functions Prototype
 *********************************************************/

/********************************************************************************************************
 Description :
 * The function responsible for trigger the Timer0 with the PWM Mode.
 * Setup the PWM mode with Non-Inverting.
 * Setup the prescaler with F_CPU/8.
 * Setup the compare value based on the required input duty cycle
 * Setup the direction for OC0 as output pin through the GPIO driver.
 * The generated PWM signal frequency will be 500Hz to control the DC Motor speed.
 *********************************************************************************************************/
void PWM_Timer0_Start(uint8 duty_cycle);

#endif /* PWM_TIMER0_H_ */
