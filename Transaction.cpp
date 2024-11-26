#include "Transaction.h"

// Constructors
Transaction::Transaction()
    : id(0), amount(0.0), type('D') {}

Transaction::Transaction(int id)
    : id(id), amount(0.0), type('D') {}

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

bool Transaction::setType(char type) {
    if (tolower(type) == 'd' || tolower(type) == 'c') {
        this->type = toupper(type);
        return true;
    }
    return false;
}

void Transaction::printWithIndentation(int depth, ostream& out) const {
    string indent = string(depth * 2, ' ');
    out << indent << "Transaction ID: " << id << '\n';
    out << indent + "  " << "Amount: " << fixed << setprecision(2) << amount << '\n';
    out << indent + "  " << "Type: " << (type == 'D' ? "Debit" : "Credit") << '\n';
}

bool Transaction::operator<(const Transaction &other) const {
    return this->id < other.id;
}

ostream& operator<<(ostream& out, const Transaction& trans) {
    out << "Transaction ID: " << trans.getId() << "\n"
        << "Amount: " << fixed << setprecision(2) << trans.getAmount() << "\n"
        << "Type: " << (trans.getType() == 'D' ? "Debit" : "Credit");
    return out;
}


istream& operator>>(istream &in, Transaction &trans) {
    cout << "Enter transaction ID: ";
	in >> trans.id;

	cout << "Enter transaction amount: ";
	in >> trans.amount;

	cout << "Enter transaction type (D for debit, C for credit): ";
	char type;
    in >> type;

	while(!trans.setType(type)) {
		cerr << "Invalid transaction type! Use 'D' for debit or 'C' for credit!!\n";
		cout << "Re-enter transaction type (D or C): ";
		in >> type;
	}

	return in;
}
