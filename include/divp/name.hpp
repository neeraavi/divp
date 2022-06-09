#pragma once
#include "name.hpp"
#include "vectorAndMapUtils.hpp"
#include <iostream>
#include <map>
#include <string>
#include <vector>

class Name
{
   std::map<std::string, Name> nameMap{};
   StringVectorMap sectorMap{};

 public:
   std::string ticker{}; // NOLINT
   std::string name{};   // NOLINT
   std::string sector{}; // NOLINT

   explicit Name(std::vector<std::string> vec);
   void initialize();
   friend std::ostream &operator<<(std::ostream &o, Name const &n);
};
