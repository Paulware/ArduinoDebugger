#ifndef SERIAL_H
#define SERIAL_H
#include <windows.h>
class SerialClass
{
  public:          
    // Constructor
    SerialClass(); 
    static SerialClass * Instance();        
	void begin (int); 
    void setTWindow ( HWND _idnr );
	void print ( char );
	void print ( unsigned long);
	void print ( char *);
	void print ( int );
	void print ( float ){};
	void println ( float ){};
	void println ( unsigned long );
	void println ( int );
	void println ();
	void println ( char *);
	void println ( char );
	char read();
	bool available ();
	char peek();
	void saveKey (WPARAM);

    bool keyPressed;
    char keyPress;
    bool shiftKey;
    void saveLine ( char * line );
    void clearBuffer();

  private:
    HWND idnr;
    char readQueue[1000];
    int queueIndex;
    char outputQueue[1000];
    int outputIndex;
};
extern SerialClass Serial;

#endif


