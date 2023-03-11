// Andrew Thomas
// Final Project VectorCustomers.h

#include <iostream>
#include <vector>
#include <string>
using namespace std;


#include "VectorCustomers.h"



int main()
{


	VectorCustomers CustomerInfo; //declaring object

	
	CustomerInfo.InputData(); // reading in data from input file
	CustomerInfo.InputPurchases(); // reading from purchase file

	CustomerInfo.userName();

	do {
		CustomerInfo.LoadMenu(); // Loading Menu Screen
		switch (CustomerInfo.GetMenuChoice()) { //different options methods for menu
		case '0': // exits
			system("CLS"); // clears screen
			cout << "Goodbye " << CustomerInfo.GetuserName() << ", thanks for checking out Andrew's Shady Car Dealership Database! " << endl;
			exit(0);
			break;
		case '1': // Prints stat lists
			CustomerInfo.Choice1();
			CustomerInfo.returnMenu();
			system("CLS");
			break;
		case '2': // Prints specific player stats
			CustomerInfo.Choice2();
			CustomerInfo.returnMenu();
			system("CLS");
			break;
		case '3': // Add a player 
			CustomerInfo.Choice3();
			CustomerInfo.returnMenu();
			system("CLS");
			break;
		case '4': // Add a player 
			CustomerInfo.Choice4();
			CustomerInfo.returnMenu();
			system("CLS");
			break;
		case '5': // Add a player 
			CustomerInfo.Choice5();
			CustomerInfo.returnMenu();
			system("CLS");
			break;
		case '6': // Save to files
			CustomerInfo.Choice6();
			CustomerInfo.returnMenu();
			system("CLS");
			break;
		case '7':
			CustomerInfo.Choice7();
			CustomerInfo.returnMenu();
			system("CLS");
			break;
		case '8':
			CustomerInfo.Choice8();
			CustomerInfo.returnMenu();
			system("CLS");
			break;
		default: cout << endl << "You entered invalid input. Please type in one of the menu options: ";
			cout << endl << endl;

		}


	} while (CustomerInfo.GetMenuChoice() != '0'); // infinitely loads menu screen

	system("Pause");
	return 0;
}