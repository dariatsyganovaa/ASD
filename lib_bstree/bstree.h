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
	int _size;
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

	void print_table_rec(BSTreeNode<TKey, TValue>* node, std::ostream& out) const noexcept;
	void print_table(std::ostream& out) const noexcept;
	void print_DLCR() const noexcept;
	void print_DLCR_rec(BSTreeNode<TKey, TValue>*) const noexcept;

private:
	void clear_rec(BSTreeNode<TKey, TValue>* node) noexcept;
	BSTreeNode<TKey, TValue>* find_parent(const TKey& key) const;
	BSTreeNode<TKey, TValue>* find_max_left(BSTreeNode<TKey, TValue>* node) const noexcept;
};

template<class TKey, class TValue>
BSTree<TKey, TValue>::BSTree() : _root(nullptr), _size(0) {}

template<class TKey, class TValue>
BSTree<TKey, TValue>::~BSTree() { clear(); }

template<class TKey, class TValue>
size_t BSTree<TKey, TValue>::size() const noexcept { return _size; }

template<class TKey, class TValue>
bool BSTree<TKey, TValue>::is_empty() const noexcept { return _size == 0; }

template<class TKey, class TValue>
void BSTree<TKey, TValue>::clear() noexcept {
	clear_rec(_root);
	_root = nullptr;
	_size = 0;
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
	BSTreeNode<TKey, TValue>* parent = find_parent(key);
	BSTreeNode<TKey, TValue>* node = new BSTreeNode<TKey, TValue>(key, value);

	if (!parent) { _root = node; _size++; return; }
	if (parent->data.first < key && !parent->right) { parent->right = node;  _size++; return; }
	if (parent->data.first > key && !parent->left) { parent->left = node;  _size++; return; }

	throw std::logic_error("BSTree::insert: data with this key already exists! ");
	delete node;
}

template<class TKey, class TValue>
void BSTree<TKey, TValue>::erase(const TKey& key) {
	if (is_empty()) { throw std::logic_error("BSTree::erase: can`t be deleted from an empty tree! "); }
	BSTreeNode<TKey, TValue>* parent = find_parent(key);

	if (!parent->right && parent->data.first < key || !parent->left && parent->data.first > key) { throw std::logic_error("BSTree::erase: the key not found! "); } 

	if (parent->data.first == key) {
		if (!_root->left && !_root->right) {
			delete _root;
			_root = nullptr;
		}
		else if (!_root->left) {
			BSTreeNode<TKey, TValue>* node = _root;
			_root = _root->right;
			delete node;
		}
		else if (!_root->right) {
			BSTreeNode<TKey, TValue>* node = _root;
			_root = _root->left;
			delete node;
		}
		else {
			BSTreeNode<TKey, TValue>* replacer = find_max_left(_root);
			BSTreeNode<TKey, TValue>* replacer_parent = find_parent(replacer->data.first);
			_root->data = replacer->data;
			if (replacer_parent == _root) {
				replacer_parent->left = replacer->left;
			}
			else {
				replacer_parent->right = replacer->left;
			}
			delete replacer;
		}
		_size--;
		return;
	}
	if (parent->data.first < key && parent->right) {
		BSTreeNode<TKey, TValue>* to_delete = parent->right;
		if (!to_delete->left && !to_delete->right) {
			delete to_delete;
			parent->right = nullptr;
		}
		else if (!to_delete->left) {
			parent->right = to_delete->right;
			delete to_delete;
		}
		else if (!to_delete->right) {
			parent->right = to_delete->left;
			delete to_delete;
		}
		else {
			BSTreeNode<TKey, TValue>* replacer = find_max_left(to_delete);
			BSTreeNode<TKey, TValue>* replacer_parent = find_parent(replacer->data.first);
			to_delete->data = replacer->data;
			if (replacer_parent == to_delete) {
				replacer_parent->left = replacer->left;
			}
			else {
				replacer_parent->right = replacer->left;
			}
			delete replacer;
		}
	}
	if (parent->data.first > key && parent->left) {
		BSTreeNode<TKey, TValue>* to_delete = parent->left;
		if (!to_delete->left && !to_delete->right) {
			delete to_delete;
			parent->left = nullptr;
		}
		else if (!to_delete->left) {
			parent->left = to_delete->right;
			delete to_delete;
		}
		else if (!to_delete->right) {
			parent->left = to_delete->left;
			delete to_delete;
		}
		else {
			BSTreeNode<TKey, TValue>* replacer = find_max_left(to_delete);
			BSTreeNode<TKey, TValue>* replacer_parent = find_parent(replacer->data.first);
			to_delete->data = replacer->data;
			if (replacer_parent == to_delete) {
				replacer_parent->left = replacer->left;
			}
			else {
				replacer_parent->right = replacer->left;
			}
			delete replacer;
		}
	}
	_size--;
}

template<class TKey, class TValue>
TValue* BSTree<TKey, TValue>::find(const TKey& key) const noexcept {
	BSTreeNode<TKey, TValue>* parent = find_parent(key);
	if (!parent) { return nullptr; }
	if (parent->left && parent->left->data.first == key) {
		return &(parent->left->data.second);
	}
	else if (parent->right && parent->right->data.first == key) {
		return &(parent->right->data.second);
	}
	else if (parent == _root && _root->data.first == key) {
		return &(_root->data.second);
	}
	return nullptr;
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
		} else {
			if (!cur->right) { return cur; }
			if (cur->right->data.first == key) { return cur; }
			else { cur = cur->right; }
		}
	}
}

template<class TKey, class TValue>
BSTreeNode<TKey, TValue>* BSTree<TKey, TValue>::find_max_left(BSTreeNode<TKey, TValue>* node) const noexcept {
	if (!node || !node->left) { return nullptr; }
	node = node->left;
	while (node->right) {
		node = node->right;
	}
	return node;
}

template<class TKey, class TValue>
void BSTree<TKey, TValue>::print_DLCR() const noexcept {
	print_DLCR_rec(_root);
}

template<class TKey, class TValue>
void BSTree<TKey, TValue>::print_DLCR_rec(BSTreeNode<TKey, TValue>* node) const noexcept {
	if (node == nullptr) return;
	print_DLCR_rec(node->left);
	std::cout << node->data.first << " ";
	print_DLCR_rec(node->right);
}

template<class TKey, class TValue>
void BSTree<TKey, TValue>::print_table_rec(BSTreeNode<TKey, TValue>* node, std::ostream& out) const noexcept {
	if (node == nullptr) return;
	print_table_rec(node->left, out);
	out << node->data.first << " | " << node->data.second << " | " << "\n";
	print_table_rec(node->right, out);
}

template<class TKey, class TValue>
void BSTree<TKey, TValue>::print_table(std::ostream& out) const noexcept {
	print_table_rec(_root, out);
}
#endif