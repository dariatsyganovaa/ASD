#ifndef LIB_PARSER_PARSER_H_
#define LIB_PARSER_PARSER_H_

#include "..\lib_list\list.h"
#include "..\lib_lexem\lexem.h"
#include "..\lib_stack\stack.h"
#include <stdexcept>
#include <string>
#include <cctype>
#include <cfloat>
#include <cmath>

class ParserException : public std::exception {
private:
    std::string message;
    int position;
public:
    ParserException(std::string msg, int pos) : message(msg), position(pos) {}

    const char* what() const noexcept override {
        return message.c_str();
    }

    int get_pos() const { return position; }
};

namespace Parser {
    // В будущем здесь будет FSM (конечный автомат)
    List<Lexem> parse(std::string expression) {
        List<Lexem> lexems;

        // --- ТЕСТОВАЯ ЗАГЛУШКА ---
        // Если в строке есть символ '@', выкинем ошибку для теста
        size_t error_pos = expression.find('@');
        if (error_pos != std::string::npos) {
            throw ParserException("Unexpected symbol '@'", (int)error_pos);
        }

        // Эмуляция: если нашли "x", добавляем переменную, иначе считаем константой
        // В реальности тут будет сложный цикл
        if (expression.find("x") != std::string::npos) {
            lexems.push_back(Lexem("x", Variable));
            lexems.push_back(Lexem("+", Operator, 0, 1));
        }
        lexems.push_back(Lexem("10", Constant, 10.0));

        return lexems;
    }

    //double my_sin(double x) { return sin(x); }
    //double my_cos(double x) { return cos(x); }
    //double my_tg(double x) { return tan(x); }
    //double my_abs(double x) { return fabs(x); }


    //List<Lexem> parse(std::string expression) {
    //    List<Lexem> lexems;
    //    Stack<char> stack(expression.length());
    //    bool expect_operand = true;

    //    for (size_t i = 0; i < expression.length(); i++) {
    //        char c = expression[i];

    //        if (isspace(c)) continue;

    //        if (isdigit(c)) {
    //            if (!expect_operand) throw std::invalid_argument("Missing operator before number!");

    //            std::string numStr = read_number(expression, i);
    //            double val = std::stod(numStr);

    //            Lexem lex("const", Constant, val);
    //            lexems.push_back(lex);
    //            expect_operand = false;
    //        }

    //        else if (isalpha(c) || c == '_') {
    //            if (!expect_operand) throw std::invalid_argument("Missing operator before variable!");

    //            std::string name = read_identifier(expression, i);

    //            if (name == "sin") {
    //                Lexem lex("sin", Function, DBL_MAX, 4, my_sin);
    //                lexems.push_back(lex);
    //                expect_operand = true;
    //            }
    //            else if (name == "cos") {
    //                Lexem lex("cos", Function, DBL_MAX, 4, my_cos);
    //                lexems.push_back(lex);
    //                expect_operand = true;
    //            }
    //            else if (name == "tg") {
    //                Lexem lex("tg", Function, DBL_MAX, 4, my_tg);
    //                lexems.push_back(lex);
    //                expect_operand = true;
    //            }
    //            else if (name == "abs") {
    //                Lexem lex("abs", Function, DBL_MAX, 4, my_abs);
    //                lexems.push_back(lex);
    //                expect_operand = true;
    //            }
    //            else {
    //                Lexem lex(name, Variable);
    //                lexems.push_back(lex);
    //                expect_operand = false;
    //            }
    //        }

    //        else if (c == '{' || c == '[' || c == '(') {
    //            if (!expect_operand) throw std::invalid_argument("Missing operator before bracket!");
    //            stack.push(c);
    //            Lexem lex(std::string(1, c), OpenBracket);
    //            lexems.push_back(lex);
    //            expect_operand = true;
    //        }

    //        else if (c == '}' || c == ']' || c == ')') {
    //            if (expect_operand) throw std::invalid_argument("Missing operand!");
    //            if (stack.is_empty()) throw std::invalid_argument("Missing opened bracket!");

    //            char top = stack.top();
    //            if ((c == ')' && top != '(') || (c == '}' && top != '{') || (c == ']' && top != '[')) {
    //                throw std::invalid_argument("Mismatched brackets!");
    //            }
    //            stack.pop();

    //            Lexem lex(std::string(1, c), ClosedBracket);
    //            lexems.push_back(lex);
    //            expect_operand = false;
    //        }

    //        else if (c == '|') {
    //            if (expect_operand) {
    //                Lexem lexAbs("abs", Function, DBL_MAX, 4, my_abs);
    //                lexems.push_back(lexAbs);
    //                Lexem lexBr("(", OpenBracket);
    //                lexems.push_back(lexBr);
    //                stack.push('|');
    //                expect_operand = true;
    //            }
    //            else {
    //                if (stack.is_empty() || stack.top() != '|') throw std::invalid_argument("Unexpected '|'");
    //                stack.pop();
    //                Lexem lex(")", ClosedBracket);
    //                lexems.push_back(lex);
    //                expect_operand = false;
    //            }
    //        }

    //        else if (c == '+' || c == '-' || c == '*' || c == '/' || c == '^') {
    //            if (expect_operand) {
    //                if (c == '-') {
    //                    Lexem zero("0", Constant, 0.0);
    //                    lexems.push_back(zero);
    //                    Lexem op("-", Operator, DBL_MAX, 1);
    //                    lexems.push_back(op);
    //                }
    //                else {
    //                    throw std::invalid_argument("Invalid use of binary operator!");
    //                }
    //            }
    //            else {
    //                int p = 1;
    //                if (c == '*' || c == '/') p = 2;
    //                if (c == '^') p = 3;
    //                Lexem lex(std::string(1, c), Operator, DBL_MAX, p);
    //                lexems.push_back(lex);
    //                expect_operand = true;
    //            }
    //        }
    //        else {
    //            throw std::invalid_argument("Invalid character detected!");
    //        }
    //    }

    //    if (expect_operand) throw std::invalid_argument("Expression ends with operator!");
    //    if (!stack.is_empty()) throw std::invalid_argument("Unclosed bracket!");

    //    return lexems;
    //}

    //std::string read_number(const std::string& str, size_t& pos) {
    //    std::string res;
    //    while (pos < str.length() && (isdigit(str[pos]) || str[pos] == '.')) {
    //        res += str[pos];
    //        pos++;
    //    }
    //    /*while (i + 1 < expression.length() && isdigit(expression[i + 1])) {
    //        i++;
    //    }*/
    //    pos--;
    //    return res;
    //}

    //std::string read_identifier(const std::string& str, size_t& pos) {
    //    std::string res;
    //    while (pos < str.length() && (isalnum(str[pos]) || str[pos] == '_')) {
    //        res += str[pos];
    //        pos++;
    //    }
    //    pos--;
    //    return res;
    //}
};

#endif // LIB_PARSER_PARSER_H_