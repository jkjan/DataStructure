#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

extern int convert_and_calculate(char* expr);
extern void calculate();
extern int p;

int main() {
	char expr[256] = "31.6 + (19.3 - 2.1) *(1.4^0.6 +8.5)";
	convert_and_calculate(expr);
	calculate();
}