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
 * Holds data related to the platform and windowing system
 */
struct PlatformContext
{
    void *state;
    i32 windowX;
    i32 windowY;
    i32 windowWidth;
    i32 windowHeight;
    const char* applicationName;
};

class Platform
{

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
    b8 Initialize(PlatformContext* context, const char *applicationName, i32 x, i32 y, i32 width, i32 height);
    
    /**
     * Create a window on the current platform.
     * @param context The current PlatformContext that contains all necessary configuration information.
     * @return success or error status code
     */
    b8 CreateWin(PlatformContext* context);

    /**
     * Pull events, such as input events, window events, etc., from the platform operating.
     * @param context The platform context
     * @return success or error code
     */
    b8 PollEvents(PlatformContext *context);
};

#endif
