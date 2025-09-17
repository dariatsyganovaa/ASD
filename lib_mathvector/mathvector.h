#ifndef LIB_MATHVECTOR_MATHVECTOR_H_
#define LIB_MATHVECTOR_MATHVECTOR_H_

#pragma once
#include "../lib_tvector/tvector.h"

template<typename T>
class MathVector : public TVector <T> {
	size_t _N;
public:
	MathVector();
	MathVector(size_t);

	MathVector<T> operator* (T val);
	T operator* (MathVector<T> vec);
	MathVector<T> operator+ (T vec); //??

	T& operator [] (size_t);
};

template <typename T>
MathVector <T>::MathVector() : TVector <T>(), _N(0) {}

template <typename T>
MathVector <T>::MathVector(size_t N) : TVector <T>(N), _N(N) {}

template <typename T>
MathVector <T> MathVector <T>::operator* (T val) {
	MathVector <T> result(_size);
	for (size_t i = 0; i < _size; i++) {
		result[i] = (*this)[i] * val;
	}
	return result;
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
	if (index - _start_index < 0) { return T(); }
	return _data[index - _start_index];
}

#endif  // LIB_MATHVECTOR_MATHVECTOR_H_