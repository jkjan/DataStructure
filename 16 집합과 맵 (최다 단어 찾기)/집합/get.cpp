#include "maximumeffort.h"
#include <ctype.h>

#define BUFSIZE 100

char buf[BUFSIZE];
int bufp = 0;

int getch() {
	return (bufp > 0) ? buf[--bufp] : getchar();  //if buf isnt empty, pop buf. or get a new character
}

void ungetch(int c) {
	if (bufp >= BUFSIZE)
		printf("ungetch : too many characters\n");  //if there re more than 100 characters in buf
	else
		buf[bufp++] = c;           //push c into buff
}

int getword(char *word, int lim) {
	int c;
	char *w = word;

	while (isspace(c = getch()))  //wont do anything if c is space
		;
	if (c != EOF)
		*w++ = c;      //get word
	if (!isalpha(c)) {     //if c meets something that is not an english character (space, number, etc...)
		*w = '\0';     //wrap w, pack it
		return c;
	}

	for (; --lim > 0; w++)     //till it meets its limit
		if (!isalnum(*w = getch())) {   //get character
			ungetch(*w);
			break;
		}
	*w = '\0';   //wrap it
	return word[0];
}