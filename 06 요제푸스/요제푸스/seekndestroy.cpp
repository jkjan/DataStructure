#include "killemall.h" 

int main() {

	jo real;
	jo*access = &real;

	
	
	ifstream com;
	com.open("input.txt");
	cout << "input.txt";
	real.verify("input.txt");

	int n, k;
	int num;
	int i;
	int lines;
	int whowas;

	com >> lines;

	for (i = 0; i < lines; i++) {
		access = real.init();

		com >> n >> k;
		num = n;

		cout << n << "명이 앉아 " << k << "명씩 죽입니다." << endl;

		for (int j = 1; j <= n; j++) 
			real.enque(access, j);
		
		while (num >= k) {
			for (int j = 0; j < k; j++) {
				whowas = real.deque(access);
				num--;
				if (j < k - 1) {
					real.enque(access, whowas);
					num++;
					//cout << whowas << "는 살았다" << endl;
				}
			}
		}

		cout << num <<"명이 남았고, ";
		if (num==1)
			cout << "그는 ";
		else
			cout << "그들은 ";

		for (int j = 0; j < num; j++) {
			cout << real.deque(access);
			if (j < num-1)
				cout << ", ";
		}

		cout << "번째 사람입니다." <<endl;
		cout << endl;
	}



}