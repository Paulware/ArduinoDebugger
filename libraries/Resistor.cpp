#include "Resistor.h"
#include "HighLevelMenu.h"
#include "SimUtilities.h"
Resistor::Resistor(int _x, int _y, int _resistance, Component * _diagram):ConnectedComponent(_x,_y,_diagram)
{ 
  input = new Pin(this);
  output = new Pin(this);
  input->xOffset = 0;
  input->yOffset = 5;
  output->xOffset = 67;
  output->yOffset = 5; 
  x = _x;
  y = _y;
  input->x = x + input->xOffset;
  input->y = y + input->yOffset;    
  output->x = x + output->xOffset;
  output->y = y + output->yOffset; 
  input->SetName ("Left");
  output->SetName ("Right");  
  SaveType ("Resistor");  
  resistance = _resistance;  
  input->constValue.resistance = resistance;
  input->value.resistance = resistance;    
  output->constValue.resistance = resistance;
  output->value.resistance = resistance; 
  
  // Create a virtual connections between input and output.
  connections[numConnections++] = new Connection ( input, output); 
}

Resistor::~Resistor()
{
  delete (input);
  delete (output);
  DeleteConnections();  
}

void Resistor::IsConnected (Pin * localPin, Pin * remotePin)
{
  int value;
  int resistance;
  
  Connection * connection;
  HighLevelMenu * highLevelMenu = (HighLevelMenu *) diagram;
  if (remotePin->constValue.value != -1)
  {
  	input->constValue.value = remotePin->constValue.value;
  	input->value.value = remotePin->constValue.value;
  	connection = highLevelMenu->FindConnection (input);
    HighLevelMenu::Instance()->BestValue(input,output,value,resistance);	
    SimUtilities::Instance()->WriteValue (input,value,resistance);
  }  
}

void Resistor::Connect (Pin * pin1, Pin * pin2)
{
   ConnectedComponent::Connect(pin1, pin2);
   IsConnected (pin1,pin2);
}

Pin * Resistor::PinActive ()
{
  Pin * pin = 0;
  if (input->isActive)
    pin = input;
  else if (output->isActive)
    pin = output;
  return pin;
}

// Check if the mouse has moved over one of the ports.
void Resistor::HandleMouseMove (HWND hWnd, int _x, int _y)
{
  ConnectedComponent::HandleMouseMove (hWnd,_x,_y);
  input->HandleMouseMove  (hWnd, _x, _y );
  output->HandleMouseMove (hWnd, _x, _y );  
  input->value.resistance = resistance;
  output->value.resistance = resistance;
}

Pin * Resistor::FindPort ( char * port)
{
  Pin * pin = 0;
  if (!strcmp (port,"Left"))
    pin = input;
  if (!strcmp(port,"Right"))
    pin = output;
  return pin;    
}

void Resistor::SaveYourself (FILE * fp)
{
  fprintf ( fp, "Resistor%d,%d,%d",resistance,x,y);
}

void Resistor::HandleMouseDown (HWND hWnd, int _x, int _y)
{
  int value;
  int resistance;
  Connection * inConnection = FindConnection (input);
  Connection * outConnection = FindConnection (output);
  
  if (input->isActive) // we are over the ground spot     
    input->Select(!input->isSelected);
  else if (output->isActive)
    output->Select(!output->isSelected);  
  else
  {
    HighLevelMenu::Instance()->BestValue(input,output,value,resistance);	
    SimUtilities::Instance()->WriteValue (input,value,resistance);  	
  }  
}

void Resistor::SaveConnections (FILE * fp)
{
  Connection * connection;
  Pin * pin1;
  Pin * pin2;
  int index = 0;
  
  while (connection = connections[index])
  {
  	pin1 = connections[index]->pin1;
  	pin2 = connections[index]->pin2;
  	if ((pin1 == input)&&(pin2==output))
  	{
  	  // skip the virtual connection
  	}
  	else if ((pin1 == output) && (pin2 == input))
  	{
  	  // skip the virtual connection
  	}
  	else 
  	  connection->SaveConnection (fp);
  	index++;
  }
}

bool Resistor::IsSet()
{
  bool set = input->IsSet () && output->IsSet();
  return set;
}

void Resistor::Reset ()
{
  input->Reset();
  output->Reset();
}

void Resistor::HandleMouseUp (HWND hWnd)
{
  /*
  if ((hWnd == windowHandle) && !PinActive())
  {
    // Reset();
  }
  */
}

void Resistor::AddMenu ()
{
  HMENU  MainMenu;
  HMENU  FileMenu;
     
  MainMenu=CreateMenu();
  FileMenu=CreateMenu();
  InsertMenu(MainMenu,ID_Edit,MF_POPUP,(UINT_PTR)FileMenu,"Help");
  AppendMenu(FileMenu,MF_STRING,DEPRESSSWITCH_ABOUT,"&About");
  AppendMenu(FileMenu,MF_SEPARATOR,0,"");
  AppendMenu(FileMenu,MF_STRING,DEPRESSSWITCH_WIRE,"&How to Wire");
  //  activate menu 
  (void) SetMenu(windowHandle,MainMenu);
}

void Resistor::Paint(HDC _hdc, PAINTSTRUCT _ps, HDC _hdcMemory)
{     
  ConnectedComponent::Paint (_hdc, _ps, _hdcMemory);  
    
  // Paint the pins (This is why virtual function is necessary)  
  input->Paint(hdc, ps, hdcMemory);
  output->Paint(hdc, ps, hdcMemory);
}

void Resistor::Init (HWND _windowHandle, HINSTANCE _g_hInst, char * resource)
{   
   ConnectedComponent::Init ( _windowHandle, _g_hInst, resource);
   output->Init (windowHandle, g_hInst);
   input->Init (windowHandle, g_hInst);   
}

Pin * Resistor::PortSelected(){
  Pin * pin = 0;
  if (input->isSelected)
  	pin = input;
  if (output->isSelected)
  	pin = output;
  return pin;  
}

// [_x,_y] are absolute values
void Resistor::MoveTo (int _x, int _y)
{	
  x = _x-xOffset;
  y = _y-yOffset; // Get the x location of the LED after adjusting for mouse click location
  input->MoveTo (x + input->xOffset, 
                 y + input->yOffset);
  output->MoveTo (x + output->xOffset,
                  y + output->yOffset);   
  // Move connections
  ConnectedComponent::Move ();                   
}

