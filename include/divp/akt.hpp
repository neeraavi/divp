#pragma once
#include "fileUtils.hpp"
#include "transaction.hpp"
#include <map>
#include <string>

class AktFileProcessor
{
   void initialize();
   void fillTransactionMap();

   linesAsVector tVec{};

 public:
   AktFileProcessor(std::string pathToAktFile);
   void print() const;

   std::map<std::string, double> yearMonthTransactionTotalMap{};
   std::map<std::string, Transaction> transactionsMap{};
};
