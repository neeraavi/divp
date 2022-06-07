//#include "Config.h"
#include "fileUtils.hpp"
#include "dateUtils.hpp"
#include "name.hpp"
#include "transaction.hpp"
#include "vectorAndMapUtils.hpp"
#include <iostream>
#include <map>
#include <sstream>
#include <iomanip>

using namespace std;

void init(map<string, double> &ymTransTotalMap)
{
    const auto du  = dateUtils();
    const auto thisYear = du.getCurrentYear();
    const int startYear = 2017;
    ostringstream out;
    out <<  std::setfill('0') ;
    for (auto y=startYear; y<=thisYear; ++y)
    {
        for (auto m=1; m<=12; ++m)
        {
            out << std::setw(2) << m;
            auto ym=to_string(y) + "-" + out.str();
            out.str("");
            //cout<<ym<<endl;
            ymTransTotalMap.emplace(ym,0);
        }
    }
}

int main(int argc, char *argv[])
{
     if(argc<2)
     {
         cout << "Usage: divp <path/to/div>" << endl;
         return 1;
     }
     string path{argv[1]};
   // cout << "dv: Version " << dv_VERSION_MAJOR << "." << dv_VERSION_MINOR
   //      << endl;
   const string namesFile = path+"names.txt";
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

   const auto aktFile = path+"akt.txt";
   const auto tVec = readFile(aktFile);
   map<string, double> yearMonthTransactionTotalMap{};
   init(yearMonthTransactionTotalMap);
   // printLines(transactions);
   map<string, Transaction> transactionsMap{};

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
   for (const auto &[key, value] : yearMonthTransactionTotalMap)
   {
      cout << key << ": " << value << endl;
   }
   return 0;
}

