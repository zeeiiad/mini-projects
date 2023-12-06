 /******************************************************************************
 * Module: I2C(TWI)
 * File Name: I2C.c
 * Description: Source file for the TWI(I2C) AVR driver
 * Author: Ziad Hesham Ghonim
 *******************************************************************************/

#include "I2C.h"
#include "Common_Macros.h"
#include <avr/io.h>

/*********************************************************
                   Functions Declaration
 *********************************************************/

/******************************************
 Description :
 * Function to initialize the I2C driver.
 ******************************************/
void TWI_init(TWI_ConfigType* config_ptr)
{
#if (F_CPU == 1000000UL)
	/***********************************************************************************************************
	 according to SCL frequency = F_CPU / 16+2(TWBR).4^TWPS
	 - SCL is the data transfer rate decided by the user (NORMAL_MODE,FAST_MODE)
	 - using zero pre-scaler TWPS=00
	 - F_CPU is predefined by eclipse (we use 8Mhz for this project)
	 calculating the TWBR: a negative value appears on the LHS of the equation(TWBR can not be a negative value)
	 ***********************************************************************************************************/
#error "TWI Driver can not be used at F_CPU = 1Mhz."

#elif(F_CPU == 8000000UL)
	{
		if(config_ptr->bit_rate == NORMAL_MODE)
		{
			/***********************************************************************
			 according to SCL frequency = F_CPU / 16+2(TWBR).4^TWPS
			 - SCL is the data transfer rate decided by the user (NORMAL_MODE)
			 - using zero pre-scaler TWPS=00
			 - F_CPU is predefined by eclipse (we use 8Mhz for this project)
			 calculating the TWBR
			 ************************************************************************/
			TWBR = 0x20;
			TWSR = 0x00;
		}
		else if(config_ptr->bit_rate == FAST_MODE)
		{
			/***********************************************************************
			according to SCL frequency = F_CPU / 16+2(TWBR).4^TWPS
			- SCL is the data transfer rate decided by the user (FAST_MODE)
			- using zero pre-scaler TWPS=00
			- F_CPU is predefined by eclipse (we use 8Mhz for this project)
			calculating the TWBR
			*************************************************************************/
			TWBR = 0x02;
			TWSR = 0x00;
		}
	}
#elif((F_CPU) == 16000000UL)
	{
		if(config_ptr->bit_rate == NORMAL_MODE)
		{
			/***********************************************************************
			according to SCL frequency = F_CPU / 16+2(TWBR).4^TWPS
			- SCL is the data transfer rate decided by the user (NORMAL_MODE)
			- using zero pre-scaler TWPS=00
			- F_CPU is predefined by eclipse (we use 8Mhz for this project)
			calculating the TWBR
			************************************************************************/
			TWBR = 0x48;
			TWSR = 0x00;
		}
		else if(config_ptr->bit_rate == FAST_MODE)
		{
			/***********************************************************************
			according to SCL frequency = F_CPU / 16+2(TWBR).4^TWPS
			- SCL is the data transfer rate decided by the user (FAST_MODE)
			- using zero pre-scaler TWPS=00
			- F_CPU is predefined by eclipse (we use 8Mhz for this project)
			calculating the TWBR
			************************************************************************/
			TWBR = 0x0C;
			TWSR = 0x00;
		}
	}
#endif

    /* Two Wire Bus address my address if any master device want to call me: 0x1
     * (used in case this MC is a slave device)
     * General Call Recognition: Off */
    TWAR = ((config_ptr->address)<<1);     // my address = address

    TWCR = (1<<TWEN);                      // enable TWI
}

void TWI_start(void)
{
    /*
	 * Clear the TWINT flag before sending the start bit TWINT=1
	 * send the start bit by TWSTA=1
	 * Enable TWI Module TWEN=1
	 */
    TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);

    /* Wait for TWINT flag set in TWCR Register (start bit is send successfully) */
    while(BIT_IS_CLEAR(TWCR,TWINT));
}

void TWI_stop(void)
{
    /*
	 * Clear the TWINT flag before sending the stop bit TWINT=1
	 * send the stop bit by TWSTO=1
	 * Enable TWI Module TWEN=1
	 */
    TWCR = (1 << TWINT) | (1 << TWSTO) | (1 << TWEN);
}

void TWI_writeByte(uint8 data)
{
    /* Put data On TWI data Register */
    TWDR = data;
    /*
	 * Clear the TWINT flag before sending the data TWINT=1
	 * Enable TWI Module TWEN=1
	 */
    TWCR = (1 << TWINT) | (1 << TWEN);
    /* Wait for TWINT flag set in TWCR Register(data is send successfully) */
    while(BIT_IS_CLEAR(TWCR,TWINT));
}

uint8 TWI_readByteWithACK(void)
{
	/*
	 * Clear the TWINT flag before reading the data TWINT=1
	 * Enable sending ACK after reading or receiving data TWEA=1
	 * Enable TWI Module TWEN=1
	 */
    TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWEA);
    /* Wait for TWINT flag set in TWCR Register (data received successfully) */
    while(BIT_IS_CLEAR(TWCR,TWINT));
    /* Read Data */
    return TWDR;
}

uint8 TWI_readByteWithNACK(void)
{
	/*
	 * Clear the TWINT flag before reading the data TWINT=1
	 * Enable TWI Module TWEN=1
	 */
    TWCR = (1 << TWINT) | (1 << TWEN);
    /* Wait for TWINT flag set in TWCR Register (data received successfully) */
    while(BIT_IS_CLEAR(TWCR,TWINT));
    /* Read Data */
    return TWDR;
}

uint8 TWI_getStatus(void)
{
    uint8 status;
    /* masking to eliminate first 3 bits and get the last 5 bits (status bits) */
    status = TWSR & 0xF8;
    return status;
}
