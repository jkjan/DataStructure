typedef struct _edge {
	int u;
	int w;
} edge;

class stack {
private:
	edge *edges;
	int size;
	int cnt;
public:
	void init();
	void push(int u, int w);
	edge* pop();
	edge* top();
	int is_empty();
	int is_full();
}; 
#pragma once
