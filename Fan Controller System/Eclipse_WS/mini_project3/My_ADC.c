/*************************************************
 * Module:      ADC
 * File Name:   My_ADC.c
 * Description: Source File for ADC Driver
 * Author:      Ziad Hesham Ghonim
 *************************************************/

#include "My_ADC.h"
#include "My_Common_Macros.h"
#include <avr/interrupt.h>
#include <avr/io.h>

/*******************************************************************************
                                 Global Variables
 *******************************************************************************/
#ifndef POLLING
volatile uint16 g_adcResult = 0;
#endif

/*******************************************************************************
 Description : Function responsible for initializing ADC Driver.
 *******************************************************************************/
void ADC_init(ADC_ConfigType *config_ptr)
{
	ADMUX = (ADMUX & 0x3f) | ((config_ptr->refVolt)<<6);
	ADMUX &= 0xC0;
	ADCSRA = (ADCSRA & 0xF8) | (config_ptr->prescaler);
	SET_BIT(ADCSRA,ADEN);
#ifndef POLLING
	SET_BIT(ADCSRA,ADIE);
#endif
}

#ifdef POLLING
/*******************************************************************************
 Description : Function to read analog data from a certain channel
               and convert it to digital using ADC Driver.
 *******************************************************************************/
uint16 ADC_readChannel(uint8 ch_num)
{
	ADMUX = (ADMUX & 0xE0) | (ch_num);    //insert channel number

	SET_BIT(ADCSRA,ADSC);                        //Start Conversion

	while(!(GET_BIT(ADCSRA,ADIF)));              //polling until ADIF =1

	SET_BIT(ADCSRA,ADIF);                        //Clear ADC Interrupt flag by setting ADIF bit

	return ADC;
}
#endif

#ifndef POLLING
/*******************************************************************************
                                  ISR
 *******************************************************************************/
	ISR(ADC_vect)
	{
		g_adcResult = ADC;
	}
#endif

