#ifndef LIB_TRIANGLEMATRIX_TRIANGLEMATRIX_H_
#define LIB_TRIANGLEMATRIX_TRIANGLEMATRIX_H_

#include <iostream>
#include <cstddef>
#include "../lib_matrix/matrix.h"

template <typename T> class TriangleMatrix;
template <typename T> std::ostream& operator<<(std::ostream& out, const TriangleMatrix<T>& obj);

template <class T>
class TriangleMatrix : public Matrix<T> {
	size_t _N;
public:
	TriangleMatrix();
	TriangleMatrix(size_t);
	TriangleMatrix(const TriangleMatrix&);

	TriangleMatrix<T> operator+ (const TriangleMatrix& other);
	TriangleMatrix<T> operator- (const TriangleMatrix& other);
	TriangleMatrix<T> operator* (TriangleMatrix<T> matr);
	TriangleMatrix<T> operator* (T val);

	void status();
	void input_tri_matrix();
	void print_tri_matrix();

	friend std::ostream& operator << <T>(std::ostream& out, const TriangleMatrix<T>& obj);
};

template <typename T>
TriangleMatrix <T>::TriangleMatrix() : Matrix<T>(), _N(0) {}

template <typename T>
TriangleMatrix <T>::TriangleMatrix(size_t N) : Matrix<T>(N, N), _N(N){
	for (size_t i = 0; i < N; i++) {
		//_data[i] = new MathVector<T>(N - i, i); //i - доп. поле индекса
	}
}

template <typename T>
TriangleMatrix <T>::TriangleMatrix(const TriangleMatrix& other) : Matrix<T>(other), _N(other._N){}

template <class T>
void TriangleMatrix<T>::status() {
	std::cout << "upper triangular or lower triangular matrix" << std::endl;
} 

template <class T>
TriangleMatrix<T> TriangleMatrix<T>::operator+ (const TriangleMatrix& other) {
	std::cout << "operator+" << std::endl;
	return *this;
}

template <class T>
TriangleMatrix<T> TriangleMatrix<T>::operator- (const TriangleMatrix& other) {
	std::cout << "operator-" << std::endl;
	return *this;
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
void TriangleMatrix <T>::input_tri_matrix() {
	std::cout << "Enter elems: " << std::endl;
	std::cout << " - input elems" << std::endl;
}

template <typename T>
void TriangleMatrix <T>::print_tri_matrix() {
	std::cout << "Print matrix: " << std::endl;
	std::cout << " - print elems" << std::endl;
}

template <class T>
std::ostream& operator <<(std::ostream& out, const TriangleMatrix<T>& obj) {
	return out;
}

#endif  // LIB_TRIANGLEMATRIX_TRIANGLEMATRIX_H_