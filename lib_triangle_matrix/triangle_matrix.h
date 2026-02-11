#ifndef LIB_TRIANGLEMATRIX_TRIANGLEMATRIX_H_
#define LIB_TRIANGLEMATRIX_TRIANGLEMATRIX_H_

#include <iostream>
#include <cstddef>
#include "../lib_matrix/matrix.h"

template <typename T> class TriangleMatrix;
template <typename T> std::ostream& operator<<(std::ostream& out, const TriangleMatrix<T>& matr);
template <typename T> std::istream& operator>>(std::istream& in, TriangleMatrix<T>& matr);

template <class T>
class TriangleMatrix : public Matrix<T> {
public:
	TriangleMatrix();
	TriangleMatrix(size_t);
	TriangleMatrix(const Matrix<T>&);
	TriangleMatrix(const TriangleMatrix&);

	size_t get_size() const {
		return this->_N;
	}

	TriangleMatrix<T> operator+ (const TriangleMatrix<T>& other);
	TriangleMatrix<T> operator- (const TriangleMatrix<T>& other);
	TriangleMatrix<T> operator* (const TriangleMatrix<T>& matr);
	MathVector<T> operator* (const MathVector<T>& vec) const;
	TriangleMatrix<T> operator* (T val);

	TriangleMatrix<T>& operator=(const TriangleMatrix<T>& other);
	bool operator==(const TriangleMatrix<T>&) const;
	bool operator!=(const TriangleMatrix<T>&) const;

	TriangleMatrix<T>& operator+= (const TriangleMatrix<T>& other);
	TriangleMatrix<T>& operator-= (const TriangleMatrix<T>& other);
	TriangleMatrix<T>& operator*= (const TriangleMatrix<T>& other);
	TriangleMatrix<T>& operator*= (T val);

	MathVector<T>& operator [] (size_t);
	const MathVector<T>& operator [] (size_t) const;

	friend std::ostream& operator<< <T>(std::ostream& out, const TriangleMatrix<T>& matr);
	friend std::istream& operator>> <T>(std::istream& in, TriangleMatrix<T>& matr);

};

template <typename T>
TriangleMatrix <T>::TriangleMatrix() : Matrix<T>(){}

template <typename T>
TriangleMatrix <T>::TriangleMatrix(size_t N) : Matrix<T>(N, N){
	for (size_t i = 0; i < N; i++) {
		_data[i] = MathVector<T>(N - i, i); 
	}
}

template <typename T>
TriangleMatrix <T>::TriangleMatrix(const Matrix<T>& matr) : Matrix<T>(matr.get_rows(), matr.get_cols()) {
	if (matr.get_rows() != matr.get_cols()) {
		throw std::invalid_argument("TriangleMatrix requires a square matrix!");
	}
	for (size_t i = 0; i < this->_N; i++) {
		_data[i] = MathVector<T>(this->_N - i, i);
		for (size_t j = i; j < this->_N; j++) {
			_data[i][j] = matr[i][j];
		}
	}
}

template <typename T>
TriangleMatrix <T>::TriangleMatrix(const TriangleMatrix<T>& other) : Matrix<T>(other) {}

template <class T>
TriangleMatrix<T> TriangleMatrix<T>::operator+(const TriangleMatrix<T>& other) {
	TriangleMatrix<T> result(*this);
	result += other;
	return result;
}

template <typename T>
TriangleMatrix <T>& TriangleMatrix <T>::operator+= (const TriangleMatrix& other) {
	this->Matrix<T>::operator+=(other);
	return *this;
}

template <class T>
TriangleMatrix<T> TriangleMatrix<T>::operator-(const TriangleMatrix<T>& other) {
	TriangleMatrix<T> result(*this);
	result -= other;
	return result;
}

template <typename T>
TriangleMatrix <T>& TriangleMatrix <T>::operator-= (const TriangleMatrix& other) {
	this->Matrix<T>::operator-=(other);
	return *this;
}

template <typename T>
TriangleMatrix<T> TriangleMatrix<T>::operator*(const TriangleMatrix<T>& other) {
	TriangleMatrix<T> result(*this);
	result *= other;
	return result;
}

template <typename T>
TriangleMatrix<T>& TriangleMatrix<T>::operator*= (const TriangleMatrix<T>& other) {
	if (this->_N == 0 || other._N == 0) {
		throw std::invalid_argument("TriangleMatrix::operator*: can't mult empty matrices!");
	}

	if (this->_N != other._N) {
		throw std::invalid_argument("TriangleMatrix::operator*: sizes must match!");
	}

	TriangleMatrix<T> result(this->_N);

	for (size_t i = 0; i < this->_N; i++) {
		for (size_t j = i; j < this->_N; j++) {
			T sum = T();
			for (size_t k = i; k <= j; k++) {
				sum += _data[i][k] * other._data[k][j];
			}
			result[i][j] = sum;
		}
	}
	*this = result;
	return *this;
}

template <typename T>
MathVector <T> TriangleMatrix<T>::operator* (const MathVector<T>& vec) const {
	if (_N - _start_index == 0 || vec.size() == 0) {
		throw std::invalid_argument("TriangleMatrix::operator*: empty vector or matrix!");
	}
	if (_N - _start_index != vec.size()) {
		throw std::invalid_argument("TriangleMatrix::operator*: incompatible sizes!");
	}

	MathVector<T> result(_N, _start_index);
	for (size_t i = _start_index; i < _N; i++) {
		T sum = T();
		for (size_t j = i; j < _N; j++) {
			sum += _data[i][j] * vec[j];
		}
		result[i] = sum;
	}
	return result;
}

template <typename T>
TriangleMatrix<T> TriangleMatrix<T>::operator* (T val) {
	TriangleMatrix<T> result(this->_N);
	for (size_t i = 0; i < this->_N; i++) {
		for (size_t j = i; j < this->_N; j++) {
			result[i][j] = (*this)[i][j] * val;
		}
	}
	return result;
}

template <typename T>
TriangleMatrix <T>& TriangleMatrix <T>::operator*= (T val) {
	for (size_t i = 0; i < this->_N; i++) {
		for (size_t j = i; j < this->_N; j++) {
			_data[i][j] *= val;
		}
	}
	return *this;
}

template <typename T>
TriangleMatrix <T>& TriangleMatrix <T>::operator= (const TriangleMatrix& other) { 
	Matrix<T>::operator=(other);
	return *this;
}

template <typename T>
bool TriangleMatrix <T>::operator== (const TriangleMatrix& other) const {
	return Matrix<T>::operator==(other);
}

template <typename T>
bool TriangleMatrix <T>::operator!= (const TriangleMatrix& other) const {
	return !(*this == other);
}

template <typename T>
MathVector<T>& TriangleMatrix<T>::operator [] (size_t index) {
	return Matrix<T>::operator[](index); 
}

template <typename T>
const MathVector<T>& TriangleMatrix<T>::operator [] (size_t index) const {
	return Matrix<T>::operator[](index);
}

template <class T>
std::ostream& operator<< (std::ostream& out, const TriangleMatrix<T>& matr) {
	out << " ---- UPPER TRIANGULAR MATRIX ---- " << std::endl;
	for (size_t i = 0; i < matr.get_size(); i++) {
		for (size_t j = 0; j < matr.get_size(); j++) {
			if (j < i) {
				out << "0 ";
			}
			else {
				out << matr[i][j] << " ";
			}
		}
		out << std::endl;
	}
	return out;
}

template <class T>
std::istream& operator>> (std::istream& in, TriangleMatrix<T>& matr) {
	size_t N;
	std::cout << "Enter the size of triangular matrix: ";
	in >> N;

	matr = TriangleMatrix<T>(N);
	for (size_t i = 0; i < N; i++) {
		std::cout << "Row " << i + 1 << ": ";

		for (size_t j = i; j < N; j++) {
			in >> matr[i][j];
		}
	}
	return in;
}

#endif  // LIB_TRIANGLEMATRIX_TRIANGLEMATRIX_H_