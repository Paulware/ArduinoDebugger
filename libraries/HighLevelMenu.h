#ifndef HIGHLEVELMENU_H
#define HIGHLEVELMENU_H
#include "ConnectedComponent.h"
#include "ViewConnections.h"
#include <vector>
#include <string>

#define MAX_COMPONENTS 100
class HighLevelMenu:public Component
{
  public:
    HighLevelMenu(ViewConnections * _viewConnections); 
    ~HighLevelMenu();
    static HighLevelMenu * Instance();    
    // void ComputeSystem();
    HWND DrawWindow (char * title, HINSTANCE hInst, char * bmpResource, 
                     int x , int y, int width=0, int height=0);  
    void PaintStart ();
    void Paint(HWND hWnd);
    void HandleMouseMove (HWND hWnd, int x, int y);
    void HandleMenu (int command); 
    void AddMenu ();
    void AddComponent (int index, char * typeName, int x, int y);
    void HandleMouseDown (HWND hWnd, int x, int y);
    void HandleMouseUp (HWND hWnd);
    void HandleKeyUp ( int scanCode); 
	void NewProject();
    void SaveProject(char *);
    void NotSavedYet ();    
    bool ReadProject(char *);
    int DigitalRead(int pin);
    void DigitalWrite (int,int);
    ConnectedComponent * FindComponent (int,int );
    ConnectedComponent * FindComponent ( char * typeName);
    int FindComponentName (std::string str);
    void lcdPrint ( char * ch);
    void lcdPrint ( int value);   
    void lcdClear ();
    Pin * FindOtherPin ( Pin *);
    void TroubleshootPins ();
    int timerCount;
    Pin * GetNextPin ( Pin * pin);
    Connection * FindConnection ( Pin * pin);
    void Refresh();
    bool readingProject;
	void BestValue ( Pin * pin1, Pin * pin2, int & value, int & resistance);
    void ResetConnectionPins (Pin * pin);
    
    ConnectedComponent * components[MAX_COMPONENTS];   
  
  private:
    int numComponents;
    int selectedItem;      
    ViewConnections * viewConnections;
    char projectFilename[80];
    char sourceFilename[255]; 
    std::vector<std::string> ComponentNames;
    char buf[1000];  // Because ComponetNames is overwriting the array boundaries?!?
    
};

#endif


