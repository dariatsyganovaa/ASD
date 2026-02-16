#ifndef LIB_ITABLE_ITABLE_H_
#define LIB_ITABLE_ITABLE_H_

#include <iostream>

template <class TKey, class TValue>
struct TPair {
    TKey key;
    TValue value;

    TPair() = default;
    TPair(TKey k, TValue v) : key(k), value(v) {}

	TKey get_key() const { return key; }
	TValue get_value() const { return value; }
};

template <class TKey, class TValue>
class ITable {
public:
	virtual void insert(const TKey& key, const TValue& value); 
	virtual void erase(const TKey& key); 
	virtual TValue& found(const TKey& key) const noexcept; 
	virtual bool is_empty() const noexcept;
	friend std::ostream& operator<<(std::ostream& out, const ITable<TKey, TValue>& table) {
		table.print(out);
		return out;
	}
};

#endif //LIB_ITABLE_ITABLE_H_