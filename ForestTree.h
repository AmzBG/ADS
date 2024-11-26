/*-- ForestTree.h -----------------------------------------------------------

  This header file defines the ForestTree class, which represents a hierarchical
  structure of accounts in a tree-like data structure. Each node contains an
  Account object and may have child and sibling nodes.

  Basic functionalities include:
     - Adding accounts
     - Managing transactions associated with accounts
     - Searching for accounts with tracking
     - Printing the tree structure or individual accounts to console or file
     - Building the tree structure from an input file
     - Writing the tree structure to an output file

----------------------------------------------------------------------------*/

#pragma once

#include <fstream>
#include <sstream>
#include <math.h>
#include <filesystem>
#include "Account.h"

using namespace std;

class ForestTree {
private:
    /******** Nested Node Class ********/
    class Node {
    public:
        Account data;    // Account data stored in the node
        Node* sibling;   // Pointer to the sibling node
        Node* child;     // Pointer to the child node

        Node(const Account & acc) : data(acc), sibling(nullptr), child(nullptr) {};
        /*----------------------------------------------------------------------
        Constructs a Node containing an Account.

        Precondition:  acc is a valid Account object.
        Postcondition: Node is initialized with given Account, and its sibling
        and child pointers are set to nullptr.
        -----------------------------------------------------------------------*/
    };

    typedef Node* nodePtr; // Pointer type alias for Node
    nodePtr root;          // Root of the ForestTree

public:
    /******** Constructors ********/
    ForestTree();
    /*----------------------------------------------------------------------
    Constructs an empty ForestTree.

    Precondition:  None.
    Postcondition: An empty ForestTree is initialized with root set to nullptr.
    -----------------------------------------------------------------------*/

    /******** Account Management ********/
    bool addAccount(const Account &acc);
    /*----------------------------------------------------------------------
    Adds an Account object to the tree.

    Precondition:  acc is a valid Account object.
    Postcondition: The account is inserted into the tree based on its
    account number. Returns true if successful, otherwise false.
    -----------------------------------------------------------------------*/

    bool addAccount(int accountNumber, const string description, double balance);
    /*----------------------------------------------------------------------
    Creates an Account and adds it to the tree.

    Precondition:  accountNumber is a unique integer, description is non-empty,
    and balance is a valid double.
    Postcondition: A new Account is created and added to the tree. Returns true
    if successful, otherwise false.
    -----------------------------------------------------------------------*/

    bool buildTreeFromFile(const string &filePath);
    /*----------------------------------------------------------------------
    Builds the ForestTree structure from an input file.

    Precondition:  filePath is a valid file path to an account data file.
    Postcondition: Accounts from the file are added to the ForestTree.
    Returns true if the operation succeeds, otherwise false.
    -----------------------------------------------------------------------*/

    /******** Searching ********/
    vector<nodePtr> searchAccountWithTracking(int accountNumber, vector<Account*> &tracking) const;
    /*----------------------------------------------------------------------
    Searches for an account by its account number with tracking.

    Precondition:  accountNumber is a valid integer. The tracking vector
    must be empty to store the search path.
    Postcondition: If the account is found, its path is stored in the tracking
    vector. Returns a vector containing the current and previous nodes.
    -----------------------------------------------------------------------*/

    vector<nodePtr> searchAccountWithTracking(int accountNumber) const;
    /*----------------------------------------------------------------------
    Searches for an account by its account number without tracking.

    Precondition:  accountNumber is a valid integer.
    Postcondition: Returns a vector containing the current and previous
    nodes for the matching account.
    -----------------------------------------------------------------------*/

    void findAccount(int accountNumber) const;
    /*----------------------------------------------------------------------
    Displays details of an account by its account number.

    Precondition:  accountNumber is a valid integer.
    Postcondition: Prints account details to the console if found, or an
    error message if not found.
    -----------------------------------------------------------------------*/

    /******** Transaction Management ********/
    void addAcountTransaction(int accountNumber, const Transaction &transaction);
    /*----------------------------------------------------------------------
    Adds a transaction to a specified account.

    Precondition:  accountNumber is a valid integer, and transaction is a
    valid Transaction object.
    Postcondition: The transaction is added to the account. If the account is
    part of a tracked path, the balances of related accounts are updated.
    -----------------------------------------------------------------------*/

    void removeAccountTransaction(int accountNumber, int transactionID);
    /*----------------------------------------------------------------------
    Removes a transaction from a specified account.

    Precondition:  accountNumber and transactionID are valid integers.
    Postcondition: The specified transaction is removed from the account.
    If the account is part of a tracked path, the balances of related
    accounts are updated.
    -----------------------------------------------------------------------*/

    /******** Printing ********/
    void printTree(nodePtr node, int depth, ostream &out) const;
    /*----------------------------------------------------------------------
    Prints the tree structure starting from a given node.

    Precondition:  node is a valid pointer, depth is non-negative, and
    out is an open output stream.
    Postcondition: The tree structure is printed to the output stream.
    -----------------------------------------------------------------------*/

    void printAccountRecursive(nodePtr node, int depth, ostream &out) const;
    /*----------------------------------------------------------------------
    Recursively prints account details starting from a given node.

    Precondition:  node is a valid pointer, depth is non-negative, and
    out is an open output stream.
    Postcondition: Account details are printed to the output stream with
    proper indentation.
    -----------------------------------------------------------------------*/

    void printAccount(int accountNumber) const;
    /*----------------------------------------------------------------------
    Prints the details of a specific account to a file.

    Precondition:  accountNumber is a valid integer.
    Postcondition: Account details are written to a file in a predefined
    directory. If the account is not found, an error message is displayed.
    -----------------------------------------------------------------------*/

    bool printTreeIntoFile(const string &fileName);
    /*----------------------------------------------------------------------
    Writes the entire tree structure to a specified file.

    Precondition:  fileName is a valid file path.
    Postcondition: The tree structure is written to the specified file.
    Returns true if successful, otherwise false.
    -----------------------------------------------------------------------*/

    void printTreeRecursive(nodePtr node, ostream &out);
    /*----------------------------------------------------------------------
    Recursively writes the tree structure starting from a given node.

    Precondition:  node is a valid pointer, and out is an open output stream.
    Postcondition: The tree structure is recursively written to the stream.
    -----------------------------------------------------------------------*/

    void printTransactions(const vector<Transaction> &transactions, int depth, ostream &out) const;
    /*----------------------------------------------------------------------
    Prints a list of transactions with specified indentation.

    Precondition:  transactions is a vector of Transaction objects, depth is
    non-negative, and out is an open output stream.
    Postcondition: Transactions are printed to the output stream with the
    specified indentation.
    -----------------------------------------------------------------------*/

    /******** Stream Operators ********/
    friend ostream& operator<<(ostream &out, const ForestTree &tree);
    /*----------------------------------------------------------------------
    Outputs the tree structure to a stream.

    Precondition:  The ostream 'out' is open.
    Postcondition: The entire tree structure is written to the stream.
    -----------------------------------------------------------------------*/
};
