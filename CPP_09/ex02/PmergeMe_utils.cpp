/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe_utils.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pswirgie <pswirgie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/19 16:44:29 by pswirgie          #+#    #+#             */
/*   Updated: 2026/10/11 11:12:19 by pswirgie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

void	PmergeMe::invalidArguement( void )
{
	std:: string	message("Invalid arguements, pattern required a unsorted"
		" positive integer sequence (at least 2 elements)"
		" separated by spaces: ./PmergeMe [numbers] [//] [//] ...");
	printMessage(ERROR, "", message);
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

void	PmergeMe::_printArrBWithWinnerIndex( void )
{
	printMessage(DEBUGS, "Print _array B with winner Index", std::string(FILLIGN - 20, '-'));
	std::cout << BLUE << "ArrB:";
	for (size_t i = 0; i < _arrayB.size(); ++i)
		std::cout << "	" << std::setfill('0') << std::setw(2) << _arrayB[i];
	std::cout << std::endl << LYLA << "Iwin:";
	for (size_t i = 0; i < _indexWinnerA.size(); ++i)
		std::cout << "		" << std::setfill('0') << std::setw(2) << _indexWinnerA[i];
	std::cout << "		NONE" << RESET << std::endl;
	printMessage(DEBUGS, "", std::string(FILLIGN, '-'));
}

int	PmergeMe::argsToNumbers( int ac, char **av ) // parser les arguemnts de av et les trsnaformer en int
{
	bool isNumber = false;

	for(int i = 0; i < ac - 1; ++i)
	{
		std::string arg = av[i];
		// printMessage(DEBUGS, "arg: ", arg);
		if (arg.empty()) // case arg = ""
		{
			invalidArguement();
			return (1);
		}
		size_t start = 0;
		for(size_t j = 0; arg[j]; ++j) // case arg != digit && space
		{
			// printMessage(DEBUGS, "arg[j]: ", arg[j]);
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
		printMessage(ERROR, "Only one arguement, required at least two", "");
		return (1);
	}
	else if (_isSorted(_arrayA)) // case already sorted
	{
		printMessage(ERROR, "Arguements already sorted", "");
		return (1);
	}
	return (0);
}

void	PmergeMe::clearArrayA( void )
{	_arrayA.clear();	}


void	PmergeMe::printArray( const std::vector<int>& arr, bool sortByLoseWin )
{
	// printMessage(DEBUGS, "PrintArray() ", (std::string(FILLIGN, '-')));
	if (sortByLoseWin)
		std::cout << CYAN << "LOSER " << LYLA << " WINNER" << std::endl;

	if (arr == _arrayA)
		std::cout << BLUE << "ArrA:	";
	else if (arr == _arrayB)
		std::cout << BLUE << "ArrB:	";
	else
		std::cout << BLUE << "Other:	";

	size_t i = 0;
	while (i < arr.size())
	{
		std::cout << std::setfill('0') << std::setw(2);
		std::cout << arr[i] << "	";
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
	// printMessage(DEBUGS, "PrintArray() - END ", (std::string(FILLIGN, '-')));
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
	// printMessage(DEBUGS, "_orderGrp() ", std::string(FILLIGN, '-'));
	if (sizeGrp < 1)
	{
		printMessage(ERROR, "Order group: sizeGrp invalid", "");
		return ;
	}
	size_t i = sizeGrp - 1;
	while(i < _arrayA.size())
	{
		size_t loser = i;
		size_t startLoser = i - (sizeGrp - 1);
		size_t winner = i + sizeGrp;

		// std::cout << BLUE << "[DEBUG] index loser = " << loser;
		// std::cout << " | index winner = " << winner;
		// std::cout << " | size = " << _arrayA.size();
		// std::cout << " | sizeGrp = " << sizeGrp;
		// std::cout << RESET << std::endl;

		if ( winner >= _arrayA.size() )
		{
			// printMessage(DEBUGS, "_orderGrp() - end ", std::string(FILLIGN, '-'));
			return ; // paire fictive, ne pas modifier
		}
		if ( i < _arrayA.size() - 1 )
		{

			// std::cout << BLUE << "[DEBUG] value loser = " << _arrayA.at(loser);
			// std::cout << " | value winner = " << _arrayA.at(winner) << std::endl;
			// printArray('A', true);

			if (_arrayA.at(loser) > _arrayA.at(winner))
				_moveRange(1, startLoser, sizeGrp, winner + 1, _arrayA, _arrayA);
		}
		i += sizeGrp * 2;
	}
	// printMessage(DEBUGS, "_orderGrp() - END ", std::string(FILLIGN, '-'));
}

// Move a group
void PmergeMe::_moveRange(bool deleteFromSrc, size_t startGrp, size_t length, size_t newIndex,
	std::vector<int>& src, std::vector<int>& dst)
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

void PmergeMe::_pushToArr(size_t start, size_t length, bool deleteFromSrc,
	std::vector<int>& src, std::vector<int>& dst)
{
	std::cout << BROWN << "[DEBUG] moveRange -> start: " << start;
	std::cout << ", length: " << length;
	std::cout << std::endl;

	std::vector<int> tmp(src.begin() + start, src.begin() + start + length);
	if (deleteFromSrc)
		src.erase(src.begin() + start, src.begin() + start + length);
	// (void)final_dst;
	// (void)dst;
	dst.insert(dst.end(), tmp.begin(), tmp.end());
}

size_t	PmergeMe::_nbGrp( size_t sizeArr, size_t sizeGrp )
{
	size_t res = ceil(static_cast<double>(sizeArr) / sizeGrp);
	// std::cout << BROWN << "[DEBUG] _nbGrp -> res: " << res << RESET << std::endl;
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

void	PmergeMe::_initSuiteJacobsthal( void )
{
	_suiteJacobsthal.push_back(1);
	_suiteJacobsthal.push_back(1);
}

/*
-> Return first index and calcul the next + 1
[0] = 1
[1] = 1
[n] = [n - 1] + 2*[n - 2]
Suite Jacobsthal : 1, 1, 3, 5, 11, 21, 43, 85, 171, 341
*/
size_t	PmergeMe::_getSuiteJacobsthal( void )
{
	size_t	index = _suiteJacobsthal.at(0);
	// printMessage(DEBUGS, "suite jaco BEGIN ----------------------------------------", "");
	// _printArrayJacobsthal();
	// printMessage(DEBUGS, "suite jaco - index[0]: ", _suiteJacobsthal.at(0));
	// printMessage(DEBUGS, "suite jaco - index[1]: ", _suiteJacobsthal.at(1));
	_suiteJacobsthal.push_back(_suiteJacobsthal.at(1) + (2*(_suiteJacobsthal.at(0))));
	_suiteJacobsthal.erase(_suiteJacobsthal.begin(), _suiteJacobsthal.begin() + 1);
	// _printArrayJacobsthal();
	// printMessage(DEBUGS, "suite jaco END ----------------------------------------", "");
	return (index);
}
