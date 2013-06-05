#include <SevenSegment.h>
SevenSegment sevenSegment (2,3,4,5,6,13,14);
void setup()
{  
  Serial.begin (115200);
  Serial.println ( "Open SevenSeg.txt project" );
  pinMode (10, INPUT);
  digitalWrite (10,1); // Pull-up resistor on
}
int buttonCount = 0;
void loop ()
{
  static int last10 = 0;
  int d10;
  d10 = digitalRead(10);
  if (!d10 && last10)
  {
  	buttonCount++;
  	Serial.print ( "Detected button press ");
  	Serial.println ( buttonCount );
    sevenSegment.print(buttonCount );  	
  }
  last10 = d10;
}
