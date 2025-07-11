/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaosilva <joaosilva@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 12:43:42 by joaosilva         #+#    #+#             */
/*   Updated: 2025/06/27 11:17:33 by joaosilva        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"
#include <iostream>

/* ****************************
STACK IS USED IN THIS EXERCISE due 2 reasons:
1. RPN (Reverse Polish Notation) was created to use a stack.
2. Stack us usefull to make pull and push operations.
****************************** */

int main(int argc, char** argv) 
{
    
    if (argc != 2) 
    {
        std::cerr << "Error" << std::endl;
        return 1;
    } 
    try {
        int result = RPN::evaluate(argv[1]);
        std::cout << result << std::endl;
    } catch (std::exception& e) {
        std::cerr << "Error" << std::endl;
        return 1;
    }
    return 0;
} 