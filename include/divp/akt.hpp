#pragma once
#include "fileUtils.hpp"
#include "transaction.hpp"
#include <map>
#include <string>

class Akt
{
   void initialize();
   void fillTransactionMap();

   linesAsVector tVec{};

 public:
   Akt(std::string pathToAktFile);
   void print() const;

   std::map<std::string, double> yearMonthTransactionTotalMap{};
   std::map<std::string, Transaction> transactionsMap{};
};
