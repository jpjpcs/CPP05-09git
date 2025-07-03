/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Span.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jode-jes <jode-jes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 11:53:25 by joaosilva         #+#    #+#             */
/*   Updated: 2025/07/02 22:58:49 by jode-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SPAN_HPP
#define SPAN_HPP

#include <vector> // for std::vector
#include <stdexcept> // for std::runtime_error
#include <algorithm> // for std::sort, std::min_element, std::max_element

/*
1 - How if (_numbers.size() + std::distance(begin, end) > _max) works?
    1.1. This line checks if adding all the elements from the given range 
        would make the container exceed its maximum allowed size:
    How does it work?
        . _numbers.size() is the current number of elements already stored in the Span.
        . std::distance(begin, end) calculates how many elements are 
            in the range you want to add.
        . Adding these two gives the total number of elements that would be 
            in the Span after the insertion.
        . If this total is greater than _max (the maximum allowed), 
            it means you would exceed the Span's capacity, so the function throws an exception.
    Example:
        If _numbers.size() is 7, std::distance(begin, end) is 4, and _max is 10:
        7 + 4 = 11 > 10 → Exception is thrown.
    1.2. For a vector, std::distance(begin, end) gives you the number of elements in the range [begin, end).
        If you use begin = v.begin() and end = v.end(), then std::distance(begin, end) 
        is exactly the same as v.size().
        Example:
            std::vector<int> v(10); // 10 elements
            std::vector<int>::iterator it1 = v.begin();
            std::vector<int>::iterator it2 = v.end();

            std::cout << v.size() << std::endl;           // prints 10
            std::cout << std::distance(it1, it2) << std::endl; // also prints 10
        So, for the whole vector, std::distance(v.begin(), v.end()) == v.size().
        But std::distance can also be used for subranges (not just the whole container).
    1.3. We use both .size() and std::distance(begin, end) in this line:
        if (_numbers.size() + std::distance(begin, end) > _max)
    because: 
       . _numbers.size() gives the current number of elements already 
            stored in the Span.
       . std::distance(begin, end) gives the number of new elements 
            you want to add (from the iterator range).
       . Adding them together gives the total number of elements that 
            would be in the Span after the insertion.
       . This check ensures that, if you add all the new elements, 
            you do not exceed the maximum allowed size (_max).
       . If the total would be greater than _max, the function 
            throws an exception to prevent overflow.
    Summary:
        . size() → current elements
        . std::distance(begin, end) → elements to add
        . Together → total after insertion
        . If total > max, throw exception
*/

class Span
{
    public:
        Span(unsigned int n);
        Span(const Span& other);
        Span& operator=(const Span& other);
        ~Span();

        void addNumber(int number);
        template <typename InputIt> // We can use template functions in the header as long they are only template functions.
        void addNumbers(InputIt begin, InputIt end)
        {
            if (_numbers.size() + std::distance(begin, end) > _max) //Comment above - Check if adding all elements in the range would exceed the maximum allowed size.
                throw std::runtime_error("Span is full");
            _numbers.insert(_numbers.end(), begin, end); // Insert all elements from the range [begin, end) at the end of the _numbers vector.
        }
        int shortestSpan() const;
        int longestSpan() const;

    private:
        unsigned int _max;
        std::vector<int> _numbers;
};

#endif
