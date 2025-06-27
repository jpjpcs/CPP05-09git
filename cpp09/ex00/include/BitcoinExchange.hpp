/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaosilva <joaosilva@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 12:44:53 by joaosilva         #+#    #+#             */
/*   Updated: 2025/06/27 11:15:59 by joaosilva        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <map>
#include <string>

class BitcoinExchange
{
    public:
        BitcoinExchange(const std::string& dbFile);
        float getRate(const std::string& date) const;
        bool isValidDate(const std::string& date) const;
        static bool isValidValue(const std::string& valueStr, float& value);

    private:
        std::map<std::string, float> _rates; // My choosen container is a map because it allows us to efficiently look up exchange rates by date, and it maintains the order of dates.
        void loadDatabase(const std::string& dbFile);
};

#endif
