#include "sparse.h"
#include <time.h>

int n;
int **matA;
int **matB;
int **matC;

int **matAT;
int **matBT;
int **matCT;

smatrix smatA;
smatrix smatB;
smatrix smatC;

smatrix smatAT;
smatrix smatBT;
smatrix smatCT;

extern void load(FILE *fpA, FILE *fpB);
extern int **transpose(int n, int **mat);
extern int **add(int n, int **matA, int **matB);
extern int **mult(int n, int **matA, int **matB);
extern void print(int**mat);

int main() {
//1. load
	FILE *fpA = fopen("matA\\matA_K.txt", "r+t");
	FILE *fpB = fopen("matB\\matB_K.txt", "r+t");
	clock_t tik, tok;

	load(fpA, fpB);
	//matA와 matB에 행렬이 저장
	fclose(fpA);
	fclose(fpB);
	
	//matA -> smatA, matB -> smatB
	smatA.convert_to_smatrix(n, matA);
	smatB.convert_to_smatrix(n, matB);
	
//2. transpose
	//2-1. ordinary transpose
	printf("transposing A : \n");
	tik = clock();
	matAT = transpose(n, matA);
	tok = clock();
	printf("Loading: %f\n\n", (float)(tok - tik) / CLOCKS_PER_SEC);

	//2-2. fast transpose
	printf("transposing sparse A : \n");
	tik = clock();
	smatAT.fastTranspose(n, smatA);
	tok = clock();
	printf("Loading: %f\n\n", (float)(tok - tik) / CLOCKS_PER_SEC);
	
//3. add
	//3-1. ordinary add
	printf("A + B = \n");
	tik = clock();
	matC = add(n, matA, matB);
	tok = clock();
	printf("Loading: %f\n\n", (float)(tok - tik) / CLOCKS_PER_SEC);

	//3-2. fast add
	tik = clock();
	smatC.fastAdd(smatA, smatB);
	tok = clock();
	printf("sparse A + B = \n");
	printf("Loading: %f\n\n", (float)(tok - tik) / CLOCKS_PER_SEC);

//4. multiply
	//4-1. ordinary multiply
	printf("A * B = \n");
	tik = clock();
	matC = mult(n, matA, matB);
	tok = clock();
	printf("Loading: %f\n\n", (float)(tok - tik) / CLOCKS_PER_SEC);

	//4-2. fast multiply
	tik = clock();
	smatC.fastMult(smatA, smatB);
	tok = clock();
	printf("sparse A * B = \n");
	printf("Loading: %f\n\n", (float)(tok - tik) / CLOCKS_PER_SEC);

	system("pause");

	free(matA);
	free(matB);
	free(matC);
	free(matAT);
	free(smatA.list);
	free(smatB.list);
	free(smatAT.list);
	free(smatA.rowTerms);
	free(smatB.rowTerms);
	free(smatAT.rowTerms);
	free(smatA.startPos);
	free(smatB.startPos);
	free(smatAT.startPos);
	free(smatC.list);
	free(smatC.rowTerms);
	free(smatC.startPos);

	return 0;
}