#include "InputBox.h"
#define ID_EDIT 1
#define ID_BUTTON 2

static char inputBoxFilename[255];
static bool done;
LRESULT CALLBACK WndProc1(HWND hwnd, UINT msg, 
    WPARAM wParam, LPARAM lParam)
{
  static HWND hwndEdit;
	
  static wchar_t *lyrics =  L"Enter the name of the source code file\n\
That contains the sketch used for this project\n\
Then press the Ok button\n\
";

  switch(msg)  
  {
      case WM_CREATE:
      
        CreateWindowW(L"STATIC", lyrics, 
            WS_CHILD | WS_VISIBLE | SS_LEFT,
            20, 20, 300, 230,
            hwnd, (HMENU) 1, NULL, NULL);
            
        hwndEdit = CreateWindowW(L"Edit", NULL, 
            WS_CHILD | WS_VISIBLE | WS_BORDER,
            50, 80, 150, 20, hwnd, (HMENU) ID_EDIT,
            NULL, NULL);
            
        CreateWindowW(L"button", L"Ok",
            WS_VISIBLE | WS_CHILD ,
            20, 120, 80, 25,
            hwnd, (HMENU) 1, NULL, NULL);

        CreateWindowW(L"button", L"Quit",
            WS_VISIBLE | WS_CHILD ,
            120, 120, 80, 25,
            hwnd, (HMENU) 2, NULL, NULL);
            
        strcpy (inputBoxFilename,"");    
                        
        break;
        
      case WM_COMMAND:

        if (LOWORD(wParam) == 1) {
          int len = GetWindowTextLengthW(hwndEdit) + 1;
           wchar_t text[len];
           GetWindowTextW(hwndEdit, text, len);
           SetWindowTextW(hwnd, text);
           PostQuitMessage(0);
        }

        if (LOWORD(wParam) == 2) {
          PostQuitMessage(0);
        }

        break;

      case WM_DESTROY:

        done = true;
        PostQuitMessage(0);
        break;
  }

  return DefWindowProcW(hwnd, msg, wParam, lParam);
}

char * InputBox::getOutput ()
{
	return &inputBoxFilename[0];
}


bool InputBox::Done()
{
  return done;
}

InputBox::InputBox(int _x, int _y)
{ 
  done = false;
  int x = _x;
  int y = _y;
  WNDCLASSW wc = {0};
  wc.lpszClassName = L"Static Control";
  wc.hInstance = 0; // g_hInst;
  wc.hbrBackground = GetSysColorBrush (COLOR_3DFACE);
  wc.lpfnWndProc = WndProc1;
  wc.hCursor       = LoadCursor(0,IDC_ARROW);
  
  RegisterClassW(&wc);
  
  CreateWindowW(wc.lpszClassName, L"Sketch filename",
                WS_OVERLAPPEDWINDOW | WS_VISIBLE,
                100, 100, 330, 270, 0, 0, wc.hInstance, 0);

}

InputBox::~InputBox()
{ 	
}
