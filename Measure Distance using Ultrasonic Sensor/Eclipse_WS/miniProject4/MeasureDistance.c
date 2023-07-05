/*************************************************
 * Project:     Distance Measurement
 * File Name:   MeasureDistance.c
 * Description: Project Application Layer (App.)
 * Author:      Ziad Hesham Ghonim
 *************************************************/

#include "My_LCD.h"
#include "icu.h"
#include "ultrasonic.h"
#include "My_Common_Macros.h"
#include "My_Standard_types.h"
#include <avr/io.h>


int main()
{
	LCD_init();
	LCD_displayStringRowColumn(0,0,"Measure Distance");
	LCD_displayStringRowColumn(1,0,"using ultrasonic");
	LCD_displayStringRowColumn(2,0,"  By:ENG. Ziad  ");
	LCD_displayStringRowColumn(3,0,"Distance=     CM");

	/* Enable Global Interrupt */
	SET_BIT(SREG,7);

	uint16 Distance = 0;

	Ultrasonic_init();

	while(1)
	{

		Distance = Ultrasonic_readDistance();
		LCD_moveCursor(3,10);
		LCD_integerToString(Distance);
		if(Distance<100)
			LCD_displayString(" ");
		if(Distance<10)
			LCD_displayString("  ");
	}
}
