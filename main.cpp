#include "ForestTree.h"

int main() {

    ForestTree ft;

    const string filePath = "accountswithspace.txt";

    ft.buildTreeFromFile(filePath);

    return 0;
}