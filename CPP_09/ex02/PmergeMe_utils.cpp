/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe_utils.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pswirgie <pswirgie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/19 16:44:29 by pswirgie          #+#    #+#             */
/*   Updated: 2026/10/12 18:22:54 by pswirgie         ###   ########.fr       */
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

void	PmergeMe::_printArrBWithWinnerIndex( ContainerType type, size_t sizeGrp )
{
	printMessage(DEBUGS, "Print _array B with winner Index", std::string(FILLIGN - 20, '-'));
	std::cout << BLUE << "ArrB:";
	// for (size_t i = 0; i < _arrayB.size(); ++i)
	size_t i = 0;
	while ((type == VECTOR && i < _arrayB.size())
			|| (type == DEQUE && i < _DarrayB.size()))
	{
		std::cout << "	" << std::setfill('0') << std::setw(2) << (type == VECTOR ? _arrayB[i] : _DarrayB[i]);
		++i;
	}
	i = 0;
	std::cout << std::endl << LYLA << "Iwin:";
	while ((type == VECTOR && i < _indexWinnerA.size())
			|| (type == DEQUE && i < _DindexWinnerA.size()))
	{
		std::cout << std::string(sizeGrp, '	') << std::setfill('0') << std::setw(2) << (type == VECTOR ? _indexWinnerA[i] : _DindexWinnerA[i]);
		++i;
	}
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
		_DarrayA.push_back((int)nb);
	}

	if (_arrayA.size() <= 1)
		throw std::runtime_error("Only one argument, required at least two");

	if (_isSorted(_arrayA))
		throw std::runtime_error("Arguments are already sorted");
}

void	PmergeMe::clearArrayA( void )
{
	_arrayA.clear();
	_DarrayA.clear();
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
