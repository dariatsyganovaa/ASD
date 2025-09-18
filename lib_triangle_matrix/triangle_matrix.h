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

	friend std::ostream& operator<< <T>(std::ostream& out, const TriangleMatrix<T>& matr);
	friend std::istream& operator>> <T>(std::istream& in, TriangleMatrix<T>& matr);

};

template <typename T>
TriangleMatrix <T>::TriangleMatrix() : Matrix<T>(), _N(0) {}

template <typename T>
TriangleMatrix <T>::TriangleMatrix(size_t N) : Matrix<T>(N, N), _N(N){
	for (size_t i = 0; i < N; i++) {
		//_data[i] = new MathVector<T>(N - i, i); //i - ���. ���� �������
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
	TriangleMatrix<T> matrix;
	std::cout << "Enter elems: ";
	std::cin >> matrix;
}

template <typename T>
void TriangleMatrix <T>::print_tri_matrix() {
	TriangleMatrix<T> matrix;
	std::cout << "Print matrix: ";
	std::cout << matrix;
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