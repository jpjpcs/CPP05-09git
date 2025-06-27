/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   easyfind.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaosilva <joaosilva@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 11:51:20 by joaosilva         #+#    #+#             */
/*   Updated: 2025/06/27 11:12:42 by joaosilva        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
What is the purpose of the easyfind function and this exercise?
    The easyfind function is designed to search for a specific value in a container 
    (like std::vector or std::list) and return an iterator to that value if found. 
    If the value is not found, it throws an exception (std::runtime_error or std::out_of_range).
    It simplifies the process of searching for a value in a container by encapsulating 
    the logic in a single function.
1 - Accordingy with the subject and the rules, can I use std::out_of_range?
    Yes, you can use std::out_of_range in your easyfind implementation 
    according to the subject and rules.
    The subject says you can throw an exception of your choice if 
    the value is not found.
    std::out_of_range is a standard exception used by STL containers 
    (like vector::at()) when an element is not found or is out of bounds.
    It is included in <stdexcept>, which is allowed.
    There are no restrictions in the subject or rules against using std::out_of_range.
    Conclusion:
        Using throw std::out_of_range("Value not found"); is correct, 
        standard, and even slightly more precise than std::runtime_error for this case. 
        Both are accepted, but std::out_of_range is a good STL-style choice.
2 - Difference between std::runtime_error and std::out_of_range:
    std::runtime_error is a general-purpose exception for runtime errors.
    std::out_of_range is a specific exception for cases where an index or key is out of bounds.
    In this case, since we are looking for a value in a container, 
    std::out_of_range is more appropriate as it indicates the value was not found 
    within the valid range of the container.
3 - Difference between std::runtime_error and std::invalid_argument:
    std::runtime_error is a general-purpose exception for runtime errors.
    std::invalid_argument is used when an argument passed to a function is invalid.
    In this case, since we are not passing an invalid argument but rather 
    indicating that a value was not found in the container, std::runtime_error 
    or std::out_of_range would be more appropriate.
4 - Difference between std::runtime_error and std::distance:
    std::runtime_error is an exception type used to indicate runtime errors.
    std::distance is a function that calculates the distance between two iterators.
    std::distance(begin, it) gives you the index of it).
    Use std::distance if you want to know the position/index of an iterator in a container.
    They serve different purposes: std::runtime_error is for error handling, 
    while std::distance is for iterator arithmetic.
    Resume:
        Best practice here:
            std::runtime_error is perfectly acceptable and generic.
            std::invalid_argument is less appropriate, because the argument 
            is not invalid—the value just wasn't found.
            std::distance is not an exception; it's a function to calculate the distance
            between two iterators, which is not relevant for this context.
            std::out_of_range is more specific and idiomatic for this case,
            as it indicates that the value was not found within the valid range of the container.
            However, std::runtime_error is also fine and idiomatic for this context.
            So, you can use either std::runtime_error or std::out_of_range.
            If you want to be even more precise, you could use std::out_of_range, 
            but std::runtime_error is totally fine and idiomatic for this context.\
5 - What are STL containers?
    STL (Standard Template Library) containers are data structures provided by C++ 
    to store collections of objects. They include:
    - std::vector: A dynamic array that can grow and shrink in size.
    - std::list: A doubly linked list that allows for efficient insertions and deletions.
    - std::deque: A double-ended queue that allows fast insertions and deletions at both ends.
    - std::set: A collection of unique elements, sorted by default.
    - std::map: A collection of key-value pairs, where keys are unique and sorted.
    - std::unordered_set: A collection of unique elements, not sorted, but allows fast access.
    - std::unordered_map: A collection of key-value pairs, not sorted, but allows fast access.
6 - Advantages of using STL containers:
    - They provide a wide range of data structures that are optimized for performance.
    - They handle memory management automatically, reducing the risk of memory leaks.
    - They offer a consistent interface and algorithms for manipulating data.
    - They are part of the C++ standard library, making them portable and widely used.
7 - What is the difference between option A, B, and C?
    Option A
        template <typename T>
        typename T::iterator easyfind(T& container, int value)
    Option B
        template <typename T>
        int easyfind(T container, int value)
    Option C
        template <class T>
        int easyfind(T& type, int target)

    Option A:
        - Returns an iterator to the found element.
        - Accepts the container by reference (no copy).
        - Follows STL conventions (like std::find).
        - Allows modifying the found element.
    
    Option B:
        - Returns an integer (not an iterator)(probably index or -1)..
        - Accepts the container by value (creates a copy, inefficient).
        - Not idiomatic for STL containers. Does not follow STL conventions.
        - Cannot modify the original container. Not flexible for all container types.
    Option C:
        - Returns an integer (not an iterator)(probably index or -1).
        - Accepts the container by reference (no copy).
        - Uses a generic type name (T), but does not follow STL conventions.
        - Cannot modify the original container. Not flexible for all container types.
            Not as flexible as returning an iterator.        
What should we use: 
    Option A is the best choice for the easyfind function. 
    It is the most idiomatic and flexible option for working with STL containers.
    Also because:
    - Using typename T::iterator allows us to return an iterator to the found value, 
      which is more flexible and allows for further operations on the container.
    - It allows us to work with any container type that supports iterators,
        not just those that can be indexed by integers.
    - It provides better type safety and avoids unnecessary copying of the container.
8 -  In option A, to return the container's iterator, must it be defined as typename T::iterator?
    Yes, in option A, to return the container's iterator, it must be defined as typename T::iterator.
    This is because T is a template type that represents the container, and typename T::iterator 
    specifies the type of iterator associated with that container.
    It allows the function to return an iterator to the found element in the container.
    This is necessary for the function to work with any STL container type that supports iterators.
    Resuming, When using templates, you must write typename T::iterator to tell the compiler that iterator is a type defined inside T.
    This is required by C++ syntax.
9 - How does the find function work? For example here:
    typename T::iterator it = std::find(container.begin(), container.end(), value);
        - std::find searches from container.begin() to container.end() for the first occurrence of value.
        - If found, it returns an iterator pointing to the element.
        - If not found, it returns container.end().
10 - What means "Follows STL conventions (like std::find)"?
    "Follows STL conventions (like std::find)" means:

    - Your function behaves in the same way as standard STL (Standard Template Library) functions, such as std::find.
    - Specifically:
        . It takes iterators or containers as parameters.
        . It returns an iterator to the found element, or end() if not found.
        . It does not return an index or a boolean, but an iterator (which is the standard way in STL).
        .   It allows the user to use the result in the same way as other STL algorithms.
    Example:
        std::find returns an iterator, not an index.
        Your easyfind does the same, so it "follows STL conventions."
11 - Can I use both (const and non-const)? Is it asked in the subject and is it right?
    Yes, you can use both const and non-const versions of the easyfind function.
    The subject does not explicitly ask for both, but it is a good practice to provide 
    both versions to allow searching in both mutable and immutable containers.
    It is right to implement both versions, as it increases the flexibility of the function.
    The const version allows searching in const containers, while the non-const version allows modifying the container.
*/

#ifndef EASYFIND_HPP
#define EASYFIND_HPP

#include <algorithm>
#include <stdexcept>

template <typename T>
typename T::iterator easyfind(T& container, int value)
{   
    // Declare an iterator and use std::find to search for 'value' in the container
    typename T::iterator it = std::find(container.begin(), container.end(), value);
    // If the value is not found, throw an exception
    if (it == container.end())
        throw std::runtime_error("Value not found");
    // Return the iterator to the found value
    return it;
}

template <typename T>
typename T::const_iterator easyfind(const T& container, int value)
{
    typename T::const_iterator it = std::find(container.begin(), container.end(), value);
    if (it == container.end())
        throw std::runtime_error("Value not found");
    return it;
}

#endif
