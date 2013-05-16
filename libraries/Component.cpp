#include "Component.h"
#include "Menus.h"

Component::Component()
{ 
  g_hInst = NULL; 
  windowHandle = NULL;                  
  hbm = 0;
  x = 0;
  y = 0;
  width = 0;
  height = 0;
  xOffset = 0;
  yOffset = 0;
  hdc = 0;
  hdcMemory = 0;
  bm.bmWidth = 0;
  ps.hdc = 0;
  wasSet = false;
  strcpy (componentType, "");
}

Component::~Component()
{
}

void Component::SaveType (char * typeName)
{
  if (strlen (typeName) < MAXCOMPONENTTYPELENGTH)
    strcpy ( componentType, typeName);
}

void Component::CenterYourself ( )
{
  x = x + bm.bmWidth/2;
  y = y + bm.bmHeight/2;
}

void Component::HandleMouseDown (HWND hWnd, int _x, int _y)
{
	// This should never be called as the virtual subclass should be called.
}

void Component::Init (HWND _windowHandle, HINSTANCE _g_hInst, char * resource)
{
  windowHandle = _windowHandle; 
  g_hInst = _g_hInst;
  strcpy ( bmpResource, resource);
} 

void Component::Refresh ()
{
  if (windowHandle)
    InvalidateRect ( windowHandle, NULL, true );      
}

/*
   Input:
       hWnd: handle to current window
       
   Note:
       PaintEnd needs to be called after calling this function    
*/
void Component::Paint(HDC _hdc, PAINTSTRUCT _ps, HDC _hdcMemory)
{   
  hdc = _hdc;
  ps = _ps;
  hdcMemory = _hdcMemory;
  
  hbm = LoadBitmap (g_hInst, bmpResource );     
    
  if (hbm && hdcMemory)
  {  	
    GetObject(hbm, sizeof(bm), &bm);          
    SelectObject(hdcMemory, hbm);    
    width = bm.bmWidth;
    height = bm.bmHeight;  
    BitBlt(hdc, x, y, bm.bmWidth, bm.bmHeight, hdcMemory, 0, 0, SRCAND);
    BitBlt(hdc, x, y, bm.bmWidth, bm.bmHeight, hdcMemory, 0, 0, SRCPAINT);
  } 
  else if (!hbm)
  {
    // MessageBox (0, "Error don't have a bitmap", "Error", 0); 
    hbm = 0;
  }
  else if (!hdcMemory)
  {
  //   MessageBox (0, "Cannot Select object in memory", "Error", 0);
    hdcMemory = 0;
  }
}

void Component::SaveYourself (FILE * fp)
{
  fprintf ( fp, "Generic Component saving itself");
  MessageBox (0,"Implement SaveYourself for one of these components", "OOPS", 0);
}

void Component::MoveTo (int _x, int _y)
{
  x=_x; 
  y=_y;
}

// DrawWindow is only used by the high level windows to draw the actual window with menu
HWND Component::DrawWindow(char * title, HINSTANCE hInst, char * bmpResource, 
                           int x, int y, int width, int height)
{
  g_hInst = hInst; 
  int Style = WS_MINIMIZEBOX | WS_SIZEBOX | WS_CAPTION | WS_MAXIMIZEBOX |
              WS_POPUP | WS_SYSMENU;                    
 
  // Load the bitmap background image
  hbm = LoadBitmap (g_hInst, bmpResource );   
  
  // Create and show the window
  windowHandle = CreateWindowEx(0,"ListBox1",title,
      Style, x, y, 4+width, 12+height, NULL,(HMENU)NULL,hInst,NULL);      
  SendMessage(windowHandle,(UINT)WM_SETFONT,(WPARAM)GetStockObject(DEFAULT_GUI_FONT),
    (LPARAM)MAKELPARAM(FALSE,0));
  RedrawWindow(windowHandle,0,0,0);
  ShowWindow(windowHandle,SW_SHOW);
  AddMenu();
  return windowHandle;
}


