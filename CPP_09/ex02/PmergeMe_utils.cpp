/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe_utils.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pswirgie <pswirgie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/19 16:44:29 by pswirgie          #+#    #+#             */
/*   Updated: 2026/10/12 15:50:17 by pswirgie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

void	PmergeMe::_invalidArguement( void )
{
	std:: string	message("Invalid arguments, pattern required a unsorted"
		" positive integer sequence (at least 2 elements)"
		" separated by spaces: ./PmergeMe [numbers] [//] [//] ...");
	throw std::runtime_error(message);
}

void PmergeMe::_sendToArray( std::string str )
{
	char *end;
	long nb = std::strtol(str.c_str(), &end, 10); // INT MIN, INT MAX
	// std::cout << BLUE << "[DEBUG] " << nb << RESET << std::endl;
	if (errno || nb < 0 || nb > INT_MAX)
		_invalidArguement();
	_arrayA.push_back((int)nb);
}

void	PmergeMe::_printArrBWithWinnerIndex( size_t sizeGrp )
{
	printMessage(DEBUGS, "Print _array B with winner Index", std::string(FILLIGN - 20, '-'));
	std::cout << BLUE << "ArrB:";
	for (size_t i = 0; i < _arrayB.size(); ++i)
		std::cout << "	" << std::setfill('0') << std::setw(2) << _arrayB[i];
	std::cout << std::endl << LYLA << "Iwin:";
	for (size_t i = 0; i < _indexWinnerA.size(); ++i)
		std::cout << std::string(sizeGrp, '	') << std::setfill('0') << std::setw(2) << _indexWinnerA[i];
	std::cout << RESET << std::endl;
	printMessage(DEBUGS, "", std::string(FILLIGN, '-'));
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

bool	PmergeMe::_isSorted( void )
{
	for (size_t i = 0; i < _arrayA.size(); ++i)
	{
		if (i + 1 < _arrayA.size() && _arrayA[i] > _arrayA[i + 1])
			return (false);
	}
	return (true);
}

void	PmergeMe::_parsing( int ac, char **av ) // parser les arguemnts de av et les trsnaformer en int
{
	if (ac < 2 || !av[1])
		_invalidArguement();

	size_t len = (size_t)ac;
	// printMessage(DEBUGS, "ac: ", ac);
	// for (size_t i = 1; i < len; ++i)
	// 	printMessage(DEBUGS, "av[i]: ", av[i]);
	
	for (size_t i = 1; i < len && av[i]; ++i)
	{
		std::string	strNb(av[i]);
		if (!isStrOnlyType<int(*)(int)>(std::isdigit, strNb, 0, strNb.size()))
			throw std::runtime_error("Argument is not only a number: " + strNb);
		char *end;
		long nb = std::strtol(strNb.c_str(), &end, 10);
		if (errno || nb < 0 || nb > INT_MAX)
			_invalidArguement();
		_arrayA.push_back((int)nb);
	}

	if (_arrayA.size() <= 1)
		throw std::runtime_error("Only one argument, required at least two");

	if (_isSorted())
		throw std::runtime_error("Arguments are already sorted");
}

void	PmergeMe::clearArrayA( void )
{	_arrayA.clear();	}

void	PmergeMe::printArray( const std::vector<int>& arr )
{
	for (size_t i = 0; i < arr.size(); ++i)
	{
		std::cout << std::setfill('0') << std::setw(2);
		std::cout << arr[i] << "	";
	}
	std::cout << std::endl;
}

void	PmergeMe::_printArrayWithIndexs( const std::vector<int>& arr, bool sortByLoseWin, size_t sizeGrp )
{
	// printMessage(DEBUGS, "PrintArray() ", (std::string(FILLIGN, '-')));

	// Title ----------------------------------------------------
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
		throw std::runtime_error("Order group: sizeGrp invalid");
	size_t i = sizeGrp - 1;
	while(i < _arrayA.size())
	{
		size_t loser = i;
		size_t startLoser = i - (sizeGrp - 1);
		size_t winner = i + sizeGrp;

		// printMessage(DEBUGS, "i: ", i);
		// printMessage(DEBUGS, "loser: ", loser);
		// printMessage(DEBUGS, "startLoser: ", startLoser);
		// printMessage(DEBUGS, "winner: ", winner);

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
	// std::cout << BROWN << "[DEBUG] moveRange -> start: " << start;
	// std::cout << ", length: " << length;
	// std::cout << RESET << std::endl;

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

size_t	PmergeMe::_nbGrpStrict( size_t sizeArr, size_t sizeGrp )
{
	size_t res = floor(sizeArr / sizeGrp);
	// printMessage(DEBUGS, "_nbGrpStrict() - res: ", res);
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

void	PmergeMe::_initLeftOvers( size_t sizeGrp, size_t nbGrp )
{
	// printMessage(DEBUGS, "_initLeftOvers() - sizeGrp: ", sizeGrp);
	// printMessage(DEBUGS, "_initLeftOvers() - nbGrp: ", nbGrp);
	// printMessage(DEBUGS, "_initLeftOvers() - _arrayA.size(): ", _arrayA.size());
	// printMessage(DEBUGS, "_arrayA.size(): ", _arrayA.size());
	// printMessage(DEBUGS, "sizeGrp: ", sizeGrp);
	// printArray(_arrayA, 0, sizeGrp);

	// There is a rest
	// Here It's the last grp, a incomplete loser/winner, size is < sizeGrp
	// Don' t misunderstood with a complete loser
	if (_arrayA.size() % sizeGrp != 0)
	{
		// printMessage(DEBUGS, "_initLeftOvers() - is leftOver", "");
		// printMessage(DEBUGS, "_initLeftOvers() - sizeGrp: ", sizeGrp);
		size_t start = sizeGrp * (nbGrp - 1);
		for (size_t i = start; i < _arrayA.size(); ++i)
			_leftOver.push_back(_arrayA[i]);
		_arrayA.erase(_arrayA.begin() + start, _arrayA.end());
	}
	// printArray(_leftOver, 0);
}
