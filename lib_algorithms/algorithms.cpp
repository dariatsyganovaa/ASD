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