
#include "Win32Platform.h"
#include "Renderer.h"

#include <windows.h>


int __stdcall WINAPI WinMain(HINSTANCE handle, HINSTANCE prevHandle, PSTR args, int displayMode)
{

  Win32Platform p = Win32Platform("test game", 500, 500, 500, 500);

  char createwin = p.Win32CreateWindow();
  if (createwin) // window creation failure)
  {
    return 1;
  }

  Renderer renderer = Renderer(&p, 60);
  renderer.start();

  return 0;
}