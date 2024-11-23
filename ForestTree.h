#pragma once

#include <fstream>
#include <math.h>
#include "Account.h"

class ForestTree {
    private:
        class Node {
            public:
                Account data;
                Node* sibiling;
                Node* child;
                Node(const Account & acc) : data(acc), sibiling(nullptr), child(nullptr) {};
        };

        typedef Node* nodePtr;
        nodePtr root;
    
    public:
        ForestTree();
        void addAccount(const Account &);
        void buildTreeFromFile(const string &);
        void addTransaction(const int, const Transaction &);
        // void printTree() const; //! let's use the operator much better
        void searchAccount(int) const; // if found would display it
        nodePtr binarySearchSibling(nodePtr, const string &) const;

        void printTree(nodePtr, int, ofstream &) const;
        friend ostream& operator<<(ostream &, const ForestTree &);
};
