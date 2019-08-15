#include "lunatic.h"

void node::treeprint() {
	if (this->adjnode != -1) {
		this->lc->treeprint();
		printf("%2d, ", this->adjnode);
		this->rc->treeprint();
	}
}

void node::addtree(int adj) {
	if (this->adjnode == -1) {
		this->adjnode = adj;
		this->lc->init();
		this->rc->init();
	}

	else if (this->adjnode > adj) {
		this->lc->addtree(adj);
	}
	else {
		this->rc->addtree(adj);
	}
}

void node::init() {
	this->adjnode = -1;
	this->lc = (node*)malloc(sizeof(node));
	this->rc = (node*)malloc(sizeof(node));
}

int node::search(int v) {
	if (this->adjnode == -1)
		return 0;
	if (this->adjnode == v)
		return 1;
	else if (this->adjnode > v)
		this->lc->search(v);
	else
		this->rc->search(v);
 }

void node::thanos() {
	if (this->adjnode != -1) {
		this->lc->thanos();
		this->rc->thanos();
		free(this);
	}
}