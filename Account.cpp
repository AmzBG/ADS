#include "Account.h"

// Constructor
Account::Account() 
    : accountNumber(0), balance(0.0), description("") {}

Account::Account(int number, const std::string &desc, double bal)
    : accountNumber(number), description(desc), balance(bal) {}

// Getters
int Account::getAccountNumber() const {
    return accountNumber;
}

double Account::getBalance() const {
    return balance;
}

string Account::getDescription() const {
    return description;
}
   
const vector<Transaction>& Account::getTransactions() const {
    return transactions;
}

void Account::addTransaction(const Transaction &trans) {
    // update account balance
    updateBalance(trans.getAmount());
    transactions.push_back(trans);  
}

Transaction Account::removeTransaction(int id) {
    for (auto it = transactions.begin(); it != transactions.end(); it++) {
        if (it->getId() == id) {
            // update account balance
            Transaction trans = *it;
            updateBalance(it->getAmount() * (it->getType() == 'D' ? -1 : 1));
            transactions.erase(it);
            cout << "Transaction successfully removed!!\n";
            return trans;
        }
    }
    cerr << "Transaction not found!!\n";
    return Transaction(-1);
}

Transaction Account::findTransaction(const int transactionID) const{
    for(auto & trans : transactions) {
        if (trans.getId() == transactionID)
            return trans;
    }
    return Transaction(-1);
}

void Account::updateBalance(double amount) {
    balance += amount;
}

bool Account::compAccountNumber(const int otherAccountNum) const {
    return to_string(otherAccountNum).find(to_string(accountNumber)) == 0;
}

vector<string> split(string& line, char delimiter) {
    vector<string> parts;
    string current;
    for(char &c : line) {
        if(c == delimiter && !current.empty()) {
            parts.push_back(current);
            current.clear();
        } else {
            current += c;
        }
    }
    if (!current.empty()) parts.push_back(current);
    return parts;
}

void Account::readAccount(istream& in) {
    string line;
    if (!getline(in, line)) {
        return; 
    }

    if (line.empty()) {
        return;
    }

    vector<string> parts = split(line, ' ');
    if (parts.size() < 3) {
        cerr << "Error: Invalid account format in line: " << line << endl;
        return;
    }

    accountNumber = stoi(parts[0]);
    balance = stod(parts[parts.size() - 1]);

    string desc;
    for (int i = 1; i < parts.size() - 2; i++) {
        desc += parts[i] + ' ';
    }
    desc += parts[parts.size() - 2];

    description = desc;
}

void Account::printAccount(ostream & out) const {
    out << "Number: " << accountNumber << '\n'
        << "Balance: " << balance << '\n'
        << "Description: " << description << '\n'
        << "Transactions: \n";
    if (transactions.empty()) {
        out << "No transactions found.\n";
    } else {
        for (const auto &trans : transactions) {
            out << trans << '\n';
        }
    }

}

istream &operator>>(istream & in, Account & account) {
    account.readAccount(in);
    return in;
}

ostream &operator<<(ostream & out, const Account & account) {
    account.printAccount(out);
    return out;
}

