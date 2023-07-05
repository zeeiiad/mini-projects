/*************************************************
 * Module:      ADC
 * File Name:   My_ADC.h
 * Description: Header File for ADC Driver
 * Author:      Ziad Hesham Ghonim
 *************************************************/
#ifndef MY_ADC_H_
#define MY_ADC_H_

#include "My_Standard_types.h"

/*******************************************************************
                           Definitions
 *******************************************************************/
#define POLLING

#define ADC_MAXIMUM_VALUE    1023
#define ADC_REF_VOLT_VALUE   2.56

#define CH0_ID               0x00
#define CH1_ID               0x01
#define CH2_ID               0x02
#define CH3_ID               0x03
#define CH4_ID               0x04
#define CH5_ID               0x05
#define CH6_ID               0x06
#define CH7_ID               0x07

/*******************************************************************************
                          Types Declaration
 *******************************************************************************/
typedef enum
{
	AREF,AVCC,INT_REF_VOLT=3
}ADC_ReferenceVoltage;

typedef enum
{
	F_CPU_2=1,F_CPU_4,F_CPU_8,F_CPU_16,F_CPU_32,F_CPU_64,F_CPU_128
}ADC_Prescaler;

typedef struct
{
	ADC_ReferenceVoltage refVolt;
	ADC_Prescaler prescaler;
}ADC_ConfigType;

/*******************************************************************************
                          Functions Prototypes
 *******************************************************************************/

/*******************************************************************************
 Description : Function responsible for initializing ADC Driver.
 *******************************************************************************/
void ADC_init(ADC_ConfigType *config_ptr);


#ifdef POLLING
/*******************************************************************************
 Description : Function to read analog data from a certain channel
               and convert it to digital using ADC Driver.
 *******************************************************************************/
uint16 ADC_readChannel(uint8 ch_num);
#endif

#endif /* MY_ADC_H_ */
