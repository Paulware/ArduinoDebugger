#ifndef ShiftRegister_H
#define ShiftRegister_H
#include "ConnectedComponent.h"

/*
    Windows class to properly display the rotary Dip switch
*/
class ShiftRegister:public ConnectedComponent
{
  public:          
    // Constructor
    ShiftRegister(int, int, Component *); 
    // Destructor
    ~ShiftRegister();
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
    void Update ();
    Pin * FindPort ( char * port);
	Pin * PinActive(); 
    Pin * PortSelected();
 
  private:
  	int shiftValue;
    int lastSRCLK;
	bool pinSelected;
    static int const MAX_SHIFTREGISTER_PINS = 16;
    
    Pin * pin[MAX_SHIFTREGISTER_PINS];
    void WriteOutValue (int value);
    
    HBITMAP       hbmPinDot;
    BITMAP        bmPinDot;
    
    HBITMAP       hbmRedDot;
    BITMAP        bmRedDot;

    HBITMAP       hbmBlackDot;
    BITMAP        bmBlackDot;	
};

#endif


