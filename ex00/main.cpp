/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvan-pae <bryan.vanpaemel@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 10:12:05 by bvan-pae          #+#    #+#             */
/*   Updated: 2024/04/25 08:52:23 by bvan-pae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"
#include <iostream>

int main(int ac, char *av[]) {
    char dataFileName[] = "./data/data.csv";

    if (ac != 2) {
        std::cerr << "Error: Usage: " << av[0] << " <input_file>" << std::endl;
        return 1;
    }

	BitcoinExchange btc;

	try {
		btc.loadDataBases(dataFileName, av[1]);
	} catch (std::exception & e) {
		std::cerr << e.what() << std::endl;
	}

    return 0;
}

