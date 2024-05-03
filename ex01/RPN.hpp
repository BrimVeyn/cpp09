/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvan-pae <bryan.vanpaemel@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 10:13:59 by bvan-pae          #+#    #+#             */
/*   Updated: 2024/04/25 14:37:17 by bvan-pae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RPN_H
# define RPN_H

#include <iostream>
#include <stack>

class RPN {
	public:
		RPN();
		~RPN();
		RPN(const RPN& other);
		RPN &operator=(const RPN& other);

		void compute(char *expression);
		static int isop(int c);
		static bool isWhiteSpace(char c);

	private:
		std::stack<float> _data;

	class InvalidSyntax : public std::exception {
	public:
		const char* what() const throw() {
			return "Error: invalid syntax";
		}
	};
};


#endif
