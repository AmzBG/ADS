#pragma once

#include <string>
#include <iostream> // online gdb
#include <iomanip>

using namespace std;

class Transaction {
    private:
        int id;
        double amount;
        char type;

    public:
        Transaction();
        Transaction(int);
        Transaction(int, double, char);

        // Getters
        double getAmount() const;
        char getType() const;
        int getId() const;

        // Setters
        bool setType(char);
        void setId(int);

        void printWithIndentation(int, ostream &) const;

        // Operators
        friend ostream& operator<<(ostream &, const Transaction &);
        friend istream& operator>>(istream &, Transaction &);
};
