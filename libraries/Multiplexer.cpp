#include "Multiplexer.h"
#include "HighLevelMenu.h"
#include "SimUtilities.h"

/*  
 Note: 
                      +--v--+
     Channel 4     [1]|     |[16] Vcc        
                      |     |
     Channel 6     [2]|     |[15] Channel 2
                      |     |
  Common I/O       [3]|     |[14] Channel 1                      
                      |     |
     Channel 7     [4]|     |[13] Chanel 0                        
                      |     |
     Channel 5     [5]|     |[12] Channel 3                                                   
                      |     |
      Inhibit      [6]|     |[11]   A
                      |     |
    Not Connected  [7]|     |[10]   B
                      |     |
       VCC         [8]|     |[9]    C
                      +-----+     
*/

Multiplexer::Multiplexer(int _x, int _y, Component * _diagram): ConnectedComponent(_x,_y,_diagram)
{ 
  char names[][MAX_MULTIPLEXER_PINS] = {"VCC1", "CH2", "CH1", "CH0", "CH3",   "A",  "B",    "C",
                                         "CH4", "CH6",  "IO", "CH7", "CH5", "Inh", "NC", "VCC2"};
                                 
       
  int xOff[] = {15,53,91,130,165,205,242,278, 15, 53, 91,130,165,205,242,278};
  int yOff[] = { 0, 0, 0,  0,  0,  0,  0,  0,109,109,109,109,109,109,109,109};
  pinSelected = false;
  lastSelection = 0;
  x = _x;
  y = _y;
  clearTheText = false; 
  
  for (int i=0; i<MAX_MULTIPLEXER_PINS; i++)
  {
    pin[i] = new Pin(this);
  	pin[i]->SetName ( names[i] );
  	pin[i]->xOffset = xOff[i];
  	pin[i]->yOffset = yOff[i];
	pin[i]->x = x + pin[i]->xOffset;
	pin[i]->y = y + pin[i]->yOffset;
  }
  firstUpdate = true;    
  SaveType ("Multiplexer");     
}

void Multiplexer::Select ( bool select)
{
  for (int i=0; i<MAX_MULTIPLEXER_PINS; i++)
    pin[i]->Select (false);
}

void Multiplexer::Init (HWND _windowHandle, HINSTANCE _g_hInst, char * resource)
{   
   ConnectedComponent::Init ( _windowHandle, _g_hInst, resource);
   
   for (int i=0; i<MAX_MULTIPLEXER_PINS; i++)	
   	 pin[i]->Init (windowHandle, g_hInst);  
  
}

void Multiplexer::SaveYourself (FILE * fp)
{
  fprintf ( fp, "Multiplexer,%d,%d",x,y);
}

void Multiplexer::AddMenu ()
{
  HMENU  MainMenu;
  HMENU  FileMenu;
     
  MainMenu=CreateMenu();
  FileMenu=CreateMenu();
  InsertMenu(MainMenu,ID_Edit,MF_POPUP,(UINT_PTR)FileMenu,"Help");
  AppendMenu(FileMenu,MF_STRING,MULTIPLEXER_ABOUT,"&About");
  AppendMenu(FileMenu,MF_SEPARATOR,0,"");
  AppendMenu(FileMenu,MF_STRING,MULTIPLEXER_HELP,"&Component Help");
  //  activate menu 
  (void) SetMenu(windowHandle,MainMenu);
}

void Multiplexer::HandleMenu ( int command )
{
  switch (command)
  {
    case MULTIPLEXER_ABOUT:
      MessageBox(windowHandle, "This item can be purchased for about $0.50 on Mouser", "Multiplexer", MB_OK | MB_ICONEXCLAMATION);  
    break;
    
    case MULTIPLEXER_HELP:
      MessageBox(windowHandle, "Multiplexer Help", "Multiplexer", MB_OK | MB_ICONEXCLAMATION);  
    break;
  }   
}

void Multiplexer::print (char * line)
{
  int len = strlen (line);
  int index;  
  Refresh();
}

Multiplexer::~Multiplexer()
{	
  for (int i=0; i<MAX_MULTIPLEXER_PINS; i++)
  {
  	delete (pin[i]);
  }

  DeleteConnections();
}

void Multiplexer::HandleMouseDown (HWND hWnd, int _x, int _y)
{
  int xOff = _x - x;
  int yOff = _y - y;
  
  Component::HandleMouseDown (hWnd,_x,_y);
  pinSelected = false;
  for (int i=0; i<MAX_MULTIPLEXER_PINS; i++)
    if (pin[i]->isActive)
    {
      pin[i]->Select (!pin[i]->isSelected);
      pinSelected = true;
      break;
    }
}

void Multiplexer::HandleMouseUp (HWND hWnd)
{  
  pinSelected = false;
}

// Check if the mouse has moved over one of the ports.
void Multiplexer::HandleMouseMove (HWND hWnd, int _x, int _y)
{
  for (int i=0; i<MAX_MULTIPLEXER_PINS; i++)
    pin[i]->HandleMouseMove (hWnd, _x, _y);   
}

Pin * Multiplexer::PinActive ()
{
  Pin * p;
  for (int i=0; i<MAX_MULTIPLEXER_PINS; i++)
    if (pin[i]->isActive)
	{
	  p = pin[i];
	  break;
	}	
  return p;
}

// [_x,_y] are absolute values
void Multiplexer::MoveTo (int _x, int _y)
{	
  x = _x-xOffset;
  y = _y-yOffset; // Get the x location of the LED after adjusting for mouse click location
  for (int i=0; i<MAX_MULTIPLEXER_PINS; i++)
  {
    pin[i]->MoveTo ( x + pin[i]->xOffset, y + pin[i]->yOffset);
  }
  // Move connections
  ConnectedComponent::Move (); 
}

Pin * Multiplexer::PortSelected(){
  Pin * p = 0;
  for (int i=0; i<MAX_MULTIPLEXER_PINS; i++)
  if (pin[i]->isSelected)
  {
  	p = pin[i];
  	break;
  }	
	  
  return p;  
}


Pin * Multiplexer::FindPort ( char * port)
{
  char names[][MAX_MULTIPLEXER_PINS] = {"VCC1", "CH2", "CH1", "CH0", "CH3",   "A",  "B",    "C",
                                         "CH4", "CH6",  "IO", "CH7", "CH5", "Inh", "NC", "VCC2"};

  Pin * p = 0;
  
  for (int i=0; i<MAX_MULTIPLEXER_PINS; i++)
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

void Multiplexer::WriteOutValue (int value)
{
  
  char port[] = " ";
  Pin * pin;
  int val = 1;
  /*
  for (int i=0; i<8; i++)
  {
  	port [0] = 'IO' + i;
  	pin = FindPort (port);
  	if (value & val)
      SimUtilities::Instance()->WriteValue (pin,1,0);    
    else
      SimUtilities::Instance()->WriteValue (pin,0,0);
    val *= 2; // shift to next value  
  }
  */
}

/* 
   This procedure should be called after every digitalWrite 
*/
void Multiplexer::Update ()
{  
  int selection = 0;
  Pin * A  = FindPort ("A");
  Pin * B  = FindPort ("B");
  Pin * C  = FindPort ("C");
  Pin * IO = FindPort ("IO");
  char channel[] = "CH?";  
  
  if (firstUpdate)
    AddTempConnector (FindPort ("CH0"), FindPort("IO"));
  firstUpdate = false;  

  if (A->value.value == 1)
    selection += 1; 
  if (B->value.value == 1)
    selection += 2;
  if (C->value.value == 1)
    selection += 4;
    
  if (selection != lastSelection)
  {
  	ClearTemporaryConnections();
  	channel[2] = '0' + selection;
  	AddTempConnector (FindPort (channel), IO);
  }
  lastSelection = selection; 
}

void Multiplexer::Paint(HDC _hdc, PAINTSTRUCT _ps, HDC _hdcMemory)
{
  bool ledOn; 
  HFONT hFont;
  int pinValue;
   
  char resourceName[] = "MULTIPLEXER";
      
  Component::Init (windowHandle, g_hInst, resourceName);
  ConnectedComponent::Paint (_hdc, _ps, _hdcMemory); // Show image

  // Update();  
  
  // Paint the pins
  for (int i=0; i<MAX_MULTIPLEXER_PINS; i++)
    pin[i]->Paint(hdc, ps, hdcMemory);  
}
