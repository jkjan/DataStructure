//메인함수
#include "poly.h"
#include <stdlib.h>

poly* A;
poly* B;


int main() {
	FILE*fp = fopen("poly.txt", "rt");

	A = (poly*)malloc(sizeof(poly));
	B = (poly*)malloc(sizeof(poly));

	poly *C = (poly*)malloc(sizeof(poly));

	load(fp);
	printf("polynomial A = ");
	A->pprint();

	printf("polynomial B = ");
	B->pprint();
	
	printf("A + B = ");
	C->add(A, B);
	C->pprint();

	printf("A * B = ");
	C->multi(A, B);
	C->pprint();
}