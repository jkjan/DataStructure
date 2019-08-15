#include "maximumeffort.h"
#include <cstdlib>

static int stop; //문제의 전역변수

void tnode::init() {  //최대한 교수님이 권하신 대로 하였습니다.
	this->num = -1;
	this->lc = NULL;
	this->rc = NULL;
}

tnode* tnode:: addtree(tnode *p, int r, int lc, int rc) {  //insert를 재귀로 하고 val... ?
	if (p->num == -1)									   //교수님이 주신 해결 방법을 잘 이해하지 못해서
		p = addnode(r);									   //제가 직접 만든 방식으로 해결했습니다

	p->lc = addnode(lc);
	p->rc = addnode(rc);
	return p;
}

tnode* tnode::addnode(int val) {
	tnode* newnode = new tnode;			//대신 노드 하나 하나 만드는 함수를 만들어
	newnode->num = val;					//포인터 변수 저장공간에 그 주소를 저장하는 식으로 구현했습니다
	newnode->lc = newnode->rc = NULL;
	return newnode;
}

tnode* tnode::search(tnode* p, int val) {
	stop = 0;

	if (p == NULL)
		return NULL;

	else {
		if (p->num == val) {   //원래 형태는 treeprint와 같은 순회인데 이게 return p를 하여도 멈추지 않더랍니다
			stop = 1;
			return p;
		}
		if (!stop)             //재귀함수가 멈추질 않아서 전역변수를 썼는데..
			search(p->lc, val);

		if (!stop)
			search(p->rc, val);
	}
}

tnode* tnode::valid(tnode* p, int val, int l, int r) {
	tnode* next;
	if ((next = search(p, val)) != NULL)
		//이렇게 한 이유는 main에서 search 함수가 한 번 더 호출되는 것을 막기 위해서입니다.
		if (isleaf(next, val) && checkrulethree(p, l, r))
			return next; //문장이 valid하다 판단되면 어디다가 노드를 넣을지 main에게 친절하게 알려주는 코드입니다

	return NULL;
}

bool tnode::checkrulethree(tnode* p, int l, int r) {
	tnode* lv;
	tnode* rv;	//left child, right child 의 후보들이 트리에 이미 존재하는지 안 하는지를 알려주는 함수입니다.
	return ((lv = search(p, l)) == NULL) && ((rv = search(p, r)) == NULL) ? true : false;
	//원래 valid에 합치려고 했는데 더러워져서 뺐습니다.
}

//일단 p가 존재하는 건 확실한데 그게 자식이 있는지 없는지를 확인해주는 함수입니다.
bool tnode::isleaf(tnode* temp, int val) {  
	return temp->lc == temp->rc ? (temp->lc == NULL ? true : false) : false;
}

void tnode:: treeprint(tnode*p) {   
	if (p != NULL) {
		treeprint(p->lc);         //in order 순회입니다
		cout<< p->num<<' ';    
		treeprint(p->rc);            
	}
}

int tnode::height(tnode*p) {
	if (p == NULL)
		return 0;
	int lh = height(p->lc);
	int rh = height(p->rc);
	return 1 + (lh > rh ? lh : rh);
}

int tnode::width(tnode* p) {
	if (p == NULL)
		return 0;
	int lw = width(p->lc);
	int rw = width(p->rc);
	int ww = height(p->lc) + height(p->rc);
	return ww > lw ? (ww > rw ? ww : rw) : (lw > rw ? lw : rw); //lw와 rw, lh+hw 의 최대값입니다
}

void tnode::thanos(tnode* p) {
	if (p != NULL) {
		thanos(p->lc);
		thanos(p->rc);
		delete(p);
	}
}