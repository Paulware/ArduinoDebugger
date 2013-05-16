#ifndef MOMENTARYDEPRESS_H
#define MOMENTARYDEPRESS_H
#include "ConnectedComponent.h"
class MomentaryDepress:public ConnectedComponent
{
  public:          
    MomentaryDepress(int _x, int _y, Component * diagram); 
    ~MomentaryDepress();
    Pin * PortSelected ();    
    void Paint(HDC _hdc, PAINTSTRUCT _ps, HDC _hdcMemory);
    void HandleMouseDown (HWND hWnd, int _x, int _y);                      
    void HandleMouseMove (HWND hWnd, int _x, int _y);                      
    void HandleMouseUp (HWND hWnd); 
	void HandleMenu(int command){};
    void AddMenu ();       
    void MoveTo (int, int);  
    Pin * PinActive ();      
    void Init (HWND _windowHandle, HINSTANCE _g_hInst, char *);
    void CleanUp();
    bool IsSet();
    void Select (bool){};    
    void SaveYourself (FILE * fp);        
    Pin * FindPort ( char * port);
    Pin * input;
    Pin * output;
    
  private:
    bool depressed;
    HBITMAP       hbmDepressed;
    BITMAP        bmDepressed;
};

#endif


