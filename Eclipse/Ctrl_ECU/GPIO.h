/*********************************************************
 * Module:      GPIO
 * File Name:   GPIO.h
 * Description: Header File for AVR GPIO Driver
 * Author:      Ziad Hesham Ghonim
 *********************************************************/
#ifndef GPIO_H_
#define GPIO_H_

#include "Standard_types.h"

/*********************************************************
                    Definitions
 *********************************************************/
#define NUM_OF_PORTS          4
#define NUM_OF_PINS_PER_PORT  8

#define PORTA_ID              0
#define PORTB_ID              1
#define PORTC_ID              2
#define PORTD_ID              3

#define PIN0_ID               0
#define PIN1_ID               1
#define PIN2_ID               2
#define PIN3_ID               3
#define PIN4_ID               4
#define PIN5_ID               5
#define PIN6_ID               6
#define PIN7_ID               7

/*********************************************************
                    Types Declaration
 *********************************************************/
typedef enum
{
	PIN_INPUT,PIN_OUTPUT
}GPIO_PinDirectionType;

typedef enum
{
	PORT_INPUT,PORT_OUTPUT=0xFF
}GPIO_PortDirectionType;

/*********************************************************
                   Functions Prototype
 *********************************************************/

/*******************************************************************************************************
 Description:
   * A function to setup the direction of a required pin input/output.
   * * Direction: The required direction for this pin should be PIN_INPUT or PIN_OUTPUT.
   * If the input port or the pin number are not correct, the function will not handle the request.
 *******************************************************************************************************/
void GPIO_setupPinDirection(uint8 port_num, uint8 pin_num, GPIO_PinDirectionType direction);


/*******************************************************************************************************
 Description:
   * A function to write a logic high or logic low on required pin.
   * value: value to be written on this pin should be LOGIC_HIGH or LOGIC_LOW.
   * If the input port or the pin number are not correct, the function will not handle the request.
   * If the pin is input, this function will enable/disable the internal pull-up resistor.
 *******************************************************************************************************/
void GPIO_writePin(uint8 port_num, uint8 pin_num, uint8 value);

/*******************************************************************************************************
 Description:
   * A function to read and return the value of required pin, it should be logic high or logic low.
   * If the input port number or pin number are not correct, the function will return logic low.
 *******************************************************************************************************/
uint8 GPIO_readPin(uint8 port_num, uint8 pin_num);

/*******************************************************************************************************
 Description:
   * A function to setup the direction of the required port, all pins input/output.
   * If the direction value is PORT_INPUT all pins in this port should be input pins.
   * If the direction value is PORT_OUTPUT all pins in this port should be output pins.
   * If the input port or the pin number are not correct, the function will not handle the request.
 *******************************************************************************************************/
void GPIO_setupPortDirection(uint8 port_num, GPIO_PortDirectionType direction);

/*******************************************************************************************************
 Description:
   * A function to write a value in required port.
   * If any pin in the port is output pin the value will be written.
   * If any pin in the port is input this will active/deactivate the internal pull-up resistor.
   * If the input port number is not correct, the function will not handle the request.
 *******************************************************************************************************/
void GPIO_writePort(uint8 port_num, uint8 value);

/*******************************************************************************************************
 Description:
   * A function to read and return the value of required port.
   * If the input port number is not correct, the function will return ZERO value.
 *******************************************************************************************************/
uint8 GPIO_readPort(uint8 port_num);

#endif
