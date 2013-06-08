#ifndef Multiplexer_H
#define Multiplexer_H
#include "ConnectedComponent.h"

class Multiplexer:public ConnectedComponent
{
  public:          
    // Constructor
    Multiplexer(int, int, Component *); 
    // Destructor
    ~Multiplexer();
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
  	bool firstUpdate;
    int lastSelection;
	bool pinSelected;
    static int const MAX_MULTIPLEXER_PINS = 16;
    
    Pin * pin[MAX_MULTIPLEXER_PINS];
    void WriteOutValue (int value);
    
    HBITMAP       hbmPinDot;
    BITMAP        bmPinDot;
    
    HBITMAP       hbmRedDot;
    BITMAP        bmRedDot;

    HBITMAP       hbmBlackDot;
    BITMAP        bmBlackDot;	
};

#endif


