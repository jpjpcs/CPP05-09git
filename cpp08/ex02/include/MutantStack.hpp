/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MutantStack.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaosilva <joaosilva@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 12:02:07 by joaosilva         #+#    #+#             */
/*   Updated: 2025/06/05 13:43:27 by joaosilva        ###   ########.fr       */
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
