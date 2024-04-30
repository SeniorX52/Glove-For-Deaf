/*
 * ADC_interface.h
 *
 * Created: 1/27/2024 6:18:49 PM
 *  Author: HP
 */ 


#ifndef ADC_INTERFACE_H_
#define ADC_INTERFACE_H_

/***********ADC CHANNELS***********/
#define ADC_CHANNEL0			0
#define ADC_CHANNEL1			1
#define ADC_CHANNEL2			2
#define ADC_CHANNEL3			3
#define ADC_CHANNEL4			4
#define ADC_CHANNEL5			5
#define ADC_CHANNEL6			6
#define ADC_CHANNEL7			7


/***********Options for max. voltage***********/
#define ADC_REFERENCE_AVCC      1 // External Capacitor (5v)
#define ADC_REFERENCE_AREF      2 // (0 ~ 5)v
#define ADC_REFERENCE_INTERNAL  3 // Internal 2.56v

/*************** APIS PROTOTYPES ***************/
void ADC_init           (u8 referenceVoltage);
u16  ADC_getDigitalValue(u8 channelNum);



#endif /* ADC_INTERFACE_H_ */