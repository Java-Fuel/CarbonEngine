#include "Platform.hpp"

#if ENGINE_PLATFORM == WIN32

#include <windows.h>


/**
 * Maintains all the state information for a Windows window
*/
struct WindowsState {
  HWND hwnd;
};


/**
 * @brief Windows Callback function to respond to Windows events
 * @param handle a handle to the window where event occurred
 * @param msg the event message code 
 * @param wparam additional message information (depends on msg value)
 * @param lparam additional message information (depends on msg value)
 */
LRESULT CALLBACK WindowProc(HWND handle, UINT msg, WPARAM wparam, LPARAM lparam)
{
  
  i64 result = 0;

  switch(msg)
  {
    case WM_SIZE:
    {
      OutputDebugStringA("Size of window changed");
      result = 0;
    } break;
    case WM_PAINT:
    {
      OutputDebugStringA("Need to paint window.\n");
      result = 0;
    } break;
    // TODO: Handle closed window
    default:
    {
      result = DefWindowProcA(handle, msg, wparam, lparam);
    }
  }
  
  return result;
}

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
  i32 result = RegisterClassA(&wc);

  // Create Window from WNDCLASS
  HWND hwnd = CreateWindowExA(
    0,
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
    
    // Get Error Code and Message
    // TODO: Move to GetError utility function
    DWORD errorCode = GetLastError();
    LPVOID msgBuffer;
    FormatMessage(
      FORMAT_MESSAGE_ALLOCATE_BUFFER | 
      FORMAT_MESSAGE_FROM_SYSTEM |
      FORMAT_MESSAGE_IGNORE_INSERTS,
      NULL,
      errorCode,
      MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
      (LPTSTR) &msgBuffer,
      0, 
      NULL 
    );

    OutputDebugStringA((LPCSTR)msgBuffer);
    return (b8)1;
  }

  ShowWindow(hwnd, SW_SHOW);

  // Everything initiated successfully, so set our state
  WindowsState* ws = (WindowsState*)malloc(sizeof(WindowsState));
  ws->hwnd = hwnd;
  s->state = ws;
  
  return 0;
}


#endif 