/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Identify.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaosilva <joaosilva@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 11:38:42 by joaosilva         #+#    #+#             */
/*   Updated: 2025/05/30 12:40:13 by joaosilva        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "A.hpp"
#include "B.hpp"
#include "C.hpp"
#include <cstdlib>
#include <ctime>
#include <iostream>

Base* generate(void)
{
    int r = std::rand() % 3;
    if (r == 0)
        return new A;
    else if (r == 1)
        return new B;
    else
        return new C;
}

void identify(Base* p)
{
    if (dynamic_cast<A*>(p))
        std::cout << "A class" << std::endl;
    else if (dynamic_cast<B*>(p))
        std::cout << "B class" << std::endl;
    else if (dynamic_cast<C*>(p))
        std::cout << "C class" << std::endl;
    else
        std::cout << "Unknown" << std::endl;
}

void identify(Base& p)
{
    try {
        (void)dynamic_cast<A&>(p);
        std::cout << "It´s A" << std::endl;
        return;
    } catch (...) {} // Catch all exceptions from failed dynamic_cast, 
                      // which indicates that p is not of type A
                      // This is necessary to avoid program termination
                      // when the cast fails.
                      // Repeat for B and C
    try {
        (void)dynamic_cast<B&>(p);
        std::cout << "It´s B" << std::endl;
        return;
    } catch (...) {}
    try {
        (void)dynamic_cast<C&>(p);
        std::cout << "It´s C" << std::endl;
        return;
    } catch (...) {}
    std::cout << "Unknown" << std::endl;
}
