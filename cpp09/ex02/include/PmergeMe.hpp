/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaosilva <joaosilva@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 12:44:53 by joaosilva         #+#    #+#             */
/*   Updated: 2025/06/11 13:03:13 by joaosilva        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <vector>
#include <deque>
#include <string>

class PmergeMe {
public:
    static void sortVector(std::vector<int>& v);
    static void sortDeque(std::deque<int>& d);
    static bool parseInput(int argc, char** argv, std::vector<int>& v, std::deque<int>& d);
};

#endif
