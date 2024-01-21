#include <Math/Math.hpp>
#include <Platform/Platform.hpp>
#include <Utils/Defines.h>

// Windows Entry Point
#if _WIN32

#include <windows.h>
#include <Debugapi.h>

int WINAPI WinMain(HINSTANCE handle, HINSTANCE prevHandle, PSTR args, int displayMode)
{

    Platform p;    
    PlatformContext context = {};

    b8 init = p.Initialize(&context, "Test Game", 500, 500, 500, 500);
    if(init > 0) // Initialization Failure
    {
        OutputDebugStringA("Could not initialize the Windows platform layer!\n");
        return 1;
    }

    b8 createWin = p.CreateWin(&context);
    if (createWin > 0) // Window Creation Failure)
    {
        OutputDebugStringA("Could not create window!\n");
        return 1;
    }
	
    p.PollEvents(&context);

    return 0;
}

#else

int main(int argc, char *argv[])
{
    printf("Hello Carbon");
    return 0;
}

#endif
