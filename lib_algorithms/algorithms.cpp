#include <stdexcept>
#include <random>
#include <cctype>
#include "../lib_algorithms/algorithms.h"

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

		if (isspace(c)) continue;

		if (isdigit(c) || c == 'x' || c == 'y') {
			if (!expect_operand) {
				throw std::invalid_argument("Missing operator before number!");
			}

			if (isdigit(c)) {
				while (i + 1 < expression.length() && isdigit(expression[i + 1])) {
					i++;
				}
			}
			
			expect_operand = false;
		}
		else if (c == '{' || c == '[' || c == '(') {
			if (!expect_operand) {
				throw std::invalid_argument("Missing operator before brecket!");
			}
			stack.push(c);
			expect_operand = true;
		}
		else if (c == '}' || c == ']' || c == ')') {
			if (expect_operand) {
				throw std::invalid_argument("Missing operand!");
			}
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
		else if (c == '+' || c == '-' || c == '*' || c == '^') {
			if (expect_operand) {
				if (c == '-') {
				}
				else {
					throw std::invalid_argument("Invalid use of binary operator!");
				}
			}
			else {
				expect_operand = true;
			}
		}
		else {
			throw std::invalid_argument("Invalid character detected!");
		}
	}
	if (expect_operand) {
		throw std::invalid_argument("Expression ends with operator!");
	}
	if (!stack.is_empty()) {
		throw std::invalid_argument("Unclosed brecket!");
	}
}

int count_of_islands(Matrix<int>& islands) {
	if (islands.size() == 0) return 0;

	int rows = islands.size();
	int cols = islands[0].size();
	DSU dsu(rows * cols);

	int total_land = 0;

	int dx[2] = { 1, 0 };
	int dy[2] = { 0, 1 };

	for (size_t i = 0; i < rows; i++) {
		for (size_t j = 0; j < cols; j++) {
			if (islands[i][j] == 1) {
				total_land++; 
				int cur_index = i * cols + j;

				for (int move = 0; move < 2; move++) {
					int new_row = i + dx[move];
					int new_col = j + dy[move];

					if (new_row < rows && new_col < cols && islands[new_row][new_col] == 1) {
						int neighbor_index = new_row * cols + new_col;

						if (dsu.find(cur_index) != dsu.find(neighbor_index)) {
							dsu.union_dsu(cur_index, neighbor_index);
							total_land--;
						}
					}
				}
			}
		}
	}
	return total_land;
}
