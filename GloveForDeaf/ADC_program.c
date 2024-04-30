/*
 * ADC_program.c
 *
 * Created: 1/27/2024 6:19:01 PM
 *  Author: HP
 */ 
/* UTILES_LIB */
#include "STD_TYPES.h"
#include "BIT_MATH.h"

/* MCAL */
#include "ADC_interface.h"
#include "ADC_private.h"


void ADC_init(u8 referenceVoltage)
{
	switch(referenceVoltage){
		case ADC_REFERENCE_AVCC:{
			SET_BIT(ADMUX,REFS0);
			CLR_BIT(ADMUX,REFS1);
			break;
		}
		case ADC_REFERENCE_AREF:{
			CLR_BIT(ADMUX,REFS0);
			CLR_BIT(ADMUX,REFS1);
			break;
		}
		case ADC_REFERENCE_INTERNAL:{
			SET_BIT(ADMUX,REFS0);
			SET_BIT(ADMUX,REFS1);
			break;
		}
		
	}
	// Select Right Adjustment
	CLR_BIT(ADMUX,ADLAR);

	// Single Conversation Mode
	CLR_BIT(ADCSRA,ADATE);
	
	//Disable ADC Interrupt
	CLR_BIT(ADCSRA,ADIE);
	
	// Prescaler 128 For 16MHZ (125 KHZ)
	SET_BIT(ADCSRA,ADPS2);
	SET_BIT(ADCSRA,ADPS1);
	SET_BIT(ADCSRA,ADPS0);
	
	// ADC Enable
	SET_BIT(ADCSRA,ADEN);
}


u16  ADC_getDigitalValue(u8 channelNum)
{
	if(channelNum<32)
	{
		//Clear ADMUX Channel Bits
		ADMUX &= 0xE0; //0b11100000, 1110->E (0000)->0
		
		// Select Channel Number
		ADMUX |= channelNum;
		
		// Start Conversion
		SET_BIT(ADCSRA,ADSC);
		// Busy wait on ADC flag
		while(GET_BIT(ADCSRA,ADIF)==0);
		// Clear Flag(write one to clear)
		SET_BIT(ADCSRA,ADIF);
		return ADC_u16;
	}
	else
	{
		return 0;
	}
}