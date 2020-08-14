#include <iostream>
#include "deque.h"

int main() {
    deque<int> test;
    test.push_back(3);
    test.push_back(5);
    test.push_back(6);
    printf("%d\n", test.front());
    printf("%d\n", test.back());

    return 0;
}