#include "MinTheGreat.h"
lib * info::create(info* list, int n) {
	list->library = (lib *)malloc(sizeof(lib) * n);
	list->num = n;
	list->cnt = 0;
	return library;
}

int info::line(istream& fp) {
	int lines = 0;
	char enter[255];

	while (!fp.eof()) {
		fp.getline(enter, 255);
		lines++;
	}
	num = lines;
	return lines;
}

lib* info::load(istream& fp, info*list, int n) {
	int i = 0;
	int j;
	list->cnt = n;
	
	while (i < list->num) {
		fp >> ((list->library)+i)->name >> ((list->library) + i)->sex >> 
			  ((list->library) + i)->loc >> ((list->library) + i)->major >> 
			  ((list->library) + i)->score >> ((list->library) + i)->height >> 
			  ((list->library) + i)->weight;
		i++;
	}

	//정렬
	lib temp;
	for (i = 0; i < (list->num)-2; i++) {
		for (j = 0; j < (list->num)-i - 1; j++) {
			if (strcmp(((list->library) + j)->name, ((list->library) + j+1)->name) > 0) {
				temp = *((list->library) + j);
				*(list->library + j) = *(list->library + j + 1);
				*(list->library + j + 1) = temp;
			}
		}
	}

	return (list->library);
}

//전체 출력
void info::print(info*list) {
	cout << fixed;
	cout.precision(2);
	for (int i = 0; i < list->cnt; i++) {
		cout << (list->library + i)->name << ' ' 
			<< (list->library + i)->sex << ' ' 
			<< (list->library + i)->loc << ' ' 
			<< (list->library + i)->major << ' ' 
			<< (list->library + i)->score << ' ' 
			<< (list->library + i)->height << ' ' 
			<< (list->library + i)->weight << endl;
	}
	printf("\n");
}

int info::insert(info*list, lib* data) {
	int i;

	if (list->cnt < 100 && list->cnt != 0) {            //data가 꽉 차지 않았다면
		if (strcmp((list->library)->name, data->name) > 0)  //만약 처음에 들어가야 할 놈이면
			i = -1;

		else {
			for (i = 0; i < list->cnt; i++) {
				if (strcmp((list->library + i)->name, data->name) > 0)
					break;
			}
		}

		for (int j =0; j < list->cnt -i; j++) //i 뒤에 있는 놈들을 다 한 칸씩 미루기
			*(list->library +list->cnt -j) = *(list->library + list->cnt -j -1);

		if(i<0)
			*(list->library) = *data;

		else
			*(list->library + i) = *data;

		list->cnt++;
		cout << ' '<< data->name << endl;
		cout << data->name << " 학생을 저장하였습니다.\n" << endl;

		return 1;
	}

	else if (list->cnt >= 100) {
		cout << "다 찼습니다." << endl;
		return 0;
	}
	else {
		*(list->library) = *data;
		list->cnt++;
		return 1;
	}
}

int info::remove(info*data, char* rmv) {
	int i;
	int index;
	if ((index = search(rmv, data, 0, 0, data->cnt-1)) != -1) {
		for (i = 0; i < data->cnt - index - 1; i++)
			*((data->library)+index + i)= *((data->library)+index + i + 1);
		data->cnt--;
		return 1;
	}
	
	return 0;
}

int info::search(char*sch, info*data, int n, int first, int last) {
	int i;
	if (first == last) {
		return (strcmp(((data->library) + first)->name, sch) == 0) ? first : -1;
	}
	int mid = (first + last) / 2;
	if (strcmp(sch, (data->library+mid)->name)==0)
		return mid;
	else if (strcmp(sch, (data->library+mid)->name) < 0)
		return search(sch, data, n, first, mid - 1);
	else
		return search(sch, data, n, mid + 1, last);
}

int info::save(ofstream&fp, info*list) {
	for (int i = 0; i < list->cnt; i++) {
		fp << (list->library + i)->name << ' '
			<< (list->library + i)->sex << ' '
			<< (list->library + i)->loc << ' '
			<< (list->library + i)->major << ' '
			<< (list->library + i)->score << ' '
			<< (list->library + i)->height << ' '
			<< (list->library + i)->weight << endl;
	}

	//마지막 개행 제거
	fp.seekp(-1, ios::end);
	fp << 0;

	return 0;
}

//파일 유무 확인
bool info::verify(const std::string& filename)
{
	struct stat buf;
	if (stat(filename.c_str(), &buf) != -1)
	{
		cout <<" has been successfully opened\n" << endl;
		return true;
	}
	cout << "Failed to open the file\n" << endl;
	return false;
}