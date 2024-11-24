#include "Transaction.h"

// Constructor
Transaction::Transaction(int id, double amount, char type)
    : id(id), amount(amount), type(type) {}

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

bool Transaction::operator<(const Transaction &other) const {
    return this->id < other.id;
}

ostream& operator<<(ostream &out, const Transaction &trans) {
    out << "\t Transaction ID: " << trans.getId() << "\n"
       << "\t Amount: " << fixed << setprecision(2) << trans.getAmount()<< "\n"
       << "\t Type: " << (trans.getType() == 'D' ? "Debit" : "Credit") << "\n";
    return out;
}

istream& operator>>(istream &in, Transaction &trans) {
    in >> trans.id;
    in >> trans.amount;
    in >> trans.type;
    // in.ignore();  // To ignore the newline character that may remain after reading 'type'
    return in;
}
