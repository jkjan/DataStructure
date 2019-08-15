//다항식 연산
#include "poly.h"
#include <stdlib.h>
#include <ctype.h>
#include <math.h>

extern poly* A;
extern poly* B;

void hang::setHang(int c, int e, hang* next) {
	this->coef = c;
	this->exp = e;
	this->next = next;
}

void load(FILE*fp) {
	A->zero();
	B->zero();

	int cnt;
	int c = 0;
	int start = 0;

	int AorB = 0;

	while (fscanf(fp, "%d", &cnt) != EOF) {
		if (start == 0 && cnt != 0) {
			start = cnt*2;
			continue;
		}
		
		if (start % 2 == 0)
			c = cnt;
		else {
			if (AorB == 0)
				A->insert(c, cnt);
			else {
				B->insert(c, cnt);
			}
		}
		
		if (start == 1) {
			AorB = 1;
			start = 0;
		}
		else
			start--;
	}

	if (start != 0) { //수가 맞지 않음
		printf("error : the polynomials in the text file are ambiguous.\n");
		printf("        please check the numbers.\n");
		exit(0);
	}

}

void poly::zero() { //0짜리 생성 
	this->head = (hang*)malloc(sizeof(hang));
	hang *zerohang = (hang*)malloc(sizeof(hang));
	zerohang->setHang(0, 0, NULL);
	this->head->setHang(-1, -1, zerohang);
	this->tail = zerohang;
}

int poly::isZero() { //0인지 확인
	return ((this->leadExp() == 0) && (this->head->next->coef == 0) && (this->head->next->next == NULL)) ? 1 : 0;
}

int poly::coef(int e) { //지수가 e인 항의 계수 리턴
	hang *cur = this->head;

	while (cur != NULL) {
		if (cur->exp == e)
			return cur->coef;
		cur = cur->next;
	}

	if (cur == NULL)
		return 0;
}

int poly::leadExp() { //최고차항의 지수 리턴
	return this->head->next->exp;
}

void poly::append(int c, int e) { //cx^e를 마지막에 추가
	if (this->tail->exp > e) {
		hang* newhang = (hang*)malloc(sizeof(hang));
		newhang->setHang(c, e, NULL);

		this->tail->next = newhang;
		this->tail = newhang;
	}
	else if (this->tail->exp == e) {
		this->tail->coef += c;
		if (this->tail->coef == 0) {
			this->tail->exp = 0;
			if ((this->leadExp() == 0) && (this->head->next->coef == 0)) //마지막 항이 0이 되었는데 최고차항도 0이면
				this->zero(); //0으로 초기화
		}
	}
	//장점 : 맨 뒤에 들어가야 할 시 O(1)
	//단점 : 연산의 결과가 0이 될 시 삭제가 안 되고 남아있음. 단, 출력이나 추후 연산에 영향 x
}

void poly::insert(int c, int e) { //cx^e를 적절한 위치에 삽입
	if (c == 0)
		return;

	hang* cur = this->head;
	hang* newhang = (hang*)malloc(sizeof(hang));
	newhang->setHang(c, e, NULL);

	if (this->isZero()) {
		this->head->next->coef = c;
		this->head->next->exp = e;
		this->tail = this->head->next;
		return;
	}

	if ((e <= this->tail->exp)) {  //마지막 항의 지수보다 작음 -> append
		this->append(c, e);
		return;
	}

	while (cur->next != NULL) {
		if (cur->next->exp == e) {
			cur->next->coef += c;

			if (cur->next->coef == 0) {
				cur->next->exp = 0;
				if ((this->leadExp() == 0) && (this->head->next->coef == 0) && (cur->next->next == NULL)) { //합이 0인데 최고차항도 0이면
					this->zero(); 
				}
			}
			return;
		}

		else if (cur->next->exp < e) {
			break;
		}

		cur = cur->next;
	}
	
	newhang->next = cur->next;
	cur->next = newhang;
}