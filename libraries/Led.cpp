#include "Led.h"
Led::Led(int _x, int _y, Component * _diagram):ConnectedComponent(_x,_y, _diagram)
{ 
  offOn = false;
  gnd = new Pin(this);
  power = new Pin(this);
  power->xOffset = 38;
  power->yOffset = 170;
  gnd->xOffset = 55;
  gnd->yOffset = 140;
  x = _x;
  y = _y;
  gnd->x = x + gnd->xOffset;
  gnd->y = y + gnd->yOffset;    
  power->x = x + power->xOffset;
  power->y = y + power->yOffset; 
  power->SetName ("LED +");
  gnd->SetName ("LED -");   
  SaveType ("LED");       
}

Led::~Led()
{
  delete (gnd);
  delete (power);
  DeleteConnections();
}

Pin * Led::FindPort ( char * port)
{
  Pin * pin;
  if (!strcmp (port,"LED -"))
    pin = gnd;
  if (!strcmp(port,"LED +"))
    pin = power;
  return pin;    
}

void Led::AddMenu ()
{
  HMENU  MainMenu;
  HMENU  FileMenu;
     
  //arduinoMain.setHwnd ( hwndOwner);
  MainMenu=CreateMenu();
  FileMenu=CreateMenu();
  InsertMenu(MainMenu,ID_Edit,MF_POPUP,(UINT_PTR)FileMenu,"Help");
  AppendMenu(FileMenu,MF_STRING,COMPONENT_ABOUT,"&About");
  AppendMenu(FileMenu,MF_SEPARATOR,0,"");
  AppendMenu(FileMenu,MF_STRING,COMPONENT_HELP,"&Component Help");
  //  activate menu 
  (void) SetMenu(windowHandle,MainMenu);
}

void Led::HandleMouseDown (HWND hWnd, int _x, int _y)
{
  ConnectedComponent::HandleMouseDown (hWnd,_x,_y);
  if (gnd->isActive) // we are over the ground spot     
    gnd->Select(!gnd->isSelected);
  else if (power->isActive)
    power->Select(!power->isSelected);  
}

// Move the ports and any connections
void Led::MoveTo (int _x, int _y)
{	
  x = _x-xOffset;
  y = _y-yOffset; // Get the x location of the LED after adjusting for mouse click location
  gnd->MoveTo (x + gnd->xOffset, y + gnd->yOffset);
  power->MoveTo (x + power->xOffset, y + power->yOffset);
  // Move connections
  ConnectedComponent::Move ();   
}

void Led::Select ( bool select)
{
  gnd->Select(false);
  power->Select(false);
}

Pin * Led::PortSelected(){
  Pin * pin = 0;
  if (gnd->isSelected)
  	pin = gnd;
  if (power->isSelected)
  	pin = power;
    
  return pin;  
}

Pin * Led::PinActive ()
{
  Pin * pin = 0;
  if (gnd->isActive)
    pin = gnd;
  else if (power->isActive)
    pin = power;
  return pin;
}

// Check if the mouse has moved over one of the ports.
// This should only set isActive to true (not move the item)
void Led::HandleMouseMove (HWND hWnd, int _x, int _y)
{
  gnd->HandleMouseMove ( hWnd, _x, _y );
  power->HandleMouseMove (hWnd, _x, _y ); 
}

void Led::HandleMouseUp (HWND hWnd)
{
}

void Led::HandleMenu ( int command )
{
}

void Led::SaveYourself (FILE * fp)
{
  fprintf ( fp, "Led,%d,%d",x,y);	
}

bool Led::IsSet()
{
  bool set = (gnd->IsSet() && power->IsSet());
  return set;
}

void Led::Reset()
{
  gnd->Reset();
  power->Reset();
}

void Led::Paint(HDC _hdc, PAINTSTRUCT _ps, HDC _hdcMemory)
{
  bool ledOn; 
  static int lastReason = 0;
  int gndValue = gnd->GetValue();
  int pwrValue = power->GetValue();
   
  // Paint the light on/off
  if (gndValue == 1) // Off
  {
    ledOn = false;
    lastReason = 1;
  }
  else if (pwrValue == 0) // Off 
  {
    ledOn = false;
    lastReason = 2;
  }
  else if (gndValue == -1) // Not set yet
  {
    ledOn = false;
    lastReason = 3;
  }
  else if (pwrValue == -1) // Not set yet
  {
    ledOn = false;  
    lastReason =  4;
  }
  else
  {
    ledOn = true;  
    lastReason = 5; 
  }
  if (ledOn)
    ConnectedComponent::Init ( windowHandle, g_hInst, "REDLED");
  else
    ConnectedComponent::Init ( windowHandle, g_hInst, "BLACKLED");
    
  // Paint the background
  ConnectedComponent::Paint (_hdc, _ps, _hdcMemory);
    
  // Paint the hotspots
  gnd->Paint(hdc, ps, hdcMemory);
  power->Paint(hdc, ps, hdcMemory);
}

void Led::CleanUp()
{
  ConnectedComponent::CleanUp();
  
  gnd->CleanUp();
  power->CleanUp();
}

void Led::Init (HWND _windowHandle, HINSTANCE _g_hInst, char * resource)
{   
   ConnectedComponent::Init ( _windowHandle, _g_hInst, resource);
   gnd->Init (windowHandle, g_hInst);
   power->Init (windowHandle, g_hInst);   
}

