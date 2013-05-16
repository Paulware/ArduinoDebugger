#ifndef COMPONENTS_H
#define COMPONENTS_H
#include <Arduino.h>
#include "DebugUtilities.h"
class Components
{
  public:          
    // Constructor
    Components();  
    float thermistorFahrenheit (int AnalogInputNumber);

    int thermistorInput;
  private:
    DebugUtilities debugUtils;
};
#endif


