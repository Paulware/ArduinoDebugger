#include "ViewConnections.h"
#include "Pin.h"
#include "ArduinoComponent.h"
#include "HighLevelMenu.h"
#include "SimUtilities.h"

HWND viewConnectionHandle=0; // Handle to this classe' window

ViewConnections::ViewConnections(int _x, int _y):Component()
{ 
  x = _x;
  y = _y;
}

ViewConnections::~ViewConnections()
{ 	
}

// Set the hdcWindow, hdcMemory and ps for all the components 
void ViewConnections::PaintStart ()
{
}

void ViewConnections::Paint(HWND hWnd)
{
  int x;
  int y=0;	
  Connection * connection;
  ArduinoComponent * arduino = (ArduinoComponent *)HighLevelMenu::Instance()->FindComponent("Arduino");
  char * name;
  Pin * pin;
  char value[10];
  /*
  char * names[numConnections] = {    "d0",  "d1",  "d2",  "d3", "d4", "d5", "d6", "d7", "d8", "d9",
                                    "d10", "d11", "d12", "d13", "a0", "a1", "a2", "a3", "a4", "a5", 
   				   			      "power", "gnd"};
  char * info[numConnections] = { "NC", "NC", "NC", "NC", "NC", "NC", "NC", "NC", "NC", "NC",
                                  "NC", "NC", "NC", "NC", "NC", "NC", "NC", "NC", "NC", "NC", 
   				   			      "NC", "NC"};			   			      
  */   				   			      
  int index = 0;   				   			      
  // PaintStart ();
  hdc = BeginPaint (hWnd, &ps);
  hdcMemory = CreateCompatibleDC (hdc);
  
  SimUtilities::Instance()->MakeConnectionList();
  SimUtilities::Instance()->ViewConnections(hdc);  
  
  DeleteDC (hdcMemory);    
  EndPaint (hWnd, &ps);
}

HWND ViewConnections::DrawWindow (HINSTANCE hInst)
{                            
  viewConnectionHandle = Component::DrawWindow("Arduino Connections", hInst, "", x, y, 500,500);
  Paint (windowHandle);
  // AddMenu();
  return viewConnectionHandle;
}
