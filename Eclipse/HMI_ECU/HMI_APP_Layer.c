/*********************************************************
 * File Name:   HMI_APP_Layer.c
 * Description: Source File for Human Machine Interface ECU
 * Author:      Ziad Hesham Ghonim
 *********************************************************/

#include "Keypad.h"
#include "LCD.h"
#include "UART.h"
#include "Timer1.h"
#include "common_macros.h"
#include <avr/io.h>
#include <util/delay.h>

/****************** Preprocessor Macros ******************/
#define Ctrl_ECU_READY 0x1
#define PASSWORD_CONFIRMED 1
#define PASSWORD_INCORRECT 0
#define GO_TO_MENU 0xFF

/********************* GLOBLE Variables *********************/
uint8 key;
uint8 Password1[5];
uint8 Password2[5];
uint8 confirmation;

/*********************************************************
 description:
 * Function to Set  the password for the system
 *********************************************************/
void SET_PASSWORD(void)
{
	uint8 x = 0,y=0;
	LCD_clearScreen();
	LCD_displayString("Enter New Pass:");
	LCD_moveCursor(1,0);

	while(x<5)
	{
		key = KEYPAD_getPressedKey();
		if (key > 9 )
		{
			continue;
		}
		Password1[x] = key;
		LCD_displayCharacter('*');
		x++;
	}
	while(KEYPAD_getPressedKey()!= '=');

	LCD_clearScreen();
	LCD_moveCursor(0,0);
	LCD_displayString("Please Re-enter");
	LCD_moveCursor(1,0);
	LCD_displayString("same pass: ");
	LCD_moveCursor(1,11);

	while(y<5)
	{

		key = KEYPAD_getPressedKey();
		if (key > 9 )
		{
			continue;
		}
		Password2[y] = key;
		LCD_displayCharacter('*');
		y++;
	}
	while(KEYPAD_getPressedKey()!= '=');
}

/*********************************************************
 description:
 * Function to Send the two passwords to Control ECU
 *********************************************************/
void PASSWORD_Confirmation(void)
{
	uint8 x;
	for(x=0 ; x<5 ; x++)
	{
		UART_sendByte(Password1[x]);
	}

	for(x=0 ; x<5 ; x++)
	{
		UART_sendByte(Password2[x]);
	}
}

/**************************************
 description:
 * Function to take password from user
 ***************************************/
void Enter_Password(void)
{
	uint8 x=0;
	LCD_clearScreen();
	LCD_moveCursor(0,0);
	LCD_displayString("Enter Password:");
	LCD_moveCursor(1,0);

	while(x<5)
	{
		key = KEYPAD_getPressedKey();
		if (key > 9 )
		{
			continue;
		}
		Password1[x] = key;
		LCD_displayCharacter('*');
		x++;
	}
}

/**********************************************************
 description:
 * Function to send password taken from user to control ECU
 **********************************************************/
void Send_Password(void)
{
	uint8 x;
	while(KEYPAD_getPressedKey()!= '=');

	for(x=0 ; x<5 ; x++)
	{
		UART_sendByte(Password1[x]);
	}
}

/**********************************************************
 description:
 * Function to enable timer for 3 seconds
 **********************************************************/
void wait_3_seconds(void)
{
	Timer1_ConfigType timer1_configPtr={CTC,POLLING,0,23438,CLK_1024};
	Timer1_init(&timer1_configPtr);
	while(BIT_IS_CLEAR(TIFR,OCF1A));
	Timer1_deInit();
	SET_BIT(TIFR,OCF1A);
}

/**********************************************************
 description:
 * Function to enable timer for 15 seconds
 **********************************************************/
void wait_15_seconds(void)
{
	uint8 x;
	Timer1_ConfigType timer1_configPtr={CTC,POLLING,0,23438,CLK_1024};
	for(x=0;x<5;x++)
	{
		Timer1_init(&timer1_configPtr);
		while(BIT_IS_CLEAR(TIFR,OCF1A));
		Timer1_deInit();
		SET_BIT(TIFR,OCF1A);
	}
}

/**********************************************************
 description:
 * Function to enable timer for 60 seconds
 **********************************************************/
void wait_60_seconds(void)
{
	uint8 x;
	Timer1_ConfigType timer1_configPtr={CTC,POLLING,0,23438,CLK_1024};
	for(x=0;x<12;x++)
	{
		Timer1_init(&timer1_configPtr);
		while(BIT_IS_CLEAR(TIFR,OCF1A));
		Timer1_deInit();
		SET_BIT(TIFR,OCF1A);
	}
}

/***********************************************************
 description:
 * Function indicates that password is incorrect for 3 times
 * display warning messages on LCD
 ***********************************************************/
void warning(void)
{
	LCD_clearScreen();
	LCD_moveCursor(0,5);
	LCD_displayString("ERROR");
	wait_60_seconds();
}

int main(void)
{
	uint8 trials = 0; /* Local Variable to count password trials*/

	/* Setting UART Configuration
	 * UART Enable
	 * Wait for Control ECU to get ready */
	UART_ConfigType UART_ptr={DISABLE,ONE_STOPBIT,EIGHT_BIT,9600};
	UART_init(&UART_ptr);
	while(UART_recieveByte() != Ctrl_ECU_READY){}

	LCD_init();

	while(1)
	{
		/* Setting Password for the system
		   Wait for confirmation from control ECU */
		do{
			SET_PASSWORD();
			PASSWORD_Confirmation();
			confirmation = UART_recieveByte();
		}while(confirmation != PASSWORD_CONFIRMED);


		do{
			/* System main menu */
			LCD_clearScreen();
			LCD_moveCursor(0,0);
			LCD_displayString("+ : Open Door");
			LCD_moveCursor(1,0);
			LCD_displayString("- : Change pass.");

			/* wait for user choice */
			do{
				key = KEYPAD_getPressedKey();
			}while(key != '+' && key != '-');

			/* Send user choice to Control ECU */
			UART_sendByte(key);

			/* user decided to open door */
			if( key == '+')
			{
				do{
					/* take password from user,send it to Control ECU */
					Enter_Password();
					Send_Password();

					/* open door if password confirmed */
					if(UART_recieveByte() == PASSWORD_CONFIRMED)
					{
						LCD_clearScreen();
						LCD_moveCursor(0,0);
						LCD_displayString("Door is opening");
						wait_15_seconds();

						LCD_clearScreen();
						LCD_moveCursor(0,1);
						LCD_displayString("Door is opened");
						wait_3_seconds();

						LCD_clearScreen();
						LCD_moveCursor(0,0);
						LCD_displayString("Door is closing");
						wait_15_seconds();

						/* in case password is not confirmed
						   from the first trial */
						trials = 0;

						/* Go bake to the system main menu */
						key = GO_TO_MENU;
						break;
					}

					else
					{
						/* in case password is not confirmed */
						trials++;
					}

				}while(trials<3);
			}

			/* user decided to change password */
			else if( key == '-')
			{
				do{
					/* take password from user,send it to Control ECU */
					Enter_Password();
					Send_Password();

					if(UART_recieveByte()==PASSWORD_CONFIRMED)
					{
						/* in case password is not confirmed
						   from the first trial */
						trials=0;

						/* Restart System */
						break;
					}
					else
					{
						/* in case password is not confirmed */
						trials++;
					}

				}while(trials<3);
			}

			/* if password were wrong for 3 times */
			if(trials==3)
			{
				warning();
				key = GO_TO_MENU;
			}
		}while(key == GO_TO_MENU);
	}
}
