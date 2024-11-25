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

    vector<Account*> tracked;
    // res = { currNode, behind }
    vector<nodePtr> res = searchAccountWithTracking(accountNum, tracked);
    
    // acc.getBalance() == 0
    if (!tracked.empty()) {
        for(auto & account : tracked) {
            account->updateBalance(acc.getBalance());
        }
    }

    if (res[0] != nullptr) {
        // Account already exists
        if (accountNum == res[0]->data.getAccountNumber()) {
            cerr << "Error: Account with number " << accountNum << " already exists!" << endl;
            delete newNode;  // Cleanup
            return;
        }
        // First child (current: 10 - add: 10124)
        if (to_string(res[0]->data.getAccountNumber()).size() < to_string(accountNum).size()) {
            res[0]->child = newNode;
            return;
        }

        if (accountNum < res[0]->data.getAccountNumber()) {
            // Before child (current: 10, 1011 - add: 100)
            if (res[1]->child == res[0]) {
                newNode->sibling = res[0];
                res[1]->child = newNode;
            }
            else {
                // Insert between sbilings, but with a child (current: 1, 45, 52 - add: 4)
                if (to_string(res[0]->data.getAccountNumber()).size() > to_string(accountNum).size()) {
                    newNode->sibling = res[0]->sibling;
                    newNode->child = res[0];
                    res[0]->sibling = nullptr;
                    res[1]->sibling = newNode;
                }
                // Insert between sibling and sibling (current: 1, 5 - add: 4)
                else {
                    newNode->sibling = res[0];
                    res[1]->sibling = newNode;
                }
            }
            return;
        }
    }
    // Insert infront of a sibling (current: 5 - add 632)
    res[1]->sibling = newNode;
}

vector<ForestTree::nodePtr> ForestTree::searchAccountWithTracking(int accountNum, vector<Account*> & tracked) const {
    nodePtr currNode = root, behind = nullptr;
    while(currNode != nullptr) {
        if (currNode->data.compAccountNumber(accountNum)) {
            if (accountNum == currNode->data.getAccountNumber()) {
                break;
            }
            // Add to path
            tracked.push_back(&currNode->data);

            if (currNode->child == nullptr) {
                break;
            }
            // Move to child
            behind = currNode;
            currNode = currNode->child;
        }
        else {
            if (accountNum < currNode->data.getAccountNumber()) {
                break;   
            }
            // Move to sibling
            behind = currNode;
            currNode = currNode->sibling;
        }
    }
    if (currNode == nullptr && behind == nullptr)
        cerr << "Account not found\n";
    return { currNode, behind };
}

vector<ForestTree::nodePtr> ForestTree::searchAccountWithTracking(int accountNum) const {
    vector<Account*> dummy;
    return searchAccountWithTracking(accountNum, dummy);
}

void ForestTree::findAccount(int accountNum) const {
    vector<nodePtr> res = searchAccountWithTracking(accountNum);
    if (res[0] != nullptr && res[0]->data.getAccountNumber() == accountNum) {
        cout << "Account Found:\n" << res[0]->data;
    } else {
        cerr << "Error: account with number: " << accountNum << " not found!!\n";
    }
}

void ForestTree::addAcountTransaction(const int accountNum, const Transaction & t) {
    vector<Account*> tracked;
    nodePtr currNode = searchAccountWithTracking(accountNum, tracked)[0];
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
    nodePtr currNode = searchAccountWithTracking(accountNum, tracked)[0];
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



void ForestTree::printAccountRecursive(nodePtr node, int depth, ostream& out) const {
    if (!node) return;
    string description = node->data.getDescription();
    // Check for the condition and remove the starting double quote if necessary
    if (!description.empty() && description[0] == '"' && (description.size() <= 10 || description[9] != '"')) {
        description = description.substr(1); // Remove the starting double quote
    }
    // Print current node with indentation based on depth
    out << string(depth * 2, '-') << "Account Number: " << node->data.getAccountNumber() << '\n';
    out << string(depth * 2, '-') << "Description: " << description.substr(0, 10)<< '\n';
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
    printAccountRecursive(node->child, depth + 1, out);
    if (depth != 0) {
        printAccountRecursive(node->sibling, depth, out);
    }
}


void ForestTree::printAccount(int accountNum) const {
 vector<nodePtr> res = searchAccountWithTracking(accountNum);
 
    if (res[0] != nullptr && res[0]->data.getAccountNumber() == accountNum) {
        string fileName=to_string(res[0]->data.getAccountNumber());
            ofstream outFile("Account "+fileName);
        if (!outFile.is_open()) {
            cerr << "Error: Unable to open file: " << fileName << endl;
            return;
        }
       printAccountRecursive(res[0],0,outFile);
    }
}


void ForestTree::printTreeIntoFile(const string& fileName) {
    // Open the file for writing
    ofstream outFile(fileName);
    if (!outFile.is_open()) {
        cerr << "Error: Unable to open file: " << fileName << endl;
        return;
    }
        nodePtr node = root;
        
        if (!node){
        cout<< "empty tree";
        outFile.close();
        return;}
    
    // Recursive traversal and printing
    printTreeRecursive(node, outFile);

    // Close the file
    outFile.close();
}

void ForestTree::printTreeRecursive(nodePtr node, ostream& out) {
    if (!node) return;
    // Write current node data to the stream
    out << node->data.getAccountNumber()<<" "
        << node->data.getDescription()<<" "
        << node->data.getBalance() << '\n';

    // Recursively print child and sibling nodes
    printTreeRecursive(node->child, out);
    printTreeRecursive(node->sibling, out);
}