#include <EEPROM.h>
EEPROMClass::EEPROMClass ()
{
  for (int i=0; i<MAX_EEPROM; i++)
    buf[i] = 0;
}
uint8_t EEPROMClass::read(int index)
{
  uint8_t val = 0;
  if (index < MAX_EEPROM) 
    val = buf[index];
  return val;
}

void EEPROMClass::write ( int index, uint8_t value)
{
  if (index < MAX_EEPROM)
    buf[index] = value;
}
