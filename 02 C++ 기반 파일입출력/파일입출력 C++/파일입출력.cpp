#include <iostream>
#include <fstream>
#include <cstdlib>

using namespace std;

int i = 0;

//학생 정보를 저장할 클래스 선언
class info {
private:
	char name[7];
	char sex;
	char loc[7];
	char major[13];
	float score;
	int height;
	int weight;

public:
	int line(istream& fp);
	info* alloc(int lines);
	int scan(istream& fp, info*list, int lines);
	void print(info*list, int lines);
};

//파일의 줄 수 세기
int info::line(istream& fp) {
	int lines = 0;
	char enter[255];

	//int lines = 0;

	while (!fp.eof()) {
		fp.getline(enter, 255);
		lines++;
	}

	return lines;
}

//(클래스 멤버 함수로) 클래스 배열 동적 메모리 할당하기
info* info::alloc(int lines) {
	info * infoarray = new info[lines];

	return infoarray;
}

//(클래스 멤버 함수로) 입력받기
int info::scan(istream& fp, info*list, int lines) {
	try {
		while (i < lines) {
			fp >> (list + i)->name >> (list + i)->sex >> (list + i)->loc >>
				(list + i)->major >> (list + i)->score >> (list + i)->height
				>> (list + i)->weight;
			if (fp.fail())
				throw 1;
			i++;
			}
		}

	/*자료형 오류 예외 처리
	이름에 숫자가 들어가는 오류도 추가하고 싶었으나 이를 하려면 문자 하나하나를 검색해서
	(list + i)->name[i] - atoi((list+i)->name[i]) 가 48이 되는지를 판단해야 하고, 이때문에 
	알고리즘이 O(n^2)가 되기 때문에 생략하였습니다.
	오류가 있는 줄을 정확히 찾지 못하는 이유는
	만약 학생의 무게에 60dd 라는 값이 들어갔을 때 다음 번의 이름이 dd라고 인식이 되어서입니다.
	*/
	catch (int expn) {
		if (expn) {
			cout << (list + i-1)->name << " 학생, 혹은 다음 학생의 수치 정보에 오류가 있습니다. "
				<< "재확인 하십시오." << endl;
			return 1;
		}
	}
	
	return 0;
	}

//(클래스 멤버 함수로) 출력하기
void info::print(info*list, int lines) {
	cout << fixed;
	cout.precision(2);
	for (i = 0; i < lines; i++) {
		cout << (list + i)->name << ' ' << (list + i)->sex << ' ' << (list + i)->loc << ' ' <<
			(list + i)->major << ' ' << (list + i)->score << ' ' << (list + i)->height << ' ' << (list + i)->weight << endl;
	}
}

int main() {
	ifstream it;
	it.open("list.txt");
	int error, line;

	//파일 열기 성공 여부 확인 메시지
	if (it.is_open())
		cout << "The file has been successfully opened" << endl;
	else {
		cout << "Failed to open the file" << endl;
		return 0;
	}

	//클래스 삽입
	info in;

	//파일의 줄 수 세기
	line = in.line(it);

	//(클래스 멤버 함수로) 클래스 배열 동적 메모리 할당하기
	info * inarrays = in.alloc(line);

	it.clear();
	it.seekg(0);

	//(클래스 멤버 함수로) 입력받기
	error = in.scan(it, inarrays, line);

	//(클래스 멤버 함수로) 출력하기
	if (!error)
		in.print(inarrays, line);

	delete[] inarrays;
	it.close();

	return 0;
}