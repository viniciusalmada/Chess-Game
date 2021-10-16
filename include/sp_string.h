#pragma once
#include <string>
#include <vector>

namespace SP
{
  class String
  {
    std::string mStr;

  public:
    String();

    String(std::string base);
    
    std::vector<SP::String> split(std::string delimiter) const;

    std::string getStr() const { return mStr; }

    SP::String appendAll(std::vector<SP::String> strings, std::string joinStr = "") const;
  };
}