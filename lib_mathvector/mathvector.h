#ifndef LIB_MATHVECTOR_MATHVECTOR_H_
#define LIB_MATHVECTOR_MATHVECTOR_H_

#pragma once
#include "../lib_tvector/tvector.h"

template <typename T> class MathVector;
template <typename T> std::ostream& operator<<(std::ostream& out, const MathVector<T>& vec);
template <typename T> std::istream& operator>>(std::istream& in, MathVector<T>& vec);

template <class T>
class MathVector : public TVector <T> {
protected:
	size_t _start_index;
public:
	MathVector();
	MathVector(size_t);
	MathVector(size_t, size_t);
	MathVector(const T*, size_t);
	MathVector(const MathVector<T>&);

	size_t start_index() const noexcept;

	MathVector<T> operator+ (const MathVector<T>& vec) const;
	MathVector<T> operator- (const MathVector<T>& vec) const;
	T operator* (const MathVector<T>& vec) const;
	MathVector<T> operator* (T val);

	MathVector<T>& operator=(const MathVector<T>& other);
	bool operator==(const MathVector<T>&) const;
	bool operator!=(const MathVector<T>&) const;

	MathVector<T>& operator+= (const MathVector<T>& other);
	MathVector<T>& operator-= (const MathVector<T>& other);
	MathVector<T>& operator*= (const MathVector<T>& other);
	MathVector<T>& operator*= (T val);
	
	T& at(size_t);
	T& operator [] (size_t);
	const T& operator [] (size_t) const;

	friend std::ostream& operator<< <T>(std::ostream& out, const MathVector<T>& vec);
	friend std::istream& operator>> <T>(std::istream& in, MathVector<T>& vec);
};

template <typename T>
MathVector <T>::MathVector() : TVector <T>(), _start_index(0) {}

template <typename T>
MathVector <T>::MathVector(size_t size) : TVector <T>(size), _start_index(0) {}

template <typename T>
MathVector <T>::MathVector(size_t size, size_t start_index) : TVector <T>(size), _start_index(start_index) {}

template<class T>
MathVector<T>::MathVector(const T* arr, size_t size) : TVector <T>(arr, size), _start_index(0) {}

template <typename T>
MathVector <T>::MathVector(const MathVector& other) : TVector <T>(other), _start_index(other._start_index) {}

template<typename T>
size_t MathVector<T>::start_index() const noexcept { return _start_index; }

template <typename T>
MathVector <T> MathVector <T>::operator+ (const MathVector<T>& vec) const {
	if (_size - _start_index != vec._size - vec._start_index) {
		throw std::invalid_argument("MathVector::operator+: the sizes of the vectors must match!");
	}
	MathVector <T> result(*this);
	result += vec;
	return result;
}

template <typename T>
MathVector <T>& MathVector <T>::operator+= (const MathVector& other) {
	if (_size - _start_index != other._size - other._start_index) {
		throw std::invalid_argument("MathVector::operator+=: the sizes of the vectors must match!");
	}
	for (size_t i = 0; i < _size; i++) {
		_data[i] += other._data[i];
	}
	return *this;
}

template <typename T>
MathVector <T> MathVector <T>::operator- (const MathVector<T>& vec) const {
	if (_size - _start_index != vec._size - vec._start_index) {
		throw std::invalid_argument("MathVector::operator-: the sizes of the vectors must match!");
	}
	MathVector <T> result(*this);
	result -= vec;
	return result;
}

template <typename T>
MathVector <T>& MathVector <T>::operator-= (const MathVector& other) {
	if (_size - _start_index != other._size - other._start_index) {
		throw std::invalid_argument("MathVector::operator-=: the sizes of the vectors must match!");
	}
	for (size_t i = 0; i < _size; i++) {
		_data[i] -= other._data[i];
	}
	return *this;
}

template <typename T>
MathVector <T> MathVector <T>::operator* (T val) {
	MathVector <T> result(*this);
	result *= val;
	return result;
}

template <typename T>
MathVector <T>& MathVector <T>::operator*= (T val) {
	for (size_t i = 0; i < _size; i++) {
		_data[i] *= val;
	}
	return *this;
}

template <typename T>
T MathVector <T>::operator* (const MathVector<T>& vec) const {
	if (_size - _start_index != vec._size - vec._start_index) {
		throw std::invalid_argument("MathVector::operator*: the sizes of the vectors must match!");
	}
	T result = T();
	for (size_t i = 0; i < _size; i++) {
		result += _data[i] * vec._data[i];
	}
	return result;
}

template <typename T>
MathVector <T>& MathVector <T>::operator*= (const MathVector& other) {
	if (_size - _start_index != other._size - other._start_index) {
		throw std::invalid_argument("MathVector::operator*=: the sizes of the vectors must match!");
	}
	for (size_t i = 0; i < _size; i++) {
		_data[i] *= other._data[i];
	}
	return *this;
}

template <typename T>
MathVector <T>& MathVector <T>::operator= (const MathVector& other) {
	if (this != &other) {
		this->TVector<T>::operator=(other);
		_start_index = other._start_index; 
	}
	return *this;
}

template <typename T>
bool MathVector <T>::operator== (const MathVector& other) const {
	if (_size - _start_index != other._size - other._start_index) return false;
	return this->TVector<T>::operator==(other);
}

template <typename T>
bool MathVector <T>::operator!= (const MathVector& other) const {
	return !(*this == other);
}

template<typename T>
T& MathVector<T>::at(size_t index) {
	if (index - _start_index < 0) {
		throw std::out_of_range("MathVector::at: index out of bounds");
	}
	return _data[index - _start_index];
}

template <typename T>
T& MathVector<T>::operator[] (size_t index) {
	if (index - _start_index < 0 && index - _start_index >= -_start_index ) {
		T default_value;
		return default_value;
	}
	return _data[index - _start_index];
}

template <typename T>
const T& MathVector<T>::operator[] (size_t index) const {
	if (index - _start_index < 0 && index - _start_index >= -_start_index) {
		T default_value;
		return default_value;
	}
	return _data[index - _start_index];
}

template <class T>
std::ostream& operator<<(std::ostream& out, const MathVector<T>& vec){
	for (size_t i = 0; i < vec.size(); i++) {
		out << vec[i] << " ";
	}
	out << std::endl;
	return out;
}

template <class T>
std::istream& operator>>(std::istream& in, MathVector<T>& vec) {
	std::cout << ("Enter the elements of the vector: ");
	for (size_t i = 0; i < vec.size(); i++) {
		in >> vec[i];
	}
	return in;
}

#endif  // LIB_MATHVECTOR_MATHVECTOR_H_