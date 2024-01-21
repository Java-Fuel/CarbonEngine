#ifndef WIN32PLATFORM_H
#define WIND32PLATFORM_h


#include <Windows.h>

/**
 * Maintain Windows platform specific state
 */
struct Win32State {
    HWND hwnd;
};


#endif
