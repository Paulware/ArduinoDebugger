#include "HighLevelMenu.h"
#include "Menus.h"
#include "Led.h"
#include "MomentaryDepress.h"
#include "SevenSeg.h"
#include "LCDDisplay.h"
#include "ArduinoComponent.h"
#include "Resistor.h"
#include "KeypadDevice.h"
#include "Pot.h"
#include "Connection.h"
#include "Digit3.h"
#include "RotaryDip.h"
#include "SimUtilities.h"
#include "ShiftRegister.h"
#include "Multiplexer.h"
#include <Commdlg.h>

static HighLevelMenu * highLevelMenu;

class OpenFileDialog {
  public: 
    OpenFileDialog (){};
	  
    void Open (const char * filter)
    {
      // open a file name
      ZeroMemory( &ofn , sizeof( ofn));
      ofn.lStructSize = sizeof ( ofn );
      ofn.hwndOwner = NULL  ;   
	  ofn.lpstrFile = szFile ;
   	  ofn.lpstrFile[0] = '\0';
	  ofn.nMaxFile = sizeof( szFile );
	  // ofn.lpstrFilter = "All\0*.*\0Text\0*.TXT\0";
	  //ofn.lpstrFilter = "Text\0*.TXT\0";
	  ofn.lpstrFilter=filter;
	  ofn.nFilterIndex =1;
	  ofn.lpstrFileTitle = NULL ;
	  ofn.nMaxFileTitle = 0 ;
	  ofn.lpstrInitialDir=NULL ;
	  ofn.Flags = OFN_PATHMUSTEXIST|OFN_FILEMUSTEXIST ;
	  GetOpenFileName( &ofn );
	  // Now simpley display the file name 
	  // MessageBox ( NULL , ofn.lpstrFile , "File Name" , MB_OK);
	};
	  
	void Save (const char * filter)
	{
      // open a file name
	  ZeroMemory( &ofn , sizeof( ofn));
	  ofn.lStructSize = sizeof ( ofn );
      ofn.hwndOwner = NULL  ;   
	  ofn.lpstrFile = szFile ;
   	  ofn.lpstrFile[0] = '\0';
	  ofn.nMaxFile = sizeof( szFile );
	  ofn.lpstrFilter=filter;
	  ofn.nFilterIndex =1;
	  ofn.lpstrFileTitle = NULL ;
	  ofn.nMaxFileTitle = 0 ;
	  ofn.lpstrInitialDir=NULL ;
	  ofn.Flags = OFN_PATHMUSTEXIST;
	  GetSaveFileName( &ofn );
	}
	char * Filename ()
	{
	  return &szFile[0];
	}
	
	private:
  	  OPENFILENAME ofn ;
  	  char szFile[100] ;
};


class String{
   private:
      char * pString;
   public:
      String(){ pString = 0;}
      
      char * Me () { 
        return pString;
      }
      
      String( char * s )
	  {
	    int len = strlen (s);
		pString = (char *)calloc (len +1, sizeof (char));
		strcpy (pString, s); 
	  }
      void display() // const
	  { 
	    MessageBox (0,pString,"show",0); 
	  }
	  
	  int Len () {
	  	return strlen(pString);
	  }
      //void getstr(){ cin.get(str, SZ); }
      bool operator == (String str) const{
      	bool match = false;
      	if (!strcmp (pString, str.pString))
      	  match = true;
      	return match;
      }
      
      String& operator+(char ch)
      {
      	char * append;
    	append = (char *)calloc (Len() + 1 + 1, 1);
      	strcpy (append,pString);
      	append[Len()] = ch; // Append the character
      	delete (pString);
      	pString = append;      	
      }
      
      String& operator+(String &Str)
      {
      	char * append;
      	if (Str.Len())
      	{
      	  append = (char *)calloc (Len() + Str.Len() + 1, 1);
      	  strcpy (append,pString);
      	  strcpy (&append[Len()],Str.Me());
      	  delete (pString);
      	  pString = append;
      	}      	
      }
      
      String& operator=(const String& Str) 
	  {
	  	int len;
        if(this != &Str)
        {
		  len = strlen (Str.pString);
          if (pString)
            delete (pString);
          pString = (char *)calloc (len+1, sizeof (char));
          //std::
		  strcpy (pString, Str.pString);          
        }

      return *this;
      }    
   };

//String * temp = new String ( "Hello");
//int len = temp->Len();
const int MAXCHARS = 25;
typedef char LineType[MAXCHARS];
struct LineInfo
{
  LineType component1;
  int x1;
  int y1;
  LineType port1;
  
  LineType component2;
  int x2;
  int y2;
  LineType port2;
  bool newData;
  bool readingComponent;
  bool readingSource;
};

LineInfo DefaultLine ()
{
  LineInfo line;
  strcpy (line.component1,"");
  line.x1 = 0;
  line.y1 = 0;
  strcpy (line.port1,"");
  strcpy (line.component2,"");
  line.x2 = 0;
  line.y2 = 0;
  strcpy (line.port2,"");
  line.newData = false;
  line.readingComponent = false;
  line.readingSource = false;
  return line;
}

void GetLine ( FILE * fp, char * line, int lineLength)
{
  char ch = 0;	
  int len = 0;
  line[0]=0;
  while (!feof(fp) && (ch != 13) && (ch != 10))
  {
  	ch = fgetc (fp);
  	if ((ch == 13) || (ch == 10) || (ch == -1))
  	  break;
	if ((len + 1) < lineLength)
  	{
  	  line[len++]=ch;
  	  line[len]=0;
    }
  }
}

void GetToken ( FILE * fp, char * line)
{
  char ch = 0;	
  int len = 0;
  line[0]=0;
  while (!feof(fp))
  {
  	ch = fgetc (fp);
  	if ((ch == ',') || (ch == '\n') || (ch == -1))
  	  break;
  	else
  	{
  	  line[len++]=ch;
  	  line[len]=0;
    }
  }
}

void ReadLine (FILE * fp, LineInfo & line, bool & readingComponents, bool & readingSource)
{
  char token[MAXCHARS];
  char filename[255];
  GetToken (fp,&token[0]);
  line = DefaultLine ();
  line.readingComponent = readingComponents;
  line.readingSource = readingSource;
  if (strlen(token))
  {
    line.newData = true;  
    if (!strcmp(token,"Project Components")) // First line of the file
    {
      readingComponents = true;
      readingSource = false;
    }
    else if (!strcmp(token,"Project Connections"))	
      readingComponents = false;
    else if (!strcmp(token,"Project Source"))
    {
      readingSource = true;
      line.readingSource = true;
    }
    else if (readingSource)
    {
    }
    else if (readingComponents)
    { 
      strcpy (line.component1, token);
      GetToken (fp,&token[0]); // x
      line.x1 = atoi (&token[0]);
      GetToken (fp,&token[0]); // y
      line.y1 = atoi (&token[0]);	
    }
    else // Reading Connections
    {
      strcpy ( line.component1, token);
      GetToken (fp,&token[0]); // x
      line.x1 = atoi (&token[0]);
      GetToken (fp,&token[0]); // y
      line.y1 = atoi (&token[0]);
      GetToken (fp,&token[0]); // portName
      strcpy (line.port1, token);
      GetToken (fp,&token[0]); // Component
      strcpy (line.component2, token); 
      GetToken (fp,&token[0]); // x
      line.x2 = atoi(&token[0]);
      GetToken (fp,&token[0]); // y
      line.y2 = atoi(&token[0]);
      GetToken (fp,&token[0]); // portName
      strcpy (line.port2, token); 
    }
  }
}

bool FilesDifferent ( char * filename1, char * filename2)
{
  bool different = false;
  FILE * file1;
  FILE * file2;
  
  char line1 [255];
  char line2 [255];
 
  file1 = fopen (filename1,"r");
  file2 = fopen (filename2,"r");
  
  while (!feof(file1) && !feof(file2))
  {
    GetLine (file1, line1, sizeof (line1));
    GetLine (file2, line2, sizeof (line2));
    if (strcmp (line1,line2)) // Lines are different
    {
      different = true;
      break;
    } 
  }
  
  fclose(file1);
  fclose(file2);
  
  return different;
}



void FPrintF ( FILE * outFile, char * line)
{
  int len = strlen (line);	
  char oneCh[] = " ";
  char ch;
  
  for (int i=0;i<len; i++)
  {
  	ch = line[i];
  	oneCh[0] = ch;
    if (ch == '%')
      fprintf (outFile, "%%");
    else if (ch == '\\')  
      fprintf (outFile, "\\");
    else 
      fprintf (outFile, oneCh);
  }
}

void CopyFile ( char * inFilename, char * outFilename)
{
 char sourceLine[255];
 FILE * outFile;
 FILE * inFile;
 
 inFile = fopen (inFilename,"r");
 outFile = fopen (outFilename, "w"); // Open sketch filename for output
	   	
 while (!feof(inFile))
 {
   GetLine (inFile, sourceLine, sizeof (sourceLine));
   if (strlen (sourceLine))
   	 FPrintF (outFile, sourceLine);
   	 
   fprintf (outFile, "\n");	
 }
 fclose(outFile);
 fclose(inFile);
}

/*****************************  Class Procedures **********************************/

HighLevelMenu::HighLevelMenu(ViewConnections * _viewConnections):Component()
{ 
  numComponents = 0; 
  readingProject = false; 
  selectedItem = -1;
  for (int i=0; i<MAX_COMPONENTS; i++)
  	components[i] = 0;
  
  viewConnections = _viewConnections;
  strcpy(projectFilename,"");
  highLevelMenu = this;
  
  ComponentNames.push_back ("Arduino");
  ComponentNames.push_back ("Led");
  ComponentNames.push_back ("MomentaryDepress");
  ComponentNames.push_back ("Resistor10000");
  ComponentNames.push_back ("LCDDisplay");
  ComponentNames.push_back ("Keypad");
  ComponentNames.push_back ("Seven Segment");
  ComponentNames.push_back ("Resistor220");
  ComponentNames.push_back ("Pot");
  ComponentNames.push_back ("Digit3");
  ComponentNames.push_back ("RotaryDip");
  ComponentNames.push_back ("ShiftRegister");
  ComponentNames.push_back ("Multiplexer");
  timerCount = 0;
  strcpy ( sourceFilename,"");  
}

HighLevelMenu::~HighLevelMenu()
{

  ConnectedComponent * component;
  
  int index = 0;
  index = 0;
  while (component = components[index++])
    delete (component);	
}

// Singleton pointer to class
HighLevelMenu * HighLevelMenu::Instance()
{
  return highLevelMenu;
}

Pin * HighLevelMenu::FindOtherPin ( Pin * pin)
{
  Pin * otherPin;
  int index = 0;
  int found = -1;
  ConnectedComponent * component = 0;
  
  while (component=components[index])
  {
    if (otherPin = component->FindOtherPin (pin))
    {      
      found = index;
      break;
    }
    index++;
  }    
  return otherPin;	
}

void HighLevelMenu::TroubleshootPins ()
{
  int index = 0;
  ConnectedComponent * component;
  bool ok = true;
  
  while ((component=components[index++]) && ok)
    ok = component->TroubleshootPins();

  if (ok)      
    MessageBox (0,"Could not detect wiring issues", "Done Troubleshooting Pins", 0);    
}

ConnectedComponent * HighLevelMenu::FindComponent ( char * typeName)
{
  int index = 0;
  ConnectedComponent * component = 0;
  ConnectedComponent * conn = 0;
  
  while (component=components[index])
  {
    if (!strcmp ( component->componentType, typeName))
    {
      conn = component;
      break;
    }
    index++;
  }
    
  return conn;
}

int HighLevelMenu::DigitalRead(int pin)
{
  int value = -1;
  ArduinoComponent * arduino;
  
  if (arduino = (ArduinoComponent *)FindComponent ( "Arduino"))
    value = arduino->d[pin]->GetValue();
    
  if (value == 1)
    value = 1;  
    
  return value; 	
}
void HighLevelMenu::ResetConnectionPins (Pin * pin)
{
  ConnectedComponent * component;
  Connection * connection;
  char * n = pin->name;
  Pin * pin1;
  Pin * pin2;
  char * name1;
  char * name2;
  char * tName;
  
  int index = 0;
  int connectionIndex;
  // For all the components on the diagram
  while (component = components[index++])
  {
  	tName = &component->componentType[0];
  	
  	// For all the connections this component has
  	connectionIndex = 0;
  	while ( connection = component->connections[connectionIndex++])
  	{  	  
  	  pin1 = connection->pin1;
  	  pin2 = connection->pin2;
  	  if (pin == pin1)
  	  {
  	  	if (pin1->constValue.value != -1)
  	  	{
  	  	  if (pin1->value.value != pin1->constValue.value)
  	  	  {
  	  	  	pin1->value.value = pin1->constValue.value;
  	  	  	pin1->value.resistance = pin1->constValue.resistance;
  	  	  	ResetConnectionPins (pin2);
  	  	  }
  	  	}
  	  	else if (pin1->value.value != -1)
  	  	{
  	  	  pin->value.value = -1;
  	  	  pin->value.resistance = -1;
  	  	  ResetConnectionPins (pin2);
  	  	}
      }
      else if (pin == pin2)
      {
  	  	if (pin2->constValue.value != -1)
  	  	{
  	  	  if (pin2->value.value != pin2->constValue.value)
  	  	  {
  	  	  	pin2->value.value = pin2->constValue.value;
  	  	  	pin2->value.resistance = pin2->constValue.resistance;
  	  	  	ResetConnectionPins (pin1);
  	  	  }
  	  	}
      	else if (pin2->value.value != -1)
      	{
      	  pin->value.value = -1;
      	  pin->value.resistance = -1;
      	  ResetConnectionPins (pin1);
      	}
      }
  	}
  }
}

/* 
   Determine what is the best value when 2 pins are connected 
*/
void HighLevelMenu::BestValue (Pin * pin1, Pin * pin2, int & value, int & resistance)
{
  char * name1 = pin1->name;
  char * name2 = pin2->name;
  
  value = -1;
  resistance = -1;
  if (pin1->constValue.value != -1)
  {
  	value = pin1->constValue.value;
  	resistance = pin1->constValue.resistance;
  }
  else if (pin2->constValue.value != -1)
  {
  	value = pin2->constValue.value;
  	resistance = pin2->constValue.resistance;
  }
  else if (pin1->value.value == -1)
  {
  	value = pin2->value.value;
  	resistance = pin2->value.resistance;
  }
  else if (pin2->value.value == -1)
  {
  	value = pin1->value.value;
  	resistance = pin1->value.resistance;
  }
  
  if (value == -1) // Still no value
  {
  	if (pin1->value.resistance < pin2->value.resistance)
    {
   	  value = pin1->value.value;
      resistance = pin1->value.resistance;
    }
    else if (pin2->value.resistance < pin1->value.resistance)
    {
      value = pin2->value.value;
      resistance = pin2->value.resistance;
    }
  }
  
  if (value == -1) // Still no value
  {
  	if (pin1->value.value != -1)
    {
   	  value = pin1->value.value;
      resistance = pin1->value.resistance;
    }
    else
    {
   	  value = pin2->value.value;
      resistance = pin2->value.resistance;
    }
  }
}

void HighLevelMenu::DigitalWrite(int pin, int value)
{
  ArduinoComponent * arduino;
  int resistance;
  
  if (arduino = (ArduinoComponent *)FindComponent ( "Arduino"))
  {
	resistance = arduino->d[pin]->GetResistance();  
	ResetConnectionPins (arduino->d[pin]);
	
	// Write to all related connections
    SimUtilities::Instance()->WriteValue (arduino->d[pin], value, resistance);
  }
}

void HighLevelMenu::lcdPrint(char * line)
{
  LCDDisplay * lcdDisplay;
  
  if (lcdDisplay = (LCDDisplay *)FindComponent ( "LCDDisplay"))
    lcdDisplay->print(line);
}

void HighLevelMenu::lcdClear()
{
  LCDDisplay * lcdDisplay;
  
  if (lcdDisplay = (LCDDisplay *)FindComponent ( "LCDDisplay"))
    lcdDisplay->clear();
}

void HighLevelMenu::lcdPrint ( int value)
{
  LCDDisplay * lcdDisplay;
  
  if (lcdDisplay = (LCDDisplay *)FindComponent ( "LCDDisplay"))
    lcdDisplay->print(value);
}

void HighLevelMenu::AddMenu ()
{     
  HMENU  MainMenu, hAddMenu, hSaveMenu, hResistorMenu, hProjectMenu, hViewMenu,
         hFileMenu, hTroubleShootMenu;
  
  MainMenu = CreateMenu();
  SetMenu (windowHandle, MainMenu); 
  
  hTroubleShootMenu = CreatePopupMenu();
  InsertMenu (MainMenu, 0,         MF_POPUP|MF_BYPOSITION, (UINT_PTR)hTroubleShootMenu, "Trouble Shoot");
  AppendMenu (hTroubleShootMenu,   MF_STRING, TROUBLESHOOTCONNECTIONS,             "Connections" );
    
  hAddMenu = CreatePopupMenu();
  InsertMenu (MainMenu, 0,         MF_POPUP|MF_BYPOSITION, (UINT_PTR)hAddMenu, "Add");
  AppendMenu (hAddMenu, MF_STRING, ADDPOT,             "Pot" );
  AppendMenu (hAddMenu, MF_STRING, ADDLED,             "Led" );
  AppendMenu (hAddMenu, MF_STRING, ADDMOMENTARYSWITCH, "Depress Switch");
  AppendMenu (hAddMenu, MF_STRING, ADDSEVENSEGMENT,    "7Segment Display");
  AppendMenu (hAddMenu, MF_STRING, ADDLCDDISPLAY,      "LCD Display");
  AppendMenu (hAddMenu, MF_STRING, ADD4X4KEYPAD,       "4x4 Keypad");
  AppendMenu (hAddMenu, MF_STRING, ADDARDUINO,         "Arduino");
  AppendMenu (hAddMenu, MF_STRING, ADDDIGIT3,          "3 Digit Display");
  AppendMenu (hAddMenu, MF_STRING, ADDROTARYDIP,       "Rotary Dip Switch");
  AppendMenu (hAddMenu, MF_STRING, ADDSHIFTREGISTER,   "74HC595 Shift Register");
  AppendMenu (hAddMenu, MF_STRING, ADDMULTIPLEXER,     "4051 Multiplexer");
    
  hResistorMenu = CreatePopupMenu();
  InsertMenu (hAddMenu, 0,         MF_POPUP|MF_BYPOSITION, (UINT_PTR)hResistorMenu, "Resistor");
  AppendMenu (hResistorMenu, MF_STRING, ADDRESISTOR220,        "220 ohm");
  AppendMenu (hResistorMenu, MF_STRING, ADDRESISTOR10K,        "10k ohm");
    
  hViewMenu = CreatePopupMenu();
  AppendMenu (hViewMenu, MF_STRING, VIEWARDUINOCONNECTIONS, "Arduino Connections");
  InsertMenu ( MainMenu, 0, MF_POPUP|MF_BYPOSITION, (UINT_PTR)hViewMenu, "View");
    
  hProjectMenu = CreatePopupMenu();
  AppendMenu (hProjectMenu, MF_STRING, NEWPROJECT, "New Project");
  AppendMenu (hProjectMenu, MF_STRING, READPROJECT, "Open Project"); // OpenProject ReadProject
  AppendMenu (hProjectMenu, MF_STRING, SAVE, "Save");
  AppendMenu (hProjectMenu, MF_STRING, SAVEAS, "Save As");
  InsertMenu (MainMenu, 0,         MF_POPUP|MF_BYPOSITION, (UINT_PTR)hProjectMenu, "Project");
 
  hFileMenu = CreatePopupMenu(); 
  AppendMenu (hFileMenu, MF_STRING, 1005, "Exit");
  InsertMenu ( MainMenu, 0, MF_POPUP|MF_BYPOSITION, (UINT_PTR)hFileMenu, "File");
  
  //  activate menu 
  (void) SetMenu(windowHandle,MainMenu);
}

void HighLevelMenu::HandleMenu (int command)
{
  OpenFileDialog ofd;		
  switch (command)
  {
    case ADDLED: 
      AddComponent (1,"",0,0);
    break;
    
    case ADDMOMENTARYSWITCH:
      AddComponent (2,"",0,0);
    break;   
	 
    case ADDSEVENSEGMENT:
      AddComponent (6,"",0,0);
    break;  
    
    case ADDLCDDISPLAY:
      AddComponent (4,"",0,0);
    break;
    
    case ADD4X4KEYPAD:
      AddComponent (5,"",0,0);
    break;
	  
    case ADDARDUINO:
      AddComponent (0,"",0,0);
    break;
    
    case ADDDIGIT3:
      AddComponent (9,"",0,0);
    break;
    
    case ADDROTARYDIP:
      AddComponent (10,"",0,0);
    break;
    
    case ADDRESISTOR10K:
      AddComponent (3,"",0,0);
    break;
    
    case ADDRESISTOR220:
      AddComponent (7,"",0,0);
    break;
    
    case ADDPOT:
      AddComponent (8,"",0,0);
    break;
    
    case ADDSHIFTREGISTER:
      AddComponent (11,"",0,0);
    break;
    
    case ADDMULTIPLEXER:
      AddComponent (12,"",0,0);
    break;
    
	case SAVEAS:
	  ofd.Save("Text\0*.TXT");		
	  if (strlen (ofd.Filename()))
	    SaveProject (ofd.Filename());
	break;   	
    
    case VIEWARDUINOCONNECTIONS:
      viewConnections->DrawWindow (g_hInst);
    break; 
	
	case SAVE: 
	  SaveProject(projectFilename);
	break;
	
	case READPROJECT:
	  ofd.Open("Text\0*.TXT");		
	  if (ReadProject(ofd.Filename()))
        if (FilesDifferent ( sourceFilename, "sketch.ino"))
        {
          CopyFile (sourceFilename, "sketch.ino"); // Copy source to sketch.ino	  
  	      MessageBox (0,"You will need to rebuild the project since sketch.ino has changed", "Project Read", 0); 
        }
	break;
	
	case NEWPROJECT:
	  NewProject();
	break;
	
	case TROUBLESHOOTCONNECTIONS:
	  TroubleshootPins();
	break;	  
  }   
  Refresh();
}


ConnectedComponent * HighLevelMenu::FindComponent (int x, int y)
{
  int index = 0;
  ConnectedComponent * component;
  while (component = components[index++])
  {
  	if ((component->x == x) && (component->y == y))
  	{
  	  break;
  	}
  }
  return component;
}

void HighLevelMenu::NewProject()
{
  ConnectedComponent * component;
  int index = 0;
  // Delete all the components
  while (component = components[index])
  {
    InvalidateRect ( component->windowHandle, NULL, true ); // Invalidate old
    delete (component);
    components[index++] = 0;
  }
  numComponents = 0;
  Refresh();
  strcpy ( sourceFilename, "");	
}

int HighLevelMenu::FindComponentName (std::string str)
{
  int found = -1;
  
  if (!str.size())
    MessageBox (0,"Component name is null string", "FindComponentName",0);
  else  
    for (int i=0; i<ComponentNames.size(); i++)
  	  if (str == ComponentNames[i])
  	  {
  	    found = i;
  	    break;
  	  }
  
  return found;
}
Pin * HighLevelMenu::GetNextPin ( Pin * pin)
{
  Pin * startPin = pin;
  Pin * source = 0;
  ConnectedComponent * component;
  int index = 0;
  // Delete all the components
  while (component = components[index])
  {
    if (source = components[index++]->FindOtherPin (startPin))
    { // Found something connected to this pin
      break; // We found a potential source 
    }  
  }
  
  return source;
}

Connection * HighLevelMenu::FindConnection ( Pin * pin)
{
  ConnectedComponent * component;
  Connection * connection;
  Connection * conn=0;
  char * compName;
  int index = 0;
  
  while (component = components[index++])
  {
  	compName = &component->componentType[0];
  	if (connection=component->FindConnect(pin))
  	{
  	   conn = connection;
  	   break;
  	}
  }
  return conn;
}

void HighLevelMenu::AddComponent (int index, char * typeName, int x, int y)
{
  SevenSeg * sevenSegment;	
  ArduinoComponent * arduino;
  ConnectedComponent * component; 
  
  int componentIndex = index;
  if (componentIndex == -1)
    componentIndex = FindComponentName (typeName);
    
  switch (componentIndex)    
  {
    case 0:
   	  component = new ArduinoComponent ( x, y, this);
	  component->Init (windowHandle, g_hInst, "ARDUINOBMP");
	  components[numComponents++] = component;
      break;
    case 1:
      component = new Led ( x, y, this);
	  component->Init (windowHandle, g_hInst, "LEDBMP");
	  components[numComponents++] = component;
      break;
    case 2:
      component = new MomentaryDepress ( x, y, this);
	  component->Init (windowHandle, g_hInst, "MOMENTARYDEPRESS");
	  components[numComponents++] = component;
	  break;
	case 3:
      component = new Resistor ( x, y, 10000,this);
	  component->Init (windowHandle, g_hInst, "TENKOHMS");
	  components[numComponents++] = component;
      break;
      
    case 4:
      component = new LCDDisplay ( x, y, this);
	  component->Init (windowHandle, g_hInst, "LCDDISPLAY");
	  components[numComponents++] = component;
	  break;
	case 5:	
  	  component = new KeypadDevice (x,y,this);
	  component->Init (windowHandle, g_hInst, "KEYPAD");
	  components[numComponents++] = component;
  	  break;
  	case 6:
      component = new SevenSeg (x, y, this);
	  component->Init (windowHandle, g_hInst, "SEVENSEGMENT");
	  components[numComponents++] = component;
      break;  
	case 7:  
      component = new Resistor (x, y, 220, this);
	  component->Init (windowHandle, g_hInst, "TWOTWENTYOHMS");
	  components[numComponents++] = component;
      break;
    case 8:
      component = new Pot (x, y, this);
	  component->Init (windowHandle, g_hInst, "POT");
	  components[numComponents++] = component;
      break;
	case 9:	  // Add the 3 digit display 
	  component = new Digit3(x,y, this);
	  component->Init (windowHandle, g_hInst, "DIGIT3");
	  components[numComponents++] = component;
	  break;        
	case 10:
	  component = new RotaryDip(x,y, this);
	  component->Init (windowHandle, g_hInst, "ROTARYDIP0");
	  components[numComponents++] = component;
	  break;        
	case 11:	 
	  component = new ShiftRegister(x,y, this);
	  component->Init (windowHandle, g_hInst, "SHIFTREGISTER");
	  components[numComponents++] = component;
	  break;        
	case 12:	 
	  component = new Multiplexer(x,y, this);
	  component->Init (windowHandle, g_hInst, "MULTIPLEXER");
	  components[numComponents++] = component;
	  break;        
      /*
        arduino = (ArduinoComponent *)FindComponent ("Arduino");
        arduino->Connect (arduino->d[2], sevenSegment->segment[0], g_hInst);
        arduino->Connect (arduino->d[3], sevenSegment->segment[1], g_hInst);
        arduino->Connect (arduino->d[4], sevenSegment->segment[2], g_hInst);
        arduino->Connect (arduino->d[5], sevenSegment->segment[3], g_hInst);
        arduino->Connect (arduino->d[6], sevenSegment->segment[4], g_hInst);
        arduino->Connect (arduino->d[13], sevenSegment->segment[5], g_hInst);
        arduino->Connect (arduino->d[14], sevenSegment->segment[6], g_hInst);    
   	    arduino->Connect (arduino->gnd, sevenSegment->gnd, g_hInst);    
	  */
      
    default:
      MessageBox (0,typeName,"Unknown type requested",0);
	  break;
  }
}

void HighLevelMenu::HandleKeyUp ( int scanCode) 
{
  bool debug = false;
  char code[20];
  ConnectedComponent * component;
  Connection * connection;
  int index = 0;
  bool shifting = false;
  
  switch (scanCode)
  {
  	case 46:   
      while (component = components[index])
      {
        if (component->isActive && !shifting)
        {	
		  delete (component); // component will delete all connections
		  component = 0; // necessary?
          shifting = true;
          Refresh();
          numComponents--;
        } 
        if (shifting)
          components[index] = components[index+1];
		index++;    
      } 
   	  
   	  break;
    default:
      itoa (scanCode, code, 10); 
      if (debug)
        MessageBox ( 0,code, "Scan Code", 0);
      break;      	  
  }
}
bool HighLevelMenu::ReadProject(char * filename)
{
 FILE * fp;
 char _sourceFilename[255];
 Connection * connection;
 ConnectedComponent * component;
 ConnectedComponent * component1;
 ConnectedComponent * component2;
 LineInfo line;
 int len;
 int index = 0;
 Pin * port1;
 Pin * port2;
 char * name1;
 char * name2;
 timerCount = 0;
 bool readingComponents = false;
 bool readingSource = false;
 bool projectRead = false;

 readingProject = true;
 len = strlen (filename);
 if (len)
   if (fp = fopen (filename,"r"))
   {
     NewProject();	
     strcpy ( projectFilename,filename);	
     while (!feof(fp))
     {	  	
   	   ReadLine ( fp, line, readingComponents, readingSource );
	   if (line.readingSource)
	   {
         GetLine (fp, _sourceFilename, sizeof(_sourceFilename));
         strcpy (sourceFilename,_sourceFilename);
         break;
  	   }	
 	   else if (line.newData)
 	   {
 	     if(strlen ( line.component1))
 	       if (line.readingComponent)
 	  	     AddComponent (-1, line.component1, line.x1, line.y1);	 	  	    
 	  	   else // reading a connection
 	  	   {
 	  	     component1 = FindComponent (line.x1,line.y1);
 	  	     component2 = FindComponent (line.x2,line.y2);
 	  	     if (!component1)
 	  	     {
 	  	  	   MessageBox (0,"Can't find component1","Oops",0);
 	  	  	   MessageBox (0, line.component1,"Oops1",0);
 	  	  	   break;
 	         }
 	  	     else if (!component2)
 	  	     {
 	  	  	   MessageBox (0,"Can't find component2", "Oops", 0);
 	  	  	   MessageBox (0,line.component2,"oops2", 0);
 	  	  	   break;
 	         }
 	  	     port1 = (Pin *)component1->FindPort (line.port1);
 	  	     if (!port1)
 	  	     {
 	  	  	   MessageBox (0,"Can't find port1:","Oops", 0);
 	  	       MessageBox (0, line.port1, "Oops", 0);
 	  	  	   break;
 	  	     }
 	  	   	  
 	  	     port2 = (Pin *)component2->FindPort (line.port2);
 	  	     if (!port2)
 	  	     {
 	  	       MessageBox (0,"Can't find port2:","Oops",0);
 	  	       MessageBox (0, line.port2, "Oops", 0);
 	  	       (void)component2->FindPort (line.port2);
 	  	       break;
 	         }
 	  	     else
 	  	     {
 	  	       name1 = port1->name;
 	  	       name2 = port2->name;
               component1->Connect (port1, port2);
  	         }
 	  	   }
 	 
  	   }
 	   else
 	     break;
    }
    fclose (fp);
    projectRead = true;
  }
  readingProject = false;
  return projectRead;
}

void HighLevelMenu::NotSavedYet ()
{
  ConnectedComponent * component;	
  int index = 0;
  while (component=components[index++])
    component->NotSavedYet();
}

void HighLevelMenu::SaveProject(char * filename)
{
  OpenFileDialog ofd;
  int index = 0;
  FILE *fp;
  ConnectedComponent * component;  
  int len = strlen (sourceFilename);
  char * str;
  
  if (!len)
  {
    MessageBox (0,"Select the sketch that will be associated with this project.  It should be in the same directory", "Define Source file", 0); 	
	ofd.Open("Sketch\0*.INO");		
	len = strlen (ofd.Filename());
	if (len)
	{
	  strcpy (sourceFilename, ofd.Filename());
	}
	else
	{
	  MessageBox (0,"Sketch not selected", "Error", 0);
	  return;
    }
  }

  NotSavedYet();
  
  if (strlen(filename))
    fp = fopen (filename, "w");
  else
  {
    ofd.Save("Text\0*.TXT\0");
    if (strlen(ofd.Filename()))
      fp = fopen(ofd.Filename(), "w");
    else  
      return;
  }
  
  
  if (fp)
  {
  	if (components[0])
  	{
  	  fprintf (fp, "Project Components\n");
      while (component = components[index++])
      {
        component->SaveYourself (fp);  
	    fprintf (fp, "\n");
      }
       
      fprintf (fp, "Project Connections\n");
      index = 0;
  	  while (component=components[index])
  	  {
	    component->SaveConnections(fp);
		index++; 
      }
    }
    fprintf ( fp, "Project Source\n");
    fprintf ( fp, sourceFilename);
    fprintf ( fp, "\n");
    fclose (fp);
  }
  CopyFile ("sketch.ino", sourceFilename);
  MessageBox ( 0,"Project Saved", "Save", 0);
}

void HighLevelMenu::Paint(HWND hWnd)
{
  int index = 0;
  ConnectedComponent * component;
  Connection * connection;
   
  if (hWnd == windowHandle)
  {
  	hdc = BeginPaint (hWnd, &ps);
  	hdcMemory = CreateCompatibleDC (hdc);
  	
    while (component = components[index])
    {
      component->Paint (hdc, ps, hdcMemory);
      index++;
    } 
    

    index = 0;
    while (component = components[index++])
      component->CleanUp();

    DeleteDC (hdcMemory);    
    EndPaint (hWnd, &ps);
  }
}

HWND HighLevelMenu::DrawWindow (char * title, HINSTANCE hInst, char * bmpResource, 
                                int x , int y, int width, int height)
{                            
  HWND hWnd = Component::DrawWindow(title, hInst, "", x, y, 1200,1100);
  AddMenu();
  return hWnd;
}

void HighLevelMenu::HandleMouseMove (HWND hWnd, int x, int y)
{  
  ConnectedComponent * component;
  Connection * connection;
  int index = 0;
  
  while (component = components[index++])
  {
  	component->isActive =  (
	    (x >= component->x) && (x <= component->x + component->width) &&
        (y >= component->y) && (y <= component->y + component->height));
    if (component->isActive)
    { 
      // HandleMouseMove shows offset within the window  
      component->HandleMouseMove (hWnd, x,y);
      break;
    }     
  } 
      
  if (selectedItem > -1)
  {
    components[selectedItem]->MoveTo (x,y);
    components[selectedItem]->Refresh();
    index = 0;
    while (component=components[index++])
      component->Move();
  }   
}

void HighLevelMenu::Refresh()
{
  
  ConnectedComponent * component;
  int index = 0;
  while (component=components[index++])
  {
  	if (component->windowHandle)
      InvalidateRect ( component->windowHandle, NULL, true );  
  }  
}

// Set the component xOffset and yOffset
void HighLevelMenu::HandleMouseDown (HWND hWnd, int x, int y)
{
  bool isActive = false;
  ConnectedComponent * component;
  int index = 0;

  while (component = components[index])
  {
    if ((x >= component->x) && (x <= component->x + component->width) &&
        (y >= component->y) && (y <= component->y + component->height))
    {   
      component->xOffset = x - component->x;
      component->yOffset = y - component->y;
      // Make the port like a radio button so that only 1 port is selectable
      // at a time.
      if (!component->PortSelected() || !component->PinActive())
      {
        component->HandleMouseDown(hWnd, x, y);               
        selectedItem = index;
      }
      else // Toggle the pin activity
      {
        if ((component->PortSelected() != component->PinActive()))
        {
          component->Select(false);
          component->HandleMouseDown(hWnd, x, y);               
          selectedItem = index;
        }
        else // Deselect the port
          component->Select(false);
      }      
      break;
    }  
    index++;
  } 
  // ComputeSystem();
  Refresh();
  
}

void HighLevelMenu::HandleMouseUp (HWND hWnd)
{
  int numSelected = 0;
  Connection * c;
  struct IdPort
  {
  	COORD port;
  	int componentIndex;
  };
  Pin * pin;
  Pin * pin1 = 0;
  Pin * pin2 = 0;
  
  ConnectedComponent * component1 = 0;
  ConnectedComponent * component2 = 0;
  ConnectedComponent * component = 0;
  int index = 0;
  
  // Set all values to -1
  // Reset();
  
  index = 0;    
  while (component = components[index])
  {
  	if (component->isActive)
      component->HandleMouseUp (hWnd);
      
    if (pin = (Pin *)component->PortSelected())
    {
      if (!pin1) // This is the first port selected
      {
        pin1 = pin;
        component1 = component;
      }
      else
      {
        pin2 = pin;
        component2 = component;
      }
      numSelected++;
      if (numSelected ==2)
      {
        component1->Connect (pin1, pin2);
        component2->IsConnected (pin2, pin1); // Connect 2 pins 
      }
    }
    index++;
  }
  
  // ComputeSystem();
  selectedItem = -1; // Stop tracking the mouse      
  Refresh();
}

