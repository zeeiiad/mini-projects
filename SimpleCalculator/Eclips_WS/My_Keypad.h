/*************************************************
 * Module:      Keypad
 * File Name:   My_Keypad.h
 * Description: Header File for Keypad Driver
 * Author:      Ziad Hesham Ghonim
 *************************************************/

#ifndef MY_KEYPAD_H_
#define MY_KEYPAD_H_

#include "My_Standard_types.h"

/*******************************************************************
                           Definitions
 *******************************************************************/

/* Keypad Configuration for number of row and columns */
#define KEYPAD_NUM_ROWS            4
#define KEYPAD_NUM_COLS            4

/************* Keypad PORT Configurations *************/
#define KEYPAD_ROW_PORT_ID         PORTB_ID
#define KEYPAD_FIRST_ROW_PIN_ID    PIN4_ID

#define KEYPAD_COL_PORT_ID         PORTD_ID
#define KEYPAD_FIRST_COL_PIN_ID    PIN2_ID

/********* Keypad button Logic configuration *********/
#define KEYPAD_BUTTON_PRESSED      LOGIC_LOW
#define KEYPAD_BUTTON_RELEASED     LOGIC_HIGH


/*******************************************************************
                        Functions Prototype
 *******************************************************************/

/**** Description: Get the Keypad Pressed button ****/
uint8 KEYPAD_getPressedKey(void);

#endif /* MY_KEYPAD_H_ */
