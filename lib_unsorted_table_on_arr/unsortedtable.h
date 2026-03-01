#ifndef LIB_UNSORTEDTABLEONARR_UNSORTEDTABLEONARR_H_
#define LIB_UNSORTEDTABLEONARR_UNSORTEDTABLEONARR_H_

#include <iostream>

#include "../lib_tvector/tvector.h"
#include "../lib_table/table.h"

template <class TKey, class TValue>
class UnsortedTableM : public Table<TKey, TValue> {
	TVector <std::pair<TKey, TValue>> _rows;
public:
	UnsortedTableM() : _rows() {}
	~UnsortedTableM() override = default;

	size_t size() const noexcept override;
	bool is_empty() const noexcept override;

	void insert(const TKey& key, const TValue& value) override;
	void erase(const TKey& key) override;
	TValue& found(const TKey& key) override;

	void print(std::ostream& out) const override;
private:
	int search_key(const TKey& key) const;
};

template<class TKey, class TValue>
size_t UnsortedTableM<TKey, TValue>::size() const noexcept { return _rows.size(); }

template<class TKey, class TValue>
bool UnsortedTableM<TKey, TValue>::is_empty() const noexcept { return _rows.is_empty(); }

template <class TKey, class TValue>
void UnsortedTableM<TKey, TValue>::insert(const TKey& key, const TValue& value) {
	int pos = search_key(key);
	if (pos != -1){ 
		throw std::logic_error("UnsortedTableM::insert: the keys must be unique! "); 
	}
	_rows.push_back_elem(std::make_pair(key, value)); 
}

template <class TKey, class TValue>
void UnsortedTableM<TKey, TValue>::erase(const TKey& key) { 
	int pos = search_key(key);
	if (pos == -1) {
		throw std::logic_error("UnsortedTableM::erase: the key not found! ");
	}
	_rows.erase_elem(pos);
}

template <class TKey, class TValue>
TValue& UnsortedTableM<TKey, TValue>::found(const TKey& key) { 
	int pos = search_key(key);
	if (pos == -1) {
		throw std::logic_error("UnsortedTableM::found: the key not found! ");
	}
	return _rows[pos].second;
}

template <class TKey, class TValue>
void UnsortedTableM<TKey, TValue>::print(std::ostream& out) const {
	for (size_t i = 0; i < _rows.size(); i++) {
		out << "| " << _rows[i].first << " | " << _rows[i].second << " |" << "\n";
	}
}

template<class TKey, class TValue>
int UnsortedTableM<TKey, TValue>::search_key(const TKey& key) const {
	for (size_t i = 0; i < _rows.size(); i++) {
		if (_rows[i].first == key) {
			return i;
		}
	}
	return -1;
}

#endif //LIB_UNSORTEDTABLEONARR_UNSORTEDTABLEONARR_H_