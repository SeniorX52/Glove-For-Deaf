/*
 * Kit_config.h
 *
 * Created: 3/2/2024 2:57:36 PM
 *  Author: HP
 */ 


#ifndef KIT_CONFIG_H_
#define KIT_CONFIG_H_
#include "DIO_interface.h"



#define LED0_PORT					DIO_PORTC
#define LED1_PORT					DIO_PORTC		
#define LED2_PORT					DIO_PORTD		

#define LED0_PIN					DIO_PIN2
#define LED1_PIN					DIO_PIN7
#define LED2_PIN					DIO_PIN3	

#define BUTTON0_PORT				DIO_PORTB
#define BUTTON1_PORT				DIO_PORTD
#define BUTTON2_PORT				DIO_PORTD

#define BUTTON0_PIN					DIO_PIN0
#define BUTTON1_PIN					DIO_PIN6
#define BUTTON2_PIN					DIO_PIN2

#define BUZZER_PORT					DIO_PORTA
#define BUZZER_PIN					DIO_PIN3				



#endif /* KIT_CONFIG_H_ */