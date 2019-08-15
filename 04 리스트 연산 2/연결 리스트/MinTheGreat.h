#pragma once
#ifndef _MinTheGreat
#define _MinTheGreat
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string.h>

using namespace std;

typedef struct _lib {
	char name[7];
	char sex;
	char loc[7];
	char major[13];
	float score;
	int height;
	int weight;
}lib;

typedef struct _node node;

struct _node {
	lib* library;
	_node*lnext;
	_node*rnext;
};

class link {
private:
	int cnt;
	node* nodes;

public:
	//클래스 내 구조체 생성
	link * create();

	//파일 유무 확인
	bool verify(const std::string& filename);

	//파일 읽어들여서 클래스 내 구조체에 쓰기
	node *load(istream& fp, link*list, int n);

	//라인 수 세서 반복 시 횟수 가져오기
	int line(istream& fp);

	//전체 출력
	void print(link*list);
	
	//데이터 추가
	int insert(link*list, node* data);
	
	//데이터 삭제
	int remove(link*list, char* rmv);

	//데이터 탐색
	node* search(char*sch, link*list);

	//새 데이터 저장
	int save(ofstream&fp, link*data);
};

#endif
#pragma once