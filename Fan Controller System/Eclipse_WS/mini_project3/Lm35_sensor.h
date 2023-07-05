/*********************************************************
 * Module:      Lm35 Temperature Sensor
 * File Name:   Lm35_sensor.h
 * Description: Header File for Lm35 temperature sensor
 * Author:      Ziad Hesham Ghonim
 ********************************************************/

#ifndef LM35_SENSOR_H_
#define LM35_SENSOR_H_

#include "My_Standard_types.h"

/*******************************************************************
                           Definitions
 *******************************************************************/
#define SENSOR_CHANNEL_ID         2
#define SENSOR_MAX_VOLT_VALUE     1.5
#define SENSOR_MAX_TEMPERATURE    150
/*******************************************************************
                        Functions Prototype
 *******************************************************************/

/*******************************************************************************
 Description : Function responsible for calculating the temperature from
               the ADC digital value.
 *******************************************************************************/
uint8 LM35_getTemperature(void);

#endif /* LM35_SENSOR_H_ */
