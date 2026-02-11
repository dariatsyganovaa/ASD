#ifndef LIB_QUEUE_ON_LIST_QUEUE_ON_LIST_H_
#define LIB_QUEUE_ON_LIST_QUEUE_ON_LIST_H_

#pragma once
#include "..\lib_list\list.h"

template <typename T> class QueueOnList;

template<class T>
class QueueOnList {
	List<T> _data;
	size_t _cur_size = 0;
	size_t _max_size = -1;
public:
	QueueOnList() = default;
	QueueOnList(size_t size);
	QueueOnList(const QueueOnList<T>&);
	void push(T val);
	void pop();
	T head() const;
	T tail() const;
	inline bool is_empty() const noexcept;
	inline bool is_full() const noexcept;
	void clear() noexcept;
};

template<class T>
QueueOnList<T>::QueueOnList(size_t size) : _max_size(size) {}

template<class T>
QueueOnList<T>::QueueOnList(const QueueOnList<T>& other) : _data(other._data) {}

template<class T>
T QueueOnList<T>::head() const {
	if (is_empty()) {
		throw std::out_of_range("Can't get head from empty queue!");
	}
	return _data.head()->data;
}

template<class T>
T QueueOnList<T>::tail() const {
	if (is_empty()) {
		throw std::out_of_range("Can't get tail from empty queue!");
	}
	return _data.tail()->data;
}

template<class T>
void QueueOnList<T>::push(T val) {
	_data.push_back(val);
}

template<class T>
void QueueOnList<T>::pop() {
	if (is_empty()) {
		throw std::out_of_range("Can't pop from empty queue!");
	}
	_data.pop_front();
}

template<class T>
inline bool QueueOnList<T>::is_empty() const noexcept {
	return _data.is_empty();
}

template<class T>
void QueueOnList<T>::clear() noexcept {
	while (!_data.is_empty()) {
		_data.pop_front();
	}
}

#endif //LIB_QUEUE_ON_LIST_QUEUE_ON_LIST_H_