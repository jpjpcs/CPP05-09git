/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaosilva <joaosilva@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 11:10:05 by joaosilva         #+#    #+#             */
/*   Updated: 2025/06/27 11:10:54 by joaosilva        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <string>
#include "iter.hpp"

/*
The goal of this exercise is to create a template function iter that applies a function to each element of an array.

1 - This will give an error:
        iter: Applies the function f to each element of the array.
        template <typename T>
        void iter(T* array, int length, void (*f)(T const &))
        {
            for (int i = 0; i < length; ++i)
                f(array[i]);
        }
        because of this: ::iter(arr, 5, setTo42); and        ::iter(arr, 5, print);
        The error occurs because the function prototype expects a pointer to T (T* array),
        but you are passing an array (arr) which decays to a pointer, but the C++98 compiler
        does not deduce the size of the array correctly when using function templates as parameters.
        The error message will likely be something like:
        "error: no matching function for call to 'iter(int [5], int, void (&)(int&))'"
        This is because the compiler cannot deduce the type of the array correctly when passing it
        as a function argument.

    Why does this happen?
    When you write print, the compiler sees a template, not a function pointer.
    When you write print<int>, you are giving the compiler a real function pointer of the correct type.

    How to correct it?
        The error occurs because your original iter prototype expects a pointer (T* array), 
        but you are passing an array. In C++, arrays can decay to pointers, but this is not 
        always deduced correctly by the C++98 compiler, especially when using function templates as parameters.

        Solution:
        Change the prototype to accept an array by reference with a fixed size, like this:
            #ifndef ITER_HPP
            #define ITER_HPP

            // Accepts array by reference, deducing size automatically
            template <typename T, typename F, size_t N>
            void iter(T (&array)[N], size_t length, F f)
            {
                for (size_t i = 0; i < length; ++i)
                    f(array[i]);
            }

            #
2 - But the solution above will also give an error:
        Your error happens because you are passing a function template (print) 
        as the third argument, but the compiler cannot deduce the template parameter 
        for F in your iter function.
            How to fix:
                Option 1: Pass the instantiated function template
                    Explicitly instantiate print for the type you want:
                        ::iter(arr, 5, print<int>);
                        ::iter(strArr, 3, print<std::string>);
                    Change your calls to:
                        ::iter(arr, 5, print<int>);
                        ::iter(arr, 5, setTo42);
                        ::iter(arr, 5, print<int>);
                        ::iter(strArr, 3, print<std::string>);
                Option 2: Use a regular function for print
                    If you only need to print int or std::string, define a non-template function:
                        void printInt(const int &x) { std::cout << x << std::endl; }
                        void printString(const std::string &x) { std::cout << x << std::endl; }
                        ::iter(arr, 5, printInt);
                        ::iter(strArr, 3, printString);
                Option 3: Take off the const from the function pointer as well as from print
                Change the iter function to accept a non-const function pointer:
                    template <typename T>
                    void iter(T* array, int length, void (*f)(T &))
                    {
                        for (int i = 0; i < length; ++i)
                            f(array[i]);
                    }
                    This will allow you to pass functions that modify the elements of the array.

                    and 

                    Change the print function to take a non-const reference:
                    void print(int &x) { std::cout << x << std::endl; }

                    It will also work with void setTo42(int& x) once the const was removed.

3 - What was my solution?
    Maintain the const in the function pointer and the print function and comment the setTo42 function.
*/

// Simple print function for any type
template <typename T>
void print(T const &x)
{
    std::cout << x << std::endl;
}

/* // Function to set all elements to 42 (for int arrays)
void setTo42(int& x)
{
    x = 42;
}  */

int main()
{
    int arr[5] = {0, 1, 2, 3, 4};
    ::iter(arr, 5, print); // Should print 0 1 2 3 4

    //::iter(arr, 5, setTo42);
    // ::iter(arr, 5, print); // Should print 42 42 42 42 42

    std::string strArr[3] = {"hello", "world", "42"};
    ::iter(strArr, 3, print); // Should print hello world 42

    return 0;
}
