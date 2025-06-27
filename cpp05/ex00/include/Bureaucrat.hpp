/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bureaucrat.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaosilva <joaosilva@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 13:40:16 by joaosilva         #+#    #+#             */
/*   Updated: 2025/06/27 10:57:59 by joaosilva        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUREAUCRAT_HPP
#define BUREAUCRAT_HPP

#include <iostream>
#include <string>
#include <stdexcept> 

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

        // Exception classes
        class GradeTooHighException : public std::exception 
        {
            public:
                virtual const char* what() const throw(); // Returns error message for high grade. O what é uma função virtual que retorna uma string com a mensagem de erro. O throw indica que a função pode lançar exceções. Ambas as classes de exceção herdam de std::exception, que é a classe base para todas as exceções padrão em C++. Isso permite que você use essas exceções em qualquer lugar onde uma std::exception seja esperada. A função é marcada como const, indicando que não modifica o estado do objeto. Isso é importante para garantir que a função possa ser chamada em objetos constantes. 
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
