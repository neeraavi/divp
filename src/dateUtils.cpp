#include <chrono>
#include "dateUtils.hpp"

using namespace std::chrono;

int getCurrentYear()
{
    const auto ymd = std::chrono::year_month_day{floor<days>(system_clock::now())};
    return static_cast<int>(ymd.year());
}
unsigned getCurrentMonth()
{
    const auto ymd = year_month_day{floor<days>(system_clock::now())};
    return static_cast<unsigned>(ymd.month());
}
