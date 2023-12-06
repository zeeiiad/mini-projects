/*********************************************************
 * File Name:   Ctrl_APP_Layer.c
 * Description: Source File for Control ECU
 * Author:      Ziad Hesham Ghonim
 *********************************************************/

#include "UART.h"
#include "I2C.h"
#include "EEPROM.h"
#include "DcMotor.h"
#include "Timer1.h"
#include "common_macros.h"
#include "Buzzer.h"
#include <avr/io.h>
#include <util/delay.h>

/****************** Preprocessor Macros ******************/
#define Ctrl_ECU_READY    0x1
#define PASSWORD_CONFIRMED 1
#define PASSWORD_INCORRECT 0
#define GO_TO_MENU 0xFF

/********************* GLOBLE Variables *********************/
uint8 Password1[5];
uint8 Password2[5];
uint8 confirmation;

/**********************************************************
 description:
 * Function to receive the two passwords sent form HMI ECU
 * It compares them and see if they confirmed or not.
 **********************************************************/
void Confirm_Password(void)
{
	uint8 x;
	for(x=0 ; x<5 ; x++)
	{
		Password1[x] = UART_recieveByte();
	}

	for(x=0 ; x<5 ; x++)
	{
		Password2[x] = UART_recieveByte();
	}

	for(x=0 ; x<5 ; x++)
	{
		if(Password1[x] != Password2[x])
		{
			confirmation =  PASSWORD_INCORRECT;
			break;
		}
		else if (Password1[4] == Password2[4])
		{
			confirmation =  PASSWORD_CONFIRMED;
		}
	}
}

/**********************************************************
 description:
 * Function to save system password to EEPROM
 **********************************************************/
void SaveToEEPROM(uint8 pass[])
{
	uint16 i;
	for(i=0 ; i<5 ; i++)
	{
		EEPROM_writeByte(0x0030+i,pass[i]);
		_delay_ms(10);
	}
}

/**********************************************************
 description:
 * Function to receive password taken from user
 **********************************************************/
void Receive_Password(void)
{
	uint8 x;
	for(x=0 ; x<5 ; x++)
	{
		Password1[x]= UART_recieveByte();
	}
}

/*****************************************************************************
 description:
 * Function to compare the password taken from user to the one saved in EEPROM
 *****************************************************************************/
uint8 Compare_To_EEPROM(void)
{
	uint8 EEPROM_ELEMENT;
	uint8 x;
	for(x=0 ; x<5 ; x++)
	{
		EEPROM_readByte(0x0030+x,&EEPROM_ELEMENT);
		if(Password1[x] != EEPROM_ELEMENT)
		{
			return PASSWORD_INCORRECT;
		}
	}
	return PASSWORD_CONFIRMED;
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
 * Enable buzzer for 60 second
 ***********************************************************/
void warning(void)
{
	Buzzer_on();
	wait_60_seconds();
	Buzzer_off();
}

int main(void)
{
	uint8 trials = 0; /* Local Variable to count password trials*/
	uint8 key;

	/* Setting UART Configuration
	 * UART Enable
	 * Send Ready to HMI ECU */
	UART_ConfigType UART_ptr={DISABLE,ONE_STOPBIT,EIGHT_BIT,9600};
	UART_init(&UART_ptr);
	UART_sendByte(Ctrl_ECU_READY);

	/* Setting I2C Configuration
	 * I2c Enable*/
	TWI_ConfigType TWI_ptr={1,FAST_MODE};
	TWI_init(&TWI_ptr);

	DcMotor_init();
	Buzzer_init();

	while(1)
	{
		/* Setting Password for the system
		   send confirmation to HMI ECU */
		do{
			Confirm_Password();
			UART_sendByte(confirmation);
		}while(confirmation != PASSWORD_CONFIRMED);

		/* Save system password to EEPROM */
		SaveToEEPROM(Password1);

		do{
			/* receive user choice */
			key = UART_recieveByte();

			/* user decided to open door */
			if(key == '+')
			{
				do{
					/* receive password taken from user
					 * compare it to the system password saved at EEPROM*/
					Receive_Password();
					confirmation=Compare_To_EEPROM();

					/* send password confirmation to HMI ECU */
					UART_sendByte(confirmation);

					/* open door if password confirmed */
					if(confirmation == PASSWORD_CONFIRMED)
					{
						DcMotor_Rotate(CW,100);
						wait_15_seconds();

						DcMotor_Rotate(OFF,0);
						wait_3_seconds();

						DcMotor_Rotate(ACW,100);
						wait_15_seconds();
						DcMotor_Rotate(OFF,0);

						/* in case password is not confirmed
						   from the first trial */
						trials=0;

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
			else if (key == '-')
			{
				do{
					/* receive password taken from user
					   compare it to the system password saved at EEPROM*/
					Receive_Password();
					confirmation=Compare_To_EEPROM();
					UART_sendByte(confirmation);

					if(confirmation == PASSWORD_CONFIRMED)
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
