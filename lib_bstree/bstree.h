#ifndef LIB_BSTREE_BSTREE_H
#define LIB_BSTREE_BSTREE_H

#include <string>
#include <iostream>

template<class TKey, class TValue>
struct BSTreeNode {
	std::pair<TKey, TValue> data;
	BSTreeNode<TKey, TValue>* left, * right;

	BSTreeNode(const TKey& key, const TValue& value) : data(key, value), left(nullptr), right(nullptr) {}
};

template<class TKey, class TValue>
class BSTree {
	BSTreeNode<TKey, TValue>* _root;
public:
	BSTree();
	~BSTree();

	BSTreeNode<TKey, TValue>* root() const { return _root; }

	size_t size() const noexcept;
	bool is_empty() const noexcept;
	void clear() noexcept;
	void insert(const TKey& key, const TValue& value);
	TValue* find(const TKey& key) const noexcept;
	void erase(const TKey& key);

	void print_W() const noexcept;
	void print_table(std::ostream& out) const noexcept;
	void print_DLCR() const noexcept;
	void print_DLCR_rec(BSTreeNode<TKey, TValue>*) const noexcept;

private:
	void clear_rec(BSTreeNode<TKey, TValue>* node) noexcept;
	BSTreeNode<TKey, TValue>* find_parent(const TKey& key) const;
	BSTreeNode<TKey, TValue>* find_max_left(BSTreeNode<TKey, TValue>*) const noexcept;
};

template<class TKey, class TValue>
BSTree<TKey, TValue>::BSTree() : _root(nullptr) {}

template<class TKey, class TValue>
BSTree<TKey, TValue>::~BSTree() { clear(); }

template<class TKey, class TValue>
size_t BSTree<TKey, TValue>::size() const noexcept {}

template<class TKey, class TValue>
bool BSTree<TKey, TValue>::is_empty() const noexcept {
	return _root == nullptr;
}

template<class TKey, class TValue>
void BSTree<TKey, TValue>::clear() noexcept {
	clear_rec(_root);
	_root = nullptr;
}

template<class TKey, class TValue>
void BSTree<TKey, TValue>::clear_rec(BSTreeNode<TKey, TValue>* node) noexcept {
	if (node == nullptr) return;
	clear_rec(node->left);
	clear_rec(node->right);
	delete node;
}

template<class TKey, class TValue>
void BSTree<TKey, TValue>::insert(const TKey& key, const TValue& value) {
	BSTreeNode<TKey, TValue>* node = new BSTreeNode<TKey, TValue>(key, value);
	BSTreeNode<TKey, TValue>* parent = find_parent(key);
	if (!parent) { _root = node; return; }

	if (parent->data.first < key && !parent->right) {
		parent->right = node;
		return;
	}
	if (parent->data.first > key && !parent->left) {
		parent->left = node;
		return;
	}
	delete node;
	throw std::logic_error("BSTree::insert: data with this key already exists! ");
}

template<class TKey, class TValue>
void BSTree<TKey, TValue>::erase(const TKey& key) {
	BSTreeNode<TKey, TValue>* parent = find_parent(key);

	if (parent->data.first < key && parent->right) {
		if (!parent->right->left && !parent->right->right) {
			delete parent->right;
			parent->right = nullptr;
		}
		else if (!parent->right->left) {
			BSTreeNode<TKey, TValue>* node = parent->right;
			parent->right = parent->right->right;
			delete node;
		}
		else if (!parent->right->right) {
			BSTreeNode<TKey, TValue>* node = parent->right;
			parent->right = parent->right->left;
			delete node;
		}
		else {
			BSTreeNode<TKey, TValue>* replacer = find_max_left(parent->right);

		}
	}
	if (parent->data.first > key && parent->left) {
		parent->left = node;
		return;
	}
}

template<class TKey, class TValue>
TValue* BSTree<TKey, TValue>::find(const TKey& key) const noexcept {
	BSTreeNode<TKey, TValue>* parent = find_parent(key);
	if (!parent) { return nullptr; }
	if (parent->left && parent->left->data.first == key) {
		return &(parent->left->data.second);
	}
	else if(parent->right && parent->right->data.first == key){
		return &(parent->right->data.second);
	}
	else if (parent == _root) {
		return &(_root->data.second);
	}
}

template<class TKey, class TValue>
BSTreeNode<TKey, TValue>* BSTree<TKey, TValue>::find_parent(const TKey& key) const {
	if (is_empty()) { return nullptr; }
	if (_root->data.first == key) { return _root; }

	BSTreeNode<TKey, TValue>* cur = _root;
	while (1) {
		if (cur->data.first > key) {
			if (!cur->left) { return cur; }
			if (cur->left->data.first == key) { return cur; }
			else { cur = cur->left; }
		}else{
			if (!cur->right) { return cur; }
			if (cur->right->data.first == key) { return cur; }
			else { cur = cur->right; }
		}
	}
}

template<class TKey, class TValue>
BSTreeNode<TKey, TValue>* BSTree<TKey, TValue>::find_max_left(BSTreeNode<TKey, TValue>*) const noexcept {

}

#endif