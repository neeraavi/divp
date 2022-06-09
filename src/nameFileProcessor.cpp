#include "nameFileProcessor.hpp"
#include "fileUtils.hpp"
#include "strUtils.hpp"

using namespace std;

NameFileProcessor::NameFileProcessor(const std::string &pathToNameFile)
{
   initialize(pathToNameFile);
}

void NameFileProcessor::initialize(const std::string &namesFile)
{
   const auto namesVec = readFile(namesFile);
   printLines(namesVec);

   for (const auto &l : namesVec)
   {
      const auto n = Name{l};
      cout << n;
      nameMap.emplace(n.name, n);
      addValueToVectorMap(sectorMap, n.sector, n.name);
   }
}

void NameFileProcessor::print() const
{
   for (const auto &[key, value] : sectorMap)
   {
      std::cout << key << ": ";
      printStringVector(value);
   }
}
