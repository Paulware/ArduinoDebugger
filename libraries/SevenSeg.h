#ifndef SEVENSEG_H
#define SEVENSEG_H
#include "ConnectedComponent.h"
class SevenSeg:public ConnectedComponent
{
  public:          
    // Constructor
    SevenSeg(int,int,Component *); 
    // Destructor
    ~SevenSeg(); 
    void Init (HWND _windowHandle, HINSTANCE _g_hInst, char *);
    void CleanUp();    
    void Paint(HDC _hdc, PAINTSTRUCT _ps, HDC _hdcMemory);                      
    void AddMenu();
    void HandleMenu ( int command );
    void HandleMouseMove (HWND hWnd, int _x, int _y);  
    Pin * PortSelected();
    void HandleMouseDown (HWND hWnd, int _x, int _y);  
    void MoveTo (int, int);  
    Pin * PinActive ();      
    Pin * segment[7];
    Pin * gnd; // Common Ground
    void SaveYourself (FILE * fp);
    void Select ( bool select);
    Pin * FindPort ( char *);     

    
  private:
    // bool offOn;
    HBITMAP       hbmUpDown;
    BITMAP        bmUpDown;

    HBITMAP       hbmLeftRight;
    BITMAP        bmLeftRight;

    struct SegmentInfo
    {
      int x;
      int y;
      bool horizontalVertical;
    };
    SegmentInfo segmentValues[7]; 	   
    Component * displayedSegments[7];
};

#endif


