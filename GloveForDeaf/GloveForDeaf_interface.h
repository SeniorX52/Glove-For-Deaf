/*
 * GloveForDeaf_interface.h
 *
 * Created: 2/28/2024 4:58:11 PM
 *  Author: HP
 */ 


#ifndef GLOVEFORDEAF_INTERFACE_H_
#define GLOVEFORDEAF_INTERFACE_H_

#include "STD_TYPES.h"
#include "GloveForDeaf_config.h"
#define ABS(x)							((x)<0?-(x):(x))
#define POSTURENON						52   //Undefined reference
#define PASSWORD_ADDRESS				507

#define PROFILE1						1	
#define PROFILE2						2 

#define CONTROL0						0
#define CONTROL1						1
#define CONTROL2						2


						
void GloveForDeaf_init						(void);
void GloveForDeaf_getFingerValues			(void);
void GloveForDeaf_displayFingerValues		(void);
u8	 GloveForDeaf_getSpeechPosture			(void);
void GloveForDeaf_printSpeechPosture		(u8 posture);
u8	 GloveForDeaf_getControlPosture			(void);
void GloveForDeaf_sendFingerValues			(void);
void GloveForDeaf_passwordCheck				(void);
void GloveForDeaf_displayFingerValuesPASS	(void);
void GloveForDeaf_sendPostureSentence		(u8 posture);
void GloveForDeaf_saveCurrentValues			(u8 profile,u16 position);
void GloveForDeaf_createNewProfile			(u8 profile);
void GloveForDeaf_loadValues				(u8 profile,u8* array,u16 position);
void GloveForDeaf_loadProfile				(u8 profile);
void GloveForDeaf_setCallBackControl		(void(*ptrToFun)(void),u8 control);
void GloveForDeaf_executeControl			(u8 posture);
void GloveForDeaf_deleteProfile				(u8 profile);
void GloveForDeaf_newPassword				(void);
void GloveForDeaf_loadPassword				(void);
void GloveForDeaf_saveCurrentPassword		(void);
u8 GloveForDeaf_getPasswordDigit			(u8 finger);
u8 GloveForDeaf_checkOverlap				(u8 profile,u16 position,u8 isControl);

//Debugging Functions
void GloveForDeaf_printPosturesData			(u8 profile);
void GloveForDeaf_displayArray				(u8* array);


#endif /* GLOVEFORDEAF_INTERFACE_H_ */