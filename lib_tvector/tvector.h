#ifndef LIB_TVECTOR_TVECTOR_H_
#define LIB_TVECTOR_TVECTOR_H_

#include <cstddef>
#include <stdexcept>
#include <iostream> 
#include <ctime>  

#define STEP_OF_CAPACITY 15
#define PERS_OF_DELETED 15

template <typename T> class TVector;
template<typename T> int find_first_elem(const TVector<T>&, const T&);
template<typename T> int find_last_elem(const TVector<T>&, const T&);
template<typename T> int* find_elems(const TVector<T>&, const T&, int&);
template<typename T> void swap(TVector<T>&, size_t, size_t); 
template<typename T> void randomize(TVector<T>&); 
template<typename T> void hoara_sort_rec(TVector<T>&, int, int); 
template<typename T> void hoara_sort(TVector<T>&);

enum State { empty, busy, deleted };

template <class T>
class TVector {
protected:
	T* _data;
	size_t _capacity;
	size_t _size;
    size_t _deleted; 
    State* _states;
public:
	TVector();
	TVector(size_t);
    TVector(const T*, size_t);
    TVector(const TVector<T>&);
    ~TVector();

    size_t capacity() const noexcept;
    size_t size() const noexcept;

    inline bool is_empty() const noexcept;

    inline T& front() noexcept;
    inline T& back() noexcept; 

    inline T* begin() noexcept; 
    inline T* end() noexcept; 

    inline const T* data() const noexcept;
    inline const State* states() const noexcept;

    void shift_elements(size_t, size_t);

    void push_front_elem(const T&);
    void push_front_elems(T*, size_t);
    void push_back_elem(const T&);
    void push_back_elems(T*, size_t);
    void insert_elem(const T&, size_t);
    void insert_elems(size_t, T*, size_t);

    void pop_front_elem();
    void pop_front_elems(size_t);
    void pop_back_elem();
    void pop_back_elems(size_t);
    void erase_elem(size_t);
    void erase_elems(size_t, size_t);

    void emplace(size_t, T);

    void assign(const TVector<T>&);
    T& at(size_t);
    void clear() noexcept;

    void shrink_to_fit();
    void reserve(size_t); 
    void resize(size_t);
    void resize(size_t, const T&);

    TVector<T>& operator=(const TVector<T>&);
    bool operator==(const TVector<T>&) const;
    bool operator!=(const TVector<T>&) const;
    T& operator[](size_t);

    void print_elems();
    void print_states();

    friend int find_first_elem<T>(const TVector<T>&, const T&);
    friend int find_last_elem<T>(const TVector<T>&, const T&);
    friend int* find_elems<T>(const TVector<T>&, const T&, int&);
    friend void swap<T>(TVector<T>&, size_t, size_t); 
    friend void randomize<T>(TVector<T>&);
    friend void hoara_sort_rec<T>(TVector<T>&, int, int);
    friend void hoara_sort<T>(TVector<T>&);

private:
    inline bool is_full() const noexcept;
    void allocate_memory(size_t);
    void reallocate_memory(size_t);
    void reallocate_memory_for_delete();
    void free_memory() noexcept;
};

template<class T>
TVector<T>::TVector() {
    _data = nullptr;
    _size = 0;
    _capacity = 0;
    _states = nullptr;
    _deleted = 0;
}

template<class T>
TVector<T>::TVector(size_t size) {
    _data = nullptr;
    _size = size;
    _capacity = 0;
    _states = nullptr;
    _deleted = 0;

    if (_size > 0) {
        _capacity = (size / STEP_OF_CAPACITY + 1) * STEP_OF_CAPACITY;
        _data = new T[_capacity];
        _states = new State[_capacity];
        for (size_t i = 0; i < _capacity; i++) {
            _states[i] = empty;
        }
    }
}

template<class T>
TVector<T>::TVector(const T* arr, size_t size) {
    _size = size;
    _capacity = 0;
    _data = nullptr;
    _states = nullptr;
    _deleted = 0;

    if (_size > 0) {
        _capacity = (size / STEP_OF_CAPACITY + 1) * STEP_OF_CAPACITY;
        _data = new T[_capacity];

        for (size_t i = 0; i < _size; i++) {
            _data[i] = arr[i];
        }

        _states = new State[_capacity];
        for (size_t i = 0; i < _size; i++) {
            _states[i] = busy;
        }
        for (size_t i = _size; i < _capacity; i++) {
            _states[i] = empty;
        }
    }
}

template<class T>
TVector<T>::TVector(const TVector<T>& other) {
    _data = nullptr;
    _states = nullptr;
    _size = other._size;
    _capacity = 0;
    _deleted = other._deleted;

    if (_size > 0) {
        _capacity = (_size / STEP_OF_CAPACITY + 1) * STEP_OF_CAPACITY;
        _data = new T[_capacity];
        _states = new State[_capacity];

        for (size_t i = 0; i < _size; i++) {
            _data[i] = other._data[i];
            _states[i] = other._states[i];
        }

        for (size_t i = _size; i < _capacity; i++) {
            _states[i] = empty;
        }
    }
}

template<class T>
TVector<T>::~TVector() {
    if (_data != nullptr) {
        delete[] _data;
        delete[] _states;
    }
}

template<class T>
size_t TVector<T>::size() const noexcept { return _size; }

template<class T>
size_t TVector<T>::capacity() const noexcept { return _capacity; }

template<class T>
inline const T* TVector<T>::data() const noexcept { return _data; }

template<class T>
inline const State* TVector<T>::states() const noexcept { return _states; }

template<class T>
inline T& TVector<T>::front() noexcept {
    if (_size == 0 || _states[0] != busy) throw std::out_of_range("TVector::front: vector is empty or first element is invalid");
    return _data[0];
}

template<class T>
inline T& TVector<T>::back() noexcept {
    if (_size == 0) throw std::out_of_range("TVector::back: vector is empty");
    for (size_t i = _size + _deleted - 1; i >= 0; --i) {
        if (_states[i] == busy) return _data[i];
    }
    throw std::logic_error("TVector::back: no valid element found");
}

template<class T>
inline T* TVector<T>::begin() noexcept {
    return _data;
}

template<class T>
inline T* TVector<T>::end() noexcept {
    return _data + _size;
}

template<class T>
inline bool TVector<T>::is_empty() const noexcept {
    return _size == 0;
}

template<class T>
void TVector<T>::shift_elements(size_t count, size_t pos) {
    if (count == 0 || pos >= _size) return;

    for (size_t i = _size + _deleted - 1; i >= pos + count; --i) {
        _data[i] = _data[i - count];
        _states[i] = _states[i - count];
    }
}

template<class T>
void TVector<T>::push_front_elem(const T& value) {
    if (_size >= _capacity) {
        reallocate_memory(_capacity + STEP_OF_CAPACITY);
    }
    if (_size > 0) {
        shift_elements(1, 0);
    }
    _data[0] = value;
    _states[0] = busy;
    _size++;
}

template<class T>
void TVector<T>::push_front_elems(T* values, size_t count) {
    if (values == nullptr) {
        throw std::invalid_argument("TVector::push_front_elems: values is nullptr");
    }
    if (count == 0) {
        throw std::invalid_argument("TVector::push_front_elems: count cannot be zero");
    }

    _size += count;
    if (_size >= _capacity) {
        reallocate_memory(_capacity + STEP_OF_CAPACITY);
    }
    if (_size > 0) {
        shift_elements(count, 0);
    }

    for (size_t i = 0; i < count; i++) {
        _data[i] = values[i];
        _states[i] = busy;
    }
}

template<class T>
void TVector<T>::push_back_elem(const T& value) {
    if (_size >= _capacity) {
        reallocate_memory(_capacity + STEP_OF_CAPACITY);
    }
    _data[_size] = value;
    _states[_size] = busy;
    _size++;
}

template<class T>
void TVector<T>::push_back_elems(T* values, size_t count) {
    if (values == nullptr) {
        throw std::invalid_argument("TVector::push_back_elems: values is nullptr");
    }
    if (count == 0) {
        throw std::invalid_argument("TVector::push_back_elems: count cannot be zero");
    }
    if (_size + count > _capacity) {
        reallocate_memory(_capacity + count + STEP_OF_CAPACITY);
    }
    for (size_t i = 0; i < count; ++i) {
        _data[_size + i] = values[i];
        _states[_size + i] = busy;
    }
    _size += count;
}

template<class T>
void TVector<T>::insert_elem(const T& value, size_t pos) {
    if (pos > _size) {
        throw std::out_of_range("TVector::insert_elem: insert position out of range!");
    }

    if (_size >= _capacity) {
        reallocate_memory(_capacity + STEP_OF_CAPACITY);
    }
    if (_size > 0) {
        shift_elements(1, pos);
    }
    _data[pos] = value;
    _states[pos] = busy;
    _size++;
}

template<class T>
void TVector<T>::insert_elems(size_t pos, T* values, size_t count) {
    if (pos > _size) {
        throw std::out_of_range("TVector::insert_elems: insert position out of range");
    }
    _size += count;
    if (_size >= _capacity) {
        reallocate_memory(_capacity + STEP_OF_CAPACITY);
    }
    if (_size > 0) {
        shift_elements(count, pos);
    }
    for (size_t i = 0; i < count; i++) {
        _data[pos + i] = values[i];
        _states[pos + i] = busy;
    }
}

template<class T>
void TVector<T>::pop_front_elem() {
    if (_size == 0) {
        throw std::out_of_range("TVector::pop_front_elem: cannot be deleted from an empty vector");
    }
    _states[0] = deleted;
    _deleted++;
    _size--;
    if (_deleted * 100 > _capacity * PERS_OF_DELETED) {
        reallocate_memory_for_delete();
    }
}

template<class T>
void TVector<T>::pop_front_elems(size_t count) {
    if (_size == 0) {
        throw std::out_of_range("TVector::pop_front_elems: cannot be deleted from an empty vector");
    }
    if (count > _size) {
        throw std::invalid_argument("TVector::pop_front_elems: the counter cannot be larger than the size");
    }
    for (size_t i = 0; i < count; i++) {
        _states[i] = deleted;
    }
    _deleted += count;
    _size -= count;
    if (_deleted * 100 > _capacity * PERS_OF_DELETED) {
        reallocate_memory_for_delete();
    }
}

template<class T>
void TVector<T>::pop_back_elem() {
    if (_size == 0) {
        throw std::out_of_range("TVector::pop_back_elem: cannot be deleted from an empty vector");
    }
    for (size_t i = _size + _deleted - 1; i >= 0; --i) {
        if (_states[i] == busy) {
            _states[i] = deleted;
            _deleted++;
            _size--;
            break;
        }
    }
    if (_deleted * 100 > _capacity * PERS_OF_DELETED) {
        reallocate_memory_for_delete();
    }
}

template<class T>
void TVector<T>::pop_back_elems(size_t count) {
    if (_size == 0) {
        throw std::out_of_range("TVector::pop_back_elems: cannot be deleted from an empty vector");
    }
    if (count > _size) {
        throw std::invalid_argument("TVector::pop_back_elems: the counter cannot be larger than the size");
    }
    size_t j = 0;
    for (size_t i = _size + _deleted - 1; i >= 0; --i) {
        if (_states[i] == busy) {
            _states[i] = deleted;
            j++;
            if (j == count) break;
        }
    }
    _deleted += count;
    _size -= count;
    if (_deleted * 100 > _capacity * PERS_OF_DELETED) {
        reallocate_memory_for_delete();
    }
}

template<class T>
void TVector<T>::erase_elem(size_t pos) {
    if (pos >= _size) {
        throw std::out_of_range("TVector::erase_elem: erase position out of range");
    }
    if (_size == 0) {
        throw std::out_of_range("TVector::erase_elem: cannot be deleted from an empty vector");
    }
    size_t j = 0;
    for (size_t i = 0; i < _size + _deleted; i++) {
        if (_states[i] == busy) {
            if (j == pos) {
                _states[i] = deleted;
                _deleted++;
                _size--;
                break;
            }
            j++;
        }
    }
    if (_deleted * 100 > _capacity * PERS_OF_DELETED) {
        reallocate_memory_for_delete();
    }
}

template<class T>
void TVector<T>::erase_elems(size_t pos, size_t count) {
    if (_size == 0) {
        throw std::out_of_range("TVector::erase_elems: cannot be deleted from an empty vector");
    }
    if (count > _size) {
        throw std::invalid_argument("TVector::erase_elems: the counter cannot be larger than the size");
    }
    if (pos >= _size) {
        throw std::out_of_range("TVector::erase_elems: erase position out of range");
    }
    size_t j = 0;
    for (size_t i = 0; i < _size + _deleted; i++) {
        if (_states[i] == busy) {
            if (j >= pos && j < pos + count) {
                _states[i] = deleted;
                _deleted++;
            }
            j++;
        }
    }
    _size -= count;
    if (_deleted * 100 > _capacity * PERS_OF_DELETED) {
        reallocate_memory_for_delete();
    }
}

template<class T>
void TVector<T>::emplace(size_t pos, T val) {
    if (_size == 0) {
        throw std::out_of_range("TVector::emplace: cannot be emplaced from an empty vector");
    }
    if (pos >= _size) {
        throw std::out_of_range("TVector::emplace: emplace position out of range");
    }
    size_t j = 0;
    for (size_t i = 0; i < _size + _deleted; i++) {
        if (_states[i] == busy) {
            if (j == pos) {
                _data[i] = val;
                break;
            }
            j++;
        }
    }
}

template<class T>
void TVector<T>::assign(const TVector<T>& other) {
    if (this == &other) {
        return;
    }
    clear();
    if (other._size > 0) {
        _capacity = (other._size / STEP_OF_CAPACITY + 1) * STEP_OF_CAPACITY;
        _data = new T[_capacity];
        _states = new State[_capacity];
        for (size_t i = 0; i < other._size; i++) {
            _data[i] = other._data[i];
            _states[i] = other._states[i];
        }
        for (size_t i = other._size; i < _capacity; i++) {
            _states[i] = empty;
        }
        _size = other._size;
        _deleted = other._deleted;
    }
}

template<class T>
T& TVector<T>::at(size_t index) {
    if (index >= _size) {
        throw std::out_of_range("TVector::at: index out of range");
    }
    size_t j = 0;
    for (size_t i = 0; i < _size + _deleted; i++) {
        if (_states[i] == busy) {
            if (j == index) {
                return _data[i];
            }
            j++;
        }
    }
    throw std::logic_error("TVector::at: element not found");
}

template<class T>
void TVector<T>::clear() noexcept {
    if (_data != nullptr) {
        delete[] _data;
        delete[] _states;
    }
    _data = nullptr;
    _states = nullptr;
    _capacity = 0;
    _size = 0;
    _deleted = 0;
}

template<class T>
void TVector<T>::shrink_to_fit() {
    if (_size == 0) {
        clear();
        return;
    }
    T* new_data = new T[_size];
    State* new_states = new State[_size];
    size_t j = 0;
    for (size_t i = 0; i < _capacity; i++) {
        if (_states[i] == busy) {
            new_data[j] = _data[i];
            new_states[j] = busy;
            j++;
        }
    }
    delete[] _data;
    delete[] _states;
    _data = new_data;
    _states = new_states;
    _capacity = _size;
    _deleted = 0;
}

template<class T>
void TVector<T>::reserve(size_t new_capacity) {
    if (new_capacity <= _capacity) {
        return;
    }
    T* new_data = new T[new_capacity];
    State* new_states = new State[new_capacity]();
    size_t j = 0;
    for (size_t i = 0; i < _capacity; i++) {
        if (_states[i] == busy) {
            new_data[j] = _data[i];
            new_states[j] = busy;
            j++;
        }
    }
    delete[] _data;
    delete[] _states;
    _data = new_data;
    _states = new_states;
    _capacity = new_capacity;
}

template<class T>
void TVector<T>::resize(size_t new_size) {
    if (new_size < _size) {
        for (size_t i = new_size; i < _size + _deleted; i++) {
            if (_states[i] == busy || _states[i] == deleted) {
                _states[i] = empty;
            }
        }
        _size = new_size;
    }
    else if (new_size > _size) {
        reserve(new_size);
        for (size_t i = _size; i < new_size; i++) {
            _data[i] = T(); // ???????? ?? ????????? ??? ???? T
            _states[i] = busy;
        }
        _size = new_size;
    }
}

template<class T>
void TVector<T>::resize(size_t new_size, const T& value) {
    if (new_size < _size) {
        for (size_t i = new_size; i < _size; i++) {
            if (_states[i] == busy) {
                _states[i] = empty;
            }
        }
        _size = new_size;
    }
    else if (new_size > _size) {
        reserve(new_size);
        for (size_t i = _size; i < new_size; i++) {
            _data[i] = value;
            _states[i] = busy;
        }
        _size = new_size;
    }
}

template<class T>
TVector<T>& TVector<T>::operator=(const TVector<T>& other) {
    if (this != &other) {
        clear();
        if (other._size > 0) {
            _capacity = (other._size / STEP_OF_CAPACITY + 1) * STEP_OF_CAPACITY;
            _data = new T[_capacity];
            _states = new State[_capacity];
            for (size_t i = 0; i < other._size; i++) {
                _data[i] = other._data[i];
                _states[i] = other._states[i];
            }
            for (size_t i = other._size; i < _capacity; i++) {
                _states[i] = empty;
            }
            _size = other._size;
            _deleted = other._deleted;
        }
    }
    return *this;
}

template<class T>
bool TVector<T>::operator==(const TVector<T>& other) const {
    if (this == &other) return true;
    if (_size != other._size) return false;
    for (size_t i = 0; i < _size + _deleted; i++) {
        if (_states[i] == busy) {
            size_t j = 0;
            bool found = false;
            for (size_t k = 0; k < other._size + other._deleted; k++) {
                if (other._states[k] == busy && _data[i] == other._data[k]) {
                    found = true;
                    break;
                }
            }
            if (!found) return false;
        }
    }
    return true;
}

template<class T>
bool TVector<T>::operator!=(const TVector<T>& other) const {
    return !(*this == other);
}

template<class T>
T& TVector<T>::operator[](size_t pos) {
    if (pos >= _size) {
        throw std::out_of_range("TVector::operator[]: index out of range");
    }
    size_t j = 0;
    for (size_t i = 0; i < _size + _deleted; i++) {
        if (_states[i] == busy) {
            if (j == pos) {
                return _data[i];
            }
            j++;
        }
    }
    throw std::logic_error("TVector::operator[]: element not found");
}

template<class T>
void TVector<T>::print_elems() {
    size_t count = 0;
    for (size_t i = 0; i < _capacity; i++) {
        if (_states[i] == busy) {
            std::cout << _data[i] << " ";
            count++;
        }
    }
    std::cout << std::endl;
}

template<class T>
void TVector<T>::print_states() {
    for (size_t i = 0; i < _capacity; i++) {
        std::cout << static_cast<int>(_states[i]) << " ";
    }
    std::cout << std::endl;
}

template<typename T>
int find_first_elem(const TVector<T>& vec, const T& value) {
    if (vec.size() == 0) {
        throw std::invalid_argument("TVector::find_first_elem: cannot find from empty vector");
    }
    size_t index = 0;
    for (size_t i = 0; i < vec._capacity; i++) {
        if (vec._states[i] == busy && vec._data[i] == value) {
            return static_cast<int>(index);
        }
        if (vec._states[i] == busy) {
            index++;
        }
    }
    return -1;
}

template<typename T>
int find_last_elem(const TVector<T>& vec, const T& value) {
    if (vec.size() == 0) {
        throw std::invalid_argument("TVector::find_last_elem: cannot find from empty vector");
    }
    int index = static_cast<int>(vec.size()) - 1;
    for (size_t i = vec._capacity; i > 0; --i) {
        if (vec._states[i - 1] == busy) {
            if (vec._data[i - 1] == value) {
                return index;
            }
            index--;
        }
    }
    return -1;
}

template<typename T>
int* find_elems(const TVector<T>& vec, const T& value, int& size) {
    if (vec.size() == 0) {
        throw std::invalid_argument("TVector::find_elems: cannot find from empty vector");
    }
    size = 0;
    for (size_t i = 0; i < vec._capacity; i++) {
        if (vec._states[i] == busy && vec._data[i] == value) {
            size++;
        }
    }

    if (size == 0) {
        return nullptr;
    }

    int* result = new int[size];
    int index = 0;
    size_t j = 0;
    for (size_t i = 0; i < vec._capacity; i++) {
        if (vec._states[i] == busy) {
            if (vec._data[i] == value) {
                result[j] = index;
                j++;
            }
            index++;
        }
    }
    return result;
}

template<class T>
inline bool TVector<T>::is_full() const noexcept { return _size >= _capacity; }

template<class T>
void TVector<T>::allocate_memory(size_t new_capacity) {
    T* new_data = static_cast<T*>(operator new[](new_capacity * sizeof(T)));
    State* new_states = new State[new_capacity]();
    _data = new_data;
    _states = new_states;
    _capacity = new_capacity;
}

template<class T>
void TVector<T>::reallocate_memory_for_delete() {
    T* new_data = new T[_size + STEP_OF_CAPACITY];
    State* new_states = new State[_size + STEP_OF_CAPACITY]();
    size_t j = 0;
    for (size_t i = 0; i < _capacity; i++) {
        if (_states[i] == busy) {
            new_data[j] = _data[i];
            new_states[j] = busy;
            j++;
        }
    }
    delete[] _data;
    delete[] _states;
    _data = new_data;
    _states = new_states;
    _capacity = _size + STEP_OF_CAPACITY;
    _deleted = 0;
    for (size_t i = _size; i < _capacity; i++) {
        _states[i] = empty;
    }
}

template<class T>
void TVector<T>::reallocate_memory(size_t new_capacity) {
    if (_capacity == 0) {
        allocate_memory(STEP_OF_CAPACITY);
        return;
    }
    T* new_data = static_cast<T*>(operator new[](new_capacity * sizeof(T)));
    State* new_states = new State[new_capacity]();
    size_t j = 0;
    for (size_t i = 0; i < _capacity; i++) {
        if (_states[i] == busy) {
            new (&new_data[j]) T(std::move(_data[i]));
            new_states[j] = busy;
            j++;
        }
    }
    delete[] _data;
    delete[] _states;
    _data = new_data;
    _states = new_states;
    _capacity = new_capacity;
    _deleted = 0;
}

template<class T>
void TVector<T>::free_memory() noexcept {
    delete[] _data;
    delete[] _states;
    _data = nullptr;
    _states = nullptr;
    _size = 0;
    _capacity = 0;
    _deleted = 0;
}

template<typename T>
void randomize(TVector<T>& vec) {
    srand(static_cast<unsigned>(time(nullptr)));
    for (size_t i = 0; i < vec._size; i++) {
        if (vec._states[i] == busy) {
            size_t j = i + rand() % (vec._size - i);
            if (j < vec._capacity && vec._states[j] == busy) {
                swap(vec, i, j);
            }
        }
    }
}

template<typename T>
void swap(TVector<T>& vec, size_t i, size_t j) {
    T temp = vec._data[i];
    vec._data[i] = vec._data[j];
    vec._data[j] = temp;
    State temp_state = vec._states[i];
    vec._states[i] = vec._states[j];
    vec._states[j] = temp_state;
}

template<typename T>
void hoara_sort_rec(TVector<T>& vec, int left, int right) {
    if (left < right) {
        int pivot = left + (right - left) / 2;
        T pivot_value = vec._data[pivot];
        int i = left, j = right;
        while (i <= j) {
            while (vec._states[i] == busy && vec._data[i] < pivot_value) i++;
            while (vec._states[j] == busy && vec._data[j] > pivot_value) j--;
            if (i <= j) {
                if (vec._states[i] == busy && vec._states[j] == busy) {
                    swap(vec, i, j);
                }
                i++;
                j--;
            }
        }
        hoara_sort_rec(vec, left, j);
        hoara_sort_rec(vec, i, right);
    }
}

template<typename T>
void hoara_sort(TVector<T>& vec) {
    hoara_sort_rec(vec, 0, static_cast<int>(vec._size) - 1);
}

#endif  // LIB_TVECTOR_TVECTOR_H_