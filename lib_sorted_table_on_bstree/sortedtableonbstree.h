#ifndef LIB_SORTEDTABLEONBSTREE_SORTEDTABLEONBSTREE_H_
#define LIB_SORTEDTABLEONBSTREE_SORTEDTABLEONBSTREE_H_

#include <iostream>

#include "../lib_bstree/bstree.h"
#include "../lib_table/table.h"

template <class TKey, class TValue>
class SortedTableOnBSTree : public Table<TKey, TValue> {
	BSTree<TKey, TValue> _rows;
public:
	SortedTableOnBSTree() : _rows() {}
	~SortedTableOnBSTree() override = default;

	size_t size() const noexcept override;
	bool is_empty() const noexcept override;

	void insert(const TKey& key, const TValue& value) override;
	void erase(const TKey& key) override;
	TValue& found(const TKey& key) override;

	void print(std::ostream& out) const override;
};

template<class TKey, class TValue>
size_t SortedTableOnBSTree<TKey, TValue>::size() const noexcept { return _rows.size(); }

template<class TKey, class TValue>
bool SortedTableOnBSTree<TKey, TValue>::is_empty() const noexcept { return _rows.is_empty(); }

template <class TKey, class TValue>
void SortedTableOnBSTree<TKey, TValue>::insert(const TKey& key, const TValue& value) {
	if (_rows.find(key) != nullptr) {
		throw std::logic_error("SortedTableOnBSTree::insert: the keys must be unique! ");
	}
	_rows.insert(key, value);
}

template <class TKey, class TValue>
void SortedTableOnBSTree<TKey, TValue>::erase(const TKey& key) {
	if (_rows.find(key) == nullptr) {
		throw std::logic_error("SortedTableOnBSTree::erase: the key not found! ");
	}
	_rows.erase(key);
}

template <class TKey, class TValue>
TValue& SortedTableOnBSTree<TKey, TValue>::found(const TKey& key) {
	TValue* val = _rows.find(key);
	if (!val) {
		throw std::logic_error("SortedTableOnBSTree::found: the key not found! ");
	}
	return *val;
}

template <class TKey, class TValue>
void SortedTableOnBSTree<TKey, TValue>::print(std::ostream& out) const {
	_rows.print_table(out);
}

#endif //LIB_SORTEDTABLEONBSTREE_SORTEDTABLEONBSTREE_H_