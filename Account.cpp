#include "Account.h"

// Constructor
Account::Account() 
 : accountNumber(0), balance(0.0), description("") {}

Account::Account(int number, const string & desc, double bal)
 : description(desc), balance(bal) {
    setAccountNumber(number);
}

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

void Account::setAccountNumber(int num) {
    if (num < 1) {
        cerr << "Invalid Account Number\n";
        return;
    }
    accountNumber = num;
}

void Account::addTransaction(const Transaction &trans) {
    if (findTransaction(trans.getId()) != transactions.end()) {
        cout << "Transaction " << trans.getId() << " already exists" << endl;
        return;
    }
    // update account balance
    updateBalance(trans.getAmount() * (trans.getType() == 'C' ? -1 : 1));
    transactions.push_back(trans);
}

Transaction Account::removeTransaction(int id) {
    auto it = findTransaction(id);
    
    // Found the transaction
    if (it != transactions.end()) {
        Transaction trans = *it;
        updateBalance(it->getAmount() * (it->getType() == 'D' ? -1 : 1));
        transactions.erase(it);
        cout << "Transaction successfully removed!!\n";
        return trans;
    }

    cerr << "Transaction not found!!\n";
    return Transaction(-1);
}

vector<Transaction>::iterator Account::findTransaction(int transactionID) {
    int left = 0;
    int right = transactions.size() - 1;
  radixSortTransactions();
    while (left <= right) {
        int mid = left + (right - left) / 2;

        if (transactions[mid].getId() == transactionID) {
            return transactions.begin() + mid;  // Return iterator pointing to the transaction
        } else if (transactions[mid].getId() < transactionID) {
            left = mid + 1;  // Search in the right half
        } else {
            right = mid - 1;  // Search in the left half
        }
    }

    return transactions.end();  // Return end() if not found
}

void Account::radixSortTransactions() {
    // Find the maximum transaction ID
    int maxId = 0;
    for (const auto &trans : transactions) {
        maxId = max(maxId, trans.getId());
    }

    // Perform counting sort for each digit
    for (int exp = 1; maxId / exp > 0; exp *= 10) {
        countingSortByDigit(transactions, exp);
    }
}

void Account::countingSortByDigit(vector<Transaction> & transactions, int exp) {
    int n = transactions.size();
    vector<Transaction> output(n);
    int count[10] = {0};

    // Count occurrences of digits in the current position
    for (int i = 0; i < n; i++) {
        int digit = (transactions[i].getId() / exp) % 10;
        count[digit]++;
    }

    // Update count[i] to hold the actual position of digits
    for (int i = 1; i < 10; i++) {
        count[i] += count[i - 1];
    }

    // Build the output array
    for (int i = n - 1; i >= 0; i--) {
        int digit = (transactions[i].getId() / exp) % 10;
        output[count[digit] - 1] = transactions[i];
        count[digit]--;
    }

    // Copy the sorted transactions back to the original vector
    for (int i = 0; i < n; i++) {
        transactions[i] = output[i];
    }
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

