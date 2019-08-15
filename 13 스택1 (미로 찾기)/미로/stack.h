//typedef int block;

class block {
public:
	int wall;
	int isWay;
};

class pos {
public :
	int x;
	int y;
	int posCheck(int x, int y);
};

class skein {
private :
	pos* stack;
	int size;
	int cnt;
public :
	void init(int n);
	void push(int x, int y);
	pos* pop();
	pos* top();
	int isFull();
	int isEmpty();
};