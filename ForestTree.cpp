#include "ForestTree.h"

ForestTree::ForestTree() : root(nullptr) {}

void ForestTree::addAccount(const Account & acc) {
    // navigate based on the number of digits
    // navigate based on the account# increasing order
    // if 11 max parent and inserting 1452
    // then adding 1
    // handle inserting root after ex: root = 4 adding 1
    
    cout << "Adding account: " << acc.getAccountNumber() << '\n';

    // first node
    nodePtr newNode = new Node(acc);
    if (root == nullptr) {
        root = newNode;
        return;
    }
    // replace root
    if (ceil(log10(root->data.getAccountNumber())) > ceil(log10(acc.getAccountNumber()))) {
        newNode->child = root;
        root = newNode;
        return;
    } else if (root->data.getAccountNumber() > acc.getAccountNumber()) {
        newNode->sibiling = root;
        root = newNode;
        return;
    }
    nodePtr curr = root, behind = nullptr;
    while(ceil(log10(curr->data.getAccountNumber())) < ceil(log10(acc.getAccountNumber())) and curr->child != nullptr) {
        behind = curr;
        curr = curr->child;
    }
    while(curr->data.getAccountNumber() < acc.getAccountNumber() and curr->sibiling != nullptr) {
        behind = curr;
        curr = curr->sibiling;
    }
    if (ceil(log10(curr->data.getAccountNumber())) > ceil(log10(acc.getAccountNumber()))) {
        newNode->child = curr;
        behind->child = newNode;
    } else if (ceil(log10(curr->data.getAccountNumber())) < ceil(log10(acc.getAccountNumber()))) { // curr->child == nullptr
        curr->child = newNode;
    } else if (curr->data.getAccountNumber() == acc.getAccountNumber()) {
        cout << "Account already exists!!\n";
    } else if (curr->data.getAccountNumber() > acc.getAccountNumber()) { // curr->sibling == nullptr
        newNode->sibiling = curr;
        behind->sibiling = newNode;
    } else {
        curr->sibiling = newNode;
    }
}

void ForestTree::searchAccount(int accountNumber) const {
    nodePtr currentNode = root;

    while (currentNode != nullptr) {
        // Convert the account number to string for prefix matching
        string searchStr = to_string(accountNumber);
        string currentNodeStr = to_string(currentNode->data.getAccountNumber());

        // Check if the current node matches the prefix of the account number
        if (searchStr.find(currentNodeStr) == 0) {
            // Full match found
            if (searchStr == currentNodeStr) {
                cout << "Account found: " << currentNode->data << endl;
                return;
            }

            // Otherwise, continue searching in the child
            currentNode = currentNode->child;
        } else {
            // Use binary search to find the correct sibling
            currentNode = binarySearchSibling(currentNode->sibiling, searchStr);
        }
    }

    // If we reached here, the account number was not found
    cout << "Account not found!" << endl;
}


ForestTree::nodePtr ForestTree::binarySearchSibling(nodePtr startNode, const string& searchStr) const {
    vector<nodePtr> siblings;
    nodePtr currentNode = startNode;
    
    // Collect all siblings into a vector
    while (currentNode != nullptr) {
        siblings.push_back(currentNode);
        currentNode = currentNode->sibiling;
    }

    // Perform binary search on the vector of siblings
    int left = 0, right = siblings.size() - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        string currentNodeStr = to_string(siblings[mid]->data.getAccountNumber());

        // Compare the prefix of the account number with the sibling
        if (searchStr.find(currentNodeStr) == 0) {
            // If we find a match, return the sibling node
            return siblings[mid];
        } else if (currentNodeStr < searchStr) {
            // Move to the right half of the siblings
            left = mid + 1;
        } else {
            // Move to the left half of the siblings
            right = mid - 1;
        }
    }
    
    // No matching sibling found
    return nullptr;
}

void ForestTree::buildTreeFromFile(const string &filePath) {

    ifstream file(filePath);

    if (!file.is_open()) {
        cerr << "Error: Could not open input file " << filePath << endl;
        return;
    }

    Account acc;
    while (file >> acc) {
        addAccount(acc);
    }
    ofstream tree("tree.txt");
    printTree(root, 0, tree);

    file.close();
}

void ForestTree::printTree(nodePtr node, int depth, ofstream & tree) const {
    if (!node) return;
    tree << string(depth * 2, '-') << node->data.getAccountNumber() << '\n';
    printTree(node->child, depth + 1, tree);
    printTree(node->sibiling, depth, tree);
}
