#include "Platform.hpp"

#if ENGINE_PLATFORM == WIN32

#include <windows.h>
#include "Win32Platform.h"


/**
 * @brief Windows Callback function to respond to Windows events
 * @param handle a handle to the window where event occurred
 * @param msg the event message code
 * @param wparam additional message information (depends on msg value)
 * @param lparam additional message information (depends on msg value)
 */
LRESULT CALLBACK WindowProc(HWND handle, UINT msg, WPARAM wparam, LPARAM lparam);

/* Platform.hpp Implementation */
b8 Platform::Initialize(PlatformContext* context, const char* applicationName, i32 x, i32 y, i32 width, i32 height)
{   
    context->windowWidth = width;
    context->windowHeight = height;
    context->windowX = x;
    context->windowY = y;
    context->applicationName = applicationName;
    
    return 0;
}

b8 Platform::CreateWin(PlatformContext* context)
{
    // Get Handle to application instance
    HINSTANCE hinstance = (HINSTANCE)GetModuleHandleA(0);

    // Define Window Class Name
    const char *windowClassName = "carbon_window_class";

    // Create Window Class
    WNDCLASS wc = {};
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hinstance;
    wc.lpszClassName = windowClassName;
    wc.style = CS_OWNDC | CS_HREDRAW | CS_VREDRAW;

    // Register window class with OS
    i32 result = RegisterClassA(&wc);

    // Create Window from WNDCLASS
    HWND hwnd = CreateWindowExA(
        WS_EX_OVERLAPPEDWINDOW,
        wc.lpszClassName,
        context->applicationName,
        WS_OVERLAPPEDWINDOW,
        context->windowX,
        context->windowY,
        context->windowWidth,
        context->windowHeight,
        NULL,
        NULL,
        wc.hInstance,
        NULL);

    // Check Window Creation for Errors
    if (hwnd == NULL)
    {
        // TODO: Handle hwnd creation failure

        // Get Error Code and Message
        // TODO: Move to GetError utility function
        DWORD errorCode = GetLastError();
        LPVOID msgBuffer;
        FormatMessage(
            FORMAT_MESSAGE_ALLOCATE_BUFFER |
                FORMAT_MESSAGE_FROM_SYSTEM |
                FORMAT_MESSAGE_IGNORE_INSERTS,
            NULL,
            errorCode,
            MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
            (LPTSTR)&msgBuffer,
            0,
            NULL);

        OutputDebugStringA((LPCSTR)msgBuffer);
        return (b8)1;
    }
    
    // Display window and run first paint call
    ShowWindow(hwnd, SW_SHOW);
    UpdateWindow(hwnd);

    // Everything initiated successfully, so set our state
    // TODO: Switch to platform specific memory allocation instead of malloc
    Win32State *ws = (Win32State *)malloc(sizeof(Win32State));
    ws->hwnd = hwnd;
    context->state = ws;

    return 0;
}

b8 Platform::PollEvents(PlatformContext *context)
{
    MSG msg = {};

    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}



/* Private Methods */
LRESULT CALLBACK WindowProc(HWND handle, UINT msg, WPARAM wparam, LPARAM lparam)
{

    i64 result = 0;

    switch (msg)
    {
    case WM_SIZE:
    {
        OutputDebugStringA("Size of window changed");
        result = 0;
    }
    break;
    case WM_PAINT:
    {
        OutputDebugStringA("Need to paint window.\n");

        PAINTSTRUCT ps;
        HDC deviceContext = BeginPaint(handle, &ps);

        HBRUSH brush = CreateSolidBrush(0x00000000);
        FillRect(deviceContext, &ps.rcPaint, brush);

        EndPaint(handle, &ps);

        result = 0;
    }
    break;
    case WM_CLOSE:
    {
        OutputDebugStringA("Closing window...\n");
        BOOL r = DestroyWindow(handle); // TODO: Can fail, need to handle error scenario
        if (r)
        {
            DWORD errorCode = GetLastError();
            LPVOID msgBuffer;
            FormatMessage(
                FORMAT_MESSAGE_ALLOCATE_BUFFER |
                    FORMAT_MESSAGE_FROM_SYSTEM |
                    FORMAT_MESSAGE_IGNORE_INSERTS,
                NULL,
                errorCode,
                MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
                (LPTSTR)&msgBuffer,
                0,
                NULL);

            OutputDebugStringA((LPCSTR)msgBuffer);
        }
        result = 0;
    }
    break;
    case WM_DESTROY:
    {
        OutputDebugStringA("Destroying window...\n");
        PostQuitMessage(0);
        result = 0;
    }
    break;
    // TODO: Handle closed window
    default:
    {
        OutputDebugStringA("Handling msg with default method.\n");
        result = DefWindowProcA(handle, msg, wparam, lparam);
    }
    }

    return result;
}


#endif
