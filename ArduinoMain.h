#ifndef ARDUINOMAIN_H
#define ARDUINOMAIN_H
#include <windows.h>
class ArduinoMain
{
  public:          
    // Constructor
    ArduinoMain();  
    void loop();
    void setHwnd(HWND hwndOwner);
  private:
    HWND hWnd;
};
#endif


