/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvan-pae <bryan.vanpaemel@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 10:29:24 by bvan-pae          #+#    #+#             */
/*   Updated: 2024/05/01 15:50:31 by bvan-pae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PMERGME_H
# define PMERGME_H
#include <iostream>
#include <deque>
#include <vector>
#include <list>
#include <map>
#include <cstdlib>
#include <utility>
#define nullptr 0

class PmergeMe {

	public:
		~PmergeMe();
		PmergeMe();
		PmergeMe(int ac, char *av[], char mode);
		PmergeMe(const PmergeMe & other);

		PmergeMe &operator=(const PmergeMe & other);

		template<typename Iterator>
		class IteratorPairList {
			public :
				IteratorPairList() {}

				void addPair(Iterator begin, Iterator end);
				void display();
				std::size_t size();
				void swap(typename std::list<std::pair<Iterator, Iterator> >::iterator it, typename std::list<std::pair<Iterator, Iterator> >::iterator next_it);
				void insertionSort();
				void sortPairs();
				std::list<std::pair<Iterator, Iterator> > &getPairList();
				void addToMainChain(std::list<int> & list);
				void insertList(std::list<int> &list, int n);
			private:
				std::list<std::pair<Iterator, Iterator> > pairs;
		};


		template<typename T>
		void display(T & c, char mode);

		void mergeInsertionSortDeque();
		void mergeInsertionSortList();

	private:
		std::list<int> l;
		std::deque<int> dq;

	class UnknownMode : public std::exception {
		public:
			virtual const char* what() const throw() {
			return "Error: mode is either L or Q {list or deque}";
		}
	};
	
	class WrongAlgorithm : public std::exception {
		public:
			virtual const char* what() const throw() {
			return "Error: wrong algorithm";
		}
	};


};

#endif
