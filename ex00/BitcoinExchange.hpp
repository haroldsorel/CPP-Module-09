/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haroldsorel <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 23:24:00 by haroldsorel       #+#    #+#             */
/*   Updated: 2025/04/08 23:24:01 by haroldsorel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <fstream>
#include <map>

class BitcoinExchange
{
    private:
        std::map<std::string, float>    _rates;
        bool                            isValidFile(const std::string &file);
    public:
        BitcoinExchange();
        BitcoinExchange(const std::string &file);
        BitcoinExchange(const BitcoinExchange &src);
        ~BitcoinExchange();
        BitcoinExchange &operator=(const BitcoinExchange &src);

        void    printExchange();
        bool    getValue(std::string &line);
        
        class InvalidFile : public std::exception
        {
            virtual const char *what() const throw()
            {
                return ("Invalid Csv File");
            }
        };
        class OpenFailure : public std::exception
        {
            virtual const char *what() const throw()
            {
                return ("Can't Open Csv File");
            }
        };
};

bool        isValidDate(std::string &date);
bool        isValidNumber(std::string &num, int flag);
