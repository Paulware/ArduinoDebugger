#include "ThreeBySevenSegment.h"
ThreeBySevenSegment seg (3,4,5,6,7,8,9,10,11,12,13);
void setup()
{
  Serial.begin (115200);
  Serial.println ( "Open Digit3.txt project" );
  pinMode (2,INPUT);
  digitalWrite(2,1); // Internal pull-up resistor on.
}
int count = 0;
bool primed = false;
void loop ()
{ 
  if (digitalRead (2) == 0)
  {
  	primed = true;
  }
  if (primed)
  {
    if (digitalRead(2)==1)
    {
  	  primed = false;  	
  	  seg.lightCharacter (count % 3,'0'+count);
  	  count++;
    }
  }
}
