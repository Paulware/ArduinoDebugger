#include <Keypad.h>
#include <LiquidCrystal.h>
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
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);
  
void setup()
{  
  bool d10;
  Serial.begin (115200);
  lcd.begin(20, 4); // Specify how many columns and rows in the LCD unit
  lcd.clear();
  lcd.print("LCD Ready   ");
  Serial.println ("Project: KeypadDisplay");
  Serial.println ("Press '*' or '#' to see a message");
}
void loop()
{
  char key = keypad.getKey();
  
  switch (key)
  {
  	case '*':
  	  lcd.clear();
      lcd.print ("A star was pressed");
  	break;
  	
  	case '#':
  	  lcd.clear();
      lcd.print ("A pound was pressed");
  	break;
  	
  	default:
  	  if (key)
   	    lcd.print (key);
	break;
  }
   
  
}
