#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "stack.h"
#include <math.h>

double result[100];
int p;

void operatorPrint(int oper) {
	switch (oper) {
	case PLUS:
		printf("+ ");
		return ;

	case MINUS:
		printf("- ");
		return ;

	case MULTI:
		printf("* ");
		return ;

	case DIVID:
		printf("/ ");
		return ;

	default:
		return;
	}
}

int convert_and_calculate(char* expr) {
	stack* op = (stack*)malloc(sizeof(stack));
	op->init();

	double num = 0;
	char c;
	double power = 1;
	int dot = 0;
	int len = strlen(expr);
	int i = 0;
	int upper = 0;
	double temp;

	while (i < len) {
		c = expr[i];

		if (c >= '0' && c <= '9') {
			num = num * 10 + (c - '0');
			if (dot == 1)
				power *= 0.1;
			if (i == len - 1) {
				printf("%g ", num);
				if (upper == 1)
					temp = pow(temp, num*power);
				else
					temp = num;

				result[p++] = temp;

				break;
			}
		}

		else if (c == '.') {
			dot = 1;
		}
	
//------keep out from here--------
		
		else if (c == '(') {
			op->push(OPEN);
		}

		else if (c == ')') {
			if (num != 0) {
				if (upper == 1) {
					printf("%g^%g ", temp, num*power);
					temp = pow(temp, num*power);
					result[p++] = temp;
				}
				else {
					temp = num*power;
					printf("%g ", temp);
					result[p++] = temp;
				}
			}
			num = 0;
			dot = 0;
			upper = 0;
			power = 1;

			while (op->top() != OPEN) {
				if (op->top() != OPEN || op->top() != CLOSE)
					result[p++] = op->top();
					if (op->isEmpty()) {
					printf("\nerror : wrong bracket pairs");
					exit(0);
				}
				operatorPrint((int)op->pop());
			}

			op->pop();
			
		}

		else if (c == '+' || c == '-' || c == '*' || c == '^' || c == '/') {
			if (c != '^') {
				if (num != 0) {
					if (upper == 1) {
						printf("%g^%g ", temp, num*power);
						temp = pow(temp, num*power);
						result[p++] = temp;
					}

					else {
						temp = num * power;
						result[p++] = temp;
						printf("%g ", temp);
					}
					num = 0;
					power = 1;
					dot = 0;
					upper = 0;
				}
			}
			switch (c) {
			case '+' :
				if (op->top() != MULTI && op->top() != DIVID) {
					op->push(PLUS);
					break;
				}
				else {
					while (op->top() != MULTI && op->top() != DIVID) {
						if (op->top() != OPEN && op->top() != CLOSE)
							result[p++] = op->top();

						operatorPrint((int)op->pop());
					}

					if (op->top() != OPEN && op->top() != CLOSE)
						result[p++] = op->top();
					operatorPrint((int)op->pop());
					op->push(PLUS);
				}
				break;

			case '-' :
				if (op->top() != MULTI && op->top() != DIVID) {
					op->push(MINUS);
					break;
				}
				else {
					while (op->top() != MULTI && op->top() != DIVID) {
						if (op->top() != OPEN && op->top() != CLOSE)
							result[p++] = op->top();

						operatorPrint((int)op->pop());
					}

					if (op->top() != OPEN && op->top() != CLOSE)
						result[p++] = op->top();
					operatorPrint((int)op->pop());
					op->push(MINUS);
				}
				break;

			case '*' :
				op->push(MULTI);
				break;

			case '/':
				op->push(DIVID);
				break;

			case '^' :
				temp = num*power;
				num = 0;
				break;

			default :
				break;
			}
			num = 0;
			dot = 0;
			if (c =='^')
				upper = 1;
			power = 1;
		}

		i++;
	}

	while (!op->isEmpty()) {
		if (op->top() == OPEN || op->top() == CLOSE) {
			printf("\nerror : wrong bracket pairs");
			exit(0);
		}
		result[p++] = op->top();
		operatorPrint((int)op->pop());
	}

	printf("\n\n");

	return 0;
}

void calculate() {
	double op1;
	double op2;
	stack* cal = (stack*)malloc(sizeof(stack));
	cal->init();

	for (int i = 0; i < p; i++) {
		if (result[i] > 0) {
			cal->push(result[i]);
		}

		else {
			op2 = cal->pop();
			op1 = cal->pop();

			if (result[i] == PLUS) {
				cal->push(op1 + op2);
			}

			else if (result[i] == MINUS) {
				cal->push(op1 - op2);
			}

			else if (result[i] == MULTI) {
				cal->push(op1 * op2);
			}

			else if (result[i] == DIVID) {
				cal->push(op1 / op2);
			}
		}
	}

	printf("%g ", cal->top());
}