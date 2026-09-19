/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pswirgie <pswirgie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/19 16:44:29 by pswirgie          #+#    #+#             */
/*   Updated: 2026/08/22 12:11:36 by pswirgie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"
#include <climits>
#include <stdlib.h>
#include <errno.h>
#include <cmath>
#include <iomanip>

void	printError( char *message )
{
	std::cerr << RED << "Error" << std::endl;
	std::cerr << message << RESET << std::endl;
}

void	PmergeMe::invalidArguement( void )
{
	std::cerr << RED << "Error" << std::endl;
	std::cerr << "Invalid arguements, pattern required a unsorted"
	" positive integer sequence (at least 2 elements)";
	std::cerr << " separated by spaces: ./PmergeMe [numbers] [//] [//] ...";
	std::cerr << RESET << std::endl;
}

int PmergeMe::_sendToArray( std::string str )
{
	char *end;
	long nb = std::strtol(str.c_str(), &end, 10); // INT MIN, INT MAX
	// std::cout << BLUE << "[DEBUG] " << nb << RESET << std::endl;
	if (errno || nb < 0 || nb > INT_MAX)
	{
		invalidArguement();
		return (1);
	}
	_arrayA.push_back((int)nb);
	return (0);
}

bool	PmergeMe::_isSorted( std::vector<int>& array )
{
	size_t i = 0;
	while(i <= array.size())
	{
		if (i < array.size() - 1)
		{
			// std::cout << BLUE << "[DEBUG] e1 = " << array.at(i);
			// std::cout << " e2 = " << array.at(i + 1) << RESET << std::endl;
			if (array.at(i) > array.at(i + 1))
				return (false);
		}
		++i;
	}
	return (true);
}

int	PmergeMe::argsToNumbers( int ac, char **av ) // parser les arguemnts de av et les trsnaformer en int
{
	bool isNumber = false;

	for(int i = 0; i < ac - 1; ++i)
	{
		std::string arg = av[i];
		// std::cout << BLUE << "[DEBUG] arg = " << arg << RESET << std::endl;
		if (arg.empty()) // case arg = ""
		{
			invalidArguement();
			return (1);
		}
		size_t start = 0;
		for(size_t j = 0; arg[j]; ++j) // case arg != digit && space
		{
			// std::cout << BLUE << "[DEBUG] arg j = " << arg[j] << RESET << std::endl;
			if (std::isspace(arg[j]))
			{
				if (isNumber)
				{
					std::string nb = arg.substr(start, j - 1);
					// std::cout << "[DEBUG] string nb = " << nb << std::endl;
					if (_sendToArray(nb))
						return (1);
				}
				isNumber = false;
			}
			else if (std::isdigit(arg[j]))
			{
				isNumber = true;
				while (arg[j] && std::isdigit(arg[j]))
					j++;
				if (!arg[j])
				{
					std::string nb = arg.substr(start, j);
					// std::cout << "[DEBUG] string nb = " << nb << std::endl;
					j--;
					if (_sendToArray(nb))
						return (1);
				}
			}
			else
			{
				invalidArguement();
				return (1);
			}
		}
	}
	if (_arrayA.size() <= 1) // case one argument
	{
		printError((char *)"Only one arguement, required at least two");
		return (1);
	}
	else if (_isSorted(_arrayA)) // case already sorted
	{
		printError((char *)"Arguements already sorted");
		return (1);
	}
	return (0);
}

void	PmergeMe::clearArrayA( void )
{	_arrayA.clear();	}

void	PmergeMe::printArray( char arr, bool sortByLoseWin )
{
	std::vector<int> *src = NULL;
	switch (arr)
	{
		case 'A':
		{
			std::cout << BLUE << "ArrA:	";
			src = &_arrayA;
			break;
		}
		case 'B':
		{
			std::cout << BLUE << "ArrB:	";
			src = &_arrayB;
			break;
		}
		default:
		{
			printError((char *)"Invalid array, choose A or B");
			return;
		}
	} 
	size_t i = 0;
	while (i < src->size())
	{
		std::cout << std::setfill('0') << std::setw(2);
		std::cout << (*src)[i] << " ";
		++i;
	}
	std::cout << std::endl << LYLA << "i:	";
	size_t j = 0;
	bool loser = false;
	while (j < i)
	{
		if (sortByLoseWin)
		{
			if (loser)
				std::cout << CYAN << std::setfill('0') << std::setw(2) << j;
			else 
				std::cout << LYLA << std::setfill('0') << std::setw(2) << j;
		}
		else
			std::cout << LYLA << std::setfill('0') << std::setw(2) << j;
		if (!((j + 1)%GROUP))
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
	std::cout << RESET << std::endl;
}

/*
the group size is parameter
5 4 6 1 2 3
for groups of 3 elements : 6 is loser, 3 is winner
if loser > winner, we invert group positions
1 2 3 5 4 6
*/
void	PmergeMe::_orderGrp( size_t sizeGrp )
{
	std::cout << BROWN << "[DEBUG] _orderGrp" << std::string(60, '-') << std::endl;
	if (sizeGrp < 1)
	{
		printError((char *)"Order group: sizeGrp invalid");
		return ;
	}
	size_t i = sizeGrp - 1;
	while(i < _arrayA.size())
	{
		size_t loser = i;
		size_t startLoser = i - (sizeGrp - 1);
		size_t winner = i + sizeGrp;

		std::cout << BLUE << "[DEBUG] index loser = " << loser;
		std::cout << " | index winner = " << winner;
		std::cout << BLUE << " | size = " << _arrayA.size();
		std::cout << BLUE << " | sizeGrp = " << sizeGrp;
		std::cout << RESET << std::endl;

		if ( winner >= _arrayA.size() )
		{
			std::cout << BROWN << "[DEBUG] end " << std::string(60, '-') << RESET << std::endl;
			return ; // paire fictive, ne pas modifier
		}
		if ( i < _arrayA.size() - 1 )
		{

			std::cout << BLUE << "[DEBUG] value loser = " << _arrayA.at(loser);
			std::cout << " | value winner = " << _arrayA.at(winner) << std::endl;
			printArray('A', true);

			if (_arrayA.at(loser) > _arrayA.at(winner))
				_moveRange(startLoser, sizeGrp, winner + 1, _arrayA, _arrayA);
		}
		i += sizeGrp * 2;
	}
	std::cout << BROWN << "[DEBUG] _orderGrp end " << std::string(60, '-') << RESET << std::endl;
}

void PmergeMe::_moveRange(size_t start, size_t length, size_t newIndex,
	std::vector<int>& src, std::vector<int>& dst)
{
	const size_t final_dst = newIndex > start ? newIndex - length : newIndex;
	std::cout << BLUE << "[DEBUG] moveRange -> start: " << start;
	std::cout << ", length: " << length << ", newIndex: " << newIndex;
	std::cout << std::endl;

	std::vector<int> tmp(src.begin() + start, src.begin() + start + length);
	src.erase(src.begin() + start, src.begin() + start + length);
	// (void)final_dst;
	// (void)dst;
	dst.insert(dst.begin() + final_dst, tmp.begin(), tmp.end());
}

void PmergeMe::_pushToArr(size_t start, size_t length,
	std::vector<int>& src, std::vector<int>& dst)
{
	std::cout << BROWN << "[DEBUG] moveRange -> start: " << start;
	std::cout << ", length: " << length;
	std::cout << std::endl;

	std::vector<int> tmp(src.begin() + start, src.begin() + start + length);
	src.erase(src.begin() + start, src.begin() + start + length);
	// (void)final_dst;
	// (void)dst;
	dst.insert(dst.end(), tmp.begin(), tmp.end());
}

void	PmergeMe::_allLosersToArrayB( size_t sizeGrp, size_t nbGrp )
{
	std::cout << BROWN << "[DEBUG] _allLosersToArrayB" << std::string(50, '-') << std::endl;
	size_t	i = 0;
	(void) nbGrp; // retirer des params ?
	float nbGrpLosers = _nbGrp(_arrayA.size(), sizeGrp) / 2;
	size_t nbTransfer = 0;
	size_t skipWinners = 1;
	std::cout << BLUE << "[DEBUG] nbGrpLosers: " << static_cast<float>(nbGrpLosers) ;
	std::cout << std::endl;
	while(nbTransfer < nbGrpLosers)
	{
		size_t start = i;
		// size_t end = i + sizeGrp;
		_pushToArr(start, sizeGrp, _arrayA, _arrayB);
		printArray('A', false);
		printArray('B', false);
		nbTransfer++;
		i = sizeGrp * skipWinners;
		skipWinners++;
	}
	std::cout << BROWN << "[DEBUG] _allLosersToArrayB -> end " << std::string(40, '-') << RESET << std::endl;
}

size_t	PmergeMe::_nbGrp( size_t sizeArr, size_t sizeGrp )
{
	size_t res = ceil(static_cast<double>(sizeArr) / sizeGrp);
	std::cout << BROWN << "[DEBUG] _nbGrp -> res: " << res << RESET << std::endl;
	return (res);
}

void	PmergeMe::_printArrayJacobsthal( void )
{
	size_t i = 0;
	while (i < _suiteJacobsthal.size())
	{
		std::cout << std::setfill('0') << std::setw(2);
		std::cout << _suiteJacobsthal[i] << " ";
		++i;
	}
	std::cout << RESET << std::endl;
}

void	PmergeMe::_setSuiteJacobsthal( void )
{
	_suiteJacobsthal.push_back(1);
	_suiteJacobsthal.push_back(1);
	_suiteJacobsthal.push_back(3);
}

// 1 1 3
// 3 + 3 - 1 = 5
// 3 + 5 -1 = 7


size_t	PmergeMe::_getSuiteJacobsthal( void )
{
	size_t	index = _suiteJacobsthal.at(1);
	_suiteJacobsthal.push_back(_suiteJacobsthal.at(1) + _suiteJacobsthal.at(2) - 1);
	_suiteJacobsthal.erase(_suiteJacobsthal.begin(), _suiteJacobsthal.begin() + 1);
	return (index);
}
// toujours garder l index davant 
// des que j utilise la fonction 
//  - calculer un nouvel index
// - retourner l index actuel
// - retirer le 1er index

void	PmergeMe::algo( void )
{
// Suite de Jacobsthal------------
	_setSuiteJacobsthal();

	_getSuiteJacobsthal();
	_printArrayJacobsthal();

	// printArray('A', true);
	// _orderGrp(GROUP);
	// printArray('A', true);
	// _allLosersToArrayB(GROUP, 0);


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