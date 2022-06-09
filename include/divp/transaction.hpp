#pragma once
#include <string>
#include <vector>

enum class TransactionType
{
   buy,
   sell
};

std::ostream &operator<<(std::ostream &os, TransactionType t);

class Transaction
{
 public:
   std::string ticker{};//NOLINT
   unsigned int year{};//NOLINT
   unsigned int month{};//NOLINT
   TransactionType transactionType{};//NOLINT
   unsigned int howMany{};//NOLINT
   double cost{};//NOLINT
   std::string ym{};//NOLINT

   explicit Transaction(std::vector<std::string> v);
   friend std::ostream &operator<<(std::ostream &o, Transaction const &t);
};
