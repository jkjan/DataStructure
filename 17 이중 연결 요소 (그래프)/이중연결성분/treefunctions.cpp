#include "treengraph.h"
#include "stack.h"

extern int* visited;
extern int vertex;
extern int *dfns;
int dfncnt;
extern stack* ver;
extern int *lows;

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

void node::dfs(int u, int v) {
	if (this->adjnode != -1) {

		this->lc->dfs(u, v);

		//if (visited[this->adjnode] == 0) {
		if (dfns[this->adjnode] < 0) {
			//visited[this->adjnode] = 1;
			ver->push(u, this->adjnode);
			//printf("[%d, %d]\n",u, this->adjnode);

			dfsg(this->adjnode, u);
			lows[u] = lows[u] < lows[this->adjnode] ? lows[u] : lows[this->adjnode];
			//printf(" %d %d\n", lows[this->adjnode], dfns[u]);
			if (lows[this->adjnode] >= dfns[u]) {
				//printf("%d : articulation point %d %d\n", u, lows[this->adjnode], dfns[u]);
				printf("new bicon : \n");
				edge*Edge;
				do {
					Edge = ver->pop();
					printf("<%d %d>\n", Edge->u, Edge->w);

				} while (Edge->u != u || Edge->w != this->adjnode);
				printf("\n");
			}
		}
		else if (this->adjnode != v)
			lows[u] = lows[u] < lows[this->adjnode] ? lows[u] : lows[this->adjnode];
		this->rc->dfs(u, v);
	}
}