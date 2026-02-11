#ifndef LIB_UNSORTEDTABLEONARR_UNSORTEDTABLEONARR_H_
#define LIB_UNSORTEDTABLEONARR_UNSORTEDTABLEONARR_H_

template <class TKey, class TValue>
class UnsortedTableM : public ITable<TKey, TValue> {
protected:
    TVector<TPair<TKey, TValue>> _rows;

public:
    UnsortedTableM() {}

    // Проверка на пустоту
    bool is_empty() const noexcept override {
        return _rows.size() == 0;
    }

    size_t size() const noexcept override {
        return _rows.size();
    }

    // Поиск: возвращаем адрес значения
    TValue* find(const TKey& key) const noexcept override {
        for (size_t i = 0; i < _rows.size(); ++i) {
            if (_rows[i].key == key) {
                // Т.к. метод const, а нам нужно вернуть не-const указатель, 
                // используем const_cast (в рамках лабы это допустимо)
                return const_cast<TValue*>(&_rows[i].value);
            }
        }
        return nullptr;
    }

    // Вставка
    void insert(const TKey& key, const TValue& val) override {
        if (find(key) != nullptr) {
            throw std::runtime_error("Key already exists!");
        }
        _rows.push_back(TPair<TKey, TValue>(key, val));
        // ВАЖНО: убедись, что в твоем TVector есть push_back
    }

    // Удаление
    void erase(const TKey& key) override {
        for (size_t i = 0; i < _rows.size(); ++i) {
            if (_rows[i].key == key) {
                // Меняем местами с последним и удаляем последний (O(1))
                _rows[i] = _rows[_rows.size() - 1];
                _rows.pop_back();
                // ВАЖНО: убедись, что в твоем TVector есть pop_back
                return;
            }
        }
        throw std::runtime_error("Key not found!");
    }

    // Реализация вывода (для operator<<)
    void print(std::ostream& out) const override {
        for (size_t i = 0; i < _rows.size(); ++i) {
            out << _rows[i].key << " | " << _rows[i].value << std::endl;
        }
    }
};
#endif //LIB_UNSORTEDTABLEONARR_UNSORTEDTABLEONARR_H_