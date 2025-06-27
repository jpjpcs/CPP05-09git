/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaosilva <joaosilva@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 09:53:58 by joaosilva         #+#    #+#             */
/*   Updated: 2025/06/27 11:10:24 by joaosilva        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <string>
#include "whatever.hpp"

/*
The goal of this exercise is to create three template functions: swap, min, and max.
1 - Use of ::swap(a, b); in the main: 
    Yes, you can (and should) use ::swap(a, b); in your main.
    The :: means you are calling the function from the global namespace, which is exactly where your template function is defined.
    This is not because it is a template, but because it is a free function (not inside a class or namespace).
    Using ::swap avoids ambiguity with any other swap function (like std::swap).
    This is the correct and expected usage for global-scope functions, especially in 42 projects.
    Summary:
    You use ::swap(a, b); because your function is in the global namespace, not because it is a template or because it is not in a class.
2 - In the subject it says:
    "These functions can be called with any type of argument. The only requirement is
    that the two arguments must have the same type and must support all the comparison
    operators"
    a - What does this mean?
        It means your swap, min, and max functions can be used with any type (like int, float, std::string, or your own classes), as long as:
        - Both arguments are of the same type (e.g., int and int, or std::string and std::string).
        - The type supports the necessary operators:
            . For swap: assignment (=)
            . For min and max: comparison operators (< and >)
    b - If I wanted to call with different types of arguments, what should I do? Use cast? static or dynamic cast?
        If you want to use different types (e.g., min(2, 2.5)), you must explicitly cast one argument so both have the same type.
        Use static_cast for this purpose, for example: min(static_cast<double>(2), 2.5);
        dynamic_cast is only for polymorphic classes (with virtual functions) and is not used for basic types or most user-defined types.
        In general, always use static_cast for converting between compatible types (like int to double).
        Summary:
        The template functions require both arguments to be the same type.
        If you want to use different types, cast one to match the other using static_cast.
*/

int main(void)
{
    int a = 2;
    int b = 3;
    ::swap(a, b); // comment above.
    std::cout << "a = " << a << ", b = " << b << std::endl;
    std::cout << "min(a, b) = " << ::min(a, b) << std::endl;
    std::cout << "max(a, b) = " << ::max(a, b) << std::endl;

    std::string c = "chaine1";
    std::string d = "chaine2";
    
    ::swap(c, d);
    std::cout << "c = " << c << ", d = " << d << std::endl;
    std::cout << "min(c, d) = " << ::min(c, d) << std::endl;
    std::cout << "max(c, d) = " << ::max(c, d) << std::endl;

    return 0;
}
