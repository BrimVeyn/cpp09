/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvan-pae <bryan.vanpaemel@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 10:19:36 by bvan-pae          #+#    #+#             */
/*   Updated: 2024/04/25 15:06:51 by bvan-pae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"
#include <cctype>

RPN::RPN() {
	return ;
}

RPN::~RPN() {
	return ;
}

RPN::RPN(const RPN & other) {
	(void) other;
	return ;
}

RPN &RPN::operator=(const RPN & other) {
	(void) other;
	return *this;
}

bool RPN::isWhiteSpace(char c)
{
	return ((c >= 9 && c <= 13) || c == 32);
}

int RPN::isop(int c) {
	if (c == '+') return 1;
	if (c == '-') return 2;
	if (c == '*') return 3;
	if (c == '/') return 4;
	return 0;
}

void RPN::compute(char *expression) {

	std::string ex = expression;

	for (size_t i = 0; i < ex.size(); i++)
	{
		if (std::isdigit(ex[i]))
			this->_data.push((ex[i] - 48));
		else if (RPN::isop(ex[i]))
		{
			if (this->_data.size() < 2)
				throw InvalidSyntax();
			float ope2 = this->_data.top();
			this->_data.pop();
			float ope1 = this->_data.top();
			this->_data.pop();
			switch (RPN::isop(ex[i])) {
				case 1:
					this->_data.push(ope1 + ope2);
					break;
				case 2:
					this->_data.push(ope1 - ope2);
					break;
				case 3:
					this->_data.push(ope1 * ope2);
					break;
				case 4:
					this->_data.push(ope1 / ope2);
					break;
				default:
					break;
				}
		}
		else if (RPN::isWhiteSpace(ex[i]) == false)
			throw InvalidSyntax();
	}
	
	for (; this->_data.size();)
	{
		std::cout << this->_data.top();
		this->_data.pop();
		std::cout << " ";
	}
	std::cout << std::endl;
	return ;
}
