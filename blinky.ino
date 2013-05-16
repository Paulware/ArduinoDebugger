void setup()
{
  Serial.begin (115200);
  Serial.println ( "Open Blinky.txt project" );
  pinMode (13,OUTPUT);
}
unsigned long timeout = 0;
void loop()
{
  static int onOff = 0;
  if (millis() > timeout)
  {
  	timeout = millis() + 1000;
  	onOff = 1 - onOff;
  	digitalWrite (13,onOff);
  }
}
