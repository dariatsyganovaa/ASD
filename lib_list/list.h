#ifndef LIB_LIST_LIST_H_
#define LIB_LIST_LIST_H_

#pragma once
#include "..\lib_list\list.h"
#include <stdexcept>

template <class T>
struct Node {
	T data;
	Node<T>* next;
	Node(const T& value);

};

template <class T>
Node<T>::Node(const T& value) : data(value), next(nullptr) {}


template<class T>
class List {
	Node<T>* _head, * _tail;
	size_t _size; 

public:
	List();
	List(size_t);
	List(const List<T>&);
	~List();

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

	Iterator begin() {
		return Iterator(_head);
	}

	Iterator end() {
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
List<T>::List() : _head(nullptr), _tail(nullptr), _size(0) {}

template <class T>
List<T>::List(size_t size) : _head(nullptr), _tail(nullptr), _size(size) {}

template <class T>
List<T>::List(const List<T>& other) : _head(nullptr), _tail(nullptr), _size(0) {
	if (other.is_empty()) {
		return;
	}

	Node<T>* cur_other = other._head;

	while (cur_other != nullptr) {
		push_back(cur_other->data);
		cur_other = cur_other->next;
	}
}

template <class T>
List<T>::~List() {
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
Node<T>* List<T>::head() const {
	return _head;
}

template <class T>
Node<T>* List<T>::tail() const {
	return _tail;
}

template <class T>
size_t List<T>::size() const {
	return _size;
}

template <class T>
bool List<T>::is_empty() const {
	return _head == nullptr;
}

template <class T>
void List<T>::push_front(const T& value) noexcept {
	Node<T>* node = new Node<T>(value);
	if (is_empty()) {
		_head = node;
		_tail = node;
		_size++;
		return;
	}
	node->next = _head;
	_head = node;
	_size++;
}

template <class T>
void List<T>::push_back(const T& value) noexcept {
	Node<T>* node = new Node<T>(value);
	if (is_empty()) {
		_head = node;
		_tail = node;
		_size++;
		return;
	}
	_tail->next = node;
	_tail = node;
	_size++;
}

template <class T>
void List<T>::insert(Node<T>* node, const T& value) { 
	if (node == nullptr || is_empty()) {
		throw std::invalid_argument("Can't insert after a nullptr!");
	}

	Node<T>* new_node = new Node<T>(value);

	new_node->next = node->next; 
	node->next = new_node; 

	if (node == _tail) {
		_tail = new_node;
	}
	_size++;
}

template <class T>
void List<T>::insert(size_t pos, const T& value) {
	if (pos > _size) {
		throw std::out_of_range("Position is out of bounds!");
	}

	if (pos == 0) {
		push_front(value);
		return;
	}

	if (pos == _size) {
		push_back(value);
		return;
	}

	Node<T>* cur = _head; 
	size_t cur_pos = 0;
	while (cur != nullptr) {
		if (cur_pos == pos - 1) {
			break;
		}
		cur_pos++;
		cur = cur->next;
	}

	Node<T>* new_node = new Node<T>(value);

	new_node->next = cur->next;
	cur->next = new_node;
	_size++;
}

template <class T>
void List<T>::pop_back() {
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
	while (cur->next != _tail) {
		cur = cur->next;
	}

	Node<T>* old_tail = _tail;

	_tail = cur;
	_tail->next = nullptr;

	delete old_tail;
	_size--;
}

template <class T>
void List<T>::pop_front() {
	if (is_empty()) {
		throw std::out_of_range("Can't pop from an empty list!");
	}

	Node<T>* cur = _head;
	_head = _head->next;
	delete cur;

	if (_head == nullptr) {
		_tail = nullptr;
	}
	_size--;
}

template <class T>
void List<T>::erase(Node<T>* node) {
	if (node == nullptr || is_empty()) {
		throw std::invalid_argument("Node can't be nullptr or list empty!");
	}

	if (node == _head) {
		pop_front();
		return;
	}

	Node<T>* cur = _head;

	while (cur != nullptr && cur->next != node) {
		cur = cur->next;
	}

	if (cur == nullptr) {
		throw std::invalid_argument("Node not found in list!");
	}

	cur->next = node->next;

	if (node == tail) {
		_tail = cur;
	}

	delete node;
	_size--;
}

template <class T>
void List<T>::erase(size_t pos) {
	if (pos >= _size || is_empty()) {
		throw std::out_of_range("Position is out of bounds or list is empty!");
	}

	if (pos == 0) {
		pop_front();
		return;
	}

	Node<T>* cur = _head;
	size_t cur_pos = 0;

	while (cur != nullptr) {
		if (cur_pos == pos - 1) {
			break;
		}
		cur_pos++;
		cur = cur->next;
	}

	Node<T>* to_delete = cur->next;
	cur->next = to_delete->next;

	if (to_delete == _tail) {
		_tail = cur;
	}

	delete to_delete;
	_size--;
}

#endif //LIB_LIST_LIST_H_