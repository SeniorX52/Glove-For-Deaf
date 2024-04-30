/*
 * Kit.h
 *
 * Created: 3/2/2024 2:49:34 PM
 *  Author: HP
 */ 


#ifndef KIT_H_
#define KIT_H_

#include "STD_TYPES.h"

#define LED0						0
#define LED1						1
#define LED2						2

#define BUTTON0						0
#define BUTTON1						1
#define BUTTON2						2


//Buzzer
void Kit_BUZ_init  ();
void Kit_BUZ_on    ();
void Kit_BUZ_off   ();
void Kit_BUZ_toggle();

//LED
void Kit_LED_init  (u8 led);
void Kit_LED_on    (u8 led);
void Kit_LED_off   (u8 led);
void Kit_LED_toggle(u8 led);

u8 Kit_pushButton_isPressed(u8 button);
void Kit_pushButton_init(u8 button);



#endif /* KIT_H_ */