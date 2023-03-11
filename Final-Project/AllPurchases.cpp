// Andrew Thomas
// Final Project AllPurchases.cpp

#include "AllPurchases.h"



#include "AllPurchases.h"
#include <iostream>
#include <vector>

using namespace std;




void AllPurchases::SetAccount(int account) { // setting account
	this->account = account;
	
}

void AllPurchases::SetVectorInfo(string car, string date, float amount,bool clean) { // clearing vector for next customer
	if (clean == true) {
		items.clear();
		dates.clear();
		prices.clear();
	}
	items.push_back(car);
	dates.push_back(date);
	prices.push_back(amount);
}

void AllPurchases::ClearVector() { // clears vector if needed
		items.clear();
		dates.clear();
		prices.clear();
}


int AllPurchases::GetAccount()
{
	return account;
}

string AllPurchases::GetItems(int i) // returns a particular item
{
	return items.at(i);
}

string AllPurchases::GetDates(int i) // returns a particular date
{
	return dates.at(i);
}

float AllPurchases::GetPrices(int i) // returns a particular price
{
	return prices.at(i);
}

int AllPurchases::GetVectorSize() {
	return items.size();
}


