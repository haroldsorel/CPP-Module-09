/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_parsing.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsorel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 19:18:56 by hsorel            #+#    #+#             */
/*   Updated: 2025/08/26 19:18:58 by hsorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

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
    day = std::atoi(date.substr(8, 2).c_str());
    month = std::atoi(date.substr(5, 2).c_str());
    year = std::atoi(date.substr(0, 4).c_str());
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
    char *end = NULL;
    const char *c_num = num.c_str();
    float x = std::strtof(c_num, &end);
    
    while (*end == ' ' || *end == '\t' || *end == '\n' || *end == '\v' || *end == '\f' || *end == '\r')
        end++;
    if (end == c_num || *end != '\0' || x < 0)
        return (false);
    if (flag == 1 && x > 1000)
        return (false);
    return (true);
}

bool    CheckInputLine(std::string &line)
{
    std::string     date;
    std::string     num;

    if (line.length() < 14)
    {
        std::cout << "\033[31mError: \033[0m" << line << ": Wrong Format" << std::endl;
        return (false);
    }
    if (line[10] != ' ' || line[11] != '|' || line[12] != ' ' || (!std::isdigit(line[13]) && line[13] != '-'))
    {
        std::cout << "\033[31mError: \033[0m" << line << ": Wrong Format" << std::endl;
        return (false);
    }
    date = line.substr(0, 10);
    num = line.substr(13);
    if (!isValidDate(date))
    {
        std::cout << "\033[31mError: \033[0m" << date << ": Wrong Date" << std::endl;
        return (false);
    }
    if (!isValidNumber(num, 1))
    {
        std::cout << "\033[31mError: \033[0m" << num << ": Wrong Number" << std::endl;
        return (false);
    }
    return (true);
}
