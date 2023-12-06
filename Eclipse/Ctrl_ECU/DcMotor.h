/*********************************************************
 * Module:      DC Motor
 * File Name:   DcMotor.h
 * Description: Header File for DC Motor Driver
 * Author:      Ziad Hesham Ghonim
 *********************************************************/

#ifndef DCMOTOR_H_
#define DCMOTOR_H_

#include "Standard_types.h"

/*********************************************************
                    Definitions
 *********************************************************/
#define DcMotor_PORT_ID     PORTB_ID
#define DcMotor_PIN0_ID     PIN0_ID
#define DcMotor_PIN1_ID     PIN1_ID

typedef enum
{
	CW,ACW,OFF
}DcMotor_State;

/*********************************************************
                   Functions Prototype
 *********************************************************/

/********************************************************************************************************
 Description :
 * The Function responsible for setup the direction for the two motor pins through the GPIO driver.
 * Stop at the DC-Motor at the beginning through the GPIO driver.
 *********************************************************************************************************/
void DcMotor_init(void);

/********************************************************************************************************
 Description :
 * Function is responsible for rotate the DC Motor CW/ or A-CW or stop the motor based on the state
   input state value.
 * Send the required duty cycle to the PWM driver based on the required speed value
 *********************************************************************************************************/
void DcMotor_Rotate(DcMotor_State state,uint8 speed);

#endif /* DCMOTOR_H_ */
