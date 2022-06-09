#include "fileUtils.hpp"
#include "strUtils.hpp"
#include <fstream>
#include <iostream>
#include <regex>
#include <string>
#include <vector>
#include <cstdlib>

using namespace std;

linesAsVector readFile(const string &filename)
{
   ifstream inFile(filename);
   if (!inFile.good())
   {
      cout << filename << " not found!" << endl;
      std::exit(EXIT_FAILURE);
   }

   linesAsVector lines;
   string line;
   string part;
   std::vector<std::string> parts;
   while (inFile)
   {
      getline(inFile, line);
      if ((line.rfind('#', 0) == 0) ||
          (line.find_first_not_of(' ') == std::string::npos))
      {
         continue;
      }
      std::replace(line.begin(), line.end(), '_', ' ');
      istringstream l(line);
      while (getline(l, part, '-'))
      {
         parts.emplace_back(trim(part));
      }
      lines.emplace_back(parts);
      parts.clear();
      //      cout << line << endl;
   }
   return lines;
}

void printLines(const linesAsVector &lines)
{
   for (const auto &l : lines)
   {
      for (const auto &p : l)
      {
         cout << p << " -- ";
      }
      cout << endl;
   }
}

void printStringVector(const std::vector<std::string> &v)
{
   for (const auto &item : v)
   {
      cout << item << ",";
   }
   cout << std::endl;
}
