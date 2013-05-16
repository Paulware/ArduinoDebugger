#include "Pot.h"
Pot::Pot(int _x, int _y,Component * _diagram):ConnectedComponent(_x,_y,_diagram)
{ 
  offOn = false;
  analogInput = new Pin (this);
  gnd = new Pin(this);
  power = new Pin(this);
  power->xOffset = 20;
  power->yOffset = 151;
  analogInput->xOffset = 43;
  analogInput->yOffset = 151;
  gnd->xOffset = 68;
  gnd->yOffset = 151;
  x = _x;
  y = _y;
  gnd->x = x + gnd->xOffset;
  gnd->y = y + gnd->yOffset;    
  power->x = x + power->xOffset;
  power->y = y + power->yOffset; 
  analogInput->x = x + analogInput->xOffset;
  analogInput->y = y + analogInput->yOffset;
  power->SetName ("POT +");
  gnd->SetName ("POT -");
  analogInput->SetName ("POT A");  
  SaveType ("POT");       
}

Pot::~Pot()
{
  delete (gnd);
  delete (power);
  delete (analogInput);
  DeleteConnections();
}

Pin * Pot::FindPort ( char * port)
{
  Pin * pin;
  if (!strcmp (port,"POT -"))
    pin = gnd;
  if (!strcmp(port,"POT +"))
    pin = power;
  if (!strcmp(port,"POT A"))
    pin = analogInput;
  return pin;    
}

void Pot::AddMenu ()
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

void Pot::HandleMouseDown (HWND hWnd, int _x, int _y)
{
  ConnectedComponent::HandleMouseDown (hWnd,_x,_y);
  if (gnd->isActive) // we are over the ground spot     
    gnd->Select(!gnd->isSelected);
  else if (power->isActive)
    power->Select(!power->isSelected);
  else if (analogInput->isActive)
    analogInput->Select (!analogInput->isSelected);  
}

// Move the ports and any connections
void Pot::MoveTo (int _x, int _y)
{	
  x = _x-xOffset;
  y = _y-yOffset; // Get the x location after adjusting for mouse click location
  gnd->MoveTo (x + gnd->xOffset, y + gnd->yOffset);
  power->MoveTo (x + power->xOffset, y + power->yOffset);
  analogInput->MoveTo (x + analogInput->xOffset, y + analogInput->yOffset);
  // Move connections
  ConnectedComponent::Move ();   
}

void Pot::Select ( bool select)
{
  gnd->Select(false);
  power->Select(false);
  analogInput->Select(false);
}

Pin * Pot::PortSelected(){
  Pin * pin = 0;
  if (gnd->isSelected)
  	pin = gnd;
  if (power->isSelected)
  	pin = power;
  if (analogInput->isSelected)
    pin = analogInput;  
    
  return pin;  
}

Pin * Pot::PinActive ()
{
  Pin * pin = 0;
  if (gnd->isActive)
    pin = gnd;
  else if (power->isActive)
    pin = power;
  else if (analogInput->isActive)
    pin = analogInput;  
  return pin;
}

// Check if the mouse has moved over one of the ports.
// This should only set isActive to true (not move the item)
void Pot::HandleMouseMove (HWND hWnd, int _x, int _y)
{
  gnd->HandleMouseMove ( hWnd, _x, _y );
  power->HandleMouseMove (hWnd, _x, _y );
  analogInput->HandleMouseMove (hWnd, _x, _y);  
}

void Pot::HandleMouseUp (HWND hWnd)
{
}

void Pot::HandleMenu ( int command )
{
}

void Pot::SaveYourself (FILE * fp)
{
  fprintf ( fp, "Pot,%d,%d",x,y);	
}

bool Pot::IsSet()
{
  bool set = (gnd->IsSet() && power->IsSet() && analogInput->IsSet());
  return set;
}

void Pot::Reset()
{
  gnd->Reset();
  power->Reset();
  analogInput->Reset();
}

void Pot::Paint(HDC _hdc, PAINTSTRUCT _ps, HDC _hdcMemory)
{
  bool ledOn; 
   
  /* 
  // Paint the light on/off
  if (gnd->GetValue() == 1)
    ledOn = false;
  else if (power->GetValue() == 0)
    ledOn = false;
  else if (gnd->GetValue() == -1)
    ledOn = false;
  else if (power->GetValue() == -1)
    ledOn = false;  
  else
    ledOn = true;  
      
  if (ledOn)
    ConnectedComponent::Init ( windowHandle, g_hInst, "REDLED");
  else
    ConnectedComponent::Init ( windowHandle, g_hInst, "BLACKLED");
  
  */  
  // Paint the background
  ConnectedComponent::Paint (_hdc, _ps, _hdcMemory);
    
  // Paint the hotspots
  gnd->Paint(hdc, ps, hdcMemory);
  power->Paint(hdc, ps, hdcMemory);
  analogInput->Paint (hdc, ps, hdcMemory);
}

void Pot::CleanUp()
{
  ConnectedComponent::CleanUp();
  
  gnd->CleanUp();
  power->CleanUp();
  analogInput->CleanUp();
}

void Pot::Init (HWND _windowHandle, HINSTANCE _g_hInst, char * resource)
{   
   ConnectedComponent::Init ( _windowHandle, _g_hInst, resource);
   gnd->Init (windowHandle, g_hInst);
   power->Init (windowHandle, g_hInst);   
   analogInput->Init (windowHandle, g_hInst);
}

