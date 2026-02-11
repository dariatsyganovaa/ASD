#ifndef LIB_EXPRESSION_EXPRESSION_H_
#define LIB_EXPRESSION_EXPRESSION_H_

#include "..\lib_list\list.h"
#include "..\lib_lexem\lexem.h"
#include "..\lib_stack\stack.h"
#include "..\lib_parser\parser.h"
#include <stdexcept>
#include <iostream>
#include <string>
#include <cmath>
#include <vector> // Для GetOperands (возврат списка имен)

class Expression {
    std::string infix;       // Исходная строка
    List<Lexem> lexems;      // Список лексем (вместо vector<char>)
    List<Lexem> postfix;     // Постфиксная запись (вместо string postfix)

    // Метод Parse теперь использует наш мощный Parser
    void Parse() {
        lexems = Parser::parse(infix);
    }

    // Перевод в постфиксную запись (Shunting-yard)
    void ToPostfix() {
        postfix.clear();
        Stack<Lexem> st; // Стек лексем, а не char
        Lexem stackItem;

        for (auto it = lexems.begin(); it != lexems.end(); ++it) {
            Lexem item = *it;

            switch (item.type) {
                // 1. Операнды (Числа и Переменные) -> сразу в выход
            case Constant:
            case Variable:
                postfix.push_back(item);
                break;

                // 2. Открывающая скобка или Функция -> в стек
            case OpenBracket: // В твоем enum OpenBrecket
            case Function:
                st.push(item);
                break;

                // 3. Закрывающая скобка
            case ClosedBracket:
                if (st.is_empty()) throw std::logic_error("Missing opened bracket");

                stackItem = st.top(); // Сначала смотрим
                st.pop();             // Потом удаляем (так как pop void)

                while (stackItem.type != OpenBracket) {
                    postfix.push_back(stackItem);

                    if (st.is_empty()) throw std::logic_error("Missing opened bracket");
                    stackItem = st.top();
                    st.pop();
                }

                // Если перед скобкой была функция (sin(...)), её тоже выталкиваем
                if (!st.is_empty() && st.top().type == Function) {
                    postfix.push_back(st.top());
                    st.pop();
                }
                break;

                // 4. Операторы
            case Operator:
                while (!st.is_empty()) {
                    stackItem = st.top(); // Смотрим верхушку

                    // Если на вершине оператор и его приоритет >= текущему
                    if (stackItem.type == Operator && stackItem.priority >= item.priority) {
                        postfix.push_back(stackItem);
                        st.pop(); // Удаляем из стека
                    }
                    else {
                        break; // Прерываем, если приоритет меньше
                    }
                }
                st.push(item);
                break;

            default:
                break;
            }
        }

        // Выталкиваем остатки
        while (!st.is_empty()) {
            stackItem = st.top();
            st.pop();
            if (stackItem.type == OpenBracket) throw std::logic_error("Unclosed bracket");
            postfix.push_back(stackItem);
        }
    }

public:
    // Конструктор
    Expression(std::string infx) : infix(infx) {
        Parse();     // Сразу парсим
        // ToPostfix(); // Можно вызвать сразу, а можно перед вычислением
    }

    std::string GetInfix() const {
        return infix;
    }

    // Возвращает постфиксную запись в виде строки (для отображения)
    std::string GetPostfix() {
        ToPostfix(); // Актуализируем RPN
        std::string res = "";
        for (auto it = postfix.begin(); it != postfix.end(); ++it) {
            res += (*it).name + " ";
        }
        return res;
    }

    // Аналог GetOperands преподавателя
    // Возвращает список переменных, чтобы мы могли их спросить у пользователя
    std::vector<std::string> GetOperands() const {
        std::vector<std::string> op;
        for (auto it = lexems.begin(); it != lexems.end(); ++it) {
            if ((*it).type == Variable) {
                // Добавляем только уникальные (можно добавить проверку)
                op.push_back((*it).name);
            }
        }
        return op;
    }

    // Метод для установки значений переменных (вместо передачи map в Calculate)
    void SetVariable(std::string name, double value) {
        // Обновляем значение и в lexems (для истории), и в postfix (если он уже построен)
        for (auto it = lexems.begin(); it != lexems.end(); ++it) {
            if ((*it).type == Variable && (*it).name == name) {
                (*it).value = value;
            }
        }
    }

    // Вычисление
    double Calculate() {
        ToPostfix(); // Строим заново, чтобы подтянуть значения переменных из lexems

        Stack<double> st;
        double leftOperand, rightOperand;

        for (auto it = postfix.begin(); it != postfix.end(); ++it) {
            Lexem item = *it;

            switch (item.type) {
            case Constant:
            case Variable:
                st.push(item.value); // Берем уже сохраненное значение
                break;

            case Operator:
                // Внимание: pop() void, поэтому сначала top()
                if (st.is_empty()) throw std::logic_error("Stack underflow");
                rightOperand = st.top(); st.pop();

                if (st.is_empty()) throw std::logic_error("Stack underflow");
                leftOperand = st.top(); st.pop();

                if (item.name == "+") st.push(leftOperand + rightOperand);
                else if (item.name == "-") st.push(leftOperand - rightOperand);
                else if (item.name == "*") st.push(leftOperand * rightOperand);
                else if (item.name == "/") {
                    if (rightOperand == 0) throw std::logic_error("Division by zero");
                    st.push(leftOperand / rightOperand);
                }
                else if (item.name == "^") st.push(pow(leftOperand, rightOperand));
                break;

            case Function:
                if (st.is_empty()) throw std::logic_error("Stack underflow");
                leftOperand = st.top(); st.pop(); // Аргумент функции

                if (item.function) st.push(item.function(leftOperand));
                else {
                    // Fallback если указатель пуст
                    if (item.name == "sin") st.push(sin(leftOperand));
                    else if (item.name == "cos") st.push(cos(leftOperand));
                    else if (item.name == "abs") st.push(fabs(leftOperand));
                }
                break;

            default:
                break;
            }
        }

        if (st.is_empty()) return 0.0;

        double result = st.top();
        st.pop();
        return result;
    }
};

#endif // LIB_EXPRESSION_EXPRESSION_H_