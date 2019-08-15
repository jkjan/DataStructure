class stack {
private :
	char** kings;
	int size;
	int cnt;
public:
	void init();
	void push(char* name);
	char* pop();
	char* top();
	int is_empty();
	int is_full();
};