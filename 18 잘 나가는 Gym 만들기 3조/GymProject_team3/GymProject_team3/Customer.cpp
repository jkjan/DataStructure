#include "Customer.h"
#include <string>
#include <ctime>
using namespace std;
Customer::Customer() : Customer(0, "", "", "", "", "", "", false, "", 0, 0, 0, 0, "", 0, 0, "", "") {}
Customer::Customer(int _id, string _name, string _home, string _phone, string _recommender,
	string _birthday, string _lastOrderTickeMonth, bool _isPT, string _trainer,
	double _firstBMI, double _curBMI, double _objBMI, int _locker, string _firstRegistDate,
	int _countExe, int _countPT, string _lastExerciseDate, string _expiredDate) {
	this->customerID = _id;
	this->name = _name;
	this->home = _home;
	this->phoneNumber = _phone;
	this->recommender = _recommender;
	this->birthday = _birthday;
	this->lastOrderTickeMonth = _lastOrderTickeMonth;
	this->isPTmember = _isPT;
	this->trainerName = _trainer;
	this->firstBMI = _firstBMI;
	this->currentBMI = _curBMI;
	this->objectBMI = _objBMI;
	this->locker = _locker;
	this->firstRegistDate = _firstRegistDate;
	this->countExercise = _countExe;
	this->countPT = _countPT;
	this->lastExerciseDate = _lastExerciseDate;
	this->expiredDate = _expiredDate;
}

bool operator<(const CancleCustomer& left, const CancleCustomer& right) {
	if (left.score1 + left.score2 < right.score1 + right.score2)
		return true;
	else return false;
}