/*********************************************************
 * Module:      Buzzer
 * File Name:   Buzzer.h
 * Description: Header File for Buzzer Driver
 * Author:      Ziad Hesham Ghonim
 *********************************************************/
#ifndef BUZZER_H_
#define BUZZER_H_

#include "Standard_types.h"


/*********************************************************
                    Definitions
 *********************************************************/
#define Buzzer_PORT_ID     PORTD_ID
#define Buzzer_PIN_ID      PIN7_ID

/*********************************************************
                   Functions Prototype
 *********************************************************/

/*******************************************************************************
 Description :
 * Setup the direction for the buzzer pin as output pin through the GPIO driver.
 *  Turn off the buzzer through the GPIO.
 ********************************************************************************/
void Buzzer_init(void);

/**************************************************
 Description :
 *  Function to enable the Buzzer through the GPIO.
 **************************************************/
void Buzzer_on(void);

/****************************************************
 Description :
 *   Function to disable the Buzzer through the GPIO.
 ****************************************************/
void Buzzer_off(void);

#endif /* BUZZER_H_ */
