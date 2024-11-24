#pragma once
#include <string>
#include <iostream>
#include <queue>
#include "Transaction.h"

using namespace std;

class Account {
private:
  int accountNumber;
  string description;
  double balance;
  vector<Transaction> transactions;
  void readAccount(istream &);
  void printAccount(ostream &) const;


public:
  Account();
  Account(int, const string &, double);
  void addTransaction(const Transaction &);
  Transaction removeTransaction(int);
  void updateBalance(double);
  bool compAccountNumber(const int) const;
  Transaction findTransaction(const int) const;
  
  // Getters
  int getAccountNumber() const;
  double getBalance() const;
  string getDescription() const;
  const vector<Transaction>& getTransactions() const;

  friend istream& operator>>(istream &, Account &);
  friend ostream& operator<<(ostream &, const Account &);
};
