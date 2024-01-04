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

    /**
     * @brief Initiate platform shutdown by cleaning up any resources
     * @param s pointer to platform data to cleanup
     * @return 0 on successful cleanup, error number greater than zero on failed cleanup
    */
    b8 Shutdown(PlatformState* s);

};

#endif