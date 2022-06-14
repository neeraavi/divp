#pragma once
#include <set>
#include <string>
#include <vector>

class Sector
{
   std::string sector;
   std::set<std::string> tickers;
   double total;

 public:
   Sector(std::vector<std::string> lineAsVector);
};