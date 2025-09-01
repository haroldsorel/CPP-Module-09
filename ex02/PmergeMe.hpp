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
#include <list>
#include <cstdlib>
#include <climits>
#include <utility>
#include <algorithm>
#include <ctime>

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
std::ostream& operator<<(std::ostream& os, const std::deque<T> &deq)
{
    typename std::deque<T>::const_iterator it;

    for (it = deq.begin(); it != deq.end(); ++it)
    {
        os << *it;
        if (it + 1 != deq.end())
            os << " ";
    }
    return os;
}

template <typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<std::pair<T, T> > &pairs)
{
    for (size_t i = 0; i < pairs.size(); i++)
    {
        os << "("<< pairs[i].first << ", " << pairs[i].second << ")";
        if (i < pairs.size() - 1)
            os << " ";
    }
    return os;
}

class PmergeMe
{
    private:
        std::vector<int>    _Uvec;
        std::deque<int>     _Udeq;
        std::vector<int>    _Svec;
        std::deque<int>     _Sdeq;
        double              _time_to_sort_vec;
        double              _time_to_sort_deq;
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

std::vector<std::pair<int, int> > mergeSort(std::vector<std::pair<int, int> > &vec);
std::vector<std::pair<int, int> > make_pairs(std::vector<int> &vec);
std::vector<int> insert(std::vector<std::pair<int, int> > pairs, int remainer);

std::deque<std::pair<int, int> > mergeSort(std::deque<std::pair<int, int> > &vec);
std::deque<std::pair<int, int> > make_pairs(std::deque<int> &vec);
std::deque<int> insert(std::deque<std::pair<int, int> > pairs, int remainer);
