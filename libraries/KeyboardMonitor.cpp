#include "KeyboardMonitor.h"
#include "windows.h"
#include "SerialClass.h"
#include "Menus.h"

KeyboardMonitor::KeyboardMonitor():Component()
{ 
  hWndEdit = NULL;
}


void KeyboardMonitor::Paint(HWND hWnd, HDC &hdcWindow, HDC &hdcMemory, PAINTSTRUCT &ps)
{
   
  Component::Paint (hdcWindow, ps, hdcMemory); // Show image    
  // Component::PaintEnd ( &hdcMemory, hWnd, &ps);
}

void KeyboardMonitor::AddMenu ()
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

HWND KeyboardMonitor::DrawWindow (char * title, HINSTANCE hInst, char * bmpResource, 
                                  int x , int y, int width, int height)
{                           
  HWND textHandle;
  HWND hWnd;
  hWnd = Component::DrawWindow(title, hInst, "", x, y, 450,550);
  int Style = WS_CHILD | WS_VISIBLE | WS_VSCROLL | WS_TABSTOP;
  int Exstyle = WS_EX_CLIENTEDGE; 
  int id = 1009;
  
  // Create the edit box 
  hWndEdit = CreateWindow ( TEXT ( "edit"), TEXT ( ""), 
          WS_VISIBLE | WS_CHILD | WS_BORDER | ES_MULTILINE | ES_WANTRETURN | ES_AUTOVSCROLL,  
          10,10,300,20,
          windowHandle, (HMENU)11, NULL, NULL );   
          
  
  // Create the list box 
  textHandle = CreateWindowEx(WS_EX_CLIENTEDGE,"Listbox",NULL,
               WS_CHILD | WS_VISIBLE | WS_VSCROLL | WS_TABSTOP,
               10, 40, 400, 450, windowHandle, (HMENU)id, hInst, NULL);
  SendMessage(textHandle,(UINT)WM_SETFONT,(WPARAM)GetStockObject
             (DEFAULT_GUI_FONT),(LPARAM)MAKELPARAM(FALSE,0));
  Serial.setTWindow (textHandle); // Set text window where Serial will write to?
  
  return hWnd;
}

void KeyboardMonitor::GetWindowTxt ( TCHAR * szText )
{
  int len;
  if (hWndEdit)
  {
    GetWindowText ( hWndEdit, szText, 511 );
    len = strlen (szText);
    for (int i=0; i<len; i++)
    {
      if ((char) *(szText+i) == '\r')
      {
        SetWindowText ( hWndEdit, "" ); 
        break;
      }      
    }  
  }    
}


