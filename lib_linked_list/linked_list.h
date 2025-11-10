#ifndef LIB_LINKED_LIST_LINKED_LIST_H_
#define LIB_LINKED_LIST_LINKED_LIST_H_

#pragma once
#include "..\lib_linked_list\linked_list.h"
#include <stdexcept>

template <class T>
struct Node {
	T data;
	Node<T>* next;
	Node<T>* prev;

	Node(T value, Node<T>* prev_ = nullptr, Node<T>* next_ = nullptr) : data(value), prev(prev_), next(next_){}
};

template<class T>
class LinkedList {
	Node<T>* _head, *_tail;
	size_t _size;
public:
	LinkedList();
	LinkedList(const LinkedList<T>&);
	~LinkedList();

	class Iterator {
		Node<T>* _cur;
	public:
		Iterator() : _cur(nullptr) {}
		Iterator(Node<T>* node) : _cur(node) {}

		Iterator& operator=(const Node<T>& other) {
			_cur = other._cur;
			return *this;
		}

		Iterator& operator++() { //++it
			_cur = _cur->next;
			return *this;
		}

		Iterator operator++(int) {//it++
			Iterator temp = *this;
			++(*this);
			return temp;
		}

		Iterator& operator--() { //--it
			_cur = _cur->prev;
			return *this;
		}

		Iterator operator--(int) {//it--
			Iterator temp = *this;
			--(*this);
			return temp;
		}

		bool operator== (const Iterator& other) {
			return _cur == other._cur;
		}

		bool operator!= (const Iterator& other) {
			return !(*this == other);
		}

		T& operator*() const {
			return _cur->data;
		}
	};

	Iterator begin() const {
		return Iterator(_head);
	}

	Iterator end() const {
		return Iterator(nullptr);
	}

	Node<T>* head() const;
	Node<T>* tail() const;
	size_t size() const;

	bool is_empty() const;

	void push_back(const T& value) noexcept;
	void push_front(const T& value) noexcept;
	void insert(size_t pos, const T& value);
	void insert(Node<T>* node, const T& value);

	void pop_back();
	void pop_front();
	void erase(size_t pos);
	void erase(Node<T>* node);
}; 

template <class T>
LinkedList<T>::LinkedList() : _head(nullptr), _tail(nullptr), _size(0) {}

template <class T>
LinkedList<T>::LinkedList(const LinkedList<T>& other) : _head(nullptr), _tail(nullptr), _size(0) {
	if (other.is_empty()) {
		return;
	}

	LinkedList<int>::Iterator it;
	for (it = other.begin(); it != other.end(); it++) {
		push_back(*it);
	}
}

template <class T>
LinkedList<T>::~LinkedList() {
	Node<T>* cur = _head;
	Node<T>* next_node = nullptr;
	while (cur != nullptr) {
		next_node = cur->next;
		delete cur;
		cur = next_node;
	}
	_head = _tail = nullptr;
	_size = 0;
}

template <class T>
Node<T>* LinkedList<T>::head() const {
	return _head;
}

template <class T>
Node<T>* LinkedList<T>::tail() const {
	return _tail;
}

template <class T>
size_t LinkedList<T>::size() const {
	return _size;
}

template <class T>
bool LinkedList<T>::is_empty() const {
	return _size == 0;
}

template <class T>
void LinkedList<T>::push_front(const T& value) noexcept {
	Node<T>* node = new Node<T>(value);
	if (is_empty()) {
		_head = _tail = node;
	}
	else {
		node->next = _head;
		_head->prev = node;
		_head = node;
	}
	_size++;
}

template <class T>
void LinkedList<T>::push_back(const T& value) noexcept {
	Node<T>* node = new Node<T>(value);
	if (is_empty()) {
		_head = _tail = node;
	}
	else {
		_tail->next = node;
		node->prev = _tail;
		_tail = node;
	}	
	_size++;
}

template <class T>
void LinkedList<T>::insert(Node<T>* node, const T& value) {
	if (node == nullptr) {
		throw std::invalid_argument("Node can't be nullptr!");
	}
	if (is_empty()) {
		throw std::invalid_argument("List is empty!");
	}

	Node<T>* new_node = new Node<T>(value, node, node->next);

	node->next = new_node;
	if (new_node->next != nullptr) {
		new_node->next->prev = new_node;
	}
	
	if (node == _tail) {
		_tail = new_node;
	}
	_size++;
}

template <class T>
void LinkedList<T>::insert(size_t pos, const T& value) {
	if (pos > _size + 1 || pos < 1) {
		throw std::out_of_range("Position is out of bounds!");
	}

	if (pos == 1) {
		push_front(value);
		return;
	}

	if (pos == _size + 1) {
		push_back(value);
		return;
	}

	Node<T>* cur = _head;
	for (size_t i = 1; i < pos - 1; i++) {
		cur = cur->next;
	}

	insert(cur, value);
}

template <class T>
void LinkedList<T>::pop_front() {
	if (is_empty()) {
		throw std::out_of_range("Can't pop from an empty list!");
	}

	if (_head == _tail) {
		delete _head;
		_head = nullptr;
		_tail = nullptr;
		_size = 0;
		return;
	}

	Node<T>* cur = _head;
	_head = _head->next;
	_head->prev = nullptr;
	delete cur;
	
	_size--;
}

template <class T>
void LinkedList<T>::pop_back() {
	if (is_empty()) {
		throw std::out_of_range("Can't pop from an empty list!");
	}

	if (_head == _tail) {
		delete _head;
		_head = nullptr;
		_tail = nullptr;
		_size = 0;
		return;
	}

	Node<T>* cur = _tail;
	_tail = _tail->prev;
	_tail->next = nullptr;
	delete cur;

	_size--;
}

template <class T>
void LinkedList<T>::erase(Node<T>* node) {
	if (node == nullptr) {
		throw std::invalid_argument("Node can't be nullptr!");
	}

	if (is_empty()) {
		throw std::invalid_argument("List is empty!");
	}

	if (node == _head) {
		pop_front();
		return;
	}

	if (node == _tail) {
		pop_back();
		return;
	}

	node->prev->next = node->next;
	node->next->prev = node->prev;

	delete node;
	_size--;
}

template <class T>
void LinkedList<T>::erase(size_t pos) {
	if (is_empty()) {
		throw std::out_of_range("List is empty!");
	}
	if (pos > _size || pos < 1) {
		throw std::out_of_range("Position is out of bounds!");
	}

	if (pos == 1) {
		pop_front();
		return;
	}

	if (pos == _size) {
		pop_back();
		return;
	}

	Node<T>* cur = _head;
	for (size_t i = 1; i < pos; i++) {
		cur = cur->next;
	}

	erase(cur);
}


#endif //LIB_LINKED_LIST_LINKED_LIST_H_