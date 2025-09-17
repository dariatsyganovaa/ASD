#ifndef LIB_MATRIX_MATRIX_H_
#define LIB_MATRIX_MATRIX_H_

#include <cstddef>
#include "../lib_mathvector/mathvector.h"

template <typename T>
class Matrix : public MathVector <MathVector <T>>{
	size_t _N;
	size_t _M;
public:
	Matrix ();
	Matrix (size_t, size_t);

	Matrix<T> trans();

	Matrix<T> operator+ (const Matrix&);
	Matrix<T> operator- (const Matrix&);

	Matrix<T> operator* (T val);
	MathVector<T> operator* (MathVector<T> vec);//?? тип вектора
	Matrix<T> operator* (Matrix<T> matr);


};

template <typename T>
Matrix <T>::Matrix() : MathVector <MathVector <T>>(), _N(0), _M(0) {}

template <typename T>
Matrix <T>::Matrix(size_t N, size_t M) : MathVector <MathVector <T>>(N), _N(N), _M(M) {
	for (size_t i = 0; i < N; i++) {
		_data[i] = MathVector<T>(M);
	}
}

template <typename T>
Matrix<T> Matrix <T>::operator+ (const Matrix& other) {
	if (_N != other._N || _M != other._M) {
		std::cout << "The matrices must have the same dimensions!" << std::endl;
	}

	Matrix<T> result(_M, _N);
	for (size_t i = 0; i < _M; i++) {
		for (size_t j = 0; j < _N; j++) {
			result[i][j] = (*this)[i][j] + other[i][j];
		}
	}
	return result;
	//return this->MathVector <MathVector <T>> :: operator+ (other);
}

template <typename T>
Matrix<T> Matrix<T>::operator* (T val){
	if (_M != other._N) {
		std::cout << "The matrices must have the same dimensions!" << std::endl;
	}

	Matrix<T> result(_M, _N);
	for (size_t i = 0; i < _M; i++) {
		result[i] = (*this)[i] * val;
	}
	return result;
}

template <typename T>
MathVector <T> Matrix<T>::operator* (MathVector <T> vec) {
	MathVector <T> result(_M);
	for (size_t i = 0; i < _M; i++) {
		result[i] = (*this)[i] * vec[i];
	}
	return result;
}

template <typename T>
Matrix<T> Matrix<T>::operator* (Matrix<T> matr) {
	Matrix<T> result(_M, matr._N);
	Matrix<T> Matr_t = matr.trans();

	for (size_t i = 0; i < _M; i++) {
		for (size_t j = 0; j < matr._N; j++) {
			result[i][j] = (*this)[i] * Matr_t[j];
		}
	}
	return result;
}

#endif  // LIB_MATRIX_MATRIX_H_