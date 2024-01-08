#ifndef PLATFORM_HPP
#define PLATFORM_HPP

#include "Utils/Defines.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * Defines the standard interface for interacting with different
 * platforms. 
*/

#include <stdio.h>

/**
 * Keeps track of all platform data for game engine
*/
struct PlatformState {
  void* state;
};

/**
 * Holds data related to the platform and windowing system
*/
struct PlatformContext {
  void* state;
};

/**
 * Holds event and event data emitted by the platform OS
*/
struct PlatformEvent {
  i32 eventCode;
  void* data;
};


class Platform {

  public:
    /**
     * @brief Initialize the platform by creating an application window
     * @param s a pointer to a PlatformState object used to keep track of all necessary platform data
     * @param applicationName name of the application window
     * @param x the X coordinate to create window
     * @param y the Y coordinate to create the window
     * @param width the starting width of the window
     * @param height the starting height of the window
     * @return 0 on successful initialization, error number greater than zero on failed init
    */
    b8 Init(PlatformState* s, const char* applicationName, i32 x, i32 y, i32 width, i32 height);

    /* V2 */
    // Initialize the platform 
    b8 Initialize(PlatformContext* context, const char* applicationName, i32 x, i32 y, i32 width, i32 height);
    // Display Window on system
    b8 DisplayWindow(PlatformContext* context);
    // Get Error message for errorCode from system
    char* GetErrorMessage(i32 errorCode);
    /**
     * @brief Initiate platform shutdown by cleaning up any resources
     * @param s pointer to platform data to cleanup
     * @return 0 on successful cleanup, error number greater than zero on failed cleanup
    */
    b8 Shutdown(PlatformState* s);
    // Allocate memory on the platform
    void* Allocate(i32 size);
    // deallocate memory on the platform
    void Deallocate(void* data);

};

#endif