#ifndef CHOSEON
#define CHOSEON

class kings;

struct _enemy {
	kings* king;
	_enemy *next;
};

typedef struct _enemy enemy;

class kings {
public:
	char name[7];
	int num;
	enemy* enemies;

public:
	void init(char *name);
	void init();
	bool is_empty();
	int insert(int nchildren, char** names);
	enemy* get_children(char* name);  //
	kings* get_daddy(char* name);
	char** get_enemies(char* name);
	void treeprint();
	void whosNotKing();
	void theBestKingMaker();
	//void descendents(char* name);
};

#endif