#ifndef CARBONLOGGER_H
#define CARBONLOGGER_H

#include <string>
#include <stdio.h>
#include <windows.h>
#include "Defines.h"

/*
TODO: Currently we are just logging to windows debug console, we will need to:
    - Output to file
    - Output to console window in engine
    - Output to console window in game
TODO: Add bit signature variable to keep track of which logging types are enabled:
    - File 
    - Console
    - Engine/Game Terminal
*/

enum LogLevel
{
    INFO,
    WARN,
    ERR
};

CAPI class CarbonLogger
{
public:
    LogLevel logLevel;

private:
    static CarbonLogger* m_instance;

public:
    static CarbonLogger* current();
    void info(std::string message);
    void warn(std::string message);
    void error(std::string message);
    void winError();

protected:
    CarbonLogger();
};

#include "Logger_inl.h"

#endif