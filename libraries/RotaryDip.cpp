#include "RotaryDip.h"
#include "HighLevelMenu.h"
#include "SimUtilities.h"

RotaryDip::RotaryDip(int _x, int _y, Component * _diagram): ConnectedComponent(_x,_y,_diagram)
{ 
  char names[][MAX_ROTARYDIP_PINS] = {"pin01", "pin02", "pin03", "pin04", "pin05", "pin06"};
  int xOff[] = {2,2,2,120,120,120};
  int yOff[] = {35,65,95,95,65,35};
  pinSelected = false;
  rotateDial = false;
  whichDip = 0;
  x = _x;
  y = _y;
  clearTheText = false; 
  
  for (int i=0; i<MAX_ROTARYDIP_PINS; i++)
  {
    pin[i] = new Pin(this);
  	pin[i]->SetName ( names[i] );
  	pin[i]->xOffset = xOff[i];
  	pin[i]->yOffset = yOff[i];
	pin[i]->x = x + pin[i]->xOffset;
	pin[i]->y = y + pin[i]->yOffset;
  }
       
  SaveType ("RotaryDip");   
  lastDip = -1;
}

void RotaryDip::Select ( bool select)
{
  for (int i=0; i<MAX_ROTARYDIP_PINS; i++)
    pin[i]->Select (false);
}

void RotaryDip::print ( int value)
{
  char val[] = "000000000000";
  itoa (value, val, 10);
  print (val);
}

void RotaryDip::Init (HWND _windowHandle, HINSTANCE _g_hInst, char * resource)
{   
   ConnectedComponent::Init ( _windowHandle, _g_hInst, resource);
   
   for (int i=0; i<MAX_ROTARYDIP_PINS; i++)	
   	 pin[i]->Init (windowHandle, g_hInst);  
  
}

void RotaryDip::SaveYourself (FILE * fp)
{
  fprintf ( fp, "RotaryDip,%d,%d",x,y);
}

void RotaryDip::showScreen(HDC hdcWindow)
{
  // TODO output to the leds rather than a textout 
  // TextOut ( hdcWindow, x+55, y+150, &screen[0], MAX_CHARS);
}

void RotaryDip::AddMenu ()
{
  HMENU  MainMenu;
  HMENU  FileMenu;
     
  //arduinoMain.setHwnd ( hwndOwner);
  MainMenu=CreateMenu();
  FileMenu=CreateMenu();
  InsertMenu(MainMenu,ID_Edit,MF_POPUP,(UINT_PTR)FileMenu,"Help");
  AppendMenu(FileMenu,MF_STRING,ROTARYDIP_ABOUT,"&About");
  AppendMenu(FileMenu,MF_SEPARATOR,0,"");
  AppendMenu(FileMenu,MF_STRING,ROTARYDIP_HELP,"&Component Help");
  //  activate menu 
  (void) SetMenu(windowHandle,MainMenu);
}

void RotaryDip::HandleMenu ( int command )
{
  switch (command)
  {
    case ROTARYDIP_ABOUT:
      MessageBox(windowHandle, "This item can be purchased from ebay for about $1.00", "RotaryDip", MB_OK | MB_ICONEXCLAMATION);  
    break;
    
    case ROTARYDIP_HELP:
      MessageBox(windowHandle, "Rotary Dip Help", "RotaryDip", MB_OK | MB_ICONEXCLAMATION);  
    break;
  }   
}

void RotaryDip::print (char * line)
{
  int len = strlen (line);
  int index;  
  Refresh();
}

RotaryDip::~RotaryDip()
{	
  for (int i=0; i<MAX_ROTARYDIP_PINS; i++)
  {
  	delete (pin[i]);
  }

  DeleteConnections();
}

void RotaryDip::HandleMouseDown (HWND hWnd, int _x, int _y)
{
  int xOff = _x - x;
  int yOff = _y - y;
  
  if ((xOff > 45) && (xOff < 85) && (yOff > 45) && (yOff < 85))
    rotateDial = true;  
  Component::HandleMouseDown (hWnd,_x,_y);
  pinSelected = false;
  for (int i=0; i<MAX_ROTARYDIP_PINS; i++)
    if (pin[i]->isActive)
    {
      pin[i]->Select (!pin[i]->isSelected);
      pinSelected = true;
      break;
    }
}

void RotaryDip::HandleMouseUp (HWND hWnd)
{  
  char * name;
  HighLevelMenu * highLevelMenu = (HighLevelMenu *)diagram;
  SimUtilities * utils = SimUtilities::Instance();
  int value;
  int resistance;
  if (rotateDial) // Go to the next RotaryDip 
  { 
    ClearTemporaryConnections();
    whichDip++;
    whichDip %= 10;
    pinSelected = false;
    
    switch ( whichDip)
    {
      case 0: // No connections
      break;
      case 1:
      	AddTempConnector ( pin[0], pin[1]);
      	utils->MakeConnectionList (pin[0]);    
      	if (utils->HasConstantValue (value, resistance))
      	  utils->WritePinValue (pin[0], value, resistance);
      	else
		  value = -1;  
      break;     
      case 2:
      	AddTempConnector ( pin[3], pin[4]);
      	utils->MakeConnectionList (pin[3]);    
      	if (utils->HasConstantValue (value, resistance))
      	  utils->WritePinValue (pin[3], value, resistance);
      	else
		  value = -1;  
      break;      
      case 3:
      	AddTempConnector ( pin[0], pin[1]);
      	utils->MakeConnectionList (pin[0]);    
      	if (utils->HasConstantValue (value, resistance))
      	  utils->WritePinValue (pin[0], value, resistance);
      	else
		  value = -1;  
		  
      	AddTempConnector ( pin[3], pin[4]);
      	utils->MakeConnectionList (pin[3]);    
      	if (utils->HasConstantValue (value, resistance))
      	  utils->WritePinValue (pin[3], value, resistance);
      	else
		  value = -1;  
      break;
      case 4:
      	AddTempConnector ( pin[2], pin[1]);
      	utils->MakeConnectionList (pin[1]);    
      	if (utils->HasConstantValue (value, resistance))
      	  utils->WritePinValue (pin[1], value, resistance);
      	else
		  value = -1;  
      break;
      case 5:
      	AddTempConnector ( pin[2], pin[1]);
      	utils->MakeConnectionList (pin[1]);          	
      	if (utils->HasConstantValue (value, resistance))
      	  utils->WritePinValue (pin[1], value, resistance);
      	else
		  value = -1;  
      	AddTempConnector ( pin[0], pin[1]);
      	utils->MakeConnectionList (pin[0]);    
      	if (utils->HasConstantValue (value, resistance))
      	  utils->WritePinValue (pin[0], value, resistance);
      	else
		  value = -1;  
      break;
      case 6:
      	AddTempConnector ( pin[2], pin[1]);
      	utils->MakeConnectionList (pin[1]);    
      	if (utils->HasConstantValue (value, resistance))
      	  utils->WritePinValue (pin[1], value, resistance);
      	else
		  value = -1;  
      	AddTempConnector ( pin[3], pin[4]);
      	utils->MakeConnectionList (pin[3]);    
      	if (utils->HasConstantValue (value, resistance))
      	  utils->WritePinValue (pin[3], value, resistance);
      	else
		  value = -1;  
      break;
      case 7:
      	AddTempConnector ( pin[2], pin[1]);
      	utils->MakeConnectionList (pin[1]);    
      	if (utils->HasConstantValue (value, resistance))
      	  utils->WritePinValue (pin[1], value, resistance);
      	else
		  value = -1;  
      	AddTempConnector ( pin[3], pin[4]);
      	utils->MakeConnectionList (pin[3]);    
      	if (utils->HasConstantValue (value, resistance))
      	  utils->WritePinValue (pin[3], value, resistance);
      	else
		  value = -1;  
      	AddTempConnector ( pin[0], pin[1]);
      	utils->MakeConnectionList (pin[0]);    
      	if (utils->HasConstantValue (value, resistance))
      	  utils->WritePinValue (pin[0], value, resistance);
      	else
		  value = -1;  
      break;
      case 8:
      	AddTempConnector ( pin[4], pin[5]);
      	utils->MakeConnectionList (pin[4]);    
      	if (utils->HasConstantValue (value, resistance))
      	  utils->WritePinValue (pin[4], value, resistance);
      	else
		  value = -1;  
      break;
      case 9:
      	AddTempConnector ( pin[5], pin[4]);
      	utils->MakeConnectionList (pin[4]);    
      	if (utils->HasConstantValue (value, resistance))
      	  utils->WritePinValue (pin[4], value, resistance);
      	else
		  value = -1;  
      	AddTempConnector ( pin[0], pin[1]);
      	utils->MakeConnectionList (pin[0]);    
      	if (utils->HasConstantValue (value, resistance))
      	  utils->WritePinValue (pin[0], value, resistance);
      	else
		  value = -1;  
      break;
    }
    // HighLevelMenu::Instance()->BestValue(pin1,pin2,value,resistance);	
    // utils->WriteValue(pin1, value, resistance); // Check for constant value?    
  } 
  rotateDial = false;
}

// Check if the mouse has moved over one of the ports.
void RotaryDip::HandleMouseMove (HWND hWnd, int _x, int _y)
{
  for (int i=0; i<MAX_ROTARYDIP_PINS; i++)
    pin[i]->HandleMouseMove (hWnd, _x, _y);   
}

Pin * RotaryDip::PinActive ()
{
  Pin * p;
  for (int i=0; i<MAX_ROTARYDIP_PINS; i++)
    if (pin[i]->isActive)
	{
	  p = pin[i];
	  break;
	}	
  return p;
}

// [_x,_y] are absolute values
void RotaryDip::MoveTo (int _x, int _y)
{	
  x = _x-xOffset;
  y = _y-yOffset; // Get the x location of the LED after adjusting for mouse click location
  for (int i=0; i<MAX_ROTARYDIP_PINS; i++)
  {
    pin[i]->MoveTo ( x + pin[i]->xOffset, y + pin[i]->yOffset);
  }
  // Move connections
  ConnectedComponent::Move (); 
}

Pin * RotaryDip::PortSelected(){
  Pin * p = 0;
  for (int i=0; i<MAX_ROTARYDIP_PINS; i++)
  if (pin[i]->isSelected)
  {
  	p = pin[i];
  	break;
  }	
	  
  return p;  
}

Pin * RotaryDip::FindPort ( char * port)
{
  char names[][MAX_ROTARYDIP_PINS] = {"pin01", "pin02", "pin03", "pin04", "pin05", "pin06"};

  Pin * p = 0;
  
  for (int i=0; i<MAX_ROTARYDIP_PINS; i++)
  {
  	if (!strcmp (port,names[i]))
  	{
  	  p = pin[i]; 
  	  break;
  	}
  }
  return p;    
}

void RotaryDip::Paint(HDC _hdc, PAINTSTRUCT _ps, HDC _hdcMemory)
{
  bool ledOn; 
  HFONT hFont;
  int pinValue;
   
  /*  
  value [pin number]
  Note: 
     [2] is common for 1/3
     [5] is common for 4/6
     [2] and [5] are not connected internally
    
          +--v--+
     1 [1]|     |[6] 8
          |  ^  |
     C [2]|  O  |[5] C
          |     |
     4 [3]|     |[4] 2
          +-----+
     
  */
  
  char resourceName[] = "ROTARYDIP?";
  resourceName[9] = '0' + whichDip;
      
  if (lastDip != whichDip)     
    Component::Init (windowHandle, g_hInst, resourceName);
  lastDip = whichDip;  
  ConnectedComponent::Paint (_hdc, _ps, _hdcMemory); // Show image                
  
  // Paint the pins
  for (int i=0; i<MAX_ROTARYDIP_PINS; i++)
    pin[i]->Paint(hdc, ps, hdcMemory);  
}


