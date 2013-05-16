#include "Line.h"
Line::Line(int _x1, int _y1, int _x2, int _y2):Component()
{ 
  float xOffset = 0.0;
  float yOffset = 0.0;
  int x;
  int y;
  x1 = _x1;
  y1 = _y1;
  x2 = _x2;
  y2 = _y2;
  float xDiff = (float)(x2 - x1) / (float)DOTSPERLINE;
  float yDiff = (float)(y2 - y1) / (float)DOTSPERLINE;
  
  for (int i=0; i<DOTSPERLINE; i++)
  {
  	x = x1+xOffset;
  	y = y1+yOffset;
    dot[i] = new Component ();
    dot[i]->x = x;
    dot[i]->y = y;
    xOffset += xDiff;
    yOffset += yDiff;
  }
}

Line::~Line()
{
}

void Line::HandleMouseDown (HWND hWnd, int _x, int _y)
{
  Component::HandleMouseDown (hWnd,_x,_y);
}

void Line::MoveTo (int _x1, int _y1, int _x2, int _y2)
{
  float xOffset = 0.0;
  float yOffset = 0.0;
  int x;
  int y;
  
  x1 = _x1;
  y1 = _y1;
  x2 = _x2;
  y2 = _y2;
  float xDiff = (float)(x2 - x1) / (float)(DOTSPERLINE-1);
  float yDiff = (float)(y2 - y1) / (float)(DOTSPERLINE-1);
  
  for (int i=0; i<DOTSPERLINE-1; i++)
  {
  	dot[i]->MoveTo (x1+xOffset,y1+yOffset);
  	dot[i]->CenterYourself ();
	xOffset += xDiff;
    yOffset += yDiff;
  }  
  dot[DOTSPERLINE-1]->MoveTo ( x2,y2);
}

void Line::CleanUp()
{
  for (int i=0; i<DOTSPERLINE; i++)	
    dot[i]->CleanUp();
}

void Line::Init (HWND _windowHandle, HINSTANCE _g_hInst)
{   
  Component::Init ( _windowHandle, _g_hInst, "");
  for (int i=0; i<DOTSPERLINE; i++)	
    dot[i]->Init (windowHandle, g_hInst, "DOT");
}

void Line::Paint(HDC _hdc, PAINTSTRUCT _ps, HDC _hdcMemory)
{
  for (int i=0; i<DOTSPERLINE; i++)	
    dot[i]->Paint (_hdc, _ps, _hdcMemory);
}
