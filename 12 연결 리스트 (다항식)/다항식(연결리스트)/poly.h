#ifndef LINKED
#define LINKED
#include <stdio.h>

class hang {
public:
	int coef; //계수
	int exp;  //지수
	hang* next;
	void setHang(int c, int e, hang* next);
};

class poly {
private :
	hang* head; //항들의 연결리스트
	hang* tail;
public :
	//void load(FILE*fp);
	void zero(); //0짜리 생성
	int isZero(); //0인지 확인 (공간이 있나 없나?)
	int coef(int e); //지수가 e인 항의 계수 리턴
	int leadExp(); //최고차항의 지수 리턴
	void append(int c, int e); //cx^e를 마지막에 추가
	void insert(int c, int e); //cx^e를 적절한 위치에 삽입

	void add(poly *A, poly *B);
	void multi(poly* A, poly *B);
	void pprint();
};

void load(FILE*fp);

#endif