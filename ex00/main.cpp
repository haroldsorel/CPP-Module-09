/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haroldsorel <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 23:21:59 by haroldsorel       #+#    #+#             */
/*   Updated: 2025/04/08 23:22:00 by haroldsorel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

static bool    CheckInputLine(std::string &line)
{
    std::string     date;
    std::string     num;

    if (line.length() < 14)
    {
        std::cout << "\033[31mError: \033[0m" << line << ": Wrong Format" << std::endl;
        return (false);
    }
    if (line[10] != ' ' || line[11] != '|' || line[12] != ' ')
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

int main(int argc, char **argv)
{
    //checking user input
    if (argc != 2)
    {
        std::cout << "Enter one file as argument" << std::endl;
        return (1);
    }

    //checking input file
    std::string     filename = argv[1];
    std::fstream    file(filename);
    std::string     line;
    BitcoinExchange btcE;
    if (!file.is_open())
    {
        std::cout << "Error: Could Not Open File." << std::endl;
        return (1);
    }
    //initializing BitcoinExchange object based on data.csv: fotmat (date, exchange rate)
    try {btcE = BitcoinExchange("data.csv");}
    catch (std::exception &e) { std::cout << e.what() << std::endl; return (1);}

    //checking if first line is correct and skipping it
    std::getline(file, line);
    if (line != "date | value")
    {
        std::cout << "\033[31mError: \033[0m" << line << ": Wrong Format" << std::endl;
        return (false);
    }

    //looping through the input file and printing results
    while (std::getline(file, line))
    {
        if (CheckInputLine(line))
            btcE.getValue(line);
    }
    return (0);
}
