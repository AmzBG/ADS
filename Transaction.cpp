#include "Transaction.h"

// Constructor
Transaction::Transaction(int id, double amount, char type, const string &description)
    : id(id), amount(amount), type(type), description(description) {}

// Getters
double Transaction::getAmount() const {
    return amount;
}

char Transaction::getType() const {
    return type;
}
int Transaction::getId() const {
    return id;
}
string Transaction::getDescription() const {
    return description;
}

// Operators
bool Transaction::operator<(const Transaction &other) const {
    return this->id < other.id;
}

// Output operator for printing transaction details
ostream& operator<<(ostream &out, const Transaction &trans) {
    out << "\t Transaction ID: " << trans.getId() << "\n"
       << "\t Amount: " << fixed << setprecision(2) << trans.getAmount()<< "\n"
       << "\t Type: " << (trans.getType() == 'D' ? "Debit" : "Credit") << "\n"
       << "\t Description: " << trans.getDescription()<<"\n";
    return out;
}

// Input operator for reading transaction details
istream& operator>>(istream &in, Transaction &trans) {
    in >> trans.id;
    in >> trans.amount;
    in >> trans.type;
    // in.ignore();  // To ignore the newline character that may remain after reading 'type'
    getline(in, trans.description);
    return in;
}
