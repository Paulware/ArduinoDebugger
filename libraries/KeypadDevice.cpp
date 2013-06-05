#include "KeypadDevice.h"
#include "HighLevelMenu.h"
#include "SimUtilities.h"

/*
   This device has 8 pins the first 4 are column pins.
   The next 4 are row pins.  One question is if the row pins start at bottom or the top
   and another question is where the column pins start left or right.
*/

char KeypadDevice::keypadChars[16];
char KeypadDevice::getKey;
int  KeypadDevice::pinIndex;
byte KeypadDevice::connectedTo[MAX_KEYPAD_PINS];

void KeypadDevice::ConnectPin (byte pin)
{
  if (pinIndex < MAX_KEYPAD_PINS)
    connectedTo[pinIndex++] = pin;
}

bool KeypadDevice::TroubleshootPins ( )
{
  bool ok = true;
  char pinName[] = "d00";
  Pin * otherPin;
  for (int i=0; i<MAX_KEYPAD_PINS; i++)
  {
    otherPin = HighLevelMenu::Instance()->FindOtherPin ( keypadPin[i]);	
    if (otherPin)
    {
      pinName[1] = connectedTo[i] / 10 + '0';
      pinName[2] = connectedTo[i] % 10 + '0';
      if (strcmp (otherPin->name, pinName ))
      {
        MessageBox ( 0,keypadPin[i]->name, "Not connected correctly", 0);
        ok = false;
      }
    }
    else
      MessageBox ( 0, "Could not find pin connected to", keypadPin[i]->name,0);
  }
  return ok;
}

KeypadDevice::KeypadDevice(int _x, int _y, Component * _diagram): ConnectedComponent(_x,_y, _diagram)
{
  pinIndex = 0; 
  depressedPad = -1;
  SHORT xs[] = {27,75,122,168};
  SHORT ys[] = {15,61,108,155};
  SHORT tempX, tempY;
  x = _x;
  y = _y;
  clearTheText = false; 
  char pinName[] = "pin0";
  
  for (int i=0; i<MAX_KEYPADS; i++)
  {
  	pads[i].X = xs[i%4];
  	pads[i].Y = ys[i/4];
  	// debug only
  	tempX = pads[i].X;
  	tempY = pads[i].Y;
  }
  
  for (int i=0; i<MAX_KEYPAD_PINS; i++)
  {
    keypadPin[i] = new Pin(this);
    keypadPin[i]->xOffset = 64 + (7-i)*13;
	keypadPin[i]->yOffset = 196;
	keypadPin[i]->x = x + keypadPin[i]->xOffset;
	keypadPin[i]->y = y + keypadPin[i]->yOffset;
	pinName[3] = i + '0';
	keypadPin[i]->SetName ( pinName);
  }	 
  SaveType ("Keypad");     
}

void KeypadDevice::Init (HWND _windowHandle, HINSTANCE _g_hInst, char * resource)
{   
   ConnectedComponent::Init ( _windowHandle, _g_hInst, resource);
   for (int i=0; i<MAX_KEYPAD_PINS; i++)	
   	 keypadPin[i]->Init (windowHandle, g_hInst);
}

void KeypadDevice::SaveYourself (FILE * fp)
{
  fprintf ( fp, "Keypad,%d,%d",x,y);
}

void KeypadDevice::AddMenu ()
{
  HMENU  MainMenu;
  HMENU  FileMenu;
     
  //arduinoMain.setHwnd ( hwndOwner);
  MainMenu=CreateMenu();
  FileMenu=CreateMenu();
  InsertMenu(MainMenu,ID_Edit,MF_POPUP,(UINT_PTR)FileMenu,"Help");
  AppendMenu(FileMenu,MF_STRING,LCDDISPLAY_ABOUT,"&About");
  AppendMenu(FileMenu,MF_SEPARATOR,0,"");
  AppendMenu(FileMenu,MF_STRING,LCDDISPLAY_HELP,"&Component Help");
  //  activate menu 
  (void) SetMenu(windowHandle,MainMenu);
}

Pin * KeypadDevice::FindPort ( char * port)
{
  char pinName[] = "pin0";
  Pin * p = 0;
  
  for (int i=0; i<MAX_KEYPAD_PINS; i++)
  {
  	pinName[3] = '0' + i;
  	if (!strcmp (port,pinName))
  	{
  	  p = keypadPin[i]; 
  	  break;
  	}
  }
  return p;    
}


void KeypadDevice::HandleMenu ( int command )
{
  switch (command)
  {
    default:
    break;
  }   
}

KeypadDevice::~KeypadDevice()
{
  for (int i=0; i<MAX_KEYPAD_PINS; i++)
    delete (keypadPin[i]);	
  DeleteConnections();
}

void KeypadDevice::Paint(HDC _hdc, PAINTSTRUCT _ps, HDC _hdcMemory)
{ 
  ConnectedComponent::Paint (_hdc, _ps, _hdcMemory); // Show image  
     
  // Paint the pins
  for (int i=0; i<MAX_KEYPAD_PINS; i++)
    keypadPin[i]->Paint(hdc, ps, hdcMemory);
}
Pin * KeypadDevice::GetPins (int i, Pin * & rowPin, Pin * & columnPin)
{
  int column = i % 4;
  int row = i / 4;
  rowPin = keypadPin[row+4];
  columnPin = keypadPin[column];
}

// Check if the mouse has moved over one of the ports.
void KeypadDevice::HandleMouseMove (HWND hWnd, int _x, int _y)
{
  for (int i=0; i<MAX_KEYPAD_PINS; i++)
    keypadPin[i]->HandleMouseMove (hWnd, _x, _y); 
}

Pin * KeypadDevice::PinActive ()
{
  Pin * p;
  for (int i=0; i<MAX_KEYPAD_PINS; i++)
    if (keypadPin[i]->isActive)
	{
	  p = keypadPin[i];
	  break;
	}	
  return p;
}

void KeypadDevice::Select ( bool select)
{
  for (int i=0; i<MAX_KEYPAD_PINS; i++)
    keypadPin[i]->Select(false);
}

// [_x,_y] are absolute values
void KeypadDevice::MoveTo (int _x, int _y)
{	
  x = _x-xOffset;
  y = _y-yOffset; // Get the x location of the LED after adjusting for mouse click location
  for (int i=0; i<MAX_KEYPAD_PINS; i++)
  {
    keypadPin[i]->MoveTo ( x + keypadPin[i]->xOffset, y + keypadPin[i]->yOffset);
  }
  // Move connections
  ConnectedComponent::Move (); 
}

Pin * KeypadDevice::PortSelected(){
  Pin * p = 0;
  for (int i=0; i<MAX_KEYPAD_PINS; i++)
  if (keypadPin[i]->isSelected)
  {
  	p = keypadPin[i];
  	break;
  }	
	  
  return p;  
}

bool KeypadDevice::IsSet()
{
  bool set = true;
  for (int i=0; i<MAX_KEYPAD_PINS; i++)
  {
  	if (!keypadPin[i]->IsSet())
  	{
  	  set = false;
  	  break;
  	}
  }
  return set;
}

void KeypadDevice::HandleMouseDown (HWND hWnd, int _x, int _y)
{
  ConnectedComponent::HandleMouseDown (hWnd,_x,_y);
  int pad = -1;
  int column;
  int row;
  char msg[20] = "1 key pressed";
  char ch;
  Connection * connection;
  Pin * pin1;
  Pin * pin2;
  char * name1;
  char * name2;
  int value;
  int resistance;
  int numConns;

  for (int i=0; i<MAX_KEYPAD_PINS; i++)
    if (keypadPin[i]->isActive)
      keypadPin[i]->Select (!keypadPin[i]->isSelected);
      
  for (int i=0; i<MAX_KEYPADS; i++)
  {
  	if ((_x >= x+pads[i].X) && (_x <= x+pads[i].X + 33) && // within width
  	    (_y >= y+pads[i].Y) && (_y <= y+pads[i].Y + 30))   // within height
  	{
  	  pad = i;
  	  depressedPad = i;
  	  // getKey = keypadChars[i];
  	  // Find column and row for this pad 
  	  column = i % 4;
  	  row = i / 4;
  	  
  	  // Create a new "virtual" connection
  	  GetPins ( i, pin1, pin2);
  	  name1 = pin1->name;
  	  name2 = pin2->name;
  	  
  	  connection = new Connection (pin1, pin2);
  	  connections[numConnections++] = connection;  	  
  	  
  	  break;
  	}
  }    
}

void KeypadDevice::HandleMouseUp (HWND hWnd)
{ 	
  Pin * pin1;
  Pin * pin2;
  HighLevelMenu * highLevelMenu = (HighLevelMenu *) diagram;
  // Find column and row for this pad 
  int column = depressedPad % 4;
  int row = depressedPad / 4;
  Connection * columnConnection = FindConnection (keypadPin[column]);
  Connection * rowConnection = FindConnection (keypadPin[row+4]);
  // remove the "virtual" connection
  if (depressedPad != -1)
  {
    numConnections--;   
  	pin1 = connections[numConnections]->pin1;
  	pin2 = connections[numConnections]->pin2;
  	connections[numConnections] = 0; // Clear out old connection
  }
  depressedPad = -1;
  getKey = 0;
}

