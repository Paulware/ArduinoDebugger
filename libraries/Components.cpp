#include "Components.h"

// Datasheet of thermistor will specify following values:
#define BCONSTANT 4050.0f
#define T0 298.15f
#define R0 10000.0f

Components::Components ():debugUtils()
{
}

float Components::thermistorFahrenheit (int AnalogInputNumber)
{
  float R,T;
  float R_Balance = 10000.0f; // Balance Resistor (same resistance as R0 of thermistor)

  R=1024.0f*R_Balance/float(analogRead(AnalogInputNumber))-R_Balance;
  T=1.0f/(1.0f/T0+(1.0f/BCONSTANT)*log(R/R0));
  // Determine Fahrenheit temperature 
  T=9.0f*(T-273.15f)/5.0f+32.0f;
   
  debugUtils.printPSTR ( PSTR ( "Thermistor read: " ) );
  Serial.println ( T );
  return T;
}
