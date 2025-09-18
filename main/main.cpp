#include <iostream>
#include <iomanip>

#define MATRIX

#ifdef MATRIX

#include "../lib_triangle_matrix/triangle_matrix.h"

int main() {
    int N1, M1;
    int user;

    std::cout << "Specify the size of the matrix, where N is the number of rows, M is the number of cols" << std::endl;

    std::cout << "Enter the size of 1-st matrix separated by a space: ";
    std::cin >> N1 >> M1;
    Matrix <int> matrix_1(N1, M1);
    matrix_1.input_matrix();
    system("pause");

    while (1) {       
        system("cls");
        std::cout << "==== MATRIX CALCULATOR ====" << std::endl;
        std::cout << "Choose:\n1. add \n2. sub \n3. mult \n4. mult by a scalar \n5. transposition \n0. exit\nYour: ";
        std::cin >> user;
        std::cout << "===========================" << std::endl;
        
        int N2, M2;

        if (user == 0) break;

        switch (user) {
        case 1:
            system("cls");
            std::cout << "==== MATRIX ADDITION ====" << std::endl;

            while (1) {
                std::cout << "Enter the size of 2-nd matrix: ";
                std::cin >> N2 >> M2;
                if (N1 != N2 || M1 != M2) {
                    std::cout << "Error! The sizes of the matrices must match! ";
                    continue;
                }
                Matrix<int> matrix_2(N2, M2);
                matrix_2.input_matrix();

                Matrix<int> result = matrix_1 + matrix_2;
                result.print_matrix();
                system("pause");
                break;
            }
            break;
        case 2:
            system("cls");
            std::cout << "==== MATRIX SUBTRACTION ====" << std::endl;

            while (1) {
                std::cout << "Enter the size of 2-nd matrix: ";
                std::cin >> N2 >> M2;
                if (N1 != N2 || M1 != M2) {
                    std::cout << "Error! The sizes of the matrices must match! ";
                    continue;
                }
                Matrix<int> matrix_2(N2, M2);
                matrix_2.input_matrix();

                Matrix<int> result = matrix_1 - matrix_2;
                result.print_matrix();
                system("pause");
                break;
            }
            break;
        case 3:
            system("cls");
            std::cout << "==== MATRIX MULTIPLICATION ====" << std::endl;

            while (1) {
                std::cout << "Enter the size of 2-nd matrix: ";
                std::cin >> N2 >> M2;
                if (M1 != N2) {
                    std::cout << "Error! The number of cols in the 1-st matrix must match the number of rows in the 2-nd matrix! ";
                    continue;
                }
                Matrix<int> matrix_2(N2, M2);
                matrix_2.input_matrix();

                Matrix<int> result = matrix_1 * matrix_2;
                result.print_matrix();
                system("pause");
                break;
            }
            break;

        case 4:
            system("cls");
            std::cout << "==== MATRIX MULTIPLICATION BY A SCALAR ====" << std::endl;

            while (1) {
                std::cout << "Enter a scalar: ";
                int scalar;
                std::cin >> scalar;
                Matrix<int> result = matrix_1 * scalar;

                result.print_matrix();
                system("pause");
                break;
            }
            break;
        case 5:
            system("cls");
            std::cout << "==== MATRIX TRANSPOSITION ====" << std::endl;

            while (1) {
                matrix_1.trans();
                matrix_1.print_matrix();
                system("pause");
                break;
            }
            break;

        default:
            std::cout << "Wrong input!\n";
            system("pause");
            break;
        }
    }
    return 0;
}

#endif  // MATRIX
