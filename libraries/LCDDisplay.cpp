#include "LCDDisplay.h"

LCDDisplay::LCDDisplay(int _x, int _y, Component * _diagram): ConnectedComponent(_x,_y,_diagram)
{ 
  offOn = false;
  char pinName[] = "pin00";
  x = _x;
  y = _y;
  for (int i=0; i<MAX_SCREEN_CHARS; i++)
    screen[i] = ' ';
  clearTheText = false; 
  
  for (int i=0; i<MAX_LCD_PINS; i++)
  {
  	pinName [4] = (i % 10) + '0';
  	pinName [3] = (i / 10) + '0';
  	
    pin[i] = new Pin(this);
	if (i<3)  
	  pin[i]->xOffset = 168 + i*11;
	else if (i<9)
	  pin[i]->xOffset = 167 + i*12;  
	else 
	  pin[i]->xOffset = 165 + i*12;  
	pin[i]->yOffset = 258;
	pin[i]->x = x + pin[i]->xOffset;
	pin[i]->y = y + pin[i]->yOffset;
	pin[i]->SetName (pinName);	
  }	 
  SaveType ("LCDDisplay");   
  col = 0;
  row = 0;
}

void LCDDisplay::Select ( bool select)
{
  for (int i=0; i<MAX_LCD_PINS; i++)
    pin[i]->Select (false);
}

void LCDDisplay::print ( int value)
{
  char val[] = "000000000000";
  itoa (value, val, 10);
  print (val);
}

void LCDDisplay::Init (HWND _windowHandle, HINSTANCE _g_hInst, char * resource)
{   
   ConnectedComponent::Init ( _windowHandle, _g_hInst, resource);
   for (int i=0; i<MAX_LCD_PINS; i++)	
   	 pin[i]->Init (windowHandle, g_hInst);      
}

void LCDDisplay::SaveYourself (FILE * fp)
{
  fprintf ( fp, "LCDDisplay,%d,%d",x,y);
}

void LCDDisplay::clear()
{
  
  for (int i=0; i<MAX_SCREEN_CHARS; i++)
    screen[i]=' ';
  row = 0;
  col = 0;
  
}

void LCDDisplay::showScreen(HDC hdcWindow)
{ 
  char line[20];
  int index;
   
  for (int i=0; i<4; i++)
  {
    index = i*20;
    for (int j=0; j<20; j++)
    {
      line[j] = screen[index+j];
    }
    TextOut ( hdcWindow, x+55, y+73 + (30*i), &line[0], 20);
  }  
}

void LCDDisplay::AddMenu ()
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

void LCDDisplay::HandleMenu ( int command )
{
  switch (command)
  {
    case LCDDISPLAY_ABOUT:
      MessageBox(windowHandle, "This item can be purchased from ebay for about $7.00 (Free shipping).  Search ebay for \"20x4 LCD Module\".  It has a 16 pin interface.  A $15.00 pcb is available from Tindie.com which has the pins broken out and can be programmed like an Arduino.  Search www.tindie.com  for\n \"20x4 LCD Module\"", "HD44780", MB_OK | MB_ICONEXCLAMATION);  
    break;
    
    case LCDDISPLAY_HELP:
      MessageBox(windowHandle, "LCDDisplay Help", "HD44780", MB_OK | MB_ICONEXCLAMATION);  
    break;
  }   
}

void LCDDisplay::print (char * line)
{
  int len = strlen (line);
  int index;  
  
  /*
  if (clearTheText)
  {
    for (int i=0; i<80; i++)
    {
      screen[i] = ' ';
      col = 0;
      row = 0;
    }
    clearTheText = false;
  } 
  */ 
  
  index  = col + (row*20);
  
  index %= 80;  
  for (int i=0; i<len; i++)
  {
    screen[index++] = line[i];
    col++;
    if (col == 20)
    {
      col = 0;
      row ++;
      if ( row == 4)
        row = 0;
    }
    index %= 80;
  }
  Refresh();
}

LCDDisplay::~LCDDisplay()
{
  for (int i=0; i<MAX_LCD_PINS; i++)
  	delete (pin[i]);
  DeleteConnections();
}

void LCDDisplay::Paint(HDC _hdc, PAINTSTRUCT _ps, HDC _hdcMemory)
{
  bool ledOn; 
  HFONT hFont;
   
  ConnectedComponent::Paint (_hdc, _ps, _hdcMemory); // Show background image  
    
  hFont = CreateFont (28,0,0,0,FW_DONTCARE, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS,
  CLIP_DEFAULT_PRECIS, 0, VARIABLE_PITCH, TEXT ( "Courier New"));
  (void) SetTextColor ( hdc, RGB (255,255,255));
  (void) SetBkMode( hdc, TRANSPARENT);
  SelectObject (hdc, hFont);
  showScreen(hdc);
      
  // Paint the hotspots
  for (int i=0; i<MAX_LCD_PINS; i++)
    pin[i]->Paint(hdc, ps, hdcMemory);
}

void LCDDisplay::HandleMouseDown (HWND hWnd, int _x, int _y)
{
  Component::HandleMouseDown (hWnd,_x,_y);
  for (int i=0; i<MAX_LCD_PINS; i++)
    if (pin[i]->isActive)
      pin[i]->Select (!pin[i]->isSelected);
}
// Check if the mouse has moved over one of the ports.
void LCDDisplay::HandleMouseMove (HWND hWnd, int _x, int _y)
{
  for (int i=0; i<MAX_LCD_PINS; i++)
    pin[i]->HandleMouseMove (hWnd, _x, _y);
}

Pin * LCDDisplay::PinActive ()
{
  Pin * p;
  for (int i=0; i<MAX_LCD_PINS; i++)
    if (pin[i]->isActive)
	{
	  p = pin[i];
	  break;
	}	
  return p;
}

// [_x,_y] are absolute values
void LCDDisplay::MoveTo (int _x, int _y)
{	
  x = _x-xOffset;
  y = _y-yOffset; // Get the x location of the LED after adjusting for mouse click location
  for (int i=0; i<MAX_LCD_PINS; i++)
  {
    pin[i]->MoveTo ( x + pin[i]->xOffset, y + pin[i]->yOffset);
  }
  // Move connections
  ConnectedComponent::Move (); 
}

Pin * LCDDisplay::PortSelected(){
  Pin * p = 0;
  for (int i=0; i<MAX_LCD_PINS; i++)
  if (pin[i]->isSelected)
  {
  	p = pin[i];
  	break;
  }	
	  
  return p;  
}

Pin * LCDDisplay::FindPort ( char * port)
{
  char pinName[] = "pin00";
  Pin * p = 0;
  
  for (int i=0; i<MAX_LCD_PINS; i++)
  {
  	pinName[4] = (i % 10) + '0';
  	pinName[3] = (i/10) + '0';
  	if (!strcmp (port,pinName))
  	{
  	  p = pin[i]; 
  	  break;
  	}
  }
  return p;    
}

