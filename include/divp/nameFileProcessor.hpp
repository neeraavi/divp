#pragma once
#include "name.hpp"
#include <map>
#include <string>

class NameFileProcessor
{
   std::map<std::string, Name> nameMap{};
   StringVectorMap sectorMap{};

   void initialize(const std::string& namesFile);

 public:
   explicit NameFileProcessor(const std::string &namesFile);
   void print() const;
};
