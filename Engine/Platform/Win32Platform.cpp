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

Win32Platform::Win32Platform(const char* applicationName, i32 x, i32 y, i32 width, i32 height)
{   
    this->windowWidth = width;
    this->windowHeight = height;
    this->windowX = x;
    this->windowY = y;
    this->applicationName = applicationName;
    this->bytesPerPixel = 4;

    PlatformEventManager* current = PlatformEventManager::current();
    current->subscribe(PlatformEventType::WINDOW_RESIZE, new PlatformEventHandler<Win32Platform>(this, &Win32Platform::ResizeWindowHandler));
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
    u32 windowWidth = windowRect.right - windowRect.left;
    u32 windowHeight = windowRect.bottom - windowRect.top;
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

void Win32Platform::ResizeWindowHandler(PlatformEventArgs* args)
{
    i32 width = args->first;
    i32 height = args->second;
    u32 i = 9;

    // Release old memory if it exists 
    if (backBuffer)
    {
        Vfree((void*)backBuffer, 0);
    }

    // Create new bitMapInfo
    bitMapInfo = {};
    bitMapInfo.bmiHeader.biSize = sizeof(bitMapInfo.bmiHeader);
    bitMapInfo.bmiHeader.biWidth = width;
    bitMapInfo.bmiHeader.biHeight = -height; // Negative so we go top down 
    bitMapInfo.bmiHeader.biPlanes = 1;
    bitMapInfo.bmiHeader.biBitCount = 32; // RGBa 8 bits * 4 values giving us (0-255, 0-255, 0-255, 0-255)
    bitMapInfo.bmiHeader.biCompression = BI_RGB;

    // Allocate new back buffer
    bufferSize = (width * height) * bytesPerPixel;
    backBuffer = (u8*)Valloc(bufferSize);
    bufferWidth = width;
    bufferHeight = height;


    Win32Draw();
}

void* Win32Platform::Valloc(u32 size)
{
    LPVOID memory = VirtualAlloc(NULL, size, MEM_COMMIT, PAGE_READWRITE);
    // Check if allocation failed
    if (!memory)
    {
        // CarbonLogger* logger = CarbonLogger::current();
        // logger->error("Could not allocate memory in virtual address space.\n");
        // logger->winError();
    }
    return (void*)memory;
}

void Win32Platform::Vfree(void* ptr, unsigned int size)
{
    VirtualFree(
        ptr,
        0,
        MEM_RELEASE
    );
}

void* Win32Platform::Halloc(unsigned int size)
{
    HANDLE heapHandle = GetProcessHeap();

    // Check if we were unable to get process heap
    if (heapHandle == NULL)
    {
        CarbonLogger* logger = CarbonLogger::current();
        logger->error("Could not get handle to process heap.\n");
        logger->winError();
        return nullptr;
    }

    LPVOID memory = HeapAlloc(heapHandle, HEAP_ZERO_MEMORY, size);
    return memory;
}

void Win32Platform::Hfree(void* ptr)
{
    CarbonLogger* logger = CarbonLogger::current();

    HANDLE heapHandle = GetProcessHeap();
    if (heapHandle == NULL)
    {
        logger->error("Could not get handle to process heap.\n");
        logger->winError();
        return;
    }

    BOOL result = HeapFree(heapHandle, HEAP_NO_SERIALIZE, ptr);
    // Check if free operation failed
    if (!result)
    {
        logger->error("Could not free memory in heap.\n");
        logger->winError();
    }
}

/* Private Methods */

LRESULT CALLBACK WindowProc(HWND handle, UINT msg, WPARAM wparam, LPARAM lparam)
{

    i64 result = 0;

    switch (msg)
    {
    case WM_SIZE:
    {
        int width = (int)LOWORD(lparam);
        int height = (int)HIWORD(lparam);
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

