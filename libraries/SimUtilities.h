#ifndef SIMUTILITIES_H
#define SIMUTILITIES_H
#include "Pin.h"
#include "Connection.h"
class SimUtilities
{
  public:          
    // Constructor
    SimUtilities(); 
	static SimUtilities * Instance();
    int NumConnections (Pin * pin);
	void ShowConnections (Pin * pin); 
    void MakeConnectionList (Pin * pin);
    Connection * GetConnection (int index);
    void WriteValue ( Pin* pin, int value, int resistance);
	
  private:
    void MakeList (Pin * pin);
    bool ConnectionInList (Connection * connection);
    int numConnections;
    static const int MAXCONNECTIONS = 50;
    Connection * connections[MAXCONNECTIONS];
};
#endif


