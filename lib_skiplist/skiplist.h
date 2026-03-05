#ifndef LIB_SKIPLIST_SKIPLIST_H_
#define LIB_SKIPLIST_SKIPLIST_H_

#include <iostream>
#include <random>
#include "../lib_list/list.h"

template <class TKey, class TValue>
struct SkipNode {
	std::pair<TKey, TValue> _data;
	SkipNode** _next;
public:
	SkipNode() : _next(nullptr) {}
	SkipNode(size_t level, TKey key, TValue value) : _data(key, value) {
		_next = new SkipNode* [level];
		for (size_t i = 0; i < level; i++) {
			_next[i] = nullptr;
		}
	}
	~SkipNode() {
		delete[] _next;
	}
};

template <class TKey, class TValue>
class SkipList {
	size_t _max_level;
	size_t _level;
	List<SkipNode<TKey, TValue>*> _heads;
public:
	SkipList();
	SkipList(size_t max_level);
	~SkipList();
	size_t get_level() const noexcept;
	void insert(const TKey& key, const TValue& value);
	TValue& found_pos(const TKey& key);
	void print() const noexcept;
protected:
	size_t flip_coin() const noexcept;
	SkipNode<TKey, TValue>** find_nearest(const TKey& key) const noexcept;
};

template <class TKey, class TValue>
SkipList<TKey, TValue>::SkipList() : _max_level(16), _level(0) {
	for (size_t i = 0; i < _max_level; i++) {
		_heads.push_back(nullptr);
	}
}

template <class TKey, class TValue>
SkipList<TKey, TValue>::SkipList(size_t max_level) : _max_level(max_level), _level(0) {
	for (size_t i = 0; i < _max_level; i++) {
		_heads.push_back(nullptr);
	}
}

template <class TKey, class TValue>
SkipList<TKey, TValue>::~SkipList() {
	SkipNode<TKey, TValue>* cur = _heads[0];
	while (cur != nullptr) {
		SkipNode<TKey, TValue>* next_node = cur->_next[0];
		delete cur;
		cur = next_node;
	}
}

template <class TKey, class TValue>
size_t SkipList<TKey, TValue>::get_level() const noexcept {
	return _level;
}

template <class TKey, class TValue>
void SkipList<TKey, TValue>::insert(const TKey& key, const TValue& value) {
	SkipNode<TKey, TValue>** new_arr = find_nearest(key);

	size_t lvl = flip_coin();
	if (lvl > _level) {
		_level = lvl;
	}

	SkipNode<TKey, TValue>* new_node = new SkipNode<TKey, TValue>(lvl, key, value);

	for (size_t i = 0; i < lvl; i++) {
		if (new_arr[i] == nullptr) {
			new_node->_next[i] = _heads[i];
			_heads[i] = new_node;
		}
		else {
			new_node->_next[i] = new_arr[i]->_next[i];
			new_arr[i]->_next[i] = new_node;
		}
	}
}

template <class TKey, class TValue>
TValue& SkipList<TKey, TValue>::found_pos(const TKey& key) {
	SkipNode<TKey, TValue>* cur = _heads[_level - 1];

	for (int i = _level - 1; i >= 0; i--) {
		while (cur != nullptr && cur->_data.first < key) {
			cur = cur->_next[i];
		}
	}

	if (cur != nullptr && cur->_data.first == key) {
		return cur->_data.second;
	}

	throw std::out_of_range("SkipList::found_pos : key not found!");
}

template <class TKey, class TValue>
void SkipList<TKey, TValue>::print() const noexcept {
	for (int i = _level - 1; i >= 0; i--) {
		std::cout << "Level " << i << ": ";

		SkipNode<TKey, TValue>* cur = _heads[i];
		while (cur != nullptr) {
			std::cout << "|" << cur->_data.first /*<< ":" << cur->_data.second */ << "|";
			if (cur->_next[i] != nullptr) {
				std::cout << " -> ";
			}
			cur = cur->_next[i];
		}

		std::cout << " -> NULL\n";
	}
	std::cout << "\n";
}

template <class TKey, class TValue>
size_t SkipList<TKey, TValue>::flip_coin() const noexcept {
	size_t level = 1;
	while (level < _max_level && rand() % 100 + 1 > 50) {
		level++;
	}
	return level;
}

template <class TKey, class TValue>
SkipNode<TKey, TValue>** SkipList<TKey, TValue>::find_nearest(const TKey& key) const noexcept {
	SkipNode<TKey, TValue>** new_arr = new SkipNode<TKey, TValue>* [_max_level];
	for (size_t i = 0; i < _max_level; i++) {
		new_arr[i] = nullptr;
	}

	SkipNode<TKey, TValue>* cur = nullptr;
	for (int i = _level - 1; i >= 0; i--) {
		SkipNode<TKey, TValue>* node = nullptr;
		if (cur == nullptr) {
			node = _heads[i];
		}
		else {
			node = cur->_next[i];
		}

		while (node != nullptr && node->_data.first < key) {
			cur = node;
			node = node->_next[i];
		}
		new_arr[i] = cur;
	}
	return new_arr;
}

#endif //LIB_SKIPLIST_SKIPLIST_H_