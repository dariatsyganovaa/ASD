#include <iostream>
#include <iomanip>

#define MATRIX
#ifndef MATRIX

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

#define LEXEM
#ifndef LEXEM

#include "../lib_tvector/tvector.h"
#include "../lib_expression/expression.h"
#include "../lib_parser/parser.h"

TVector<Expression*> expressions;

void print_separator() {
    std::cout << "+------+------------------------------------------+--------------------------------+" << std::endl;
}

void print_header() {
    print_separator();
    std::cout << "| " << std::setw(4) << std::left << "ID"
        << " | " << std::setw(40) << "EXPRESSION"
        << " | " << std::setw(30) << "VARIABLES VALUES" << " |" << std::endl;
    print_separator();
}

void create_new_expression() {
    std::string input;
    std::cout << "Input expression: ";
    std::cin.ignore(); // Очистка буфера перед getline
    std::getline(std::cin, input);

    if (input.empty()) return;

    try {
        // Пытаемся создать выражение (внутри вызовется Parser::parse)
        Expression* new_expr = new Expression(input);
        expressions.push_back_elem(new_expr);
        std::cout << "Expression added successfully.\n";
    }
    catch (const ParserException& e) {
        // Форматированный вывод ошибки по ТЗ
        std::cout << "Input expression: " << input << std::endl;
        std::cout << "                  "; // Отступ для Input expression: 
        for (int i = 0; i < e.get_pos(); ++i) std::cout << " ";
        std::cout << "^" << std::endl;
        std::cout << "Error in function 'Parser::parse()' at " << e.get_pos() << " symbol: " << e.what() << std::endl;
    }
    catch (const std::exception& e) {
        std::cout << "Critical error: " << e.what() << std::endl;
    }
    system("pause");
}

void delete_expression_ui() {
    int id;
    std::cout << "Enter ID to delete: ";
    std::cin >> id;

    if (id >= 1 && id <= (int)expressions.size()) {
        // Удаляем объект из памяти
        delete expressions[id - 1];
        // Удаляем указатель из вектора (сдвиг элементов)
        expressions.erase_elem(id - 1);
        std::cout << "Deleted.\n";
    }
    else {
        std::cout << "Expression with ID " << id << " not found.\n";
    }
    system("pause");
}

void set_variables_ui() {
    int id;
    std::cout << "Enter ID to set variables: ";
    std::cin >> id;

    if (id >= 1 && id <= (int)expressions.size()) {
        expressions[id - 1]->set_variables();
    }
    else {
        std::cout << "Expression with ID " << id << " not found.\n";
        system("pause");
    }
}

void calculate_expression_ui() {
    int id;
    std::cout << "Enter ID to calculate: ";
    std::cin >> id;

    if (id >= 1 && id <= (int)expressions.size()) {
        double res = expressions[id - 1]->calculate();
        std::cout << "Result: " << res << std::endl;
    }
    else {
        std::cout << "Expression with ID " << id << " not found.\n";
    }
    system("pause");
}

int main() {
    while (true) {
        system("cls"); // Очистка экрана (Windows)

        print_header();

        // Вывод таблицы
        if (expressions.size() == 0) {
            std::cout << "| " << std::setw(78) << std::left << "List is empty" << " |" << std::endl;
        }
        else {
            for (size_t i = 0; i < expressions.size(); ++i) {
                // Обрезаем строку, если она слишком длинная для таблицы
                std::string expr_str = expressions[i]->get_expression_str();
                if (expr_str.length() > 40) expr_str = expr_str.substr(0, 37) + "...";

                std::string var_str = expressions[i]->get_variables_str();
                if (var_str.length() > 30) var_str = var_str.substr(0, 27) + "...";

                std::cout << "| " << std::setw(4) << std::left << (i + 1)
                    << " | " << std::setw(40) << expr_str
                    << " | " << std::setw(30) << var_str << " |" << std::endl;
            }
        }
        print_separator();

        std::cout << "\nMENU:\n"
            << "1. Create a new expression\n"
            << "2. Delete expression\n"
            << "3. Set variables\n"
            << "4. Calculate the value of an expression\n"
            << "0. Exit\n"
            << "Your choice: ";

        int choice;
        // Проверка на корректный ввод числа
        if (!(std::cin >> choice)) {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            continue;
        }

        if (choice == 0) break;

        switch (choice) {
        case 1: create_new_expression(); break;
        case 2: delete_expression_ui(); break;
        case 3: set_variables_ui(); break;
        case 4: calculate_expression_ui(); break;
        default:
            std::cout << "Wrong input!\n";
            system("pause");
            break;
        }
    }

    // Очистка памяти перед выходом
    for (size_t i = 0; i < expressions.size(); ++i) {
        delete expressions[i];
    }

    return 0;
}
#endif  // LEXEM

