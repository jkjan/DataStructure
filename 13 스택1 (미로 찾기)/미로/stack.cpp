#include "stack.h"
#include <stdlib.h>
#include <stdio.h>
void skein::init(int n){
	this->stack = (pos*)malloc(sizeof(pos)*n);
	this->size = n;
	this->cnt = 0;
}

void skein::push(int x, int y){
	if (this->isFull())
		return;
	
	this->stack[cnt].x = x;
	this->stack[cnt].y = y;
	this->cnt++;
}

pos* skein::pop(){
	if (this->isEmpty())
		return NULL;

	return this->stack+(--cnt);
}

pos* skein::top(){
	if (this->isEmpty())
		return NULL;

	return &(this->stack[cnt-1]);
}

int skein::isFull(){
	return (this->size == this->cnt) ? 1 : 0;
}

int skein::isEmpty(){
	return this->cnt == 0 ? 1 : 0;
}