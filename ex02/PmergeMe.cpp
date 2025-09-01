/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haroldsorel <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 23:26:49 by haroldsorel       #+#    #+#             */
/*   Updated: 2025/04/08 23:26:50 by haroldsorel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

template <typename Container>
Container argv2container(char **argv)
{
    int i = 0;
    int num;
    Container c;

    while (argv[i])
    {
        num = std::atol(argv[i]);
        c.push_back(num);
        i++;
    }
    return (c);
}

PmergeMe::PmergeMe()
{

}

PmergeMe::PmergeMe(char **input)
{
    this->_Uvec = argv2container<std::vector<int> >(input);
    this->_Udeq = argv2container<std::deque<int> >(input);
}

PmergeMe::PmergeMe(const PmergeMe &src) : _Uvec(src._Uvec), _Udeq(src._Udeq), _Svec(src._Svec), _Sdeq(src._Udeq)
{

}

PmergeMe::~PmergeMe()
{
}

PmergeMe &PmergeMe::operator=(const PmergeMe &src)
{
    if (this != &src)
    {
        this->_Uvec = src._Uvec;
        this->_Udeq = src._Udeq;
        this->_Svec = src._Svec;
        this->_Sdeq = src._Sdeq;
    }
    return (*this);
}

std::vector<int> merge(std::vector<int> v1, std::vector<int> v2)
{
    size_t i = 0;
    size_t j = 0;

    std::vector<int> sorted;
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

std::vector<int> mergeSort(std::vector<int> &vec)
{
    if (vec.size() == 1)
        return vec;
    std::vector<int>::iterator half = vec.begin() + (vec.size() / 2);
    std::vector<int> v1(vec.begin(), half);
    std::vector<int> v2(half, vec.end());
    //std::cout << v1 << std::endl;
    //std::cout << v2 << std::endl;
    return(merge(mergeSort(v1), mergeSort(v2)));
}

std::vector<int> jacobsthal_generator(int size)
{
    int Jmin1 = 1;
    int Jmin2 = 0;
    int num = 1;
    std::vector<int> jacobsthal_numbers;

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

std::vector<int> pend_insertion_order(size_t size, std::vector<int> smalls)
{
    std::vector<int> jacobsthal_numbers;
    std::vector<int> insertion_order;
    std::vector<int> pend_order;
    
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

    jacobsthal_numbers = jacobsthal_generator(size);
    std::cout << "jacobsthal number : " << jacobsthal_numbers << std::endl;
    for (size_t i = 1; i < jacobsthal_numbers.size(); i++)
    {
        milestone2 = jacobsthal_numbers[i];
        insertion_order.push_back(milestone2);
        inside = milestone2 - 1; //amount of numbers to insert between milestones
        while (inside > milestone1)
        {
            insertion_order.push_back(inside); //backfilling from milestone2 to milestone1
            inside--;
        }
        milestone1 = milestone2;
    }

    //backfilling the rest 
    for (int i = size; i > milestone2; i--)
        insertion_order.push_back(i);
    std::cout << "insertion order : " << insertion_order << std::endl;

    //actually putting the smalls in that order
    for (size_t i = 0; i < size; i++)
    {
        pend_order.push_back(smalls[insertion_order[i] - 1]);
    }
    std::cout << "pend order : " << pend_order << std::endl;
    return (insertion_order);
}

void    insert(std::vector<int> main, std::vector<int> pend, std::vector<int> bigs, int remainer)
{
    //To Do
}

void    PmergeMe::sortVec()
{
    std::cout << "SORTING VECTOR..."<< std::endl;

    //do not sort if there is only one number
    if (this->_Uvec.size() <= 1)
    {
        //time
        return ; 
    }

    //STEP ONE : Making pairs and sorting them
    //Pairs are in 2 different containers but are linked by index, maintaining relationship
    std::vector<int>            bigs;
    std::vector<int>            smalls;
    size_t i, j;
    int remainer = -1;

    for (i = 0, j = i + 1; i < this->_Uvec.size() && j < this->_Uvec.size(); i+=2, j+=2)
    {
        bigs.push_back(std::max(this->_Uvec[i], this->_Uvec[j]));
        smalls.push_back(std::min(this->_Uvec[i], this->_Uvec[j]));
    }
    //if there is an uneven amount of numbers add the remaining in the smalls
    if (i < this->_Uvec.size())
        remainer = this->_Uvec[i];
    std::cout << "bigs : "<< bigs << std::endl;
    std::cout << "smalls : " << smalls << std::endl;

    //STEP TWO : Sorting the bigs using a recursive merge sort i can insert the smalls inside;
    std::vector<int>    main = mergeSort(bigs);

    //STEP THREE : determine the order of insertion of the pend
    //To Do -> pair it back with the bigs
    std::vector<int> pend = pend_insertion_order(smalls.size(), smalls);

    //STEP FOUR : insert pend numbers into main
    std::cout << "main before insertion : " << main << std::endl;
    insert(main, pend, bigs, remainer);
    std::cout << "main after insertion : " << main << std::endl;
    std::cout << "Oh damn it's sorted!" << main << std::endl;
    this->_Svec = main;
}


void    PmergeMe::sortDeq()
{
    std::cout << "SORTING DEQUE..."<< std::endl;
}

void    PmergeMe::sortAll()
{
    sortVec();
    sortDeq();
}

void    PmergeMe::printInfo()const
{
    std::cout << std::endl;
    std::cout << "Before : " << this->_Uvec << std::endl;
    std::cout << "After : " << this->_Svec << std::endl;
    //std::cout << "Time To Process a Range Of " << (this->_Uvec).size() << " elements with std::deque : " << this->_vecSortTime << std::endl;
    std::cout << "Before : " << this->_Udeq << std::endl;
    std::cout << "After : " << this->_Sdeq << std::endl;
    //std::cout << "Time To Process a Range Of " << (this->_Udeq).size() << " elements with std::deque : " << this->_deqSortTime << std::endl;
    std::cout << std::endl;
}
