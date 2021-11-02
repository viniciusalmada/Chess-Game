#pragma once
#include <string>
#include <iostream>

class Log
{
public:
  static void logDebug(std::string message);

};

inline void Log::logDebug(std::string message)
{
#ifdef _DEBUG
  std::cout << message << std::endl;
#endif // _DEBUG

}