#include <Math/Math.hpp>
#include <Platform/Platform.hpp>
#include <Utils/Defines.h>

// Windows Entry Point
# if _WIN32

#include <windows.h>
#include <Debugapi.h>

int WINAPI WinMain(HINSTANCE handle, HINSTANCE prevHandle, PSTR args, int displayMode)
{
  OutputDebugStringA("Windows is working\n");
  int s = sizeof(LPVOID);

  Platform p;

  PlatformState state = {};

  b8 init = p.Init(&state, "TestGame", 500, 500, 500, 500);

  if (init)
  {
    OutputDebugStringA("Failed to initialize window.\n");
    return 1;
  }

  // Get HWND
  HWND hwnd = (HWND)state.state;

  // ShowWindow(hwnd, SW_SHOW);
  // UpdateWindow(hwnd);

  // Listen for messages
  MSG msg = {};
  while(GetMessage(&msg, NULL, 0, 0) != FALSE)
  {
    TranslateMessage(&msg);
    DispatchMessage(&msg);
  }

  return 0;
}

#else

int main(int argc, char* argv[])
{
  printf("Hello Carbon");
  return 0;
}

#endif 