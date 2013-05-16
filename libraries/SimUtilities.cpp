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
  connections[0] = 0;
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

int SimUtilities::NumConnections (Pin * pin)
{
  MakeConnectionList (pin);	
  return numConnections;
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
  
  MakeConnectionList (pin);
  while (connection = connections[index++])
  {
  	pin1 = connection->pin1;
  	pin2 = connection->pin2;
  	
  	pin1->value.value = value;
  	pin1->value.resistance = resistance;
  	pin2->value.value = value;
  	pin2->value.resistance = resistance;
  }
}

Connection * SimUtilities::GetConnection (int index)
{
  return connections[index];
}

void SimUtilities::MakeConnectionList ( Pin * pin)
{
  numConnections = 0;
  connections[0] = 0;
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
  	    if ((connection->pin1 == pin)|| (connection->pin2 == pin))
  	    {
  	  	  // Add pin to list
  	  	  if (numConnections < MAXCONNECTIONS - 1)
  	  	  {
  	  	    connections[numConnections++] = connection;	
  	  	    connections[numConnections] = 0;
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

