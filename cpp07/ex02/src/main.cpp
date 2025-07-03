/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jode-jes <jode-jes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 12:11:42 by joaosilva         #+#    #+#             */
/*   Updated: 2025/07/02 12:52:22 by jode-jes         ###   ########.fr       */
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
    - The template parameter name is completely arbitrary. You can use any valid identifier:
            template <typename T>
            class Array { ... . };
            
             template <typename A>
             class Array {  ...  };

            template <typename B>
            class Array {  ...  };

            template <typename MyType>
            class Array {  ...  };

            template <typename Element>
            class Array {  ...  };

            template <typename DataType>
            class Array {  ...  };
            . So, Case sensitivity matters:
                template <typename T>    // ✅ Valid
                template <typename t>    // ✅ Valid (different from T)
                template <typename A>    // ✅ Valid
                template <typename a>    // ✅ Valid (different from A)
            . Common conventions:
                - Most common:
                    - T - Generic type (most popular)
                    - U, V - Additional types when you need multiple
                    - Key, Value - For maps/pairs
                    - Element - For containers

                - Examples in practice: 
                    // Generic container
                    template <typename T>
                    class Vector { T* data; };

                    // Key-value pair
                    template <typename Key, typename Value>
                    class Map {  ...  };

                    // Multiple types
                    template <typename T, typename U, typename V>
                    class Triple { T first; U second; V third; };

                    // Descriptive names
                    template <typename ElementType>
                    class List { ElementType* head; };
                - What we need to change if you use different name:
                    If we change from T to A, you must change everywhere in the class:
                        template <typename A>  // Changed here
                        class Array
                        {
                            private:
                                A*          _data;        // Changed here
                                std::size_t _size;

                            public:
                                Array(unsigned int n) : _data(NULL), _size(n)
                                {
                                    if (n > 0)
                                        _data = new A[n]();   // Changed here
                                }

                                A& operator[](std::size_t idx)  // Changed here
                                {
                                    if (idx >= _size)
                                        throw std::out_of_range("Array index out of bounds");
                                    return _data[idx];
                                }

                                const A& operator[](std::size_t idx) const  // Changed here
                                {
                                    // ...
                                }
                        };
                -Bottom line:
                    The template parameter name is just a placeholder - it's like a variable name. 
                    Choose whatever makes your code most readable and follows your team's conventions. 
                    T is just the most common choice for "Type".

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
    . This shows that in C++, when we do new int();, the value pointed to by a is zero (the default value for primitive types).
    . The subject wants us to use new T[n]();n; to ensure all elements of the array are default-initialized (zero for 
    primitive types, default constructor for complex types).
    . In the code:
        _data = new T[n]();
    This initializes all elements of the array.
4. "modifying either the original array or its copy after copying musn’t affect the other array."
    What does it mean?
    . If you copy an array to another (by copy or assignment), changing one must not change the other.
    . That is, each array must have its own memory (deep copy).
    . In main.cpp, you test this:
        Array<std::string> s2(s);
        s2[1] = "Copy";
        This means that modifying s2 does not affect s, and vice versa.
5. "You MUST use the operator new[] to allocate memory. Preventive allocation (allocating memory in advance) is forbidden. 
    Your program must never access non-allocated memory"
    What does it mean?
        . We must use new[] to create the dynamic array.
        . We cannot allocate more memory than requested.
        . We must never access memory that was not allocated.
        . In the code:
            _data = new T[n]();
            And whenever the array is destroyed:
            ~Array() { delete[] _data; }
6. What is a subscript operator?
    . It is the [] operator that allows you to access array elements.
    . In the code:
        T& operator[](std::size_t idx)
        const T& operator[](std::size_t idx) const
7. "When accessing an element with the [ ] operator, if its index is out of bounds, an std::exception is thrown."
    . If you try to access an invalid index, you must throw an exception.
    . In the code:
        (idxif  >= _size)
            throw std::out_of_range("Array index out of bounds");
   . In main.cpp, you test this:
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

9 - MAIN GIVEN IN THE MODULE:

    #include <iostream>
    #include <Array.hpp>
    #include <cstdlib>

    #define MAX_VAL 750
    int main(int, char**)
    {
        Array<int> numbers(MAX_VAL); // Create an array of integers with size MAX_VAL
        // Fill the array with random values and create a mirror array to check values later
        int* mirror = new int[MAX_VAL]; // Create a C-style array to mirror the values
        srand(time(NULL)); // Seed the random number generator
        for (int i = 0; i < MAX_VAL; i++) // Fill the array with random values
        {
            const int value = rand(); // Generate a random value
            numbers[i] = value; // Assign the random value to the Array
            mirror[i] = value; // Store the value in the mirror array
        }
        //SCOPE
        {
            Array<int> tmp = numbers; // Create a temporary Array<int> using the assignment operator
            Array<int> test(tmp); // Create another Array<int> using the copy constructor
        }

        for (int i = 0; i < MAX_VAL; i++) // Check if the values in the mirror array match the original Array
        {
            if (mirror[i] != numbers[i])
            {
                std::cerr << "didn't save the same value!!" << std::endl;
                return 1;
            }
        }
        try // Test out of bounds access
        {
            numbers[-2] = 0; // -2 converted to size_t = a very large number, so it will throw an exception because it's out of bounds
        }
        catch(const std::exception& e) //exception will be caught here
        {
            std::cerr << e.what() << '\n';
        }
        try // Test out of bounds access at the upper limit
        // This will throw an exception because MAX_VAL is out of bounds
        // (MAX_VAL is 750, so accessing index 750 is out of bounds)
        // Why? Its out of bounds because the valid indices are 0 to 749 (MAX_VAL - 1)
        {
            numbers[MAX_VAL] = 0; // This will throw an exception because MAX_VAL is out of bounds
        }
        catch(const std::exception& e) // Catch the exception thrown by the out of bounds access
        {
            std::cerr << e.what() << '\n';
        }

        for (int i = 0; i < MAX_VAL; i++) // Fill the array with new random values
        {
            numbers[i] = rand(); // Assign new random values to the Array
        }
        delete [] mirror; // Delete the mirror array to free memory
        return 0;
    }
10 - WHY THE IMPLEMENTATION IS CORRECT and works with this main::

    ARRAY IMPLEMENTATION ANALYSIS
    ============================
    
    OUTPUT CORRECTNESS:
    The expected output is:
        Array index out of bounds
        Array index out of bounds
    
    This is correct because:
    
    1. First exception: numbers[-2] = 0;
       - -2 (signed int) converts to std::size_t (unsigned) = very large number
       - This large number >= 750, so throw std::out_of_range("Array index out of bounds")
    
    2. Second exception: numbers[MAX_VAL] = 0;
       - MAX_VAL = 750, but valid indices are 0-749
       - 750 >= 750, so throw std::out_of_range("Array index out of bounds")
    
    3. No "didn't save the same value!!" message: 
       - This confirms that deep copying works correctly
    
    
    IMPLEMENTATION COMPLIANCE WITH SUBJECT:
    =======================================
    
    Required Features - ALL IMPLEMENTED:
    
    ✓ Default constructor: Array() : _data(NULL), _size(0) {}
      Creates empty array
    
    ✓ Parameterized constructor: Array(unsigned int n)
      Creates array of n elements initialized by default
      Uses new T[n]() which default-initializes elements (as hinted by the tip)
    
    ✓ Copy constructor: Array(const Array& other)
      Deep copy implementation - modifying original or copy doesn't affect the other
    
    ✓ Assignment operator: Array& operator=(const Array& other)
      Deep copy with self-assignment protection
    
    ✓ Subscript operator: Both const and non-const versions implemented
      Throws std::out_of_range when index is out of bounds
    
    ✓ Size function: std::size_t size() const
      Returns number of elements, doesn't modify instance
    
    ✓ Memory management: Uses operator new[] and delete[], no preventive allocation
    
    
    COMPLIANCE WITH GENERAL RULES:
    ==============================
    
    Memory Management:
    ✓ Uses new[] and delete[] (no malloc/free)
    ✓ No memory leaks (proper destructor)
    ✓ No preventive allocation
    
    Orthodox Canonical Form:
    ✓ Default constructor
    ✓ Copy constructor
    ✓ Assignment operator
    ✓ Destructor
    
    C++98 Compatibility:
    ✓ No C++11 features used
    ✓ Uses standard library appropriately
    ✓ No forbidden containers/algorithms
    
    Template Implementation:
    ✓ Template class properly implemented
    ✓ Function templates in header file (allowed)
    
    Naming and Structure:
    ✓ Class name: Array (UpperCamelCase)
    ✓ File name: Array.hpp (matches class name)
    ✓ Include guards present
    ✓ Independent header (includes all dependencies)
    
    
    MAIN FUNCTION VALIDATION:
     ========================
    
    The provided main tests all required functionality:
    - Constructor with parameter
    - Deep copy behavior (scope test)
    - Data integrity after copying
    - Exception handling for out-of-bounds access
    - Element access and modification
    
    
     CONCLUSION:
     ==========
    
    The implementation is 100% compliant with both the subject requirements 
     and general rules. The output demonstrates that:
     
    1. Deep copying works correctly (no integrity errors)
    2. Bounds checking works correctly (proper exceptions thrown)
    3. Memory management is sound (no crashes or leaks)
    
    This is a perfect implementation for the exercise requirements.
11 - SYNTAX DIFFERENCES: CONSTRUCTOR vs ARRAY INITIALIZATION
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

int main()
{
    // Test empty 
    std::cout << std::endl;
    std::cout << "Test 1: Testing empty array:" << std::endl;
    Array<int> empty;
    std::cout << "Empty array size: " << empty.size() << std::endl;
    std::cout << std::endl;
    
    // Test array of ints
    std::cout << "Test 2: Testing array of integers:" << std::endl;
    Array<int> a(5); // (5) are the arguments of the constructor similar to Aray<int> a = Array<int>(5);, while int arr [5] = {0, 1, 2, 3, 4}; is a C-style array and {0, 1, 2, 3, 4} is an initializer list.
    for (unsigned int i = 0; i < a.size(); ++i)
        a[i] = i * 10;
    std::cout << "Int array: ";
    for (unsigned int i = 0; i < a.size(); ++i)
        std::cout << a[i] << " ";
    std::cout << std::endl;
    std::cout << std::endl;

    // Test array of strings (complex type)
    std::cout << "Test 3: Testing array of strings:" << std::endl;
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
    std::cout << "Test 4: Testing copy constructor:" << std::endl;
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
    std::cout << "Test 5: Testing assignment operator:" << std::endl;
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
    std::cout << "Test 6: Testing out of bounds access:" << std::endl;
    try {
        std::cout << "Accessing out of bounds: ";
        std::cout << a[100] << std::endl;
    } catch (const std::exception& e) {
        std::cout << "Caught exception: " << e.what() << std::endl;
    }
    std::cout << std::endl;
    
    return 0;
}

