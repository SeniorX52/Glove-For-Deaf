/*
 * Glove_config.h
 *
 * Created: 2/18/2024 11:23:53 PM
 *  Author: HP
 */ 


#ifndef GLOVE_CONFIG_H_
#define GLOVE_CONFIG_H_
#include "DIO_interface.h"
#include "ADC_interface.h"
#define GLOVE_FINGER1_PORT				DIO_PORTA
#define GLOVE_FINGER2_PORT				DIO_PORTA
#define GLOVE_FINGER3_PORT				DIO_PORTA
#define GLOVE_FINGER4_PORT				DIO_PORTA
#define GLOVE_FINGER5_PORT				DIO_PORTA

#define GLOVE_FINGER1_PIN				DIO_PIN0
#define GLOVE_FINGER2_PIN				DIO_PIN4
#define GLOVE_FINGER3_PIN				DIO_PIN5
#define GLOVE_FINGER4_PIN				DIO_PIN6
#define GLOVE_FINGER5_PIN				DIO_PIN7

#define GLOVE_FINGER1					ADC_CHANNEL0
#define GLOVE_FINGER2					ADC_CHANNEL4
#define GLOVE_FINGER3					ADC_CHANNEL5
#define GLOVE_FINGER4					ADC_CHANNEL6
#define GLOVE_FINGER5					ADC_CHANNEL7


#define GLOVE_ADC_REF					ADC_REFERENCE_AVCC

#define GLOVE_CONSTANT					0.25

#endif /* GLOVE_CONFIG_H_ */