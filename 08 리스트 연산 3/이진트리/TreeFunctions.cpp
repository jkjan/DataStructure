#include "MinIsTheBestProfInTheWorld.h"
#include <string.h>
#include <fstream>
static int stop;

void node::treeprint() {
	if (this != NULL) {
		this->lc->treeprint();
		this->info->infoprint();
		this->rc->treeprint();
	}
}

node* node::addtree(node* p, sinfo* w) {
	if (p == NULL) {
		p = talloc();
		p->info = w;
		p->lc = p->rc = NULL;
	}

	else if (strcmp(w->getname(), p->info->getname()) < 0)
		p->lc = addtree(p->lc, w);
	else
		p->rc = addtree(p->rc, w);

	return p;
}

getReturn* node::search(char* name) {
	stop = 0;

	if (this == NULL)
		return NULL;

	if (strcmp(this->info->getname(), name) == 0)
		return setReturn(this, 2);

	if (this->lc != NULL && strcmp(this->lc->info->getname(), name) == 0) {
		stop = 1;
		return setReturn(this, 1);
	}

	else if (this->rc != NULL && strcmp(this->rc->info->getname(), name) == 0) {
		stop = 1;
		return setReturn(this, 0);
		
	}

	if (!stop) {
		this->lc->search(name);
	}

	if (!stop) {
		this->rc->search(name);
	}
}

int node::remove(node * p, char* name) {
	node* LeftMax = new node;
	node* whatwas = talloc();
	getReturn* returned = new getReturn;
	/*
	������ �ڵ� ����
	int cond;

	if ((cond = strcmp(name, p->info->name)) == 0) {
		if (p->lc == NULL && p->rc == NULL)
			return 1;
		if (p->lc == NULL && p->rc != NULL) {
			p->info = p->rc->info;
			p->lc = p->rc->lc;
			p->rc = p->rc->rc;
			return 0;
		}
		if (p->lc != NULL && p->rc == NULL) {
			p->info = p->lc->info;
			p->lc = p->lc->lc;
			p->rc = p->lc->rc;
			return 0;
		}

		if (p->lc != NULL && p->rc != NULL) {
			p->info = getLeftMax(p->lc)->rc->info;
			if (remove(p->lc, p->info->name) == 1)
				p->lc = NULL;
			return 0;
		}
	}

	else if (cond < 0) {
		if (p->lc != NULL) {
			if (remove(p->lc, name) == 1)
				p->lc = NULL;
		}
		return 0;
	}

	else {
		if (p->rc != NULL) {
			if (remove(p->rc, name) == 1)
				p->rc = NULL;
		}
		return 0;
	}
	*/

	if (strcmp(p->info->getname(), name) != 0) {  //�� ù��° �̸��� ã������ �̸��� �ƴ� �� (ã������ ���� ��Ʈ�� �ƴ� ��)
		returned = p->search(name);				  //returned�� ã�� ��� ���� ����

		if (returned == NULL)                     //���� �� ����
			return 0;
	}

	else {										  //��Ʈ ����� ��
		if (p->lc != NULL) {					  //������ ������ ��
			whatwas = LeftMax = getLeftMax(p->lc);//

			if (LeftMax->rc != NULL) {
				LeftMax = LeftMax->rc;
			}
			p->info = LeftMax->info;

			if (LeftMax->lc != NULL) {
				whatwas->rc = LeftMax->lc;
			}

			else
				whatwas->rc = NULL;
			return 1;
		}
		else {
			p = p->rc;
			return 1;
		}
	}

	if (returned->lr == 1) {    //ã�� ����� ������ Ÿ��
		if (isleaf(returned->searched->lc) == 1) {    //Ÿ���� ������ ���
			node* delnode = new node;
			delnode = returned->searched->lc;
			returned->searched->lc = NULL;			  //ã�� ����� ���ʿ� NULL ����
			delete(delnode);

			return 1;
		}

		if (returned->searched->lc->lc == NULL && returned->searched->lc->rc != NULL) { //������ ���� �����ʸ� ������ ���
			node* delnode = new node;
			delnode = returned->searched->lc;
			returned->searched->lc = returned->searched->lc->rc;  //Ÿ���� �������� Ÿ���� �θ��� ���ʿ� ����
			delete(delnode);

			return 1;
		}

		if (returned->searched->lc->lc != NULL && returned->searched->lc->rc == NULL) { //���ʸ� �ְ� �����ʸ� ����
			node* delnode = new node;
			delnode = returned->searched->lc;
			returned->searched->lc = returned->searched->lc->lc;  //Ÿ���� ������ Ÿ���� �θ��� ���ʿ� ����
			delete(delnode);
			return 1;
		}

		else { //�� �� ����
			whatwas = LeftMax = getLeftMax(returned->searched->lc->lc); //���⼭ LeftMax�� �ִ밪 ����� �ٷ� �� �����
			if (LeftMax->rc != NULL) { //LeftMax �� �������� NULL�� ���� Ÿ���� ���� ����� �������� �������� ���� ���(����Ʈ���� ��Ʈ)
				LeftMax = LeftMax->rc;  //�� ��찡 �ƴ϶�� whatwas���� LeftMax�� �ּҰ�, LeftMax���� ���� �ִ밪�� ��尡 �����
			}
		}

		//���� �۾�
		returned->searched->lc->info = LeftMax->info;

		if (whatwas->rc == NULL) {  //������ �ִ밪�� Ÿ���� ���� ����Ʈ���� ��Ʈ����� ���
			if (whatwas->lc != NULL) //�� ��Ʈ�� �������� Ʈ���� �����Ѵٸ�
				returned->searched->lc->lc = LeftMax->lc;  //Ÿ���� ���ʿ� LeftMax�� ���� ����Ʈ���� ����
			else                    //�ƴ϶�� (�� ���� ������ ���. �����ʿ� ���� ����ó�� ���� ������ �������� �־��ٸ� ���ʿ� �ִ밪�� ��Ʈ�� ���� ����)
				returned->searched->lc->lc = NULL;
			
			delete(LeftMax);
			return 1;
		}
	}

	else {
		if (isleaf(returned->searched->rc) == 1) {    //Ÿ���� ������ ���
			node* delnode = new node;
			delnode = returned->searched->rc;
			returned->searched->rc = NULL;			  //ã�� ����� ���ʿ� NULL ����
			delete(delnode);

			return 1;
		}

		if (returned->searched->rc->lc == NULL && returned->searched->rc->rc != NULL) { //������ ���� �����ʸ� ������ ���
			node* delnode = new node;
			delnode = returned->searched->rc;
			returned->searched->rc = returned->searched->rc->rc;  //Ÿ���� �������� Ÿ���� �θ��� ���ʿ� ����
			delete(delnode);

			return 1;
		}

		if (returned->searched->rc->lc != NULL && returned->searched->rc->rc == NULL) { //���ʸ� �ְ� �����ʸ� ����
			node* delnode = new node;
			delnode = returned->searched->rc;
			returned->searched->rc = returned->searched->rc->lc;  //Ÿ���� ������ Ÿ���� �θ��� ���ʿ� ����
			delete(delnode);
			return 1;
		}

		else {
			whatwas = LeftMax = getLeftMax(returned->searched->rc->lc); 

			if (LeftMax->rc != NULL) {  
				LeftMax = LeftMax->rc;
			}
		}

		returned->searched->rc->info = LeftMax->info;
		if (whatwas->rc == NULL) {
			if (whatwas->lc != NULL) 
				returned->searched->rc->lc = whatwas->lc;
			else 
				returned->searched->rc->lc = NULL;
			
			delete(LeftMax);
			return 1;
		}
	}

	if (LeftMax->lc != NULL) {
		whatwas->rc = LeftMax->lc;
		
	}
	else
		whatwas->rc = NULL;
	delete(LeftMax);

	return 1;
}

int node::isleaf(node * p) {
	if ((p->lc == NULL) && (p->rc == NULL))
		return 1;
	else
		return 0;
}

node * node::getLeftMax(node * p) {
	node* max = new node;
	max = p;

	while (p->rc != NULL) {
		max = p;
		p = p->rc;
	}
	return max;
}

node* node::talloc() {
	return (node*)malloc(sizeof(node));
}

getReturn* node::setReturn(node * p, int l) {
	getReturn* srched = new getReturn;
	srched->searched = p;
	srched->lr = l;
	return srched;
}