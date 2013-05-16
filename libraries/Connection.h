#ifndef CONNECTION_H
#define CONNECTION_H
#include "Component.h"
#include "Pin.h"
#include "Line.h"
class Connection:public Component
{
  public:          
    Connection(Pin *, Pin *); // Constructor
    ~Connection();       // Destructor
    void Paint(HDC _hdc, PAINTSTRUCT _ps, HDC _hdcMemory);                     
    void HandleMouseMove (HWND hWnd, int x1, int y1, int x2, int y2);
    void Move ();
	void HandleMouseDown (HWND hWnd, int _x, int _y){};
    void NotSavedYet(){};
    void SaveConnection ( FILE *);
    Pin * pin1;
    Pin * pin2;
    Pin * OtherPin (Pin *);
    void Init (HWND, HINSTANCE);
    void CleanUp();
    int value;
    int resistance;
   
  private:
    Line * line;
    int x1;
    int y1;
    int x2;
    int y2;
};
#endif

