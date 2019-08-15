#ifndef metallica
#define metallica
#include <iostream>
#include <cstdlib>
#include <fstream>

using namespace std;


typedef struct _node node;

struct _node {
	int who;
	_node*next;
};

class jo {
private:
	node*people;
	node*cur;
	int cnt;

public:
	jo*init();
	int isempty(jo*que);
	int isfull(jo* que);
	int enque(jo*que, int what);
	int deque(jo*que);
	bool verify(const std::string& filename);
};

#endif


#pragma once
