#ifndef I2C_EEPROM_H
#define I2C_EEPROM_H
// 
//    FILE: I2C_eeprom.h
//  AUTHOR: Rob Tillaart
// PURPOSE: Simple I2C_eeprom library for Arduino with EEPROM 24LC256 et al.
// VERSION: 0.2.00
//     URL: http://arduino.cc/playground/Main/LibraryForI2CEEPROM
// HISTORY: See I2C_eeprom.cpp
//
// Released to the public domain
//

#include <Wire.h>

// BLOCKSIZE must be 16, 128?
#define BLOCKSIZE 16

// #define I2C_EEPROM_VERSION "0.2"

// interface
class I2C_eeprom 
{
	public:
	// (I2C address)
	I2C_eeprom(uint8_t, uint8_t);
	// (mem_address, value)
	void writeByte(unsigned long, uint8_t );
	// (mem_address, buffer, length)
	void writeBlock(unsigned long, uint8_t*, int ); 
	// (mem_address, value, count)
	void setBlock(unsigned long, uint8_t, int ); 
	// (mem_address)
	uint8_t readByte(unsigned long );
	// (mem_address, buffer, length)
	void readBlock(unsigned long, uint8_t*, int );

	private:
	uint8_t _Device;      // Access lower 512K bits
    uint8_t upperDevice;  // Access upper 512K bits
	// (address)
	int endOfPage(unsigned long);  
	// (mem_address, buffer, length)
	void _WriteBlock(unsigned long, uint8_t*, uint8_t );
	void _ReadBlock(unsigned long, uint8_t*, uint8_t );
    int minValue (int val1, int val2 );
};
#endif
