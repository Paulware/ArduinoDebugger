#ifndef DEBUGUTILITIES_H
#define DEBUGUTILITIES_H
#include <Arduino.h>
class DebugUtilities
{
  public:          
    // Constructor
    DebugUtilities();  
    bool debugging (); 
    void showNumber ( PGM_P s, int number );
    void printPSTR ( PGM_P s );

  // private:
};
#endif


