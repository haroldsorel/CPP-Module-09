/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haroldsorel <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 23:22:07 by haroldsorel       #+#    #+#             */
/*   Updated: 2025/04/08 23:22:08 by haroldsorel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

bool    isOperator(char c)
{
    if (c != '+' && c != '-' && c != '*' && c != '/')
        return (false);
    return (true);
}

bool    isValidInput(const std::string &op)
{
    if (op.length() < 1 || op[op.length() - 1] == ' ')
        return (false);
    for(size_t i = 0; i < op.length(); i++)
    {
        switch (i % 2)
        {
            case 0:
            {
                if (!std::isdigit(op[i]) && !isOperator(op[i]))
                    return (false);
                break;
            }
            case 1:
            {
                if (op[i] != ' ')
                    return (false);
            }
        }
    }
    return (true);
}

std::string trimmedStr(const std::string &op)
{
    std::string trimmedOp;

    for(size_t i = 0; i < op.length(); i++)
    {
        if(i % 2 == 0)
            trimmedOp.push_back(op[i]);
    }
    return (trimmedOp);
}

int main(int argc, char **argv)
{
    //check if there is an input
    if (argc != 2)
    {
        std::cerr << "Error: Enter a valid RPN" << std::endl;
        return (1);
    }

    //check if the input format is correct i.e operator/digit followed by a space ect...
    std::string op = argv[1];
    if (!isValidInput(op))
    {
        std::cerr << "Error: Enter a valid RPN Format" << std::endl;
        return (1);
    }

    //trimming the spaces so it is easier to iterate through the string
    op = trimmedStr(op);


    //computing the result if the operation is valid
    RPN rpn;
    try
    {
        int result = rpn.eval(op);
        std::cout << result << std::endl;
    }
    catch (std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }
    return (0);
}
