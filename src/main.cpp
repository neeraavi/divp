//#include "Config.h"
#include "fileUtils.hpp"
#include "name.hpp"
#include "transaction.hpp"
#include "vectorAndMapUtils.hpp"
#include <iostream>
#include <map>

using namespace std;

int main()
{
   // cout << "dv: Version " << dv_VERSION_MAJOR << "." << dv_VERSION_MINOR
   //      << endl;
   const auto namesFile = "/home/iyerns/iyer/div/names.txt";
   const auto namesVec = readFile(namesFile);
   printLines(namesVec);

   map<string, Name> nameMap{};
   StringVectorMap sectorMap{};
   for (const auto &l : namesVec)
   {
      const auto n = Name{l};
      cout << n;
      nameMap.emplace(n.name, n);
      addValueToVectorMap(sectorMap, n.sector, n.name);
   }

   for (const auto &[key, value] : sectorMap)
   {
      std::cout << key << ": ";
      printStringVector(value);
   }

   const auto aktFile = "/home/iyerns/iyer/div/akt.txt";
   const auto tVec = readFile(aktFile);
   // printLines(transactions);
   map<string, Transaction> transactionsMap{};
   map<string, double> yearMonthTransactionTotal{};
   for (const auto l : tVec)
   {
      const auto t = Transaction{l};
      transactionsMap.emplace(t.ticker, t);
      cout << t;
      const auto it = yearMonthTransactionTotal.find(t.ym);
      const int factor = (t.transactionType == TransactionType::buy) ? 1 : -1;
      if (it != yearMonthTransactionTotal.end())
      {
         it->second += factor * t.cost;
      }
      else
      {
         yearMonthTransactionTotal.emplace(t.ym, factor * t.cost);
      }
   }
   for (const auto &[key, value] : yearMonthTransactionTotal)
   {
      cout << key << ": " << value << endl;
   }
   return 0;
}
