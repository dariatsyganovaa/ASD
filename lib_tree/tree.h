#ifndef LIB_TREE_TREE_H
#define LIB_TREE_TREE_H

#include <string>
#include <iostream>
#include "..\lib_queue_on_list\queue_on_list.h"

template<class TKey, class TValue>
struct TreeNode {
	std::pair<TKey, TValue> data;
	TreeNode<TKey, TValue>* left, * right;

	TreeNode(const TKey& key, const TValue& value) : data(key, value), left(nullptr), right(nullptr) {}
};

template<class TKey, class TValue>
class Tree {
	TreeNode<TKey, TValue>* _root;
public:
	Tree();
	~Tree();

	TreeNode<TKey, TValue>* root() const { return _root; }

	size_t size() const noexcept;
	bool is_empty() const noexcept;
	void clear() noexcept;
	void insert(const TKey& key, const TValue& value);
	TValue* find(const TKey& key) const noexcept;
	void erase(const TKey& key);

	void print_W() const noexcept;
	void print_table(std::ostream& out) const noexcept;
	void print_DLCR() const noexcept;
	void print_DLRC() const noexcept;
	void print_DCLR() const noexcept;

	void print_DLCR_rec(TreeNode<TKey, TValue>*) const noexcept;
	void print_DLRC_rec(TreeNode<TKey, TValue>*) const noexcept;
	void print_DCLR_rec(TreeNode<TKey, TValue>*) const noexcept;

private:
	void clear_rec(TreeNode<TKey, TValue>* node) noexcept;
	TreeNode<TKey, TValue>* find_parent(const TKey& key) const;
	TreeNode<TKey, TValue>* find_node(const TKey& key) const noexcept;
};

template<class TKey, class TValue>
Tree<TKey, TValue>::Tree() : _root(nullptr) {}

template<class TKey, class TValue>
Tree<TKey, TValue>::~Tree() { clear(); }

template<class TKey, class TValue>
size_t Tree<TKey, TValue>::size() const noexcept {
	if (is_empty()) { return 0; }
	size_t count = 0;
	TreeNode<TKey, TValue>* cur = nullptr;
	QueueOnList<TreeNode<TKey, TValue>*> q;
	q.push(_root);
	while (!q.is_empty()) {
		cur = q.head(); 
		q.pop();
		count++;
		if (cur->left) { q.push(cur->left); }
		if (cur->right) { q.push(cur->right); }
	}
	return count;
}

template<class TKey, class TValue>
bool Tree<TKey, TValue>::is_empty() const noexcept {
	return _root == nullptr;
}

template<class TKey, class TValue>
void Tree<TKey, TValue>::clear() noexcept {
	clear_rec(_root);
	_root = nullptr;
}

template<class TKey, class TValue>
void Tree<TKey, TValue>::clear_rec(TreeNode<TKey, TValue>* node) noexcept {
	if (node == nullptr) return;
	clear_rec(node->left);
	clear_rec(node->right);
	delete node;
}

template<class TKey, class TValue>
void Tree<TKey, TValue>::insert(const TKey& key, const TValue& value) {
	TreeNode<TKey, TValue>* node = new TreeNode<TKey, TValue>(key, value);
	if (is_empty()) { _root = node; return; }
	TreeNode<TKey, TValue>* cur = nullptr;
	QueueOnList<TreeNode<TKey, TValue>*> q;
	q.push(_root);

	while (1) {
		cur = q.head();
		q.pop();
		if (!cur->left) {
			cur->left = node;
			return;
		}
		if (!cur->right) {
			cur->right = node;
			return;
		}
		q.push(cur->left);
		q.push(cur->right);
	}
}

template<class TKey, class TValue>
void Tree<TKey, TValue>::erase(const TKey& key) {
	if (is_empty()) { throw std::logic_error("Tree::erase: can`t be deleted from an empty tree! "); }

	TreeNode<TKey, TValue>* node = find_node(key);
	if (!node) { throw std::logic_error("Tree::erase: the key not found! "); }

	TreeNode<TKey, TValue>* last = nullptr;
	QueueOnList<TreeNode<TKey, TValue>*> q;
	q.push(_root);

	while (!q.is_empty()) {
		last = q.head();
		q.pop();
		if (last->left) { q.push(last->left); }
		if (last->right) { q.push(last->right); }
	}

	TreeNode<TKey, TValue>* last_parent = find_parent(last->data.first);
	node->data = last->data;
	if (last == _root) {
		delete _root;
		_root = nullptr;
		return;
	}

	if (last_parent->left == last) {
		last_parent->left = nullptr;
	}
	else {
		last_parent->right = nullptr;
	}
	delete last;
}

template<class TKey, class TValue>
TValue* Tree<TKey, TValue>::find(const TKey& key) const noexcept {
	TreeNode<TKey, TValue>* node = find_node(key);
	if (!node) { return nullptr; }
	return &(node->data.second);
}

template<class TKey, class TValue>
TreeNode<TKey, TValue>* Tree<TKey, TValue>::find_node(const TKey& key) const noexcept {
	if (is_empty()) { return nullptr; }

	TreeNode<TKey, TValue>* cur = nullptr;
	QueueOnList<TreeNode<TKey, TValue>*> q;
	q.push(_root);

	while (!q.is_empty()) {
		cur = q.head();
		q.pop();
		if (cur->data.first == key) { return cur; }
		if (cur->left) { q.push(cur->left); }
		if (cur->right) { q.push(cur->right); }
	}
	return nullptr;
}

template<class TKey, class TValue>
TreeNode<TKey, TValue>* Tree<TKey, TValue>::find_parent(const TKey& key) const {
	if (is_empty()) { return nullptr; }

	TreeNode<TKey, TValue>* cur = nullptr;
	QueueOnList<TreeNode<TKey, TValue>*> q;
	q.push(_root);

	while (!q.is_empty()) {
		cur = q.head();
		q.pop();
		if (cur->left && cur->left->data.first == key) { return cur; }
		if (cur->right && cur->right->data.first == key) { return cur; }
		if (cur->left) {q.push(cur->left);}
		if (cur->right) { q.push(cur->right); }
	}
	return nullptr;
}

template<class TKey, class TValue>
void Tree<TKey, TValue>::print_W() const noexcept {
	if (is_empty()) { return; }

	TreeNode<TKey, TValue>* cur = nullptr;
	QueueOnList<TreeNode<TKey, TValue>*> q;
	q.push(_root);

	while (!q.is_empty()) {
		cur = q.head();
		std::cout << cur->data.second << " ";
		q.pop();
		if (cur->left) { q.push(cur->left); }
		if (cur->right) { q.push(cur->right); }
	}
}

template<class TKey, class TValue>
void Tree<TKey, TValue>::print_table(std::ostream& out) const noexcept {
	if (is_empty()) { return; }

	TreeNode<TKey, TValue>* cur = nullptr;
	QueueOnList<TreeNode<TKey, TValue>*> q;
	q.push(_root);

	while (!q.is_empty()) {
		cur = q.head();
		out << " |" << cur->data.first << " | " << cur->data.second << "| " << "\n";
		q.pop();
		if (cur->left) { q.push(cur->left); }
		if (cur->right) { q.push(cur->right); }
	}
}

template<class TKey, class TValue>
void Tree<TKey, TValue>::print_DLCR() const noexcept {
	print_DLCR_rec(_root);
}

template<class TKey, class TValue>
void Tree<TKey, TValue>::print_DLRC() const noexcept {
	print_DLRC_rec(_root);
}

template<class TKey, class TValue>
void Tree<TKey, TValue>::print_DCLR() const noexcept {
	print_DCLR_rec(_root);
}

template<class TKey, class TValue>
void Tree<TKey, TValue>::print_DLCR_rec(TreeNode<TKey, TValue>* node) const noexcept {
	if (node == nullptr) return;
	print_DLCR_rec(node->left);
	std::cout << node->data.second << " ";
	print_DLCR_rec(node->right);
}

template<class TKey, class TValue>
void Tree<TKey, TValue>::print_DLRC_rec(TreeNode<TKey, TValue>* node) const noexcept {
	if (node == nullptr) return;
	print_DLRC_rec(node->left);
	print_DLRC_rec(node->right);
	std::cout << node->data.second << " ";
}

template<class TKey, class TValue>
void Tree<TKey, TValue>::print_DCLR_rec(TreeNode<TKey, TValue>* node) const noexcept {
	if (node == nullptr) return;
	std::cout << node->data.second << " ";
	print_DCLR_rec(node->left);
	print_DCLR_rec(node->right);
}

#endif