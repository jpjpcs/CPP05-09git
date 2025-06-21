/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaosilva <joaosilva@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 12:44:33 by joaosilva         #+#    #+#             */
/*   Updated: 2025/06/11 13:02:34 by joaosilva        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"
#include <sstream>
#include <stdexcept>
#include <cstdlib>

int RPN::evaluate(const std::string& expr) {
    std::stack<int> stack;
    std::istringstream iss(expr);
    std::string token;
    while (iss >> token) {
        if (token.size() == 1 && std::string("+-/*").find(token) != std::string::npos) {
            if (stack.size() < 2)
                throw std::runtime_error("Error");
            int b = stack.top(); stack.pop();
            int a = stack.top(); stack.pop();
            if (token == "+") stack.push(a + b);
            else if (token == "-") stack.push(a - b);
            else if (token == "*") stack.push(a * b);
            else if (token == "/") {
                if (b == 0) throw std::runtime_error("Error");
                stack.push(a / b);
            }
        } else {
            char* end;
            int n = std::strtol(token.c_str(), &end, 10);
            if (*end != '\0' || n < 0 || n > 9)
                throw std::runtime_error("Error");
            stack.push(n);
        }
    }
    if (stack.size() != 1)
        throw std::runtime_error("Error");
    return stack.top();
}
