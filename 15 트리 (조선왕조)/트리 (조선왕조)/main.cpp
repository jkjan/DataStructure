#include "choseon_dynasty.h"
#include "kingstack.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
자료에서 고종이 인조의 직계후손으로 입력됐으나
고종은 영조의 아들인 정조의 이복동생(은신군)의 아들(남연군)의 아들(흥선대원군)의 아들로
자료의 규칙(서자 제외한 직계)에 맞게 영조의 아들로 바꿨습니다.
*/

char** cutStrings(int n, char* string) {
	char** cut = new char*[n];
	for (int i = 0; i < n; i++) {
		cut[i] = new char[7];
	}

	int len = strlen(string);

	for (int i = len - 1; i >= 0; i--) {
		if (string[i] == ' ') {
			strcpy(cut[(n--)-1], &string[i+1]);
			string[i] = '\0';
		}
	}

	strcpy(cut[(n--) - 1], string);

	return cut;
}

stack* dynasty;
int kingcnt;
extern char bestKing[7];
extern int kingmade;
extern int upToTwo;

int main() {
	kings* taejo = new kings;
	dynasty = new stack;
	dynasty->init();

	taejo->init();
	
	FILE* fp = fopen("조선왕조.txt", "rt");
	
	char buffer[256];
	int nchildren = 0;
	int len;
	
	while (fscanf(fp, " %[^\n]", buffer) != EOF) {
		//printf("%s \n", buffer);
		for (int i = 0; i < strlen(buffer); i++) {
			if (buffer[i] == ' ')
				nchildren++;
		}

		taejo->insert(nchildren, cutStrings(nchildren+1, buffer));
		nchildren = 0;
	}

	printf("조선의 왕을 순서대로 출력하시오. : \n");
	taejo->treeprint();
	printf("\n\n");

	printf("조선의 왕을 역순으로 출력하시오. : \n");
	while (!dynasty->is_empty()) {
		printf("%s\n", dynasty->pop());
	}

	printf("\n\n");

	printf("조선의 왕은 모두 몇 명인가? \n");
	printf("%d", kingcnt);

	printf("\n\n");

	printf("조선의 왕 중에서 인조의 후손은 누구누구인가?\n");
	char name[7] = "인조";
	taejo->get_daddy(name)->enemies->next->king->treeprint();
	

	//taejo->get_children((char*)"인조");

	printf("\n\n");

	printf("직계 후손이 왕이 되지 못한 왕은 누구누구인가?\n");
	//-> 자료에 자식이 없는 사람 (왕이 아닌 자식은 자료에 없다)
	taejo->whosNotKing();

	printf("\n\n");

	printf("직계 후손이 왕이 된 수가 가장 많은 왕은 누구인가?\n");
	//자료에 주어진 모든 이들이 왕이 됨
	taejo->theBestKingMaker();
	printf("%s", bestKing);

	printf("\n\n");


	printf("정종의 형제로 조선의 왕이 된 사람은 누구인가?\n");
	taejo->get_enemies((char*)"정종");

	printf("\n\n");


	printf("순종의 직계 선조를 모두 출력하시오.\n");
	strcpy(name, "순종");
	while (strcmp(name, "태조") != 0) {
		strcpy(name, taejo->get_daddy(name)->name);
		printf("%s\n", name);
	}
	printf("\n\n");

	printf("직계 후손이 2명 이상 왕이 된 왕은 몇 명인가?\n");
	printf("%d명\n", upToTwo);
	printf("\n\n");

	printf("예종은 태종의 몇 대 후손인가?\n");
	strcpy(name, "예종");
	int son = 0;
	while (strcmp(name, "태종") != 0) {
		strcpy(name, taejo->get_daddy(name)->name);
		son++;
	}
	printf("%d대 후손\n", son);

	printf("\n\n");
	fclose(fp);
	delete(taejo);
	delete(dynasty);
}