/*************************************************
 * Module:      Ultrasonic Sensor
 * File Name:   Ultrasonic.c
 * Description: Source File for Ultrasonic Sensor
 * Author:      Ziad Hesham Ghonim
 *************************************************/
#include "ultrasonic.h"
#include "icu.h"
#include "MY_GPIO.h"
#include "My_Common_Macros.h"
#include <util/delay.h>


uint16 g_timeHigh = 0;


/*******************************************************************************
                             Functions Declaration
 *******************************************************************************/

/*******************************************************************************
 Description : Initialize the Ultrasonic Sensor:
               1- initialize ICU driver.
               2- Setup the ICU call back function.
               3- setup the direction for the trigger pin.
 *******************************************************************************/
void Ultrasonic_init(void)
{
	ICU_ConfigType ICU_Configurations = {F_CPU_8,RAISING};

	/* initialize ICU driver */
	ICU_init(&ICU_Configurations);

	/* Setup the ICU call back function */
	ICU_setCallBack(Ultrasonic_edgeProcessing);

	/* Setup the direction for the trigger pin as output pin through the GPIO driver */
	GPIO_setupPinDirection(Ultrasonic_Trigger_Port,Ultrasonic_Trigger_pin,PIN_OUTPUT);
}

/*******************************************************************************
 Description : Send the Trigger pulse to the ultrasonic.
 *******************************************************************************/
void Ultrasonic_Trigger(void)
{
	GPIO_writePin(Ultrasonic_Trigger_Port,Ultrasonic_Trigger_pin,LOGIC_HIGH);
	_delay_us(10);
	GPIO_writePin(Ultrasonic_Trigger_Port,Ultrasonic_Trigger_pin,LOGIC_LOW);
}

/*******************************************************************************
 Description : 1- Send the trigger pulse by using Ultrasonic_Trigger function.
               2- Start the measurements by the ICU from this moment.
 *******************************************************************************/
uint16 Ultrasonic_readDistance(void)
{
	uint16 Distance;

	Ultrasonic_Trigger();

	Distance = g_timeHigh/58.8;

	return Distance+1;
}

/******************************************************************************************************
 Description : This is the Call Back Function called by the ICU Driver
               It is used to calculate the high time (pulse time) generated by the ultrasonic sensor.
 ******************************************************************************************************/
void Ultrasonic_edgeProcessing(void)
{
	static uint8 g_edgeCount = 0;
	g_edgeCount++;
	if(g_edgeCount == 1)
	{
		ICU_clearTimerValue();
		ICU_setEdgeDetectionType(FALLING);
	}
	else if(g_edgeCount == 2)
	{
	    g_edgeCount = 0;
		g_timeHigh = ICU_getInputCaptureValue();
		ICU_setEdgeDetectionType(RAISING);
		ICU_clearTimerValue();
	}
}