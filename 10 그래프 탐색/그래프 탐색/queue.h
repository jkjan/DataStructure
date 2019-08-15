#ifndef metallica
#define metallica

typedef struct _node qnode;

struct _node {
	int who;
	_node*next;
};

class jo {
private:
	qnode*people;
	qnode*cur;
	int cnt;

public:
	void init();
	int isempty();
	int isfull();
	int enque(int what);
	int deque();
};
#endif
#pragma once