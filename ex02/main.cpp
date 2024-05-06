/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvan-pae <bryan.vanpaemel@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 10:21:32 by bvan-pae          #+#    #+#             */
/*   Updated: 2024/05/06 13:13:23 by bvan-pae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"
#include <cctype>
#include <sys/time.h>

static bool isValid(std::string str) {
	for (size_t i = 0; i < str.size(); i++)
		if (!std::isdigit(str[i]))
			return false;
	return true;
}

int main(int ac, char *av[])
{
	if (ac < 2)
	{
		std::cerr << "Error: usage: " << av[0] << " {positive integer sequence}" << std::endl;
		return (1);
	}

	for (int i = 1; i < ac; i++)
    {
		if (isValid(std::string(av[i])) == false)
        {
			std::cerr << "Error: invalid argument: not a number" << std::endl;	
			return (1);
        }
		else if (std::atoi(av[i]) < 0)
        {
			std::cerr << "Error: invalid argument: only positive number are allowed"<< std::endl;	
			return (1);
        }
    }
	for (int i = 1; i < ac; i++) {
		for (int j = 1; j < ac; j++ ) {
			if (i != j && std::atoi(av[i]) == std::atoi(av[j]))
            {
				std::cerr << "Error: invalid argument: you entered the same number twice" << std::endl;
				return (1);
            }
		}
    }
	struct timeval start,end;
	//
	gettimeofday(&start, NULL);

	PmergeMe<std::list> l_sort(ac, av);

	l_sort.display('B');
	l_sort.FordJohnson();
	l_sort.display('A');

	gettimeofday(&end, NULL);
	double elapsed_time_us = (end.tv_sec - start.tv_sec) * 1000000.0 + (end.tv_usec - start.tv_usec);
	std::cout << "Time to process a range of " << ac - 1 << " elements with std::list : " << elapsed_time_us << " µs" <<  std::endl;

	gettimeofday(&start, NULL);

	PmergeMe<std::deque> dq_sort(ac, av);

	dq_sort.FordJohnson();

	gettimeofday(&end, NULL);
	elapsed_time_us = (end.tv_sec - start.tv_sec) * 1000000.0 + (end.tv_usec - start.tv_usec);
	std::cout << "Time to process a range of " << ac - 1 << " elements with std::deque : " << elapsed_time_us << " µs" <<  std::endl;

	gettimeofday(&start, NULL);

	PmergeMe<std::vector> vect_sort(ac, av);

	vect_sort.FordJohnson();

	gettimeofday(&end, NULL);
	elapsed_time_us = (end.tv_sec - start.tv_sec) * 1000000.0 + (end.tv_usec - start.tv_usec);
	std::cout << "Time to process a range of " << ac - 1 << " elements with std::vector : " << elapsed_time_us << " µs" <<  std::endl;

	gettimeofday(&start, NULL);

}
