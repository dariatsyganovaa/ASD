#define SKIPLIST
#ifdef SKIPLIST

#include <iostream>
#include <iomanip>
#include "../lib_skiplist/skiplist.h"

int main() {
    /*SkipList<std::string, int> list(8);

    list.insert("five", 5);
    list.insert("two", 2);
    list.insert("eight", 8);
    list.insert("one", 1);
    list.insert("seven", 7);*/

    SkipList<int, std::string> list(8);

    list.insert(5, "five");
    list.insert(2, "two");
    list.insert(8, "eight");
    list.insert(1, "one");
    list.insert(7, "seven");

    list.print();

    return 0;
}

#endif  // SKIPLIST
