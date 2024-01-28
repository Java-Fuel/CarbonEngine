#include <Math/Math.hpp>
#include <Platform/Platform.hpp>
#include <Utils/Defines.h>

// Windows Entry Point
#if _WIN32

#include <windows.h>
#include <Debugapi.h>

u8* RenderRed(PlatformContext* context)
{
    i32 width = context->windowWidth;
    i32 height = context->windowHeight;

    return 0;
}

int WINAPI WinMain(HINSTANCE handle, HINSTANCE prevHandle, PSTR args, int displayMode)
{

    Win32Platform p = Win32Platform::instance(); 

    b8 init = p.Initialize("Test Game", 500, 500, 500, 500);
    if(init) // Initialization Failure
    {
        OutputDebugStringA("Could not initialize the Windows platform layer!\n");
        return 1;
    }

    b8 createWin = p.CreateWin();
    if (createWin) // Window Creation Failure)
    {
        OutputDebugStringA("Could not create window!\n");
        return 1;
    }
    
    u8 running = true;
    while (running)
    {
        running = p.PollEvents();
        
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
