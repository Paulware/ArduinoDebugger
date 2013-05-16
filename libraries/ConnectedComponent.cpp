#include "ConnectedComponent.h"
#include "HighLevelMenu.h"
ConnectedComponent::ConnectedComponent(int _x, int _y, Component * _diagram):Component()
{
  x = _x;
  y = _y;
  for (int i=0; i<CONNECTIONSPERCOMPONENT; i++)
    connections[i] = 0;
  numConnections = 0;
  diagram = _diagram; // Save the parent diagram
}

ConnectedComponent::~ConnectedComponent()
{
  int index = 0;
  Connection * connection;
  while (connection = connections[index])
  {
  	delete (connection);
  	index++;
  }
  DeleteConnections();
}

void ConnectedComponent::Refresh()
{	
  HighLevelMenu * highLevelMenu = (HighLevelMenu *) diagram;
  highLevelMenu->Refresh();
}

void ConnectedComponent::CleanUp()
{
  Connection * connection;	
  int index = 0;
  Component::CleanUp();
  while ( connection = connections[index++])
    connection->CleanUp();
}

Pin * ConnectedComponent::FindOtherPin (Pin * pin)
{
  Connection * connection;
  int index = 0;
  Pin * otherPin = 0;
  while (connection = connections[index++])
    if (otherPin = connection->OtherPin (pin))
	  break;  
	  
  return otherPin;	
}

// All pins should be updated before this procedure is caled
void ConnectedComponent::DeleteConnections()
{
  int index = 0;
  Connection * connection;
  while (connection = connections[index])
  {
    delete (connection);
    connections[index]=0;
    index++;
  }
}

// All pins should be updated before this procedure is caled
void ConnectedComponent::Move()
{
  int index = 0;
  Connection * connection;
  while (connection = connections[index++])
    connection->Move ();
}

Connection * ConnectedComponent::FindConnection (Pin * pin)
{
  HighLevelMenu * parent = (HighLevelMenu *)diagram;
  return parent->FindConnection (pin);
}

Connection * ConnectedComponent::FindConnect (Pin * pin)
{
  int index = 0;
  Connection * conn = 0;
  Connection * connection;
  int numConn = numConnections;
  while (connection = connections[index++])
  {
  	if ((connection->pin1 == pin) || (connection->pin2 == pin))
  	{
  	  conn = connection;
  	  break;
  	}
  }
  return conn;  
}

void ConnectedComponent::Paint (HDC _hdc, PAINTSTRUCT _ps, HDC _hdcMemory)
{
  Connection * connection;
  int index = 0;
  
  Component::Paint (_hdc, _ps, _hdcMemory);
  
  while (connection = connections[index++])
  {
  	connection ->Paint(hdc, ps, hdcMemory );
  }
  
}
void ConnectedComponent::Init (HWND _windowHandle, HINSTANCE _g_hInst, char * resource) {
  Component::Init (_windowHandle, _g_hInst, resource);
  // TODO: Call Init for the connection or maybe do this when created
}


void ConnectedComponent::Connect (Pin * pin1, Pin * pin2)
{
  int value;
  int resistance;
  connections[numConnections] = new Connection (pin1,pin2);
  connections[numConnections]->Init (windowHandle, g_hInst);
  
  pin1->Select (false); 
  pin2->Select (false);
  pin1->SetConnection (connections[numConnections]);
  pin2->SetConnection (connections[numConnections++]); 

  HighLevelMenu::Instance()->BestValue(pin1,pin2,value,resistance);	
  HighLevelMenu::Instance()->WriteValue (pin1,value,resistance,false);
}

void ConnectedComponent::SaveConnections (FILE * fp)
{
  Connection * connection;
  int index = 0;
  
  while (connection = connections[index++])
  	connection ->SaveConnection (fp);
}
