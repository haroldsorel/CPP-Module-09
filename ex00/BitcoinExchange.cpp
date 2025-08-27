/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haroldsorel <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 23:24:07 by haroldsorel       #+#    #+#             */
/*   Updated: 2025/04/08 23:24:08 by haroldsorel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

bool isValidNumber(std::string &num, int flag);
bool        isValidDate(std::string &date);

BitcoinExchange::BitcoinExchange()
{
}

BitcoinExchange::BitcoinExchange(const std::string &file)
{
    std::ifstream   s(file.c_str());
    std::string     line;
    std::string     date;
    std::string     exchange;
    size_t          commaPos;

    if (!s.is_open())
        throw (OpenFailure());
    if (!isValidFile(file))
        throw (InvalidFile());
    std::getline(s, line); //skips "data, exchange rate"
    while (std::getline(s, line))
    {
        commaPos = line.find(',');
        date = line.substr(0, commaPos);
        exchange = line.substr(commaPos + 1);
        (this->_rates)[date] = std::atof(exchange.c_str());
    }
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &src) : _rates(src._rates)
{}

BitcoinExchange::~BitcoinExchange()
{}

BitcoinExchange &BitcoinExchange::operator=(const BitcoinExchange &src)
{
    if (this != &src)
        this->_rates = src._rates;
    return (*this);
}

void    BitcoinExchange::printExchange()
{
    std::map<std::string, float>::iterator it;

    for (it = (this->_rates).begin(); it != (this->_rates).end(); ++it)
        std::cout << it->first << " -> " << it->second << std::endl;
}

bool    BitcoinExchange::getValue(std::string &date, float num)
{
    std::map<std::string, float>::iterator it;

    //if a precise date is found return the iterator to that data-rate
    if ((it = (this->_rates).find(date)) != (this->_rates).end())
    {
        std::cout << date << '\t' << "=>" << '\t' << num << " = " << it->second * num << " (according to data from " << it->first << ')' << std::endl;
        return (true);
    }

    //Returns an iterator to the first element whose key is strictly greater than the given key.
    //if nothing is greater then it returns negin and we have no past data
    if ((it = (this->_rates).upper_bound(date)) == (this->_rates).begin())
    {
        std::cout << "\033[31mError: \033[0m" << date << ": No Past Data" << std::endl;
        return (false);
    }

    //if upper_bounds returned something do it-- to get the past data and not the future data 
    it--;
    std::cout << date << '\t' << "=>" << '\t' << num << " = " << it->second * num << " (according to data from " << it->first << ')' << std::endl;
    return (true);
}

bool    BitcoinExchange::isValidFile(const std::string &file)
{
    std::string     line;
    std::string     date;
    std::string     num;
    std::ifstream   s(file.c_str());

    if (!s.is_open())
        throw (BitcoinExchange::OpenFailure());
    std::getline(s, line); 
    if (line != "date,exchange_rate")
        return (false);
    while (std::getline(s, line))
    {
        if (line.length() < 12)
            return (false);
        if (line[10] != ',')
            return (false);
        date = line.substr(0, 10);
        num = line.substr(11);
        if (!isValidDate(date))
            return (false);
        if (!isValidNumber(num, 0))
            return (false);
    }
    return (true);
}
