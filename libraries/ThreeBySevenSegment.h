/*
||
|| ThreeBySevenSegment Library 
|| Arduino library to correctly display a value on the hardware 
||
*/

#ifndef ThreeBySevenSegment_h
#define ThreeBySevenSegment_h

#include <Arduino.h>

class ThreeBySevenSegment{

public:
  ThreeBySevenSegment (); // Pins will be set later
  ThreeBySevenSegment(byte segmentA, byte segmentB, byte segmentC, byte segmentD, 
                      byte segmentE, byte segmentF, byte segmentG, byte segmentDP, 
					  byte digit_1,   byte digit_2, byte digit_3); 
					  
  void setPins (byte segmentA, byte segmentB, byte segmentC, byte segmentD, 
                byte segmentE, byte segmentF, byte segmentG, byte segmentDP, 
				byte digit_1, byte digit_2, byte digit_3);    
				
  // void lightWord ( char * msg );
  void lightCharacter(int whichDigit, char ch);
    
private:
  static int const MAXPINS = 10;
  static int const DISPLAY_BRIGHTNESS = 500;
  
  int digit1;  // Digit 1 turn on 
  int digit2;  // Digit 2 turn on
  int digit3;  // Digit 3 turn on

/*
    For a seven segment display, segments are defined:

            A
         -------    
        |       |
     F  |       | B
        |   G   |
         -------
        |       |
     E  |       | C
        |       |
         -------
            D      Dp (Decimal Point)
*/  
  
  // variables to hold the pin numbers of each segment
  int segA;   
  int segB;
  int segC;
  int segD;
  int segE;
  int segF;
  int segG;
  int segDP;  
};

#endif
