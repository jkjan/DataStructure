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

class info {
private:
	int num;
	int cnt;
	lib * library;

public:
	//클래스 내 구조체 생성
	lib * create(info* list, int n);        

	//파일 유무 확인
	bool verify(const std::string& filename);

	//파일 읽어들여서 클래스 내 구조체에 쓰기
	lib *load(istream& fp, info*list, int n);

	//라인 수 세서 반복 시 횟수 가져오기
	int line(istream& fp);

	//전체 출력
	void print(info*list);

	//데이터 추가
	int insert(info*list, lib* data);

	//데이터 삭제
	int remove(info*data, char* rmv);

	//데이터 탐색
	int search(char*sch, info* data, int n, int first, int last);

	//새 데이터 저장
	int save(ofstream&fp, info*data);
};

#endif
#pragma once