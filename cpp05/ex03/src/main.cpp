/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaosilva <joaosilva@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 13:40:33 by joaosilva         #+#    #+#             */
/*   Updated: 2025/05/27 16:30:03 by joaosilva        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "Intern.hpp"
#include "Bureaucrat.hpp"

int main() 
{
    std::cout << std::endl;
    Intern someRandomIntern;
    AForm* form; // Pointer to AForm, which can point to any derived form such
                 // as ShrubberyCreationForm, RobotomyRequestForm, or PresidentialPardonForm.

    std::cout << "\n--- Test 1: Intern creates ShrubberyCreationForm ---" << std::endl;
    form = someRandomIntern.makeForm("shrubbery creation", "Garden");
    if (form)
        delete form;

    std::cout << "\n--- Test 2: Intern creates RobotomyRequestForm ---" << std::endl;
    form = someRandomIntern.makeForm("robotomy request", "Bender");
    if (form)
        delete form;

    std::cout << "\n--- Test 3: Intern creates PresidentialPardonForm ---" << std::endl;
    form = someRandomIntern.makeForm("presidential pardon", "Arthur Dent");
    if (form)
        delete form;

    std::cout << "\n--- Test 4: Intern tries to create an unknown form ---" << std::endl;
    form = someRandomIntern.makeForm("coffee making", "Office");
    if (form)
        delete form;
   
    return 0;
}
