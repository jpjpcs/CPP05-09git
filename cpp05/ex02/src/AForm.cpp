/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AForm.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaosilva <joaosilva@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 12:15:07 by joaosilva         #+#    #+#             */
/*   Updated: 2025/06/27 11:02:19 by joaosilva        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AForm.hpp"

// Default constructor
AForm::AForm() : _name("default"), _isSigned(false), _gradeToSign(150), _gradeToExecute(150)
{
    std::cout << "AForm default constructor called!" << std::endl;
}

AForm::AForm(const std::string &name, int gradeToSign, int gradeToExecute)
    : _name(name), _isSigned(false), _gradeToSign(gradeToSign), _gradeToExecute(gradeToExecute)
{
    if (gradeToSign < 1 || gradeToExecute < 1)
        throw GradeTooHighException();
    if (gradeToSign > 150 || gradeToExecute > 150)
        throw GradeTooLowException();
    std::cout << "AForm Parameter constructor called!" << std::endl;
}
/*
The correct copy constructor is the one that initializes all members (including const members) in the initializer list.
You should not use the assignment operator inside the copy constructor for const members, as they can only be initialized in the initializer list.

Always use the members directly in the initializer list (e.g., src._name), not the getters.
Do not call the assignment operator inside the copy constructor, since const members cannot be reassigned.
Include _isSigned in the initializer list.

Getters can be overridden in derived classes, potentially changing the expected behavior (especially if they are virtual).
The initializer list is executed before the constructor body, and you only have direct access to the source object's members, not to any potentially altered behavior from getters.
Efficiency: Accessing the member directly is more efficient than calling a function.
Consistency: This ensures that the copied values are exactly those of the original object, without any extra logic from getters.

Summary:
Always initialize all members (including const) directly in the copy constructor's initializer list using the source object's members, not getters, and never call the assignment operator inside the copy constructor.
This guarantees efficiency, consistency, and correct behavior, especially for const members.
*/
AForm::AForm(const AForm &src)
    : _name(src._name), _isSigned(src._isSigned),
      _gradeToSign(src._gradeToSign), _gradeToExecute(src._gradeToExecute)
{
    std::cout << "AForm copy constructor called!" << std::endl;
    // Don´t call *this = src;
}

AForm::~AForm() {std::cout << "AForm destructor called!" << std::endl;}

// Assignment operator
AForm &AForm::operator=(const AForm &src)
{
    std::cout << "AForm assignment operator called!" << std::endl;
    if (this != &src)
        this->_isSigned = src._isSigned;
    return *this;
}

// Getters
std::string AForm::getName() const { return _name; }
bool        AForm::getIsSigned() const { return _isSigned; }
int         AForm::getGradeToSign() const { return _gradeToSign; }
int         AForm::getGradeToExecute() const { return _gradeToExecute; }

// beSigned implementation
void AForm::beSigned(const Bureaucrat &bureaucrat)
{
    if (_isSigned)
        throw std::runtime_error("AForm is already signed");
    if (bureaucrat.getGrade() > _gradeToSign)
        throw GradeTooLowException();
    _isSigned = true;
}

// Exception classes
const char* AForm::GradeTooHighException::what() const throw()
{
    return "AForm: Grade is too high";
}
const char* AForm::GradeTooLowException::what() const throw()
{
    return "AForm: Grade is too low";
}
const char* AForm::FormNotSignedException::what() const throw()
{
    return "AForm: AForm is not signed";
}

// Overload insertion operator
std::ostream &operator<<(std::ostream &out, const AForm &form)
{
    out << "AForm \"" << form.getName() << "\", signed: " << (form.getIsSigned() ? "yes" : "no")
        << ", grade to sign: " << form.getGradeToSign()
        << ", grade to execute: " << form.getGradeToExecute();
    return out;
}
