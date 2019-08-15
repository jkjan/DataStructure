#ifndef sss
#define sss
#include <stdio.h>
#include <string.h>
#include <ctype.h>

struct tnode {     //the tree node
	char *word;   //points to the text
	int count;     //number of occurrences
	struct tnode *left;     //left child
	struct tnode *right;    //right child
};

typedef struct tnode tnode; //to make easy and quick when using this struct next time
#endif