#include "Pin.h"
#include "HighLevelMenu.h"
#include "Connection.h"
Pin::Pin(Component * _parent):Component()
{ 
  value.value = -1;
  value.resistance = 100000;
  constValue.value = -1;	 
  constValue.resistance = 100000;
  
  x = 0;
  y = 0; 
  xOffset = 0;
  yOffset = 0;  
  isActive = false;
  isSelected = false;
  name = 0; 
  parent = _parent;
  connection = 0;
  traversed = false;
}

Pin::~Pin()
{
  delete (name);
}

void Pin::SetConnection (Component * _connection)
{
  connection = _connection;
}

void Pin::SetName(char * _name)
{
  name = (char *)calloc (1,strlen(_name)+1);
  strcpy ( name,_name);
}

void Pin::Init (HWND _windowHandle, HINSTANCE _g_hInst)
{
  Component::Init (_windowHandle, _g_hInst, "");
} 

void Pin::Paint (HDC _hdc, PAINTSTRUCT _ps, HDC _hdcMemory)
{ 
  if (isActive)   
    Component::Init (windowHandle, g_hInst, "REDDOT");
  else
    Component::Init (windowHandle, g_hInst, "BLACKDOT");
    
  Component::Paint (_hdc, _ps, _hdcMemory);   
}

void Pin::MoveTo (int _x, int _y)
{
  x = _x;
  y = _y;
  Refresh();
}

// Change color of pin to indicate active
void Pin::Select(bool active)
{
  isSelected = active;    
}

// [_x,_y] is absolute not relative to parent
void Pin::HandleMouseMove (HWND hWnd, int _x, int _y)
{
  if ((_x >= x) && (_x <= x+bm.bmWidth) && (_y >= y) && (_y <= y+bm.bmHeight))
    isActive = true;
  else if (isActive)
    isActive = false;    
}

bool Pin::IsSet()
{
  bool set = true;
  if (GetValue() == -1)
    set = false;
  return set;  
}

int Pin::GetResistance()
{
  return value.resistance;
}

// Check constValue, actual value or connected value
int Pin::GetValue ()
{ 
  int val = value.value;
   
  /*   
  char * n = name; // For debug

  if (value.value != -1)
  {
    if (value.resistance <= constValue.resistance)
      val = value.value;
    else if (constValue.value != -1)
	  val = constValue.value;  
  }
  if (val == 1)
    val = 1;  
  */
  return val;
}


bool Pin::IsSelected ()
{
  return isSelected;
}

