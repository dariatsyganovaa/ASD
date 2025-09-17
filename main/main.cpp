#include <iostream>
#include <iomanip>

#define MATRIX

#ifdef MATRIX

#include "../lib_matrix/matrix.h"

void start_main_menu();

template <typename T>
void start_add_matrix(int N1, int N2, int M1, int M2);

template <typename T>
void start_sub_matrix(int N1, int N2, int M1, int M2);

template <typename T>
void start_mult_matrix(int N1, int N2, int M1, int M2);

int main() {
    start_main_menu();
    return 0;
}

void start_main_menu() {
    int N1, M1, N2, M2;
    std::cout << "Hello! Specify the size of the matrix, where N is the number of rows, M is the number of columns" << std::endl;

    std::cout << "Enter the size of your first matrix separated by a space: ";
    std::cin >> N1 >> M1;
    std::cout << "The size of your first matrix: " << N1 << " x " << M1 << std::endl;

    std::cout << "Enter the size of your second matrix separated by a space: ";
    std::cin >> N2 >> M2;
    std::cout << "The size of your second matrix: " << N2 << " x " << M2 << std::endl << std::endl;

    char operation;
    while (1) {
        system("cls");

        std::cout << "==== MATRIX CALCILATOR ====" << std::endl;
        std::cout << "Matrix 1: " << N1 << " x " << M1 << std::endl;
        std::cout << "Matrix 2: " << N2 << " x " << M2 << std::endl;
        std::cout << "===========================" << std::endl;

        std::cout << "Select operation (+, -, *)" << std::endl;
        std::cout << "Your choice: ";
        std::cin >> operation;

        switch (operation) {
        case '+':
            start_add_matrix<int>(N1, N2, M1, M2);
            break;
        case '-':
            start_sub_matrix<int>(N1, N2, M1, M2);
            break;
        case '*':
            start_mult_matrix<int>(N1, N2, M1, M2);
            break;
        case '0':
            std::cout << "Goodbye!" << std::endl;
            return;
        default:
            std::cout << "Invalid operation! Try again! " << std::endl;
            system("pause");
            break;
        }
    }
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
