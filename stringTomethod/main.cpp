#include <iostream>
#include <string>
#include <stack>

bool evaluateExpression(const std::string& expression) {
    std::stack<char> operators;
    std::stack<bool> operands;

    for (char ch : expression) {
        if (ch == ' ') {
            continue;
        } else if (ch == '(' || ch == '&' || ch == '|') {
            operators.push(ch);
        } else if (ch == 't' || ch == 'f') {
            bool value = (ch == 't');
            operands.push(value);
        } else if (ch == ')') {
            while (!operators.empty() && operators.top() != '(') {
                char op = operators.top();
                operators.pop();

                if (op == '&') {
                    bool operand2 = operands.top();
                    operands.pop();
                    bool operand1 = operands.top();
                    operands.pop();
                    operands.push(operand1 && operand2);
                } else if (op == '|') {
                    bool operand2 = operands.top();
                    operands.pop();
                    bool operand1 = operands.top();
                    operands.pop();
                    operands.push(operand1 || operand2);
                }
            }

            if (!operators.empty() && operators.top() == '(') {
                operators.pop();
            }
        }
    }

    while (!operators.empty()) {
        char op = operators.top();
        operators.pop();

        bool operand2 = operands.top();
        operands.pop();
        bool operand1 = operands.top();
        operands.pop();

        if (op == '&') {
            operands.push(operand1 && operand2);
        } else if (op == '|') {
            operands.push(operand1 || operand2);
        }
    }

    return operands.top();
}

int main() {
    std::string expression = "(t && t) || f";
    bool result = evaluateExpression(expression);
    std::cout << "Result: " << (result ? "true" : "false") << std::endl;

    return 0;
}