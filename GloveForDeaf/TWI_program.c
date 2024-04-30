/*
 * TWI_program.c
 *
 * Created: 2/16/2024 10:47:22 PM
 *  Author: HP
 */ 

//**********UTILES**********//
#include "STD_TYPES.h"
#include "BIT_MATH.h"
//**********MCAL**********//
#include "TWI_interface.h"
#include "TWI_private.h"

void TWI_initMaster                   (void){
	//Set Prescaler to 00
	CLR_BIT(TWSR,TWPS0);
	CLR_BIT(TWSR,TWPS1);
	
	//Set Bit rate to 12
	TWBR=12;
	
	//Enable TWI
	SET_BIT(TWCR,TWEN);
	
}

void TWI_sendStartCondition           (void){
	//Application writes to TWCR to initiate transmission of START
	//Request Start condition
	SET_BIT(TWCR,TWSTA);
	
	// Clear flag to start current job
	CLR_BIT(TWCR,TWINT);
	
	// Busy Wait for the flag
	while(GET_BIT(TWCR,TWINT)==0);
	
	//Check ACK = SC ACK
	while(TWI_STATUS_VALUE !=TWI_START_CONDITION_ACK);
}

void TWI_sendRepStartCondition        (void){
	SET_BIT(TWCR,TWSTA);
	
	// Clear flag to start current job
	CLR_BIT(TWCR,TWINT);
	
	// Busy Wait for the flag
	while(GET_BIT(TWCR,TWINT)==0);
	//Check ACK = Rep SC ACK
	while(TWI_STATUS_VALUE !=TWI_REP_START_CONDITION_ACK);
}

void TWI_sendStopCondition            (void){
	//Request Stop condition
	SET_BIT(TWCR,TWSTO);
	
	//Clear TWI Interrupt Flag (Read Datasheet)
	SET_BIT(TWCR,TWINT);
}

void TWI_sendSlaveAddWithWrite        (u8 slaveAdd){
	//Check if slave add < 128
	if(slaveAdd<128){
		//Send slave address in the MSB of the byte
		TWDR=(slaveAdd<<1);
		//Select write operation
		CLR_BIT(TWDR,0);
		// Clear start condition bit
		CLR_BIT(TWCR,TWSTA);
		//Clear TWI Interrupt Flag (Read Datasheet)
		SET_BIT(TWCR,TWINT);
		//Busy wait for the flag
		while(GET_BIT(TWCR,TWINT)==0);
		//Check ACK = Master transmit ( slave address + Write request )
		while(TWI_SLAVE_ADDRESS_WRITE_ACK!=TWI_STATUS_VALUE);
	}
}
void TWI_sendSlaveAddWithRead         (u8 slaveAdd){
	if(slaveAdd<128){
		//Send slave address in the MSB of the byte
		TWDR=(slaveAdd<<1);
		//Select read operation
		SET_BIT(TWDR,0);
		// Clear start condition bit
		CLR_BIT(TWCR,TWSTA);
		//Clear TWI Interrupt Flag (Read Datasheet)
		SET_BIT(TWCR,TWINT);
		//Busy wait for the flag
		while(GET_BIT(TWCR,TWINT)==0);
		//Check ACK = Master transmit ( slave address + Read request )
		while(TWI_SLAVE_ADDRESS_READ_ACK!=TWI_STATUS_VALUE);
	}
}
void TWI_sendMasterDataByte           (u8 TxData){
	//Load data into the data register
	TWDR=TxData;
	//Clear TWI Interrupt Flag (Read Datasheet)
	SET_BIT(TWCR,TWINT);
	//Busy wait for the flag
	while(GET_BIT(TWCR,TWINT)==0);
	//Check ACK = Master transmit data ACK
	while(TWI_MASTER_DATA_TRANSMIT_ACK!=TWI_STATUS_VALUE);
}
void TWI_receiveMasterDataByteWithAck (u8* RxData){
	//Read from data register
	if(RxData!=NULL){
		//Enable ACK
		SET_BIT(TWCR,TWEA);
		//Clear TWI Interrupt Flag (Read Datasheet)
		SET_BIT(TWCR,TWINT);
		//Busy wait for the flag
		while(GET_BIT(TWCR,TWINT)==0);
		//Check ACK = Master receive data ACK
		while(TWI_MASTER_DATA_RECIEVE_ACK!=TWI_STATUS_VALUE);
		*RxData=TWDR;
		// Disable ACK
		CLR_BIT(TWCR,TWEA);
	}
	
}
void TWI_receiveMasterDataByteWithNack(u8* RxData){
	if(RxData!=NULL){
		//Clear TWI Interrupt Flag (Read Datasheet)
		SET_BIT(TWCR,TWINT);
		//Busy wait for the flag
		while(GET_BIT(TWCR,TWINT)==0);
		//Check ACK = Master receive data ACK
		while(TWI_MASTER_DATA_RECIEVE_NACK!=TWI_STATUS_VALUE);
		*RxData=TWDR;
	}
}