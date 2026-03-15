#ifndef LIB_UNSORTEDTABLEONTREE_UNSORTEDTABLEONTREE_H_
#define LIB_UNSORTEDTABLEONTREE_UNSORTEDTABLEONTREE_H_

#include <iostream>

#include "../lib_tree/tree.h"
#include "../lib_table/table.h"

template <class TKey, class TValue>
class UnsortedTableOnTree : public Table<TKey, TValue> {
	Tree<TKey, TValue> _rows;
public:
	UnsortedTableOnTree() : _rows() {}
	~UnsortedTableOnTree() override = default;

	size_t size() const noexcept override;
	bool is_empty() const noexcept override;

	void insert(const TKey& key, const TValue& value) override;
	void erase(const TKey& key) override;
	TValue& found(const TKey& key) override;

	void print(std::ostream& out) const override;
};


template<class TKey, class TValue>
bool UnsortedTableOnTree<TKey, TValue>::is_empty() const noexcept { return _rows.is_empty(); }

template<class TKey, class TValue>
size_t UnsortedTableOnTree<TKey, TValue>::size() const noexcept { return _rows.size(); }

template <class TKey, class TValue>
void UnsortedTableOnTree<TKey, TValue>::insert(const TKey& key, const TValue& value) {
	if (_rows.find(key) != nullptr) {
		throw std::logic_error("UnsortedTableOnTree::insert: the keys must be unique! ");
	}
	_rows.insert(key, value);
}

template <class TKey, class TValue>
void UnsortedTableOnTree<TKey, TValue>::erase(const TKey& key) {
	if (_rows.find(key) == nullptr) {
		throw std::logic_error("UnsortedTableOnTree::erase: the key not found! ");
	}
	_rows.erase(key);
}

template <class TKey, class TValue>
TValue& UnsortedTableOnTree<TKey, TValue>::found(const TKey& key) {
	TValue* val = _rows.find(key);
	if (!val) {
		throw std::logic_error("UnsortedTableOnTree::found: the key not found! ");
	}
	return *val;
}

template <class TKey, class TValue>
void UnsortedTableOnTree<TKey, TValue>::print(std::ostream& out) const {
	_rows.print_table(out);
}

#endif //LIB_UNSORTEDTABLEONTREE_UNSORTEDTABLEONTREE_H_