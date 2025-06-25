/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaosilva <joaosilva@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 12:44:33 by joaosilva         #+#    #+#             */
/*   Updated: 2025/06/23 18:17:34 by joaosilva        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"
#include <sstream>
#include <stdexcept>
#include <cstdlib>

RPN::RPN() {}

RPN::RPN(RPN const &other) 
{
    (void)other; // No members to copy, but keeping the signature
}

RPN &RPN::operator=(RPN const &other) 
{
    (void)other; // No members to assign, but keeping the signature
    return *this;
}

// No dynamic resources to release, but keeping the signature
RPN::~RPN() {}

/*
The stack is not empty when you reach the first operator.

At the beginning, the stack is empty, but each time you read a number, you do stack.push(n);.
Only when you encounter an operator (+, -, *, /) do you perform the two pops to get the operands.

Step-by-step example for "3 4 +":

Read "3" → do stack.push(3) → stack: [3]
Read "4" → do stack.push(4) → stack: [3, 4]
Read "+" → now the stack has two elements (3 and 4), so you can do:
int b = stack.top(); stack.pop(); → b = 4, stack: [3]
int a = stack.top(); stack.pop(); → a = 3, stack: []
Calculate a + b → 3 + 4 = 7
stack.push(7) → stack: [7]
Summary:

The stack only needs to have two elements when you reach an operator.
At the beginning it is empty, but it gets filled with numbers before each operation.
*/
int RPN::evaluate(const std::string& expr) 
{
    std::stack<int> stack; // Using a stack to evaluate the RPN expression, which allows us to easily push and pop operands as we encounter them in the expression.
    // How? Example: "3 4 + 2 *" will be evaluated as follows:
    // 1. Push 3 onto the stack.
    // 2. Push 4 onto the stack.
    // 3. Pop 4 and 3 from the stack, add them, and push the result (7) onto the stack.
    // 4. Push 2 onto the stack.
    // 5. Pop 2 and 7 from the stack, multiply them, and push the result (14) onto the stack.
    // 6. The final result is the only element left in the stack (14).

    std::istringstream iss(expr); // Using istringstream to parse the expression and get tokens.
    // std::istringstream iss(expr); creates an input string stream from the string expr.
    // It allows us to read the string expr as if it were an input stream (like reading from std::cin or a file), 
    // so we can easily extract tokens (numbers and operators) separated by whitespace using the >> operator.
    // For example, "3 4 + 2 *" will be split into tokens "3", "4", "+", "2", "*". in the next while.
    // Example:
    // If expr is "3 4 + 2 *",
    // then iss >> token will give you "3", then "4", then "+", then "2", then "*".

    std::string token;
    // RESUME: AT THE BEGINNING, stack is empty, but each time we encounter a number in the expression, we push it onto the stack using stack.push(n);
    // Only when we encounter an operator (like +, -, *, /), we pop the top two elements from the stack, perform the operation, and push the result back onto the stack.
    while (iss >> token) // Extract tokens from the expression. >> is used to read whitespace-separated tokens from the input stream. The stream automatically skips whitespace (spaces, tabs, newlines) and only extracts the next non-whitespace token.
    {
        if (token.size() == 1 && std::string("+-/*").find(token) != std::string::npos) // Check if the token size is 1 and if it is an operator. Why 1? Because we are only interested in single-character operators (+, -, *, /).
        {
            if (stack.size() < 2) // Why? Because we need at least two operands to perform an operation. If there are not enough operands, we cannot perform the operation. 
            // example: // "3 +" would result in an error because we need two operands to perform the addition operation.
                throw std::runtime_error("Error");
            int b = stack.top(); stack.pop(); // Pop (remove the top element from the stack).
            int a = stack.top(); stack.pop(); // Pop the next top element from the stack.
            // We do stack.top(); stack.pop(); twice because we need to get two operands from the stack for each operator 
            // in Reverse Polish Notation (RPN). The first stack.top(); stack.pop(); gets the second operand (b), which is on the top of the stack.
            // The second stack.top(); stack.pop(); gets the first operand (a), which is now on the top after popping b.
            // Example:
            // For the expression 3 4 +:
            // Stack after pushing: [3, 4]. And we push when we do this in the stack.push(n); in the next lines in case the stack is empty.
            // When we see +, we pop 4 (b), then pop 3 (a), then compute a + b (3 + 4).
            // So, Order matters:In RPN, the operation is always a <op> b, where a is the first popped, b is the second popped.
            // And that's why you need to pop twice: once for each operand.
            if (token == "+") stack.push(a + b); // push the result of the operation back onto the stack.
            else if (token == "-") stack.push(a - b);
            else if (token == "*") stack.push(a * b);
            else if (token == "/") 
            {
                if (b == 0) throw std::runtime_error("Error");
                stack.push(a / b);
            }
        } 
        else 
        {
            char* end;
            int n = std::strtol(token.c_str(), &end, 10); //strtol converts the string token to a long integer, using base 10.
            // c_str() converts the std::string token to a C-style string (const char*), which is required by strtol.
            // Why? Because in RPN, the operands are integers, and we need to convert the string representation of the number into an integer to perform arithmetic operations.
            if (*end != '\0' || n < 0 || n > 9)
                throw std::runtime_error("Error");
            stack.push(n);
        }
    }
    if (stack.size() != 1)
        throw std::runtime_error("Error");
    return stack.top(); // Return the final result, which should be the only element left in the stack after and its the result of the RPN expression evaluation. Example: For the expression "3 4 + 2 *", the final result is 14, which is the only element left in the stack after evaluating the expression.
}
