#ifndef DIGIT3_H
#define DIGIT3_H
#include "ConnectedComponent.h"

/*
    Windows class to properly display the 3Digit display
*/
class Digit3:public ConnectedComponent
{
  public:          
    // Constructor
    Digit3(int, int, Component *); 
    // Destructor
    ~Digit3();
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
    static int const MAX_DIGIT3_PINS = 12;
    static int const NUM_DIGITS = 3;
	// Standard seven segment
    static int const NUM_SEGMENTS = 7;
    char screen[NUM_DIGITS+1];
    void showScreen(HDC hdcWindow);
    Pin * pin[MAX_DIGIT3_PINS];
    
    HBITMAP       hbmPinDot;
    BITMAP        bmPinDot;
    
    HBITMAP       hbmRedDot;
    BITMAP        bmRedDot;

    HBITMAP       hbmBlackDot;
    BITMAP        bmBlackDot;
    
    int col;
	int row;
	
    struct SegmentInfo
    {
      int x;
      int y;
    };
    SegmentInfo segmentValues[NUM_DIGITS][NUM_SEGMENTS]; 	   
    Component * displayedSegments[NUM_DIGITS][NUM_SEGMENTS];  
};

#endif


