/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haroldsorel <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 23:25:42 by haroldsorel       #+#    #+#             */
/*   Updated: 2025/04/08 23:25:43 by haroldsorel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

RPN::RPN()
{
}

RPN::RPN(const RPN &src) : _stack(src._stack)
{
}

RPN::~RPN()
{
}

RPN &RPN::operator=(const RPN &src)
{
    if (this != &src)
    {
        this->_stack = src._stack;
    }
    return (*this);
}

void RPN::printFifo()
{
    std::stack<int> buffer;

    buffer = this->_stack;
    while (!buffer.empty())
    {
        std::cout << buffer.top() << " ";
        buffer.pop();
    }
    std::cout << std::endl;
}

void RPN::printLifo()
{
    std::stack<int> buffer;
    std::stack<int> invert;

    buffer = this->_stack;
    while (!buffer.empty())
    {
        invert.push(buffer.top());
        buffer.pop();
    }
    while (!invert.empty())
    {
        std::cout << invert.top() << " ";
        invert.pop();
    }
    std::cout << std::endl;
}

int operation(int first, int second, char c)
{
    long    res;

    switch (c)
    {
        case '+':
        {
            res = second + first;
            break;
        }
        case '-':
        {
            res = second - first;
            break;
        }
        case '*':
        {
            res = second * first;
             break;
        }
        case '/':
        {
            if (first == 0)
                throw RPN::DivisionByZero();
            res = second / first;
            break;
        }
    }
    if (res > INT_MAX || res < INT_MIN)
        throw RPN::IntegerOverflow();
    return (static_cast<int>(res));
}

int RPN::eval(std::string &op)
{
    int firstPopped;
    int secondPopped;

    size_t i = 0;

    for (; i < op.length(); i++)
    {

        //if it is a digit put it in the stack, waiting for an operater
        if (isdigit(op[i]))
            (this->_stack).push(op[i] - '0');
        else
        {
            //if we have an operator but no operands, there is not enough operands
            if ((this->_stack).empty())
                throw (NotEnoughOperands());

            //popping fist member of the stack to perform the operation
            firstPopped = (this->_stack).top();
            (this->_stack).pop();

            //if we have an operator but only one operand there is not enough operands 
            if ((this->_stack).empty())
                throw (NotEnoughOperands());

            //popping second member of the stack to perform the operation 
            secondPopped = (this->_stack).top();
            (this->_stack).pop();

            try
            {
                //this can fail only if there is a division by zero or an int overflow
                //puts the result back into the stack to execute the next operation
                //because of stack this will be the first one popped (LiLFo, FiLo)
                (this->_stack).push(operation(firstPopped, secondPopped, op[i]));
            }
            catch (std::exception &e) { throw;}
        }
    }
    //Now that the loop is finished there should be only one number remaining which is the result of the operation
    //if NOT there is not enough operators to complete the operation. Throws an error.
    if (i == 1 || (this->_stack).size() > 1)
        throw (NotEnoughOperators());

    return ((this->_stack).top());
}
