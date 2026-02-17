#ifndef LIB_UNSORTEDTABLEONLIST_UNSORTEDTABLEONLIST_H_
#define LIB_UNSORTEDTABLEONLIST_UNSORTEDTABLEONLIST_H_

#include <iostream>

#include "../lib_list/list.h"
#include "../lib_table/table.h"

template <class TKey, class TValue>
class UnsortedTableOnList : public Table<TKey, TValue> {
	List <std::pair<TKey, TValue>> _rows;
public:
	UnsortedTableOnList() : _rows() {}
	~UnsortedTableOnList() override = default;

	size_t size() const noexcept override;
	bool is_empty() const noexcept override;

	void insert(const TKey& key, const TValue& value) override;
	void erase(const TKey& key) override;
	TValue& found(const TKey& key) override;

	void print(std::ostream& out) const override;
};

template<class TKey, class TValue>
size_t UnsortedTableOnList<TKey, TValue>::size() const noexcept { return _rows.count(); }

template<class TKey, class TValue>
bool UnsortedTableOnList<TKey, TValue>::is_empty() const noexcept { return _rows.is_empty(); }

template <class TKey, class TValue>
void UnsortedTableOnList<TKey, TValue>::insert(const TKey& key, const TValue& value) {
	for (auto it = _rows.begin(); it != _rows.end(); it++) {
		if ((*it).first == key) {
			throw std::logic_error("UnsortedTableOnList::insert: the keys must be unique! ");
		}
	}
	_rows.push_back(std::make_pair(key, value));
}

template <class TKey, class TValue>
void UnsortedTableOnList<TKey, TValue>::erase(const TKey& key) {
	for (auto it = _rows.begin(); it != _rows.end(); it++) {
		if ((*it).first == key) {
			_rows.erase(it.get_node());
			return;
		}
	}
	throw std::logic_error("UnsortedTableOnList::erase: the key not found! ");
}

template <class TKey, class TValue>
TValue& UnsortedTableOnList<TKey, TValue>::found(const TKey& key) {
	for (auto it = _rows.begin(); it != _rows.end(); it++) {
		if ((*it).first == key) {
			return (*it).second;
		}
	}
	throw std::logic_error("UnsortedTableOnList::found: the key not found! ");
}

template <class TKey, class TValue>
void UnsortedTableOnList<TKey, TValue>::print(std::ostream& out) const {
	for (auto it = _rows.begin(); it != _rows.end(); it++) {
		out << "| " << (*it).first << " | " << (*it).second << " |" << "\n";
	}
}

#endif //LIB_UNSORTEDTABLEONLIST_UNSORTEDTABLEONLIST_H_