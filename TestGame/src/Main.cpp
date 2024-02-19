#include <Platform/Win32Platform.h>
#include "Platform/PlatformEventManager.h"
#include <Utils/Defines.h>

// Windows Entry Point
#if _WIN32

#include <windows.h>
#include <Debugapi.h>

void WindowResizeHandler(PlatformEventArgs* args)
{
    const char* output1 = STR("width: ", args->first);
    const char* output2 = STR("height: ", args->second);
    OutputDebugStringA(output1);
    OutputDebugStringA(output2);
}


int WINAPI WinMain(HINSTANCE handle, HINSTANCE prevHandle, PSTR args, int displayMode)
{

    Win32Platform p = Win32Platform(); 

    b8 init = p.Win32Init("Test Game", 500, 500, 500, 500);
    if(init) // Initialization Failure
    {
        OutputDebugStringA("Could not initialize the Windows platform layer!\n");
        return 1;
    }

    b8 createWin = p.Win32CreateWindow();
    if (createWin) // Window Creation Failure)
    {
        OutputDebugStringA("Could not create window!\n");
        return 1;
    }
    
    u8 running = true;
    while (running)
    {
        running = p.Win32PollEvents();
        
    }

    return 0;
}


#else

int main(int argc, char *argv[])
{
    printf("Hello Carbon");
    return 0;
}

#endif
