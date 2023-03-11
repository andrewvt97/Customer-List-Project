#pragma once
#ifndef ALLPURCHASES_H
#define ALLPURCHASES_H
// Andrew Thomas
// Final Project AllPurchases.h

#include <string>
#include <vector>
using namespace std;


class AllPurchases
{
public:
	void SetAccount(int account);
	void SetVectorInfo(string car, string date, float amount, bool clean);
	void ClearVector();
	int GetAccount();
	string GetItems(int i);
	string GetDates(int i);
	float GetPrices(int i);
	int GetVectorSize();
	
	


private:
	int account;
	vector<string> items;
	vector<string> dates;
	vector<float> prices;


};

#endif

