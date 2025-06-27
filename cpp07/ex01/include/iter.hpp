/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iter.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaosilva <joaosilva@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 11:09:40 by joaosilva         #+#    #+#             */
/*   Updated: 2025/06/27 11:10:48 by joaosilva        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITER_HPP
#define ITER_HPP

// iter: Applies the function f to each element of the array.
template <typename T>
void iter(T* array, int length, void (*f)(T const &))
{
    for (int i = 0; i < length; ++i)
        f(array[i]);
}

#endif
