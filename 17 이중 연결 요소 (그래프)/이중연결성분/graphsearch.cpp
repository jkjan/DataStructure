#include "treengraph.h"

extern int num;
extern int* visited;
extern graph* glist;  //트리로 구현하는 바람에 for로 순차적으로 참조를 못해서..
int vertex;
extern int *dfns;
extern int dfncnt;
int * lows;

void vinit() {
	visited = (int*)malloc(sizeof(int)*(num + 1));
	for (int i = 0; i <= num; i++)
		visited[i] = 0;

	dfns = (int*)malloc(sizeof(int)*(num + 1));
	for (int i = 0; i <= num; i++)
		dfns[i] = -1;
	lows = (int*)malloc(sizeof(int)*(num + 1));
	for (int i = 0; i <= num; i++)
		lows[i] = 0;

}

void dfsg(int u, int v) {
	//visited[u] = 1;
	//vertex = n;

	dfns[u] = lows[u] =  dfncnt++;

	(glist + u)->adjs->dfs(u, v);
	//lows[u] = lows[u] < lows[n] ? lows[u] : lows[n];
}