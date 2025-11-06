// Algebraic Expression Evaluator

// Build a command-line calculator that evaluates expressions like "2 + 3 * (4 - 1)" using stacks for parentheses and operator precedence. This reinforces PEMDAS rules and teaches parsing logic. Start with infix notation; output the result. (Math benefit: Practice algebraic manipulation; C++: String manipulation with `std::string` and `std::stack`.)

#include <iostream>
#include <stack>
#include <string>
#include <iomanip>

// Function to perform arithmetic operations
double applyOp(double a, double b, char op)
{
    switch (op)
    {
    case '+':
        return a + b;
    case '-':
        return a - b;
    case '*':
        return a * b;
    case '/':
        return a / b;
    }
    return 0; // Should not reach here for valid inputs
}

// Function to determine the precedence of an operator
int precedence(char op)
{
    if (op == '+' || op == '-')
        return 1;
    if (op == '*' || op == '/')
        return 2;
    return 0; // For other characters like parentheses
}

// Function to evaluate an arithmetic expression
double evaluate(std::string expression)
{
    std::stack<double> values;
    std::stack<char> ops;

    for (int i = 0; i < expression.length(); i++)
    {
        // Skip whitespace
        if (expression[i] == ' ')
            continue;

        // If a digit, parse the full number
        if (isdigit(expression[i]) || expression[i] == '.')
        {
            std::string numStr;
            while (i < expression.length() && (isdigit(expression[i]) || expression[i] == '.'))
            {
                numStr += expression[i];
                i++;
            }
            values.push(std::stod(numStr)); // Convert string to double
            i--;                            // Decrement i to offset the increment in the for loop
        }
        // If an opening parenthesis, push to ops stack
        else if (expression[i] == '(')
        {
            ops.push(expression[i]);
        }
        // If a closing parenthesis, evaluate the expression inside the parenthesis
        else if (expression[i] == ')')
        {
            while (!ops.empty() && ops.top() != '(')
            {
                double val2 = values.top();
                values.pop();
                double val1 = values.top();
                values.pop();
                char op = ops.top();
                ops.pop();
                values.push(applyOp(val1, val2, op));
            }
            if (!ops.empty())
                ops.pop(); // Pop the '('
        }
        // If an operator
        else
        {
            // While top of 'ops' has same or greater precedence than current operator,
            // apply operator on top of 'ops' to top two elements in 'values' stack.
            while (!ops.empty() && precedence(ops.top()) >= precedence(expression[i]))
            {
                double val2 = values.top();
                values.pop();
                double val1 = values.top();
                values.pop();
                char op = ops.top();
                ops.pop();
                values.push(applyOp(val1, val2, op));
            }
            // Push current operator to 'ops' stack
            ops.push(expression[i]);
        }
    }

    // After scanning the whole expression, apply any remaining operators
    // in the ops stack to the values stack.
    while (!ops.empty())
    {
        double val2 = values.top();
        values.pop();
        double val1 = values.top();
        values.pop();
        char op = ops.top();
        ops.pop();
        values.push(applyOp(val1, val2, op));
    }

    // The top of the values stack is the result
    return values.top();
}

int main()
{
    std::string expression;
    std::cout << "Enter an algebraic expression (e.g., \"2 + 3 * (4 - 1)\"): ";
    std::getline(std::cin, expression);

    try
    {
        double result = evaluate(expression);
        // Using fixed and setprecision to format output nicely
        std::cout << "Result: " << std::fixed << std::setprecision(2) << result << std::endl;
    }
    catch (...)
    {
        std::cout << "Error: Invalid expression or calculation error (e.g., division by zero)." << std::endl;
    }

    return 0;
}
