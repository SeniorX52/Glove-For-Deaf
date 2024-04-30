/*
 * LCD_program.c
 *
 * Created: 12/23/2023 4:25:45 AM
 *  Author: study
 */ 
#define F_CPU 16000000UL
#include <util/delay.h>

/* UTILES_LIB */
#include "STD_TYPES.h"
#include "BIT_MATH.h"

/* MCAL */
#include "DIO_interface.h"

/* HAL */
#include "LCD_interface.h"
#include "LCD_config.h"


void LCD_init(void)
{
	// Intialize LCD pins As OutPut Pins
	DIO_setPinDirection(LCD_RS_PORT,LCD_RS_PIN,DIO_PIN_OUTPUT);
	DIO_setPinDirection(LCD_RW_PORT,LCD_RW_PIN,DIO_PIN_OUTPUT);
	DIO_setPinDirection(LCD_E_PORT ,LCD_E_PIN ,DIO_PIN_OUTPUT);
	DIO_setPinDirection(LCD_D4_PORT,LCD_D4_PIN,DIO_PIN_OUTPUT);
	DIO_setPinDirection(LCD_D5_PORT,LCD_D5_PIN,DIO_PIN_OUTPUT);
	DIO_setPinDirection(LCD_D6_PORT,LCD_D6_PIN,DIO_PIN_OUTPUT);
	DIO_setPinDirection(LCD_D7_PORT,LCD_D7_PIN,DIO_PIN_OUTPUT);
	_delay_ms(35);
	
	// set Rs pin = 0 (write command)
	DIO_setPinValue(LCD_RS_PORT,LCD_RS_PIN,DIO_PIN_LOW);
	// set Rw pin = 0 (write)
	DIO_setPinValue(LCD_RW_PORT,LCD_RW_PIN,DIO_PIN_LOW);
	DIO_setPinValue(LCD_D4_PORT,LCD_D4_PIN,0);
	DIO_setPinValue(LCD_D5_PORT,LCD_D5_PIN,1);
	DIO_setPinValue(LCD_D6_PORT,LCD_D6_PIN,0);
	DIO_setPinValue(LCD_D7_PORT,LCD_D7_PIN,0);
	/* Enable Pulse *//* H => L */
	DIO_setPinValue(LCD_E_PORT,LCD_E_PIN,DIO_PIN_HIGH);
	_delay_ms(1);
	DIO_setPinValue(LCD_E_PORT,LCD_E_PIN,DIO_PIN_LOW);
	// Function Set command 2*16 LCD , 4 Bit Mode
	LCD_sendCmnd(0b00101000);
	_delay_us(45);
	
	
	// Display on off Control (DisplayOn, Cursor on, Blink on)
	LCD_sendCmnd(0b00001111);
	_delay_us(45);
	
	// Clear Display
	LCD_sendCmnd(0b00000001);
	_delay_ms(2);
	
	// Set Entry Mode (IncrementOn, ShiftOff)
	LCD_sendCmnd(0b00000110);
}


void LCD_sendCmnd(u8 cmnd)
{
	// set Rs pin = 0 (write command)
	DIO_setPinValue(LCD_RS_PORT,LCD_RS_PIN,DIO_PIN_LOW);
	
	// set Rw pin = 0 (write)
	DIO_setPinValue(LCD_RW_PORT,LCD_RW_PIN,DIO_PIN_LOW);
	
	// Write The Most 4 bits Of command on Data Pins
	DIO_setPinValue(LCD_D4_PORT,LCD_D4_PIN,GET_BIT(cmnd,4));
	DIO_setPinValue(LCD_D5_PORT,LCD_D5_PIN,GET_BIT(cmnd,5));
	DIO_setPinValue(LCD_D6_PORT,LCD_D6_PIN,GET_BIT(cmnd,6));
	DIO_setPinValue(LCD_D7_PORT,LCD_D7_PIN,GET_BIT(cmnd,7));
	
	/* Enable Pulse *//* H => L */
	DIO_setPinValue(LCD_E_PORT,LCD_E_PIN,DIO_PIN_HIGH);
	_delay_ms(1);
	DIO_setPinValue(LCD_E_PORT,LCD_E_PIN,DIO_PIN_LOW);
	
	// Write The Least 4 bits Of command on Data Pins
	DIO_setPinValue(LCD_D4_PORT,LCD_D4_PIN,GET_BIT(cmnd,0));
	DIO_setPinValue(LCD_D5_PORT,LCD_D5_PIN,GET_BIT(cmnd,1));
	DIO_setPinValue(LCD_D6_PORT,LCD_D6_PIN,GET_BIT(cmnd,2));
	DIO_setPinValue(LCD_D7_PORT,LCD_D7_PIN,GET_BIT(cmnd,3));
	
	/* Enable Pulse *//* H => L */
	DIO_setPinValue(LCD_E_PORT,LCD_E_PIN,DIO_PIN_HIGH);
	_delay_ms(1);
	DIO_setPinValue(LCD_E_PORT,LCD_E_PIN,DIO_PIN_LOW);
}


void LCD_sendChar(u8 data)
{
	// set Rs pin = 1 (write data)
	DIO_setPinValue(LCD_RS_PORT,LCD_RS_PIN,DIO_PIN_HIGH);
	
	// set Rw pin = 0 (write)
	DIO_setPinValue(LCD_RW_PORT,LCD_RW_PIN,DIO_PIN_LOW);
	
	// Write The Most 4 bits Of data on Data Pins
	DIO_setPinValue(LCD_D4_PORT,LCD_D4_PIN,GET_BIT(data,4));
	DIO_setPinValue(LCD_D5_PORT,LCD_D5_PIN,GET_BIT(data,5));
	DIO_setPinValue(LCD_D6_PORT,LCD_D6_PIN,GET_BIT(data,6));
	DIO_setPinValue(LCD_D7_PORT,LCD_D7_PIN,GET_BIT(data,7));
	
	/* Enable Pulse *//* H => L */
	DIO_setPinValue(LCD_E_PORT,LCD_E_PIN,DIO_PIN_HIGH);
	_delay_ms(1);
	DIO_setPinValue(LCD_E_PORT,LCD_E_PIN,DIO_PIN_LOW);
	
	// Write The Least 4 bits Of data on Data Pins
	DIO_setPinValue(LCD_D4_PORT,LCD_D4_PIN,GET_BIT(data,0));
	DIO_setPinValue(LCD_D5_PORT,LCD_D5_PIN,GET_BIT(data,1));
	DIO_setPinValue(LCD_D6_PORT,LCD_D6_PIN,GET_BIT(data,2));
	DIO_setPinValue(LCD_D7_PORT,LCD_D7_PIN,GET_BIT(data,3));
	
	/* Enable Pulse *//* H => L */
	DIO_setPinValue(LCD_E_PORT,LCD_E_PIN,DIO_PIN_HIGH);
	_delay_ms(1);
	DIO_setPinValue(LCD_E_PORT,LCD_E_PIN,DIO_PIN_LOW);
}


void LCD_clear(void)
{
	// Clear Display
	LCD_sendCmnd(0b00000001);
	_delay_ms(2);
}


void LCD_writeString(u8* string)
{
	if(string!=NULL)
	{
		u8 counter = 0;
		while(string[counter]!='\0')
		{
			LCD_sendChar(string[counter]);
			counter++;
		}
		if(counter>16){
			_delay_ms(1000);
			for(u8 i=0;i<counter-16;i++){
				LCD_shift(LCD_SHIFT_LEFT);
				_delay_ms(200);
			}
		}
	}
}


void LCD_shift(u8 shifttingDirection)
{
	switch(shifttingDirection)
	{
		case LCD_SHIFT_RIGHT:
		LCD_sendCmnd(0b00011100);
		_delay_us(45);
		break;
		
		case LCD_SHIFT_LEFT:
		LCD_sendCmnd(0b00011000);
		_delay_us(45);
		break;
	}
}


void LCD_goToSpecificPosition(u8 LineNumber, u8 Position)
{
	switch(LineNumber)
	{
		case LCD_LINE_ONE:
		LCD_sendCmnd(0x80+Position);
		_delay_us(45);
		break;
		
		case LCD_LINE_TWO:
		LCD_sendCmnd(0xc0+Position);
		_delay_us(45);
		break;
	}
}


void LCD_writeNumber(u32 number)
{
	u32 reversedNum = 1;
	
	if(number == 0)
	{
		LCD_sendChar('0');
	}
	else
	{
		// reverse the number
		while(number != 0)
		{
			reversedNum = reversedNum*10 + number%10;
			number /= 10;
		}
		
		
		do
		{
			LCD_sendChar(reversedNum%10 + '0');
			reversedNum /= 10;
		}
		while(reversedNum != 1);
	}
}
void LCD_defineCustomCharacter(u8 location,u8 *pattern) {
	// Set CGRAM address
	LCD_sendCmnd(0b01000000 | (location << 3));
	// Write pattern to CGRAM
	for (u8 i = 0; i < 8; i++) {
		LCD_sendChar(pattern[i]);
	}
}
