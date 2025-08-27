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
#include <cstdlib>
#include <climits>
#include <vector>
#include <deque>
#include <list>

class PmergeMe
{
    private:
        double  _vec_sort_time;
        double  _deq_sort_time;

        std::vector<int>    _vec;
        std::deque<int>     _deq;
    public:

        //construtors
        PmergeMe();
        PmergeMe(char **list);
        PmergeMe(const PmergeMe &src);

        //destructors
        ~PmergeMe();

        //operator overloads
        PmergeMe& operator=(const PmergeMe& other);

        //getters
        double  get_vec_start_time()const;
        double  get_deq_start_time()const;

        //methods
        void    vec_sort();
        void    deq_sort();
        void    vec_print();
        void    deq_print();
        void    print_all();
};