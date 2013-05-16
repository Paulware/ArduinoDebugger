#include "ArduinoComponent.h"
#include "HighLevelMenu.h"
// 14 Digitals plus 6 analogs can also be used
ArduinoComponent::ArduinoComponent(int _x, int _y, Component * _diagram): ConnectedComponent(_x, _y, _diagram)
{ 
  char name[] = "d00";
  x = _x;
  y = _y;
  gnd = new Pin(this);
  gnd->constValue.value = 0;
  gnd->constValue.resistance = 0;
  gnd->xOffset = 310;
  gnd->yOffset = 319;
  gnd->x = x + gnd->xOffset;
  gnd->y = y + gnd->yOffset;
  gnd->SetName ("gnd");
  power = new Pin (this);
  power->constValue.value = 1;
  power->constValue.resistance=0;
  power->xOffset = 278;
  power->yOffset = 319;
  power->x = x + power->xOffset;
  power->y = y + power->yOffset;
  power->SetName ("5v");
  for (int i=0; i<MAX_DIGITAL_VALUES; i++)
  {
    d[i] = new Pin(this);  
    name[1] = '0' + (i/10);
    name[2] = '0' + (i%10);
    d[i]->SetName (&name[0]);
  }  
  
  digitalValues[0]  = (digitalInfo) {440, 11,false};
  digitalValues[1]  = (digitalInfo) {424, 11,false};
  digitalValues[2]  = (digitalInfo) {408, 11,false};
  digitalValues[3]  = (digitalInfo) {392, 11,false};
  digitalValues[4]  = (digitalInfo) {376, 11,false};
  digitalValues[5]  = (digitalInfo) {360, 11,false};
  digitalValues[6]  = (digitalInfo) {344, 11,false};
  digitalValues[7]  = (digitalInfo) {326, 11,false};
  digitalValues[8]  = (digitalInfo) {300, 11,false};
  digitalValues[9]  = (digitalInfo) {284, 11,false};
  digitalValues[10] = (digitalInfo) {268, 11,false};
  digitalValues[11] = (digitalInfo) {252, 11,false};
  digitalValues[12] = (digitalInfo) {236, 11,false};
  digitalValues[13] = (digitalInfo) {220, 11,false};
  digitalValues[14] = (digitalInfo) {359,320,false}; 
  digitalValues[15] = (digitalInfo) {375,320,false}; 
  digitalValues[16] = (digitalInfo) {391,320,false}; 
  digitalValues[17] = (digitalInfo) {407,320,false}; 
  digitalValues[18] = (digitalInfo) {423,320,false}; 
  digitalValues[19] = (digitalInfo) {439,320,false}; 
  
  for (int i=0; i<MAX_DIGITAL_VALUES; i++)
  {
    d[i]->x = digitalValues[i].x+x;
    d[i]->y = digitalValues[i].y+y;
  }
  SaveType ("Arduino");
}

bool ArduinoComponent::IsSet()
{
  bool isSet = true;
  for (int i=0; i<MAX_DIGITAL_VALUES; i++)
  	if (!d[i]->IsSet())
  	{
  	  isSet = false;
  	  break;
  	}
  return isSet;	
}


void ArduinoComponent::Reset()
{
  for (int i=0; i<MAX_DIGITAL_VALUES; i++)
  	d[i]->Reset();
}


Pin * ArduinoComponent::FindPort ( char * port)
{
  Pin * pin = 0;
  char name[] = "d00";
  
  if (!strcmp ( port, "gnd"))
    pin = gnd;
  if (!strcmp(port, "5v"))
    pin = power;
  for (int i=0; i<MAX_DIGITAL_VALUES; i++)
  {
    name[1] = '0' + (i/10);
    name[2] = '0' + (i%10);
    if (!strcmp ( port, name))
    {
      pin = d[i];
      break;
    }
  }  
  return pin;
}

ArduinoComponent::~ArduinoComponent()
{
	
  delete (gnd);
  delete (power);
  for (int i=0; i<MAX_DIGITAL_VALUES; i++)
  {
    delete (d[i]);
  }
  DeleteConnections();
}

void ArduinoComponent::Connect (Pin * pin1, Pin * pin2)
{
  ConnectedComponent::Connect (pin1,pin2);
}


Pin * ArduinoComponent::GetConnection (int which)
{
  Pin * pin;
  switch (which)
  {
    case 20:
      pin = power;
      break;
    case 21: 
      pin = gnd;
      break;
    default:
      pin = d[which];
	  break;
  }
  return pin;
}

void ArduinoComponent::Paint(HDC _hdc, PAINTSTRUCT _ps, HDC _hdcMemory)
{  
  ConnectedComponent::Paint (_hdc, _ps, _hdcMemory);    
       
  for (int i=0; i<MAX_DIGITAL_VALUES;i++)
  {
    d[i]->g_hInst = g_hInst;
    d[i]->windowHandle = windowHandle;  	
    d[i]->Paint (hdc, ps, hdcMemory);
  }
    
  // Paint the hotspots
  gnd->g_hInst = g_hInst;
  gnd->windowHandle = windowHandle;  	
  gnd->Paint(hdc, ps, hdcMemory);
  power->g_hInst = g_hInst;
  power->windowHandle = windowHandle;  	
  power->Paint(hdc, ps, hdcMemory);
}

void ArduinoComponent::SaveYourself (FILE * fp)
{
  fprintf ( fp, "Arduino,%d,%d",x,y);
}

void ArduinoComponent::digitalWrite (int pin, int value )
{
  Connection * connection;
  Pin * p = 0;
  if ((pin >= 0) && (pin < MAX_DIGITAL_VALUES))
    p = d[pin];
    
  if (p)
  {
    digitalValues[pin].blackRed = (bool) value;
  }
    
  Refresh();
}

void ArduinoComponent::AddMenu ()
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

void ArduinoComponent::CleanUp()
{
  ConnectedComponent::CleanUp();
  gnd->CleanUp();
  power->CleanUp();
  for (int i=0; i<MAX_DIGITAL_VALUES; i++)
    d[i]->CleanUp();
}

void ArduinoComponent::Init (HWND _windowHandle, HINSTANCE _g_hInst, char * resource)
{
   ConnectedComponent::Init (_windowHandle, _g_hInst, resource);
   gnd->Init (windowHandle, g_hInst);
   power->Init (windowHandle, g_hInst);   
   // Show image of digitalValues
   for (int i=0; i<MAX_DIGITAL_VALUES; i++)
     d[i]->Init (windowHandle, g_hInst);   
}

// Move the ports and any connections
void ArduinoComponent::MoveTo (int _x, int _y)
{	
  ConnectedComponent::MoveTo (_x,_y);	

  x = _x-xOffset; // xOffset is where mouse was pressed
  y = _y-yOffset; // yOffset is where mouse was pressed
  
  gnd->MoveTo (x+gnd->xOffset,y+gnd->yOffset);
  power->MoveTo (x+power->xOffset,y+power->yOffset);
  for (int i=0; i<MAX_DIGITAL_VALUES; i++)
    d[i]->MoveTo (x+digitalValues[i].x,y+digitalValues[i].y); 
  // Move connections
  ConnectedComponent::Move ();   
}

Pin * ArduinoComponent::PortSelected()
{
  Pin * pin = 0;
  if (gnd->isSelected)
    pin = gnd;
  else if (power->isSelected)
    pin = power;  
  else
    for (int i=0; i<MAX_DIGITAL_VALUES;i++)
    {
      if (d[i]->isSelected)
      {
        pin = d[i];
        break;
      }
    }
  
  return pin;  
}

Pin * ArduinoComponent::PinActive ()
{
  Pin * pin = 0;
  if (gnd->isActive)
    pin = gnd;
  else if (power->isActive)
    pin = power;  
  else 
    for (int i=0; i<MAX_DIGITAL_VALUES;i++)
    {
      if (d[i]->isActive)
      {
        pin = d[i];
        break;
      }
    }
  return pin;
}

// Check if the mouse has moved over one of the ports.
// This should only set isActive to true (not move the item)
void ArduinoComponent::HandleMouseMove (HWND hWnd, int _x, int _y)
{	
  gnd->HandleMouseMove ( hWnd, _x, _y );
  power->HandleMouseMove (hWnd, _x, _y );
  for (int i=0; i<MAX_DIGITAL_VALUES;i++)
    d[i]->HandleMouseMove (hWnd, _x, _y); 
}

void ArduinoComponent::HandleMouseDown (HWND hWnd, int _x, int _y)
{
  ConnectedComponent::HandleMouseDown (hWnd,_x,_y);  // Does nothing
  if (gnd->isActive) // we are over the ground spot     
    gnd->Select(!gnd->isSelected);
  else if (power->isActive)
    power->Select(!power->isSelected);  
  else
    for (int i=0; i<MAX_DIGITAL_VALUES;i++)
      if (d[i]->isActive)
      {
        d[i]->Select(!d[i]->isSelected);
        break;
      }
}

void ArduinoComponent::Select ( bool select)
{
  gnd->Select(false);
  power->Select(false);
  for (int i=0;i<MAX_DIGITAL_VALUES;i++)
    d[i]->Select(false);
}

