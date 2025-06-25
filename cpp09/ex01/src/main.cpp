/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaosilva <joaosilva@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 12:43:42 by joaosilva         #+#    #+#             */
/*   Updated: 2025/06/23 17:27:42 by joaosilva        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"
#include <iostream>

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