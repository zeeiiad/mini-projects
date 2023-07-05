/*************************************************
 * Project:     Simple Calculator using AtMega32
 * File Name:   simplecalculator.c
 * Author:      Ziad Hesham Ghonim
 *************************************************/

#include "My_Keypad.h"
#include "My_LCD.h"
#include <util/delay.h>
#include <string.h>

uint8 simple_calculator(uint8 value1,uint8 operator,uint8 value2)
{
	uint8 result;
	switch (operator)
	{
	case'+': result=value1+value2;
	         break;
	case'-': result=value1-value2;
	         break;
	case'*': result=value1*value2;
             break;
	case'/': result=value1/value2;
	         break;
	}
	return result;
}

int main(void)
{
	uint8 key;

	uint8 value1;
	uint8 operator;
	uint8 value2;
	uint8 result;

	LCD_init();
    LCD_displayStringRowColumn(0,0,"SimpleCalculator");
	LCD_displayStringRowColumn(1,0,"Eng: Ziad Hesham");
	_delay_ms(1500);
	LCD_clearScreen();
	LCD_moveCursor(0,0);

	while(1)
	{
		if((key=KEYPAD_getPressedKey())==13)
		{
			LCD_clearScreen();
			LCD_moveCursor(0,0);
			_delay_ms(500);
		}
		else
		{
			key = KEYPAD_getPressedKey();
			value1 = key;
			LCD_intgerToString(key);
			_delay_ms(500);


			key = KEYPAD_getPressedKey();
			operator = key;
			LCD_displayCharacter(key);
			_delay_ms(500);

			key = KEYPAD_getPressedKey();
			value2 = key;
			LCD_intgerToString(key);
			_delay_ms(500);


			if((key=KEYPAD_getPressedKey())=='=')
			{
				LCD_displayString("=");
				LCD_moveCursor(1,0);
				result=simple_calculator(value1,operator,value2);
				LCD_intgerToString(result);
				_delay_ms(500);
			}
		}
	}
}
