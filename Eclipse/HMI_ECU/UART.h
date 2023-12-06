 /*******************************************************
 * Module: UART
 * File Name: uart.h
 * Description: Header file for the UART driver
 * Author: Ziad Hesham Ghonim
 *********************************************************/

#ifndef UART_H_
#define UART_H_

#include "Standard_types.h"

/*******************************************************************************
 *                         Types Declaration                                   *
 *******************************************************************************/
typedef enum
{
	DISABLE,EVEN_PARITY=2,ODD_PARITY
}UART_ParityMode;

typedef enum
{
	ONE_STOPBIT,TWO_STOPBIT
}UART_StopBit;

typedef enum
{
	FIVE_BIT,SIX_BIT,SEVEN_BIT,EIGHT_BIT,NINE_BIT=7
}UART_DataBitsFrame;

typedef struct
{
	UART_ParityMode    ParityMode;
	UART_StopBit       StopBit;
	UART_DataBitsFrame DataBitsFrame;
	uint32             BaudRate;
}UART_ConfigType;

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/**********************************************************************************************
  Description: Functional responsible for Initialize the UART device by:
  1. Setup the Frame format like number of data bits, parity bit type and number of stop bits.
  2. Enable the UART.
  3. Setup the UART baud rate.
 **********************************************************************************************/
void UART_init(UART_ConfigType *UART_config_ptr);

/***************************************************************************
  Description: Functional responsible for send byte to another UART device.
 ***************************************************************************/
void UART_sendByte(const uint8 data);

/******************************************************************************
  Description: Functional responsible for receive byte from another UART device.
 *******************************************************************************/
uint8 UART_recieveByte(void);

/****************************************************************************
  Description: Send the required string through UART to the other UART device.
 *****************************************************************************/
void UART_sendString(const uint8 *Str);

/******************************************************************************************************
 Description: Receive the required string until the '#' symbol through UART from the other UART device.
 ******************************************************************************************************/
void UART_receiveString(uint8 *Str);

#endif /* UART_H_ */
