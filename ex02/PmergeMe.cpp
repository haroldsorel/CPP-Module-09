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

std::vector<std::pair<int, int> > merge(std::vector<std::pair<int, int> > v1, std::vector<std::pair<int, int> > v2)
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

std::vector<int> pend_insertion_order(size_t size)
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
    //generating jacobthal's number
    jacobsthal_numbers = jacobsthal_generator(size);
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
    main.insert(main.begin(), pend.front());
    pend.erase(pend.begin());
    std::cout << "main : " << main << std::endl;
    std::cout << "pend : " << pend << std::endl;
    //we build a jacobsthal number vector based on the size of the pend.
    //this will be used to determine the pend insertion order
    pend_order_index = pend_insertion_order(pend.size());
    std::cout << "pend order by index: " << pend_order_index << std::endl;
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
    //if there was a remainer. add it.
    if (remainer != -1)
    {
        insert_position = std::lower_bound(main.begin(), main.end(), remainer);
        main.insert(insert_position, remainer);
    }
    return (main);
}

void    PmergeMe::sortVec()
{
    std::cout << "SORTING VECTOR..." << "\n" << std::endl;

    clock_t start = clock();
    //do not sort if there is only one number
    if (this->_Uvec.size() <= 1)
    {
        //time
        return ; 
    }

    //STEP ONE : Making pairs and sorting them
    //Pairs are in 2 different containers but are linked by index, maintaining relationship
    //Bigs will be sorted in order and smalls order will follow Jacobsthals number so we need to keep the pairs
    int remainer = -1;

    if (this->_Uvec.size() % 2 != 0)
        remainer = this->_Uvec.back();
    std::vector<std::pair<int, int> > pairs = make_pairs(this->_Uvec);

    std::cout << "pairs before sorting : " << pairs << std::endl;
    std::cout << "remainer : " << remainer << std::endl;

    //STEP TWO : Sorting the pairs by order of the biggest of each pair using a recursive merge;
    pairs = mergeSort(pairs);
    std::cout << "pairs after sorting : " << pairs << std::endl;


    //STEP THREE : Make a main vector and a pend vector. main has the sorted bigs and pens has the corresponding smalls.
    //insert the pend in the main in the order that is indicated by the corresponding Jacobsthal's number
    std::vector<int> main = insert(pairs, remainer);

    //time's up
    clock_t end = clock();
    std::cout << start << " -> " << end << std::endl;
    double elapsed_secs = double(end - start) / CLOCKS_PER_SEC;
    std::cout << elapsed_secs << std::endl;
    double elapsed_ms = elapsed_secs * 1000.0;
    std::cout << elapsed_ms << std::endl;
    
    //assigning values
    this->_time_to_sort_vec = elapsed_ms;
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
    std::cout << "Time To Process a Range Of " << (this->_Uvec).size() << " elements with std::vector : " << this->_time_to_sort_vec << std::endl;
    //std::cout << "Before : " << this->_Udeq << std::endl;
    //std::cout << "After : " << this->_Sdeq << std::endl;
    //std::cout << "Time To Process a Range Of " << (this->_Udeq).size() << " elements with std::deque : " << this->_time_to_sort_deq << std::endl;
    //std::cout << std::endl;
}
