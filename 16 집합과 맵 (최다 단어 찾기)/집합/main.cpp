#include "maximumeffort.h"
#include <Windows.h>
#include "heap.h"
#define MAXWORD 100

tnode *addtree(tnode*, char*);  //predefinition of functions that are used in this main func
void treeprint(tnode *);
int getword(char *, int);
char * strdupli(char *s);
tnode* talloc();

heap hip[100000];
int cnt = 1;

void swap(int a, int b) {
	heap temp = hip[a];
	hip[a] = hip[b];
	hip[b] = temp;
}

void insert(char* key, int value) {
	if (cnt >= 100000) {
		return;
	}

	strcpy(hip[cnt].key, key);
	hip[cnt].value = value;
	int index = cnt;
	while (index != 1) {
		if (hip[index].value > hip[index / 2].value) {
			swap(index, index / 2);
		}
		else
			break;
		index /= 2;
	}
	cnt++;

}

void deque() {
	if (cnt == 1) {
		return;
	}
	
	printf("%d : %s\n", hip[1].value, hip[1].key);

	hip[1] = hip[cnt-1];

	int index = 1;

	while (index <= cnt / 2) {
		if (hip[index].value < hip[index * 2].value || hip[index].value < hip[index * 2 + 1].value) {
			if (hip[index * 2 + 1].value < hip[index * 2].value) {
				swap(index, index * 2);
				index *= 2;
			}
			else {
				swap(index, index * 2 + 1);
				index = index * 2 + 1;
			}
		}
		else
			break;
	}
	cnt--;
}






int main() {
	tnode *root;                //declare a tnode
	char word[MAXWORD];

	for (int i = 1; i < 256; i++) {
		hip[i].value = -1;
	}

	FILE*fp = fopen("obama.txt", "rt");
	int len;
	int i;
	int pt = 0;
	root = NULL;
	while (fscanf(fp, "%s", word) != EOF) {//get a word
		len = strlen(word);
		char * real = new char[len];
		for (i = 0; i < len; i++) { //if it is an english word
			tolower(word[i]);
			if (isalpha(word[i])) {

				real[pt++] = tolower(word[i]);
			}
		}
		
		real[pt] = NULL;
		if (pt != 0)
			root = addtree(root, real);    //add tree
			pt = 0;
		}
	
	treeprint(root); //print the whole tree nodes

	printf("\n\n");

	
	for (i = 0; i<10; i++) {
		deque();
	}

	system("pause");
	return 0;
}