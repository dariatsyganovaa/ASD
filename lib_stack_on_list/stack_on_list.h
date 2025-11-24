#ifndef LIB_STACK_ON_LIST_STACK_ON_LIST_H_
#define LIB_STACK_ON_LIST_STACK_ON_LIST_H_

#pragma once
#include "..\lib_list\list.h"

template <typename T> class StackOnList;

template<class T>
class StackOnList {
	List<T> _data;
public:
	StackOnList() = default;
	StackOnList(size_t size);
	StackOnList(const StackOnList<T>&);
	void push(T val);
	void pop();
	T top() const;
	inline bool is_empty() const noexcept;
	void clear() noexcept;
};

template<class T>
StackOnList<T>::StackOnList(size_t size) : _data(size) {}

template<class T>
StackOnList<T>::StackOnList(const StackOnList<T>& other) : _data(other._data) {}

template<class T>
void StackOnList<T>::push(T val) {
	_data.push_back(val);
}

template<class T>
void StackOnList<T>::pop() {
	if (is_empty()) {
		throw std::out_of_range("Can't pop from empty stack!");
	}
	_data.pop_back();
}

template<class T>
T StackOnList<T>::top() const {
	if (is_empty()) {
		throw std::out_of_range("Can't get top from empty stack!");
	}
	return _data.tail()->data;
}

template<class T>
inline bool StackOnList<T>::is_empty() const noexcept {
	return _data.is_empty();
}

template<class T>
void StackOnList<T>::clear() noexcept {
	while (!_data.is_empty()) {
		_data.pop_back();
	}
}

#endif //LIB_STACK_ON_LIST_STACK_ON_LIST_H_