#ifndef VIEWCONNECTIONS_H
#define VIEWCONNECTIONS_H
#include "Component.h"

class ViewConnections:public Component
{
  public:	
    ViewConnections(int,int); 
    ~ViewConnections();
    HWND DrawWindow (HINSTANCE); 
    void PaintStart ();
    void Paint(HWND hWnd);
    void HandleMouseMove (HWND hWnd, int x, int y){};
    void HandleMenu (int command){}; 
    void AddMenu (){};
    void HandleMouseDown (HWND hWnd, int x, int y){};
    void HandleMouseUp (HWND hWnd){};
    void NotSavedYet(){};
};
#endif


