#pragma once

#include <string>
#include <iomanip>

using namespace std;

class Transaction {
    private:
        int id;
        double amount;
        char type;

    public:
        Transaction(int);
        Transaction(int, double, char);

        // Getters
        double getAmount() const;
        char getType() const;
        int getId() const;

        // Operators
        bool operator<(const Transaction &) const; // used for sorting
        friend ostream& operator<<(ostream &, const Transaction &);
        friend istream& operator>>(istream &, Transaction &);
};
