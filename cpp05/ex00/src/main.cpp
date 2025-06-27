/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaosilva <joaosilva@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 13:40:33 by joaosilva         #+#    #+#             */
/*   Updated: 2025/06/27 10:58:09 by joaosilva        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bureaucrat.hpp"

/*
Why are destructors called after each test and not only at the end of main?

    This happens because local variables inside each try block (for example, Bureaucrat joao("João Silva", 2);) are local objects that exist only during that block.
    When the try block ends (either because it finished normally or because an exception was thrown and caught), those local variables are immediately destroyed, calling their destructors.

    More in detail:
        In your code, each test creates Bureaucrat objects inside its own try block.
        When the flow exits the try (after executing the code inside it, or after throwing/catching exceptions), the local scope ends.
        Local variables (the Bureaucrat objects) go out of scope — and this automatically invokes the destructor.
        That’s why the destructor is called right after the test ends, not at the end of main.
        If you want the destructors to be called only at the end of main:
        You would have to create the objects outside the try-catch blocks and keep their lifetime until the end of main.
            Bureaucrat joao("João Silva", 2);
            try {
                joao.incrementGrade();
                joao.incrementGrade(); // May throw exception
            } catch (const std::exception &e) {
                std::cerr << "Error: " << e.what() << std::endl;
            }
    Burocraut joao's destructor will be called only at the end of main, when joao goes out of scope.

Why did I say "not recommended" in that example?
    It’s more about good design and code clarity than about something technically wrong.
    Here are the main reasons:
    Separating object creation and exception handling helps keep the code clearer
    Normally, it makes sense to create the object inside the try block because the construction itself can throw exceptions (like in your case if the grade is invalid).
    This way, the try block covers all the failure-prone code — construction and operations — and catching exceptions is more organized.

    Keep object lifetime as limited as possible
        If you create objects before the try, their lifetime might be longer than necessary.
        The shorter the lifetime, the lower the risk of unexpected errors and the easier it is to manage resources (e.g., memory, files, connections).
        In your example, ideally, the object should only live while needed — inside the try block.
        Exceptions during construction are easier to manage if the object is created inside the try
        If object construction fails and throws, you cannot catch that exception outside the try.
        Therefore, it is safer to put the construction inside the try.

    Summary
        The example with the object created outside the try can work but loses clarity, organization, and good practices.
        Creating the object inside the try is more idiomatic, safer, and clearer.
        That’s why I said “not recommended” — not because it’s wrong, but because it doesn’t follow best practices for exception handling.
*/

// Main function to test Bureaucrat class functionality
int main() 
{
    // Test 1: Invalid grade (too high)
    std::cout << "Test 1: Invalid grade (too high)" << std::endl;
    try {
        Bureaucrat invalidHigh("InvalidHigh", 0); // Try to create bureaucrat with grade 0
        std::cout << invalidHigh << std::endl; // Should not reach here
    } catch (const std::exception &e) {
        std::cerr << "Error: " << e.what() << std::endl; // Print exception message
    }

    // Test 2: Invalid grade (too low)
    std::cout << "Test 2: Invalid grade (too low)" << std::endl;
    try {
        Bureaucrat invalidLow("InvalidLow", 151); // Try to create bureaucrat with grade 151
        std::cout << invalidLow << std::endl; // Should not reach here
    } catch (const std::exception &e) {
        std::cerr << "Error: " << e.what() << std::endl; // Print exception message
    }

    // Test 3: Increment grade to highest possible
    std::cout << "Test 3: Increment grade to highest possible" << std::endl;
    try {
        Bureaucrat joao("João Silva", 2); // Create bureaucrat with grade 2
        std::cout << joao << std::endl; // Print initial state
        joao.incrementGrade(); // Try to increment to grade 1
        std::cout << joao << std::endl; // Print new state
        joao.incrementGrade(); // Try to increment to grade 0 (should throw)
        std::cout << joao << std::endl; // Should not reach here
    } catch (const std::exception &e) {
        std::cerr << "Error: " << e.what() << std::endl; // Print exception message
    }

    // Test 4: Decrement grade to lowest possible
    std::cout << "Test 4: Decrement grade to lowest possible" << std::endl;
    try {
        Bureaucrat low("LowGrade", 150); // Create bureaucrat with lowest grade
        std::cout << low << std::endl; // Print initial state
        low.decrementGrade(); // Try to decrement to 151 (should throw)
        std::cout << low << std::endl; // Should not reach here
    } catch (const std::exception &e) {
        std::cerr << "Error: " << e.what() << std::endl; // Print exception message
    }

    // Test 5: Copy constructor and assignment operator
    std::cout << "Test 5: Copy constructor and assignment operator" << std::endl;
    try {
        Bureaucrat original("Original", 100); // Create original bureaucrat
        Bureaucrat copy(original); // Use copy constructor
        Bureaucrat assigned("Assigned", 50); // Create another bureaucrat
        assigned = original; // Use assignment operator
        std::cout << "Original: " << original << std::endl; // Print original
        std::cout << "Copy: " << copy << std::endl; // Print copy
        std::cout << "Assigned: " << assigned << std::endl; // Print assigned
    } catch (const std::exception &e) {
        std::cerr << "Error: " << e.what() << std::endl; // Print exception message
    }
    std::cout << std::endl;
    return 0;
}
