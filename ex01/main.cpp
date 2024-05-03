/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvan-pae <bryan.vanpaemel@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 10:12:29 by bvan-pae          #+#    #+#             */
/*   Updated: 2024/04/25 15:06:54 by bvan-pae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

int main(int ac, char *av[])
{

	if (ac != 2)
	{
		std::cerr << "Error: usage " << av[0] << " {RPN expression}" << std::endl;
		return (1);
	}

	RPN solver;
	try {
	solver.compute(av[1]);
	} catch (std::exception &e ) {
		std::cerr << e.what() << std::endl;
	}
}
