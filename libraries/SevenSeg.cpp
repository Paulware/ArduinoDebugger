#include "SevenSeg.h"
#include "HighLevelMenu.h"
SevenSeg::SevenSeg(int _x, int _y, Component * _diagram):ConnectedComponent(_x,_y,_diagram)
{ 
  int xs[] = { 20, 45, 70,  5, 20, 45, 70};                       
  int ys[] = {127,127,127, 63,  5,  5,  5};
  char segmentName[] = "segment[i]";
  Connection * connection;
  x = _x;
  y = _y;
  gnd = new Pin(this);
  gnd->xOffset = 85;
  gnd->yOffset = 63;
  gnd->x = x + gnd->xOffset;
  gnd->y = y + gnd->yOffset;
  gnd->SetName ("gnd");
  
  for (int i=0; i<7;i++)
  {
    segment[i] = new Pin(this);
	segment[i]->xOffset = xs[i];
	segment[i]->yOffset = ys[i];
	segment[i]->x = x + segment[i]->xOffset;
	segment[i]->y = y + segment[i]->yOffset;
	segmentName[8] = '0' + i;
	segment[i]->SetName (segmentName);
	
    displayedSegments[i] = new Component();	
  }	
  segmentValues[5] = (SegmentInfo) { 21,  27,  true};
  segmentValues[4] = (SegmentInfo) { 21,  75,  true};
  segmentValues[1] = (SegmentInfo) { 71,  27,  true};
  segmentValues[2] = (SegmentInfo) { 71,  75,  true};
  segmentValues[0] = (SegmentInfo) { 26,  20, false};
  segmentValues[6] = (SegmentInfo) { 26,  70, false};
  segmentValues[3] = (SegmentInfo) { 26, 116, false};
  
  SaveType ("SevenSegment");     
}

Pin * SevenSeg::FindPort ( char * port)
{
  char segmentName[] = "segment[i]";
  Pin * pin;
  if (!strcmp (port,"gnd"))
    pin = gnd;
    
  for (int i=0; i<7;i++)
  {
	segmentName[8] = '0' + i;
  	if (!strcmp(port,segmentName))
  	{
  	  pin = segment[i];
	  break;
	}
  }	
    
  return pin;  
}

void SevenSeg::Select ( bool select)
{
  gnd->Select(false);
  for (int i=0; i<7; i++)
    segment[i]->Select(false);
}


void SevenSeg::SaveYourself (FILE * fp)
{
  fprintf ( fp, "Seven Segment,%d,%d",x,y);
}

// [_x,_y] are absolute values
void SevenSeg::MoveTo (int _x, int _y)
{
  ConnectedComponent::MoveTo (_x,_y);	
	
  x = _x-xOffset;
  y = _y-yOffset; // Get the x location of the LED after adjusting for mouse click location
  gnd->MoveTo (x + gnd->xOffset,
               y + gnd->yOffset);    
  for (int i=0; i<7; i++)
  	segment[i]->MoveTo (x + segment[i]->xOffset,
                        y + segment[i]->yOffset);
  // Move connections
  ConnectedComponent::Move ();                         
}

void SevenSeg::HandleMouseDown (HWND hWnd, int _x, int _y)
{
  ConnectedComponent::HandleMouseDown (hWnd,_x,_y);
  if (gnd->isActive) // we are over the ground spot     
    gnd->Select(!gnd->isSelected);
  else
  {
    for (int i=0; i<7; i++)
    {
      if (segment[i]->isActive)
      {  
        segment[i]->Select(!segment[i]->isSelected);
        break; 
      }   
    }
  } 
}


Pin * SevenSeg::PinActive ()
{
  Pin * pin = 0;
  if (gnd->isActive)
    pin = gnd;
  else 
    for (int i=0; i<7;i++)
    {
      if (segment[i]->isActive)
      {
        pin = segment[i];
        break;
      }
    }  
  
  return pin;
}

SevenSeg::~SevenSeg()
{
  delete (gnd);                    
  for (int i=0; i<7; i++)
  {
    delete (segment[i]);
  }
  DeleteConnections();
}

// Check if the mouse has moved over one of the ports.
void SevenSeg::HandleMouseMove (HWND hWnd, int _x, int _y)
{
  gnd->HandleMouseMove ( hWnd, _x, _y );
  for (int i=0; i<7; i++)
    segment[i]->HandleMouseMove (hWnd, _x, _y);
}

void SevenSeg::AddMenu ()
{
  HMENU  MainMenu;
  HMENU  FileMenu;
     
  //arduinoMain.setHwnd ( hwndOwner);
  MainMenu=CreateMenu();
  FileMenu=CreateMenu();
  InsertMenu(MainMenu,ID_Edit,MF_POPUP,(UINT_PTR)FileMenu,"Help");
  AppendMenu(FileMenu,MF_STRING,SEVENSEGMENT_ABOUT,"&About");
  AppendMenu(FileMenu,MF_SEPARATOR,0,"");
  AppendMenu(FileMenu,MF_STRING,SEVENSEGMENT_HELP,"&Component Help");
  //  activate menu 
  (void) SetMenu(windowHandle,MainMenu);
}

void SevenSeg::HandleMenu ( int command )
{
  switch (command)
  {
    case SEVENSEGMENT_ABOUT:
      MessageBox(windowHandle, "7 Segment About", "TBD", MB_OK | MB_ICONEXCLAMATION);  
    break;
    
    case SEVENSEGMENT_HELP:
      MessageBox(windowHandle, "7 Segment Help", "TBD", MB_OK | MB_ICONEXCLAMATION);  
    break;
  }       
}

void SevenSeg::CleanUp()
{
  ConnectedComponent::CleanUp();
  for (int i=0; i<7; i++)
    segment[i]->CleanUp();
}

void SevenSeg::Paint(HDC _hdc, PAINTSTRUCT _ps, HDC _hdcMemory)
{
  int width;
  int height;
  bool vertical;
  bool offOn;
  int pinValue;
   
  ConnectedComponent::Paint (_hdc, _ps, _hdcMemory); // Show background image   
   
  for (int i=0; i<7; i++)
  {  
    vertical = segmentValues[i].horizontalVertical;
    offOn = false;
    pinValue = segment[i]->GetValue();
    if (pinValue == 1)
      pinValue = 1;
    if ((gnd->GetValue() == 0) && (pinValue == 1))
      offOn = true;
    if (offOn)  
    {
      displayedSegments[i]->x = segmentValues[i].x + x;
      displayedSegments[i]->y = segmentValues[i].y + y;
      displayedSegments[i]->Paint (hdc, ps, hdcMemory);
    }
    segment[i]->Paint (hdc, ps, hdcMemory);        
  }
  gnd->Paint(hdc, ps, hdcMemory);
    
}
void SevenSeg::Init (HWND _windowHandle, HINSTANCE _g_hInst, char * resource)
{   
  ConnectedComponent::Init ( _windowHandle, _g_hInst, resource);
  gnd->Init (windowHandle, g_hInst);
  for (int i=0; i<7;i++)
    segment[i]->Init (windowHandle, g_hInst);

  displayedSegments[0]->Init (windowHandle, g_hInst, "LEFTRIGHT");
  displayedSegments[1]->Init (windowHandle, g_hInst, "UPDOWN");
  displayedSegments[2]->Init (windowHandle, g_hInst, "UPDOWN");
  displayedSegments[3]->Init (windowHandle, g_hInst, "LEFTRIGHT");
  displayedSegments[4]->Init (windowHandle, g_hInst, "UPDOWN");
  displayedSegments[5]->Init (windowHandle, g_hInst, "UPDOWN");
  displayedSegments[6]->Init (windowHandle, g_hInst, "LEFTRIGHT");
}

Pin * SevenSeg::PortSelected(){
  Pin * pin = 0;
  if (gnd->isSelected)
  	pin = gnd;
  if (!pin)
    for (int i=0; i<7; i++)
	  if (segment[i]->isSelected)
	  {
	  	pin = segment[i];
	  	break;
	  }	
	  
  return pin;  
}


