#ifndef LIB_LIST_LIST_H_
#define LIB_LIST_LIST_H_

#include <stdexcept>

template <class T>
struct Node {
	T data;
	Node<T>* next;

	Node(const T& value) : data(value), next(nullptr) {}
};

template<class T>
class List {
	Node<T>* _head, * _tail;
	size_t _count; 

public:
	List();
	List(const List<T>&);
	~List();

	class Iterator {
		Node<T>* _cur;
	public:
		Iterator() : _cur(nullptr) {}
		Iterator(Node<T>* node) : _cur(node) {}

		Node<T>* get_node() const { return _cur; }

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

		bool operator== (const Iterator& other) const {
			return _cur == other._cur;
		}

		bool operator!= (const Iterator& other) const {
			return !(*this == other);
		}

		T& operator*() const {
			return _cur->data;
		}

		T* operator->() const {
			return &(_cur->data);
		}
	};

	Iterator begin() {
		return Iterator(_head);
	}

	Iterator end() {
		return Iterator(nullptr);
	}

	Iterator begin() const {
		return Iterator(_head);
	}

	Iterator end() const {
		return Iterator(nullptr);
	}
	
	Node<T>* head() const;
	Node<T>* tail() const;
	size_t count() const;

	bool is_empty() const noexcept;

	void push_back(const T& value) noexcept;
	void push_front(const T& value) noexcept;
	void insert(size_t pos, const T& value);
	void insert(Node<T>* node, const T& value);

	void pop_back();
	void pop_front();
	void erase(size_t pos);
	void erase(Node<T>* node);

	void clear();

	List<T>& operator=(const List<T>& other);
	T& operator[](size_t pos);
	const T& operator[](size_t pos) const;
};


template <class T>
List<T>::List() : _head(nullptr), _tail(nullptr), _count(0) {}

template <class T>
List<T>::List(const List<T>& other) : _head(nullptr), _tail(nullptr), _count(0) {
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
	clear();
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
size_t List<T>::count() const {
	return _count;
}

template <class T>
bool List<T>::is_empty() const noexcept {
	return _count == 0;
}

template <class T>
void List<T>::push_front(const T& value) noexcept {
	Node<T>* node = new Node<T>(value);
	if (is_empty()) {
		_head = node;
		_tail = node;
		_count++;
		return;
	}
	node->next = _head;
	_head = node;
	_count++;
}

template <class T>
void List<T>::push_back(const T& value) noexcept {
	Node<T>* node = new Node<T>(value);
	if (is_empty()) {
		_head = node;
		_tail = node;
		_count++;
		return;
	}
	_tail->next = node;
	_tail = node;
	_count++;
}

template <class T>
void List<T>::insert(Node<T>* node, const T& value) { 
	if (node == nullptr) {
		throw std::invalid_argument("Node can't be nullptr!");
	}
	if (is_empty()) {
		throw std::invalid_argument("List is empty!");
	}

	Node<T>* new_node = new Node<T>(value);

	new_node->next = node->next; 
	node->next = new_node; 

	if (node == _tail) {
		_tail = new_node;
	}
	_count++;
}

template <class T>
void List<T>::insert(size_t pos, const T& value) {
	if (pos > _count || pos < 0) {
		throw std::out_of_range("Position is out of bounds!");
	}

	if (pos == 0) {
		push_front(value);
		return;
	}

	if (pos == _count) {
		push_back(value);
		return;
	}

	Node<T>* cur = _head;
	for (size_t i = 0; i < pos - 1; i++) {
		cur = cur->next;
	}

	Node<T>* new_node = new Node<T>(value);
	new_node->next = cur->next;
	cur->next = new_node;
	_count++;
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
		_count = 0;
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
	_count--;
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
	_count--;
}

template <class T>
void List<T>::erase(Node<T>* node) {
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

	Node<T>* cur = _head;

	while (cur != nullptr && cur->next != node) {
		cur = cur->next;
	}

	if (cur == nullptr) {
		throw std::invalid_argument("Node not found in list!");
	}

	cur->next = node->next;

	if (node == _tail) {
		_tail = cur;
	}

	delete node;
	_count--;
}

template <class T>
void List<T>::erase(size_t pos) {
	if (is_empty()) {
		throw std::out_of_range("List is empty!");
	}
	if (pos >= _count || pos < 0) {
		throw std::out_of_range("Position is out of bounds!");
	}

	if (pos == 0) {
		pop_front();
		return;
	}

	if (pos == _count - 1) {
		pop_back();
		return;
	}

	Node<T>* cur = _head;
	for (size_t i = 0; i < pos - 1; i++) {
		cur = cur->next;
	}

	Node<T>* to_delete = cur->next;
	cur->next = to_delete->next;

	if (to_delete == _tail) {
		_tail = cur;
	}

	delete to_delete;
	_count--;
}

template <class T>
void List<T>::clear() {
	Node<T>* cur = _head;
	while (cur != nullptr) {
		Node<T>* next = cur->next;
		delete cur;
		cur = next;
	}
	_head = _tail = nullptr;
	_count = 0;
}

template <class T>
List<T>& List<T>::operator=(const List<T>& other) {
	if (this != &other) {
		clear();
		Node<T>* cur = other._head;
		while (cur != nullptr) {
			push_back(cur->data);
			cur = cur->next;
		}
	}
	return *this;
}

template <class T>
T& List<T>::operator[](size_t pos) {
	if (pos > _count || pos < 0) {
		throw std::out_of_range("Position is out of bounds!");
	}

	Node<T>* cur = _head;
	for (size_t i = 0; i < pos; i++) {
		cur = cur->next;
	}
	return cur->data;
}

template <class T>
const T& List<T>::operator[](size_t pos) const {
	if (pos > _count || pos < 0) {
		throw std::out_of_range("Position is out of bounds!");
	}

	Node<T>* cur = _head;
	for (size_t i = 0; i < pos; i++) {
		cur = cur->next;
	}
	return cur->data;
}

#endif //LIB_LIST_LIST_H_