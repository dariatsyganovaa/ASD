#ifndef LIB_SKIPLIST_SKIPLIST_H_
#define LIB_SKIPLIST_SKIPLIST_H_

#define INT_MAX

#include <iostream>
#include <random>
#include "../lib_list/list.h"

template <class TKey, class TValue>
struct Node {
	std::pair<TKey, TValue> _data;
	Node** _next;
public:
	Node() = default;
	Node(size_t level, TKey key, TValue value) : _data(key, value) {
		_next = new Node* [level];
		for (size_t i = 0; i < level; i++) {
			_next[i] = nullptr;
		}
	}
	~Node() {
		delete[] _next;
	}
};

template <class TKey, class TValue>
class SkipList {
	size_t _max_level;
	size_t _level;
	List<Node*> _heads;
public:
	SkipList();
	SkipList(size_t max_level);
	void insert(const TKey& key, const TValue& value);
	TValue& found_pos(const TKey& key);
	void print() const noexcept;
protected:
	size_t flip_coin() const noexcept;
	Node* find_nearest(const TKey& key) const noexcept;
};

template <class TKey, class TValue>
SkipList<TKey, TValue>::SkipList() : _max_level(INT_MAX), _level(0) {
	
}

template <class TKey, class TValue>
SkipList<TKey, TValue>::SkipList(size_t max_level) : _max_level(max_level), _level(0) {

}

template <class TKey, class TValue>
void SkipList<TKey, TValue>::insert(const TKey& key, const TValue& value) {
	
}

template <class TKey, class TValue>
TValue& SkipList<TKey, TValue>::found_pos(const TKey& key) {

}

template <class TKey, class TValue>
void SkipList<TKey, TValue>::print() const noexcept {

}

template <class TKey, class TValue>
size_t SkipList<TKey, TValue>::flip_coin() const noexcept {
	int rand = 1 + rand() % 50;

}

template <class TKey, class TValue>
Node<TKey>* SkipList<TKey, TValue>::find_nearest(const TKey& key) const noexcept { //? подумать над шаблона для звена

}

#endif //LIB_SKIPLIST_SKIPLIST_H_