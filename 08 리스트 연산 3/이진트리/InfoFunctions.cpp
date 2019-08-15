#include "MinIsTheBestProfInTheWorld.h"

void sinfo::infoprint() {
	cout << this->name << ' ' <<
		this->sex << ' ' <<
		this->loc << ' ' <<
		this->major << ' ' <<
		this->score << ' ' <<
		this->height << ' ' <<
		this->weight << endl;
}

sinfo* sinfo::setInfo(char* name,
	char sex,
	char* loc,
	char* major,
	float score,
	int height,
	int weight) {
	strcpy(this->name, name);
	this->sex = sex;


	strcpy(this->loc, loc);
	strcpy(this->major, major);
	this->score = score;
	this->height = height;
	this->weight = weight;

	return this;
}

char* sinfo::getname() {
	return this->name;
}