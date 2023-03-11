// Andrew Thomas
// Final Project AllCustomers.cpp

#include "AllCustomers.h"
#include <iostream>
#include <cstring>
#include <algorithm>


using namespace std;


AllCustomers::AllCustomers() { // constructor
	firstname = "NoFirst";
	lastname = "NoLast";
	address = "NoAddress";
	city = "NoCity";
	state = "NoState";
	account = -1;
	zip = -1;
	phone = " - 1";

}

void AllCustomers::SetName(string first, string last) { // setting name
	firstname = first;
	lastname = last;
	 
}

void AllCustomers::SetNumericalInfo(int account, string zip, string phone) { // setting numerical info
	this->account = account;
	this->zip = zip;
	this->phone = phone;

}

void AllCustomers::SetAddressInfo(string address, string city, string state) { // setting address info
	this->address = address;
	this->city = city;
	this->state = state;

}

string AllCustomers:: GetFirstName() {
	return firstname;
}

string AllCustomers::GetLastName() {
	return lastname;
}


string AllCustomers::GetAddress()
{
	return address;
}
int AllCustomers::GetAccount()
{
	return account;
}
string AllCustomers::GetZip()
{
	return zip;
}
string AllCustomers::GetPhone()
{
	return phone;
}
string AllCustomers::GetCity()
{
	return city;
}
string AllCustomers::GetState()
{
	return state;
}

