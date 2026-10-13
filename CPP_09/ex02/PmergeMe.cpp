/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pswirgie <pswirgie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/19 16:44:29 by pswirgie          #+#    #+#             */
/*   Updated: 2026/10/13 08:54:42 by pswirgie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"
#include <sys/time.h>

PmergeMe::PmergeMe( void ){}

void	PmergeMe::_invalidArguement( void )
{
	std:: string	message("Invalid arguments, pattern required a unsorted"
		" positive integer sequence (at least 2 elements)"
		" separated by spaces: ./PmergeMe [numbers] [//] [//] ...");
	throw std::runtime_error(message);
}

size_t	PmergeMe::_nbGrp( size_t sizeArr, size_t sizeGrp )
{
	size_t res = ceil(static_cast<double>(sizeArr) / sizeGrp);
	return (res);
}

size_t	PmergeMe::_nbGrpStrict( size_t sizeArr, size_t sizeGrp )
{
	size_t res = floor(sizeArr / sizeGrp);
	return (res);
}

template <typename T>
void	PmergeMe::_printArrayJacobsthal( const T& suiteJaco )
{
	size_t i = 0;
	while (i < suiteJaco.size())
	{
		std::cout << std::setfill('0') << std::setw(2);
		std::cout << suiteJaco[i] << " ";
		++i;
	}
	std::cout << RESET << std::endl;
}

template <typename T>
bool	PmergeMe::_isSorted( const T& arr )
{
	if (arr.empty())
		return (false);
	for (size_t i = 0; i < arr.size(); ++i)
	{
		if (i + 1 < arr.size() && arr[i] > arr[i + 1])
			return (false);
	}
	return (true);
}

template <typename T>
void	PmergeMe::_initSuiteJacobsthal( T& arr )
{
	arr.push_back(1);
	arr.push_back(1);
}

/*
-> Return first index and calcul the next + 1
[0] = 1
[1] = 1
[n] = [n - 1] + 2*[n - 2]
Suite Jacobsthal : 1, 1, 3, 5, 11, 21, 43, 85, 171, 341
*/
template <typename T>
size_t	PmergeMe::_getSuiteJacobsthal( T& suiteJaco )
{
	size_t	index = suiteJaco.at(0);
	suiteJaco.push_back(suiteJaco.at(1) + (2*(suiteJaco.at(0))));
	suiteJaco.erase(suiteJaco.begin(), suiteJaco.begin() + 1);
	return (index);
}

template <typename T>
void	PmergeMe::_initLeftOvers( T& arrA, T& leftOver, size_t sizeGrp, size_t nbGrp )
{
	// There is a rest
	// Here It's the last grp, a incomplete loser/winner, size is < sizeGrp
	// Don' t misunderstood with a complete loser
	if (arrA.size() % sizeGrp != 0)
	{
		size_t start = sizeGrp * (nbGrp - 1);
		for (size_t i = start; i < arrA.size(); ++i)
			leftOver.push_back(arrA[i]);
		arrA.erase(arrA.begin() + start, arrA.end());
	}
}

template <typename T>
void	PmergeMe::_printArrBWithWinnerIndex( T& arrB, T& indexWinnerA, size_t sizeGrp )
{
	printMessage(DEBUGS, "Print _array B with winner Index", std::string(FILLIGN - 20, '-'));
	std::cout << BLUE << "ArrB:";
	for (size_t i = 0; i < arrB.size(); ++i)
		std::cout << "	" << std::setfill('0') << std::setw(2) << arrB[i];
	std::cout << std::endl << LYLA << "Iwin:";
	for (size_t i = 0; i < indexWinnerA.size(); ++i)
		std::cout << std::string(sizeGrp, '	') << std::setfill('0') << std::setw(2) << indexWinnerA[i];
	std::cout << RESET << std::endl;
	printMessage(DEBUGS, "", std::string(FILLIGN, '-'));
}

template <typename T>
void	PmergeMe::_printArrayWithIndexs( const std::string& context, const T& arr, bool sortByLoseWin, size_t sizeGrp )
{
	// Title ----------------------------------------------------
	if (sortByLoseWin)
		std::cout << CYAN << "LOSER " << LYLA << " WINNER" << std::endl;

	std::cout << BLUE << context;

	size_t i = 0;
	while (i < arr.size())
	{
		std::cout << std::setfill('0') << std::setw(2);
		std::cout << arr[i] << "	";
		++i;
	}
	std::cout << std::endl;

	// Indexs ---------------------------------------------------
	std::cout << LYLA << "i:	";
	size_t j = 0;
	bool loser = false;
	while (j < i)
	{
		if (sortByLoseWin)
		{
			if (loser)
				std::cout << CYAN;
			else 
				std::cout << LYLA;
			if (j != 0)
				std::cout << "	";
			std::cout << std::setfill('0') << std::setw(2) << j;
		}
		else
		{
			if (j != 0)
				std::cout << "	";
			std::cout << LYLA << std::setfill('0') << std::setw(2) << j;
		}
		if (sizeGrp > 0 && !((j + 1) % sizeGrp))
		{
			std::cout << BLUE << "|" << LYLA;
			if (loser)
				loser = false;
			else
				loser = true;
		}
		else
			std::cout << " ";
		++j;
	}
	std::cout << std::endl << std::string(FILLIGN, '-') << RESET << std::endl;
}

template <typename T>
void PmergeMe::_pushToArr(size_t start, size_t length, bool deleteFromSrc,
	T& src, T& dst)
{
	std::vector<int> tmp(src.begin() + start, src.begin() + start + length);
	if (deleteFromSrc)
		src.erase(src.begin() + start, src.begin() + start + length);
	dst.insert(dst.end(), tmp.begin(), tmp.end());
}

template <typename T>
void	PmergeMe::_printArray( const T& arr )
{
	for (size_t i = 0; i < arr.size(); ++i)
	{
		std::cout << std::setfill('0') << std::setw(2);
		std::cout << arr[i] << "	";
	}
	std::cout << std::endl;
}

template <typename T>
void	PmergeMe::_printAfter( ContainerType type, const T& arr )
{
	std::cout << "After:	";
	_printArray(arr);
	bool	sorted = _isSorted(arr);
	printMessage((sorted ? INFO : ERROR), (type == VECTOR ? "(vector)" : "(deque)"),
		(sorted ? " - Yes, it's sorted. Congratulations !" : " - No, it isn't sorted. Good luck, yes you can !"));
}

// Move a group
template <typename T>
void PmergeMe::_moveRange(bool deleteFromSrc, size_t startGrp, size_t length, size_t newIndex,
	T& src, T& dst)
{
	// if newIndex > startGrp -> - length -> have first index to move group
	size_t final_dst = newIndex > startGrp ? newIndex - length : newIndex;
	std::vector<int> tmp(src.begin() + startGrp, src.begin() + startGrp + length);
	if (deleteFromSrc)
		src.erase(src.begin() + startGrp, src.begin() + startGrp + length);
	dst.insert(dst.begin() + final_dst, tmp.begin(), tmp.end());
}

/*
the group size is parameter
5 4 6 1 2 3
for groups of 3 elements : 6 is loser, 3 is winner
if loser > winner, we invert group positions
1 2 3 5 4 6
*/
template <typename T>
void	PmergeMe::_orderGrp( T& arr, size_t sizeGrp )
{
	if (sizeGrp < 1)
		throw std::runtime_error("Order group: sizeGrp invalid");
	size_t i = sizeGrp - 1;
	while(i < arr.size())
	{
		size_t loser = i;
		size_t startLoser = i - (sizeGrp - 1);
		size_t winner = i + sizeGrp;
		if ( winner >= arr.size() )
			return ;
		if ( i < arr.size() - 1 )
		{
			if (arr.at(loser) > arr.at(winner))
				_moveRange(1, startLoser, sizeGrp, winner + 1, arr, arr);
		}
		i += sizeGrp * 2;
	}
}

template <typename T>
void	PmergeMe::_allLosersToArrayB( T& arrA, T& arrB, T& indexWinnerA, size_t sizeGrp, size_t nbGrp )
{
	size_t	start = 0;
	float nbGrpLosers = (nbGrp / 2) + 1; // fragile
	size_t nbTransfer = 0;
	size_t skipWinners = 1;

	while((nbTransfer < nbGrpLosers) && start < arrA.size())
	{
		_pushToArr(start, sizeGrp, 1, arrA, arrB);
		nbTransfer++;
		start = sizeGrp * skipWinners;
		skipWinners++;
	}
	size_t i = sizeGrp - 1;
	while (i < arrB.size())
	{
		indexWinnerA.push_back(i);
		i += sizeGrp;
	}
}

template <typename T>
void	PmergeMe::_insertGrpBinarySearch( T& arrA, T&arrB, T& indexWinnerA, size_t sizeGrp, size_t indexNextGrpToInsert, size_t isInter )
{
	size_t startGrp;
	if (isInter)
		startGrp = sizeGrp * isInter;
	else
		startGrp = (sizeGrp*(indexNextGrpToInsert)) - sizeGrp;
	
	if (startGrp >= arrB.size())
		return ;

	size_t indexNbTarget = startGrp + sizeGrp - 1; // in arrB
	int nbTarget = arrB[indexNbTarget];
	size_t endSearch;
	if ((indexNbTarget - 1) < indexWinnerA.size())
		endSearch = indexWinnerA[indexNbTarget - 1];
	else
		endSearch = arrA.size();

	size_t indexInsert = _binarySearch(arrA, nbTarget, sizeGrp, endSearch);

	T tmp(arrB.begin() + startGrp, arrB.begin() + startGrp + sizeGrp);
	arrA.insert(arrA.begin() + indexInsert, tmp.begin(), tmp.end());
	for (size_t i = 0; i < indexWinnerA.size(); ++i) // readapt index winner with new insertion
		indexWinnerA[i] += sizeGrp;
}


// Comparison with winners only
// 1. create a vector* with only winners
// 2. search in winners
template <typename T>
size_t	PmergeMe::_binarySearch( T& arr, int nbTarget, size_t sizeGrp, size_t endSearch )
{
	if (endSearch <= 1) // search end at 1, so insert at 0
		return (0);

	// 1. Create winner vector ------------------------------------------
	std::vector<int*> winners;
	size_t current = 0;
	
	/*
	- sizeGrp > 1
	eg: for sizeGrp = 4
	winners are index 03 and 07 -> (4 or 8) - 1
	(sizeGrp * current) - 1 -> current = 1 -> 03
	(sizeGrp * current) - 1 -> current = 2 -> 07
	- sizeGrp = 1
	All index in _arrayA are winners
	*/
	if (sizeGrp > 1)
		current = 1;
	while ((sizeGrp == 1 && current < arr.size())
			|| (sizeGrp > 1 && ((sizeGrp * current) - 1) < arr.size()))
	{
		if (sizeGrp > 1)
			winners.push_back(&arr[(sizeGrp * current) - 1]);
		else
			winners.push_back(&arr[current]);
		++current;
	}

	// std::cout << "winners only vector:" << std::endl;
	// for (size_t i = 0; i < winners.size(); ++i)
	// 	std::cout << "	" << *winners[i];
	// std::cout << std::endl;

	// ------------------------------------------------------------------

	// 2. find index ------------------------------------------------------
	// values are indexs
	size_t start = 0;
	// endSearch = index winner
	endSearch = endSearch / sizeGrp; // convert for the winner-only vector
	while (start < endSearch)
	{
		size_t half = floor(start + ((endSearch - start)/2));
		if (half <= 0)
		{
			start = 0;
			break;
		}
		if (*winners[half] > nbTarget)
		{
			if ((half - 1) < winners.size() && *winners[half - 1] < nbTarget)
			{
				start = half - 1;
				break;
			}
			endSearch = half - 1;
			continue;
		}
		else if (*winners[half] < nbTarget)
		{
			start = half + 1;
			if ((start < winners.size() && *winners[start] > nbTarget)
				|| start >= winners.size())
			{
				start = half;
				break;
			}
			continue;
		}
		--endSearch;
	}

	// 3. Convert winner index to array index ------------------------------------------------------
	size_t res = 0;
	if (start > 0)
	{
		size_t nbGroup = start + 1; // start is a index, start 0, but it is the nb of group 1st, 2nd, etc
		res = (nbGroup * sizeGrp);
	}
	else if (start == 0 && *winners[start] > nbTarget)
		res = 0;
	else if (start == 0 && *winners[start] < nbTarget)
		res = sizeGrp;

	return (res);
}

template <typename T>
void	PmergeMe::_sortAll( ContainerType type, T& arrA, size_t levelIteration, size_t sizeGrp )
{
	T arrB, leftOver, suiteJaco, indexWinnerA;
	
	if (sizeGrp == 1)
	{
		for (size_t i = 0; i < _unsortedNumbers.size(); ++i)
			arrA.push_back(_unsortedNumbers[i]);
	}

	// Sort all by grp with loser - winner ----------------------------------
	if (_nbGrpStrict(arrA.size(), sizeGrp) < 2)
		return ;

	_orderGrp(arrA, sizeGrp);
	++levelIteration;
	// ----------------------------------------------------------------------

	// Recursivity ----------------------------------------------------------
	_sortAll(type, arrA, levelIteration, pow(2, levelIteration));
	
	// Insertion ------------------------------------------------------------
	if (_nbGrpStrict(arrA.size(), sizeGrp) < 3) // already sorted
		return ;
	
	// 1. All losers to array B
	_initSuiteJacobsthal(suiteJaco);
	_initLeftOvers(arrA, leftOver, sizeGrp, _nbGrp(arrA.size(), sizeGrp));
	_allLosersToArrayB( arrA, arrB, indexWinnerA, sizeGrp, _nbGrp(arrA.size(), sizeGrp));

	// 2. Reinsert to array A
	size_t indexLastGrpInsert = _getSuiteJacobsthal(suiteJaco);
	size_t indexNextGrpToInsert = _getSuiteJacobsthal(suiteJaco);

	/*
	   3. Insert interval inbetween two Jacobasthal Numbers
	1 grp a inserer -> (1(indexdugrp) * 2(sizegrp)) - sizegrp(revenir au premier)
	*/
	bool interJaco = false;
	while (indexNextGrpToInsert < arrB.size())
	{
		_insertGrpBinarySearch(arrA, arrB, indexWinnerA, sizeGrp, indexNextGrpToInsert, 0);
	
		if (interJaco)
		{
			interJaco = false;
			size_t endInter = indexNextGrpToInsert - 1;
			while (indexLastGrpInsert < endInter)
			{
				_insertGrpBinarySearch(arrA, arrB, indexWinnerA, sizeGrp, indexNextGrpToInsert, indexLastGrpInsert);
				++indexLastGrpInsert;
			}
		}
		indexLastGrpInsert = indexNextGrpToInsert;
		indexNextGrpToInsert = _getSuiteJacobsthal(suiteJaco);
		interJaco = true;
	}
	/*
	Insert lasts groups if exist
	if indexNextGrpToInsert >= array.size
	-> check if inbetween arrayB[indexLastGrpInsert] - arrB[indexNextGrpToInsert]
	we have value 
	-> eg: (IndexNext = 5) == (arrB.size = 5)
	arrB[3] - _array[5], we have _array[4]
	*/
	if (indexLastGrpInsert < arrB.size())
	{
		++indexLastGrpInsert;
		while (indexLastGrpInsert < arrB.size() + 1)
		{
			_insertGrpBinarySearch(arrA, arrB, indexWinnerA, sizeGrp, indexLastGrpInsert, 0);
			++indexLastGrpInsert;
		}
	}

	// 4. Insert leftOver
	if (leftOver.empty())
	{
		if (sizeGrp == 1)
			_printAfter(type, arrA);
		return ;
	}
	for (size_t i = 0; i < leftOver.size(); ++i)
		arrA.push_back(leftOver[i]);

	if (sizeGrp == 1)
		_printAfter(type, arrA);
}

long long elapsed_us(const timeval& start, const timeval& end)
{
	return (end.tv_sec - start.tv_sec) * 1000000LL + (end.tv_usec - start.tv_usec);
}

template <typename T>
void	PmergeMe::_startSort( T& arrA, ContainerType type )
{
	struct timeval start, end;
	gettimeofday(&start, NULL); 
	_sortAll(type, arrA, 0, 1);
	gettimeofday(&end, NULL);
	
	std::cout << "Time to process a range of " << arrA.size();
	std::cout << " elements with std::" << (type == VECTOR ? "vector" : "deque") << "	: ";
	std::cout << std::setfill('0') << std::setw(8) << elapsed_us(start, end);
	std::cout << " us" << std::endl;
}

template < typename T >
bool	isStrOnlyType( T function, const std::string& src, const size_t& start, const size_t& end )
{
	size_t	index = start;
	if (start >= end)
		return (false);
	while (index < end)
	{
		if (!function(src[index]))
			return (false);
		++index;
	}
	return (true);
}

void	PmergeMe::_parsing( int ac, char **av ) // parser les arguemnts de av et les trsnaformer en int
{
	if (ac < 2 || !av[1])
		_invalidArguement();

	size_t len = (size_t)ac;
	for (size_t i = 1; i < len && av[i]; ++i)
	{
		std::string	strNb(av[i]);
		if (!isStrOnlyType<int(*)(int)>(std::isdigit, strNb, 0, strNb.size()))
			throw std::runtime_error("Argument is not only a number: " + strNb);
		char *end;
		long nb = std::strtol(strNb.c_str(), &end, 10);
		if (errno || nb < 0 || nb > INT_MAX)
			_invalidArguement();
		_unsortedNumbers.push_back((int)nb);
	}

	if (_unsortedNumbers.size() <= 1)
		throw std::runtime_error("Only one argument, required at least two");

	if (_isSorted(_unsortedNumbers))
		throw std::runtime_error("Arguments are already sorted");
}

void	PmergeMe::algo( int ac, char **av )
{
	try
	{
		_unsortedNumbers.clear();
		_parsing(ac, av);
		std::cout << "Before:	";
		_printArray(_unsortedNumbers);

		std::vector<int> VarrA;
		_startSort(VarrA, VECTOR);

		std::deque<int> DarrA;
		_startSort(DarrA, DEQUE);
	}
	catch (const std::exception& e)
	{
		printMessage(ERROR, "Parsing - ", e.what());
		return ;
	}
}


