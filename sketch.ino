// clockPin
#define SRCLK 12
// data pin
#define SER 11

int offOn = 0;
bool switchPressed = false;
int count = 0;

void setup()
{  
  Serial.begin (115200);
  Serial.println ( "Open ShiftRegister.txt project" );
  pinMode (10,INPUT);
  digitalWrite (10,1); // pull-up resistor set
  pinMode (SRCLK,OUTPUT);  // Shift Register Clock
  digitalWrite (SRCLK,0);  // No-Shift
  pinMode (SER,OUTPUT);    // Shift Register Data
  digitalWrite (SER,0);    // Clear Data
}

void shiftOut_X(uint8_t dataPin, uint8_t clockPin, uint8_t bitOrder, uint8_t NofRegisters, uint8_t *val)
{
  uint8_t i;
  uint8_t i1;
  uint8_t Sbyte;
  uint8_t shiftNo;
  
  if (bitOrder == LSBFIRST)
  {
    shiftNo = 0;
    Sbyte = *(val + shiftNo);
    for (i1 = 0; i1 < NofRegisters; i1++) 
    {					
      for (i = 0; i < 8; i++)  
      {
	    digitalWrite(dataPin, !!(Sbyte & (1 << i)));
        digitalWrite(clockPin, HIGH);
        digitalWrite(clockPin, LOW);
      }
      Sbyte = *(val + (++shiftNo));
    }
  }
  else if (bitOrder == MSBFIRST)
  {
    shiftNo = NofRegisters - 1;
    Sbyte = *(val + shiftNo);
    for (i1 = 0; i1 < NofRegisters; i1++) 
    {
      for (i = 0; i < 8; i++)  
      {
        digitalWrite(dataPin, !!(Sbyte & (1 << (7 - i))));						
        digitalWrite(clockPin, HIGH);
        digitalWrite(clockPin, LOW);
      }
      Sbyte = *(val + (--shiftNo));
	}
  }		
}

void loop ()
{
  uint8_t val;
  if (!digitalRead (10)) // Button Down
  	switchPressed = true;
  else
  {
  	if (switchPressed) // Button Up
  	{
  	  if (!offOn)
  	  {
  	  	count++;
  	  	val = count & 0xFF;
  	  	shiftOut_X ( SER, SRCLK, MSBFIRST, 1, &val);
        /* 
  	    digitalWrite (SER,1);
  	    Serial.println (++count);
  	    digitalWrite (SRCLK,1); // Cause shift 
  	    */
      }
  	  offOn = 1; // Only written once 
  	} 
	else 
  	{
  	  if (offOn) // Only do this once
  	  {
  	    digitalWrite (SER,0);
  	    digitalWrite (SRCLK,0);
      }
  	  offOn = 0;
  	}
  	switchPressed = false;
  }
}

