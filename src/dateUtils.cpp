#include "dateUtils.hpp"
#include <chrono>

int dateUtils::getCurrentYear() const { return static_cast<int>(ymd.year()); }
unsigned dateUtils::getCurrentMonth() const
{
   return static_cast<unsigned>(ymd.month());
}
