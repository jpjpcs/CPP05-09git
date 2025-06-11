/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bureaucrat.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaosilva <joaosilva@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 13:40:16 by joaosilva         #+#    #+#             */
/*   Updated: 2025/05/22 21:09:15 by joaosilva        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUREAUCRAT_HPP
#define BUREAUCRAT_HPP

#include <iostream>
#include <string>
#include <stdexcept> 
#include "AForm.hpp" // Include Form class for Bureaucrat to interact with

class AForm; // Forward declaration of Form class

// Defining the Bureaucrat class in Orthodox Canonical Form
class Bureaucrat
{
    private:
        const std::string _name; // Constant name of the bureaucrat
        int _grade;              // Grade of the bureaucrat (1 to 150)

    public:
        // Constructors
        Bureaucrat();                              // Default constructor
        Bureaucrat(const std::string name, int grade); // Parameterized constructor
        Bureaucrat(const Bureaucrat &src);         // Copy constructor
        // Destructor
        ~Bureaucrat();
        // Assignment operator
        Bureaucrat &operator=(const Bureaucrat &src);

        // Getters
        std::string getName() const; // Returns the bureaucrat's name
        int getGrade() const;        // Returns the bureaucrat's grade

        // Member functions
        void incrementGrade(); // Increments grade (decreases number, e.g., 3 to 2)
        void decrementGrade(); // Decrements grade (increases number, e.g., 2 to 3)
        void signForm(AForm &form);
        void executeForm(AForm const &form) const;

        // Exception classes
        class GradeTooHighException : public std::exception 
        {
            public:
                virtual const char* what() const throw(); // Returns error message for high grade. The what is a virtual function that returns a string with the error message. The throw indicates that the function may throw exceptions. Both exception classes inherit from std::exception, which is the base class for all standard exceptions in C++. This allows you to use these exceptions anywhere a std::exception is expected. The function is marked as const, indicating that it does not modify the state of the object. This is important to ensure that the function can be called on constant objects. 
        };

        class GradeTooLowException : public std::exception 
        {
            public:
                virtual const char* what() const throw(); // Returns error message for low grade
        };
};

// Overload of the insertion operator for printing Bureaucrat
std::ostream &operator<<(std::ostream &out, const Bureaucrat &src);

#endif
