#include "treengraph.h"
#include "queue.h"

extern int num;
extern int* visited;
extern graph* glist;  //트리로 구현하는 바람에 for로 순차적으로 참조를 못해서..
extern jo* que;
int vertex;

void vinit() {
	visited = (int*)malloc(sizeof(int)*(num + 1));
	for (int i = 0; i <= num; i++)
		visited[i] = 0;
}

void dfsg(int n) {
	visited[n] = 1;
	vertex = n;
	(glist + n)->adjs->dfs();
}

void bfsg() {
	int v;

	visited[1] = 1;
	que->enque(1);

	while (!que->isempty()) {
		v = que->deque();
		vertex = v;
		(glist + v)->adjs->bfs();
	}
}