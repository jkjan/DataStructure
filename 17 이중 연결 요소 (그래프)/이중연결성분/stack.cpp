#include "stack.h"
#include <string.h>

void stack::init() {
	this->edges = new edge[100];
	this->cnt = 0;
	this->size = 100;
}

void stack::push(int u, int w) {
	if (this->is_full())
		return;
	this->edges[this->cnt].u = u;
	this->edges[this->cnt].w = w;
	this->cnt++;
}

edge* stack::pop() {
	if (this->is_empty())
		return NULL;
	return this->edges + (--this->cnt);
}

edge* stack::top() {
	if (this->is_empty())
		return NULL;
	return this->edges+ (this->cnt - 1);
}

int stack::is_empty() {
	return this->cnt == 0 ? 1 : 0;
}

int stack::is_full() {
	return this->cnt >= this->size ? 1 : 0;
}