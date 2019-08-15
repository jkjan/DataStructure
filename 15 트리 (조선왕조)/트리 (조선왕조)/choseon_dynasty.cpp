#include "choseon_dynasty.h"
#include "kingstack.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern stack* dynasty;
extern int kingcnt;

void kings::init(char* name){
	strcpy(this->name, name);
	this->num = 0;
	this->enemies = new enemy;
	this->enemies->king = new kings;
	strcpy(this->enemies->king->name, "-2");
	this->enemies->next = NULL;
}

void kings::init() {
	strcpy(this->name, "-1");
	this->num = 0;
	this->enemies = new enemy;
	this->enemies->king = new kings;
	strcpy(this->enemies->king->name, "-2");
	this->enemies->next = NULL;
}

bool kings::is_empty(){
	return strcmp(this->name, "-1") == 0 ? true : false;
}

int kings::insert(int nchildren, char** names) {

	//printStrings(nchildren + 1, names);

	kings* sun = new kings;

	if (strcmp(this->name, "-2") == 0) {
		return 0;
	}


	if (strcmp(this->name, names[0]) == 0 || strcmp(this->name, "-1") == 0) {
		this->init(names[0]);
		this->num = nchildren;
		enemy* enemy_append = this->enemies;
		for (int i = 0; i < nchildren; i++) {
			enemy_append->king->init(names[i + 1]);
			if (i < nchildren - 1) {
				enemy_append->next = new enemy;
				enemy_append->next->king = new kings;
				enemy_append = enemy_append->next;
			}

			else {
				enemy_append->next = NULL;
				break;
			}
		}

		return 1;
	}

	else {
		enemy* enemy_append = this->enemies;

		while (enemy_append != NULL) {
			if (enemy_append->king->insert(nchildren, names)==1)
				break;
			enemy_append = enemy_append->next;
		}
	}
	return 0;
}

enemy* kings::get_children(char* name){
	enemy* returning;

	if (this->is_empty()) {
		printf("no family tree exists");
		return 0;
	}

	if (strcmp(this->name, "-2") == 0) {
		return 0;
	}

	else if (strcmp(this->name, name) == 0) {
		if (this->num == 0) {
			printf("자식이 없습니다.\n");
			return 0;
		}

		/*
		kings** children = new kings*[n+1];

		for (int i = 0; i < n+1; i++)
			children[i] = new kings;
			*/

		//enemy* enemy_list = this->enemies;
		/*
		char buf[3];
		itoa(n, buf, 10);
		children[0]->num = n;

		//printf("%s 자식 : %d %s", name, n, buf);
		//printf("%s ", enemy_list->king->name);

		for (int i = 0; i < n; i++) {
		//	printf("%d ", i);
			//strcpy(children[i+1], enemy_list->king->name);
			children[i + 1] = enemy_list->king;
			//printf("%s ", enemy_list->king->name);
			enemy_list = enemy_list->next;
		}
		printf("\n");
		*/

		return this->enemies;
	}

	else {

		enemy* enemies_list = this->enemies;
		while (enemies_list != NULL) {
			if ((returning = enemies_list->king->get_children(name)) != NULL)
				break;
			enemies_list = enemies_list->next;
		}
	}

	return returning;
}

kings* kings::get_daddy(char* name){
	kings* returning;

	if (this->is_empty()) {
		printf("no family tree exists");
		return NULL;
	}

	if (strcmp(this->name, "-2") == 0) {
		return NULL;
	}

	if (strcmp(name, "태조") == 0) {
		printf("아버지 : 이자춘\n");
		return this;
	}

	else {
		enemy* enemy_list = this->enemies;
		
		while (enemy_list != NULL) {
			if (strcmp(enemy_list->king->name, name) == 0) {
				return this;
			}
			enemy_list = enemy_list->next;
		}

		enemy_list = this->enemies;

		while (enemy_list != NULL) {
			if ((returning = enemy_list->king->get_daddy(name)) != NULL) {
				break;
			}
			enemy_list = enemy_list->next;
		}
	}

	return returning;
}

char** kings::get_enemies(char* name){
	if (this->is_empty()) {
		return NULL;
	}

	printf("형제 : ");

	if (strcmp(name, "태조") == 0) {
		printf("완풍대군, 정화공주\n");
		return NULL;
	}

	kings* father = new kings;
	father = this->get_daddy(name);

	if (father->num < 2) {
		printf("형제가 없습니다.\n");
		return NULL;
	}

	char** enemies = new char*[father->num];
	for (int i = 0; i < father->num; i++)
		enemies[i] = new char[7];

	enemy* enemy_list = father->enemies;

	for (int i = 0; i < father->num; i++) {
		strcpy(enemies[i], enemy_list->king->name);
		if (strcmp(enemy_list->king->name, name) != 0)
			printf("%s ", enemy_list->king->name);
		enemy_list = enemy_list->next;
	}
	printf("\n");

	return enemies;
}

void kings::treeprint(){
	if (this->is_empty()) {
		printf("no family tree exists");
		return;
	}

	if (strcmp(this->name, "-2") == 0) {
		return;
	}

	enemy * enemies_list = this->enemies;

	printf("%s ", this->name);
	dynasty->push(this->name);
	kingcnt++;
	printf("\n");

	enemies_list = this->enemies;

	while (enemies_list != NULL) {
		enemies_list->king->treeprint();
		enemies_list = enemies_list->next;
	}
}


void kings::whosNotKing() {
	if (this->is_empty()) {
		printf("no family tree exists");
		return;
	}

	if (strcmp(this->name, "-2") == 0) {
		return;
	}

	enemy * enemies_list = this->enemies;
	int no = 0;
	for (int i = 0; i < this->num; i++) {
		if (strcmp(enemies_list->king->name, "-2") == 0)
			no++;
		enemies_list = enemies_list->next;
	}
	if (no >= this->num)
		printf("%s\n", this->name);
	
	enemies_list = this->enemies;

	while (enemies_list != NULL) {
		enemies_list->king->whosNotKing();
		enemies_list = enemies_list->next;
	}
}

char bestKing[7];
int kingmade;
int upToTwo;

void kings::theBestKingMaker() {
	if (this->is_empty()) {
		printf("no family tree exists");
		return;
	}

	if (strcmp(this->name, "-2") == 0) {
		return;
	}

	enemy * enemies_list = this->enemies;

	if (this->num >= 2)
		upToTwo++;

	if (this->num >= kingmade) {
		strcpy(bestKing, this->name);
		kingmade = this->num;
	}

	enemies_list = this->enemies;

	while (enemies_list != NULL) {
		enemies_list->king->theBestKingMaker();
		enemies_list = enemies_list->next;
	}
}
/*
void kings::descendents(char* name) {
	int n;
	enemy* child;
	child = this->get_children(name);

	enemy* children_list = child;
	
	while (children_list != NULL) {
		printf("%s ", children_list->king->name);
		children_list = children_list->next;
	}
	children_list = child;

	while (1) {

	}
}
*/