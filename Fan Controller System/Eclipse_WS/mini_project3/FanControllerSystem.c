#include "My_LCD.h"
#include "lm35_sensor.h"
#include "DcMotor.h"
#include "My_ADC.h"
#include <util/delay.h>

int main(void)
{
	uint8 temprature;
	ADC_ConfigType ADC_configurations = {INT_REF_VOLT,F_CPU_8};
	ADC_init(&ADC_configurations);
	LCD_init();
	DcMotor_init();

	LCD_displayStringRowColumn(0,1,"Fan Controller");
	LCD_displayStringRowColumn(1,5,"System.");
	_delay_ms(2000);

	LCD_clearScreen();
	LCD_moveCursor(0,0);

	LCD_displayStringRowColumn(0,4,"Fan is ");
	LCD_displayStringRowColumn(1,2,"Temp. =     C");
	while(1)
	{
		temprature=LM35_getTemperature();
		if(temprature < 30)
		{
			DcMotor_Rotate(OFF,0);
			LCD_displayStringRowColumn(0,11,"OFF");
			LCD_moveCursor(1,10);
			LCD_integerToString(temprature);
			if(temprature<10)
				LCD_displayString(" ");
		}
		else if(temprature >= 30 && temprature < 60)
		{
			DcMotor_Rotate(CW,25);
			LCD_displayStringRowColumn(0,11,"ON ");
			LCD_moveCursor(1,10);
			LCD_integerToString(temprature);
		}
		else if(temprature >= 60 && temprature < 90)
		{
			DcMotor_Rotate(CW,50);
			LCD_displayStringRowColumn(0,11,"ON ");
			LCD_moveCursor(1,10);
			LCD_integerToString(temprature);
		}
		else if(temprature >= 90 && temprature < 120)
		{
			DcMotor_Rotate(CW,75);
			LCD_displayStringRowColumn(0,11,"ON ");
			LCD_moveCursor(1,10);
			LCD_integerToString(temprature);
			if(temprature<100)
				LCD_displayString(" ");
		}
		else if(temprature >= 120)
		{
			DcMotor_Rotate(CW,100);
			LCD_displayStringRowColumn(0,11,"ON ");
			LCD_moveCursor(1,10);
			LCD_integerToString(temprature);
		}

	}
}
