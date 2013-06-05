#ifndef ROTARYDIP_H
#define ROTARYDIP_H
#include "ConnectedComponent.h"

/*
    Windows class to properly display the rotary Dip switch
*/
class RotaryDip:public ConnectedComponent
{
  public:          
    // Constructor
    RotaryDip(int, int, Component *); 
    // Destructor
    ~RotaryDip();
    void Paint(HDC _hdc, PAINTSTRUCT _ps, HDC _hdcMemory);  
	void Init (HWND _windowHandle, HINSTANCE _g_hInst, char *);
	void print (char * ch);  
	void print (int value);
    bool clearTheText;
    void HandleMenu ( int command );
    void AddMenu ();     
    void HandleMouseMove (HWND hWnd, int _x, int _y);  
    void HandleMouseDown (HWND hWnd, int _x, int _y);
    void HandleMouseUp (HWND hWnd);
    void MoveTo (int, int); 
    void SaveYourself (FILE * fp);
    void NotSavedYet(){}; 
    void Select ( bool select);
    
	Pin * PinActive(); 
    Pin * PortSelected();
    Pin * FindPort ( char * port);    
 
  private:
  	int whichDip;
  	int lastDip;
  	bool pinSelected;
    // bool offOn;
    bool rotateDial;
    static int const MAX_ROTARYDIP_PINS = 6;
    static int const NUM_DIGITS = 3;
    
    void showScreen(HDC hdcWindow); // necessary?
    Pin * pin[MAX_ROTARYDIP_PINS];
    
    HBITMAP       hbmPinDot;
    BITMAP        bmPinDot;
    
    HBITMAP       hbmRedDot;
    BITMAP        bmRedDot;

    HBITMAP       hbmBlackDot;
    BITMAP        bmBlackDot;	
};

#endif


