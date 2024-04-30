/*
 * Glove_program.c
 *
 * Created: 2/18/2024 11:56:37 PM
 *  Author: HP
 */ 
//**********UTILES**********//
#include "STD_TYPES.h"
//**********MCAL**********//
#include "DIO_interface.h"
#include "ADC_interface.h"
//**********HAL**********//
#include "Glove_interface.h"
#include "Glove_config.h"

void Glove_init(void){
	DIO_setPinDirection(GLOVE_FINGER1_PORT,GLOVE_FINGER1_PIN,DIO_PIN_INPUT);
	DIO_setPinDirection(GLOVE_FINGER2_PORT,GLOVE_FINGER2_PIN,DIO_PIN_INPUT);
	DIO_setPinDirection(GLOVE_FINGER3_PORT,GLOVE_FINGER3_PIN,DIO_PIN_INPUT);
	DIO_setPinDirection(GLOVE_FINGER4_PORT,GLOVE_FINGER4_PIN,DIO_PIN_INPUT);
	DIO_setPinDirection(GLOVE_FINGER5_PORT,GLOVE_FINGER5_PIN,DIO_PIN_INPUT);
	ADC_init(GLOVE_ADC_REF);
}
u16 Glove_getFingerValue(u8 finger){
	u16 digitalValue=ADC_getDigitalValue(finger);
	return digitalValue*GLOVE_CONSTANT;
}