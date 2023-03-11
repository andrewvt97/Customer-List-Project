// Andrew Thomas
// Final Project AllCustomers.h


#ifndef ALLCUSTOMERS_H
#define ALLCUSTOMERS_H

#include <string>
using namespace std;


class AllCustomers {

public:
	AllCustomers();
	void SetName(string firstname, string lastname);
	void SetNumericalInfo(int account, string zip, string phone);
	void SetAddressInfo(string address, string city, string state);
	string GetFirstName();
	string GetLastName();
	int GetAccount();
	string GetAddress();
	string GetCity();
	string GetState();
	string GetZip();
	string GetPhone();



	

private:
	string firstname;
	string lastname;
	string address;
	string city;
	string state;
	int account;
	string phone;
	string zip;
	

};


#endif

