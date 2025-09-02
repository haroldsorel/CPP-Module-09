/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sortVec_utils.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsorel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 19:10:05 by hsorel            #+#    #+#             */
/*   Updated: 2025/09/01 19:10:06 by hsorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

static std::vector<std::pair<int, int> > merge(std::vector<std::pair<int, int> > v1, std::vector<std::pair<int, int> > v2)
{
    size_t i = 0;
    size_t j = 0;

    std::vector<std::pair<int, int> > sorted;
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

std::vector<std::pair<int, int> > mergeSort(std::vector<std::pair<int, int> > &vec)
{
    if (vec.size() == 1)
        return vec;
    std::vector<std::pair<int, int> >::iterator half = vec.begin() + (vec.size() / 2);
    std::vector<std::pair<int, int> > v1(vec.begin(), half);
    std::vector<std::pair<int, int> > v2(half, vec.end());
    //std::cout << v1 << std::endl;
    //std::cout << v2 << std::endl;
    return(merge(mergeSort(v1), mergeSort(v2)));
}

static std::vector<int> jacobsthal_generator(int size)
{
    int Jmin1 = 1;
    int Jmin2 = 0;
    int num = 1;
    std::vector<int> jacobsthal_numbers;

    //jacobsthal_numbers.push_back(Jmin2);
    //jacobsthal_numbers.push_back(Jmin1);
    if (size == 1)
    {
        jacobsthal_numbers.push_back(1);
        return (jacobsthal_numbers);
    }
    if (size == 2)
    {

    }
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

static std::vector<int> pend_insertion_order(size_t size)
{
    std::vector<int> jacobsthal_numbers;
    std::vector<int> insertion_order;
    std::vector<int> pend_order;
    
    int milestone1 = 1;
    int milestone2;
    int inside;

    //hardcoding case 1 and 2
    insertion_order.push_back(0);
    if (size == 1)
        return (insertion_order);
    if (size == 2)
    {
        insertion_order.push_back(1);
        return (insertion_order);
    }
    //generating jacobthal's number
    jacobsthal_numbers = jacobsthal_generator(size);
    //std::cout << "jacobsthal number : " << jacobsthal_numbers << std::endl;
    //filling jacobsthal's numbers and backfilling between milestones 
    for (size_t i = 1; i < jacobsthal_numbers.size(); i++)
    {
        milestone2 = jacobsthal_numbers[i];
        insertion_order.push_back(milestone2 - 1);
        inside = milestone2 - 1;
        while (inside > milestone1)
        {
            insertion_order.push_back(inside - 1);
            inside--;
        }
        milestone1 = milestone2;
    }
    //backfilling the rest if there is no next milestone
    for (int i = size; i > milestone2; i--)
        insertion_order.push_back(i - 1);
    return (insertion_order);
}

std::vector<std::pair<int, int> > make_pairs(std::vector<int> &vec)
{
    size_t i;
    size_t j;
    std::vector<std::pair<int, int> > pairs;

    for (i = 0, j = i + 1; i < vec.size() && j < vec.size(); i+=2, j+=2)
    {
        int first = std::max(vec[i], vec[j]);
        int second = std::min(vec[i], vec[j]);
        pairs.push_back(std::make_pair(first, second));
    }
    return (pairs);
}

std::vector<int> insert(std::vector<std::pair<int, int> > pairs, int remainer)
{
    std::vector<int> main;
    std::vector<int> pend;
    std::vector<int> pend_order_index;

    //creates pend and main based on the pairs
    for (size_t i = 0; i < pairs.size(); i++)
    {
        main.push_back(pairs[i].first);
        pend.push_back(pairs[i].second);
    }
    //first element in pend is smaller than the first element main, 
    //we insert it in the ‘0’ index of S.
    //std::cout << "main : " << main << std::endl;
    //std::cout << "pend : " << pend << std::endl;
    main.insert(main.begin(), pend.front());
    pend.erase(pend.begin());
    //std::cout << "main after : " << main << std::endl;
    //std::cout << "pend after : " << pend << std::endl;
    if (pairs.size() != 1)
    {
        //we build a jacobsthal number vector based on the size of the pend.
        //this will be used to determine the pend insertion order
        pend_order_index = pend_insertion_order(pend.size());
        //now that we have the insertion order i need to use the pairs again so i have the upperbounds
        //first i need to take off the first pair because i already inserted it
        pairs.erase(pairs.begin());
        std::vector<int>::iterator upper_limit;
        std::vector<int>::iterator insert_position;
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
        std::vector<int>::iterator insert_position = std::lower_bound(main.begin(), main.end(), remainer);
        main.insert(insert_position, remainer);
    }
    return (main);
}