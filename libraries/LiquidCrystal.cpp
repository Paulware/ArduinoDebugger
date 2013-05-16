#include "LiquidCrystal.h"
#include "HighLevelMenu.h"

LiquidCrystal::LiquidCrystal()
{ 
}

void LiquidCrystal::print (char ch)
{
  char oneCh[] = " ";
  oneCh[0] = ch;	
  HighLevelMenu::Instance()->lcdPrint ( oneCh );
}

void LiquidCrystal::print (char * line)
{
  HighLevelMenu::Instance()->lcdPrint ( line );
}

void LiquidCrystal::clear()
{
  HighLevelMenu::Instance()->lcdClear();
}

void LiquidCrystal::print ( int value)
{
  HighLevelMenu::Instance()->lcdPrint ( value );
}

LiquidCrystal::LiquidCrystal(int a,int b,int c,int d,int e,int f)
{
} 

void LiquidCrystal::setCursor(uint8_t _x, uint8_t _y )
{
  x =_x; 
  y=_y;
}
