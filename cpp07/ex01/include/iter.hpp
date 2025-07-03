/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iter.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jode-jes <jode-jes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 11:09:40 by joaosilva         #+#    #+#             */
/*   Updated: 2025/07/02 11:13:14 by jode-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITER_HPP
#define ITER_HPP


/*// Generic Template version - accepts any callable
template <typename T, typename Function>
void iter(T* array, int length, Function f)
{
    for (int i = 0; i < length; ++i)
        f(array[i]);
}
*/

//Implementation to const
template <typename T>
void iter(T* array, int length, void (*f)(T const &))
{
    for (int i = 0; i < length; ++i)
        f(array[i]);
}

// Implementation to Non-Const
template <typename T>
void iter(T* array, int length, void (*f)(T &))
{
    for (int i = 0; i < length; ++i)
        f(array[i]);
}

#endif
