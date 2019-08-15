#ifndef HEAP
#define HEAP

struct _heap {
	char key[64];
	int value;
};

typedef struct _heap heap;


void swap(int a, int b);
void insert(char* key, int value);
void deque();
#endif
#pragma once
