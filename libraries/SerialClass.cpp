#include "SerialClass.h"
#include <string.h>
#include <stdio.h>
#include "conio.h"

extern void addLB (HWND idnr, char *ltext);
static SerialClass * serialClass;

void SerialClass::setTWindow ( HWND _idnr )
{
  idnr = _idnr;
}

SerialClass::SerialClass()
{ 
  keyPressed = false;   
  shiftKey = false; 
  queueIndex = 0;
  outputIndex = 0;
  readQueue [0] = 0;
  outputQueue [0] = 0;
  serialClass = this;
}

// Singleton pointer to class
// Example:
//   SerialClass::Instance()->println ( "Hello" );
SerialClass * SerialClass::Instance()
{
  return serialClass;
}

void SerialClass::saveKey ( WPARAM chParam )
{
  char ch = chParam & 0xFF; 
  if (shiftKey) 
    ch = ch;   
  else if (!shiftKey && (ch >= 'A') && (ch <= 'Z'))
    ch = ch + 'a' - 'A';
  keyPressed = true;
  keyPress = ch;
}

char SerialClass::read () 
{
  char ch = 0;
  if (available())
    ch = readQueue[queueIndex++];    
  return ch;
}

char SerialClass::peek ( )
{ 
  return keyPress;
}

void SerialClass::begin (int baudrate)
{
  // Don't care;
} 

bool SerialClass::available ()
{
  bool found = false; 
  int len = strlen (readQueue);  
  if (queueIndex < len)
    found = true;
     
  return found;
}

void SerialClass::print ( char * line )
{
  int len = strlen (line);     
  for (int i=0; i<len; i++)
    print ( line[i]);
}
void SerialClass::println ( char * line )
{
  char outputLine [1000];   
  int len = strlen (line);
  for (int i=0; i<outputIndex; i++)
    outputLine [i] = outputQueue [i];
      
  for (int i=0; i<len; i++)
    outputLine [i + outputIndex] = line[i];
  
  outputLine[len+outputIndex] = 0; // Terminate the string  
  
  SendMessage(idnr,LB_ADDSTRING,0,(LPARAM)&outputLine[0]);  
  //addLB (idnr, &outputLine[0]);
  outputIndex = 0;
}
void SerialClass::print ( char ch)
{
  outputQueue[outputIndex++] = ch;     
  if (ch == '\n')
    println ("");
}

void SerialClass::print ( unsigned long number )
{
  print ( (int) number );   
}

void SerialClass::print ( int number)
{
  char line[100];
  itoa ( number, &line[0], 10 );
  print ( line );
}

void SerialClass::println ( unsigned long number )
{
  print (number);
  println ();
}

void SerialClass::println ( int number )
{
  print (number);
  println();     
}

void SerialClass::println ()
{
  println ( "" );
}
void SerialClass::println (char ch)
{
  print (ch);
  println();    
}

void SerialClass::clearBuffer()
{
  queueIndex = 0;
}
void SerialClass::saveLine ( char * line )
{
  int len = strlen (line);
  queueIndex = 0;
  for (int i=0; i<len; i++)
    readQueue [i] = line[i];
  readQueue[len] = 0; // String termination  
}



