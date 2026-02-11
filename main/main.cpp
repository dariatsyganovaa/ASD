#include <iostream>
#include <iomanip>

#define MATRIX
#ifdef MATRIX

#include "../lib_triangle_matrix/triangle_matrix.h"

void start_add_matrix(Matrix<int>& matrix_1) {
    system("cls");
    std::cout << "==== MATRIX ADDITION ====" << std::endl;

    size_t N2, M2;
    while (1) {
        std::cout << "Enter the size of 2-nd matrix: ";
        std::cin >> N2 >> M2;

        if (matrix_1.get_rows() != N2 || matrix_1.get_cols() != M2) {
            std::cout << "Error! The sizes of the matrices must match! " << std::endl;
            continue;
        }
        break;
    }
    Matrix<int> matrix_2(N2, M2);
    std::cin >> matrix_2;

    matrix_1 += matrix_2;
    std::cout << matrix_1;
    system("pause");
}

void start_sub_matrix(Matrix<int>& matrix_1) {
    system("cls");
    std::cout << "==== MATRIX SUBTRACTION ====" << std::endl;

    size_t N2, M2;
    while (1) {
        std::cout << "Enter the size of 2-nd matrix: ";
        std::cin >> N2 >> M2;

        if (matrix_1.get_rows() != N2 || matrix_1.get_cols() != M2) {
            std::cout << "Error! The sizes of the matrices must match! " << std::endl;
            continue;
        }
        break;
    }
    Matrix<int> matrix_2(N2, M2);
    std::cin >> matrix_2;

    matrix_1 = matrix_1 - matrix_2;
    std::cout << matrix_1;
    system("pause");
}

void start_mult_matrix(Matrix<int>& matrix_1) {
    system("cls");
    std::cout << "==== MATRIX MULTIPLICATION ====" << std::endl;

    size_t N2, M2;
    while (1) {
        std::cout << "Enter the size of 2-nd matrix: ";
        std::cin >> N2 >> M2;
        if (matrix_1.get_cols() != N2) {
            std::cout << "Error! The number of cols in the 1-st matrix must match the number of rows in the 2-nd matrix! " << std::endl;
            continue;
        }
        break;
    }
    Matrix<int> matrix_2(N2, M2);
    std::cin >> matrix_2;

    matrix_1 *= matrix_2;
    std::cout << matrix_1;
    system("pause");
}

void start_matrix_scalar_mult(Matrix<int>& matrix_1) {
    system("cls");
    std::cout << "==== MATRIX MULTIPLICATION BY A SCALAR ====" << std::endl;

    int scalar;
    std::cout << "Enter a scalar: ";
    std::cin >> scalar;

    matrix_1 *= scalar;
    std::cout << matrix_1;
    system("pause");
}

void start_matrix_vec_mult(Matrix<int>& matrix_1) {
    system("cls");
    std::cout << "==== MATRIX MULTIPLICATION BY A VECTOR ====" << std::endl;

    int size;
    while (1) {
        std::cout << "Enter a vector size: ";
        std::cin >> size;
        if (matrix_1.get_rows() != size) {
            std::cout << "Error! The number of columns of the matrix must be equal to the size of the vector!"<< std::endl;
            continue;
        }
        break;
    }
    
    MathVector<int> vec(size);
    std::cin >> vec;

    std::cout << "Vector elements: ";
    vec = matrix_1 * vec;
    std::cout << vec;
    system("pause");
}

void start_trans_matrix(Matrix<int>& matrix_1) {
    system("cls");
    std::cout << "==== MATRIX TRANSPOSITION ====" << std::endl;

    matrix_1 = matrix_1.trans();
    std::cout << matrix_1;
    system("pause");
}

void start_comparison_of_matrices(Matrix<int>& matrix_1) {
    system("cls");
    std::cout << "==== COMPARISON OF MATRICES ====" << std::endl;

    size_t N2, M2;
    while (1) {
        std::cout << "Enter the size of 2-nd matrix: ";
        std::cin >> N2 >> M2;
        if (matrix_1.get_rows() != N2 || matrix_1.get_cols() != M2) {
            std::cout << "Error! The sizes of the matrices must match! " << std::endl;
            continue;
        }
        break;
    }
    Matrix<int> matrix_2(N2, M2);
    std::cin >> matrix_2;

    bool isComp = (matrix_1 == matrix_2);
    if (isComp == true) {
        std::cout << "The matrices are equal! " << std::endl;
    }
    else {
        std::cout << "The matrices are not equal! " << std::endl;
    }
    system("pause");
}

void start_add_tri_matrix(TriangleMatrix<int>& tri_matrix_1) {
    system("cls");
    std::cout << "==== TRIANGULAR MATRIX ADDITION ====" << std::endl;
    
    TriangleMatrix<int> tri_matrix_2;
    std::cin >> tri_matrix_2;

    try {
        tri_matrix_1 += tri_matrix_2;
        std::cout << tri_matrix_1;
    }
    catch (const std::exception& ex) {
        std::cerr << ex.what() << std::endl;
    }
    
    system("pause");
}

void start_sub_tri_matrix(TriangleMatrix<int>& tri_matrix_1) {
    system("cls");
    std::cout << "==== TRIANGULAR MATRIX SUBTRACTION ====" << std::endl;

    TriangleMatrix<int> tri_matrix_2;
    std::cin >> tri_matrix_2;

    try {
        tri_matrix_1 -= tri_matrix_2;
        std::cout << tri_matrix_1;
    }
    catch (const std::exception& ex) {
        std::cerr << ex.what() << std::endl;
    }

    system("pause");
}

void start_mult_tri_matrix(TriangleMatrix<int>& tri_matrix_1) {
    system("cls");
    std::cout << "==== TRIANGULAR MATRIX MULTIPLICATION ====" << std::endl;

    TriangleMatrix<int> tri_matrix_2;
    std::cin >> tri_matrix_2;

    try {
        tri_matrix_1 *= tri_matrix_2;
        std::cout << tri_matrix_1;
    }
    catch (const std::exception& ex) {
        std::cerr << ex.what() << std::endl;
    }

    system("pause");
}

void start_tri_matrix_vec_mult(TriangleMatrix<int>& tri_matrix_1) {
    system("cls");
    std::cout << "==== TRIANGULAR MATRIX MULTIPLICATION BY A VECTOR ====" << std::endl;

    int size; 
    std::cout << "Enter a vector size: ";
    std::cin >> size;
       
    MathVector<int> vec(size);
    std::cin >> vec;

    try {
        vec = tri_matrix_1 * vec;

        std::cout << "Vector elements: ";
        std::cout << vec;
    }
    catch (const std::exception& ex) {
        std::cerr << ex.what() << std::endl;
    }

    system("pause");
}

void start_tri_matrix_scalar_mult(TriangleMatrix<int>& tri_matrix_1) {
    system("cls");
    std::cout << "==== TRIANGULAR MATRIX MULTIPLICATION BY A SCALAR ====" << std::endl;

    int scalar;
    std::cout << "Enter a scalar: ";
    std::cin >> scalar;

    try {
        tri_matrix_1 *= scalar;
        std::cout << tri_matrix_1;
    }
    catch (const std::exception& ex) {
        std::cerr << ex.what() << std::endl;
    }

    system("pause");
}

void start_comparison_of_tri_matrices(TriangleMatrix<int>& tri_matrix_1) {
    system("cls");
    std::cout << "==== COMPARISON OF MATRICES ====" << std::endl;

    TriangleMatrix<int> tri_matrix_2;
    std::cin >> tri_matrix_2;

    bool isComp = (tri_matrix_1 == tri_matrix_2);
    if (isComp == true) {
        std::cout << "The matrices are equal! " << std::endl;
    }
    else {
        std::cout << "The matrices are not equal! " << std::endl;
    }
    system("pause");
}

void MatrixOperations() {
    size_t N1, M1;
    std::cout << "Specify the size of the matrix, where N is the number of rows, M is the number of cols" << std::endl;
    std::cout << "Enter the size of 1-st matrix separated by a space: ";
    std::cin >> N1 >> M1;
    Matrix <int> matrix_1(N1, M1);
    std::cin >> matrix_1;
    
    system("pause");
    while (1) {
        system("cls");

        std::cout << "==== MATRIX CALCULATOR ====" << std::endl;
        std::cout << matrix_1;

        std::cout << "Choose:\n1. Add \n2. Sub \n3. Mult \n4. Mult by a scalar \n5. Mult by a vector \n6. Transposition \n7. Comparison \n0. Back to main menu\nYour: ";

        int user;
        std::cin >> user;

        if (user == 0) break;

        switch (user) {
        case 1: {
            start_add_matrix(matrix_1);
            break;
        }
        case 2: {
            start_sub_matrix(matrix_1);
            break;
        } 
        case 3: {
            start_mult_matrix(matrix_1);
            break;
        }
        case 4: {
            start_matrix_scalar_mult(matrix_1);
            break;
        }
        case 5: {
            start_matrix_vec_mult(matrix_1);
            break;
        }
        case 6: {
            start_trans_matrix(matrix_1);
            break;
        }
        case 7: {
            start_comparison_of_matrices(matrix_1);
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
    TriangleMatrix<int> tri_matrix_1;
    std::cin >> tri_matrix_1;

    if (tri_matrix_1.get_size() == 0) {
        std::cout << "Error: Matrix input failed!" << std::endl;
        system("pause");
        return;
    }

    system("pause");
    while (1) {
        system("cls");
        std::cout << "==== TRIANGULAR MATRIX CALCULATOR ====" << std::endl;
        std::cout << tri_matrix_1;
        std::cout << "Choose:\n1. Add \n2. Sub \n3. Mult \n4. Mult by a scalar \n5. Mult by a vector \n6. Comparison \n0. Back to main menu\nYour: ";

        int user;
        std::cin >> user;

        if (user == 0) break;

        switch (user) {
        case 1: {
            start_add_tri_matrix(tri_matrix_1);
            break;
        }
        case 2: {
            start_sub_tri_matrix(tri_matrix_1);
            break;
        }
        case 3: {
            start_mult_tri_matrix(tri_matrix_1);
            break;
        }
        case 4: {
            start_tri_matrix_scalar_mult(tri_matrix_1);
            break;
        }
        case 5: {
            start_tri_matrix_vec_mult(tri_matrix_1);
            break;
        }
        case 6: {
            start_comparison_of_tri_matrices(tri_matrix_1);
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
