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
	//size_t _N;
public:
	TriangleMatrix();
	TriangleMatrix(size_t);
	TriangleMatrix(const Matrix<T>&);
	TriangleMatrix(const TriangleMatrix&);

	TriangleMatrix<T> operator+ (const TriangleMatrix& other);
	TriangleMatrix<T> operator- (const TriangleMatrix& other);
	TriangleMatrix<T> operator* (TriangleMatrix<T> matr);
	TriangleMatrix<T> operator* (T val);

	TriangleMatrix<T>& operator=(const TriangleMatrix<T>& other);
	bool operator==(const TriangleMatrix<T>&) const;
	bool operator!=(const TriangleMatrix<T>&) const;

	TriangleMatrix<T>& operator+= (const TriangleMatrix<T>& other) const;
	TriangleMatrix<T>& operator-= (const TriangleMatrix<T>& other) const;
	TriangleMatrix<T>& operator*= (T val);

	MathVector<T>& operator [] (size_t);
	const MathVector<T>& operator [] (size_t) const;

	bool isUpperTriangular();
	bool isLowerTriangular();

	void status();
	void input_tri_matrix(size_t);
	void print_tri_matrix();

	friend std::ostream& operator<< <T>(std::ostream& out, const TriangleMatrix<T>& matr);
	friend std::istream& operator>> <T>(std::istream& in, TriangleMatrix<T>& matr);

};

template <typename T>
TriangleMatrix <T>::TriangleMatrix() : Matrix<T>() {}

template <typename T>
TriangleMatrix <T>::TriangleMatrix(size_t N) : Matrix<T>(N, N) {
	for (size_t i = 0; i < this->_N; i++) {
		(*this)[i] = MathVector<T>(N - i, i); //i - доп. поле индекса
	}
}

template <typename T>
TriangleMatrix <T>::TriangleMatrix(const Matrix<T>& matr) : Matrix<T> (matr) {
	for (size_t i = 0; i < this->_N; i++) {
		for (size_t j = 0; j < this->_N; j++) {
			if (i > j) {
				(*this)[i][j] = T();
			}
		}
	}
}

template <typename T>
TriangleMatrix <T>::TriangleMatrix(const TriangleMatrix& other) : Matrix<T>(other) {}

template <class T>
bool TriangleMatrix<T>::isUpperTriangular() {
	std::cout << "checking upper triangular matrix" << std::endl;
	return true;
}

template <class T>
bool TriangleMatrix<T>::isLowerTriangular() {
	std::cout << "checking lower triangular matrix" << std::endl;
	return true;
}

template <class T>
void TriangleMatrix<T>::status() {
	bool isUpper = isUpperTriangular();
	bool isLower = isLowerTriangular();

	if (isUpper && isLower) {
		std::cout << "Diagonal matrix" << std::endl;
	}
	else if (isUpper) {
		std::cout << "Upper triangular matrix" << std::endl;
	}
	else if (isLower) {
		std::cout << "Lower triangular matrix" << std::endl;
	}
	else {
		std::cout << "Not a triangular matrix" << std::endl;
	}
} 

template <class T>
TriangleMatrix<T> TriangleMatrix<T>::operator+ (const TriangleMatrix& other) {
	return this->Matrix<T> :: operator+ (other);
}

template <class T>
TriangleMatrix<T> TriangleMatrix<T>::operator- (const TriangleMatrix& other) {
	return this->Matrix<T> :: operator- (other);
}

template <typename T>
TriangleMatrix<T> TriangleMatrix<T>::operator* (TriangleMatrix<T> matr) {
	std::cout << "operator* matr" << std::endl;
	return *this;
}

template <typename T>
TriangleMatrix<T> TriangleMatrix<T>::operator* (T val) {
	std::cout << "operator* val" << std::endl;
	return *this;
}

template <typename T>
TriangleMatrix <T>& TriangleMatrix <T>::operator= (const TriangleMatrix& other) { 
	Matrix<T>::operator=(other);
	this->_N = other._N;
	return *this;
}

template <typename T>
bool TriangleMatrix <T>::operator== (const TriangleMatrix& other) const {
	return Matrix<T>::operator==(other);
}

template <typename T>
bool TriangleMatrix <T>::operator!= (const TriangleMatrix& other) const {
	return Matrix<T>::operator!=(other);
}

template <typename T>
TriangleMatrix <T>& TriangleMatrix <T>::operator+= (const TriangleMatrix& other) const {
	std::cout << "operator +=" << std::endl;
	return *this;
}

template <typename T>
TriangleMatrix <T>& TriangleMatrix <T>::operator-= (const TriangleMatrix& other) const {
	std::cout << "operator -=" << std::endl;
	return *this;
}

template <typename T>
TriangleMatrix <T>& TriangleMatrix <T>::operator*= (T val) {
	std::cout << "operator *=" << std::endl;
	return *this;
}

template <typename T>
MathVector<T>& TriangleMatrix<T>::operator [] (size_t index) {
	return this->Matrix<T>::operator[](index); //used start_index
}

template <typename T>
const MathVector<T>& TriangleMatrix<T>::operator [] (size_t index) const {
	return this->Matrix<T>::operator[](index);
}

template <typename T>
void TriangleMatrix <T>::input_tri_matrix(size_t N) { 
	this->resize(N, N);
	for (size_t i = 0; i < N; i++) {
		std::cout << "Row " << i + 1 << ": ";
		MathVector<T> row_vector(N);
		row_vector.input_math_vector();

		for (size_t j = 0; j < N; j++) {
			this->_data[i][j] = row_vector[j];
		}
	}
}

template <typename T>
void TriangleMatrix <T>::print_tri_matrix() {
	std::cout << " ---- YOUR MATRIX ---- " << std::endl;
	for (size_t i = 0; i < this->_N; ++i) {
		for (size_t j = 0; j < this->_N; ++j) {
			std::cout << _data[i][j] << " ";
		}
		std::cout << std::endl;
	}
}

template <class T>
std::ostream& operator<< (std::ostream& out, const TriangleMatrix<T>& matr) {
	std::cout << "operator<<" << std::endl;
	return out;
}

template <class T>
std::istream& operator>> (std::istream& in, TriangleMatrix<T>& matr) {
	std::cout << "operator>>" << std::endl;
	return in;
}
#endif  // LIB_TRIANGLEMATRIX_TRIANGLEMATRIX_H_