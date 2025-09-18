#include <iostream>
#include <iomanip>

#define MATRIX

#ifdef MATRIX

#include "../lib_triangle_matrix/triangle_matrix.h"

typedef int TYPE;

template <typename T>
void start_add_matrix(int N1, int N2, int M1, int M2);

template <typename T>
void start_sub_matrix(int N1, int N2, int M1, int M2);

template <typename T>
void start_mult_matrix(int N1, int N2, int M1, int M2);

int main() {
    int N1, M1, N2, M2;
    int user;

    TYPE result;

    std::cout << "Hello! Specify the size of the matrix, where N is the number of rows, M is the number of columns" << std::endl;

    std::cout << "Enter the size of your first matrix separated by a space: ";
    std::cin >> N1 >> M1;

    std::cout << "Enter the size of your second matrix separated by a space: ";
    std::cin >> N2 >> M2;

    TriangleMatrix <TYPE> matrix_1(N1);
    TriangleMatrix <TYPE> matrix_2(N2);

    char operation;
    while (1) {
        system("cls");

        std::cout << "==== MATRIX CALCULATOR ====" << std::endl;
        std::cout << "Choose:\n1. func\n2. foo\n3. output\n0. exit\nYour: ";
        std::cout << "===========================" << std::endl;


        if (user == 0) break;

        switch (user) {
        case 1:
            matrix_1.func();
            break;
        case 2:
            result = matrix_1.foo();
            std::cout << "Result is " << result << ".\n";
            break;
        case 3:
            std::cout << matrix_1;
            break;
        default:
            std::cout << "Wrong input!\n";
            break;
        }
    }
    return 0;
}

template <typename T>
void start_add_matrix(int N1, int N2, int M1, int M2) {
    system("cls");
    std::cout << "==== MATRIX ADDITION ====" << std::endl;
 
    try {
        Matrix<T> matrix_1(N1, M1);
        Matrix<T> matrix_2(N2, M2);

        Matrix<T> result = matrix_1 + matrix_2;
    }
    catch (const std::exception& e){
        std::cout << "Error: " << e.what() << std::endl;
    }
    
}

template <typename T>
void start_sub_matrix(int N1, int N2, int M1, int M2) {
    system("cls");
    std::cout << "==== MATRIX SUBTRACTION ====" << std::endl;

    try {
        Matrix<T> matrix_1(N1, M1);
        Matrix<T> matrix_2(N2, M2);

        Matrix<T> result = matrix_1 - matrix_2;
    }
    catch (const std::exception& e) {
        std::cout << "Error: " << e.what() << std::endl;
    }
}

template <typename T>
void start_mult_matrix(int N1, int N2, int M1, int M2) {
    system("cls");

    std::cout << "==== MATRIX MULTIPLICATION ====" << std::endl;

    try {
        Matrix<T> matrix_1(N1, M1);
        Matrix<T> matrix_2(N2, M2);

        Matrix<T> result = matrix_1 * matrix_2;
    }
    catch (const std::exception& e) {
        std::cout << "Error: " << e.what() << std::endl;
    }
}

#endif  // MATRIX
