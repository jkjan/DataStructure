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
	교수님 코드 적용
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

	if (strcmp(p->info->getname(), name) != 0) {  //맨 첫번째 이름이 찾으려는 이름이 아닐 때 (찾으려는 값이 루트가 아닐 시)
		returned = p->search(name);				  //returned에 찾은 노드 정보 저장

		if (returned == NULL)                     //없을 시 종료
			return 0;
	}

	else {										  //루트 노드일 시
		if (p->lc != NULL) {					  //왼쪽이 존재할 시
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

	if (returned->lr == 1) {    //찾은 노드의 왼쪽이 타겟
		if (isleaf(returned->searched->lc) == 1) {    //타겟이 리프일 경우
			node* delnode = new node;
			delnode = returned->searched->lc;
			returned->searched->lc = NULL;			  //찾은 노드의 왼쪽에 NULL 저장
			delete(delnode);

			return 1;
		}

		if (returned->searched->lc->lc == NULL && returned->searched->lc->rc != NULL) { //왼쪽은 없고 오른쪽만 존재할 경우
			node* delnode = new node;
			delnode = returned->searched->lc;
			returned->searched->lc = returned->searched->lc->rc;  //타겟의 오른쪽을 타겟의 부모의 왼쪽에 저장
			delete(delnode);

			return 1;
		}

		if (returned->searched->lc->lc != NULL && returned->searched->lc->rc == NULL) { //왼쪽만 있고 오른쪽만 존재
			node* delnode = new node;
			delnode = returned->searched->lc;
			returned->searched->lc = returned->searched->lc->lc;  //타겟의 왼쪽을 타겟의 부모의 왼쪽에 저장
			delete(delnode);
			return 1;
		}

		else { //둘 다 존재
			whatwas = LeftMax = getLeftMax(returned->searched->lc->lc); //여기서 LeftMax는 최대값 노드의 바로 전 노드임
			if (LeftMax->rc != NULL) { //LeftMax 의 오른쪽이 NULL일 경우는 타겟의 왼쪽 노드의 오른쪽이 존재하지 않을 경우(서브트리의 루트)
				LeftMax = LeftMax->rc;  //이 경우가 아니라면 whatwas에는 LeftMax의 주소가, LeftMax에는 실제 최대값의 노드가 저장됨
			}
		}

		//삭제 작업
		returned->searched->lc->info = LeftMax->info;

		if (whatwas->rc == NULL) {  //왼쪽의 최대값이 타겟의 왼쪽 서브트리의 루트노드일 경우
			if (whatwas->lc != NULL) //그 루트의 왼쪽으로 트리가 존재한다면
				returned->searched->lc->lc = LeftMax->lc;  //타겟의 왼쪽에 LeftMax의 왼쪽 서브트리를 저장
			else                    //아니라면 (이 경우는 리프일 경우. 오른쪽에 대한 예외처리 없는 이유는 오른쪽이 있었다면 애초에 최대값이 루트일 수가 없음)
				returned->searched->lc->lc = NULL;
			
			delete(LeftMax);
			return 1;
		}
	}

	else {
		if (isleaf(returned->searched->rc) == 1) {    //타겟이 리프일 경우
			node* delnode = new node;
			delnode = returned->searched->rc;
			returned->searched->rc = NULL;			  //찾은 노드의 왼쪽에 NULL 저장
			delete(delnode);

			return 1;
		}

		if (returned->searched->rc->lc == NULL && returned->searched->rc->rc != NULL) { //왼쪽은 없고 오른쪽만 존재할 경우
			node* delnode = new node;
			delnode = returned->searched->rc;
			returned->searched->rc = returned->searched->rc->rc;  //타겟의 오른쪽을 타겟의 부모의 왼쪽에 저장
			delete(delnode);

			return 1;
		}

		if (returned->searched->rc->lc != NULL && returned->searched->rc->rc == NULL) { //왼쪽만 있고 오른쪽만 존재
			node* delnode = new node;
			delnode = returned->searched->rc;
			returned->searched->rc = returned->searched->rc->lc;  //타겟의 왼쪽을 타겟의 부모의 왼쪽에 저장
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