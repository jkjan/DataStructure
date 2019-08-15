#include "maximumeffort.h"
#include <fstream>

int main() {
	ifstream tony;
	tony.open("stark.txt");
	cout << "stark.txt";
	verify("stark.txt");

	tnode* acc = new tnode;
	acc->init();

	int lines, i;
	int root, left, right;
	lines = line(tony);  //줄 수를 한 번에 셌습니다.
	tony.clear();
	tony.seekg(0);

	tnode* next;

	for (i = 0; i < lines; i++) {
		tony >> root >> left >> right;
		cout << root <<' ' << left<< ' ' << right << endl;
		if (!i) {	//addtree 자체에 예외처리가 없습니다. 또한 루트 노드를 저장해야 합니다.
			acc = acc->addtree(acc, root, left, right);
			cout << "gimme the root!" << endl;
		}

		else if ((next = acc->valid(acc, root, left, right)) != NULL) { //valid 여부 확인하는 동시에
			acc->addtree(next, root, left, right);						//노드를 추가할 주소도 얻을 수 있습니다
			cout << "added" << endl;
		}

		else
			cout << "invalid" << endl;

		cout << '\n';
	}
	tony.close();

	acc->treeprint(acc);
	cout << '\n';
	cout << "height : " << acc->height(acc) << endl;
	cout << " width : " << acc->width(acc) << endl;

	acc->thanos(acc);
	
	return 0;
}
