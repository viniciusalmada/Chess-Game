#include "sp_string.h"

SP::String::String() : mStr("")
{
}

SP::String::String(std::string base) : mStr(base)
{
}

std::vector<SP::String> SP::String::split(std::string delimiter) const
{
  std::string strCopy = mStr;
  size_t pos = 0;
  std::vector<SP::String> splits;
  while ((pos = strCopy.find(delimiter)) != std::string::npos)
  {
    SP::String token = strCopy.substr(0, pos);
    splits.push_back(token);
    strCopy.erase(0, pos + delimiter.length());
  }
  splits.push_back(strCopy);
  return splits;
}

SP::String SP::String::appendAll(std::vector<SP::String> strings, std::string joinStr) const
{
  std::string strCopy = mStr;
  for (auto s : strings)
  {
    strCopy.append(s.getStr()).append(joinStr);
  }
  return { strCopy };
}
