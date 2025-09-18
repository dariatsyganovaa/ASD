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
	Matrix(const MathVector <MathVector <T>>&);
	Matrix(const Matrix&);

	Matrix<T> operator+ (const Matrix& other);
	Matrix<T> operator- (const Matrix& other);
	Matrix<T> operator* (Matrix<T> matr);
	Matrix<T> operator* (T val);
	MathVector<T> operator* (MathVector<T> vec);

	Matrix<T> trans();
	void input_matrix();
	void print_matrix();
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
Matrix <T>::Matrix(const MathVector <MathVector <T>>& vec) : MathVector <MathVector <T>>(vec), _N(vec.size()), _M(_N > 0 ? vec[0].size() : 0) {}

template <typename T>
Matrix <T>::Matrix(const Matrix& other) : MathVector <MathVector <T>>(other), _N(other._N), _M(other._M) {}

template <typename T>
Matrix<T> Matrix <T>::operator+ (const Matrix& other) {
	std::cout << "operator+" << std::endl;	
	return *this;
	//return this->MathVector <MathVector <T>> :: operator+ (other);
}

template <typename T>
Matrix<T> Matrix <T>::operator- (const Matrix& other) {
	std::cout << "operator-" << std::endl;
	return *this;
	//return this->MathVector <MathVector <T>> :: operator- (other);
}

template <typename T>
Matrix<T> Matrix<T>::operator* (T val){
	/*Matrix<T> result(_M, _N);
	for (size_t i = 0; i < _M; i++) {
		result[i] = (*this)[i] * val;
	}
	return result;*/

	std::cout << "operator* val" << std::endl;
	return *this;
}

template <typename T>
MathVector <T> Matrix<T>::operator* (MathVector <T> vec) {
	/*MathVector <T> result(_M);
	for (size_t i = 0; i < _M; i++) {
		result[i] = (*this)[i] * vec[i];
	}
	return result;*/

	std::cout << "operator* vec" << std::endl;
	return *this;
}

template <typename T>
Matrix<T> Matrix<T>::operator* (Matrix<T> matr) {
	/*Matrix<T> result(_M, matr._N);
	Matrix<T> Matr_t = matr.trans();

	for (size_t i = 0; i < _M; i++) {
		for (size_t j = 0; j < matr._N; j++) {
			result[i][j] = (*this)[i] * Matr_t[j];
		}
	}
	return result;*/

	std::cout << "operator* matr" << std::endl;
	return *this;
}

template <typename T>
Matrix<T> Matrix <T>::trans() {
	std::cout << " - transposition matrix" << std::endl;
	return *this;
}

template <typename T>
void Matrix <T>::input_matrix() {
	std::cout << "Enter elems: " << std::endl;
	std::cout << " - input elems" << std::endl;
}

template <typename T>
void Matrix <T>::print_matrix() {
	std::cout << "Print matrix: " << std::endl;
	std::cout << " - print elems" << std::endl;
}

#endif  // LIB_MATRIX_MATRIX_H_