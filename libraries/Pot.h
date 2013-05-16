#ifndef POT_H
#define POT_H
#include "ConnectedComponent.h"
class Pot:public ConnectedComponent
{
  public:          
    Pot(int,int,Component *);
    ~Pot();
    Pin * PortSelected ();
    void Select (bool);
    void Paint(HDC _hdc, PAINTSTRUCT _ps, HDC _hdcMemory);                      
    void HandleMenu ( int command );
    void HandleMouseMove (HWND hWnd, int _x, int _y);  
    void HandleMouseDown (HWND hWnd, int _x, int _y);  
    void HandleMouseUp (HWND hWnd);
    void Reset();
    bool IsSet();
    void MoveTo (int, int);  
	void Init (HWND _windowHandle, HINSTANCE _g_hInst, char *);    
    Pin * PinActive ();      
    Pin * gnd;
    Pin * power;
	Pin * analogInput;
    void AddMenu ();
    void SaveYourself (FILE * fp);    
    Pin * FindPort ( char *);    
    void CleanUp();
	 	    
  private:
    bool offOn;    
};

#endif


