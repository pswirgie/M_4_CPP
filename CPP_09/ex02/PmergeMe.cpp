/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pswirgie <pswirgie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/19 16:44:29 by pswirgie          #+#    #+#             */
/*   Updated: 2026/10/12 18:37:48 by pswirgie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"
#include <sys/time.h>

PmergeMe::PmergeMe( void ){}

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
	// printMessage(DEBUGS, "suite jaco BEGIN ----------------------------------------", "");
	// _printArrayJacobsthal();
	// printMessage(DEBUGS, "suite jaco - index[0]: ", suiteJaco.at(0));
	// printMessage(DEBUGS, "suite jaco - index[1]: ", suiteJaco.at(1));
	suiteJaco.push_back(suiteJaco.at(1) + (2*(suiteJaco.at(0))));
	suiteJaco.erase(suiteJaco.begin(), suiteJaco.begin() + 1);
	// _printArrayJacobsthal();
	// printMessage(DEBUGS, "suite jaco END ----------------------------------------", "");
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

// Move a group
template <typename T>
void PmergeMe::_moveRange(bool deleteFromSrc, size_t startGrp, size_t length, size_t newIndex,
	T& src, T& dst)
{
	// if newIndex > startGrp -> - length -> have first index to move group
	size_t final_dst = newIndex > startGrp ? newIndex - length : newIndex;
	// std::cout << BLUE << "[DEBUG] moveRange -> start: " << start;
	// std::cout << ", length: " << length << ", newIndex: " << newIndex;
	// std::cout << std::endl;
	// printMessage(DEBUGS, "_moveRange() - final_dst: ", final_dst);
	// printMessage(DEBUGS, "_moveRange() - newIndex: ", newIndex);
	// printMessage(DEBUGS, "_moveRange() - startGrp: ", startGrp);

	std::vector<int> tmp(src.begin() + startGrp, src.begin() + startGrp + length);
	if (deleteFromSrc)
		src.erase(src.begin() + startGrp, src.begin() + startGrp + length);
	// printMessage(DEBUGS, "_moveRange() - tmp: ", "");
	// printArray(tmp, 0);
	// printMessage(DEBUGS, "_moveRange() - length: ", length);
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
	// printMessage(DEBUGS, "_orderGrp() ", std::string(FILLIGN, '-'));
	if (sizeGrp < 1)
		throw std::runtime_error("Order group: sizeGrp invalid");
	size_t i = sizeGrp - 1;
	while(i < arr.size())
	{
		size_t loser = i;
		size_t startLoser = i - (sizeGrp - 1);
		size_t winner = i + sizeGrp;

		// printMessage(DEBUGS, "i: ", i);
		// printMessage(DEBUGS, "loser: ", loser);
		// printMessage(DEBUGS, "startLoser: ", startLoser);
		// printMessage(DEBUGS, "winner: ", winner);

		if ( winner >= arr.size() )
		{
			// printMessage(DEBUGS, "_orderGrp() - end ", std::string(FILLIGN, '-'));
			return ; // paire fictive, ne pas modifier
		}
		if ( i < arr.size() - 1 )
		{

			// std::cout << BLUE << "[DEBUG] value loser = " << arr.at(loser);
			// std::cout << " | value winner = " << arr.at(winner) << std::endl;
			// printArray('A', true);

			if (arr.at(loser) > arr.at(winner))
				_moveRange(1, startLoser, sizeGrp, winner + 1, arr, arr);
		}
		i += sizeGrp * 2;
	}
	// printMessage(DEBUGS, "_orderGrp() - END ", std::string(FILLIGN, '-'));
}

template <typename T>
void	PmergeMe::_allLosersToArrayB( ContainerType type, T& arrA, T& arrB, size_t sizeGrp, size_t nbGrp )
{
	// printMessage(DEBUGS, "_allLosersToArrayB() ", std::string(50, '-'));
	size_t	start = 0;
	// printMessage(DEBUGS, "_allLosersToArrayB() - sizeGrp: ", sizeGrp);
	float nbGrpLosers = (nbGrp / 2) + 1; // fragile
	size_t nbTransfer = 0;
	size_t skipWinners = 1;

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
	size_t i = sizeGrp - 1;
	while (i < arrB.size())
	{
		// 	printMessage(DEBUGS, "_allLosersToArrayB() - i: ", i);
		if (type == VECTOR)
			_indexWinnerA.push_back(i);
		else
			_DindexWinnerA.push_back(i);
		i += sizeGrp;
	}
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



void	PmergeMe::_sortAll( size_t levelIteration, size_t sizeGrp )
{
	// Sort all by grp with loser - winner ----------------------------------
	// printMessage(DEBUGS, "_sortAll() - order is finished ", "");

	if (_nbGrpStrict(_arrayA.size(), sizeGrp) < 2)
		return ;
	
	// printMessage(DEBUGS, "before _orderGrp() ", "" );
	// _printArrayWithIndexs(_arrayA, false, sizeGrp);
	
	_orderGrp(_arrayA, sizeGrp);
	
	// printMessage(DEBUGS, "after _orderGrp() ", "" );
	// printMessage(DEBUGS, "sizeGrp: ", sizeGrp );
	// _printArrayWithIndexs("arrA:	", _arrayA, false, sizeGrp);
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
	_allLosersToArrayB(VECTOR, _arrayA, _arrayB, sizeGrp, _nbGrp(_arrayA.size(), sizeGrp));
	// if (sizeGrp == 1)
	// {
		// printMessage(DEBUGS, "after remove losers", "");
		// _printArrayWithIndexs(_arrayA, false, sizeGrp);
		// _printArrBWithWinnerIndex(sizeGrp);
		// _printArrayWithIndexs(_leftOver, false, sizeGrp);
	// }
	
	// _printArrayWithIndexs(_arrayB, false, sizeGrp);

	// 2. Reinsert to array A
	size_t indexLastGrpInsert = _getSuiteJacobsthal(_suiteJacobsthal);
	size_t indexNextGrpToInsert = _getSuiteJacobsthal(_suiteJacobsthal);

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
		indexNextGrpToInsert = _getSuiteJacobsthal(_suiteJacobsthal);
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

	std::cout << "Time to process a range of " << _arrayA.size();
	std::cout << " elements with std::vector" << " : " << elapsed_us(start, end)  << " us" << std::endl;

	if (_isSorted(_arrayA))
		printMessage(INFO, "(Vector) - Yes, it's sorted. Congratulations !", "");
	else
		printMessage(ERROR, "(Vector) - No, it isn't sorted. Good luck, yes you can !", "");
}

void	PmergeMe::_DinsertGrpBinarySearch( bool deleteFromSrc, size_t sizeGrp, size_t indexNextGrpToInsert, size_t isInter )
{
	size_t startGrp;
	if (isInter)
		startGrp = sizeGrp * isInter;
	else
		startGrp = (sizeGrp*(indexNextGrpToInsert)) - sizeGrp;
	
	if (startGrp >= _DarrayB.size())
		return ;

	size_t indexNbTarget = startGrp + sizeGrp - 1; // in arrB
	int nbTarget = _DarrayB[indexNbTarget];
	size_t endSearch;
	if ((indexNbTarget - 1) < _DindexWinnerA.size())
		endSearch = _DindexWinnerA[indexNbTarget - 1];
	else
		endSearch = _DarrayA.size();

	size_t indexInsert = _binarySearch(_DarrayA, nbTarget, sizeGrp, endSearch);

	std::deque<int> tmp(_DarrayB.begin() + startGrp, _DarrayB.begin() + startGrp + sizeGrp);
	if (deleteFromSrc)
		_DarrayB.erase(_DarrayB.begin() + startGrp, _DarrayB.begin() + startGrp + sizeGrp);
	_DarrayA.insert(_DarrayA.begin() + indexInsert, tmp.begin(), tmp.end());
	for (size_t i = 0; i < _DindexWinnerA.size(); ++i) // readapt index winner with new insertion
		_DindexWinnerA[i] += sizeGrp;
}

void	PmergeMe::_sortDeque( size_t levelIteration, size_t sizeGrp )
{
	// Sort all by grp with loser - winner ----------------------------------
	// printMessage(DEBUGS, "_sortAll() - order is finished ", "");

	// _printArrayWithIndexs("_DarrA:	", _DarrayA, false, sizeGrp);

	if (_nbGrpStrict(_DarrayA.size(), sizeGrp) < 2)
		return ;
	_orderGrp(_DarrayA, sizeGrp);
	
	// ----------------------------------------------------------------------
	
	// Recursivity ----------------------------------------------------------
	++levelIteration;
	_sortDeque(levelIteration, pow(2, levelIteration));
	
	// Insertion ------------------------------------------------------------
	if (_nbGrpStrict(_DarrayA.size(), sizeGrp) < 3) // already sorted
		return ;

	// Clear all reusables - DONT MOVE
	_DarrayB.clear();
	_DleftOver.clear();
	_DsuiteJacobsthal.clear();
	_DindexWinnerA.clear();

	// printMessage(DEBUGS, "before remove losers", "");
	// _printArrayWithIndexs("_DarrA:	", _DarrayA, false, sizeGrp);

	// 1. All losers to array B
	_initSuiteJacobsthal(_DsuiteJacobsthal);
	_initLeftOvers(_DarrayA, _DleftOver, sizeGrp, _nbGrp(_DarrayA.size(), sizeGrp));
	_allLosersToArrayB(DEQUE, _DarrayA, _DarrayB, sizeGrp, _nbGrp(_DarrayA.size(), sizeGrp));

	// printMessage(DEBUGS, "after remove losers", "");
	// _printArrayWithIndexs("_DarrA:	", _DarrayA, false, sizeGrp);
	// _printArrBWithWinnerIndex(DEQUE, sizeGrp);
	// _printArrayWithIndexs("_DleftO:	", _DleftOver, false, sizeGrp);

	// 2. Reinsert to array A
	size_t indexLastGrpInsert = _getSuiteJacobsthal(_DsuiteJacobsthal);
	size_t indexNextGrpToInsert = _getSuiteJacobsthal(_DsuiteJacobsthal);
	bool interJaco = false;
	while (indexNextGrpToInsert < _DarrayB.size())
	{
		// printMessage(DEBUGS, "before insert", "");
		// _printArrayWithIndexs("_DarrA:	", _DarrayA, false, sizeGrp);
		// _printArrBWithWinnerIndex(DEQUE, sizeGrp);
		_DinsertGrpBinarySearch(0, sizeGrp, indexNextGrpToInsert, 0);
		// printMessage(DEBUGS, "after insert", "");
		// _printArrayWithIndexs("_DarrA:	", _DarrayA, false, sizeGrp);
		// _printArrBWithWinnerIndex(DEQUE, sizeGrp);
	
		if (interJaco)
		{
			interJaco = false;
			size_t endInter = indexNextGrpToInsert - 1;
			while (indexLastGrpInsert < endInter)
			{
				_DinsertGrpBinarySearch(0, sizeGrp, indexNextGrpToInsert, indexLastGrpInsert);
				++indexLastGrpInsert;
			}
		}
		indexLastGrpInsert = indexNextGrpToInsert;
		indexNextGrpToInsert = _getSuiteJacobsthal(_DsuiteJacobsthal);
		interJaco = true;
	}
	if (indexLastGrpInsert < _DarrayB.size())
	{
		++indexLastGrpInsert;
		while (indexLastGrpInsert < _DarrayB.size() + 1)
		{
			_DinsertGrpBinarySearch(0, sizeGrp, indexLastGrpInsert, 0);
			++indexLastGrpInsert;
		}
	}

	// 4. Insert leftOver
	_insertLeftOverBinarySearch(sizeGrp);
}

void	PmergeMe::_startDeque( void )
{
	std::cout << "Before:	";
	printArray(_DarrayA);
	
	struct timeval start, end;
	gettimeofday(&start, NULL); 
	_sortDeque(0, 1);
	gettimeofday(&end, NULL);
	std::cout << "After:	";
	printArray(_DarrayA);

	std::cout << "Time to process a range of " << _arrayA.size();
	std::cout << " elements with std::vector" << " : " << elapsed_us(start, end)  << " us" << std::endl;

	if (_isSorted(_DarrayA))
		printMessage(INFO, "(Deque) - Yes, it's sorted. Congratulations !", "");
	else
		printMessage(ERROR, "(Deque) - No, it isn't sorted. Good luck, yes you can !", "");
}
void	PmergeMe::algo( int ac, char **av )
{
	try
	{
		_parsing(ac, av);
		// _startVector();
		_startDeque();
	}
	catch (const std::exception& e)
	{
		printMessage(ERROR, "Parsing - ", e.what());
		return ;
	}
}


