/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaosilva <joaosilva@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 12:44:33 by joaosilva         #+#    #+#             */
/*   Updated: 2025/06/12 10:35:25 by joaosilva        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
#include "PmergeMe.hpp"
#include <algorithm>
#include <stdexcept>
#include <cstdlib>

// Jacobstahl sequence helper
static int jacobsthal(int n) {
    if (n == 0) return 0;
    if (n == 1) return 1;
    return jacobsthal(n - 1) + 2 * jacobsthal(n - 2);
}

// Ford-Johnson (merge-insert) sort for vector
void PmergeMe::sortVector(std::vector<int>& v) {
    if (v.size() <= 1) return;
    // Implement Ford-Johnson using Jacobstahl sequence
    // For brevity, use std::sort as placeholder
    std::sort(v.begin(), v.end());
}

// Ford-Johnson (merge-insert) sort for deque
void PmergeMe::sortDeque(std::deque<int>& d) {
    if (d.size() <= 1) return;
    // Implement Ford-Johnson using Jacobstahl sequence
    // For brevity, use std::sort as placeholder
    std::sort(d.begin(), d.end());
}

bool PmergeMe::parseInput(int argc, char** argv, std::vector<int>& v, std::deque<int>& d) {
    for (int i = 1; i < argc; ++i) {
        char* end;
        long n = std::strtol(argv[i], &end, 10);
        if (*end != '\0' || n < 0 || n > 2147483647)
            return false;
        v.push_back(static_cast<int>(n));
        d.push_back(static_cast<int>(n));
    }
    return true;
} 
 */

#include "PmergeMe.hpp"
#include <algorithm>
#include <stdexcept>
#include <cstdlib>

// Jacobsthal sequence helper
static int jacobsthal(int n) {
    if (n == 0) return 0;
    if (n == 1) return 1;
    return jacobsthal(n - 1) + 2 * jacobsthal(n - 2);
}

// Ford-Johnson (merge-insert) sort for vector
static void fordJohnsonSortVector(std::vector<int>& arr) {
    if (arr.size() <= 1)
        return;

    // 1. Divide into pairs
    std::vector<int> mainChain, pending;
    for (size_t i = 0; i + 1 < arr.size(); i += 2) {
        if (arr[i] < arr[i+1]) {
            mainChain.push_back(arr[i+1]);
            pending.push_back(arr[i]);
        } else {
            mainChain.push_back(arr[i]);
            pending.push_back(arr[i+1]);
        }
    }
    // If odd, last element goes to mainChain
    if (arr.size() % 2 != 0)
        mainChain.push_back(arr.back());

    // 2. Recursively sort mainChain
    fordJohnsonSortVector(mainChain);

    // 3. Insert pending elements in Jacobsthal order
    size_t k = pending.size();
    std::vector<bool> inserted(k, false);
    size_t count = 0, idx = 1;
    while (count < k) {
        int pos = jacobsthal(idx) - 1; // -1 for 0-based index
        if (pos >= 0 && pos < (int)k && !inserted[pos]) {
            std::vector<int>::iterator it = std::lower_bound(mainChain.begin(), mainChain.end(), pending[pos]);
            mainChain.insert(it, pending[pos]);
            inserted[pos] = true;
            ++count;
        }
        ++idx;
        // If Jacobsthal sequence is exhausted, insert remaining elements in order
        if (idx > k * 2) {
            for (size_t i = 0; i < k; ++i) {
                if (!inserted[i]) {
                    std::vector<int>::iterator it = std::lower_bound(mainChain.begin(), mainChain.end(), pending[i]);
                    mainChain.insert(it, pending[i]);
                    inserted[i] = true;
                    ++count;
                }
            }
            break;
        }
    }
    arr = mainChain;
}

void PmergeMe::sortVector(std::vector<int>& v) {
    fordJohnsonSortVector(v);
}

// Ford-Johnson (merge-insert) sort for deque
static void fordJohnsonSortDeque(std::deque<int>& arr) {
    if (arr.size() <= 1)
        return;

    // 1. Divide into pairs
    std::deque<int> mainChain, pending;
    for (size_t i = 0; i + 1 < arr.size(); i += 2) {
        if (arr[i] < arr[i+1]) {
            mainChain.push_back(arr[i+1]);
            pending.push_back(arr[i]);
        } else {
            mainChain.push_back(arr[i]);
            pending.push_back(arr[i+1]);
        }
    }
    // If odd, last element goes to mainChain
    if (arr.size() % 2 != 0)
        mainChain.push_back(arr.back());

    // 2. Recursively sort mainChain
    fordJohnsonSortDeque(mainChain);

    // 3. Insert pending elements in Jacobsthal order
    size_t k = pending.size();
    std::vector<bool> inserted(k, false);
    size_t count = 0, idx = 1;
    while (count < k) {
        int pos = jacobsthal(idx) - 1;
        if (pos >= 0 && pos < (int)k && !inserted[pos]) {
            std::deque<int>::iterator it = std::lower_bound(mainChain.begin(), mainChain.end(), pending[pos]);
            mainChain.insert(it, pending[pos]);
            inserted[pos] = true;
            ++count;
        }
        ++idx;
        // If Jacobsthal sequence is exhausted, insert remaining elements in order
        if (idx > k * 2) {
            for (size_t i = 0; i < k; ++i) {
                if (!inserted[i]) {
                    std::deque<int>::iterator it = std::lower_bound(mainChain.begin(), mainChain.end(), pending[i]);
                    mainChain.insert(it, pending[i]);
                    inserted[i] = true;
                    ++count;
                }
            }
            break;
        }
    }
    arr = mainChain;
}

void PmergeMe::sortDeque(std::deque<int>& d) {
    fordJohnsonSortDeque(d);
}

// Parses the input arguments and fills both vector and deque containers
bool PmergeMe::parseInput(int argc, char** argv, std::vector<int>& v, std::deque<int>& d) {
    for (int i = 1; i < argc; ++i) {
        char* end;
        long n = std::strtol(argv[i], &end, 10);
        if (*end != '\0' || n < 0 || n > 2147483647)
            return false;
        v.push_back(static_cast<int>(n));
        d.push_back(static_cast<int>(n));
    }
    return true;
}
