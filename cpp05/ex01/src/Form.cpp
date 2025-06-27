/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Form.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaosilva <joaosilva@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 12:15:07 by joaosilva         #+#    #+#             */
/*   Updated: 2025/06/27 11:00:17 by joaosilva        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Form.hpp"

// Constructor
Form::Form(const std::string name, int gradeToSign, int gradeToExecute)
    : _name(name), _isSigned(false), _gradeToSign(gradeToSign), _gradeToExecute(gradeToExecute)
{
    if (gradeToSign < 1 || gradeToExecute < 1)
        throw Form::GradeTooHighException();
    if (gradeToSign > 150 || gradeToExecute > 150)
        throw Form::GradeTooLowException();
    std::cout << "Form constructor called!" << std::endl;
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
// Copy constructor
Form::Form(const Form &src)
    : _name(src._name), _isSigned(src._isSigned),
      _gradeToSign(src._gradeToSign), _gradeToExecute(src._gradeToExecute)
{
    std::cout << "Form copy constructor called!" << std::endl;
    // Don´t call *this = src;
}

// Destructor
Form::~Form() {std::cout << "Form destructor called!" << std::endl;}

// Assignment operator
Form &Form::operator=(const Form &src)
{
    std::cout << "Form assignment operator called!" << std::endl;
    if (this != &src)
        this->_isSigned = src._isSigned;
    return *this;
}

// Getters
std::string Form::getName() const { return _name; }
bool        Form::getGradeIsSigned() const { return _isSigned; }
int         Form::getGradeToSign() const { return _gradeToSign; }
int         Form::getGradeToExecute() const { return _gradeToExecute; }

// beSigned implementation
void Form::beSigned(const Bureaucrat &bureaucrat)
{
    if (_isSigned)
        throw std::runtime_error("Form is already signed");
    if (bureaucrat.getGrade() > _gradeToSign)
        throw Form::GradeTooLowException();
    _isSigned = true;
}

// Exception messages
const char* Form::GradeTooHighException::what() const throw()
{
    return "Form: Grade is too high";
}
const char* Form::GradeTooLowException::what() const throw()
{
    return "Form: Grade is too low";
}

// Overload insertion operator
std::ostream &operator<<(std::ostream &out, const Form &form)
{
    out << "Form \"" << form.getName() << "\", signed: " << (form.getGradeIsSigned() ? "yes" : "no")
        << ", grade to sign: " << form.getGradeToSign()
        << ", grade to execute: " << form.getGradeToExecute();
    return out;
}
