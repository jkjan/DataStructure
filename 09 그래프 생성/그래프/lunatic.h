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
};

typedef struct _graph {
	int ver;
	node* adjs;
	int adjcnt;
}graph;

#endif

#pragma once
