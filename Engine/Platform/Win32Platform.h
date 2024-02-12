#ifndef PLATFORM_HPP
#define PLATFORM_HPP

#include "Utils/Defines.h"
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "PlatformEventManager.h"

/**
 * Defines the standard interface for interacting with different
 * platforms.
 */

class Win32Platform
{

public:
    i32 windowX;
    i32 windowY;
    i32 windowWidth;
    i32 windowHeight;
    i32 bufferWidth;
    i32 bufferHeight;
    HWND windowHandle;
    const char* applicationName;
    u8* backBuffer;
    u8 bytesPerPixel;
    BITMAPINFO bitMapInfo;
    

public:
    
    /**
     * Initialize the platform by creating an application window
     * @param context The PlatformContext to be initialized
     * @param applicationName name of the application window
     * @param x the X coordinate to create window
     * @param y the Y coordinate to create the windog
     * @param width the starting width of the window
     * @param height the starting height of the window
     * @return 0 on successful initialization, error number greater than zero on failed init
     */
    b8 Win32Init(const char *applicationName, i32 x, i32 y, i32 width, i32 height);
    
    /**
     * Create a window on the current platform.
     * @param context The current PlatformContext that contains all necessary configuration information.
     * @return success or error status code
     */
    b8 Win32CreateWindow();

    /**
     * Pull events, such as input events, window events, etc., from the platform operating.
     * @param context The platform context
     * @return success or error code
     */
    b8 Win32PollEvents();

    /**
     * Draw buffer to the display
     * @param buffer The buffer data to draw to the screen
     */
    void Win32Draw(u8* buffer, u32 bufferWidth, u32 bufferHeight);

    void ResizeWindowHandler(PlatformEventArgs* args);

private:
    /**
     * Resize the Device Independent Bitman (DIB) provided by Windows platform
     */
    void ResizeBackbuffer(i32 newWidth, i32 newHeight);

    /**
     * Update window with new data that was moved into back buffer
     * Note: This is like executing a render call
     */
    void DrawBuffer(RECT* windowRect);
};
#endif
