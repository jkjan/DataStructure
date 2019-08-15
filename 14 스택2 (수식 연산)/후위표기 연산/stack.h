#define PLUS -1
#define MINUS -2
#define MULTI -3
#define DIVID -4
#define POWER -5
#define OPEN -6
#define CLOSE -7

class stack {
private:
	double stack[100];
	int cnt;
	int size = 100;
public :
	void init();
	void push(double n);
	double pop();
	double top();
	int isFull();
	int isEmpty();
};