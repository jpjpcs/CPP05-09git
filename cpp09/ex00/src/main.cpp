/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaosilva <joaosilva@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 12:43:42 by joaosilva         #+#    #+#             */
/*   Updated: 2025/06/27 11:16:14 by joaosilva        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
1 - Put isNumber and trim in the header file?
   No, they should not be in the header file.
   Why? Because they are utility functions that are not part of the BitcoinExchange class interface.
   How? They are used for parsing and validating user input, which is the responsibility of main.cpp.
   Where? They should remain in main.cpp, where they are used to process user input before interacting with the BitcoinExchange class.
2 - These functions (isValidDate and isValidValue) should indeed be part of the BitcoinExchange class because:
    - Why keep them in the class?
    . They are part of the class's domain logic:
        Validating dates and values is part of what the BitcoinExchange class represents (working with bitcoin dates and values).
    . They can be reused in other parts of the code:
        If you need to validate dates/values in other methods of the class, they are already available.
    . They are public (or static) methods of the interface:
        The header exposes these functions to anyone using the class, making the code more modular and reusable.
    . Responsibility:
        Validating whether a date is valid for the bitcoin database, or if a value is within the correct range, is the responsibility of the class's business logic, not the main function.
    - Why not put them in main?
        . The main function should only handle the program flow and input parsing, not business logic.
        . If you put these functions in main, you lose encapsulation and reusability.
        . The subject and evaluation sheet expect that date/value validation is part of the class logic, as it is directly related to the class's domain.
    - Summary:
        . Generic utility functions (like trim and isNumber) → main.cpp.
        . Domain validation functions (like isValidDate and isValidValue) → in the BitcoinExchange class.
    - Conclusion:
        . You have it correct!
        . Keep isValidDate and isValidValue in the BitcoinExchange class.
        . Keep trim and isNumber in main.cpp.
        . This way your code is clean, modular, and in accordance with the subject and evaluation.
*/

#include "BitcoinExchange.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <cctype>

static std::string trim(const std::string& s) 
{
    size_t start = s.find_first_not_of(" \t"); // Find the first character that is not a space or tab. 
    if (start == std::string::npos) return ""; // If no non-space character is found, return an empty string.
    size_t end = s.find_last_not_of(" \t"); // Find the last character that is not a space or tab.
    // Why? Because we want to remove any leading or trailing whitespace from the string.
    return s.substr(start, end - start + 1); // It returns the substring from the first non-space character to the last non-space character, effectively trimming leading and trailing whitespace.
}

static bool isNumber(const std::string& s) 
{
    if (s.empty()) return false;
    char* end;
    std::strtof(s.c_str(), &end); // Convert string to float. Why? To check if the string represents a valid floating-point number.
    // Why? Because we need to validate the input value before processing it.
    // How? By using `strtof`, which converts a string to a float and provides a pointer to the end of the parsed string.   
    return *end == '\0'; // Check if the entire string was converted to a float.
    // If `*end` is not equal to '\0', it means there are characters left in the string that were not part of the number.
    // If `*end` is '\0', it means the entire string was a valid float representation.
}

int main(int argc, char** argv)
{
    if (argc != 2) 
    {
        std::cerr << "Error: could not open file." << std::endl;
        return 1;
    }
    try {
        BitcoinExchange btc("data.csv"); // Initialize BitcoinExchange with the database file. 
        //We pass "data.csv" to BitcoinExchange because "data.csv" is the database file that contains the historical bitcoin prices (the rates for each date).
        // This file is provided with the subject and is always the same for your program.
        // On the other hand, argv[1] is the input file provided by the user at runtime, which contains the dates and values you want to evaluate (the queries).
        std::ifstream input(argv[1]); // Open the input file specified in the command line argument
        if (!input) 
        {
            std::cerr << "Error: could not open file." << std::endl;
            return 1;
        }
        std::string line; // Declare a string variable to hold each line read from the input file.
        getline(input, line); // skip header. Why? Because the first line of the input file is usually a header that describes the data format, and we don't need to process it.
        // How we exlude the header? By calling `getline(input, line)` before entering the loop that processes the rest of the file.
        // This reads the first line and stores it in the `line` variable, effectively skipping it.
        // Now we can process the rest of the file line by line.
        while (getline(input, line)) // Read each line from the input file until the end of the file is reached.
        {
            // Check if line contains '|'
            size_t pipe = line.find('|');
            if (pipe == std::string::npos) // npos means "not found", so if we can't find the pipe character, it means the line is not formatted correctly.
            // And if a line does not contain a pipe character, it means it is not formatted correctly.
            {
                std::cout << "Error: bad input => " << line << std::endl;
                continue;
            }
            std::string date = trim(line.substr(0, pipe)); // Extract the date part of the line up to the pipe character and trim whitespace.
            // Why? Because the date is the first part of the line, and we need to validate it before processing the value.
            // How? By using `line.substr(0, pipe)` to get the substring from the start of the line up to the pipe character,
            // and then using the `trim` function to remove any leading or trailing whitespace from the date string.
            // The `trim` function is defined above and removes spaces and tabs from both ends of the string.
            std::string valueStr = trim(line.substr(pipe + 1)); // +1 to skip the pipe character, extract the value part of the line and trim whitespace.
            float value; // Declare a float variable to hold the value after validation.
            // Why? Because the value is the second part of the line, and we need to validate it before processing it.
            // How? By using `line.substr(pipe + 1)` to get the substring from the character after the pipe to the end of the line, 
            // and then using the `trim` function to remove any leading or trailing whitespace from the value string.
            // The `trim` function is defined above and removes spaces and tabs from both ends of the string.

            // Validate date
            if (!btc.isValidDate(date)) // Check if the date is valid using the BitcoinExchange method.
            {
                std::cout << "Error: bad input => " << date << std::endl;
                continue;
            }
            // Validate value: check if it's a number
            if (!isNumber(valueStr)) // Check if the value string represents a valid number.
            {
                std::cout << "Error: bad input => " << line << std::endl;
                continue;
            }
            // Validate value: check range
            if (!BitcoinExchange::isValidValue(valueStr, value)) 
            {
                if (value < 0)
                    std::cout << "Error: not a positive number." << std::endl;
                else
                    std::cout << "Error: too large a number." << std::endl;
                continue;
            }
            try {
                float rate = btc.getRate(date); // Get the exchange rate for the given date
                std::cout << date << " => " << value << " = " << value * rate << std::endl;
            } catch (std::exception& e) {
                std::cout << e.what() << std::endl; // If an error occurs while getting the rate, we catch the exception and print the error message.
                // This could happen if the date is not found in the database or if there is an issue with the exchange rate retrieval.
                // The `what()` method of the exception object provides a human-readable error message.
                // This way, we can inform the user about the specific error that occurred during the rate retrieval process.
                // In this case, we simply print the error message to the console that is returned by the `what()` method of the exception object
                // and it is this specific message: "Error: no rate available for this date.".
            }
        }
    } catch (std::exception& e) {
        std::cerr << e.what() << std::endl; // If an error occurs while processing the input file or initializing BitcoinExchange, we catch the exception and print the error message.
        // This could happen if the database file cannot be opened or if there is an issue with the input file format.
        // The `what()` method of the exception object provides a human-readable error message.
        // This way, we can inform the user about the specific error that occurred during the processing of the input file or the initialization of BitcoinExchange.
        // In this case, we simply print the error message to the console that is returned by the `what()` method of the exception object.
        // If the error is related to the database file, it will be something like "Error: could not open database file."
        // If the error is related to the input file, it will be something like "Error: could not open file."
        // In either case, we return 1 to indicate that an error occurred.
        return 1;
    }
    return 0;
}
