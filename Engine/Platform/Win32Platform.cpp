#include "Platform.hpp"

#if ENGINE_PLATFORM == WIN32

#include <windows.h>

/**
 * Maintains all the state information for a Windows window
*/
struct WindowsState {
  HWND hwnd;
};

b8 Platform::Init(PlatformState* s, const char* applicationName, i32 x, i32 y, i32 width, i32 height)
{
  // Get Handle to application instance 
  HINSTANCE hinstance = (HINSTANCE) GetModuleHandleA(0);

  // Define Window Class Name
  const char* windowClassName = "carbon_window_class";

  // Create Window Class
  WNDCLASS wc = { };
  wc.lpfnWndProc = WindowProc;
  wc.hInstance = hinstance;
  wc.lpszClassName = windowClassName;
  wc.style = CS_OWNDC | CS_HREDRAW | CS_VREDRAW;


  // Register window class with OS
  RegisterClass(&wc);

  // Create Window from WNDCLASS
  HWND hwnd = CreateWindowExA(
    NULL,
    wc.lpszClassName,
    applicationName,
    WS_OVERLAPPEDWINDOW,
    x,
    y,
    width,
    height,
    NULL,
    NULL,
    wc.hInstance,
    NULL
  );

  // Check Window Creation for Errors
  if (hwnd == NULL)
  {
    // TODO: Handle hwnd creation failure
    // Failed to create window
    printf("Failed to create window.\n");
    return 0;
  }

  b8 showResult = ShowWindow(hwnd, SW_SHOW);
  if(!showResult)
  {
    // TODO: Handle failed display 
    printf("Failed to show window.\n");
    return 0;
  }

  // Everything initiated successfully, so set our state
  WindowsState* ws = (WindowsState*)malloc(sizeof(WindowsState));
  ws->hwnd = hwnd;
  s->state = ws;
  
  return 1;
}


#endif 