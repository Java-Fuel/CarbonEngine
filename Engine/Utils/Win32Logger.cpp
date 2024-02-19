#include "CarbonLogger.h"

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