#ifndef LIB_ITABLE_ITABLE_H_
#define LIB_ITABLE_ITABLE_H_

#include <iostream>

template <class TKey, class TValue>
class ITable {
public:
	virtual ~ITable() {}
	virtual void insert(const TKey& key, const TValue& value) = 0; 
	virtual void erase(const TKey& key) = 0; 
	virtual TValue& found(const TKey& key) = 0; 
	virtual size_t size() const noexcept = 0;
	virtual bool is_empty() const noexcept = 0;
	virtual void print(std::ostream& out) const = 0;
};

#endif //LIB_ITABLE_ITABLE_H_