#ifndef LIB_TVECTOR_TVECTOR_H_
#define LIB_TVECTOR_TVECTOR_H_

#define STEP_OF_CAPACITY 15

template <typename T> class TVector;

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

    size_t size() const { return _size; }

    TVector<T>& operator=(const TVector<T>&);
    bool operator==(const TVector<T>&) const;
    bool operator!=(const TVector<T>&) const;
    T& operator[](size_t);
    
    void clear() noexcept;
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

#endif  // LIB_TVECTOR_TVECTOR_H_