#include <iostream>

using namespace std;

bool verify(const std::string& filename) {
	struct stat buf;
	if (stat(filename.c_str(), &buf) != -1) {
		cout << " has been successfully opened\n" << endl;
		return true;
	}
	cout << "Failed to open the file\n" << endl;
	return false;
}

int line(istream& fp) {
	int lines = 0;
	char enter[255];
	while (!fp.eof()) {
		fp.getline(enter, 255);
		lines++;
	}

	return lines;
}