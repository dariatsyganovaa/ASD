#ifndef LIB_STACK_STACK_H_
#define LIB_STACK_STACK_H_

#pragma once
#include "..\lib_tvector\tvector.h"

template <typename T> class Stack;

template<class T>
class Stack {
	TVector<T> _data;
public:
	Stack() = default;
	Stack(size_t);
	Stack(const Stack<T>&);
	void push(T val);
	void pop();
	T top() const;
	inline bool is_empty() const noexcept;
	inline bool is_full() const noexcept;
	void clear() noexcept; 
};

template<class T>
Stack<T>::Stack(size_t size) : _data(0) {
	_data.reserve(size);
}

template<class T>
Stack<T>::Stack(const Stack<T>& other) : _data(other._data){}

template<class T>
void Stack<T>::push(T val) {
	if (is_full()) {
		throw std::out_of_range("Stack is full!");
	}
	_data.push_back_elem(val);
}

template<class T>
void Stack<T>::pop() {
	if (is_empty()) {
		throw std::out_of_range("Can't pop from empty stack!");
	}
	_data.pop_back_elem();
}

template<class T>
T Stack<T>::top() const{
	if (is_empty()) {
		throw std::out_of_range("Can't get top from empty stack!");
	}
	return _data.back();
}

template<class T>
inline bool Stack<T>::is_full() const noexcept {
	return _data.is_full();
}

template<class T>
inline bool Stack<T>::is_empty() const noexcept {
	return _data.is_empty();
}

template<class T>
void Stack<T>::clear() noexcept {
	size_t size = _data.capacity();
	_data.clear();
	_data.reserve(size);
}

#endif //LIB_STACK_STACK_H_