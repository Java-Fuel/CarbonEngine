#include <Platform/Win32Platform.h>
#include "Platform/PlatformEventManager.h"
#include <Utils/Defines.h>
#include <windows.h>
#include <Debugapi.h>

void RenderPattern(Win32Platform* platform, int xOffset, int yOffset)
{
    // Draw to buffer
    u32 stride = platform->bufferWidth * platform->bytesPerPixel;
    u8* row = platform->backBuffer;
    for(u32 Y = 0; Y < platform->bufferHeight; ++Y)
    {   
        // Row of Pixel
        u8* pixel = row;
        for(u32 X = 0; X < platform->bufferWidth; ++X)
        {
            // Set Blue
            *pixel = X + Y;
            ++pixel;

            // Set Green
            *pixel = (u8)(X + xOffset);
            ++pixel;

            // Set Red
            *pixel = 0;
            ++pixel;

            // Set Alpha
            *pixel = (u8)(Y + yOffset);
            ++pixel;
        }
        row += stride;
    }
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
    
    int xOffset = 0;
    int yOffset = 100;
    u8 running = true;
    while (running)
    {
        running = p.Win32PollEvents();
        RenderPattern(&p, xOffset, yOffset);
        p.Win32Draw();

        xOffset++;
        yOffset++;      
    }

    return 0;
}
