#include <iostream>
#include <string>
#include "ForestTree.h"
using namespace std;

int main() {
	ForestTree forest;
	int choice;

	do {
		cout << "\n*** Chart of Accounts Menu ***" << endl;
		cout << "1. Build Chart of Accounts (Read from a text file)" << endl;
		cout << "2. Add an Account" << endl;
		cout << "3. Add a Transaction or Delete a Transaction" << endl;
		cout << "4. Print a Detailed Report for an Account (Includes Subaccounts and Transactions)" << endl;
		cout << "5. Search for an Account by Number" << endl;
		cout << "6. Print the Forest Tree into a File" << endl;
		cout << "7. Print the Forest Tree into a file with all transactions " << endl;
		cout << "0. Exit" << endl;
		cout << "Enter your choice: ";
		cin >> choice;

		switch (choice) {
		case 1: {
			string fileName;
			do {
				cout << "Enter the file name to build the chart of accounts: ";
				cin >> fileName;
				bool result = forest.buildTreeFromFile(fileName);
				if (result) {
                    cout << "Read file successfully!!\n";
                    break;
                }
                string repeat;
				cout << "Do you want to build another chart of accounts? (yes/no): ";
				cin >> repeat;
				if (repeat != "yes") break;
			} while (true);
			break;
		}
		case 2: {
			do {
				int number;
				double balance;
				string description;

				cout << "Enter account number: ";
				cin >> number;
				cout << "Enter account balance: ";
				cin >> balance;
				cout << "Enter account description: ";
				cin.ignore();
				getline(cin, description);

				if(forest.addAccount(number, description, balance)) {
					cout << "Account added successfully!" << endl;
				}

				string repeat;
				cout << "Do you want to add another account? (yes/no): ";
				cin >> repeat;
				if (repeat != "yes") break;
			} while (true);
			break;
		}
		case 3: {
			do {
				int accNumber;
				cout << "Enter the account number: ";
				cin >> accNumber;

				string operation;
				cout << "Enter 'add' to add a transaction or 'delete' to delete a transaction: ";
				cin >> operation;

				if (operation == "add") {
					Transaction newTransaction;
					cin >> newTransaction;
					forest.addAcountTransaction(accNumber, newTransaction);
				} else if (operation == "delete") {
					int transId;
                    do {
                        cout << "Enter transaction ID to delete: ";
                        cin >> transId;
                    } while(transId < 0);

					forest.removeAccountTransaction(accNumber, transId);
				} else {
					cout << "Invalid operation! Please enter 'add' or 'delete'." << endl;
				}
				string repeat;
				cout << "Do you want to perform another transaction operation? (yes/no): ";
				cin >> repeat;
				if (repeat != "yes") break;
			} while (true);
			break;
		}
		case 4: {
			do {
				int accNumber;
				cout << "Enter the account number for the detailed report: ";
				cin >> accNumber;
				forest.printAccount(accNumber);
				string repeat;
				cout << "Do you want to print another detailed report? (yes/no): ";
				cin >> repeat;
				if (repeat != "yes") break;
			} while (true);
			break;
		}
		case 5: {
			do {
				int accNumber;
				cout << "Enter the account number to search: ";
				cin >> accNumber;
				forest.findAccount(accNumber);

				string repeat;
				cout << "Do you want to search for another account? (yes/no): ";
				cin >> repeat;
				if (repeat != "yes") break;
			} while (true);
			break;
		}
		case 6: {
                string fileName;
                cout << "Enter the file name to print the forest tree: ";
                cin >> fileName;
                if (forest.printTreeIntoFile(fileName)) {
                    cout << "Forest tree successfully printed into the file!" << endl;
                }
                break;
            }
			case 7: {
				string fileName;
				cout << "Enter the file name to print the forest tree with all transactions: ";
				cin >> fileName;
                string folderName = "Extra features/";
                if (!filesystem::exists(folderName)) {
                    filesystem::create_directory(folderName);
                }
                ofstream outFile(folderName + fileName + ".txt");
                outFile << forest;
                break;
		}
		case 0: {
			cout << "Exiting program. Goodbye!" << endl;
			break;
		}
		default:
			cout << "Invalid choice! Please try again." << endl;
		}
	} while (choice != 0);

	return 0;
}
