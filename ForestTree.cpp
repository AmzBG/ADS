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

    nodePtr currNode = root, behind;

    while (currNode != nullptr) {
        int currNodeAccountNum = currNode->data.getAccountNumber();
        if (currNode->data.compAccountNumber(accountNum)) {
            
            // Account already exists
            if (accountNum == currNodeAccountNum) {
                cerr << "Error: Account with number " << accountNum << " already exists!" << endl;
                delete newNode;  // Cleanup
                return;
            }

            // Move down to the child
            if (ceil(log10(currNodeAccountNum)) != ceil(log10(accountNum))) {
                // Child not found
                if (currNode->child == nullptr) {
                    currNode->child = newNode;
                    return;
                } 
                // Child exists
                else {
                    behind = currNode;
                    currNode = currNode->child;
                }
            }
        } else {
            // Insert node between parent and child
            if (accountNum < currNodeAccountNum && behind->child == currNode) {
                newNode->sibling = currNode;
                behind->child = newNode;
                return;
            }
            
            // Insert infront of a sibling
            if (currNode->sibling == nullptr) {
                currNode->sibling = newNode;
                return;
            }

            // Insert between sibling and sibling
            if (accountNum > currNodeAccountNum && currNode->sibling->data.getAccountNumber() > accountNum) {
                newNode->sibling = currNode;
                behind->sibling = newNode;
                return;
            }

            // Move to sibling
            behind = currNode;
            currNode = currNode->sibling;
        }
    }
}

ForestTree::nodePtr ForestTree::searchAccount(int accountNum) const {
    nodePtr currNode = root, behind;

    while (currNode != nullptr) {
        int currNodeAccountNum = currNode->data.getAccountNumber();

        if (currNode->data.compAccountNumber(accountNum)) {
            // Account found
            if (accountNum == currNodeAccountNum) {
                return currNode;
            }

            // Move down to the child
            else if (ceil(log10(currNode->data.getAccountNumber())) != ceil(log10(accountNum)) && currNode->child != nullptr) {
                behind = currNode;
                currNode = currNode->child;
                continue;
            }
        }
        // Move to sibling
        behind = currNode;
        currNode = currNode->sibling;
    }

    // Account not found
    cout << "Account not found:" << accountNum << endl;
    return nullptr;
}

// Uses searchAccount
void ForestTree::findAccount(int accountNum) const {
    nodePtr res = searchAccount(accountNum);
    if (res != nullptr) {
        cout << "Account Found:\n" << res;
    }
}

void ForestTree::addAcountTransaction(const int accountNum, const Transaction & t) {
    nodePtr currNode = root;
    vector<Account*> accountsPassedThrough;
    while(currNode != nullptr) {
        bool compRes = currNode->data.compAccountNumber(accountNum);
        if (compRes && accountNum == currNode->data.getAccountNumber()) {
            break;
        }
        // Add to path
        accountsPassedThrough.push_back(&currNode->data);
        // Move to child
        if (compRes && ceil(log10(currNode->data.getAccountNumber())) != ceil(log10(accountNum)) && currNode->child != nullptr) {
            currNode = currNode->child;
        } 
        // Move to sibling
        else {
            currNode = currNode->sibling;
        }
    }
    if (currNode == nullptr || currNode->data.getAccountNumber() != accountNum) {
        cerr << "Account not found!!\n";
        return;
    }
    currNode->data.addTransaction(t);
    for(auto & acc : accountsPassedThrough) {
        acc->updateBalance(t.getAmount() * (t.getType() == 'D' ? 1 : -1));
    }
}

void ForestTree::removeAccountTransaction(const int accountNum, const int transactionID) {
    nodePtr currNode = root;
    vector<Account*> accountsPassedThrough;
    while(currNode != nullptr) {
        bool compRes = currNode->data.compAccountNumber(accountNum);
        if (compRes && accountNum == currNode->data.getAccountNumber()) {
            break;
        }
        // Add to path
        accountsPassedThrough.push_back(&currNode->data);
        // Move to child
        if (compRes && ceil(log10(currNode->data.getAccountNumber())) != ceil(log10(accountNum)) && currNode->child != nullptr) {
            currNode = currNode->child;
        } 
        // Move to sibling
        else {
            currNode = currNode->sibling;
        }
    }
    if (currNode == nullptr || currNode->data.getAccountNumber() != accountNum) {
        cerr << "Account not found!!\n";
        return;
    }
    Transaction trans = currNode->data.removeTransaction(transactionID);
    if (trans.getId() == -1) {
        return;
    }
    for(auto & acc : accountsPassedThrough) {
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
