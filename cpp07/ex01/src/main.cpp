/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jode-jes <jode-jes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 11:10:05 by joaosilva         #+#    #+#             */
/*   Updated: 2025/07/02 12:44:28 by jode-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <string>
#include "iter.hpp"

/*
The goal of this exercise is to create a template function iter that applies a function to each element of an array, 
receiving as a third paramenter a function that could be const or non-const.

1 - Possible solutions: Use of 2 functions (one to const and one to non-const callables) - OVERLOADING or use of one GENERIC solution.
 
    1.1. WHY OVERLOADING (Use of 2 functions to const and non-const calls) is better vs GENERIC TEMPLATE?
 
        * Overload solution:
        
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
                
        * Generic template solution:
            template <typename T, typename Function>
            void iter(T* array, int length, Function f)
            {
                for (int i = 0; i < length; ++i)
                    f(array[i]);
            }
        
        1.1.2. - Function Overloading is superior because:
            . it allows the compiler to automatically deduce the correct function signature based on the type of the callable passed
            . Ie, Generic function works for both cases (const and non-const) but it requires explicit instantiation of the function type, which is not user-friendly. So, if we use generic template, we have to do this:
                Use of GENERIC FUNCTION...We must use EXPLICIT INSTANTIATION (works with both approaches):
                    iter(arr, 5, print<int>);    // print<int> = concrete function
            . So, if we tell to the compiler which type we want to use, it works fine with the generic template. 
            But if we don't do it, it will give a compile error: 
                src/main.cpp:142:5: error: no matching function for call to 'iter'
                ::iter(arr, 5, print);
            ^~~~~~
            include/iter.hpp:19:6: note: candidate template ignored: couldn't infer template argument 'Function'
            void iter(T* array, int length, Function f)

        1.1.3. - Other and better solution is to use the OVERLOAD SOLUTION (2 functions instead of 1) ... which allows AUTOMATIC DEDUCTION (only works with overloading). 
            1.1.3.1. Why its better? Because we don't have to tell the compiler which type we want to use, he deduces it automatically in the context if he should use the const or non-const version of the function.
                iter(arr, 5, print);         // compiler deduces print<int> from context
                . With overloading: The compiler sees 'arr' is int[], looks at available iter overloads, and automatically deduces 
                that 'print' should become 'print<int>'.
                . With generic template: The compiler cannot deduce what 'Function' type should be from just 'print' (a template), so deduction fails.
                . This is why overloading provides better user experience and flexibility.
 
1.2 - How it works with the compiler?
    Case 1: ::iter(arr, 5, print<int>) - Explicit Instantiation
        . What happens:
            1. print<int> is a concrete function with signature void(*)(const int&)
            2. Compiler sees: int arr[] → T = int
            3. Compiler matches void(*)(const int&) with the const overload
            4. ✅ Success: Uses iter(T* array, int length, void (*f)(T const &))
    Case 2: ::iter(arr, 5, print) - Template Argument Deduction
        . What happens:
            1. print is a function template, not a concrete function yet
            2. Compiler sees: int arr[] → T = int
            3. Compiler knows it needs either:
                - void(*)(int const &) for the const overload
                - void(*)(int &) for the non-const overload
            4. Key insight: Compiler can instantiate print as print<int> because:
                - It knows the target type must be int (from the array)
                - It has specific function signatures to match against
            5. Compiler creates print<int> with signature void(*)(const int&)
            6. ✅ Success: Matches const overload and uses iter(T* array, int length, void (*f)(T const &))
        . Why This Works: The Magic of Overload Resolution
            - The compiler's step-by-step process:
                ::iter(arr, 5, print);  // What the compiler does:
            1. Array Analysis: arr is int[5] → T* = int*
            2. Overload Candidate Search: Find all iter functions that could work:
                - iter(int*, int, void(*)(int const &)) ← const version
                - iter(int*, int, void(*)(int &)) ← non-const version
            3. Template Argument Deduction for print:
                - "I need a function that takes int as parameter"
                - "I have print<T> template, let me try print<int>"
                - "Does print<int> match any of my candidates?"
            4. Signature Matching:
                - print<int> creates: void print(const int& x)
                - Function pointer type: void(*)(const int&)
                - ✅ Matches: iter(int*, int, void(*)(int const &))
            5. Final Selection: Choose const overload
        . Why Generic Template Fails
            - With generic template:
                template <typename T, typename Function>
                void iter(T* array, int length, Function f)
    . The problem:
        1. T can be deduced as int from arr
        2. But Function cannot be deduced from print alone
        3. print could be instantiated as print<int>, print<string>, etc.
        4. ❌ Failure: Compiler cannot guess which instantiation you want

. Summary
    - Overloaded functions work because:
        . They provide specific target signatures for the compiler to match against
        . The compiler can deduce the correct template instantiation based on these concrete targets
        . Template argument deduction has enough information to resolve ambiguity
    - Generic template fails because:
        . It has no specific target signature to guide template instantiation
        . The compiler cannot guess which template parameters to use
        . Template argument deduction lacks sufficient information
        . This is why overloaded functions provide superior usability - they enable both explicit instantiation and automatic type deduction!
 
2 - SYNTAX DIFFERENCES: CONSTRUCTOR vs ARRAY INITIALIZATION
    * =======================================================
    * 
    * Why Array<int> a(5) uses parentheses () and int arr[5] = {0,1,2,3,4} uses braces {}?
    * 
    * DETAILED COMPARISON:
    * ===================
    * 
    * Aspect               | Array<int> a(5)           | int arr[5] = {0,1,2,3,4}
    * ---------------------|---------------------------|---------------------------
    * Type                 | Template class object     | C-style array
    * Syntax               | Constructor call ()       | Initialization list {}
    * Size                 | Dynamic (runtime)         | Fixed (compile-time)
    * Meaning              | "Create Array with 5 elements" | "Create array with these values"
    * Memory               | Heap (dynamic)            | Stack (automatic)
    * Initialization       | Default (zeros)           | Explicit values
    * 
    * 
    * OTHER EXAMPLES:
    * ==============
    * 
    * Constructor Calls (always use parentheses):
    *     Array<int> a(10);           // 10 elements
    *     Array<std::string> s(3);    // 3 empty strings
    *     std::string str("hello");   // string with "hello"
    * 
    * Array Initialization (always use braces):
    *     int arr[] = {1, 2, 3};           // Size deduced
    *     double values[3] = {1.5, 2.5};   // Last element = 0.0
    *     char letters[] = {'a', 'b', 'c'};
    * 
    * 
    * WHY THIS DIFFERENCE EXISTS:
    * ==========================
    * 
    * Language History:
    * - C-style arrays exist since C (1970s)
    *   {} was the original syntax for initialization
    * 
    * - C++ classes introduced later (1980s)
    *   () for calling object constructors
    * 
    * Specific Syntax:
    * - () = "Call a function/constructor"
    * - {} = "List of values for initialization"
    * 
    * 
    * SIMPLE SUMMARY:
    * ==============
    * 
    * // OBJECT - uses PARENTHESES for constructor
    * Array<int> a(5);          // "Construct Array with size 5"
    * 
    * // ARRAY - uses BRACES for values
    * int arr[5] = {1,2,3,4,5}; // "Array with these values"
    * 
    * The difference is conceptual: one is object creation (constructor),
    * the other is direct array initialization!
 */ 


// Only works for const
template <typename T>
void print(T const &x)
// void print(T &x)
{
    std::cout << x << std::endl;
}

// Function to set all elements to 42 (for int arrays)
void setTo42(int& x)
{
    x = 42;
} 

// only works with non-const
void increment(int& x)
{
    x++;
}

int main()
{
    std::cout  << std::endl;
    int arr[5] = {0, 1, 2, 3, 4};
    std::cout << "Array created: ";
    for (int i = 0; i < 5; ++i)
        std::cout << arr[i] << " ";
    std::cout << std::endl << std::endl;
    
    std::cout << "Test 1 - Printf const" << std::endl;
    ::iter(arr, 5, print<int>); // Should print 0 1 2 3 4
    std::cout << std::endl;
    
    std::cout << "Test 2 - Set to 42 non-const and iter printed with const" << std::endl;
    ::iter(arr, 5, setTo42);
    ::iter(arr, 5, print<int>); // Should print 42 42 42 42 42
    std::cout << std::endl;
    
    std::cout << "Test 3 - Increment non-const and iter printed with const)" << std::endl;
    ::iter(arr, 3, increment);
    std::cout << "... increment done with 3" << std::endl;
    ::iter(arr, 5, print<int>);
    std::cout << std::endl;
    
    std::cout << "Test 4 - String array iter with const print" << std::endl;
    std::string strArr[3] = {"hello", "world", "42"};
    ::iter(strArr, 3, print<std::string>); // Should print hello world 42
    std::cout << std::endl;
    
    std::cout << "All tests done!" << std::endl;

    std::cout << std::endl;

    return 0;
}



