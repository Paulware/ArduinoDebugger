#ifndef ARDUINO_H
#define ARDUINO_H
#include "SerialClass.h"
#include "stdlib.h"
#define PSTR (char *)
#define PGM_P char *
#define prog_char char
#define OUTPUT 1
#define INPUT 0
#define HIGH 1
#define LOW 0
#define INPUT_PULLUP 0x2
extern char pgm_read_byte ( char * );
extern SerialClass Serial;
extern unsigned long millis();
extern void digitalWrite ( byte, byte);
extern int digitalRead (byte);
extern void delay (int);
extern int analogRead (int);
extern float log (float);
extern void pinMode (byte pin, byte m);
extern int bitRead (unsigned int, int);
extern HWND viewConnectionHandle; // definition outside class declaration
extern void bitWrite (unsigned int &value, int bit, int val);
extern void delayMicroseconds(int value);
#endif
