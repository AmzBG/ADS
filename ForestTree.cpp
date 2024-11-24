#include "ForestTree.h"

ForestTree::ForestTree() : root(nullptr) {}

void ForestTree::addAccount(const Account & acc) {
    int accountNum = acc.getAccountNumber();
    nodePtr newNode = new Node(acc);

    // First node
    if (root == nullptr) {
        root = newNode;
        return;
    }

    // Insert before root
    if (accountNum < root->data.getAccountNumber()) {
        newNode->sibling = root;
        root = newNode;
        return;
    }

    // res = { currNode, behind }
    vector<nodePtr> res = searchAccount(accountNum);

    if (res[0] != nullptr) {
        // Account already exists
        if (accountNum == res[0]->data.getAccountNumber()) {
            cerr << "Error: Account with number " << accountNum << " already exists!" << endl;
            delete newNode;  // Cleanup
            return;
        }
        // First child (current: 10 - add: 10124)
        if (ceil(log10(res[0]->data.getAccountNumber())) < ceil(log10(accountNum))) {
            res[0]->child = newNode;
            return;
        }

        if (accountNum < res[0]->data.getAccountNumber()) {
            // Before child (current: 10, 1011 - add: 100)
            if (res[1]->child == res[0]) {
                newNode->sibling = res[0];
                res[1]->child = newNode;
            } 
            // Insert between sibling and sibling (current: 1, 5 - add: 4)
            else {
                newNode->sibling = res[0];
                res[1]->sibling = newNode;
            }
            return;
        }
    }
    // Insert infront of a sibling (current: 5 - add 632)
    res[1]->sibling = newNode;
}

vector<ForestTree::nodePtr> ForestTree::searchAccount(int accountNum) const {
    nodePtr currNode = root, behind = nullptr;

    while (currNode != nullptr) {
        int currNodeAccountNum = currNode->data.getAccountNumber();

        // doesn't get in unless accountNumbers match
        if (currNode->data.compAccountNumber(accountNum)) {
            // Account found
            if (accountNum == currNodeAccountNum) {
                return { currNode, behind };
            }
            if (currNode->child == nullptr) {
                return { currNode, behind };
            }
            // Move down to the child
            behind = currNode;
            currNode = currNode->child;
        } else {
            if (accountNum < currNode->data.getAccountNumber()) {
                return { currNode, behind };   
            }
            // Move to sibling
            behind = currNode;
            currNode = currNode->sibling;
        }
    }

    // // Account not found
    // cout << "Account not found:" << accountNum << endl;
    return { currNode, behind };
}

ForestTree::nodePtr ForestTree::searchAccountWithTracking(int accountNum, vector<Account*> & tracked) const
{
    nodePtr currNode = root;
    while(currNode != nullptr) {
        bool compRes = currNode->data.compAccountNumber(accountNum);
        if (compRes && accountNum == currNode->data.getAccountNumber()) {
            return currNode;
        }
        // Add to path
        tracked.push_back(&currNode->data);
        // Move to child
        if (compRes && ceil(log10(currNode->data.getAccountNumber())) != ceil(log10(accountNum)) && currNode->child != nullptr) {
            currNode = currNode->child;
        } 
        // Move to sibling
        else {
            currNode = currNode->sibling;
        }
    }
    cerr << "Account not found!!\n";
    return nullptr;
}

// Uses searchAccount
void ForestTree::findAccount(int accountNum) const {
    vector<nodePtr> res = searchAccount(accountNum);
    if (res[0] != nullptr && res[0]->data.getAccountNumber() == accountNum) {
        cout << "Account Found:\n" << res[0];
    }
}

void ForestTree::addAcountTransaction(const int accountNum, const Transaction & t) {
    vector<Account*> tracked;
    nodePtr currNode = searchAccountWithTracking(accountNum, tracked);
    if (currNode == nullptr || currNode->data.getAccountNumber() != accountNum) {
        return;
    }
    currNode->data.addTransaction(t);
    for(auto & acc : tracked) {
        acc->updateBalance(t.getAmount() * (t.getType() == 'D' ? 1 : -1));
    }
}

void ForestTree::removeAccountTransaction(const int accountNum, const int transactionID) {
    vector<Account*> tracked;
    nodePtr currNode = searchAccountWithTracking(accountNum, tracked);
    if (currNode == nullptr || currNode->data.getAccountNumber() != accountNum) {
        return;
    }
    Transaction trans = currNode->data.removeTransaction(transactionID);
    if (trans.getId() == -1) {
        return;
    }
    for(auto & acc : tracked) {
        acc->updateBalance(trans.getAmount() * (trans.getType() == 'C' ? 1 : -1));
    }
}

void ForestTree::buildTreeFromFile(const string &filePath) {

    ifstream file(filePath);

    if (!file.is_open()) {
        cerr << "Error: Could not open input file " << filePath << endl;
        return;
    }

    Account acc;
    string line;
    while (getline(file, line)) {
        if (line.empty()) continue;
        istringstream lineStream(line);
        lineStream >> acc;
        addAccount(acc);
    }

    file.close();
}

void ForestTree::printTree(nodePtr node, int depth, ostream& out) const {
    if (!node) return;
    // Print current node with indentation based on depth
    out << string(depth * 2, '-') << "Account Number: " << node->data.getAccountNumber() << '\n';
    out << string(depth * 2, '-') << "Description: " << node->data.getDescription() << '\n';
    out << string(depth * 2, '-') << "Balance: " << node->data.getBalance() << '\n';
    out << string(depth * 2, '-') << "Transactions:\n";
    const vector<Transaction>& transactions = node->data.getTransactions();
    if (transactions.empty()) {
        out << string((depth + 1) * 2, ' ') << "No transactions\n";
    } else {
        for (const auto& transaction : transactions) {
            out << string((depth + 1) * 2, ' ') << transaction << '\n';
        }
    }
    out << '\n';
    // recall function
    printTree(node->child, depth + 1, out);
    printTree(node->sibling, depth, out);
}

ostream& operator<<(ostream& out, const ForestTree& tree) {
    tree.printTree(tree.root, 0, out);
    return out;
}
