#ifndef LCDDISPLAY_H
#define LCDDISPLAY_H
#include "ConnectedComponent.h"

class LCDDisplay:public ConnectedComponent
{
  public:          
    // Constructor
    LCDDisplay(int, int, Component *); 
    // Destructor
    ~LCDDisplay();
    void Paint(HDC _hdc, PAINTSTRUCT _ps, HDC _hdcMemory);  
	void Init (HWND _windowHandle, HINSTANCE _g_hInst, char *);
	void print (char * ch);  
	void print (int value);
    void clear();
    bool clearTheText;
    void HandleMenu ( int command );
    void AddMenu ();     
    void HandleMouseMove (HWND hWnd, int _x, int _y);  
    void HandleMouseDown (HWND hWnd, int _x, int _y);  
    void MoveTo (int, int); 
	Pin * PinActive(); 
    Pin * PortSelected();
    void SaveYourself (FILE * fp);
    void NotSavedYet(){}; 
    void Select ( bool select);
    Pin * FindPort ( char * port);    
 
  private:
    bool offOn;
    static int const MAX_LCD_PINS = 16;
    static int const MAX_SCREEN_CHARS = 80;
    char screen[MAX_SCREEN_CHARS];
    void showScreen(HDC hdcWindow);
    Pin * pin[MAX_LCD_PINS];
    
    HBITMAP       hbmPinDot;
    BITMAP        bmPinDot;
    
    HBITMAP       hbmRedDot;
    BITMAP        bmRedDot;

    HBITMAP       hbmBlackDot;
    BITMAP        bmBlackDot;
    
    int col;
	int row;
    
};

#endif


