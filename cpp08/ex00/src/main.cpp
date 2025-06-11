/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaosilva <joaosilva@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 11:51:32 by joaosilva         #+#    #+#             */
/*   Updated: 2025/06/05 14:49:16 by joaosilva        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <vector>
#include <list>
#include "easyfind.hpp"

/*
ex00 (Easy find):
The goal is to write a function template easyfind that searches for an integer 
in any STL container (like std::vector, std::list, etc.) using STL algorithms. 
If the value is found, it returns an iterator to it; if not, it throws an exception 
or returns an error value. This exercise is about using STL algorithms and templates.

ex01 (Span):
The goal is to implement a Span class that can store up to N integers and provides 
methods to add numbers, find the shortest span (smallest difference between any two numbers), 
and the longest span (largest difference). You must also implement a way to add
multiple numbers at once using a range of iterators. The exercise focuses on using 
STL containers, algorithms, and canonical class form.

ex02 (MutantStack):
The goal is to create a MutantStack class that inherits from std::stack and adds 
iterator support, making it possible to iterate through the stack like other STL containers. 
This exercise is about extending STL containers and working with iterators and templates.

1 - Which means std::vector<int> v;
and the int in std::vector<int> v;
?
    std::vector<int> v; means:
        . You are declaring a variable v of type std::vector<int>.
        . std::vector is a dynamic array (from the C++ Standard Library).
        . The <int> part means this vector will store elements of type int (integers).
        . So, v is an empty vector that can store integers.
        Summary:
            - std::vector<int> = a vector (dynamic array) of integers
            - v = the name of your vector variable
            - int = the type of elements stored in the vector (in this case, integers)
2 - What is the difference between
std::vector<int> v;
and
std::vector<int> v(5);
and which is more correct?
    . std::vector<int> v;
        Creates an empty vector (size 0). No memory is allocated
         for elements until you add them (e.g., with push_back).
    . std::vector<int> v(5);
        Creates a vector with 5 elements, all initialized to 0 
        (the default value for int). Memory for 5 elements is allocated immediately.

    - Which is more correct?
        For your code, where you use push_back to add elements,
        std::vector<int> v; is more correct.
        If you use std::vector<int> v(5);, you will have 5 zeros in the 
        vector before you add your own values, which is not what you want.
3 - Shouldn't we have initialized all the container, for memory reasons?
    No, you don't need to pre-initialize the vector.

    Vectors manage memory automatically and efficiently.
    When you use push_back, the vector grows as needed.
    Pre-initializing with std::vector<int> v(5); only makes sense if you want 
    5 elements already in the vector, which is not your case.
    There is no memory leak or performance problem with starting empty and using push_back.
    Summary:

    Use std::vector<int> v; and fill it as needed.
    Only pre-initialize if you really want a fixed number of default elements.
4 - What´s the difference between std::vector<int>::const_iterator it and
std::vector<int>::iterator it
and in what situations should we use one or the other?
For example: why we use typename T::iterator it = std::find(container.begin(), container.end(), value); in the template <typename T>
typename T::iterator easyfind(T& container, int value) and then use std::vector<int>::const_iterator it in the main?
    Difference:
        . std::vector<int>::iterator
            - This is a mutable iterator.
            - You can use it to read and modify elements in the vector.
        . std::vector<int>::const_iterator
            - This is a read-only iterator.
            - You can use it to read elements, but cannot modify the elements it points to.
    When to use each:
        . Use iterator when you need to change the elements in the container.
        . Use const_iterator when you only need to read the elements, or when the container itself is const.
    In your code:
        . In easyfind(T& container, int value), you use typename T::iterator because you might want to allow the caller to modify the found element.
        . In easyfind(const T& container, int value), you use typename T::const_iterator because the container is const and you cannot modify its elements.
    In main:
        . If your container is not const, you can use either, but if you only need to read, const_iterator is safer and clearer.
        . If your container is const, you must use const_iterator.
    Summary:
        - Use iterator for non-const containers when you might modify elements.
        - Use const_iterator for const containers or when you only need to read.
*/

int main()
{
    // Testing with a vector
    std::cout << std::endl;
    std::cout << "Testing with a vector:" << std::endl;
    std::vector<int> v; 
    for (int i = 0; i <= 5; ++i)
        v.push_back(i * 2);
    std::cout << "Vector elements: ";
    for (std::vector<int>::const_iterator it = v.begin(); it != v.end(); ++it)
        std::cout << *it << " ";
    std::cout << std::endl;

    try {
        std::vector<int>::iterator it = easyfind(v, 4);
        std::cout << "Found in vector: " << *it << std::endl;
    } catch (std::exception& e) {
        std::cout << "Not found in vector: " << e.what() << std::endl;
    }

    try {
        easyfind(v, 7);
    } catch (std::exception& e) {
        std::cout << "Not found in vector: " << e.what() << std::endl;
    }

    // Testing with a list
    std::cout << std::endl;
    std::cout << "Testing with a list:" << std::endl;
    std::list<int> l;
    for (int i = 10; i < 20; ++i)
        l.push_back(i);
    std::cout << "List elements: ";
    for (std::list<int>::const_iterator it = l.begin(); it != l.end(); ++it)
        std::cout << *it << " ";
    std::cout << std::endl;
    

    try {
        std::list<int>::iterator it = easyfind(l, 15);
        std::cout << "Found in list: " << *it << std::endl;
    } catch (std::exception& e) {
        std::cout << "Not found in list: " << e.what() << std::endl;
    }
    try {
        easyfind(l, 25);
    } catch (std::exception& e) {
        std::cout << "Not found in list: " << e.what() << std::endl;
    }
    std::cout << std::endl;
    
    return 0;
}
