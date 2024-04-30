/*
 * main.h
 *
 * Created: 3/2/2024 3:37:25 PM
 *  Author: HP
 */ 


#ifndef MAIN_H_
#define MAIN_H_


//Main functions for LCD interface

void mainMenu			(void);
void chooseProfile		(void);
void speechMode			(void);
void controlMode		(void);
void start_1			(void);
void chooseMode			(void);
void overrideProfile	(void);
void initialize			(void);
void LEDS_ON			(void);
void LEDS_OFF			(void);
void BUZZ				(void);
void goBack				(void);
void backMenu			(void);
void settings			(void);
void clearData			(void);
void changePassword		(void);

//Debugging functions
void freeHandMode		(void);
void EEPROM_debug		(u16 address);
#endif /* MAIN_H_ */