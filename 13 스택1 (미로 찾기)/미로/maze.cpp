#include "stack.h"
#include <stdio.h>
#include <stdlib.h>

block** Block;
skein* maze;
int ER;
int EC;
int XR;
int XC;
int col;
int row;

extern void load(FILE*fp);
extern void solveMaze();
extern void printMaze();

int main() {
	FILE * fp = fopen("maze2.txt", "rt");
	load(fp);
	printMaze();
	solveMaze();
	printMaze();

	free(maze);
	
	free(Block);

	fclose(fp);
}