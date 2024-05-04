#include "CarbonLogger.h"


CarbonLogger* CarbonLogger::m_instance = 0;

CarbonLogger* CarbonLogger::current()
{
    if (m_instance == nullptr)
    {
        m_instance = new CarbonLogger();
    }

    return m_instance;
}


CarbonLogger::CarbonLogger()
{
    return;
}

void CarbonLogger::info(std::string message)
{
    OutputDebugStringA(message.c_str());
}

void CarbonLogger::warn(std::string message)
{
    OutputDebugStringA(message.c_str());
}

void CarbonLogger::error(std::string message)
{
    OutputDebugStringA(message.c_str());
}

void CarbonLogger::winError()
{
    u32 errorCode = GetLastError();
    LPVOID msgBuffer;

    FormatMessage(
            FORMAT_MESSAGE_ALLOCATE_BUFFER | 
            FORMAT_MESSAGE_FROM_SYSTEM |
            FORMAT_MESSAGE_IGNORE_INSERTS,
            NULL,
            errorCode,
            MAKELANGID(LANG_NEUTRAL, SUBLANG_NEUTRAL),
            (LPTSTR) &msgBuffer,
            0,
            NULL
    );

    OutputDebugStringA((LPCSTR)msgBuffer);
}
