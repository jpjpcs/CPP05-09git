/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaosilva <joaosilva@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 11:10:30 by joaosilva         #+#    #+#             */
/*   Updated: 2025/06/27 11:04:46 by joaosilva        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ScalarConverter.hpp"
#include <iostream>

/*
1 - The aim of this exercise is to implement a ScalarConverter class that converts 
various types of literals (char, int, float, double) to their corresponding types in C++. 
The class should handle conversions and print the results.
And why? To use static cast functions like static_cast<char>, static_cast<int>, 
static_cast<float>, and static_cast<double> to convert the literals to their corresponding types.

2 - A double literal is a value written in code that represents a double type in C++. Examples: 0.0, -4.2, 3.14, 42.0. Double literals always have a decimal point and do not use the f suffix (which is for float).

    nan, +inf, and -inf are called special floating-point values or pseudo-literals.

    nan stands for "Not a Number" (e.g., the result of 0.0/0.0)
    +inf and -inf represent positive and negative infinity (e.g., the result of 1.0/0.0 or -1.0/0.0)
    They are part of the IEEE 754 floating-point standard, which C++ uses for float and double. Even though they are not regular numbers, they are valid values for the double type and can be written as literals in C++ code.

    A double is a floating-point type in C++ that can represent real numbers (numbers with decimals), both positive and negative, as well as special values like infinity and NaN.
    A double is a floating-point type (not fixed-point). It uses scientific notation internally and can represent very large or very small numbers with a certain precision.

    An int is an integer type that can only represent whole numbers (without decimals), both positive and negative.

    Main differences:
        double can store fractional (decimal) values; int cannot.
        double has a much larger range and can represent very small or very large numbers, but with limited precision.
        double supports special values like nan and inf; int does not.
*/

/* int main() 
{
    const char* tests[] = 
    {
        "'a'",    // char literal
        "'*'",    // char literal
        "0",      // int
        "-42",    // negative int
        "42",     // positive int
        "2147483647", // INT_MAX
        "-2147483648", // INT_MIN
        "2147483648", // above INT_MAX
        "-2147483649", // bellow INT_MIN
        "0.0f",   // float
        "42.0f",  // float (subject example)
        "-4.2f",  // negative float
        "4.2f",   // positive float
        "-inff",  // float pseudo-literal. Tests the -INFINITY value
        "+inff",  // float pseudo-literal. Tests the INFINITY value.
        "nanf",   // float pseudo-literal. Tests the Not a Number value. NAN is sometthing that is not a number, like 0.0/0.0 or sqrt(-1.0) or log(-1.0) or log10(0.0) or log(0.0) or log2(0.0) or log1p(-1.0) or log1p(0.0) or log2(0.0) or log10(0.0).
        "0.0",    // double
        "-4.2",   // negative double
        "4.2",    // positive double
        "-inf",   // double pseudo-literal. Tests the -INFINITY value
        "+inf",   // double pseudo-literal. Tests the INFINITY value.
        "nan",    // double pseudo-literal. Tests the Not a Number value. NAN is sometthing that is not a number, like 0.0/0.0 or sqrt(-1.0) or log(-1.0) or log10(0.0) or log(0.0) or log2(0.0) or log1p(-1.0) or log1p(0.0) or log2(0.0) or log10(0.0).
        "not_a_literal", // invalid input
        "999999999999999999999999", // int overflow
        "'\\n'",  // non-displayable char (should not be used, but for testing)
        "127",    // char displayable limit
        "128",    // above char limit
        "-1",     // below char limit
    };

    size_t n = sizeof(tests) / sizeof(tests[0]);
    for (size_t i = 0; i < n; ++i) 
    {
        std::cout << "Test: " << tests[i] << std::endl;
        ScalarConverter::convert(tests[i]);
        std::cout << "------------------------" << std::endl;
    }
    return 0;
} */

int main(int argc, char **argv) 
{
    if (argc != 2) 
    {
        std::cout << "Usage: ./convert <literal>" << std::endl;
        return 1;
    }
    ScalarConverter::convert(argv[1]);
    return 0;
} 
