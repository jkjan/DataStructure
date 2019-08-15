#pragma once
#include<string>
using namespace std;
class Customer {
public:
	int customerID;
	string name;
	string home;
	string phoneNumber;
	string birthday;

	string recommender;

	string lastOrderTickeMonth;
	string expiredDate;

	bool isPTmember;
	string trainerName;

	double firstBMI;
	double currentBMI;
	double objectBMI;

	int locker;

	int countExercise;
	int countPT;

	string firstRegistDate;
	string lastExerciseDate;

	Customer();
	Customer(int, string, string, string, string, string, string, bool, string,
		double, double, double, int, string, int, int, string, string);
};

class CancleCustomer {
public:
	int id;
	long long diffDay;
	double rate;
	int score1, score2;
};

bool operator<(const CancleCustomer& left, const CancleCustomer& right);