/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MutantStack.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jode-jes <jode-jes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 12:02:07 by joaosilva         #+#    #+#             */
/*   Updated: 2025/07/02 22:55:17 by jode-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MUTANTSTACK_HPP
#define MUTANTSTACK_HPP

#include <stack>
#include <deque>

/*
1 - Can we put copy constructor in the header?
    For template classes, all member functions—including the copy constructor, 
    assignment operator, and destructor—must be implemented in the header file.
    Why?
    . The rule about "no function implementation in the header except for 
        template functions" applies to non-template classes.
    . For template classes, the compiler needs to see the full implementation 
        of all member functions (including the copy constructor, 
        assignment operator, destructor, etc.) in every translation unit that 
        uses the template with a specific type.
    . This is because template instantiation happens at compile time, 
        and the compiler must have access to the code.
    So:
    . Even though the copy constructor is not itself a template function, 
        it is a member of a template class.
    . Therefore, it must be implemented in the header file, together with 
        all other member functions of the template class.
    Summary:
    . For template classes: All member functions (including copy constructor, 
        assignment operator, destructor, etc.) must be implemented in the header file.
    . For non-template classes: Only template functions can be implemented in the header; 
        all other functions must go in the .cpp file.
2 - Accordingy with the subject and the rules, can I use std::out_of_range?
    Yes, you can use std::out_of_range in your easyfind implementation 
    according to the subject and rules.
    The subject says you can throw an exception of your choice if 
    the value is not found.
    std::out_of_range is a standard exception used by STL containers 
    (like vector::at()) when an element is not found or is out of bounds.
    It is included in <stdexcept>, which is allowed.
    There are no restrictions in the subject or rules against using std::out_of_range.
    Conclusion:
        Using throw std::out_of_range("Value not found"); is correct, 
        standard, and even slightly more precise than std::runtime_error for this case. 
        Both are accepted, but std::out_of_range is a good STL-style choice.
3 - Difference between std::runtime_error and std::out_of_range:
    std::runtime_error is a general-purpose exception for runtime errors.
    std::out_of_range is a specific exception for cases where an index or key is out of bounds.
    In this case, since we are looking for a value in a container, 
    std::out_of_range is more appropriate as it indicates the value was not found 
    within the valid range of the container.
4 - Difference between std::runtime_error and std::invalid_argument:
    std::runtime_error is a general-purpose exception for runtime errors.
    std::invalid_argument is used when an argument passed to a function is invalid.
    In this case, since we are not passing an invalid argument but rather 
    indicating that a value was not found in the container, std::runtime_error 
    or std::out_of_range would be more appropriate.
5 - Difference between std::runtime_error and std::distance:
    std::runtime_error is an exception type used to indicate runtime errors.
    std::distance is a function that calculates the distance between two iterators.
    std::distance(begin, it) gives you the index of it).
    Use std::distance if you want to know the position/index of an iterator in a container.
    They serve different purposes: std::runtime_error is for error handling, 
    while std::distance is for iterator arithmetic.
    Resume:
        Best practice here:
            std::runtime_error is perfectly acceptable and generic.
            std::invalid_argument is less appropriate, because the argument 
            is not invalid—the value just wasn't found.
            std::distance is not an exception; it's a function to calculate the distance
            between two iterators, which is not relevant for this context.
            std::out_of_range is more specific and idiomatic for this case,
            as it indicates that the value was not found within the valid range of the container.
            However, std::runtime_error is also fine and idiomatic for this context.
            So, you can use either std::runtime_error or std::out_of_range.
            If you want to be even more precise, you could use std::out_of_range, 
            but std::runtime_error is totally fine and idiomatic for this context.\
*/

template <typename T>
class MutantStack : public std::stack<T>
{
    public:
        typedef typename std::stack<T>::container_type::iterator iterator;
        typedef typename std::stack<T>::container_type::const_iterator const_iterator;

        MutantStack() : std::stack<T>() {}
        MutantStack(const MutantStack& other) : std::stack<T>(other) {}
        MutantStack& operator=(const MutantStack& other)
        {
            std::stack<T>::operator=(other);
            return *this;
        }
        ~MutantStack() {}

        iterator begin() { return this->c.begin(); }
        iterator end() { return this->c.end(); }
        const_iterator begin() const { return this->c.begin(); }
        const_iterator end() const { return this->c.end(); }
};

#endif
