#include <map>
#include <string>
#include <vector>

using StringVectorMap = std::map<std::string, std::vector<std::string>>;

void addValueToVectorMap(
    StringVectorMap &svm,
    const std::string &key,
    const std::string &value);
