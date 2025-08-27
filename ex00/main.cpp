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

bool    CheckInputLine(std::string &line);


void printRes(BitcoinExchange &be, std::fstream &file)
{
    std::string line; //buffer
    std::string date;
    float       num;

     //looping through the input file and printing results
    while (std::getline(file, line))
    {
        if (CheckInputLine(line))
        {
            date = line.substr(0, 10);
            num = std::atof(line.substr(13).c_str());
            be.getValue(date, num);
        }
    }
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
    std::fstream    file(argv[1]);
    std::string     line;
    BitcoinExchange btcE;
    if (!file.is_open())
    {
        std::cout << "Error: Could Not Open File." << std::endl;
        return (1);
    }
    //initializing BitcoinExchange object based on data.csv: fotmat (date, exchange rate)
    try
    {
        btcE = BitcoinExchange("data.csv");
    }
    catch (std::exception &e) { std::cout << e.what() << std::endl; return (1);}

    //checking if first line is correct and skipping it
    std::getline(file, line);
    if (line != "date | value")
    {
        std::cout << "\033[31mError: \033[0m" << line << ": Wrong Format" << std::endl;
        return (1);
    }
    printRes(btcE, file);
    return (0);
}
