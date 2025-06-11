/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   whatever.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaosilva <joaosilva@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 09:54:24 by joaosilva         #+#    #+#             */
/*   Updated: 2025/06/05 15:22:48 by joaosilva        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WHATEVER_HPP
#define WHATEVER_HPP

// swap: Swaps the values of two given parameters.
template <typename T>
void swap(T &a, T &b)
{
    T tmp = a;
    a = b;
    b = tmp;
}

// min: Returns the smallest of two values. If equal, returns the second. 
template <typename T>
const T &min(const T &a, const T &b)
{
    return (a < b) ? a : b; // If a is less than b, return a; otherwise, return b. returns the second because if a is equal to b, then a < b is false, and as a result it will return b.
}

// max: Returns the greatest of two values. If equal, returns the second.
template <typename T>
const T &max(const T &a, const T &b)
{
    return (a > b) ? a : b;
}

#endif
