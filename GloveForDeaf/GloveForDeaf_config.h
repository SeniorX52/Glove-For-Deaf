/*
 * GloveForDeaf_config.h
 *
 * Created: 2/28/2024 6:26:08 PM
 *  Author: HP
 */ 


#ifndef GLOVEFORDEAF_CONFIG_H_
#define GLOVEFORDEAF_CONFIG_H_

//Used postures are helpful for debugging and testing
#define SPEECH_POSTURES_USED_NUMBER						15
#define CONTROL_POSTURES_USED_NUMBER					3

//If profiles used =1, 
//you can double the number of max postures
/*Total Range for postures for 2 profiles -> 0~25 for each profile
if only 1 profile used then -> 0~50*/
#define SPEECH_POSTURES_MAX_NUMBER						15
#define CONTROL_POSTURES_MAX_NUMBER						3
#define SPEECH_SENTENCE_MAX_LENGTH						16
//Maximum physical bending for our flex sensor
#define MAX_BEND										180
//Prescalling the range of motion of all fingers to be from 0 to MAX_FINGER_VALUE
#define MAX_FINGER_VALUE								7
#define MAX_PASSWORD_VALUE								9
/*Lowering finger numbers 
will make the program not able to read 
last fingers according to RH or LH*/
#define FINGERS_NUMBER									5
#define PROFILES_USED									1
#define LCD_LATENCY										100
#define PUSH_BUTTON_LATENCY								300

#endif /* GLOVEFORDEAF_CONFIG_H_ */