/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaosilva <joaosilva@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 12:11:42 by joaosilva         #+#    #+#             */
/*   Updated: 2025/06/02 17:58:59 by joaosilva        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <string>
#include "Array.hpp"

/*
Goal of this exercise: 
Create a template class Array that represents a dynamic array.

1 - template <typename T> means that you are defining a template.
        It tells the compiler that the class (or function) that follows will 
        work with any type T that the user specifies.
        T is a placeholder for a type (like int, double, std::string, etc).
        When you create an Array<int>, T becomes int.
        When you create an Array<std::string>std::string, T becomes std::string.
    In summary:
         <typename T> allows your class or function to be generic and work with any data type.
 - Elements of type T are the items stored inside your Array class, 
    where T is the template parameter (the type you choose when you create an Array).
    For example, if you write Array<int> a;, then the elements are of type int.
    If you write Array<std::string> s;std::string s;, then the elements are of type std::string.
    Where are they in your code?
    They are stored in the private member:
        T* _data; // Pointer to the array data
    This pointer points to the dynamically allocated memory where the elements of type T are stored.
    This pointer points to a dynamically allocated array of elements of type T.
    When you create an Array<int>, _data points to an array of int.
    When you create an Array<std::string>std::string, _data points to an array of std::string.
    You access these elements using the subscript operator:
    T& operator[](std::size_t idx)
    {
        // ...
        return _data[idx];
    }
    and 
    const T& operator[](std::size_t idx) const
    {
        // ...
        return _data[idx];
    }
    Summary:
        The "elements of type T" are the objects stored in the memory pointed to by _data.
        They are created with new T[n]()n in the constructor and accessed with operator[].
2 - Is it required by the subject to use an initializer list in the default constructor?
    No, you are not required by the subject to use an initializer list in the default constructor.
    However, using an initializer list is the correct and idiomatic way in C++ to 
    initialize member variables, especially for pointers and built-in types.
    Why use Array() : _data(NULL), _size(0) {} instead of just Array() {}?
    If you write Array() {}, the members _data and _size are not initialized (they will have indeterminate values).
    If you write Array() : _data(NULL), _size(0) {}, you guarantee that _data starts as NULL and _size as 0.
    Is it required by the subject?
    No, the subject does not require the use of an initializer list.
    The subject only requires:
    Construction with no parameter: Creates an empty array.
3. *Tip: Try to compile int * a = new int(); then display a
    What does it mean?

    This shows that in C++, when you do new int();, the value pointed to by a is zero (the default value for primitive types).
    The subject wants you to use new T[n]();n; to ensure all elements of the array are default-initialized (zero for 
    primitive types, default constructor for complex types).
    In the code:
        _data = new T[n]();
    This initializes all elements of the array.
4. "modifying either the original array or its copy after copying musn’t affect the other array."
    What does it mean?
    If you copy an array to another (by copy or assignment), changing one must not change the other.
    That is, each array must have its own memory (deep copy).
    In main.cpp, you test this:
        Array<std::string> s2(s);
        s2[1] = "Copy";
        This means that modifying s2 does not affect s, and vice versa.
5. "You MUST use the operator new[] to allocate memory. Preventive allocation (allocating memory in advance) is forbidden. 
    Your program must never access non-allocated memory"
    What does it mean?
        You must use new[] to create the dynamic array.
        You cannot allocate more memory than requested.
        You must never access memory that was not allocated.
        In the code:
            _data = new T[n]();
            And whenever the array is destroyed:
            ~Array() { delete[] _data; }
6. What is a subscript operator?
    It is the [] operator that allows you to access array elements.
    In the code:
        T& operator[](std::size_t idx)
        const T& operator[](std::size_t idx) const
7. "When accessing an element with the [ ] operator, if its index is out of bounds, an std::exception is thrown."
    If you try to access an invalid index, you must throw an exception.
    In the code:
        (idxif  >= _size)
            throw std::out_of_range("Array index out of bounds");
    In main.cpp, you test this:
        try {
            std::cout << "Accessing out of bounds: ";
            std::cout << a[100] << std::endl;
        } catch (const std::exception& e) {
            std::cout << "Caught exception: " << e.what() << std::endl;
        }
8. What is the difference between these two functions?
        // Subscript operator (read/write)
        T& operator[](std::size_t idx)
        {
            if (idx >= _size)
                throw std::out_of_range("Array index out of bounds");
            return _data[idx];
        }
        and 
        // Subscript operator (read-only for const)
        const T& operator[](std::size_t idx) const
        {
            if (idx >= _size)
                throw std::out_of_range("Array index out of bounds");
            return _data[idx];
        }
        *******************-****************
        - T& operator[](std::size_t idx)
            Returns a non-const reference to the element.
            Allows you to read and modify the element (array[i] = value;).
            Called when the Array object is not const.
        - const T& operator[](std::size_t idx) const
            Returns a const reference to the element.
            Allows you to only read the element (value = array[i];).
            Called when the Array object is const.
        * What are they for?
            They allow you to access elements of your array using the [] operator, just like a normal array.
            The first version is for reading and writing.
            The second version is for read-only access when the array is const.
        * Do we have to use both? Or is the first one enough?
            If you only implement the first one, you cannot access elements of a const Array (e.g., const Array<int> arr; arr[0]; will not compile).
            If you implement both, your class is const-correct:
                You can access elements of both const and non-const arrays.
            Best practice: Always implement both for full functionality and const-correctness.
                This is the standard in C++.
*/

int main()
{
    // Test empty 
    std::cout << std::endl;
    std::cout << "Testing empty array:" << std::endl;
    Array<int> empty;
    std::cout << "Empty array size: " << empty.size() << std::endl;
    std::cout << std::endl;
    
    // Test array of ints
    std::cout << "Testing array of integers:" << std::endl;
    Array<int> a(5);
    for (unsigned int i = 0; i < a.size(); ++i)
        a[i] = i * 10;
    std::cout << "Int array: ";
    for (unsigned int i = 0; i < a.size(); ++i)
        std::cout << a[i] << " ";
    std::cout << std::endl;
    std::cout << std::endl;

    // Test array of strings (complex type)
    std::cout << "Testing array of strings:" << std::endl;
    Array<std::string> s(3);
    s[0] = "Hello";
    s[1] = "Array";
    s[2] = "World";
    std::cout << "String array: ";
    for (unsigned int i = 0; i < s.size(); ++i)
        std::cout << s[i] << " ";
    std::cout << std::endl;
    std::cout << std::endl;
    
    // Test copy constructor
    std::cout << "Testing copy constructor:" << std::endl;
    Array<std::string> s2(s);
    s2[1] = "Copy";
    std::cout << "Original string array: ";
    for (unsigned int i = 0; i < s.size(); ++i)
        std::cout << s[i] << " ";
    std::cout << std::endl;
    std::cout << "Copied string array: ";
    for (unsigned int i = 0; i < s2.size(); ++i)
        std::cout << s2[i] << " ";
    std::cout << std::endl;
    std::cout << std::endl;

    // Test assignment operator
    std::cout << "Testing assignment operator:" << std::endl;
    Array<int> b;
    b = a;
    b[0] = 42;
    std::cout << "Original int array: ";
    for (unsigned int i = 0; i < a.size(); ++i)
        std::cout << a[i] << " ";
    std::cout << std::endl;
    std::cout << "Assigned int array: ";
    for (unsigned int i = 0; i < b.size(); ++i)
        std::cout << b[i] << " ";
    std::cout << std::endl;
    std::cout << std::endl;

    // Test out of 
    std::cout << "Testing out of bounds access:" << std::endl;
    try {
        std::cout << "Accessing out of bounds: ";
        std::cout << a[100] << std::endl;
    } catch (const std::exception& e) {
        std::cout << "Caught exception: " << e.what() << std::endl;
    }
    std::cout << std::endl;
    
    return 0;
}
