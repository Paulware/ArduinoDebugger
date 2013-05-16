#include "Connection.h"
#include "HighLevelMenu.h"
Connection::Connection(Pin * _pin1, Pin * _pin2)
{ 
  char * name1 = _pin1->name;
  char * name2 = _pin2->name;
  pin1 = _pin1;
  pin2 = _pin2;
  line = new Line (_pin1->x,_pin1->y,_pin2->x,_pin2->y);
}

Pin * Connection::OtherPin (Pin * pin)
{
  char * name1 = pin1->name;
  char * name2 = pin2->name;
  // char * name = pin->name;
  
  Pin * otherPin = 0;
  if (pin1 == pin)
    otherPin = pin2;  
  else if (pin2 == pin)
    otherPin = pin1;
  return otherPin;
}

void Connection::Init (HWND hWnd, HINSTANCE hInst)
{	
  line->Init (hWnd, hInst);  
}

void Connection::CleanUp()
{
  line->CleanUp();
}

void Connection::Paint (HDC _hdc, PAINTSTRUCT _ps, HDC _hdcMemory)
{
  line->Paint (_hdc, _ps, _hdcMemory);
}

void Connection::Move()
{  	
  x1 = pin1->x;
  y1 = pin1->y;
  x2 = pin2->x;
  y2 = pin2->y;
  line->MoveTo (x1, y1, x2, y2);
}

Connection::~Connection()
{
  if (line)
    delete (line);
}

void Connection::SaveConnection(FILE * fp)
{
  pin1->parent->SaveYourself (fp);
  fprintf ( fp, ",%s,", pin1->name);
  pin2->parent->SaveYourself (fp);
  fprintf ( fp, ",%s\n", pin2->name);
}
