#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <string>
#include <stdio.h>

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
    WARNING,
    ERROR
};

class CarbonLogger
{
public:
    LogLevel loglevel;

private:
    static CarbonLogger* m_instance;

public:
    CarbonLogger();
    static CarbonLogger* Current();
    void Info(std::string message);
    void Warn(std::string message);
    void Error(std::string message);
};

#endif