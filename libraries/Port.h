#ifndef CONNECTION_H
#define CONNECTION_H
#include "Component.h"
class Connection:public Component
{
  public:          
    Connection(int,int){}; // Constructor
    ~Connection() {};       // Destructor
    void PaintStart (HDC & _hdcWindow ,HDC & _hdcMemory, PAINTSTRUCT &_ps) {};
    void Paint(HWND hWnd) {};                      
    void HandleMouseMove (HWND hWnd, int _x, int _y){};  
    void HandleMouseDown (HWND hWnd, int _x, int _y){};  
    void MoveTo (int, int){};  
  private:
};
#endif


