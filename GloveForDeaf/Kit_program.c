/*
 * Kit_program.c
 *
 * Created: 3/2/2024 2:49:49 PM
 *  Author: HP
 */ 
//**********UTILES**********//
#include "STD_TYPES.h"
//**********MCAL**********//
#include "DIO_interface.h"
//**********HAL**********//
#include "Kit_interface.h"
#include "Kit_config.h"


u8 Kit_pushButton_isPressed(u8 button){
	u8 isPressed=0;
	switch(button){
		case BUTTON0:{
			isPressed=DIO_getPinValue(BUTTON0_PORT,BUTTON0_PIN);
			break;
		}
		case BUTTON1:{
			isPressed=DIO_getPinValue(BUTTON1_PORT,BUTTON1_PIN);
			break;
		}
		case BUTTON2:{
			isPressed=DIO_getPinValue(BUTTON2_PORT,BUTTON2_PIN);
			break;
		}
	}
	return isPressed;
}

void Kit_pushButton_init(u8 button){
	switch(button){
		case BUTTON0:{
			DIO_setPinDirection(BUTTON0_PORT,BUTTON0_PIN,DIO_PIN_INPUT);
			break;
		}
		case BUTTON1:{
			DIO_setPinDirection(BUTTON1_PORT,BUTTON1_PIN,DIO_PIN_INPUT);
			break;
		}
		case BUTTON2:{
			DIO_setPinDirection(BUTTON2_PORT,BUTTON2_PIN,DIO_PIN_INPUT);
			break;
		}
	}
}
void Kit_BUZ_init  (){
	DIO_setPinDirection(BUZZER_PORT,BUZZER_PIN,DIO_PIN_OUTPUT);
}
void Kit_BUZ_on    (){
	DIO_setPinValue(BUZZER_PORT,BUZZER_PIN,DIO_PIN_HIGH);
}
void Kit_BUZ_off   (){
	DIO_setPinValue(BUZZER_PORT,BUZZER_PIN,DIO_PIN_LOW);
}
void Kit_BUZ_toggle(){
	DIO_togglePinValue(BUZZER_PORT,BUZZER_PIN);
}

void Kit_LED_init  (u8 led){
	switch(led){
		case LED0:{
			DIO_setPinDirection(LED0_PORT,LED0_PIN,DIO_PIN_OUTPUT);
			break;
		}
		case LED1:{
			DIO_setPinDirection(LED1_PORT,LED1_PIN,DIO_PIN_OUTPUT);
			break;
		}
		case LED2:{
			DIO_setPinDirection(LED2_PORT,LED2_PIN,DIO_PIN_OUTPUT);
			break;
		}
	}
}
void Kit_LED_on    (u8 led){
	switch(led){
		case LED0:{
			DIO_setPinValue(LED0_PORT,LED0_PIN,DIO_PIN_HIGH);
			break;
		}
		case LED1:{
			DIO_setPinValue(LED1_PORT,LED1_PIN,DIO_PIN_HIGH);
			break;
		}
		case LED2:{
			DIO_setPinValue(LED2_PORT,LED2_PIN,DIO_PIN_HIGH);
			break;
		}
	}
}
void Kit_LED_off   (u8 led){
	switch(led){
		case LED0:{
			DIO_setPinValue(LED0_PORT,LED0_PIN,DIO_PIN_LOW);
			break;
		}
		case LED1:{
			DIO_setPinValue(LED1_PORT,LED1_PIN,DIO_PIN_LOW);
			break;
		}
		case LED2:{
			DIO_setPinValue(LED2_PORT,LED2_PIN,DIO_PIN_LOW);
			break;
		}
	}
}
void Kit_LED_toggle(u8 led){
	switch(led){
		case LED0:{
			DIO_togglePinValue(LED0_PORT,LED0_PIN);
			break;
		}
		case LED1:{
			DIO_togglePinValue(LED1_PORT,LED1_PIN);
			break;
		}
		case LED2:{
			DIO_togglePinValue(LED2_PORT,LED2_PIN);
			break;
		}
	}
}