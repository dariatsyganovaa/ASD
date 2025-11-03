#include <stdexcept>
#include <random>
#include <cctype>
#include "../lib_algorithms/algorithms.h"

int local_minimum_of_a_matrix(Matrix<int>& matrix) {
	int rows = matrix.get_rows();
	int cols = matrix.get_cols();

	if (rows != cols) {
		throw std::invalid_argument("The matrix must be square!");
	}

	int random_rows = rand() % rows;
	int random_cols = rand() % cols;

	int dx[4] = { -1, 1, 0, 0 };
	int dy[4] = { 0, 0, -1, 1 };

	while (1) {
		int rand_val = matrix[random_rows][random_cols];

		bool found_better = false;
		int best_row = random_rows;
		int best_col = random_cols;
		int best_val = rand_val;

		for (int move = 0; move < 4; move++) {
			int new_rows = random_rows + dx[move];
			int new_cols = random_cols + dy[move];

			if (new_rows >= 0 && new_rows < rows && new_cols >= 0 && new_cols < cols) {
				int neighbor_val = matrix[new_rows][new_cols];

				if (neighbor_val < rand_val) {
					best_val = neighbor_val;
					best_row = new_rows;
					best_col = new_cols;
					found_better = true;
					break;
				}
			}
		}
		if (!found_better) {
			return rand_val;
		}
		
		random_rows = best_row;
		random_cols = best_col;
	}
}

bool check_breckets(std::string str) {
	Stack<char> stack(str.length());
	for (size_t i = 0; i < str.length(); i++) {
		char c = str[i];
		if (c == '{' || c == '[' || c == '(') {
			stack.push(c);
		}
		else if (c == '}' || c == ']' || c == ')') {
			if (stack.is_empty()) {
				return false;
			}
			char top = stack.top();
			if ((c == ')' && top != '(') || (c == '}' && top != '{') || (c == ']' && top != '[')) {
				return false;
			}
			stack.pop();
		}
	}
	if (!stack.is_empty()) {
		return false;
	}
	return true;
}

void read_expression(std::string expression) {
	Stack<char> stack(expression.length());
	bool expect_operand = true; // если true, то ожидаем число, переменная, унарный -, открывающая скобка 
	// если false, то +, -, *, ^, закрывающая скобка

	for (size_t i = 0; i < expression.length(); i++) {
		char c = expression[i];

		if (isspace(c)) {
			continue;
		}
		if (c == '{' || c == '[' || c == '(') {
			if (!expect_operand) {
				throw std::invalid_argument("Missing operator before brecket!");
			}
			stack.push(c);
			expect_operand = true;
		}
		else if (c == '}' || c == ']' || c == ')') {
			if (stack.is_empty()) {
				throw std::invalid_argument("Missing opened brecket!");
			}
			char top = stack.top();
			if ((c == ')' && top != '(') || (c == '}' && top != '{') || (c == ']' && top != '[')) {
				throw std::invalid_argument("Missing closed brecket!");
			}
			stack.pop();
			expect_operand = false;
		}
		else if (c == 'x' || c == 'y') {
			if (!expect_operand) {
				throw std::invalid_argument("Missing operator before variable!");
			}
			expect_operand = false;
		}
		else if (isdigit(c)) {
			if (!expect_operand) {
				throw std::invalid_argument("Missing operator before number!");
			}

			while (i < expression.length() && isdigit(expression[i])) {
				i++;
			}
			i--;
			expect_operand = false;
		}
		else if (c == '+' || c == '-' || c == '*' || c == '^') {
			if ((expect_operand) && (c == '*' || c == '^')) {
				throw std::invalid_argument("Invalid unary operator!");
			}
			if (c == '^') {
				size_t j = i + 1;
				while (j < expression.length() && isspace(expression[j])) {
					j++;
				}
				if (j >= expression.length() || !isdigit(expression[j])) {
					throw std::invalid_argument("Missing second operand in operation ^ !");
				}
			}
			expect_operand = true;
		}
		else {
			throw std::invalid_argument("Invalid character: '" + std::string(1, c) + "'");
		}
	}
	if (expect_operand) {
		throw std::invalid_argument("Expression ends with operator!");
	}
	if (!stack.is_empty()) {
		throw std::invalid_argument("Unclosed brecket!");
	}
}