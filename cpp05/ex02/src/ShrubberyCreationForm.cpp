/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ShrubberyCreationForm.cpp                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaosilva <joaosilva@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 16:54:21 by joaosilva         #+#    #+#             */
/*   Updated: 2025/06/27 11:02:51 by joaosilva        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ShrubberyCreationForm.hpp"
#include <fstream>
#include <iostream>

// Default constructor: sets target to "default"
ShrubberyCreationForm::ShrubberyCreationForm()
    : AForm("ShrubberyCreationForm", 145, 137), _target("default") {std::cout << "ShrubberyCreationForm default constructor called!" << std::endl;}

// Constructor with target parameter
ShrubberyCreationForm::ShrubberyCreationForm(const std::string &target)
    : AForm("ShrubberyCreationForm", 145, 137), _target(target) {std::cout << "ShrubberyCreationForm parameter constructor called!" << std::endl;}

ShrubberyCreationForm::ShrubberyCreationForm(const ShrubberyCreationForm &src)
    : AForm(src), _target(src._target) {std::cout << "Copy constructor called!" << std::endl;}

ShrubberyCreationForm::~ShrubberyCreationForm() {std::cout << "ShrubberyCreationForm destructor called!" << std::endl;}

ShrubberyCreationForm &ShrubberyCreationForm::operator=(const ShrubberyCreationForm &src)
{
    if (this != &src)
        this->_target = src._target;
    return *this;
}

void ShrubberyCreationForm::execute(Bureaucrat const &executor) const
{
    if (!getIsSigned())
        throw FormNotSignedException();
    if (executor.getGrade() > getGradeToExecute())
        throw GradeTooLowException();

    std::ofstream file((_target + "_shrubbery").c_str());
    if (!file)
    {
        std::cerr << "Error: could not open file for writing." << std::endl;
        return;
    }
    file << "       _-_\n"
            "    /~~   ~~\\\n"
            " /~~    |    ~~\\\n"
            "{      |||       }\n"
            " \\  _-     -_  /\n"
            "   ~  \\\\ //  ~\n"
            "_- -   | | _- _\n"
            "  _ -  | |   -_\n"
            "      // \\\\\n";
    file.close();
}
