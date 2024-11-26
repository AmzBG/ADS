/*-- Transaction.h ----------------------------------------------------------

  This header file defines the Transaction class, which represents a
  single financial transaction with attributes for ID, amount, and type.

  Basic operations include:
     - Constructors: Default and parameterized constructors
     - Getters and setters for transaction attributes
     - Stream operations for input and output
     - Custom print function for formatted display

----------------------------------------------------------------------------*/

#pragma once

#include <string>
#include <iostream>
#include <iomanip>

using namespace std;

class Transaction {
private:
    /******** Data Members ********/
    int id;        // Unique identifier for the transaction
    double amount; // Transaction amount
    char type;     // Transaction type ('D' for deposit, 'W' for withdrawal, etc.)

public:
    /******** Constructors ********/
    Transaction();
    /*----------------------------------------------------------------------
    Construct a Transaction object with default values.

    Precondition:  None.
    Postcondition: A Transaction object is created with id = 0,
    amount = 0.0, and type = '\0'.
    -----------------------------------------------------------------------*/

    Transaction(int id);
    /*----------------------------------------------------------------------
    Construct a Transaction object with a specified ID.

    Precondition:  id is a valid integer.
    Postcondition: A Transaction object is created with the given id,
    amount = 0.0, and type = '\0'.
    -----------------------------------------------------------------------*/

    Transaction(int id, double amount, char type);
    /*----------------------------------------------------------------------
    Construct a Transaction object with specified ID, amount, and type.

    Precondition:  id is a valid integer, amount is a valid double, and
    type is a valid character ('D', 'W', etc.).
    Postcondition: A Transaction object is created with the given values.
    -----------------------------------------------------------------------*/

    /******** Getters ********/
    double getAmount() const;
    /*----------------------------------------------------------------------
    Get the amount of the transaction.

    Precondition:  None.
    Postcondition: Returns the amount of the transaction.
    -----------------------------------------------------------------------*/

    char getType() const;
    /*----------------------------------------------------------------------
    Get the type of the transaction.

    Precondition:  None.
    Postcondition: Returns the type of the transaction ('D', 'W', etc.).
    -----------------------------------------------------------------------*/

    int getId() const;
    /*----------------------------------------------------------------------
    Get the ID of the transaction.

    Precondition:  None.
    Postcondition: Returns the ID of the transaction.
    -----------------------------------------------------------------------*/

    /******** Setters ********/
    bool setType(char type);
    /*----------------------------------------------------------------------
    Set the type of the transaction.

    Precondition:  type is a valid character ('D', 'W', etc.).
    Postcondition: If the type is valid, updates the transaction type and
    returns true; otherwise, returns false.
    -----------------------------------------------------------------------*/

    void setId(int id);
    /*----------------------------------------------------------------------
    Set the ID of the transaction.

    Precondition:  id is a valid integer.
    Postcondition: Updates the transaction's ID.
    -----------------------------------------------------------------------*/

    /******** Printing ********/
    void printWithIndentation(int indentation, ostream &out) const;
    /*----------------------------------------------------------------------
    Print the transaction details with specified indentation.

    Precondition:  indentation is a non-negative integer, and the output
    stream 'out' is open.
    Postcondition: Outputs the transaction details to the stream with the
    specified indentation.
    -----------------------------------------------------------------------*/

    /******** Stream Operators ********/
    friend ostream& operator<<(ostream &out, const Transaction &transaction);
    /*----------------------------------------------------------------------
    Output stream insertion operator for a Transaction object.

    Precondition:  The ostream 'out' is open.
    Postcondition: Writes the transaction's details to the output stream
    in a formatted manner.
    -----------------------------------------------------------------------*/

    friend istream& operator>>(istream &in, Transaction &transaction);
    /*----------------------------------------------------------------------
    Input stream extraction operator for a Transaction object.

    Precondition:  The istream 'in' is open.
    Postcondition: Reads the transaction's ID, amount, and type from the
    input stream and initializes the object.
    -----------------------------------------------------------------------*/
};
