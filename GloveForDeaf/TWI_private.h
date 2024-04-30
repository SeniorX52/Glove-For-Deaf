/*
 * TWI_private.h
 *
 * Created: 2/16/2024 10:47:10 PM
 *  Author: HP
 */ 


#ifndef TWI_PRIVATE_H_
#define TWI_PRIVATE_H_
#include "STD_TYPES.h"
//Status register values:
#define TWI_STATUS_VALUE             (TWSR&0xF8) //=0b11111000
#define TWI_START_CONDITION_ACK       0x08
#define TWI_REP_START_CONDITION_ACK   0x10
#define TWI_SLAVE_ADDRESS_WRITE_ACK   0x18
#define TWI_SLAVE_ADDRESS_READ_ACK    0x40
#define TWI_MASTER_DATA_TRANSMIT_ACK  0x28
#define TWI_MASTER_DATA_RECIEVE_ACK   0x50
#define TWI_MASTER_DATA_RECIEVE_NACK  0x58


//****************** Bit rate register ******************//
#define TWBR			(*(volatile u8*)0x20)

//****************** Control Register ******************//
#define TWCR			(*(volatile u8*)0x56)
#define TWIE			0
#define TWEN			2
#define TWWC			3
#define TWSTO			4
#define TWSTA			5
#define TWEA			6
#define TWINT			7

//****************** Status register ******************//
#define TWSR			(*(volatile u8*)0x21)
#define TWPS0			0
#define TWPS1			1

//****************** Data register ******************//
#define TWDR			(*(volatile u8*)0x23)

//****************** Slave address register ******************//
#define TWAR			(*(volatile u8*)0x22)
#define TWGCE			0

#endif /* TWI_PRIVATE_H_ */