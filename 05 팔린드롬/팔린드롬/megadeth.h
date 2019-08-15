#ifndef _mustaine
#define _mustaine

#include <iostream>
#include <string.h>
#include <cstdlib>
#include <fstream>
#include <cctype>

using namespace std;

typedef struct _node node;

struct _node {
	char space;
	_node*next;
};

class stack {
private:
	node*head;
	int cnt;
	int size;
public:
	stack * init();
	int is_full(stack* seg);
	int is_empty(stack* seg);
	void push(stack* seg, char ch);
	char pop(stack* seg);
	char top(stack* seg);
};

#endif

#pragma once
