#pragma once
#include <string>
#include <stdio.h>
#include <windows.h>

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

static LogLevel logLevel = LogLevel::INFO;

void LogInfo(std::string message);
void LogWarn(std::string message);
void LogError(std::string message);
void LogWinError();