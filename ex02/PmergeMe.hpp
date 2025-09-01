/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haroldsorel <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 23:26:43 by haroldsorel       #+#    #+#             */
/*   Updated: 2025/04/08 23:26:45 by haroldsorel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <vector>
#include <deque>
#include <cstdlib>

template <typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& vec)
{
    typename std::vector<T>::const_iterator it;

    for (it = vec.begin(); it != vec.end(); ++it)
    {
        os << *it;
        if (it + 1 != vec.end())
            os << " ";
    }
    return os;
}

template <typename T>
std::ostream& operator<<(std::ostream& os, const std::deque<T>& deq)
{
    typename std::deque<T>::const_iterator it;

    for (it = deq.begin(); it != deq.end(); ++it)
    {
        os << *it;
        if (std::next(it) != deq.end())
            os << " ";
    }
    return os;
}

template <typename T>
void    printC(T &c)
{
    typename T::iterator it;

    for (it = c.begin(); it != c.end(); it++)
    {
        if (it + 1 != c.end())
            std::cout << *it << " ";
    }
    std::cout << std::endl;
}

class PmergeMe
{
    private:
        std::vector<int>    _Uvec;
        std::deque<int>     _Udeq;
        std::vector<int>    _Svec;
        std::deque<int>     _Sdeq;
    public:
        PmergeMe();
        PmergeMe(char **argv);
        PmergeMe(const PmergeMe &src);

        ~PmergeMe();

        PmergeMe &operator=(const PmergeMe &src);

        void    sortVec();
        void    sortDeq();
        void    sortAll();
        void    printInfo()const;
};
