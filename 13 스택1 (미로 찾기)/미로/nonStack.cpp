#include "stack.h"
#include <stdio.h>
#include <stdlib.h>

#define ABLE 0
#define WALL 1
#define ENTRA 2
#define EXIT 3
#define CHECKED 4
#define CROSS 5

extern block** Block;
extern skein* maze;
extern int ER;
extern int EC;
extern int XR;
extern int XC;
extern int col;
extern int row;

int pos::posCheck(int x, int y) {
	return ((this->x == x) && (this->y == y)) ? 1 : 0;
}

void load(FILE* fp) {
	char c;

	int curR = 0;
	int curC = 0;;

	fscanf(fp, "%d", &row);
	fscanf(fp, "%d", &col);

	Block = (block**)malloc(sizeof(block*)*row);

	for (int i = 0; i < col; i++)
		Block[i] = (block*)malloc(sizeof(block)*col);

	maze = (skein*)malloc(sizeof(skein));

	maze->init(row*col);

	while ((c = fgetc(fp)) != EOF && (curR < row)) {
		if (c == ' ' || c == '\n')
			continue;

		if (c == '1' || c == '0' || c == 'E' || c == 'X') {
			if (c == '1' || c == '0') {
				Block[curR][curC].wall = (c == '1' ? 1 : 0);
				if (c == '0')
					Block[curR][curC].isWay = 0;
			}

			if (c == 'X') {
				Block[curR][curC].wall = EXIT;
				XR = curR;
				XC = curC;
			}

			else if (c == 'E') {
				Block[curR][curC].wall = ENTRA;
				ER = curR;
				EC = curC;
			}
		}

		else {
			printf("wrong maze\n");
			exit(0);
		}

		if (curC < col-1) {
			curC++;
		}

		else {
			curC = 0;
			curR++;
		}
	}

	if (c != EOF || curC != 0) {
		printf("wrong maze\n");
		exit(0);
	}
}

int checkCross(int curR, int curC) {
	//위
	int otherway = 0;

	if (curR - 1 >= 0) {
		if (Block[curR - 1][curC].wall == ABLE) {
			//Block[curR][curC] = CROSS;
			otherway++;
		}
	}

	//오른쪽
	if (curC + 1 < col) {
		if (Block[curR][curC + 1].wall == ABLE) {
			//Block[curR][curC] = CROSS;
			otherway++;
		}
	}

	//아래
	if (curR + 1 < row) {
		if (Block[curR + 1][curC].wall == ABLE) {
			//Block[curR][curC] = CROSS;
			otherway++;
		}
	}

	//왼쪽
	if (curC - 1 >= 0) {
		if (Block[curR][curC - 1].wall == ABLE) {
			//Block[curR][curC] == CROSS;
			otherway++;
		}
	}

	if (otherway > 1)
		return 1;
	else
		return 0;
}

void printMaze() {
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			switch (Block[i][j].wall) {
			case 0 :
				printf("0 ");
				break;
			case 1 :
				printf("1 ");
				break;
			case ENTRA :
				printf("E ");
				break;
			case EXIT :
				printf("X ");
				break;
			case CHECKED :
				if (Block[i][j].isWay == 0)
					printf("0 ");
				else
					printf("P ");
				break;
			default :
				break;
			}
		}
		printf("\n");
	}
	printf("\n");
}

void solveMaze() {
	int curC = EC;
	int curR = ER;

	int xc = XC;
	int xr = XR;

	pos* start = (pos*)malloc(sizeof(pos));

	while (1) {
		//위
		if (curR - 1 >= 0) {
			if (Block[curR - 1][curC].wall == ABLE || Block[curR - 1][curC].wall == EXIT) {
				Block[curR][curC].wall = (CHECKED);
				if (checkCross(curR, curC)) {
					Block[curR][curC].wall = (CROSS);
				}

				Block[curR][curC].isWay = 1;
				maze->push(curR--, curC);
				continue;
			}
		}

		//오른쪽
		if (curC + 1 < col) {
			if (Block[curR][curC + 1].wall == ABLE || Block[curR][curC + 1].wall == EXIT) {
				Block[curR][curC].wall = (CHECKED);
				if (checkCross(curR, curC)) {
					Block[curR][curC].wall = (CROSS);
				}
				Block[curR][curC].isWay = 1;
				maze->push(curR, curC++);
				continue;
			}
		}

		//아래
		if (curR + 1 < row) {
			if (Block[curR + 1][curC].wall == ABLE || Block[curR + 1][curC].wall == EXIT) {
				Block[curR][curC].wall = (CHECKED);
				if (checkCross(curR, curC)) {
					Block[curR][curC].wall = (CROSS);
				}
				Block[curR][curC].isWay = 1;
				maze->push(curR++, curC);
				continue;
			}
		}

		//왼쪽
		if (curC - 1 >= 0) {
			if (Block[curR][curC - 1].wall == ABLE || Block[curR][curC - 1].wall == EXIT) {
				Block[curR][curC].wall = (CHECKED);
				if (checkCross(curR, curC)) {
					Block[curR][curC].wall = (CROSS);
				}

				Block[curR][curC].isWay = 1;
				maze->push(curR, curC--);
				continue;
			}
		}

//------이동 못한 경우--------------

		//출구일 경우
		if (curR == XR && curC == XC) {
			Block[ER][EC].wall = ENTRA;
			printf("found the way out\n\n");
			return;
		}

		//막혔을 경우
		else {
			Block[curR][curC].wall = (CHECKED);
			Block[curR][curC].isWay = 0;

			while (Block[maze->top()->x][maze->top()->y].wall != CROSS) {
				start = maze->pop();
				Block[start->x][start->y].isWay = 0;
				if (start->posCheck(ER, EC)) {
					printf("no way out\n");
					exit(0);
				}
			}

			curR = maze->top()->x;
			curC = maze->top()->y;
		}
	}
	free(start);
}