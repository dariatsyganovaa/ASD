#ifndef LIB_QUEUE_QUEUE_H_
#define LIB_QUEUE_QUEUE_H_

#pragma once÷¸
#include "..\lib_queue\queue.h"

template <typename T> class Queue;

template<class T>
class Queue {
	T* _data;
	size_t _size;
	size_t _head = 0;
	size_t _tail = 0; 
public:
	Queue() = default;
	Queue(size_t);
	Queue(const Queue<T>&);
	~Queue();
	void push(T val);
	void pop();
	T head() const;
	T tail() const;
	inline bool is_full() const noexcept;
	inline bool is_empty() const noexcept;
	void clear() noexcept;
};

template<class T>
Queue<T>::Queue(size_t size) : _size(size + 1), _head(0), _tail(0) {
	if (_size > 0) {
		_data = new T[_size];
	}
}

template<class T>
Queue<T>::Queue(const Queue<T>& other) : _size(other._size), _head(other._head), _tail(other._tail) {
	if (_size > 0) {
		_data = new T[_size];
		for (size_t i = 0; i < _size; i++) {
			_data[i] = other._data[i];
		}
	}
	else {
		_data = nullptr;
	}
}

template<class T>
Queue<T>::~Queue() {
	delete[] _data;
}

template<class T>
T Queue<T>::head() const {
	if (is_empty()) {
		throw std::out_of_range("Can't get head from empty queue!");
	}
	return _data[_head];
}

template<class T>
T Queue<T>::tail() const {
	if (is_empty()) {
		throw std::out_of_range("Can't get tail from empty queue!");
	}
	return _data[(_tail - 1 + _size) % _size];
}

template<class T>
void Queue<T>::push(T val) {
	if (is_full()) {
		throw std::out_of_range("Queue is full!");
	}
	_data[_tail] = val;
	_tail = (_tail + 1) % _size;
}

template<class T>
void Queue<T>::pop() {
	if (is_empty()) {
		throw std::out_of_range("Can't pop from empty queue!");
	}
	_head = (_head + 1) % _size;
}

template<class T>
inline bool Queue<T>::is_full() const noexcept {
	return (_tail + 1) % _size == _head;
}

template<class T>
inline bool Queue<T>::is_empty() const noexcept {
	return _tail == _head;
}

template<class T>
void Queue<T>::clear() noexcept {
	_head = _tail = 0;
}

#endif //LIB_QUEUE_QUEUE_H_