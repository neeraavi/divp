#pragma once
#include <chrono>
class dateUtils
{
    const std::chrono::year_month_day ymd{floor<std::chrono::days>(std::chrono::system_clock::now())};
public:
    int getCurrentYear() const;
    unsigned getCurrentMonth() const;
};
