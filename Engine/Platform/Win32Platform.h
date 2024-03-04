#ifndef PLATFORM_H
#define PLATFORM_H

#include "Utils/Defines.h"
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "PlatformEventManager.h"
#include "Utils/CarbonLogger.h"

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
     */
    void Win32Draw();
    
    /**
     * Handle window resize event for back buffer
     * @param args The arguments from resize event
    */
    void ResizeWindowHandler(PlatformEventArgs* args);

    /**
     * Alloc pages in virtual memory space.
     * Note: This method allows the system to determine where to allocate 
     * the memory (it does not specify a location in virtual address space).
     * It also assumes read write access for the memory location in the OS.
     * @param size The size of memory block to allocate in bytes
     * @return Pointer to block of memory
    */
    void* Valloc(u32 size);

    /**
     * Allocate memory directly from the heap. 
     * Note: Memory allocated using Halloc is not movable. 
     * @param size The size of the memory region to allocate in bytes
     * @return pointer to memory region
    */
    void* Halloc(u32 size);

    /**
     * Frees memory that was allocated using Halloc.
    */
    void Hfree();

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
