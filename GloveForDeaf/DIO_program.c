/*
 * DIO_program.c
 *
 * Created: 12/11/2023 7:28:29 PM
 *  Author: Mostafa
 */ 

//**********UTILES**********//
#include "STD_TYPES.h"
#include "BIT_MATH.h"
//**********MCAL**********//
#include "DIO_interface.h"
#include "DIO_private.h"

void DIO_setPinDirection(u8 PortId, u8 PinId, u8 PinDirection)
{
	if((PortId<=3)&&(PinId<=7)&&((PinDirection == DIO_PIN_INPUT)||(PinDirection == DIO_PIN_OUTPUT)))
	{
		switch(PortId)
		{
			case DIO_PORTA:
			if(DIO_PIN_OUTPUT == PinDirection) 
			{
				SET_BIT(DDRA,PinId);
			}
			else 
			{
				CLR_BIT(DDRA,PinId);
			}
			break;
			
			case DIO_PORTB:
			if(DIO_PIN_OUTPUT == PinDirection) 
			{
				SET_BIT(DDRB,PinId);
			}
			else 
			{
				CLR_BIT(DDRB,PinId);
			}
			break;
			
			case DIO_PORTC:
			if(DIO_PIN_OUTPUT == PinDirection) 
			{
				SET_BIT(DDRC,PinId);
			}
			else 
			{
				CLR_BIT(DDRC,PinId);
			}
			break;
			
			case DIO_PORTD:
			if(DIO_PIN_OUTPUT == PinDirection) 
			{
				SET_BIT(DDRD,PinId);
			}
			else 
			{
				CLR_BIT(DDRD,PinId);
			}
			break;
		}
	}
	else
	{
		// Do Nothing
	}
}


void DIO_setPinValue(u8 PortId, u8 PinId, u8 PinValue)
{
	if((PortId<=3)&&(PinId<=7)&&((PinValue == DIO_PIN_HIGH)||(PinValue == DIO_PIN_LOW)))
	{
		switch(PortId)
		{
			case DIO_PORTA:
			if(PinValue == DIO_PIN_HIGH)
			{
				SET_BIT(PORTA,PinId);
			}
			else
			{
				CLR_BIT(PORTA,PinId);
			}
			break;
			
			case DIO_PORTB:
			if(PinValue == DIO_PIN_HIGH)
			{
				SET_BIT(PORTB,PinId);
			}
			else
			{
				CLR_BIT(PORTB,PinId);
			}
			break;
			
			case DIO_PORTC:
			if(PinValue == DIO_PIN_HIGH)
			{
				SET_BIT(PORTC,PinId);
			}
			else
			{
				CLR_BIT(PORTC,PinId);
			}
			break;
			
			case DIO_PORTD:
			if(PinValue == DIO_PIN_HIGH)
			{
				SET_BIT(PORTD,PinId);
			}
			else
			{
				CLR_BIT(PORTD,PinId);
			}
			break;
		}
	}
	else
	{
		// Do Nothing
	}
}


u8 DIO_getPinValue(u8 PortId, u8 PinId)
{
	if((PortId<=3)&&(PinId<=7))
	{
		switch(PortId)
		{
			case DIO_PORTA:
			return (GET_BIT(PINA,PinId));
			break;
			
			case DIO_PORTB:
			return (GET_BIT(PINB,PinId));
			break;
			
			case DIO_PORTC:
			return (GET_BIT(PINC,PinId));
			break;
			
			case DIO_PORTD:
			return (GET_BIT(PIND,PinId));
			break;
		}
	}
	else
	{
		// Do Nothing
	}
	return 0;
}


/*void DIO_getPinValue(u8 PortId, u8 PinId, u8* PinValue)
{
	if((PortId<=3)&&(PinId<=7)&&(PinValue!=NULL))
	{
		switch(PortId)
		{
			case DIO_PORTA:
			*PinValue = GET_BIT(PINA,PinId);
			break;
			
			case DIO_PORTB:
			*PinValue = GET_BIT(PINB,PinId);
			break;
			
			case DIO_PORTC:
			*PinValue = GET_BIT(PINC,PinId);
			break;
			
			case DIO_PORTD:
			*PinValue = GET_BIT(PIND,PinId);
			break;
		}
	}
	else
	{
		// Do Nothing
	}
}*/


void DIO_togglePinValue(u8 PortId, u8 PinId)
{
	if((PortId<=3)&&(PinId<=7))
	{
		switch(PortId)
		{
			case DIO_PORTA:
			TOG_BIT(PORTA,PinId);
			break;
			
			case DIO_PORTB:
			TOG_BIT(PORTB,PinId);
			break;
			
			case DIO_PORTC:
			TOG_BIT(PORTC,PinId);
			break;
			
			case DIO_PORTD:
			TOG_BIT(PORTD,PinId);
			break;
		}
	}
	else
	{
		// Do Nothing
	}
}


void DIO_activePinInPullUpResistance(u8 PortId, u8 PinId)
{
	if((PortId<=3)&&(PinId<=7))
	{
		switch(PortId)
		{
			case DIO_PORTA:
			SET_BIT(PORTA,PinId);
			break;
			
			case DIO_PORTB:
			SET_BIT(PORTB,PinId);
			break;
			
			case DIO_PORTC:
			SET_BIT(PORTC,PinId);
			break;
			
			case DIO_PORTD:
			SET_BIT(PORTD,PinId);
			break;
		}
	}
	else
	{
		// Do Nothing
	}
}