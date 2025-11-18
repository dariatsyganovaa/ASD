#ifndef LIB_ALGORITHMS_ALGORITHMS_H_
#define LIB_ALGORITHMS_ALGORITHMS_H_

#include <iostream>
#include <cstddef>
#include "../lib_matrix/matrix.h"
#include "../lib_stack/stack.h"
#include "../lib_list/list.h"

int local_minimum_of_a_matrix(Matrix<int>& matrix);

bool check_breckets(std::string str);

void read_expression(std::string expression);

template <class T>
bool is_looped(List<T>* list) {
	for (auto it1 = (*list).begin(), it2 = (*list).begin(); it1 != (*list).end(), it2 != (*list).end(); ) {
		++it1;
		++it2; ++it2;

		if (it1 == it2) {
			return true;
			break;
		}
		else {
			return false;
		}

	}
	/*auto it1 = list.begin(), it2 = list.begin();
	while (it1 != list.end() && it2 != list.end()) {

		++it1;
		++it2; ++it2;
		if (it1 == it2) {
			return true;
		}
	}
	return false;*/
}



#endif  // LIB_ALGORITHMS_ALGORITHMS_H_