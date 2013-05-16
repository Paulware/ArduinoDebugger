#include "SevenSegment.h"

SevenSegment::SevenSegment( ShiftRegister& userShiftRegister ){
	shiftRegister = &userShiftRegister;
	initialize();
}

SevenSegment::SevenSegment(byte p0, byte p1, byte p2, byte p3, byte p4, byte p5, byte p6){
	initialize();
    pinArray[0] = p0;
    pinArray[1] = p1;
    pinArray[2] = p2;
	pinArray[3] = p3;
	pinArray[4] = p4;
	pinArray[5] = p5;
	pinArray[6] = p6;
	for (int i=0;i<7;i++)
		pinMode(pinArray[i],OUTPUT);
	
	print (1);
}

void SevenSegment::setPins (byte p0, byte p1, byte p2, byte p3, byte p4, byte p5, byte p6) 
{
    pinArray[0] = p0;
    pinArray[1] = p1;
    pinArray[2] = p2;
	pinArray[3] = p3;
	pinArray[4] = p4;
	pinArray[5] = p5;
	pinArray[6] = p6;
    for (int i=0; i<7; i++)
      pinMode (pinArray[i], OUTPUT);
}

//buffer a number to display
void SevenSegment::buffer(byte number){
	bufferByte = number;
}

//print a number to the display
void SevenSegment::print(){
/*
	if(shiftRegister){
		shiftRegister->write( bufferByte );
	}else{
		for (byte col=0;col<7;col++){
			digitalWrite(pinArray[col],bitRead(bufferByte,col));
		}
	}
	*/
}

//print a number to the display
void SevenSegment::print(byte number){
  int pin;
  int value;
  if(shiftRegister){
	shiftRegister->write( dataArray[number] );
  }else{
	for (byte col=0;col<7;col++){
      pin = pinArray[col];
      // Make sure number if bounded
      value = bitRead(dataArray[number % 10],col);
      digitalWrite (pin,value);  
	}
	value = digitalRead (3);
  }
}

void SevenSegment::attachShiftRegister( ShiftRegister& userShiftRegister ){
	shiftRegister = &userShiftRegister;
}

//initialize data
void SevenSegment::initialize(){
	bufferByte = 0;
	shiftRegister = 0;
	byte data[10] = {
        0x3F,
		// B011 1111, 0 (6 segments )
		0x06,
		// B000 0110, 1 (2 segments)
		0x5B,
		// B101 1011, 2 (5 segments)
		0x4F,
		// B100 1111, 3 (5 segments)
		0x66,
		// B110 0110, 4 (4 segments)
		0x6D,
		// B110 1101, 5 (5 segments)
		0x7D,
		// B111 1101, 6 (6 segments)
		0x07,
		// B000 0111, 7 (3 segments)
		0x7F,
		// B111 1111, 8 (All 7 segments)
		0x6F
		// B110 1111  9 (6 segments)
	};
	for (byte row=0; row<10; row++){
		dataArray[row]=data[row];
	}
}
