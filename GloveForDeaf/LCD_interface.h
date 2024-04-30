/*
 * LCD_interface.h
 *
 * Created: 12/18/2023 8:07:10 PM
 *  Author: Mostafa
 */ 


#ifndef LCD_INTERFACE_H_
#define LCD_INTERFACE_H_


/* Macros For LCD Shifting Direction */
#define LCD_SHIFT_LEFT          1
#define LCD_SHIFT_RIGHT         2

/* Macros For LCD Line Id */
#define LCD_LINE_ONE            1
#define LCD_LINE_TWO            2


void LCD_init                (void);
void LCD_sendCmnd            (u8 cmnd);
void LCD_sendChar            (u8 data);
void LCD_clear               (void);
void LCD_writeString         (u8* string);
void LCD_shift               (u8 shifttingDirection);
void LCD_goToSpecificPosition(u8 LineNumber, u8 Position);
void LCD_writeNumber         (u32 number);
void LCD_defineCustomCharacter(u8 location,u8 *pattern);

#endif /* LCD_INTERFACE_H_ */