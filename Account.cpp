#include "Account.h"

// Constructor
Account::Account() : accountNumber(0), balance(0.0), description("") {}

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

// Add a transaction to the max-heap
void Account::addTransaction(const Transaction &transaction) {
    transactions.push_back(transaction);  // Add transaction to the max-heap
   if (transaction.getType() == 'C') {
            updateBalance(-transaction.getAmount());
    }
    else{
     updateBalance(transaction.getAmount());
    }
}

Transaction Account::removeTransaction(int id) {
    // Iterate through the transactions to find the one with the matching id
    for (auto it = transactions.begin(); it != transactions.end(); ++it) {
        if (it->getId() == id) {
            // Transaction found, now remove it
            Transaction txn = *it;  // Copy the transaction to return
            transactions.erase(it);  // Erase the transaction from the vector
    if (txn.getType() == 'D') {
            updateBalance(-txn.getAmount());
    }
    else{
     updateBalance(txn.getAmount());
    }
            return txn;
        }
    }

    // If no matching transaction was found
    throw std::runtime_error("Transaction with the specified ID not found!");
}

void Account::updateBalance(double amount) {
        balance += amount;
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
        // If getline fails (reached EOF or an error), do not continue
        return; 
    }

    // If the line is empty after reading, treat it as EOF or invalid data
    if (line.empty()) {
        return;  // Skip empty lines and stop reading
    }

    vector<string> parts = split(line, ' ');
    
    // Basic sanity check for parts (ensure there are at least 3 parts: account number, balance, and description)
    if (parts.size() < 3) {
        cerr << "Error: Invalid account format in line: " << line << endl;
        return;
    }

    // Parse the account number, balance, and description
    accountNumber = stoi(parts[0]);
    balance = stod(parts[parts.size() - 1]);

    // Join the parts for the description (which are between account number and balance)
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

