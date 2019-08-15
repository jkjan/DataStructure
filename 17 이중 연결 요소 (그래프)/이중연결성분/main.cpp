#include "treengraph.h"
#include "stack.h"

int num;
int * visited;
graph*glist;
int *dfns;
stack* ver;

int main() {
	ver = new stack;
	ver->init();
	FILE * fp = fopen("graph02.txt", "rt");

	if (fp == NULL) {
		printf("File not found\n");
		return 0;
	}

	int vs;
	int i;
	int a, b;

	fscanf(fp, "%d %d", &num, &vs);
	glist = (graph*)malloc(sizeof(graph)*(num+1));

	for (i = 1; i <= num; i++) {
		(glist + i)->ver = i;
		(glist + i)->adjs = (node*)malloc(sizeof(node));
		(glist + i)->adjs->init();
		(glist + i)->adjcnt = 0;
	}

	for (i = 0; i < vs; i++) {
		fscanf(fp, " %d %d", &a, &b);
		if ((glist + a)->adjs->search(b) == 0) {
			(glist + a)->adjs->addtree(b);
			(glist + a)->adjcnt++;
		}

		else
			puts("duplicate edge");

		if ((glist + b)->adjs->search(a) == 0) {
			(glist + b)->adjs->addtree(a);
			(glist + b)->adjcnt++;
		}

		else
			puts("duplicate edge");
	}

	fclose(fp);

	puts("==============================");
	for (i = 1; i <= num; i++) {
		printf("vertex %d: ", i);
		(glist + i)->adjs->treeprint();
		printf("\n");
	}
	puts("==============================");
	puts("dfs =================\n");

	vinit();
	dfsg(1, 0);

	for (i = 1; i <= num; i++) {
		(glist + i)->adjs->thanos();
	}
	
	free(glist);
	free(visited);
	free(ver);

	return 0;
}