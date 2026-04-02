#ifndef LIB_PRIORITY_QUEUE_PRIORITY_QUEUE_H_
#define LIB_PRIORITY_QUEUE_PRIORITY_QUEUE_H_

#pragma once
#include "..\lib_heap\heap.h"

template<class T>
struct QueueNode {
	int priority;
	T data;
	int order;

	QueueNode() : priority(0), order(0), data(0) {}
	QueueNode(int pr, int ord, const T& value) : priority(pr), order(ord), data(value) {}

	bool operator>(const QueueNode& other) const {
		if (priority == other.priority) {
			return order > other.order; 
		}
		return priority > other.priority;
	}

	bool operator<(const QueueNode& other) const {
		return other > *this;
	}
};

template <typename T>
class PriorityQueue {
	Heap<QueueNode<T>> queue;
	int next_order = 0;
public:
	PriorityQueue() = default;
	bool is_empty() const noexcept;
	size_t size() const noexcept;
	T top();
	void insert(int prior, const T& value);
	T pop();
	void print();
};

template<typename T>
size_t PriorityQueue<T>::size() const noexcept {
	return queue.size();
}

template<typename T>
bool PriorityQueue<T>::is_empty() const noexcept {
	return queue.size() == 0;
}

template<typename T>
T PriorityQueue<T>::top() {
	if (is_empty()) { throw std::runtime_error("PriorityQueue::top: queue is empty!"); }
	return queue.get_min().data;
}

template<typename T>
void PriorityQueue<T>::insert(int prior, const T& value) {
	QueueNode<T> elem(prior, next_order++, value);
	queue.insert(elem);
}

template<typename T>
T PriorityQueue<T>::pop() {
	if (is_empty()) { throw std::runtime_error("PriorityQueue::pop: queue is empty!"); }
	return queue.extract_min().data;
}

template<typename T>
void PriorityQueue<T>::print() {
	queue.print_heap();
}

#endif