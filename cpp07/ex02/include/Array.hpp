/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Array.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jode-jes <jode-jes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 12:11:32 by joaosilva         #+#    #+#             */
/*   Updated: 2025/07/02 12:49:51 by jode-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ARRAY_HPP
#define ARRAY_HPP

#include <stdexcept>
#include <cstddef>

template <typename T>
class Array
{
    private:
        T*          _data; // Pointer to the array data. T comes from the template parameter and it means that the array can hold any type T specified when creating the Array instance (such as int, double, std::string, etc).
        // _data is a pointer to the dynamically allocated array of elements of type T.
        // When we create an Array<int>, _data points to an array of int.
        // When we create an Array<std::string>, _data points to an array of std::string.
        // We access these elements using the subscript operator: T& operator[](std::size_t idx) and const T& operator[](std::size_t idx) const.
        // The operator[] allows you to access elements of your array using the [] operator, just like a normal array.
        // The first version is for reading and writing: T& operator[](std::size_t idx).
        // The second version is for read-only access when the array is const: const T& operator[](std::size_t idx) const.
        std::size_t _size;

    public:
        // Default constructor: empty array
        Array() : _data(NULL), _size(0) {}

        // Constructor with size
        Array(unsigned int n) : _data(NULL), _size(n)
        {
            if (n > 0)
                _data = new T[n]();
        }

        // Copy constructor
        Array(const Array& other) : _data(NULL), _size(other._size)
        {
            if (_size > 0)
            {
                _data = new T[_size];
                for (std::size_t i = 0; i < _size; ++i)
                    _data[i] = other._data[i];
            }
        }

        // Assignment operator
        Array& operator=(const Array& other)
        {
            if (this != &other)
            {
                delete[] _data;
                _size = other._size;
                if (_size > 0)
                {
                    _data = new T[_size];
                    for (std::size_t i = 0; i < _size; ++i)
                        _data[i] = other._data[i];
                }
                else
                    _data = NULL;
            }
            return *this;
        }

        // Destructor
        ~Array()
        {
            delete[] _data;
        }

        // Subscript operator (read/write for non-const)
        T& operator[](std::size_t idx)
        {
            if (idx >= _size)
                throw std::out_of_range("Array index out of bounds");
            return _data[idx];
        }

        // Subscript operator (read-only for const)
        const T& operator[](std::size_t idx) const
        {
            if (idx >= _size)
                throw std::out_of_range("Array index out of bounds");
            return _data[idx];
        }

        // Size getter
        std::size_t size() const { return _size; }
};

#endif

