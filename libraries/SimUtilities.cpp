#include "SimUtilities.h"
#include "SerialClass.h"
#include "HighLevelMenu.h"
#include "ConnectedComponent.h"
#include "Connection.h"

static SimUtilities * simUtilities;
SimUtilities::SimUtilities ()
{
  simUtilities = this;
  numConnections = 0;
  numPins = 0;
  for (int i=0; i<MAXCONNECTIONS; i++)
  {
    connections[i] = 0;
    pins[i]=0;
  }
}

void SimUtilities::UpdateSystem()
{
  int index = 0;
  HighLevelMenu * highLevelMenu = HighLevelMenu::Instance();
  ConnectedComponent * component;  
  while (component = highLevelMenu->components[index])
  {
  	component->Update();
  	index++;
  }  	
}

void SimUtilities::ClearConnections()
{
  int index = 0;
  Connection * connection;
  while (connection = connections[index])
  {
    pins[index]=0;	
  	connections[index++] = 0;
  }
  numConnections = 0;
  numPins = 0;
}

SimUtilities::~SimUtilities()
{
  ClearConnections();
}

SimUtilities * SimUtilities::Instance()
{
  return simUtilities;
}

bool SimUtilities::ConnectionInList (Connection * connection)
{
  int index = 0;
  bool found = false;
  
  while (connections[index])
    if (connections[index] == connection)
      break;
    else
      index++;
      
  if (connections[index]==connection)
    found = true;
     
  return found;
}

bool SimUtilities::PinInList (Pin * pin)
{
  int index = 0;
  bool found = false;
  
  while (pins[index])
    if (pins[index] == pin)
      break;
    else
      index++;
      
  if (pins[index]==pin)
    found = true;
     
  return found;
}

int SimUtilities::NumConnections (Pin * pin)
{
  MakeConnectionList (pin);	
  return numConnections;
}

/*
   Return true if the connection list has a constant value in the list
*/
bool SimUtilities::HasConstantValue (int & value, int & resistance)
{
  Pin * pin1;
  Pin * pin2;
  int val = -1;
  int resist = 1000000;
  int index = 0;
  Connection * connection;
  bool hasConstant = false;
  
  while (connection = connections[index])
  {
  	pin1 = connection->pin1;
  	if (pin1->constValue.value != -1)
  	  if (pin1->constValue.resistance <= resist)
  	  {
  	  	resist = pin1->constValue.resistance;
  	  	val = pin1->constValue.value;
  	  }
  	  
  	pin2 = connection->pin2;
  	if (pin2->constValue.value != -1)
	  if (pin2->constValue.resistance <= resist)
	  {
	  	resist = pin2->constValue.resistance;
	  	val = pin2->constValue.value;
	  }  
	  
    index++;
  }
  value = -1;
  resistance = 1000000;
  if (val != -1)
  {
    hasConstant = true;
    value = val;
    resistance = resist;
  }
  return hasConstant;  	
}

void SimUtilities::ViewConnections (HDC hdc)
{
  int index = 0;
  int y=0;
  char * name;
  char value[10];
  Connection * connection;
  
  while (connection = connections[index])
  {
  	name = connection->pin1->name;
    TextOut (hdc,  10, y,name,strlen(name));
    
    name = connection->pin2->name;
    TextOut (hdc, 100, y,name,strlen(name));
    
    if (connection->pin1->GetValue() == -1)
      y = y;
      
    itoa (connection->pin1->GetValue(), value, 10);
    TextOut (hdc, 190, y, value, strlen (value));
    
    itoa (connection->pin2->GetValue(), value, 10);
    TextOut (hdc, 280, y, value, strlen (value));
    y += 20;
    index++;
  }
}

void SimUtilities::ShowConnections (Pin * pin)
{
  Connection * connection;
  ConnectedComponent * component = 0;
  int index = 0;
  int head;
  char * charName;
  bool first;
  HighLevelMenu * highLevelMenu = HighLevelMenu::Instance();
  SerialClass * serialClass = SerialClass::Instance();
  Pin * pin1;
  Pin * pin2;
    
  serialClass->print ("\nShow connections to ");
  serialClass->println (pin->name);
  MakeConnectionList (pin);
  
  while (component = highLevelMenu->components[index++])
  {
  	first = true;
  	head = 0;
  	while (connection=component->connections[head++])
  	{
	  if (ConnectionInList(connection))
  	  {  	
		pin1 = connection->pin1;
		pin2 = connection->pin2;  
        if (first)
	    {
          serialClass->println (component->componentType); 
          first = false;
	    }
	    serialClass->print ("  ");
        serialClass->print ( pin1->name);
        serialClass->print ( "<->" );
        serialClass->println ( pin2->name);
  	  }
  	}
  }   
}

void SimUtilities::WriteValue ( Pin* pin, int value, int resistance)
{
  Connection * connection;
  Pin * pin1;
  Pin * pin2;
  int index = 0;
  char * name1;
  char * name2;
  
  MakeConnectionList (pin);
  while (connection = connections[index++])
  {
  	pin1 = connection->pin1;
  	pin2 = connection->pin2;
  	name1 = pin1->name;
  	name2 = pin2->name;
  	
  	pin1->value.value = value;
  	pin1->value.resistance = resistance;
  	pin2->value.value = value;
  	pin2->value.resistance = resistance;
  }
}

void SimUtilities::WritePinValue ( Pin* pin, int value, int resistance)
{
  Pin * p;
  int index = 0;
  char * name;
  int num;
  
  MakeConnectionList (pin);
  num = numPins;
  while (p = pins[index++])
  {
  	name = p->name;  	
  	p->value.value = value;
  	p->value.resistance = resistance;
  }
}

Connection * SimUtilities::GetConnection (int index)
{
  return connections[index];
}

void SimUtilities::MakeConnectionList ( Pin * pin)
{
  ClearConnections();
  MakeList (pin);
}

void SimUtilities::MakeList ( Pin * pin)
{
  Connection * connection;
  ConnectedComponent * component = 0;
  int index = 0;
  int head;
  HighLevelMenu * highLevelMenu = HighLevelMenu::Instance();
  SerialClass * serialClass = SerialClass::Instance();
    
  while (component = highLevelMenu->components[index++])
  {
  	head = 0;
  	while (connection=component->connections[head++])
  	{
	  if (!ConnectionInList(connection))
  	  {  	  
  	    if (((connection->pin1 == pin)|| (connection->pin2 == pin)) || !pin)
  	    {
  	  	  // Add pin to list
  	  	  if (numConnections < MAXCONNECTIONS - 1)
  	  	  {
  	  	    connections[numConnections++] = connection;	
  	  	    connections[numConnections] = 0;
  	  	    if (!PinInList (connection->pin1))
  	  	      pins[numPins++]=connection->pin1;
  	  	      
  	  	    if (!PinInList (connection->pin2))
  	  	      pins[numPins++]=connection->pin2;
  	  	    
	        if (pin == connection->pin1)
	          MakeList (connection->pin2);
	        else
	          MakeList (connection->pin1);
	      }
	    }
  	  }
  	}
  }	
}
