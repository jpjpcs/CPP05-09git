/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RobotomyRequestForm.cpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaosilva <joaosilva@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 17:10:49 by joaosilva         #+#    #+#             */
/*   Updated: 2025/06/27 11:02:46 by joaosilva        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RobotomyRequestForm.hpp"
#include <cstdlib>
#include <ctime>
#include <iostream>

// Default constructor
RobotomyRequestForm::RobotomyRequestForm()
    : AForm("RobotomyRequestForm", 72, 45), _target("default") {std::cout << "RobotomyRequestForm default constructor called!" << std::endl;}

RobotomyRequestForm::RobotomyRequestForm(const std::string &target)
    : AForm("RobotomyRequestForm", 72, 45), _target(target) {std::cout << "RobotomyRequestForm parameter constructor called!" << std::endl;}

RobotomyRequestForm::RobotomyRequestForm(const RobotomyRequestForm &src)
    : AForm(src), _target(src._target) {std::cout << "Copy constructor called!" << std::endl;}

RobotomyRequestForm::~RobotomyRequestForm() {std::cout << "RobotomyRequestForm destructor called!" << std::endl;}

RobotomyRequestForm &RobotomyRequestForm::operator=(const RobotomyRequestForm &src)
{
    if (this != &src)
        this->_target = src._target;
    return *this;
}

void RobotomyRequestForm::execute(Bureaucrat const &executor) const
{
    if (!getIsSigned())
        throw FormNotSignedException();
    if (executor.getGrade() > getGradeToExecute())
        throw GradeTooLowException();

    std::cout << "* drilling noises *" << std::endl;
    std::srand(std::time(0));
    if (std::rand() % 2)
        std::cout << _target << " has been robotomized successfully!" << std::endl;
    else
        std::cout << "Robotomy failed on " << _target << "!" << std::endl;
}
