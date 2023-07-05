/*********************************************************
 * Module:      GPIO
 * File Name:   MY_GPIO.c
 * Description: Source File for AVR GPIO Driver
 * Author:      Ziad Hesham Ghonim
 *********************************************************/
#include "MY_GPIO.h"
#include "My_Common_Macros.h"
#include <avr/io.h>           /* to use the I/O PORTS REGISTERS */

/*******************************************************************************************************
 Description:
   * A function to setup the direction of a required pin input/output.
   * Direction: The required direction for this pin should be PIN_INPUT or PIN_OUTPUT.
   * If the input port or the pin number are not correct, the function will not handle the request.
 *******************************************************************************************************/
void GPIO_setupPinDirection(uint8 port_num, uint8 pin_num, GPIO_PinDirectionType direction)
{
	if( (pin_num >= NUM_OF_PINS_PER_PORT) || (port_num >= NUM_OF_PORTS) )
	{
		/* Do NOTHING */
	}
	else
	{
		switch(port_num)
		{

		case PORTA_ID:
			if(direction == PIN_OUTPUT)
			{
				SET_BIT(DDRA,pin_num);
			}
			else
			{
				CLEAR_BIT(DDRA,pin_num);
			}
			break;

		case PORTB_ID:
			if(direction == PIN_OUTPUT)
			{
				SET_BIT(DDRB,pin_num);
			}
			else
			{
				CLEAR_BIT(DDRB,pin_num);
			}
			break;

		case PORTC_ID:
			if(direction == PIN_OUTPUT)
			{
				SET_BIT(DDRC,pin_num);
			}
			else
			{
				CLEAR_BIT(DDRC,pin_num);
			}
			break;

		case PORTD_ID:
			if(direction == PIN_OUTPUT)
			{
				SET_BIT(DDRD,pin_num);
			}
			else
			{
				CLEAR_BIT(DDRD,pin_num);
			}
			break;
		}
	}
}

/*******************************************************************************************************
 Description:
   * A function to write a logic high or logic low on required pin.
   * value: value to be written on this pin should be LOGIC_HIGH or LOGIC_LOW.
   * If the input port or the pin number are not correct, the function will not handle the request.
   * If the pin is input, this function will enable/disable the internal pull-up resistor.
 *******************************************************************************************************/
void GPIO_writePin(uint8 port_num, uint8 pin_num, uint8 value)
{
	if( (pin_num >= NUM_OF_PINS_PER_PORT) || (port_num >= NUM_OF_PORTS) )
		{
			/* Do NOTHING */
		}
	else
	{
		switch(port_num)
		{
		case PORTA_ID:
			if(value == LOGIC_HIGH)
			{
				SET_BIT(PORTA,pin_num);
			}
			else
			{
				CLEAR_BIT(PORTA,pin_num);
			}
			break;

		case PORTB_ID:
			if(value == LOGIC_HIGH)
			{
				SET_BIT(PORTB,pin_num);
			}
			else
			{
				CLEAR_BIT(PORTB,pin_num);
			}
			break;

		case PORTC_ID:
			if(value == LOGIC_HIGH)
			{
				SET_BIT(PORTC,pin_num);
			}
			else
			{
				CLEAR_BIT(PORTC,pin_num);
			}
			break;

		case PORTD_ID:
			if(value == LOGIC_HIGH)
			{
				SET_BIT(PORTD,pin_num);
			}
			else
			{
				CLEAR_BIT(PORTD,pin_num);
			}
			break;
		}
	}
}

/*******************************************************************************************************
 Description:
   * A function to read and return the value of required pin, it should be logic high or logic low.
   * If the input port number or pin number are not correct, the function will return logic low.
 *******************************************************************************************************/
uint8 GPIO_readPin(uint8 port_num, uint8 pin_num)
{
	uint8 pin_value = LOGIC_LOW;
	if( (pin_num >= NUM_OF_PINS_PER_PORT) || (port_num >= NUM_OF_PORTS) )
	{
		/* Do NOTHING */
	}
	else
	{
		switch(port_num)
		{
		case PORTA_ID:
			if(BIT_IS_SET(PINA,pin_num))
			{
				pin_value = LOGIC_HIGH;
			}
			else
			{
				pin_value = LOGIC_LOW;
			}
			break;

		case PORTB_ID:
			if(BIT_IS_SET(PINB,pin_num))
			{
				pin_value = LOGIC_HIGH;
			}
			else
			{
				pin_value = LOGIC_LOW;
			}
			break;

		case PORTC_ID:
			if(BIT_IS_SET(PINC,pin_num))
			{
				pin_value = LOGIC_HIGH;
			}
			else
			{
				pin_value = LOGIC_LOW;
			}
			break;

		case PORTD_ID:
			if(BIT_IS_SET(PIND,pin_num))
			{
				pin_value = LOGIC_HIGH;
			}
			else
			{
				pin_value = LOGIC_LOW;
			}
			break;
		}
	}
	return pin_value;
}

/*******************************************************************************************************
 Description:
   * A function to setup the direction of the required port, all pins input/output.
   * If the direction value is PORT_INPUT all pins in this port should be input pins.
   * If the direction value is PORT_OUTPUT all pins in this port should be output pins.
   * If the input port or the pin number are not correct, the function will not handle the request.
 *******************************************************************************************************/
void GPIO_setupPortDirection(uint8 port_num, GPIO_PortDirectionType direction)
{
	if( port_num >= NUM_OF_PORTS)
	{
		/* Do NOTHING */
	}
	else
	{
		switch(port_num)
		{
		case PORTA_ID:
			DDRA = direction;
			break;
		case PORTB_ID:
			DDRB = direction;
			break;
		case PORTC_ID:
			DDRC = direction;
			break;
		case PORTD_ID:
			DDRD = direction;
			break;
		}
	}
}

/*******************************************************************************************************
 Description:
   * A function to write a value in required port.
   * If any pin in the port is output pin the value will be written.
   * If any pin in the port is input this will active/deactivate the internal pull-up resistor.
   * If the input port number is not correct, the function will not handle the request.
 *******************************************************************************************************/
void GPIO_writePort(uint8 port_num, uint8 value)
{
	if( port_num >= NUM_OF_PORTS)
	{
		/* Do NOTHING */
	}
	else
	{
		switch(port_num)
		{
		case PORTA_ID:
			PORTA = value;
			break;
		case PORTB_ID:
			PORTB = value;
			break;
		case PORTC_ID:
			PORTC = value;
			break;
		case PORTD_ID:
			PORTD = value;
			break;
		}
	}
}

/*******************************************************************************************************
 Description:
   * A function to read and return the value of required port.
   * If the input port number is not correct, the function will return ZERO value.
 *******************************************************************************************************/
uint8 GPIO_readPort(uint8 port_num)
{
	uint8 value = 0;
	if( port_num >= NUM_OF_PORTS)
	{
		/* Do NOTHING */
	}
	else
	{
		switch(port_num)
		{
		case PORTA_ID:
			value = PINA;
			break;
		case PORTB_ID:
			value = PINB;
			break;
		case PORTC_ID:
			value = PINC;
			break;
		case PORTD_ID:
			value = PIND;
			break;
		}
	}
	return value;
}
