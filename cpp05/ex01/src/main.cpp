/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaosilva <joaosilva@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 13:40:33 by joaosilva         #+#    #+#             */
/*   Updated: 2025/05/22 13:38:15 by joaosilva        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bureaucrat.hpp"

// Main function to test the Bureaucrat and Form classes
#include <iostream>
#include "Bureaucrat.hpp"
#include "Form.hpp"

int main() 
{
    std::cout << std::endl;
    std::cout << "=== Bureaucrat and Form Test ===" << std::endl << std::endl;
    std::cout << "=== Test 1: Form creation with valid and invalid grades ===" << std::endl;
    try {
        Form f1("FormA", 50, 100);
        std::cout << f1 << std::endl;
    } catch (std::exception &e) {
        std::cout << "Failed to create FormA: " << e.what() << std::endl;
    }
    try {
        Form f2("FormB", 0, 100); // Invalid grade to sign
    } catch (std::exception &e) {
        std::cout << "Failed to create FormB: " << e.what() << std::endl;
    }
    try {
        Form f3("FormC", 50, 151); // Invalid grade to execute
    } catch (std::exception &e) {
        std::cout << "Failed to create FormC: " << e.what() << std::endl;
    }

    std::cout << "\n=== Test 2: Bureaucrat tries to sign forms ===" << std::endl;
    Bureaucrat high("Alice", 1);
    Bureaucrat mid("Bob", 75);
    Bureaucrat low("Charlie", 150);
    std::cout << std::endl;
    
    Form easy("EasyForm", 150, 150);
    Form medium("MediumForm", 75, 75);
    Form hard("HardForm", 1, 1);
    std::cout << std::endl;
     
    std::cout << easy << std::endl;
    std::cout << medium << std::endl;
    std::cout << hard << std::endl;

    std::cout << "\n-- Bob tries to sign EasyForm (should succeed) --" << std::endl;
    mid.signForm(easy);
    std::cout << easy << std::endl;

    // Charlie cannot sign the MediumForm because his grade is 150 and the MediumForm requires a grade of 75 or higher (that is, a number less than or equal to 75).
    std::cout << "\n-- Charlie tries to sign MediumForm (should fail) --" << std::endl;
    low.signForm(medium);
    std::cout << medium << std::endl;

    std::cout << "\n-- Alice tries to sign HardForm (should succeed) --" << std::endl;
    high.signForm(hard);
    std::cout << hard << std::endl;

    std::cout << "\n-- Bob tries to sign HardForm (should fail) --" << std::endl;
    mid.signForm(hard);
    std::cout << hard << std::endl;

    std::cout << "\n-- Alice tries to sign EasyForm (already signed) --" << std::endl;
    high.signForm(easy);
    std::cout << easy << std::endl;

    std::cout << "\n=== Test 3: Copy constructor and assignment operator ===" << std::endl;

    // Test copy constructor
    std::cout << "=== Test Copy Constructor ===" << std::endl;
    Form original("OriginalForm", 42, 42);
    std::cout << "Original: " << original << std::endl;
    Form copy(original); // Calls copy constructor
    std::cout << "Copy (constructed): " << copy << std::endl;
    std::cout << std::endl;
    
    // Test assignment operator
    std::cout << "=== Test Assignment Operator ===" << std::endl;
    Form assigned("AssignedForm", 100, 100);
    std::cout << "Assigned before: " << assigned << std::endl;
    assigned = original; // Calls assignment operator
    std::cout << "Assigned after: " << assigned << std::endl;
    std::cout << std::endl;
    
    return 0;
}
