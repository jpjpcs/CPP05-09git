/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Base.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaosilva <joaosilva@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 11:31:21 by joaosilva         #+#    #+#             */
/*   Updated: 2025/05/30 11:45:14 by joaosilva        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Base.hpp"

// The destructor is virtual to ensure proper cleanup of derived classes.
// This is important in polymorphic base classes to avoid memory leaks when deleting derived class objects through base class pointers.
// If you delete a derived class object through a base class pointer without a virtual destructor, the derived class's destructor won't be called, leading to resource leaks.
// In this case, the destructor is empty because there are no resources to clean up in the Base class itself.
// Derived classes (A, B, C) will have their own destructors if they need to clean up resources.
Base::~Base() {}

