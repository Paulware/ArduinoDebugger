#include "ArduinoMain.h"
#include <stdio.h>

ArduinoMain::ArduinoMain()
{
  //hWnd = _hWnd;      
}

void ArduinoMain::loop()
{
  cout << "What's up?\n"
  /*
  char ch;
  // #include "loop.ino"  
  FILE *portfp;
  system ("mode com15:baud=115200 parity=0 data=8 stop=1 to=off xon=off");
  portfp = fopen ("com1", "wb+");
  ch = fgetc(portfp);
  while (ch != ' ')
  {         
    fprintf (, ch);
    ch = fgetc(portfp);
  }  
  fclose (portfp);
  */  
}
void ArduinoMain::setHwnd(HWND hwndOwner)
{
  hWnd = hwndOwner;
}

