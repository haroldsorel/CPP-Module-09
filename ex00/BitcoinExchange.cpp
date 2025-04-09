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

BitcoinExchange::BitcoinExchange()
{
}

BitcoinExchange::BitcoinExchange(const std::string &file)
{
    std::ifstream   s(file);
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
        (this->_rates)[date] = std::stof(exchange);
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

bool    BitcoinExchange::getValue(std::string &line)
{
    std::string date;
    float       num;
    std::map<std::string, float>::iterator it;

    date = line.substr(0, 10);
    num = std::stof(line.substr(13));
    if ((it = (this->_rates).find(date)) != (this->_rates).end())
    {
        std::cout << line.replace(11, 1, "=>") << " = " << it->second * num <<std::endl;
        return (true);
    }
    if ((it = (this->_rates).upper_bound(date)) == (this->_rates).begin())
    {
        std::cout << "\033[31mError: \033[0m" << date << ": No Past Data" << std::endl;
        return (false);
    }
    it--;
    std::cout << line.replace(11, 1, "=>") << " = " << it->second * num <<std::endl;
    return (true);
}

bool    BitcoinExchange::isValidFile(const std::string &file)
{
    std::string     line;
    std::string     date;
    std::string     num;
    std::ifstream   s(file);

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

static bool        isValidDateFormat(std::string &date)
{
    if (date.length() != 10)
        return (false);
    for (int i = 0; i < 10; i++)
    {
        switch (i)
        {
            case 4: case 7:
            {
                if (date[i] != '-')
                    return (false);
                break ;
            }
            default:
            {
                if (!std::isdigit(date[i]))
                    return (false);
            }
        }
    }
    return (true);
}

bool        isValidDate(std::string &date)
{
    int day;
    int month;
    int year;

    if (!isValidDateFormat(date))
        return (false);
    day = std::stoi(date.substr(8, 2));
    month = std::stoi(date.substr(5, 2));
    year = std::stoi(date.substr(0, 4));
    //valid years
    if (year < 2009 || year > 2025)
        return (false);
    //valid months
    if (month < 1 || month > 12)
        return (false);
    //valid days
    if (month != 2)
    {
        switch (month)
        {
            case 1: case 3: case 5: case 7: case 8: case 10: case 12:
            {
                if (day < 1 || day > 31)
                    return (false);
                break;
            }
            default:
            {
                if (day < 1 || day > 30)
                    return (false);
            }
        }
    }
    else
    {
        switch (year)
        {
            case 2012: case 2016: case 2020: case 2024:
            {
                if (day < 1 || day > 29)
                    return (false);
                break;
            }
            default:
            {
                if (day < 1 || day > 28)
                    return (false);
            }
        }
    }
    return (true);
}

bool isValidNumber(std::string &num, int flag)
{
    try
    {
        size_t pos;
        float x = std::stof(num, &pos);
        
        if (pos != num.length() || x < 0)
            return (false);
        if (flag == 1 && x > 1000)
            return (false);
    }
    catch(const std::exception& e)
    {
        return (false);
    }
    return (true);
}
