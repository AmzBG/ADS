/*-- Account.h -------------------------------------------------------------

  This header file defines the Account class, which represents a bank
  account. It includes operations to manage account details, update balance,
  handle transactions, and perform sorting on transactions.

  Basic operations include:
     - Constructors: Default and parameterized constructors
     - Transaction Management: Add, remove, and search transactions
     - Balance Update: Update the account balance
     - Sorting: Radix sort transactions
     - Stream Operations: Input and output operators for the Account class

---------------------------------------------------------------------------*/

#pragma once

#include <string>
#include <iostream>
#include <vector>
#include "Transaction.h"

using namespace std;

class Account {

private:
    /******** Data Members ********/
    int accountNumber;              // Unique account number
    string description;             // Description of the account
    double balance;                 // Current account balance
    vector<Transaction> transactions; // List of transactions associated with the account

    /******** Private Member Functions ********/
    void readAccount(istream &);
    /*----------------------------------------------------------------------
    Read account details from an input stream.

    Precondition:  The input stream 'in' is open and valid.
    Postcondition: Reads the account's data (number, description, balance)
    from the input stream.
    -----------------------------------------------------------------------*/

    void printAccount(ostream &) const;
    /*----------------------------------------------------------------------
    Print account details to an output stream.

    Precondition:  The output stream 'out' is open.
    Postcondition: Writes the account's details to the output stream.
    -----------------------------------------------------------------------*/

public:
    /******** Constructors ********/
    Account();
    /*----------------------------------------------------------------------
    Construct an Account object with default values.

    Precondition:  None.
    Postcondition: An Account object is created with default values for
    accountNumber (0), description (empty string), and balance (0.0).
    -----------------------------------------------------------------------*/

    Account(int accountNumber, const string &description, double balance);
    /*----------------------------------------------------------------------
    Construct an Account object with specified values.

    Precondition:  accountNumber must be a positive integer, description
    is a non-empty string, and balance is a valid double.
    Postcondition: An Account object is initialized with the given values.
    -----------------------------------------------------------------------*/

    /******** Transaction Management ********/
    void addTransaction(const Transaction &transaction);
    /*----------------------------------------------------------------------
    Add a transaction to the account.

    Precondition:  The transaction is valid.
    Postcondition: The transaction is added to the account's transaction list.
    -----------------------------------------------------------------------*/

    Transaction removeTransaction(int transactionID);
    /*----------------------------------------------------------------------
    Remove a transaction by its ID.

    Precondition:  transactionID corresponds to an existing transaction.
    Postcondition: The transaction with the specified ID is removed and
    returned. If no transaction matches, an error is handled.
    -----------------------------------------------------------------------*/

    vector<Transaction>::iterator findTransaction(int transactionID);
    /*----------------------------------------------------------------------
    Find a transaction by its ID.

    Precondition:  transactionID is valid.
    Postcondition: Returns an iterator to the transaction if found, or to
    transactions.end() if not found.
    -----------------------------------------------------------------------*/

    /******** Balance Management ********/
    void updateBalance(double amount);
    /*----------------------------------------------------------------------
    Update the account balance by adding the specified amount.

    Precondition:  amount is a valid double.
    Postcondition: The balance is updated by adding the amount.
    -----------------------------------------------------------------------*/

    /******** Account Number Comparison ********/
    bool compAccountNumber(const int number) const;
    /*----------------------------------------------------------------------
    Compare the account number with a given number.

    Precondition:  number is a valid integer.
    Postcondition: Returns true if the account number matches the given number,
    otherwise returns false.
    -----------------------------------------------------------------------*/

    /******** Sorting ********/
    void radixSortTransactions();
    /*----------------------------------------------------------------------
    Perform radix sort on the account's transactions.

    Precondition:  The transaction list is populated.
    Postcondition: The transaction list is sorted in ascending order.
    -----------------------------------------------------------------------*/

    void countingSortByDigit(vector<Transaction> &transactions, int digit);
    /*----------------------------------------------------------------------
    Perform counting sort on the transactions based on a specific digit.

    Precondition:  transactions is non-empty, and digit is a valid index.
    Postcondition: transactions is sorted based on the specified digit.
    -----------------------------------------------------------------------*/

    /******** Getters ********/
    int getAccountNumber() const;
    /*----------------------------------------------------------------------
    Get the account number.

    Precondition:  None.
    Postcondition: Returns the account number.
    -----------------------------------------------------------------------*/

    double getBalance() const;
    /*----------------------------------------------------------------------
    Get the account balance.

    Precondition:  None.
    Postcondition: Returns the account's current balance.
    -----------------------------------------------------------------------*/

    string getDescription() const;
    /*----------------------------------------------------------------------
    Get the account description.

    Precondition:  None.
    Postcondition: Returns the account's description.
    -----------------------------------------------------------------------*/

    const vector<Transaction>& getTransactions() const;
    /*----------------------------------------------------------------------
    Get the list of transactions associated with the account.

    Precondition:  None.
    Postcondition: Returns a constant reference to the transaction list.
    -----------------------------------------------------------------------*/

    /******** Setters ********/
    void setAccountNumber(int accountNumber);
    /*----------------------------------------------------------------------
    Set the account number.

    Precondition:  accountNumber must be a positive integer.
    Postcondition: Updates the account number.
    -----------------------------------------------------------------------*/

    /******** Stream Operators ********/
    friend istream& operator>>(istream &in, Account &account);
    /*----------------------------------------------------------------------
    Input stream extraction operator for an Account object.

    Precondition:  The input stream 'in' is open and valid.
    Postcondition: Reads account data (number, description, balance) from
    the input stream and initializes the account object.
    -----------------------------------------------------------------------*/

    friend ostream& operator<<(ostream &out, const Account &account);
    /*----------------------------------------------------------------------
    Output stream insertion operator for an Account object.

    Precondition:  The output stream 'out' is open.
    Postcondition: Writes account data to the output stream.
    -----------------------------------------------------------------------*/

};
