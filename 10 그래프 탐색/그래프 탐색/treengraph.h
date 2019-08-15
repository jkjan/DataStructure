#ifndef isonthegrass
#define isonthegrass

#include <iostream>
#include <cstdlib>

class node {
public:
	int adjnode;
	node* lc;
	node* rc;
public:
	void init();
	void treeprint();
	void addtree(int adj);
	int search(int v);
	void thanos();
	void dfs();
	void bfs();
};

void dfsg(int n);

typedef struct _graph {
	int ver;
	node* adjs;
	int adjcnt;
}graph;

void vinit();
void dfsg(int n);
void bfsg();

#endif