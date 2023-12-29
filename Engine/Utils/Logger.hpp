#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <string>
#include <stdio.h>

namespace Logging {

  class Logger {
    public:
      static void Info(std::string message);
  };
}

#endif