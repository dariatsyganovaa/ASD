#ifndef LIB_ALGORITHMS_ALGORITHMS_H_
#define LIB_ALGORITHMS_ALGORITHMS_H_

#include <iostream>
#include <cstddef>
#include "../lib_matrix/matrix.h"
#include "../lib_stack/stack.h"
#include "../lib_list/list.h"
#include "../lib_dsu/dsu.h"

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
	if (list->is_empty()) return false;

	Node<T>* start = list->head();
	Node<T>* cur = start;
	Node<T>* prev = nullptr;
	Node<T>* next = nullptr;
	bool has_cycle = false;

	while (cur != nullptr) {
		next = cur->next;
		cur->next = prev;
		prev = cur;
		cur = next;

		if (cur == start) {
			has_cycle = true;
			break;
		}
	}

	Node<T>* r_cur = prev;
	Node<T>* r_prev = cur;
	Node<T>* r_next = nullptr;

	while (r_cur != nullptr) {
		r_next = r_cur->next;
		r_cur->next = r_prev;
		r_prev = r_cur;
		r_cur = r_next;
	}

	return has_cycle;
}

template <class T>
Node<T>* find_loop(List<T>* list) {
	if (list->is_empty()) {
		return nullptr;
	}

	Node<T>* turtle = list->head();
	Node<T>* rabbit = list->head();
	bool is_cycle = false;

	while (rabbit != nullptr && rabbit->next != nullptr) {
		turtle = turtle->next;
		rabbit = rabbit->next->next;

		if (turtle == rabbit) {
			is_cycle = true;
			break;
		}
	}

	if (!is_cycle) {
		return nullptr;
	}

	turtle = list->head();
	while (turtle != rabbit) {
		turtle = turtle->next;
		rabbit = rabbit->next;
	}

	return turtle;
}

#endif  // LIB_ALGORITHMS_ALGORITHMS_H_