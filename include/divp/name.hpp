#pragma once
#include <string>
#include <vector>
using namespace std;

class Name
{
 public:
   std::string ticker{};
   string name{};
   string sector{};

   Name(vector<string>);
   friend std::ostream &operator<<(std::ostream &, Name const &);
};
