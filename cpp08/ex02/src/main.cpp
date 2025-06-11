/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaosilva <joaosilva@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 12:02:22 by joaosilva         #+#    #+#             */
/*   Updated: 2025/06/05 14:48:35 by joaosilva        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "MutantStack.hpp"
#include <list>
/* 
ex00 (Easy find):
The goal is to write a function template easyfind that searches for an integer 
in any STL container (like std::vector, std::list, etc.) using STL algorithms. 
If the value is found, it returns an iterator to it; if not, it throws an exception 
or returns an error value. This exercise is about using STL algorithms and templates.

ex01 (Span):
The goal is to implement a Span class that can store up to N integers and provides 
methods to add numbers, find the shortest span (smallest difference between any two numbers), 
and the longest span (largest difference). You must also implement a way to add
multiple numbers at once using a range of iterators. The exercise focuses on using 
STL containers, algorithms, and canonical class form.

ex02 (MutantStack):
The goal is to create a MutantStack class that inherits from std::stack and adds 
iterator support, making it possible to iterate through the stack like other STL containers. 
This exercise is about extending STL containers and working with iterators and templates.
*/

int main()
{
    // Create a MutantStack of integers.
    MutantStack<int> mstack;

    // Push values onto the stack.
    mstack.push(5);
    mstack.push(17);

    // Print the top value of the stack (should be 17).
    std::cout << std::endl;
    std::cout << "---------- TEST 1: ";
    std::cout << "Print the top value of the stack ... " << mstack.top() << std::endl;

    // Remove the top value (17) from the stack.
    std::cout << std::endl;
    std::cout << "---------- TEST 2: ";
    std::cout << "Remove the top value (17) from the stack and ";
    mstack.pop();

    // Print the current size of the stack (should be 1).
    std::cout << "Print the current value of the stack (should be 1): " << std::endl;
    std::cout << mstack.size() << std::endl;

    // Push more values onto the stack.
    mstack.push(3);
    mstack.push(5);
    mstack.push(737);
    mstack.push(0);

    // Create iterators to the beginning and end of the stack.
    MutantStack<int>::iterator it = mstack.begin();
    MutantStack<int>::iterator ite = mstack.end();

        // Increment and then decrement the iterator (demonstrates iterator operations).
    // ++it;
    // --it;
    // Print the value at the initial iterator position
    std::cout << std::endl;
    std::cout << "---------- TEST 3: ";
    std::cout << "Testing iterator incrementation/decrementation" << std::endl;
    std::cout << "Initial iterator value: " << *it << std::endl;

    // Increment the iterator and print the new value
    ++it;
    std::cout << "After increment (++it): " << *it << std::endl;

    // Decrement the iterator and print the value again (should be back to the initial)
    --it;
    std::cout << "After decrement (--it): " << *it << std::endl;

    // Iterate through the stack and print each value.
    std::cout << std::endl;
    std::cout << "---------- TEST 4: ";
    std::cout << "Iterate through the stack and print each value: " << std::endl;
    while (it != ite)
    {
        std::cout << *it << " ";
        ++it;
    }
    std::cout << std::endl;
    
    // Create a standard stack as a copy of the MutantStack.
    std::stack<int> s(mstack);
    // Extra tests: create another MutantStack and fill it with values 0 to 9.
    MutantStack<int> m2;
    for (int i = 0; i < 10; ++i)
        m2.push(i);
    // Print all values in the standard stack s (will be printed from top to bottom)
    std::cout << std::endl;
    std::cout << "---------- TEST 5: ";
    std::cout << "Print all values in the --- COPIED --- standard stack s: " << std::endl;
    // In each iteration: It prints the current top value of the stack.
    // Then it removes that value from the stack.
    // This loop prints all the elements of the stack from top to bottom (LIFO order), 
    // and at the end, the stack s will be empty.
    // "from top to bottom" means from the last element added to the first element added.
    // The top of the stack is the most recently added element (last-in).
    // The bottom is the first element that was added (first-in).
    while (!s.empty())
    {
        std::cout << s.top() << " "; // s.top() returns the value at the top of the stack (the most recently added element).
        s.pop(); // s.pop() removes the top element from the stack.
    }
    std::cout << std::endl; 

    // Print all values in m2 using iterators.
    std::cout << std::endl;
    std::cout << "---------- TEST 6: ";
    std::cout << "Print all values in m2 using iterators: " << std::endl;
    for (MutantStack<int>::iterator i = m2.begin(); i != m2.end(); ++i)
        std::cout << *i << " ";
    std::cout << std::endl;

    // Comparison: create a std::list and fill it with values 0 to 9.
    std::list<int> l;
    for (int i = 0; i < 10; ++i)
        l.push_back(i);

    // Print all values in the list using iterators.
    std::cout << std::endl;
    std::cout << "---------- TEST 7: ";
    std::cout << "Print all values in the list using iterators: " << std::endl;
    for (std::list<int>::iterator i = l.begin(); i != l.end(); ++i)
        std::cout << *i << " ";
    
    std::cout << std::endl;
    std::cout << std::endl;

    return 0;
}
