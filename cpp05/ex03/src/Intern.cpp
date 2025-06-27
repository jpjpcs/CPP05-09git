/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Intern.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaosilva <joaosilva@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 16:01:07 by joaosilva         #+#    #+#             */
/*   Updated: 2025/06/27 11:03:44 by joaosilva        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Intern.hpp"
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"
#include <iostream>

/*
1 - Forbidden use of lambdas in C++98:
    The [] indicate lambdas (anonymous functions) in C++.
    They are not allowed in C++98.
    You should use pointers to static functions instead of lambdas.
2 - The Intern class is responsible for creating forms based on their names.
    AForm* Intern::makeForm(const std::string &formName, const std::string &target) const
    {
        static const FormPair forms[] = {
            {"shrubbery creation", [](const std::string &t){ return new ShrubberyCreationForm(t); }},
            {"robotomy request",   [](const std::string &t){ return new RobotomyRequestForm(t); }},
            {"presidential pardon",[](const std::string &t){ return new PresidentialPardonForm(t); }}
        };

        for (size_t i = 0; i < sizeof(forms)/sizeof(forms[0]); ++i) {
            if (formName == forms[i].name) {
                std::cout << "Intern creates " << formName << std::endl;
                return forms[i].creator(target);
            }
        }
        std::cout << "Intern: Error! Form \"" << formName << "\" does not exist." << std::endl;
        return NULL;
    }
  
    The [] indicate lambdas (anonymous functions) in C++.
    For example:
        This is a lambda function that takes a std::string and returns a new ShrubberyCreationForm.
        However:
            Lambdas only exist from C++11 onwards.
            Your project must be done in C++98 (as stated in the subject: -std=c++98).
            Therefore, you cannot use lambdas in this exercise!
            You should use pointers to static functions (such as &Intern::createShrubbery) instead of lambdas.
        Summary:
            The [] are for lambdas (anonymous functions).
            They are not allowed in C++98.
            Replace them with pointers to static functions to comply with the subject.
*/

Intern::Intern() {std::cout << "Intern default constructor called" << std::endl;}
Intern::Intern(const Intern &src) 
{
    (void)src; // To avoid unused parameter warning
    std::cout << "Intern copy constructor called" << std::endl;
}

Intern &Intern::operator=(const Intern &src) 
{
    (void)src;
    std::cout << "Intern assignment operator called" << std::endl; 
    return *this; 
}

Intern::~Intern() {std::cout << "Intern destructor called" << std::endl;}

AForm* Intern::createShrubbery(const std::string &target) 
{
    return new ShrubberyCreationForm(target);
}
AForm* Intern::createRobotomy(const std::string &target) 
{
    return new RobotomyRequestForm(target);
}
AForm* Intern::createPardon(const std::string &target) 
{
    return new PresidentialPardonForm(target);
}

AForm* Intern::makeForm(const std::string &formName, const std::string &target) const {
    static const FormPair forms[] = {
        {"shrubbery creation", &Intern::createShrubbery},
        {"robotomy request",   &Intern::createRobotomy},
        {"presidential pardon",&Intern::createPardon}
    };
    for (int i = 0; i < 3; ++i) {
        if (formName == forms[i].name) {
            std::cout << "Intern creates " << formName << std::endl;
            return forms[i].creator(target);
        }
    }
    std::cout << "Intern: Error! Form \"" << formName << "\" does not exist." << std::endl;
    return NULL;
}
