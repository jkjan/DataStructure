#include "poly.h"
#include <math.h>

void poly::add(poly* A, poly* B) {
	this->zero();

	if (A->isZero()) {
		this->head = B->head;
		this->tail = B->tail;
		return;
	}

	if (B->isZero()) {
		this->head = A->head;
		this->tail = A->tail;
		return;
	}

	hang* curA = A->head->next;
	hang* curB = B->head->next;

	while (curA != NULL && curB != NULL) {
		if (curA->exp > curB->exp) {
			this->insert(curA->coef, curA->exp);
			curA = curA->next;
		}

		else if (curA->exp == curB->exp) {
			if (curA->coef + curB->coef != 0)
				this->insert(curA->coef + curB->coef, curA->exp);
			curA = curA->next;
			curB = curB->next;
		}

		else {
			this->insert(curB->coef, curB->exp);
			curB = curB->next;
		}
	}

	while (curA != NULL) {
		this->insert(curA->coef, curA->exp);
		curA = curA->next;
	}
	
	while (curB != NULL) {
		this->insert(curB->coef, curB->exp);
		curB = curB->next;
	}
}

void poly::multi(poly* A, poly *B) {
	if (A->isZero() || B->isZero()) {
		this->zero();
		return;
	}

	this->zero();
	hang*curA = A->head->next;
	hang*curB = B->head->next;

	while (curA != NULL) {
		while (curB != NULL) {
			if (curA->coef * curB->coef != 0)
				this->insert(curA->coef * curB->coef, curA->exp + curB->exp);
			curB = curB->next;
		}

		curA = curA->next;
		curB = B->head->next;
	}
}

void poly::pprint() {
	hang * cur = this->head->next;
	
	if (this->isZero()) {
		printf("0\n\n");
		return;
	}

	while (cur != NULL) {
		if (cur->coef != 0) {	//계수가 0이 아니면서
			if (cur->coef < 0) { //음수라면
				if (cur->exp == this->leadExp())   //최고차항일시
					printf("-");
				else
					printf(" - ");
			}
			if (abs(cur->coef) != 1 || cur->exp == 0)    //절대값이 1이 아니거나 지수가 0일 때
				printf("%d", abs(cur->coef));

			if (cur->exp != 0) {   //지수가 0이 아닐 경우
				printf("x");       //x 출력

				if (cur->exp < 0)  //지수가 음수면 괄호
					printf("^(%d)", cur->exp);

				else if (cur->exp != 1)
					printf("^%d", cur->exp);
			}
		}

		if (cur->coef != 0 && cur->next != NULL && cur->next->coef > 0)   // 다음 항이 존재하고 그 계수가 양수일 때
			printf(" + ");

		cur = cur->next;
	}
	printf("\n\n");
}