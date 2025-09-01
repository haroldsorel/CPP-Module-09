/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haroldsorel <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 23:22:17 by haroldsorel       #+#    #+#             */
/*   Updated: 2025/04/08 23:22:18 by haroldsorel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

bool    isValidInput(char **argv)
{
    int i = 0;
    std::string buffer;

    while (argv[i])
    {
        buffer = argv[i];
        //check if it's empty
        if (buffer.empty())
        {
            std::cout << "There is an empty argument" << std::endl;
            return (false);
        }
        //check if there are other characters then digits
        if (buffer.find_first_not_of("0123456789") != std::string::npos)
        {
            std::cout << buffer << " : invalid character" << std::endl;
            return (false);
        }
        //killing leading zeroes
        for (std::string::iterator it = buffer.begin(); it != buffer.end() && *it == '0';)
            it = buffer.erase(it);
        //checking if it wasn't only zeroes
        if (buffer.empty())
            return (true);
        //checking if there are no overflows. One part to check Long overflow. one part to check int overflow
        if (buffer.length() > 10)
        {
            std::cout << buffer << " : overflowing(1)" << std::endl;
            return (false);
        }
        //the number safely goes in a long
        long l = std::atol(buffer.c_str());
        //checking fot in overflow
        if (l > INT_MAX)
        {
            std::cout << buffer <<" : overflowing(2)" << std::endl;
            return (false);
        }
        //string ok!:) to the next
        i++;
    }
    return (true);
}

int main(int argc, char **argv)
{   
    if (argc < 2 || !(isValidInput(++argv)))
    {
        std::cout << "Error : Enter a valid Positive Integer Sequence"<< std::endl;
        return (0);
    }
    PmergeMe pmm(argv);
    pmm.sortAll();
    pmm.printInfo();
    return (0);
}
