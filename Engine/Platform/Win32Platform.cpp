#include <windows.h>
#include "Win32Platform.h"
#include "Platform/PlatformEventManager.h"


/**
 * @brief Windows Callback function to respond to Windows events
 * @param handle a handle to the window where event occurred
 * @param msg the event message code
 * @param wparam additional message information (depends on msg value)
 * @param lparam additional message information (depends on msg value)
 */
LRESULT CALLBACK WindowProc(HWND handle, UINT msg, WPARAM wparam, LPARAM lparam);


/* Platform.hpp Implementation */

b8 Win32Platform::Win32Init(const char* applicationName, i32 x, i32 y, i32 width, i32 height)
{   
    windowWidth = width;
    windowHeight = height;
    windowX = x;
    windowY = y;
    applicationName = applicationName;
    bytesPerPixel = 4;

    PlatformEventManager* current = PlatformEventManager::current();
    current->subscribe(PlatformEventType::WINDOW_RESIZE, new PlatformEventHandler<Win32Platform>(this, &Win32Platform::ResizeWindowHandler));
    
    return 0;
}

b8 Win32Platform::Win32CreateWindow()
{
    // Get Handle to application instance
    HINSTANCE hinstance = (HINSTANCE)GetModuleHandleA(0);

    PlatformEventManager* current = PlatformEventManager::current();


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
        applicationName,
        WS_OVERLAPPEDWINDOW,
        windowX,
        windowY,
        windowWidth,
        windowHeight,
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

    windowHandle = hwnd;
    Win32Draw();
    return 0;
}

b8 Win32Platform::Win32PollEvents()
{
    MSG msg = {};

    while (PeekMessageA(&msg, 0, 0, 0, PM_REMOVE))
    {
        if (msg.message == WM_QUIT)
        {
            return 0;
        }

        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 1;
}

void Win32Platform::Win32Draw()
{
    RECT windowRect;
    GetClientRect(windowHandle, &windowRect);
    DrawBuffer(&windowRect);
}

void Win32Platform::ResizeWindowHandler(PlatformEventArgs* args)
{
    i32 width = args->first;
    i32 height = args->second;
    u32 i = 9;

    ResizeBackbuffer(width, height);
    Win32Draw();
}


/* Private Methods */

LRESULT CALLBACK WindowProc(HWND handle, UINT msg, WPARAM wparam, LPARAM lparam)
{

    i64 result = 0;

    switch (msg)
    {
    case WM_SIZE:
    {
        i32 width = (i32)LOWORD(lparam);
        i32 height = (i32)HIWORD(lparam);
        PlatformEventManager::current()->publishEvent(PlatformEventType::WINDOW_RESIZE, new PlatformEventArgs{width, height});
        result = 0;
    }
    break;
    case WM_CLOSE:
    {
        OutputDebugStringA("Closing window...\n");
        BOOL r = DestroyWindow(handle);
        if (r)
        {
            // TODO: Move to logging system
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

void Win32Platform::ResizeBackbuffer(i32 newWidth, i32 newHeight)
{
    // TODO: Release old buffer (going to mem leak)
    // MEMORY LEAKING LIKE CRAZY
    
    // Create new bitMapInfo
    bitMapInfo = {};
    bitMapInfo.bmiHeader.biSize = sizeof(bitMapInfo.bmiHeader);
    bitMapInfo.bmiHeader.biWidth = newWidth;
    bitMapInfo.bmiHeader.biHeight = -newHeight;
    bitMapInfo.bmiHeader.biPlanes = 1;
    bitMapInfo.bmiHeader.biBitCount = 32; // RGBa 8 bits * 4 values giving us (0-255, 0-255, 0-255, 0-255)
    bitMapInfo.bmiHeader.biCompression = BI_RGB;


    // Allocate new back buffer
    i32 backBufferSize = (newWidth * newHeight) * bytesPerPixel;
    backBuffer = (u8*)VirtualAlloc(NULL, backBufferSize, MEM_COMMIT, PAGE_READWRITE);
    bufferWidth = newWidth;
    bufferHeight = newHeight;
    
    // Draw to buffer
    u32 stride = bufferWidth * bytesPerPixel;
    u8* row = (u8*)backBuffer;
    for(u32 Y = 0; Y < bufferHeight; ++Y)
    {   
        // Row of Pixel
        u8* pixel = row;
        for(u32 X = 0; X < bufferWidth; ++X)
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

void Win32Platform::DrawBuffer(RECT* windowRect)
{
    u32 windowWidth = windowRect->right - windowRect->left;
    u32 windowHeight = windowRect->bottom - windowRect->top;
    HDC context = GetDC(windowHandle);
    StretchDIBits(
        context,
        0,
        0, 
        windowWidth,
        windowHeight,
        0,
        0,
        bufferWidth,
        bufferHeight,
        backBuffer,
        &bitMapInfo,
        DIB_RGB_COLORS,
        SRCCOPY
    );
    ReleaseDC(windowHandle, context);
}
