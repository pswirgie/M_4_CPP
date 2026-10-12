/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pswirgie <pswirgie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/19 16:44:29 by pswirgie          #+#    #+#             */
/*   Updated: 2026/10/12 17:37:38 by pswirgie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"
#include <sys/time.h>

PmergeMe::PmergeMe( void ){}

template <typename T>
void	PmergeMe::_initSuiteJacobsthal( T& arr )
{
	arr.push_back(1);
	arr.push_back(1);
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
void	PmergeMe::_printArrayWithIndexs( const std::string& context, const T& arr, bool sortByLoseWin, size_t sizeGrp )
{
	// printMessage(DEBUGS, "PrintArray() ", (std::string(FILLIGN, '-')));

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
	// std::cout << RESET << std::endl;
	std::cout << std::endl << std::string(FILLIGN, '-') << RESET << std::endl;
	
	// printMessage(DEBUGS, "PrintArray() - END ", (std::string(FILLIGN, '-')));
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
void	PmergeMe::printArray( const T& arr )
{
	for (size_t i = 0; i < arr.size(); ++i)
	{
		std::cout << std::setfill('0') << std::setw(2);
		std::cout << arr[i] << "	";
	}
	std::cout << std::endl;
}

template <typename T>
void	PmergeMe::_allLosersToArrayB( T& arrA, T& arrB, size_t sizeGrp, size_t nbGrp )
{
	// printMessage(DEBUGS, "_allLosersToArrayB() ", std::string(50, '-'));
	size_t	start = 0;
	// printMessage(DEBUGS, "_allLosersToArrayB() - sizeGrp: ", sizeGrp);
	float nbGrpLosers = (nbGrp / 2) + 1; // fragile
	size_t nbTransfer = 0;
	size_t skipWinners = 1;
	// bool	isLeftOver = false;
	// printMessage(DEBUGS, "nbGrpLosers: ", nbGrpLosers);


	while((nbTransfer < nbGrpLosers) && start < arrA.size())
	{
		// printMessage(DEBUGS, "nbTransfer: ", nbTransfer);
		// _printArrayWithIndexs(arrA, 0, sizeGrp);
		// printMessage(DEBUGS, "_allLosersToArrayB() - sizeGrp: ", sizeGrp);
		
		_pushToArr(start, sizeGrp, 1, arrA, arrB);
		
		// printMessage(DEBUGS, "_allLosersToArrayB() - start + sizeGrp - 1: ", start + sizeGrp - 1);
		// _printArrayWithIndexs(arrA, false);
		// _printArrayWithIndexs(arrB, false);
		
		nbTransfer++;
		start = sizeGrp * skipWinners;
		skipWinners++;
	}

	// if (sizeGrp == 1)
	// 	_printArrBWithWinnerIndex(sizeGrp);
	

	// test pour garder les indexs
	size_t i = sizeGrp - 1;
	while (i < arrB.size())
	{
		// if (sizeGrp == 1)
		// 	printMessage(DEBUGS, "_allLosersToArrayB() - i: ", i);
		_indexWinnerA.push_back(i);
		i += sizeGrp;
	}
	
	
	// if (sizeGrp == 1)
		// _printArrBWithWinnerIndex(sizeGrp);
	
	// std::cout << BROWN << "[DEBUG] _allLosersToArrayB -> end " << std::string(40, '-') << RESET << std::endl;
}

void	PmergeMe::_insertLeftOverBinarySearch( size_t sizeGrp )
{
	if (_leftOver.empty())
		return ;

	(void) sizeGrp;
	// printMessage(DEBUGS, "_insertLeftOverBinarySearch()", std::string(FILLIGN, '-'));

	// printMessage(DEBUGS, "sizeGrp: ", sizeGrp);
	// _printArrayWithIndexs(_leftOver, 0, sizeGrp);
	// _printArrayWithIndexs(_arrayA, 0, sizeGrp);

	for (size_t i = 0; i < _leftOver.size(); ++i)
		_arrayA.push_back(_leftOver[i]);

	
	// printMessage(DEBUGS, "_leftOver[_leftOver.size() - 1]: ", _leftOver[_leftOver.size() - 1]);
	// printMessage(DEBUGS, "_leftOver.size(): ", _leftOver.size());
	// printMessage(DEBUGS, "_arrayA.size(): ", _arrayA.size());
	// size_t endSearch = _arrayA.size();
	// size_t indexInsert = _binarySearch(_arrayA, _leftOver[_leftOver.size() - 1], sizeGrp, endSearch);
	// printMessage(DEBUGS, "indexInsert: ", indexInsert);
	// _arrayA.insert(_arrayA.begin() + indexInsert, _leftOver.begin(), _leftOver.end());

	// _printArrayWithIndexs(_arrayA, 0, sizeGrp);
	
	// printMessage(DEBUGS, "_insertLeftOverBinarySearch() - end", std::string(FILLIGN, '-'));
	// exit(1);
}


void	PmergeMe::_insertGrpBinarySearch( bool deleteFromSrc, size_t sizeGrp, size_t indexNextGrpToInsert, size_t isInter )
{
	// printMessage(DEBUGS, "_insertGrpBinarySearch() ", std::string(FILLIGN, '-'));
	// printMessage(DEBUGS, "indexNextGrpToInsert: ", indexNextGrpToInsert);

	size_t startGrp;
	if (isInter)
		startGrp = sizeGrp * isInter;
	else
		startGrp = (sizeGrp*(indexNextGrpToInsert)) - sizeGrp;
	if (startGrp >= _arrayB.size())
		return ;

	size_t indexNbTarget = startGrp + sizeGrp - 1; // in arrB
	int nbTarget = _arrayB[indexNbTarget];
	size_t endSearch;
	if ((indexNbTarget - 1) < _indexWinnerA.size())
		endSearch = _indexWinnerA[indexNbTarget - 1];
	else
		endSearch = _arrayA.size();

	// if (endSearch == _arrayA.size() )
	// 	printMessage(DEBUGS, "endSearch: ", endSearch);

	// if (sizeGrp == 1 && indexNextGrpToInsert == 6)
	// {
	// 	printMessage(DEBUGS, "startGrp: ", startGrp);
	// 	printMessage(DEBUGS, "sizeGrp: ", sizeGrp);
	// 	printMessage(DEBUGS, "NbTarget: ", _arrayB[indexNbTarget]);
	// 	printMessage(DEBUGS, "endSearch: ", endSearch);
	// 	printMessage(DEBUGS, "_arrayB[indexNextGrpToInsert]: ", _arrayB[indexNextGrpToInsert - 1]);
		
	// }

	size_t indexInsert = _binarySearch(_arrayA, nbTarget, sizeGrp, endSearch);

	std::vector<int> tmp(_arrayB.begin() + startGrp, _arrayB.begin() + startGrp + sizeGrp);
	if (deleteFromSrc)
		_arrayB.erase(_arrayB.begin() + startGrp, _arrayB.begin() + startGrp + sizeGrp);
	_arrayA.insert(_arrayA.begin() + indexInsert, tmp.begin(), tmp.end());
	for (size_t i = 0; i < _indexWinnerA.size(); ++i) // readapt index winner with new insertion
		_indexWinnerA[i] += sizeGrp;

	// if (sizeGrp == 1)
	// {
	// 	printMessage(DEBUGS, "sizeGrp = 1 ------------","");
	// 	_printArrayWithIndexs(_arrayA, 0, sizeGrp);
	// 	_printArrayWithIndexs(_arrayB, 0, sizeGrp);
	// 	_printArrBWithWinnerIndex(sizeGrp);
	// }
	// printMessage(DEBUGS, "_insertGrpBinarySearch() - end ", std::string(FILLIGN, '-'));
}


// Comparison with winners only
// 1. create a vector* with only winners
// 2. search in winners
template <typename T>
size_t	PmergeMe::_binarySearch( T& arr, int nbTarget, size_t sizeGrp, size_t endSearch )
{
	// printMessage(DEBUGS, "_binarySearch() ", std::string(FILLIGN, '-'));
	// if (sizeGrp == 1)
	// 	printMessage(DEBUGS, "_binarySearch() - nbTarget: ", nbTarget);

	if (endSearch <= 1) // search end at 1, so insert at 0
	{
		// printMessage(DEBUGS, "endSearch: ", endSearch);
		return (0);
	}

	// 1. Create winner vector ------------------------------------------
	std::vector<int*> winners;
	size_t current = 0;
	
	// printMessage(DEBUGS, "_binarySearch() - nbGrp: ", nbGrp);
	// printMessage(DEBUGS, "_binarySearch() - sizeGrp: ", sizeGrp);

	/*
	sizeGrp > 1
	eg: for sizeGrp = 4
	winners are index 03 and 07 -> (4 or 8) - 1
	(sizeGrp * current) - 1 -> current = 1 -> 03
	(sizeGrp * current) - 1 -> current = 2 -> 07
	
	sizeGrp = 1
	All index in _arrayA are winners
	*/
	if (sizeGrp > 1)
		current = 1;

	// _printArrayWithIndexs(_arrayA, 0, sizeGrp);
	// _printArrayWithIndexs(_arrayB, 0, sizeGrp);
	
	while ((sizeGrp == 1 && current < arr.size())
			|| (sizeGrp > 1 && ((sizeGrp * current) - 1) < arr.size()))
	{
		if (sizeGrp > 1)
		{
			winners.push_back(&arr[(sizeGrp * current) - 1]);
			// printMessage(DEBUGS, "sizegrp > 1 -> ", arr[(sizeGrp * current) - 1]);
		}
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

	// _printArrayWithIndexs(_arrayA, 0, sizeGrp);


	size_t start = 0;
	// endSearch -> la coordonnes du winner
	endSearch = endSearch / sizeGrp; // convert for the winner-only vector
	// printMessage(DEBUGS, "_binarySearch() - endSearch: ", endSearch);
	while (start < endSearch)
	{
		size_t half = floor(start + ((endSearch - start)/2));
		// start + ((end - start)/2);
		// if (nbTarget == 4)
		// {
			// printMessage(DEBUGS, "_binarySearch() - nbTarget: ", nbTarget);
			// printMessage(DEBUGS, "_binarySearch() - start: ", start);
			// printMessage(DEBUGS, "_binarySearch() - half: ", half);
			// printMessage(DEBUGS, "_binarySearch() - *winners[half]: ", *winners[half]);
		// }
		if (half <= 0)
		{
			// if (sizeGrp == 1)
			// 	printMessage(DEBUGS, "_binarySearch() - half: ", half);
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
			// printMessage(DEBUGS, "_binarySearch() - *winners[start]: ", *winners[start]);
			// printMessage(DEBUGS, "_binarySearch() - start: ", start);
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
	// printMessage(DEBUGS, "_binarySearch() - start def: ", start);

	// 3. Convert winner index to array index ------------------------------------------------------
	size_t res = 0;
	// printMessage(DEBUGS, "start: ", start);
	if (start > 0)
	{
		
		size_t nbGroup = start + 1; // start is a index, start 0, but it is the nb of group 1st, 2nd, etc
		// printMessage(DEBUGS, "_binarySearch() - nbGroup: ", nbGroup);
		res = (nbGroup * sizeGrp);
		// if (start == winners.size() && *winners[start] > nbTarget)
		// 	res = (nbGroup * sizeGrp);
		// else if ()
	}
	else if (start == 0 && *winners[start] > nbTarget)
		res = 0;
	else if (start == 0 && *winners[start] < nbTarget)
		res = sizeGrp;
	
	// printMessage(DEBUGS, "res: ", res);

	
	// printMessage(DEBUGS, "_binarySearch() - res: ", res);
	// printMessage(DEBUGS, "_binarySearch() end ", std::string(FILLIGN, '-'));
	return (res);
}

void	PmergeMe::_sortDeque( size_t levelIteration, size_t sizeGrp )
{
	// Sort all by grp with loser - winner ----------------------------------
	// printMessage(DEBUGS, "_sortAll() - order is finished ", "");

	_printArrayWithIndexs("_DarrA:	", _DarrayA, false, sizeGrp);

	if (_nbGrpStrict(_DarrayA.size(), sizeGrp) < 2)
		return ;
	_orderGrp(sizeGrp);
	++levelIteration;
	// ----------------------------------------------------------------------

	// Recursivity ----------------------------------------------------------
	_sortAll(levelIteration, pow(2, levelIteration));
	
	// Insertion ------------------------------------------------------------
	if (_nbGrpStrict(_DarrayA.size(), sizeGrp) < 3) // already sorted
		return ;

	// Clear all reusables - DONT MOVE
	_DarrayB.clear();
	_DleftOver.clear();
	_DsuiteJacobsthal.clear();
	_DindexWinnerA.clear();

	printMessage(DEBUGS, "before remove losers", "");
	_printArrayWithIndexs("_DarrA:	", _DarrayA, false, sizeGrp);

	// 1. All losers to array B
	_initSuiteJacobsthal(_DsuiteJacobsthal);
	_initLeftOvers(_DarrayA, _DleftOver, sizeGrp, _nbGrp(_DarrayA.size(), sizeGrp));
	_allLosersToArrayB(_DarrayA, _DarrayB, sizeGrp, _nbGrp(_DarrayA.size(), sizeGrp));

	printMessage(DEBUGS, "after remove losers", "");
	_printArrayWithIndexs("_DarrA:	", _DarrayA, false, sizeGrp);
	_printArrBWithWinnerIndex(sizeGrp);
	_printArrayWithIndexs("_DleftO:	", _DleftOver, false, sizeGrp);

	// 2. Reinsert to array A
	size_t indexLastGrpInsert = _getSuiteJacobsthal();
	size_t indexNextGrpToInsert = _getSuiteJacobsthal();
	bool interJaco = false;
	while (indexNextGrpToInsert < _arrayB.size())
	{
		_insertGrpBinarySearch(0, sizeGrp, indexNextGrpToInsert, 0);
	
		if (interJaco)
		{
			interJaco = false;
			size_t endInter = indexNextGrpToInsert - 1;
			while (indexLastGrpInsert < endInter)
			{
				_insertGrpBinarySearch(0, sizeGrp, indexNextGrpToInsert, indexLastGrpInsert);
				++indexLastGrpInsert;
			}
		}
		indexLastGrpInsert = indexNextGrpToInsert;
		indexNextGrpToInsert = _getSuiteJacobsthal();
		interJaco = true;
	}
	if (indexLastGrpInsert < _arrayB.size())
	{
		++indexLastGrpInsert;
		while (indexLastGrpInsert < _arrayB.size() + 1)
		{
			_insertGrpBinarySearch(0, sizeGrp, indexLastGrpInsert, 0);
			++indexLastGrpInsert;
		}
	}

	// 4. Insert leftOver
	_insertLeftOverBinarySearch(sizeGrp);
}

void	PmergeMe::_sortAll( size_t levelIteration, size_t sizeGrp )
{
	// Sort all by grp with loser - winner ----------------------------------
	// printMessage(DEBUGS, "_sortAll() - order is finished ", "");

	if (_nbGrpStrict(_arrayA.size(), sizeGrp) < 2)
		return ;
	
	// printMessage(DEBUGS, "before _orderGrp() ", "" );
	// _printArrayWithIndexs(_arrayA, false, sizeGrp);
	
	_orderGrp(sizeGrp);
	
	// printMessage(DEBUGS, "after _orderGrp() ", "" );
	// printMessage(DEBUGS, "sizeGrp: ", sizeGrp );
	// _printArrayWithIndexs(_arrayA, false, sizeGrp);
	++levelIteration;
	// ----------------------------------------------------------------------

	// Recursivity ----------------------------------------------------------
	_sortAll(levelIteration, pow(2, levelIteration));
	
	// Insertion ------------------------------------------------------------
	if (_nbGrpStrict(_arrayA.size(), sizeGrp) < 3) // already sorted
		return ;
	// printMessage(DEBUGS, "levelIteration: ", levelIteration);

	// Clear all reusables - DONT MOVE
	_arrayB.clear();
	_leftOver.clear();
	_suiteJacobsthal.clear();
	_indexWinnerA.clear();
	
	// 1. All losers to array B
	_initSuiteJacobsthal(_suiteJacobsthal);
	_initLeftOvers(_arrayA, _leftOver, sizeGrp, _nbGrp(_arrayA.size(), sizeGrp));
	_allLosersToArrayB(_arrayA, _arrayB, sizeGrp, _nbGrp(_arrayA.size(), sizeGrp));
	// if (sizeGrp == 1)
	// {
		// printMessage(DEBUGS, "after remove losers", "");
		// _printArrayWithIndexs(_arrayA, false, sizeGrp);
		// _printArrBWithWinnerIndex(sizeGrp);
		// _printArrayWithIndexs(_leftOver, false, sizeGrp);
	// }
	
	// _printArrayWithIndexs(_arrayB, false, sizeGrp);

	// 2. Reinsert to array A
	size_t indexLastGrpInsert = _getSuiteJacobsthal();
	size_t indexNextGrpToInsert = _getSuiteJacobsthal();

	/*
		3. Insert interval inbetween two Jacobasthal Numbers
	1 grp a inserer -> (1(indexdugrp) * 2(sizegrp)) - sizegrp(revenir au premier)
	*/
	bool interJaco = false;
	while (indexNextGrpToInsert < _arrayB.size())
	{
		// if (sizeGrp == 1)
		// 	printMessage(DEBUGS, "interJaco - indexNextGrpToInsert: ", indexNextGrpToInsert);

		_insertGrpBinarySearch(0, sizeGrp, indexNextGrpToInsert, 0);
	
		if (interJaco)
		{
			interJaco = false;
			size_t endInter = indexNextGrpToInsert - 1;
			// if (sizeGrp == 1)
			// 	printMessage(DEBUGS, "interJaco - indexNextGrpToInsert: ", indexNextGrpToInsert);
			// printMessage(DEBUGS, "interJaco - endInter: ", endInter);
			while (indexLastGrpInsert < endInter)
			{
				_insertGrpBinarySearch(0, sizeGrp, indexNextGrpToInsert, indexLastGrpInsert);
				
				++indexLastGrpInsert;
				
				// _printArrayWithIndexs(_arrayB, false);
			}
		}
		indexLastGrpInsert = indexNextGrpToInsert;
		indexNextGrpToInsert = _getSuiteJacobsthal();
		// if (sizeGrp == 1)
		// 	printMessage(DEBUGS, "interJaco - indexNextGrpToInsert: ", indexNextGrpToInsert);
		interJaco = true;
	}
	/*
	Insert lasts groups if exist
	if indexNextGrpToInsert >= array.size
	-> check if inbetween arrayB[indexLastGrpInsert] - _arrayB[indexNextGrpToInsert]
	we have value 
	-> eg: (IndexNext = 5) == (_arrayB.size = 5)
	_arrayB[3] - _array[5], we have _array[4]
	*/
	if (indexLastGrpInsert < _arrayB.size())
	{
		++indexLastGrpInsert;
		// printMessage(DEBUGS, "-- indexLastGrpInsert: ", indexLastGrpInsert);
		// size_t end = _arrayB.size();
		while (indexLastGrpInsert < _arrayB.size() + 1)
		{
			_insertGrpBinarySearch(0, sizeGrp, indexLastGrpInsert, 0);
			++indexLastGrpInsert;
			// _printArrayWithIndexs(_arrayA, false);
			// _printArrayWithIndexs(_arrayB, false);
		}
	}

	// 4. Insert leftOver
	_insertLeftOverBinarySearch(sizeGrp);

	// _printArrayWithIndexs(_arrayA, false, sizeGrp);

	// printMessage(DEBUGS, "indexLastGrpInsert: ", indexLastGrpInsert);
	// printMessage(DEBUGS, "startGrp: ", startGrp);
	// printMessage(DEBUGS, "sizeGrp: ", sizeGrp);
	// printMessage(DEBUGS, "_arrayB[startGrp + sizeGrp]: ", _arrayB[startGrp + sizeGrp]);
	// }
	// _printArrayWithIndexs(_arrayA, false, sizeGrp);
}

long long elapsed_us(const timeval& start, const timeval& end)
{
	return (end.tv_sec - start.tv_sec) * 1000000LL + (end.tv_usec - start.tv_usec);
}

void	PmergeMe::_startVector( void )
{
	std::cout << "Before:	";
	printArray(_arrayA);

	struct timeval start, end;
	gettimeofday(&start, NULL); 
	_sortAll(0, 1);
	gettimeofday(&end, NULL);

	std::cout << "After:	";
	printArray(_arrayA);

	ContainerType type(VECTOR);
	std::cout << "Time to process a range of " << _arrayA.size();
	std::cout << " elements with std::" << (type == VECTOR ? "vector" : "else")<< " : " << elapsed_us(start, end)  << " us" << std::endl;

	if (_isSorted())
		printMessage(INFO, "Yes, it's sorted. Congratulations !", "");
	else
		printMessage(ERROR, "No, it isn't sorted. Good luck, yes you can !", "");
}

void	PmergeMe::_startDeque( void )
{
	
	_sortDeque(0, 1);
}
void	PmergeMe::algo( int ac, char **av )
{
	try
	{
		_parsing(ac, av);
		_startVector();
		_startDeque();
	}
	catch (const std::exception& e)
	{
		printMessage(ERROR, "Parsing - ", e.what());
		return ;
	}
}


