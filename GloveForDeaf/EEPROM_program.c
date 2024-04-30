/*
 * EEPROM_program.c
 *
 * Created: 2/17/2024 7:15:55 PM
 *  Author: HP
 */ 

#define F_CPU 16000000UL
#include <util/delay.h>
//*********UTILES_LIB*********//
#include "BIT_MATH.h"
#include "STD_TYPES.h"
//*********MCAL*********//
#include "TWI_interface.h"
//*********HAL*********//
#include "EEPROM_interface.h"

void EEPROM_init		(void){
	TWI_initMaster();
}
void EEPROM_writeByte	(u16 wordAddress,u8 data){
	TWI_sendStartCondition();
	u8 slaveAddress=(wordAddress>>8)|EEPROM_FIXED_ADDRESS;
	TWI_sendSlaveAddWithWrite(slaveAddress);
	u8 word=(u8)wordAddress;
	TWI_sendMasterDataByte(word);
	TWI_sendMasterDataByte(data);
	TWI_sendStopCondition();
	// Self-timed Write Cycle delay
	_delay_ms(5);
}
void EEPROM_writePage	(u16 baseAddress,u8* data,u8 dataSize){
	if(data!=NULL&&(dataSize<=16)){
		TWI_sendStartCondition();
		u8 slaveAddress=(baseAddress>>8)|EEPROM_FIXED_ADDRESS;
		TWI_sendSlaveAddWithWrite(slaveAddress);
		u8 word=(u8)baseAddress;
		TWI_sendMasterDataByte(word);
		for(int i=0;i<dataSize;i++){
			TWI_sendMasterDataByte(data[i]);
			_delay_ms(5);
		}
		TWI_sendStopCondition();
		// Self-timed Write Cycle delay
		_delay_ms(5);
	}
}
void EEPROM_readByte	(u16 wordAddress,u8* data){
	if(data!=NULL){
		TWI_sendStartCondition();
		u8 slaveAddress=(wordAddress>>8)|EEPROM_FIXED_ADDRESS;
		//Dummy write
		TWI_sendSlaveAddWithWrite(slaveAddress);
		u8 word=(u8)wordAddress;
		TWI_sendMasterDataByte(word);
		TWI_sendRepStartCondition();
		TWI_sendSlaveAddWithRead(slaveAddress);
		TWI_receiveMasterDataByteWithNack(data);
		TWI_sendStopCondition();
		// Self-timed Write Cycle delay
		_delay_ms(5);
	}
}
void EEPROM_readPage	(u16 baseAddress,u8* data,u8 dataSize){
	if(data!=NULL&& dataSize<=16){
		TWI_sendStartCondition();
		u8 slaveAddress=(baseAddress>>8)|EEPROM_FIXED_ADDRESS;
		u8 word=(u8)baseAddress;
		//Dummy write
		TWI_sendSlaveAddWithWrite(slaveAddress);
		TWI_sendMasterDataByte(word);
		TWI_sendRepStartCondition();
		TWI_sendSlaveAddWithRead(slaveAddress);
		for(int i=0;i<dataSize-1;i++){
			TWI_receiveMasterDataByteWithAck(&data[i]);
			_delay_ms(5);
		}
		TWI_receiveMasterDataByteWithNack(&data[dataSize-1]);
		TWI_sendStopCondition();
		// Self-timed Write Cycle delay
		_delay_ms(5);
	}
}
u8 len(u8* string){
	int c=0;
	while(string[c]!='\0'){
		c++;
	}
	return c;
}
void EEPROM_writeString(u8 address,u8* string){
	u8 c=0;
	u8 length=len(string);
	while(c<length){
		EEPROM_writeByte(address++,(u8)string[c++]);
		_delay_ms(10);
	}
}
void EEPROM_readString(u8 address,u8* string,u8 letters){
	u8 c=0;
	while(c<letters){
		EEPROM_readByte(address++,&string[c++]);
		_delay_ms(10);
	}
	string[c]='\0';
}
void EEPROM_clear(void){
	for(int i=0;i<512;i++){
		EEPROM_writeByte(i,0);
	}
}

