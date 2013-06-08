#define A 2
#define B 3
#define C 4
void setup()
{  
  Serial.begin (115200);
  Serial.println ( "Open Multiplexer.txt project" );
  pinMode (A,OUTPUT);
  pinMode (B,OUTPUT);
  pinMode (C,OUTPUT);
  pinMode (10,INPUT);
  digitalWrite (10,1); // Set pull-up resistor
  digitalWrite (A,0);
  digitalWrite (B,0);
  digitalWrite (C,0);
}
int offOn = 0;
bool switchPressed = false;
int count = 0;
void loop () // Switch press will toggle between Ch0 and Ch1
{
  if (!digitalRead (10)) // Button Down
  	switchPressed = true;
  else
  {
  	if (switchPressed) // Button Up
  	{
  	  if (!offOn)
  	  {
	    count++;
		Serial.println ( count );
		if (count & 1)
		  digitalWrite (A,0); // Ch0
        else
		  digitalWrite (A,1); // Ch1
      }
  	  offOn = 1; // Only written once 
  	} 
	else 
  	{
  	  offOn = 0;
  	}
  	switchPressed = false;
  }
}
