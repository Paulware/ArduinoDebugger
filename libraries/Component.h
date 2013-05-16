#ifndef COMPONENT_H
#define COMPONENT_H
#include <windows.h>
#include <stdio.h>
#include "Menus.h"
class Component
{
  public:
    Component();
    virtual ~Component();
    // Next function is virtual so that the matching component will call DrawWindow
    virtual HWND DrawWindow (char * title, HINSTANCE hInst, char * bmpResource, 
                             int x , int y, int width=0, int height=0);
	virtual int NumConnections(){return 0;};	  
    virtual void Paint (HDC _hdc, PAINTSTRUCT _ps, HDC _hdcMemory);
    virtual void Select (bool select){};
    virtual Component * SelectedPort (){ return NULL;};
    void Refresh ();
    virtual bool IsSelected (){return false;};
    virtual void * PortSelected () {return 0;};
    virtual void * GetConnection (int){return 0;};
    void HandleMenu (int command) {};
    virtual void AddMenu () {};
    virtual void HandleMouseDown (HWND hWnd, int _x, int _y);
    virtual void HandleMouseUp (HWND hWnd) {};
    virtual void HandleMouseMove (HWND, int, int){};  
	virtual void Reset (){};
	virtual bool IsSet(){return false;};
    virtual void * PinActive (){return 0;};
    virtual void Activate (bool active) {};
    virtual void MoveTo (int _x, int _y);
	virtual void Init (HWND _windowHandle, HINSTANCE _g_hInst, char * resource);
    virtual void CenterYourself ();
    virtual void SaveYourself (FILE *);
    virtual void NotSavedYet (){}; // Mark each pin as connection not saved
    virtual void SaveConnections ( FILE * fp){fprintf (fp,"Generic Connections\n");};
    virtual void * FindPort (char*) {return 0;};
    virtual void CleanUp () { DeleteObject (hbm);};
    HBITMAP hbm;
    BITMAP bm;
    HWND   windowHandle;
    HINSTANCE g_hInst;    
    int x;
    int y;
    int width;
    int height;
    int xOffset;
    int yOffset;
    HDC hdcMemory;
    HDC hdc;
    PAINTSTRUCT ps;
    bool isActive;
    bool wasSet;
    void SaveType ( char *);
    
    static int const MAXCOMPONENTTYPELENGTH=20;
    char componentType[MAXCOMPONENTTYPELENGTH];
    
    static int const MAXRESOURCECHARS=20;
    char bmpResource [MAXRESOURCECHARS];
    
  protected:    
};
#endif


