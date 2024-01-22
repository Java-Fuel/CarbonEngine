#include "Platform.hpp"

#if ENGINE_PLATFORM == WIN32

#include <windows.h>
#include "Win32Platform.h"

// TODO: Refactor Globals
/* Global Variable */
static BITMAPINFO BitMapInfo;
static i32 BytesPerPixel = 4;
static void* BackBuffer;
static u32 BitmapWidth = 500;
static u32 BitmapHeight = 500;


/* Private Method Prototypes */

/**
 * @brief Windows Callback function to respond to Windows events
 * @param handle a handle to the window where event occurred
 * @param msg the event message code
 * @param wparam additional message information (depends on msg value)
 * @param lparam additional message information (depends on msg value)
 */
LRESULT CALLBACK WindowProc(HWND handle, UINT msg, WPARAM wparam, LPARAM lparam);

/**
 * Resize the Device Independent Bitman (DIB) provided by Windows platform
 */
void ResizeBackbuffer(i32 newWidth, i32 newHeight);

/**
 * Update window with new data that was moved into back buffer
 * Note: This is like executing a render call
 */
void DrawBuffer(HWND window, HDC deviceContext, RECT* windowRect);

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
        u32 width = (u32)LOWORD(lparam);
        u32 height = (u32)HIWORD(lparam);
        ResizeBackbuffer(width, height);
        result = 0;
    }
    break;
    case WM_PAINT:
    {
        OutputDebugStringA("Need to paint window.\n");

        PAINTSTRUCT ps;
        HDC deviceContext = BeginPaint(handle, &ps);
        RECT windowRect;
        GetClientRect(handle, &windowRect);
        DrawBuffer(handle, deviceContext, &windowRect); 

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

void ResizeBackbuffer(i32 newWidth, i32 newHeight)
{
    // TODO: Release old buffer (going to mem leak)
    
    // Create new BitMapInfo
    BitMapInfo = {};
    BitMapInfo.bmiHeader.biSize = sizeof(BitMapInfo.bmiHeader);
    BitMapInfo.bmiHeader.biWidth = newWidth;
    BitMapInfo.bmiHeader.biHeight = -newHeight;
    BitMapInfo.bmiHeader.biPlanes = 1;
    BitMapInfo.bmiHeader.biBitCount = 32; // RGBa 8 bits * 4 values giving us (0-255, 0-255, 0-255, 0-255)
    BitMapInfo.bmiHeader.biCompression = BI_RGB;


    // Allocate new back buffer
    i32 backBufferSize = (newWidth * newHeight) * BytesPerPixel;
    BackBuffer = (u8*)VirtualAlloc(NULL, backBufferSize, MEM_COMMIT, PAGE_READWRITE);
    BitmapWidth = newWidth;
    BitmapHeight = newHeight;
    
    // Draw to buffer
    u32 stride = BitmapWidth * BytesPerPixel;
    u8* row = (u8*)BackBuffer;
    for(u32 Y = 0; Y < BitmapHeight; ++Y)
    {   
        // Row of Pixel
        u8* pixel = row;
        for(u32 X = 0; X < BitmapWidth; ++X)
        {
            // Set Blue
            *pixel = 0;
            ++pixel;

            // Set Green
            *pixel = 0;
            ++pixel;

            // Set Red
            *pixel = 255;
            ++pixel;

            // Set Alpha
            *pixel = 0;
            ++pixel;
        }
        row += stride;
    }
}

void DrawBuffer(HWND window, HDC deviceContext, RECT* windowRect)
{
    u32 windowWidth = windowRect->right - windowRect->left;
    u32 windowHeight = windowRect->bottom - windowRect->top;
    StretchDIBits(
        deviceContext,
        0,
        0, 
        windowWidth,
        windowHeight,
        0,
        0,
         BitmapWidth,
        BitmapHeight,
        BackBuffer,
        &BitMapInfo,
        DIB_RGB_COLORS,
        SRCCOPY
    );

}

#endif
