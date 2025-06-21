/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaosilva <joaosilva@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 12:43:42 by joaosilva         #+#    #+#             */
/*   Updated: 2025/06/12 10:36:39 by joaosilva        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* 
#include "RPN.hpp"
#include <iostream>

int main(int argc, char** argv) {
    if (argc != 2) {
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
}  */

#include "PmergeMe.hpp"
#include <iostream>
#include <vector>
#include <deque>
#include <ctime>
#include <iomanip>

int main(int argc, char** argv) {
    if (argc < 2) {
        std::cerr << "Error" << std::endl;
        return 1;
    }
    std::vector<int> v;
    std::deque<int> d;
    if (!PmergeMe::parseInput(argc, argv, v, d)) {
        std::cerr << "Error" << std::endl;
        return 1;
    }

    std::cout << "Before:";
    for (size_t i = 0; i < v.size(); ++i)
        std::cout << " " << v[i];
    std::cout << std::endl;

    clock_t start = clock();
    PmergeMe::sortVector(v);
    clock_t end = clock();
    double timeVec = 1e6 * (end - start) / CLOCKS_PER_SEC;

    start = clock();
    PmergeMe::sortDeque(d);
    end = clock();
    double timeDeq = 1e6 * (end - start) / CLOCKS_PER_SEC;

    std::cout << "After:";
    for (size_t i = 0; i < v.size(); ++i)
        std::cout << " " << v[i];
    std::cout << std::endl;

    std::cout << "Time to process a range of " << v.size() << " elements with std::vector : "
              << std::fixed << std::setprecision(5) << timeVec << " us" << std::endl;
    std::cout << "Time to process a range of " << d.size() << " elements with std::deque : "
              << std::fixed << std::setprecision(5) << timeDeq << " us" << std::endl;
    return 0;
}
