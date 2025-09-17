#include <iostream>
#include <iomanip>

#define MATRIX

#ifdef MATRIX

#include "../lib_matrix/matrix.h"

template <typename T>
Matrix <T> add_matrix(Matrix <T> matrix_1, Matrix <T> matrix_2) {
    Matrix <T> result;
    std::cout << "TBD add_matrix";
    return result;
}

template <typename T>
Matrix <T> sub_matrix(Matrix <T> matrix_1, Matrix <T> matrix_2) {
    Matrix <T> result;
    std::cout << "TBD sub_matrix";
    return result;
}

template <typename T>
Matrix <T> mult_matrix(Matrix <T> matrix_1, Matrix <T> matrix_2) {
    Matrix <T> result;
    std::cout << "TBD mult_matrix";
    return result;
}

int main() {
    int N1, M1;
    int N2, M2;
    std::cout << "Hello! Specify the size of the matrix, where N is the number of rows, M is the number of columns" << std::endl;

    std::cout << "Enter the size of your first matrix separated by a space: ";
    std::cin >> N1 >> M1;
    std::cout << "The size of your first matrix: " << N1 << "*" << M1 << std::endl;

    std::cout << "Enter the size of your second matrix separated by a space: ";
    std::cin >> N2 >> M2;
    std::cout << "The size of your second matrix: " << N2 << "*" << M2 << std::endl << std::endl;

    std::cout << "Select operation (+, -, *) : " << std::endl;
    char operation;
    std::cin >> operation;

    Matrix<int> matrix_1(N1, M1);
    Matrix<int> matrix_2(N2, M2);
    switch (operation) {
    case '+':
        add_matrix(matrix_1, matrix_2);
        break;
    case '-':
        sub_matrix(matrix_1, matrix_2);
        break;
    case '*':
        mult_matrix(matrix_1, matrix_2);
        break;
    }

    return 0;
}

#endif  // MATRIX
