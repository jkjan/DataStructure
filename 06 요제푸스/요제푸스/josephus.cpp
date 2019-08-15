
#include "killemall.h"

jo* jo::init() {
	jo* real = new jo;
	real->people = NULL;
	real->cur = real->people;
	real->cnt = 0;

	return real;
}
int jo::isempty(jo*que) {
	return (que->cnt == 0) ? 1 : 0;
}

int jo::isfull(jo* que) {
	return 0;
}

int jo::enque(jo*que, int what) {
	node*newnode = new node;
	newnode->who = what;
	newnode->next = NULL;

	if (!isfull(que)) {
		if (que->people == NULL) {
			que->cur = newnode;
			que->people = newnode;
		}
		else
			que->cur->next = newnode;
		que->cur = newnode;

		que->cnt++;

		return 1;
	}

	else {
		cout << "error : queue full" << endl;
		return -1;
	}
}

int jo::deque(jo*que) {
	if (!isempty(que)) {
		node*delnode = que->people;
		int whowasit = delnode->who;
		que->people = que->people->next;
		delete delnode;
		que->cnt--;
		return whowasit;
	}
	else {
		cout << "error : queue empty" << endl;
		return -1;
	}
	
}

bool jo::verify(const std::string& filename)
{
	struct stat buf;
	if (stat(filename.c_str(), &buf) != -1)
	{
		cout << " has been successfully opened\n" << endl;
		return true;
	}
	cout << "Failed to open the file\n" << endl;
	return false;
}
