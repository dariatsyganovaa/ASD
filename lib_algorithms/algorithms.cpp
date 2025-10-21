#include <stdexcept>
#include <random>
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
	for (size_t i = 0; i < expression.length(); i++) {
		char c = expression[i];

		if (c == '{' || c == '[' || c == '(') {
			stack.push(c);
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
		}

		if (c == 'x' || c == 'y') {
			stack.push(c);
		}
		if (!stack.is_empty()) {
			char top = stack.top();
			if ((top == 'x' || top == 'y') && (i + 1 < expression.length())) {
				char next_c = expression[i + 1];
				if (next_c != '+' && next_c != '-' && next_c != '*') {
					throw std::invalid_argument("Missing operation!");
				}
				
			}
		}
	}
}