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

std::vector<int> argvToIntVector(char **argv)
{
    int     i = 0;

    std::vector<int> vec;
    while (argv[i])
    {
        vec.push_back(std::atoi(argv[i]));
        i++;
    }
    return (vec);
}

std::deque<int> argvToIntDequeu(char **argv)
{
    int     i = 0;

    std::deque<int> deq;
    while (argv[i])
    {
        deq.push_back(std::atoi(argv[i]));
        i++;
    }
    return (deq);
}

bool    handleError(char **argv)
{
    int         i = 0;
    long        bufi;
    char        *end;
    std::string bufs;

    while (argv[i])
    {
        std::string bufs(argv[i]);

        if (bufs.empty())
        {
            std::cout << "Error: Empty argument" << std::endl;
            return false;
        }
        
        if(bufs.find_first_not_of("0123456789") != std::string::npos)
        {
            std::cout << "Error: Wrong number" << std::endl;
            return (false);
        }
        if (bufs.length() > 10)
        {
            std::cout << "Error: Integer overflow"<< std::endl;
            return (false);
        }
        bufi = atol(bufs.c_str());
        if (bufi > INT_MAX)
        {
            std::cout << "Error: Integer overflow" << std::endl;
            return (false);
        }
        i++;
    }
    return (true);
}

int main(int argc, char **argv)
{
    std::vector<int> vec;
    std::deque<int> deq;

    std::vector<int>::iterator itv;
    std::deque<int>::iterator itd;
    if (argc < 2)
    {
        std::cerr << "Error: Enter a Positive Integer Sequence" << std::endl;
        return (1);
    }
    argv++;
    if (!handleError(argv))
        return (1);
    vec = argvToIntVector(argv);
    deq = argvToIntDequeu(argv);
    for (itv = vec.begin(); itv != vec.end(); ++itv)
    {
        std::cout << *itv << " ";
    }
    std::cout << std::endl;
    for (itd = deq.begin(); itd != deq.end(); ++itd)
    {
        std::cout << *itd << " ";
    }
    std::cout << std::endl;
    return (0);
}
