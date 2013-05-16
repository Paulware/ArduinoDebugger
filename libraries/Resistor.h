#ifndef RESISTOR_H
#define RESISTOR_H
#include "ConnectedComponent.h"
class Resistor:public ConnectedComponent
{
  public:          
    // Constructor
    Resistor(int _x, int _y, int _resistance, Component * _diagram); 
    // Destructor
    ~Resistor();
    Pin * PortSelected ();    
    void Paint(HDC _hdc, PAINTSTRUCT _ps, HDC _hdcMemory);
    void HandleMouseDown (HWND hWnd, int _x, int _y);                      
    void HandleMouseMove (HWND hWnd, int _x, int _y);                      
    void HandleMouseUp (HWND hWnd); 
	void HandleMenu(int command){};
    void AddMenu ();       
    void MoveTo (int, int);  
    Pin * PinActive ();      
    bool IsSet();
    void Reset();
    void SaveYourself (FILE * fp);        
    void SaveConnections (FILE * fp);
    void Select (bool){};
	void Init (HWND _windowHandle, HINSTANCE _g_hInst, char *);
    void IsConnected (Pin *, Pin *);    
    void Connect (Pin * pin1, Pin * pin2); 
       
    Pin * FindPort ( char * port);
    Pin * input;
    Pin * output;
    int resistance;
    
  private:
};

#endif


