#ifndef isonthegrass
#define isonthegrass

#include <iostream>
#include <cstdlib>

class node {
public:
	int adjnode;
	int dfn, low;
	node* lc;
	node* rc;
public:
	void init();
	void treeprint();
	void addtree(int adj);
	int search(int v);
	void thanos();
	void dfs(int u, int v);
	void bfs();
};

typedef struct _graph {
	int ver;
	node* adjs;
	int adjcnt;
}graph;

void vinit();
void dfsg(int u, int n);
void bfsg();

#endif