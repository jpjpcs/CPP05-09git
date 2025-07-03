/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jode-jes <jode-jes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 12:44:53 by joaosilva         #+#    #+#             */
/*   Updated: 2025/07/02 20:19:55 by jode-jes         ###   ########.fr       */
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
        void isValidDate(const std::string& date);
        static bool isValidValue(const std::string& valueStr, float& value);

    private:
        std::map<std::string, float> _rates; // My choosen container is a map because it allows us to efficiently look up exchange rates by date, and it maintains the order of dates.
        void loadDatabase(const std::string& dbFile);
};

#endif
