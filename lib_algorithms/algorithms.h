#ifndef LIB_ALGORITHMS_ALGORITHMS_H_
#define LIB_ALGORITHMS_ALGORITHMS_H_

#include <iostream>
#include <cstddef>
#include "../lib_matrix/matrix.h"
#include "../lib_stack/stack.h"

int local_minimum_of_a_matrix(Matrix<int>& matrix);

bool check_breckets(std::string str);

void read_expression(std::string expression);

#endif  // LIB_ALGORITHMS_ALGORITHMS_H_