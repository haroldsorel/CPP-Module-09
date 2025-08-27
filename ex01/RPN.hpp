/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haroldsorel <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 23:25:30 by haroldsorel       #+#    #+#             */
/*   Updated: 2025/04/08 23:25:31 by haroldsorel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <stack>
#include <climits>

class RPN
{
    private:
        std::stack<int> _stack;
    public:
        RPN();
        RPN(const RPN &src);
        ~RPN();
        RPN &operator=(const RPN &src);

        void    printFifo();
        void    printLifo();
        void    printRes(std::string &op);
        int     eval(std::string &op);

        class NotEnoughOperands : public std::exception
        {
            public:
                virtual const char *what() const throw()
                {
                    return ("Error: Not Enough Operands");
                }
        };
        class NotEnoughOperators : public std::exception
        {
            public:
                virtual const char *what() const throw()
                {
                    return ("Error: Not Enough Operators");
                }
        };
        class DivisionByZero : public std::exception
        {
            public:
                virtual const char *what() const throw()
                {
                    return ("Error: Division By Zero");
                }
        };
        class IntegerOverflow : public std::exception
        {
            public:
                virtual const char *what() const throw()
                {
                    return ("Error: Integer Overflow");
                }
        };
};

bool    isOperator(char c);