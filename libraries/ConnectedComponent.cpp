#include "ConnectedComponent.h"
#include "HighLevelMenu.h"
#include "SimUtilities.h"
ConnectedComponent::ConnectedComponent(int _x, int _y, Component * _diagram):Component()
{
  x = _x;
  y = _y;
  for (int i=0; i<CONNECTIONSPERCOMPONENT; i++)
    connections[i] = 0;
  numConnections = 0;
  diagram = _diagram; // Save the parent diagram
  numTempConnections = 0;
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

void ConnectedComponent::AddTempConnector ( Pin * pin1, Pin * pin2)
{
  int value;
  int resistance;
  Connection * connection;
  // Create a new "virtual" connection
  connection = new Connection (pin1, pin2);  // pin01 and pin02 are connected
  connections[numConnections++] = connection; 	
  HighLevelMenu::Instance()->BestValue(pin1,pin2,value,resistance);	
  SimUtilities::Instance()->WriteValue (pin1,value,resistance);
  numTempConnections++;
}

void ConnectedComponent::ClearTemporaryConnections()
{
  Connection * connection;
  Pin * pin1;
  Pin * pin2;
  int index = numConnections - 1;
  HighLevelMenu * highLevelMenu = HighLevelMenu::Instance();
  if (numTempConnections)
  {
  	for (int i=0; i<numTempConnections; i++)
  	{
  	  connection = connections[index];
  	  pin1 = connection->pin1;
  	  pin2 = connection->pin2;
  	  connections[index]=0;
  	  delete (connection);
  	  highLevelMenu->ResetConnectionPins (pin1);	
  	  highLevelMenu->ResetConnectionPins (pin2);	
  	  index--;
  	  numConnections--;
  	}
  }
  numTempConnections = 0;
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
  
  if (pin1->constValue.value != -1)
  {
  	pin2->constValue.value = pin1->constValue.value;
  	pin2->constValue.resistance = pin1->constValue.resistance;
  }
  else if (pin2->constValue.value != -1)
  {
  	pin1->constValue.value = pin2->constValue.value;
  	pin1->constValue.resistance = pin2->constValue.resistance;
  }
  HighLevelMenu::Instance()->BestValue(pin1,pin2,value,resistance);	
  SimUtilities::Instance()->WriteValue (pin1,value,resistance);
}

void ConnectedComponent::SaveConnections (FILE * fp)
{
  Connection * connection;
  int index = 0;
  
  ClearTemporaryConnections();
  
  while (connection = connections[index++])
  	connection ->SaveConnection (fp);
}
