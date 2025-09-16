#ifndef LIB_MATRIX_MATRIX_H_
#define LIB_MATRIX_MATRIX_H_
#include <cstddef>
#include "../lib_mathvector/mathvector.h"

template <typename T>
class Matrix : public MathVector <MathVector <T>>{
	size_t _N;
	size_t _M;
public:
	Matrix(size_t N, size_t M) : MathVector <MathVector <T>>(N), _N(N), _M(M) {
		for (size_t i = 0; i < N; i++) {
			_data[i] = new MathVector<T>(M);
		}
	}
};


#endif  // LIB_MATRIX_MATRIX_H_