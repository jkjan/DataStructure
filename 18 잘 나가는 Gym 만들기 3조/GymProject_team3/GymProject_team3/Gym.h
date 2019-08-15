#pragma once
#include<string>
#include<vector>
#include<ctime>
#include"Customer.h"
using namespace std;
class Gym {
	vector<Customer> customerList;
	static time_t curr;
	static struct tm* d;
public:
	Gym();

	void addCustomer(char line[]);
	void printAllCustomerInformation();
	void printCustomerListInformation(const vector<Customer>&);
	void printCustomerOneInformation(const Customer&);
	void printCustomerOneInformationByCustomerID(unsigned int);
	void printCustomerListInformationByCustomerID(const vector<int>&);
	
	Customer& getCustomerInformationByID(unsigned int cid);

	// 1
	void getMaxCustomerOfTrainer();
	// 3
	void getMaxAttendanceCustomer();
	// 4
	void getMaxMinHomeCustomer();
	// 5
	void getMaxRegistMonth();
	// 6
	void getMaxOldCustomer();
	// 11
	void getPTMemberAndNoLocker();
	// 12
	void getRateAgeTwenty();
	// 13 
	void getMaxLongestDoNotAttendanceCustomer();
	// 14
	void getEarlyRegistCancleCustomer();
	// 19
	void getMaxMinAgeLevel();

	friend int getAge(const Customer&);
	friend bool isValidCustomer(const Customer&);
};

int compareAge(const Customer&, const Customer&);
bool isValidCustomer(const Customer&);
int getAge(const Customer&);
long long totalday(int, int, int);
long long totalday(string);