#define BAUDRATE 115200
#define LOWPIN 2
#define HIPIN 13
unsigned long timeout = 0;
void setup()
{
  Serial.begin(BAUDRATE);
  Serial.println ( "Open Rotary Dip project: RotaryDip.txt" );
  for (int i=HIPIN; i>(LOWPIN-1); i--)
  {
    pinMode (i, INPUT);
    digitalWrite(i,1); // set pull-up resistor
  }
}
int readPins()
{
  int values[] = {0,0,1,2,4,8,10,20,40,80,100,200,400,800};
  int value = 0;     
    
  for (int i=HIPIN; i>(LOWPIN-1); i--)
    if (!digitalRead (i))
      value += values[i];
  return value;
}
void loop()
{
  static int lastPins = 0;
  int pins = readPins();
  if (pins != lastPins)
  {
    Serial.print ( "Switch Selection: " );
    Serial.println ( pins);
  }
  lastPins = pins;
}
