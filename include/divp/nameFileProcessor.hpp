#pragma once
#include "name.hpp"
#include <map>
#include <string>

class NameFileProcessor
{
   std::map<std::string, Name> nameMap{};
   StringVectorMap sectorMap{};

   void initialize(std::string);

 public:
   NameFileProcessor(std::string);
   void print() const;
};
