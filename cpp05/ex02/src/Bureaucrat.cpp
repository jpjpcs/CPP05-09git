/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bureaucrat.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaosilva <joaosilva@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 13:40:22 by joaosilva         #+#    #+#             */
/*   Updated: 2025/05/23 12:33:47 by joaosilva        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bureaucrat.hpp"

// Default constructor: sets name to "default" and grade to 150
Bureaucrat::Bureaucrat() : _name("default"), _grade(150) 
{
    std::cout << "Bureaucrat default constructor called!" << std::endl;
}

// Parameterized constructor: initializes name and grade, checks grade validity
Bureaucrat::Bureaucrat(const std::string name, int grade) : _name(name), _grade(grade) 
{
    if (grade < 1) // If grade is too high (less than 1)
        throw Bureaucrat::GradeTooHighException();
    if (grade > 150) // If grade is too low (greater than 150)
        throw Bureaucrat::GradeTooLowException();
    std::cout << "Bureaucrat parameterized constructor called!" << std::endl;
}

// Copy constructor: copies name and grade from source
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
// Copy constructor: copies name and grade from source
Bureaucrat::Bureaucrat(const Bureaucrat &src)
    : _name(src._name), _grade(src._grade)
{
    std::cout << "Bureaucrat copy constructor called!" << std::endl;
    // don´t call *this = src;
}

// Destructor
Bureaucrat::~Bureaucrat() 
{
    std::cout << "Bureaucrat destructor called!" << std::endl;
}

/*
You could also do it like this:
Bureaucrat &Bureaucrat::operator=(const Bureaucrat &src) {
    if (this != &src) { // Check for self-assignment
        _grade = src._grade; // Copy grade
    }
    return *this; // Return reference to this object
}
But this is not good practice.
The most recommended way is to use the first approach, with the getter (rhs.getGrade()):
Using the getter (getGrade()) respects the encapsulation of the class.
If _grade is private (as is common), accessing it directly (src._grade) may not be allowed outside the class.
The getter may contain extra logic in the future (validation, logs, etc).
*/
// Assignment operator: copies grade from source (name is const, cannot be changed)
Bureaucrat &Bureaucrat::operator=(const Bureaucrat &src) 
{
    std::cout << "Bureaucrat assignment operator called!" << std::endl;
    if (this != &src) { // Check for self-assignment
        this->_grade = src.getGrade(); // Copy grade
    }
    return *this; // Return reference to this object
}

// Getter for name
std::string Bureaucrat::getName() const 
{
    return _name; // Return the constant name
}

// Getter for grade
int Bureaucrat::getGrade() const 
{
    return _grade; // Return the current grade
}

/* 
1 - Ambiguity happens when the parameter name or a local variable has the same name as a class member.

    void Bureaucrat::setGrade(int _grade) {
        _grade = _grade; // This assigns the parameter to itself, not to the class member!
    }

Using this-> removes this ambiguity, making it clear that you are accessing the instance member. If you need to highlight that you are using a class member (for example, in large methods or with ambiguous names), use this->. Otherwise, _grade is sufficient and more readable. The difference between using this->_grade and just _grade is mainly about style and clarity, not functionality:

this->_grade:
    Uses the explicit this pointer, making it clear you are accessing a member of the current instance.
    Useful when there is ambiguity (e.g., a parameter or local variable has the same name).

_grade:
    Directly accesses the class member.
    Works the same inside non-static methods, as long as there is no ambiguity.

2 - According to the 42 subject standard and good C++ practices, the used form is correct instead of this one:

    void Bureaucrat::incrementGrade(){
        try{
            if (_grade - 1 < 1)
                throw Bureaucrat::GradeTooHighException();
            _grade--;
        }
        catch(const std::exception& e){
            std::cerr << e.what() << '\n';
        }
    }
Why?
    The subject usually requires that exceptions are thrown, not handled inside the method itself.
    Exception handling (try/catch) should be done by whoever calls the method, not inside it.
    This allows the code to be more flexible and follows the single responsibility principle.
    Do not put try/catch inside the method.
    Throw the exception and let the calling code handle it.
    Exception handling should be done in main (or by whoever calls the method).
    This way, you can decide how to handle the error (show a message, exit the program, etc).

Summary:

    The method throws the exception.
    main (or the caller) handles it with try/catch.
*/

// Increments grade (decreases number), throws exception if too high
void Bureaucrat::incrementGrade() 
{
    if (_grade - 1 < 1) // Check if new grade would be less than 1
        throw Bureaucrat::GradeTooHighException();
    _grade--; // Decrease grade (e.g., 3 to 2)
}

// Decrements grade (increases number), throws exception if too low
void Bureaucrat::decrementGrade() 
{
    if (_grade + 1 > 150) // Check if new grade would be more than 150
        throw Bureaucrat::GradeTooLowException();
    _grade++; // Increase grade (e.g., 2 to 3)
}

// Exception message for GradeTooHighException
const char* Bureaucrat::GradeTooHighException::what() const throw() 
{
    return ("Grade is too high\n");
}

// Exception message for GradeTooLowException
const char* Bureaucrat::GradeTooLowException::what() const throw() 
{
    return ("Grade is too low.\n");
}

// Overload insertion operator to print Bureaucrat details
std::ostream &operator<<(std::ostream &out, const Bureaucrat &src) 
{
    out << src.getName() << ", bureaucrat grade " << src.getGrade(); // Print name and grade
    return out; // Return output stream
}

void Bureaucrat::signForm(AForm &form) 
{
    try {
        form.beSigned(*this);
        std::cout << _name << " signed " << form.getName() << std::endl;
    } 
    catch (std::exception &e) {
        std::cout << _name << " couldn't sign " << form.getName()
                  << " because " << e.what() << std::endl;
    }
}

void Bureaucrat::executeForm(AForm const &form) const
{
    try {
        form.execute(*this); // *this is the Bureaucrat object calling the method. In the case of low.executeForm(shrub); is low.
        std::cout << this->_name << " executed " << form.getName() << std::endl;
    } catch (std::exception &e) {
        std::cout << this->_name << " couldn't execute " << form.getName()
                  << " because " << e.what() << std::endl;
    }
}
