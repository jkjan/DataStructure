#include <stdio.h>
#include <stdlib.h>

//학생 정보를 저장할 구조체 선언
typedef struct _info {
	char name[7];
	char sex;
	char loc[7];
	char major[13];
	float score;
	int height;
	int weight;

}info;

int main() {
	FILE*fp = fopen("list.txt", "rt");
	char enter;
	int line = 0;
	int i;

	//파일 열기 성공 여부 확인 메시지
	if (fp)
		puts("The file has been successfully opened\n");
	else
		puts("Failed to open the file\n");

	//파일의 줄 수 세기
	while ((enter = fgetc(fp)) != EOF)
		if (enter == '\n')
			line++;
	line += 1; // n줄일 시 '\n'의 개수는 n-1이므로 
	

	//동적 메모리 할당하기
	info* smu = (info*)malloc(sizeof(info)*line);

	rewind(fp);

	//입력 받기
	for (i = 0; i < line; i++) {
		fscanf(fp, "%s %c %s %s %f %d %d", (smu+i)->name, &(smu+i)->sex, (smu+i)->loc,
			(smu+i)->major, &(smu+i)->score, &(smu+i)->height, &(smu+i)->weight);
	}

	//출력하기
	for (i = 0; i < line; i++) {
		printf("%s %c %s %s %.2f %d %d\n", (smu+i)->name, (smu+i)->sex, (smu+i)->loc,
			(smu+i)->major, (smu+i)->score, (smu+i)->height, (smu+i)->weight);
	}

	free(smu);
	fclose(fp);

	return 0;
}