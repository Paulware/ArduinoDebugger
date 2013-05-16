#ifndef LIQUIDCRYSTAL_H
#define LIQUIDCRYSTAL_H
#include <Arduino.h>
#include <stdint.h>
class LiquidCrystal
{
  public:          
    // Constructor
    LiquidCrystal();
    LiquidCrystal(int a,int b,int c,int d,int e,int f); 
	void setCursor(uint8_t _x, uint8_t _y );
	void print (char *);
	void print (char);
	void print (int);
	void clear();
    void begin(uint8_t cols, uint8_t rows, uint8_t charsize = 0){};
    
  private:
    uint8_t x;
	uint8_t y;
};

#endif


