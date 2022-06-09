#include "strUtils.hpp"

std::string ltrim(const std::string &s)
{
   return std::regex_replace(s, spaceAtBeginning, emptyString);
}

std::string rtrim(const std::string &s)
{
   return std::regex_replace(s, spaceAtEnd, emptyString);
}

std::string trim(const std::string &s) { return ltrim(rtrim(s)); }

std::string toLower(std::string &data)
{
   // NOLINTNEXTLINE(bugprone-narrowing-conversions,
   // cppcoreguidelines-narrowing-conversions)
   std::for_each(data.begin(), data.end(), [](char &c) { c = ::tolower(c); });
   return data;
}
