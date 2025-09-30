#ifndef LIB_MATRIX_MATRIX_H_
#define LIB_MATRIX_MATRIX_H_

#include <cstddef>
#include "../lib_mathvector/mathvector.h"

template <typename T> class Matrix;
template <typename T> std::ostream& operator<<(std::ostream& out, const Matrix<T>& matr);
template <typename T> std::istream& operator>>(std::istream& in, Matrix<T>& matr);

template <class T>
class Matrix : public MathVector <MathVector <T>>{
protected:
	size_t _N;
	size_t _M;
public:
	Matrix ();
	Matrix (size_t, size_t);
	Matrix(const MathVector <MathVector <T>>&);
	Matrix(const Matrix&);

	size_t get_rows() {
		return _N;
	}
	size_t get_cols() {
		return _M;
	}

	Matrix<T> operator+ (const Matrix<T>& other);
	Matrix<T> operator- (const Matrix<T>& other);
	Matrix<T> operator* (Matrix<T> matr);
	Matrix<T> operator* (T val);
	MathVector<T> operator* (MathVector<T> vec);

	Matrix<T>& operator=(const Matrix<T>& other);
	bool operator==(const Matrix<T>&) const;
	bool operator!=(const Matrix<T>&) const;

	Matrix<T>& operator+= (const Matrix<T>& other);
	Matrix<T>& operator-= (const Matrix<T>& other);
	Matrix<T>& operator*= (const Matrix<T>& other);
	Matrix<T>& operator*= (T val);

	/*T& operator [] (size_t);
	const T& operator [] (size_t) const;*/

	Matrix<T> trans();
	void input_matrix(size_t, size_t);
	void print_matrix() const;

	friend std::ostream& operator<< <T>(std::ostream& out, const Matrix<T>& matr);
	friend std::istream& operator>> <T>(std::istream& in, Matrix<T>& matr);
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
	return this->MathVector <MathVector <T>> :: operator+ (other);
}

template <typename T>
Matrix<T> Matrix <T>::operator- (const Matrix& other) {
	return this->MathVector <MathVector <T>> :: operator- (other);
}

template <typename T>
Matrix<T> Matrix<T>::operator* (T val){
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
		result[i] = (*this)[i] * vec;
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

template <typename T>
Matrix <T>& Matrix <T>::operator= (const Matrix& other) {
	return MathVector<T>::operator=(other);
}

template <typename T>
bool Matrix <T>::operator== (const Matrix& other) const {
	return MathVector<T>::operator==(other);
}

template <typename T>
bool Matrix <T>::operator!= (const Matrix& other) const {
	return MathVector<T>::operator!=(other);
}

template <typename T>
Matrix <T>& Matrix <T>::operator+= (const Matrix& other) {
	for (size_t i = 0; i < _M; i++) {
		for (size_t j = 0; j < _N; j++) {
			_data[i * _N + j] += other._data[i * _N + j];
		}
	}
	return *this;
}

template <typename T>
Matrix <T>& Matrix <T>::operator-= (const Matrix& other) {
	for (size_t i = 0; i < _M; i++) {
		for (size_t j = 0; j < _N; j++) {
			_data[i * _N + j] -= other._data[i * _N + j];
		}
	}
	return *this;
}

template <typename T>
Matrix <T>& Matrix <T>::operator*= (const Matrix& other) {
	for (size_t i = 0; i < _M; i++) {
		for (size_t j = 0; j < _N; j++) {
			_data[i * _N + j] *= other._data[i * _N + j];
		}
	}
	return *this;
}

template <typename T>
Matrix <T>& Matrix <T>::operator*= (T val) {
	std::cout << "operator *=" << std::endl;
	return *this;
}

//template <typename T>
//T& Matrix<T>::operator [] (size_t index) {
//	return MathVector<T>::operator[](index);
//}

//template <typename T>
//const T& Matrix<T>::operator [] (size_t index) const {
//	return MathVector<T>::operator[](index);
//}

template <typename T>
Matrix<T> Matrix <T>::trans() {
	std::cout << " - transposition matrix" << std::endl;
	return *this;
}

template<typename T>
void Matrix<T>::input_matrix(size_t N, size_t M) {
	this->resize(N, M);
	for (size_t i = 0; i < N; i++) {
		std::cout << "Row " << i + 1 << ": ";
		MathVector<T> row_vector(M);
		row_vector.input_math_vector();

		for (size_t j = 0; j < M; j++) {
			this->_data[i][j] = row_vector[j]; 
		}
	}
}

template<typename T>
void Matrix<T>::print_matrix() const {
	std::cout << "==== RESULT MATRIX ====" << std::endl;
	for (size_t i = 0; i < _N; ++i) {
		for (size_t j = 0; j < _M; ++j) {
			std::cout << _data[i][j] << " "; 
		}
		std::cout << std::endl;
	}
}

template <class T>
std::ostream& operator<< (std::ostream& out, const Matrix<T>& matr) {
	std::cout << "operator<<" << std::endl;
	return out;
}

template <class T>
std::istream& operator>> (std::istream& in, Matrix<T>& matr){
	std::cout << "operator>>" << std::endl;
	return in;
}


#endif  // LIB_MATRIX_MATRIX_H_