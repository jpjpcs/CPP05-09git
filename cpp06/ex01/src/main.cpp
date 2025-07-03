/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jode-jes <jode-jes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 20:52:05 by joaosilva         #+#    #+#             */
/*   Updated: 2025/07/01 10:35:42 by jode-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Serializer.hpp"
#include <iostream>

/*
1 - The aim of this exercise is to implement a Serializer class that handles serialization and deserialization of a Data object.
   The class should convert a pointer to a Data object into a raw address (uintptr_t) and reconstruct the Data object from that raw address.
   The exercise demonstrates how to safely manipulate pointers and addresses in C++.
   Why? To use reinterpret_cast to convert a pointer to an integer type (uintptr_t) for serialization,
    and then convert it back to a pointer type during deserialization.
2 - What is serialization?
    Serialization is the process of converting an object or data structure into a format that can be easily stored (for example, 
    in a file or memory buffer) or transmitted (for example, over a network) and later reconstructed (deserialized) back into the original object.
    In C++, serialization often involves converting pointers or objects into raw data (such as integers or byte streams) 
    so they can be saved or sent, and then converting them back to usable objects when
3 - What is deserialization?
    Deserialization is the reverse process of serialization. It involves taking the serialized data (such as a raw address 
    or byte stream) and reconstructing it back into the original object or data structure.
    This allows the program to retrieve the original object from its serialized form, 
    restoring its state and making it usable again.
4 - Why do we need serialization and deserialization?
    Serialization and deserialization are essential for several reasons:
    - **Data Persistence**: They allow objects to be saved to files or databases, enabling data persistence across program executions.
    - **Network Communication**: They enable objects to be sent over networks, allowing distributed systems to communicate and share data.
    - **Interoperability**: They facilitate communication between different programming languages or systems by converting objects into a common format.
5 - What is the purpose of the Serializer class?
    The `Serializer` class in this context is designed to handle the serialization and deserialization of objects of type `Data`.
    It provides static methods to convert a pointer to a `Data` object into a raw address (uintptr_t) and to reconstruct the `Data` object from that raw address.
6 - Why do we use uintptr_t for serialization?
    `uintptr_t` is an unsigned integer type that is capable of holding a pointer value. It is used for serialization because it allows 
    us to convert a pointer to a raw address without losing information about the pointer's value.
    This is important for deserialization, where we need to reconstruct the original pointer from the raw address.
7 - What is the significance of the reinterpret_cast in the Serializer class?
    The `reinterpret_cast` is used to convert between pointer types and integer types (uintptr_t) in the `Serializer` class.
    It allows us to treat a pointer as an integer (uintptr_t) for serialization and then convert it back to a pointer type during deserialization.
    This cast is necessary because pointers and integers are different types, and we need to ensure that the pointer's value is preserved 
    when converting it to an integer representation.
    However, it is important to use `reinterpret_cast` carefully, as it can lead to undefined behavior if the pointer is not valid or if the types are incompatible.
    It is generally safe to use `reinterpret_cast` in this context because we are converting between pointer types and uintptr_t,
    which are designed to hold pointer values. However, care must be taken to ensure that the pointer being serialized is valid and points to an object of the expected type.
8 - What´s the purpose of this exercise?
    The purpose of this exercise is to demonstrate the concepts of serialization and deserialization in C++ using a simple class (`Data`)
    and a `Serializer` class that handles the conversion between pointers and raw addresses.
    It illustrates how to serialize an object to a raw address, deserialize it back to a pointer, and handle cases where the pointer may not point to a valid object.
    The exercise also highlights the importance of checking pointer validity and understanding the implications of accessing members of pointers that may not point to valid objects.
    It serves as a practical example of how serialization can be implemented in C++ and the potential pitfalls of pointer manipulation.
        In Ex01, serialization means converting a pointer to an object (Data*) into an integer value (uintptr_t) that represents the memory address of that object.
        The goal is to demonstrate how you can transform a pointer into a "raw" value (raw address), which can be stored, transmitted, or manipulated as a number, and then reconstruct the original pointer from that value using reinterpret_cast.
        This is not data serialization to a file or network, but rather serialization of the pointer address into an integer type that is safe for pointers.
9 - Why the value 140732698565360?
        Why does "Serialized Data to raw address" give this value: 140732698565360? Shouldn't it show a pointer value?
        That value is the pointer value, just displayed as a decimal (integer) number.
        When you do uintptr_t raw = Serializer::serialize(&data);, you are taking the memory address of data and converting it to an unsigned integer.
        When you print raw, you are showing that address as a decimal number (for example, 140732698565360).
        If you printed &data or ptr directly, you would normally see the address in hexadecimal (e.g., 0x7ffeefbff5b0).
        Summary:
        The displayed value is the pointer address, just in decimal format.
10 - Why do we not access the members of fake_ptr in test 4?
    In the failure test (test 4), do not access the members of fake_ptr because, by modifying the value of raw (for example, raw + 1), 
    the resulting pointer (fake_ptr) no longer points to a valid object of type Data. It points to an arbitrary memory address, 
    which may not belong to your program or may contain invalid data.
    Accessing members of an invalid pointer causes undefined behavior in C/C++. 
    
    This can result in:
    - Program crash (segmentation fault)
    - Reading garbage/random values
    - Memory corruption
    - Security vulnerabilities
    
    Summary:
        We should only access members of a pointer if it points to a valid object.
        When we manually change the address, this is no longer guaranteed.
        Therefore, only compare the pointers—never access their members in simulated failure cases!
11 - What types of cast exist?
    In C++, there are four explicit cast operators:
    - static_cast
    - dynamic_cast
    - const_cast
    - reinterpret_cast
    There are also implicit casts (automatic conversions) and C-style casts (e.g., (int)x).

12 - What's the difference between static and dynamic cast and when to use one or the other?
    - static_cast:
    Compile-time cast. Used for conversions between related types (e.g., base/derived pointers, numeric types). No runtime check.
    Use when you are sure about the types and want performance.
    - dynamic_cast:
    Runtime-checked cast. Used for safe downcasting in polymorphic class hierarchies (classes with virtual functions).
    Use when you need to check at runtime if a pointer/reference can be safely cast to a derived type.
13 - What is reinterpret_cast and for what's useful for?
    - reinterpret_cast:
    Used for low-level, unsafe conversions between unrelated types (e.g., pointer to integer, integer to pointer, pointer to different pointer type).
    Useful for serialization, working with raw memory, or interfacing with hardware.
14 - What's downcast, upcast, type qualifier? Give me simple but effective examples.
    - Upcast: Casting from derived to base class (always safe).
        class Base {};
        class Derived : public Base {};
        Derived d;
        Base* b = static_cast<Base*>(&d); // upcast

    - Downcast:
        Casting from base to derived class (may be unsafe, use dynamic_cast for safety).
        Base* b = new Derived();
        Derived* d = dynamic_cast<Derived*>(b); // downcast

    - Type qualifier cast (const_cast):
        Adds or removes const/volatile qualifiers.
        const int* a = ...;
        int* b = const_cast<int*>(a);
15 - implicit cast and explicit cast are C casts or C++ casts? Or both. For what are they useful for? Examples.
    - Implicit cast:
    Automatic conversion by the compiler (both C and C++).
        int a = 42;
        double b = a; // implicit cast from int to double
    - Explicit cast:
    Programmer-specified conversion.
        C-style: (int)x
        C++-style: static_cast<int>(x), etc.
        -------
        double x = 3.14;
        int y = (int)x; // C-style explicit cast
        int z = static_cast<int>(x); // C++-style explicit cast
16 - Implicit conversion is the same as implicit cast? and explicit conversion is the same as explicit cast?
    Yes, in practice:
    Implicit conversion = implicit cast (automatic by compiler)
    Explicit conversion = explicit cast (programmer-specified)
17 - What is being done here?
    uintptr_t Serializer::serialize(Data* ptr)
    {
        return reinterpret_cast<uintptr_t>(ptr);
    }
    Data* Serializer::deserialize(uintptr_t raw)
    {
        return reinterpret_cast<Data*>(raw);
    }
    - serialize: Converts a pointer (Data*) to an integer type (uintptr_t) using reinterpret_cast. This is useful for serialization or storing pointers as numbers.
    - deserialize: Converts the integer (uintptr_t) back to a pointer (Data*) using reinterpret_cast.
    This is a typical pattern for pointer serialization/deserialization in C++.
18 - "This is useful for serialization or storing pointers as numbers.
"Why should we want to store pointers as numbers?!

    Storing pointers as numbers (using an integer type like uintptr_t) can be useful in several situations:
    - Serialization/Deserialization:
    When you need to save the state of a program (including pointers) to a file or send it over a network, you can't directly store pointers as memory addresses, but you can convert them to numbers for later reconstruction (within the same process or context).
    - Low-level Programming:
    Sometimes you need to perform arithmetic or bitwise operations on addresses, which requires treating pointers as numbers.
    - Interfacing with Hardware or OS:
    Some system APIs or hardware interfaces require addresses to be passed as integer types.
    - Debugging and Logging:
    Printing pointer values as numbers (especially in hexadecimal) can help with debugging memory issues.

    Important:
        Storing and restoring pointers as numbers is only safe if the memory they point to remains valid and the context (process, address space) does not change.
        You should never serialize a pointer to disk and expect it to be valid after restarting the program! This technique is mainly for temporary, in-memory use or for advanced low-level tasks.
19 - "You should never serialize a pointer to disk and expect it to be valid after restarting the program! This technique is mainly for temporary, in-memory use or for advanced low-level tasks."
why? the data is erased after restart?
    You should never serialize a pointer to disk and expect it to be valid after restarting the program because:
        Pointers store memory addresses (locations in RAM) that are only meaningful while your program is running.
        When you restart the program, the operating system can load your program and its data into different memory locations.
        The address that a pointer had in a previous run is almost never the same in a new run.
        If you try to use an old pointer value after a restart, it will point to an invalid or random location in memory, leading to crashes or undefined behavior.
    Summary:
        The data itself may still exist (if you saved it), but the memory address (pointer) is not guaranteed to be the same after a restart.
        Pointers are only valid within the same process and session.
        For persistent storage, you must serialize the actual data, not the pointer value.
*/

int main()
{
    Data data;
    data.number = 42;
    data.text = "Hello, 42!";
    data.value = 3.14159;

    std::cout << std::endl;
    std::cout << "-------------- Test 1: Serialization and Deserialization (Success)" << std::endl;
    uintptr_t raw = Serializer::serialize(&data);
    std::cout << "     Serialized Data to raw address: " << raw << std::endl;
    std::cout << "     Serialized Data to raw address (hex): 0x" << std::hex << raw << std::dec << std::endl;
    
    Data* ptr = Serializer::deserialize(raw);
    std::cout << "     Original Data address: " << &data << std::endl;
    std::cout << "     Deserialized Data address: " << ptr << std::endl;
    if (ptr == &data)
        std::cout << "     Success: The deserialized pointer matches the original!" << std::endl;
    else
        std::cout << "     Error: The deserialized pointer does not match the original!" << std::endl;

    std::cout << "---- Original Data content:" << std::endl;
    std::cout << "     number: " << data.number << std::endl;
    std::cout << "     text: " << data.text << std::endl;
    std::cout << "     value: " << data.value << std::endl;

    std::cout << "---- Deserialized Data content:" << std::endl;
    std::cout << "     number: " << ptr->number << std::endl;
    std::cout << "     text: " << ptr->text << std::endl;
    std::cout << "     value: " << ptr->value << std::endl;
    std::cout << "---- End of test 1 ----" << std::endl;
    

    
    std::cout << "\n------------ Test 2: Serialization and Deserialization (Failure simulation)" << std::endl;
    uintptr_t fake_raw = raw + 1; // Simulate a wrong address
    Data* fake_ptr = Serializer::deserialize(fake_raw);

    std::cout << "     Original Data address: " << &data << std::endl;
    std::cout << "     Fake Deserialized Data address: " << fake_ptr << std::endl;
    if (fake_ptr == &data)
        std::cout << "     Success: The fake deserialized pointer matches the original." << std::endl;
    else
        std::cout << "     Error: The fake deserialized pointer does NOT match the original." << std::endl;
    
    std::cout << "---- Original Data content:" << std::endl;
    std::cout << "     number: " << data.number << std::endl;
    std::cout << "     text: " << data.text << std::endl;
    std::cout << "     value: " << data.value << std::endl;
    
/*     std::cout << "--- Fake Deserialized Data content (may be garbage):" << std::endl;   
    std::cout << "     number: " << fake_ptr->number << std::endl;
    std::cout << "     text: " << fake_ptr->text << std::endl;
    std::cout << "     value: " << fake_ptr->value << std::endl;
    std::cout << "---- End of test 2 ----" << std::endl; */
    
    
    
    std::cout << "\n---- Test 3: Null Pointer Serialization" << std::endl;
    uintptr_t null_raw = Serializer::serialize(NULL);
    Data* null_ptr = Serializer::deserialize(null_raw);
    std::cout << "     Null pointer serialized to: " << null_raw << std::endl;
    if (null_ptr == NULL)
        std::cout << "     Success: Deserialized null pointer is indeed null!" << std::endl;
    else
        std::cout << "     Error: Deserialized null pointer is not null!" << std::endl;
    
    if (fake_ptr == NULL)
        std::cout << "     Fake pointer is null, as expected." << std::endl;
    else
        std::cout << "     Fake pointer is not null, unexpected behavior!" << std::endl;
    std::cout << "---- End of test 3 ----" << std::endl;
   
    std::cout << std::endl;
    std::cout << "-------------------- End of tests -----------------------" << std::endl;
    std::cout << std::endl;
    
    return 0;
}
