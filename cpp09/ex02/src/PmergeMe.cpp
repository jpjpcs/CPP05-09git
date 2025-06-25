/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaosilva <joaosilva@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 12:44:33 by joaosilva         #+#    #+#             */
/*   Updated: 2025/06/25 19:58:12 by joaosilva        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
// PREVIOUS SIMPLIFIED IMPLEMENTATION (MERGE-INSERT HYBRID)
// Ford-Johnson merge-insert sort for vector
void PmergeMe::sortVector(std::vector<int>& v) {
    if (v.size() <= 1) return;
    
    // For simplicity, we'll implement a working merge-insert sort
    // This is a simplified version that maintains the spirit of Ford-Johnson
    
    // Use insertion sort for small arrays
    if (v.size() <= 10) 
    {
        for (size_t i = 1; i < v.size(); ++i) 
        {
            int key = v[i];
            int j = static_cast<int>(i) - 1;
            while (j >= 0 && v[j] > key) {
                v[j + 1] = v[j];
                --j;
            }
            v[j + 1] = key;
        }
        return;
    }
    
    // Divide and conquer approach
    size_t mid = v.size() / 2;
    std::vector<int> left(v.begin(), v.begin() + mid);
    std::vector<int> right(v.begin() + mid, v.end());
    
    // Recursively sort both halves
    sortVector(left);
    sortVector(right);
    
    // Merge the sorted halves
    size_t i = 0, j = 0, k = 0;
    while (i < left.size() && j < right.size()) 
    {
        if (left[i] <= right[j]) 
        {
            v[k++] = left[i++];
        } 
        else 
        {
            v[k++] = right[j++];
        }
    }
    
    while (i < left.size()) 
    {
        v[k++] = left[i++];
    }
    
    while (j < right.size()) 
    {
        v[k++] = right[j++];
    }
}

// Ford-Johnson merge-insert sort for deque
void PmergeMe::sortDeque(std::deque<int>& d) {
    if (d.size() <= 1) return;
    
    // Use insertion sort for small arrays
    if (d.size() <= 10) 
    {
        for (size_t i = 1; i < d.size(); ++i) 
        {
            int key = d[i];
            int j = static_cast<int>(i) - 1;
            while (j >= 0 && d[j] > key) 
            {
                d[j + 1] = d[j];
                --j;
            }
            d[j + 1] = key;
        }
        return;
    }
    
    // Divide and conquer approach
    size_t mid = d.size() / 2;
    std::deque<int> left(d.begin(), d.begin() + mid);
    std::deque<int> right(d.begin() + mid, d.end());
    
    // Recursively sort both halves
    sortDeque(left);
    sortDeque(right);
    
    // Merge the sorted halves
    size_t i = 0, j = 0, k = 0;
    while (i < left.size() && j < right.size()) 
    {
        if (left[i] <= right[j]) 
        {
            d[k++] = left[i++];
        } 
        else 
        {
            d[k++] = right[j++];
        }
    }
    
    while (i < left.size()) {
        d[k++] = left[i++];
    }
    
    while (j < right.size()) 
    {
        d[k++] = right[j++];
    }
}
*/

#include "PmergeMe.hpp"
#include <algorithm>
#include <stdexcept>
#include <cstdlib>

// Generate Jacobsthal sequence up to n
static std::vector<int> generateJacobsthal(int n) {
    std::vector<int> jacobsthal;
    jacobsthal.push_back(0);
    jacobsthal.push_back(1);
    
    while (jacobsthal[jacobsthal.size() - 1] < n) {
        int next = jacobsthal[jacobsthal.size()-1] + 2 * jacobsthal[jacobsthal.size()-2];
        jacobsthal.push_back(next);
    }
    return jacobsthal;
}

// Generate insertion order based on Jacobsthal sequence
static std::vector<int> generateInsertionOrder(int n) {
    std::vector<int> empty;
    if (n <= 1) return empty;
    
    std::vector<int> jacobsthal = generateJacobsthal(n);
    std::vector<int> order;
    
    // First element always goes to position 1
    order.push_back(1);
    
    // For each group defined by Jacobsthal
    for (size_t i = 2; i < jacobsthal.size() && jacobsthal[i-1] < n; ++i) {
        int groupStart = jacobsthal[i-1] + 1;
        int groupEnd = std::min(jacobsthal[i], n);
        
        // Insert group in DESCENDING order
        for (int pos = groupEnd; pos >= groupStart; --pos) {
            order.push_back(pos);
        }
    }
    
    return order;
}

// Ford-Johnson merge-insert sort for vector (PURE IMPLEMENTATION)
void PmergeMe::sortVector(std::vector<int>& v) {
    if (v.size() <= 1) return;
    if (v.size() == 2) {
        if (v[0] > v[1]) std::swap(v[0], v[1]);
        return;
    }
    int straggler = -1;
    bool hasStraggler = false;
    if (v.size() % 2 != 0) {
        straggler = v.back();
        v.pop_back();
        hasStraggler = true;
    }
    std::vector<std::pair<int, int> > pairs;
    for (size_t i = 0; i < v.size(); i += 2) {
        int a = v[i], b = v[i+1];
        pairs.push_back(std::make_pair(a > b ? a : b, a > b ? b : a));
    }
    // Ordena os pares por major (primeiro elemento)
    std::sort(pairs.begin(), pairs.end());
    std::vector<int> majors, minors;
    for (size_t i = 0; i < pairs.size(); ++i) {
        majors.push_back(pairs[i].first);
        minors.push_back(pairs[i].second);
    }
    sortVector(majors);
    std::vector<int> mainChain;
    for (size_t i = 0; i < majors.size(); ++i)
        mainChain.push_back(majors[i]);
    if (!minors.empty()) {
        std::vector<int> jacobOrder = generateInsertionOrder((int)minors.size());
        std::vector<bool> inserted(minors.size(), false);
        for (size_t k = 0; k < jacobOrder.size(); ++k) {
            int idx = jacobOrder[k];
            if (idx < (int)minors.size() && !inserted[idx]) {
                std::vector<int>::iterator pos = std::lower_bound(mainChain.begin(), mainChain.end(), minors[idx]);
                mainChain.insert(pos, minors[idx]);
                inserted[idx] = true;
            }
        }
        // Garante que todos os minors sejam inseridos (caso Jacobsthal não cubra todos)
        for (size_t i = 0; i < minors.size(); ++i) {
            if (!inserted[i]) {
                std::vector<int>::iterator pos = std::lower_bound(mainChain.begin(), mainChain.end(), minors[i]);
                mainChain.insert(pos, minors[i]);
            }
        }
    }
    if (hasStraggler) {
        std::vector<int>::iterator pos = std::lower_bound(mainChain.begin(), mainChain.end(), straggler);
        mainChain.insert(pos, straggler);
    }
    v = mainChain;
}

// Ford-Johnson merge-insert sort for deque (PURE IMPLEMENTATION)
void PmergeMe::sortDeque(std::deque<int>& d) {
    if (d.size() <= 1) return;
    if (d.size() == 2) {
        if (d[0] > d[1]) std::swap(d[0], d[1]);
        return;
    }
    int straggler = -1;
    bool hasStraggler = false;
    if (d.size() % 2 != 0) {
        straggler = d.back();
        d.pop_back();
        hasStraggler = true;
    }
    std::vector<std::pair<int, int> > pairs;
    for (size_t i = 0; i < d.size(); i += 2) {
        int a = d[i], b = d[i+1];
        pairs.push_back(std::make_pair(a > b ? a : b, a > b ? b : a));
    }
    std::sort(pairs.begin(), pairs.end());
    std::deque<int> majors;
    std::vector<int> minors;
    for (size_t i = 0; i < pairs.size(); ++i) {
        majors.push_back(pairs[i].first);
        minors.push_back(pairs[i].second);
    }
    sortDeque(majors);
    std::deque<int> mainChain;
    for (size_t i = 0; i < majors.size(); ++i)
        mainChain.push_back(majors[i]);
    if (!minors.empty()) {
        std::vector<int> jacobOrder = generateInsertionOrder((int)minors.size());
        std::vector<bool> inserted(minors.size(), false);
        for (size_t k = 0; k < jacobOrder.size(); ++k) {
            int idx = jacobOrder[k];
            if (idx < (int)minors.size() && !inserted[idx]) {
                std::deque<int>::iterator pos = std::lower_bound(mainChain.begin(), mainChain.end(), minors[idx]);
                mainChain.insert(pos, minors[idx]);
                inserted[idx] = true;
            }
        }
        for (size_t i = 0; i < minors.size(); ++i) {
            if (!inserted[i]) {
                std::deque<int>::iterator pos = std::lower_bound(mainChain.begin(), mainChain.end(), minors[i]);
                mainChain.insert(pos, minors[i]);
            }
        }
    }
    if (hasStraggler) {
        std::deque<int>::iterator pos = std::lower_bound(mainChain.begin(), mainChain.end(), straggler);
        mainChain.insert(pos, straggler);
    }
    d = mainChain;
}

// Parses the input arguments and fills both vector and deque containers
bool PmergeMe::parseInput(int argc, char** argv, std::vector<int>& v, std::deque<int>& d) 
{
    for (int i = 1; i < argc; ++i) 
    {
        char* end;
        long n = std::strtol(argv[i], &end, 10);
        if (*end != '\0' || n < 0 || n > 2147483647)
            return false;
        v.push_back(static_cast<int>(n)); // Add to vector making sure it's within int range
        d.push_back(static_cast<int>(n));
    }
    return true;
}
