/*
 * UART_program.c
 *
 * Created: 2/15/2024 1:28:38 AM
 *  Author: HP
 */ 
//**********UTILES**********//
#include "STD_TYPES.h"
#include "BIT_MATH.h"
//**********MCAL**********//
#include "UART_interface.h"
#include "UART_private.h"

void UART_init      (void){
	//Set transmission Speed to normal
	CLR_BIT(UCSRA,U2X);
	// Set Buad Rate = 9600 
	UBRRL=103;
	/* writing the UCSRC
	select UART MODE = Asynchronous
	configure no parity
	configure stop bits = 1
	configure data bits = 8
	configure no polarity */
	CLR_BIT(UCSRB,UCSZ2);
	UCSRC = 0b10000110;
	//Enable Tx
	SET_BIT(UCSRB,TXEN);
	//Enable Rx
	SET_BIT(UCSRB,RXEN);
}
void UART_TxChar    (u8 TxData){
	UDR = TxData;
	
	// Busy Wait on Data Register empty flag
	while(0 == GET_BIT(UCSRA,UDRE));
}
void UART_RxChar(u8* RxData)
{
	if(RxData!=NULL)
	{
		// Busy Wait on Receive Compelete flag
		while(0 == GET_BIT(UCSRA,RXC));
		
		*RxData = UDR;
	}
}
void UART_sendString(u8* TxString){
	if (TxString!=NULL){
		u8 counter=0;
		while(TxString[counter]!='\0'){
			UART_TxChar(TxString[counter++]);
		}
	}
}
void UART_sendNumber(u32 TxNumber){
	u32 reversedNum = 1;
	if(TxNumber == 0)
	{
		UART_TxChar('0');
	}
	else
	{
		// reverse the number
		while(TxNumber != 0)
		{
			reversedNum = reversedNum*10 + TxNumber%10;
			TxNumber /= 10;
		}
		
		
		do
		{
			UART_TxChar(reversedNum%10 + '0');
			reversedNum /= 10;
		}
		while(reversedNum != 1);
	}
}