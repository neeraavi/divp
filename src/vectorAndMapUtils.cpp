#include "vectorAndMapUtils.hpp"

void addValueToVectorMap(
    StringVectorMap &svm,
    const std::string &key,
    const std::string &value)
{
   auto it = svm.find(key);
   if (it != svm.end())
   {
      it->second.emplace_back(value);
      return;
   }

   std::vector<std::string> v{value};
   svm[key] = v;
}
