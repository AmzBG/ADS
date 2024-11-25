#pragma once

#include <fstream>
#include <sstream> // online gdb
#include <math.h>
#include "Account.h"

using namespace std; // online gdb

class ForestTree {
    private:
        class Node {
            public:
                Account data;
                Node* sibling;
                Node* child;
                Node(const Account & acc) : data(acc), sibling(nullptr), child(nullptr) {};
        };

        typedef Node* nodePtr;
        nodePtr root;
    
    public:
        ForestTree();
        void addAccount(const Account &);
        void buildTreeFromFile(const string &);


        vector<nodePtr> searchAccountWithTracking(int, vector<Account*> &) const;
        vector<nodePtr> searchAccountWithTracking(int) const;
        void findAccount(int) const;
        void addAcountTransaction(const int, const Transaction &);
        void removeAccountTransaction(const int, const int);


        void printTree(nodePtr, int, ostream &) const;
        friend ostream& operator<<(ostream &, const ForestTree &);


        void printAccountRecursive(nodePtr, int, ostream &) const;
        void printAccount(int) const;
        void printTreeIntoFile(const string &);
        void printTreeRecursive(nodePtr, ostream &);
};
