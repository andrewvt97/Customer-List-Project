// Andrew Thomas
// Final Project VectorCustomers.h

#ifndef VectorCustomers_H
#define VectorCustomers_H

#include "AllCustomers.h"
#include "AllPurchases.h"


class VectorCustomers {

public:
	VectorCustomers();
	void LoadMenu();
	void InputData();
	void InputPurchases();
	void returnMenu();
	string invalidInput();
	void userName();
	string GetuserName();
	char GetMenuChoice();
	void Choice1();
	void Choice2();
	void Choice3();
	void AddCustomer(int repetitions);
	void AddPurchase(int repetitions,string userPlayer);
	void Choice4();
	void Choice5();
	void Choice6();
	void Choice7();
	void Choice8();
	void SetMax(int max);
	int GetMax();
	int CompareString(string s1, string s2);
	vector<string> StateList = { "Alabama", "Alaska", "Arizona", "Arkansas", "California", "Colorado", "Connecticut", "Delaware", "Florida","Georgia", "Hawaii", "Idaho", "Illinois", "Indiana", "Iowa", "Kansas", "Kentucky", "Louisiana", "Maine",
		"Maryland", "Massachusetts", "Michigan", "Minnesota", "Mississippi", "Missouri", "Montana","Nebraska", "Nevada", "New Hampshire", "New Jersey", "New Mexico", "New York", "North Carolina", "North Dakota", "Ohio", "Oklahoma", "Oregon", "Pennsylvania", "Rhode Island",
		"South Carolina", "South Dakota", "Tennessee", "Texas", "Utah", "Vermont", "Virginia", "Washington", "West Virginia", "Wisconsin", "Wyoming","AL","AK","AZ","AR","CA","CO","CT","DE",
		"FL","GA","HI","ID","IL","IN","IA","KS","KY","LA","ME","MD","MA","MI","MN","MS","MO","MT","NE","NV","NH","NJ","NM","NY","NC","ND","OH","OK","OR","PA","RI","SC","SD","TN","TX","UT","VT","VA","WA","WV","WI","WY"};
	
	


private:
	vector<AllCustomers> CustomerList;
	vector<AllPurchases> PurchaseList;
	
	int userFunction;
	int max;
	string username;
};

#endif
#pragma once
