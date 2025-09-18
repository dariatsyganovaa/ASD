#include <iostream>
#include <iomanip>

#define MATRIX

#ifdef MATRIX

#include "../lib_triangle_matrix/triangle_matrix.h"

void MatrixOperations() {
    int N1, M1;
    std::cout << "Specify the size of the matrix, where N is the number of rows, M is the number of cols" << std::endl;
    std::cout << "Enter the size of 1-st matrix separated by a space: ";
    std::cin >> N1 >> M1;
    Matrix <int> matrix_1(N1, M1);
    matrix_1.input_matrix();

    while (1) {
        system("cls");

        std::cout << "==== MATRIX CALCULATOR ====" << std::endl;
        std::cout << "Choose:\n1. add \n2. sub \n3. mult \n4. mult by a scalar \n5. transposition \n0. back to main menu\nYour: ";

        int user;
        std::cin >> user;

        if (user == 0) break;

        switch (user) {
        case 1: {
            system("cls");
            std::cout << "==== MATRIX ADDITION ====" << std::endl;

            int N2, M2;
            while (1) {
                std::cout << "Enter the size of 2-nd matrix: ";
                std::cin >> N2 >> M2;

                if (N1 != N2 || M1 != M2) {
                    std::cout << "Error! The sizes of the matrices must match! ";
                    continue;
                }
                break;
            }
            Matrix<int> matrix_2(N2, M2);
            matrix_2.input_matrix();

            Matrix<int> result = matrix_1 + matrix_2;
            result.print_matrix();
            system("pause");

            break;
        }
            
        case 2: {
            system("cls");
            std::cout << "==== MATRIX SUBTRACTION ====" << std::endl;

            int N2, M2;
            while (1) {
                std::cout << "Enter the size of 2-nd matrix: ";
                std::cin >> N2 >> M2;

                if (N1 != N2 || M1 != M2) {
                    std::cout << "Error! The sizes of the matrices must match! ";
                    continue;
                }
                break;
            }
            Matrix<int> matrix_2(N2, M2);
            matrix_2.input_matrix();

            Matrix<int> result = matrix_1 - matrix_2;
            result.print_matrix();
            system("pause");

            break;
        }
            
        case 3: {
            system("cls");
            std::cout << "==== MATRIX MULTIPLICATION ====" << std::endl;

            int N2, M2;
            while (1) {
                std::cout << "Enter the size of 2-nd matrix: ";
                std::cin >> N2 >> M2;
                if (M1 != N2) {
                    std::cout << "Error! The number of cols in the 1-st matrix must match the number of rows in the 2-nd matrix! ";
                    continue;
                }
                break;
            }
            Matrix<int> matrix_2(N2, M2);
            matrix_2.input_matrix();

            Matrix<int> result = matrix_1 * matrix_2;
            result.print_matrix();
            system("pause");

            break;
        }

        case 4: {
            system("cls");
            std::cout << "==== MATRIX MULTIPLICATION BY A SCALAR ====" << std::endl;

            int scalar;
            std::cout << "Enter a scalar: ";
            std::cin >> scalar;

            Matrix<int> result = matrix_1 * scalar;
            result.print_matrix();
            system("pause");

            break;
        }
            
        case 5: {
            system("cls");
            std::cout << "==== MATRIX TRANSPOSITION ====" << std::endl;

            matrix_1.trans();
            matrix_1.print_matrix();
            system("pause");

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
    int size_1;
    std::cout << "Enter the size of 1-st matrix: ";
    std::cin >> size_1;

    TriangleMatrix<int> tri_matrix_1(size_1);
    tri_matrix_1.input_matrix();

    while (1) {
        system("cls");
        std::cout << "==== TRIANGULAR MATRIX CALCULATOR ====" << std::endl;
        std::cout << "Choose:\n1. add \n2. sub \n3. mult \n4. mult by a scalar \n5. status \n0. back to main menu\nYour: ";

        int user;
        std::cin >> user;

        if (user == 0) break;

        switch (user) {
        case 1: {
            system("cls");
            std::cout << "==== TRIANGULAR MATRIX ADDITION ====" << std::endl;

            int size_2;
            while (1) {
                std::cout << "Enter the size of 2-nd matrix: ";
                std::cin >> size_2;

                if (size_1 != size_2) { 
                    std::cout << "Error! The sizes of the matrices must match! ";
                    continue;
                }
                break;
            }
            TriangleMatrix<int> tri_matrix_2(size_2);
            tri_matrix_2.input_tri_matrix();

            TriangleMatrix<int> result = tri_matrix_1 + tri_matrix_2;
            result.print_tri_matrix();
            system("pause");

            break;
        }
        case 2: {
            system("cls");
            std::cout << "==== TRIANGULAR MATRIX SUBTRACTION ====" << std::endl;

            int size_2;
            while (1) {
                std::cout << "Enter the size of 2-nd matrix: ";
                std::cin >> size_2;

                if (size_1 != size_2) { 
                    std::cout << "Error! The sizes of the matrices must match! ";
                    continue;
                }
                break;
            }
            TriangleMatrix<int> tri_matrix_2(size_2);
            tri_matrix_2.input_tri_matrix();

            TriangleMatrix<int> result = tri_matrix_1 - tri_matrix_2;
            result.print_tri_matrix();
            system("pause");

            break;
        }
        case 3: {
            system("cls");
            std::cout << "==== TRIANGULAR MATRIX MULTIPLICATION ====" << std::endl;

            int size_2;
            while (1) {
                std::cout << "Enter the size of 2-nd matrix: ";
                std::cin >> size_2;

                if (size_1 != size_2) { //??
                    std::cout << "Error! The sizes of the matrices must match! ";
                    continue;
                }
                break;
            }
            TriangleMatrix<int> tri_matrix_2(size_2);
            tri_matrix_2.input_tri_matrix();

            TriangleMatrix<int> result = tri_matrix_1 * tri_matrix_2;
            result.print_tri_matrix();
            system("pause");

            break;
        }
        case 4: {
            system("cls");
            std::cout << "==== TRIANGULAR MATRIX MULTIPLICATION BY A SCALAR ====" << std::endl;

            int scalar;
            std::cout << "Enter a scalar: ";
            std::cin >> scalar;

            TriangleMatrix<int> result = tri_matrix_1 * scalar;
            result.print_tri_matrix();
            system("pause");

            break;
        }
        case 5: {
            system("cls");
            std::cout << "==== TRIANGULAR MATRIX TYPE ====" << std::endl;
            tri_matrix_1.status();
            system("pause");
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
