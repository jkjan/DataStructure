#include <stdio.h>
#include <stdlib.h>

class element {
public:
	int row;
	int col;
	int val;
};

class smatrix {
public:
	int n;
	int cnt;
	element *list;
	int *startPos;
	int *rowTerms;

public:
	void convert_to_smatrix(int n, int **mat);
	void fastTranspose(int n, smatrix mat);
	void fastAdd(smatrix matA, smatrix matB);
	void fastMult(smatrix matB, smatrix smatB);

	void makeRowTerms();
	void makeStartPos();

	void print();
	void setList(int i, int row, int col, int val);
};
