/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Form.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaosilva <joaosilva@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 12:14:48 by joaosilva         #+#    #+#             */
/*   Updated: 2025/06/27 11:00:09 by joaosilva        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FORM_HPP
#define FORM_HPP

#include "Bureaucrat.hpp"

class Bureaucrat;

class Form 
{
    private:
        const std::string   _name;
        bool                _isSigned;
        const int           _gradeToSign;
        const int           _gradeToExecute;

    public:
        // Constructors & Destructor
        Form();
        Form(const std::string name, int gradeToSign, int gradeToExecute);
        Form(const Form &src);
        ~Form();

        // Assignment operator
        Form &operator=(const Form &src);

        // Getters
        std::string getName() const;
        bool        getGradeIsSigned() const; // Is grade already signed?
        int         getGradeToSign() const; // Grade to sign
        int         getGradeToExecute() const; // Grade to execute

        // Member function
        void        beSigned(const Bureaucrat &bureaucrat);

         // Exceptions
        class GradeTooHighException : public std::exception {
            public:
                virtual const char* what() const throw();
        };
        class GradeTooLowException : public std::exception {
            public:
                virtual const char* what() const throw();
        };
};

// Overload insertion operator
std::ostream &operator<<(std::ostream &out, const Form &form);

#endif
