/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaosilva <joaosilva@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 13:40:33 by joaosilva         #+#    #+#             */
/*   Updated: 2025/06/27 11:02:33 by joaosilva        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "Bureaucrat.hpp"
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"

int main()
{
    std::cout << std::endl;
    std::cout << "=== Bureaucrat and AForm Test ===\n" << std::endl;

    // Create Bureaucrat objects with different grades
    std::cout << "\n--- Bureaucrat creation ---" << std::endl;
    Bureaucrat low("Low", 150);
    Bureaucrat mid("Mid", 70);
    Bureaucrat boss("Boss", 1);
    
    std::cout << std::endl;
    
    // Form creation
    std::cout << "\n--- Form creation ---" << std::endl;
    ShrubberyCreationForm shrub("home");
    RobotomyRequestForm robot("Bender");
    PresidentialPardonForm pardon("Arthur Dent");
    
    std::cout << std::endl;
    
    std::cout << "\n--- Test 1: Signing forms: failure and success ---" << std::endl;
    try {
        low.signForm(shrub);  // Should FAIL to sign Shrubbery (required grade: 145, low's grade: 150)
    } catch (std::exception &e) {
        std::cout << e.what() << std::endl;
    }
    try {
        mid.signForm(robot); // Should SUCCEED to sign Robotomy (required grade: 72, mid's grade: 70)
    } catch (std::exception &e) {
        std::cout << e.what() << std::endl;
    }
    try {
        boss.signForm(pardon); // Should SUCCEED to sign Pardon (required grade: 25, boss's grade: 1)
    } catch (std::exception &e) {
        std::cout << e.what() << std::endl;
    }

    std::cout << "\n--- Test 2: Executing forms (failure) ---" << std::endl;

    // Shrubbery: low couldn't execute because it wasn't signed (requires grade: 137, low's grade: 150)
    low.executeForm(shrub);
    
    // Robotomy: mid couldn't execute because it wasn't signed (requires grade: 72, mid's grade: 70)
    mid.executeForm(robot);

    // Shrubbery: boss couldn't execute because it wasn't signed (requires grade: 137, boss's grade: 1)
    boss.executeForm(shrub);

    // Test 3: Signing and executing forms
    std::cout << "\n--- Test 3: Executing forms (success) ---" << std::endl;
    
    // Test 3.1.: newLow signs and executes ShrubberyCreationForm (should succeed)
    std::cout << "\n--- Test 3.1. - NewLow signs and executes ShrubberyCreationForm:" << std::endl;
    Bureaucrat newLow("newLow", 125);
    newLow.signForm(shrub); // NewLow signs Shrubbery (grade: 145, newLow's grade: 125)
    newLow.executeForm(shrub); // NewLow executes Shrubbery (grade: 137, newLow's grade: 125)

    // Test 3.2.: newMid signs and executes RobotomyRequestForm (should succeed)
    std::cout << "\n--- Test 3.2. - Newmid signs RobotomyRequestForm:" << std::endl;
    Bureaucrat newMid("newmid", 45);
    RobotomyRequestForm robot2("Bender2");
    newMid.signForm(robot2); // Newmid signs Robotomy (grade: 72, newMid's grade: 45)
    newMid.executeForm(robot2); // Newmid executes Robotomy (grade: 45, newMid's grade: 45)

    // Test 3.3.: Boss executes PresidentialPardonForm after signing it (should succeed)
    std::cout << "\n--- Test 3.3. - Boss executes PresidentialPardonForm:" << std::endl;
    boss.executeForm(pardon); // then executes it
    
    // Test 3.4.: Boss tries to sign and it fails but tries to execute and gets success.
    // And why? Because Execution can be performed by any Bureaucrat with a sufficient grade, 
    // as long as the form is signed (it doesn't matter by whom).
    std::cout << "\n--- Test 3.4. - Boss tries to execute RobotomyRequestForm: should fail" << std::endl;
    boss.signForm(robot); // Boss signs Robotomy (grade: 72, boss's grade: 1)
    boss.executeForm(robot); // Boss tries to execute Robotomy (grade: 45, boss's grade: 1)
    
    std::cout << "\n=== End of tests ===" << std::endl;
    return 0;
}
