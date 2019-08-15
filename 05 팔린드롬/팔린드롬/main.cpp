#include "megadeth.h"

using namespace std;

int main() {
	int lines;
	int i, j;
	int h = 0;
	stack real;
	stack*access = &real;

	char reading[50];
	char c;
	char d;
	char origin[50];

	FILE*fp = fopen("test.txt", "rt");
	fscanf(fp, "%d", &lines);
	fgetc(fp);

	int here = ftell(fp);

	char** they = (char**)malloc(sizeof(char*)*lines);

	for (i = 0; i < lines; i++) {
		*(they + i) = (char*)malloc(sizeof(char) * 50);
		fgets(*(they + i), sizeof(char) * 50, fp);
		*(*(they+i)+strlen(*(they+i))-1) = '\0';
	}

	fseek(fp, here, SEEK_SET);

	for (i = 0; i < lines; i++) {
		access = real.init();
		while ((c = fgetc(fp)) != '\n') {
			if (c == EOF)
				break;
			if (((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))) {
				if (c >= 'A' && c <= 'Z')
					c += 32;
				origin[h] = c;
				real.push(access, c);
				h++;
			}

			else if ((c & 0x80) != 0) {
				origin[h] = c;
				h++;
				d = fgetc(fp);
				origin[h] = d;
				h++;

				real.push(access, d);
				real.push(access, c);
			}
		}

		origin[h] = '\0';
		cout << "Is \"";
		cout << *(they + i);
		cout << "\" a palindrome?" << endl;

		for (j = 0; j < h; j++)
			reading[j] = real.pop(access);

		reading[j] = '\0';

		if (strcmp(reading, origin) == 0) {
			cout << "Yes. ";
			cout << "Proof : " << reading << endl << endl;
		}

		else {
			cout << "No. Proof : ";
			cout << reading << endl << endl;;
		}

		h = 0;
	}

	return 0;
}