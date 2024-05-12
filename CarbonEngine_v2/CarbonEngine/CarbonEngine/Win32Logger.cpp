#include "CarbonLogger.h"


void LogInfo(std::string message)
{
  OutputDebugStringA(message.c_str());
  OutputDebugStringA("\n");
}

void LogWarn(std::string message)
{
  OutputDebugStringA(message.c_str());
  OutputDebugStringA("\n");
}

void LogError(std::string message)
{
  OutputDebugStringA(message.c_str());
  OutputDebugStringA("\n");
}

void LogWinError()
{
  unsigned int errorCode = GetLastError();
  LPVOID msgBuffer;

  FormatMessage(
    FORMAT_MESSAGE_ALLOCATE_BUFFER |
    FORMAT_MESSAGE_FROM_SYSTEM |
    FORMAT_MESSAGE_IGNORE_INSERTS,
    NULL,
    errorCode,
    MAKELANGID(LANG_NEUTRAL, SUBLANG_NEUTRAL),
    (LPTSTR)&msgBuffer,
    0,
    NULL
  );

  OutputDebugStringA((LPCSTR)msgBuffer);
}