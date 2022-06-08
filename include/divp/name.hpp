#pragma once
#include "name.hpp"
#include <string>
#include <vector>
#include <map>
#include <iostream>
#include "vectorAndMapUtils.hpp"

using namespace std;

class Name
{
   std::map<std::string, Name> nameMap{};
   StringVectorMap sectorMap{};

 public:
   std::string ticker{};
   std::string name{};
   std::string sector{};

   Name(std::vector<std::string>);
   void initialize();
   friend std::ostream &operator<<(std::ostream &, Name const &);
};
