/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sortDeq_utils.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsorel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 19:10:17 by hsorel            #+#    #+#             */
/*   Updated: 2025/09/01 19:10:19 by hsorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

std::deque<std::pair<int, int> > merge(std::deque<std::pair<int, int> > v1, std::deque<std::pair<int, int> > v2)
{
    size_t i = 0;
    size_t j = 0;

    std::deque<std::pair<int, int> > sorted;
    //std::cout << "merging : " << v1 << " and " << v2;
    while (i < v1.size() && j < v2.size())
    {
        if (v1[i] < v2[j])
        {
            sorted.push_back(v1[i]);
            i++;
        }
        else
        {
            sorted.push_back(v2[j]);
            j++;
        }
    }
    while (i < v1.size())
    {
        sorted.push_back(v1[i]);
        i++;
    }
    while (j < v2.size())
    {
        sorted.push_back(v2[j]);
        j++;
    }
    //std::cout << " result : " << sorted << std::endl;
    return (sorted);
}

std::deque<std::pair<int, int> > mergeSort(std::deque<std::pair<int, int> > &vec)
{
    if (vec.size() == 1)
        return vec;
    std::deque<std::pair<int, int> >::iterator half = vec.begin() + (vec.size() / 2);
    std::deque<std::pair<int, int> > v1(vec.begin(), half);
    std::deque<std::pair<int, int> > v2(half, vec.end());
    //std::cout << v1 << std::endl;
    //std::cout << v2 << std::endl;
    return(merge(mergeSort(v1), mergeSort(v2)));
}

std::deque<int> jacobsthal_generator_deq(int size)
{
    int Jmin1 = 1;
    int Jmin2 = 0;
    int num = 1;
    std::deque<int> jacobsthal_numbers;

    //jacobsthal_numbers.push_back(Jmin2);
    //jacobsthal_numbers.push_back(Jmin1);
    while (num <= size)
    {
        num = Jmin1 + (2 * Jmin2);
        Jmin2 = Jmin1;
        Jmin1 = num;
        if (num <= size)
            jacobsthal_numbers.push_back(num);
    }
    return (jacobsthal_numbers);
}

std::deque<int> pend_insertion_order_deq(size_t size)
{
    std::deque<int> jacobsthal_numbers;
    std::deque<int> insertion_order;
    std::deque<int> pend_order;
    
    int milestone1 = 1;
    int milestone2;
    int inside;

    //hardcoding case 1 and 2
    insertion_order.push_back(1);
    if (size == 1)
        return (insertion_order);
    if (size == 2)
    {
        insertion_order.push_back(2);
        return (insertion_order);
    }
    //generating jacobthal's number
    jacobsthal_numbers = jacobsthal_generator_deq(size);
    std::cout << "jacobsthal number : " << jacobsthal_numbers << std::endl;
    //filling jacobsthal's numbers and backfilling between milestones 
    for (size_t i = 1; i < jacobsthal_numbers.size(); i++)
    {
        milestone2 = jacobsthal_numbers[i];
        insertion_order.push_back(milestone2);
        inside = milestone2 - 1;
        while (inside > milestone1)
        {
            insertion_order.push_back(inside);
            inside--;
        }
        milestone1 = milestone2;
    }
    //backfilling the rest if there is no next milestone
    for (int i = size; i > milestone2; i--)
        insertion_order.push_back(i);
    std::cout << "insertion order : " << insertion_order << std::endl;
    return (insertion_order);
}

std::deque<std::pair<int, int> > make_pairs(std::deque<int> &vec)
{
    size_t i;
    size_t j;
    std::deque<std::pair<int, int> > pairs;

    for (i = 0, j = i + 1; i < vec.size() && j < vec.size(); i+=2, j+=2)
    {
        int first = std::max(vec[i], vec[j]);
        int second = std::min(vec[i], vec[j]);
        pairs.push_back(std::make_pair(first, second));
    }
    return (pairs);
}

std::deque<int> insert(std::deque<std::pair<int, int> > pairs, int remainer)
{
    std::deque<int> main;
    std::deque<int> pend;
    std::deque<int> pend_order_index;

    //creates pend and main based on the pairs
    for (size_t i = 0; i < pairs.size(); i++)
    {
        main.push_back(pairs[i].first);
        pend.push_back(pairs[i].second);
    }
    //first element in pend is smaller than the first element main, 
    //we insert it in the ‘0’ index of S.
    main.insert(main.begin(), pend.front());
    pend.erase(pend.begin());
    std::cout << "main before : " << main << std::endl;
    std::cout << "pend before : " << pend << std::endl;
    if (pairs.size() != 1)
    {
        std::cout << "main after : " << main << std::endl;
        std::cout << "pend after : " << pend << std::endl;
        //we build a jacobsthal number deque based on the size of the pend.
        //this will be used to determine the pend insertion order
        pend_order_index = pend_insertion_order_deq(pend.size());
        std::cout << "pend order by index: " << pend_order_index << std::endl;
        //now that we have the insertion order i need to use the pairs again so i have the upperbounds
        //first i need to take off the first pair because i already inserted it
        pairs.erase(pairs.begin());
        std::deque<int>::iterator upper_limit;
        std::deque<int>::iterator insert_position;
        for (size_t i = 0; i < pend_order_index.size(); i++)
        {
            //isolate each pair. the big pair draws the line where you will be searching in the main to insert the small one
            int big = pairs[pend_order_index[i]].first;
            int small = pairs[pend_order_index[i]].second;
            //find the position of the upperbound in main
            upper_limit  = find(main.begin(), main.end(), big);
            //lower bound returns an iterator to the first value that is bigger or equal (in the range it is given)
            //returns begin()
            insert_position = std::lower_bound(main.begin(), upper_limit, small);
            main.insert(insert_position, small);
        }
    }
    //if there was a remainer. add it.
    if (remainer != -1)
    {
        std::deque<int>::iterator insert_position = std::lower_bound(main.begin(), main.end(), remainer);
        main.insert(insert_position, remainer);
    }
    return (main);
}
