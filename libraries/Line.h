#ifndef LINE_H
#define LINE_H
#include "Component.h"
class Line:public Component
{
  public:          
    Line(int,int,int,int); // Constructor
    ~Line(); // Destructor
    void Paint(HDC _hdc, PAINTSTRUCT _ps, HDC _hdcMemory);                      
    void HandleMouseMove (HWND hWnd, int _x, int _y){};  
    void HandleMouseDown (HWND hWnd, int _x, int _y);  
    void MoveTo (int, int, int , int);  
	void Init (HWND, HINSTANCE);
    void CleanUp();		 
    
  private:
    
    int x1;
    int y1;
    int x2; 
    int y2;
    
    static const int DOTSPERLINE = 40;
    Component * dot[DOTSPERLINE];
};
#endif


