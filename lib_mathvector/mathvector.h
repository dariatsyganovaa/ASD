#ifndef LIB_MATHVECTOR_MATHVECTOR_H_
#define LIB_MATHVECTOR_MATHVECTOR_H_

#pragma once
#include "../lib_tvector/tvector.h"

template<typename T>
class MathVector : public TVector <T> {
	size_t _N;
	size_t _start_index;
public:
	MathVector();
	MathVector(size_t);
	//MathVector(size_t, size_t);

	MathVector<T> operator+ (const MathVector<T>& vec) const;
	MathVector<T> operator- (const MathVector<T>& vec) const;
	MathVector<T> operator* (T val);

	MathVector<T>& operator=(const MathVector<T>& other);
	bool operator==(const MathVector<T>&) const;
	bool operator!=(const MathVector<T>&) const;

	MathVector<T>& operator+= (const MathVector<T>& other) const;
	MathVector<T>& operator-= (const MathVector<T>& other) const;
	MathVector<T>& operator*= (T val);
	
	T operator* (MathVector<T> vec);
	T& operator [] (size_t);
	const T& operator [] (size_t) const;
};

template <typename T>
MathVector <T>::MathVector() : TVector <T>(), _N(0), _start_index(0) {}

template <typename T>
MathVector <T>::MathVector(size_t N) : TVector <T>(N), _N(N) {}

//template <typename T>
//MathVector <T>::MathVector(size_t N, size_t start_index) : TVector <T>(N), _N(N), _start_index(start_index) {}

template <typename T>
MathVector <T> MathVector <T>::operator+ (const MathVector& other) const {
	MathVector <T> result(_size);
	for (size_t i = 0; i < _size; i++) {
		result[i] = (*this)[i] + other[i];
	}
	return result;
}

template <typename T>
MathVector <T> MathVector <T>::operator- (const MathVector& other) const {
	MathVector <T> result(_size);
	for (size_t i = 0; i < _size; i++) {
		result[i] = (*this)[i] - other[i];
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
MathVector <T>& MathVector <T>::operator+= (const MathVector& other) const {
	std::cout << "operator +=" << std::endl;
	return *this;
}

template <typename T>
MathVector <T>& MathVector <T>::operator-= (const MathVector& other) const {
	std::cout << "operator -=" << std::endl;
	return *this;
}

template <typename T>
MathVector <T>& MathVector <T>::operator*= (T val) {
	std::cout << "operator *=" << std::endl;
	return *this;
}

template <typename T>
T MathVector <T>::operator* (MathVector <T> vec) {
	T result = T();
	for (size_t i = 0; i < _size; i++) {
		result += (*this)[i] * vec[i];
	}
	return result;
}

template <typename T>
T& MathVector<T>::operator [] (size_t index) {
	if (index - _start_index < 0) {
		//return T(); 
		throw std::out_of_range("Index out of range");
	}
	return _data[index - _start_index];
}

template <typename T>
const T& MathVector<T>::operator [] (size_t index) const{
	if (index - _start_index < 0) { 
		//return T(); 
		throw std::out_of_range("Index out of range");
	}
	return _data[index - _start_index];
}

#endif  // LIB_MATHVECTOR_MATHVECTOR_H_