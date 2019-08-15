#include "megadeth.h"

stack* stack::init(){
	stack* real = (stack*)malloc(sizeof(stack));
	real->head = NULL;
	real->cnt = 0;
	return real;
}
int stack::is_full(stack* seg){
	return 0;
}

int stack::is_empty(stack* seg){
	if (seg->cnt == 0)
		return 1;
	return 0;
}

void stack::push(stack* seg, char ch){
	node*newnode = (node*)malloc(sizeof(node));
	newnode->space = ch;
	newnode->next = NULL;

	if (!is_full(seg)) {
		if (seg->head == NULL)
			seg->head = newnode;
		else
			newnode->next = seg->head;

		seg->head = newnode;

		seg->cnt++;
	}

	else
		cout << "error : stack full" << endl;
}

char stack::pop(stack* seg){
	if (is_empty(seg))
		cout << "error : stack empty" << endl;
		
	else{
		char was = seg->head->space;
		node*delnode = seg->head;
		seg->head = seg->head->next;
		free(delnode);
		seg->cnt--;
		
		return was;
	}
}

char stack::top(stack* seg){
	if (!is_empty(seg))
		return seg->head->space;
	else {
		cout << "error : stack empty" << endl;
		return -1;
	}
}