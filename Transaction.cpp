#include "Transaction.h"

// Constructors
Transaction::Transaction()
 : id(0), amount(0.0), type('D') {}

Transaction::Transaction(int id)
 : id(id), amount(0.0), type('D') {}

Transaction::Transaction(int id, double amount, char type)
 : amount(amount), type(type) {
    setId(id);
 }

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

void Transaction::setId(int id) {
	if (id < 1) {
        cerr << "Invalid Transaction ID\n";
        return;
    }
    this->id= id;
}

void Transaction::printWithIndentation(int depth, ostream& out) const {
    string indent = string(depth * 2, ' ');
    out << indent << "Transaction ID: " << id << '\n';
    out << indent + "  " << "Amount: " << fixed << setprecision(2) << amount << '\n';
    out << indent + "  " << "Type: " << (type == 'D' ? "Debit" : "Credit") << '\n';
}

ostream& operator<<(ostream& out, const Transaction& trans) {
    out << "Transaction ID: " << trans.getId() << "\n"
        << "Amount: " << fixed << setprecision(2) << trans.getAmount() << "\n"
        << "Type: " << (trans.getType() == 'D' ? "Debit" : "Credit");
    return out;
}


istream& operator>>(istream &in, Transaction &trans) {
    int id;
    do {
        cout << "Enter transaction ID: ";
        in >> id;
    } while(id <= 0);
    trans.id = id;

    double amount;
    do {
	    cout << "Enter transaction amount: ";
        in >> amount;
    } while(amount < 0);
    trans.amount = amount;


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
