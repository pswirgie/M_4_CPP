/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pswirgie <pswirgie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/19 16:44:29 by pswirgie          #+#    #+#             */
/*   Updated: 2026/10/12 15:08:47 by pswirgie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

PmergeMe::PmergeMe( void ){}

void	PmergeMe::_allLosersToArrayB( size_t sizeGrp, size_t nbGrp )
{
	printMessage(DEBUGS, "_allLosersToArrayB() ", std::string(50, '-'));
	size_t	start = 0;
	// printMessage(DEBUGS, "_allLosersToArrayB() - sizeGrp: ", sizeGrp);
	float nbGrpLosers = (nbGrp / 2) + 1; // fragile
	size_t nbTransfer = 0;
	size_t skipWinners = 1;
	// bool	isLeftOver = false;
	// printMessage(DEBUGS, "nbGrpLosers: ", nbGrpLosers);


	while((nbTransfer < nbGrpLosers) && start < _arrayA.size())
	{
		// printMessage(DEBUGS, "nbTransfer: ", nbTransfer);
		// printArray(_arrayA, 0, sizeGrp);
		// printMessage(DEBUGS, "_allLosersToArrayB() - sizeGrp: ", sizeGrp);
		
		_pushToArr(start, sizeGrp, 1, _arrayA, _arrayB);
		
		// printMessage(DEBUGS, "_allLosersToArrayB() - start + sizeGrp - 1: ", start + sizeGrp - 1);
		// printArray(_arrayA, false);
		// printArray(_arrayB, false);
		
		nbTransfer++;
		start = sizeGrp * skipWinners;
		skipWinners++;
	}

	// if (sizeGrp == 1)
	// 	_printArrBWithWinnerIndex(sizeGrp);
	

	// test pour garder les indexs
	size_t i = sizeGrp - 1;
	while (i < _arrayB.size())
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
	printMessage(DEBUGS, "_insertLeftOverBinarySearch()", std::string(FILLIGN, '-'));

	printMessage(DEBUGS, "sizeGrp: ", sizeGrp);
	printArray(_leftOver, 0, sizeGrp);
	printArray(_arrayA, 0, sizeGrp);

	for (size_t i = 0; i < _leftOver.size(); ++i)
		_arrayA.push_back(_leftOver[i]);

	
	// printMessage(DEBUGS, "_leftOver[_leftOver.size() - 1]: ", _leftOver[_leftOver.size() - 1]);
	// printMessage(DEBUGS, "_leftOver.size(): ", _leftOver.size());
	// printMessage(DEBUGS, "_arrayA.size(): ", _arrayA.size());
	// size_t endSearch = _arrayA.size();
	// size_t indexInsert = _binarySearch(_arrayA, _leftOver[_leftOver.size() - 1], sizeGrp, endSearch);
	// printMessage(DEBUGS, "indexInsert: ", indexInsert);
	// _arrayA.insert(_arrayA.begin() + indexInsert, _leftOver.begin(), _leftOver.end());

	// printArray(_arrayA, 0, sizeGrp);
	
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
	// 	printArray(_arrayA, 0, sizeGrp);
	// 	printArray(_arrayB, 0, sizeGrp);
	// 	_printArrBWithWinnerIndex(sizeGrp);
	// }
	// printMessage(DEBUGS, "_insertGrpBinarySearch() - end ", std::string(FILLIGN, '-'));
}


// Comparison with winners only
// 1. create a vector* with only winners
// 2. search in winners
size_t	PmergeMe::_binarySearch( std::vector<int>& arr, int nbTarget, size_t sizeGrp, size_t endSearch )
{
	printMessage(DEBUGS, "_binarySearch() ", std::string(FILLIGN, '-'));
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
	printMessage(DEBUGS, "_binarySearch() - sizeGrp: ", sizeGrp);

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

	printArray(_arrayA, 0, sizeGrp);
	printArray(_arrayB, 0, sizeGrp);
	
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

	std::cout << "winners only vector:" << std::endl;
	for (size_t i = 0; i < winners.size(); ++i)
		std::cout << "	" << *winners[i];
	std::cout << std::endl;

	// ------------------------------------------------------------------

	// 2. find index ------------------------------------------------------
	// values are indexs

	// printArray(_arrayA, 0, sizeGrp);


	size_t start = 0;
	// endSearch -> la coordonnes du winner
	endSearch = endSearch / sizeGrp; // convert for the winner-only vector
	printMessage(DEBUGS, "_binarySearch() - endSearch: ", endSearch);
	while (start < endSearch)
	{
		size_t half = floor(start + ((endSearch - start)/2));
		// start + ((end - start)/2);
		if (nbTarget == 4)
		{
			printMessage(DEBUGS, "_binarySearch() - nbTarget: ", nbTarget);
			printMessage(DEBUGS, "_binarySearch() - start: ", start);
			printMessage(DEBUGS, "_binarySearch() - half: ", half);
			printMessage(DEBUGS, "_binarySearch() - *winners[half]: ", *winners[half]);
		}
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
	
	printMessage(DEBUGS, "before _orderGrp() ", "" );
	printArray(_arrayA, false, sizeGrp);
	
	_orderGrp(sizeGrp);
	
	printMessage(DEBUGS, "after _orderGrp() ", "" );
	printMessage(DEBUGS, "sizeGrp: ", sizeGrp );
	printArray(_arrayA, false, sizeGrp);
	++levelIteration;
	// ----------------------------------------------------------------------

	// Recursivity ----------------------------------------------------------
	_sortAll(levelIteration, pow(2, levelIteration));
	
	// Insertion ------------------------------------------------------------
	if (_nbGrpStrict(_arrayA.size(), sizeGrp) < 3) // already sorted
		return ;
	// printMessage(DEBUGS, "_sortAll() - already sorted", "");
	// printMessage(DEBUGS, "levelIteration: ", levelIteration);

	// Clear all reusables - DONT MOVE
	_arrayB.clear();
	_leftOver.clear();
	_suiteJacobsthal.clear();
	_indexWinnerA.clear();
	
	// 1. All losers to array B
	_initSuiteJacobsthal();
	_initLeftOvers(sizeGrp, _nbGrp(_arrayA.size(), sizeGrp));
	_allLosersToArrayB(sizeGrp, _nbGrp(_arrayA.size(), sizeGrp));
	// if (sizeGrp == 1)
	// {
		printMessage(DEBUGS, "after remove losers", "");
		printArray(_arrayA, false, sizeGrp);
		_printArrBWithWinnerIndex(sizeGrp);
		printArray(_leftOver, false, sizeGrp);
	// }
	
	// printArray(_arrayB, false, sizeGrp);

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
				
				// printArray(_arrayB, false);
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
		printMessage(DEBUGS, "-- indexLastGrpInsert: ", indexLastGrpInsert);
		// size_t end = _arrayB.size();
		while (indexLastGrpInsert < _arrayB.size() + 1)
		{
			_insertGrpBinarySearch(0, sizeGrp, indexLastGrpInsert, 0);
			++indexLastGrpInsert;
			// printArray(_arrayA, false);
			// printArray(_arrayB, false);
		}
	}

	// 4. Insert leftOver
	_insertLeftOverBinarySearch(sizeGrp);

	printArray(_arrayA, false, sizeGrp);

	// printMessage(DEBUGS, "indexLastGrpInsert: ", indexLastGrpInsert);
	// printMessage(DEBUGS, "startGrp: ", startGrp);
	// printMessage(DEBUGS, "sizeGrp: ", sizeGrp);
	// printMessage(DEBUGS, "_arrayB[startGrp + sizeGrp]: ", _arrayB[startGrp + sizeGrp]);
	// }
	// printArray(_arrayA, false, sizeGrp);
}

void	PmergeMe::algo( int ac, char **av )
{
	try
	{
		_parsing(ac, av);
		_sortAll(0, 1);
		printMessage(DEBUGS, "Final result: ", "");
		printArray(_arrayA, false, 0);
	}
	catch (const std::exception& e)
	{
		printMessage(ERROR, "Parsing - ", e.what());
		return ;
	}

	/*
	taile du groupe = 2 puissance etape de la cursion  -> i 
	if (groupes de la taille requise < 2)
		return -: trie fini
	Merge -> a partir des gagnants trier entre perdants et gagnants et deplacer, sort loser winner groups by pair
	recursif = refaire merge puis insertion
	if (min 3 groupes) sinon deja trier
			 mettre les perdants dans l arrayB
				- choisir le groupe perdants a prendre -> suite de machin
					la suite de machin permet de donner la premiere position position
					du grouppe perdant a prendre, puis c est vers la droite tant qu on ne recontre pas un groupe deja comparer
						-> on peut compter le nb de groupes par index de machin
							-> entre l index 1 et 3 il y a juste un groupe a comparer etc 
							-> l index de machn commence a 1 attention
				- choisir a partir du groupe de quel gagnant le comparer -> calcul nombre 
					puis ce sera une comparaison vers la gauche
	
	*/
}


