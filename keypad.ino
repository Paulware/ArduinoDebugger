#include <Keypad.h>
const byte ROWS = 4; //four rows
const byte COLS = 4; //four columns
char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte rowPins[ROWS] = {5, 4, 3, 2}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {9, 8, 7, 6}; //connect to the column pinouts of the keypad
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );  
void setup()
{  
  Serial.begin (115200);
  Serial.println ("Open Project Keypad.txt");
  Serial.println ("Press a key");
}
unsigned long timeout = 0;
void loop()
{	
  char key;
  if (millis() > timeout)
  {
  	timeout = millis() + 100;
    key = keypad.getKey();
    if (key)
      Serial.println ( key );
  }
}