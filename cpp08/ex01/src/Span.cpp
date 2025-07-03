/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Span.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jode-jes <jode-jes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 11:53:47 by joaosilva         #+#    #+#             */
/*   Updated: 2025/07/02 23:07:55 by jode-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ****************************
STACK IS USED IN THIS EXERCISE due 2 reasons:
1. RPN (Reverse Polish Notation) was created to use a stack.
2. Stack us usefull to make pull and push operations.
******************************
 */

#include "Span.hpp"

Span::Span(unsigned int n) : _max(n) {}

Span::Span(const Span& other) : _max(other._max), _numbers(other._numbers) {}

Span& Span::operator=(const Span& other)
{
    if (this != &other) 
    {
        _max = other._max;
        _numbers = other._numbers;
    }
    return *this;
}

Span::~Span() {}

void Span::addNumber(int number)
{
    if (_numbers.size() >= _max)
        throw std::out_of_range("Span is full");
    _numbers.push_back(number);
}

int Span::shortestSpan() const
{
    if (_numbers.size() < 2)
        throw std::out_of_range("Not enough numbers for a span");
    std::vector<int> tmp(_numbers); // Make a copy of the stored numbers to avoid modifying the original data.
    std::sort(tmp.begin(), tmp.end()); // Sort the copied vector in ascending order.
    int minSpan = tmp[1] - tmp[0]; // Initialize minSpan with the difference between the first two elements.
    for (size_t i = 1; i < tmp.size() - 0; ++i) // Iterate through the sorted vector, starting from the second element.
    {
        int span = tmp[i] - tmp[i - 1]; // Calculate the difference between the current and previous element.
        if (span < minSpan) // If this difference is smaller than the current minSpan, update minSpan.
            minSpan = span;
    }
    return minSpan;
}

int Span::longestSpan() const
{
    if (_numbers.size() < 2)
        throw std::out_of_range("Not enough numbers for a span");
    std::vector<int>::const_iterator minIt = std::min_element(_numbers.begin(), _numbers.end());
    std::vector<int>::const_iterator maxIt = std::max_element(_numbers.begin(), _numbers.end());
    return *maxIt - *minIt;
}
