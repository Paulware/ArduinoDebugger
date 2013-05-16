// 
//    FILE: I2C_eeprom.cpp
//  AUTHOR: Rob Tillaart, Paul Richards
// VERSION: 0.3.00
// PURPOSE: Simple I2C_eeprom library for Arduino with EEPROM 24FC1026
//
// HISTORY: 
// 0.1.00 - 2011-01-21 initial version
// 0.1.01 - 2011-02-07 added setBlock function
// 0.2.00 - 2011-02-11 fixed 64 bit boundary bug
// 0.3.00 - 2012-10-4  PRR support for bytes beyond 64K
// 
// Released to the public domain
//

#include <I2C_eeprom.h>
#include <Wire.h>
#include <Arduino.h>

////////////////////////////////////////////////////////////////////
//
// PUBLIC
//

I2C_eeprom::I2C_eeprom(uint8_t device, uint8_t _upperDevice)
{
	_Device = (uint8_t) device;
    upperDevice = _upperDevice;
	Wire.begin(); 		// initialise the connection
}

void I2C_eeprom::writeByte(unsigned long address, uint8_t data )
{
	_WriteBlock(address, &data, 1);
}

void I2C_eeprom::writeBlock(unsigned long address, uint8_t* buffer, int length)
{
	// determine length until end of page
	int le = endOfPage(address);
	if (le > 0)
	{
		_WriteBlock(address, buffer, le);
		address += le;
		buffer += le;
		length -= le;
	}

    // TODO: This block may be on a difference device
	// write the rest at BLOCKSIZE (16) byte boundaries 
	while (length > 0)
	{
		_WriteBlock(address, buffer, minValue(length, BLOCKSIZE));
		address += BLOCKSIZE;
		buffer += BLOCKSIZE;
		length -= BLOCKSIZE;
	}
}

int I2C_eeprom::minValue (int val1, int val2 )
{
  if (val1 < val2)
    return val1;
  else
    return val2;
}

void I2C_eeprom::setBlock(unsigned long address, uint8_t data, int length)
{
	uint8_t buffer[BLOCKSIZE];
	for (uint8_t i =0; i< BLOCKSIZE; i++) buffer[i] = data;

	// determine length until end of page
	int le = endOfPage(address);
	if (le > 0)
	{
		_WriteBlock(address, buffer, le);
		address += le;
		length -= le;
	}

	while (length > 0)
	{
        if (length < BLOCKSIZE)
  		  _WriteBlock(address, buffer, length);
        else
  		  _WriteBlock(address, buffer, BLOCKSIZE);
		address += BLOCKSIZE;
		length -= BLOCKSIZE;
	}
}

uint8_t I2C_eeprom::readByte(unsigned long address)
{
	uint8_t rdata;
	_ReadBlock(address, &rdata, 1);
	return rdata;
}

// maybe let's not read more than BLOCKSIZE uint8_ts at a time!
void I2C_eeprom::readBlock(unsigned long address, uint8_t* buffer, int length)
{
	while (length > 0)
	{
        if (length < BLOCKSIZE)
		  _ReadBlock(address, buffer, length);
		else
		  _ReadBlock(address, buffer, BLOCKSIZE);
		address += BLOCKSIZE;
		buffer += BLOCKSIZE;
		length -= BLOCKSIZE;
	}
}

////////////////////////////////////////////////////////////////////
//
// PRIVATE
//

// detemines length until first multiple of 16 of an address
// so writing allways occurs up to 16 byte boundaries
// this is automatically 64 byte boundaries
int I2C_eeprom::endOfPage(unsigned long address)
{
	const int m = BLOCKSIZE;
	unsigned long eopAddr = ((address + m - 1) / m) * m;  // "end of page" address
	return eopAddr - address;  // length until end of page
}

// pre: length < 32;
void I2C_eeprom::_WriteBlock(unsigned long address, uint8_t* buffer, uint8_t length)
{
    unsigned long msb = address >> 8;
    unsigned long lsb = address & 0xFF;
    uint8_t device;
    
    if (address & 0x10000)
      device = upperDevice;
    else // Todo handle write that span the devices 
      device = _Device;
    Wire.beginTransmission(device);
      
    msb = msb & 0xFFFF; // Clear the device bit
    
	Wire.write((int)msb); 
	Wire.write((int)lsb);  
	for (uint8_t c = 0; c < length; c++)
	Wire.write(buffer[c]);
	Wire.endTransmission();
	delay(5);
}

// pre: buffer is large enough to hold length bytes
void I2C_eeprom::_ReadBlock(unsigned long address, uint8_t* buffer, uint8_t length)
{
    unsigned long msb = address >> 8;
    unsigned long lsb = address & 0xFF;
    uint8_t device;
    if (address & 0x10000)
      device = upperDevice;
    else 
      device = _Device;
      
    Wire.beginTransmission(device);
    msb = msb & 0xFFFF; // Clear the device bit
    
	Wire.write((int)msb);
	Wire.write((int)lsb);
	Wire.endTransmission();
    
    /* 
       Todo: the read may actually span a device, so 2 reads may be required
    */
	Wire.requestFrom(device, length);
	for (int c = 0; c < length; c++ )
	if (Wire.available()) buffer[c] = Wire.read();
}
//
// END OF FILE
//
