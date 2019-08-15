#include "treengraph.h"
#include "queue.h"

extern int* visited;
extern jo* que;
extern int vertex;

void node::treeprint() {
	if (this->adjnode != -1) {
		this->lc->treeprint();
		printf("%d,  ", this->adjnode);
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

void node::dfs() {
	if (this->adjnode != -1) {
		this->lc->dfs();

		if (visited[this->adjnode] == 0) {
			visited[this->adjnode] = 1;
			printf("[%d, %d]\n",vertex, this->adjnode);

			dfsg(this->adjnode);
		}
		this->rc->dfs();
	}
}

void node::bfs() {  //for나 while같은 반복문으로 인접노드를 순차적으로 참조할 수가 없어서..
	if (this->adjnode != -1) {
		this->lc->bfs();

		if (visited[this->adjnode] == 0) {
			visited[this->adjnode] = 1;
			printf("[%d, %d]\n",vertex, this->adjnode);
			que->enque(this->adjnode);
		}

		this->rc->bfs();
	}
}