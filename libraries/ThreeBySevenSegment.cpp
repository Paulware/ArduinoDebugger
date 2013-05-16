#include "ThreeBySevenSegment.h"
#include "Arduino.h"

ThreeBySevenSegment::ThreeBySevenSegment(byte segmentA, byte segmentB, byte segmentC, byte segmentD, 
                                         byte segmentE, byte segmentF, byte segmentG, byte segmentDP, 
				                    	 byte digit_1, byte digit_2, byte digit_3)
{
	segA = segmentA;
	segB = segmentB;
	segC = segmentC;
	segD = segmentD;
	segE = segmentE;
	segF = segmentF;
	segG = segmentG;
	segDP = segmentDP;
	digit1 = digit_1;
	digit2 = digit_2;
	digit3 = digit_3;
	
	pinMode (segA, OUTPUT);
	pinMode (segB, OUTPUT);
	pinMode (segC, OUTPUT);
	pinMode (segD, OUTPUT);
	pinMode (segE, OUTPUT);
	pinMode (segG, OUTPUT);
	pinMode (segDP, OUTPUT);
	pinMode (digit1, OUTPUT);
	pinMode (digit2, OUTPUT);
	pinMode (digit3, OUTPUT);		
}

void ThreeBySevenSegment::setPins (byte segmentA, byte segmentB, byte segmentC, byte segmentD, 
                                   byte segmentE, byte segmentF, byte segmentG, byte segmentDP, 
				                   byte digit_1, byte digit_2, byte digit_3) 
{
	segA = segmentA;
	segB = segmentB;
	segC = segmentC;
	segD = segmentD;
	segE = segmentE;
	segF = segmentF;
	segG = segmentG;
	segDP = segmentDP;
	digit1 = digit_1;
	digit2 = digit_2;
	digit3 = digit_3;
	
	pinMode (segA, OUTPUT);
	pinMode (segB, OUTPUT);
	pinMode (segC, OUTPUT);
	pinMode (segD, OUTPUT);
	pinMode (segE, OUTPUT);
	pinMode (segG, OUTPUT);
	pinMode (segDP, OUTPUT);
	pinMode (digit1, OUTPUT);
	pinMode (digit2, OUTPUT);
	pinMode (digit3, OUTPUT);		
}

//Given a character, turn on those segments for the character
void ThreeBySevenSegment::lightCharacter(int whichDigit, char ch) 
{

  digitalWrite ( segDP, 0 ); // TODO hook up decimal point
  
  switch ( whichDigit)
  {
  	case 0: 
  	  digitalWrite ( digit2, 0);
  	  digitalWrite ( digit3, 0);
  	  digitalWrite ( digit1, 1);
  	break;
  	case 1: 
  	  digitalWrite ( digit1, 0);
  	  digitalWrite ( digit3, 0);
  	  digitalWrite ( digit2, 1);
  	break;
  	case 2: 
  	  digitalWrite ( digit1, 0);
  	  digitalWrite ( digit2, 0);
  	  digitalWrite ( digit3, 1);
  	break;
  }
  /*
  digitalWrite(segA, 0);
  digitalWrite(segB, 0);
  digitalWrite(segC, 0);
  digitalWrite(segD, 1);
  digitalWrite(segE, 0);
  digitalWrite(segF, 0);
  digitalWrite(segG, 0);
  return;
  */

  switch (ch)
  {			

  case '0':
  case 0:
    digitalWrite(segA, 1);
    digitalWrite(segB, 1);
    digitalWrite(segC, 1);
    digitalWrite(segD, 1);
    digitalWrite(segE, 1);
    digitalWrite(segF, 1);
    digitalWrite(segG, 0);
    break;

  case 'l':
  case '1':
  case 1:
    digitalWrite(segA, 0);
    digitalWrite(segB, 1);
    digitalWrite(segC, 1);
    digitalWrite(segD, 0);
    digitalWrite(segE, 0);
    digitalWrite(segF, 0);
    digitalWrite(segG, 0);
    break;

  case '2':
  case 2:
    digitalWrite(segA, 1);
    digitalWrite(segB, 1);
    digitalWrite(segC, 0);
    digitalWrite(segD, 1);
    digitalWrite(segE, 1);
    digitalWrite(segF, 0);
    digitalWrite(segG, 1);
    break;

  case '3':
  case 3:
    digitalWrite(segA, 1);
    digitalWrite(segB, 1);
    digitalWrite(segC, 1);
    digitalWrite(segD, 1);
    digitalWrite(segE, 0);
    digitalWrite(segF, 0);
    digitalWrite(segG, 1);
    break;

  case 'y':
  case '4':
  case 4:
    digitalWrite(segA, 0);
    digitalWrite(segB, 1);
    digitalWrite(segC, 1);
    digitalWrite(segD, 0);
    digitalWrite(segE, 0);
    digitalWrite(segF, 1);
    digitalWrite(segG, 1);
    break;

  case 'S':
  case '5':
  case 5:
    digitalWrite(segA, 1);
    digitalWrite(segB, 0);
    digitalWrite(segC, 1);
    digitalWrite(segD, 1);
    digitalWrite(segE, 0);
    digitalWrite(segF, 1);
    digitalWrite(segG, 1);
    break;

  case '6':
  case 6:
    digitalWrite(segA, 1);
    digitalWrite(segB, 0);
    digitalWrite(segC, 1);
    digitalWrite(segD, 1);
    digitalWrite(segE, 1);
    digitalWrite(segF, 1);
    digitalWrite(segG, 1);
    break;

  case '7':
  case 7:
    digitalWrite(segA, 1);
    digitalWrite(segB, 1);
    digitalWrite(segC, 1);
    digitalWrite(segD, 0);
    digitalWrite(segE, 0);
    digitalWrite(segF, 0);
    digitalWrite(segG, 0);
    break;
    
  case 'K':
    digitalWrite(segA, 0);
    digitalWrite(segB, 1);
    digitalWrite(segC, 1);
    digitalWrite(segD, 0);
    digitalWrite(segE, 1);
    digitalWrite(segF, 1);
    digitalWrite(segG, 1);
    break;

  case '8':
  case 8:
    digitalWrite(segA, 1);
    digitalWrite(segB, 1);
    digitalWrite(segC, 1);
    digitalWrite(segD, 1);
    digitalWrite(segE, 1);
    digitalWrite(segF, 1);
    digitalWrite(segG, 1);
    break;

  case '9':
  case 9:
    digitalWrite(segA, 1);
    digitalWrite(segB, 1);
    digitalWrite(segC, 1);
    digitalWrite(segD, 1);
    digitalWrite(segE, 0);
    digitalWrite(segF, 1);
    digitalWrite(segG, 1);
    break;
    
  case 'R':
  case 'A':
    digitalWrite(segA, 1);
    digitalWrite(segB, 1);
    digitalWrite(segC, 1);
    digitalWrite(segD, 0);
    digitalWrite(segE, 1);
    digitalWrite(segF, 1);
    digitalWrite(segG, 1);
    break;
  
  case 'B':
    digitalWrite(segA, 1);
    digitalWrite(segB, 1);
    digitalWrite(segC, 1);
    digitalWrite(segD, 1);
    digitalWrite(segE, 1);
    digitalWrite(segF, 1);
    digitalWrite(segG, 1);
    break;
  
  case 'C':
    digitalWrite(segA, 1);
    digitalWrite(segB, 0);
    digitalWrite(segC, 0);
    digitalWrite(segD, 1);
    digitalWrite(segE, 1);
    digitalWrite(segF, 1);
    digitalWrite(segG, 0);
    break;

  case 'O':    
  case 'D':
    digitalWrite(segA, 1);
    digitalWrite(segB, 1);
    digitalWrite(segC, 1);
    digitalWrite(segD, 1);
    digitalWrite(segE, 1);
    digitalWrite(segF, 1);
    digitalWrite(segG, 0);
    break;

  case 'E':
    digitalWrite(segA, 1);
    digitalWrite(segB, 0);
    digitalWrite(segC, 0);
    digitalWrite(segD, 1);
    digitalWrite(segE, 1);
    digitalWrite(segF, 1);
    digitalWrite(segG, 1);
    break;
  
  case 'F':
    digitalWrite(segA, 1);
    digitalWrite(segB, 0);
    digitalWrite(segC, 0);
    digitalWrite(segD, 0);
    digitalWrite(segE, 1);
    digitalWrite(segF, 1);
    digitalWrite(segG, 1);
    break;
  
  case 'G':
    digitalWrite(segA, 1);
    digitalWrite(segB, 0);
    digitalWrite(segC, 1);
    digitalWrite(segD, 1);
    digitalWrite(segE, 1);
    digitalWrite(segF, 1);
    digitalWrite(segG, 1);
    break;
  
  case 'H':
    digitalWrite(segA, 0);
    digitalWrite(segB, 1);
    digitalWrite(segC, 1);
    digitalWrite(segD, 0);
    digitalWrite(segE, 1);
    digitalWrite(segF, 1);
    digitalWrite(segG, 1);
    break;
  
  case 'c':
    digitalWrite(segA, 0);
    digitalWrite(segB, 0);
    digitalWrite(segC, 0);
    digitalWrite(segD, 1);
    digitalWrite(segE, 1);
    digitalWrite(segF, 0);
    digitalWrite(segG, 1);
    break;
  
  case 'd':
    digitalWrite(segA, 0);
    digitalWrite(segB, 1);
    digitalWrite(segC, 1);
    digitalWrite(segD, 1);
    digitalWrite(segE, 1);
    digitalWrite(segF, 0);
    digitalWrite(segG, 1);
    break;
  
  case 'r':
    digitalWrite(segA, 0);
    digitalWrite(segB, 0);
    digitalWrite(segC, 0);
    digitalWrite(segD, 0);
    digitalWrite(segE, 1);
    digitalWrite(segF, 0);
    digitalWrite(segG, 1);
    break;
  
  case 'b':
    digitalWrite(segA, 0);
    digitalWrite(segB, 0);
    digitalWrite(segC, 1);
    digitalWrite(segD, 1);
    digitalWrite(segE, 1);
    digitalWrite(segF, 1);
    digitalWrite(segG, 1);
    break;
    
  case 'h':    
    digitalWrite(segA, 0);
    digitalWrite(segB, 0);
    digitalWrite(segC, 1);
    digitalWrite(segD, 0);
    digitalWrite(segE, 1);
    digitalWrite(segF, 1);
    digitalWrite(segG, 1);
    break;
    
  case 'L':    
    digitalWrite(segA, 0);
    digitalWrite(segB, 0);
    digitalWrite(segC, 0);
    digitalWrite(segD, 1);
    digitalWrite(segE, 1);
    digitalWrite(segF, 1);
    digitalWrite(segG, 0);
    break;
    
  case 't':    
    digitalWrite(segA, 0);
    digitalWrite(segB, 0);
    digitalWrite(segC, 0);
    digitalWrite(segD, 1);
    digitalWrite(segE, 1);
    digitalWrite(segF, 1);
    digitalWrite(segG, 1);
    break;
    
  case 'P':    
    digitalWrite(segA, 1);
    digitalWrite(segB, 1);
    digitalWrite(segC, 0);
    digitalWrite(segD, 0);
    digitalWrite(segE, 1);
    digitalWrite(segF, 1);
    digitalWrite(segG, 1);
    break;
    
  case 'U':    
    digitalWrite(segA, 0);
    digitalWrite(segB, 1);
    digitalWrite(segC, 1);
    digitalWrite(segD, 1);
    digitalWrite(segE, 1);
    digitalWrite(segF, 1);
    digitalWrite(segG, 0);
    break;
    
  case 'n':
    digitalWrite(segA, 0);
    digitalWrite(segB, 0);
    digitalWrite(segC, 1);
    digitalWrite(segD, 0);
    digitalWrite(segE, 1);
    digitalWrite(segF, 0);
    digitalWrite(segG, 1);
    break;
    
  case 'a':
  case 'o':
    digitalWrite(segA, 0);
    digitalWrite(segB, 0);
    digitalWrite(segC, 1);
    digitalWrite(segD, 1);
    digitalWrite(segE, 1);
    digitalWrite(segF, 0);
    digitalWrite(segG, 1);
    break;
  
  // All off
  case ' ':
  case 10: 
  default:
    digitalWrite(segA, 0);
    digitalWrite(segB, 0);
    digitalWrite(segC, 0);
    digitalWrite(segD, 0);
    digitalWrite(segE, 0);
    digitalWrite(segF, 0);
    digitalWrite(segG, 0);
    break;
  }
}
