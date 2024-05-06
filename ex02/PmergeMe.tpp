/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.tpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvan-pae <bryan.vanpaemel@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 13:18:35 by bvan-pae          #+#    #+#             */
/*   Updated: 2024/05/06 13:19:49 by bvan-pae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

template<template<typename, typename> class Cont>
template<typename Iterator, template<typename, typename> class Container>
void PmergeMe<Cont>::IteratorPairList<Iterator, Container>::addPair(Iterator begin, Iterator end) {
	this->pairs.push_back(std::pair<Iterator, Iterator> (begin,end));
}

template<template<typename, typename> class Cont>
template<typename Iterator, template<typename, typename> class Container>
std::size_t PmergeMe<Cont>::IteratorPairList<Iterator, Container>::size() {
	typename Container<std::pair<Iterator, Iterator>, std::allocator<int> >::iterator it = this->pairs.begin();
	std::size_t i = 0;
	for (; it != this->pairs.end(); it++, i++) ;
	return (i);
}

template<template<typename, typename> class Cont>
template<typename Iterator, template<typename, typename> class Container>
void PmergeMe<Cont>::IteratorPairList<Iterator, Container>::display() {
	int i = 1;
    if (!pairs.empty()) {
		
		typename Container<std::pair<Iterator, Iterator>, std::allocator<int> >::iterator end_it = this->pairs.end(); // Iterator to the element before the last one
		for (typename Container<std::pair<Iterator, Iterator>, std::allocator<int> >::iterator it = this->pairs.begin(); it != end_it; ++it, i++) {
            std::cout << "Pair " << i << ": (" << *(it->first) << ", " << *(it->second) << ")" << std::endl;
		}
    } else {
        std::cout << "Pairs list is empty." << std::endl;
    }
}

template<template<typename, typename> class Cont>
template<typename Iterator, template<typename, typename> class Container>
void PmergeMe<Cont>::IteratorPairList<Iterator, Container>::fillPairs(Container<int, std::allocator<int> > & container)
{
    typename Container<int, std::allocator<int> >::iterator end_it = container.end(); // Iterator to the last element
	--end_it; // Iterator to the element before the last one

	for (typename Container<int, std::allocator<int> >::iterator it = container.begin(); it != end_it; ++it) {
		typename Container<int, std::allocator<int> >::iterator next_it = it;
		++next_it;// Get iterator to the next element
		this->addPair(it, next_it); // Add pair of current element and next element
		if (++it == end_it)
			break;
	}
	if (container.size() % 2 == 1) {
		this->addPair(--container.end(), --container.end());
	}
}

template<template<typename, typename> class Cont>
template<typename Iterator, template<typename, typename> class Container>
void PmergeMe<Cont>::IteratorPairList<Iterator, Container>::swap(typename Container<std::pair<Iterator, Iterator>, std::allocator<int> >::iterator it,
															typename Container<std::pair<Iterator, Iterator>, std::allocator<int> >::iterator next_it) {
	if (*(it->first) > *(next_it->first) && *(it->first) != *(it->second)) {
		std::swap(it->first, next_it->first);
		std::swap(it->second, next_it->second);
	}
}

template<template<typename, typename> class Cont>
template<typename Iterator, template<typename, typename> class Container>
void PmergeMe<Cont>::IteratorPairList<Iterator, Container>::sortPairs() {
	typename Container<std::pair<Iterator, Iterator>, std::allocator<int> >::iterator it = this->pairs.begin();
	for (; it != this->pairs.end(); it++) {
		if (*(it->first) > *(it->second))
			std::swap(it->first, it->second);
	}
}

template<template<typename, typename> class Cont>
template<typename Iterator, template<typename, typename> class Container>
void PmergeMe<Cont>::IteratorPairList<Iterator, Container>::addToMainChain(Container<int, std::allocator<int> > & container) {
    typename Container<std::pair<Iterator, Iterator>, std::allocator<int> >::iterator it = this->pairs.begin();
    for (; it != this->pairs.end(); it++) {
        if (*(it->first) != *(it->second)) {
            int n = *(it->first);
            container.push_back(n);
        }
    }
}

template<template<typename, typename> class Cont>
template<typename Iterator, template<typename, typename> class Container>
void PmergeMe<Cont>::IteratorPairList<Iterator, Container>::insertionSort() {
	typename Container<std::pair<Iterator, Iterator>, std::allocator<int> >::iterator it = ++this->pairs.begin();
	typename Container<std::pair<Iterator, Iterator>, std::allocator<int> >::iterator last_it = this->pairs.end();
	for (int i = 1; it != last_it; it++, i++) {
		int j = i;
		typename Container<std::pair<Iterator, Iterator>, std::allocator<int> >::iterator j_it = it;
		typename Container<std::pair<Iterator, Iterator>, std::allocator<int> >::iterator j_m1_it = it;
		--j_m1_it;
		while (j > 0 && *(j_it->first) > *(j_m1_it->first))
		{
			this->swap(j_it, j_m1_it);
			j--;
			j_it--;
			j_m1_it--;
		}
	}
}

template<template<typename, typename> class Cont>
template<typename Iterator, template<typename, typename> class Container>
void PmergeMe<Cont>::IteratorPairList<Iterator, Container>::insert(Container<int, std::allocator<int> > & container, int n) {
	typename Container<std::pair<Iterator, Iterator>, std::allocator<int> >::iterator it = this->pairs.begin();
	std::advance(it, n - 1);
    typename Container<int, std::allocator<int> >::iterator itl = container.begin(); // Fix here

	for (; itl != container.end(); itl++) {
		if (*(it->second) > *itl) {
			container.insert(itl, *(it->second));
			return ;
        }
	}
	container.insert(container.end(), *(it->second));
}

template<template<typename, typename> class Cont>
template<typename Iterator, template<typename, typename> class Container>
void PmergeMe<Cont>::IteratorPairList<Iterator, Container>::binarySearch(Container<int, std::allocator<int> > & container, int n) {
    typename Container<std::pair<Iterator, Iterator>, std::allocator<int> >::iterator it = this->pairs.begin();
    std::advance(it, n - 1);

    typename Container<int, std::allocator<int> >::iterator itj = container.begin();
    std::size_t i = 0;

    while (itj != container.end() && *itj != *(it->first)) {
        ++itj;
        ++i;
    }

    int l = 0;
    int r = i;

    while (l < r) {
        int m = (l + r) / 2;
        typename Container<int, std::allocator<int> >::iterator tc = container.begin();
        std::advance(tc, m);

        if (*(it->second) < *tc)
            l = m + 1;
        else
            r = m;
    }

    typename Container<int, std::allocator<int> >::iterator tc = container.begin();
    std::advance(tc, l);

    container.insert(tc, *(it->second));
}

template<template<typename, typename> class Cont>
PmergeMe<Cont>::~PmergeMe() {
	return ;
}

template<template<typename, typename> class Cont>
PmergeMe<Cont>::PmergeMe() {
	return ;
}

template<template<typename, typename> class Cont>
PmergeMe<Cont>::PmergeMe(int ac , char *av[]) {
	for (int i = 1; i < ac; i++) {
		this->data.push_back(std::atoi(av[i]));
	}
	return ;
}

template<template<typename, typename> class Cont>
void	PmergeMe<Cont>::display(Cont<int, std::allocator<int> > & container, char mode) {
	if (mode == 'B') {
		std::cout << "Before : ";
		for (typename Cont<int, std::allocator<int> >::iterator it = container.begin(); it != container.end(); it++) {
			std::cout << *(it) << " ";
		}
		std::cout << std::endl;
	}
	else if (mode == 'A') {
		std::cout << "After : ";
		for (typename Cont<int, std::allocator<int> >::iterator it = --container.end(); it != container.begin(); it--) {
			std::cout << *(it) << " ";
		}
		std::cout << *(this->data.begin());
		std::cout << std::endl;
	}
}

template<template<typename, typename> class Cont>
void	PmergeMe<Cont>::display(char mode) {
	if (mode == 'B') {
		std::cout << "Before : ";
		for (typename Cont<int, std::allocator<int> >::iterator it = this->data.begin(); it != this->data.end(); it++) {
			std::cout << *(it) << " ";
		}
		std::cout << std::endl;
	}
	else if (mode == 'A') {
		std::cout << "After : ";
		for (typename Cont<int, std::allocator<int> >::iterator it = --this->data.end(); it != this->data.begin(); it--) {
			std::cout << *(it) << " ";

		}
		std::cout << *(this->data.begin());
		std::cout << std::endl;
	}
}

template<template<typename, typename> class Cont>
void PmergeMe<Cont>::FordJohnson() {
    // Assuming you have already created an instance of PmergeMe and data is populated
    IteratorPairList<typename Cont<int, std::allocator<int> >::iterator, Cont> pair_list;

	pair_list.fillPairs(this->data);
	pair_list.sortPairs();
	pair_list.insertionSort();

	Cont<int, std::allocator<int> > main_chain;
	pair_list.addToMainChain(main_chain);

	const std::size_t JacobsthalSequence[] = { 1, 3, 4, 11, 21, 43, 85, 171, 341, 683, 1365, 2731, 5461, 10923, 21845, 43691, 87381, 174763 };

	std::size_t index = 1;
	std::size_t pair_size = pair_list.size();
	
	pair_list.insert(main_chain, 1);
	for (std::size_t pushed = 0; pushed < pair_size - 1;) {

		std::size_t JNumber = JacobsthalSequence[index];
		std::size_t JNumber_m_1 = JacobsthalSequence[index - 1];

		if (JNumber > pair_size)
				JNumber = pair_size;
		while (JNumber > JNumber_m_1)
        {
			// pair_list.insert(main_chain, JNumber--);
			pair_list.binarySearch(main_chain, JNumber--);
			pushed++;
        }
		index++;
	}
	this->data = main_chain;
}
