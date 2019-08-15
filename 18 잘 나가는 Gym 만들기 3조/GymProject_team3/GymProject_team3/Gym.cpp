#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<string>
#include<vector>
#include<sstream>
#include<map>
#include<queue>
#include<ctime>
#include "Customer.h"
#include "Gym.h"
using namespace std;
vector<string> split(const char line[], char delimiter) {
	vector<string> tokenizer;
	stringstream ss(line);
	string temp;

	while (getline(ss, temp, delimiter)) {
		tokenizer.push_back(temp);
	}
	
	string& lastElem = tokenizer.back();
	size_t lastElemSize = lastElem.size();
	if (lastElem.at(lastElemSize - 1) == '\n')
		lastElem = lastElem.substr(0, lastElemSize - (size_t)1);
	
	return tokenizer;
}

Gym::Gym(){}
time_t Gym::curr = time(NULL);
struct tm* Gym::d = localtime(&curr);

void Gym::addCustomer(char line[]) {
	vector<string> token = split(line, ',');

	int token12 = 0;
	if (!(token[12] == "-" || token[12] == "")) {
		token12 = stoi(token[12]);
	}
	int token14 = 0;
	if (!(token[14] == "-" || token[14] == "")) {
		token14 = stoi(token[14]);
	}
	int token15 = 0;
	if (!(token[15] == "-" || token[15] == "")) {
		token15 = stoi(token[15]);
	}
	this->customerList.push_back(Customer(stoi(token[0]), token[1], token[2], token[3], token[4], token[5], token[6], token[7] == "Y" ? true : false, token[8], 
												stod(token[9]), stod(token[10]), stod(token[11]), token12, token[13], token14, token15, token[16], token[17]));
}

void Gym::printAllCustomerInformation() {
	printCustomerListInformation(this->customerList);
}

void Gym::printCustomerListInformation(const vector<Customer>& customerListDetail) {
	for (const Customer& customers : customerListDetail) {
		printCustomerOneInformation(customers);
	}
	cout << ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>총 [" << customerListDetail.size() << "]명을 출력하였습니다.<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<\n\n";
}
void Gym::printCustomerOneInformation(const Customer& customer){
	printf(" %3d ", customer.customerID);
	printf(" %8s ", customer.name.c_str());
	printf(" %8s ", customer.home.c_str());
	printf(" %14s ", customer.phoneNumber.c_str());
	printf(" %8s ", customer.recommender.c_str());
	printf(" %9s ", customer.birthday.c_str());
	printf(" %8s ", customer.lastOrderTickeMonth.c_str());
	customer.isPTmember ? printf(" Y ") : printf(" N ");
	printf(" %8s ", customer.trainerName.c_str());
	printf(" %.2lf ", customer.firstBMI);
	printf(" %.2lf ", customer.currentBMI);
	printf(" %.2lf ", customer.objectBMI);
	printf(" %4d ", customer.locker);
	printf(" %9s ", customer.firstRegistDate.c_str());
	printf(" %3d ", customer.countExercise);
	printf(" %3d ", customer.countPT);
	printf(" %9s ", customer.lastExerciseDate.c_str());
	printf(" %9s ", customer.expiredDate.c_str());
	printf("\n\n");
}

void Gym::printCustomerOneInformationByCustomerID(unsigned int cid) {
	if (cid <= 0) {
		printf("회원 아이디 0 이하인 값을 찾고 계십니다. 회원 아이디는 1부터 시작합니다. 다시 한번 확인해 주십시오.\n");
		return;
	}
	printCustomerOneInformation(this->customerList[cid - 1]);
}
void Gym::printCustomerListInformationByCustomerID(const vector<int>& customerListDetailByID) {
	for (int customerID : customerListDetailByID) {
		printCustomerOneInformationByCustomerID(customerID);
	}
	cout << ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>총 [" << customerListDetailByID.size() << "]명을 출력하였습니다.<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<\n\n";
}

Customer& Gym::getCustomerInformationByID(unsigned int cid) {
	if (cid <= 0) {
		printf("회원 아이디 0 이하인 값을 찾고 계십니다. 회원 아이디는 1부터 시작합니다. 다시 한번 확인해 주십시오.\n");
		return customerList[0];
	}
	return this->customerList[cid - 1];
}

// 1
void Gym::getMaxCustomerOfTrainer(){
	map<string, int> countMem;
	for (Customer& c : this->customerList) {
		if (isValidCustomer(c) && c.isPTmember)
			countMem[c.trainerName]++;
	}

	priority_queue<pair<int, string>> trainer;
	for (pair<string, int> countPair : countMem) {
		trainer.push(make_pair(countPair.second, countPair.first));
	}
	printf("가장 많은 회원 수를 가지는 트레이너 5명만 추출합니다.\n\n");
	for (int i = 0; i < 5; i++) {
		pair<int, string> popElem = trainer.top();
		printf("트레이너 : [%s] ===========> [%d] 명의 회원 수를 보유하고 있습니다.\n\n", popElem.second.c_str(), popElem.first);
		trainer.pop();
	}
}
// 3
void Gym::getMaxAttendanceCustomer() {
	priority_queue<pair<double, int>> attendance;
	long long now = totalday(this->d->tm_year + 1900, this->d->tm_mon + 1, this->d->tm_mday);

	for (const Customer& c : this->customerList) {
		if (isValidCustomer(c)) {
			long long diffDay = now - totalday(c.firstRegistDate);
			if (diffDay > 0) {
				double rate = (double)c.countExercise / diffDay;
				if (rate < 1) { // 운동한 횟수가 두 날짜의 차이보다 크다면 논리적 오류가 있는 데이터 이므로 출력하지 않는다.
					attendance.push(make_pair(rate, c.customerID));
				}
			}
		}
	}
	
	// 10개 뽑기
	printf("가장 높은 출석률을 가지는 사람 10명을 추출합니다.\n\n");
	for (int i = 0; i < 10; i++) {
		const Customer& popElem = getCustomerInformationByID(attendance.top().second);
		printf("%2d번째 =====> 회원번호[%3d] : 회원이름[%6s] : 최초 등록일 [%s] : 누적 운동 횟수 [%4d] : 출석률[%lf]\n\n", i + 1, popElem.customerID, popElem.name.c_str(), popElem.firstRegistDate.c_str(), popElem.countExercise, attendance.top().first);
		attendance.pop();
	}
}
// 4
void Gym::getMaxMinHomeCustomer() {
	map<string, int> countHome;
	for (const Customer& c : this->customerList) {
		if (isValidCustomer(c))
			countHome[c.home]++;
	}

	multimap<int, string> countHomeMulti;
	for (const pair<string, int>& pairStringInt : countHome) {
		countHomeMulti.insert(make_pair(pairStringInt.second, pairStringInt.first));
	}

	auto maxElem = countHomeMulti.rbegin();
	printf("가장 많은 거주지는 다음과 같습니다. ======> ");
	for (int i = 0; i < 2; i++) {
		printf("<[%s] : [%3d명]> ", maxElem->second.c_str(), maxElem->first);
		maxElem++;
	}
	printf("\n\n");
	printf("가장 적은 거주지는 다음과 같습니다. ======> ");
	auto minElem = countHomeMulti.begin();
	for (int i = 0; i < 2; i++) {
		printf("<[%s] : [%3d명]> ", minElem->second.c_str(), minElem->first);
		minElem++;
	}
	printf("\n\n");
}
// 5
void Gym::getMaxRegistMonth() {
	int month[13] = { 0, };
	for (Customer& c : this->customerList) {
		if (isValidCustomer(c)) {
			int mm = stoi(c.firstRegistDate.substr(7, 2));
			month[mm]++;
		}

	}
	int maxMonth = 1;
	int minMonth = 1;
	int maxValue = month[1];
	int minValue = month[1];


	for (int i = 2; i <= 12; i++) {
		if (month[i] > maxValue) {
			maxMonth = i;
			maxValue = month[i];
		}
		if (month[i] < minValue) {
			minMonth = i;
			minValue = month[i];
		}
	}
	for (int i = 1; i <= 12; i++) {
		printf("%2d월\t", i);
	}
	printf("\n");
	for (int i = 1; i <= 12; i++) {
		printf(" %3d\t", month[i]);
	}
	printf("\n\n");


	printf("최대 등록 달은[");
	for (int i = 1; i < 13; i++) {
		if (maxValue == month[i])
			printf("%d ", i);
	}
	printf("]월 입니다 \n\n");

	printf("최소 등록 달은[");
	for (int i = 1; i < 13; i++) {
		if (minValue == month[i])
			printf("%d ", i);
	}
	printf("]월 입니다 \n\n");
}
// 6
void Gym::getMaxOldCustomer() { 
	priority_queue<pair<long long, int>> oldCustomer;
	long long now = totalday(this->d->tm_year + 1900, this->d->tm_mon + 1, this->d->tm_mday);

	for (const Customer& c : this->customerList) {
		if (isValidCustomer(c)) {
			long long firstDate = totalday(c.firstRegistDate);
			if(now - firstDate >= 0)
				oldCustomer.push(make_pair(now - firstDate, c.customerID));
		}
	}
	
	// 10개 뽑기
	printf("등록된 회원 중 최초 등록일이 빠른 사람 10명을 추출합니다.\n\n");
	for (int i = 0; i < 10; i++) {
		const pair<long long, int>& popElem = oldCustomer.top();
		const Customer& popCustomer = getCustomerInformationByID(popElem.second);
		printf("%2d번째 =====> 회원번호[%3d] : 회원이름[%6s] : 등록권 만료일자[%s] :최초 등록일 [%s] : 오늘 날짜와의 차이[%lld]\n\n", i + 1, popCustomer.customerID, popCustomer.name.c_str(), popCustomer.expiredDate.c_str(), popCustomer.firstRegistDate.c_str(), popElem.first);
		oldCustomer.pop();
	}
}
// 11
void Gym::getPTMemberAndNoLocker() {
	vector<Customer> customerList;
	for (const Customer& customers : this->customerList) {
		if (isValidCustomer(customers) && customers.isPTmember && customers.locker == 0) {
			customerList.push_back(customers);
		}
	}
	printCustomerListInformation(customerList);
}
// 12
void Gym::getRateAgeTwenty() {
	int totalValidMember = 0;
	int twentyMember = 0;

	for (const Customer& c : this->customerList) {
		if (isValidCustomer(c)) {
			totalValidMember++;
			int tempAge = getAge(c);
			if (tempAge >= 20 && tempAge <= 29) {
				twentyMember++;
			}
		}
	}
	printf("등록된 회원의 수는 [%d]명이고, 20대 회원의 수는 [%d]명 입니다. \n\n", totalValidMember, twentyMember);
	printf("20대의 비율은 다음과 같습니다. [%lf]%% \n", ((double)twentyMember / totalValidMember) * 100);
}
// 13
void Gym::getMaxLongestDoNotAttendanceCustomer() {
	priority_queue<pair<long long, int>> doNotAttendance;
	long long now = totalday(this->d->tm_year + 1900, this->d->tm_mon + 1, this->d->tm_mday);

	for (const Customer& c : this->customerList) {
		if (isValidCustomer(c)) {
			long long diffDay = now - totalday(c.lastExerciseDate);
			if (diffDay > 0) { // 마지막 운동날짜가 오늘 날짜보다 크면 논리적 오류가 있는 데이터 이므로 처리하지 않는다.
				doNotAttendance.push(make_pair(diffDay, c.customerID));
			}
		}
	}
	printf("등록은 했지만 최근에 운동을 하지 않은 사람 10명을 추출합니다.\n\n");
	for (int i = 0; i < 10; i++) {
		const Customer& popElem = getCustomerInformationByID(doNotAttendance.top().second);
		printf("%2d번째 =====> 회원번호[%3d] : 회원이름[%6s] : 등록권 만료일자[%s] : 최근 운동날짜[%s] : 결석일수[%4lld]\n\n", i + 1, popElem.customerID, popElem.name.c_str(), popElem.expiredDate.c_str(), popElem.lastExerciseDate.c_str(), doNotAttendance.top().first);
		doNotAttendance.pop();
	}
}
// 14
void Gym::getEarlyRegistCancleCustomer() {
	priority_queue<CancleCustomer> earlyCancleCustomer;
	long long now = totalday(this->d->tm_year + 1900, this->d->tm_mon + 1, this->d->tm_mday);

	for (const Customer& c : this->customerList) {
		long long diffDay = totalday(c.expiredDate) - now;

		if (isValidCustomer(c) && (diffDay <= 30)) { // 등록 중인 회원들 중에 30일 이내의 사람에서
			CancleCustomer temp;
			temp.id = c.customerID;

			long long lastExerciseDiffDay = now - totalday(c.lastExerciseDate); // 마지막 운동하러 온 날짜와의 차이
			temp.diffDay = lastExerciseDiffDay;
			// 마지막 운동날짜와의 차이를 보는 부분
			if (lastExerciseDiffDay >= 70)
				temp.score1 = 7;
			else if (lastExerciseDiffDay >= 60) 
				temp.score1 = 6;
			else if (lastExerciseDiffDay >= 50) 
				temp.score1 = 5;
			else if (lastExerciseDiffDay >= 40) 
				temp.score1 = 4;
			else if (lastExerciseDiffDay >= 30) 
				temp.score1 = 3;
			else if (lastExerciseDiffDay >= 20) 
				temp.score1 = 2;
			else if (lastExerciseDiffDay >= 10) 
				temp.score1 = 1;
			else
				temp.score1 = 0;
			// 출석률을 보는 부분
			long long firstRegistDateDiffDay = now - totalday(c.firstRegistDate);
			if (firstRegistDateDiffDay > 0) { // 최초로 등록한 날짜가 더 크면 논리적 오류가 있는 데이터이므로 무시
				double rate = (double)c.countExercise / firstRegistDateDiffDay;
				if (rate < 1) {
					temp.rate = rate;
					if (rate <= 0.1)// 출석률이 10% 이하인 사람 
						temp.score2 = 3;
					else if (rate <= 0.2)// 출석률이 20% 이하인 사람
						temp.score2 = 2;
					else if (rate <= 0.35) // 출석률이 35% 이하인 사람
						temp.score2 = 1;
					else
						temp.score2 = 0;
				}
			}
			earlyCancleCustomer.push(temp);
		}
	}

	printf("가장 일찍 등록을 취소할 것 같은 인원 10명을 추출합니다.\n\n");
	for (int i = 0; i < 10; i++) {
		const CancleCustomer popElem = earlyCancleCustomer.top();
		const Customer& popElemCustomer = getCustomerInformationByID(popElem.id);
		printf("%2d번째 =====> 회원번호[%3d] : 회원이름[%6s] : 등록권 만료일자[%s] : 최근 운동날짜[%s] : 최근 운동날짜 - 오늘날짜 [%lld일][%d점] : 출석률 [%5.2lf%%][%d점] :캔슬 점수[%d]\n\n", i + 1, popElemCustomer.customerID, popElemCustomer.name.c_str(), popElemCustomer.expiredDate.c_str(), popElemCustomer.lastExerciseDate.c_str(), popElem.diffDay, popElem.score1, popElem.rate * 100, popElem.score2, popElem.score1 + popElem.score2);
		earlyCancleCustomer.pop();
	}
}
//19
void Gym::getMaxMinAgeLevel() {
	map<int, int> ageLevel;
	for (const Customer& c : this->customerList) {
		if (c.isPTmember && isValidCustomer(c)) {
			ageLevel[getAge(c) / 10]++;
		}
	}
	pair<int, int> maxPair = *ageLevel.begin();
	pair<int, int> minPair = *ageLevel.begin();

	for (pair<int, int> elem : ageLevel) {
		if (elem.second > maxPair.second)
			maxPair = elem;
		if (elem.second < minPair.second) 
			minPair = elem;
	}
	if (maxPair.first == 0) 
		cout << "가장 PT를 많이 이용하는 연령대는 [10대 이하] 이며, 총 [" << maxPair.second << "]명 있습니다." << endl << endl;
	else
		cout << "가장 PT를 많이 이용하는 연령대는 [" << maxPair.first << "0]대 이며, 총 [" << maxPair.second << "]명 있습니다." << endl << endl;
	if(minPair.first == 0)
		cout << "가장 PT를 적게 이용하는 연령대는 [10대 이하] 이며, 총 [" << maxPair.second << "]명 있습니다." << endl << endl;
	else
		cout << "가장 PT를 적게 이용하는 연령대는 [" << minPair.first << "0]대 이며, 총 [" << minPair.second << "]명 있습니다." << endl;
}


int compareAge(const Customer& left, const Customer& right) {
	if (getAge(left) < getAge(right))
		return 1;
	else if (getAge(left) > getAge(right))
		return -1;
	else
		return 0;
}
int getAge(const Customer& customer) {
	vector<string> YYMMDD = split(customer.birthday.c_str(), '.');
	int yy = stoi(YYMMDD[0]);
	int mm = stoi(YYMMDD[1]);
	int dd = stoi(YYMMDD[2]);

	int age;
	age = (Gym::d->tm_year - yy) % 100;
	if (mm - (Gym::d->tm_mon + 1) > 0)
		age = age - 1;
	else if (mm - (Gym::d->tm_mon + 1) == 0) {
		if (dd - (Gym::d->tm_mday) > 0)
			age = age - 1;
	}

	return age;
}
bool isValidCustomer(const Customer& customer) {
	vector<string> YYMMDD = split(customer.expiredDate.c_str(), ' ');
	YYMMDD[0] = YYMMDD[0].substr(0, YYMMDD[0].size() - 2);
	YYMMDD[1] = YYMMDD[1].substr(0, YYMMDD[1].size() - 2);
	YYMMDD[2] = YYMMDD[2].substr(0, YYMMDD[2].size() - 2);

	int yy = stoi(YYMMDD[0]);
	int mm = stoi(YYMMDD[1]);
	int dd = stoi(YYMMDD[2]);

	if (yy - (Gym::d->tm_year + 1900) < 0) {
		return false;
	}
	else if (yy - (Gym::d->tm_year + 1900) == 0) {
		if ((mm - (Gym::d->tm_mon + 1) < 0)) {
			return false;
		}
		else if ((mm - (Gym::d->tm_mon + 1) == 0)) {
			if (dd - (Gym::d->tm_mday) < 0)
				return false;
		}
	}
	return true;
}

long long totalday(int yy, int mm, int dd) {
	int months[] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
	int i;
	long long total;

	total = ((long long)yy - 1L) * 365L;
	total += ((long long)yy - 1L) / 4L - ((long long)yy - 1L) / 100L + ((long long)yy - 1) / 400L;

	if (!(yy % 4) && yy % 100 || !(yy % 400)) // 윤년이면
		months[1]++;

	for (i = 0; i < mm - 1; i++)
		total += months[i];

	total += dd;

	return total;
}

long long totalday(string strdate) {
	vector<string> YYMMDD = split(strdate.c_str(), ' ');
	YYMMDD[0] = YYMMDD[0].substr(0, YYMMDD[0].size() - 2);
	YYMMDD[1] = YYMMDD[1].substr(0, YYMMDD[1].size() - 2);
	YYMMDD[2] = YYMMDD[2].substr(0, YYMMDD[2].size() - 2);

	int yy = stoi(YYMMDD[0]);
	int mm = stoi(YYMMDD[1]);
	int dd = stoi(YYMMDD[2]);

	return totalday(yy, mm, dd);
}