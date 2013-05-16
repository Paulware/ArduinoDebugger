#ifndef ARDUINOCOMPONENT_H
#define ARDUINOCOMPONENT_H
#include <windows.h>
#include "ConnectedComponent.h"
#define MAX_DIGITAL_VALUES 20
class ArduinoComponent:public ConnectedComponent
{
  public:          
    // Constructor
    ArduinoComponent(int, int, Component *); 
    // Destructor
    ~ArduinoComponent();
    Pin * power;
	Pin * gnd;
	Pin * d[MAX_DIGITAL_VALUES];
	Pin * GetConnection (int);
    void Select (bool);
    void Paint (HDC _hdc, PAINTSTRUCT _ps, HDC _hdcMemory);    
    void digitalWrite (int, int); 
    void MoveTo (int _x, int _y); 
    void AddMenu ();    
    void HandleMouseDown (HWND hWnd, int _x, int _y); 
    void HandleMouseMove (HWND hWnd, int _x, int _y);    
    void SaveYourself (FILE * fp);         
    Pin * FindPort ( char *); 
    bool IsSet();
    void Reset();	   
    void Init (HWND _windowHandle, HINSTANCE _g_hInst, char *);    
	void CleanUp();
    void Connect (Pin * pin1, Pin * pin2);    
    
    Pin * PortSelected();
    Pin * PinActive();	  
    
  private:
    int redDotX,redDotY,blackDotX,blackDotY;   
    struct digitalInfo
    {
      int x;
      int y;
      bool blackRed;     
    };
    digitalInfo digitalValues[MAX_DIGITAL_VALUES];

};

#endif


