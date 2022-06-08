#include "akt.hpp"
#include "dateUtils.hpp"
#include <iomanip>
#include <iostream>
#include <map>
#include <sstream>

using namespace std;

Akt::Akt(string pathToAktFile)
{
   tVec = readFile(pathToAktFile);
   initialize();
   fillTransactionMap();
}

void Akt::initialize()
{
   const auto du = dateUtils();
   const auto thisYear = du.getCurrentYear();
   const int startYear = 2017;
   ostringstream out;
   out << std::setfill('0');
   for (auto y = startYear; y <= thisYear; ++y)
   {
      for (auto m = 1; m <= 12; ++m)
      {
         out << std::setw(2) << m;
         auto ym = to_string(y) + "-" + out.str();
         out.str("");
         yearMonthTransactionTotalMap.emplace(ym, 0);
      }
   }
}

void Akt::fillTransactionMap()
{
   for (const auto &l : tVec)
   {
      const auto t = Transaction{l};
      transactionsMap.emplace(t.ticker, t);
      cout << t;
      const auto it = yearMonthTransactionTotalMap.find(t.ym);
      const int factor = (t.transactionType == TransactionType::buy) ? 1 : -1;
      if (it != yearMonthTransactionTotalMap.end())
      {
         it->second += factor * t.cost;
      }
      else
      {
         yearMonthTransactionTotalMap.emplace(t.ym, factor * t.cost);
      }
   }
}

void Akt::print() const
{
   for (const auto &[key, value] : yearMonthTransactionTotalMap)
   {
      cout << key << ": " << value << endl;
   }
}
