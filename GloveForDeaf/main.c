/*
 * GloveForDeaf.c
 *
 * Created: 3/1/2024 3:08:43 PM
 * Author : HP
 */ 

#define F_CPU 16000000UL
#include <util/delay.h>
//**********UTILES**********//
#include "STD_TYPES.h"
//**********MCAL**********//
#include "main.h"
//**********HAL**********//
#include "GloveForDeaf_interface.h"
#include "LCD_interface.h"
#include "Kit_interface.h"


int main(void)
{
	start_1();
	
}
void start_1(){
	initialize();
	/*To reset password when forgotten,
	burn the hex file again without 
	loading the password from memory*/
	//GloveForDeaf_passwordCheck();
	mainMenu();
}
//Useful for EEPROM debugging
void EEPROM_debug(u16 address){
	initialize();
	GloveForDeaf_loadProfile(PROFILE1);
	u8 array[5]={0,0,0,0,0};
	GloveForDeaf_loadValues(PROFILE1,array,address);
	GloveForDeaf_displayArray(array);
}

void freeHandMode(){
	while(1){
		GloveForDeaf_getFingerValues();
		GloveForDeaf_displayFingerValues();
		_delay_ms(LCD_LATENCY);
	}
}

void initialize(){
	
	//For future use of interrupts
	//GI_enable();
	//EXTI_enable(EXTI_INT0,EXTI_RISING_EDGE);
	//EXTI_setCallBackINT0(goBack);
	Kit_BUZ_init();
	Kit_pushButton_init(BUTTON0);
	Kit_pushButton_init(BUTTON1);
	Kit_pushButton_init(BUTTON2);
	Kit_LED_init(LED0);
	Kit_LED_init(LED1);
	Kit_LED_init(LED2);
	GloveForDeaf_setCallBackControl(LEDS_ON,CONTROL0);
	GloveForDeaf_setCallBackControl(LEDS_OFF,CONTROL1);
	GloveForDeaf_setCallBackControl(BUZZ,CONTROL2);
	GloveForDeaf_init();
	GloveForDeaf_loadPassword();
}
void LEDS_ON(void){
	Kit_LED_on(LED0);
	Kit_LED_on(LED1);
	Kit_LED_on(LED2);
}
void LEDS_OFF(void){
	Kit_LED_off(LED0);
	Kit_LED_off(LED1);
	Kit_LED_off(LED2);
}
void BUZZ(void){
	Kit_BUZ_on();
	_delay_ms(1000);
	Kit_BUZ_off();
}
void mainMenu(void){
	LCD_clear();
	LCD_goToSpecificPosition(LCD_LINE_ONE,0);
	LCD_writeString((u8*)"0-Load Profile");
	LCD_goToSpecificPosition(LCD_LINE_TWO,0);
	LCD_writeString((u8*)"1-New Profile");
	//Busy wait till user choose
	while(Kit_pushButton_isPressed(BUTTON0)==0 
	&& Kit_pushButton_isPressed(BUTTON1)==0 
	&&Kit_pushButton_isPressed(BUTTON2)==0);
	if(Kit_pushButton_isPressed(BUTTON0)){
		_delay_ms(PUSH_BUTTON_LATENCY);
		chooseProfile();
	}
	else{
		if(Kit_pushButton_isPressed(BUTTON1)){
			_delay_ms(PUSH_BUTTON_LATENCY);
			overrideProfile();
		}
		else{
			_delay_ms(PUSH_BUTTON_LATENCY);
			backMenu();
		}
		
	}
	
}
void chooseProfile(){
	LCD_clear();
	LCD_goToSpecificPosition(LCD_LINE_ONE,0);
	LCD_writeString((u8*)"0-Profile 1");
	if(PROFILES_USED==2){
		LCD_goToSpecificPosition(LCD_LINE_TWO,0);
		LCD_writeString((u8*)"1-Profile 2");
	}
	while(Kit_pushButton_isPressed(BUTTON0)==0 
	&& ((Kit_pushButton_isPressed(BUTTON1)==0)||(PROFILES_USED!=2))
	&&Kit_pushButton_isPressed(BUTTON2)==0);
	if(Kit_pushButton_isPressed(BUTTON0)){
		_delay_ms(PUSH_BUTTON_LATENCY);
		GloveForDeaf_loadProfile(PROFILE1);
	}
	else{
		if(Kit_pushButton_isPressed(BUTTON1)&&(PROFILES_USED==2)){
			_delay_ms(PUSH_BUTTON_LATENCY);
			GloveForDeaf_loadProfile(PROFILE2);
		}
		else{
			_delay_ms(PUSH_BUTTON_LATENCY);
			mainMenu();
			return;
		}
	}
	chooseMode();
}
void chooseMode(void){
	LCD_clear();
	LCD_goToSpecificPosition(LCD_LINE_ONE,0);
	LCD_writeString((u8*)"0-Speech Mode");
	LCD_goToSpecificPosition(LCD_LINE_TWO,0);
	LCD_writeString((u8*)"1-Control Mode");
	while(Kit_pushButton_isPressed(BUTTON0)==0 
	&& Kit_pushButton_isPressed(BUTTON1)==0
	&& Kit_pushButton_isPressed(BUTTON2)==0);
	if(Kit_pushButton_isPressed(BUTTON0)){
		_delay_ms(PUSH_BUTTON_LATENCY);
		speechMode();
	}
	else{
		if(Kit_pushButton_isPressed(BUTTON1)){
			_delay_ms(PUSH_BUTTON_LATENCY);
			controlMode();
		}
		else{
			_delay_ms(PUSH_BUTTON_LATENCY);
			mainMenu();
		}
	}
}
void speechMode(){
	LCD_clear();
	while(1){
		GloveForDeaf_getFingerValues();
		u8 posture=GloveForDeaf_getSpeechPosture();
		GloveForDeaf_printSpeechPosture(posture);
		if(Kit_pushButton_isPressed(BUTTON2)){
			_delay_ms(PUSH_BUTTON_LATENCY);
			chooseMode();
		}
		_delay_ms(LCD_LATENCY);
	}
}
void controlMode(){
	LCD_clear();
	while(1){
		GloveForDeaf_getFingerValues();
		u8 posture=GloveForDeaf_getControlPosture();
		GloveForDeaf_executeControl(posture);
		if(Kit_pushButton_isPressed(BUTTON2)){
			_delay_ms(PUSH_BUTTON_LATENCY);
			chooseMode();
		}
		_delay_ms(LCD_LATENCY);
	}
}
void overrideProfile(){
	LCD_clear();
	LCD_goToSpecificPosition(LCD_LINE_ONE,0);
	LCD_writeString((u8*)"0-Profile_1");
	if(PROFILES_USED==2){
		LCD_goToSpecificPosition(LCD_LINE_TWO,0);
		LCD_writeString((u8*)"1-Profile_2");
	}
	while(Kit_pushButton_isPressed(BUTTON0)==0 
	&&((Kit_pushButton_isPressed(BUTTON1)==0)||(PROFILES_USED==1))
	&& Kit_pushButton_isPressed(BUTTON2)==0);
	if(Kit_pushButton_isPressed(BUTTON0)){
		_delay_ms(PUSH_BUTTON_LATENCY);
		GloveForDeaf_createNewProfile(PROFILE1);
		
	}
	else{
		if(Kit_pushButton_isPressed(BUTTON1)&&(PROFILES_USED==2)){
			_delay_ms(PUSH_BUTTON_LATENCY);
			GloveForDeaf_createNewProfile(PROFILE2);
		}
		else{
			_delay_ms(PUSH_BUTTON_LATENCY);
			mainMenu();
			return;
		}
	}
	chooseProfile();
}

void goBack				(void){
	backMenu();
}
void backMenu(){
	LCD_clear();
	LCD_goToSpecificPosition(LCD_LINE_ONE,0);
	LCD_writeString((u8*)"0-Main Menu");
	LCD_goToSpecificPosition(LCD_LINE_TWO,0);
	LCD_writeString((u8*)"1-Settings");
	while(Kit_pushButton_isPressed(BUTTON0)==0 
	&& Kit_pushButton_isPressed(BUTTON1)==0
	&& Kit_pushButton_isPressed(BUTTON2)==0);
	if(Kit_pushButton_isPressed(BUTTON0)){
		_delay_ms(PUSH_BUTTON_LATENCY);
		mainMenu();
	}
	else{
		if(Kit_pushButton_isPressed(BUTTON1)){
			_delay_ms(PUSH_BUTTON_LATENCY);
			settings();
		}
		else{
			_delay_ms(PUSH_BUTTON_LATENCY);
			mainMenu();
		}
	}
}
void settings(){
	LCD_clear();
	LCD_goToSpecificPosition(LCD_LINE_ONE,0);
	LCD_writeString((u8*)"0-Clear Data");
	LCD_goToSpecificPosition(LCD_LINE_TWO,0);
	LCD_writeString((u8*)"1-New Password");
	while(Kit_pushButton_isPressed(BUTTON0)==0 
	&& Kit_pushButton_isPressed(BUTTON1)==0
	&& Kit_pushButton_isPressed(BUTTON2)==0);
	if(Kit_pushButton_isPressed(BUTTON0)){
		_delay_ms(PUSH_BUTTON_LATENCY);
		clearData();
	}
	else{
		if(Kit_pushButton_isPressed(BUTTON1)){
			_delay_ms(PUSH_BUTTON_LATENCY);
			changePassword();
		}
		else{
			_delay_ms(PUSH_BUTTON_LATENCY);
			goBack();
		}
	}
}
void clearData(){
	LCD_clear();
	LCD_goToSpecificPosition(LCD_LINE_ONE,0);
	LCD_writeString((u8*)"0-Profile 1");
	if(PROFILES_USED==2){
		LCD_goToSpecificPosition(LCD_LINE_TWO,0);
		LCD_writeString((u8*)"1-Profile 2");
	}
	//Busy wait till user choose
	while(Kit_pushButton_isPressed(BUTTON0)==0
	&&((Kit_pushButton_isPressed(BUTTON1)==0)||(PROFILES_USED!=2))
	&&Kit_pushButton_isPressed(BUTTON2)==0);
	if(Kit_pushButton_isPressed(BUTTON0)){
		_delay_ms(PUSH_BUTTON_LATENCY);
		GloveForDeaf_deleteProfile(PROFILE1);
	}
	else{
		if(Kit_pushButton_isPressed(BUTTON1)&&(PROFILES_USED==2)){
			_delay_ms(PUSH_BUTTON_LATENCY);
			GloveForDeaf_deleteProfile(PROFILE2);
		}
		else{
			_delay_ms(PUSH_BUTTON_LATENCY);
			settings();
		}
		
	}
	
	mainMenu();	
}
void changePassword(){
	LCD_clear();
	LCD_goToSpecificPosition(LCD_LINE_ONE,0);
	LCD_writeString((u8*)"Press 0 to Save");
	_delay_ms(1000);
	GloveForDeaf_newPassword();
	LCD_clear();
	LCD_goToSpecificPosition(LCD_LINE_ONE,0);
	LCD_writeString((u8*)"Password changed successfully!");
	_delay_ms(1000);
	LCD_clear();
	mainMenu();
}



