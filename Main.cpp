#include <iostream>
#include "GrammarManager.h"
#include "FileManager.h"
#include <fstream>
#include <string>
using namespace std;

void menu(GrammarManager* grammarManager, FileManager* fileManager)
{
	int command = -1;
	do
	{
		cout << "\n1.  Open\n"
			"2.  Close\n"
			"3.  Save\n"
			"4.  Save as\n"
			"5.  List\n"
			"6.  Print\n"
			"7.  Add grammar\n"
			"8.  Add rule\n"
			"9.  Remove rule\n"
			"10. Union\n"
			"11. Concat\n"
			"12. Iter\n"
			"13. Empty\n"
			"14. Chomsky\n"
			"0.  Exit\n"
			"Enter command: ";
		cin >> command;
		switch (command)
		{
			// Open
			case 1:
			{
				cout << "Enter file name: ";
				string filename;
				cin >> filename;
				fileManager->Open(filename);
				break;
			}
			// Close
			case 2:
			{
				fileManager->Close();
				cout << "Closed" << endl;
				break;
			}
			// Save
			case 3:
			{
				fileManager->Save();
				cout << "File saved as \"defaultFile.txt\"" << endl;
				break;
			}
			// Save as
			case 4:
			{
				cout << "Enter file name: ";
				string filename;
				cin >> filename;
				fileManager->SaveAs(filename);
				cout << "File saved as " << filename << endl;
				break;
			}
			// List
			case 5:
			{
				grammarManager->List();
				break;
			}
			// Print
			case 6:
			{
				int id;
				cout << "Enter grammar id: ";
				cin >> id;
				grammarManager->Print(id);
				break;
			}
			// Add grammar
			case 7:
			{
				string startVar;
				cout << "Enter start variable: ";
				cin >> startVar;
				cout << "Added grammar with number: " << grammarManager->AddGrammar(startVar) << endl;
				break;
			}
			// Add rule
			case 8:
			{
				int id;
				string variable, replacement;
				cout << "Enter grammar id: ";
				cin >> id;
				cout << "Enter variable: ";
				cin >> variable;
				//TODO fix replacements
				cout << "Enter replacement: ";
				cin >> replacement;
				cout << "Added rule with number: " << grammarManager->AddRule(id, variable, replacement.c_str()) << endl;
				break;
			}
			// Remove rule
			case 9:
			{
				int id, ruleNum;
				cout << "Enter grammar id: ";
				cin >> id;
				cout << "Enter rule number: ";
				cin >> ruleNum;
				grammarManager->RemoveRule(id, ruleNum);
				break;
			}
			// Union
			case 10:
			{
				int id1, id2;
				cout << "Enter first grammar id: ";
				cin >> id1;
				cout << "Enter second grammar id: ";
				cin >> id2;
				cout << "Merged into new grammar with number: " << grammarManager->Union(id1, id2) << endl;
				break;
			}
			// Concat
			case 11:
			{
				int id1, id2;
				cout << "Enter first grammar id: ";
				cin >> id1;
				cout << "Enter second grammar id: ";
				cin >> id2;
				cout << "Merged into new grammar with number: " << grammarManager->Concat(id1, id2) << endl;
				break;
			}
			// Iter
			case 12:
			{
				int id;
				cout << "Enter grammar id: ";
				cin >> id;
				cout << "New grammar with number: " << grammarManager->Iter(id) << endl;
				break;
			}
			// Empty
			case 13:
			{
				int id;
				cout << "Enter grammar id: ";
				cin >> id;
				cout << "Grammar is : " << (grammarManager->Empty(id) ? "empty" : "not empty") << endl;
				break;
			}
			// Chomsky
			case 14:
			{
				int id;
				cout << "Enter grammar id: ";
				cin >> id;
				cout << "Grammar is : " << (grammarManager->Chomsky(id) ? "Chomsky" : "not Chomsky") << endl;
				break;
			}
			case 0:
			{
				break;
			}
			default:
			{
				cout << "Invalid command!" << endl;
				break;
			}
		}
	} while (command != 0);
}

int main() 
{
	GrammarManager grammarManager;
	FileManager fileManager(&grammarManager);
	menu(&grammarManager, &fileManager);

	system("pause");
}