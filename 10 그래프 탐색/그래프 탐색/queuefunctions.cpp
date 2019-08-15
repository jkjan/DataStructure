#include "queue.h"
#include <iostream>
#include <cstdlib>

void jo::init() {
	this->people = NULL;
	this->cur = this->people;
	this->cnt = 0;
}

int jo::isempty() {
	return (this->cnt == 0) ? 1 : 0;
}

int jo::isfull() {
	return 0;
}

int jo::enque(int what) {
	qnode*newnode = new qnode;
	newnode->who = what;
	newnode->next = NULL;

	if (!isfull()) {
		if (this->people == NULL)
			this->people = newnode;

		else
			this->cur->next = newnode;

		this->cur = newnode;

		this->cnt++;

		return 1;
	}

	else {
		puts("error : queue full");
		return -1;
	}
}

int jo::deque() {
	if (!this->isempty()) {
		qnode*delnode = this->people;
		int whowasit = delnode->who;
		this->people = this->people->next;
		delete delnode;
		this->cnt--;
		return whowasit;
	}

	else {
		puts("error : queue empty");
		return -1;
	}
}