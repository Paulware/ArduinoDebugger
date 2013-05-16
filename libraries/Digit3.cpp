#include "Digit3.h"

Digit3::Digit3(int _x, int _y, Component * _diagram): ConnectedComponent(_x,_y,_diagram)
{ 
  char names[][12] = {"pin01", "pin02", "pin03", "pin04", "pin05", "pin06",
                      "pin07", "pin08", "pin09", "pin10", "pin11", "pin12"};
  offOn = false;
  x = _x;
  y = _y;
  strcpy ( screen, "   ");
  clearTheText = false; 
  
  for (int i=0; i<MAX_DIGIT3_PINS; i++)
  {
    pin[i] = new Pin(this);
  	pin[i]->SetName ( names[i] );
	if (i<6)  
	{
	  pin[i]->xOffset = 60 + i*30;
 	  pin[i]->yOffset = 120;
    }
	else
	{
	  pin[i]->xOffset = 60 + 150 - ((i-6)*30);  
 	  pin[i]->yOffset = 2;
    }
	pin[i]->x = x + pin[i]->xOffset;
	pin[i]->y = y + pin[i]->yOffset;
	
  }
  
  // Digit1 
  segmentValues[0][0] = (SegmentInfo) { 5,  74}; // Segment E  
  segmentValues[0][1] = (SegmentInfo) {17, 105}; // Segment D
  segmentValues[0][2] = (SegmentInfo) {53,  75}; // Segment C
  segmentValues[0][3] = (SegmentInfo) {26,  60}; // Segment G
  segmentValues[0][4] = (SegmentInfo) {61,  27}; // Segment B
  segmentValues[0][5] = (SegmentInfo) {13,  27}; // Segment F
  segmentValues[0][6] = (SegmentInfo) {31,  15}; // Segment A
  
  // Digit2
  segmentValues[1][0] = (SegmentInfo) { 93,  74}; // Segment E  
  segmentValues[1][1] = (SegmentInfo) {105, 105}; // Segment D
  segmentValues[1][2] = (SegmentInfo) {141,  75}; // Segment C
  segmentValues[1][3] = (SegmentInfo) {114,  60}; // Segment G
  segmentValues[1][4] = (SegmentInfo) {149,  27}; // Segment B
  segmentValues[1][5] = (SegmentInfo) {101,  27}; // Segment F
  segmentValues[1][6] = (SegmentInfo) {119,  15}; // Segment A
  
  // Digit3
  segmentValues[2][0] = (SegmentInfo) {182,  75}; // Segment E  
  segmentValues[2][1] = (SegmentInfo) {194, 106}; // Segment D
  segmentValues[2][2] = (SegmentInfo) {230,  76}; // Segment C
  segmentValues[2][3] = (SegmentInfo) {203,  61}; // Segment G
  segmentValues[2][4] = (SegmentInfo) {238,  28}; // Segment B
  segmentValues[2][5] = (SegmentInfo) {190,  28}; // Segment F
  segmentValues[2][6] = (SegmentInfo) {208,  17}; // Segment A
  
  for (int i=0; i<NUM_DIGITS; i++)
    for (int j=0; j<NUM_SEGMENTS; j++)
      displayedSegments[i][j] = new Component();		
     
  SaveType ("Digit3");   
  col = 0;
  row = 0;
}

void Digit3::Select ( bool select)
{
  for (int i=0; i<MAX_DIGIT3_PINS; i++)
    pin[i]->Select (false);
}

void Digit3::print ( int value)
{
  char val[] = "000000000000";
  itoa (value, val, 10);
  print (val);
}

void Digit3::Init (HWND _windowHandle, HINSTANCE _g_hInst, char * resource)
{   
   ConnectedComponent::Init ( _windowHandle, _g_hInst, resource);
   
   for (int i=0; i<MAX_DIGIT3_PINS; i++)	
   	 pin[i]->Init (windowHandle, g_hInst);  

  /* 
  
    -A-
    | |
    F B
    | |
    -G-
    | |
	E C
	| |
	-D-
  
  segmentValues[0][0] = (SegmentInfo) { 5,  74}; // Segment E  (Vertical)
  segmentValues[0][1] = (SegmentInfo) {17, 105}; // Segment D  (Horizontal)
  segmentValues[0][2] = (SegmentInfo) {53,  75}; // Segment C  (Vertical)
  segmentValues[0][3] = (SegmentInfo) {26,  60}; // Segment G  (Horizontal)
  segmentValues[0][4] = (SegmentInfo) {61,  27}; // Segment B  (Vertical)
  segmentValues[0][5] = (SegmentInfo) {13,  27}; // Segment F  (Vertical)
  segmentValues[0][6] = (SegmentInfo) {31,  15}; // Segment A  (Horizontal)
  
*/

  // Digit1		
  displayedSegments[0][0]->Init (windowHandle, g_hInst, "VERTICAL3DIGIT");
  displayedSegments[0][1]->Init (windowHandle, g_hInst, "HORIZONTAL3DIGIT");
  displayedSegments[0][2]->Init (windowHandle, g_hInst, "VERTICAL3DIGIT");
  displayedSegments[0][3]->Init (windowHandle, g_hInst, "HORIZONTAL3DIGIT");
  displayedSegments[0][4]->Init (windowHandle, g_hInst, "VERTICAL3DIGIT");
  displayedSegments[0][5]->Init (windowHandle, g_hInst, "VERTICAL3DIGIT");
  displayedSegments[0][6]->Init (windowHandle, g_hInst, "HORIZONTAL3DIGIT");		    
  
  // Digit2
  displayedSegments[1][0]->Init (windowHandle, g_hInst, "VERTICAL3DIGIT");
  displayedSegments[1][1]->Init (windowHandle, g_hInst, "HORIZONTAL3DIGIT");
  displayedSegments[1][2]->Init (windowHandle, g_hInst, "VERTICAL3DIGIT");
  displayedSegments[1][3]->Init (windowHandle, g_hInst, "HORIZONTAL3DIGIT");
  displayedSegments[1][4]->Init (windowHandle, g_hInst, "VERTICAL3DIGIT");
  displayedSegments[1][5]->Init (windowHandle, g_hInst, "VERTICAL3DIGIT");
  displayedSegments[1][6]->Init (windowHandle, g_hInst, "HORIZONTAL3DIGIT");		    
  
  // Digit2
  displayedSegments[2][0]->Init (windowHandle, g_hInst, "VERTICAL3DIGIT");
  displayedSegments[2][1]->Init (windowHandle, g_hInst, "HORIZONTAL3DIGIT");
  displayedSegments[2][2]->Init (windowHandle, g_hInst, "VERTICAL3DIGIT");
  displayedSegments[2][3]->Init (windowHandle, g_hInst, "HORIZONTAL3DIGIT");
  displayedSegments[2][4]->Init (windowHandle, g_hInst, "VERTICAL3DIGIT");
  displayedSegments[2][5]->Init (windowHandle, g_hInst, "VERTICAL3DIGIT");
  displayedSegments[2][6]->Init (windowHandle, g_hInst, "HORIZONTAL3DIGIT");		    
}

void Digit3::SaveYourself (FILE * fp)
{
  fprintf ( fp, "Digit3,%d,%d",x,y);
}

void Digit3::clear()
{ 
  for (int i=0; i<NUM_DIGITS; i++)
    screen[i]=' ';
  row = 0;
  col = 0;  
}

void Digit3::showScreen(HDC hdcWindow)
{
  // TODO output to the leds rather than a textout 
  // TextOut ( hdcWindow, x+55, y+150, &screen[0], MAX_CHARS);
}

void Digit3::AddMenu ()
{
  HMENU  MainMenu;
  HMENU  FileMenu;
     
  //arduinoMain.setHwnd ( hwndOwner);
  MainMenu=CreateMenu();
  FileMenu=CreateMenu();
  InsertMenu(MainMenu,ID_Edit,MF_POPUP,(UINT_PTR)FileMenu,"Help");
  AppendMenu(FileMenu,MF_STRING,DIGIT3_ABOUT,"&About");
  AppendMenu(FileMenu,MF_SEPARATOR,0,"");
  AppendMenu(FileMenu,MF_STRING,DIGIT3_HELP,"&Component Help");
  //  activate menu 
  (void) SetMenu(windowHandle,MainMenu);
}

void Digit3::HandleMenu ( int command )
{
  switch (command)
  {
    case DIGIT3_ABOUT:
      MessageBox(windowHandle, "This item can be purchased from ebay for about $3.00", "Digit3", MB_OK | MB_ICONEXCLAMATION);  
    break;
    
    case DIGIT3_HELP:
      MessageBox(windowHandle, "3 Digit Display Help", "Digit3", MB_OK | MB_ICONEXCLAMATION);  
    break;
  }   
}

void Digit3::print (char * line)
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
  
  for (int i=0; i<NUM_DIGITS; i++)
  {
    screen[i] = line[i];
  }
  Refresh();
}

Digit3::~Digit3()
{	
  for (int i=0; i<MAX_DIGIT3_PINS; i++)
  {
  	delete (pin[i]);
  }

  for (int i=0; i<NUM_DIGITS; i++)
    for (int j=0; j<NUM_SEGMENTS; j++)
      delete (displayedSegments[i][j]);  	
  DeleteConnections();
}

void Digit3::HandleMouseDown (HWND hWnd, int _x, int _y)
{
  Component::HandleMouseDown (hWnd,_x,_y);
  for (int i=0; i<MAX_DIGIT3_PINS; i++)
    if (pin[i]->isActive)
      pin[i]->Select (!pin[i]->isSelected);
}
// Check if the mouse has moved over one of the ports.
void Digit3::HandleMouseMove (HWND hWnd, int _x, int _y)
{
  for (int i=0; i<MAX_DIGIT3_PINS; i++)
    pin[i]->HandleMouseMove (hWnd, _x, _y);
}

Pin * Digit3::PinActive ()
{
  Pin * p;
  for (int i=0; i<MAX_DIGIT3_PINS; i++)
    if (pin[i]->isActive)
	{
	  p = pin[i];
	  break;
	}	
  return p;
}

// [_x,_y] are absolute values
void Digit3::MoveTo (int _x, int _y)
{	
  x = _x-xOffset;
  y = _y-yOffset; // Get the x location of the LED after adjusting for mouse click location
  for (int i=0; i<MAX_DIGIT3_PINS; i++)
  {
    pin[i]->MoveTo ( x + pin[i]->xOffset, y + pin[i]->yOffset);
  }
  // Move connections
  ConnectedComponent::Move (); 
}

Pin * Digit3::PortSelected(){
  Pin * p = 0;
  for (int i=0; i<MAX_DIGIT3_PINS; i++)
  if (pin[i]->isSelected)
  {
  	p = pin[i];
  	break;
  }	
	  
  return p;  
}

Pin * Digit3::FindPort ( char * port)
{
  char names[][12] = {"pin01", "pin02", "pin03", "pin04", "pin05", "pin06",
                      "pin07", "pin08", "pin09", "pin10", "pin11", "pin12"};

  Pin * p = 0;
  
  for (int i=0; i<MAX_DIGIT3_PINS; i++)
  {
  	if (!strcmp (port,names[i]))
  	{
  	  p = pin[i]; 
  	  break;
  	}
  }
  return p;    
}

void Digit3::Paint(HDC _hdc, PAINTSTRUCT _ps, HDC _hdcMemory)
{
  bool ledOn; 
  HFONT hFont;
  int pinValue;
   
  ConnectedComponent::Paint (_hdc, _ps, _hdcMemory); // Show background image  
    
  hFont = CreateFont (28,0,0,0,FW_DONTCARE, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS,
  CLIP_DEFAULT_PRECIS, 0, VARIABLE_PITCH, TEXT ( "Courier New"));
  (void) SetTextColor ( hdc, RGB (255,255,255));
  (void) SetBkMode( hdc, TRANSPARENT);
  SelectObject (hdc, hFont);
  showScreen(hdc);
  static int offset = 0;
  /*
    Pin12  Pin11 Pin10 Pin9   Pin8   Pin7
    Digit1 SegA  SegF  Digit2 Digit3 SegB
  
    Pin1   Pin2  Pin3  Pin4   Pin5   Pin6            
    SegE   SegD  DP    SegC   SegG    NC
  */
  bool segmentPins[] = {true, true, false, true, true, false, true, false, false, true, true, false };
  int digit = 0;
  int segment = 0;
      
  // Paint the pins
  for (int i=0; i<MAX_DIGIT3_PINS; i++)
    pin[i]->Paint(hdc, ps, hdcMemory);
        
  // Determine which digit is active
  if (pin[11]->GetValue() == 1) // Digit1 
    digit = 0;
  else if (pin[8]->GetValue() == 1) // Digit 2
    digit = 1;
  else if (pin[7]->GetValue()==1) // Digit 3
    digit = 2;   
	  
  // These pins are mapped to the device  
  for (int i=0; i<MAX_DIGIT3_PINS; i++)
  {  
    offOn = false;
    if (segmentPins[i])
    {
      pinValue = pin[i]->GetValue();
      if (pinValue == 1)
      {
        displayedSegments[digit][segment]->x = segmentValues[digit][segment].x + x;
        displayedSegments[digit][segment]->y = segmentValues[digit][segment].y + y;
        displayedSegments[digit][segment]->wasSet = true;
      }
      else
      {
        displayedSegments[digit][segment]->wasSet = false;
      }
      segment++;
    }
  }
    
  for (int i=0; i<NUM_DIGITS; i++)
    for (int j=0; j<NUM_SEGMENTS; j++)
      if (displayedSegments[i][j]->wasSet)
        displayedSegments[i][j]->Paint (hdc, ps, hdcMemory);
      
}


