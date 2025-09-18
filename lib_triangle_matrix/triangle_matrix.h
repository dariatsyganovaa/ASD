#ifndef LIB_TRIANGLEMATRIX_TRIANGLEMATRIX_H_
#define LIB_TRIANGLEMATRIX_TRIANGLEMATRIX_H_

#include <iostream>
#include <cstddef>
#include "../lib_matrix/matrix.h"

template <typename T> class TriangleMatrix;
template <typename T> std::ostream& operator<<(std::ostream& out, const TriangleMatrix<T>&);

template <class T>
class TriangleMatrix : public Matrix<T> {
public:
	TriangleMatrix();
	TriangleMatrix(size_t);

	void func();
	T foo();
	friend std::ostream& operator << <T>(std::ostream& out, const TriangleMatrix<T>& obj);
};

template <typename T>
TriangleMatrix <T>::TriangleMatrix() : MathVector <MathVector <T>>(), _N(0) {}

template <typename T>
TriangleMatrix <T> ::TriangleMatrix(size_t N) : MathVector <MathVector <T>>(N), _N(N){
	for (size_t i = 0; i < N; i++) {
		_data[i] = new MathVector<T>(N - i, i); //i - доп. поле индекса
	}
}

template <class T>
void TriangleMatrix<T>::func() {}

template <class T>
T TriangleMatrix<T>::foo() { return T(); }

template <class T>
std::ostream& operator << <T>(std::ostream& out, const TriangleMatrix<T>& obj) {
	return out;
}

#endif  // LIB_TRIANGLEMATRIX_TRIANGLEMATRIX_H_