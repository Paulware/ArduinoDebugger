#ifndef SIMUTILITIES_H
#define SIMUTILITIES_H

#include <windows.h>
#include "Pin.h"
#include "Connection.h"
class SimUtilities
{
  public:          
    // Constructor
    SimUtilities(); 
    ~SimUtilities(); 
	static SimUtilities * Instance();
    int NumConnections (Pin * pin);
	void ShowConnections (Pin * pin); 
    void ClearConnections();
    void MakeConnectionList (Pin * pin = 0);  
    Connection * GetConnection (int index);
    void WriteValue ( Pin* pin, int value, int resistance);
    void WritePinValue ( Pin* pin, int value, int resistance);
    void ViewConnections (HDC hdc);
    bool HasConstantValue (int & value, int & resistance);
    void UpdateSystem ();
    
  private:
    void MakeList (Pin * pin);
    bool ConnectionInList (Connection * connection);
    bool PinInList (Pin * pin);
    int numConnections;
    int numPins;
    static const int MAXCONNECTIONS = 50;
    Connection * connections[MAXCONNECTIONS];
    Pin * pins[MAXCONNECTIONS];
};
#endif

