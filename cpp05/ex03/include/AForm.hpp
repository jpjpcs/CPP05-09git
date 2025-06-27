/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AForm.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaosilva <joaosilva@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 12:14:48 by joaosilva         #+#    #+#             */
/*   Updated: 2025/06/27 11:03:07 by joaosilva        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AFORM_HPP
#define AFORM_HPP

#include "Bureaucrat.hpp"

class Bureaucrat;

class AForm
{
    private:
        const std::string   _name;
        bool                _isSigned;
        const int           _gradeToSign;
        const int           _gradeToExecute;

    public:
        // Constructors & Destructor
        AForm();
        AForm(const std::string &name, int gradeToSign, int gradeToExecute);
        AForm(const AForm &src);
        virtual ~AForm();

        // Assignment operator
        AForm &operator=(const AForm &src);

        // Getters
        std::string getName() const;
        bool        getIsSigned() const;
        int         getGradeToSign() const;
        int         getGradeToExecute() const;

        // Member functions
        void        beSigned(const Bureaucrat &bureaucrat);
        virtual void execute(Bureaucrat const &executor) const = 0;

        // Exceptions
        class GradeTooHighException : public std::exception {
            public: virtual const char* what() const throw();
        };
        class GradeTooLowException : public std::exception {
            public: virtual const char* what() const throw();
        };
        class FormNotSignedException : public std::exception {
            public: virtual const char* what() const throw();
        };
};

std::ostream &operator<<(std::ostream &out, const AForm &form);

#endif
