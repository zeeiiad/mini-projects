/*********************************************************
 * Module:      Buzzer
 * File Name:   Buzzer.c
 * Description: Header File for Buzzer Driver
 * Author:      Ziad Hesham Ghonim
 *********************************************************/

#include "Buzzer.h"
#include "GPIO.h"
#include "Common_Macros.h"

/*********************************************************
                   Functions Definitions
 *********************************************************/

/*******************************************************************************
 Description :
 * Setup the direction for the buzzer pin as output pin through the GPIO driver.
 * Turn off the buzzer through the GPIO.
 ********************************************************************************/
void Buzzer_init(void)
{
	/* Configure the direction for Buzzer input pins as output pins */
	GPIO_setupPinDirection(Buzzer_PORT_ID,Buzzer_PIN_ID,PIN_OUTPUT);

	/* Buzzer is OFF at the beginning */
	GPIO_writePin(Buzzer_PORT_ID,Buzzer_PIN_ID,LOGIC_LOW);
}

/**************************************************
 Description :
 *  Function to enable the Buzzer through the GPIO.
 **************************************************/
void Buzzer_on(void)
{
	GPIO_writePin(Buzzer_PORT_ID,Buzzer_PIN_ID,LOGIC_HIGH);
}

/****************************************************
 Description :
 *   Function to disable the Buzzer through the GPIO.
 ****************************************************/
void Buzzer_off(void)
{
	GPIO_writePin(Buzzer_PORT_ID,Buzzer_PIN_ID,LOGIC_LOW);
}
