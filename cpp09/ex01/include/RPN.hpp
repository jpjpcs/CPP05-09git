/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaosilva <joaosilva@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 12:44:53 by joaosilva         #+#    #+#             */
/*   Updated: 2025/06/27 11:17:17 by joaosilva        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RPN_HPP
#define RPN_HPP

#include <stack>
#include <string>

class RPN 
{
    public:
        RPN();
		RPN(RPN const &other);
		RPN &operator=(RPN const &other);
		~RPN();
        
        static int evaluate(const std::string& expr);
};

#endif
