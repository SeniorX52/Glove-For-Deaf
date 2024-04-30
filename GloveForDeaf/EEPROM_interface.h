/*
 * EEPROM_interface.h
 *
 * Created: 2/17/2024 7:15:12 PM
 *  Author: HP
 */ 


#ifndef EEPROM_INTERFACE_H_
#define EEPROM_INTERFACE_H_


#include "STD_TYPES.h"

#define EEPROM_FIXED_ADDRESS			0x50
#define EEPROM_MAX_SIZE					512
void EEPROM_init		(void);
void EEPROM_writeByte	(u16 wordAddress,u8 data);
void EEPROM_writePage	(u16 wordAddress,u8* data,u8 dataSize);
void EEPROM_readByte	(u16 baseAddress,u8* data);
void EEPROM_readPage	(u16 baseAddress,u8* data,u8 dataSize);
u8 len(u8* string);
void EEPROM_writeString(u8 address,u8* string);
void EEPROM_readString(u8 address,u8* string,u8 letters);
void EEPROM_clear(void);


#endif /* EEPROM_INTERFACE_H_ */