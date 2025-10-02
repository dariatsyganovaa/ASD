#ifndef LIB_MATHVECTOR_MATHVECTOR_H_
#define LIB_MATHVECTOR_MATHVECTOR_H_

#pragma once
#include "../lib_tvector/tvector.h"

template<typename T>
class MathVector : public TVector <T> {
protected:
	size_t _start_index;
public:
	MathVector();
	MathVector(size_t);
	MathVector(size_t, size_t);
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
	
	T& operator [] (size_t);
	const T& operator [] (size_t) const;

	void input_math_vector();
	void print_math_vector();
};

template <typename T>
MathVector <T>::MathVector() : TVector <T>(), _start_index(0) {}

template <typename T>
MathVector <T>::MathVector(size_t size) : TVector <T>(size), _start_index(0) {}

template <typename T>
MathVector <T>::MathVector(size_t size, size_t start_index) : TVector <T>(size), _start_index(start_index) {}

template <typename T>
MathVector <T>::MathVector(const MathVector& other) : TVector <T>(other), _start_index(other._start_index) {}

template<typename T>
size_t MathVector<T>::start_index() const noexcept { return _start_index; }

template <typename T>
MathVector <T> MathVector <T>::operator+ (const MathVector<T>& vec) const {
	if (_size != vec._size) {
		throw std::invalid_argument("MathVector::operator+: the sizes of the vectors must match!");
	}
	MathVector <T> result(_size);
	for (size_t i = 0; i < _size; i++) {
		result[i] = (*this)[i] + vec[i];
	}
	return result;
}

template <typename T>
MathVector <T> MathVector <T>::operator- (const MathVector<T>& vec) const {
	if (_size != vec._size) {
		throw std::invalid_argument("MathVector::operator-: the sizes of the vectors must match!");
	}
	MathVector <T> result(_size);
	for (size_t i = 0; i < _size; i++) {
		result[i] = (*this)[i] - vec[i];
	}
	return result;
}

template <typename T>
MathVector <T> MathVector <T>::operator* (T val) {
	MathVector <T> result(_size);
	for (size_t i = 0; i < _size; i++) {
		result[i] = (*this)[i] * val;
	}
	return result;
}

template <typename T>
T MathVector <T>::operator* (const MathVector<T>& vec) const {
	T result = T();
	for (size_t i = 0; i < _size; i++) {
		result += (*this)[i] * vec[i];
	}
	return result;
}

template <typename T>
MathVector <T>& MathVector <T>::operator= (const MathVector& other) {
	TVector<T>::operator=(other);
	return *this;
}

template <typename T>
bool MathVector <T>::operator== (const MathVector& other) const {
	return TVector<T>::operator==(other);
}

template <typename T>
bool MathVector <T>::operator!= (const MathVector& other) const {
	return TVector<T>::operator!=(other);
}

template <typename T>
MathVector <T>& MathVector <T>::operator+= (const MathVector& other) {
	for (size_t i = 0; i < _size; i++) {
		(*this)[i] += other[i];
	}
	return *this;
}

template <typename T>
MathVector <T>& MathVector <T>::operator-= (const MathVector& other) {
	for (size_t i = 0; i < _size; i++) {
		(*this)[i] -= other[i];
	}
	return *this;
}

template <typename T>
MathVector <T>& MathVector <T>::operator*= (const MathVector& other) {
	for (size_t i = 0; i < _size; i++) {
		_data[i] *= other._data[i];
	}
	return *this;
}

template <typename T>
MathVector <T>& MathVector <T>::operator*= (T val) {
	for (size_t i = 0; i < _size; i++) {
		_data[i] *= val;
	}
	return *this;
}

template <typename T>
T& MathVector<T>::operator[] (size_t index) {
	/*if (index - _start_index < 0) {
		throw std::out_of_range("Index out of bounds");
	}*/
	return _data[index - _start_index];
}

template <typename T>
const T& MathVector<T>::operator[] (size_t index) const {
	/*if (index - _start_index < 0) {
		return T();
	}*/
	return _data[index - _start_index];
}

template <typename T>
void MathVector<T>::input_math_vector() {
	std::cout << ("Enter the elements of the vector: ") << std::endl;
	for (size_t i = 0; i < _size; i++) {
		std::cin >> _data[i];
	}
}

template <typename T>
void MathVector<T>::print_math_vector() {
	std::cout << ("Elements of the vector: ") << std::endl;
	for (size_t i = 0; i < _size; i++) {
		std::cout << (*this)[i] << std::endl;
	}
}

#endif  // LIB_MATHVECTOR_MATHVECTOR_H_