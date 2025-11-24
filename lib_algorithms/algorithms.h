#ifndef LIB_ALGORITHMS_ALGORITHMS_H_
#define LIB_ALGORITHMS_ALGORITHMS_H_

#include <iostream>
#include <cstddef>
#include "../lib_matrix/matrix.h"
#include "../lib_stack/stack.h"
#include "../lib_list/list.h"
#include "../lib_dsu/dsu.h"

int local_minimum_of_a_matrix(Matrix<int>& matrix);

bool check_breckets(std::string str);

void read_expression(std::string expression);

int count_of_islands(Matrix<int>& islands);

template <class T>
bool is_looped_rabbit_turtle(List<T>* list) {
	if (list->is_empty()) {
		return false;
	}

	auto turtle = list->begin();
	auto rabbit = list->begin();

	while (rabbit != list->end() && ++rabbit != list->end()) {
		++turtle;
		++rabbit;
		if (turtle == rabbit) {
			return true;
		}
	}
	return false;
}

template <class T>
bool is_looped(List<T>* list) {
	Node<T>* cur = list->head();
	Node<T>* prev = nullptr;
	Node<T>* next = nullptr;
	Node<T>* start = list->head();

	while (cur != nullptr) {
		next = cur->next;
		cur->next = prev;
		prev = cur;
		cur = next;
		if (cur == start) {
			return true;
		}
	}
	return false;
}

#endif  // LIB_ALGORITHMS_ALGORITHMS_H_