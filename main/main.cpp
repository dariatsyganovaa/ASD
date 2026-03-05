#define SKIPLIST
#ifdef SKIPLIST

#include <iostream>
#include <iomanip>
#include "../lib_skiplist/skiplist.h"

int main() {
    SkipList<int, std::string> sl(8); 

    sl.insert(5, "five");
    sl.insert(2, "two");
    sl.insert(8, "eight");
    sl.insert(1, "one");
    sl.insert(7, "seven");

    sl.print();

    std::string* val = &sl.found_pos(7);
    if (val != nullptr) {
        std::cout << "found: " << *val << "\n";
    }

    return 0;
}

#endif  // SKIPLIST
