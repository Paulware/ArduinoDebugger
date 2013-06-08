#ifndef CONNECTEDCOMPONENT_H
#define CONNECTEDCOMPONENT_H
#include "Component.h"
#include "Connection.h"
#include "Pin.h"
/* 
  Connected Commponents are Components which also can be connected to other components
  As opposed to simple components like Dots which can only be displayed
*/

class ConnectedComponent:public Component
{
  public:          
    ConnectedComponent(int,int,Component *); 
    ~ConnectedComponent(); 
    virtual void Connect (Pin * pin1, Pin * pin2);
    virtual void IsConnected (Pin * localPin, Pin * remotePin){};
    virtual void SaveConnections(FILE * fp);
    void Paint (HDC _hdc, PAINTSTRUCT _ps, HDC _hdcMemory);
    void Move ();
    Connection * FindConnection ( Pin * pin); // Call the parent
    Connection * FindConnect ( Pin * pin); // Look at all my connections
    virtual void Select (bool) = 0;    
	// Create setter/accessor for next 2 items?		    
    int numConnections;
    static int const CONNECTIONSPERCOMPONENT = 20;    
	Connection * connections[CONNECTIONSPERCOMPONENT];	
    Pin * FindOtherPin (Pin *);    	
    virtual bool TroubleshootPins (){return true;};
	virtual void Init (HWND _windowHandle, HINSTANCE _g_hInst, char * resource);  
	virtual void CleanUp(); 
    Component * diagram;
	void Refresh();
	virtual void Update (){};
    void AddTempConnector ( Pin * pin1, Pin * pin2);
	void ClearTemporaryConnections();
	void DeleteConnections();
    private:
	  int numTempConnections;	
};
#endif


