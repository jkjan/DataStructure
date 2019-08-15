#include "MinTheGreat.h"

int main() {
	int i;
	int index;
	int students;
	info std; //std 클래스
	info*access = &std; //std 클래스(모체)의 주소
	lib*thelist;  //std 클래스 안에 학생 정보가 담긴 알짜

	char command[10];  //명령어
	
	ifstream in, list;
	in.open("input.txt");
	cout << "input.txt";
	std.verify("input.txt");

	int many = std.line(in);
	
	in.clear();
	in.seekg(0);

	info garbage; // insert 시 임시로 저장될 info*
	info*ga = &garbage;

	for (i = 0; i < many; i++) {
		in >> command;

		if (strcmp(command, "CREATE") == 0) {
			thelist = std.create(access, 100);    // 학생들 정보가 저장될 클래스 배열 크기 100짜리
		}

		else if (strcmp(command, "LOAD") == 0) {
			in >> command;
			list.open(command);
			cout << command;
			std.verify(command);
			students = std.line(list);
			list.clear();
			list.seekg(0);

			std.load(list, access, students);
		}

		else if (strcmp(command, "PRINT") == 0) {
			cout << command << endl;
			cout << "전체 정보를 출력합니다.\n" << endl;
			std.print(access);
		}

		else if (strcmp(command, "INSERT") == 0) {
			cout << command;
			lib*galist = std.create(ga, 1);
			if (std.insert(access, std.load(in, ga, 1)));
				students++;
		}

		else if (strcmp(command, "DELETE") == 0) {
			cout << command;
			in >> command;
			cout << ' ' << command << endl;

			if (std.remove(access, command)) {
				cout << command << " 학생을 삭제합니다.\n" << endl;
				students--;
			}

			else
				cout << "삭제할 것이 없습니다." << endl << endl;
			
		}

		else if (strcmp(command, "SEARCH") == 0) {
			cout << command;
			in >> command;
			cout << ' ' << command << endl;
			cout << command << " 학생의 정보입니다 : " << endl;
			if ((index = std.search(command, access, 1, 0, students-1)) > -1) {
				cout
					<< (thelist + index)->sex << ' '
					<< (thelist + index)->loc << ' '
					<< (thelist + index)->major << ' '
					<< (thelist + index)->score << ' '
					<< (thelist + index)->height << ' '
					<< (thelist + index)->weight << endl << endl;
			}
			
			else
				puts("학생이 존재하지 않습니다\n");
		}
	}

	in.close();
	list.close();

	ofstream newlymade;
	newlymade.open("new.txt");
	cout << "new.txt";
	if (std.verify("new.txt")) 
		std.save(newlymade, access);

	cout << "새 자료를 new.txt에 저장했습니다." << endl;

	delete[] thelist;
	newlymade.close();

	return 0;
}