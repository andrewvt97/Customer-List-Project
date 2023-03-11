// Andrew Thomas
// Final Project VectorCustomers.cpp

#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <fstream>
#include <cstdlib>
#include <algorithm>
#include <sstream>
#include <string.h>


using namespace std;
#include "VectorCustomers.h"



VectorCustomers::VectorCustomers() { // Constructor
	userFunction = -1;
	username = "NoName";
}

void VectorCustomers::LoadMenu() {

	string input;

	do {
		// Printing Menu Details

		cout << endl;
		cout << "Main Menu" << endl << endl;
		cout << "Type 1 to see the list of all the customers in our company. " << endl << endl;
		cout << "Type 2 to sort the list of our customers by first name, last name, or account number. " << endl << endl;
		cout << "Type 3 to see account info for a specific customer. " << endl << endl;
		cout << "Type 4 to update or delete a customer's account information." << endl << endl;
		cout << "Type 5 to add one or more customers. " << endl << endl;
		cout << "Type 6 to add one or more customer purchases. " << endl << endl;
		cout << "Type 7 to see purchase information for a customer and total money spent." << endl << endl;
		cout << "Type 8 to output the customer list and purchase info into external files." << endl << endl;


		cout << endl << "Enter 1, 2,3, 4, 5, 6, 7, or 8 (Type 0 to exit): " << endl << endl;

		// Checking for invalid input
		getline(cin, input);
		if (input.length() != 1)
			cout << endl << "You entered invalid input. Please type in one of the menu options: " << endl;
	} while (input.length() != 1);


	userFunction = input[0];
	// converting the string input to char

}

char VectorCustomers::GetMenuChoice() {
	return userFunction; // get the user's choice
}

void VectorCustomers::InputData() {
	string firstname;
	string lastname;
	int account = 0;
	string phone,zip;
	string address, city, state;
	string dummy;
	AllCustomers currPerson;

	ifstream inData;

	inData.open("input.txt"); // open file


	if (inData.fail())//checks that file can be opened
	{
		cerr << "File failed to open: input.txt";//spits out error message if not
		abort();// aborts program
	}



	getline(inData, firstname); // take first value out of the loop to avoid extra line


	// bringing in the data values from the file
	while (!inData.eof()) {
		getline(inData, lastname);
		currPerson.SetName(firstname, lastname);
		inData >> account;
		getline(inData, dummy);
		getline(inData, address);
		getline(inData, city);
		getline(inData, state);
		currPerson.SetAddressInfo(address, city, state);
		inData >> zip >> phone;
		getline(inData, dummy);
		currPerson.SetNumericalInfo(account, zip, phone);
		CustomerList.push_back(currPerson); //Pushing back all values to the vector
		getline(inData, firstname);
	}

	VectorCustomers::SetMax(account); // Getting max to set next account numbers

	inData.close(); // closing file

	
}
void VectorCustomers::InputPurchases() {
	AllPurchases currPerson;
	int account;
	string item;
	string date;
	float amount;
	string dummy;
	string problem;
	int counter;
	int i = 0;
	bool clearvector;

	

	ifstream inData;

	inData.open("Purchases.txt"); // open file


	if (inData.fail())//checks that file can be opened
	{
		cerr << "File failed to open: Purchases.txt";//spits out error message if not
		abort();// aborts program
	}


	PurchaseList.clear(); // clearing vector of values
	
	getline(inData, dummy);

	// bringing in the data values from the file
	while (!inData.eof()) {
		
		
		
		
		counter = 0;
		while (dummy != "-") {
			if (counter == 0) {
				account=stoi(dummy);
				currPerson.SetAccount(account);
				getline(inData, item);
				if (item == "-") { // clearing the vector from previous customer
					dummy = item;
					currPerson.ClearVector();
					break;
				}
			}
			if (counter == 1) // creating condition to loop through items until next customer
				item = dummy;
			getline(inData, date);
			inData >> amount;
			getline(inData, problem);
			if (counter == 0) {
				counter++;
				clearvector = true;
			}
			currPerson.SetVectorInfo(item, date, amount,clearvector); // setting the vector info for each item
			if (clearvector == true)
				clearvector = false;
			getline(inData, dummy);
		}
			
		
		PurchaseList.push_back(currPerson); //Pushing back all values to the vector
		getline(inData, dummy);
	}

	
	inData.close(); // closing file
}

void VectorCustomers::returnMenu() {

	string input;
	cout << "Type 'm' when you are ready to go back to the main menu" << endl;
	getline(cin, input);
	// invalid input checker
	while (input.length() != 1 || input[0] != 'm' && input[0] != 'M') {
		cout << endl << "You entered invalid input. Please type in 'm' to go back to the main menu: " << endl;
		getline(cin, input);
	}
}

void VectorCustomers::Choice1() {

	AllCustomers currPerson;


	// for loop to display rest of the info for the table for each person; different setw for some variables to make it look more centralized
		// displaying table headings using setw to define column length
	cout << endl << endl;
	cout << left << setw(5) << "#" << setw(23) << "Name" << setw(12) << "Account #" << setw(27) << "Address" << setw(19) << "City" << setw(8) << "State" << setw(8) << "Zip" << setw(15) << "Phone" << endl;
	cout << "_________________________________________________________________________________________________________________";
	cout << endl << endl;


	// Displays the list
	for (int i = 0; i < CustomerList.size(); i++) {
		currPerson = CustomerList.at(i);
		cout << setw(5) << i + 1 << setw(23) << currPerson.GetFirstName() + " " + currPerson.GetLastName() << right << setfill('0') << setw(5) << currPerson.GetAccount() << left << setfill(' ') << setw(7) << ""
			<< setw(27) << currPerson.GetAddress() << setw(19) << currPerson.GetCity()
			<< setw(8) << currPerson.GetState() << setw(8) << currPerson.GetZip()
			<< setw(10) << currPerson.GetPhone() << endl << endl;
	}

	cout << endl << endl;


}

void VectorCustomers::Choice2() {
	AllCustomers currPerson;
	vector<string> nameList;
	vector<int> accountList;
	int i = 0;
	string name;
	int account;
	size_t size=0;
	string namechoice, orderchoice;

	cout << "Type 1 to sort the customer list by first name." << endl;
	cout << "Type 2 to sort the customer list by last name." << endl;
	cout << "Type 3 to sort the customer list by account number." << endl;
	getline(cin, namechoice);

	while (namechoice != "1" && namechoice != "2" && namechoice!="3") { // getting user choice for what to sort
		cout << endl << "You entered invalid input. Please type in a valid number: " << endl << endl;
		getline(cin, namechoice);
	}


	for (i = 0; i < CustomerList.size(); i++) { // creating a vector of that type to sort easily
		currPerson = CustomerList.at(i);
		if (namechoice == "1") {
			name = currPerson.GetFirstName();
		}
		else if (namechoice == "2")
			name = currPerson.GetLastName();
		else
			account = currPerson.GetAccount();
		
		if (namechoice == "3")
			accountList.push_back(account);
		else
			nameList.push_back(name);
	}

	cout << endl << endl <<  "Type 1 to sort the customer list in ascending order." << endl;
	cout << "Type 2 to sort the customer list in descending order." << endl;
	getline(cin, orderchoice); // getting choice for sorting order

	while (orderchoice != "1" && orderchoice != "2") {
		cout << endl << "You entered invalid input. Please type in a valid number: " << endl << endl;
		getline(cin, orderchoice);
	}

	if (orderchoice == "1") { // sorting both vectors depending on choice
		sort(nameList.begin(), nameList.end());
		sort(accountList.begin(), accountList.end());
	}
	else {
		sort(nameList.begin(), nameList.end(), greater<string>());
		sort(accountList.begin(), accountList.end(), greater<int>());
	}

	if (namechoice == "3")
		size = accountList.size();
	else
		size = nameList.size();

	for (i = 0; i < size; i++) { // finding vector order and pushing back object before deleting ojbect from previous position
		for (int j = 0; j < size; j++) {
			currPerson = CustomerList.at(j);
			if (namechoice == "1")
				if (currPerson.GetFirstName() == nameList.at(i)) {
					CustomerList.push_back(currPerson);
					CustomerList.erase(CustomerList.begin() + j);
				}
			if (namechoice == "2")
				if (currPerson.GetLastName() == nameList.at(i)) {
					CustomerList.push_back(currPerson);
					CustomerList.erase(CustomerList.begin() + j);
				}
			if (namechoice == "3")
				if (currPerson.GetAccount() == accountList.at(i)) {
					CustomerList.push_back(currPerson);
					CustomerList.erase(CustomerList.begin() + j);
				}

		}

	}

	

	// for loop to display rest of the info for the table for each person; different setw for some variables to make it look more centralized
		// displaying table headings using setw to define column length
	cout << endl << endl;
	cout << left << setw(5) << "#" << setw(23) << "Name" << setw(12) << "Account #" << setw(27) << "Address" << setw(19) << "City" << setw(8) << "State" << setw(8) << "Zip" << setw(15) << "Phone" << endl;
	cout << "_________________________________________________________________________________________________________________";
	cout << endl << endl;


	// Displays the list
	for (i = 0; i < CustomerList.size(); i++) {
		currPerson = CustomerList.at(i);
		cout << setw(5) << i + 1 << setw(23) << currPerson.GetFirstName() + " " + currPerson.GetLastName() << right << setfill('0') << setw(5) << currPerson.GetAccount() << left << setfill(' ') << setw(7) << ""
			<< setw(27) << currPerson.GetAddress() << setw(19) << currPerson.GetCity()
			<< setw(8) << currPerson.GetState() << setw(8) << currPerson.GetZip()
			<< setw(10) << currPerson.GetPhone() << endl << endl;
	}

	cout << endl << endl;

	cout << "The customer list has been sorted! " << endl << endl;
}

void VectorCustomers::Choice3() {
	AllCustomers currPerson;
	string userPlayer;
	unsigned int i;

	system("CLS"); // clears screen

	cout  << "Here is the list of customers: " << endl << endl;
	for (i = 0; i < CustomerList.size(); i++) { // Shows list
		currPerson = CustomerList.at(i);
		cout << i + 1 << ". " << currPerson.GetFirstName() << " " << currPerson.GetLastName() << endl << endl;
	}

	cout << "Type a number to choose a specific customer: ";
	getline(cin, userPlayer);
	cout << endl;
	size_t size = CustomerList.size();
	i = 0;

	while (userPlayer == "") { // stops enter debugging error
		while (isdigit(userPlayer[i]) == false || stoi(userPlayer) > size || stoi(userPlayer) == 0 || userPlayer == "") {
			cout << endl << "You entered invalid input. Please type in a valid number: " << endl << endl;
			getline(cin, userPlayer);
			i = 0;
		}
	}

	for (i = 0; i < userPlayer.size(); i++) // checks for invalid input other than the enter key
		while (isdigit(userPlayer[i]) == false || stoi(userPlayer) > size || stoi(userPlayer) == 0) {
			cout << endl << "You entered invalid input. Please type in a valid number: " << endl << endl;
			getline(cin, userPlayer);
			i = 0;
		}




	
	system("CLS"); // clears screen
	cout << endl;
	// displays stats for specific person
	for ( i = 0; i < CustomerList.size(); i++) {
		currPerson = CustomerList.at(i);
		if ((i + 1) == stoi(userPlayer)) {
			cout << left << setw(5) << "#" << setw(23) << "Name" << setw(12) << "Account #" << setw(27) << "Address" << setw(19) << "City" << setw(8) << "State" << setw(8) << "Zip" << setw(15) << "Phone" << endl;
			cout << "_________________________________________________________________________________________________________________";
			cout << endl << endl;
			cout << setw(5) << i + 1 << setw(23) << currPerson.GetFirstName() + " " + currPerson.GetLastName() << right << setfill('0') << setw(5) << currPerson.GetAccount() << left << setfill(' ') << setw(7) << ""
				<< setw(27) << currPerson.GetAddress() << setw(19) << currPerson.GetCity()
				<< setw(8) << currPerson.GetState() << setw(8) << currPerson.GetZip()
				<< setw(10) << currPerson.GetPhone() << endl << endl;
			i = CustomerList.size();
		}
	}

}

void VectorCustomers::Choice4() {
	AllCustomers currPerson;
	string input;
	string choice;
	string userPlayer;
	string player;
	string  address, city, state, phone;
	string zip, account;
	string rightoutput;
	char statFunction = 0;

	

	cout << "Type 1 to update the person's information or type 2 to delete their information" << endl; // getting user choice
	getline(cin, choice);

	while (choice != "1" && choice != "2") {
		cout << endl << "You entered invalid input. Please type in a valid number: " << endl << endl;
		getline(cin, choice);
	}
	
	if (choice == "1") // choosing correct ouptut for choice
		rightoutput = "update";
	else
		rightoutput = "delete";


	cout << "Here is the list of customers: " << endl << endl;
	for (int i = 0; i < CustomerList.size(); i++) { // Shows list
		currPerson = CustomerList.at(i);
		cout << i + 1 << ". " << currPerson.GetFirstName() + " " + currPerson.GetLastName() << endl << endl;
	}
	cout << "Type the number of the customer you would like to choose: ";
	getline(cin, userPlayer);
	cout << endl;
	int size = CustomerList.size();
	int i = 0;

	//Checks for invalid input from enter key
	while (userPlayer == "")
		while (isdigit(userPlayer[i]) == false || stoi(userPlayer) > size || stoi(userPlayer) == 0 || userPlayer == "") {
			cout << endl << "You entered invalid input. Please type in a valid number: " << endl << endl;
			getline(cin, userPlayer);
			i = 0;
		}

	//Checks for any other invalid input 
	for (int i = 0; i < userPlayer.size(); i++)
		while (isdigit(userPlayer[i]) == false || stoi(userPlayer) > size || stoi(userPlayer) == 0) {
			cout << endl << "You entered invalid input. Please type in a valid number: " << endl << endl;
			getline(cin, userPlayer);
			i = 0;
		}

	// Finds player
	for (int i = 0; i < CustomerList.size(); i++) {
		currPerson = CustomerList.at(i);
		if (i + 1 == stoi(userPlayer)) {

			// Prints out questions for the code
			cout << "Which part of " << currPerson.GetFirstName() + " " + currPerson.GetLastName() << "'s account information would you like to " <<rightoutput << "?  \n"
				<< "Type 1 to " << rightoutput <<" " << currPerson.GetFirstName() + " " + currPerson.GetLastName() << "'s address. \n"
				<< "Type 2 to " << rightoutput << " " << currPerson.GetFirstName() + " " + currPerson.GetLastName() << "'s city. \n"
				<< "Type 3 to " << rightoutput << " " << currPerson.GetFirstName() + " " + currPerson.GetLastName() << "'s state. \n"
				<< "Type 4 to " << rightoutput << " " << currPerson.GetFirstName() + " " + currPerson.GetLastName() << "'s zip code. \n"
				<< "Type 5 to " << rightoutput << " " << currPerson.GetFirstName() + " " + currPerson.GetLastName() << "'s phone number. \n" << endl;

			// Checking for invalid input

			getline(cin, input);
			while (input.length() != 1 || input[0] < '1' || input[0]>'5') {
				cout << endl << "You entered invalid input. Please type in one of the options: " << endl;
				getline(cin, input);
			}

			statFunction = input[0];
			switch (statFunction) { //different options methods
				
			case '1': // Updating Address 
				if (choice == "2") {
					address = '-';
				}
				else {
					cout << "Type " << currPerson.GetFirstName() + " " + currPerson.GetLastName() << "'s new address. " << endl;
					getline(cin, address);
				}
				CustomerList.at(i).SetAddressInfo(address, currPerson.GetCity(), currPerson.GetState());
				cout << currPerson.GetFirstName() + " " + currPerson.GetLastName() << "'s address has been " << rightoutput << "d! " << endl;
				break;
			case '2': // Updating City
				if (choice == "2") {
					city = '-';
				}
				else {
					cout << "Type " << currPerson.GetFirstName() + " " + currPerson.GetLastName() << "'s new city. " << endl;
					getline(cin, city);
				}
				CustomerList.at(i).SetAddressInfo(currPerson.GetAddress(), city, currPerson.GetState());
				cout << currPerson.GetFirstName() + " " + currPerson.GetLastName() << "'s city has been " << rightoutput << "d! " << endl;
				break;
			case '3': // Updating State
				if (choice == "2") {
					state = '-';
				}
				else {
					cout << "Type " << currPerson.GetFirstName() + " " + currPerson.GetLastName() << "'s new state. " << endl;
					
					getline(cin, state);

					int j;
					int count=0;

					while (count==0){
					for (j = 0; j < StateList.size(); j++) 
						if (CompareString(state,StateList.at(j))) {
							count++;
							if (j < 50)
								state = StateList.at(j + 50);
							j = StateList.size();
						}
					if (count == 0) {
						cout << "You entered invalid input. Please type in a valid state." << endl << endl;
						getline(cin, state);
					}
					}
				}
				CustomerList.at(i).SetAddressInfo(currPerson.GetAddress(), currPerson.GetCity(), state);
				cout << currPerson.GetFirstName() + " " + currPerson.GetLastName() << "'s state has been " << rightoutput << "d! " << endl;
				break;
			case '4': // Updating Zip Code
				if (choice == "2") {
					zip = "-";
				}
				else {
					cout << "Type " << currPerson.GetFirstName() + " " + currPerson.GetLastName() << "'s new zip code. " << endl;
					zip =invalidInput();
					while (zip.length() != 5) {
						cout << "You entered invalid input! Please type in a valid zip code." << endl;
						zip = invalidInput();
					}
				}
				CustomerList.at(i).SetNumericalInfo(currPerson.GetAccount(), zip, currPerson.GetPhone());
				cout << currPerson.GetFirstName() + " " + currPerson.GetLastName() << "'s zip code has been " << rightoutput << "d! " << endl;
				break;
			case '5': // Updating Phone Number
				if (choice == "2") {
					phone = '-';
				}
				else {
					cout << "Type " << currPerson.GetFirstName() + " " + currPerson.GetLastName() << "'s new phone number. " << endl;
					phone = invalidInput();
					while (phone.length() != 10) {
						cout << "You entered invalid input! Please type in a valid ten digit phone number." << endl;
						phone = invalidInput();
					}
				}
				CustomerList.at(i).SetNumericalInfo(currPerson.GetAccount(), currPerson.GetZip(), phone);
				cout << currPerson.GetFirstName() + " " + currPerson.GetLastName() << "'s phone number has been " << rightoutput << "d! " << endl;
				break;
			default: cout << "Oops something went wrong!";
			}

			i = CustomerList.size();

		}
	}
}

void VectorCustomers::Choice5() {
	int input;

	cout << "How many new customers would you like to add to the database" << endl;
	input = (stoi(invalidInput()));
	if (input > 0) {
		VectorCustomers::AddCustomer(input); // calling recursive function
	}
}

void VectorCustomers::Choice6() {
	int input;
	AllCustomers currPerson;
	string userPlayer;

	cout << "How many new purchases would you like to add to the database" << endl;
	input = (stoi(invalidInput()));
	if (input > 0) {
		
		VectorCustomers::AddPurchase(input, userPlayer); // calling recursive function
	}
}


void VectorCustomers::Choice7() {
	AllCustomers currPerson;
	string userPlayer;
	int comparison=0;
	AllPurchases currCustomer;
	float total=0;
	


	cout << "Here is the list of customers: " << endl << endl;
	for (int i = 0; i < CustomerList.size(); i++) { // Shows list
		currPerson = CustomerList.at(i);
		cout << i + 1 << ". " << currPerson.GetFirstName() << " " << currPerson.GetLastName() << endl << endl;
	}

	cout << "Type the number of the number of the customer you would like to choose: ";
	getline(cin, userPlayer);
	cout << endl;
	int size = CustomerList.size();
	int i = 0;

	while (userPlayer == "") { // stops enter debugging error
		while (isdigit(userPlayer[i]) == false || stoi(userPlayer) > size || stoi(userPlayer) == 0 || userPlayer == "") {
			cout << endl << "You entered invalid input. Please type in a valid number: " << endl << endl;
			getline(cin, userPlayer);
			i = 0;
		}
	}

	for (int i = 0; i < userPlayer.size(); i++) // checks for invalid input other than the enter key
		while (isdigit(userPlayer[i]) == false || stoi(userPlayer) > size || stoi(userPlayer) == 0) {
			cout << endl << "You entered invalid input. Please type in a valid number: " << endl << endl;
			getline(cin, userPlayer);
			i = 0;
		}




	cout << endl;
	// selects correct purson
	for (int i = 0; i < CustomerList.size(); i++) {
		currPerson = CustomerList.at(i);
		if ((i + 1) == stoi(userPlayer)) {
			comparison = currPerson.GetAccount();
			i = CustomerList.size();
		}
	}

	cout << fixed << setprecision(2);

	for (i = 0; i < PurchaseList.size(); i++) { // finds items for account number and displays it with total spent
		currCustomer = PurchaseList.at(i);
		if (comparison == currCustomer.GetAccount()) {
			cout << "Account Number: " << setfill('0') << setw(4) << "" << setfill(' ') << currCustomer.GetAccount() << endl << endl;
			for (int j = 0; j < currCustomer.GetVectorSize(); j++) {
				cout << "Item " << j + 1 << ": " << currCustomer.GetItems(j) << endl;
				cout << setw(2) << "" << "Date"  << ": " << currCustomer.GetDates(j) << endl;
				cout << setw(1) << "" << "Price"  << ": $" << currCustomer.GetPrices(j) << endl << endl;
				total += currCustomer.GetPrices(j);

			}
			cout << endl;
			i = PurchaseList.size();
		}
	}


	cout << "The total amount spent by " << currPerson.GetFirstName() << " " << currPerson.GetLastName() << " is $" << total;
	cout << endl << endl;

}


void VectorCustomers::Choice8() {
	AllCustomers currPerson;
	AllPurchases currCustomer;
	ofstream outData;
	string choice;
	string customerinfo;
	string purchaseinfo;

	cout << "Type 1 to save over the current files or type 2 to save to new files" << endl; // choice for output
	getline(cin, choice);

	while (choice != "1" && choice != "2") {
		cout << endl << "You entered invalid input. Please type in a valid number: " << endl << endl;
		getline(cin, choice);
	}

	if (choice == "1") { // correct choice for file
		customerinfo = "input.txt";
		purchaseinfo = "Purchases.txt";
	}
	else {
		customerinfo = "output.txt";
		purchaseinfo = "newpurchases.txt";
	}


	cout << "Your data has been outputted to your external files! " << endl;
	outData.open(customerinfo); //opens output file

	if (outData.fail()) //checks that file can be opened
	{
		cerr << "File failed to open:" << customerinfo; //spits out error message if not
		abort(); // aborts program
	}


	for (int i = 0; i < CustomerList.size(); i++) { // printing in output file
		currPerson = CustomerList.at(i);
		outData << currPerson.GetFirstName() << endl << currPerson.GetLastName() << endl << right << setfill('0') << setw(5) << currPerson.GetAccount() << left << setfill(' ')
			<< endl << currPerson.GetAddress() << endl << currPerson.GetCity()
			<< endl << currPerson.GetState() << endl << currPerson.GetZip()
			<< " " << currPerson.GetPhone() << endl;
	}

	cout << endl << endl;

	outData.close();

	outData.open(purchaseinfo); //opens output file

	if (outData.fail()) //checks that file can be opened
	{
		cerr << "File failed to open:" << purchaseinfo; //spits out error message if not
		abort(); // aborts program
	}

	for (int i = 0; i < PurchaseList.size(); i++) { // printing in output file
		currCustomer = PurchaseList.at(i);
		outData << right << setfill('0') << setw(5) << currCustomer.GetAccount() << left << setfill(' ') << endl;
		for (int j = 0; j < currCustomer.GetVectorSize(); j++) {
			outData << currCustomer.GetItems(j) << endl;
			outData << currCustomer.GetDates(j) << endl;
			outData << currCustomer.GetPrices(j) << endl;
		}
		outData << "-" << endl;
	}

	outData.close();
}

void VectorCustomers::AddCustomer(int repetitions) { // recursive function
	AllCustomers currPerson;
	AllPurchases currCustomer;
	string input;
	string firstname;
	string lastname;
	string player, address, phone, city, state;
	string zip;
	int account;
	

	 if (repetitions == 1) { // base case
		cout << "Type the first name of the person you would like to add: " << endl;
		getline(cin, firstname);
		while (firstname == "") { //Checks against enter key
			cout << endl << "You entered invalid input. Please type a valid first name: " << endl << endl;
			getline(cin, firstname);
		}

		cout << "Now type their last name: " << endl;
		getline(cin, lastname);
		while (lastname == "") { //Checks against enter key
			cout << endl << "You entered invalid input. Please type a valid last name: " << endl << endl;
			getline(cin, lastname);
		}
		currPerson.SetName(firstname, lastname);


		cout << "Type the person's address: " << endl;
		getline(cin, address);
		while (address == "") { // Checks against enter key
			cout << endl << "You entered invalid input. Please type in a valid address: " << endl << endl;
			getline(cin, address);
		}

		cout << "Type the person's city: " << endl;
		getline(cin, city);
		while (city == "") { // Checks against enter key
			cout << endl << "You entered invalid input. Please type in a valid city: " << endl << endl;
			getline(cin, city);
		}

		cout << "Type the person's state: " << endl;
		getline(cin, state);

		int j;
		int count = 0;

		while (count == 0) { // matches state
			for (j = 0; j < StateList.size(); j++)
				if (CompareString(state, StateList.at(j))) {
					count++;
					if (j < 50)
						state = StateList.at(j + 50);
					j = StateList.size();
				}
			if (count == 0) {
				cout << "You entered invalid input. Please type in a valid state." << endl << endl;
				getline(cin, state);
			}
		}

		currPerson.SetAddressInfo(address, city, state);

		cout << "Type the person's zip code: " << endl; // zip code
		zip = invalidInput();
		while (zip.length() != 5) {
			cout << "You entered invalid input! Please type in a valid zip code." << endl;
			zip = invalidInput();
		}

		cout << "Type the person's phone number: " << endl; // phone number
		phone = invalidInput();
		while (phone.length() != 10) {
			cout << "You entered invalid input! Please type in a valid ten digit phone number." << endl;
			phone = invalidInput();
		}


		account = VectorCustomers::GetMax() + 1; // setting next account
		VectorCustomers::SetMax(account);
		currPerson.SetNumericalInfo(account, zip, phone); // sets info for customer
		currCustomer.SetAccount(account); // sets account

		CustomerList.push_back(currPerson);
		PurchaseList.push_back(currCustomer);
		cout << currPerson.GetFirstName() << " " << currPerson.GetLastName() << " has been added! " << endl << endl << endl;
	}
	else // recursive case
	{
		AddCustomer(1); // does the base case
		AddCustomer(repetitions - 1); // calls itself again
	}
}





void VectorCustomers::AddPurchase(int repetitions,string userPlayer) { // recursive function
	AllCustomers currPerson;
	AllPurchases currCustomer;
	int comparison=0;
	string input;
	string firstname;
	string lastname;
	string player, account, address, phone, city, state;
	string item,date;
	float amount = 0;
	bool clearvector = false;
	int i=0,j=0;
	if (repetitions == 1) { // base case
		cout << "Here is the list of customers: " << endl << endl;
		for (int i = 0; i < CustomerList.size(); i++) { // Shows list
			currPerson = CustomerList.at(i);
			cout << i + 1 << ". " << currPerson.GetFirstName() << " " << currPerson.GetLastName() << endl << endl;
		}

		cout << "Type the number of the customer you would like to choose: ";
		getline(cin, userPlayer);
		cout << endl;
		int size = CustomerList.size();
		int i = 0;

		while (userPlayer == "") { // stops enter debugging error
			while (isdigit(userPlayer[i]) == false || stoi(userPlayer) > size || stoi(userPlayer) == 0 || userPlayer == "") {
				cout << endl << "You entered invalid input. Please type in a valid number: " << endl << endl;
				getline(cin, userPlayer);
				i = 0;
			}
		}

		for (int i = 0; i < userPlayer.size(); i++) // checks for invalid input other than the enter key
			while (isdigit(userPlayer[i]) == false || stoi(userPlayer) > size || stoi(userPlayer) == 0) {
				cout << endl << "You entered invalid input. Please type in a valid number: " << endl << endl;
				getline(cin, userPlayer);
				i = 0;
			}

		cout << endl;
	
	// displays stats for specific person
	for (i = 0; i < CustomerList.size(); i++) {
		currPerson = CustomerList.at(i);
		if ((i + 1) == stoi(userPlayer)) {
			comparison = currPerson.GetAccount();
			i = CustomerList.size();
		}
	}

	for (i = 0; i < PurchaseList.size(); i++) {
		currCustomer = PurchaseList.at(i);
		if (comparison == currCustomer.GetAccount()) {
			j = i;
			i = PurchaseList.size();
		}
	}
		cout << "Type the name of the car that was purchased: "; // car name
		getline(cin, item);
		while (item == "") { //Checks against enter key
			cout << endl << "You entered invalid input. Please type a valid car: " << endl << endl;
			getline(cin, item);
		}


		cout << "Type in the date of purchase in (mm/dd/yy) format Ex:(04/26/03): ";
		getline(cin, date);
		
		while (date == ""|| date.length() != 8){ //Checks against enter key
			cout << endl << "You entered invalid input. Please type a valid date: (mm/dd/yy) " << endl << endl;
			getline(cin, date);
		}


		cout << "Type in the purchase price: $"; //gets amount
		amount = stof(invalidInput());

		
		currCustomer.SetVectorInfo(item, date, amount, clearvector);

		PurchaseList.erase(PurchaseList.begin() + j); 
		if (j > PurchaseList.size()-1) { // pushes back if vector has been deleted else adds to the customer list
			PurchaseList.push_back(currCustomer);
		}
		else
		PurchaseList.at(j)=currCustomer; // adds item
		cout << "The " << item << " has been added! " << endl << endl << endl;
	}
	else
	{
		AddPurchase(1,userPlayer); // base case
		AddPurchase(repetitions - 1,userPlayer); // recursive case
	}

}

string VectorCustomers::invalidInput() {
	int i = 0;
	string input;
	getline(cin, input);
	while (input == "") // enter key checker
		while (isdigit(input[i]) == false || input == "") {
			cout << endl << "You entered invalid input. Please type in a valid number: " << endl << endl;
			getline(cin, input);
			i = 0;
		}

	for (int i = 0; i < input.length(); i++) // invalid input checker
		while (isdigit(input[i]) == false) {
			cout << endl << "You entered invalid input. Please type in a valid number: " << endl << endl;
			getline(cin, input);
			i = 0;
		}
	return input;
}
void VectorCustomers::userName() {
	string username;
	cout << "What is your name? ";
	getline(cin, username);
	while (username == "") // enter key checker
	{
		cout << endl << "You entered invalid input. Please enter a valid name: " << endl << endl;
		getline(cin, username);
	}
	cout << endl << endl;

	cout << "Hi " << username << "! Welcome to the database for Andrew's Shady Car Dealership. Cars mysteriously appear in our parking lot \novernight ";
	cout << "which we sell to our extremely rich customers for suspiciously low prices. Just don't ask too many \nquestions. Here's the main menu:" << endl;
	this->username = username; // pointer
}

string VectorCustomers::GetuserName() {
	return username;
}

void VectorCustomers::SetMax(int max) { // setting max
	this->max=max;
}

int VectorCustomers::GetMax() { // getting max
	return max;
}

int VectorCustomers::CompareString(string s1, string s2) {
	//convert s1 and s2 into lower case strings
	transform(s1.begin(), s1.end(), s1.begin(), ::tolower);
	transform(s2.begin(), s2.end(), s2.begin(), ::tolower);
	if (s1.compare(s2) == 0)
		return 1; //The strings are same
	return 0; //not matched
}

