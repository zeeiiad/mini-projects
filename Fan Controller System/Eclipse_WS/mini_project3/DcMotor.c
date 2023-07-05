/*********************************************************
 * Module:      DC Motor
 * File Name:   DcMotor.c
 * Description: Source File for DC Motor Driver
 * Author:      Ziad Hesham Ghonim
 *********************************************************/
#include "My_Common_Macros.h"
#include "MY_GPIO.h"
#include "DcMotor.h"
#include "PWM_Timer0.h"
#include <avr/io.h>           /* to use the I/O PORTS REGISTERS */

/*******************************************************************************
                             Functions Definitions
 *******************************************************************************/


/********************************************************************************************************
 Description :
 * The Function responsible for setup the direction for the two motor pins through the GPIO driver.
 * Stop at the DC-Motor at the beginning through the GPIO driver.
 *********************************************************************************************************/
void DcMotor_init(void)
{
	/* Configure the direction for Motor input pins as output pins */
	GPIO_setupPinDirection(DcMotor_PORT_ID,DcMotor_PIN0_ID,PIN_OUTPUT);
	GPIO_setupPinDirection(DcMotor_PORT_ID,DcMotor_PIN1_ID,PIN_OUTPUT);

	      /* DC Motor is stopped at the beginning */
	GPIO_writePin(DcMotor_PORT_ID,DcMotor_PIN0_ID,LOGIC_LOW);
	GPIO_writePin(DcMotor_PORT_ID,DcMotor_PIN1_ID,LOGIC_LOW);
}


/********************************************************************************************************
 Description :
 * Function is responsible for rotate the DC Motor CW/ or A-CW or stop the motor based on the state
   input state value.
 * Send the required duty cycle to the PWM driver based on the required speed value
 *********************************************************************************************************/
void DcMotor_Rotate(DcMotor_State state,uint8 speed)
{
	if(state == OFF)
	{
		GPIO_writePin(DcMotor_PORT_ID,DcMotor_PIN0_ID,LOGIC_LOW);
		GPIO_writePin(DcMotor_PORT_ID,DcMotor_PIN1_ID,LOGIC_LOW);
		PWM_Timer0_Start(speed);
	}
	else if(state == ACW)
	{
		GPIO_writePin(DcMotor_PORT_ID,DcMotor_PIN0_ID,LOGIC_LOW);
		GPIO_writePin(DcMotor_PORT_ID,DcMotor_PIN1_ID,LOGIC_HIGH);
		PWM_Timer0_Start(speed);
	}
	else
	{
		GPIO_writePin(DcMotor_PORT_ID,DcMotor_PIN0_ID,LOGIC_HIGH);
		GPIO_writePin(DcMotor_PORT_ID,DcMotor_PIN1_ID,LOGIC_LOW);
		PWM_Timer0_Start(speed);
	}

}
