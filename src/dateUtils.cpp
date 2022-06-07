#include <chrono>
#include "dateUtils.hpp"


int dateUtils::getCurrentYear() const
{
    return static_cast<int>(ymd.year());
}
unsigned dateUtils::getCurrentMonth() const
{
    return static_cast<unsigned>(ymd.month());
}
