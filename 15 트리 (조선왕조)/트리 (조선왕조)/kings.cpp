#include "kingstack.h"
#include <string.h>

void stack::init() {
	this->kings = new char*[30];
	for (int i = 0; i < 30; i++) {
		this->kings[i] = new char[7];
	}

	this->cnt = 0;
	this->size = 30;
}

void stack::push(char* name) {
	if (this->is_full())
		return;
	strcpy(this->kings[this->cnt++], name);
}

char* stack::pop() {
	if (this->is_empty())
		return NULL;
	return this->kings[--this->cnt];
}

char* stack::top() {
	if (this->is_empty())
		return NULL;
	return this->kings[this->cnt-1];
}

int stack::is_empty() {
	return this->cnt == 0 ? 1 : 0;
}

int stack::is_full() {
	return this->cnt >= this->size ? 1 : 0;
}