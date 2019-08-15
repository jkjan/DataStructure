#include "stack.h"

void stack::init(){
	this->cnt = 0;
}

void stack::push(double n){
	if (this->isFull())
		return;
	this->stack[(this->cnt)++] = n;
}

double stack::pop(){
	if (this->isEmpty())
		return -8;
	return this->stack[--(this->cnt)];
}

double stack::top(){
	if (this->isEmpty())
		return -8;
	return this->stack[(this->cnt)-1];
}

int stack::isFull(){
	return this->cnt >= 100 ? 1 : 0;
}

int stack::isEmpty(){
	return this->cnt == 0 ? 1 : 0;
}
