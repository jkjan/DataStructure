#include "MinTheGreat.h"
link * link::create() {
	link* real = (link*)malloc(sizeof(link));
	real->nodes = NULL;
	real->cnt = 0;
	return real;
}

int link::line(istream& fp) {
	int lines = 0;
	char enter[255];

	while (!fp.eof()) {
		fp.getline(enter, 255);
		lines++;
	}
	cnt = lines;
	return lines;
}

node* link::load(istream& fp, link*list, int n) {
	list->cnt = n;

	node*head = list->nodes;
	node*cur = head;

	int i;

	for (i = 0; i < n; i++) {
		node*newnode = (node*)malloc(sizeof(node));
		(newnode->library) = (lib*)malloc(sizeof(lib));
		newnode->rnext = NULL;
		newnode->lnext = NULL;

		fp >> newnode->library->name >> newnode->library->sex >>
			newnode->library->loc >> newnode->library->major >>
			newnode->library->score >> newnode->library->height >>
			newnode->library->weight;

		if (cur == NULL) {
			cur = newnode;
			list->nodes = cur;
			head = cur;
		}

		else {
			cur->rnext = newnode;
			newnode->lnext = cur;
			cur = cur->rnext;
		}
	}
	cur->rnext = NULL;

	//정렬
	cur = head;
	lib temp;
	
	for (i=0; i<n-2; i++ ){
		while (cur->rnext != NULL) {
			if (strcmp(cur->library->name, cur->rnext->library->name) > 0) {
				temp = *(cur->library);
				*(cur->library) = *(cur->rnext->library);
				*(cur->rnext->library) = temp;
			}
			cur = cur->rnext;
		}
		cur = head;
	}
	return list->nodes;
}

//전체 출력
void link::print(link*list) {
	cout << fixed;
	cout.precision(2);

	node * cur = list->nodes;

	for (int i = 0; i < list->cnt; i++) {
		cout << (cur->library)->name << ' '
			<< cur->library->sex << ' '
			<< cur->library->loc << ' '
			<< cur->library->major << ' '
			<< cur->library->score << ' '
			<< cur->library->height << ' '
			<< cur->library->weight << endl;

		cur = cur->rnext;
	}
	printf("\n");
}

int link::insert(link*list, node* data) {
	node*cur = list->nodes;

	//추가하려는 학생이 맨 앞에 와야할 때
	if (strcmp(list->nodes->library->name, data->library->name) > 0) {
		data->rnext = list->nodes;
		list->nodes->lnext = data;
		list->nodes = data;
	}

	else {
		while (cur->rnext != NULL) {
			if (strcmp(cur->library->name, data->library->name) > 0)
				break;
			cur = cur->rnext;
		}
		if (cur->rnext != NULL) {
			data->rnext = cur->rnext;
			cur->rnext = data;

			data->lnext = cur;
			data->rnext->lnext = data;
		}

		//맨 끝에 올 때
		else {
			cur->rnext = data;
			data->lnext = cur;
		}
	}

	cout << ' ' << data->library->name << endl;
	cout << data->library->name << " 학생을 저장하였습니다.\n" << endl;
	list->cnt++;
	
	return 1;
}

int link::remove(link*list, char* rmv) {
	node*pos;

	if ((pos = search(rmv, list))!= NULL) {
		pos->lnext->rnext = pos->rnext;
		pos->rnext->lnext = pos->lnext;
		free(pos);
		list->cnt--;
		
		return 1;
	}

	return 0;
}

node* link::search(char*sch, link*list) {
	node*cur = list->nodes;

	while (cur->rnext != NULL) {
		if (strcmp(cur->library->name, sch) == 0)
			return cur;
		cur = cur->rnext;
	}

	return NULL;
}


int link::save(ofstream&fp, link*list) {

	node*cur = list->nodes;

	for (int i = 0; i < list->cnt; i++) {
		fp << cur->library->name << ' '
			<< cur->library->sex << ' '
			<< cur->library->loc << ' '
			<< cur->library->major << ' '
			<< cur->library->score << ' '
			<< cur->library->height << ' '
			<< cur->library->weight << endl;

			cur= cur->rnext;
	}

	//마지막 개행 제거
	fp.seekp(-1, ios::end);
	fp << 0;

	return 0;
}

//파일 유무 확인
bool link::verify(const std::string& filename)
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
