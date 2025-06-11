/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScalarConverter.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaosilva <joaosilva@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 11:12:11 by joaosilva         #+#    #+#             */
/*   Updated: 2025/05/29 20:12:24 by joaosilva        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ScalarConverter.hpp"
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <climits>
#include <cfloat>
#include <cerrno>
#include <cmath>
/*
1 - The functions isChar, isInt, isFloat, and isDouble should be declared in the .hpp file or not?

    No, these functions (isChar, isInt, isFloat, isDouble) should not be declared in the .hpp file.

    They are internal helper functions used only inside the implementation file (.cpp).
    Only the public interface (convert) and the canonical form constructors/destructor/operators should be declared in the header.

    Declaring these helpers in the header would unnecessarily expose them and pollute the class interface.
    Your current header is correct and follows the subject's requirements.

2 - What is a double literal in C++? What is the difference between a double and an int? What are the main differences between them? What is a float? What is a double? What is an int? What is the difference between them?
   - A double literal is a value written in code that represents a double type in C++. 
     Examples: 0.0, -4.2, 3.14, 42.0. Double literals always have a decimal point and do not use the f suffix (which is for float).

    - nan, +inf, and -inf are called special floating-point values or pseudo-literals.
        nan stands for "Not a Number" (e.g., the result of 0.0/0.0)
        +inf and -inf represent positive and negative infinity (e.g., the result of 1.0/0.0 or -1.0/0.0)
        They are part of the IEEE 754 floating-point standard, which C++ uses for float and double. Even though they are not regular numbers, they are valid values for the double type and can be written as literals in C++ code.

    - A double is a floating-point type in C++ that can represent real numbers (numbers with decimals), both positive and negative, as well as special values like infinity and NaN.
        A double is a floating-point type (not fixed-point). It uses scientific notation internally and can represent very large or very small numbers with a certain precision.

    - An int is an integer type that can only represent whole numbers (without decimals), both positive and negative.

    Main differences:

    double can store fractional (decimal) values; int cannot.
    double has a much larger range and can represent very small or very large numbers, but with limited precision.
    double supports special values like nan and inf; int does not.

3 - Functions such as std::strtol, std::strtof, and std::strtod are used to convert C-strings to numeric types. What do they do? How do they work? What are the differences between them?

    - std::strtol
        Converts a C-string (const char*) to a long int.
        Example: long value = std::strtol("123", NULL, 10); // value == 123

    - std::strtof
        Converts a C-string (const char*) to a float.
        Example: float value = std::strtof("3.14", NULL); // value == 3.14f

    - std::strtod
        Converts a C-string (const char*) to a double.
        Example: double value = std::strtod("2.718", NULL); // value == 2.718

    Those functions corretly handle both positive and negative numbers, as well as special values like NaN and infinity. 
    The functions std::strtof and std::strtod automatically parse numbers with a leading + or - sign, as well as numbers without any sign.
    For example, all of these will be correctly recognized as valid floats/doubles:
    "4.2f", "-4.2f", "+4.2f"
    "4.2", "-4.2", "+4.2"
    The check for special pseudo-literals (-inff, +inff, nanf, -inf, +inf, nan) also covers both positive and negative infinity.

    They also set the end pointer to the first character after the number, allowing you to check if the entire string was consumed during conversion.
    Consumed means that the function successfully parsed the entire string as a valid number and have validated the conversion.
*/  

ScalarConverter::ScalarConverter() {std::cout << "ScalarConverter default constructor called" << std::endl; }
ScalarConverter::ScalarConverter(const ScalarConverter &src) 
{
    std::cout << "ScalarConverter copy constructor called" << std::endl;
    (void)src; // Avoid unused parameter warning 
}

ScalarConverter &ScalarConverter::operator=(const ScalarConverter &src) 
{ 
    std::cout << "ScalarConverter assignment operator called" << std::endl;
    (void)src; // Avoid unused parameter warning
    return *this;
}

ScalarConverter::~ScalarConverter() {std::cout << "ScalarConverter destructor called" << std::endl; }

static bool isChar(const std::string &s) 
{
    return (s.length() == 3 && s[0] == '\'' && s[2] == '\'');
}

static bool isInt(const std::string &s) 
{
    char *end;
    errno = 0; // Reset errno to 0 before conversion. Why? Because if the conversion fails, errno will be set to ERANGE, which indicates an overflow or underflow condition.
    long val = std::strtol(s.c_str(), &end, 10); // Convert string to long int
    return *end == '\0' && errno != ERANGE && val >= INT_MIN && val <= INT_MAX; // Check if the entire string was consumed and within int range
}
/*
1 - first it checks if the string is one of the special float values: "-inff", "+inff", or "nanf". If it is, it returns true.
2 - If not, it uses std::strtof to attempt to convert the string to a float.
3 - It checks if the end pointer points to 'f' and the next character is '\0', indicating a valid float literal.
4 - It also checks if errno is not set to ERANGE, which would indicate an overflow or underflow condition.
5 - If all these conditions are met, it returns true, indicating the string is a valid float literal.
*/
static bool isFloat(const std::string &s) 
{
    if (s == "-inff" || s == "+inff" || s == "nanf") // NAN is sometthing that is not a number, like 0.0/0.0 or sqrt(-1.0) or log(-1.0) or log10(0.0) or log(0.0) or log2(0.0) or log1p(-1.0) or log1p(0.0) or log2(0.0) or log10(0.0).
        return true;
    char *end;
    errno = 0;
    std::strtof(s.c_str(), &end);
    return *end == 'f' && *(end + 1) == '\0' && errno != ERANGE;
}

/*
1 - first it checks if the string is one of the special double values: "-inf", "+inf", or "nan". If it is, it returns true.
2 - If not, it uses std::strtod to attempt to convert the string to a double.
3 - It checks if the end pointer points to '\0', indicating a valid double literal.
4 - It also checks if errno is not set to ERANGE, which would indicate an overflow or underflow condition.
5 - If all these conditions are met, it returns true, indicating the string is a valid double literal.
*/
static bool isDouble(const std::string &s) 
{
    if (s == "-inf" || s == "+inf" || s == "nan") // NAN is sometthing that is not a number, like 0.0/0.0 or sqrt(-1.0) or log(-1.0) or log10(0.0) or log(0.0) or log2(0.0) or log1p(-1.0) or log1p(0.0) or log2(0.0) or log10(0.0).
        return true;
    char *end;
    errno = 0;
    std::strtod(s.c_str(), &end);
    return *end == '\0' && errno != ERANGE;
}

void ScalarConverter::convert(const std::string &literal)
{
    std::cout << std::fixed << std::setprecision(1); // Set precision for float and double output. What this does? It sets the number of digits after the decimal point to 1 for float and double outputs.

    // CHAR
    if (isChar(literal)) 
    {
        char c = literal[1];
        std::cout << "char: '" << c << "'" << std::endl;
        std::cout << "int: " << static_cast<int>(c) << std::endl;
        std::cout << "float: " << static_cast<float>(c) << "f" << std::endl;
        std::cout << "double: " << static_cast<double>(c) << std::endl;
        return;
    }

    // FLOAT
    if (isFloat(literal)) 
    {
        float f;
        if (literal == "-inff") f = -INFINITY; // -INFINITY is a special value representing negative infinity in floating-point arithmetic. Are defined in the cmath library and it can be used in C++98.
        else if (literal == "+inff") f = INFINITY; // INFINITY is a special value representing positive infinity in floating-point arithmetic. Are defined in the cmath library and it can be used in C++98.
        else if (literal == "nanf") f = NAN; // NAN is a special value representing "Not a Number" in floating-point arithmetic. Are defined in the cmath library and it can be used in C++98.
        else f = std::strtof(literal.c_str(), NULL);

        // char
        if (f < 0 || f > 127 || std::isnan(f))
            std::cout << "char: impossible" << std::endl;
        else if (!std::isprint(static_cast<int>(f))) // in the asccii table, the printable characters are from 32 to 126.
            std::cout << "char: Non displayable" << std::endl;
        else
            std::cout << "char: '" << static_cast<char>(f) << "'" << std::endl;

        // int
        if (f < static_cast<float>(INT_MIN) || f > static_cast<float>(INT_MAX) || std::isnan(f)) // INT_MIN and INT_MAX are defined in the climits library and it can be used in C++98.
            std::cout << "int: impossible" << std::endl;
        else
            std::cout << "int: " << static_cast<int>(f) << std::endl;

        // float
        if (literal == "-inff" || literal == "+inff" || literal == "nanf")
            std::cout << "float: " << literal << std::endl;
        else
            std::cout << "float: " << f << "f" << std::endl;

        // double
        if (literal == "-inff")
            std::cout << "double: -inf" << std::endl;
        else if (literal == "+inff")
            std::cout << "double: +inf" << std::endl;
        else if (literal == "nanf")
            std::cout << "double: nan" << std::endl;
        else
            std::cout << "double: " << static_cast<double>(f) << std::endl;
        return;
    }

    // DOUBLE
    if (isDouble(literal))
    {
        double d;
        if (literal == "-inf") d = -INFINITY;
        else if (literal == "+inf") d = INFINITY;
        else if (literal == "nan") d = NAN; 
        else d = std::strtod(literal.c_str(), NULL);

        // char
        if (d < 0 || d > 127 || std::isnan(d))
            std::cout << "char: impossible" << std::endl;
        else if (!std::isprint(static_cast<int>(d)))
            std::cout << "char: Non displayable" << std::endl;
        else
            std::cout << "char: '" << static_cast<char>(d) << "'" << std::endl;

        // int
        if (d < static_cast<double>(INT_MIN) || d > static_cast<double>(INT_MAX) || std::isnan(d))
            std::cout << "int: impossible" << std::endl;
        else
            std::cout << "int: " << static_cast<int>(d) << std::endl;

        // float
        if (literal == "-inf")
            std::cout << "float: -inff" << std::endl;
        else if (literal == "+inf")
            std::cout << "float: +inff" << std::endl;
        else if (literal == "nan")
            std::cout << "float: nanf" << std::endl;
        else
            std::cout << "float: " << static_cast<float>(d) << "f" << std::endl;

        // double
        if (literal == "-inf" || literal == "+inf" || literal == "nan")
            std::cout << "double: " << literal << std::endl;
        else
            std::cout << "double: " << d << std::endl;
        return;
    }

    // INT
    if (isInt(literal)) 
    {
        // Convert the string to a long int
        // Why long? Because long can hold larger values than int, and we need to ensure we don't overflow when converting from string to int.
        long l = std::strtol(literal.c_str(), NULL, 10); // why 10? // Because we are converting a decimal number, so the base is 10. NULL because // we don't need to check the end pointer in this case.

        // char
        if (l < 0 || l > 127)
            std::cout << "char: impossible" << std::endl;
        else if (!std::isprint(static_cast<int>(l)))
            std::cout << "char: Non displayable" << std::endl;
        else
            std::cout << "char: '" << static_cast<char>(l) << "'" << std::endl;

        // int
        std::cout << "int: " << l << std::endl;

        // float
        std::cout << "float: " << static_cast<float>(l) << "f" << std::endl;

        // double
        std::cout << "double: " << static_cast<double>(l) << std::endl;
        return;
    }

    // Not recognized
    std::cout << "char: impossible" << std::endl;
    std::cout << "int: impossible" << std::endl;
    std::cout << "float: impossible" << std::endl;
    std::cout << "double: impossible" << std::endl;
}
