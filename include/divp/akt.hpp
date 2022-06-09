#pragma once
#include "fileUtils.hpp"
#include "transaction.hpp"
#include <map>
#include <string>

class AktFileProcessor
{
   void initialize();
   void fillTransactionMap();

   linesAsVector tVec{}; //NOLINT
   std::map<std::string, double> yearMonthTransactionTotalMap{}; //NOLINT
   std::map<std::string, Transaction> transactionsMap{}; //NOLINT

 public:
   explicit AktFileProcessor(const std::string& pathToAktFile);
   void print() const;

};
