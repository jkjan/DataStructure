//일반 정사각행렬
#include "sparse.h"

extern int n;
extern int **matA;
extern int **matB;
extern int **matC;
extern int **matAT;

void print(int **mat) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			printf("%2d ", mat[i][j]);
		}
		printf("\n");
	}
}

//1. load
void load(FILE *fpA, FILE* fpB) {  //fp에 저장된 file에서 n x n 크기의 행렬 저장
	int Acnt, Bcnt;
	fscanf(fpA, "%d", &Acnt);
	fscanf(fpB, "%d", &Bcnt);
	if (Acnt != Bcnt) {
		printf("error");
		exit(1);
	}

	n = Acnt;

	matA = (int**)malloc(sizeof(int*)*n);
	for (int i = 0; i < n; i++)
		matA[i] = (int*)malloc(sizeof(int)*n);

	matB = (int**)malloc(sizeof(int*)*n);
	for (int i = 0; i < n; i++)
		matB[i] = (int*)malloc(sizeof(int)*n);

	for (int i = 0; i < Acnt; i++) {
		for (int j = 0; j < Acnt; j++) {
			fscanf(fpA, "%d", &matA[i][j]);
		}
	}

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			fscanf(fpB, "%d", &matB[i][j]);
		}
	}
}

//2. transpose
int **transpose(int n, int **mat) {
	int **transposed = new int*[n];
	for (int i = 0; i < n; i++)
		transposed[i] = new int[n];

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			transposed[i][j] = mat[j][i];
		}
	}
	return transposed;
}

//3. add
int **add(int n, int **matA, int **matB) {
	int **added = new int*[n];
	for (int i = 0; i < n; i++)
		added[i] = new int[n];

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			added[i][j] = matA[i][j] + matB[i][j];
		}
	}
	return added;
}

//4. multiply
int **mult(int n, int **matA, int **matB) {
	int elem = 0;

	int **multiplied = new int*[n];
	for (int i = 0; i < n; i++)
		multiplied[i] = new int[n];

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			for (int k = 0; k < n; k++) {
				elem += (matA[i][k] * matB[k][j]);
			}
			multiplied[i][j] = elem;
			elem = 0;
		}
	}

	return multiplied;
}