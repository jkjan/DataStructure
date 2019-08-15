#include "MinIsTheBestProfInTheWorld.h"
#include <fstream>

int main() {
	node* ironman = new node;

	char command[10];
	int i, lines, students;

	char name[7];
	char sex;
	char loc[7];
	char major[13];
	float score;
	int height;
	int weight;


	ifstream in, list;
	in.open("input.txt");
	cout << "input.txt";
	verify("input.txt");

	lines = line(in);  //�� ���� �� ���� �ý��ϴ�.
	in.clear();
	in.seekg(0);

	for (i = 0; i < lines; i++) {
		in >> command;

		if (strcmp(command, "CREATE") == 0) {
			ironman = NULL;
		}

		else if (strcmp(command, "LOAD") == 0) {
			cout << command << endl;
			in >> command;
			list.open(command);
			cout << command;
			verify(command);

			students = line(list);

			list.clear();
			list.seekg(0);

			for (int j = 0; j < students; j++) {
				sinfo* info = new sinfo;
				list >> name >> sex
					>> loc >> major
					>> score >> height
					>> weight;

				info= info->setInfo(name, sex, loc, major, score, height, weight);

				ironman = ironman->addtree(ironman, info);
			}

			cout << "list.txt�� �������� �����߽��ϴ�.\n" << endl;
		}

		else if (strcmp(command, "PRINT") == 0) {
			cout << command << endl;
			cout << "��ü ������ ����մϴ�.\n" << endl;
			ironman->treeprint();
			cout << '\n';
		}

		else if (strcmp(command, "INSERT") == 0) {
			cout << command << endl;

			sinfo* info = new sinfo;
			in >> name >> sex
				>> loc >> major
				>> score >> height
				>> weight;

			info = info->setInfo(name, sex, loc, major, score, height, weight);

			ironman = ironman->addtree(ironman, info);
			cout << info->getname() << " �л��� �߰��߽��ϴ�.\n" << endl;
		}

		else if (strcmp(command, "DELETE") == 0) {
			cout << command;
			in >> command;
			cout << ' ' << command << endl;

			if (ironman->remove(ironman, command) != 0) {
				cout << command << " �л��� �����մϴ�.\n" << endl;
			}

			else
				cout << "������ ���� �����ϴ�." << endl << endl;

		}

		else if (strcmp(command, "SEARCH") == 0) {
			cout << command;
			in >> command;
			cout << ' ' << command << endl;
			cout << command << " �л��� �����Դϴ� : " << endl;

			getReturn* index = NULL;
			if ((index = ironman->search(command)) != NULL) {
				if (index->lr == 1)
					index->searched->lc->info->infoprint();
				else if (index->lr == 0)
					index->searched->rc->info->infoprint();
				else
					index->searched->info->infoprint();
				cout << '\n';
			}

			else
				puts("�л��� �������� �ʽ��ϴ�\n");
		}
	}

	in.close();
	list.close();

	
	delete (ironman);

	return 0;
}