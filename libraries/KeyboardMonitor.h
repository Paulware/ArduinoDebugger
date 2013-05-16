#ifndef KEYBOARDMONITOR_H
#define KEYBOARDMONITOR_H
#include "Component.h"
class KeyboardMonitor:Component
{
  public:          
    // Constructor
    KeyboardMonitor(); 
    HWND DrawWindow (char * title, HINSTANCE hInst, char * bmpResource, 
                     int x , int y, int width=0, int height=0);
    void Paint(HWND hWnd, HDC &hdcWindow, HDC &hdcMemory, PAINTSTRUCT &ps);
    void GetWindowTxt (  TCHAR * szText );
    void AddMenu();
    void HandleMenu (int command) {};  
    void HandleMouseDown (HWND hWnd) {};
    void HandleMouseUp (HWND hWnd){};
    void NotSavedYet(){};
	    
  private:
    HWND hWndEdit;
};

#endif


