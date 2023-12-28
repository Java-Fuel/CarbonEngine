#include "Logger.hpp"

using Logging::Logger;

void Logger::Info(std::string message)
{
  const char* msg = message.c_str();
  printf(msg);
}