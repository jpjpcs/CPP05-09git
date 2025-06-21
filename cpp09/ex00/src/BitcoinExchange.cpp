/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaosilva <joaosilva@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 12:44:33 by joaosilva         #+#    #+#             */
/*   Updated: 2025/06/12 12:07:59 by joaosilva        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"
#include <fstream>
#include <sstream>
#include <iostream>
#include <cstdlib>
#include <limits>

BitcoinExchange::BitcoinExchange(const std::string& dbFile) 
{
    loadDatabase(dbFile);
}

void BitcoinExchange::loadDatabase(const std::string& dbFile) 
{
    std::ifstream file(dbFile.c_str()); // Open the database file
    if (!file)
        throw std::runtime_error("Error: could not open database file.");
    std::string line;
    getline(file, line); // skip header. // Why? Because the first line of the database file is usually a header that describes the data format, and we don't need to process it.
    while (getline(file, line)) // Read each line from the database file until the end of the file is reached.
    {
        std::istringstream iss(line); // Create a string stream to parse the line. 
        // Why? Because we need to extract the date and value from each line of the database file.
        // How? By using `std::istringstream`, which allows us to treat the line as a stream and extract values from it.
        // The `iss` variable is an instance of `std::istringstream`, which is a stream class that operates on strings.
        // It allows us to read formatted data from a string as if it were an input stream, making it easy to parse the date and value from each line.
        std::string date, valueStr; // Declare strings to hold the date and value extracted from the line.
        if (getline(iss, date, ',') && getline(iss, valueStr)) // It verifies if the line contains both a date and a value separated by a comma.
        {
            float value = std::atof(valueStr.c_str()); // Convert the value string to a float using `atof`.
            // Why? Because we need to convert the string representation of the value to a float for further processing.
            // How? By using `std::atof`, which converts a C-style string to a float.
            // atof means "ASCII to float", and it is a standard C library function that converts a string to a floating-point number.
            // The `valueStr.c_str()` converts the `valueStr` string to a C-style string (const char*), which is required by `atof`.
            _rates[date] = value; // Store the date and corresponding value in the `_rates` map, my choosen container.
        }
    }
}

float BitcoinExchange::getRate(const std::string& date) const 
{
    std::map<std::string, float>::const_iterator it = _rates.lower_bound(date); // Find the first date that is not less than the given date.
    // it is an iterator that points to the first element in the map whose key is not less than the specified date.
    // lower_bound returns an iterator pointing to the first element that is not less than the specified key (in this case, the date).
    // Why? Because we want to find the exchange rate for the given date or the closest previous date if the exact date is not found.
    // How? By using the `lower_bound` method of the map, which performs a binary search to find the appropriate position.
    // The `lower_bound` method is efficient because it uses a binary search algorithm, which has a time complexity of O(log n).
    if (it != _rates.end() && it->first == date) // If the iterator points to the end of the map or if the date matches the key in the map, return the corresponding value.
        return it->second; // Return the exchange rate for the exact date found in the map.
    // If the iterator points to the end of the map or if the date does not match, we need to return the rate for the closest previous date.
    if (it == _rates.begin()) // If the iterator is at the beginning of the map, it means there are no rates available for any date before the given date.
        throw std::runtime_error("Error: no rate available for this date.");
    --it; // Move the iterator back to the previous element, which will be the closest previous date.
    return it->second; // Return the exchange rate for the closest previous date.
}

bool BitcoinExchange::isValidDate(const std::string& date) const 
{
    // Simple YYYY-MM-DD validation
    if (date.size() != 10 || date[4] != '-' || date[7] != '-') // !10 because we expect the format YYYY-MM-DD and !10 means the string is not exactly 10 characters long and the string must be exactly 10 characters long to match the format (YYYY-MM-DD) and num. 4 and 7 must be '-' characters.
        return false;
    // Further checks omitted for brevity
    return true;
}

bool BitcoinExchange::isValidValue(const std::string& valueStr, float& value) {
    char* end;
    value = std::strtof(valueStr.c_str(), &end); // Convert string to float
    // Why? To check if the string represents a valid floating-point number.
    // How? By using `strtof`, which converts a string to a float and provides a pointer to the end of the parsed string.
    // Where? In the BitcoinExchange class, where we need to validate user input before processing it.
    if (*end != '\0' || value < 0 || value > 1000)
        return false;
    return true;
}
