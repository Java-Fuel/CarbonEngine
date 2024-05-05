#pragma once

#include "PlatformEventManager.h"
#include "CarbonLogger.h"
#include "KeyboardInput.h"
#include "Defines.h"

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <sysinfoapi.h>
#include <string>


/**
 * Defines the standard interface for interacting with different
 * platforms.
 */

class CAPI Win32Platform
{

public:
  int windowX;
  int windowY;
  int windowWidth;
  int windowHeight;
  int bufferWidth;
  int bufferHeight;
  HWND windowHandle;
  std::string applicationName;
  unsigned char* backBuffer;
  unsigned char bytesPerPixel;
  unsigned int bufferSize;
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
  Win32Platform(const char* applicationName, int x, int y, int width, int height);

  /**
   * Create a window on the current platform.
   * @param context The current PlatformContext that contains all necessary configuration information.
   * @return success or error status code
   */
  char Win32CreateWindow();

  /**
   * Pull events, such as input events, window events, etc., from the platform operating.
   * @param context The platform context
   * @return success or error code
   */
  char Win32PollEvents();

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
  void* Valloc(unsigned int size);

  /**
   * Allocate memory directly from the heap.
   * Note: Memory allocated using Halloc is not movable.
   * @param size The size of the memory region to allocate in bytes
   * @return pointer to memory region
  */
  void* Halloc(unsigned int size);

  /**
   * Frees memory that was allocated using Halloc.
   * @param ptr A pointer to the memory that needs to be freed
  */
  void Hfree(void* ptr);

  /**
   * Free virtual memory allocated by win32 system
   * @param ptr A pointer to the memeory to be freed
   * @param size Size of the memory to free. If set to 0, the size will be calculated
  */
  void Vfree(void* ptr, unsigned int size);

  /**
   * Get time in ms since system started.
   * Note: time is updated every 10 ms - 16 ms through Windows, this could cause issues if game is running
   * at a very high FPS
  */
  unsigned int getTick();

private:
  /**
   * Resize the Device Independent Bitman (DIB) provided by Windows platform
   */
  void ResizeBackbuffer(int newWidth, int newHeight);

  /**
   * Update window with new data that was moved into back buffer
   * Note: This is like executing a render call
   */
  void DrawBuffer(RECT* windowRect);
};