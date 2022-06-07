#include "transaction.hpp"
#include <regex>

using namespace std;
static const auto buy = std::regex("buy", std::regex_constants::icase);

Transaction::Transaction(vector<string> v)
    : ticker{v[0]}
    , year{(unsigned int)stoi(v[1])}
    , month{(unsigned int)stoi(v[2])}
    , transactionType{regex_match(v[4], buy) ? TransactionType::buy : TransactionType::sell}
    , howMany{(unsigned int)stoi(v[5])}
    , cost{stod(v[6])}
{
   ym = v[1] + "-" + v[2];
}

          std::ostream
          & operator<<(std::ostream &os, TransactionType t)
{
   switch (t)
   {
   case TransactionType::buy:
      os << "buy";
      break;
   case TransactionType::sell:
      os << "sell";
      break;
   }
   return os;
}

std::ostream &operator<<(std::ostream &o, Transaction const &t)
{
   return o << t.ticker << "; "
            << "; " << t.ym << ";" << t.transactionType << "; " << t.howMany
            << "; " << t.cost << endl;
}
