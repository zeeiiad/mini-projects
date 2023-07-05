/*********************************************************
 * Module:      Lm35 Temperature Sensor
 * File Name:   Lm35_sensor.c
 * Description: Source File for Lm35 temperature sensor
 * Author:      Ziad Hesham Ghonim
 ********************************************************/

#include "Lm35_sensor.h"
#include "My_ADC.h"

/*******************************************************************************
 Description : Function responsible for calculating the temperature from
               the ADC digital value.
 *******************************************************************************/
uint8 LM35_getTemperature(void)
{
	uint8  temp_value = 0;
	uint16 ADC_value  = 0;

	ADC_value = ADC_readChannel(SENSOR_CHANNEL_ID);

	temp_value = (uint8)(((uint32)ADC_value*SENSOR_MAX_TEMPERATURE*ADC_REF_VOLT_VALUE)/(ADC_MAXIMUM_VALUE*SENSOR_MAX_VOLT_VALUE));

	return temp_value;
}
