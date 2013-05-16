#ifndef PIN_H
#define PIN_H

#define MAX_PIN_CONNECTIONS 10
#include "Component.h"
struct PinValueType
{
  int value;
  int resistance;
};

class Pin: public Component
{
  public:          
    // Constructor
    Pin(Component *); 
    ~Pin(); // Clean up the connection
    
    void SetName(char *);
	int GetValue();
	int GetResistance();
	bool IsSet();
	// void WriteValue (int value);
	void Connect ( Pin * pin );
    void HandleMouseMove (HWND,int,int);
    void Init (HWND, HINSTANCE);
    void Paint(HDC _hdc, PAINTSTRUCT _ps, HDC _hdcMemory);
    void Select (bool);
    void MoveTo (int, int);
    void SetConnection (Component * _connection);
    int xOffset;
    int yOffset;
    bool IsSelected();
    bool isSelected;
    char * name;   
    bool isActive; 
    
    PinValueType value;
    PinValueType constValue;
 
    Component * parent;  
	Component * connection; 
	bool traversed; 
	// TODO WriteValue 

};
#endif


