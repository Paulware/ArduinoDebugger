#include <LiquidCrystal.h>
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);
unsigned long runTimeout;
void setup()
{  
  Serial.begin (115200);  
  Serial.println ( "Open LCDDisplay.txt project");
  lcd.begin(20, 4); // Specify how many columns and rows in the LCD unit
  lcd.clear();
  lcd.print("HD44780 LCD Ready   ");
  pinMode (10,INPUT); // Switch
  digitalWrite (10,1); // Set the pull-up resistor
}
void loop()
{
  static unsigned long runTimeout;
  static bool last10 = false;
  static int buttonCount = 0;
  int d10; 
  d10 = digitalRead(10);
  if (!d10 && last10)
  {
  	buttonCount++;
  	Serial.print ( "Detected button press ");
  	Serial.println ( buttonCount );
  	lcd.print ( buttonCount ); 	
  }
  last10 = d10; 
}