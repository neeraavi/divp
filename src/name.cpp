#include "name.hpp"
#include "strUtils.hpp"

using namespace std;

Name::Name(vector<string> v)
    : ticker{toLower(v[0])}
    , name{v[1]}
    , sector{v[2]}
{
}

std::ostream &operator<<(std::ostream &o, Name const &n)
{
   return o << n.ticker << ";" << n.name << "; " << n.sector << endl;
}
