/*
 * GloveForDeaf_program.c
 *
 * Created: 2/28/2024 4:58:35 PM
 *  Author: HP
 */ 
#define F_CPU 16000000UL
#include <util/delay.h>
//**********UTILES**********//
#include "STD_TYPES.h"
//**********MCAL**********//
#include "UART_interface.h"
//**********HAL**********//
#include "Glove_interface.h"
#include "Glove_config.h"
#include "LCD_interface.h"
#include "GloveForDeaf_interface.h"
#include "GloveForDeaf_config.h"
#include "EEPROM_interface.h"
#include "Kit_interface.h"


static void (*private_pCallBackC0)(void) = NULL;
static void (*private_pCallBackC1)(void) = NULL;
static void (*private_pCallBackC2)(void) = NULL;
//Default loaded password when reset occur
static u8 PASSWORD[5]={0,0,0,0,0};
static u8 fingerValues[5];
static const u8 fingers[5]={GLOVE_FINGER1,GLOVE_FINGER2,GLOVE_FINGER3,GLOVE_FINGER4,GLOVE_FINGER5};
//Posture Range ->MIN,MAX
static u8 speechRange[SPEECH_POSTURES_MAX_NUMBER*2][FINGERS_NUMBER];

static u8 speechSentences[SPEECH_POSTURES_MAX_NUMBER][SPEECH_SENTENCE_MAX_LENGTH] = {
	//Posture 0 = Relaxed
	"Hello",
	//Posture 1 = See you later
	"See you later",
	//Posture 2 = Love you
	"Love you",
	//Posture 3 = Like you
	"Like you",
	//Posture 4 = Not sure
	"Not sure",
	//Posture 5 = Watching you
	"Watching you",
	//Posture 6 = Amazing
	"Amazing",
	//Posture 7 = Quote
	"Quote",
	//Posture 8 = Question
	"Question",
	//Posture 9 = No
	"No",
	//Posture 10 = You
	"You",
	//Posture 11 = Ok
	"Ok",
	//Posture 12 = Good job
	"Good job",
	//Posture 13 = Victory
	"Victory",
	//Posture 14 = Custom
	"Eng.Mostafa"
};
static u8 controlRange[CONTROL_POSTURES_MAX_NUMBER*2][FINGERS_NUMBER]=
{
	//Control 0 = private_pCallBackC0
	{0,0,0,0,0},
	{0,0,0,0,0},
	//Control 1 = private_pCallBackC1
	{0,0,0,0,0},
	{0,0,0,0,0},
	//Control 2 = private_pCallBackC2
	{0,0,0,0,0},
	{0,0,0,0,0}
};
void GloveForDeaf_init(void){
	//Initialize glove, LCD, UART,EEPROM
	Glove_init();
	LCD_init();
	UART_init();
	EEPROM_init();
}

void GloveForDeaf_getFingerValues(void){
	for(u8 i=0;i<FINGERS_NUMBER;i++){
		fingerValues[i]=(u8)(((double)(Glove_getFingerValue(fingers[i]))) / MAX_BEND * MAX_FINGER_VALUE);
	}
}
void GloveForDeaf_displayFingerValues(void){
	LCD_clear();
	LCD_goToSpecificPosition(LCD_LINE_ONE,0);
	for(u8 i=0;i<FINGERS_NUMBER-2;i++){
		LCD_writeNumber(fingerValues[i]);
		LCD_writeString((u8*)" ");
	}
	LCD_goToSpecificPosition(LCD_LINE_TWO,0);
	for(u8 i=3;i<FINGERS_NUMBER;i++){
		LCD_writeNumber(fingerValues[i]);
		LCD_writeString((u8*)" ");
	}
}
u8	GloveForDeaf_getSpeechPosture(void){
	//Check range of posture max and min
	u8 counter=0;
	int i;
	for(i=0;i<SPEECH_POSTURES_USED_NUMBER*2;i+=2){
		for(int j=0;j<FINGERS_NUMBER;j++){
			if((fingerValues[j]<speechRange[i][j]&&fingerValues[j]<speechRange[i+1][j])
			||(fingerValues[j]>speechRange[i][j]&&fingerValues[j]>speechRange[i+1][j])){
				break;
			}
			//If not in this range break
			else{
				counter++;
			}
			if(counter==FINGERS_NUMBER){
				//All five fingers are in this posture range
				return (i/2);
			}
			
		}
		counter=0;
	}
	//Out of range, --> default posture 0
	return POSTURENON;
}
void GloveForDeaf_printSpeechPosture(u8 posture){
	//To prevent printing relax -> && posture!=0
	if(posture!=POSTURENON){
		LCD_clear();
		LCD_goToSpecificPosition(LCD_LINE_ONE,0);
		u8* sentence=speechSentences[posture];
		LCD_writeString(sentence);
		UART_sendString(sentence);
	}
// 	else{
// 		GloveForDeaf_displayFingerValues();
// 	}
}
u8	GloveForDeaf_getControlPosture(void){
	//Check range of posture max and min
	u8 counter=0;
	for(u8 i=0;i<CONTROL_POSTURES_USED_NUMBER*2;i+=2){
		for(u8 j=0;j<FINGERS_NUMBER;j++){
			//Check if the finger position between min and max
			//also check if the min>max
			if(
			(fingerValues[j]<controlRange[i][j]&&fingerValues[j]<controlRange[i+1][j])
			||(fingerValues[j]>controlRange[i][j]&&fingerValues[j]>controlRange[i+1][j])
			){
				break;
			}
			//If not in this range break
			else{
				counter++;
				
			}
			if(counter==5){
				//All five fingers are in this posture range
				return (i/2);
			}
		}
		counter=0;
	}
	//Out of range, --> default posture 0
	return POSTURENON;
}
void GloveForDeaf_sendFingerValues(void){
	UART_TxChar('{');
	for(int i=0;i<FINGERS_NUMBER-1;i++){
		UART_sendNumber(fingerValues[i]);
		UART_TxChar(',');
	}
	UART_sendNumber(fingerValues[FINGERS_NUMBER-1]);
	UART_TxChar('}');
	
}

void GloveForDeaf_passwordCheck(void){
	while(1){
		LCD_clear();
		LCD_goToSpecificPosition(LCD_LINE_ONE,0);
		LCD_writeString((u8*)"Enter Password");
		GloveForDeaf_getFingerValues();
		GloveForDeaf_displayFingerValuesPASS();
		u8 counter=0;
		for(u8 i=0;i<FINGERS_NUMBER;i++){
			u8 digit =GloveForDeaf_getPasswordDigit(i);
			if(digit==PASSWORD[i]){
				counter++;
			}
		}
		if(counter==5){
			//Password correct
			LCD_clear();
			LCD_goToSpecificPosition(LCD_LINE_ONE,0);
			LCD_writeString((u8*)"Welcome to SmartGlove v1.4");
			LCD_clear();
			break;
		}
		_delay_ms(LCD_LATENCY);
	}
	
	
}
void GloveForDeaf_sendPostureSentence(u8 posture){
	if(posture!=POSTURENON){
		UART_sendString(speechSentences[posture]);
	}
}
void GloveForDeaf_displayFingerValuesPASS(void){
	LCD_goToSpecificPosition(LCD_LINE_TWO,3);
	for(int i=0;i<FINGERS_NUMBER;i++){;
		//Convert motion range to 0~9 according to possible range of motion
		u8 digit =GloveForDeaf_getPasswordDigit(i);
		LCD_writeNumber(digit);
		LCD_writeString((u8*)" ");
	}
}
u8 GloveForDeaf_getPasswordDigit(u8 finger){
	return (u8)(((double)(fingerValues[finger])) / MAX_FINGER_VALUE * MAX_PASSWORD_VALUE);
}
void GloveForDeaf_saveCurrentValues(u8 profile,u16 position){
	if(profile==PROFILE2){
		position+=(SPEECH_POSTURES_USED_NUMBER+CONTROL_POSTURES_USED_NUMBER)*FINGERS_NUMBER*2;
	}
	for(u8 i=0;i<FINGERS_NUMBER;i++){
		EEPROM_writeByte(position,fingerValues[i]);
		position++;
	}
}
void GloveForDeaf_createNewProfile(u8 profile){
	//For simulation, record your values from UART terminal
	//by uncommenting the following UART functions
	LCD_clear();
	LCD_writeString((u8*)"Press button 0 for calibration");
	u8 memoryStepSize=FINGERS_NUMBER;
	u16 memoryPosition=0;
	for(u8 i=0;i<SPEECH_POSTURES_USED_NUMBER+CONTROL_POSTURES_USED_NUMBER;i++){
		
		//-------------------------------MIN-----------------------------
		while (1)
		{
			u8 isControl=0;
			u8 overlapFlag=0;
			LCD_clear();
			if(i>=SPEECH_POSTURES_USED_NUMBER){
				LCD_writeString((u8*)"Control: ");
				UART_sendString((u8*)"Control: ");
				LCD_writeNumber((i-SPEECH_POSTURES_USED_NUMBER));
				UART_sendNumber((i-SPEECH_POSTURES_USED_NUMBER));
				isControl=1;
			}
			else{
				LCD_writeString(speechSentences[i]);
				UART_sendString((u8*)speechSentences[i]);
			}
			LCD_goToSpecificPosition(LCD_LINE_TWO,0);
			LCD_writeString((u8*)"Min->");
			//Busy wait till button 0 is pressed
			_delay_ms(1500);
			while(Kit_pushButton_isPressed(BUTTON0)==0){
				GloveForDeaf_getFingerValues();
				GloveForDeaf_displayFingerValues();
				_delay_ms(LCD_LATENCY);
			}
			_delay_ms(PUSH_BUTTON_LATENCY);
			overlapFlag=GloveForDeaf_checkOverlap(profile,memoryPosition,isControl);
			if(overlapFlag){
				LCD_clear();
				LCD_goToSpecificPosition(LCD_LINE_ONE,0);
				LCD_writeString((u8*)"Try again: Overlapped positions");
				_delay_ms(1000);
			}
			else{
				break;
			}
		}
		GloveForDeaf_sendFingerValues();
		GloveForDeaf_saveCurrentValues(profile,memoryPosition);
		memoryPosition+=memoryStepSize;
		//-------------------------------MAX-----------------------------
		
		while (1)
		{
			u8 overlapFlag=0;
			u8 isControl=0;
			LCD_clear();
			LCD_goToSpecificPosition(LCD_LINE_ONE,0);
			if(i>=SPEECH_POSTURES_USED_NUMBER){
				LCD_writeString((u8*)"Control: ");
				LCD_writeNumber((i-SPEECH_POSTURES_USED_NUMBER));
				isControl=1;
			}
			else{
				LCD_writeString(speechSentences[i]);
			}
			LCD_goToSpecificPosition(LCD_LINE_TWO,0);
			LCD_writeString((u8*)"Max->");
			_delay_ms(1500);
			while(Kit_pushButton_isPressed(BUTTON0)==0){
				GloveForDeaf_getFingerValues();
				GloveForDeaf_displayFingerValues();
				_delay_ms(LCD_LATENCY);
			}
			_delay_ms(PUSH_BUTTON_LATENCY);
			overlapFlag=GloveForDeaf_checkOverlap(profile,memoryPosition,isControl);
			if(overlapFlag){
				LCD_clear();
				LCD_goToSpecificPosition(LCD_LINE_ONE,0);
				LCD_writeString((u8*)"Try again: Overlapped positions");
				_delay_ms(1000);
			}
			else{
				break;
			}
		}
		GloveForDeaf_sendFingerValues();
		GloveForDeaf_saveCurrentValues(profile,memoryPosition);
		memoryPosition+=memoryStepSize;
		//----------------------------------------------------------------
	}
	//Display: profile (n) created!
	LCD_clear();
	LCD_writeString((u8*)"Profile ");
	LCD_writeNumber(profile);
	LCD_writeString((u8*)" created!");
	_delay_ms(500);
	LCD_shift(LCD_SHIFT_RIGHT);
	LCD_shift(LCD_SHIFT_RIGHT);
	_delay_ms(2000);
	LCD_clear();
}

u8 GloveForDeaf_checkOverlap(u8 profile,u16 position,u8 isControl){
	u8 overlapFlag=0;
	u16 memoryPosition=0;
	u8 memoryStepSize=FINGERS_NUMBER*2;//Min & Max-->*2
	if(profile==PROFILE2){
		memoryPosition+=(SPEECH_POSTURES_USED_NUMBER+CONTROL_POSTURES_USED_NUMBER)*memoryStepSize;
		position+=memoryPosition;
	}
	if(isControl==1){
		memoryPosition+=SPEECH_POSTURES_USED_NUMBER*memoryStepSize;
	}
	u8 countOverlapped=0;
	//Comment this if you don't want min & max ranges to be equal
	if(position>memoryPosition){
		position-=FINGERS_NUMBER;
	}
	while(memoryPosition<position){
		u8 min[5]={0,0,0,0,0};
		u8 max[5]={0,0,0,0,0};
		for(u8 c=0;c<10;c++){
			if(c<5){
				EEPROM_readByte(memoryPosition++,&min[c]);
			}
			else{
				EEPROM_readByte(memoryPosition++,&max[c-5]);
			}
		}
		for(u8 c=0;c<5;c++){
			if((fingerValues[c] < min[c] && fingerValues[c] < max[c]) ||
		(fingerValues[c] > min[c] && fingerValues[c] > max[c])){
				break;
			}
			else{
				countOverlapped++;
			}
		}
		if(countOverlapped==FINGERS_NUMBER){
			overlapFlag=1;
			break;
		}
		countOverlapped=0;
	}
	return overlapFlag;
}
void GloveForDeaf_loadProfile(u8 profile){
	u16 memoryPosition=0;
	u8 memoryStepSize=FINGERS_NUMBER;
	LCD_clear();
	LCD_goToSpecificPosition(LCD_LINE_ONE,0);
	LCD_writeString((u8*)"Loading...");
	for(u8 i=0;i<(SPEECH_POSTURES_USED_NUMBER+CONTROL_POSTURES_USED_NUMBER)*2;i+=2){
		if(i>=SPEECH_POSTURES_USED_NUMBER*2){
			//Load control values
			GloveForDeaf_loadValues(profile,controlRange[(i-SPEECH_POSTURES_USED_NUMBER*2)],memoryPosition);
			memoryPosition+=memoryStepSize;
			GloveForDeaf_loadValues(profile,controlRange[(i-SPEECH_POSTURES_USED_NUMBER*2)+1],memoryPosition);
		}
		else{
			GloveForDeaf_loadValues(profile,speechRange[i],memoryPosition);
			memoryPosition+=memoryStepSize;
			GloveForDeaf_loadValues(profile,speechRange[i+1],memoryPosition);
		}
		memoryPosition+=memoryStepSize;
	}
	//Display: profile (n) loaded!
	LCD_clear();
	LCD_writeString((u8*)"Profile ");
	LCD_writeNumber(profile);
	LCD_writeString((u8*)" loaded!");
	_delay_ms(500);
	LCD_shift(LCD_SHIFT_RIGHT);
	_delay_ms(2000);
	LCD_clear();
}

void GloveForDeaf_loadValues(u8 profile,u8* array,u16 position){
	if(profile==PROFILE2){
		u8 memoryStepSize=FINGERS_NUMBER*2;//Min & Max-->*2
		position+=(SPEECH_POSTURES_USED_NUMBER+CONTROL_POSTURES_USED_NUMBER)*memoryStepSize;
	}
	for(u8 i=0;i<FINGERS_NUMBER;i++){
		EEPROM_readByte(position,&array[i]);
		position++;
	}
}
void GloveForDeaf_setCallBackControl(void (*ptrToFun)(void),u8 control){
	switch(control){
		case CONTROL0:
		{
			private_pCallBackC0 = ptrToFun;
			break;
		}
		case CONTROL1:
		{
			private_pCallBackC1 = ptrToFun;
			break;
		}
		case CONTROL2:
		{
			private_pCallBackC2 = ptrToFun;
			break;
		}
	}
}

void GloveForDeaf_executeControl(u8 posture){
	if(posture!=POSTURENON){
		switch(posture){
			case CONTROL0:
			{
				if(private_pCallBackC0!=NULL){
					private_pCallBackC0();
				}
				break;
				
			}
			case CONTROL1:
			{
				if(private_pCallBackC1!=NULL){
					private_pCallBackC1();
				}
				break;
			}
			case CONTROL2:
			{
				if(private_pCallBackC2!=NULL){
					private_pCallBackC2();
				}
				break;
			}
		}
	}
}
void GloveForDeaf_deleteProfile(u8 profile){
	LCD_clear();
	LCD_goToSpecificPosition(LCD_LINE_ONE,0);
	LCD_writeString((u8*)"Deleting...");
	u16 startAddress=0;
	u16 endAddress=(SPEECH_POSTURES_USED_NUMBER+CONTROL_POSTURES_USED_NUMBER)*10;
	if(profile==PROFILE2){
		startAddress=endAddress;
		endAddress=(endAddress)*2;
	}
	for(u16 i=startAddress;i<endAddress;i++){
		EEPROM_writeByte(i,0);
	}
	LCD_clear();
	LCD_writeString((u8*)"Profile ");
	LCD_writeNumber(profile);
	LCD_writeString((u8*)" deleted successfully!");
	for(u8 i=0;i<16;i++){
		LCD_shift(LCD_SHIFT_RIGHT);
		_delay_ms(200);
	}
	_delay_ms(1000);
	LCD_clear();
}
void GloveForDeaf_newPassword(){
	LCD_clear();
	LCD_goToSpecificPosition(LCD_LINE_ONE,0);
	LCD_writeString((u8*)"New Password:");
	while(Kit_pushButton_isPressed(BUTTON0)==0){
		GloveForDeaf_getFingerValues();
		GloveForDeaf_displayFingerValuesPASS();
		_delay_ms(LCD_LATENCY);
	}
	GloveForDeaf_getFingerValues();
	for(u8 i=0;i<FINGERS_NUMBER;i++){
		PASSWORD[i]=GloveForDeaf_getPasswordDigit(i);
	}
	GloveForDeaf_saveCurrentPassword();
	_delay_ms(PUSH_BUTTON_LATENCY);
}
void GloveForDeaf_loadPassword(){
	for(u16 i=PASSWORD_ADDRESS;i<EEPROM_MAX_SIZE;i++){
		EEPROM_readByte(i,&PASSWORD[i-PASSWORD_ADDRESS]);
	}
}
void GloveForDeaf_saveCurrentPassword(){
	for(u16 i=PASSWORD_ADDRESS;i<EEPROM_MAX_SIZE;i++){
		EEPROM_writeByte(i,PASSWORD[i-PASSWORD_ADDRESS]);
	}
}
//Print saved postures (useful to detect memory errors or shifting in memory position)
void GloveForDeaf_printPosturesData			(u8 profile){
	GloveForDeaf_loadProfile(profile);
	for(u8 i=0;i<SPEECH_POSTURES_USED_NUMBER;i++){
		LCD_clear();
		LCD_goToSpecificPosition(LCD_LINE_ONE,0);
		LCD_writeString(speechSentences[i]);
		LCD_goToSpecificPosition(LCD_LINE_TWO,0);
		LCD_writeString((u8*)"Min->");
		_delay_ms(3000);
		GloveForDeaf_displayArray(speechRange[i*2]);
		_delay_ms(5000);
		LCD_clear();
		LCD_goToSpecificPosition(LCD_LINE_ONE,0);
		LCD_writeString(speechSentences[i]);
		LCD_goToSpecificPosition(LCD_LINE_TWO,0);
		LCD_writeString((u8*)"Max->");
		_delay_ms(3000);
		GloveForDeaf_displayArray(speechRange[i*2+1]);
		_delay_ms(5000);
	}
	for(u8 i=0;i<CONTROL_POSTURES_USED_NUMBER;i++){
		LCD_clear();
		LCD_goToSpecificPosition(LCD_LINE_ONE,0);
		LCD_writeString((u8*)"Control: ");
		LCD_writeNumber(i);
		LCD_goToSpecificPosition(LCD_LINE_TWO,0);
		LCD_writeString((u8*)"Min->");
		_delay_ms(3000);
		GloveForDeaf_displayArray(controlRange[i*2]);
		_delay_ms(5000);
		LCD_clear();
		LCD_goToSpecificPosition(LCD_LINE_ONE,0);
		LCD_writeString((u8*)"Control: ");
		LCD_writeNumber(i);
		LCD_goToSpecificPosition(LCD_LINE_TWO,0);
		LCD_writeString((u8*)"Max->");
		_delay_ms(3000);
		GloveForDeaf_displayArray(controlRange[i*2+1]);
		_delay_ms(5000);
	}
}

void GloveForDeaf_displayArray(u8* array){
	LCD_clear();
	LCD_goToSpecificPosition(LCD_LINE_ONE,0);
	for(int i=0;i<FINGERS_NUMBER-2;i++){
		LCD_writeNumber(array[i]);
		LCD_writeString((u8*)" ");
	}
	LCD_goToSpecificPosition(LCD_LINE_TWO,0);
	for(int i=3;i<FINGERS_NUMBER;i++){
		LCD_writeNumber(array[i]);
		LCD_writeString((u8*)" ");
	}
}

