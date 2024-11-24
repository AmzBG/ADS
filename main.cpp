#include "ForestTree.h"

int main() {

    ForestTree ft;

    const string filePath = "accountswithspace.txt";

    ft.buildTreeFromFile(filePath);

    Transaction t1(1, 5.00, 'D');
    // Transaction t2(2, 50.00, 'C');
    // Transaction t3(3, 100.00, 'D');
    // Transaction t4(4, 75.00, 'C');

    // ft.addAcountTransaction(10131, t3);
    ft.addAcountTransaction(1013, t1);
    // ft.addAcountTransaction(1011, t2);
    // ft.addAcountTransaction(10, t3);
    // ft.addAcountTransaction(1, t4);

    // ft.addAccount(Account(0, "testin", -1.0));

    // ft.addAcountTransaction(891, Transaction(10, 142.0, 'C'));



    ft.removeAccountTransaction(1013, 1);

    ofstream tree("tree.txt");
    tree << ft;
    return 0;
}