#ifndef INPUTBOX_H
#define INPUTBOX_H
#include <windows.h>

class InputBox
{
  public:	
    InputBox(int, int); 
    ~InputBox();
    char * getOutput();
    bool Done();
};
#endif


