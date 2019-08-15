#include "lunatic.h"

int main() {
	FILE * fp = fopen("input.txt", "rt");

	if (fp == NULL) {
		printf("File not found\n");
		return 0;
	}

	int num, vs;
	int i;
	int a, b;
	
	fscanf(fp, "%d %d", &num, &vs);
	graph* glist = (graph*)malloc(sizeof(graph)*(num));
	
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

			(glist + b)->adjs->addtree(a);
			(glist + b)->adjcnt++;
		}
		else
			puts("duplicate edge");
	}

	int max, min;
	max = min = (glist + 1)->adjcnt;

	int* maxes = (int*)malloc(sizeof(int)*num);
	int* mins = (int*)malloc(sizeof(int) * num);
	int mp, np;
	mp = np = 0;

	for (i = 2; i <=  num; i++) {
		max = (glist + i)->adjcnt > max ? (glist + i)->adjcnt : max;
		min = (glist + i)->adjcnt < min ? (glist + i)->adjcnt : min;
	}
	puts("==============================");
	for (i = 1; i <= num; i++) {
		printf("vertex %d: ", i);
		(glist + i)->adjs->treeprint();
		printf("\n");
		if ((glist + i)->adjcnt == max)
			*(maxes+(mp++)) = (glist + i)->ver;
		if ((glist + i)->adjcnt == min)
			*(mins+(np++)) = (glist + i)->ver;
	}
	puts("==============================");
	printf("Max adj vertex: ");
	for (i = 0; i < mp; i++) {
		printf("%2d, ", *(maxes+i));
	}
	printf("\n");

	printf("Min adj vertex: ");
	for (i = 0; i < np; i++) {
		printf("%2d, ", *(mins + i));
	}
	
	for (i = 1; i <= num; i++) {
		(glist + i)->adjs->thanos();
	}
	
	free(maxes);
	free(mins);
	//free(glist); Èü ¼Õ»ó ¿À·ù

	return 0;
}