#include "ShiftRegister.h"
#include "HighLevelMenu.h"
#include "SimUtilities.h"

/*  
 Note: 
                 +--v--+
        B     [1]|     |[16] Vcc        
                 |     |
        C     [2]|     |[15] A        
                 |     |
        D     [3]|     |[14] Serial value to be shifted in
                 |     |
        E     [4]|     |[13] Output disable (pull to ground) 
                 |     |
        F     [5]|     |[12] Register Clock must toggle (ignore in this implementation)
                 |     |
        G     [6]|     |[11] SRCLK (SER shifted in when transition to high)
                 |     |
        H     [7]|     |[10] Shift Register Clear (pull high)
                 |     |
       GND    [8]|     |[9]  Output to next Shift Register
                 +-----+     
*/

ShiftRegister::ShiftRegister(int _x, int _y, Component * _diagram): ConnectedComponent(_x,_y,_diagram)
{ 
  char names[][MAX_SHIFTREGISTER_PINS] = {"VCC", "A", "SER", "Output Disable", "RCLK", "SRCLK", "SRCLR",  "Qh",
                                            "B", "C",   "D",              "E",    "F",     "G",     "H", "GND"};
                                 
       
  int xOff[] = {15,53,91,130,165,205,242,278, 15, 53, 91,130,165,205,242,278};
  int yOff[] = { 0, 0, 0,  0,  0,  0,  0,  0,109,109,109,109,109,109,109,109};
  pinSelected = false;
  shiftValue = 0;
  lastSRCLK = 0;
  x = _x;
  y = _y;
  clearTheText = false; 
  
  for (int i=0; i<MAX_SHIFTREGISTER_PINS; i++)
  {
    pin[i] = new Pin(this);
  	pin[i]->SetName ( names[i] );
  	pin[i]->xOffset = xOff[i];
  	pin[i]->yOffset = yOff[i];
	pin[i]->x = x + pin[i]->xOffset;
	pin[i]->y = y + pin[i]->yOffset;
  }
       
  SaveType ("ShiftRegister");   
}

void ShiftRegister::Select ( bool select)
{
  for (int i=0; i<MAX_SHIFTREGISTER_PINS; i++)
    pin[i]->Select (false);
}

void ShiftRegister::Init (HWND _windowHandle, HINSTANCE _g_hInst, char * resource)
{   
   ConnectedComponent::Init ( _windowHandle, _g_hInst, resource);
   
   for (int i=0; i<MAX_SHIFTREGISTER_PINS; i++)	
   	 pin[i]->Init (windowHandle, g_hInst);  
  
}

void ShiftRegister::SaveYourself (FILE * fp)
{
  fprintf ( fp, "ShiftRegister,%d,%d",x,y);
}

void ShiftRegister::AddMenu ()
{
  HMENU  MainMenu;
  HMENU  FileMenu;
     
  MainMenu=CreateMenu();
  FileMenu=CreateMenu();
  InsertMenu(MainMenu,ID_Edit,MF_POPUP,(UINT_PTR)FileMenu,"Help");
  AppendMenu(FileMenu,MF_STRING,SHIFTREGISTER_ABOUT,"&About");
  AppendMenu(FileMenu,MF_SEPARATOR,0,"");
  AppendMenu(FileMenu,MF_STRING,SHIFTREGISTER_HELP,"&Component Help");
  //  activate menu 
  (void) SetMenu(windowHandle,MainMenu);
}

void ShiftRegister::HandleMenu ( int command )
{
  switch (command)
  {
    case SHIFTREGISTER_ABOUT:
      MessageBox(windowHandle, "This item can be purchased for about $0.50 on Mouser", "Shift Register", MB_OK | MB_ICONEXCLAMATION);  
    break;
    
    case SHIFTREGISTER_HELP:
      MessageBox(windowHandle, "Shift Register Help", "ShiftRegister", MB_OK | MB_ICONEXCLAMATION);  
    break;
  }   
}

void ShiftRegister::print (char * line)
{
  int len = strlen (line);
  int index;  
  Refresh();
}

ShiftRegister::~ShiftRegister()
{	
  for (int i=0; i<MAX_SHIFTREGISTER_PINS; i++)
  {
  	delete (pin[i]);
  }

  DeleteConnections();
}

void ShiftRegister::HandleMouseDown (HWND hWnd, int _x, int _y)
{
  int xOff = _x - x;
  int yOff = _y - y;
  
  Component::HandleMouseDown (hWnd,_x,_y);
  pinSelected = false;
  for (int i=0; i<MAX_SHIFTREGISTER_PINS; i++)
    if (pin[i]->isActive)
    {
      pin[i]->Select (!pin[i]->isSelected);
      pinSelected = true;
      break;
    }
}

void ShiftRegister::HandleMouseUp (HWND hWnd)
{  
  char * name;
  HighLevelMenu * highLevelMenu = (HighLevelMenu *)diagram;
  SimUtilities * utils = SimUtilities::Instance();
  int value;
  int resistance;
  if (true)
  { 
    ClearTemporaryConnections();
    pinSelected = false;    
  } 
}

// Check if the mouse has moved over one of the ports.
void ShiftRegister::HandleMouseMove (HWND hWnd, int _x, int _y)
{
  for (int i=0; i<MAX_SHIFTREGISTER_PINS; i++)
    pin[i]->HandleMouseMove (hWnd, _x, _y);   
}

Pin * ShiftRegister::PinActive ()
{
  Pin * p;
  for (int i=0; i<MAX_SHIFTREGISTER_PINS; i++)
    if (pin[i]->isActive)
	{
	  p = pin[i];
	  break;
	}	
  return p;
}

// [_x,_y] are absolute values
void ShiftRegister::MoveTo (int _x, int _y)
{	
  x = _x-xOffset;
  y = _y-yOffset; // Get the x location of the LED after adjusting for mouse click location
  for (int i=0; i<MAX_SHIFTREGISTER_PINS; i++)
  {
    pin[i]->MoveTo ( x + pin[i]->xOffset, y + pin[i]->yOffset);
  }
  // Move connections
  ConnectedComponent::Move (); 
}

Pin * ShiftRegister::PortSelected(){
  Pin * p = 0;
  for (int i=0; i<MAX_SHIFTREGISTER_PINS; i++)
  if (pin[i]->isSelected)
  {
  	p = pin[i];
  	break;
  }	
	  
  return p;  
}


Pin * ShiftRegister::FindPort ( char * port)
{
  char names[][MAX_SHIFTREGISTER_PINS] = {"VCC", "A", "SER", "Output Disable", "RCLK", "SRCLK", "SRCLR",  "Qh",
                                            "B", "C",   "D",              "E",    "F",     "G",     "H", "GND"};

  Pin * p = 0;
  
  for (int i=0; i<MAX_SHIFTREGISTER_PINS; i++)
  {
  	if (!strcmp (port,names[i]))
  	{
  	  p = pin[i]; 
  	  break;
  	}
  }
  if (!p)
     MessageBox(0, "COULD NOT FIND A PORT", "BAD PORT NAME", MB_OK | MB_ICONEXCLAMATION);  

  return p;    
}

void ShiftRegister::WriteOutValue (int value)
{
  char port[] = " ";
  Pin * pin;
  int val = 1;
  
  for (int i=0; i<8; i++)
  {
  	port [0] = 'A' + i;
  	pin = FindPort (port);
  	if (value & val)
      SimUtilities::Instance()->WriteValue (pin,1,0);    
    else
      SimUtilities::Instance()->WriteValue (pin,0,0);
    val *= 2; // shift to next value  
  }
}

/* 
   This procedure should be called after every digitalWrite 
*/
void ShiftRegister::Update ()
{
  Pin * clkPin = FindPort ( "SRCLK");
  int SRCLK = clkPin->value.value; 
  Pin * serPin = FindPort ("SER");
  int SER = serPin->value.value;
  Pin * Qh = FindPort ("Qh");
  int QhValue;
   
  if ((SRCLK==1) && !lastSRCLK && (SER !=-1)) // Transition to high so shift
  {
  	shiftValue *= 2;              // shift
  	QhValue = shiftValue & 0x100; // Get the shifted out value
  	shiftValue &= 0xFF;           // zero out Qh
  	shiftValue += SER;            // Shift in the new value
  	WriteOutValue (shiftValue);
  	if (QhValue)
      SimUtilities::Instance()->WriteValue (Qh,1,0);  
	else
	  SimUtilities::Instance()->WriteValue (Qh,0,0);  	
  }   
  lastSRCLK = SRCLK;
}

void ShiftRegister::Paint(HDC _hdc, PAINTSTRUCT _ps, HDC _hdcMemory)
{
  bool ledOn; 
  HFONT hFont;
  int pinValue;
   
  char resourceName[] = "SHIFTREGISTER";
      
  Component::Init (windowHandle, g_hInst, resourceName);
  ConnectedComponent::Paint (_hdc, _ps, _hdcMemory); // Show image

  Update();  
  
  // Paint the pins
  for (int i=0; i<MAX_SHIFTREGISTER_PINS; i++)
    pin[i]->Paint(hdc, ps, hdcMemory);  
}
