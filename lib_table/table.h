#ifndef LIB_ITABLE_ITABLE_H_
#define LIB_ITABLE_ITABLE_H_

#include <iostream>

template <class TKey, class TValue>
struct TPair {
    TKey key;
    TValue value;

    // Конструкторы
    TPair() {}
    TPair(TKey k, TValue v) : key(k), value(v) {}

    // Оператор сравнения (нужен для некоторых функций TVector)
    bool operator==(const TPair& other) const {
        return key == other.key;
    }

    bool operator!=(const TPair& other) const {
        return !(*this == other);
    }

    // Геттеры (если они требуются по заданию)
    TKey getKey() const { return key; }
    TValue getValue() const { return value; }
};

template <class TKey, class TValue>
class ITable {
public:
    virtual ~ITable() {}

    // Чисто виртуальные методы (интерфейс)
    virtual void insert(const TKey& key, const TValue& val) = 0;
    virtual void erase(const TKey& key) = 0;

    // Возвращаем указатель. Если не нашли - nullptr.
    // const в конце означает, что поиск не меняет саму таблицу.
    virtual TValue* find(const TKey& key) const noexcept = 0;

    virtual bool is_empty() const noexcept = 0;
    virtual size_t size() const noexcept = 0;

    // Метод для вывода (понадобится для оператора <<)
    virtual void print(std::ostream& out) const = 0;

    // Дружественный оператор вывода
    friend std::ostream& operator<<(std::ostream& out, const ITable<TKey, TValue>& table) {
        table.print(out);
        return out;
    }
};

#endif //LIB_ITABLE_ITABLE_H_