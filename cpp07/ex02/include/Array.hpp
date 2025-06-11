/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Array.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaosilva <joaosilva@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 12:11:32 by joaosilva         #+#    #+#             */
/*   Updated: 2025/06/02 15:48:17 by joaosilva        ###   ########.fr       */
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
        T*          _data;
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

        // Subscript operator (read/write)
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

