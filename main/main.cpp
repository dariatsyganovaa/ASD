#include <iostream>
#include <iomanip>

#define MATRIX
#ifdef MATRIX

#include "../lib_triangle_matrix/triangle_matrix.h"

void start_add_matrix(Matrix<int>& matrix_1, size_t N1, size_t M1) {
    system("cls");
    std::cout << "==== MATRIX ADDITION ====" << std::endl;

    size_t N2, M2;
    while (1) {
        std::cout << "Enter the size of 2-nd matrix: ";
        std::cin >> N2 >> M2;

        if (N1 != N2 || M1 != M2) {
            std::cout << "Error! The sizes of the matrices must match! " << std::endl;
            continue;
        }
        break;
    }
    Matrix<int> matrix_2(N2, M2);
    matrix_2.input_matrix(N2, M2);

    matrix_1 += matrix_2;
    matrix_1.print_matrix();
    system("pause");
}

void start_sub_matrix(Matrix<int>& matrix_1, size_t N1, size_t M1) {
    system("cls");
    std::cout << "==== MATRIX SUBTRACTION ====" << std::endl;

    size_t N2, M2;
    while (1) {
        std::cout << "Enter the size of 2-nd matrix: ";
        std::cin >> N2 >> M2;

        if (N1 != N2 || M1 != M2) {
            std::cout << "Error! The sizes of the matrices must match! " << std::endl;
            continue;
        }
        break;
    }
    Matrix<int> matrix_2(N2, M2);
    matrix_2.input_matrix(N2, M2);

    matrix_1 = matrix_1 - matrix_2;
    matrix_1.print_matrix();
    system("pause");
}

void start_mult_matrix(Matrix<int>& matrix_1, size_t N1, size_t M1) {
    system("cls");
    std::cout << "==== MATRIX MULTIPLICATION ====" << std::endl;

    size_t N2, M2;
    while (1) {
        std::cout << "Enter the size of 2-nd matrix: ";
        std::cin >> N2 >> M2;
        if (M1 != N2) {
            std::cout << "Error! The number of cols in the 1-st matrix must match the number of rows in the 2-nd matrix! " << std::endl;
            continue;
        }
        break;
    }
    Matrix<int> matrix_2(N2, M2);
    matrix_2.input_matrix(N2, M2);

    matrix_1 *= matrix_2;
    matrix_1.print_matrix();
    system("pause");
}

void start_matrix_scalar_mult(Matrix<int>& matrix_1) {
    system("cls");
    std::cout << "==== MATRIX MULTIPLICATION BY A SCALAR ====" << std::endl;

    int scalar;
    std::cout << "Enter a scalar: ";
    std::cin >> scalar;

    matrix_1 *= scalar;
    matrix_1.print_matrix();
    system("pause");
}

void start_matrix_vec_mult(Matrix<int>& matrix_1, size_t N1, size_t M1) {
    system("cls");
    std::cout << "==== MATRIX MULTIPLICATION BY A VECTOR ====" << std::endl;

    int size;
    while (1) {
        std::cout << "Enter a vector size: ";
        std::cin >> size;
        if (N1 != size) {
            std::cout << "Error! The number of columns of the matrix must be equal to the size of the vector!"<< std::endl;
            continue;
        }
        break;
    }
    
    MathVector<int> vec(size);
    vec.input_math_vector();

    MathVector<int> result = matrix_1 * vec;
    result.print_math_vector();
    system("pause");
}

void start_trans_matrix(Matrix<int>& matrix_1) {
    system("cls");
    std::cout << "==== MATRIX TRANSPOSITION ====" << std::endl;

    matrix_1 = matrix_1.trans();
    matrix_1.print_matrix();
    system("pause");
}

void start_add_tri_matrix(TriangleMatrix<int>& tri_matrix_1, int size) {
    system("cls");
    std::cout << "==== TRIANGULAR MATRIX ADDITION ====" << std::endl;

    TriangleMatrix<int> tri_matrix_2(size);
    tri_matrix_2.input_tri_matrix(size);

    TriangleMatrix<int> result = tri_matrix_1 + tri_matrix_2;
    result.print_tri_matrix();
    system("pause");
}

void start_sub_tri_matrix(TriangleMatrix<int>& tri_matrix_1, int size) {
    system("cls");
    std::cout << "==== TRIANGULAR MATRIX SUBTRACTION ====" << std::endl;

    TriangleMatrix<int> tri_matrix_2(size);
    tri_matrix_2.input_tri_matrix(size);

    TriangleMatrix<int> result = tri_matrix_1 - tri_matrix_2;
    result.print_tri_matrix();
    system("pause");
}

void start_mult_tri_matrix(TriangleMatrix<int>& tri_matrix_1, int size) {
    system("cls");
    std::cout << "==== TRIANGULAR MATRIX MULTIPLICATION ====" << std::endl;

    TriangleMatrix<int> tri_matrix_2(size);
    tri_matrix_2.input_tri_matrix(size);

    TriangleMatrix<int> result = tri_matrix_1 * tri_matrix_2;
    result.print_tri_matrix();
    system("pause");
}

void start_tri_matrix_scalar_mult(TriangleMatrix<int>& tri_matrix_1) {
    system("cls");
    std::cout << "==== TRIANGULAR MATRIX MULTIPLICATION BY A SCALAR ====" << std::endl;

    int scalar;
    std::cout << "Enter a scalar: ";
    std::cin >> scalar;

    TriangleMatrix<int> result = tri_matrix_1 * scalar;
    result.print_tri_matrix();
    system("pause");
}

void start_type_tri_matrix(TriangleMatrix<int>& tri_matrix_1) {
    system("cls");
    std::cout << "==== TRIANGULAR MATRIX TYPE ====" << std::endl;
    tri_matrix_1.status();
    system("pause");
}

void MatrixOperations() {
    size_t N1, M1;
    std::cout << "Specify the size of the matrix, where N is the number of rows, M is the number of cols" << std::endl;
    std::cout << "Enter the size of 1-st matrix separated by a space: ";
    std::cin >> N1 >> M1;
    Matrix <int> matrix_1(N1, M1);
    matrix_1.input_matrix(N1, M1);
    
    system("pause");

    while (1) {
        system("cls");

        std::cout << "==== MATRIX CALCULATOR ====" << std::endl;
        matrix_1.print_matrix();

        std::cout << "Choose:\n1. Add \n2. Sub \n3. Mult \n4. Mult by a scalar \n5. Mult by a vector \n6. Transposition \n0. Back to main menu\nYour: ";

        int user;
        std::cin >> user;

        if (user == 0) break;

        switch (user) {
        case 1: {
            start_add_matrix(matrix_1, N1, M1);
            break;
        }
        case 2: {
            start_sub_matrix(matrix_1, N1, M1);
            break;
        } 
        case 3: {
            start_mult_matrix(matrix_1, N1, M1);
            break;
        }
        case 4: {
            start_matrix_scalar_mult(matrix_1);
            break;
        }
        case 5: {
            start_matrix_vec_mult(matrix_1, N1, M1);
            break;
        }
        case 6: {
            start_trans_matrix(matrix_1);
            break;
        }
        default:
            std::cout << "Wrong input!\n";
            system("pause");
            break;
        }
    }
}

void TriangleMatrixOperations() {
    int size;
    std::cout << "Enter the size of triangular matrix: ";
    std::cin >> size;

    TriangleMatrix<int> tri_matrix_1(size);
    tri_matrix_1.input_tri_matrix(size);
    system("pause");

    while (1) {
        system("cls");
        std::cout << "==== TRIANGULAR MATRIX CALCULATOR ====" << std::endl;
        tri_matrix_1.print_tri_matrix();
        std::cout << "Choose:\n1. Add \n2. Sub \n3. Mult \n4. Mult by a scalar \n5. Status \n0. Back to main menu\nYour: ";

        int user;
        std::cin >> user;

        if (user == 0) break;

        switch (user) {
        case 1: {
            start_add_tri_matrix(tri_matrix_1, size);
            break;
        }
        case 2: {
            start_sub_tri_matrix(tri_matrix_1, size);
            break;
        }
        case 3: {
            start_mult_tri_matrix(tri_matrix_1, size);
            break;
        }
        case 4: {
            start_tri_matrix_scalar_mult(tri_matrix_1);
            break;
        }
        case 5: {
            start_type_tri_matrix(tri_matrix_1);
            break;
        }
        default:
            std::cout << "Wrong input!\n";
            system("pause");
            break;

        }
    }
}

int main() {
    while (1) {
        system("cls");

        std::cout << "==== MATRIX CALCULATOR ====" << std::endl;
        std::cout << "Choose:\n1. Matrix \n2. Triangle Matrix \n0. Exit\nYour: ";

        int choose;
        std::cin >> choose;

        if (choose == 0) break;

        switch (choose) {
        case 1:
            MatrixOperations();
            break;
        case 2:
            TriangleMatrixOperations();
            break;
        default:
            std::cout << "Wrong input!\n";
            break;
        }
    }
    return 0;
}

#endif  // MATRIX
