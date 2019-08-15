#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<string>
#include "Customer.h"
#include "Gym.h"
using namespace std;

void showMenuPrint() {
	printf("########################################################################\n");
	printf("0. 회원 정보 모두 출력 \n\n");
	printf("1. 가장 회원을 많이 확보한 트레이너는? \n\n");
	printf("3. 가장 출석률이 좋은회원은? \n\n");
	printf("4. 가장 많은/적은 회원이 사는 동은? \n\n");
	printf("5. 가장 등록이 많은/적은 달은? \n\n");
	printf("6. 가장 오래된 회원은? \n\n");
	printf("11. PT를 받는 회원 중 라커를 이용하지 않는 회원은? \n\n");
	printf("12. 회원 중 나이가 20대인 회원의 비율은? \n\n");
	printf("13. 가장 오랫동안 오지 않은 회원은? \n\n");
	printf("14. 가장 빨리 등록을 취소할 가능성이 높은 회원은? \n\n");
	printf("19. PT를 가장 많이/적게 이용하는 연령대는? \n\n");
	printf("99. 종료하기 \n\n");
	printf("메뉴 아이템을 선택하세요 >> ");
}
int main() {
	FILE* fp = fopen("JOJO.csv", "r+t");
	Gym myGym;
	char line[1000];
	int n = 0;
	fgets(line, sizeof(line), fp);
	while (!feof(fp)) {
		fgets(line, sizeof(line), fp);
		myGym.addCustomer(line);
	}
	int menuSelect;
	showMenuPrint();
	while (true) {
		cin >> menuSelect;
		system("cls");
		printf("..........................................................\n\n");
		switch (menuSelect) {
		case 1:
			myGym.getMaxCustomerOfTrainer();
			break;
		case 3:
			myGym.getMaxAttendanceCustomer();
			break;
		case 4:
			myGym.getMaxMinHomeCustomer();
			break;
		case 5:
			myGym.getMaxRegistMonth();
			break;
		case 6:
			myGym.getMaxOldCustomer();
			break;
		case 11:
			myGym.getPTMemberAndNoLocker();
			break;
		case 12:
			myGym.getRateAgeTwenty();
			break;
		case 13:
			myGym.getMaxLongestDoNotAttendanceCustomer();
			break;
		case 14:
			myGym.getEarlyRegistCancleCustomer();
			break;
		case 19:
			myGym.getMaxMinAgeLevel();
			break;
		case 0:
			myGym.printAllCustomerInformation();
			break;
		case 99:
			fclose(fp);
			return 0;
		default:
			printf("잘못 입력하셨습니다. 다시 입력하세요.\n");
		}
		printf("..........................................................\n\n");
		showMenuPrint();
	}
	return 0;
}