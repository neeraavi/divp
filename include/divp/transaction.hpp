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
   std::string ticker{};
   unsigned int year{};
   unsigned int month{};
   TransactionType transactionType{};
   unsigned int howMany{};
   double cost{};
   std::string ym{};

   Transaction(std::vector<std::string>);
   friend std::ostream &operator<<(std::ostream &, Transaction const &);
};
