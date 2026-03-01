#ifndef LIB_SORTEDTABLEONARR_SORTEDTABLEONARR_H_
#define LIB_SORTEDTABLEONARR_SORTEDTABLEONARR_H_

#include <iostream>

#include "../lib_tvector/tvector.h"
#include "../lib_table/table.h"

template <class TKey, class TValue>
class SortedTableM : public Table<TKey, TValue> {
	TVector <std::pair<TKey, TValue>> _rows;
public:
	SortedTableM() : _rows() {}
	~SortedTableM() override = default;

	size_t size() const noexcept override;
	bool is_empty() const noexcept override;

	void insert(const TKey& key, const TValue& value) override;
	void erase(const TKey& key) override;
	TValue& found(const TKey& key) override;

	void print(std::ostream& out) const override;
	TValue& operator[](size_t pos);
	TKey get_key(size_t pos) const;

private:
	int binary_search(const TKey& key) const;
};

template<class TKey, class TValue>
size_t SortedTableM<TKey, TValue>::size() const noexcept { return _rows.size(); }

template<class TKey, class TValue>
bool SortedTableM<TKey, TValue>::is_empty() const noexcept { return _rows.is_empty(); }

template <class TKey, class TValue>
void SortedTableM<TKey, TValue>::insert(const TKey& key, const TValue& value) {
	int elem = binary_search(key);

	if (elem != -1) {
		throw std::logic_error("SortedTableM::insert: the keys must be unique! ");
	}

	int left = 0; int right = _rows.size();
	while (left < right) {
		int middle = left + (right - left) / 2;
		const TKey& middle_key = _rows[middle].first;
		if (middle_key < key) {
			left = middle + 1;
		}
		else {
			right = middle;
		}
	}

	_rows.insert_elem(std::make_pair(key, value), left);
}

template <class TKey, class TValue>
void SortedTableM<TKey, TValue>::erase(const TKey& key) {
	int pos = binary_search(key);
	if (pos == -1) {
		throw std::logic_error("SortedTableM::erase: the key not found! ");
	}
	_rows.erase_elem(pos);
}

template <class TKey, class TValue>
TValue& SortedTableM<TKey, TValue>::found(const TKey& key) {
	int pos = binary_search(key);
	if (pos == -1) {
		throw std::logic_error("SortedTableM::found: the key not found! ");
	}
	return _rows[pos].second;
}

template <class TKey, class TValue>
void SortedTableM<TKey, TValue>::print(std::ostream& out) const {
	for (size_t i = 0; i < _rows.size(); i++) {
		out << "| " << _rows[i].first << " | " << _rows[i].second << " |" << "\n";
	}
}

template<class TKey, class TValue>
TValue& SortedTableM<TKey, TValue>::operator[](size_t pos) {
	if (pos >= _rows.size()) {
		throw std::out_of_range("SortedTableM::operator[]: index out of range");
	}
	return _rows[pos].second;
}

template<class TKey, class TValue>
TKey SortedTableM<TKey, TValue>::get_key(size_t pos) const { 
	if (pos >= _rows.size()) {
		throw std::out_of_range("SortedTableM::operator[]: index out of range");
	}
	return _rows[pos].first;
}

template<class TKey, class TValue>
int SortedTableM<TKey, TValue>::binary_search(const TKey& key) const {
	int left = 0; int right = _rows.size() - 1;

	while (left <= right) {
		int middle = left + (right - left) / 2;
		const TKey& middle_key = _rows[middle].first;
		if (middle_key == key) {
			return middle;
		}
		else if (middle_key < key) {
			left = middle + 1;
		}
		else {
			right = middle - 1;
		}
	}
	return -1;
}


#endif //LIB_SORTEDTABLEONARR_SORTEDTABLEONARR_H_