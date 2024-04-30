/*
 * UART_interface.h
 *
 * Created: 2/15/2024 1:28:11 AM
 *  Author: HP
 */ 


#ifndef UART_INTERFACE_H_
#define UART_INTERFACE_H_

#include "STD_TYPES.h"
void UART_init      (void);
void UART_TxChar    (u8 TxData);
void UART_RxChar    (u8* RxData);
void UART_sendString(u8* TxString);
void UART_sendNumber(u32 TxNumber);

#endif /* UART_INTERFACE_H_ */