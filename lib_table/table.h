#ifndef LIB_TABLE_TABLE_H_
#define LIB_TABLE_TABLE_H_

#include <iostream>
#include "../lib_itable/itable.h"

template <class TKey, class TValue>
class Table : public ITable<TKey, TValue> {
public:
    virtual void print(std::ostream& out) const override = 0;

    friend std::ostream& operator<<(std::ostream& out, const Table<TKey, TValue>& table) {
        table.print(out);
        return out;
    }
};

#endif //LIB_TABLE_TABLE_H_