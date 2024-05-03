/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvan-pae <bryan.vanpaemel@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 10:34:41 by bvan-pae          #+#    #+#             */
/*   Updated: 2024/05/02 09:25:49 by bvan-pae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

template<typename Iterator>
void PmergeMe::IteratorPairList<Iterator>::addPair(Iterator begin, Iterator end) {
	this->pairs.push_back(std::pair<Iterator, Iterator> (begin,end));
}

template<typename Iterator>
std::size_t PmergeMe::IteratorPairList<Iterator>::size() {
	typename std::list<std::pair<Iterator, Iterator> >::iterator it = this->pairs.begin();
	std::size_t i = 0;
	for (; it != this->pairs.end(); it++, i++) ;
	return (i);
}

template<typename Iterator>
std::list<std::pair<Iterator, Iterator> > &PmergeMe::IteratorPairList<Iterator>::getPairList() {
	return this->pairs;
}

template<typename Iterator>
void PmergeMe::IteratorPairList<Iterator>::display() {
	int i = 1;
    if (!pairs.empty()) {
		
		typename std::list<std::pair<Iterator, Iterator> >::iterator end_it = this->pairs.end(); // Iterator to the element before the last one

		for (typename std::list<std::pair<Iterator, Iterator> >::iterator it = this->pairs.begin(); it != end_it; ++it, i++) {

            std::cout << "Pair " << i << ": (" << *(it->first) << ", " << *(it->second) << ")" << std::endl;
			// std::cout << "Pair: (" << it << ", " << *it << ")" << std::endl;
		}
    } else {
        std::cout << "Pairs list is empty." << std::endl;
    }
}

template<typename Iterator>
void PmergeMe::IteratorPairList<Iterator>::swap(typename std::list<std::pair<Iterator, Iterator> >::iterator it,
															typename std::list<std::pair<Iterator, Iterator> >::iterator next_it) {
	if (*(it->first) > *(next_it->first) && *(it->first) != *(it->second)) {
		std::swap(it->first, next_it->first);
		std::swap(it->second, next_it->second);
	}
}

template<typename Iterator>
void PmergeMe::IteratorPairList<Iterator>::sortPairs() {
	typename std::list<std::pair<Iterator, Iterator> >::iterator it = this->pairs.begin();
	for (; it != this->pairs.end(); it++) {
		if (*(it->first) > *(it->second))
			std::swap(it->first, it->second);
	}
}

template<typename Iterator>
void PmergeMe::IteratorPairList<Iterator>::addToMainChain(std::list<int> & list) {
	typename std::list<std::pair<Iterator, Iterator> >::iterator it = this->pairs.begin();
	for (; it != this->pairs.end(); it++)
	{
		// std::cout << *(it->first) << " " << *(it->second) << std::endl;
		if (*(it->first) != *(it->second))
        {
			int n = *(it->first);
			list.push_back(n);
        }
	}
}

template<typename Iterator>
void PmergeMe::IteratorPairList<Iterator>::insertionSort() {
	typename std::list<std::pair<Iterator, Iterator> >::iterator it = ++this->pairs.begin();
	typename std::list<std::pair<Iterator, Iterator> >::iterator last_it = this->pairs.end();
	for (int i = 1; it != last_it; it++, i++) {
		int j = i;
		typename std::list<std::pair<Iterator, Iterator> >::iterator j_it = it;
		typename std::list<std::pair<Iterator, Iterator> >::iterator j_m1_it = it;
		--j_m1_it;
		// std::cout << "l[j] value = " << *(j_it->first) << " l[j -1] value = " << *(j_m1_it->first) << std::endl;
		while (j > 0 && *(j_it->first) > *(j_m1_it->first))
		{
			this->swap(j_it, j_m1_it);
			j--;
			j_it--;
			j_m1_it--;
		}
	}

}

PmergeMe::~PmergeMe() {
	return ;
}

PmergeMe::PmergeMe() {
	return ;
}

template<typename T>
void PmergeMe::display(T &c, char mode) {
	if (mode == 'B')
    {
		std::cout << "Before : ";
		for (typename T::iterator it = c.begin(); it != c.end(); it++) {
			std::cout << *it << " ";
		}
    }
	else if (mode == 'A')
    {
		std::cout << "After : ";
		for (typename T::iterator it = --c.end(); ; it--) {
			std::cout << *it << " ";
			if (it == c.begin())
				break;
		}
    }
	std::cout << std::endl;
}

PmergeMe::PmergeMe(int ac , char *av[], char mode) {
	if (mode != 'L' && mode != 'Q')
		throw UnknownMode();
	for (int i = 1; i < ac; i++) {
		if (mode == 'L')
			this->l.push_back(std::atoi(av[i]));
		if (mode == 'Q')
			this->dq.push_back(std::atoi(av[i]));
	}
	return ;
}

template<typename Iterator>
void PmergeMe::IteratorPairList<Iterator>::insertList(std::list<int> &list, int n) {
	typename std::list<std::pair<Iterator, Iterator> >::iterator it = this->pairs.begin();
	std::advance(it, n - 1);
	std::list<int>::iterator itl = list.begin();

	for (; itl != list.end(); itl++) {
		if (*(it->second) > *itl) {
			list.insert(itl, *(it->second));
			return ;
        }
	}
	list.insert(list.end(), *(it->second));
}

void PmergeMe::mergeInsertionSortDeque() {
	if (this->dq.empty())
		throw WrongAlgorithm();
	return ;
}

void PmergeMe::mergeInsertionSortList() {
	if (this->l.empty())
		throw WrongAlgorithm();
	
	// this->display(this->l, 'B');
	//Create a list of pair of iterators 
    IteratorPairList<std::list<int>::iterator> pair_list;

    std::list<int>::iterator end_it = this->l.end(); // Iterator to the last element

	--end_it; // Iterator to the element before the last one

	for (std::list<int>::iterator it = this->l.begin(); it != end_it; ++it) {
		std::list<int>::iterator next_it = it;
		++next_it;// Get iterator to the next element
		pair_list.addPair(it, next_it); // Add pair of current element and next element
		if (++it == end_it)
			break;
	}
	if (this->l.size() % 2 == 1) {
		pair_list.addPair(--this->l.end(), --this->l.end());
	}
	
	// std::cout << "------- Origin pair list -------" << std::endl;
 //    pair_list.display();
	// std::cout << "--------------------------------" << std::endl;

	//Sort each pair
	pair_list.sortPairs();

	//Insertion sort on pair list
	pair_list.insertionSort();

	//Display sorted pairs by a
	// std::cout << "------- Sorted pair list -------" << std::endl;
 //    pair_list.display();
	// std::cout << "--------------------------------" << std::endl;


	//Create main chain
	std::list<int> main_chain;
	pair_list.addToMainChain(main_chain);
	// this->display(main_chain, 'A');

	//Insert following jacobstal sequence
	std::size_t JacobsthalSequence[] = { 1, 3, 4, 11, 21, 43, 85, 171, 341, 683, 1365, 2731, 5461, 10923, 21845, 43691, 87381, 174763 };
	std::size_t index = 1;
	std::size_t pair_size = pair_list.size();
	
	pair_list.insertList(main_chain, 1);
	for (std::size_t pushed = 0; pushed < pair_size - 1;) {
		std::size_t JNumber = JacobsthalSequence[index];
		std::size_t JNumber_m_1 = JacobsthalSequence[index - 1];
		while (JNumber > pair_size)
				JNumber = pair_size;
		// std::cout << "JNumber : " << JNumber << " JNumber_m_1 : " << JNumber_m_1 << std::endl;
		while (JNumber > JNumber_m_1)
        {
			// std::cout << "To_push = " << JNumber << std::endl;
			pair_list.insertList(main_chain, JNumber--);
			pushed++;
        }
		index++;
	}

	// this->display(main_chain, 'A');
	// std::cout << "main chain size : " << main_chain.size() << std::endl;
}

PmergeMe::PmergeMe(const PmergeMe & other) {
	(void) other;
	return ;
}

PmergeMe &PmergeMe::operator=(const PmergeMe & other) {
	(void) other;
	return *this;
}

// void init	return ;();
